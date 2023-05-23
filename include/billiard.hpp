#ifndef BILLIARD_HPP
#define BILLIARD_HPP

class Billiard
{
public:
	Billiard(double r1, double r2, double length) //
		: m_r1{r1}, m_r2{r2}, m_length{length} {};

	double r1() const { return m_r1; }
	double r2() const { return m_r2; }
	double length() const { return m_length; }

private:
	double m_r1;	 // y-value of the left end
	double m_r2;	 // y-value of the right end
	double m_length; // x-value of the right end
};

#endif // BILLIARD_HPP