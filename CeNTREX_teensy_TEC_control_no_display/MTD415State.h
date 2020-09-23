#ifndef mtd415state_h
#define mtd415state_h
#include "Arduino.h"
#include "MTD415.h"

struct connections{
  MTD415 *devices[4];
  int nrdevices;
};
typedef struct connections Connections;

class MTD415State{
  public:
    MTD415State(MTD415 *control_1, MTD415 *control_2, MTD415 *control_3, MTD415 *control_4);
    MTD415State(MTD415 *control_1, MTD415 *control_2, MTD415 *control_3);
    MTD415State(MTD415 *control_1, MTD415 *control_2);
    MTD415State(MTD415 *control);
    int devices;
    // General
    void updateVersion();
    void getVersion(String * arr);
    void updateUUID();
    void getUUID(String * arr);
    void updateErrorRegister();
    void getErrorRegister(int * arr);
    void resetErrorRegister(int device);
    // Temperature
    void updateTemperature();
    void getTemperature(int * arr);
    int getTemperature(int dev);
    void updateTemperatureSetpoint();
    void getTemperatureSetpoint(int * arr);
    int getTemperatureSetpoint(int dev);
    void setTemperatureSetpoint(int * arr);
    void updateTemperatureWindow();
    void getTemperatureWindow(int * arr);
    int getTemperatureWindow(int dev);
    void setTemperatureWindow(int * arr);
    void updateTemperatureWindowDelay();
    void getTemperatureWindowDelay(int * arr);
    int getTemperatureWindowDelay(int dev);
    void setTemperatureWindowDelay(int * arr);
    // TEC
    void updateTECCurrentLimit();
    void getTECCurrentLimit(int * arr);
    int getTECCurrentLimit(int dev);
    void updateTECCurrentActual();
    void getTECCurrentActual(int * arr);
    int getTECCurrentActual(int dev);
    void updateTECVoltage();
    void getTECVoltage(int * arr);
    int getTECVoltage(int dev);
    void setTECCurrentLimit(int * arr);
    // Control loop
    void updateCriticalGain();
    void getCriticalGain(int * arr);
    int getCriticalGain(int dev);
    void updateCriticalPeriod();
    void getCriticalPeriod(int * arr);
    int getCriticalPeriod(int dev);
    void updateCyclingTime();
    void getCyclingTime(int * arr);
    int getCyclingTime(int dev);
    void updateProportional();
    void getProportional(int * arr);
    int getProportional(int dev);
    void updateIntegral();
    void getIntegral(int * arr);
    int getIntegral(int dev);
    void updateDerivative();
    void getDerivative(int * arr);
    int getDerivative(int dev);
    void setCriticalGain(int * arr);
    void setCriticalPeriod(int * arr);
    void setCyclingTime(int * arr);
    void setProportional(int * arr);
    void setIntegral(int * arr);
    void setDerivative(int * arr);
    // save settings
    void saveSetup(int device);
    // init    
    void initAll();
    // enabled
    void getEnabled(bool * arr);
  private:
    Connections _connections;
    int _devices;
    // Temperature
    int _temperature[4];
    int _temperature_setpoint[4];
    int _temperature_window[4];
    int _temperature_window_delay[4];
    // TEC
    int _tec_current_limit[4];
    int _tec_current_actual[4];
    int _tec_voltage[4];
    // Control loop
    int _critical_gain[4];
    int _critical_period[4];
    int _cycling_time[4];
    int _proportional[4];
    int _integral[4];
    int _derivate[4];
    String _version[4];
    String _uuid[4];
    int _error[4];
    bool _enabled[4];
    int _bitmask;
};

#endif
