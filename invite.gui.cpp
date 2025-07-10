/*
	this file was created from C:\CRESD\Source\Invite\invite.gui with MG Gui Builder
	+++++++++++++++++++++++
	!!!!! Do not Edit !!!!!
	+++++++++++++++++++++++
*/

#include "C:\CRESD\Source\Invite\invite.gui.h"

namespace winlibGUI {

	gak::xml::Document *GuiApplication::getGuiDoc() {
		gak::xml::Document *doc = winlib::Application::getGuiDoc();
		if(!doc) {
			gak::STRING xmlSrc = "<?xml version=\"1.0\" encoding=\"iso-8859-1\" ?>\n"
"<gui>\n"
"<forms>\n"
"<form name=\"InviteFORM\" style=\"277807104\" width=\"758\" height=\"508\" caption=\"Einladung\" id=\"128\" baseClass=\"PopupWindow\" bgColor=\"COLOR_BTNFACE\" bg_red=\"0\" bg_green=\"0\" bg_blue=\"0\">\n"
"<layoutManager type=\"TableManager\" />\n"
"<child type=\"ListBox\" name=\"EventsLISTBOX\" caption=\"\" x=\"15\" y=\"9\" width=\"120\" height=\"400\" style=\"1353777409\" id=\"129\">\n"
"<layout x=\"0\" y=\"0\" width=\"1\" growWidth=\"0\" growHeight=\"1\" height=\"10\" />\n"
"</child>\n"
"<child type=\"Label\" name=\"\" caption=\"&amp;Titel\" x=\"16\" y=\"16\" width=\"0\" height=\"0\" style=\"1342242827\">\n"
"<layout x=\"1\" y=\"0\" width=\"1\" height=\"1\" growWidth=\"0\" growHeight=\"0\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"EditControl\" name=\"TitelEDIT\" caption=\"\" x=\"154\" y=\"6\" width=\"80\" height=\"25\" style=\"1350631808\" id=\"130\">\n"
"<layout x=\"2\" y=\"0\" width=\"2\" height=\"1\" growWidth=\"1\" growHeight=\"0\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"Label\" name=\"\" caption=\"&amp;Ort\" x=\"16\" y=\"50\" width=\"0\" height=\"0\" style=\"1342242827\">\n"
"<layout x=\"1\" y=\"1\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"EditControl\" name=\"LocationEDIT\" caption=\"\" x=\"160\" y=\"40\" width=\"80\" height=\"25\" style=\"1350631808\" id=\"131\">\n"
"<layout x=\"2\" y=\"1\" width=\"2\" height=\"1\" growWidth=\"1\" growHeight=\"0\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"Label\" name=\"\" caption=\"&amp;Start\" x=\"18\" y=\"89\" width=\"0\" height=\"0\" style=\"1342242827\">\n"
"<layout x=\"1\" y=\"2\" width=\"1\" height=\"1\" growWidth=\"0\" growHeight=\"0\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"DateTimePicker\" name=\"StartDATEPICKER\" caption=\"\" x=\"203\" y=\"151\" width=\"80\" height=\"25\" style=\"1342242816\" id=\"132\">\n"
"<layout x=\"2\" y=\"2\" width=\"1\" height=\"1\" growWidth=\"1\" growHeight=\"0\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"DateTimePicker\" name=\"StartTIMEPICKER\" caption=\"\" x=\"302\" y=\"139\" width=\"80\" height=\"25\" style=\"1342242825\" id=\"133\">\n"
"<layout x=\"3\" y=\"2\" width=\"1\" height=\"1\" growWidth=\"1\" growHeight=\"0\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" attachment=\"2\" />\n"
"</child>\n"
"<child type=\"Label\" name=\"\" caption=\"&amp;Ende\" x=\"15\" y=\"129\" width=\"0\" height=\"0\" style=\"1342242827\">\n"
"<layout x=\"1\" y=\"3\" width=\"1\" height=\"1\" growWidth=\"0\" growHeight=\"0\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"DateTimePicker\" name=\"EndDATEPICKER\" caption=\"\" x=\"192\" y=\"216\" width=\"80\" height=\"25\" style=\"1342242816\" id=\"134\">\n"
"<layout x=\"2\" y=\"3\" width=\"1\" height=\"1\" growWidth=\"1\" growHeight=\"0\" />\n"
"</child>\n"
"<child type=\"DateTimePicker\" name=\"EndTIMEPICKER\" caption=\"\" x=\"480\" y=\"208\" width=\"80\" height=\"25\" style=\"1342242825\" id=\"135\">\n"
"<layout x=\"3\" y=\"3\" width=\"1\" height=\"1\" growWidth=\"1\" growHeight=\"0\" />\n"
"</child>\n"
"<child type=\"Label\" name=\"\" caption=\"&amp;Beschreibung\" x=\"10\" y=\"159\" width=\"0\" height=\"0\" style=\"1342242827\">\n"
"<layout x=\"1\" y=\"4\" width=\"1\" height=\"1\" growWidth=\"0\" growHeight=\"0\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"MemoControl\" name=\"DescrMEMO\" caption=\"\" x=\"205\" y=\"284\" width=\"80\" height=\"25\" style=\"1353781700\" id=\"136\">\n"
"<layout x=\"2\" y=\"4\" width=\"2\" height=\"5\" growWidth=\"1\" growHeight=\"1\" />\n"
"</child>\n"
"<child type=\"Label\" name=\"\" caption=\"O&amp;rganisator\" x=\"14\" y=\"207\" width=\"0\" height=\"0\" style=\"1342242827\">\n"
"<layout y=\"9\" x=\"1\" width=\"1\" height=\"1\" growWidth=\"0\" growHeight=\"0\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"EditControl\" name=\"OrgaEDIT\" caption=\"\" x=\"165\" y=\"183\" width=\"80\" height=\"25\" style=\"1350631808\" id=\"137\">\n"
"<layout x=\"2\" y=\"9\" width=\"1\" height=\"1\" growWidth=\"1\" growHeight=\"0\" paddingLeft=\"2\" paddingRight=\"2\" paddingTop=\"2\" paddingBottom=\"2\" />\n"
"</child>\n"
"<child type=\"EditControl\" name=\"OrgaMailEDIT\" caption=\"\" x=\"188\" y=\"399\" width=\"80\" height=\"25\" style=\"1350631808\" id=\"138\">\n"
"<layout x=\"3\" y=\"9\" width=\"1\" height=\"1\" growWidth=\"1\" growHeight=\"0\" />\n"
"</child>\n"
"<child type=\"FrameChild\" name=\"FRAMECHILD\" caption=\"\" x=\"22\" y=\"209\" width=\"80\" height=\"40\" style=\"1342308352\" id=\"142\">\n"
"<layout x=\"2\" y=\"10\" width=\"2\" height=\"1\" growWidth=\"1\" growHeight=\"0\" />\n"
"<child type=\"PushButton\" name=\"NewBUTTON\" caption=\"Neu\" x=\"8\" y=\"8\" width=\"80\" height=\"24\" style=\"1342242816\" id=\"139\" />\n"
"<child type=\"PushButton\" name=\"LoadBUTTON\" caption=\"&amp;Laden...\" x=\"96\" y=\"8\" width=\"80\" height=\"24\" style=\"1342242816\" id=\"140\" />\n"
"<child type=\"PushButton\" name=\"SaveBUTTON\" caption=\"S&amp;peichern...\" x=\"184\" y=\"8\" width=\"80\" height=\"24\" style=\"1342242816\" id=\"141\" />\n"
"</child>\n"
"</form>\n"
"</forms>\n"
"</gui>";
			return Application::getGuiDoc( xmlSrc );
		}
		return doc;
	}


	void InviteFORM_form::getControls() {
		EventsLISTBOX=static_cast<winlib::ListBox*>(findChild(EventsLISTBOX_id));
		TitelEDIT=static_cast<winlib::EditControl*>(findChild(TitelEDIT_id));
		LocationEDIT=static_cast<winlib::EditControl*>(findChild(LocationEDIT_id));
		StartDATEPICKER=static_cast<winlib::DateTimePicker*>(findChild(StartDATEPICKER_id));
		StartTIMEPICKER=static_cast<winlib::DateTimePicker*>(findChild(StartTIMEPICKER_id));
		EndDATEPICKER=static_cast<winlib::DateTimePicker*>(findChild(EndDATEPICKER_id));
		EndTIMEPICKER=static_cast<winlib::DateTimePicker*>(findChild(EndTIMEPICKER_id));
		DescrMEMO=static_cast<winlib::MemoControl*>(findChild(DescrMEMO_id));
		OrgaEDIT=static_cast<winlib::EditControl*>(findChild(OrgaEDIT_id));
		OrgaMailEDIT=static_cast<winlib::EditControl*>(findChild(OrgaMailEDIT_id));
		NewBUTTON=static_cast<winlib::PushButton*>(findChild(NewBUTTON_id));
		LoadBUTTON=static_cast<winlib::PushButton*>(findChild(LoadBUTTON_id));
		SaveBUTTON=static_cast<winlib::PushButton*>(findChild(SaveBUTTON_id));
		FRAMECHILD=static_cast<winlib::FrameChild*>(findChild(FRAMECHILD_id));
	}	// InviteFORM
}	// namespace winlibGUI
