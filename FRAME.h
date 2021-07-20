#pragma once
#include "Defs.h"
#include "Labeled_List.h"
#include <wx/textdlg.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/listbox.h>

class ListboxFrame : public wxFrame
{
public:
	ListboxFrame(const wxString& title);

	//upper part

	wxSlider *slider;
	wxStaticText* slider_label;
	wxStaticText* slider_value;

	void OnScroll(wxScrollEvent& event);
	

	//lower part
	
	titled_List_panel* events_list;

	//Day and Average
	wxStaticText* day_text;
	wxStaticText* average_text;

	
	//the waiting Lists panel
	wxStaticText* wtitle1;
	wxStaticText* wtitle2;
	wxStaticText* wtitle3;

	wxTextCtrl* waiting_miss;
	wxTextCtrl* Checkup_rovers;
	wxTextCtrl* waiting_Rovers;

	titled_List_panel* events_log;


	titled_List_panel* listbox1;
	titled_List_panel* listbox2;
	titled_List_panel* listbox3;


	wxStaticLine* sl1;
	wxStaticLine* sl2;
	wxStaticLine* sl3;


};

ListboxFrame::ListboxFrame(const wxString& title)
	:wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(700,600))
{
	wxFrame::SetMinSize(wxSize(700, 600));
	
	//designing that shit
	
	wxPanel* panel = new wxPanel(this, -1);
	wxBoxSizer* v_all_box = new wxBoxSizer(wxVERTICAL);

	//the upper part with the slider
	wxBoxSizer* h_upper_box = new wxBoxSizer(wxHORIZONTAL);

	slider_label = new wxStaticText(panel, -1, wxT("Simulation speed (in Secs)"));
	slider = new wxSlider(panel, ID_SLIDER, 2, 0 ,20, wxPoint(-1, -1),
		wxSize(200, -1), wxSL_HORIZONTAL );
	

	Connect(ID_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED,
		wxScrollEventHandler(ListboxFrame::OnScroll));

	
	slider_value = new wxStaticText(panel, ID_SLIDER_value, wxT("1.00"));
	h_upper_box->Add(slider_label,0, wxEXPAND | wxUP, 10);
	h_upper_box->Add(slider, 0, wxEXPAND | wxALL, 5);
	h_upper_box->Add(slider_value, 0, wxEXPAND | wxUP, 10);



	
	wxBoxSizer* h_lower_p_box = new wxBoxSizer(wxHORIZONTAL); //contains the Lower Part

	
	wxBoxSizer* v_miss_with_average_and_day_box = new wxBoxSizer(wxVERTICAL);

	day_text = new wxStaticText(panel, -1, wxT("DAY: -1"));


	
	wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL); //contains the THREE types of missions
	
	


	
	//the waiting Lists panel
	wxBoxSizer* v_waiting_box = new wxBoxSizer(wxVERTICAL);
	wtitle1 = new wxStaticText(panel, -1, wxT("waiting missions"));
	waiting_miss = new wxTextCtrl(panel, ID_WAIT_MISS_TEXT, wxEmptyString, wxPoint(-1, -1), wxDefaultSize
		, wxTE_MULTILINE | wxTE_BESTWRAP | wxTE_READONLY);
	//waiting_miss->SetWindowStyleFlag(wxTE_MULTILINE | wxTE_BESTWRAP);

	wtitle2 = new wxStaticText(panel, -1, wxT("Checkup rovers"));
	Checkup_rovers = new wxTextCtrl(panel, ID_WAIT_MISS_TEXT, wxEmptyString, wxPoint(-1, -1), wxDefaultSize
		, wxTE_MULTILINE | wxTE_BESTWRAP | wxTE_READONLY);


	wtitle3 = new wxStaticText(panel, -1, wxT("waiting rovers"));
	waiting_Rovers = new wxTextCtrl(panel, ID_WAIT_MISS_TEXT, wxEmptyString, wxPoint(-1, -1), wxDefaultSize
		, wxTE_MULTILINE | wxTE_BESTWRAP | wxTE_READONLY);



	v_waiting_box->Add(wtitle1, 1, wxEXPAND | wxALL, 0);
	v_waiting_box->Add(waiting_miss, 3, wxEXPAND | wxDOWN, 5);
	v_waiting_box->Add(wtitle2, 1, wxEXPAND | wxALL, 0);
	v_waiting_box->Add(Checkup_rovers, 3, wxEXPAND | wxDOWN, 5);
	v_waiting_box->Add(wtitle3, 1, wxEXPAND | wxALL, 0);
	v_waiting_box->Add(waiting_Rovers, 3, wxEXPAND | wxDOWN, 5);
	listbox2 = new titled_List_panel(panel, "in-ex missions");
	listbox3 = new titled_List_panel(panel, "completed missions");
	hbox->Add(v_waiting_box, 1, wxEXPAND | wxALL, 10);
	hbox->Add(listbox2, 1, wxEXPAND | wxALL, 10);
	hbox->Add(listbox3, 1, wxEXPAND | wxALL, 10);



	average_text = new wxStaticText(panel, -1, wxT("Average Waiting time: -1"));
	
	v_miss_with_average_and_day_box->Add(day_text, 0, wxEXPAND | wxALL, 10);
	wxStaticLine* sl1 = new wxStaticLine(panel, wxID_ANY, wxPoint(-1, -1),
		wxSize(300, 1));
	v_miss_with_average_and_day_box->Add(sl1, 0, wxEXPAND | wxLEFT | wxUP, 0);

	
	v_miss_with_average_and_day_box->Add(hbox, 1, wxEXPAND | wxALL, 0);

	wxStaticLine* sl2 = new wxStaticLine(panel, wxID_ANY, wxPoint(-1, -1),
		wxSize(300, 1));
	v_miss_with_average_and_day_box->Add(sl2, 0, wxEXPAND | wxLEFT | wxUP, 0);
	
	v_miss_with_average_and_day_box->Add(average_text, 0, wxEXPAND | wxALL , 10);




	events_log = new titled_List_panel(panel, "Events LOG");



	h_lower_p_box->Add(v_miss_with_average_and_day_box, 4, wxEXPAND | wxALL, 0);
	h_lower_p_box->Add(events_log,1, wxEXPAND | wxALL, 10);


	

	v_all_box->Add(h_upper_box, 0, wxEXPAND | wxALL, 0);
	v_all_box->Add(h_lower_p_box, 1, wxEXPAND | wxALL, 0);

	panel->SetSizer(v_all_box);
	Center();
}





void ListboxFrame::OnScroll(wxScrollEvent& event)
{
	wxString stringnumber = wxString::Format(wxT("%.2f"), slider->GetValue() / 2.0);
	
	slider_value->SetLabel(stringnumber);
	
	
}













