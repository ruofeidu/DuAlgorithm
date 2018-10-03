# 167. Two Sum II - Input array is sorted
# Linear scanning O(n)
def twoSum(self, numbers, target):
	"""
	:type numbers: List[int]
	:type target: int
	:rtype: List[int]
	"""
	l, r = 0, len(numbers) - 1
	while l < r:
		s = numbers[l] + numbers[r]
		if s > target:
			r -= 1
		elif s < target:
			l += 1
		else:
			return [l + 1, r + 1]
	return None