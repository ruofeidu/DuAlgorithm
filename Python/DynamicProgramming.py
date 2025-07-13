import math


# Linear Double-ended DP with Transformation
def getStackCost(N, R, A, B) -> int:
  if N == 0:
    return 0

  T = [R[i] - i for i in range(N)]

  # At most N target values for each disc to change to.
  targets = set(T)

  # Add boundary values (1, 2, 3, .. N)
  for i in range(N):
    targets.add(1 - i)

  V = sorted(list(targets))
  k = len(V)

  def cost(initial_t, final_s):
    if final_s > initial_t:
      return A * (final_s - initial_t)
    else:
      return B * (initial_t - final_s)

  # dp[j] := min cost for the first disc with
  # for i = 0:
  dp = [math.inf] * k

  # S[0] = V[j]
  for j in range(k):
    s_val = V[j]
    if s_val >= 1:
      dp[j] = cost(T[0], s_val)

  # DP iterations for the rest of the discs (i = 1 to N-1).
  for i in range(1, N):
    # Calculate prefix minimums of the previous DP row for efficient transition.
    min_prev_dp = [math.inf] * k
    current_min = math.inf
    for j in range(k):
      current_min = min(current_min, dp[j])
      min_prev_dp[j] = current_min

    next_dp = [math.inf] * k

    # Constraint for the current disc: R'_i = S'_i + i >= 1 => S'_i >= 1 - i.
    lower_bound = 1 - i

    for j in range(k):
      s_val = V[j]
      if s_val >= lower_bound:
        # Cost for current disc + min cost for a valid previous state.
        cost_i = cost(T[i], s_val)
        prev_min_cost = min_prev_dp[j]

        if prev_min_cost != math.inf:
          next_dp[j] = cost_i + prev_min_cost

      # Update dp for the next iteration.
    dp = next_dp

  # The result is the minimum cost in the final DP row.
  min_total_cost = min(dp) if dp else 0

  return int(min_total_cost)


print(getStackCost(4, [100, 100, 1, 1], 2, 1))
print(getStackCost(6, [6, 5, 2, 4, 4, 7], 1, 1))
