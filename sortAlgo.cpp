#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
void _merge(vector<int>& nums, int lsta, int lend, int rsta, int rend) {
    vector<int> tmps;
    int l = lsta, r = rsta;
    while (l <= lend && r <= rend) {
        if (nums[l] <= nums[r]) {
            tmps.push_back(nums[l]);
            ++l;
        } else {
            tmps.push_back(nums[r]);
            ++r;
        }
    }
    while (l <= lend) {
        tmps.push_back(nums[l]);
        ++l;
    }
    while (r <= rend) {
        tmps.push_back(nums[r]);
        ++r;
    }
    for (auto i : tmps) {
        nums[lsta++] = i;
    }
}
void _mergeSort(vector<int>& nums, int l, int r) {
    if (r - l < 1) return;
    int mid = (r + l) / 2;
    _mergeSort(nums, l, mid);
    _mergeSort(nums, mid + 1, r);
    _merge(nums, l, mid, mid + 1, r);
}
void MergeSort(vector<int>& nums) {
    int l = 0, r = nums.size() - 1;
    _mergeSort(nums, l, r);
}

void _quicksort(vector<int>& nums,int l ,int r){
    if(r - l < 2)
        return;
    int k = l+1, mi = l;
    int pivot = nums[l]; //初始选择最左边的值为锚点
    while(k < r){
        if(pivot > nums[k]){
            ++mi;
            swap(nums[mi],nums[k]);
        }
        ++k;
    }
    swap(nums[l],nums[mi]);
    _quicksort(nums,l,mi);
    _quicksort(nums,mi+1,r);
}
void QuickSort(vector<int>& nums){
    _quicksort(nums, 0, nums.size());
}

int main() {
    vector<int> nums{2, 3, 1, 2, 4, 6, 5};
    QuickSort(nums);
    for (auto i : nums) {
        std::cout << i << ",";
    }
    cout<<endl;
    system("pause");
    return 0;
}