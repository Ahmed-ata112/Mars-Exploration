#include <iostream>
#include "MarsStation.h"
#include "FRAME.h"




class MyApp : public wxApp
{
public:
	MyCanvas* listbox;
	virtual bool OnInit();
};


IMPLEMENT_APP_NO_MAIN(MyApp)


bool MyApp::OnInit()
{
	
	listbox = new MyCanvas(wxT("MyCanvas"));
	listbox->Show(true);

	return true;
	
}






int main()
{
	//wxEntry();
	

	SIM_MODE mode = UI::get_input_mode();
	if (mode == SIM_MODE::INTERACTIVE) //as i only implement the Step by Step Here
	{
		wxEntry();
	}
	else {
		MarsStation station_;
		station_.execute_mode(mode);
	}
	return 0;
}