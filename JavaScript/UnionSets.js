// Union Find Set with Compressed Path in O(alpha)
UnionSet = function(n) {
  this.roots = Array(n);
  this.n = n;
  for (let i = 0; i < n; ++i) {
    this.roots[i] = i;
  };
  this.find = function(id) {
    while (id != this.roots[id]) {
      this.roots[id] = this.roots[this.roots[id]];
      id = this.roots[id];
    }
    return id;
  };

  // set a to b
  this.setParent = function(a, b) {
    this.roots[a] = this.find(b);
  };
};
