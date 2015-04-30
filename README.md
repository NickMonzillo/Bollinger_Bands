# Bollinger_Bands
An algorithmic trading strategy written in C++.

This program runs an algorithmic trading strategy that utilizes Bollinger Bands to buy and sell shares.
Requires a .csv file of daily price data.

Strategy:
Buy shares when the stock price is below a specified number of standard deviations from the moving average.
Sell shares when the stock price is above a specified number of standard deviations from the moving average.

A graph of the strategy. Signal is 1 if buy, -1 if sell, 0 if hold:

![alt tag](http://i.imgur.com/uxwmoHr.png)
