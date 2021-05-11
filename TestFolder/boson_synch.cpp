#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
extern "C"
{
#include "boson/EnumTypes.h"
#include "boson/UART_Connector.h"
#include "boson/Client_API.h"
}

// to compile run: gcc boson_synch.cpp -o bosonsynch -lstdc++ -lboson -lFSLP


int main(int argc, char* argv[]) 
{
	FLR_BOSON_EXT_SYNC_MODE_E sync_mode = FLR_BOSON_EXT_SYNC_DISABLE_MODE;
	printf("Test of Boson SDK install. If this works you will see the camera SN and part number\n");

	// Connect to the camera. 16 is ttyACM0.
	int32_t dev = 16;
	int32_t baud = 921600;

	FLR_RESULT result;
	result = Initialize(dev, baud); //COM6, 921600 baud (port_number=5 for COM6)
	printf("Initialize: 0x%08X\n", result);
	if (result)
	{
		printf("You may need to give the Camera a minute to complete initializing before running this.\n");
		printf("Failed to initialize, exiting.\n");
		Close();
		return -1;
	}

	// Retrieve the Camera SN and print it
	printf("CameraSN: ");
	uint32_t camera_sn;
	result = bosonGetCameraSN(&camera_sn);
	if (result)
	{
		printf("Failed with status 0x%08X, exiting.\n", result);
		Close();
		return -1;
	}
	printf(" %d \n", camera_sn);

	FLR_DVO_TYPE_E dvo_src;
	result = dvoGetType(&dvo_src);
	printf("DVO Source:  0x%08X -- 0x%08X \n", result, dvo_src);

	printf("\n");
	uint32_t major, minor, patch;
	printf("SoftwareRev:  ");
	result = bosonGetSoftwareRev(&major, &minor, &patch);
	if (result)
	{
		printf("Failed with status 0x%08X, exiting.\n", result);
		Close();
		return -1;
	}
	printf(" %u.%u.%u \n", major, minor, patch);


	FLR_BOSON_SENSOR_PARTNUMBER_T part_num;
	result = bosonGetSensorPN(&part_num);
	if (result)
	{
		printf("Failed with status 0x%08X, exiting.\n", result);
		Close();
		return -1;
	}
	printf("PartNum: \"%s\"\n", part_num.value);


    // Set Synch mode based on args --------------------------------------
	printf("\n");
	printf("VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVv\n");
	result = bosonGetExtSyncMode(&sync_mode);
	if (result)
	{
		printf("Failed with status 0x%08X, exiting.\n", result);
		Close();
		return -1;
	}
	else
	{
		printf("Boson Synch mode currently is %d\n", sync_mode);
	} 

	printf("-------------------------------------------\n");
sync_mode = FLR_BOSON_EXT_SYNC_DISABLE_MODE;
   if (argc > 1) {
        printf("argv[1] is : -%s-\n",argv[1] );
        if (std::string(argv[1]) == "s"){
	sync_mode = FLR_BOSON_EXT_SYNC_SLAVE_MODE;
printf("Setting to slave");

    }
    else if(std::string(argv[1]) == "m"){
	    sync_mode = FLR_BOSON_EXT_SYNC_MASTER_MODE;
printf("Setting to master");
    }
    }

	printf("Attempting to set to mode: -%d-\n",sync_mode);



	result = bosonSetExtSyncMode(sync_mode);
	if (result)
	{
		printf("Failed with status 0x%08X, exiting.\n", result);
		Close();
		return -1;
	}
	else
	{
		printf("Boson Synch mode set to %d\n",sync_mode );
	}

	result = bosonWriteDynamicHeaderToFlash();
	if (result)
	{
		printf("Failed with status 0x%08X, exiting.\n", result);
		Close();
		return -1;
	}
	else
	{
		printf("Boson Synch write to flash failed\n" );
	}


	result = bosonGetExtSyncMode(&sync_mode);
	if (result)
	{
		printf("Failed with status 0x%08X, exiting.\n", result);
		Close();
		return -1;
	}
	else
	{
		printf("Boson Synch mode is %d\n", sync_mode);
	} 





	Close();

	printf("\n");
	return 0;
}

/* 

1.12.1.1 FLR_MEM_LOCATION_E — <INT_32>
FLR_MEM_INVALID = 0
FLR_MEM_BOOTLOADER = 1
FLR_MEM_UPGRADE_APP = 2
FLR_MEM_LENS_NVFFC = 3
FLR_MEM_LENS_SFFC = 4
FLR_MEM_LENS_GAIN = 5
FLR_MEM_LENS_DISTORTION = 6
FLR_MEM_USER_SPACE = 7
FLR_MEM_RUN_CMDS = 8
FLR_MEM_JFFS2 = 9
FLR_MEM_LAST = 10 











*/
