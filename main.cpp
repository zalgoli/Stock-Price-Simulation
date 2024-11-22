#include <iostream>
#include <map>
#include <fstream>
#include <sstream>

#include "pricing_models.h"

std::map<std::string, std::vector<StockData>> readCSV(const std::string& filename)
{
	std::map<std::string, std::vector<StockData>> data;
	std::ifstream file(filename);

	if (!file.is_open())
	{
		std::cerr << "Error: Could not open file " << filename << std::endl;
		return data;
	}

	std::string line;

	std::getline(file, line); // Skip headers

	while (std::getline(file, line))
	{
		std::istringstream ss(line);
		std::string unused, ticker, yearStr, avgMovementStr;

		// Read CSV values
		std::getline(ss, unused, ',');         // Skip the first column (index)
		std::getline(ss, ticker, ',');         // Read ticker
		std::getline(ss, yearStr, ',');        // Read year
		std::getline(ss, avgMovementStr, ',');

		int year = std::stoi(yearStr);
		double avgMinuteMovement = std::stod(avgMovementStr);

		data[ticker].push_back({ year, avgMinuteMovement });
	}

	file.close();
	return data;
}

int main()
{
	float initial_price{ 100.0f };
	float sigma{ 0.2f };
	float dt{ 1.0f / (252.0f * 390.0f) };
	int steps{ 252 * 390 }; // The number of trading days in a year, the number of minutes in a trading day

	// Read data
	std::string filename = "nasdaq100_historical_data.csv";
	std::map<std::string, std::vector<StockData>> stockData = readCSV(filename);

	std::string ticker{};
	int numDays{};

	std::cout << "Enter the desired ticker, followed by the number of trading days you would like to simulate: \n";
	std::cin >> ticker;
	std::cin >> numDays;


	std::vector<float> prices = simulateGBM(initial_price, stockData, ticker, sigma, dt, numDays);

	for (size_t i = 0; i < prices.size(); i += 390) { // Print daily prices
		std::cout << "Day " << i / 390 + 1 << ": " << prices[i] << std::endl;
	}


	return 0;
}