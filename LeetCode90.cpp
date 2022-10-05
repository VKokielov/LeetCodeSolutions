class Solution {
public:
    
    struct StateEntry
    {
        int value;
        unsigned int count;
        
        StateEntry(int value_, unsigned int count_)
            :value(value_), count(count_)
        { }
    };
    
    void exploreTree(vector<StateEntry>& stateVec,
                     vector<vector<int>>& answer,
                     int elementIndex)
    {
       // cout << "state vec size " << stateVec.size() << "\n";
        
        if (elementIndex == stateVec.size())
        {
            // Add as prescribed
            vector<int> result;
            for (auto& stateEntry : stateVec)
            {
        //        cout << "Adding " << stateEntry.count << " of " << stateEntry.value << "\n";
                
                for (unsigned int i = 0; i < stateEntry.count; ++i)
                {
                    result.push_back(stateEntry.value);
                }
            }
     //       cout << "---------\n";
            answer.emplace_back(move(result));
            return;
        }
        
 //       cout << "element index " << elementIndex << "\n";
        
        unsigned int maxCount = stateVec[elementIndex].count;
        for (unsigned int fcount = maxCount+1; 
             fcount > 0; 
             --fcount)
        {
            unsigned int realcount = fcount-1;
      //      cout << "setting count for " << stateVec[elementIndex].value << " to " << realcount << "\n";
            
            stateVec[elementIndex].count = realcount;
            exploreTree(stateVec, answer, elementIndex+1);
        }
        
        stateVec[elementIndex].count = maxCount;
    }
    
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int> > result;
        
        if (nums.empty())
        {
            return result;
        }
        
        unordered_map<int, unsigned int> histogram;
        
        for (int num : nums)
        {
            ++histogram[num];
        }
        
        // Convert to state vector
        vector<StateEntry> stateVec;
        for (auto& histEntry : histogram)
        {
            stateVec.emplace_back(histEntry.first, histEntry.second);
          // cout << "Adding " << histEntry.first << " " << histEntry.second << "\n";
        }
        
        
        exploreTree(stateVec, result, 0);
        
        return result;
    }
};
