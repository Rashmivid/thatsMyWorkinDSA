#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    cin.ignore();
    
    string line;
    getline(cin, line); // "shuffled"
    
    vector<string> shuffled(n);
    for (int i = 0; i < n; i++) {
        getline(cin, shuffled[i]);
    }
    
    getline(cin, line); // "original"
    
    vector<string> original(n);
    unordered_map<string, int> originalPos;
    for (int i = 0; i < n; i++) {
        getline(cin, original[i]);
        originalPos[original[i]] = i;
    }
    
    // Map shuffled instructions to their positions in original
    vector<int> positions(n);
    for (int i = 0; i < n; i++) {
        positions[i] = originalPos[shuffled[i]];
    }
    
    // Find longest increasing subsequence
    vector<int> lis;
    vector<int> lisIndices; // indices in shuffled array that form LIS
    
    for (int i = 0; i < n; i++) {
        auto it = lower_bound(lis.begin(), lis.end(), positions[i]);
        if (it == lis.end()) {
            lis.push_back(positions[i]);
        } else {
            *it = positions[i];
        }
    }
    
    int lisLength = lis.size();
    
    // Elements not in LIS need to be moved
    // We need to count contiguous segments that need moving
    
    // Reconstruct which elements are in LIS
    vector<int> dp(n);
    vector<int> parent(n, -1);
    
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (positions[j] < positions[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
    }
    
    // Find the actual LIS elements
    int maxLen = 0, maxIdx = -1;
    for (int i = 0; i < n; i++) {
        if (dp[i] > maxLen) {
            maxLen = dp[i];
            maxIdx = i;
        }
    }
    
    vector<bool> inLIS(n, false);
    int idx = maxIdx;
    while (idx != -1) {
        inLIS[idx] = true;
        idx = parent[idx];
    }
    
    // Count contiguous segments not in LIS
    int segments = 0;
    bool inSegment = false;
    for (int i = 0; i < n; i++) {
        if (!inLIS[i]) {
            if (!inSegment) {
                segments++;
                inSegment = true;
            }
        } else {
            inSegment = false;
        }
    }
    
    cout << segments << endl;
    
    return 0;
}