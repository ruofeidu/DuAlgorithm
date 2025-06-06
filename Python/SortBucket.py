# 164. Maximum Gap [H]
# Given an unsorted array, find the maximum difference between the successive elements in its sorted form.
# Return 0 if the array contains less than 2 elements.
def maximumGap(self, nums):
  """
	:type nums: List[int]
	:rtype: int
	"""
  N = len(nums)
  if N < 2:
    return 0
  max_val, min_val = max(nums), min(nums)
  gap = max(1, (max_val - min_val) / (N - 1))

  # the size of the buckets equals to num of gaps + 1
  B = int((max_val - min_val) / gap + 1)
  INF = (1 << 32) - 1
  bucket_min = [INF for _ in range(B)]
  bucket_max = [-1 for _ in range(B)]

  # Find the bucket where each num should be put
  for x in nums:
    i = int((x - min_val) / gap)
    bucket_min[i] = min(bucket_min[i], x)
    bucket_max[i] = max(bucket_max[i], x)

  # Count each bucket gap between the first and the last bucket
  max_gap, pre_bucket_max = 0, min_val
  for i in range(B):
    if bucket_min[i] == INF and bucket_max[i] == -1:
      continue
    max_gap = max(max_gap, bucket_min[i] - pre_bucket_max)
    pre_bucket_max = bucket_max[i]
  # Count the last bucket
  max_gap = max(max_gap, max_val - pre_bucket_max)
  return max_gap
