using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Leap;
using System.Media;

namespace LeapWindowsFormCSharp
{
    class birdSongListener : Listener
    {
        private delegate void writeLineDel(string line);

        private Object thisLock;
        private SoundPlayer soundPlayer;

        public birdSongListener(SoundPlayer soundPlayer)
        {
            this.soundPlayer = soundPlayer;
            thisLock = new Object();
        }

        public void lineToBox(string line)
        {
            //displayBox.Items.Add(line);
        }


        private void SafeWriteLine(String line)
        {
            lock (thisLock)
            {
                writeLineDel writeLineDel = new writeLineDel(lineToBox);
                //displayBox.Invoke(writeLineDel, line);
            }
        }

        public override void OnInit(Controller controller)
        {
            //SafeWriteLine("OnInit Raised");
        }

        public override void OnConnect(Controller controller)
        {
            //SafeWriteLine("OnConnect Raised");
            controller.EnableGesture(Gesture.GestureType.TYPECIRCLE);
            controller.EnableGesture(Gesture.GestureType.TYPEKEYTAP);
            controller.EnableGesture(Gesture.GestureType.TYPESCREENTAP);
            controller.EnableGesture(Gesture.GestureType.TYPESWIPE);
        }

        public override void OnDisconnect(Controller controller)
        {
            //SafeWriteLine("OnDisconnect Raised");
        }

        public override void OnExit(Controller controller)
        {
            //SafeWriteLine("On Exit Raised");
        }

        public override void OnFrame(Controller controller)
        {
            // Get the most recent frame and report some basic information
            Frame frame = controller.Frame();

            // Get gestures
            GestureList gestures = frame.Gestures();
            for (int i = 0; i < gestures.Count; i++)
            {
                Gesture gesture = gestures[i];

                switch (gesture.Type)
                {
                    case Gesture.GestureType.TYPEKEYTAP:
                        soundPlayer.Play();
                        break;
                    case Gesture.GestureType.TYPESCREENTAP:
                        soundPlayer.Stop();
                        break;
                    default:
                        break;
                }
            }
        }
    }
}
