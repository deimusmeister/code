#include <iostream>
#include <vector>

/**
 * Counting sort works on data set the **range of which is known**
 *  e.g. integers from 1 to 100
 * Description : 
 *    The idea is following
 *    1. count the number of elements with the same value and put 
 *       into the same bucket
 *    2. update the buckets by adding the the value of previous 
 *       bucket into current bucket
 *       **As we know the range of elements, by this action we will 
 *       store in each action how many elements are in bucket with
 *       lesser value**
 *    3. Interage over the input arra and store it into the slot at
 *       index with (bucket_size -1)
 *       **This will guarantee the in order location of elements,
 *       as in previous step we've constructed buckets with 
 *       corresponding size**
 */

std::vector<int> countingSort(std::vector<int> v, int start, int end) {
    std::vector<int> result(v.size());
    std::vector<int> buckets(end - start + 1);
    for(auto i : v) {
        ++buckets[i];
    }
    for(auto i = buckets.begin(); i != std::prev(buckets.end()); ++i) {
        auto next = std::next(i);
        *next = *next + *i;
    }
    for(auto i : v) {
        result[buckets[i] - 1] = i;
        --buckets[i];  
    }
    return result;
}


int main() {
    auto result1 = countingSort({4, 1, 3, 2, 5, 5, 6}, 0, 100);
    // Test1 
    for(auto i : result1) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}
