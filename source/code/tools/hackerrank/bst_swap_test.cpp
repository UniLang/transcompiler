#include "code/utilities/types/tree/tree_traversal.hpp"
#include "code/tools/hackerrank/bst_swap_solution_sliding_window_two_ptrs.hpp"
#include "code/tools/hackerrank/bst_swap_solution_in_out.hpp"
#include "code/tools/hackerrank/bst_swap_solution_geeks_five_ptrs.hpp"
#include "code/tools/hackerrank/bst_swap_solution_geeks_four_ptrs.hpp"
#include "code/tools/hackerrank/bst_swap_solution_geeks_three_ptrs.hpp"
#include "code/tools/hackerrank/bst_swap_algorithm.hpp"
#include "code/tools/hackerrank/bst_swap_solution.hpp"
#include "code/utilities/data_structures/tree/binary_nodes.hpp"
#include "gtest/gtest.h"
#include <algorithm>
#include <vector>
#include <utility>

void wrong_by_only_two_nodes(std::vector<int> nodes){
  auto sorted = nodes;
  std::sort(sorted.begin(),sorted.end());
  
  int discrepency_count = 0;
  for (size_t i = 0; i < sorted.size(); ++i){
    if (nodes[i] != sorted[i]){
      ++discrepency_count;
    }
  }
  EXPECT_EQ(discrepency_count,2);
}

void check_algorithm_fixes_tree(BinaryNode<int> & root, Bst_Swap_Algorithm const& algo){
  
  //the tree SHOULD NOT be sorted before we start
  auto before = Tree_Traversal::inorder_traversal_as_list(&root);
  EXPECT_FALSE(std::is_sorted(before.begin(),before.end()));
  
  //in fact, it should only be wrong by two nodes
  //we don't accept trees that are already fixed or broken beyond two nodes out of place
  wrong_by_only_two_nodes(before);
  
  //Time to fix the tree, and confirm that we actually fixed it.
  Bst_Swap_Solution::fix_bst(&root,algo);
  auto after = Tree_Traversal::inorder_traversal_as_list(&root);
  EXPECT_TRUE(std::is_sorted(after.begin(),after.end()));
}

void check_every_swap_combination(BinaryNode<int> & root, Bst_Swap_Algorithm const& algo){
    auto ordered = Tree_Traversal::inorder_traversal_as_node_list(&root);
    for (size_t i = 0; i < ordered.size(); ++i){
      for (size_t j = 0; j < ordered.size(); ++j){
        if (ordered[i]->val != ordered[j]->val){
          std::swap(ordered[i]->val,ordered[j]->val);
          //std::cout << "swapped " << ordered[i]->val << " " << ordered[j]->val << std::endl;
          check_algorithm_fixes_tree(root,algo);
        }
      }
    }
}



// a linked list is a special kind of tree in which there exists only 1 childless node.
// all other trees have 2 or more childless nodes.
// the hickey hijack requires that 1 pointer capture a childless node, in which the available child storage can be used to connect back to the root,
// then using the final child storage, connect to another childless node in order to gain two pointers of additional storage during later traversal.
// this transformation renders the original pointer the ability of two pointers indirectly, tags the both the childless nodes involved, and ensures
// the original pointer can get back to the root.  From this point, we perform a modified morris traversal in which we capture the first discrepancy,
// in the first pointers indirected storage.  Using the first pointer's indirected storage, the morris traversal is able to complete, with knowledge of the
// first node that needs swapped, and knowledge of how to return to the root.  At this point, we perform a modified reverse morris traversal choosing to forget
// how the first pointer could return to the root,  The second traversal will identify the second node, swap the values, and complete with lost knowledge of the root.
// as the tree is fixed, deriving the root can be performed by the first pointer.  Pointer A and B work together to repair the tree.


std::vector<Bst_Swap_Algorithm> algorithms_to_test(){
  std::vector<Bst_Swap_Algorithm> x;
  x.emplace_back(Bst_Swap_Algorithm::HACKERRANK_RECURSIVE_FIVE);
  x.emplace_back(Bst_Swap_Algorithm::HACKERRANK_RECURSIVE_FOUR);
  x.emplace_back(Bst_Swap_Algorithm::HACKERRANK_RECURSIVE_THREE);
  x.emplace_back(Bst_Swap_Algorithm::SLIDING_WINDOW_AND_PAIR);
  x.emplace_back(Bst_Swap_Algorithm::INORDER_OUTORDER_THREE);
  return x;
}

BinaryNodes<int> TwoNodesSwapped_NonAdjecent_Example1(){
  
  //     6 
  //    /  \ 
  //   10   2 
  //  /  \ /  \ 
  // 1   3 7  12 
  // 10 and 2 are swapped
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(6));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(10));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(3));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(7));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(12));
  x.nodes[0]->left = &*x.nodes[1];
  x.nodes[0]->right = &*x.nodes[2];
  x.nodes[0]->left->left = &*x.nodes[3];
  x.nodes[0]->left->right = &*x.nodes[4];
  x.nodes[0]->right->left = &*x.nodes[5];
  x.nodes[0]->right->right = &*x.nodes[6];
  return x;
}
BinaryNodes<int> TwoNodesSwapped_NonAdjecent_Example2(){
  
  //       10
  //      /  \
  //     5    8
  //    / \
  //   2   20
  // 20 and 8 are swapped
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(10));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(5));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(8));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(20));
  x.nodes[0]->left = &*x.nodes[1];
  x.nodes[0]->right = &*x.nodes[2];
  x.nodes[0]->left->left = &*x.nodes[3];
  x.nodes[0]->left->right = &*x.nodes[4];
  return x;
}
BinaryNodes<int> TwoNodesSwapped_NonAdjecent_Example3(){
  //        2
  //      /  \
  //     3    1
  // 3 and 1 are swapped
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(3));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
  x.nodes[0]->left = &*x.nodes[1];
  x.nodes[0]->right = &*x.nodes[2];
  return x;
}
BinaryNodes<int> TwoNodesSwapped_NonAdjecent_Example4(){
    //        2
    //      /  \
    //     1    3
    //    /      \
    //   4        0
    // 4 and 0 are swapped
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(3));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(4));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(0));
  x.nodes[0]->left = &*x.nodes[1];
  x.nodes[0]->right = &*x.nodes[2];
  x.nodes[0]->left->left = &*x.nodes[3];
  x.nodes[0]->right->right = &*x.nodes[4];
  return x;
}
BinaryNodes<int> TwoNodesSwapped_NonAdjecent_Example5(){
  //       4
  //      /  \
  //     3    5
  //    /      \
  //   2        6
  //  /          \
  // 7            1
  // 7 and 1 are swapped
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(4));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(3));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(5));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(6));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(7));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
  x.nodes[0]->left = &*x.nodes[1];
  x.nodes[0]->right = &*x.nodes[2];
  x.nodes[0]->left->left = &*x.nodes[3];
  x.nodes[0]->right->right = &*x.nodes[4];
  x.nodes[0]->left->left->left = &*x.nodes[5];
  x.nodes[0]->right->right->right = &*x.nodes[6];
  return x;
}
BinaryNodes<int> TwoNodesSwapped_NonAdjecent_Example6(){
  //       7
  //      /  \
  //     3    5
  //    /      \
  //   2        6
  //  /          \
  // 1            4
  // 7 and 4 are swapped
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(7));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(3));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(5));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(6));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(4));
  x.nodes[0]->left = &*x.nodes[1];
  x.nodes[0]->right = &*x.nodes[2];
  x.nodes[0]->left->left = &*x.nodes[3];
  x.nodes[0]->right->right = &*x.nodes[4];
  x.nodes[0]->left->left->left = &*x.nodes[5];
  x.nodes[0]->right->right->right = &*x.nodes[6];
  return x;
}
BinaryNodes<int> TwoNodesSwapped_NonAdjecent_Example7(){
  //     6 
  //    /  \ 
  //   2    10 
  //  /  \ /  \ 
  // 12   3 7  1 
  // 12 and 1 are swapped
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(6));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(10));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(12));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(3));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(7));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
  x.nodes[0]->left = &*x.nodes[1];
  x.nodes[0]->right = &*x.nodes[2];
  x.nodes[0]->left->left = &*x.nodes[3];
  x.nodes[0]->left->right = &*x.nodes[4];
  x.nodes[0]->right->left = &*x.nodes[5];
  x.nodes[0]->right->right = &*x.nodes[6];
  return x;
}
BinaryNodes<int> TwoNodesSwapped_Adjecent_Example1(){
  //       10
  //      /  \
  //     6    20
  //    / \
  //   2   5
  // 5 and 6 are swapped
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(10));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(6));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(20));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(5));
  x.nodes[0]->left = &*x.nodes[1];
  x.nodes[0]->right = &*x.nodes[2];
  x.nodes[0]->left->left = &*x.nodes[3];
  x.nodes[0]->left->right = &*x.nodes[4];
  return x;
}
BinaryNodes<int> TwoNodesSwapped_Adjecent_Example2(){
  //       10
  //      /  \
  //     4    20
  //    / \
  //   5   7
  // 4 and 5 are swapped
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(10));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(4));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(20));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(5));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(7));
  x.nodes[0]->left = &*x.nodes[1];
  x.nodes[0]->right = &*x.nodes[2];
  x.nodes[0]->left->left = &*x.nodes[3];
  x.nodes[0]->left->right = &*x.nodes[4];
  return x;
}
BinaryNodes<int> TwoNodesSwapped_Adjecent_Example3(){
  //        5
  //      /  \
  //     10    20
  //    / \
  //   4   7
  // 5 and 10 are swapped
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(5));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(10));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(20));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(4));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(7));
  x.nodes[0]->left = &*x.nodes[1];
  x.nodes[0]->right = &*x.nodes[2];
  x.nodes[0]->left->left = &*x.nodes[3];
  x.nodes[0]->left->right = &*x.nodes[4];
  return x;
}
BinaryNodes<int> TwoNodesSwapped_Adjecent_Example4(){
  
  //        1
  //      /  \
  //     2    3
  // 2 and 1 are swapped
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(3));
  x.nodes[0]->left = &*x.nodes[1];
  x.nodes[0]->right = &*x.nodes[2];
  return x;
}
BinaryNodes<int> TwoNodesSwapped_Adjecent_Example5(){
  
  //        1
  //      /  \
  //     2    3
  //    /
  //   0
  // 2 and 1 are swapped
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(3));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(0));
  x.nodes[0]->left = &*x.nodes[1];
  x.nodes[0]->right = &*x.nodes[2];
  x.nodes[0]->left->left = &*x.nodes[3];
  return x;
}
BinaryNodes<int> TwoNodesSwapped_Adjecent_Example6(){
  //        1
  //      /  \
  //     2    3
  //           \
  //            4
  // 2 and 1 are swapped
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(3));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(4));
  x.nodes[0]->left = &*x.nodes[1];
  x.nodes[0]->right = &*x.nodes[2];
  x.nodes[0]->right->right = &*x.nodes[3];
  return x;
}
BinaryNodes<int> TwoNodesSwapped_Adjecent_Example7(){
    //        1
    //      /  \
    //     2    3
    //   /       \
    //  0         4
    // 2 and 1 are swapped
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(3));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(0));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(4));
  x.nodes[0]->left = &*x.nodes[1];
  x.nodes[0]->right = &*x.nodes[2];
  x.nodes[0]->left->left = &*x.nodes[3];
  x.nodes[0]->right->right = &*x.nodes[4];
  return x;
}
BinaryNodes<int> TwoNodesSwapped_Adjecent_Example8(){
 //           20
 //         /
 //        19
 //      /
 //     18
 //    /
 //   5
 //  / \
 // 6   7
   
 //    6 and 5 are swapped
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(20));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(19));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(18));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(5));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(6));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(7));
  x.nodes[0]->left = &*x.nodes[1];
  x.nodes[0]->left->left = &*x.nodes[2];
  x.nodes[0]->left->left->left = &*x.nodes[3];
  x.nodes[0]->left->left->left->left = &*x.nodes[4];
  x.nodes[0]->left->left->left->right = &*x.nodes[5];
  return x;
}
BinaryNodes<int> TwoNodesSwapped_Adjecent_Example9(){
 //           20
 //         /
 //        19
 //      /
 //     18
 //    /
 //   7
 //  / \
 // 5   6
   
 //    7 and 6 are swapped
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(20));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(19));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(18));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(7));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(5));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(6));
  x.nodes[0]->left = &*x.nodes[1];
  x.nodes[0]->left->left = &*x.nodes[2];
  x.nodes[0]->left->left->left = &*x.nodes[3];
  x.nodes[0]->left->left->left->left = &*x.nodes[4];
  x.nodes[0]->left->left->left->right = &*x.nodes[5];
  return x;
}
BinaryNodes<int> TwoNodesSwapped_Adjecent_Example10(){
    //        3
    //      /  \
    //     1    2
    // 3 and 2 are swapped
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(3));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
  x.nodes[0]->left = &*x.nodes[1];
  x.nodes[0]->right = &*x.nodes[2];
  return x;
}
BinaryNodes<int> TwoNodesSwapped_Adjecent_Example11(){
  // 2
  //  \
  //   1
  //   1 and 2 are swapped
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
  x.nodes[0]->right = &*x.nodes[1];
  return x;
}
BinaryNodes<int> TwoNodesSwapped_Adjecent_Example12(){
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
  x.nodes[0]->left = &*x.nodes[1];
  return x;
}
BinaryNodes<int> Correct_Tree_Example1(){
     //     6 
     //    /  \ 
     //   2    10 
     //  /  \ /  \ 
     // 1   3 7  12 
    BinaryNodes<int> x;
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(6));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(10));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(3));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(7));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(12));
    x.nodes[0]->left = &*x.nodes[1];
    x.nodes[0]->right = &*x.nodes[2];
    x.nodes[0]->left->left = &*x.nodes[3];
    x.nodes[0]->left->right = &*x.nodes[4];
    x.nodes[0]->right->left = &*x.nodes[5];
    x.nodes[0]->right->right = &*x.nodes[6];
    return x;
}
BinaryNodes<int> Correct_Tree_Example2(){
    //    2
    //  /  \
    // 1    3
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(3));
  x.nodes[0]->left = &*x.nodes[1];
  x.nodes[0]->right = &*x.nodes[2];
  return x;
}
BinaryNodes<int> Correct_Tree_Example3(){
     //       2
     //     /  \
     //    1    3
     //  /       \
     // 0         4
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(3));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(0));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(4));
  x.nodes[0]->left = &*x.nodes[1];
  x.nodes[0]->right = &*x.nodes[2];
  x.nodes[0]->left->left = &*x.nodes[3];
  x.nodes[0]->right->right = &*x.nodes[4];
  return x;
}
BinaryNodes<int> Correct_Tree_Example4(){
  // 1-2-3-4-5-6-7-8-9-10
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(10));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(9));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(8));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(7));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(6));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(5));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(4));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(3));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
  x.nodes[0]->left = &*x.nodes[1];
  x.nodes[0]->left->left = &*x.nodes[2];
  x.nodes[0]->left->left->left = &*x.nodes[3];
  x.nodes[0]->left->left->left->left = &*x.nodes[4];
  x.nodes[0]->left->left->left->left->left = &*x.nodes[5];
  x.nodes[0]->left->left->left->left->left->left = &*x.nodes[6];
  x.nodes[0]->left->left->left->left->left->left->left = &*x.nodes[7];
  x.nodes[0]->left->left->left->left->left->left->left->left = &*x.nodes[8];
  x.nodes[0]->left->left->left->left->left->left->left->left->left = &*x.nodes[9];
  return x;
}
BinaryNodes<int> Correct_Tree_Example5(){
  // 1-2-3-4-5-6-7-8-9-10
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(3));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(4));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(5));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(6));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(7));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(8));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(9));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(10));
  x.nodes[0]->right = &*x.nodes[1];
  x.nodes[0]->right->right = &*x.nodes[2];
  x.nodes[0]->right->right->right = &*x.nodes[3];
  x.nodes[0]->right->right->right->right = &*x.nodes[4];
  x.nodes[0]->right->right->right->right->right = &*x.nodes[5];
  x.nodes[0]->right->right->right->right->right->right = &*x.nodes[6];
  x.nodes[0]->right->right->right->right->right->right->right = &*x.nodes[7];
  x.nodes[0]->right->right->right->right->right->right->right->right = &*x.nodes[8];
  x.nodes[0]->right->right->right->right->right->right->right->right->right = &*x.nodes[9];
  return x;
}
BinaryNodes<int> Correct_Tree_Example6(){
    //  2
    // /
    // 1
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
  x.nodes[0]->left = &*x.nodes[1];
  return x;
}
BinaryNodes<int> Correct_Tree_Example7(){
     // 1
     // \
     //  2
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
  x.nodes[0]->right = &*x.nodes[1];
  return x;
}
BinaryNodes<int> Correct_Tree_Example8(){
    //    2
    //  /  \
    // 1    3
    //       \
    //        5
    //       / \
    //      4   6
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(3));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(5));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(4));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(6));
  x.nodes[0]->left = &*x.nodes[1];
  x.nodes[0]->right = &*x.nodes[2];
  x.nodes[0]->right->right = &*x.nodes[3];
  x.nodes[0]->right->right->left = &*x.nodes[4];
  x.nodes[0]->right->right->right = &*x.nodes[5];
  return x;
}
BinaryNodes<int> Correct_Tree_Example9(){
      //       5
      //      / \
      //     4   6
      //    /
      //   2
      //  / \
      // 1   3
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(5));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(4));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(6));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(3));
  x.nodes[0]->left = &*x.nodes[1];
  x.nodes[0]->right = &*x.nodes[2];
  x.nodes[0]->left->left = &*x.nodes[3];
  x.nodes[0]->left->left->left = &*x.nodes[4];
  x.nodes[0]->left->left->right = &*x.nodes[5];
  return x;
}
BinaryNodes<int> Correct_Tree_Example10(){
  // 13
  // /
  // 11
  // \
  //  12
  //  /
  //  9
  //  \
  //   10
  BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(13));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(11));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(12));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(9));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(10));
  x.nodes[0]->left = &*x.nodes[1];
  x.nodes[0]->left->right = &*x.nodes[2];
  x.nodes[0]->left->right->left = &*x.nodes[3];
  x.nodes[0]->left->right->left->right = &*x.nodes[4];
  return x;
}
BinaryNodes<int> Correct_Tree_Example11(){
   // 1
   //  \
   //   6
   //  /
   // 3
   //  \
   //   5
   //   /
   //  4
   BinaryNodes<int> x;
   x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
   x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(6));
   x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(3));
   x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(5));
   x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(4));
    x.nodes[0]->right = &*x.nodes[1];
    x.nodes[0]->right->left = &*x.nodes[2];
    x.nodes[0]->right->left->right = &*x.nodes[3];
    x.nodes[0]->right->left->right->left = &*x.nodes[4];
   return x;
}
BinaryNodes<int> Correct_Tree_Example12(){
     //     6 
     //    /  \ 
     //   2    10 
     //  /  \ /   \ 
     // 1   3 7     12
     //      \  \   /
     //      4  8  11
   BinaryNodes<int> x;
   x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(6));
   x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
   x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(10));
   x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
   x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(3));
   x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(7));
   x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(12));
   x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(4));
   x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(8));
   x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(11));
    x.nodes[0]->left = &*x.nodes[1];
    x.nodes[0]->right = &*x.nodes[2];
    x.nodes[0]->left->left = &*x.nodes[3];
    x.nodes[0]->left->right = &*x.nodes[4];
    x.nodes[0]->right->left = &*x.nodes[5];
    x.nodes[0]->right->right = &*x.nodes[6];
    x.nodes[0]->left->right->right = &*x.nodes[7];
    x.nodes[0]->right->left->right = &*x.nodes[8];
    x.nodes[0]->right->right->left = &*x.nodes[9];
   return x;
}
BinaryNodes<int> Correct_Tree_Example13(){
   //        10
   //       /  \
   //      9    11
   //    /       \
   //   8         12
   //  /           \
   // 0             20
   //  \            /
   //   1          19
   //     \       / 
   //       2   18
   //        \  /
   //        3  17
   BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(10));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(9));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(11));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(8));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(12));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(0));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(20));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(19));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(18));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(3));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(17));
    x.nodes[0]->left = &*x.nodes[1];
    x.nodes[0]->right = &*x.nodes[2];
    x.nodes[0]->left->left = &*x.nodes[3];
    x.nodes[0]->right->right = &*x.nodes[4];
    x.nodes[0]->left->left->left = &*x.nodes[5];
    x.nodes[0]->right->right->right =&*x.nodes[6];
    x.nodes[0]->left->left->left->right = &*x.nodes[7];
    x.nodes[0]->right->right->right->left = &*x.nodes[8];
    x.nodes[0]->left->left->left->right->right = &*x.nodes[9];
    x.nodes[0]->right->right->right->left->left = &*x.nodes[10];
    x.nodes[0]->left->left->left->right->right->right = &*x.nodes[11];
    x.nodes[0]->right->right->right->left->left->left = &*x.nodes[12];
   return x;
}
BinaryNodes<int> Correct_Tree_Example14(){
       //    12
       //  /    \
       // 1      23
       //  \    /
       //   11 13
       //  /    \
       // 2      22
       //  \    /
       //   10 14
       //  /    \
       // 3      21
       //  \    /
       //   9  15
       //  /    \
       // 4      20
       //  \    /
       //   8  16
       //  /    \
       // 5      19
       //  \    /
       //   7  17
       //  /    \
       // 6      18
   BinaryNodes<int> x;
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(12));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(23));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(11));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(13));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(22));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(10));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(14));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(3));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(21));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(9));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(15));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(4));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(20));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(8));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(16));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(5));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(19));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(7));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(17));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(6));
  x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(18));
  x.nodes[0]->left = &*x.nodes[1];
  x.nodes[0]->right = &*x.nodes[2];
  x.nodes[0]->left->right = &*x.nodes[3];
  x.nodes[0]->right->left = &*x.nodes[4];
  x.nodes[0]->left->right->left = &*x.nodes[5];
  x.nodes[0]->right->left->right = &*x.nodes[6];
  x.nodes[0]->left->right->left->right = &*x.nodes[7];
  x.nodes[0]->right->left->right->left = &*x.nodes[8];
  x.nodes[0]->left->right->left->right->left = &*x.nodes[9];
  x.nodes[0]->right->left->right->left->right = &*x.nodes[10];
  x.nodes[0]->left->right->left->right->left->right = &*x.nodes[11];
  x.nodes[0]->right->left->right->left->right->left = &*x.nodes[12];
  x.nodes[0]->left->right->left->right->left->right->left = &*x.nodes[13];
  x.nodes[0]->right->left->right->left->right->left->right = &*x.nodes[14];
  x.nodes[0]->left->right->left->right->left->right->left->right = &*x.nodes[15];
  x.nodes[0]->right->left->right->left->right->left->right->left = &*x.nodes[16];
  x.nodes[0]->left->right->left->right->left->right->left->right->left = &*x.nodes[17];
  x.nodes[0]->right->left->right->left->right->left->right->left->right = &*x.nodes[18];
  x.nodes[0]->left->right->left->right->left->right->left->right->left->right = &*x.nodes[19];
  x.nodes[0]->right->left->right->left->right->left->right->left->right->left = &*x.nodes[20];
  x.nodes[0]->left->right->left->right->left->right->left->right->left->right->left = &*x.nodes[21];
  x.nodes[0]->right->left->right->left->right->left->right->left->right->left->right = &*x.nodes[22];
  return x;
}
BinaryNodes<int> Correct_Tree_Example15(){
       //    12
       //  /    \
       // 1      23
       //  \    /  \
       //   11 13   24
       //  /    \    \
       // 2      22   25
       //  \    /      \
       //   10 14       26
       //  /    \        \
       // 3      21      27
       //  \    /         \
       //   9  15         28
       //  /    \
       // 4      20
       //  \    /
       //   8  16
       //  /    \
       // 5      19
       //  \    /
       //   7  17
       //  /    \
       // 6      18
    BinaryNodes<int> x;
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(12));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(1));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(23));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(11));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(13));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(2));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(22));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(10));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(14));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(3));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(21));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(9));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(15));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(4));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(20));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(8));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(16));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(5));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(19));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(7));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(17));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(6));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(18));
    
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(24));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(25));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(26));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(27));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>>(28));
    
    x.nodes[0]->left = &*x.nodes[1];
    x.nodes[0]->right = &*x.nodes[2];
    x.nodes[0]->left->right = &*x.nodes[3];
    x.nodes[0]->right->left = &*x.nodes[4];
    x.nodes[0]->left->right->left = &*x.nodes[5];
    x.nodes[0]->right->left->right = &*x.nodes[6];
    x.nodes[0]->left->right->left->right = &*x.nodes[7];
    x.nodes[0]->right->left->right->left = &*x.nodes[8];
    x.nodes[0]->left->right->left->right->left = &*x.nodes[9];
    x.nodes[0]->right->left->right->left->right = &*x.nodes[10];
    x.nodes[0]->left->right->left->right->left->right = &*x.nodes[11];
    x.nodes[0]->right->left->right->left->right->left = &*x.nodes[12];
    x.nodes[0]->left->right->left->right->left->right->left = &*x.nodes[13];
    x.nodes[0]->right->left->right->left->right->left->right = &*x.nodes[14];
    x.nodes[0]->left->right->left->right->left->right->left->right = &*x.nodes[15];
    x.nodes[0]->right->left->right->left->right->left->right->left = &*x.nodes[16];
    x.nodes[0]->left->right->left->right->left->right->left->right->left = &*x.nodes[17];
    x.nodes[0]->right->left->right->left->right->left->right->left->right = &*x.nodes[18];
    x.nodes[0]->left->right->left->right->left->right->left->right->left->right = &*x.nodes[19];
    x.nodes[0]->right->left->right->left->right->left->right->left->right->left = &*x.nodes[20];
    x.nodes[0]->left->right->left->right->left->right->left->right->left->right->left = &*x.nodes[21];
    x.nodes[0]->right->left->right->left->right->left->right->left->right->left->right = &*x.nodes[22];
    
    x.nodes[0]->right->right = &*x.nodes[23];
    x.nodes[0]->right->right->right = &*x.nodes[24];
    x.nodes[0]->right->right->right->right = &*x.nodes[25];
    x.nodes[0]->right->right->right->right->right = &*x.nodes[26];
    x.nodes[0]->right->right->right->right->right->right = &*x.nodes[27];
    return x;
}
BinaryNodes<int> Correct_Tree_Example16(){
       //    12
       //  /    \
       // 1      23
       //  \    /  \
       //   11 13   24
       //  /    \    \
       // 2      22   25
       //  \    /      \
       //   10 14       26
       //  /    \        \
       // 3      21      27
       //  \    /         \
       //   9  15         31
       //  /    \        /
       // 4      20     28
       //  \    /        \
       //   8  16         30
       //  /    \        /
       // 5      19     29
       //  \    /
       //   7  17
       //  /    \
       // 6      18
    BinaryNodes<int> x;
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (12));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (1));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (23));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (11));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (13));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (2));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (22));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (10));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (14));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (3));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (21));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (9));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (15));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (4));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (20));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (8));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (16));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (5));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (19));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (7));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (17));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (6));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (18));
    
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (24));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (25));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (26));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (27));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (31));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (28));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (30));
    x.nodes.emplace_back(std::make_shared<BinaryNode<int>> (29));
    
    x.nodes[0]->left = &*x.nodes[1];
    x.nodes[0]->right = &*x.nodes[2];
    x.nodes[0]->left->right = &*x.nodes[3];
    x.nodes[0]->right->left = &*x.nodes[4];
    x.nodes[0]->left->right->left = &*x.nodes[5];
    x.nodes[0]->right->left->right = &*x.nodes[6];
    x.nodes[0]->left->right->left->right = &*x.nodes[7];
    x.nodes[0]->right->left->right->left = &*x.nodes[8];
    x.nodes[0]->left->right->left->right->left = &*x.nodes[9];
    x.nodes[0]->right->left->right->left->right = &*x.nodes[10];
    x.nodes[0]->left->right->left->right->left->right = &*x.nodes[11];
    x.nodes[0]->right->left->right->left->right->left = &*x.nodes[12];
    x.nodes[0]->left->right->left->right->left->right->left = &*x.nodes[13];
    x.nodes[0]->right->left->right->left->right->left->right = &*x.nodes[14];
    x.nodes[0]->left->right->left->right->left->right->left->right = &*x.nodes[15];
    x.nodes[0]->right->left->right->left->right->left->right->left = &*x.nodes[16];
    x.nodes[0]->left->right->left->right->left->right->left->right->left = &*x.nodes[17];
    x.nodes[0]->right->left->right->left->right->left->right->left->right = &*x.nodes[18];
    x.nodes[0]->left->right->left->right->left->right->left->right->left->right = &*x.nodes[19];
    x.nodes[0]->right->left->right->left->right->left->right->left->right->left = &*x.nodes[20];
    x.nodes[0]->left->right->left->right->left->right->left->right->left->right->left = &*x.nodes[21];
    x.nodes[0]->right->left->right->left->right->left->right->left->right->left->right = &*x.nodes[22];
    
    x.nodes[0]->right->right = &*x.nodes[23];
    x.nodes[0]->right->right->right = &*x.nodes[24];
    x.nodes[0]->right->right->right->right = &*x.nodes[25];
    x.nodes[0]->right->right->right->right->right = &*x.nodes[26];
    x.nodes[0]->right->right->right->right->right->right = &*x.nodes[27];
    x.nodes[0]->right->right->right->right->right->right->left = &*x.nodes[28];
    x.nodes[0]->right->right->right->right->right->right->left->right = &*x.nodes[29];
    x.nodes[0]->right->right->right->right->right->right->left->right->left = &*x.nodes[30];
    return x;
}

TEST(BST_Fix, NonAdjacent_1) {
    
    for (auto algo: algorithms_to_test()){
      auto tree = TwoNodesSwapped_NonAdjecent_Example1();
      check_algorithm_fixes_tree(*tree.nodes[0],algo);
    }
}
TEST(BST_Fix, NonAdjacent_2) {
    
    for (auto algo: algorithms_to_test()){
      auto tree = TwoNodesSwapped_NonAdjecent_Example2();
      check_algorithm_fixes_tree(*tree.nodes[0],algo);
    }
}
TEST(BST_Fix, NonAdjacent_3) {
    
    for (auto algo: algorithms_to_test()){
      auto tree = TwoNodesSwapped_NonAdjecent_Example3();
      check_algorithm_fixes_tree(*tree.nodes[0],algo);
    }
}
TEST(BST_Fix, NonAdjacent_4) {
    
    for (auto algo: algorithms_to_test()){
      auto tree = TwoNodesSwapped_NonAdjecent_Example4();
      check_algorithm_fixes_tree(*tree.nodes[0],algo);
    }
}
TEST(BST_Fix, NonAdjacent_5) {
    
    for (auto algo: algorithms_to_test()){
      auto tree = TwoNodesSwapped_NonAdjecent_Example5();
      check_algorithm_fixes_tree(*tree.nodes[0],algo);
    }
}
TEST(BST_Fix, NonAdjacent_6) {
    
    for (auto algo: algorithms_to_test()){
      auto tree = TwoNodesSwapped_NonAdjecent_Example6();
      check_algorithm_fixes_tree(*tree.nodes[0],algo);
    }
}
TEST(BST_Fix, NonAdjacent_7) {
        
    for (auto algo: algorithms_to_test()){
      auto tree = TwoNodesSwapped_NonAdjecent_Example7();
      check_algorithm_fixes_tree(*tree.nodes[0],algo);
    }
}
TEST(BST_Fix, Adjacent_1) {
    
    for (auto algo: algorithms_to_test()){
      auto tree = TwoNodesSwapped_Adjecent_Example1();
      check_algorithm_fixes_tree(*tree.nodes[0],algo);
    }
}
TEST(BST_Fix, Adjacent_2) {
    
    for (auto algo: algorithms_to_test()){
      auto tree = TwoNodesSwapped_Adjecent_Example2();
      check_algorithm_fixes_tree(*tree.nodes[0],algo);
    }
}
TEST(BST_Fix, Adjacent_3) {
    
    for (auto algo: algorithms_to_test()){
      auto tree = TwoNodesSwapped_Adjecent_Example3();
      check_algorithm_fixes_tree(*tree.nodes[0],algo);
    }
}
TEST(BST_Fix, Adjacent_4) {
    for (auto algo: algorithms_to_test()){
      auto tree = TwoNodesSwapped_Adjecent_Example4();
      check_algorithm_fixes_tree(*tree.nodes[0],algo);
    }
}
TEST(BST_Fix, Adjacent_5) {
    for (auto algo: algorithms_to_test()){
      auto tree = TwoNodesSwapped_Adjecent_Example5();
      check_algorithm_fixes_tree(*tree.nodes[0],algo);
    }
}
TEST(BST_Fix, Adjacent_6) {
    for (auto algo: algorithms_to_test()){
      auto tree = TwoNodesSwapped_Adjecent_Example6();
      check_algorithm_fixes_tree(*tree.nodes[0],algo);
    }
}
TEST(BST_Fix, Adjacent_7) {
    for (auto algo: algorithms_to_test()){
      auto tree = TwoNodesSwapped_Adjecent_Example7();
      check_algorithm_fixes_tree(*tree.nodes[0],algo);
    }
}
TEST(BST_Fix, Adjacent_8) {
    for (auto algo: algorithms_to_test()){
      auto tree = TwoNodesSwapped_Adjecent_Example8();
      check_algorithm_fixes_tree(*tree.nodes[0],algo);
    }
}
TEST(BST_Fix, Adjacent_9) {
    for (auto algo: algorithms_to_test()){
      auto tree = TwoNodesSwapped_Adjecent_Example9();
      check_algorithm_fixes_tree(*tree.nodes[0],algo);
    }
}
TEST(BST_Fix, Adjacent_10) {
    for (auto algo: algorithms_to_test()){
      auto tree = TwoNodesSwapped_Adjecent_Example10();
      check_algorithm_fixes_tree(*tree.nodes[0],algo);
    }
}
TEST(BST_Fix, Adjacent_11) {
    for (auto algo: algorithms_to_test()){
      auto tree = TwoNodesSwapped_Adjecent_Example11();
      check_algorithm_fixes_tree(*tree.nodes[0],algo);
    }
}
TEST(BST_Fix, Adjacent_12) {
    for (auto algo: algorithms_to_test()){
      auto tree = TwoNodesSwapped_Adjecent_Example12();
      check_algorithm_fixes_tree(*tree.nodes[0],algo);
    }
}


TEST(BST_Fix, Every_Swap_1) {
  for (auto algo: algorithms_to_test()){
    auto tree = Correct_Tree_Example1();
    check_every_swap_combination(*tree.nodes[0],algo);
  }
}
TEST(BST_Fix, Every_Swap_2) {
  for (auto algo: algorithms_to_test()){
    auto tree = Correct_Tree_Example2();
    check_every_swap_combination(*tree.nodes[0],algo);
  }
}
TEST(BST_Fix, Every_Swap_3) {
  for (auto algo: algorithms_to_test()){
    auto tree = Correct_Tree_Example3();
    check_every_swap_combination(*tree.nodes[0],algo);
  }
}
TEST(BST_Fix, Every_Swap_4) {
  for (auto algo: algorithms_to_test()){
    auto tree = Correct_Tree_Example4();
    check_every_swap_combination(*tree.nodes[0],algo);
  }
}
TEST(BST_Fix, Every_Swap_5) {
  for (auto algo: algorithms_to_test()){
    auto tree = Correct_Tree_Example5();
    check_every_swap_combination(*tree.nodes[0],algo);
  }
}
TEST(BST_Fix, Every_Swap_6) {
  for (auto algo: algorithms_to_test()){
    auto tree = Correct_Tree_Example6();
    check_every_swap_combination(*tree.nodes[0],algo);
  }
}
TEST(BST_Fix, Every_Swap_7) {
  for (auto algo: algorithms_to_test()){
    auto tree = Correct_Tree_Example7();
    check_every_swap_combination(*tree.nodes[0],algo);
  }
}
TEST(BST_Fix, Every_Swap_8) {
  for (auto algo: algorithms_to_test()){
    auto tree = Correct_Tree_Example8();
    check_every_swap_combination(*tree.nodes[0],algo);
  }
}
TEST(BST_Fix, Every_Swap_9) {
  for (auto algo: algorithms_to_test()){
    auto tree = Correct_Tree_Example9();
    check_every_swap_combination(*tree.nodes[0],algo);
  }
}

TEST(BST_Fix, Every_Swap_10) {
  for (auto algo: algorithms_to_test()){
    auto tree = Correct_Tree_Example10();
    check_every_swap_combination(*tree.nodes[0],algo);
  }
}

TEST(BST_Fix, Every_Swap_11) {
  for (auto algo: algorithms_to_test()){
    auto tree = Correct_Tree_Example11();
    check_every_swap_combination(*tree.nodes[0],algo);
  }
}
TEST(BST_Fix, Every_Swap_12) {
  for (auto algo: algorithms_to_test()){
    auto tree = Correct_Tree_Example12();
    check_every_swap_combination(*tree.nodes[0],algo);
  }
}
TEST(BST_Fix, Every_Swap_13) {
  for (auto algo: algorithms_to_test()){
    auto tree = Correct_Tree_Example13();
    check_every_swap_combination(*tree.nodes[0],algo);
  }
}

TEST(BST_Fix, Every_Swap_14) {
  for (auto algo: algorithms_to_test()){
    auto tree = Correct_Tree_Example14();
    check_every_swap_combination(*tree.nodes[0],algo);
  }
}

TEST(BST_Fix, Every_Swap_15) {
  for (auto algo: algorithms_to_test()){
    auto tree = Correct_Tree_Example15();
    check_every_swap_combination(*tree.nodes[0],algo);
  }
}

TEST(BST_Fix, Every_Swap_16) {
  for (auto algo: algorithms_to_test()){
    auto tree = Correct_Tree_Example16();
    check_every_swap_combination(*tree.nodes[0],algo);
  }
}

TEST(BST_Fix, Example_Hickey_Shuffle_Easy) {
        //    2
        //  /  \
        // 1    4
        //     / \
        //    3   5
  for (auto algo: algorithms_to_test()){
    
    BinaryNode<int> root(2);
    BinaryNode<int> r1(1);
    BinaryNode<int> r2(4);
    BinaryNode<int> r3(3);
    BinaryNode<int> r4(5);
    
    root.left = &r1;
    root.right = &r2;
    root.right->left = &r3;
    root.right->right = &r4;
    
    check_every_swap_combination(root,algo);
  }
}

TEST(BST_Fix, Example_Hickey_Shuffle_Hard) {

        //    2
        //  /  \
        // 1    3
        //       \
        //        11
        //       /
        //      5
        //     / \
        //    4   7
        //       / \
        //      6   10
        //         /
        //        8
        //         \
        //          9
  for (auto algo: algorithms_to_test()){
    
    BinaryNode<int> root(2);
    BinaryNode<int> r1(1);
    BinaryNode<int> r2(3);
    BinaryNode<int> r3(11);
    BinaryNode<int> r4(5);
    BinaryNode<int> r5(4);
    BinaryNode<int> r6(7);
    BinaryNode<int> r7(6);
    BinaryNode<int> r8(10);
    BinaryNode<int> r9(8);
    BinaryNode<int> r10(9);
    
    root.left = &r1;
    root.right = &r2;
    root.right->right = &r3;
    root.right->right->left = &r4;
    root.right->right->left->left = &r5;
    root.right->right->left->right = &r6;
    root.right->right->left->right->left = &r7;
    root.right->right->left->right->right = &r8;
    root.right->right->left->right->right->left = &r9;
    root.right->right->left->right->right->left->right = &r10;
    
    check_every_swap_combination(root,algo);
  }
}







