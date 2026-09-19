class Solution {
public:
    bool checkOverlap(int radius, int xCenter, int yCenter,
                      int x1, int y1, int x2, int y2) {

        // Closest x-coordinate in rectangle to circle center
        int closestX = max(x1, min(xCenter, x2));

        // Closest y-coordinate in rectangle to circle center
        int closestY = max(y1, min(yCenter, y2));

        // Distance between closest point and circle center
        int dx = closestX - xCenter;
        int dy = closestY - yCenter;

        return dx * dx + dy * dy <= radius * radius;
    }
};