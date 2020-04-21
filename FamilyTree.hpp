#include <iostream>
#include <string>
#include <stack>
#pragma once
using namespace std;


namespace family{
    struct node{
        string name;
        node* father;
        node* mother;
    

        node(const string& name): name(name),father(nullptr),mother(nullptr){ };
    };

    class Tree{
        node* root;
        
     public:

     Tree(string);
     ~Tree();
    
     Tree& addFather(string child,string father);
     Tree& addMother(string child,string mother);
     string relation(string);
     string find(string);
     void display(); 
     void remove(string);
     node* nodeName( string name);
     void creatStack(stack<node*>& st);
     void print2DUtil(node* root, int space);
     void deleteTree(node* node);

    };
}