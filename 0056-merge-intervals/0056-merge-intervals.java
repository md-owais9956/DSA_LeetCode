import java.util.*;

class Solution {
    public int[][] merge(int[][] intervals) {

        // Sort intervals based on starting time
        Arrays.sort(intervals, (a, b) -> Integer.compare(a[0], b[0]));

        List<int[]> merged = new ArrayList<>();

        int[] current = intervals[0];

        for (int i = 1; i < intervals.length; i++) {

            // Overlapping intervals
            if (intervals[i][0] <= current[1]) {

                // Extend the ending point
                current[1] = Math.max(current[1], intervals[i][1]);

            } else {

                // No overlap, store previous interval
                merged.add(current);

                current = intervals[i];
            }
        }

        // Add the last interval
        merged.add(current);

        return merged.toArray(new int[merged.size()][]);
    }
}