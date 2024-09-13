#include "ChildView.h"

#include "Model\database.h"
#include "Model\SearchObject.h"
#include "params.h"
#include "Tools.h"
#include "Util.h"
#include <stdlib.h>
#include <sstream>
#include <iomanip.h>
#include <strstrea.h>
#include "status.h"
#include <list>
#include <assert.h>

ChildView::ChildView (Win::Dow win,
			Cmd::Vector * contextcmdVector,
			std::vector<Menu::Item const *> contextItems)
		: _context( contextItems , *contextcmdVector),
		  _win(win),
		  _scrollHPos(0),
		  _scrollVPos(0),
		  _scrollHMax(0),
		  _scrollVMax(0),
		  _numOfColumns(0),
		  _numOfRows(0),
		  _buttonPresent(false)
{

	// Create child windows

	_font.GetTextSize (_charWidth, _charHeight);
	_columnWidth = LABEL_CHARS * _charWidth;
	_labelHeight = (_charHeight + 6) * 3;
	_rowHeight = (_charHeight + 6) * 3;
	_firstColumnWidth = 8 * _charWidth;


	_editPosX = 0;
	_editPosY = 0;

}

ChildView::~ChildView ()
{
	if (_numOfColumns)
	{
		delete [] _edit;
		_edit = 0;
		delete [] _editCtrl;
		_editCtrl = 0;
		delete [] _columnLabels;
		_columnLabels = 0;
		delete [] _rowLabels;
		_rowLabels = 0;
		delete _cornerLabel;
		_cornerLabel = 0;
	}
}

void ChildView::Size (int width, int height)
{

	int arrayindex = 0;

	if(_numOfColumns)
	{
		MoveContents();
	}
	if(_buttonPresent)
	{
		RECT clrect;
		_win.GetClientSize (clrect);

		_button.Move (clrect.right - 60, clrect.bottom - 35, 50, 25);
	}

	SetScrollBars();

	_win.Invalidate ();
	_win.Update ();
}

void ChildView::SendControlMessage(int ControlId, CTRL_MSGS Msg)
{
	Win::SimpleCtrl temp = _vControlVector[ControlId];
	
	switch(Msg)
	{
	case CTRL_ENABLE:
		temp.Enable ();
		break;
	case CTRL_DISABLE:
		temp.Disable ();
		break;
	case CTRL_HIDE:
		temp.Hide ();
		break;
	case CTRL_SHOW:
		temp.Show();
		break;
	}
}

void ChildView::SetContext(Win::Dow win, int x, int y)
{
	RECT  windowrect;
	::GetWindowRect(win,&windowrect);
	_context.TrackMenu(win, windowrect.left + x, windowrect.top + y + 20);
}

void ChildView::SetHScrollBar (int scrollcode, short int scrollpos, HWND scrollHwnd)
{
	SCROLLINFO si;
	int xInc;

	switch(scrollcode)
	{ 
            // User clicked shaft left of the scroll box. 
 
            case SB_PAGELEFT: 
                 xInc = -3; 
                 break; 
 
            // User clicked shaft right of the scroll box. 
 
            case SB_PAGERIGHT: 
                 xInc = 3; 
                 break; 
 
            // User clicked the left arrow. 
 
            case SB_LINELEFT: 
                 xInc = -1; 
                 break; 
 
            // User clicked the right arrow. 
 
            case SB_LINERIGHT: 
                 xInc = 1; 
                 break; 
 
            // User dragged the scroll box. 
 
            case SB_THUMBTRACK: 
                 xInc = scrollpos - _scrollHPos; 
                 break; 
 
            default: 
                 xInc = 0; 
 
        }
	if (xInc = max (-_scrollHPos, min (xInc, _scrollHMax - _scrollHPos))) 
	{
		if(_numOfColumns)
		{
			_editPosX -= xInc * (_columnWidth * 0.75);
		
			
			MoveContents();
			

		}
		_scrollHPos += xInc;	

	    si.cbSize = sizeof(si); 
        si.fMask  = SIF_POS; 
        si.nPos   = _scrollHPos; 
        SetScrollInfo(_win, SB_HORZ, &si, TRUE);
		Redraw();
	//	_win.Invalidate (); 
	//	_win.Update ();
	}

}

void ChildView::MoveContents ()
{
	int arrayindex = 0;

	for( int rowindex = 0; rowindex < _numOfRows; rowindex++)
			{

				_rowLabels[rowindex].MoveDelayPaint (_editPosX,
			                               _editPosY + _labelHeight + (rowindex * _rowHeight),
										   _firstColumnWidth,
										   _rowHeight);

						

				for(int columnindex = 0; columnindex < _numOfColumns; columnindex++)											   
				{
					if(!rowindex)
					{
						_columnLabels[columnindex].MoveDelayPaint (_editPosX + _firstColumnWidth + (columnindex * _columnWidth),
																   _editPosY,
															       _columnWidth,
															       _labelHeight);
					}


					_edit[arrayindex].MoveDelayPaint (_editPosX + _firstColumnWidth + (columnindex*_columnWidth),
													   _editPosY + _labelHeight + (rowindex * _rowHeight),
													   _columnWidth,
													   _rowHeight);
						
					arrayindex++;
					}
			}
			_cornerLabel->MoveDelayPaint(_editPosX,
		     			   _editPosY,
			     		   _firstColumnWidth,
				    	   _labelHeight);

}

void ChildView::SetVScrollBar (int scrollcode, short int scrollpos, HWND scrollHwnd)
{
	SCROLLINFO si;
	int xInc;

	switch(scrollcode)
	{ 
            // User clicked shaft left of the scroll box. 
 
            case SB_PAGELEFT: 
                 xInc = -3; 
                 break; 
 
            // User clicked shaft right of the scroll box. 
 
            case SB_PAGERIGHT: 
                 xInc = 3; 
                 break; 
 
            // User clicked the left arrow. 
 
            case SB_LINELEFT: 
                 xInc = -1; 
                 break; 
 
            // User clicked the right arrow. 
 
            case SB_LINERIGHT: 
                 xInc = 1; 
                 break; 
 
            // User dragged the scroll box. 
 
            case SB_THUMBTRACK: 
                 xInc = scrollpos - _scrollVPos; 
                 break; 
 
            default: 
                 xInc = 0; 
 
        }
	if (xInc = max (-_scrollVPos, min (xInc, _scrollVMax - _scrollVPos))) 
	{
		if(_numOfColumns)
		{
			_editPosY -= xInc * (_rowHeight * 0.75);
			
			if(_editPosY > 0)
			{
				_editPosY = 0;
			}
			
			MoveContents();
			

		}
		_scrollVPos += xInc;	

	    si.cbSize = sizeof(si); 
        si.fMask  = SIF_POS; 
        si.nPos   = _scrollVPos; 
        SetScrollInfo(_win, SB_VERT, &si, TRUE);
		Redraw();
	//	_win.Invalidate (); 
	//	_win.Update ();
	}
}

void ChildView::MakeTable (int numofrows)
{
	if(_numOfColumns)
	{
		DestroyTable();
	}

	Win::Edit * editptr;
	ThisEditController * editcont;
	Win::StaticText * columnLabelptr;
	Win::StaticText * rowLabelptr;
	Win::EditMaker  * editmaker;
	std::string		tempstring;
	std::strstream   tempstrstream;
	std::ostringstream tempostream;
	int				tempinteger;

	_numOfRows = numofrows;
	_numOfColumns = _database->GetNumberofFields ();
	_edit = new Win::Edit [_numOfColumns * _numOfRows];
	_editCtrl = new ThisEditController [_numOfColumns * _numOfRows];
	_columnLabels = new Win::StaticText [_numOfColumns];
	_rowLabels = new Win::StaticText [_numOfRows];
	_cornerLabel = new Win::StaticText;

	editptr = _edit;
	editcont = _editCtrl;
	columnLabelptr = _columnLabels;
	rowLabelptr = _rowLabels;

	//corner label
	editmaker = new Win::EditMaker(_win, 0);
	editmaker->MakeMultiLine ();
	editmaker->MakeReadOnly ();
	editmaker->MakeCentre ();
	_cornerLabel->Init (editmaker->Create ());
	delete editmaker;
	editmaker = 0;
	_cornerLabel->SetFont (_font);
	_cornerLabel->SetText ("Record Number");
	_cornerLabel->Move(_editPosX,
					   _editPosY,
					   _firstColumnWidth,
					   _labelHeight);
	
	for(int rowindex = 0; rowindex < _numOfRows; rowindex++)
	{			//make the row labels
			editmaker = new Win::EditMaker (_win,rowindex);
			editmaker->MakeCentre ();
			editmaker->MakeReadOnly ();
			rowLabelptr->Init (editmaker->Create ());
			delete editmaker;
			editmaker = 0;
			rowLabelptr->Move (_editPosX,
							   _editPosY + _labelHeight + (rowindex * _rowHeight),
							   _firstColumnWidth,
							   _rowHeight);
			rowLabelptr++;
		
		for(int columnindex = 0; columnindex < _numOfColumns; columnindex++)
		{
			//column labels
			if(!rowindex)
			{

				editmaker = new Win::EditMaker(_win, columnindex + 1);
				editmaker->MakeMultiLine ();
				editmaker->MakeReadOnly();
				editmaker->MakeCentre ();
				columnLabelptr->Init (editmaker->Create ());
				delete editmaker;
				editmaker = 0;
				columnLabelptr->SetFont(_font);
				tempinteger = columnindex + 1;
				tempstring = ToString(tempinteger) + " : " + _database->GetFieldName (columnindex);
				if(tempstring.length () < LABEL_CHARS)
				{
					for(int i = 0; i < LABEL_CHARS - tempstring.length(); i++)
					{
						tempstring = tempstring + " ";
					}
				}
				tempstring = tempstring + "  Type : " + _database->GetTheTypeArray (columnindex);
				columnLabelptr->SetText (tempstring.c_str ());
				columnLabelptr->Move(_editPosX + _firstColumnWidth + (columnindex * _columnWidth),
											 _editPosY,
											 _columnWidth,
											 _labelHeight);
				columnLabelptr ++;
			}
			//make the cells
			editmaker = new Win::EditMaker(_win, columnindex);
			editmaker->MakeMultiLine ();
			editmaker->MakeVScroll ();
			editmaker->MakeHScroll ();
			editptr->Init(editmaker->Create ());
			editptr->SetFont(_font);
			editptr->SubClass (editcont);
			_vControlVector.push_back(*editptr);
			delete editmaker;
			editmaker = 0;
			editptr->Move(_editPosX + _firstColumnWidth + (columnindex*_columnWidth),
						  _editPosY + _labelHeight + (rowindex * _rowHeight),
						  _columnWidth,
						  _rowHeight);
			editptr ++;
			editcont ++;
			
		}//end of rows
	}//end of columns

	SetScrollBars();

}

void ChildView::SetScrollBars ()
{
	
	RECT rc;
	_win.GetClientSize (rc);
	SCROLLINFO si;
	int cellswidth = (_numOfColumns * _columnWidth) + _firstColumnWidth;
	if(cellswidth > rc.right)
	{	
		_scrollHMax = ((cellswidth - rc.right) / (_columnWidth * 0.75)) + 2;
		si.cbSize = sizeof(si); 
		si.fMask  = SIF_RANGE | SIF_POS; 
		si.nMin   = 0; 
		si.nMax   = _scrollHMax; 
		si.nPage  = _numOfColumns; 
		si.nPos   = _scrollHPos; 	
	}
	else
	{
		_scrollHMax = 0;
		si.cbSize = sizeof(si);
		si.fMask = SIF_RANGE | SIF_POS;
		si.nMin = 0;
		si.nMax = 0;
		si.nPos = 0;
		SetHScrollBar(SB_ENDSCROLL,0,0);
	}
	
	SetScrollInfo(_win, SB_HORZ, &si, TRUE);

	int cellsheight = (_numOfRows * _rowHeight) + _labelHeight;
	
	if(cellsheight > rc.bottom )
	{
		_scrollVMax = ((cellsheight - rc.bottom) / (_rowHeight * 0.75)) + 2;
		si.cbSize = sizeof(si);
		si.fMask = SIF_RANGE | SIF_POS;
		si.nMin = 0;
		si.nMax = _scrollVMax;
		si.nPos = 0;
		si.nPage = _numOfRows;
	}
	else
	{
		_scrollVMax = 0;
		si.cbSize = sizeof(si);
		si.fMask = SIF_RANGE | SIF_POS;
		si.nMin = 0;
		si.nMax = 0;
		si.nPos = 0;	
	}		
	_editPosY = 0;
	MoveContents();
	SetScrollInfo(_win, SB_VERT, &si, TRUE);
}

void ChildView::Redraw ()
{
	_win.Invalidate (); 
	_win.Update ();
}

void ChildView::AddButton ()
{
	if(!_buttonPresent)
	{
		Win::ButtonMaker button (_win, 0);
		_button.Init (button.Create());
		_button.SubClass (&_buttonCtrl);
		
		RECT clrect;
		GetClientRect (_win,&clrect);

		_button.Move (clrect.right - 60, clrect.bottom - 35, 50, 25);
		_button.SetText ("Done");
		_buttonPresent = true;
	}
	else
	{
		_button.Display ();
	}
}

void ChildView::SetDbase (database * database)
{
	_database = database;
}

void ChildView::ButtonPressed ()
{
	std::string msg = "Incorrect entry in field ";
	std::string errormsg;
	std::string data;
	std::string indata;
	int j;
	Win::Edit tempedit;
	std::vector <std::string> datavector;
	bool invalid = false;
	//validate data in boxes
	for(int i = 0; i < _numOfColumns; i++)
	{
		tempedit = _vControlVector[i];
		data = tempedit.GetText();
		if (data == "")
		{
			invalid = true;
			j = i + 1;
			errormsg = msg + ToString(j);
			break;
		}
		switch(_database->GetTypeArray (i))
		{
		case STRINGTYPE:
			indata = data;
			break;
		case INTTYPE:
			indata = GetStringIn(data);
			if(!atoi(indata.c_str ()))
			{
				invalid = true;
				j = i + 1;
				errormsg = msg + ToString(j);
			}
			break;
		case CHARTYPE:
			indata = GetStringIn(data)[0];
			break;
		case FLOATTYPE:
			indata = GetStringIn(data);
			if(!atof(indata.c_str ()))
			{
				invalid = true;
				j = i + 1;
				errormsg = msg + ToString(j);
			}
			break;
		case TYPEERROR:
			invalid = true;
			std::ostringstream out;
			out << "Internal error at " << __LINE__ << "in " << __FILE__;
			errormsg = out.str();
			break;
		}
		if(invalid)
		{
			break;
		}
		else
		{
			datavector.push_back(indata);
		}
	}				
	if(invalid)
	{
		MessageBox (_win,errormsg.c_str (), "Database Error", MB_OK | MB_ICONERROR);
	}
	else
	{	
		_database->AddRecord (datavector);
		
		DestroyTable ();

		_button.Hide ();
		_win.Hide();
	}

}

void ChildView::DestroyTable ()
{
	Win::Edit tempedit;

	for (std::vector<Win::Edit>::const_iterator iter = _vControlVector.begin ();
		 iter != _vControlVector.end ();
		 ++iter)
	{
		tempedit = *iter;
		tempedit.Hide();
		tempedit.Destroy();
	}

	for (int i = 0; i<_numOfColumns; i++)
	{
		_columnLabels[i].Hide ();
		_columnLabels[i].Destroy ();
	}

	for (i = 0; i < _numOfRows; i++)
	{
		_rowLabels[i].Hide ();
		_rowLabels[i].Destroy ();
	}
	
	_cornerLabel->Hide ();
	_cornerLabel->Destroy ();

	_numOfColumns = 0;
	_numOfRows = 0;

	delete [] _edit;
	_edit = 0;
	delete [] _editCtrl;
	_editCtrl = 0;
	delete [] _columnLabels;
	_columnLabels = 0;
	delete _cornerLabel;
	_cornerLabel = 0;
	delete _rowLabels;
	_rowLabels = 0;

	_vControlVector.clear();
}

void ChildView::ShowRecords (int recordbegin, int recordend)
{
	int numberoffields = _database->GetNumberofFields ();
	int cellindex = 0;
	int rowindex = 0;

	RecordStruct::recordstruct records(recordbegin, recordend);
	_database->ShowRecord (records);
		
	for(int i = recordbegin; i <= recordend; i++)
	{
		_rowLabels[rowindex].SetText (ToString(i).c_str());
		rowindex ++;

		for(int j = 0; j < numberoffields; j++)
		{
			_edit[cellindex].SetText (records.GetField (i,j).c_str ());
			cellindex ++;
		}
	}

}

void ChildView::ShowSearchRecords (std::vector<int> & resultlist)
{
	int bob = resultlist.size();
	assert(resultlist.size() > 0);
	MakeTable(resultlist.size());
	
	RecordStruct::recordstruct * therecords = new RecordStruct::recordstruct [resultlist.size()];
	std::vector<int>::const_iterator iter;

	int numberoffields = _database->GetNumberofFields ();
	int cellindex = 0;
	int rowindex = 0;
	int i = 0;
	int recnum;
	for(iter = resultlist.begin(); iter != resultlist.end(); ++iter)
	{
		recnum = * iter;
		therecords[i].SetRecordNum(*iter);
		_database->ShowRecord(therecords[i]);

		_rowLabels[rowindex].SetText (ToString(*iter).c_str());
		

		for(int k = 0; k < numberoffields; k++)
		{
			_edit[cellindex].SetText (therecords[i].GetField (0,k).c_str ());
			cellindex ++;
		}
		
		rowindex ++;
		i++;
	}
	delete [] therecords;
}

void ChildView::SetRecordLabel ()
{
	int recordnum = _database->GetNumberofRecords ();
	recordnum = recordnum + 1;
	std::string recordnumber = ToString(recordnum);
	_rowLabels[0].SetText (recordnumber.c_str ());
}

void ChildView::SearchRecord (std::string * SearchString)
{	
	TermRecords searchResultRecords;

	try
	{
		_database->MakeSearchObject (*SearchString);
		_database->Search(searchResultRecords);

	}
	catch (Win::Exception const & e)
	{
		TheOutput.Error (e.GetTheMessage ());
	}
	catch (...)
	{
		TheOutput.Error ("Unknown exception");
	}

	ShowSearchRecords(searchResultRecords._recordNumbers);
}

void ChildView::RemoveRecord (int toremove)
{
	_database->RemoveRecord (toremove);
}

bool ThisEditController::OnKeyDown (int vKey, int flags) throw ()
{
	if (vKey == VK_RETURN)
	{
		_h.GetParent ().SendMessage (WM_COMMAND, 
			MAKEWPARAM (IDOK, 0),
			reinterpret_cast<LPARAM> (static_cast<HWND> (_h)));
		return true;
	}
	return false;
};

bool ThisButtonController::OnLButtonDown (int x, int y, Win::KeyState kState) throw ()
{	
	_h.CaptureMouse ();

	return false;
}

bool ThisButtonController::OnLButtonUp (int x, int y, Win::KeyState kState) throw ()
{
	_h.ReleaseMouse ();
	_h.GetParent ().SendMessage (MSG_BUTTONPRES);
	return false;
}

