#include <iostream>
#include<algorithm>
#include<iomanip>
using namespace std;

struct Room{
	int output;
	int input;
	double Compare;
};

class Sort{
public:
	Sort(int num) :m_iNum(num), m_iCurNum(0){}
	int function(int start,int end, Room* Array){
		if (start >= end)
			return start;
		int Pos = start;
		int _iCurNum = m_iCurNum;
		Room value = Array[end];
		for (int index = start; index < end; index++)
		{
			if (Array[index].Compare >= value.Compare ){
				if (index != Pos)
				{
					Room iTempSwap = Array[index];
					Array[index] = Array[Pos];
					Array[Pos] = iTempSwap;
				}
				_iCurNum += Array[Pos].input;
				Pos++;
			}
		}
		if (end != Pos)
		{
			Room iTempSwap = Array[end];
			Array[end] = Array[Pos];
			Array[Pos] = iTempSwap;
		}


		if (_iCurNum > m_iNum)
		{
			return function(start, Pos-1, Array);
		}
		else if (_iCurNum + Array[Pos].input < m_iNum)
		{
			m_iCurNum = _iCurNum + Array[Pos].input;
			return function(Pos + 1, end, Array);
		}
		else
			return Pos;

		return 0;
	}
private:
	int m_iNum;
	int m_iCurNum;
};

bool bigger(Room a, Room b)
{
	if (a.Compare == b.Compare)return a.Compare>b.Compare;
	else return a.Compare>b.Compare;
}
int main(int argc, char argv[])
{
	int MyNum=0;
	int RoomNum = 0;
	Room CurRoom[1000];
	cin >> MyNum;
	cin >> RoomNum;
	while (MyNum != -1)
	{
		int curin = 0;
		int curOut = 0;
		double allOut = 0;
		for (int index = 0; index < RoomNum; index++)
		{
			cin >> CurRoom[index].output;
			cin >> CurRoom[index].input;
			curin += CurRoom[index].input;
			curOut += CurRoom[index].output;
			{
				CurRoom[index].Compare = ((double)CurRoom[index].output) / ((double)CurRoom[index].input);
			}

		}
 
		{
			//sort(CurRoom, CurRoom + RoomNum, bigger);
			Sort st(MyNum);
			int x = st.function(0,RoomNum-1, CurRoom);
			curin = 0;
			int index = 0;
			
			for (index = 0; index < RoomNum; index++)
			{
				if (MyNum>CurRoom[index].input)
				{
					MyNum -= CurRoom[index].input;
					allOut += CurRoom[index].output;
				}
				else{
					allOut += (double)MyNum / CurRoom[index].input*CurRoom[index].output;
					break;
				}
			}
			cout.setf(ios::fixed);
			cout << setprecision(3) << allOut << endl;
		}
		cin >> MyNum;
		cin >> RoomNum;
	}

	return 0;
}