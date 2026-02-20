#include <iostream>
#include <chrono>
#include "LockFreeQueue.h"
#include "FeedHandler.h"

int main() {
	std::cout << "=== HFT System Booting ===\n";

	LockFreeQueue<MarketOrder, 1024> orderBook;
	FeedHandler feedHandler(orderBook);

	const int totalOrders = 1'000'000;
	std::cout << "[System] Commencing 1-Million Order Stress Test..\n";

	auto start =
		std::chrono::high_resolution_clock::now();
	feedHandler.runDataIngestion(totalOrders);

	auto end =
		std::chrono::high_resolution_clock::now();

	auto duration_ms =
		std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto duration_us =
		std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	
	std::cout << "\n=== PERFORMANCE REPORT ===\n";
	std::cout << "Total Time: " << duration_ms.count() << " milliseconds (" << duration_us.count() << " microseconds)\n";

	double ordersPerMicro = 
		(double)totalOrders / duration_us.count();
	std::cout << "Throughput: " << ordersPerMicro << " orders per microsecond\n";
	
	return 0;
}