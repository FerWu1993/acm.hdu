#include <iostream>

class Fraction{
public:
	Fraction() :Fraction(1){}
	Fraction(long long num) :m_iNumerator(num), m_iDenominator(1){}
	Fraction(long long num, long long den) :m_iNumerator(num), m_iDenominator(den){ Simplify(); }
	Fraction(const Fraction& num, long long den) :m_iNumerator(num.GetNumerator()), m_iDenominator(num.GetDenominator()*den){ Simplify(); }
	void Simplify()
	{
		int flag = false;
		if (m_iNumerator < 0)
		{
			flag = true; 
			m_iNumerator = -m_iNumerator;
		}
		int m = m_iNumerator;
		int n = m_iDenominator;
		int sub = m%n;
		while (sub != 0)
		{
			m = n;
			n = sub;
			sub = m % n;
		}
		m_iDenominator = m_iDenominator / n;
		m_iNumerator = m_iNumerator / n;
		if (flag)
		{
			m_iNumerator = -m_iNumerator;
		}
	}
	long long GetNumerator()const { return m_iNumerator; }
	long long GetDenominator()const { return m_iDenominator; }
	bool GetAbs() { 
		return m_iNumerator >= 0; 
	}
	double GetDoubleValue() { return ((double)(m_iNumerator)) / ((double)(m_iDenominator)); }
private:
	long long  m_iNumerator;					//·Ö×Ó
	long long m_iDenominator;					//·ÖÄ¸
};
Fraction operator-(const Fraction& _left, const Fraction& _right)
{
	int iDenominator_ = _left.GetDenominator() * _right.GetDenominator();
	int iNumerator_ = _left.GetNumerator() * _right.GetDenominator() - _right.GetNumerator() * _left.GetDenominator();
	return Fraction(iNumerator_, iDenominator_);
}

Fraction operator+(const Fraction& _left, const Fraction& _right)
{
	long long iDenominator_ = _left.GetDenominator() * _right.GetDenominator();
	long long iNumerator_ = _left.GetNumerator() * _right.GetDenominator() + _right.GetNumerator() * _left.GetDenominator();
	return Fraction(iNumerator_, iDenominator_);
}
Fraction operator*(const Fraction& _left, const Fraction& _right)
{
	int iDenominator_ = _left.GetDenominator() * _right.GetDenominator();
	int iNumerator_ = _left.GetNumerator() * _right.GetNumerator() ;
	return Fraction(iNumerator_, iDenominator_);
}

Fraction operator/(const Fraction& _left, const Fraction& _right)
{
	if (_right.GetNumerator() != 0)
	{
		int iDenominator_ = _right.GetNumerator() * _left.GetDenominator();
		int iNumerator_ = _left.GetNumerator() * _right.GetDenominator() ;
		return Fraction(iNumerator_, iDenominator_);
	}
	else
	{
		return _left;
	}
}
Fraction operator%(const Fraction& _left, const Fraction& _right)
{
	int iDenominator_ = _left.GetDenominator() * _right.GetDenominator();
	int iNumerator_ = (_left.GetNumerator() * _right.GetDenominator()) % (_right.GetNumerator() * _left.GetDenominator());
	return Fraction(iNumerator_, iDenominator_);
}

bool operator>(const Fraction& _left, const Fraction& _right)
{
	if ((_left - _right).GetNumerator() == 0)
		return false;
	return (_left - _right).GetAbs();
}

bool operator<(const Fraction& _left, const Fraction& _right)
{
	if ((_left - _right).GetNumerator() == 0)
		return false;
	return (_right - _left).GetAbs();
}

class TickAndTickClock{
public:
	TickAndTickClock(int d) :m_nD(d, 1), m_happy(0), m_unhappy(0){}
	double GetResult()
	{
		if (m_nD < 0 || m_nD > 120)
			return 0;
		
		for (int index = 0; index < 43200; index++)
		{
			//Fraction hand[3] = { Fraction(6 * (index % 60)) + 360, Fraction((index % 3600), 10) + 360, Fraction(index, 240) + 360 };
			Fraction hand[3] = { Fraction(6 * (index % 60)) + 360, Fraction((index % 3600), 10) + 360, Fraction(index, 120) + 360 };
			bool bFlag = true;
			for (int iHand = 0; iHand < 3; iHand++)
			{
				Fraction min = (hand[iHand] - m_nD);
				Fraction max = (hand[iHand] + m_nD);
				if ((min  < hand[(iHand + 1) % 3])
					&& (max  > hand[(iHand + 1) % 3]))
				{
					bFlag = false;
					break;
				}
				if ((min  < (360 + hand[(iHand + 1) % 3]))
					&& (max  > (360 + hand[(iHand + 1) % 3])))
				{
					bFlag = false;
					break;
				}
				if ((min  < (hand[(iHand + 1) % 3] - 360))
					&& (max  >  (hand[(iHand + 1) % 3] - 360)))
				{
					bFlag = false;
					break;
				}
			}
			if (bFlag)
			{
				m_happy++;
			}
			else
			{
				m_unhappy++;
			}
		}
		return (double)(m_happy*100) / (double)(43200);
	}
private:
	Fraction m_nD;
	int m_happy;
	int m_unhappy;
};



class TickAndTickClockDouble{
public:
	TickAndTickClockDouble(int d) :m_nD(d), m_happy(0), m_unhappy(0){
	}
	double GetResult()
	{
		if (m_nD < 0 || m_nD > 120)
			return 0;

		double ms_speed = ((double)10) / ((double)59);
		double hs_speed = ((double)120) / ((double)719);
		double mh_speed = ((double)120) / ((double)11);
		double last_time = 0;
		double cur_time = 0;
		double need_time[3] = { 360 * ms_speed, 360 * hs_speed, 360 * mh_speed, };

		int curTimeTimes[3][2] = { { 0, 0 }, { 0, 0 }, { 0, 0 } };
		double curTime[3][2] = { { m_nD * ms_speed, (360 - m_nD) * ms_speed },
		{ m_nD * hs_speed, (360 - m_nD) * hs_speed },
		{ m_nD * mh_speed, (360 - m_nD) * mh_speed } };
		double time[3][2] = { { m_nD * ms_speed, (360 - m_nD) * ms_speed },
		{ m_nD * hs_speed, (360 - m_nD) * hs_speed },
		{ m_nD * mh_speed, (360 - m_nD) * mh_speed } };
		int select[3] = { 0 };

		for (last_time = 0; last_time < 43200;)
		{
			bool bFlag = true;
			for (int index = 0; index < 3; index++)
			{
				if (select[index] == 0)
				{
					bFlag = false;
					break;
				}
			}
			if (curTime[0][select[0]] < curTime[1][select[1]])
			{
				if (curTime[0][select[0]] < curTime[2][select[2]])
				{
					cur_time = curTime[0][select[0]];
					curTimeTimes[0][select[0]]++;
					curTime[0][select[0]] = time[0][select[0]] + need_time[0] * curTimeTimes[0][select[0]];
					select[0] = (select[0] + 1) % 2;
				}
				else
				{
					cur_time = curTime[2][select[2]];
					curTimeTimes[2][select[2]]++;
					curTime[2][select[2]] = time[2][select[2]] + need_time[2] * curTimeTimes[2][select[2]];
					select[2] = (select[2] + 1) % 2;
				}
			}
			else
			{
				if (curTime[1][select[1]] < curTime[2][select[2]])
				{
					cur_time = curTime[1][select[1]];
					curTimeTimes[1][select[1]]++;
					curTime[1][select[1]] = time[1][select[1]] + need_time[1] * curTimeTimes[1][select[1]];
					select[1] = (select[1] + 1) % 2;
				}
				else
				{
					cur_time = curTime[2][select[2]];
					curTimeTimes[2][select[2]]++;
					curTime[2][select[2]] = time[2][select[2]] + need_time[2] * curTimeTimes[2][select[2]];
					select[2] = (select[2] + 1) % 2;
				}
			}
			if (cur_time > 43200)
			{
				cur_time = 43200;
			}
			if (bFlag)
			{
				m_happy = m_happy + (cur_time - last_time);
			}
			else
			{
				m_unhappy = m_unhappy + (cur_time - last_time);
			}
			last_time = cur_time;
		}
		return ((m_happy * 100) / 43200);
	}
private:
	double m_nD;
	double m_happy;
	double m_unhappy;
};



class TickAndTickClockFraction{
public:
	TickAndTickClockFraction(int d) :m_nD(d, 1), m_happy(0), m_unhappy(0){
	}
	double GetResult()
	{
		if (m_nD < 0 || m_nD > 120)
			return 0;

		Fraction ms_speed(10, 59);
		Fraction hs_speed(120, 719);
		Fraction mh_speed(120, 11);
		Fraction last_time = 0;
		Fraction cur_time = 0;
		Fraction need_time[3] = { 360 * ms_speed, 360 * hs_speed, 360 * mh_speed, };
		Fraction time[3][2] =	{ { m_nD * ms_speed, (360 - m_nD) * ms_speed },
								{ m_nD * hs_speed, (360 - m_nD) * hs_speed },
								{ m_nD * mh_speed, (360 - m_nD) * mh_speed }};
		int select[3] = { 0 };

		for (last_time = 0; last_time < 43200;)
		{
			//Fraction hand[3] = { Fraction(6 * (index % 60)) + 360, Fraction((index % 3600), 10) + 360, Fraction(index, 240) + 360 };
			if (time[0][select[0]] < time[1][select[1]])
			{
				if (time[0][select[0]] < time[2][select[2]])
				{
					cur_time = time[0][select[0]];
					time[0][select[0]] = time[0][select[0]] + need_time[0];
					select[0] = (select[0] + 1) % 2;
				}
				else
				{
					cur_time = time[2][select[2]];
					time[2][select[2]] = time[2][select[2]] + need_time[2];
					select[2] = (select[2] + 1) % 2;

				}
			}
			else
			{
				if (time[1][select[1]] < time[2][select[2]])
				{
					cur_time = time[1][select[1]];
					time[1][select[1]] = time[1][select[1]] + need_time[1];
					select[1] = (select[1] + 1) % 2;
				}
				else
				{
					cur_time = time[2][select[2]];
					time[2][select[2]] = time[2][select[2]] + need_time[2];
					select[2] = (select[2] + 1) % 2;
				}
			}
			if (cur_time > 43200)
			{
				cur_time = 43200;
			}
			Fraction index = (cur_time + last_time) / 2;


			Fraction hand[3] = { Fraction(6 * (index % 60)) + 360, Fraction((index % 3600), 10) + 360, Fraction(index, 120) + 360 };			// sm mh hs
			bool bFlag = true;
			for (int iHand = 0; iHand < 3; iHand++)
			{
				Fraction min = (hand[iHand] - m_nD);
				Fraction max = (hand[iHand] + m_nD);
				bool result1 = (min < hand[(iHand + 1) % 3]);
				bool result2 = (max  > hand[(iHand + 1) % 3]);
				bool result3 = (min  < (360 + hand[(iHand + 1) % 3]));
				bool result4 = (max  >(hand[(iHand + 1) % 3] - 360));
				bool result5 = (min  < (hand[(iHand + 1) % 3] - 360));
				bool result6 = (max  >(hand[(iHand + 1) % 3] - 360));
				if ((min  < hand[(iHand + 1) % 3])
					&& (max  > hand[(iHand + 1) % 3]))
				{
					bFlag = false;
					break;
				}
				if ((min  < (360 + hand[(iHand + 1) % 3]))
					&& (max  >(360 + hand[(iHand + 1) % 3])))
				{
					bFlag = false;
					break;
				}
				if ((min  < (hand[(iHand + 1) % 3] - 360))
					&& (max  >(hand[(iHand + 1) % 3] - 360)))
				{
					bFlag = false;
					break;
				}
			}
			if (bFlag)
			{
				m_happy = m_happy + (cur_time - last_time).GetDoubleValue();
			}
			else
			{
				m_unhappy = m_unhappy + (cur_time - last_time).GetDoubleValue();
			}
			last_time = cur_time;
		}
		return ((m_happy * 100) / 43200);
	}
private:
	Fraction m_nD;
	double m_happy;
	double m_unhappy;
};
class TickAndTick{
public:
	TickAndTick(int d) :m_nD(d){}
	double GetResult()
	{
		if (m_nD < 0 || m_nD > 120)
			return 0;
		if (m_nD >= 90)
		{
			return function_add();
		}
		else if (m_nD < 90 && m_nD >= 0)
		{
			return function_sub_line() + function_line();
		}
		return 0;
	}
	double function_add()
	{
		return (double)(-360 * 6 * m_nD + 9 * m_nD*m_nD + 4 * 180 * 180) / (double)(360 * 360);
	}
	double function_sub_line()
	{
		return (double)((720 - 5 * m_nD)*m_nD) / (double)(360 * 360);
	}
	double function_line()
	{
		return (double)(90 * 90 + m_nD*m_nD - 180 * m_nD) / (double)(90 * 90);
	}

private:
	int m_nD;

};



class TickAndTick_goodclock{
public:
	TickAndTick_goodclock(int d) :m_nD(d, 1), m_happy(0), m_unhappy(0){}
	double GetResult()
	{
		const bool bSpeed = false;
		const int precision = 200;
		if (m_nD < 0 || m_nD > 120)
			return 0;
		int max_speed = precision /2;
		int cur_speed = 1;
		bool convert = false;
		bool bState = false;
		bool stopdouble = false;
		for (int index = 0; (index < 43200 * precision) || (cur_speed!=1); index += cur_speed)
		{
			if (true == bSpeed)
			{
				if (index >= 43200 * precision)
				{
					index -= cur_speed;
					cur_speed /= 2;
					stopdouble = true;
					continue;
				}
			}
			//Fraction hand[3] = { Fraction(6 * (index % 60)) + 360, Fraction((index % 3600), 10) + 360, Fraction(index, 240) + 360 };
			Fraction hand[3] = { Fraction(6 * (index % (60 * precision)), precision) + 360, Fraction((index % (3600*precision)), precision * 10) + 360, Fraction(index, precision * 120) + 360 };
			bool bFlag = true;
			for (int iHand = 0; iHand < 3; iHand++)
			{
				Fraction min = (hand[iHand] - m_nD);
				Fraction max = (hand[iHand] + m_nD);
				if ((min  < hand[(iHand + 1) % 3])
					&& (max  > hand[(iHand + 1) % 3]))
				{
					bFlag = false;
					break;
				}
				if ((min  < (360 + hand[(iHand + 1) % 3]))
					&& (max  >(360 + hand[(iHand + 1) % 3])))
				{
					bFlag = false;
					break;
				}
				if ((min  < (hand[(iHand + 1) % 3] - 360))
					&& (max  >(hand[(iHand + 1) % 3] - 360)))
				{
					bFlag = false;
					break;
				}
			}
			if (true == bSpeed)
			{
				if (bFlag == bState)
				{
					convert = false;
				}
				else
				{
					convert = true;
				}
			}
			if (false == convert)
			{
				if (bFlag)
				{
					m_happy+=cur_speed;
				}
				else
				{
					m_unhappy += cur_speed;
				}

				if (true == bSpeed)
				{
					if (cur_speed * 2 < max_speed && stopdouble == false)
					{
						cur_speed *= 2;
					}
				}
			}
			else
			{

				if (true == bSpeed)
				{
					index -= cur_speed;
					if (cur_speed / 2 >= 1)
					{
						cur_speed = cur_speed / 2;
						stopdouble = true;
					}
					else
					{
						bState = !bState;
						stopdouble = false;
					}
				}
			}
		}
		return (double)(m_happy * 100) / (double)(precision*43200);
	}
private:
	Fraction m_nD;
	int m_happy;
	int m_unhappy;
};


using namespace std;

int main(int argc, char* argv[])
{
	int n;
	cin >> n;
	while (n != -1)
	{
		TickAndTickClockDouble tk(n);
		printf("%.3f\n",tk.GetResult());
		cin >> n;
	}
	return 0;
}