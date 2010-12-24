#include "config.h"
#include "cctohtml.h"
#include "pcrecpp.h"

#include <QtNetwork>
#include <QString>
#include <QTime>

using namespace std;

CCtoHTML::CCtoHTML() {
	//to be defined later so people can set custom colors... temporary now...
	ColorChart[0] = "#FFFFFF";
	ColorChart[1] = "#000000";
	ColorChart[2] = "#00007F";
	ColorChart[3] = "#009300";
	ColorChart[4] = "#FF0000";
	ColorChart[5] = "#7F0000";
	ColorChart[6] = "#9C009C";
	ColorChart[7] = "#FC7F00";
	ColorChart[8] = "#FFFF00";
	ColorChart[9] = "#00FC00";
	ColorChart[10] = "#009393";
	ColorChart[11] = "#00FFFF";
	ColorChart[12] = "#0000FC";
	ColorChart[13] = "#FF00FF";
	ColorChart[14] = "#7F7F7F";
	ColorChart[15] = "#D2D2D2";

	bold = underline = italic = false;
	fg = bg = 16;
}
string CCtoHTML::ReturnHTML(string *control, string *text) {
	pcrecpp::RE ParseEmptyColor("^$");
	pcrecpp::RE ParseColorFGOnly("^(\\d\\d?)$");
	pcrecpp::RE ParseColor("^(\\d\\d?),(\\d\\d?)$");
	pcrecpp::RE ParseBold("^$");
	pcrecpp::RE ParseUnder("^$");
	pcrecpp::RE ParseItalic("^$");
	pcrecpp::RE ParseReverse("^$");
	pcrecpp::RE ParseStop("^$");
	//todo reverse? not important imho...

        if (ParseEmptyColor.FullMatch(*control)) { fg = bg = 16; }
        else if (ParseBold.FullMatch(*control)) { bold = (bold == true ? false : true); }
        else if (ParseUnder.FullMatch(*control)) { underline = (underline == true ? false : true); }
        else if (ParseItalic.FullMatch(*control)) { italic = (italic == true ? false : true); }
        else if (ParseStop.FullMatch(*control)) { bold = underline = italic = false; fg = bg = 16; }

        ParseColorFGOnly.FullMatch(*control,&fg);
        ParseColor.FullMatch(*control,&fg,&bg);

	return "<span style=\"" + (fg < 16 ? " color:" + ColorChart[fg] + ";" : "") + (bg < 16 ? " background-color:" + ColorChart[bg] + ";" : "") + (bold == true ? " font-weight:bold;" : "") + (underline == true ? " text-decoration:underline;" : "") + (italic == true ? " font-style:italic;" : "") + "\">" + *text + "</span>";
}
string CCtoHTML::translate(string text) {
	string ctrl;
	string txt;
	string tmp;
	string ret;
	pcrecpp::RE ParseCC("((?:(?:\\d\\d?),)?(?:\\d\\d?)|[])([^]*)");
	while (ParseCC.PartialMatch(text,&ctrl,&txt)) {
		tmp = ReturnHTML(&ctrl,&txt);
		pcrecpp::RE("(\\x5C)").GlobalReplace("&#92;",&tmp);
		ParseCC.Replace(tmp,&text);
	}
	return text;
}
QString CCtoHTML::TimeStamp() {
	QTime now = QTime::currentTime();
	QString timeStamp;
	timeStamp.sprintf("[%.2d:%.2d]",now.hour(),now.minute());
	return timeStamp;
}
