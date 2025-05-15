#pragma warning(disable:4996)
#include <iostream>

#ifndef __CREATEBITREE_H__
#define __CREATEBITREE_H__
using namespace std;

#define NODENUM  100       //�����������

typedef char elementType;
//���Ľ��ṹ
typedef struct btNode
{
	elementType data;   //���������
	struct btNode* lChild, * rChild;

}btNode;

struct node
{
	btNode* btnode;
	node* next;
};

void destroyBtNode(btNode* bt);//ǰ����������

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

//ɾ���ַ������ַ�������߿ո�
void BistrLTrim(char* str)
{
	int i, j;
	int n = 0;
	n = strlen(str) + 1;
	for (i = 0; i < n; i++)
	{
		if (str[i] != ' ')  //�ҵ������һ���ǿո�λ��
			break;
	}
	//�Ե�һ���ǿո��ַ�Ϊ���ַ��ƶ��ַ���
	for (j = 0; j < n; j++)
	{
		str[j] = str[i];
		i++;
	}
}

//�����ļ�������������ʼ-------------------------------------------------------------------------
//********************** �������ļ����������� ***********************//
//* ��������ɣ���һ�������ݴ��ı��ļ���������                      *//
//* �ڶ���������ݹ鴴��������                                      *//
//* ������2���������                                               *//
//*******************************************************************//

//���ı��ļ����ݶ��뵽�����У�ͬʱ����ʵ�ʽ������
bool ReadFileToArray(char fileName[], char strLine[NODENUM][3], int & nArrLen)
{
	//���ı��ļ����ݵ����飬�������鼰�䳤��
	FILE* pFile;      //������������ļ�ָ��
	char str[1000];   //��Ŷ���һ���ı����ַ���
	char strTemp[10]; //�ж��Ƿ�ע����

	pFile=fopen(fileName,"r");
	if(!pFile)
	{
		cout<<"�����ļ�"<<fileName<<"��ʧ�ܡ�"<<endl;
		return false;
	}

	while(fgets(str,1000,pFile)!=NULL)  //�������к�ע����
	{
		   //ɾ���ַ�����߿ո�
		BistrLTrim(str);
		if (str[0]=='\n')               //���У�������ȡ��һ��
			continue;

		strncpy(strTemp,str,2);
		if(strstr(strTemp,"//")!=NULL)  //����ע����
			continue;
		else                            //��ע���С��ǿ��У�����ѭ��
			break;
	}
           //ѭ��������str��Ӧ���Ѿ��Ƕ��������ݱ�ʶ"BinaryTree"���ж��ļ���ʽ
	if(strstr(str,"BinaryTree")==NULL)
	{
		printf("���󣺴򿪵��ļ���ʽ����\n");
		fclose(pFile);           //�ر��ļ�
		return false;
	}


    

	//nArrLen=0;
	//while(fscanf(pFile,"%c  %c  %c\n",&strLine[nArrLen][0],&strLine[nArrLen][1],&strLine[nArrLen][2])!=EOF)	
	//{
		//printf("%c\n",strLine[nArrLen][0]);
	//	nArrLen++;
	//}

	nArrLen=0;     //�����кų�ʼ��Ϊ0
	while(fgets(str,1000,pFile)!=NULL)
	{
		    //ɾ���ַ�����߿ո�
		BistrLTrim(str);
		if (str[0]=='\n')  //���У�������ȡ��һ��
			continue;
		
		strncpy(strTemp,str,2);
		if(strstr(strTemp,"//")!=NULL)  //ע���У�������������ȡ��һ��
			continue;

		char* token=strtok(str," ");   //�Կո�Ϊ�ָ������ָ�һ������
		if(token==NULL)  //�ָ�Ϊ�մ���ʧ���˳�
		{
			printf("���󣺶�ȡ�������������ʧ�ܣ�\n");
			fclose(pFile); //�ر��ļ�
			return false;
		}
		
		strLine[nArrLen][0]=*token;  //��ȡ�������
		token = strtok( NULL, " ");  //��ȡ��һ���Ӵ������˽�����������Ϣ
		if(token==NULL)  //�ָ�Ϊ�մ���ʧ���˳�
		{
			printf("���󣺶�ȡ�������������ʧ�ܣ�\n");
			fclose(pFile); //�ر��ļ�
			return false;
		}
		strLine[nArrLen][1]=*token;  //��ȡ�˽�����������Ϣ����
		token = strtok( NULL, " ");  //��ȡ��һ���Ӵ������˽�����������Ϣ
		if(token==NULL)  //�ָ�Ϊ�մ���ʧ���˳�
		{
			printf("���󣺶�ȡ�������������ʧ�ܣ�\n");
			fclose(pFile); //�ر��ļ�
			return false;
		}
		strLine[nArrLen][2]=*token;  //��ȡ�˽�����������Ϣ����

		nArrLen++;  //�����кż�1	
	}

	fclose(pFile); //�ر��ļ�
	return true;
}


//�����鴴��������--�����б�����Ƕ��������������У���ÿ������������Ϣ
bool CreateBiTreeFromFile(btNode* & pBT, char strLine[NODENUM][3],int nLen, int & nRow)
{
	//strLine[NODENUM][3]--����ڵ����ݵĶ�ά����
	//nLen--���鳤�ȣ������ڵ����
	//nRow--���鵱ǰ�к�

	if((nRow>=nLen) || (nLen==0))
		return false;  //�����Ѿ�������ϣ�����û�����ݣ��˳�

	//�����������ݵݹ鴴������
	pBT=new btNode;
	pBT->data=strLine[nRow][0];
	pBT->lChild=NULL;
	pBT->rChild=NULL;
	
	int nRowNext=nRow;  //�������εݹ���к�	

	if(strLine[nRowNext][1]=='1')  //��ǰ��������������ݹ鴴��������������һ������
	{
		nRow++;
		CreateBiTreeFromFile(pBT->lChild, strLine,nLen,nRow);
	}

	if(strLine[nRowNext][2]=='1')  //��ǰ��������������ݹ鴴��������������һ������
	{
		nRow++;
		CreateBiTreeFromFile(pBT->rChild, strLine,nLen,nRow);		
	}

	return true;
}

//�����ļ���������������------------------------------------------------------------------------

//���ٶ�����
void destroyBtNode(btNode* bt)
{
	if (bt->lChild != NULL)
		destroyBtNode(bt->lChild);
	else if (bt->rChild != NULL)
		destroyBtNode(bt->rChild);
	else
		delete bt;
}

//��ȡ����
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
		cout << "            |                           ��ѡ�������ļ�                                  |" << endl;
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
		cout << "����ѡ��������ļ���";
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
		default: { cout << "������Ч" << endl; }
		}
	}
}

void BinaryTree::printbtArray()
{
	cout << "��������Ӧ��˳���\"/\"��ʾ�սڵ㣩Ϊ��";
	for (int i = 1; i < arrayLength; i++)
	{
		cout << btArray[i] << " ";
	}
	cout << endl;
}

int BinaryTree::getNode()
{
	elementType x;
	cout << "����������ҽڵ��ֵ��";
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
		cout << "δ�ҵ���Ӧ�ڵ�" << endl;
		return; 
	}
	else if (xNode == 1)
	{
		cout << "�ýڵ�Ϊ���ڵ㣬�޸��ڵ���ֵܽڵ�" << endl;
		if (2 * xNode < arrayLength)
		{
			if (btArray[2 * xNode] != '/')
				cout << "�ýڵ������Ϊ��" << btArray[2 * xNode] << endl;
			else
				cout << "�ýڵ����Ӳ�����" << endl;
			if (btArray[2 * xNode + 1] != '/')
				cout << "�ýڵ���Һ���Ϊ��" << btArray[2 * xNode + 1] << endl;
			else
				cout << "�ýڵ��Һ��Ӳ�����" << endl;
		}
		else
		{
			cout << "�ýڵ����Ӳ�����" << endl;
			cout << "�ýڵ��Һ��Ӳ�����" << endl;
		}
	}
	else
	{
		cout << "�ýڵ�ĸ��ڵ�Ϊ��" << btArray[xNode / 2] << endl;
		if (xNode % 2 == 0)
		{
			cout << "�ýڵ��Ǹ��ڵ������" << endl;
			if (btArray[xNode + 1] != '/')
				cout << "�ýڵ�����ֵ�Ϊ��" << btArray[xNode + 1] << endl;
			else
				cout << "�ýڵ����ֵܲ�����" << endl;
		}
		else
		{
			cout << "�ýڵ��Ǹ��ڵ���Һ���" << endl;
			if (btArray[xNode - 1] != '/')
				cout << "�ýڵ�Ϊ�����ֵ�Ϊ��" << btArray[xNode - 1] << endl;
			else
				cout << "�ýڵ����ֵܲ�����" << endl;
		}
		if (2 * xNode < arrayLength)
		{
			if (btArray[2 * xNode] != '/')
				cout << "�ýڵ������Ϊ��" << btArray[2 * xNode] << endl;
			else
				cout << "�ýڵ����Ӳ�����" << endl;
			if (btArray[2 * xNode + 1] != '/')
				cout << "�ýڵ���Һ���Ϊ��" << btArray[2 * xNode + 1] << endl;
			else
				cout << "�ýڵ��Һ��Ӳ�����" << endl;
		}
		else
		{
			cout << "�ýڵ����Ӳ�����" << endl;
			cout << "�ýڵ��Һ��Ӳ�����" << endl;
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
	cout << "�����������Ĺ�ͬ����Ϊ" << btArray[x1Node] << endl;
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
				cout << "�ڵ�" << btArray[i] << "�����ڵ��·��Ϊ��";
				getOnePath(i);
				cout << endl;
			}
			else {}
		else if (btArray[2 * i] == '/' && btArray[2 * i + 1] == '/' && btArray[i] != '/')
		{
			cout << "�ڵ�" << btArray[i] << "�����ڵ��·��Ϊ��";
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
			cout << "�������������̷�������" << endl;
			return;
		}
	}
	else
	{
		cout << "��ȡ�ļ���Ϣʱ��������" << endl;
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
