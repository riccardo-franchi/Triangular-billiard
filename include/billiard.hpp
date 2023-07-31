#ifndef BILLIARD_HPP
#define BILLIARD_HPP

#include <stdexcept>

class Billiard
{
public:
	Billiard(const double r1, const double r2, const double l) //
		: m_r1{r1}, m_r2{r2}, m_l{l}						   //
	{
		if (m_r1 < 0 || m_r2 < 0 || m_l < 0)
		{
			throw std::domain_error("Negative argument in constructor");
		}
	}

	const double getR1() { return m_r1; }
	const double getR2() { return m_r2; }
	const double getL() { return m_l; }

private:
	double m_r1{};
	double m_r2{};
	double m_l{};
};

#endif // BILLIARD_HPP