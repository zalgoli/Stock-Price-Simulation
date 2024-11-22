# Stock Price Simulation

**A C++ project to simulate stock price movements using the Geometric Brownian Motion (GBM) model, integrated with real historical data for the top 100 NASDAQ companies.**

---

## Features
- Implements Geometric Brownian Motion for stock price simulation.
- Incorporates real historical average minute-by-minute changes.
- Dynamically handles multi-year data and user-specified durations.
- Outputs simulation results for custom analysis.

---

## How to Use

- Run historical_data.py to obtain the NASDAQ Top 100's historical data for the past 10 years and aggregate it into "nasdaq100_historical_data.csv"
- Compile main.cpp using your favorite compiler (make sure it supports C++17 or higher)