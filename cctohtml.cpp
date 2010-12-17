#include "cctohtml.h"
#include "pcrecpp.h"

using namespace std;

CCtoHTML::CCtoHTML(string text) {
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

	Text = text;
	string ctrl;
	string txt;
	bold = underline = false;
	fg = bg = 16;
	pcrecpp::RE ParseCC("((?:(?:\\d\\d?),)?(?:\\d\\d?)|[])([^]*)");
	while (ParseCC.PartialMatch(Text,&ctrl,&txt) > 0) {
		ParseCC.Replace(ReturnHTML(ctrl,txt),&Text);
	}
}
string CCtoHTML::ReturnHTML(string control, string text) {
	bool colored;
        string styles;
	pcrecpp::RE ParseEmptyColor("^$");
	pcrecpp::RE ParseColorFGOnly("^(\\d\\d?)$");
	pcrecpp::RE ParseColor("^(\\d\\d?),(\\d\\d?)$");
	pcrecpp::RE ParseBold("^$");
	pcrecpp::RE ParseUnder("^$");
	//todo reverse? not important imho...
	pcrecpp::RE ParseStop("^$");
        if (ParseBold.PartialMatch(control)) { bold = (bold == true ? false : true); }
        if (ParseUnder.PartialMatch(control)) { underline = (underline == true ? false : true); }
        if (ParseEmptyColor.PartialMatch(control)) { fg = bg = 16; }
        if (ParseStop.PartialMatch(control)) { bold = underline = false; fg = bg = 16; }
        if (ParseColorFGOnly.PartialMatch(control,&fg)) { colored = true; }
        if (ParseColor.PartialMatch(control,&fg,&bg)) { colored = true; }

	if (fg < 16) { styles += " color: " + ColorChart[fg] + ";"; }
	if (bg < 16) { styles += " background-color: " + ColorChart[bg] + ";"; }
        if (bold == true) { styles += " font-weight: bold;"; }
        if (underline == true) { styles += " text-decoration:underline;"; }

	return "<span style=\"" + styles + "\">" + text + "</span>";
}
string CCtoHTML::translate() {
	return Text;
}
