#include "CreateTree.h"
#include "CreateBiTree.h"
using namespace std;

void menu()
{
	while (1)
	{
		cout << "             ___________________________________________________________________________ " << endl;
		cout << "            |                           请选择要实现的功能                              |" << endl;
		cout << "            |1.将二叉链表存储的二叉树转换为顺序存储形式                                 |" << endl;
		cout << "            |2.求键盘输入元素x的父节点、兄弟结点、子结点                                |" << endl;
		cout << "            |3.求两个结点最近的共同祖先                                                 |" << endl;
		cout << "            |4.输出二叉树从每个叶子结点到根结点的路径                                   |" << endl;
		cout << "            |5.                                                                         |" << endl;
		cout << "            |6.                                                                         |" << endl;
		cout << "            |0.退出。                                                                   |" << endl;
		cout << "            |___________________________________________________________________________|" << endl;
		cout << endl;

		cout << "输入要执行的功能：";
		int n;
		cin >> n;
		switch (n)
		{
		case 1: { BinaryTree BT; BT.btQuestion(1); break; }
		case 2: { BinaryTree BT; BT.btQuestion(2); break; }
		case 3: { BinaryTree BT; BT.btQuestion(3); break; }
		case 4: { BinaryTree BT; BT.btQuestion(4); break; }
		case 5:
		{

			break;
		}
		case 6:
		{

			break;
		}
		case 0:
		{
			return;
			break;
		}
		default:
		{
			cout << "输入无效，请重新输入。" << endl;
			break;
		}
		}
	}
}

int main()
{
    menu();
    return 0;
}