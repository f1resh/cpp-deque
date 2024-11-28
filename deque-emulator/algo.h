#pragma once

#include <deque>

template<class T, class Comp>
std::deque<T> Merge(const std::deque<T>& half1, const std::deque<T>& half2, const Comp& comparator) {
    size_t index1 = 0;
	size_t index2 = 0;
	size_t size1 = half1.size();
	size_t size2 = half2.size();
    std::deque<T> result;
    while (index1 < size1 && index2 < size2){
        if (comparator(half1[index1], half2[index2])) {
            result.push_back(half1[index1++]);
        } else {
            result.push_back(half2[index2++]);
        }
    }
    while (index2 < size2){
		result.push_back(half2[index2++]);
	}
    while (index1 < size1){
		result.push_back(half1[index1++]);
	}
    return result;
}

template<class T, class Comp>
std::deque<T> MergeSort(const std::deque<T>& src, const Comp& comparator) {
    if (src.size() <= 1) {
        return src;
    }
    const size_t mid = src.size() / 2;
    const std::deque<T> left_sorted = MergeSort(std::deque<T>(src.begin(), src.begin() + mid), comparator);
    const std::deque<T> right_sorted = MergeSort(std::deque<T>(src.begin() + mid, src.end()), comparator);
    return Merge(left_sorted, right_sorted, comparator);
}
