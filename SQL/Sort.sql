# 176. Second Highest Salary
SELECT (SELECT Salary FROM Employee GROUP BY Salary ORDER BY Salary DESC LIMIT 1 OFFSET 1) SecondHighestSalary;

# 177. Nth Highest Salary
# Time:  O(n^2)
# Space: O(n)
#
# Write a SQL query to get the nth highest salary from the Employee table.
#
# +----+--------+
# | Id | Salary |
# +----+--------+
# | 1  | 100    |
# | 2  | 200    |
# | 3  | 300    |
# +----+--------+
# For example, given the above Employee table, the nth highest salary where n = 2 is 200. If there is no nth highest salary, then the query should return null.
#

CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
  RETURN (
      SELECT MAX(Salary) FROM Employee E1
      WHERE (N-1) = (SELECT COUNT(DISTINCT(E2.Salary)) FROM Employee E2 
      WHERE E2.Salary > E1.Salary)
  );
END

# 178. Rank Scores
# Time:  O(n^2)
# Space: O(n)
#
# Write a SQL query to rank scores. If there is a tie between two scores, both should have the same ranking. Note that after a tie, the next ranking number should be the next consecutive integer value. In other words, there should be no "holes" between ranks.
#
# +----+-------+
# | Id | Score |
# +----+-------+
# | 1  | 3.50  |
# | 2  | 3.65  |
# | 3  | 4.00  |
# | 4  | 3.85  |
# | 5  | 4.00  |
# | 6  | 3.65  |
# +----+-------+
# For example, given the above Scores table, your query should generate the following report (order by highest score):
#
#    +-------+------+
#    | Score | Rank |
#    +-------+------+
#    | 4.00  | 1    |
#    | 4.00  | 1    |
#    | 3.85  | 2    |
#    | 3.65  | 3    |
#    | 3.65  | 3    |
#    | 3.50  | 4    |
#    +-------+------+
#

# Write your MySQL query statement below
SELECT Ranks.Score, Ranks.Rank FROM Scores LEFT JOIN 
       ( SELECT r.Score, @curRow := @curRow + 1  Rank 
            FROM (SELECT DISTINCT(Score), (SELECT @curRow := 0) 
                      FROM Scores ORDER by Score DESC) r
       ) Ranks 
       ON Scores.Score = Ranks.Score
       ORDER by Score DESC


# Time:  O(n^3)
# Space: O(n)
# Write your MySQL query statement below
# SELECT Score,  (SELECT COUNT(DISTINCT(Score)) FROM  Scores b WHERE b.Score > a.Score) + 1 AS Rank
#       FROM Scores a
#       ORDER by Score DESC