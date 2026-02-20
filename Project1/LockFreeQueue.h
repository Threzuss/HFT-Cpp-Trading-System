#pragma once
#ifndef LOCK_FREE_QUEUE_H
#define LOCK_FREE_QUEUE_H

#include <atomic>
#include <array>
#include <type_traits>

template<typename T, size_t Size>
class LockFreeQueue {

	static_assert((Size != 0) && ((Size& (Size - 1)) == 0), "Size must be a power of 2");

public:
	LockFreeQueue() : head_(0), tail_(0) {}

	bool push(const T& item) {

		const size_t current_tail = tail_.load(std::memory_order_relaxed);

		const size_t next_tail = (current_tail + 1) & (Size - 1);

		if (next_tail == head_.load(std::memory_order_acquire)) {
			return false;
		}

		buffer_[current_tail] = item;
		tail_.store(next_tail, std::memory_order_release);

		return true;
	}

	bool pop(T& item) {
		const size_t current_head = head_.load(std::memory_order_relaxed);

		if (current_head == tail_.load(std::memory_order_acquire)) {
			return false;
		}

		item = buffer_[current_head];
		head_.store((current_head + 1) & (Size - 1), std::memory_order_release);

		return true;
	}

private:

	std::array<T, Size> buffer_;

	alignas(64) std::atomic<size_t> head_;
	alignas(64) std::atomic<size_t> tail_;
};

#endif
