#include <iostream>
#include "LockFreeQueue.h" 


struct MarketOrder {
    long long orderId;
    double price;
    int quantity;
};

int main() {
    
    std::cout << "[System] Initializing HFT Order Book..." << std::endl;
    LockFreeQueue<MarketOrder, 1024> orderBook;

    MarketOrder incomingOrder = { 999, 150.25, 100 };

    if (orderBook.push(incomingOrder)) {
        std::cout << "[Producer] Order #999 Pushed to Ring Buffer." << std::endl;
    }
    else {
        std::cout << "[Producer] Buffer Full! Order Dropped." << std::endl;
    }

    MarketOrder processedOrder;

    if (orderBook.pop(processedOrder)) {
        std::cout << "[Consumer] Order Popped! Processing Price: " << processedOrder.price << std::endl;
    }
    else {
        std::cout << "[Consumer] Buffer Empty. Waiting..." << std::endl;
    }

    if (processedOrder.orderId == 999) {
        std::cout << "[Test Passed] Data integrity verified." << std::endl;
    }

    return 0;
}
