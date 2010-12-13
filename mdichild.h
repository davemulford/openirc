/****************************************************************************
 **
 ** Copyright (C) 2005-2007 Trolltech ASA. All rights reserved.
 **
 ** This file is part of the example classes of the Qt Toolkit.
 **
 ** This file may be used under the terms of the GNU General Public
 ** License version 2.0 as published by the Free Software Foundation
 ** and appearing in the file LICENSE.GPL included in the packaging of
 ** this file.  Please review the following information to ensure GNU
 ** General Public Licensing requirements will be met:
 ** http://www.trolltech.com/products/qt/opensource.html
 **
 ** If you are unsure which license is appropriate for your use, please
 ** review the following information:
 ** http://www.trolltech.com/products/qt/licensing.html or contact the
 ** sales department at sales@trolltech.com.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **
 ****************************************************************************/

 #ifndef MDICHILD_H
 #define MDICHILD_H

 #include <QTextEdit>

 class MdiChild : public QTextEdit
 {
     Q_OBJECT

 public:
     MdiChild();

     void newFile();
     bool loadFile(const QString &fileName);
     bool save();
     bool saveAs();
     bool saveFile(const QString &fileName);
     QString userFriendlyCurrentFile();
     QString currentFile() { return curFile; }

 protected:
     void closeEvent(QCloseEvent *event);

 private slots:
     void documentWasModified();

 private:
     bool maybeSave();
     void setCurrentFile(const QString &fileName);
     QString strippedName(const QString &fullFileName);

     QString curFile;
     bool isUntitled;
 };

 #endif
