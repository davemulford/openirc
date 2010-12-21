#include <map>
#include "pcrecpp.h"
#include <QString>

using namespace std;

class CCtoHTML
{
	private:
		bool bold;
		bool underline;
		bool italic;
		int fg;
		int bg;
	public:
		map<int, string> ColorChart;
		CCtoHTML();
		QString TimeStamp();
                string ReturnHTML(string *control, string *text);
		string translate(string text);
};

