#pragma warning(disable:4996)
#include <iostream>

#ifndef __CREATEBITREE_H__
#define __CREATEBITREE_H__
using namespace std;

#define NODENUM  100       //定义最大结点数

typedef char elementType;
//树的结点结构
typedef struct btNode
{
	elementType data;   //结点数据域
	struct btNode* lChild, * rChild;

}btNode;

struct node
{
	btNode* btnode;
	node* next;
};

void destroyBtNode(btNode* bt);//前向引用声明

class BinaryTree
{
public:
	btNode* root;
	int nodeCount;
	char strLine[NODENUM][3];
	elementType* btArray;
	int arrayLength;
	void printbtArray();
	int getNode();
	void getFamily();
	void getCommonAncestor();
	void getOnePath(int xNode);
	void getAllPath();
	void btQuestion(int question);
	~BinaryTree() {destroyBtNode(root); delete btArray;}
};

//删除字符串、字符数组左边空格
void BistrLTrim(char* str)
{
	int i, j;
	int n = 0;
	n = strlen(str) + 1;
	for (i = 0; i < n; i++)
	{
		if (str[i] != ' ')  //找到左起第一个非空格位置
			break;
	}
	//以第一个非空格字符为手字符移动字符串
	for (j = 0; j < n; j++)
	{
		str[j] = str[i];
		i++;
	}
}

//数据文件创建二叉树开始-------------------------------------------------------------------------
//********************** 从数据文件创建二叉树 ***********************//
//* 分两步完成：第一步将数据从文本文件读入数组                      *//
//* 第二步从数组递归创建二叉树                                      *//
//* 两步由2个函数完成                                               *//
//*******************************************************************//

//从文本文件数据读入到数组中，同时返回实际结点数量
bool ReadFileToArray(char fileName[], char strLine[NODENUM][3], int & nArrLen)
{
	//读文本文件数据到数组，返回数组及其长度
	FILE* pFile;      //定义二叉树的文件指针
	char str[1000];   //存放读出一行文本的字符串
	char strTemp[10]; //判断是否注释行

	pFile=fopen(fileName,"r");
	if(!pFile)
	{
		cout<<"错误：文件"<<fileName<<"打开失败。"<<endl;
		return false;
	}

	while(fgets(str,1000,pFile)!=NULL)  //跳过空行和注释行
	{
		   //删除字符串左边空格
		BistrLTrim(str);
		if (str[0]=='\n')               //空行，继续读取下一行
			continue;

		strncpy(strTemp,str,2);
		if(strstr(strTemp,"//")!=NULL)  //跳过注释行
			continue;
		else                            //非注释行、非空行，跳出循环
			break;
	}
           //循环结束，str中应该已经是二叉树数据标识"BinaryTree"，判断文件格式
	if(strstr(str,"BinaryTree")==NULL)
	{
		printf("错误：打开的文件格式错误！\n");
		fclose(pFile);           //关闭文件
		return false;
	}


    

	//nArrLen=0;
	//while(fscanf(pFile,"%c  %c  %c\n",&strLine[nArrLen][0],&strLine[nArrLen][1],&strLine[nArrLen][2])!=EOF)	
	//{
		//printf("%c\n",strLine[nArrLen][0]);
	//	nArrLen++;
	//}

	nArrLen=0;     //数组行号初始化为0
	while(fgets(str,1000,pFile)!=NULL)
	{
		    //删除字符串左边空格
		BistrLTrim(str);
		if (str[0]=='\n')  //空行，继续读取下一行
			continue;
		
		strncpy(strTemp,str,2);
		if(strstr(strTemp,"//")!=NULL)  //注释行，跳过，继续读取下一行
			continue;

		char* token=strtok(str," ");   //以空格为分隔符，分割一行数据
		if(token==NULL)  //分割为空串，失败退出
		{
			printf("错误：读取二叉树结点数据失败！\n");
			fclose(pFile); //关闭文件
			return false;
		}
		
		strLine[nArrLen][0]=*token;  //获取结点数据
		token = strtok( NULL, " ");  //读取下一个子串，即此结点的左子树信息
		if(token==NULL)  //分割为空串，失败退出
		{
			printf("错误：读取二叉树结点数据失败！\n");
			fclose(pFile); //关闭文件
			return false;
		}
		strLine[nArrLen][1]=*token;  //获取此结点的左子树信息数据
		token = strtok( NULL, " ");  //读取下一个子串，即此结点的右子树信息
		if(token==NULL)  //分割为空串，失败退出
		{
			printf("错误：读取二叉树结点数据失败！\n");
			fclose(pFile); //关闭文件
			return false;
		}
		strLine[nArrLen][2]=*token;  //获取此结点的右子树信息数据

		nArrLen++;  //数组行号加1	
	}

	fclose(pFile); //关闭文件
	return true;
}


//从数组创建二叉树--数组中保存的是二叉树的先序序列，及每个结点的子树信息
bool CreateBiTreeFromFile(btNode* & pBT, char strLine[NODENUM][3],int nLen, int & nRow)
{
	//strLine[NODENUM][3]--保存节点数据的二维数组
	//nLen--数组长度，即：节点个数
	//nRow--数组当前行号

	if((nRow>=nLen) || (nLen==0))
		return false;  //数据已经处理完毕，或者没有数据，退出

	//根据数组数据递归创建子树
	pBT=new btNode;
	pBT->data=strLine[nRow][0];
	pBT->lChild=NULL;
	pBT->rChild=NULL;
	
	int nRowNext=nRow;  //保留本次递归的行号	

	if(strLine[nRowNext][1]=='1')  //当前结点有左子树，递归创建左子树，读下一行数据
	{
		nRow++;
		CreateBiTreeFromFile(pBT->lChild, strLine,nLen,nRow);
	}

	if(strLine[nRowNext][2]=='1')  //当前结点有右子树，递归创建右子树，读下一行数组
	{
		nRow++;
		CreateBiTreeFromFile(pBT->rChild, strLine,nLen,nRow);		
	}

	return true;
}

//数据文件创建二叉树结束------------------------------------------------------------------------

//销毁二叉树
void destroyBtNode(btNode* bt)
{
	if (bt->lChild != NULL)
		destroyBtNode(bt->lChild);
	else if (bt->rChild != NULL)
		destroyBtNode(bt->rChild);
	else
		delete bt;
}

//获取树高
int getHeight(btNode* bt)
{
	int lHeight = 1, rHeight = 1;
	if (bt->lChild != NULL)
		lHeight = getHeight(bt->lChild) + 1;
	if (bt->rChild != NULL)
		rHeight = getHeight(bt->rChild) + 1;
	return (lHeight >= rHeight) ? lHeight : rHeight;
}

int power(int a, int b)
{
	int multiple = 1;
	if (b == 0)
		return 1;
	while (b >= 1)
	{
		multiple *= a;
		b--;
	}
	return multiple;
}

void linkedToArray(btNode* bt, elementType*& btArray, int i)
{
	btArray[i] = bt->data;
	if (bt->lChild != NULL)
		linkedToArray(bt->lChild, btArray, 2 * i);
	if (bt->rChild != NULL)
		linkedToArray(bt->rChild, btArray, 2 * i + 1);
}

void getBtFileName(char* filename)
{
	while (1)
	{
		cout << "             ___________________________________________________________________________ " << endl;
		cout << "            |                           请选择数据文件                                  |" << endl;
		cout << "            |1.bt4.btr                                                                  |" << endl;
		cout << "            |2.bt8.btr                                                                  |" << endl;
		cout << "            |3.bt9.btr                                                                  |" << endl;
		cout << "            |4.bt10.btr                                                                 |" << endl;
		cout << "            |5.bt12.btr                                                                 |" << endl;
		cout << "            |6.bt14.btr                                                                 |" << endl;
		cout << "            |7.bt15.btr                                                                 |" << endl;
		cout << "            |8.bt21.btr                                                                 |" << endl;
		cout << "            |9.bt261.btr                                                                |" << endl;
		cout << "            |10.bt262.btr                                                               |" << endl;
		cout << "            |11.full4.btr                                                               |" << endl;
		cout << "            |12.full5.btr                                                               |" << endl;
		cout << "            |___________________________________________________________________________|" << endl;
		cout << endl;
		cout << "输入选择的数据文件：";
		int n;
		cin >> n;
		switch (n)
		{
		case 1: { strcpy(filename, "BTdata\\bt4.btr"); return; }
		case 2: { strcpy(filename, "BTdata\\bt8.btr"); return; }
		case 3: { strcpy(filename, "BTdata\\bt9.btr"); return;}
		case 4: { strcpy(filename, "BTdata\\bt10.btr"); return;}
		case 5: { strcpy(filename, "BTdata\\bt12.btr"); return;}
		case 6: { strcpy(filename, "BTdata\\bt14.btr"); return;}
		case 7: { strcpy(filename, "BTdata\\bt15.btr"); return;}
		case 8: { strcpy(filename, "BTdata\\bt21.btr"); return;}
		case 9: { strcpy(filename, "BTdata\\bt261.btr"); return;}
		case 10: { strcpy(filename, "BTdata\\bt262.btr"); return;}
		case 11: { strcpy(filename, "BTdata\\full4.btr"); return;}
		case 12: { strcpy(filename, "BTdata\\full5.btr"); return;}
		default: { cout << "输入无效" << endl; }
		}
	}
}

void BinaryTree::printbtArray()
{
	cout << "二叉树对应的顺序表（\"/\"表示空节点）为：";
	for (int i = 1; i < arrayLength; i++)
	{
		cout << btArray[i] << " ";
	}
	cout << endl;
}

int BinaryTree::getNode()
{
	elementType x;
	cout << "请输入待查找节点的值：";
	cin >> x;
	for (int i = 1; i < arrayLength; i++)
	{
		if (btArray[i] == x)
		{
			return i;
		}
	}
	return 0;

}

void BinaryTree::getFamily()
{
	int xNode = getNode();
	if (xNode == 0)
	{
		cout << "未找到相应节点" << endl;
		return; 
	}
	else if (xNode == 1)
	{
		cout << "该节点为根节点，无父节点和兄弟节点" << endl;
		if (2 * xNode < arrayLength)
		{
			if (btArray[2 * xNode] != '/')
				cout << "该节点的左孩子为：" << btArray[2 * xNode] << endl;
			else
				cout << "该节点左孩子不存在" << endl;
			if (btArray[2 * xNode + 1] != '/')
				cout << "该节点的右孩子为：" << btArray[2 * xNode + 1] << endl;
			else
				cout << "该节点右孩子不存在" << endl;
		}
		else
		{
			cout << "该节点左孩子不存在" << endl;
			cout << "该节点右孩子不存在" << endl;
		}
	}
	else
	{
		cout << "该节点的父节点为：" << btArray[xNode / 2] << endl;
		if (xNode % 2 == 0)
		{
			cout << "该节点是父节点的左孩子" << endl;
			if (btArray[xNode + 1] != '/')
				cout << "该节点的右兄弟为：" << btArray[xNode + 1] << endl;
			else
				cout << "该节点右兄弟不存在" << endl;
		}
		else
		{
			cout << "该节点是父节点的右孩子" << endl;
			if (btArray[xNode - 1] != '/')
				cout << "该节点为的左兄弟为：" << btArray[xNode - 1] << endl;
			else
				cout << "该节点左兄弟不存在" << endl;
		}
		if (2 * xNode < arrayLength)
		{
			if (btArray[2 * xNode] != '/')
				cout << "该节点的左孩子为：" << btArray[2 * xNode] << endl;
			else
				cout << "该节点左孩子不存在" << endl;
			if (btArray[2 * xNode + 1] != '/')
				cout << "该节点的右孩子为：" << btArray[2 * xNode + 1] << endl;
			else
				cout << "该节点右孩子不存在" << endl;
		}
		else
		{
			cout << "该节点左孩子不存在" << endl;
			cout << "该节点右孩子不存在" << endl;
		}
	}
}

void BinaryTree::getCommonAncestor()
{
	int x1Node = getNode();
	if (x1Node == 0) { return; }
	int x2Node = getNode();
	if (x2Node == 0) { return; }
	while (x1Node != x2Node)
	{
		if (x1Node > x2Node)x1Node /= 2;
		else x2Node /= 2;
	}
	cout << "两个结点最近的共同祖先为" << btArray[x1Node] << endl;
}

void BinaryTree::getOnePath(int xNode)
{
	cout << btArray[xNode];
	if (xNode != 1)
		cout << "->";
	else
		return;
	getOnePath(xNode / 2);
}

void BinaryTree::getAllPath()
{
	for (int i = 1; i < arrayLength; i++)
		if (i * 2 > arrayLength)
			if (btArray[i] != '/')
			{
				cout << "节点" << btArray[i] << "到根节点的路径为：";
				getOnePath(i);
				cout << endl;
			}
			else {}
		else if (btArray[2 * i] == '/' && btArray[2 * i + 1] == '/' && btArray[i] != '/')
		{
			cout << "节点" << btArray[i] << "到根节点的路径为：";
			getOnePath(i);
			cout << endl;
		}
}

void BinaryTree::btQuestion(int question)
{
	char filename[20] = "\0";
	getBtFileName(filename);
	int nowRow = 0;
	if (ReadFileToArray(filename, strLine, nodeCount) == true)
	{
		if (CreateBiTreeFromFile(root, strLine, nodeCount, nowRow) == false)
		{
			cout << "创建二叉树过程发生错误！" << endl;
			return;
		}
	}
	else
	{
		cout << "读取文件信息时发生错误！" << endl;
		return;
	}
	arrayLength = power(2, getHeight(root));
	btArray = new elementType[arrayLength];
	for (int i = 1; i < arrayLength; i++)
	{
		btArray[i] = '/';
	}
	linkedToArray(root, btArray, 1);
	switch (question)
	{
	case 1: { printbtArray(); break; }
	case 2: { getFamily(); break; }
	case 3: { getCommonAncestor(); break; }
	case 4: { getAllPath(); break; }
	default: { break; }
	}
}
#endif
