class Solution {
public:
    int minimumPushes(string word) {
        int count;
        if( word.length() <= 8 ){
            for(int i = 0; i < word.length(); i++){
                count++;
            }
        }else if ( word.length() <= 16 ){
            count = 8;
            for(int i = 0; i < word.length() - 8; i++){
                count += 2;
            }
            }else if ( word.length() <= 24 ){
                count = 24;
                for (int i = 0; i < word.length() - 16; i++){
                    count += 3;
                }
            }else{
                count = 48;
                for(int i = 0; i < word.length() - 24; i++){
                    count += 4;
                }
            }
        
        return count;
    }
};