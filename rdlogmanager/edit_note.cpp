// edit_note.cpp
//
// Edit a Rivendell LogManager Note
//
//   (C) Copyright 2002-2018 Fred Gleason <fredg@paravelsystems.com>
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License version 2 as
//   published by the Free Software Foundation.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public
//   License along with this program; if not, write to the Free Software
//   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//

#include <qdialog.h>
#include <qstring.h>
#include <q3textedit.h>
#include <qpainter.h>
#include <qmessagebox.h>
#include <qsqldatabase.h>

#include <rd.h>
#include <rdevent.h>

#include "edit_note.h"

EditNote::EditNote(QString *text,QWidget *parent)
  : QDialog(parent)
{
  setModal(true);

  setWindowTitle("RDLogManager - "+tr("Edit Log Note"));
  edit_text=text;

  //
  // Fix the Window Size
  //
  setMinimumWidth(sizeHint().width());
  setMaximumWidth(sizeHint().width());
  setMinimumHeight(sizeHint().height());
  setMaximumHeight(sizeHint().height());

  //
  // Create Fonts
  //
  QFont bold_font=QFont("Helvetica",12,QFont::Bold);
  bold_font.setPixelSize(12);
  QFont font=QFont("Helvetica",12,QFont::Normal);
  font.setPixelSize(12);

  //
  // The Text Editor
  //
  edit_text_edit=new Q3TextEdit(this);
  edit_text_edit->setGeometry(10,10,
			      sizeHint().width()-20,sizeHint().height()-80);
  edit_text_edit->setText(*edit_text);

  //
  //  OK Button
  //
  QPushButton *button=new QPushButton(this);
  button->setGeometry(sizeHint().width()-180,sizeHint().height()-60,80,50);
  button->setDefault(true);
  button->setFont(bold_font);
  button->setText(tr("&OK"));
  connect(button,SIGNAL(clicked()),this,SLOT(okData()));

  //
  //  Cancel Button
  //
  button=new QPushButton(this);
  button->setGeometry(sizeHint().width()-90,sizeHint().height()-60,80,50);
  button->setFont(bold_font);
  button->setText(tr("&Cancel"));
  connect(button,SIGNAL(clicked()),this,SLOT(cancelData()));
}


QSize EditNote::sizeHint() const
{
  return QSize(400,250);
} 


QSizePolicy EditNote::sizePolicy() const
{
  return QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
}


void EditNote::okData()
{
  *edit_text=edit_text_edit->text();
  done(0);
}


void EditNote::cancelData()
{
  done(-1);
}


void EditNote::closeEvent(QCloseEvent *e)
{
  cancelData();
}
