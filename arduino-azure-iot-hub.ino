// Copyright (c) Microsoft. All rights reserved.
#include "iot_configs.h"

#include <AzureIoTHub.h>
#if defined(IOT_CONFIG_MQTT)
    #include <AzureIoTProtocol_MQTT.h>
#elif defined(IOT_CONFIG_HTTP)
    #include <AzureIoTProtocol_HTTP.h>
#endif

#include "sample.h"
#include "esp8266/sample_init.h"

static char ssid[] = IOT_CONFIG_WIFI_SSID;
static char pass[] = IOT_CONFIG_WIFI_PASSWORD;

const int MOTOR_PWM_LEFT = D1;
const int MOTOR_PWM_RIGHT = D2;

const int MOTOR_DIR_LEFT = D3;
const int MOTOR_DIR_RIGHT = D4;

#define MOTOR_BACK LOW
#define MOTOR_FWD HIGH

void setup() {
  pinMode(MOTOR_PWM_LEFT, OUTPUT);
  pinMode(MOTOR_DIR_LEFT, OUTPUT);
  pinMode(MOTOR_PWM_RIGHT, OUTPUT);
  pinMode(MOTOR_DIR_RIGHT, OUTPUT);

  digitalWrite(MOTOR_PWM_LEFT, HIGH);
  digitalWrite(MOTOR_PWM_RIGHT, HIGH);

  analogWrite(MOTOR_PWM_LEFT, 0);
  analogWrite(MOTOR_PWM_RIGHT, 0);
  
  sample_init(ssid, pass);
}

static bool done = false;
void loop() {
    if (!done)
    {
        execute();
        done = true;
    }
    else
    {
      delay(500);
    }
}

void forward()
{
  digitalWrite(MOTOR_DIR_LEFT, MOTOR_FWD);
  digitalWrite(MOTOR_DIR_RIGHT, MOTOR_BACK);

  analogWrite(MOTOR_PWM_LEFT, 1023);
  analogWrite(MOTOR_PWM_RIGHT, 1023);
}

void backward()
{
  digitalWrite(MOTOR_DIR_LEFT, MOTOR_BACK);
  digitalWrite(MOTOR_DIR_RIGHT, MOTOR_FWD);

  analogWrite(MOTOR_PWM_LEFT, 1023);
  analogWrite(MOTOR_PWM_RIGHT, 1023);
}

void stopcar()
{
  analogWrite(MOTOR_PWM_LEFT, 0);
  analogWrite(MOTOR_PWM_RIGHT, 0);
}

void left()
{
  digitalWrite(MOTOR_DIR_LEFT, MOTOR_BACK);
  digitalWrite(MOTOR_DIR_RIGHT, MOTOR_BACK);

  analogWrite(MOTOR_PWM_LEFT, 1023);
  analogWrite(MOTOR_PWM_RIGHT, 1023);
}

void right()
{
  digitalWrite(MOTOR_DIR_LEFT, MOTOR_FWD);
  digitalWrite(MOTOR_DIR_RIGHT, MOTOR_FWD);
  
  analogWrite(MOTOR_PWM_LEFT, 1023);
  analogWrite(MOTOR_PWM_RIGHT, 1023);
}
