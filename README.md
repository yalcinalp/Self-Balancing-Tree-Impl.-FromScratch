# TreeMap-via-Scapegoat-Trees
TreeMap Implementation via Scapegoat Trees

# Scapegoat Tree

* A Scapegoat Tree is a <ins> self-balancing binary </ins> search tree
  
* It provides worst-case O(log n) lookup time (with n as the number of nodes) and O(log n) amortized insertion and deletion time
  
* Instead of the small incremental rebalancing operations used by most balanced tree algorithms, scapegoat trees rarely but expensively choose a “scapegoat” and completely rebuild the subtree rooted at the scapegoat when the tree becomes unbalanced

* Thus, scapegoat trees have O(n) worst-case update performance  

