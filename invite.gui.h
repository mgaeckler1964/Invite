/*
	this file was created from C:\CRESD\Source\Invite\invite.gui with MG Gui Builder
	+++++++++++++++++++++++
	!!!!! Do not Edit !!!!!
	+++++++++++++++++++++++
*/
#ifndef C__CRESD_SOURCE_INVITE_INVITE_GUI_H
#define C__CRESD_SOURCE_INVITE_INVITE_GUI_H
#include <winlib/popup.h>
#include <winlib/frame.h>
#include <winlib/scrollFrame.h>
#include <winlib/ControlW.h>
#include <winlib/xmlEditorChild.h>
#include <winlib/gridView.h>

#include <winlib/winApp.h>

namespace winlibGUI {

	const int DescrMEMO_id=136;
	const int EndDATEPICKER_id=134;
	const int EndTIMEPICKER_id=135;
	const int EventsLISTBOX_id=129;
	const int FRAMECHILD_id=142;
	const int InviteFORM_id=128;
	const int LoadBUTTON_id=140;
	const int LocationEDIT_id=131;
	const int NewBUTTON_id=139;
	const int OrgaEDIT_id=137;
	const int OrgaMailEDIT_id=138;
	const int SaveBUTTON_id=141;
	const int StartDATEPICKER_id=132;
	const int StartTIMEPICKER_id=133;
	const int TitelEDIT_id=130;

	class GuiApplication : public winlib::Application {
		public:
		virtual gak::xml::Document *getGuiDoc( void );
		GuiApplication(int iconID=-1) : winlib::Application(iconID) {}
	};

	class InviteFORM_form : public winlib::OverlappedWindow {
		public:
		InviteFORM_form(winlib::BasicWindow *owner) : OverlappedWindow(owner) {}
		winlib::SuccessCode create(winlib::BasicWindow*parent) {
			return OverlappedWindow::create(parent,"InviteFORM");
		}

		winlib::ListBox *EventsLISTBOX;
		winlib::EditControl *TitelEDIT;
		winlib::EditControl *LocationEDIT;
		winlib::DateTimePicker *StartDATEPICKER;
		winlib::DateTimePicker *StartTIMEPICKER;
		winlib::DateTimePicker *EndDATEPICKER;
		winlib::DateTimePicker *EndTIMEPICKER;
		winlib::MemoControl *DescrMEMO;
		winlib::EditControl *OrgaEDIT;
		winlib::EditControl *OrgaMailEDIT;
		winlib::PushButton *NewBUTTON;
		winlib::PushButton *LoadBUTTON;
		winlib::PushButton *SaveBUTTON;
		winlib::FrameChild *FRAMECHILD;
		private:
		virtual void getControls();
	};	// end of InviteFORM
}	// namespace winlibGUI

#endif // C__CRESD_SOURCE_INVITE_INVITE_GUI_H
