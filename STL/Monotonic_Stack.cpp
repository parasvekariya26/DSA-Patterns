#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> inputArray() {
    int n;
    cout << "Enter Size : ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter Elements : ";
    for (int i = 0; i < n; i++) cin >> arr[i];
    return arr;
}

void printArray(const vector<int>& arr) {
    cout << "[ ";
    for (int x : arr)
        cout << x << " ";
    cout << "]\n";
}

// =====================================================
// NEXT GREATER ELEMENT II (Circular)
// =====================================================
vector<int> nextGreaterElement(vector<int>& nums) {
    int n = nums.size();
    stack<int> st;
    vector<int> ans(n, -1);
    for (int i = 2 * n - 1; i >= 0; i--) {
        while (!st.empty() && nums[i % n] >= st.top())
            st.pop();
        if (!st.empty())
            ans[i % n] = st.top();
        st.push(nums[i % n]);
    }
    return ans;
}

// =====================================================
// MAIN
// =====================================================
int main() {

    // ---------- Debug Test Cases ----------
    vector<vector<int>> testCases = {
        {1, 2, 1},          // Expected: [2, -1, 2]
        {1, 2, 3, 4, 3}     // Expected: [2, 3, 4, -1, 4]
    };

    // Select test case (change index only)
    vector<int> arr = testCases[0];
    // vector<int> arr = testCases[1];

    // For manual input, comment the above line and uncomment below
    // vector<int> arr = inputArray();

    cout << "Input  : ";
    printArray(arr);

    vector<int> ans = nextGreaterElement(arr);

    cout << "Output : ";
    printArray(ans);

    return 0;
}