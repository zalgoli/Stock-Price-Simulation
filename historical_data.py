import yfinance as yf # Yahoo Finance public API
import pandas as pd
import openpyxl
import os

def split_date(date):
    date_list = date.split()[0].split("-")
    return date_list[0], date_list[1], date_list[2]

with open("tickers.txt", "r") as file:
	str_tickers = file.readline()

tickers = [x for x in str_tickers.split()]

start_date = '2014-11-17'
end_date = '2024-11-17'

df = pd.DataFrame()

for ticker in tickers:
	print(f"Fetching data for {ticker}")
	data = yf.download(ticker, start = start_date, end = end_date)
	data['Ticker'] = ticker
	data.reset_index(inplace = True)
	data['Date'] = data['Date'].astype(str)
	data.set_index('Date', inplace = True)
	data.columns = data.columns.droplevel(1)
	df = pd.concat([df,data])
	
print(df.columns)
df.reset_index(inplace = True)
df[["Year","Month","Day"]] = df["Date"].apply(lambda x: split_date(x)).apply(pd.Series)
df["Weighted Movement"] = (((df["High"] - df["Low"]) / 390))

df["Average Price"] = (df["High"] + df["Low"]) / 2
df["Weighted Movement (%)"] = (((df["High"] - df["Low"]) / 390) / df["Average Price"]) * 100

result = df.groupby(['Ticker', 'Year'])['Weighted Movement'].mean().reset_index()
result.columns = ['Ticker', 'Year', 'Average Weighted Minute Movement']

result.to_csv("nasdaq100_historical_data.csv")


(((df["High"] - df["Low"]) / 390) * df["Volume"].sum()) / df["Volume"].sum()
