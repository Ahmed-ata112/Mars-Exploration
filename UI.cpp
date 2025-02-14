#include "UI.h"
#include <iostream>
//#include "LinkedPriorityQueue.h"
#include <fstream>
#include<Windows.h>  //for the delay
using namespace std;


UI::UI(MarsStation* p_s) : p_station(p_s)
{ }


SIM_MODE UI::get_input_mode()
{

	std::cout << "Please select The mode you want to enter" << endl <<
		"1- Interactive Mode(GUI)\n2- Silent Mode\n enter: ";

	int n;
	cin >> n;
	while (n > 2 || n < 1)
	{
		cout << "Please enter a valid number: ";
		cin >> n;
	}

	SIM_MODE a;
	if (n == 1)
		return SIM_MODE::INTERACTIVE;

	return SIM_MODE::SILENT;
}


void UI::Output_Console()const
{
	cout << "Current Day : " << p_station->get_current_day() << endl;

	//Waiting Missions

	//calculate # of waiting missions
	int no_W_M = p_station->get_w_e_m().get_itemCount() + p_station->get_w_p_m().get_itemCount() + p_station->get_w_m_m().getItemCount();

	cout << no_W_M << " Waiting Missions : ";
	// First --> print the ID of the E missions
	cout << " [";
	Mission* m = nullptr;
	int j = 0;
	int count = p_station->get_w_e_m().get_itemCount();
	LinkedPriorityQueue<Mission*, int> temp;
	while (p_station->get_w_e_m().peek(m))
	{
		p_station->get_w_e_m().dequeue(m);

		if (j == 0)
			cout << m->getID();
		else
			cout << "," << m->getID();
		j++;
		// Then enqueue it again
		Pair<Mission*, int> pm(m, m->get_priority());
		temp.enqueue(pm);
	}
	cout << "]";
	p_station->get_w_e_m() = temp;

	while (temp.dequeue(m));   //clear temp

	// Second --> print the ID of the polar Mission
	cout << " (";
	j = 0;
	count = p_station->get_w_p_m().get_itemCount();
	for (int i = 1; i <= count; i++)
	{
		p_station->get_w_p_m().dequeue(m);

		if (j == 0)
			cout << m->getID();
		else
			cout << "," << m->getID();
		j++;
		//then enqueue it again
		p_station->get_w_p_m().enqueue(m);
	}
	cout << ")";


	// Third --> print the ID of the mountainous missions
	cout << " {";
	for (int i = 1; i <= p_station->get_w_m_m().getItemCount(); i++)   //itemCount does not change during this loop
	{
		if (i == p_station->get_w_m_m().getItemCount())   //so print wihtout the ","
			cout << p_station->get_w_m_m().getEntry(i)->getID();
		else
			cout << p_station->get_w_m_m().getEntry(i)->getID() << ",";

	}
	cout << "}" << endl;

	cout << "--------------------------------------------------------------------------------------------" << endl;

	//In-Execution Missions/Rovers

	//calculate no of In-Execution Missions/Rovers
	int no_exe = p_station->get_in_execution_missions().getItemCount();
	cout << no_exe << " In-Execution Missions/Rovers: ";
	cout << " [";
	j = 0;
	for (int i = 1; i <= p_station->get_in_execution_missions().getItemCount(); i++)
	{
		if (p_station->get_in_execution_missions().getEntry(i)->getMT() == MISSION_TYPE::EMERGENCY)
		{
			if (j == 0)
				cout << p_station->get_in_execution_missions().getEntry(i)->getID() << "/" << p_station->get_in_execution_missions().getEntry(i)->getRover()->getID();
			else
				cout << "," << p_station->get_in_execution_missions().getEntry(i)->getID() << "/" << p_station->get_in_execution_missions().getEntry(i)->getRover()->getID();
			j++;
		}
	}
	cout << "] " << "(";

	j = 0;
	for (int i = 1; i <= p_station->get_in_execution_missions().getItemCount(); i++)
	{
		if (p_station->get_in_execution_missions().getEntry(i)->getMT() == MISSION_TYPE::POLAR)
		{
			if (j == 0)
				cout << p_station->get_in_execution_missions().getEntry(i)->getID() << "/" << p_station->get_in_execution_missions().getEntry(i)->getRover()->getID();
			else
				cout << "," << p_station->get_in_execution_missions().getEntry(i)->getID() << "/" << p_station->get_in_execution_missions().getEntry(i)->getRover()->getID();
			j++;
		}
	}
	cout << ") " << "{";

	j = 0;
	for (int i = 1; i <= p_station->get_in_execution_missions().getItemCount(); i++)
	{
		if (p_station->get_in_execution_missions().getEntry(i)->getMT() == MISSION_TYPE::MOUNTAINOUS)
		{
			if (j == 0)
				cout << p_station->get_in_execution_missions().getEntry(i)->getID() << "/" << p_station->get_in_execution_missions().getEntry(i)->getRover()->getID();
			else
				cout << "," << p_station->get_in_execution_missions().getEntry(i)->getID() << "/" << p_station->get_in_execution_missions().getEntry(i)->getRover()->getID();
			j++;
		}
	}
	cout << "}" << endl;
	cout << "--------------------------------------------------------------------------------------------" << endl;

	//Available Rovers

	LinkedPriorityQueue<Rover*, double> temp_R;
	int no_R = p_station->get_available_rovers_emergency_().get_itemCount() + p_station->get_available_rovers_mountainous_().get_itemCount() + p_station->get_available_rovers_polar_().get_itemCount();
	Rover* r = nullptr;
	cout << no_R << " Available Rovers: " << " [";
	j = 0;
	while(p_station->get_available_rovers_emergency_().peek(r))
	{
		p_station->get_available_rovers_emergency_().dequeue(r);
		if (r->getRT() == ROVER_TYPE::EMERGENCY)
		{
			if (j == 0)
				cout << r->getID();
			else
				cout << "," << r->getID();
		}
		j++;
		//enqueue it again
		Pair<Rover*, double> pr(r, r->getSpeed());
		temp_R.enqueue(pr);
		//p_station->get_available_rovers_emergency_().enqueue(pr);
	}
	cout << "] " << "(";
	p_station->get_available_rovers_emergency_() = temp_R;
	while (temp_R.dequeue(r));   //clear temp

	
	j = 0;
	while(p_station->get_available_rovers_polar_().peek(r))
	{
		p_station->get_available_rovers_polar_().dequeue(r);
		if (r->getRT() == ROVER_TYPE::POLAR)
		{
			if (j == 0)
				cout << r->getID();
			else
				cout << "," << r->getID();
		}
		j++;
		//enqueue it again
		Pair<Rover*, double> pr(r, r->getSpeed());
		temp_R.enqueue(pr);
		//p_station->get_available_rovers_polar_().enqueue(pr);
	}
	cout << ") " << "{";
	p_station->get_available_rovers_polar_() = temp_R;
	while (temp_R.dequeue(r));   //clear temp


	j = 0;
	while(p_station->get_available_rovers_mountainous_().peek(r))
	{
		p_station->get_available_rovers_mountainous_().dequeue(r);
		if (r->getRT() == ROVER_TYPE::MOUNTAINOUS)
		{
			if (j == 0)
				cout << r->getID();
			else
				cout << "," << r->getID();
		}
		j++;
		//enqueue it again
		Pair<Rover*, double> pr(r, r->getSpeed());
		temp_R.enqueue(pr);
		//p_station->get_available_rovers_mountainous_().enqueue(pr);
	}
	cout << "} " << endl;
	p_station->get_available_rovers_mountainous_() = temp_R;
	while (temp_R.dequeue(r));   //clear temp

	cout << "--------------------------------------------------------------------------------------------" << endl;

	//In-Checkup Rovers

	cout << p_station->get_check_up_rovers().getItemCount() << " In-Checkup Rovers: ";
	cout << " [";
	j = 0;
	for (int i = 1; i <= p_station->get_check_up_rovers().getItemCount(); i++)
	{
		if (p_station->get_check_up_rovers().getEntry(i)->getRT() == ROVER_TYPE::EMERGENCY)
		{
			if (j == 0)
				cout << p_station->get_check_up_rovers().getEntry(i)->getID();
			else
				cout << "," << p_station->get_check_up_rovers().getEntry(i)->getID();
			j++;
		}
	}
	cout << "] " << "(";


	j = 0;
	for (int i = 1; i <= p_station->get_check_up_rovers().getItemCount(); i++)
	{
		if (p_station->get_check_up_rovers().getEntry(i)->getRT() == ROVER_TYPE::POLAR)
		{
			if (j == 0)
				cout << p_station->get_check_up_rovers().getEntry(i)->getID();
			else
				cout << "," << p_station->get_check_up_rovers().getEntry(i)->getID();
			j++;
		}
	}
	cout << ") " << "{";


	j = 0;
	for (int i = 1; i <= p_station->get_check_up_rovers().getItemCount(); i++)
	{
		if (p_station->get_check_up_rovers().getEntry(i)->getRT() == ROVER_TYPE::MOUNTAINOUS)
		{
			if (j == 0)
				cout << p_station->get_check_up_rovers().getEntry(i)->getID();
			else
				cout << "," << p_station->get_check_up_rovers().getEntry(i)->getID();
			j++;
		}
	}
	cout << "}" << endl;

	cout << "--------------------------------------------------------------------------------------------" << endl;


	//Completed Missions

	cout << p_station->get_completed_missions_().getItemCount() << " Completed Missions: ";
	cout << " [";
	j = 0;
	for (int i = 1; i <= p_station->get_completed_missions_().getItemCount(); i++)
	{
		if (p_station->get_completed_missions_().getEntry(i)->getMT() == MISSION_TYPE::EMERGENCY)
		{
			if (j == 0)
				cout << p_station->get_completed_missions_().getEntry(i)->getID();
			else
				cout << "," << p_station->get_completed_missions_().getEntry(i)->getID();
			j++;
		}
	}
	cout << "] " << "(";


	j = 0;
	for (int i = 1; i <= p_station->get_completed_missions_().getItemCount(); i++)
	{
		if (p_station->get_completed_missions_().getEntry(i)->getMT() == MISSION_TYPE::POLAR)
		{
			if (j == 0)
				cout << p_station->get_completed_missions_().getEntry(i)->getID();
			else
				cout << "," << p_station->get_completed_missions_().getEntry(i)->getID();
			j++;
		}
	}
	cout << ") " << "{";


	j = 0;
	for (int i = 1; i <= p_station->get_completed_missions_().getItemCount(); i++)
	{
		if (p_station->get_completed_missions_().getEntry(i)->getMT() == MISSION_TYPE::MOUNTAINOUS)
		{
			if (j == 0)
				cout << p_station->get_completed_missions_().getEntry(i)->getID();
			else
				cout << "," << p_station->get_completed_missions_().getEntry(i)->getID();
			j++;
		}
	}
	cout << "}" << endl;

	cout << "--------------------------------------------------------------------------------------------" << endl;
}


// TO BE CHANGED....
void UI::InteractivePrinting() const
{
	cout << "Interactive Mode\n";

	if (!p_station->check_valid_data())
	{
		bool isWritten = p_station->write_output_file();
		cout << "Output file created\n";
		return;
	}

	
	char key;
	
	//check if end of days
	while (!p_station->check_last_day())
	{
		cin >> key;
		
		p_station->simulate_day();

		Output_Console();


		
	}

	bool isWritten = p_station->write_output_file();
	if (isWritten)
		cout << "Simulation ends, Output file created\n";
	else
		cout << "Error! writing into file\n";
}


// TO BE CHANGED....
void UI::StepByStepPrinting() const
{
	
	cout << "Step by step Mode\n";
	if (!p_station->check_valid_data())
	{
		bool isWritten = p_station->write_output_file();
		cout << "Output file created\n";
		return;
	}

	
	while (!p_station->check_last_day())
	{
		p_station->simulate_day();
		Output_Console();
		Sleep(1000);
	}

	

	bool isWritten = p_station->write_output_file();
	if (isWritten)
		cout << "Simulation ends, Output file created\n";
	else
		cout << "Error! writing into file\n";
}


void UI::SilentPrinting() const
{
	cout << "Silent Mode\n";
	if (!p_station->check_valid_data())
	{
		bool isWritten = p_station->write_output_file();
		cout << "Output file created\n";
		return;
	}
	cout << "Simulation Starts...\n";

	while (!p_station->check_last_day())
	{
		p_station->simulate_day();
	}

	bool isWritten = p_station->write_output_file();
	if (isWritten)
		cout << "Simulation ends, Output file created\n";
	else
		cout << "Error! writing into file\n";
}