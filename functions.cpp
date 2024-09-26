#include "functions.h"

Node::Node()
    : data(""),
      left(NULL),
      right(NULL)
{
}

Node::Node(string newdata)
    : data(newdata),
      left(NULL),
      right(NULL)
{
}

Node::Node(string newData, Node *leftptr, Node *rightptr)
    : data(newData),
      left(leftptr),
      right(rightptr)
{
}

string Node::getData()
{
    return data;
}

Node *Node::goLeft()
{
    return left;
}

Node *Node::goRight()
{
    return right;
}

// Function to make expression tree from postfix expression
Tree::Tree(string postfix_exp)
{
    vector<string> exp_list = string_to_list(postfix_exp);
    stack<Node *> st;
    for (int i = 0; i < exp_list.size(); i++)
    {
        try
        {
            int operand = stoi(exp_list[i]);
            Node *operand_node = new Node(exp_list[i]);
            st.push(operand_node);
        }
        catch (const invalid_argument &e)
        {
            Node *right_node = st.top();
            st.pop();
            Node *left_node = st.top();
            st.pop();
            Node *sub_tree = new Node(exp_list[i], left_node, right_node);
            st.push(sub_tree);
        }
    }
    if (!st.empty())
    {
        root = st.top();
        st.pop();
        return;
    }
    root = NULL;
}

Node *Tree::getRoot()
{
    return root;
}

// Function to check operator precedence
int precedence(string op)
{
    if (op == "^")
    {
        return 3;
    }
    else if (op == "*" || op == "/")
    {
        return 2;
    }
    else if (op == "+" || op == "-")
    {
        return 1;
    }
    return -1;
}

// Function to convert the string input to a vector array.
// This way all the numbers, brackets and operators (except whitespace)
// will be stored as individual string elements in the array
vector<string> string_to_list(string s)
{
    vector<string> result;
    string vector_element = "";
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] != ' ')
        {
            vector_element += s[i];
        }
        else
        {
            result.push_back(vector_element);
            vector_element = "";
        }
    }
    result.push_back(vector_element);
    return result;
}

// Function to convert the infix expression to postfix
string infix_to_postfix(string exp)
{
    vector<string> exp_list = string_to_list(exp);
    stack<string> st;
    string postfix = "";
    for (int i = 0; i < exp_list.size(); i++)
    {
        try
        {
            int operand = stoi(exp_list[i]);
            postfix += exp_list[i] + " ";
        }
        catch (const invalid_argument &e)
        {
            if (exp_list[i] == "(")
            {
                st.push(exp_list[i]);
            }
            else if (exp_list[i] == ")")
            {
                while (!st.empty() && st.top() != "(")
                {
                    postfix += st.top() + " ";
                    st.pop();
                }
                if (!st.empty())
                {
                    st.pop();
                }
            }
            else
            {
                while (!st.empty() && (precedence(st.top()) >= precedence(exp_list[i])))
                {
                    postfix += st.top() + " ";
                    st.pop();
                }
                st.push(exp_list[i]);
            }
        }
    }
    while (!st.empty())
    {
        postfix += st.top() + " ";
        st.pop();
    }
    postfix.pop_back();
    return postfix;
}

// Function to print expression tree in preorder form
void Tree::preorder(Node *rootNode)
{
    if (rootNode != NULL)
    {
        cout << rootNode->getData() << " ";
        preorder(rootNode->goLeft());
        preorder(rootNode->goRight());
    }
}

// Function to print expression tree in inorder form
void Tree::inorder(Node *rootNode)
{
    if (rootNode != NULL)
    {
        cout << "( ";
        inorder(rootNode->goLeft());
        cout << rootNode->getData() << " ";
        inorder(rootNode->goRight());
        cout << ") ";
    }
}

// Function to print expression tree in postorder form
void Tree::postorder(Node *rootNode)
{
    if (rootNode != NULL)
    {
        postorder(rootNode->goLeft());
        postorder(rootNode->goRight());
        cout << rootNode->getData() << " ";
    }
}

int Tree::evaluate_tree(Node *rootNode)
{
    if (rootNode->goLeft() == NULL && rootNode->goRight() == NULL)
    {
        return stoi(rootNode->getData());
    }
    else
    {
        Node *left_subtree_root = rootNode->goLeft();
        Node *right_subtree_root = rootNode->goRight();
        switch (root->getData()[0])
        {
        case '+':
            return evaluate_tree(left_subtree_root) + evaluate_tree(right_subtree_root);
        case '-':
            return evaluate_tree(left_subtree_root) - evaluate_tree(right_subtree_root);
        case '*':
            return evaluate_tree(left_subtree_root) * evaluate_tree(right_subtree_root);
        case '/':
            return evaluate_tree(left_subtree_root) / evaluate_tree(right_subtree_root);
        default:
            return stoi(rootNode->getData());
            break;
        }
    }
}

// int Tree::evaluate_tree(Node *rootNode)
// {
//     if (rootNode != NULL)
//     {
//         try
//         {
//             int operand = stoi(rootNode->getData());
//             // return operand;
//         }
//         catch (const invalid_argument &e)
//         {
//             int left_subtree = evaluate_tree(rootNode->goLeft());
//             int right_subtree = evaluate_tree(rootNode->goRight());
//             string op = rootNode->getData();
//             switch (op[0])
//             {
//             case '+':
//                 return right_subtree + left_subtree;
//             case '-':
//                 return right_subtree - left_subtree;
//             case '*':
//                 return right_subtree * left_subtree;
//             case '/':
//                 return right_subtree / left_subtree;
//             default:
//                 break;
//             }
//         }
//     }
//     return 0;
// }

// To check if the input characters are valid
bool check_char_validity(string exp)
{
    string valid_chars = "1234567890+-*/^() ";
    for (int i = 0; i < exp.length(); i++)
    {
        if (valid_chars.find(exp[i]) == string::npos)
        {
            cout << "Input string does not contain valid characters...Please try again....." << endl;
            return false;
        }
    }
    return true;
}

// To check if the number of opening and closing brackets
// are equal for an infix input
bool equal_brackets(string exp)
{
    int open_brackets = 0;
    int close_brackets = 0;
    size_t pos = 0;
    while (pos = exp.find("(", pos) != string::npos)
    {
        open_brackets++;
        pos++;
    }
    pos = 0;
    while (pos = exp.find(")", pos) != string::npos)
    {
        close_brackets++;
        pos++;
    }
    if (open_brackets != close_brackets)
    {
        cout << "INPUT ERROR!! The number of opening anf closing brackets in your entered infix expression are not the same...";
        cout << "Please try again....." << endl;
        return false;
    }
    return true;
}

// master function to run all the error handler
// functions at once
bool check_input_validity(string exp)
{
    return (check_char_validity(exp) && equal_brackets(exp));
}