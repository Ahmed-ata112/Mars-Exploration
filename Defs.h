#pragma once
// For all the enums and any structs to be used in any part //Like The Rovers Type Part


enum class SIM_MODE
{
	INTERACTIVE,
	SILENT
};


enum class ROVER_TYPE {
	UNDETERMINED,
	EMERGENCY,
	MOUNTAINOUS,
	POLAR
};

enum class ROVER_STATUS {
	WAITING,
	IN_EXECUTION,
	CHECKUP
};

enum class MISSION_TYPE {
	UNDETERMINED,
	EMERGENCY,
	MOUNTAINOUS,
	POLAR
};

enum class MISSION_STATUS {
	WAITING,
	IN_EXECUTION,
	COMPLETED,
	CANCELLED
};


int const ID_WAIT_MISS_TEXT = 100;
int const ID_WAIT_Rovers_TEXT = 101;
int const ID_CheckUP_ROVER_TEXT = 102;
const int ID_SLIDER = 103;
const int ID_SLIDER_value = 104;
const int ID_Start_B = 105;
const int ID_Pause_B = 106;
const int ID_Step_B = 107;
