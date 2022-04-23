#include <Adafruit_MPU6050.h>
#include<Adafruit_Sensor.h>
#include<Wire.h>

Adafruit_MPU6050 mpu;

void imu_setup(){
  if(!mpu.begin())
  {
    Serial.println("Sensor error! Try Again");
    while(1)
    {};
    }
    Serial.println("IMU initiated");

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
    }
  void imu_read(float *ax, float *ay, float *az)
  {
    sensors_event_t a,g, temp;
    mpu.getEvent(&a,&g,&temp);
    *ax=a.acceleration.x;
    *ay=a.acceleration.y;
    *az=a.acceleration.z;
    }
