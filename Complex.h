#pragma once
class Complex_my
{
public:
	Complex_my();
	Complex_my(const Complex_my& other);
	Complex_my(const double& re, const double& im);
	Complex_my(const double& re);

	Complex_my operator+=(const Complex_my&);
	Complex_my operator+(const Complex_my&);
	Complex_my operator*=(const Complex_my&);
	Complex_my operator*(const Complex_my&);
	Complex_my operator=(const Complex_my&);
	double module_sqr()const;

private:
    double re;
    double im; // мнимая часть
};

