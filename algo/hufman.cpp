#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>
using namespace std;
 
//哈夫曼树节点类
class hfTNode {
public:
	int weight;//节点的权重
	int ch;//存储节点的下标
	hfTNode* leftchild, * rightchild;//创建该结点的左右孩子指针
	hfTNode() ://哈夫曼树节点类初始化
		leftchild(nullptr), rightchild(nullptr) {}
	hfTNode(int data) ://哈夫曼树节点类初始化
		leftchild(nullptr), rightchild(nullptr), weight(data) {}
	//拷贝构造函数
	hfTNode(const hfTNode& node) {
		ch = node.ch;
		weight = node.weight;
		if (node.leftchild) {
			leftchild = new hfTNode();
			*leftchild = *(node.leftchild);
		}
		else
			leftchild = nullptr;
		if (node.rightchild) {
			rightchild = new hfTNode();
			*rightchild = *(node.rightchild);
		}
		else
			rightchild = nullptr;
	}
	// 重载"<"符号，令其为最小值优先
	bool operator < (const hfTNode& node) const{
		return weight > node.weight;
	}
};
 
//哈夫曼树类
class Huffman
{
public:
	Huffman(const vector<int> &weightvec);// 构造函数
	~Huffman();// 析构函数
 
	bool IsLeaf(hfTNode* Root);//判断节点是否为叶子结点
	void GetFreq(vector<int> &des);//获取当前的权重数组
	void BuildTree();//构建一颗哈夫曼树
	void BuildCode();//根据哈夫曼树构建编码表
	void GetCodeList();//遍历编码表和编码表对应的编码
 
	//前序遍历和中序遍历是为了确定哈夫曼树的形状是否正确
	void PreOrder(hfTNode* root);//前序遍历
	void InOrder(hfTNode* root);
    hfTNode* Root; // 哈夫曼树根节点
	
 
protected:
	void dele(hfTNode* root);//删除哈夫曼树
	void build(hfTNode* root, string str);//生成 huffman对应编码 
	unordered_map<char, string> table;//key为编码表的字符，value为编码表的字符对应的编码形式例如“101”，“111”
	vector<int> freq; // 权重数组
	vector<char> st; // 编码表
	
};
 
//依据字符串生成编码表以及权重数组
Huffman::Huffman(const vector<int> &weightvec)
{
	int len = weightvec.size();
	unordered_map<char, int> newtable;//哈希表，存储字符和权值
	for (int i = 0; i < len; ++i)//依据输入字符串初始化哈希表
		newtable[char(int('A')+i)] =weightvec[i];
	for (const auto& pair : newtable) {//遍历哈希表，将key和value分别存入编码和权重数组
		st.push_back(pair.first);
		freq.push_back(pair.second);
	}
}
 
//析构函数
Huffman::~Huffman()
{
	dele(Root);
}
//判断节点是否为叶子结点
bool Huffman::IsLeaf(hfTNode* Root)
{
	if(Root==nullptr) return false;
	if (Root->leftchild == nullptr && Root->rightchild == nullptr) 
		return true;
	else 
		return false;
}
 
//获取当前的权重数组
void Huffman::GetFreq(vector<int> &freqvec)
{
	for (int i = 0; i < freq.size(); i++)
		freqvec.push_back(freq[i]);
}
 
//构建哈夫曼树
void Huffman::BuildTree()
{
	priority_queue<hfTNode> myqueue;//使用最小优先级队列存储节点
	for (int i = 0; i < freq.size(); i++){//节点初始化，并将节点压入最小优先级队列中
		hfTNode* temp = new hfTNode(freq[i]);
		temp->ch = i;
		myqueue.push(*temp);
	}
	//合并节点并生成树
	while (myqueue.size() > 1) {
		//从队列中取出两个最小元素作为新子树的左孩子和右孩子
		hfTNode left = myqueue.top();
		myqueue.pop();
		hfTNode right = myqueue.top();
		myqueue.pop();
		//创建新子树的根节点，并将其压入队列中
		hfTNode* parent = new hfTNode(left.weight + right.weight);
		parent->ch = -1;//设定子树生成的根结点下标值是-1，只做区分用
		parent->leftchild = &left;
		parent->rightchild = &right;
		myqueue.push(*parent);
	}
	//生成哈夫曼树的根结点
	Root = new hfTNode();
	*Root = myqueue.top();
	myqueue.pop();
}
 
//根据哈夫曼树构建编码表
void Huffman::BuildCode()
{
	if (Root == nullptr) return;
	//string temp('\0');
	string temp;
	temp.clear();//初始化为空字符串
	build(Root, temp);
}
 
//遍历编码表和编码表对应的编码
void Huffman::GetCodeList()
{
	for (const auto& pair : table) 
		cout << pair.first << ": " << pair.second << endl;
}



//前序遍历 
void Huffman::PreOrder(hfTNode* root)
{
	if (root == nullptr) return;
	cout << root->ch << " :" << root->weight << endl;
	PreOrder(root->leftchild);
	PreOrder(root->rightchild);
}
 
//中序遍历
void Huffman::InOrder(hfTNode* root)
{
	if (root == nullptr) return;
	InOrder(root->leftchild);
	cout << root->ch << " :" << root->weight << endl;
	InOrder(root->rightchild);
}
 
//删除哈夫曼树
void Huffman::dele(hfTNode* root)
{
	if (root == nullptr) 
		return;
	if (root->leftchild) 
		dele(root->leftchild);
	if (root->rightchild) 
		dele(root->rightchild);
}
 
void Huffman::build(hfTNode* root, string str)
{
	// 是叶子节点,将编号和对应编码加入哈希表,作为递归出口
	if (IsLeaf(root)&& root->ch >= 0) {
		table[st[root->ch]] = str;
		return;
	}
	//是中间节点,项左右孩子递归
	if(root->leftchild) build(root->leftchild, str + '0');
	if(root->rightchild) build(root->rightchild, str + '1');
}

int length;
main() {
	int num=1;
    int n;
	cin>>n;
    while(n--)
    {
        cin>>length;
        vector<int> weightvec(length);
        for(int i = 0; i < length; i++)
            cin >>  weightvec[i];
		Huffman hf(weightvec);
		hf.BuildTree();
		cout << endl;
		hf.BuildCode();//根据建好的树构建编码表
		cout << endl;
		cout<<"Case "<<num<<":"<<endl;
		hf.GetCodeList();//遍历编码表和编码表对应的编码
		num++;
		cout << endl ;
		// hf.PreOrder(hf.Root);//前序遍历输出huffman树看看结果
    }
}
