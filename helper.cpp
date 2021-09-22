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
    //elems.push_back(item);
     elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
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
void readConfig(string settings, config &cfg)
{
    vector<string> rows = split(settings, '\n');
    for(int i = 0; i < rows.size(); i++)
    {
        vector<string> columns = split(rows[i], ' ');
        if(columns[0].compare("SEED") == 0)
        {
            cfg.SEED = stoi(columns[1]);
        }
        else if(columns[0].compare("INIT_TIME") == 0)
        {
            cfg.INIT_TIME = stoi(columns[1]);
        }
        else if(columns[0].compare("FIN_TIME") == 0)
        {
            cfg.FIN_TIME = stoi(columns[1]);
        }
        else if(columns[0].compare("ARRIVE_MIN") == 0)
        {
            cfg.ARRIVE_MIN = stoi(columns[1]);
        }
        else if(columns[0].compare("ARRIVE_MAX") == 0)
        {
            cfg.ARRIVE_MAX = stoi(columns[1]);
        }
        else if(columns[0].compare("QUIT_PROB") == 0)
        {
            cfg.QUIT_PROB = stod(columns[1]);
        }
        else if(columns[0].compare("NETWORK_PROB") == 0)
        {
            cfg.NET_PROB = stod(columns[1]);
        }
        else if(columns[0].compare("CPU_MIN") == 0)
        {
            cfg.CPU_MIN = stod(columns[1]);
        }
        else if(columns[0].compare("CPU_MAX") == 0)
        {
            cfg.CPU_MAX = stod(columns[1]);
        }
        else if(columns[0].compare("DISK1_MIN") == 0)
        {
            cfg.DISK1_MIN = stod(columns[1]);
        }
        else if(columns[0].compare("DISK1_MAX") == 0)
        {
            cfg.DISK1_MAX = stod(columns[1]);
        }
        else if(columns[0].compare("DISK2_MIN") == 0)
        {
            cfg.DISK2_MIN = stod(columns[1]);
        }
        else if(columns[0].compare("DISK2_MAX") == 0)
        {
            cfg.DISK2_MAX = stod(columns[1]);
        }
        else if(columns[0].compare("NETWORK_MIN") == 0)
        {
            cfg.NETWORK_MIN = stod(columns[1]);
        }
        else if(columns[0].compare("NETWORK_MAX") == 0)
        {
            cfg.NETWORK_MAX = stod(columns[1]);
        }
    }
}