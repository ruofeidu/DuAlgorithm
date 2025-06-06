# 238. Product of Array Except Self [M]
# Given an array nums of n integers where n > 1,  return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].
def productExceptSelf(self, nums):
  """
	:type nums: List[int]
	:rtype: List[int]
	"""
  if not nums:
    return []
  n = len(nums)
  left, right = [1] * n, 1
  for i in range(1, n):
    left[i] = left[i - 1] * nums[i - 1]
  for i in range(n - 2, -1, -1):
    right *= nums[i + 1]
    left[i] *= right
  return left
