/* 2561. Rearranging Fruits:
You have two fruit baskets containing n fruits each. You are given two 0-indexed integer arrays basket1 and basket2 representing the cost
of fruit in each basket. 
You want to make both baskets equal. To do so, you can use the following operation as many times as you want:

Choose two indices i and j, and swap the ith fruit of basket1 with the jth fruit of basket2.
The cost of the swap is min(basket1[i], basket2[j]).
Two baskets are considered equal if sorting them according to the fruit cost makes them exactly the same baskets.

Return the minimum cost to make both the baskets equal or -1 if impossible. */


// Method 1
class Solution {
public:
    long long minCost(vector<int>& basket1, vector<int>& basket2) {
        unordered_map<int, int> mp;
        int minEl = INT_MAX;

        for(int &x : basket1) {
            mp[x]++;
            minEl = min(minEl, x);
        }

        for(int &x : basket2) {
            mp[x]--;
            minEl = min(minEl, x);
        }

        vector<int> finalList;
        for(auto &it : mp) {
            int cost  = it.first;
            int count = it.second;

            if(count == 0) {
                continue;
            }

            if(count % 2 != 0) {
                return -1;
            }

            for(int c = 1; c <= abs(count)/2; c++) {
                finalList.push_back(cost);
            }
        }

        //sort(begin(finalList), end(finalList)); //no need to sort entire array
        nth_element(begin(finalList), begin(finalList)+finalList.size()/2, end(finalList));

        long long result = 0;
        for(int i = 0; i < finalList.size()/2; i++) {
            result += min(finalList[i], minEl*2);
        }

        return result;
    }
};





// Method 2
/* class Solution {
public:
    long long minCost(vector<int>& basket1, vector<int>& basket2) {
        map<int, int> freq;
        map<int, int> count1, count2;

        // Count frequency in each basket
        for (int val : basket1) count1[val]++;
        for (int val : basket2) count2[val]++;
        
        // Total frequency of each fruit
        for (auto& [val, cnt] : count1) freq[val] += cnt;
        for (auto& [val, cnt] : count2) freq[val] += cnt;

        // Check if rearrangement is possible
        for (auto& [val, cnt] : freq) {
            if (cnt % 2 != 0) return -1;
        }

        vector<int> extra1, extra2;

        for (auto& [val, cnt] : freq) {
            int diff = count1[val] - count2[val];
            if (diff > 0) {
                for (int i = 0; i < diff / 2; ++i)
                    extra1.push_back(val);
            } else if (diff < 0) {
                for (int i = 0; i < -diff / 2; ++i)
                    extra2.push_back(val);
            }
        }

        sort(extra1.begin(), extra1.end());
        sort(extra2.rbegin(), extra2.rend()); // descending

        int minVal = min(*min_element(basket1.begin(), basket1.end()),
                         *min_element(basket2.begin(), basket2.end()));

        long long cost = 0;
        for (int i = 0; i < extra1.size(); ++i) {
            int a = extra1[i];
            int b = extra2[i];
            cost += min(2 * minVal, min(a, b));
        }

        return cost;
    }
}; */
