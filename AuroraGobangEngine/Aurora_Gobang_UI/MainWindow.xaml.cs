using FirstFloor.ModernUI.Windows.Controls;
using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
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

namespace Aurora_Gobang_UI
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : ModernWindow
    {
        public MainWindow()
        {
            InitializeComponent();
            paintBoard();
        }

        ~MainWindow()
        {
            try
            {
                Process p = Process.GetProcessById(cmd.Id);
                if (!p.HasExited)
                    p.Kill();
            }
            catch
            { }
        }

        private void changeState(string title,string content)
        {
            this.title.BBCode = title;
            this.content.BBCode = content;
        }

        private bool isBegin = false;
        private bool isEngineExist = false;
        
        const int range = 15;
        const int start = 25;
        const int length = 350;
        const int each = length / (range - 1);
        const int thickness = 2;
        private Color turn = Color.Black;
        private void changeTurn()
        {
            if (turn == Color.Black)
                turn = Color.White;
            else
                turn = Color.Black;
        }
        Stack<Tuple<int, int>> history = new Stack<Tuple<int, int>>();
        Color[,] board = new Color[15, 15];
        enum Color
        {
            Empty,
            Black,
            White
        }
        Color MColor;

        private string filePath = "AuroraGobangEngine.exe";
        private Process cmd;

        void begin()
        {
            if (isEngineExist)
            {
                isBegin = true;
                for (int i = 0; i < range; i++)
                {
                    for (int j = 0; j < range; j++)
                    {
                        board[i, j] = Color.Empty;
                    }
                }
                repaint();
                history.Clear();
                count = 1;
                turn = Color.Black;
                try
                {
                    Process p = Process.GetProcessById(cmd.Id);
                    if (!p.HasExited)
                        p.Kill();
                }
                catch
                { }
                cmd = new Process();
                cmd.StartInfo.FileName = filePath;
                cmd.StartInfo.UseShellExecute = false;   //将cmd的标准输入和输出全部重定向到.NET的程序里  
                //此处必须为false否则引发异常
                cmd.StartInfo.RedirectStandardError = true;
                cmd.StartInfo.RedirectStandardInput = true; //标准输入 
                cmd.StartInfo.RedirectStandardOutput = true; //标准输出   
                //不显示命令行窗口界面
                cmd.StartInfo.CreateNoWindow = true;
                cmd.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
                cmd.Start(); //启动进程
                var result = ModernDialog.ShowMessage("电脑是否执黑？", "提示", MessageBoxButton.YesNo);
                if (result == MessageBoxResult.Yes)
                {
                    cmd.StandardInput.WriteLine("Black True");
                    MColor = Color.White;
                    readNext();
                }
                else
                {
                    cmd.StandardInput.WriteLine("White True");
                    MColor = Color.Black;
                    changeState("正在游戏中...正在下第" + count + "步", "没有上一步");
                }
                this.begin_btn.Content = "重新开始";
                
            }
            else
            {
                ModernDialog.ShowMessage("引擎尚未加载！", "警告", MessageBoxButton.OK);
            }
        }

        int count = 1;
        private void inputChess(Tuple<int, int> axis)
        {
            if (isBegin)
            {
                board[axis.Item1, axis.Item2] = turn;
                history.Push(axis);
                string s = "";

                int x = history.First().Item1;
                int y = history.First().Item2;
                s = "上一步是" + board[x, y] + "(" + x + "," + y + ")";
                changeState("正在游戏中...正在下第" + (++count) + "步", s);
                repaint();

                changeTurn();
            }
            else
            {
                if (isEngineExist)
                {
                    ModernDialog.ShowMessage("游戏尚未开始", "警告", MessageBoxButton.OK);
                }
                else
                {
                    ModernDialog.ShowMessage("引擎尚未加载！", "警告", MessageBoxButton.OK);
                }
            }
        }
        private void readNext()
        {
            string s = cmd.StandardOutput.ReadLine();
            if (s.StartsWith("BlackWin") || s.StartsWith("WhiteWin"))
            {
                Color winColor = s.StartsWith("BlackWin") ? Color.Black : Color.White;
                s = s.Replace("BlackWin ", "");
                s = s.Replace("WhiteWin ", "");
                string[] temp = s.Split(' ');
                int x = int.Parse(temp[0]);
                int y = int.Parse(temp[1]);
                inputChess(new Tuple<int, int>(x, y));
                if (MColor == winColor)
                {
                    ModernDialog.ShowMessage("你战胜了电脑！", "恭喜", MessageBoxButton.OK);
                    changeState("恭喜", "你战胜了电脑！\t下一局游戏尚未开始");
                }
                else
                {
                    ModernDialog.ShowMessage("你输了！", "抱歉", MessageBoxButton.OK);
                    changeState("你输了！", "抱歉\t下一局游戏尚未开始");
                }
                isBegin = false;
            }
            else
            {
                string[] temp = s.Split(' ');
                int x = int.Parse(temp[0]);
                int y = int.Parse(temp[1]);
                inputChess(new Tuple<int, int>(x, y));
            }
        }


        private Tuple<int,int> getChess()
        {
            return new Tuple<int, int>(1, 1);
        }

        private void paintBoard()
        {
            for (int i = 0; i < range; i++)
            {
                Line rowLine = new Line();
                rowLine.Stroke = Brushes.Black;
                rowLine.StrokeThickness = thickness;
                rowLine.X1 = start;
                rowLine.Y1 = start + each * i;
                rowLine.X2 = start + length;
                rowLine.Y2 = start + each * i;
                TextBlock tb_row = new TextBlock();
                if (i < 10)
                    tb_row.Text = " " + i;
                else
                    tb_row.Text = "" + i;
                tb_row.FontWeight = FontWeights.Bold;
                tb_row.TextAlignment = TextAlignment.Right;
                chessBoard.Children.Add(tb_row);
                Canvas.SetLeft(tb_row, start - 25);
                Canvas.SetTop(tb_row, start + each * i - 10);
                chessBoard.Children.Add(rowLine);
                
                Line columnLine = new Line();
                columnLine.Stroke = Brushes.Black;
                columnLine.StrokeThickness = thickness;
                columnLine.X1 = start + each * i;
                columnLine.Y1 = start;
                columnLine.X2 = start + each * i;
                columnLine.Y2 = start + length;
                TextBlock tb_column = new TextBlock();
                if (i < 10)
                    tb_column.Text = " " + i;
                else
                    tb_column.Text = "" + i;
                chessBoard.Children.Add(columnLine);
                tb_column.FontWeight = FontWeights.Bold;
                chessBoard.Children.Add(tb_column);
                Canvas.SetLeft(tb_column, start + each * i - 10);
                Canvas.SetTop(tb_column, start - 25);
            }

            int[,] points = new int[5, 2] { { 7, 7 }, { 3, 3 }, { 11, 3 }, { 3, 11 }, { 11, 11 } };
            for (int i = 0; i < 5; i++)
            {
                Ellipse point = new Ellipse();
                point.Height = 8;
                point.Width = 8;
                point.Fill = Brushes.Black;
                chessBoard.Children.Add(point);
                Canvas.SetLeft(point, start + points[i, 0] * each - 4);
                Canvas.SetTop(point, start + points[i, 1] * each - 4);
            }
            
        }

        private void repaint()
        {
            chessBoard.Children.Clear();
            paintBoard();
            for (int row = 0; row < range; row++)
            {
                for (int column = 0; column < range; column++)
                {
                    Color color = Color.Empty;
                    switch (board[row, column])
                    {
                        case Color.Empty:
                            break;
                        case Color.Black:
                            color = Color.Black;
                            break;
                        case Color.White:
                            color = Color.White;
                            break;
                    }
                    if (color != Color.Empty)
                    {
                        Button chess = new Button();
                        chess.Style = (Style)FindResource("GlassChess");
                        chess.Height = 20;
                        chess.Width = 20;
                        switch (color)
                        {
                            case Color.Black:
                                chess.Background = Brushes.Black;
                                break;
                            case Color.White:
                                chess.Background = Brushes.White;
                                chess.BorderBrush = Brushes.Black;
                                break;
                        }
                        int _row = row * each;
                        int _column = column * each;
                        chessBoard.Children.Add(chess);
                        chess.ToolTip = row + "," + column;
                        //chess.Click += (sender, e) =>
                        //{
                        //    Point pt = chess.(chessBoard);
                        //    int _X = (int)(pt.X + each / 2 - start) / each;
                        //    int _Y = (int)(pt.Y + each / 2 - start) / each;
                        //    foreach (var item in history)
                        //    {
                        //        if (_X == item.Item1 && _Y == item.Item2)
                        //        {
                        //            ModernDialog.ShowMessage("走于第" + history.First(c => _X == c.Item1 && c.Item2 == _Y), "提示", MessageBoxButton.OK);
                        //        }
                        //    }
                        //};
                        Canvas.SetTop(chess, start + _row - 10);
                        Canvas.SetLeft(chess, start + _column - 10);
                    }
                }
            }
        }

        private void chessBoard_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (isBegin)
            {
                Point pt = e.GetPosition(chessBoard);
                int column = (int)(pt.X + each / 2 - start) / each;
                int row = (int)(pt.Y + each / 2 - start) / each;
                if (board[row, column] != Color.Empty)
                {
                    ModernDialog.ShowMessage("该处已经有棋子了！", "提示", MessageBoxButton.OK);
                }
                else
                {
                    inputChess(new Tuple<int, int>(row, column));
                    cmd.StandardInput.WriteLine(row + " " + column);
                    readNext();
                }
            }
            else
            {
                ModernDialog.ShowMessage("游戏尚未开始！", "提示", MessageBoxButton.OK);
            }
        }

        private void ModernWindow_Loaded(object sender, RoutedEventArgs e)
        {
            if (File.Exists("AuroraGobangEngine.exe"))
            {
                changeState("加载引擎成功", "游戏开始");
                isEngineExist = true;
                begin();
            }
            else
            {
                changeState("未找到引擎", "请手动加载引擎");
                isEngineExist = false;
            }
            
        }

        private void About_Click(object sender, RoutedEventArgs e)
        {
            ModernDialog.ShowMessage("AuroraDysis制作，QQ:814613512", "关于", MessageBoxButton.OK);
        }

        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void Load_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog fd = new OpenFileDialog();
            fd.Filter = "Aurora引擎(*.exe)|*.exe";
            Nullable<bool> result = fd.ShowDialog();
            if (result == true)
            {
                filePath = fd.FileName;
                changeState("加载引擎成功", "游戏开始");
                isEngineExist = true;
                begin();
            }
            else
            {
                ModernDialog.ShowMessage("未成功加载引擎", "警告", MessageBoxButton.OK);
            }
            
        }

        private void begin_btn_Click(object sender, RoutedEventArgs e)
        {
            begin();
        }

        private void Clear_Click(object sender, RoutedEventArgs e)
        {
            //string path = "";
            //if (filePath.Contains("\\"))
            //{
            //    string name = System.IO.Path.GetFileName(filePath);
            //    path = filePath.Replace(name, "");
            //}
            int i = 1;
            while (File.Exists("history" + i + ".txt"))
            {
                File.Delete("history" + i++ + ".txt");
            }
        }

        private void Undo_Click(object sender, RoutedEventArgs e)
        {
            if (isBegin)
            {
                cmd.StandardInput.WriteLine("UNDO");
                string strCount = cmd.StandardOutput.ReadLine();
                int times = int.Parse(strCount);
                for (int i = 0; i < times; i++)
                {
                    Tuple<int, int> axis = history.Pop();
                    board[axis.Item1, axis.Item2] = Color.Empty;
                    count--;
                    changeTurn();
                    string s = "";
                    if (history.Count != 0)
                    {
                        s = "上一步是" + board[history.First().Item1, history.First().Item2] + "(" + history.First().Item1 + "," + history.First().Item2 + ")";
                    }
                    else
                    {
                        s = "没有上一步";
                    }
                    changeState("正在游戏中...正在下第" + count + "步", s);
                }
                repaint();
            }
        }
    }
}
