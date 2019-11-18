Name: Sharanya Sudhakar
Date: 4/16/2018
Assignment: Treap
--------------------------------------------------------------------------
Implementing a BST with iterator and a priority value
--------------------------------------------------------------------------

BST.h and BST.cpp => runBst => bstOutput.txt

These files contain the main Binary Search implemented with only the 
insert functionality implemented by the operatore[].There is an iterator
to this class which iterates through the tree without recursion using stack.

Treap.h Treap.cpp => runtreap => treapOutput.txt

This is an entire new file that was extended from the bst.
The balance of the tree based on priority is implemented at the time 
the node is added. In addition executing a bst the treap also prints
the tree in a sideways display with the root in the middle and the 
leftsubtree below while the right subtree is above.

original.cpp => original => exout.txt

The c++ file for output comparison.
Provided as part of the question.
--------------------------------------------------------------------------
SORTED AND UNSORTED OUTPUT

For efficiency and time, 3 files each have been tested for unoptimzed 
and optimzed results using bst and unoptimized treap.
--------------------------------------------------------------------------

Reference:
Class work - Morris Bernstein
Dump routine - Prof. Zander

Intoduction to Algorithms - Cormen et al
Programming principles Bjarne Stroustrup