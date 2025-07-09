/*
		Project:		Invite
		Module:			invite.cpp
		Description:	Chess 
		Author:			Martin Gäckler
		Address:		Hofmannsthalweg 14, A-4030 Linz
		Web:			https://www.gaeckler.at/

		Copyright:		(c) 1988-2025 Martin Gäckler

		This program is free software: you can redistribute it and/or modify  
		it under the terms of the GNU General Public License as published by  
		the Free Software Foundation, version 3.

		You should have received a copy of the GNU General Public License 
		along with this program. If not, see <http://www.gnu.org/licenses/>.

		THIS SOFTWARE IS PROVIDED BY Martin Gäckler, Linz, Austria ``AS IS''
		AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
		TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
		PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR
		CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
		SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
		LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
		USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
		ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
		OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
		OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
		SUCH DAMAGE.
*/


// --------------------------------------------------------------------- //
// ----- switches ------------------------------------------------------ //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- includes ------------------------------------------------------ //
// --------------------------------------------------------------------- //

#include <iostream>
#include <iomanip>

#include <gak/queue.h>
#include <gak/numericString.h>

#include <WINLIB/WINAPP.H>

#include "invite_rc.h"
#include "invite.gui.h"

// --------------------------------------------------------------------- //
// ----- imported datas ------------------------------------------------ //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- module switches ----------------------------------------------- //
// --------------------------------------------------------------------- //

#ifdef __BORLANDC__
#	pragma option -RT-
#	pragma option -b
#	pragma option -a4
#	pragma option -pc
#endif

using namespace winlib;
using namespace winlibGUI;

// --------------------------------------------------------------------- //
// ----- constants ----------------------------------------------------- //
// --------------------------------------------------------------------- //

static char UID[]			= "uid";
static char LOCATION[]		= "location";
static char ORGANISATOR[]	= "organisator";
static char ORGAMAIL[]		= "orgamail";
static char NEWENTRY[]		= "<neu>";

static char BEGINEVENT[]	= "BEGIN:VEVENT";
static char SUMMARY[]		= "SUMMARY:";
static char DESCRIPTION[]	= "DESCRIPTION:";
static char DTSTART[]		= "DTSTART:";
static char DTEND[]			= "DTEND:";

// --------------------------------------------------------------------- //
// ----- macros -------------------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- type definitions ---------------------------------------------- //
// --------------------------------------------------------------------- //

struct Event
{
	STRING		title,
				description;
	SYSTEMTIME	start, end;
};

// --------------------------------------------------------------------- //
// ----- class definitions --------------------------------------------- //
// --------------------------------------------------------------------- //

class InviteMainWindow : public InviteFORM_form
{
	gak::Array<Event>	m_calendar;
	Event				*m_current;

	static SYSTEMTIME getDateTime(DateTimePicker *datePicker, DateTimePicker *timePicker);
	void saveDates();
	void restoreDates();

	virtual ProcessStatus handleCreate( void );
	virtual ProcessStatus handleSelectionChange( int control );
	virtual ProcessStatus handleEditChange( int control );
	virtual ProcessStatus handleButtonClick( int control );

public:
	InviteMainWindow();
};

class WindowsApplication : public GuiApplication
{
	virtual bool 	startApplication( HINSTANCE /*hInstance*/, const char * /*cmdLine*/ )
	{
		doEnableLogEx(gakLogging::llInfo);
		doDisableLog();
		setApplication("invite");
		setComapny("gak");
		return 0;
	}
	virtual CallbackWindow  *createMainWindow( const char * /*cmdLine*/, int /*nCmdShow*/ )
	{
		InviteMainWindow	*mainWindow = new InviteMainWindow;
		if( mainWindow->create( NULL ) == scERROR )
		{
			MessageBox( NULL, "Could not create window", "Error", MB_ICONERROR );
			delete mainWindow;
			mainWindow = NULL;
		}
		mainWindow->focus();

		return mainWindow;
	}
	virtual void deleteMainWindow( BasicWindow  *mainWindow )
	{
		delete mainWindow;
	}

	public:
	WindowsApplication() : GuiApplication( IDI_INVITE ) {}
};

// --------------------------------------------------------------------- //
// ----- exported datas ------------------------------------------------ //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- module static data -------------------------------------------- //
// --------------------------------------------------------------------- //

static WindowsApplication	app;

// --------------------------------------------------------------------- //
// ----- class static data --------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- prototypes ---------------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- module functions ---------------------------------------------- //
// --------------------------------------------------------------------- //

SYSTEMTIME parseSystemTime( const STRING &systimeStr)
{
	SYSTEMTIME	utctime;
	SYSTEMTIME	localtime;

	STRING	year, month, day;
	STRING	hour, minute, second;
	year = systimeStr.subString( 0, 4 );
	month = systimeStr.subString( 4, 2 );
	day = systimeStr.subString( 6, 2 );
	hour = systimeStr.subString( 9, 2 );
	minute = systimeStr.subString( 11, 2 );
	second = systimeStr.subString( 13, 2 );

	utctime.wYear = year.getValueE<WORD>();
	utctime.wMonth = month.getValueE<WORD>();
	utctime.wDay = day.getValueE<WORD>();

	utctime.wHour = hour.getValueE<WORD>();
	utctime.wMinute = minute.getValueE<WORD>();
	utctime.wSecond = second.getValueE<WORD>();
	utctime.wMilliseconds = 0;

	gak::DateTime	theTime(utctime, false);
	theTime.calcLocalTime().getSystemTime(&localtime );

	return localtime;
}
std::ostream &operator << ( std::ostream &stream, const SYSTEMTIME &timestamp )
{
	SYSTEMTIME		utcTimeStanp;
	gak::DateTime	theTime(timestamp, true);
	theTime.getSystemTime(&utcTimeStanp );

	stream << std::setw(4) << std::setfill('0') << utcTimeStanp.wYear << std::setw(2) << utcTimeStanp.wMonth << std::setw(2) << utcTimeStanp.wDay << 'T' 
		   << std::setw(2) << utcTimeStanp.wHour << std::setw(2) << utcTimeStanp.wMinute << std::setw(2) << utcTimeStanp.wSecond << 'Z';
	return stream;
}

STRING codeLongLine( const STRING &line )
{
	STRING result;
	size_t lineLen = 0;

	for(
		STRING::const_iterator it = line.cbegin(), endIT = line.cend();
		it != endIT;
		++it
	)
	{
		char c = *it;
		if( c == '\n' )
		{
			result += "\\n";
			lineLen += 2;
		}
		else if( c != '\r' )
		{
			result += c;
			++lineLen;
		}
		if( lineLen > 70 )
		{
			result += "\n\t";
			lineLen = 0;
		}
	}
	return result;
}

// --------------------------------------------------------------------- //
// ----- class inlines ------------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- class constructors/destructors -------------------------------- //
// --------------------------------------------------------------------- //

InviteMainWindow::InviteMainWindow() : InviteFORM_form(nullptr), m_current(nullptr)
{
}

// --------------------------------------------------------------------- //
// ----- class static functions ---------------------------------------- //
// --------------------------------------------------------------------- //

SYSTEMTIME InviteMainWindow::getDateTime(DateTimePicker *datePicker, DateTimePicker *timePicker)
{
	SYSTEMTIME	sysdate, systime, merged;
	datePicker->getSystemTime(sysdate);
	timePicker->getSystemTime(systime);
	merged.wYear = sysdate.wYear;
	merged.wMonth = sysdate.wMonth;
	merged.wDayOfWeek = sysdate.wDayOfWeek;
	merged.wDay = sysdate.wDay;
	merged.wHour = systime.wHour;
	merged.wMinute = systime.wMinute;
	merged.wSecond = systime.wSecond;
	merged.wMilliseconds = systime.wMilliseconds;
	return merged;
}

// --------------------------------------------------------------------- //
// ----- class privates ------------------------------------------------ //
// --------------------------------------------------------------------- //

void InviteMainWindow::saveDates()
{
	if( m_current )
	{
		m_current->start = getDateTime(StartDATEPICKER, StartTIMEPICKER);
		m_current->end = getDateTime(EndDATEPICKER, EndTIMEPICKER);
	}
}

void InviteMainWindow::restoreDates()
{
	if( m_current )
	{
		StartDATEPICKER->setSystemTime(m_current->start);
		StartTIMEPICKER->setSystemTime(m_current->start);
		EndDATEPICKER->setSystemTime(m_current->end);
		EndTIMEPICKER->setSystemTime(m_current->end);
	}
}

// --------------------------------------------------------------------- //
// ----- class protected ----------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- class virtuals ------------------------------------------------ //
// --------------------------------------------------------------------- //
   
ProcessStatus InviteMainWindow::handleCreate( void )
{
	LocationEDIT->setText( app.GetProfile("", LOCATION, "") );
	OrgaEDIT->setText( app.GetProfile("", ORGANISATOR, "") );
	OrgaMailEDIT->setText( app.GetProfile("", ORGAMAIL, "") );

	return psDO_DEFAULT;
}

ProcessStatus InviteMainWindow::handleSelectionChange( int control )
{
	if( control == EventsLISTBOX_id )
	{
		saveDates();
		int selected = EventsLISTBOX->getSelection();
		if(selected >= 0 && selected < m_calendar.size() )
		{
			m_current = &m_calendar[selected];

			TitelEDIT->setText(m_current->title);
			DescrMEMO->setText(m_current->description);
		}
		else
		{
			m_current = nullptr;
		}
		restoreDates();
	}

	return psSEND_TO_PARENT;
}

ProcessStatus InviteMainWindow::handleEditChange( int control )
{
	switch( control )
	{
		case TitelEDIT_id:
		{
			m_current->title = TitelEDIT->getText();
			int selected = EventsLISTBOX->getSelection();
			EventsLISTBOX->replaceEntry(selected, m_current->title);
			EventsLISTBOX->selectEntry(selected);
			break;
		}
		case DescrMEMO_id:
			m_current->description = DescrMEMO->getText();
			break;
	}
	return InviteFORM_form::handleEditChange( control );
}

ProcessStatus InviteMainWindow::handleButtonClick( int buttonID )
{
	switch( buttonID )
	{
		case NewBUTTON_id:
		{
			m_current = &m_calendar.createElement();
			m_current->title = NEWENTRY;
			EventsLISTBOX->addEntry(NEWENTRY);
			EventsLISTBOX->selectEntry( int(EventsLISTBOX->getNumEntries() -1) );
			handleSelectionChange(EventsLISTBOX_id);
			break;
		}
		case LoadBUTTON_id:
		{
			std::ifstream	theFile("kapu.ics");
			if( theFile.is_open() )
			{
				gak::Queue<STRING>	lines;

				gak::STRING curLine, line;
				m_calendar.clear();
				EventsLISTBOX->clearEntries();

				while(!theFile.eof())
				{
					line.readLine( theFile );

					if( line[0] == '\t' )
					{
						curLine += line.subString(1);
					}
					else
					{
						if( !curLine.isEmpty() )
						{
							lines.push( curLine );
						}
						curLine = line;
					}
				}
				if( !curLine.isEmpty() )
				{
					lines.push( curLine );
				}
				while( lines.size() )
				{
					line = "";
					STRING tmpLine = lines.pop();
					for( 
						STRING::const_iterator it = tmpLine.cbegin(), endIT = tmpLine.cend();
						endIT != it;
						++it
					)
					{
						char c = *it;
						if( c == '\\' )
						{
							++it;
							c = *it;
							if( c == 'n' )
							{
								line += "\r\n";
							}
						}
						else
						{
							line += c;
						}	
					}
					line = line.decodeUTF8();

					if( line.beginsWith(BEGINEVENT) )
					{
						m_current = &m_calendar.createElement();
					}
					else if( line.beginsWith(SUMMARY) )
					{
						STRING summary = line.subString(sizeof(SUMMARY)-1);
						m_current->title = summary;
						EventsLISTBOX->addEntry(summary);
					}
					else if( line.beginsWith(DESCRIPTION) )
					{
						STRING description = line.subString(sizeof(DESCRIPTION)-1);
						m_current->description = description;
					}
					else if( line.beginsWith(DTSTART) )
					{
						STRING start = line.subString(sizeof(DTSTART)-1);
						m_current->start = parseSystemTime(start);
					}
					else if( line.beginsWith(DTEND) )
					{
						STRING end = line.subString(sizeof(DTEND)-1);
						m_current->end = parseSystemTime(end);
					}
				}
				restoreDates();
			}
			break;
		}
		case SaveBUTTON_id:
		{
			gak::DateTime nowDT;
			SYSTEMTIME nowST;
			nowDT.calcLocalTime().getSystemTime(&nowST);

			int id = app.GetProfile( "", UID, 0 );
			std::ofstream	theFile("kapu.ics");
			theFile << "BEGIN:VCALENDAR\n";
			theFile << "VERSION:2.0\n";
			theFile << "PRODID:www.gaeckler.at/ics\n";
			theFile << "METHOD:PUBLISH\n";

			saveDates();
			for(
				gak::Array<Event>::const_iterator it = m_calendar.cbegin(), endIT = m_calendar.cend();
				it != endIT;
				++it )
			{
				theFile << BEGINEVENT << '\n';
				theFile << "UID:" << ++id << OrgaMailEDIT->getText() << "\n";
				theFile << "ORGANIZER;CN=\"" << OrgaEDIT->getText().encodeUTF8() << "\":MAILTO:"<< OrgaMailEDIT->getText() <<"\n";
				theFile << "LOCATION:" << LocationEDIT->getText().encodeUTF8() << '\n';
				theFile << SUMMARY << it->title.encodeUTF8() << '\n';
				theFile << DESCRIPTION << codeLongLine(it->description.encodeUTF8()) << '\n';
				theFile << "class:PUBLIC\n";
				theFile << "DTSTART:" << it->start << '\n';
				theFile << "DTEND:" << it->end << '\n';
				theFile << "DTSTAMP:" << nowST << '\n';
				theFile << "END:VEVENT\n";
			}

			theFile << "END:VCALENDAR\n";

			app.WriteProfile(false, "", LOCATION, LocationEDIT->getText());
			app.WriteProfile(false, "", ORGANISATOR, OrgaEDIT->getText());
			app.WriteProfile(false, "", ORGAMAIL, OrgaMailEDIT->getText());
			app.WriteProfile(false, "", UID, id );
			break;
		}
	default:
		return InviteFORM_form::handleButtonClick( buttonID );
	}
	return psPROCESSED;
}

// --------------------------------------------------------------------- //
// ----- class publics ------------------------------------------------- //
// --------------------------------------------------------------------- //

// --------------------------------------------------------------------- //
// ----- entry points -------------------------------------------------- //
// --------------------------------------------------------------------- //

#ifdef __BORLANDC__
#	pragma option -RT.
#	pragma option -b.
#	pragma option -a.
#	pragma option -p.
#endif

