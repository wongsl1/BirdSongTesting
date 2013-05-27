// Leap Sample Test.cpp : main project file.


#include "stdafx.h"
#include "Leap.h"

using namespace System;
using namespace Leap;

	class SampleListener : public Listener {
	  public:
			virtual void onInit(const Controller&);
			virtual void onConnect(const Controller&);
			virtual void onDisconnect(const Controller&);
			virtual void onExit(const Controller&);
			virtual void onFrame(const Controller&);
	
		private:
			double lastPalmPositionY;
			double lastPalmPositionX;
	};

	void SampleListener::onInit(const Controller& controller) {
	  std::cout << "Initialized" << std::endl;
	  lastPalmPositionY = 0;
	  lastPalmPositionX = 0;
	}

	void SampleListener::onConnect(const Controller& controller) {
	  std::cout << "Connected" << std::endl;
	  controller.enableGesture(Gesture::TYPE_CIRCLE);
	  controller.enableGesture(Gesture::TYPE_KEY_TAP);
	  controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
	  controller.enableGesture(Gesture::TYPE_SWIPE);
	}

	void SampleListener::onDisconnect(const Controller& controller) {
	  std::cout << "Disconnected" << std::endl;
	}

	void SampleListener::onExit(const Controller& controller) {
	  std::cout << "Exited" << std::endl;
	}
	
	void SampleListener::onFrame(const Controller& controller) 
	{
	  
		// Get the most recent frame and report some basic information
	  const Frame frame = controller.frame();

		int currentFrameId = frame.id();
		//std::cout << "CurrentFrameId " << currentFrameId << std::endl;

		if (frame.hands().count() > 0)
		{	
				//std::cout << "Frame id: " << frame.id()
				//<< ", timestamp: " << frame.timestamp()
				//<< ", hands: " << frame.hands().count()
			//	<< ", fingers: " << frame.fingers().count()
			//	<< ", tools: " << frame.tools().count()
			//	<< ", gestures: " << frame.gestures().count() << std::endl;
	
				// Dealing with the hands

		  if (!frame.hands().empty()) 
		  {
			// Get the first hand
			const Hand hand = frame.hands()[0];

			// Check if the hand has any fingers
			const FingerList fingers = hand.fingers();
			if (!fingers.empty()) {
			  // Calculate the hand's average finger tip position
			  Vector avgPos;
			  for (int i = 0; i < fingers.count(); ++i) {
				avgPos += fingers[i].tipPosition();
			  }
			  avgPos /= (float)fingers.count();
			  //std::cout << "Hand has " << fingers.count()
						//<< " fingers, average finger tip position" << avgPos << std::endl;
			}

			// Get the hand's sphere radius and palm position
			/*std::cout << "Hand sphere radius: " << hand.sphereRadius()
					  << " mm, palm position: " << hand.palmPosition() << std::endl;*/

			//deatecting Up and Down hand motions
			Vector myPalmPosition = hand.palmPosition();

			double currentPalmPositionY = myPalmPosition.y;

			if (currentPalmPositionY > lastPalmPositionY) 
			{
				std::cout << "[moving up";
			}
			else
			{
				std::cout << "[moving down";
			}

			lastPalmPositionY = currentPalmPositionY;

			//deatecting left and right hand motions
			myPalmPosition = hand.palmPosition();

			double currentPalmPositionX = myPalmPosition.x;

			if (currentPalmPositionX > lastPalmPositionX) 
			{
				std::cout << "/right] ";
			}
			else
			{
				std::cout << "/left] ";
			}

			lastPalmPositionX = currentPalmPositionX;

			// Get the hand's normal vector and direction
			const Vector normal = hand.palmNormal();
			const Vector direction = hand.direction();

			// Calculate the hand's pitch, roll, and yaw angles
			//std::cout << "Hand pitch: " << direction.pitch() * RAD_TO_DEG << " degrees, "
					//  << "roll: " << normal.roll() * RAD_TO_DEG << " degrees, "
					//<< "yaw: " << direction.yaw() * RAD_TO_DEG << " degrees" << std::endl;
	 
			//Find Gestures
// Get gestures
	  const GestureList gestures = frame.gestures();
	  for (int g = 0; g < gestures.count(); ++g) {
		Gesture gesture = gestures[g];

		switch (gesture.type()) {
		  case Gesture::TYPE_CIRCLE:
		  {
			CircleGesture circle = gesture;
			std::string clockwiseness;

			if (circle.pointable().direction().angleTo(circle.normal()) <= PI/4) {
			  std::cout << " CLOCKWISE";
			} else {
			  std::cout << " ANTICLOCKWISE";
			}
			break;
		  }
		  case Gesture::TYPE_SWIPE:
		  {
			std::cout << " SWIPE";
			break;
		  }
		  case Gesture::TYPE_KEY_TAP:
		  {
			std::cout << " KEY TAP";
			break;
		  }
		  case Gesture::TYPE_SCREEN_TAP:
		  {
			std::cout << " SCREEN TAP";
			break;
		  }
		  default:
			std::cout << "Unknown gesture type." << std::endl;
			break;
		}
	  }
			if (!frame.hands().empty()) {
					std::cout << std::endl;
			}

  } // end if frame print
  } // end on frame
} /* end class SampleListener */

int main(array<System::String ^> ^args)
{
    Console::WriteLine(L"Plug in the Leap and see if you get output....");

    
	 // Create a sample listener and controller
	SampleListener listener;
	Controller controller;

	// Have the sample listener receive events from the controller
	controller.addListener(listener);

	// Keep this process running until Enter is pressed
	std::cout << "Press Enter to quit..." << std::endl;
	std::cin.get();

	// Remove the sample listener when done
	controller.removeListener(listener);

	return 0;
}
