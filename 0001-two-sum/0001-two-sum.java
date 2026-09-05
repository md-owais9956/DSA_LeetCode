import java.util.HashMap;

class Solution {
    public int[] twoSum(int[] nums, int target) {

        // Stores number -> index
        HashMap<Integer, Integer> map = new HashMap<>();

        for (int i = 0; i < nums.length; i++) {

            int needed = target - nums[i];

            // If the required number was already seen
            if (map.containsKey(needed)) {
                return new int[]{map.get(needed), i};
            }

            // Store current number and its index
            map.put(nums[i], i);
        }

        return new int[]{};
    }
}