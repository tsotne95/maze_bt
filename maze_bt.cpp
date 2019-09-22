/*
    Tsotne Chakhvadze
    2019

    Generate maze using binary tree method
    And print path between selected two node
*/
#include <bits/stdc++.h>
using namespace std;

//print fowallrmatted maze
//for wall cell - # symbol
//if it is empty just space
void print_maze(char ** maze, int width, int height)
{
    for(int i=0;i<height;i++)
    {

        if(!i)
        {
            
            //if width<10, it looks great, 
            //if greather, then just comment that next line, 
            //first for loop and endl printing line
            ///*
            cout<<"  ";
            for(int j=0;j<width;j++)
                cout<<j<<' ';
            cout<<endl; 
            cout<<" ";
            //*/
            for(int j=0;j<2*width+1;j++)
                cout<<'#';
            cout<<endl;
        }
        //Because of same reason, comment this line too
        cout<<i;
        for(int j=0;j<width;j++)
            {
                if(!j)
                {
                    cout<<"#";
                }
                if(maze[i][j]=='R')
                {
                    cout<<"  ";
                }
                else
                {
                    cout<<" #";
                }                
            }
        cout<<endl;
        
        //Same for next line
        cout<<' ';
        for(int j=0;j<width;j++)
            {
                if(!j)
                {
                    cout<<"#";
                }
                if(maze[i][j]=='D')
                {
                    cout<<" #";
                }
                else
                {
                    cout<<"##";
                }                
            }
        cout<<endl;
    }
}

struct Node { 
    int i,j; 
    Node *left, *right,*father; 
    Node(){}
}; 
  
void getNode(struct Node* newNode,int i, int j) 
{  
    newNode->i = i; 
    newNode->j=j;
    newNode->left = newNode->right = NULL; 
    newNode->father=NULL;
} 
//print path between two cell of maze
void printPathBetweenNodes(Node* a, Node* b) 
{ 
    queue<Node*> path;
    stack<Node*>stack_n;
    
    Node*va=a;
    Node*vb=b;
    Node*x=NULL;
    unordered_map<Node*,int>m;

    while(!x)
    {
        
        if(va==vb)
            x=va;
        else if(m[va]==2)
                x=va;
        else if(m[vb]==1)
                x=vb;
        else
        {
            m[va]=1;
            if(va->father)
                va=va->father;
            stack_n.push(vb);
            m[vb]=2;
            if(vb->father)
                vb=vb->father;
        }        
    }   

    while(vb!=x)
    {
        m[vb]=0;
        
        if(!stack_n.empty())
        {
            vb=stack_n.top();
            stack_n.pop();
        }
        else
        {
            break;
        }
    }

    va=a;
    while (va!=x)
    {
        path.push(va);
        m[va]=0;
        va=va->father;
    }

    path.push(x);
    while(m[va])
    {
        m[va]=0;
        va=va->father;
    }

    while(!stack_n.empty())
    {
        vb=stack_n.top();
        stack_n.pop();
        m[vb]=0;
        path.push(vb);
    }

    cout<<"Path between that two nodes: ";

    while (!path.empty())
    {
        x=path.front();
        path.pop();
        cout<<"("<<x->i<<" "<<x->j<<") ";
    }
    cout<<endl;
    
} 
//print binary tree
//improve formating
void printLineByLine(Node *root) {
		if (!root) {
			return;
		}
		queue<Node*> queue;
		queue.push(root);
		while (!queue.empty()) {
			int size = queue.size();
			for (int i = 0; i < size; i++) {
				Node* x = queue.front();   
                queue.pop();
				cout<<x->i << " "<<x->j<<"\t";
				if (x->left ) {
					queue.push(x->left);
				}
				if (x->right) {
					queue.push(x->right);
				}
			}
			cout<<endl;
		}
	}

int main()
{
	int width,height,rand_v;
	
	cout<<"input width: ";
	cin>>width;

	cout<<"input height: ";
	cin>>height;
    
    //dynamycally allocate maze array
    //maze cell notations:
    //      W - Walls
    //      R - removed right wall
    //      D - removed down wall
	char **maze=new char*[height];

    for(int i=0;i<height;i++)
        maze[i]=new char[width];
	
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
			maze[i][j]='W';
    
    Node ** maze_tree=new Node*[height];

    for(int i=0;i<height;i++)
        maze_tree[i]=new Node[width];

    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
            getNode(&maze_tree[i][j],i,j);
    
    srand(time(0));

    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
        {
            vector<pair<int,int>> v;
            if(i+1<height)
                v.push_back({i+1,j});
            
            if(j+1<width)
                v.push_back({i,j+1});

            if(v.size())
            {
                rand_v=rand()%v.size();
                
                if(v[rand_v].first==i)
                    {
                        maze[i][j]='R';
                        maze_tree[i][j+1].right=&maze_tree[i][j];
                        maze_tree[i][j].father=&maze_tree[i][j+1];
                    }
                else
                    {
                        maze[i][j]='D';
                        maze_tree[i+1][j].left=&maze_tree[i][j];
                        maze_tree[i][j].father=&maze_tree[i+1][j];
                    }
            }
        }
	
	print_maze(maze,width,height);     

    cout<<"Enter start position: ";
    int sx,sy,ex,ey;
    cin>>sx>>sy;

    cout<<"Enter end position: ";
    cin>>ex>>ey;
    
    printPathBetweenNodes(&maze_tree[sx][sy],&maze_tree[ex][ey]);

    //printLineByLine(&maze_tree[height-1][width-1]);

	return 0;
}