#include "../pch.h"
#include <iostream>
#include <cmath>
#include <string>
#include "Vec2.h"

//std::ostream& lm::operator<<(std::ostream& stream, vec2& vec)
//{
//	stream << vec.X() << "," << vec.Y();
//	return stream;
//}
//
//std::ostream& lm::operator<<(std::ostream& stream, const vec2& vec)
//{
//	stream << vec.X() << "," << vec.Y();
//	return stream;
//}
//
//void lm::operator>>(std::istream& stream, vec2& vec)
//{
//	std::string str;
//
//	stream >> str;
//	int delimiter = 0;
//	for (unsigned int x = 0; x <= str.length(); x++)
//	{
//		if (str[x] == ',')
//		{
//			delimiter = x;
//			break;
//		}
//	}
//	if (delimiter == 0)
//	{
//		vec.X() = 0;
//		vec.Y() = 0;
//	}
//	else
//	{
//		std::string Xstr = str.substr(0, delimiter);
//		if (Xstr[0] < '0' || Xstr[0] > '9')
//			vec.X() = 0;
//		else
//			vec.X() = std::stof(Xstr);
//
//		delimiter = delimiter + 1;
//		std::string Ystr = str.substr(delimiter, str.length());
//		if (Ystr[0] < '0' || Ystr[0] > '9')
//			vec.Y() = 0;
//		else
//			vec.Y() = std::stof(Ystr);
//	}
//}
//
//std::string lm::operator+(std::string str, const vec2& vec)
//{
//	return str + "x: " + std::to_string(vec.X()) + ", y: " + std::to_string(vec.Y());
//}
//
//void lm::operator+=(std::string& str, const vec2& vec)
//{
//	str += "x: " + std::to_string(vec.X()) + ", y: " + std::to_string(vec.Y());
//}
//
//lm::vec2 lm::operator+(const vec2& vec_1, const vec2& vec_2)
//{
//	return vec2(vec_1.X() + vec_2.X(), vec_1.Y() + vec_2.Y());
//}
//
//lm::vec2 lm::operator-(const vec2& vec_1, const vec2& vec_2)
//{
//	return vec2(vec_1.X() - vec_2.X(), vec_1.Y() - vec_2.Y());
//}
//
//lm::vec2 lm::operator-(const vec2& vec)
//{
//	return vec2(vec.X() * -1, vec.Y() * -1);
//}
//
//lm::vec2 lm::operator*(const vec2& vec, const float mult)
//{
//	return vec2(vec.X() * mult, vec.Y() * mult);
//}
//
//lm::vec2 lm::operator*(const float mult, const vec2& vec)
//{
//	return vec2(vec.X() * mult, vec.Y() * mult);
//}
//
//lm::vec2 lm::operator/(const vec2& vec, const float div)
//{
//	return vec2(vec.X() / div, vec.Y() / div);
//}
//
//lm::vec2 lm::operator/(const float div, const vec2& vec)
//{
//	return vec2(div / vec.X(), div / vec.Y());
//}
//
//float lm::operator,(const vec2& vec_1, const vec2& vec_2)
//{
//	return vec_1.X() * vec_2.X() + vec_1.Y() * vec_2.Y();
//}
//
//using namespace lm;
//
//vec2 vec2::zero = vec2(0.f, 0.f);
//vec2 vec2::up = vec2(0.f, 1.f);
//vec2 vec2::down = vec2(0.f, -1.f);
//vec2 vec2::right = vec2(1.f, 0.f);
//vec2 vec2::left = vec2(-1.f, 0.f);
//
//vec2::vec2()
//{
//	this->x = 0;
//	this->y = 0;
//}
//
//vec2::vec2(float x, float y)
//{
//	this->x = x;
//	this->y = y;
//}
//
//vec2::vec2(float point)
//{
//	this->x = point;
//	this->y = point;
//}
//
//vec2::vec2(const vec2& vec)
//{
//	this->x = vec.x;
//	this->y = vec.y;
//}
//
//float& vec2::X()
//{
//	return this->x;
//}
//
//float& vec2::Y()
//{
//	return this->y;
//}
//
//float vec2::X() const
//{
//	return this->x;
//}
//
//float vec2::Y() const
//{
//	return this->y;
//}
//
//vec2& vec2::operator=(const vec2& vec)
//{
//	if (this == &vec)
//	{
//		return *this;
//	}
//
//	this->x = vec.x;
//	this->y = vec.y;
//	return *this;
//}
//
//float& vec2::operator[](int idx)
//{
//	if (idx == 0 || idx == 'x')
//		return this->x;
//
//	if (idx == 1 || idx == 'y')
//		return this->y;
//
//	return this->x;
//}
//
//float& vec2::operator[](std::string const& idx)
//{
//	if (idx == "x")
//		return this->x;
//
//	if (idx == "y")
//		return this->y;
//
//	return this->x;
//}
//
//const bool vec2::operator==(const vec2& vec) const
//{
//	if (length() == vec.length())
//	{
//		return 1;
//	}
//	return fabs(length() - vec.length()) <= std::numeric_limits<float>::epsilon() ||
//		fabs(length() - vec.length()) <= std::numeric_limits<float>::epsilon() * std::max(fabs(length()), fabs(vec.length()));
//}
//
//const bool vec2::operator!=(const vec2& vec) const
//{
//	return !(*this == vec);
//}
//
//const bool vec2::operator<(const vec2& vec) const
//{
//	if (length() < vec.length())
//	{
//		return 1;
//	}
//	else
//		return 0;
//}
//
//const bool vec2::operator<=(const vec2& vec) const
//{
//	if (length() < vec.length())
//	{
//		return true || (*this == vec);
//	}
//	else
//		return 0;
//}
//
//const bool vec2::operator>(const vec2& vec) const
//{
//	if (length() > vec.length())
//	{
//		return 1;
//	}
//	else
//		return 0;
//}
//
//const bool vec2::operator>=(const vec2& vec) const
//{
//	if (length() > vec.length())
//	{
//		return true || (*this == vec);
//	}
//	else
//		return 0;
//}
//
//vec2& vec2::operator+=(const vec2& vec)
//{
//	this->x += vec.x;
//	this->y += vec.y;
//	return *this;
//}
//
//vec2& vec2::operator-=(const vec2& vec)
//{
//	this->x -= vec.x;
//	this->y -= vec.y;
//	return *this;
//}
//
//vec2& vec2::operator*=(const float mult)
//{
//	this->x *= mult;
//	this->y *= mult;
//	return *this;
//}
//
//vec2& vec2::operator/=(const float div)
//{
//	this->x /= div;
//	this->y /= div;
//	return *this;
//}
//
//vec2& vec2::operator++(int)
//{
//	float a = length();
//	this->x *= (a + 1) / a;
//	this->y *= (a + 1) / a;
//	return *this;
//}
//
//vec2& vec2::operator--(int)
//{
//	float a = length();
//	this->x *= (a - 1) / a;
//	this->y *= (a - 1) / a;
//	return *this;
//}
//
//float vec2::length() const
//{
//	float add = this->x * this->x + this->y * this->y;
//	return sqrt(add);
//}
//
//float vec2::length_squared() const
//{
//	return this->x * this->x + this->y * this->y;
//}
//
//const float vec2::dot_product(const vec2& vec) const
//{
//	return this->x * vec.x + this->y * vec.y;
//}
//
//const float vec2::cross_product(const vec2& vec) const
//{
//	return this->x * vec.y - this->y * vec.x;
//}
//
//vec2 vec2::add(const vec2& vec) const
//{
//	return vec2(this->x + vec.x, this->y + vec.y);
//}
//
//vec2 vec2::scale(float scaler) const
//{
//	return vec2(this->x * scaler, this->y * scaler);
//}
//
//vec2 vec2::normalized() const
//{
//	float a = length();
//	return vec2(this->x / a, this->y / a);
//}
//
//vec2& vec2::add(const vec2& vec)
//{
//	this->x += vec.x;
//	this->y += vec.y;
//	return *this;
//}
//
//vec2& vec2::scale(float scaler)
//{
//	this->x *= scaler;
//	this->y *= scaler;
//	return *this;
//}
//
//vec2& vec2::normalize()
//{
//	float a = length();
//	this->x /= a;
//	this->y /= a;
//	return *this;
//}
//
//const bool vec2::IsUnit() const
//{
//	if (length() == 1)
//		return true;
//
//	return fabs(length() - 1.f) <= std::numeric_limits<float>::epsilon() ||
//		fabs(length() - 1.f) <= std::numeric_limits<float>::epsilon() * std::max(fabs(length()), fabs(1.f));
//}
//
//const float vec2::RadiansToDegrees(const float rad) const
//{
//	return rad * HALF_CIRCLE / M_PI;
//}
//
//const float vec2::DegreesToRadians(const float deg) const
//{
//	return deg * M_PI / HALF_CIRCLE;
//}
//
//const float vec2::degree_angle_between_vec(const vec2& vec_2) const
//{
//	float rad_angle = red_angle_between_vec(vec_2);
//	float degree_angle = RadiansToDegrees(rad_angle);
//	return degree_angle;
//}
//
//const float vec2::red_angle_between_vec(const vec2& vec_2) const
//{
//	float magn1 = this->length_squared();
//	float magn2 = vec_2.length_squared();
//	float dot = dot_product(vec_2);
//	float lenght = sqrt(magn1 * magn2);
//	float rad_angle = std::acos(dot / lenght);
//	return rad_angle;
//}
//
//vec2 vec2::projection(const vec2& vec) const
//{
//	float a = dot_product(vec);
//	float norm_of_v2 = vec.x * vec.x + vec.y * vec.y;
//
//	float x = (a / norm_of_v2) * vec.x;
//	float y = (a / norm_of_v2) * vec.y;
//
//	return vec2(x, y);
//}
//
//vec2 vec2::reflexion(const vec2& normal) const
//{
//	if (normal.IsUnit() == false)
//	{
//		float a = this->x - 2 * ((this->x * normal.x) / normal.length_squared()) * normal.x;
//		float b = this->y - 2 * ((this->y * normal.y) / normal.length_squared()) * normal.y;
//		return vec2(a, b);
//	}
//
//	float a = this->x - 2 * (this->x * normal.x) * normal.x;
//	float b = this->y - 2 * (this->y * normal.y) * normal.y;
//	return vec2(a, b);
//}
//
//vec2::~vec2()
//{
//}