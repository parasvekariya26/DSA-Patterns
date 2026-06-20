#include <iostream>
#include <vector>
#include <stack>
#include <map>

using namespace std;

// =====================================================
// INPUT FUNCTION
// =====================================================
vector<int> inputArray() {
    int n;
    cout << "Enter Size : ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter Elements : ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    return arr;
}

// =====================================================
// OUTPUT FUNCTION
// =====================================================
void printArray(const vector<int>& arr) {
    cout << "[ ";
    for (int x : arr)
        cout << x << " ";
    cout << "]" << endl;
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
// 84. LARGEST RECTANGLE IN HISTOGRAM
// =====================================================
int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    vector<int> NSE(n, n);
    vector<int> PSE(n, -1);
    stack<int> st;

    // Next Smaller Element
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && heights[i] <= heights[st.top()])
            st.pop();
        if (!st.empty())
            NSE[i] = st.top();
        st.push(i);
    }

    while (!st.empty()) st.pop();

    // Previous Smaller Element
    for (int i = 0; i < n; i++) {
        while (!st.empty() && heights[i] <= heights[st.top()])
            st.pop();
        if (!st.empty())
            PSE[i] = st.top();
        st.push(i);
    }

    int maxArea = 0;
    for (int i = 0; i < n; i++) {
        int width = NSE[i] - PSE[i] - 1;
        maxArea = max(maxArea, heights[i] * width);
    }
    return maxArea;
}

string countOfAtoms(string formula) {
    stack<pair<string,int>> st;
    int n = formula.length();
    for(int i=0;i<formula.length();i++){
        string atom = "";
        int repeat = 0;
        if(formula[i] == '(')
            st.push(make_pair("(",-1));
        else if(formula[i] >= 'A' && formula[i] <= 'Z'){
            atom += formula[i];
            while(i+1<n && formula[i+1]>='a' && formula[i] <='z'){
                i++;
                atom += formula[i];
            }
            while(i+1<n && formula[i+1] >= '0' && formula[i+1] <= '9'){
                i++;
                int number = formula[i]-'0';
                repeat = repeat*10 + number;
            }
            if(repeat == 0) repeat=1;
            st.push(make_pair(atom,repeat));
        }
        else if(formula[i] == ')'){
            stack<pair<string,int>> tempStack;
            repeat = 0;
            while(i+1<n && formula[i+1] >= '0' && formula[i+1] <= '9'){
                i++;
                int number = formula[i]-'0';
                repeat = repeat*10 + number;
            }
            if(repeat == 0) repeat=1;
            if(repeat>0){
                while(!st.empty() && st.top().first != "("){
                    tempStack.push(make_pair(st.top().first,st.top().second*repeat));
                    st.pop();
                }
                if(!st.empty() && st.top().first == "(") st.pop();
                while(!tempStack.empty()){
                    st.push(make_pair(tempStack.top().first,tempStack.top().second));
                    tempStack.pop();
                }
            }
        }
        else{
            //digits

        }
    }
    map<string,int> mapp;
    while(!st.empty()){
        mapp[st.top().first] += st.top().second;
        st.pop();
    }
    string ans = "";
    for(auto &[atom,freq] : mapp){
        ans += atom;
        if (freq > 1) ans += to_string(freq);
    }
    return ans;
}
// =====================================================
// MAIN
// =====================================================
int main() {

    vector<vector<int>> testCases = {
        {1,2,1},               // NGE -> [2,-1,2]
        {1,2,3,4,3},           // NGE -> [2,3,4,-1,4]
        {2,4},                 // Histogram -> 4
        {2,1,5,6,2,3},         // Histogram -> 10
        {2,1,2},               // Histogram -> 3
        {6,2,5,4,5,1,6},       // Histogram -> 12
        {1}                    // Histogram -> 1 
    };

    // Choose any test case
    vector<int> arr = testCases[0];

    // For manual input
    // vector<int> arr = inputArray();

    cout << "Input  : ";
    printArray(arr);

    // ==============================
    // Uncomment ONE problem at a time
    // ==============================

    // -------- 503. Next Greater Element II --------
    // vector<int> nge = nextGreaterElement(arr);
    // cout << "NGE Output : ";
    // printArray(nge);

    //-------- 84. Largest Rectangle --------
    // cout << "Largest Rectangle : "
    //      << largestRectangleArea(arr) << endl;
    
    countOfAtoms("K4(ON(SO3)2)2");
    // countOfAtoms("(Cn100)");

    return 0;
}