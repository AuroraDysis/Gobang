using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Gobang_UI
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        private bool flag = true, beginflag = true, again_exit = true;
        private int[][] position = new int[15][];
        private int X, Y = 0;
        private Process cmd = new Process();

        public MainWindow()
        {
            InitializeComponent();
            paint();
            initalize();
            
            cmd.StartInfo.FileName = "AuroraGobangEngine.exe";
            cmd.StartInfo.UseShellExecute = false;   //将cmd的标准输入和输出全部重定向到.NET的程序里  
            //此处必须为false否则引发异常
            cmd.StartInfo.RedirectStandardError = true;
            cmd.StartInfo.RedirectStandardInput = true; //标准输入 
            cmd.StartInfo.RedirectStandardOutput = true; //标准输出   
            //不显示命令行窗口界面  
            cmd.StartInfo.CreateNoWindow = true;
            cmd.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
            cmd.Start(); //启动进程

            if (MessageBoxResult.Yes == MessageBox.Show("我是否用黑棋？", "设置", MessageBoxButton.YesNo))
            {
                cmd.StandardInput.WriteLine("0");
                outputAxis(cmd.StandardOutput.ReadLine());
            }
            else
            {
                cmd.StandardInput.WriteLine("1");
            }
        }
        ~MainWindow()
        {
            //cmd.StandardInput.WriteLine("exit");
            //var th = Process.GetProcessesByName("AuroraGobangEngine.exe（32位）");
            try
            {
                Process p = Process.GetProcessById(cmd.Id);
                if (!p.HasExited)
                {
                    p.Kill();
                }
            }
            catch
            {
            }
        }

        public void initalize()
        {
            for (int i = 0; i < 15; i++)
            {
                position[i] = new int[15];
                for (int j = 0; j < 15; j++)
                    position[i][j] = 0;
            }
        }

        private Point center = new Point(140, 140);

        private void outputAxis(string output)
        {
            string[] temp = output.Split(' ');
            int X = int.Parse(temp[0]);
            int Y = int.Parse(temp[1]);

            if (beginflag)
            {
                Ellipse chess = new Ellipse();

                chess.Width = 20;
                chess.Height = 20;
                Point pt = new Point();
                pt.X = (X - 7) * 20 + center.X;
                pt.Y = (Y - 7) * 20 + center.Y;
                if (position[X][Y] != 0) MessageBox.Show("该处已经有棋子，请在其它地方落子！", "提示");
                else
                {
                    if (flag)
                    {
                        chess.Fill = Brushes.Black;
                        position[X][Y] = 1;
                        flag = false;
                    }
                    else
                    {
                        chess.Fill = Brushes.White;
                        chess.Stroke = Brushes.Black;
                        position[X][Y] = 2;
                        flag = true;
                    }
                    CanvasChess.Children.Add(chess);
                    Canvas.SetTop(chess, pt.Y - 10);
                    Canvas.SetLeft(chess, pt.X - 10);
                }
            }
        }

        private void inputAxis(int x, int y)
        {
            cmd.StandardInput.WriteLine(x + " " + y);
            outputAxis(cmd.StandardOutput.ReadLine());
        }

        public void paint()
        {

            for (int i = 0; i < 15; i++)
            {
                Line myline = new Line();
                Line yourline = new Line();
                myline.Stroke = new SolidColorBrush(Color.FromRgb(0, 0, 0));
                yourline.Stroke = new SolidColorBrush(Color.FromRgb(0, 0, 0));
                myline.X1 = 0;
                myline.X2 = 280;
                yourline.Y1 = 0;
                yourline.Y2 = 280;
                myline.Y1 = i * 20;
                myline.Y2 = i * 20;
                yourline.X1 = i * 20;
                yourline.X2 = i * 20;
                CanvasChess.Children.Add(myline);
                CanvasChess.Children.Add(yourline);

            }
        }

        public void repaint()
        {

            CanvasChess.Children.Clear();
            paint();
            if (position[X][Y] == 1) flag = true;
            else flag = false;
            position[X][Y] = 0;
            for (int i = 0; i < 15; i++)
            {
                for (int j = 0; j < 15; j++)
                    if (position[i][j] != 0)
                    {
                        Ellipse chess = new Ellipse();
                        chess.Width = 20;
                        chess.Height = 20;
                        if (position[i][j] == 1)
                            chess.Fill = Brushes.Black;
                        else
                        {
                            chess.Fill = Brushes.White;
                            chess.Stroke = Brushes.Black;
                        }
                        CanvasChess.Children.Add(chess);
                        Canvas.SetTop(chess, j * 20 - 10);
                        Canvas.SetLeft(chess, i * 20 - 10);

                    }
                if (JudgeWin()) { Thread.Sleep(100); MessageBox.Show("You had won! Again,exit?"); again_exit = false; }
            }
        }
        private Boolean JudgeWin()
        {
            Boolean flag = false;
            int i;
            for (i = 1; i <= 4 && Y + i >= 0 && Y + i <= 14 && position[X][Y] == position[X][Y + i]; i++) if (i == 4) flag = true;
            for (i = 1; i <= 4 && Y - i >= 0 && Y - i <= 14 && position[X][Y] == position[X][Y - i]; i++) if (i == 4) flag = true;
            for (i = 1; i <= 4 && X + i >= 0 && X + i <= 14 && position[X][Y] == position[X + i][Y]; i++) if (i == 4) flag = true;
            for (i = 1; i <= 4 && X - i >= 0 && X - i <= 14 && position[X][Y] == position[X - i][Y]; i++) if (i == 4) flag = true;
            for (i = 1; i <= 4 && X + i >= 0 && X + i <= 14 && Y + i >= 0 && Y + i <= 14 && position[X][Y] == position[X + i][Y + i]; i++) if (i == 4) flag = true;
            for (i = 1; i <= 4 && X - i >= 0 && X - i <= 14 && Y - i >= 0 && Y - i <= 14 && position[X][Y] == position[X - i][Y - i]; i++) if (i == 4) flag = true;
            for (i = 1; i <= 4 && X - i >= 0 && X - i <= 14 && Y + i >= 0 && Y + i <= 14 && position[X][Y] == position[X - i][Y + i]; i++) if (i == 4) flag = true;
            for (i = 1; i <= 4 && X + i >= 0 && X + i <= 14 && Y - i >= 0 && Y - i <= 14 && position[X][Y] == position[X + i][Y - i]; i++) if (i == 4) flag = true;
            return flag;
        }

        

        #region 事件处理
        private void CanvasChess_MouseDown(object sender, MouseButtonEventArgs e)
        {

            if (beginflag == false) MessageBox.Show("你已经认输了，请重新开始", "信息", MessageBoxButton.OK, MessageBoxImage.Warning);
            else if (again_exit == false) MessageBox.Show("You had won! Again,exit?");
            else if (beginflag == true || again_exit == true)
            {
                Ellipse chess = new Ellipse();
                Point pt = e.GetPosition(CanvasChess);
                chess.Width = 20;
                chess.Height = 20;
                X = (int)(pt.X + 10) / 20; Y = (int)(pt.Y + 10) / 20;
                pt.X = (int)(pt.X + 10) / 20 * 20;
                pt.Y = (int)(pt.Y + 10) / 20 * 20;
                if (position[X][Y] != 0) MessageBox.Show("该处已经有棋子，请在其它地方落子！", "提示");
                else
                {
                    if (flag)
                    {
                        chess.Fill = Brushes.Black;
                        position[X][Y] = 1;
                        flag = false;
                    }
                    else
                    {
                        chess.Fill = Brushes.White;
                        chess.Stroke = Brushes.Black;
                        position[X][Y] = 2;
                        flag = true;
                    }
                    CanvasChess.Children.Add(chess);
                    Canvas.SetTop(chess, pt.Y - 10);
                    Canvas.SetLeft(chess, pt.X - 10);
                    if (JudgeWin()) { Thread.Sleep(100); MessageBox.Show("You had won! Again,exit?"); again_exit = false; }
                    inputAxis(X, Y);
                }

            }
        }

        private void Set_Click(object sender, RoutedEventArgs e)
        {
            //if (MessageBoxResult.No == MessageBox.Show("是否黑子先下？", "游戏设置", MessageBoxButton.YesNo))
            //    flag = false;
        }


        private void Explain_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("五颗同一颜色的棋连成一条线则是赢家", "游戏说明");
        }


        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            ChessWindow.Close();
        }

        private void Help_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("AuroraDysis", "WPF", MessageBoxButton.OK, MessageBoxImage.Information);
        }

        private void Loser_Click(object sender, RoutedEventArgs e)
        {

            if (MessageBoxResult.OK == MessageBox.Show("你已经认输了，请重新开始", "信息", MessageBoxButton.OKCancel, MessageBoxImage.Warning))
                beginflag = false;
        }

        private void Undo_Click(object sender, RoutedEventArgs e)
        {
            if (beginflag == true && again_exit == true)
                repaint();

        }

        private void Begin_Click(object sender, RoutedEventArgs e)
        {
            beginflag = true;
            again_exit = true;
            CanvasChess.Children.Clear();
            initalize();
            paint();
        }
        #endregion
    }
}
