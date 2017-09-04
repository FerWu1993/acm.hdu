#include <iostream>
using namespace std;

struct Room{
	int output;
	int input;
	double Compare;
};

class Sort{
public:
	Sort(int num) :m_iNum(num), m_curNum(0){}
	int function(int len, Room* Array){
		if (len == 1)
			return 0;
		int len1 = 0;
		int _iCurNum=m_curNum;
		Room value = Array[len - 1];
		for (int index = 0; index < len-1; index++)
		{
			if (Array[index].Compare >= value.Compare ){
				if (index != len1)
				{
					Room iTempSwap = Array[index];
					Array[index] = Array[len1];
					Array[len1] = iTempSwap;
				}
				_iCurNum += Array[index].input;

				len1++;
			}
		}
		Room iTempSwap = Array[len-1];
		Array[len-1] = Array[len1];
		Array[len1] = iTempSwap;
		if (_iCurNum  > m_iNum)
		{
			if (len1 >= 1)
			{
				return function(len1, Array);
			}
			else
				return len1;
		}
		else if (_iCurNum + Array[len1].input < m_iNum)
		{
			m_curNum = _iCurNum + Array[len1].input;
			if (len - len1-1 > 1)
			{
				return function(len - len1 - 1, Array + len1+1) + len1+1;
			}
			else
				return len1+1;
		}
		else
		{
			return len1;
		}
	}
private:
	int m_iNum;
	int m_curNum;
};


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
		int allOut = 0;
		for (int index = 0; index < RoomNum; index++)
		{
			cin >> CurRoom[index].output;
			cin >> CurRoom[index].input;
			curin += CurRoom[index].input;
			curOut += CurRoom[index].output;
			if (CurRoom[index].input != 0)
			{
				CurRoom[index].Compare = ((double)CurRoom[index].output) / ((double)CurRoom[index].input);
			}
			else
			{
				allOut += CurRoom[index].output;
				index--;
				RoomNum--;
				continue;
			}
		}
		if (curin <= MyNum)
		{
			printf("%.3f\n", ((double)curOut));
		}
		else
		{
			Sort st(MyNum);
			int x = st.function(RoomNum, CurRoom);
			curin = 0;
			for (int index = 0; index < x; index++)
			{
				allOut += CurRoom[index].output;
				curin += CurRoom[index].input;
			}
			printf("%.3f\n", ((double)allOut) + (MyNum - curin)*CurRoom[x].Compare);
		}
		cin >> MyNum;
		cin >> RoomNum;
	}

	return 0;
}