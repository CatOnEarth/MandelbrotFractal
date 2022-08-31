#include "Complex.h"

Complex_my::Complex_my() {
    re = 0;
    im = 0;
}

Complex_my::Complex_my(const Complex_my& other) {
    re = other.re;
    im = other.im;
}

Complex_my::Complex_my(const double & re_, const double& im_) {
    re = re_;
    im = im_;
}

Complex_my::Complex_my(const double& re_) {
    re = re_;
    im = 0;
}

Complex_my Complex_my::operator=(const Complex_my& other) {
    re = other.re;
    im = other.im;
    return *this;
}

Complex_my Complex_my::operator+(const Complex_my& other) {
    Complex_my c(*this);
    return c += other;
}

Complex_my Complex_my::operator+=(const Complex_my& other) {
    re += other.re;
    im += other.im;
    return *this;
}

Complex_my Complex_my::operator*(const Complex_my& other) {
    Complex_my c(*this);
    return c *= other;
}

Complex_my Complex_my::operator*=(const Complex_my& other) {
    Complex_my c;
    c.re = re * other.re - im * other.im;
    c.im = re * other.im + im * other.re;
    *this = c;
    return *this;
}

double Complex_my::module_sqr()const {
    return re * re + im * im;
}