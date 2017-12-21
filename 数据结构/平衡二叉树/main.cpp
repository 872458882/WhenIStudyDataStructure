#include <iostream>
#include "AVLTree.h"
using namespace std;

int main()
{
	int x;
    int i;
    AVLTree<int>* tree=new AVLTree<int>();
	while(cin>>x&&x!=9999)    
    {
    	tree->Insert(x);
	}
	
    cout << "\n== 前序遍历: ";
    tree->preOrder();

    cout << "\n== 中序遍历: ";
    tree->inOrder();

    cout << "\n== 后序遍历: ";
    tree->postOrder();
    cout << endl;

    cout << "== 高度: " << tree->height() << endl;
    cout << "== 最小值: " << tree->minimum() << endl;
    cout << "== 最大值: " << tree->maximum() << endl;
    cout << "== 树的详细信息: " << endl;
    tree->print();

    i = 8;
    cout << "\n== 删除根节点: " << i;
    tree->remove(i);

    cout << "\n== 高度: " << tree->height() ;
    cout << "\n== 中序遍历: " ;
    tree->inOrder();
    cout << "\n== 树的详细信息: " << endl;
    tree->print();

    // 销毁二叉树
    tree->destroy();

    return 0;
}
