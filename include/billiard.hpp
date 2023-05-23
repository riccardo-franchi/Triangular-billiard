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

private:
	double m_r1{};
	double m_r2{};
	double m_l{};
};