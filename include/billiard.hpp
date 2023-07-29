#ifndef BILLIARD_HPP
#define BILLIARD_HPP

#include <stdexcept>

class Billiard
{
public:
	Billiard(double r1, double r2, double l) //
		: m_r1{r1}, m_r2{r2}, m_l{l}		 //
	{
		if (m_r1 < 0 || m_r2 < 0 || m_l < 0)
		{
			throw std::domain_error("Negative argument in constructor");
		}
	}

	double getR1() const { return m_r1; }
	double getR2() const { return m_r2; }
	double getL() const { return m_l; }

private:
	double m_r1{};
	double m_r2{};
	double m_l{};
};

#endif // BILLIARD_HPP