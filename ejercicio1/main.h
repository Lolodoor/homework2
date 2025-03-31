#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

class Time {
private:
    int hour, minutes, seconds;
    string period;

public:
    Time();
    Time(int h);
    Time(int h, int m);
    Time(int h, int m, int s);
    Time(int h, int m, int s, const string &p);

    void setHour(int h);
    void setMinutes(int m);
    void setSeconds(int s);
    void setPeriod(const string &p);

    int getHour() const;
    int getMinutes() const;
    int getSeconds() const;
    string getPeriod() const;

    string get12hFormat() const;
    string get24hFormat() const;
};
