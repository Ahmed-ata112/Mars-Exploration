#include <iostream>
#include "MarsStation.h"
#include "FRAME.h"




class MyApp : public wxApp
{
public:
	ListboxFrame* listbox;
	virtual bool OnInit();
};


IMPLEMENT_APP_NO_MAIN(MyApp)


bool MyApp::OnInit()
{
	
	listbox = new ListboxFrame(wxT("ListboxFrame"));
	listbox->Show(true);

	return true;
	
}






int main()
{
	wxEntry();
	MarsStation station_;

	SIM_MODE mode = station_.get_input_mode();

	station_.execute_mode(mode);

	return 0;
}