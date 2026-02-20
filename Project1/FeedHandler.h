#pragma once
#ifndef FEED_HANDLER_H
#define FEED_HANDLER_H

#include "LockFreeQueue.h"
#include <iostream>

struct MarketOrder {
	long long orderId;
	double price;
	int quantity;
};

class FeedHandler {
private:
	LockFreeQueue<MarketOrder, 1024>& orderBook_;

public:
	FeedHandler(LockFreeQueue<MarketOrder, 1024>& orderBook) : orderBook_(orderBook) {}

	void runDataIngestion(int totalOrderstoSimulate) {
		int successfulPushes = 0;
		int droppedOrders = 0;

		for (int i = 0; i < totalOrderstoSimulate; ++i) {
			MarketOrder incomingOrder = {
				i,
				150.0 + (i % 10),
				100
			};
			if (orderBook_.push(incomingOrder)) {
				successfulPushes++;
			}
			else {
				droppedOrders++;
			}
		}

		std::cout << "[Feed Handler] Ingestion Complete.\n";
		std::cout << " -> Successfully Pushed: " << successfulPushes << "\n";
		std::cout << " -> Dropped(Buffer Full): " << droppedOrders << "\n";
	}

};

#endif