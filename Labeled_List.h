#pragma once
#include <wx/wx.h>

class titled_List_panel : public wxPanel
{
public:
	titled_List_panel(wxPanel* parent, wxString ss);

	wxListBox* m_lb;

	wxStaticText* stitle;


	~titled_List_panel()
	{
		delete m_lb;
		delete stitle;
	}
};


inline titled_List_panel::titled_List_panel(wxPanel* parent, wxString ss)
	: wxPanel(parent, wxID_ANY)
{
	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);




	stitle = new wxStaticText(this, -1, ss, wxPoint(-1, -1));

	
	m_lb = new wxListBox(this, wxID_ANY,
		wxPoint(-1, -1), wxSize(-1, -1));



	vbox->Add(stitle, 0, wxEXPAND | wxALL, 0);
	vbox->Add(m_lb, 3, wxEXPAND | wxALL, 0);

	SetSizer(vbox);
}
