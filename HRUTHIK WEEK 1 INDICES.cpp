#include <iostream>
#include <vector>
#include <unordered_map>

// Function to find the indices of two numbers that add up to the target
std::vector<int> twoSum(const std::vector<int>& nums, int target) {
    std::unordered_map<int, int> num_map; // Map to store number and its index

    for (int i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];
        // Check if the complement exists in the map
        if (num_map.find(complement) != num_map.end()) {
            return {num_map[complement], i}; // Return indices of the two numbers
        }
        // Store the current number and its index in the map
        num_map[nums[i]] = i;
    }

    return {}; // Return an empty vector if no solution is found (shouldn't happen as per constraints)
}

int main() {
    // Example inputs
    std::vector<int> nums1 = {2, 7, 11, 15};
    int target1 = 9;

    std::vector<int> nums2 = {3, 2, 4};
    int target2 = 6;

    std::vector<int> nums3 = {3, 3};
    int target3 = 6;

    // Test case 1
    std::vector<int> result1 = twoSum(nums1, target1);
    std::cout << "Output: [" << result1[0] << ", " << result1[1] << "]\n";

    // Test case 2
    std::vector<int> result2 = twoSum(nums2, target2);
    std::cout << "Output: [" << result2[0] << ", " << result2[1] << "]\n";

    // Test case 3
    std::vector<int> result3 = twoSum(nums3, target3);
    std::cout << "Output: [" << result3[0] << ", " << result3[1] << "]\n";

    return 0;
}
