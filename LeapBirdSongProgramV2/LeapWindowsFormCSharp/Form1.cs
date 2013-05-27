using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Leap;
using System.Media;

//NB:
// Add a reference to LeapCSharp.NET4.0.dll to the project, but make sure that Leap.dll, 
// LeapCSharp.dll & LeapCSharp.NET4.0.dll are all in the Debug folder. Must match machine configuration
// as well.


namespace LeapWindowsFormCSharp
{
    public partial class Form1 : Form
    {

        SoundPlayer player;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            player = new SoundPlayer("BirdSong.wav");

            // Create a sample listener and controller
            //SampleListener listener = new SampleListener(listBox1);
            birdSongListener birdSong = new birdSongListener(player);
            Controller controller = new Controller();

            // Have the sample listener receive events from the controller
            controller.AddListener(birdSong);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            player.PlayLooping();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            player.Stop();
        }
    }
}
