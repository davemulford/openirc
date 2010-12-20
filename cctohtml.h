#include <map>
#include "pcrecpp.h"

using namespace std;

class CCtoHTML
{
	private:
		bool bold;
		bool underline;
		bool italic;
		int fg;
		int bg;
		map<int, string> ColorChart;
	public:
		string Text;
		CCtoHTML(string text);
                string ReturnHTML(string control, string text);
		string translate();
};

