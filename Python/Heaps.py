import heapq
import math
import sys

# Python's default heap is a min-heap.
# To simulate a max-heap for integers, store negative values.
# max_heap = [] # Example: heapq.heappush(max_heap, -value)

# For pairs, to make a max-heap based on the first element of the pair:
# max_pair_heap = [] # Example: heapq.heappush(max_pair_heap, (-key, value))


# Min-heap for integers (default heapq behavior):
# min_heap = [] # Example: heapq.heappush(min_heap, value)
class Point:
  """
  Represents a 2D point with x and y coordinates.
  """

  def __init__(self, x: int, y: int):
    self._x = x
    self._y = y

  def get_x(self) -> int:
    return self._x

  def get_y(self) -> int:
    return self._y

  # For custom objects in a min-heap, you need to define __lt__ (less than).
  # If we want a min-heap based on x, then p1 < p2 if p1.x < p2.x.
  # If we want a max-heap based on x, then p1 < p2 if p1.x > p2.x (inverted logic).
  # The C++ `myComparator` makes `pq` a min-heap based on `p1.getX() > p2.getX()`,
  # which means it's a min-heap on x (smallest x at top).
  def __lt__(self, other):
    # This makes it a min-heap based on x coordinate.
    # Equivalent to C++ `myComparator` returning `p1.getX() > p2.getX()`
    # for a min-heap (smallest x at top).
    return self._x < other._x

  def __repr__(self):
    return f"Point(x={self._x}, y={self._y})"


# Example usage for custom objects in a heap:
# pq = [] # heapq.heappush(pq, Point(5, 10))


# For strings, default comparison is lexicographical (ascending).
# ascend = [] # heapq.heappush(ascend, "apple") -> min-heap
# To get a max-heap for strings, you can use a wrapper or store tuples like (-len(s), s)
# or simply sort the list and take the last element if it's a one-off.
# descend = [] # To simulate max-heap for strings, you'd push (-len(s), s) or a custom object.
# A more direct way to get a max-heap for strings is to use a custom class with __lt__
# that inverts the comparison.
class DescendingString:

  def __init__(self, s: str):
    self.s = s

  def __lt__(self, other):
    return self.s > other.s  # Invert comparison for max-heap behavior

  def __repr__(self):
    return f"DescendingString('{self.s}')"

  def __str__(self):
    return self.s


# --- Equivalent of C++ `namespace HeapAlgos` ---


class HeapAlgos:
  """
  Collection of algorithms demonstrating heap usage.
  """

  def nthSuperUglyNumber(self, n: int, primes: List[int]) -> int:
    """
    313. Super Ugly Number
    Super ugly numbers are positive numbers whose all prime factors are in
    the given prime list. Find the nth super ugly number.
    This is a corrected and more idiomatic Python version of the heap-based C++ solution.
    """
    uglies = [1]
    # (next_ugly_number, prime_factor, index_in_uglies)
    min_heap = [(p, p, 1) for p in primes]

    while len(uglies) < n:
      next_ugly, prime, index = heapq.heappop(min_heap)

      if next_ugly > uglies[-1]:
        uglies.append(next_ugly)

      # Add the next multiple of the same prime to the heap
      new_next_ugly = prime * uglies[index]
      heapq.heappush(min_heap, (new_next_ugly, prime, index + 1))

    return uglies[-1]

  def min_cost_to_hire_workers(self, quality: list[int], wage: list[int],
                               k: int) -> float:
    """
    857. Minimum Cost to Hire K Workers
    Calculates the least amount of money needed to form a paid group
    of K workers satisfying the given conditions.

    Time Complexity: O(N log N) due to sorting, plus O(N log K) for heap operations.
                      Overall O(N log N).
    Space Complexity: O(N) for storing workers, O(K) for the heap.

    Args:
        quality: A list of integers representing the quality of each worker.
        wage: A list of integers representing the minimum wage expectation of each worker.
        k: The number of workers to hire.

    Returns:
        The least amount of money needed.
    """
    num_workers = len(quality)
    workers = []  # List of (wage_to_quality_ratio, quality) tuples

    for i in range(num_workers):
      # Calculate the ratio (wage / quality) for each worker.
      # This ratio determines the minimum "rate" for the group.
      workers.append((wage[i] / quality[i], quality[i]))

    # Sort workers by their wage-to-quality ratio in ascending order.
    # This is crucial because if we pick a worker with ratio R, all other
    # workers in the group must be paid at least R * their quality.
    workers.sort()

    min_total_cost = float('inf')
    current_quality_sum = 0.0
    # A max-heap to store the 'k' largest qualities encountered so far.
    # We store negative qualities to simulate a max-heap with heapq.
    max_quality_heap = []

    for ratio, q in workers:
      current_quality_sum += q
      heapq.heappush(max_quality_heap,
                     -q)  # Push negative quality for max-heap behavior

      # If the heap size exceeds K, remove the worker with the largest quality
      # (which is the smallest negative value in the min-heap).
      if len(max_quality_heap) > k:
        current_quality_sum += heapq.heappop(
            max_quality_heap)  # Add back the popped negative value
        # which is equivalent to subtracting its positive value
      # Once we have exactly K workers in the heap, calculate the cost.
      # The cost is (sum of qualities in the group) * (current worker's ratio).
      # This ratio is the minimum rate required for all workers in the group.
      if len(max_quality_heap) == k:
        min_total_cost = min(min_total_cost, current_quality_sum * ratio)

    return min_total_cost

  class Interval:
    """Helper class for Meeting Rooms II problem."""

    def __init__(self, start: int, end: int):
      self.start = start
      self.end = end

    def __repr__(self):
      return f"Interval({self.start}, {self.end})"

  def min_meeting_rooms(self, intervals: list['Interval']) -> int:
    """
    252. Meeting Rooms II (similar to 253. Meeting Rooms II)
    Finds the minimum number of conference rooms required.

    Time Complexity: O(N log N) due to sorting and heap operations.
    Space Complexity: O(N) for sorting (if not in-place) and O(N) for the heap
                      in the worst case (all meetings overlapping).

    Args:
        intervals: A list of Interval objects, each with a start and end time.

    Returns:
        The minimum number of meeting rooms needed.
    """
    if not intervals:
      return 0

    # Sort intervals by their start times.
    intervals.sort(key=lambda x: x.start)

    # Min-heap to store the end times of meetings currently in progress.
    # The top of the heap will always be the earliest ending meeting.
    # This is a min-heap, so we store positive end times directly.
    meeting_rooms = []  # This list will be treated as a min-heap

    # Add the end time of the first meeting to the heap.
    heapq.heappush(meeting_rooms, intervals[0].end)

    # Iterate through the rest of the intervals.
    for i in range(1, len(intervals)):
      current_meeting = intervals[i]

      # If the current meeting's start time is greater than or equal to
      # the earliest ending meeting's end time (heap's top),
      # it means we can reuse that room. So, pop that meeting.
      if meeting_rooms and meeting_rooms[0] <= current_meeting.start:
        heapq.heappop(meeting_rooms)

      # Push the current meeting's end time into the heap.
      # This either uses a new room or reuses one.
      heapq.heappush(meeting_rooms, current_meeting.end)

    # The size of the heap at the end represents the maximum number of
    # concurrent meetings, which is the minimum number of rooms required.
    return len(meeting_rooms)

  def find_kth_largest(self, nums: list[int], k: int) -> int:
    """
    215. Kth Largest Element in an Array
    Finds the Kth largest element in an unsorted array.

    Time Complexity: O(N log K), where N is the number of elements in nums.
                      Each push/pop operation on a heap of size K takes O(log K).
    Space Complexity: O(K) for the heap.

    Args:
        nums: A list of integers.
        k: The desired rank (e.g., 1st largest, 2nd largest, etc.).

    Returns:
        The Kth largest element. Returns -1 if nums is empty or k is invalid.
    """
    if not nums or k <= 0:
      return -1

    # Use a min-heap of size K.
    # The heap will always contain the K largest elements encountered so far.
    # The smallest element in this min-heap (at the top) will be the Kth largest.
    min_heap_k = []

    for num in nums:
      heapq.heappush(min_heap_k, num)
      # If the heap size exceeds K, remove the smallest element.
      # This ensures the heap always holds the K largest elements.
      if len(min_heap_k) > k:
        heapq.heappop(min_heap_k)

    # After processing all numbers, the top of the min-heap is the Kth largest element.
    return min_heap_k[0]

  class MedianFinder:
    """
    295. Find Median from Data Stream
    Data structure to find the median of a dynamically growing data stream.
    Uses two heaps:
    - `max_heap`: Stores the smaller half of the numbers (as negative values to simulate max-heap).
    - `min_heap`: Stores the larger half of the numbers.
    Ensures `len(max_heap)` is either equal to `len(min_heap)` or `len(min_heap) + 1`.
    """

    def __init__(self):
      # max_heap stores the smaller half of numbers.
      # We store negative values to simulate a max-heap using heapq.
      self.max_heap = []  # Represents the "left" half, elements <= median

      # min_heap stores the larger half of numbers.
      # Stores positive values directly.
      self.min_heap = []  # Represents the "right" half, elements >= median

    def add_num(self, num: int) -> None:
      """
      Adds a number into the data structure.
      Time Complexity: O(log N)
      """
      # Rule 1: Always add to max_heap first (smaller half).
      heapq.heappush(self.max_heap, -num)

      # Rule 2: Transfer the largest element from max_heap to min_heap.
      # This ensures that max_heap's top is always <= min_heap's top.
      heapq.heappush(self.min_heap, -heapq.heappop(self.max_heap))

      # Rule 3: Balance the heaps.
      # If max_heap becomes smaller than min_heap, move the smallest
      # element from min_heap back to max_heap.
      # This maintains the property that max_heap.size() is either
      # equal to or one greater than min_heap.size().
      if len(self.max_heap) < len(self.min_heap):
        heapq.heappush(self.max_heap, -heapq.heappop(self.min_heap))

    def find_median(self) -> float:
      """
      Returns the median of all numbers added so far.
      Time Complexity: O(1)
      """
      # If max_heap has more elements, it means there's an odd number of elements,
      # and the median is the largest element in the smaller half (top of max_heap).
      if len(self.max_heap) > len(self.min_heap):
        return -self.max_heap[0]  # Remember to negate for actual value

      # If heaps have equal size, there's an even number of elements.
      # The median is the average of the largest element in the smaller half
      # and the smallest element in the larger half.
      else:
        return (-self.max_heap[0] + self.min_heap[0]) / 2.0


# --- Example Usage ---
if __name__ == "__main__":
  algos = HeapAlgos()

  print("--- 857. Minimum Cost to Hire K Workers ---")
  quality1 = [10, 20, 5]
  wage1 = [70, 50, 30]
  k1 = 2
  # Ratios: (70/10=7), (50/20=2.5), (30/5=6)
  # Sorted workers: (2.5, 20), (6, 5), (7, 10)
  # K=2:
  # 1. Add (2.5, 20): sum=20, heap=[-20]. size=1.
  # 2. Add (6, 5): sum=20+5=25, heap=[-20, -5]. size=2. Cost = 25 * 6 = 150. min_cost = 150.
  # 3. Add (7, 10): sum=25+10=35, heap=[-20, -10, -5]. size=3. Pop -20 (quality 20). sum=35-20=15. heap=[-10, -5]. size=2.
  #    Cost = 15 * 7 = 105. min_cost = min(150, 105) = 105.
  print(
      f"Min cost to hire workers 1: {algos.min_cost_to_hire_workers(quality1, wage1, k1)}"
  )  # Expected: 105.0

  quality2 = [3, 1, 10, 10, 1]
  wage2 = [4, 8, 2, 2, 7]
  k2 = 3
  print(
      f"Min cost to hire workers 2: {algos.min_cost_to_hire_workers(quality2, wage2, k2)}"
  )  # Expected: 30.00000

  print("\n--- Meeting Rooms II ---")
  intervals1 = [
      algos.Interval(0, 30),
      algos.Interval(5, 10),
      algos.Interval(15, 20)
  ]
  print(f"Min meeting rooms 1: {algos.min_meeting_rooms(intervals1)}"
       )  # Expected: 2

  intervals2 = [algos.Interval(7, 10), algos.Interval(2, 4)]
  print(f"Min meeting rooms 2: {algos.min_meeting_rooms(intervals2)}"
       )  # Expected: 1

  intervals3 = [
      algos.Interval(1, 5),
      algos.Interval(2, 6),
      algos.Interval(3, 7),
      algos.Interval(4, 8)
  ]
  print(f"Min meeting rooms 3: {algos.min_meeting_rooms(intervals3)}"
       )  # Expected: 4

  print("\n--- 215. Kth Largest Element in an Array ---")
  nums1 = [3, 2, 1, 5, 6, 4]
  k_val1 = 2
  print(
      f"Kth largest in {nums1} (k={k_val1}): {algos.find_kth_largest(nums1, k_val1)}"
  )  # Expected: 5

  nums2 = [3, 2, 3, 1, 2, 4, 5, 5, 6]
  k_val2 = 4
  print(
      f"Kth largest in {nums2} (k={k_val2}): {algos.find_kth_largest(nums2, k_val2)}"
  )  # Expected: 4

  print("\n--- 295. Find Median from Data Stream ---")
  median_finder = HeapAlgos.MedianFinder()
  median_finder.add_num(1)
  median_finder.add_num(2)
  print(f"Median after 1, 2: {median_finder.find_median()}")  # Expected: 1.5
  median_finder.add_num(3)
  print(f"Median after 1, 2, 3: {median_finder.find_median()}")  # Expected: 2.0
  median_finder.add_num(4)
  print(f"Median after 1, 2, 3, 4: {median_finder.find_median()}"
       )  # Expected: 2.5
  median_finder.add_num(5)
  print(f"Median after 1, 2, 3, 4, 5: {median_finder.find_median()}"
       )  # Expected: 3.0

  median_finder_empty = HeapAlgos.MedianFinder()
  # Test with a different sequence
  median_finder_empty.add_num(-1)
  print(
      f"Median after -1: {median_finder_empty.find_median()}")  # Expected: -1.0
  median_finder_empty.add_num(-2)
  print(f"Median after -1, -2: {median_finder_empty.find_median()}"
       )  # Expected: -1.5
  median_finder_empty.add_num(-3)
  print(f"Median after -1, -2, -3: {median_finder_empty.find_median()}"
       )  # Expected: -2.0
