#include <iostream>
using namespace std;

class Elevator{
public:
	Elevator(int a) :CurLevel(a), nResult(0){}
	int GetValue()
	{
		return nResult;
	}
	void CalValue(int level)
	{
		if (level == CurLevel)
		{
			nResult += 5;
			return;
		}
		if (level > CurLevel)
		{
			nResult += ((level - CurLevel) * 6)+5;
		}
		else
		{
			nResult += ((CurLevel - level)* 4) + 5;
		}
		CurLevel = level;
	}
private:
	int CurLevel;
	int nResult;
};


int main(int argc, char argv[])
{
	int input_ = 15;
	int a = 0;
	int n = 0;
	cin >> n;
	while (n)
	{
		Elevator ts(0);
		for (int index = 0; index < n; index++)
		{
			cin >> a;
			ts.CalValue(a);
		}
		cout << ts.GetValue() << endl;
		cin >> n;
	}
	return 0;
}