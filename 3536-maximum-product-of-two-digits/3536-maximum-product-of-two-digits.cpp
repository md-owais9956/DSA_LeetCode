class Solution {
public:
    int maxProduct(int n) {
        int digit;
        int max1 = n % 10 ; 
        n /= 10;
        int max2 = n % 10;
        n /= 10;
        
        while ( n ){
            digit = n % 10;
            if ( digit > max1 && max1 < max2 ){
                max1 = digit;
                n /= 10;
            }else if ( digit > max2 ){
                max2 = digit;
                n /= 10;
            }else{
                n /= 10;
            }
        }
        return (max1 * max2);
    }
};