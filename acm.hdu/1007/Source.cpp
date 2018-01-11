#include <iostream>
#include <vector>
using namespace std;

class Point{
public:
	double getlfX() const { return m_lfX; }
	double getlfY() const { return m_lfY; }
	void setlfX(double _lfX) { m_lfX = _lfX; }
	void setlfY(double _lfY) { m_lfY = _lfY; }
	void Print();
private:
	double m_lfX;
	double m_lfY;
};
inline bool operator<(const Point& _left, const Point& _right)	{ return _left.getlfX() < _right.getlfX(); }
inline bool operator<=(const Point& _left, const Point& _right)	{ return _left.getlfX() <= _right.getlfX(); }
inline bool operator>(const Point& _left, const Point& _right)	{ return _left.getlfX() > _right.getlfX(); }
inline bool operator>=(const Point& _left, const Point& _right)	{ return _left.getlfX() >= _right.getlfX(); }
inline bool operator==(const Point& _left, const Point& _right)	{ return _left.getlfX() == _right.getlfX(); }
inline bool operator-(const Point& _left, const Point& _right)	{ return abs(_left.getlfX() - _right.getlfX()); }

double Leave(const Point& _left, const Point& _right) 
{ 
	return ((_left.getlfX() - _right.getlfX())*(_left.getlfX() - _right.getlfX()))
		+ ((_left.getlfY() - _right.getlfY())*(_left.getlfY() - _right.getlfY()));
}

bool Check(const Point& _left, const Point& _right, const double CheckL)
{
	if (_right.getlfX() - _left.getlfX() < CheckL)
		return true;
	else
		return false;
}

void Point::Print()
{
	cout << m_lfX << " : " << m_lfY << endl;
}

class Cal1007{
public:
	Cal1007(int nLen);
	double GetResult();
	double GetResultHeap(int iStart, int iEnd);
private:
	int m_nLen;
	int m_VaildLen;
	static Point m_vPoint[100000];
	static int m_iPoint[100000];
};

Point Cal1007::m_vPoint[100000];
int Cal1007::m_iPoint[100000];

int compare(const void* _pLeft,const void* _pRight)
{
	Point* pLeft_ = (Point*)_pLeft;
	Point* pRight_ = (Point*)_pRight;
	return pLeft_->getlfX() - pRight_->getlfX()>0?1:-1;
}

Cal1007::Cal1007(int nLen) :m_nLen(nLen), m_VaildLen(nLen)
{
	for (int index = 0; index < nLen; index++)
	{
		double lfX_, lfY_;
		cin >> lfX_;
		cin >> lfY_;
		m_vPoint[index].setlfX(lfX_);
		m_vPoint[index].setlfY(lfY_);
		m_iPoint[index] = index;
	}
	qsort(m_vPoint, nLen, sizeof(Point), compare);
}


double Cal1007::GetResult()
{
	if (m_nLen < 2)
		return 0;
	double lfMinSize = Leave(m_vPoint[0], m_vPoint[1]);
	//for (int iLeftPos = 0; iLeftPos < m_nLen; iLeftPos++)
	//{
	//	for (int iRightPos = iLeftPos + 1; iRightPos < m_nLen && Check(m_vPoint[iLeftPos], m_vPoint[iRightPos], lfMinSize); iRightPos++)
	//	{
	//		double lfTempSize = Leave(m_vPoint[iLeftPos], m_vPoint[iRightPos]);

	//		if (lfMinSize>lfTempSize)
	//		{
	//			lfMinSize = lfTempSize;
	//		}
	//	}
	//}
	for (int iWidth = 1; iWidth < m_nLen; iWidth++)
	{
		for (int iStart = 0; iStart < m_VaildLen; iStart++)
		{
			if (m_iPoint[iStart] + iWidth < m_nLen)
			{
				if (Check(m_vPoint[m_iPoint[iStart]], m_vPoint[m_iPoint[iStart] + iWidth], lfMinSize))
				{
					double lfTempSize = Leave(m_vPoint[m_iPoint[iStart]], m_vPoint[m_iPoint[iStart] + iWidth]);
					if (lfMinSize>lfTempSize)
					{
						lfMinSize = lfTempSize;
					}
				}
				else
				{
					m_VaildLen--;
					m_iPoint[iStart] = m_iPoint[m_VaildLen];
				}
			}
			else
			{
				m_VaildLen--;
				m_iPoint[iStart] = m_iPoint[m_VaildLen];
			}
		}
	}
	return sqrt(lfMinSize)/2.0;
}


int main(int argc, char * argv[])
{
	int n = 0;
	cin >> n;
	while (n != 0)
	{
		Cal1007 cl007(n);
		printf("%.2f\n", cl007.GetResult());
		cin >> n;
	}
	return 0;
}