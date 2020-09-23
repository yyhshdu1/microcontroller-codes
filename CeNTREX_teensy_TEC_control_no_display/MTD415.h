#ifndef mtd415_h
#define mtd415_h
#include "Arduino.h"

class MTD415{
  public:
    MTD415(Stream *serial);
    // General
    String getVersion();
    String getUUID();
    int getErrorRegister();
    void resetErrorRegister();
    // Temperature
    int getTemperature();
    int getTemperatureSetpoint();
    int getTemperatureWindow();
    int getTemperatureWindowDelay();
    // TEC
    int getTECCurrentLimit();
    int getTECCurrentActual();
    int getTECVoltage();
    // Control Loop
    int getCriticalGain();
    int getCriticalPeriod();
    int getCyclingTime();
    int getProportional();
    int getIntegral();
    int getDerivative();
    // Set commands
    void setTemperatureSetpoint(int setpoint);
    void setTemperatureWindow(int window);
    void setTemperatureWindowDelay(int delay);
    void setTECCurrentLimit(int limit);
    void setCriticalGain(int cricital_gain);
    void setCriticalPeriod(int cricital_period);
    void setCyclingTime(int cycling_time);
    void setProportional(int proportional);
    void setIntegral(int integral);
    void setDerivative(int derivative);
    void saveSetup();
  private:
    Stream *_serial;
    String _response;
    String _getResponse();
    int _intReturnCMD(String cmd);
    String _stringReturnCMD(String cmd);
    void _writeCommand(String cmd, int value);
    void _writeCommand(String cmd);
};

#endif
