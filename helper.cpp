#include "helper.h"

string getDateAndTime()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d_%m_%Y_%H_%M_%S",timeinfo);
    string str(buffer);
    return str;
}
vector<string> split(const string &s, char delim) {
  stringstream ss(s);
  string item;
  vector<string> elems;
  while (getline(ss, item, delim)) {
    elems.push_back(item);
    // elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
  }
  return elems;
}
string readFile(string path)
{
	try
    {
		ifstream file(path);
		if(!file.is_open())
		{
			cout << "Could not open file: " << path << endl;
			exit(1);
		}
        return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
		//return empty string if something happens
    }
    catch(exception& e)
    {
        return ""; //catch exceptions and return empty string
    }

}
void writeFile(string path, string data)
{
    /*ofstream file(path.c_str());
    file << data;   //overwrites it.
    file.close();*/ 
    ofstream file;
    file.open(path, ios_base::app); // append instead of overwrite
    file << data << endl; //append with new line
    file.close();
}
int getValue(string settings, string value)
{
    //cout << settings << endl;
    vector<string> rows = split(settings, '\n');
    for(int i = 0; i < rows.size(); i++)
    {
        string row = rows[i];
        vector<string> columns = split(row, ' ');
        string name = columns[0];
        if(name.compare(value) == 0)
        {
            try
            {
                return stoi(columns[1]);
            }
            catch(exception& e)
            {
                cerr << e.what();
            }
        }
        
    }
    
    return 0;
}
void readConfig(string path, config &cfg)
{
    string settings = readFile(path);
    cfg.SEED = getValue(settings, "SEED");
    cfg.INIT_TIME = getValue(settings, "INIT_TIME");
    cfg.FIN_TIME = getValue(settings, "FIN_TIME");
    cfg.ARRIVE_MIN = getValue(settings, "ARRIVE_MIN");
    cfg.ARRIVE_MAX = getValue(settings, "ARRIVE_MAX");
    cfg.QUIT_PROB = getValue(settings, "QUIT_PROB");
    cfg.NET_PROB = getValue(settings, "NET_PROB");
    cfg.CPU_MIN = getValue(settings, "CPU_MIN");
    cfg.CPU_MAX = getValue(settings, "CPU_MAX");
    cfg.DISK1_MIN = getValue(settings, "DISK1_MIN");
    cfg.DISK1_MAX = getValue(settings, "DISK1_MAX");
    cfg.DISK2_MIN = getValue(settings, "DISK2_MIN");
    cfg.DISK2_MAX = getValue(settings, "DISK2_MAX");
    cfg.NETWORK_MIN = getValue(settings, "NETWORK_MIN");
    cfg.NETWORK_MAX = getValue(settings," NETWORK_MAX");
}