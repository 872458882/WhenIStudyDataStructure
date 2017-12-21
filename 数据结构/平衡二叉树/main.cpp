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
	
    cout << "\n== ǰ�����: ";
    tree->preOrder();

    cout << "\n== �������: ";
    tree->inOrder();

    cout << "\n== �������: ";
    tree->postOrder();
    cout << endl;

    cout << "== �߶�: " << tree->height() << endl;
    cout << "== ��Сֵ: " << tree->minimum() << endl;
    cout << "== ���ֵ: " << tree->maximum() << endl;
    cout << "== ������ϸ��Ϣ: " << endl;
    tree->print();

    i = 8;
    cout << "\n== ɾ�����ڵ�: " << i;
    tree->remove(i);

    cout << "\n== �߶�: " << tree->height() ;
    cout << "\n== �������: " ;
    tree->inOrder();
    cout << "\n== ������ϸ��Ϣ: " << endl;
    tree->print();

    // ���ٶ�����
    tree->destroy();

    return 0;
}
