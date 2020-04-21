#include "FamilyTree.hpp"
#include <stack>

using namespace family;
using namespace std;

Tree::Tree(string name){
    root=new node(name);
}

Tree::~Tree(){

}
node* Tree::nodeName(const string name)
{
    stack < node* > stack;
    creatStack(stack);  
    node* obj;

    while (!stack.empty())
    {
        obj = stack.top();
        stack.pop();
        if (obj->name == name) return obj;
    }

    
    return nullptr;
}
void Tree::creatStack( stack <node*>& sofi)
{
    stack< node*> stack;
    stack.push(root);
    while (!stack.empty())
    {
        node* obj = stack.top();
        stack.pop();
        sofi.push(obj);
        if (obj->mother)
            stack.push(obj->mother);
        if (obj->father)
            stack.push(obj->father);
            
    }
}
Tree& Tree::addFather(string child, string father)
{
    node* obj = nodeName(child);
   
    if (!obj || obj->father)
    {
        throw string("already have father or not find a child name");   
    }
    else
    {
         obj->father = new node(father);
    }
    return *this;
}

Tree& Tree::addMother(string child, string mother)
{
    node* obj = nodeName(child);
   
    if (!obj || obj->mother)
    {
        throw string("already have mother or not find a child name");   
    }
    else
    {
         obj->mother = new node(mother);
    }
    return *this;
}

string Tree::relation(string name)
{
    stack<node*> stack;
    creatStack(stack);
    int sex=0;                
    int gen=1;
    string sofi;
    node* temp=nodeName(name);
    if (temp==nullptr)
    {
        return "unrelated";
    }

    node* newStack=temp; 
 if (root->name==name)
    {
        return "me";
    }
    while (!stack.empty())
    {
        temp = stack.top();

        if (temp->mother==newStack && sex==0)
        {
            sex=-1;
            gen++;
            newStack=temp;
            
        }
        else if (temp->father==newStack && sex==0)
        {
            sex=1;
            gen++;
            newStack=temp;
            
        }
        else if (temp->mother==newStack || temp->father==newStack)
        {
            newStack=temp;
            gen++;
        }

        stack.pop();
    }

    switch (sex)
    {
        case -1:
        if (gen == 2){sofi = "mother";}
        else{sofi = "grandmother";}
        break;

        case 1:
        if (gen == 2){sofi = "father";}
        else{sofi = "grandfather"; }
        break;
    }

    gen--;

    while (gen > 2)
    {
        sofi = "great-" + sofi;
        gen--;
    }
    return sofi;
}

string Tree::find(string obj)
{
    stack <node*> stack;
    string rel;
    creatStack(stack);
    while (!stack.empty())
    {
        node* ans=stack.top();
        rel=relation(ans->name);
        if (rel==obj)
        {
            return ans->name;
        }
        stack.pop();
    }

    throw string("No  relation "+ obj);
}

 void Tree::display() { print2DUtil(root,0); }

//https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/

void Tree::print2DUtil(node* root, int space)  
{  
    int COUNT=10;
    if (root == NULL)  
        return;  
    
    space += COUNT;  
  
    
    print2DUtil(root->mother, space);    
    cout<<endl;  
    for (int i = COUNT; i < space; i++)  
        cout<<" ";  
        cout<<root->name<<"\n";   
    print2DUtil(root->father, space);  
}  

void Tree::remove(string name)
{
    stack <node*> stack;
    creatStack(stack);
    node* temp=nodeName(name);
    node* newStack=temp;
    while (!stack.empty())
    {
       temp = stack.top();
        if (temp->father==newStack && temp->father!=nullptr)
        {   
           
            temp->father = nullptr;
            return;
        }
        if (temp->mother==newStack && temp->mother!=nullptr)
        {
            
            temp->mother = nullptr;
            return;
        }
        stack.pop();
    }

   throw string("child named:" + name + "no in the tree");
}
 
//https://www.geeksforgeeks.org/write-a-c-program-to-delete-a-tree/

void deleteTree(node* node)  
{  
    if (node == NULL) return;  
  
    /* first delete both subtrees */
    deleteTree(node->mother);  
    deleteTree(node->father);  
      
    /* then delete the node */
    cout << "\n Deleting node: " << node->name;  
    free(node);  
}  


