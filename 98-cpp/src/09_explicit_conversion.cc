#include "09_explicit_conversion.h"
#include <zephyr/logging/log.h>
#include <iostream>
#include <string>

LOG_MODULE_REGISTER(explicit_conversion, LOG_LEVEL_INF);

using String = std::string;

namespace _09_explicit_conversion
{

class Temperature
{
private:
	double celsius_;

public:
	// Single-parameter constructor allows implicit conversion
	Temperature(double celsius) : celsius_(celsius)
	{
	}

	void Print() const
	{
		std::cout << "Temperature: " << celsius_ << "°C" << std::endl;
	}

	double GetCelsius() const
	{
		return celsius_;
	}

	static void ProcessTemperature(const Temperature &temp)
	{
		temp.Print();
	}
};

class Distance
{
private:
	double meters_;

public:
	// Explicit keyword prevents implicit conversion
	explicit Distance(double meters) : meters_(meters)
	{
	}

	void Print() const
	{
		std::cout << "Distance: " << meters_ << "m" << std::endl;
	}

	double GetMeters() const
	{
		return meters_;
	}

	static void ProcessDistance(const Distance &dist)
	{
		dist.Print();
	}
};

int Entry()
{
	LOG_INF("Starting Explicit Conversion example...");

	std::cout << "=== Implicit Conversion (Temperature) ===" << std::endl;
	Temperature temp1 = 25.5;
	temp1.Print();
	Temperature::ProcessTemperature(30);

	std::cout << "=== Explicit Conversion (Distance) ===" << std::endl;
	Distance dist1(100.0);
	dist1.Print();
	Distance::ProcessDistance(Distance(50.0));
	std::cout << "ProcessDistance(50) would NOT compile - prevents accidental conversion"
		  << std::endl;

	std::cout << std::endl;
	return 0;
}

} // namespace _09_explicit_conversion
