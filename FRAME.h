#pragma once
#include "Defs.h"
#include "Labeled_List.h"
#include <wx/textdlg.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/listbox.h>

#include "Formulation.h"
#include "Promotion.h"


//wxDEFINE_EVENT(START_SIMULATION, wxCommandEvent);


class MyCanvas : public wxFrame
{
public:
	MyCanvas(const wxString& title);
	wxMessageDialog* error_dial;
	wxMessageDialog* info_dial;


	MarsStation* p_station;
	void init_station();
	//upper part

	wxSlider* slider;
	wxStaticText* slider_label;
	wxStaticText* slider_value;
	wxButton* Start_B;
	wxButton* Pause_B;
	wxButton* Step_B;



	void OnScroll(wxScrollEvent& event);
	void Update_Screen();
	//void OnClick(wxCommandEvent& event);
	void OnStart(wxCommandEvent& event);
	void OnPause(wxCommandEvent& event);
	void OnStep(wxCommandEvent& event);




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
	int nom_events = 0;

	titled_List_panel* in_ex_list;
	titled_List_panel* comp_miss_list;

	bool continue_sim;

	~MyCanvas();
};

MyCanvas::MyCanvas(const wxString& title)
	:wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)), continue_sim(true)
{
	wxFrame::SetMinSize(wxSize(700, 600));
	init_station();
	//designing that shit

	wxPanel* panel = new wxPanel(this, -1);
	wxBoxSizer* v_all_box = new wxBoxSizer(wxVERTICAL);

	//the upper part with the slider
	wxBoxSizer* h_upper_box = new wxBoxSizer(wxHORIZONTAL);

	slider_label = new wxStaticText(panel, -1, wxT("Simulation Period (in Secs)"));
	slider = new wxSlider(panel, ID_SLIDER, 2, 0, 20, wxPoint(-1, -1),
		wxSize(200, -1), wxSL_HORIZONTAL);

	Start_B = new wxButton(panel, ID_Start_B, wxT("Start"));
	Pause_B = new wxButton(panel, ID_Pause_B, wxT("Pause"));
	Step_B = new wxButton(panel, ID_Step_B, wxT("Step"));

	Connect(ID_SLIDER, wxEVT_COMMAND_SLIDER_UPDATED,
		wxScrollEventHandler(MyCanvas::OnScroll));
	//Bind is Better than Connect
	Start_B->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MyCanvas::OnStart, this);
	Pause_B->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MyCanvas::OnPause, this);
	Step_B->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MyCanvas::OnStep, this);
	
	
	slider_value = new wxStaticText(panel, ID_SLIDER_value, wxT("1.00"));
	h_upper_box->AddSpacer(10);

	h_upper_box->Add(slider_label, 0, wxEXPAND | wxUP, 10);
	h_upper_box->Add(slider, 0, wxEXPAND | wxALL, 5);
	h_upper_box->Add(slider_value, 0, wxEXPAND | wxUP, 10);
	h_upper_box->AddSpacer(10);
	h_upper_box->Add(Start_B, 0, wxEXPAND | wxALL, 5);
	h_upper_box->Add(Pause_B, 0, wxEXPAND | wxALL, 5);
	h_upper_box->Add(Step_B, 0, wxEXPAND | wxALL, 5);




	wxBoxSizer* h_lower_p_box = new wxBoxSizer(wxHORIZONTAL); //contains the Lower Part


	wxBoxSizer* v_miss_with_average_and_day_box = new wxBoxSizer(wxVERTICAL);

	day_text = new wxStaticText(panel, -1, wxT("DAY: 00"), wxPoint(-1, -1), wxSize(300, -1));



	wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL); //contains the THREE types of missions





	//the waiting Lists panel
	wxBoxSizer* v_waiting_box = new wxBoxSizer(wxVERTICAL);
	wtitle1 = new wxStaticText(panel, -1, wxT("Waiting Missions"));
	waiting_miss = new wxTextCtrl(panel, ID_WAIT_MISS_TEXT, wxEmptyString, wxPoint(-1, -1), wxDefaultSize
		, wxTE_MULTILINE | wxTE_BESTWRAP | wxTE_READONLY);
	//waiting_miss->SetWindowStyleFlag(wxTE_MULTILINE | wxTE_BESTWRAP);

	wtitle2 = new wxStaticText(panel, -1, wxT("in-Checkup Rovers"));
	Checkup_rovers = new wxTextCtrl(panel, ID_WAIT_MISS_TEXT, wxEmptyString, wxPoint(-1, -1), wxDefaultSize
		, wxTE_MULTILINE | wxTE_BESTWRAP | wxTE_READONLY);


	wtitle3 = new wxStaticText(panel, -1, wxT("Waiting Rovers"));
	waiting_Rovers = new wxTextCtrl(panel, ID_WAIT_MISS_TEXT, wxEmptyString, wxPoint(-1, -1), wxDefaultSize
		, wxTE_MULTILINE | wxTE_BESTWRAP | wxTE_READONLY);



	v_waiting_box->Add(wtitle1, 1, wxEXPAND | wxUP, 5);
	v_waiting_box->Add(waiting_miss, 5, wxEXPAND | wxDOWN, 5);
	v_waiting_box->Add(wtitle2, 1, wxEXPAND | wxUP, 5);
	v_waiting_box->Add(Checkup_rovers, 5, wxEXPAND | wxDOWN, 5);
	v_waiting_box->Add(wtitle3, 1, wxEXPAND | wxUP, 5);
	v_waiting_box->Add(waiting_Rovers, 5, wxEXPAND | wxDOWN, 5);
	in_ex_list = new titled_List_panel(panel, "in-Ex Missions");
	comp_miss_list = new titled_List_panel(panel, "Completed Missions");
	hbox->Add(v_waiting_box, 1, wxEXPAND | wxALL, 10);
	hbox->Add(in_ex_list, 1, wxEXPAND | wxALL, 10);
	hbox->Add(comp_miss_list, 1, wxEXPAND | wxALL, 10);



	average_text = new wxStaticText(panel, -1, wxT("Average Waiting time: 0.00"), wxPoint(-1, -1), wxSize(300, -1));

	v_miss_with_average_and_day_box->Add(day_text, 0, wxEXPAND | wxALL, 10);
	wxStaticLine* sl1 = new wxStaticLine(panel, wxID_ANY, wxPoint(-1, -1),
		wxSize(300, 1));
	v_miss_with_average_and_day_box->Add(sl1, 0, wxEXPAND | wxLEFT | wxUP, 0);


	v_miss_with_average_and_day_box->Add(hbox, 1, wxEXPAND | wxALL, 0);

	wxStaticLine* sl2 = new wxStaticLine(panel, wxID_ANY, wxPoint(-1, -1),
		wxSize(300, 1));
	v_miss_with_average_and_day_box->Add(sl2, 0, wxEXPAND | wxLEFT | wxUP, 0);

	v_miss_with_average_and_day_box->Add(average_text, 0, wxEXPAND | wxALL, 10);




	events_log = new titled_List_panel(panel, "Events LOG");



	h_lower_p_box->Add(v_miss_with_average_and_day_box, 3, wxEXPAND | wxALL, 0);
	h_lower_p_box->Add(events_log, 1, wxEXPAND | wxALL, 10);




	v_all_box->Add(h_upper_box, 0, wxEXPAND | wxALL, 0);
	v_all_box->Add(h_lower_p_box, 1, wxEXPAND | wxALL, 0);

	panel->SetSizer(v_all_box);
	Center();
}

inline void MyCanvas::init_station()
{
	p_station = new MarsStation;
	if (!p_station->check_valid_data())
	{
		bool isWritten = p_station->write_output_file();

		error_dial = new wxMessageDialog(NULL,
			wxT("Error: Wrong Input Data."), wxT("Error"), wxOK | wxICON_ERROR);
		error_dial->ShowModal();
	}

}
inline MyCanvas::~MyCanvas()
{
	delete error_dial;
	delete info_dial;


	delete p_station;



}

inline void MyCanvas::OnScroll(wxScrollEvent& event)
{
	wxString stringnumber = wxString::Format(wxT("%.2f"), slider->GetValue() / 2.0);

	slider_value->SetLabel(stringnumber);


}


inline void MyCanvas::OnStart(wxCommandEvent& event)
{
	wxTheApp->Yield();
	

	continue_sim = true; //to continue it if it was paused
	while (continue_sim && !p_station->check_last_day())
	{
		p_station->simulate_day();
		Update_Screen();
		Sleep(slider->GetValue() / 2.0 * 1000);
	}

	if (p_station->check_last_day())
	{

		bool isWritten = p_station->write_output_file();

		if (isWritten)
		{

			info_dial = new wxMessageDialog(NULL,
				wxT("Output File was Created."), wxT("Finished"), wxOK);
			info_dial->ShowModal();

		}
	}



}

void MyCanvas::OnPause(wxCommandEvent& event)
{
	continue_sim = false;

}
void MyCanvas::OnStep(wxCommandEvent& event)
{
	p_station->simulate_day();
	Update_Screen();



	if (p_station->check_last_day())
	{

		bool isWritten = p_station->write_output_file();

		if (isWritten)
		{

			info_dial = new wxMessageDialog(NULL,
				wxT("Output File was Created."), wxT("Finished"), wxOK);
			info_dial->ShowModal();

		}
	}
}
inline void MyCanvas::Update_Screen()
{
	wxTheApp->Yield();

	//wxString stringnumber = wxString::Format(wxT( "DAY %.0f"), p_station->get_current_day());

	day_text->SetLabel("DAY: " + std::to_string(p_station->get_current_day()));

	waiting_miss->Clear();
	// First --> print the ID of the E missions
	waiting_miss->AppendText(" [");
	Mission* m = nullptr;
	int j = 0;
	int count2 = p_station->get_w_e_m().get_itemCount();
	LinkedPriorityQueue<Mission*, int> temp;
	while (p_station->get_w_e_m().peek(m))
	{
		p_station->get_w_e_m().dequeue(m);

		if (j == 0)
			waiting_miss->AppendText(std::to_string(m->getID()));
		else {
			waiting_miss->AppendText(",");
			waiting_miss->AppendText(std::to_string(m->getID()));
		}
		j++;
		// Then enqueue it again
		Pair<Mission*, int> pm(m, m->get_priority());
		temp.enqueue(pm);
	}
	waiting_miss->AppendText("]");
	p_station->get_w_e_m() = temp;

	while (temp.dequeue(m));   //clear temp

	// Second --> print the ID of the polar Mission
	waiting_miss->AppendText(" (");
	j = 0;
	count2 = p_station->get_w_p_m().get_itemCount();
	for (int i = 1; i <= count2; i++)
	{
		p_station->get_w_p_m().dequeue(m);

		if (j == 0)
			waiting_miss->AppendText(std::to_string(m->getID()));
		else {
			waiting_miss->AppendText(",");
			waiting_miss->AppendText(std::to_string(m->getID()));
		}
		j++;
		//then enqueue it again
		p_station->get_w_p_m().enqueue(m);
	}
	waiting_miss->AppendText(")");

	// Third --> print the ID of the mountainous missions
	waiting_miss->AppendText(" {");
	for (int i = 1; i <= p_station->get_w_m_m().getItemCount(); i++)   //itemCount does not change during this loop
	{
		if (i == p_station->get_w_m_m().getItemCount())   //so print wihtout the ","
			waiting_miss->AppendText(std::to_string(p_station->get_w_m_m().getEntry(i)->getID()));
		else {
			waiting_miss->AppendText(std::to_string(p_station->get_w_m_m().getEntry(i)->getID()));
			waiting_miss->AppendText(",");
		}
	}
	waiting_miss->AppendText("}");


	Checkup_rovers->Clear();

	p_station->get_check_up_rovers();

	//CheckUp Rovers

	for (int i = 1; i <= p_station->get_check_up_rovers().getItemCount(); i++)   //itemCount does not change during this loop
	{
		if (i == p_station->get_check_up_rovers().getItemCount())   //so print wihtout the ","
			Checkup_rovers->AppendText(std::to_string(p_station->get_check_up_rovers().getEntry(i)->getID()));
		else {
			Checkup_rovers->AppendText(std::to_string(p_station->get_check_up_rovers().getEntry(i)->getID()));
			Checkup_rovers->AppendText(",");
		}
	}


	p_station->get_available_rovers_emergency_();



	waiting_Rovers->Clear();
	// First --> print the ID of the E missions
	waiting_Rovers->AppendText(" [");
	Rover* r = nullptr;
	j = 0;
	int count3 = p_station->get_available_rovers_emergency_().get_itemCount();
	LinkedPriorityQueue<Rover*, double> temp2;
	while (p_station->get_available_rovers_emergency_().peek(r))
	{
		p_station->get_available_rovers_emergency_().dequeue(r);

		if (j == 0)
			waiting_Rovers->AppendText(std::to_string(r->getID()));
		else {
			waiting_Rovers->AppendText(",");
			waiting_Rovers->AppendText(std::to_string(r->getID()));
		}
		j++;
		// Then enqueue it again
		Pair<Rover*, double> pm(r, r->getSpeed());
		temp2.enqueue(pm);
	}
	waiting_Rovers->AppendText("]");
	p_station->get_available_rovers_emergency_() = temp2;

	while (temp2.dequeue(r));   //clear temp





	waiting_Rovers->AppendText(" (");
	r = nullptr;
	j = 0;
	count3 = p_station->get_available_rovers_polar_().get_itemCount();
	while (p_station->get_available_rovers_polar_().peek(r))
	{
		p_station->get_available_rovers_polar_().dequeue(r);

		if (j == 0)
			waiting_Rovers->AppendText(std::to_string(r->getID()));
		else {
			waiting_Rovers->AppendText(",");
			waiting_Rovers->AppendText(std::to_string(r->getID()));
		}
		j++;
		// Then enqueue it again
		Pair<Rover*, double> pm(r, r->getSpeed());
		temp2.enqueue(pm);
	}
	waiting_Rovers->AppendText(")");
	p_station->get_available_rovers_polar_() = temp2;

	while (temp2.dequeue(r));   //clear temp


	p_station->get_available_rovers_mountainous_();

	waiting_Rovers->AppendText(" {");
	r = nullptr;
	j = 0;
	count3 = p_station->get_available_rovers_mountainous_().get_itemCount();
	while (p_station->get_available_rovers_mountainous_().peek(r))
	{
		p_station->get_available_rovers_mountainous_().dequeue(r);

		if (j == 0)
			waiting_Rovers->AppendText(std::to_string(r->getID()));
		else {
			waiting_Rovers->AppendText(",");
			waiting_Rovers->AppendText(std::to_string(r->getID()));
		}
		j++;
		// Then enqueue it again
		Pair<Rover*, double> pm(r, r->getSpeed());
		temp2.enqueue(pm);
	}
	waiting_Rovers->AppendText("}");
	p_station->get_available_rovers_mountainous_() = temp2;

	while (temp2.dequeue(r));   //clear temp








	//in execution

	in_ex_list->m_lb->Clear();

	for (int i = 1; i <= p_station->get_in_execution_missions().getItemCount(); i++)   //itemCount does not change during this loop
	{

		std::string ss = "Mission";
		Mission* mm = p_station->get_in_execution_missions().getEntry(i);
		if (mm->getMT() == MISSION_TYPE::EMERGENCY)
		{
			ss += " [" + std::to_string(mm->getID()) + "]";
		}
		else if (mm->getMT() == MISSION_TYPE::POLAR)
		{
			ss += " (" + std::to_string(mm->getID()) + ")";

		}
		else
		{
			ss += " {" + std::to_string(mm->getID()) + "}";

		}
		ss += " From Day: " + std::to_string(mm->getFD() + mm->getWD());


		in_ex_list->m_lb->Append(ss);

		//in_ex_list->m_lb->SetSelection(in_ex_list->m_lb->GetCount() - 1);
		//in_ex_list->m_lb->SetSelection(-1);

	}


	//completed missions
	comp_miss_list->m_lb->Clear();
	double waiting_days = 0;;
	int no_completed = p_station->get_completed_missions_().getItemCount();
	for (int i = 1; i <= no_completed; i++)   //itemCount does not change during this loop
	{

		std::string ss = "Mission";
		Mission* mm = p_station->get_completed_missions_().getEntry(i);
		waiting_days += mm->getWD();
		if (mm->getMT() == MISSION_TYPE::EMERGENCY)
		{
			ss += " [" + std::to_string(mm->getID()) + "]";
		}
		else if (mm->getMT() == MISSION_TYPE::POLAR)
		{
			ss += " (" + std::to_string(mm->getID()) + ")";

		}
		else
		{
			ss += " {" + std::to_string(mm->getID()) + "}";

		}
		ss += " At Day: " + std::to_string(mm->getCD());


		comp_miss_list->m_lb->Append(ss);

		//in_ex_list->m_lb->SetSelection(in_ex_list->m_lb->GetCount() - 1);
		//in_ex_list->m_lb->SetSelection(-1);

	}


	//Events Log.
	nom_events += p_station->get_no_events();
	for (int i = 0; i < p_station->get_no_events(); ++i)
	{
		Event* eve = nullptr;
		p_station->get_follower_events().dequeue(eve);

		if (!eve)
			break;
		wxString ss;
		if (dynamic_cast<Formulation*>(eve))
		{
			ss = wxString::Format(wxT("Day %d Created mission %d"), p_station->get_current_day(), eve->get_ID());

		}
		else if (dynamic_cast<Promotion*>(eve))
		{
			ss = wxString::Format(wxT("Day %d Promoted mission %d"), p_station->get_current_day(), eve->get_ID());
		}
		else
		{
			ss = wxString::Format(wxT("Day %d Cancelled mission %d"), p_station->get_current_day(), eve->get_ID());
		}


		events_log->m_lb->Append(ss);

	}
	if (p_station->get_no_events()) //only if an event Happened
	{
		events_log->m_lb->Append(wxString::Format(wxT("# of Events: %d"), nom_events));

	}


	if (no_completed != 0)
	{
		average_text->SetLabel(wxString::Format(wxT("Average Waiting time: %.2f"), waiting_days / no_completed));
	}





}









