#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

int n,Nn; //number of child;
struct structre
{
    structre *parentNode, *nextNode;
    string *englishWord, *banglaWord;
    int presentNode;
    bool isLeaf; //if it is a leaf the function will return true
    structre **pointer;
} ;

structre *rootNode,*firstLeaf;

structre* Create_New_Node() ;        

structre *search_leaf(structre *tempNode,string english, int *counter); 

void data_pointer_insertion(structre *parentNode,string value,structre *right); 

void Add_median_node(structre *parentNode,string value,structre *left,structre *right);

void Leaf_Insertion(string english, string bangla);

int main(void)
{
	cout << "Enter number of Child:" << endl;
	cin >> n;
	Nn=n;
    
    rootNode = Create_New_Node();

    structre *leaf;
    int i=0,counter;
    string english,bangla,searchWord;

    ifstream file;
    file.open("dictionary.txt");

    if(!file) { //if file not open
        return 0;
    }

    while(file>>english)
    {
    	getline(file, bangla);
    	Leaf_Insertion(english, bangla); //making tree
    }

    cout<<"Enter word: ";
    while(cin>>searchWord)
    {
        auto start = high_resolution_clock::now();

    	 leaf= search_leaf(rootNode, searchWord ,&counter); //find if leaf

    	 for(i=0; i<leaf->presentNode; i++) //traverse leaf nodes
         {
            if(searchWord==leaf->englishWord[i]) {
                break;
            }
         }

    	 if(i==leaf->presentNode) 
         {
            cout<<"Word is not present in dictionary.\n";
         }
    	 else 
         {
            cout<<searchWord<<" "<<leaf->banglaWord[i]<<endl;
         }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
	    cout << "Time taken for searching "<< duration.count()<< " microseconds"<<endl;
    	cout<<"Enter word: ";
    }

}

structre* Create_New_Node()         
{
    structre *treeSturcture=new structre();

    treeSturcture->pointer = new structre *[n+1]; //if number of child is n then pointer will be n+1
    treeSturcture->englishWord=new string[n];
    treeSturcture->banglaWord=new string[n];

    treeSturcture->presentNode = 0; //no node is present when first creating a node
    treeSturcture->parentNode = NULL; //initially all values will be null
    treeSturcture->nextNode = NULL;
    treeSturcture->isLeaf = true;
    
    return treeSturcture;
}

void data_pointer_insertion(structre *parentNode,string value,structre *right) //find position then insert a value and point it 
{                                      
    int i=parentNode->presentNode-1; //start searching from last record
    for(;i>=0; i--)
    {
        if(parentNode->englishWord[i]<=value) //if value is matched or less than then position is found and break loop
        {
             break;
        }
        else
        {
            parentNode->englishWord[i+1] = parentNode->englishWord[i];
            parentNode->pointer[i+2] = parentNode->pointer[i+1]; //pointer refers to next address of i so i+1 and i+2
        }
    }

    parentNode->englishWord[i+1] = value; //set value to the position
    parentNode->pointer[i+2] = right; //set pointer
    parentNode->presentNode++;
}

void Add_median_node(structre *parentNode,string value,structre *left,structre *right)
{
    if(parentNode==NULL)        //create a root if you want to split and send the smallest value to root
    {
        parentNode = Create_New_Node(); //creating a parent node
        parentNode->englishWord[0] = value; //inserting value
        parentNode->pointer[0] = left; 
        parentNode->pointer[1] = right;
        parentNode->presentNode++;
        parentNode->isLeaf = false; //parent node is not leaf at iniital stage
        rootNode = parentNode; //root ill be parent at initial stage
        left->parentNode = parentNode;
        right->parentNode = parentNode;
        return;
    }

    //if there is space and no overflow then simply insert value and make a right biased tree
    right->parentNode = parentNode;
    data_pointer_insertion(parentNode,value,right);
    
    //if there is no space and overflow condition then split and insert
    if(parentNode->presentNode==Nn)
    {
        structre *newSplitNode = Create_New_Node();
        newSplitNode->isLeaf = false; //as we are adding internal node
        int j=0;
        for(int i=parentNode->presentNode-(n)/2; i<Nn; i++) //as splitting so start from middle node
        {
            newSplitNode->englishWord[j] = parentNode->englishWord[i]; //put value in the first place of splitted node
            
            if(j==0)
            {
                newSplitNode->pointer[0] = parentNode->pointer[i];
                newSplitNode->pointer[0]->parentNode = newSplitNode;
            }

            newSplitNode->pointer[j+1] = parentNode->pointer[i+1];
            newSplitNode->pointer[j+1]->parentNode = newSplitNode;

            j++;
        }

        parentNode->presentNode-=(n)/2+1; //setting next value
        newSplitNode->presentNode = (n)/2; //number of nodes in split node will be half
        Add_median_node(parentNode->parentNode, parentNode->englishWord[parentNode->presentNode], parentNode, newSplitNode); //might add more value
    }

}

structre *search_leaf(structre *tempNode,string english, int *counter) //whether node is a leaf and in which position we will insert new data
{
    int sum=0;
    while(tempNode->isLeaf==false)
    {
        int i;
        for(i=0; i<tempNode->presentNode; i++) //search for every node
         {
            if(english<tempNode->englishWord[i]) 
            {
                break; //if given string is less than new data then insert at that position
            }
         }
        tempNode = tempNode->pointer[i]; //point to the next node
        sum++;
    }
    *counter = sum;
    return tempNode;
}

void Leaf_Insertion(string english, string bangla)
{
    int counter=0;
    structre *leafNode = search_leaf(rootNode, english, &counter);        //find leaf where it can be fit
    
    int i= leafNode->presentNode-1;
    if(i>-1) {
    for(; i>=0; i--)
    {
    	if(english<leafNode->englishWord[i])                //fit in leaf
    	{
    		leafNode->englishWord[i+1] = leafNode->englishWord[i];
    		leafNode->banglaWord[i+1] = leafNode->banglaWord[i];
    	}
    	else 
        {
            break;
        }
    }
    }

    leafNode->englishWord[i+1] = english;
    leafNode->banglaWord[i+1] = bangla;
    leafNode->presentNode++;

    if(leafNode->presentNode==Nn)               //split and create two leaf if overflowed
    {
        structre *splitNode = Create_New_Node();
        int j=0;

        for(int i=leafNode->presentNode-n/2; i<Nn; i++)
        {
            splitNode->englishWord[j] = leafNode->englishWord[i];
            splitNode->banglaWord[j] = leafNode->banglaWord[i];
            j++;
        }

        leafNode->presentNode-=n/2;
        splitNode->presentNode = n/2;
        splitNode->nextNode = leafNode->nextNode; //all leaf node internally connected
        leafNode->nextNode = splitNode;

        Add_median_node(leafNode->parentNode, splitNode->englishWord[0], leafNode, splitNode);
    }
}
