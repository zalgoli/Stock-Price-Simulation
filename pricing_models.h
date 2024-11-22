#pragma once
#ifndef PRICING_MODELS_H
#define PRICING_MODELS_H

#include <cmath>
#include <vector>
#include <random>
#include <map>
#include <iostream>

struct StockData
{
	int year;
	double avgMinuteMovement; // average weighted historical minute movement
};

// function to simulate stock price movement based on Geometric Brownian Motion
std::vector<float> simulateGBM(float initial_price,
								const std::map<std::string, std::vector<StockData>> stockData, // Historical minute data
								const std::string& ticker,
								float sigma, // Constant volatility for simplicity
								float dt,
								int numDays);


#endif