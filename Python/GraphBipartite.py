def isBipartite(self, graph):
    """
    :type graph: List[List[int]]
    :rtype: bool
    """

    col = {}
    n = len(graph)
    for node in range(n):
        if node in col:
            continue
        stack = [node]
        col[node] = 0
        while stack:
            u = stack.pop()
            for v in graph[u]:
                if v not in col:
                    stack.append(v)
                    col[v] = col[u] ^ 1
                elif col[v] == col[u]:
                    return False
    return True