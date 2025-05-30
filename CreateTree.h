#pragma warning(disable:4996)
#include <iostream>

#ifndef __CREATETREE_H__
#define __CREATETREE_H__
using namespace std;

//树（森林）的双亲表示定义和算法--------------------------------------------
#define MAXLEN 100

typedef char elementType;
   //树的结点结构
typedef struct pNode
{
	elementType data;   //结点数据域
	int parent;         //父结点指针（下标）

}PTNode;

    //双亲表示的树（森林）结构
typedef struct pTree
{
	PTNode node[MAXLEN];   //结点数组
	int n;              //结点总数
}pTree;

int firstChild(pTree &T,int v)    //搜索下标为v的结点的第一个孩子结点下标
{
	int w;
	if(v==-1)
		return -1;

	for(w=0;w<T.n;w++)
	{
		if(T.node[w].parent==v)
			return w;
	}
	return -1;
}

//孩子兄弟链表表示定义、创建算法开始---------------------------------------------------
    //树（森林）的孩子兄弟链表表示
typedef char elementType;

typedef struct csNode
{
	elementType data;
	struct csNode *firstChild, *nextSibling;
}csNode,*csTree;

//删除字符串、字符数组左边空格
void strLTrim(char* str)
{
	int i,j;
	int n=0;
	n=(int)strlen(str)+1;
	for(i=0;i<n;i++)
	{
		if(str[i]!=' ')  //找到左起第一个非空格位置
			break;
	}
	    //以第一个非空格字符为手字符移动字符串
	for(j=0;j<n;j++)
	{
		str[j]=str[i];
		i++;
	}
}


//****************** 文件创建双亲表示的树（森林）********************//
//* 函数功能：从文本文件创建双亲表示的图                            *//
//* 入口参数  char fileName[]，数据文件名                           *//
//* 出口参数：pTree &T，即创建的树                                  *//
//* 返 回 值：bool，true创建成功；false创建失败                     *//
//* 函 数 名：CreateTreeFromFile(char fileName[], pTree &T)         *//
//* 备注：本函数使用的数据文件格式以边（父子对）为基本数据          *//
//*******************************************************************//
bool CreateTreeFromFile(char fileName[], pTree &T)
{
	FILE* pFile;     //定义顺序表的文件指针
	char str[1000];  //存放读出一行文本的字符串
	char strTemp[10]; //判断是否注释行

    int i=0,j=0;


	pFile=fopen(fileName,"r");
	if(!pFile)
	{
		printf("错误：文件%s打开失败。\n",fileName);
		return false;
	}
	
	while(fgets(str,1000,pFile)!=NULL)  //跳过空行和注释行
	{
		//删除字符串左边空格
		strLTrim(str);
		if (str[0]=='\n')  //空行，继续读取下一行
			continue;

		strncpy(strTemp,str,2);
		if(strstr(strTemp,"//")!=NULL)  //跳过注释行
			continue;
		else  //非注释行、非空行，跳出循环
			break;
	}

    //循环结束，str中应该已经是文件标识，判断文件格式
	if(strstr(str,"Tree or Forest")==NULL)
	{
		printf("错误：打开的文件格式错误！\n");
		fclose(pFile); //关闭文件
		return false;
	}


	//读取结点数据，到str。跳过空行
	while(fgets(str,1000,pFile)!=NULL)
	{
		//删除字符串左边空格
		strLTrim(str);
		if (str[0]=='\n')  //空行，继续读取下一行
			continue;

		strncpy(strTemp,str,2);
		strTemp[2] = '\0'; // 确保字符串以零终止符结尾
		if(strstr(strTemp,"//")!=NULL)  //注释行，跳过，继续读取下一行
			continue;		
		else  //非空行，也非注释行，即图的顶点元素行
			break;
	}

	//结点数据存入树的结点数组		
	char* token=strtok(str," ");
	int nNum=0;	
	while(token!=NULL)
	{
		T.node[nNum].data=*token;
		T.node[nNum].parent=-1;       //父结点指针初始化为-1
		
		token = strtok( NULL, " ");
        
		nNum++;
	}
	
    //循环读取边（父子队）数据
	int nP;  //父结点数组下标
	int nC;  //子结点数组下标

	elementType Nf,Ns; //父子结点对的两个结点
	while(fgets(str,1000,pFile)!=NULL)
	{
		//删除字符串左边空格
		strLTrim(str);
		if (str[0]=='\n')  //空行，继续读取下一行
			continue;
		
		strncpy(strTemp,str,2);
		strTemp[2] = '\0'; // 确保字符串以零终止符结尾
		if(strstr(strTemp,"//")!=NULL)  //注释行，跳过，继续读取下一行
			continue;

		char* token=strtok(str," ");  //以空格为分隔符，分割一行数据，写入邻接矩阵
		
		if(token==NULL)  //分割为空串，失败退出
		{
			printf("错误：读取树的边数据失败！\n");
			fclose(pFile); //关闭文件
			return false;
		}
		Nf=*token;  //获取父结点
		
		token = strtok( NULL, " ");  //读取下一个子串，即子结点
		if(token==NULL)  //分割为空串，失败退出
		{
			printf("错误：读取树的边数据失败！\n");
			fclose(pFile); //关闭文件
			return false;
		}

		Ns=*token;  //获取边的第二个结点（子结点）
            //取得父结点下标		
		for(nP=0;nP<nNum;nP++)
		{
			if(T.node[nP].data==Nf)  //从顶点列表找到第一个顶点的编号
				break;
		}
           //获取子结点的数组下标		
		for(nC=0;nC<nNum;nC++)
		{
			if(T.node[nC].data==Ns)  //从顶点列表找到第二个顶点的编号
				break;
		}

		T.node[nC].parent=nP;        //nC的父结点的下标为nP
	}

    T.n=nNum;  //树的结点数，即顶点数组的实际大小

	fclose(pFile); //关闭文件
	return true;
}

//搜索双亲表示中，下标w的下一个兄弟结点，返回兄弟结点的下标
int next(pTree T,int w)  
{
	int i;
	for(i=w+1;i<T.n;i++)
	{
		if(T.node[w].parent==T.node[i].parent)
			return i;	
	}
	return -1;
}

//递归创建一棵孩子兄弟链表表示的树
void create(csNode *&T,pTree &T1,int v)
{
	int w;
	T=new csNode;
	T->data=T1.node[v].data;
	T->firstChild=NULL;
	T->nextSibling=NULL;
	w=firstChild(T1,v);  //搜索v的第一个孩子结点
	if(w!=-1)
	{
		create(T->firstChild,T1,w);
	}
	
	w=next(T1,v);       //搜索v的下一个兄弟结点
	if(w!=-1)
	{
		create(T->nextSibling,T1,w);
	}	
}

//从双亲表示的树（森林）创建孩子兄弟链表表示的树（森林）
void createCsTree(csNode *&T,pTree T1)
{
	int i;
	//搜索T1的第一个根结点
	for(i=0;i<T1.n;i++)
	{
		if(T1.node[i].parent==-1)   //找到第一个根结点
			break;		
	}
	if(i<T1.n)
		create(T,T1,i);
}


//孩子兄弟链表表示定义、创建算法结束---------------------------------------------------

void getTreeFileName(char* filename)
{
	while (1)
	{
		cout << "             ___________________________________________________________________________ " << endl;
		cout << "            |                           请选择数据文件                                  |" << endl;
		cout << "            |1.F14.tre                                                                  |" << endl;
		cout << "            |2.F16.tre                                                                  |" << endl;
		cout << "            |3.F18.tre                                                                  |" << endl;
		cout << "            |4.F20.tre                                                                  |" << endl;
		cout << "            |5.tree10.tre                                                               |" << endl;
		cout << "            |6.tree11.tre                                                               |" << endl;
		cout << "            |___________________________________________________________________________|" << endl;
		cout << endl;
		cout << "输入选择的数据文件：";
		int n;
		cin >> n;
		switch (n)
		{
		case 1: { strcpy(filename, "tData\\F14.tre"); return; }
		case 2: { strcpy(filename, "tData\\F16.tre"); return; }
		case 3: { strcpy(filename, "tData\\F18.tre"); return; }
		case 4: { strcpy(filename, "tData\\F20.tre"); return; }
		case 5: { strcpy(filename, "tData\\tree10.tre"); return; }
		case 6: { strcpy(filename, "tData\\tree11.tre"); return; }
		default: { cout << "输入无效" << endl; }
		}
	}
}

void getTreeDegree(csNode* csT, int& maxDegree, int nowDegree)
{
	if (csT->firstChild != NULL)
		getTreeDegree(csT->firstChild, maxDegree, 1);
	if (csT->nextSibling != NULL)
	{
		if (nowDegree + 1 > maxDegree)
			maxDegree = nowDegree + 1;
		getTreeDegree(csT->nextSibling, maxDegree, nowDegree + 1);
	}
}

int getDegree(csNode* csT)
{
	int degree = 0;
	while (csT != NULL)
	{
		int maxDegree = 0;
		getTreeDegree(csT, maxDegree, 1);
		if (maxDegree > degree)
			degree = maxDegree;
		csT = csT->nextSibling;
	}
	return degree;
}

void printCsTree(csNode* bt)
{
	if (bt == NULL)
		return;
	cout << bt->data;
	if (bt->firstChild != NULL)
	{
		cout << "(";
		printCsTree(bt->firstChild);
		cout << ")";
	}
	if (bt->nextSibling != NULL)
	{
		cout << ",";
		printCsTree(bt->nextSibling);
	}
}

void printCsTreeToGT(csNode* bt)
{
	if (bt != NULL)
	{
		cout << bt->data;
		cout << "(";
		printCsTree(bt->firstChild);
		cout << ")";
		if (bt->nextSibling != NULL)
		{
			cout << ",  ";
			printCsTreeToGT(bt->nextSibling);
		}
	}
}

void treeQuestion(int question)
{
	pTree T;
	csNode* csT;
	char filename[20] = "\0";
	getTreeFileName(filename);
	if (CreateTreeFromFile(filename, T) == true)
	{
		createCsTree(csT, T);
		if (question == 1)
		{
			cout << "树的度为：" << getDegree(csT) << endl;
		}	
		if (question == 2)
		{
			cout << "广义表表示的树（森林）为：";
			printCsTreeToGT(csT);
			cout << endl;	
		}
			
	}
	else
	{
		cout << "读取文件信息时发生错误！" << endl;
	}
}

#endif
