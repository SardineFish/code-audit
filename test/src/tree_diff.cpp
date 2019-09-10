#include "code_audit/compare_tree.h"
#include <iostream>

using namespace CodeAudit;

bool cmpr(const ComparableTree<int>::ChildPtr *a, const ComparableTree<int>::ChildPtr *b)
{
    return (*a)->element == (*b)->element;
}
int main()
{
    void *ptr = (void*)cmpr;
    auto srcTree = new ComparableTree<int>((ComparableTree<int>::Comparer)ptr);
    srcTree->root = new ComparableNode<int>(CMPR_SEQ, 1);
    auto subTree = new ComparableNode<int>(CMPR_SEQ, 1);

    srcTree->root->add(new ComparableNode<int>(CMPR_SEQ, 1));
    srcTree->root->add(subTree);
    subTree->add(new ComparableNode<int>(CMPR_SEQ, 1));
    subTree->add(new ComparableNode<int>(CMPR_SEQ, 0));
    srcTree->root->add(new ComparableNode<int>(CMPR_SEQ, 0));
    srcTree->root->add(new ComparableNode<int>(CMPR_SEQ, 1));

    auto dstTree = new ComparableTree<int>(&cmpr);
    dstTree->root = new ComparableNode<int>(CMPR_SEQ, 1);
    subTree = new ComparableNode<int>(CMPR_SEQ, 1);

    dstTree->root->add(new ComparableNode<int>(CMPR_SEQ, 1));
    dstTree->root->add(subTree);
    subTree->add(new ComparableNode<int>(CMPR_SEQ, 0));
    subTree->add(new ComparableNode<int>(CMPR_SEQ, 1));
    subTree->add(new ComparableNode<int>(CMPR_SEQ, 0));
    subTree->add(new ComparableNode<int>(CMPR_SEQ, 2));
    dstTree->root->add(new ComparableNode<int>(CMPR_SEQ, 0));
    dstTree->root->add(new ComparableNode<int>(CMPR_SEQ, 1));

    srcTree->root->updateSize();
    dstTree->root->updateSize();

    auto similarity =  srcTree->compareTo(dstTree);
    cout << srcTree->compareTo(dstTree) << endl
         << dstTree->compareTo(srcTree) << endl;
}