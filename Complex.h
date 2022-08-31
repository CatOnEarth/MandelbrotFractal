#pragma once

/** Class which describe complex numbers */
class Complex_my {
public:
	/** Default constructor */
	Complex_my();
	/** Constructor copy
	 * 
	 * @param other complex number
	*/
	Complex_my(const Complex_my& other);
	/** Constructor by real and imaginary parts
	 * 
	 * @param re real part
	 * @param im imaginary part
	*/
	Complex_my(const double& re, const double& im);
	/** Constructor by real part
	 * 
	 * @param re real part
	*/
	Complex_my(const double& re);

	/** Operator += 
	 * 
	 * @param complex operand
	 */
	Complex_my operator+=(const Complex_my&);
	/** Operator + * 
	 * @param complex operand
	 */
	Complex_my operator+(const Complex_my&);
	/** Operator *=  * 
	 * @param complex operand
	 */
	Complex_my operator*=(const Complex_my&);
	/** Operator *  * 
	 * @param complex operand
	 */
	Complex_my operator*(const Complex_my&);
	/** Operator =  * 
	 * @param complex operand
	 */
	Complex_my operator=(const Complex_my&);
	/** Module of complex number */
	double module_sqr()const;

private:
	/** Real part */
    double re;
	/** Imaginary part */
    double im;
};

