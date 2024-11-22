#include "pricing_models.h"

/*
A version of Geometric Brownian Movement, where we implement real-life historical stock data into the volatility index.
The standard discrete yearly volatility value (mu) is replaced by minute-by-minute weighted average volatility data from the
NASDAQ Top 100's past 10 years.
*/

std::vector<float> simulateGBM(
					float initial_price,
					const std::map<std::string, std::vector<StockData>> stockData, // Historical minute data
					const std::string& ticker,
					float sigma, // Constant volatility for simplicity
					float dt,
					int numDays)
{
	std::vector<float> prices;
	prices.push_back(initial_price);


	// Mersenne-Twister random device
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> range(0.0, 1.0);

	if (stockData.find(ticker) == stockData.end())
	{
		std::cerr << "Ticker not found: " << ticker << std::endl;
		return prices;
	}

	const auto& companyData = stockData.at(ticker);


	int totalSteps{ numDays * 390 };

	size_t yearIndex = 0;
	for (int step = 0; step < totalSteps; ++step) {
		// Switch to the next year's parameters if needed
		if (yearIndex >= companyData.size()) {
			std::cerr << "Insufficient data to simulate " << numDays << " days." << std::endl;
			break;
		}
		double mu_minute = companyData[yearIndex].avgMinuteMovement;

		// Generate GBM for the current minute
		double Z = range(gen); // Random component
		double prevPrice = prices.back();
		double newPrice = prevPrice * exp((mu_minute - 0.5 * sigma * sigma) * dt + sigma * sqrt(dt) * Z);
		prices.push_back(newPrice);

		// Transition to the next year's data if all minutes for the current year are processed
		if ((step + 1) % (390 * 252) == 0) { // 252 trading days in a year
			++yearIndex;
		}
	}

	return prices;
}
