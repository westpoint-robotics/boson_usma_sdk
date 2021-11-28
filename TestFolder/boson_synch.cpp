#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

extern "C" {
  #include "boson/EnumTypes.h"
  #include "boson/UART_Connector.h"
  #include "boson/Client_API.h"
}

// to compile run: gcc boson_synch.cpp -o bosonsynch -lstdc++ -lboson -lFSLP

int main(int argc, char * argv[]) {
  FLR_BOSON_EXT_SYNC_MODE_E sync_mode = FLR_BOSON_EXT_SYNC_DISABLE_MODE;
  printf("Usage:\n\tIf argument 1 is:\n\t\tm - Synch mode is set to master\n\t\ts - Synch mode is set to slave\n\t\tAnything else and synch mode is disabled\n\n");
  printf("Test of Boson SDK install and set synch mode.\nIf this works you will see the camera SN and part number then the camera will be switched to the designated synch mode\n\n");
  // Connect to the camera. 16 is ttyACM0.
  int32_t dev = 47;
  int32_t baud = 921600;


  FLR_RESULT result;
  result = Initialize(dev, baud); //COM6, 921600 baud (port_number=5 for COM6)
  printf("Initialize: 0x%08X\n", result);
  if (result) {
    printf("\nERROR\nYou may need to give the Camera a minute to complete initializing before running this.\n");
    printf("Failed to initialize, exiting.\n");
    Close();
    return -1;
  }

  // Retrieve the Camera SN and print it
  uint32_t camera_sn;
  result = bosonGetCameraSN( & camera_sn);
  if (result) {
    printf("Failed with status 0x%08X, exiting.\n", result);
    Close();
    return -1;
  }
  printf("CameraSN: %d \n", camera_sn);
  
  // Retrieve the Camera PN and print it
  FLR_BOSON_PARTNUMBER_T camera_pn;
  result = bosonGetCameraPN( & camera_pn);
  if (result) {
    printf("Failed with status 0x%08X, exiting.\n", result);
    Close();
    return -1;
  }
//  char *answer = reinterpret_cast<char>(camera_pn);
//  printf("CameraPN: %s \n", (char*)camera_pn);

  FLR_DVO_TYPE_E dvo_src;
  result = dvoGetType( & dvo_src);
  printf("DVO Source:  0x%08X -- 0x%08X \n", result, dvo_src);
  
  uint32_t major, minor, patch;
  printf("SoftwareRev:  ");
  result = bosonGetSoftwareRev( & major, & minor, & patch);
  if (result) {
    printf("Failed with status 0x%08X, exiting.\n", result);
    Close();
    return -1;
  }
  printf(" %u.%u.%u \n", major, minor, patch);

  FLR_BOSON_SENSOR_PARTNUMBER_T part_num;
  result = bosonGetSensorPN( & part_num);
  if (result) {
    printf("Failed with status 0x%08X, exiting.\n", result);
    Close();
    return -1;
  }
  printf("PartNum: \"%s\"\n", part_num.value);

  // Set Synch mode based on args --------------------------------------
  printf("\n");
  printf("VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVv\n");
  result = bosonGetExtSyncMode( & sync_mode);
  if (result) {
    printf("Failed with status 0x%08X, exiting.\n", result);
    Close();
    return -1;
  } else {
    printf("Boson Synch mode currently is %d\n", sync_mode);
  }

  printf("-------------------------------------------\n");
  sync_mode = FLR_BOSON_EXT_SYNC_DISABLE_MODE;
  if (argc > 1) {
    printf("argv[1] is : -%s-\n", argv[1]);
    if (std::string(argv[1]) == "s") {
      sync_mode = FLR_BOSON_EXT_SYNC_SLAVE_MODE;
      printf("Setting synch mode to slave\n");

    } else if (std::string(argv[1]) == "m") {
      sync_mode = FLR_BOSON_EXT_SYNC_MASTER_MODE;
      printf("Setting synch mode to master/n");
    } else {
      printf("Setting synch mode to disabled/n");
    }
  }

  printf("Attempting to set to mode: -%d-\n", sync_mode);

  result = bosonSetExtSyncMode(sync_mode);
  if (result) {
    printf("Failed with status 0x%08X, exiting.\n", result);
    Close();
    return -1;
  } else {
    printf("Boson Synch mode set to %d\n", sync_mode);
  }

  result = bosonWriteDynamicHeaderToFlash();
  if (result) { //TODO understand why this fails but the settings remain persistent.
    printf("Failed with status 0x%08X, exiting.\n", result);
    Close();
    return -1;
  } else {
    printf("Boson Synch write to flash failed\n");
  }
  
  result = bosonReboot();
  if (result) {
    printf("Reboot failed with status 0x%08X, exiting.\n", result);
    Close();
    return -1;
  } else {
    printf("Boson reboot command sent\n");
  }  
  
  
  result = bosonGetExtSyncMode( & sync_mode);
  if (result) {
    printf("Failed with status 0x%08X, exiting.\n", result);
    Close();
    return -1;
  } else {
    printf("Boson Synch mode is %d\n", sync_mode);
  }


  Close();

  printf("\n");
  return 0;
}

