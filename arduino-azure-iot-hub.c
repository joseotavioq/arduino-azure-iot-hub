#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "AzureIoTHub.h"
#include "iot_configs.h"
#include "sample.h"

static const char* connectionString = IOT_CONFIG_CONNECTION_STRING;
static char propText[1024];

static IOTHUBMESSAGE_DISPOSITION_RESULT ReceiveMessageCallback(IOTHUB_MESSAGE_HANDLE message, void* userContextCallback)
{
    const char* buf;
    size_t len;

    // Message content
    if (IoTHubMessage_GetByteArray(message, (const unsigned char**)&buf, &len) != IOTHUB_MESSAGE_OK)
    {
        (void)printf("Unable to retrieve the message data\r\n");
    }
    else
    {
      char* temp = malloc(len + 1);
      memcpy(temp, buf, len);
      temp[len] = '\0';
      
      (void)printf("Data: [%.*s]\r\n", (int)len, temp);
      
      if(strcmp(temp, "forward") == 0)
      {
        forward();
      }
      else if(strcmp(temp, "backward") == 0)
      {
        backward();
      }
      else if(strcmp(temp, "left") == 0)
      {
        left();
      }
      else if(strcmp(temp, "right") == 0)
      {
        right();
      }

      delay(300);
      stopcar();

      free(temp);
    }

    return IOTHUBMESSAGE_ACCEPTED;
}

void execute(void)
{
    if (platform_init() != 0)
    {
        (void)printf("Failed to initialize platform.\r\n");
    }
    else
    {
        if (serializer_init(NULL) != SERIALIZER_OK)
        {
            (void)printf("Failed on serializer_init\r\n");
        }
        else
        {
          IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle = IoTHubClient_LL_CreateFromConnectionString(connectionString, MQTT_Protocol);
          srand((unsigned int)time(NULL));
  
          if (iotHubClientHandle == NULL)
          {
              (void)printf("Failed on IoTHubClient_LL_Create\r\n");
          }
          else
          {
  #ifdef SET_TRUSTED_CERT_IN_SAMPLES
            // For mbed add the certificate information
            if (IoTHubClient_LL_SetOption(iotHubClientHandle, "TrustedCerts", certificates) != IOTHUB_CLIENT_OK)
            {
              (void)printf("failure to set option \"TrustedCerts\"\r\n");
            }
  #endif // SET_TRUSTED_CERT_IN_SAMPLES
  
            if (IoTHubClient_LL_SetMessageCallback(iotHubClientHandle, ReceiveMessageCallback, &propText) != IOTHUB_CLIENT_OK)
            {
              printf("unable to IoTHubClient_SetMessageCallback\r\n");
            }
            else
            {
              /* wait for commands */
              while (1)
              {
                IoTHubClient_LL_DoWork(iotHubClientHandle);
                ThreadAPI_Sleep(100);
              }
            }
          }
          IoTHubClient_LL_Destroy(iotHubClientHandle);
          serializer_deinit();
        }
      platform_deinit();
    }
}
