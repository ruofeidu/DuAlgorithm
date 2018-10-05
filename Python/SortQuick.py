# 215. Kth Largest Element in an Array
# Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

def kSort(self, a, l, r, k):
    i, j, p = l, r, a[(l + r) >> 1]
    while i < j:
        while a[i] < p:
            i += 1
        while a[j] > p:
            j -= 1
        if i <= j:
            a[i], a[j] = a[j], a[i]
            i += 1
            j -= 1
    if l < j and k <= j:
        self.kSort(a, l, j, k)
    if i < r and k >= i:
        self.kSort(a, i, r, k)

def findKthLargest(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: int
    """
    self.kSort(nums, 0, len(nums) - 1, len(nums) - k)
    return nums[len(nums) - k]