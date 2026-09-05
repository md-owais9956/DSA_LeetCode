import java.util.HashMap;

class Solution {
    public int lengthOfLongestSubstring(String s) {

        // Stores character -> latest index
        HashMap<Character, Integer> map = new HashMap<>();

        int left = 0;
        int maxLength = 0;

        for (int right = 0; right < s.length(); right++) {

            char ch = s.charAt(right);

            // If character exists inside current window,
            // move left pointer after its previous position
            if (map.containsKey(ch)) {
                left = Math.max(left, map.get(ch) + 1);
            }

            map.put(ch, right);

            // Current window length
            maxLength = Math.max(maxLength, right - left + 1);
        }

        return maxLength;
    }
}