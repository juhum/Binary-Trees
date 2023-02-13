# Binary-Trees
Algorithms and complexity project 2

Task 1 "An Introduction to Applied Dendrology", the basic task for mark 3-4

Implement a binary tree based container for e.g. integers. Draw a large set of random keys. Empirically compare the cumulative running times for inserting the keys into
a) a binary tree, in the original random order
b) a binary tree, in the best-case order of, say, building consequitive levels of the tree downwards. Root, its children, grandchildren ... (requires rearrangeing the keys beforehand)
	Explanation: the goal is to obtain a perfectly balanced tree, thus no node can be inserted before its parent. You may assume that you have n = 2^m - 1 keys.
c) a library solution, say std::set.

For each of the containers build check what is the total time of finding all of the keys from the previously generated random set.


Task 2 "Grow your own arboretum" additional task for mark 4-5. 

Include in the Task 1 your own implementation of a self-balancing tree, e.g. AVL tree.




Your REPORT should contain a concise description of you algorithms. Describe what you have done in the task and how. State clearly what are theoretical running times and what should be expected. What are your findings? OBLIGATORY graph should clearly support your conclusions.
