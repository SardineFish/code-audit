#pragma once

#include "code_audit/diff.h"
#include <vector>

using namespace std;

namespace CodeAudit
{

enum NodeType
{
    CMPR_SEQ,
    CMPR_SET,
};

template <typename T>
class ComparableNode
{
private:
    vector<ComparableNode<T> *> *children = new vector<ComparableNode<T> *>;
    int size = 0;

public:
    typedef ComparableNode<T> *ChildPtr;
    typedef bool (*Comparer)(const ChildPtr *, const ChildPtr *);
    NodeType type;
    T element;
    ComparableNode(NodeType type, T element) : type(type), element(element){}
    ~ComparableNode()
    {
        delete this->children;
    }
    void add(ComparableNode<T> *child)
    {
        this->children->push_back(child);
        this->size += child->size;
    }
    int updateSize()
    {
        if (this->children->size() == 0)
        {
            return this->size = 1;
        }
        this->size = 0;
        for (auto &child : *(this->children))
        {
            this->size += child->updateSize();
        }
        return this->size;
    }
    double compareTo(ComparableNode<T> *target, Comparer cmpr);
};

template <typename T>
class ComparableTree
{
public:
    typedef ComparableNode<T> *ChildPtr;
    typedef bool (*Comparer)(const ChildPtr *, const ChildPtr *);
    ComparableNode<T> *root;
    Comparer cmpr;
    ComparableTree(Comparer cpr)
    {
        this->cmpr = cpr;
    }
    double compareTo(ComparableTree<T>* target)
    {
        return this->root->compareTo(target->root, this->cmpr);
    }
};

template <typename T>
double ComparableNode<T>::compareTo(ComparableNode<T> *target, Comparer cmpr)
{
    if(this->children->size()==0 && target->children->size()==0)
        return 1;
    if (this->type == CMPR_SEQ && target->type == CMPR_SEQ)
    {
        vector<DiffChanges> results;
        vector<ComparableNode<T> *> src = *(this->children);
        vector<ComparableNode<T> *> dst = *(target->children);
        diff<ComparableNode<T> *>(src, dst, results, cmpr);
        mergeChanges(results);
        int i = 0, j = 0;
        int totalWeight = 0;
        for (auto &change : results)
        {
            if (change == DIFF_ADD)
            {
                totalWeight += target->children->at(j)->size;
                j++;
            }
            else if (change == DIFF_DEL)
            {
                totalWeight += this->children->at(i)->size;
                i++;
            }
            else
            {
                totalWeight += max(this->children->at(i)->size, target->children->at(j)->size);
                i++, j++;
            }
        }
        i = 0, j = 0;
        double similarity = 0;
        for (auto &change : results)
        {
            if (change == DIFF_RPL)
                i++, j++;
            else if (change == DIFF_ADD)
                j++;
            else if (change == DIFF_DEL)
                i++;
            else
            {
                double childSimilarity = this->children->at(i)->compareTo(target->children->at(j), cmpr);
                similarity += childSimilarity * (double)max((this->children->at(i)->size), target->children->at(j)->size) / (double)totalWeight;
                i++, j++;
            }
        }
        return similarity;
    }
    else
    {
        double similarity = 0;
        for (auto &srcChild : *(this->children))
        {
            double maxSimilarity = 0;
            ComparableNode<T> *similarNode = nullptr;
            for (auto &dstChild : *(target->children))
            {
                double sim = srcChild->compareTo(dstChild, cmpr);
                if (sim > maxSimilarity)
                {
                    similarNode = dstChild;
                    maxSimilarity = sim;
                }
            }
            if (similarNode != nullptr)
            {
                similarity += maxSimilarity * (double)similarNode->size / (double)this->size;
            }
        }
        return similarity;
        /* code */
    }
}

} // namespace CodeAudit
