/*
 * RepRap Ltd Open-source Oxygen Concentrator Control Program
 * 
 * https://reprapltd.com
 * 
 * Device: Arduino Uno
 * 
 * Adrian Bowyer
 * 24 March 2020
 * 
 * Licence: GPL
 * 
 * See: https://github.com/RepRapLtd/Oxygen-concentrator
 * 
 * Version 2
 * 9 April 2020
 * 
 */

// ZeolitePath is one half of the Oxygen Concentrator - either the left or the right arm.

#ifndef ZEOLITEPATH_H
#define ZEOLITEPATH_H


// The states the machine's arms can be in.

enum State { idle, o2Feed, purging, shuttingDown };

class ZeolitePath
{
  public:

    ZeolitePath(int fi, int pi, int oo, int po);

    // Tell this path about the opposite path in the machine
    
    void SetOtherPath(ZeolitePath* op);

    // Called in the main loop to run the valve sequence.  This should neither call delay()
    // nor call any functions that call delay(); that is it should always return after a few microseconds.
    
    void Spin();


  private:

    // Start the O2 flow from this path
    
    void StartFeed();

    // Switch from O2 flow to purging
    
    void SwitchToPurge();

    // Finish purging
    
    void EndPurge();

    // Shut down (i.e. close all valves)

    void ShutDown();

// The Arduino pins that drive the solenoid valves

    int feedIn;
    int purgeIn;
    int o2Out;
    int purgeOut;

// What stage in the process this arm is at.

    State state;

// The other half of the machine

    ZeolitePath* otherPath;

// Timing. lastTime is the last time something happened.  interval is how long until
// the next thing needs to happen.

    unsigned long lastTime;
    unsigned long interval;

// Flag so we know a request for O2 is waiting

    bool o2Requested;
  
};

// Tell this path about the opposite path in the machine
    
inline void ZeolitePath::SetOtherPath(ZeolitePath* op) { otherPath = op; } 


#endif
