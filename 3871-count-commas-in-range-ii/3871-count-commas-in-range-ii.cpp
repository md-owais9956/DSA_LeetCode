class Solution {
public:
    long long countCommas(long long n) {
        long long comma;
        if ( n <= 999 )
            comma = 0;
        else if ( n <= 999999 ){
            comma = n-999;
        }else if ( n <= 999999999 ){
            comma = (n-999)+(n-999999);
        }else if ( n <= 999999999999 ){
            comma = (n-999)+(n-999999)+(n-999999999);
        }else if (n <= 999999999999999){
            comma = (n-999)+(n-999999)+(n-999999999)+(n-999999999999);
        }if(n > 999999999999999){
            comma = (n-999)+(n-999999)+(n-999999999)+(n-999999999999)+1;
        }

        return comma;
    }
};