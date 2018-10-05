# 153. Find Minimum in Rotated Sorted Array
# Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
# Find the minimum element. You may assume no duplicate exists in the array.
def findMin(self, nums):
	"""
	:type nums: List[int]
	:rtype: int
	"""
	# 4 5 6 7 0 1 2
	# 5 6 7 0 1 2 4
	# 6 7 0 1 2 4 5
	# 2 1
	l, r = 0, len(nums) - 1
	while l <= r:
		p = (l+r) >> 1
		if nums[p] > nums[r]:
			l = p + 1
		elif nums[p] < nums[p - 1]:
			return nums[p]
		else:
			r = p - 1
	return nums[p]

	
# 154. Find Minimum in Rotated Sorted Array II
# The array may contain duplicates.
def bsearch(self, nums, l, r):
	while l <= r:
		p = (l+r) >> 1
		if nums[p] > nums[r]:
			l = p + 1
		elif nums[p] < nums[p - 1]:
			return nums[p]
		elif nums[p] < nums[r]:
			r = p - 1
		else:
			return min(min(self.bsearch(nums, l, p-1), self.bsearch(nums, p+1, r)), nums[p])
	return (1<<32)-1
		

def findMin(self, nums):
	"""
	:type nums: List[int]
	:rtype: int
	"""
	return self.bsearch(nums, 0, len(nums) - 1)
    
    
# 209. Minimum Size Subarray Sum
# Given an array of n positive integers and a positive integer s, find the minimal length of a contiguous subarray of which the sum ≥ s. If there isn't one, return 0 instead.
def minSubArrayLen(self, s, nums):
    """
    :type s: int
    :type nums: List[int]
    :rtype: int
    """
    l, r, cur = 0, 0, 0
    ans = len(nums) + 1
    
    while r < len(nums):
        cur += nums[r]    
        if cur >= s:
            # print(l, r, cur)
            ans = min(ans, r - l + 1)
            cur -= nums[l]
            l += 1
            if r < l:
                r += 1
            cur -= nums[r]
        else:
            r += 1
            
    return 0 if ans == len(nums) + 1 else ans