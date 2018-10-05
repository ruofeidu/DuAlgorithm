# 210. Course Schedule II
def findOrder(self, numCourses, prerequisites):
    """
    :type numCourses: int
    :type prerequisites: List[List[int]]
    :rtype: List[int]
    """
    n = numCourses
    g = [[] for _ in range(n)]
    f = [[] for _ in range(n)]
    vdn = 0
    ans = []
    q = []
    
    for i, j in prerequisites:
        g[i].append(j)
        f[j].append(i)
    
    for i in range(n):
        if len(g[i]) == 0:
            q.append(i)
            
    while len(q) > 0:
        x = q.pop(0)
        ans.append(x)
        for i in f[x]:
            g[i].remove(x)
            if len(g[i]) == 0:
                q.append(i)

    return ans if len(ans) == n else []
    