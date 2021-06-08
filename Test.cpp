#include "doctest.h"
#include "sources/BinaryTree.hpp"
#include <istream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
using namespace ariel;


TEST_CASE("char tree")
{
    BinaryTree<char> char_tree1;
    CHECK_THROWS(char_tree1.add_root('s'));
    CHECK_THROWS(char_tree1.add_left('B', 'c'));
    CHECK_THROWS(char_tree1.add_left('P', '4'));
    CHECK_THROWS(char_tree1.add_right('t', '5'));
    CHECK_THROWS(char_tree1.add_right('q', '7'));
    CHECK_THROWS(char_tree1.add_left('1', '2'));

    BinaryTree<char> char_tree2;
    CHECK_NOTHROW(char_tree2.add_root('s'));
    CHECK_NOTHROW(char_tree2.add_left('s', 'B'));
    CHECK_NOTHROW(char_tree2.add_left('B', 'C'));
    CHECK_NOTHROW(char_tree2.add_right('C', 'D'));
    CHECK_NOTHROW(char_tree2.add_right('D', 'E'));
    CHECK_NOTHROW(char_tree2.add_left('E', 'F'));
}


TEST_CASE("add left and right"){

    BinaryTree<int> tree;
    tree.add_root(1);

    CHECK_NOTHROW(tree.add_left(1,2).add_right(1,3));
    CHECK_THROWS(tree.add_right(4,5));
    CHECK_NOTHROW(tree.add_left(1,4).add_right(1,5));

    CHECK_THROWS(tree.add_left(2,3));
    CHECK_THROWS(tree.add_right(3, 6));

}


TEST_CASE(" iterators "){

    BinaryTree<int> int_tree;
    
    // CHECK_THROWS(int_tree.add_left(1,2)); // no root yet
    // CHECK_THROWS(int_tree.add_right(1,2)); // no root yet

    CHECK_NOTHROW(int_tree.add_root(1)
                        .add_left(1,2)
                        .add_right(1,3));

    
    ostringstream  output;
    for (auto it=int_tree.begin_preorder(); it!=int_tree.end_preorder(); ++it) {
        output<<(*it) <<" ";
    }  
    CHECK(output.str() == "1 2 3 ");

    output.str("");
    output.clear();
    for (auto it=int_tree.begin_inorder(); it!=int_tree.end_inorder(); ++it) {
        output<<(*it) <<" ";
    }  
    CHECK(output.str() == "2 1 3 ");

    output.str("");
    output.clear();
    for (auto it=int_tree.begin_postorder(); it!=int_tree.end_postorder(); ++it) {
        output<<(*it) <<" ";
    } 
    CHECK(output.str() == "2 3 1 "); 

    output.str("");
    output.clear();
    for(int element: int_tree){
        output<<(element) <<" ";
    }
    CHECK(output.str() == "2 1 3 ");

    CHECK_THROWS(int_tree.add_right(4,5));
    CHECK_THROWS(int_tree.add_left(4,5));

    CHECK_NOTHROW(int_tree.add_left(1,4));
    CHECK_NOTHROW(int_tree.add_left(4,5));
    CHECK_NOTHROW(int_tree.add_right(4,6));

    
}


