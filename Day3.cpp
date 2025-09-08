/* 2106. Maximum Fruits Harvested After at Most K Steps:
Fruits are available at some positions on an infinite x-axis. You are given a 2D integer array fruits where fruits[i] = [positioni, amounti]
depicts amounti fruits at the position positioni. fruits is already sorted by positioni in ascending order, and each positioni is unique.

You are also given an integer startPos and an integer k. Initially, you are at the position startPos. From any position, you can either walk
to the left or right. It takes one step to move one unit on the x-axis, and you can walk at most k steps in total. For every position you reach,
you harvest all the fruits at that position, and the fruits will disappear from that position.

Return the maximum total number of fruits you can harvest. */


/* class Solution {
public:
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
        int n = fruits.size();
        vector<int> prefixSum(n);
        vector<int> indices(n);   // positions(n)

        // Build prefix sum and extract indices
        for (int i = 0; i < n; i++) {
            indices[i]   = fruits[i][0];
            prefixSum[i] = fruits[i][1] + (i > 0 ? prefixSum[i - 1] : 0);
        }

        int maxFrutis = 0;

        for (int d = 0; d <= k / 2; d++) {
            // Move
            int remain = k - 2 * d;
            int i  = startPos - d;
            int j  = startPos + remain;

            int left = lower_bound(indices.begin(), indices.end(), i) - indices.begin();
            int right = upper_bound(indices.begin(), indices.end(), j) - indices.begin() - 1;

            if(left <= right) {
                int total = prefixSum[right] - (left > 0 ? prefixSum[left - 1] : 0);
                maxFrutis = max(maxFrutis, total);
            }

            // Second case: move right x, then left (k - 2x)
            i  = startPos - remain;
            j  = startPos + d;
            
            left  = lower_bound(indices.begin(), indices.end(), i) - indices.begin();
            right = upper_bound(indices.begin(), indices.end(), j) - indices.begin() - 1;

            if(left <= right) {
                int total = prefixSum[right] - (left > 0 ? prefixSum[left - 1] : 0);
                maxFrutis = max(maxFrutis, total);
            }
        }

        return maxFrutis;
    }
}; */






// Method 2
class Solution {
    public:
        int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k){
            int n = fruits.size();

            vector<int> prefixSum(n);   // fruits prefixSum
            vector<int> positions(n);   // sorted already 

            for(int i=0; i<n; i++){
                positions[i] = fruits[i][0];
                prefixSum[i] = fruits[i][1] + (i > 0 ? prefixSum[i-1] : 0);
            }

            int maxFruits = 0;

            for(int d=0; d <= k/2; d++){
                // case 1 - moved 'd' steps to the left 
                int remain = k-2*d;
                int i = startPos - d;
                int j = startPos + remain;

                int left = lower_bound(begin(positions), end(positions), i) - begin(positions);
                int right = upper_bound(begin(positions), end(positions), j) - begin(positions) - 1;


                if(left <= right){
                    int total = prefixSum[right] - (left > 0 ? prefixSum[left-1] : 0);
                    maxFruits = max(maxFruits, total);
                }

                // case 2 - moved 'd' to the right hand side
                // remain = k - 2*d;
                i = startPos - remain;
                j = startPos + d;

                left = lower_bound(begin(positions), end(positions), i) - begin(positions);
                right = upper_bound(begin(positions), end(positions), j) - begin(positions) - 1;

                if(left <= right) {
                    int total = prefixSum[right] - (left > 0 ? prefixSum[left-1] : 0);
                    maxFruits = max(maxFruits, total);
                }
            }

            return maxFruits;
        }
};
