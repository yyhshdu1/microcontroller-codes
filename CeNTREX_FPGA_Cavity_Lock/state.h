#ifndef state_h
#define state_h
#include "Arduino.h"

class State
{
  public:
    State(int in1, int in2, int out1, int out2);
    void getState();
    void toggleLock();
    void writeLock(int lock);
    void toggleScan();
    void writeScan(int scan);
    int lockState;
    int lockedState;
    int scanState;
  private:
    int _in1;
    int _in2;
    int _out1;
    int _out2;
};

#endif
