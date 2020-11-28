
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include <unistd.h>

#include "ntree.h"

#include "min-max.h"
//----------------------------------------
NTree
ntree_new ()
{
    return NULL;
}

//----------------------------------------


NTree
ntree_create (const void *data, size_t size, size_t arity)
{
    NTree tree = (NTree) malloc (sizeof (NTree *) + sizeof (size_t) + size);
    if (tree)
    {
        tree->subtrees = (NTree *) malloc (arity * sizeof(NTree));
        if (tree->subtrees)
        {
            size_t i;

            for (i = 0; i < arity; i++)
                tree->subtrees[i] = NULL;
            tree->arity = arity;
            memcpy (tree->data, data, size);
        }
    }
    else
    {
        free (tree);
        tree = NULL;
    }

    return tree;
}
//----------------------------------------


void
ntree_delete (NTree tree, void (*deletef) (void *))
{
    if (tree)
    {
        size_t i;

        for (i = 0; i < tree->arity; i++)
            ntree_delete (tree->subtrees[i], deletef);
        if (deletef)
            deletef (tree->data);
        free (tree);
    }
}


//----------------------------------------

void *ntree_get_data(NTree tree) {
    if (tree) {
        return tree->data;
    }
    return NULL;
}
//----------------------------------------

bool ntree_set_nth(NTree tree, NTree sub, size_t nth) {
    if (tree && nth <= tree->arity && nth > 0) {
        //Le '-1' est ici car nous voulons le xeme element, mais
        //nos pointers commencent a 0.
        tree->subtrees[nth-1] = sub;
        return true;
    }
    return false;
}
//----------------------------------------

bool ntree_set_data(NTree tree, const void *data, size_t size) {
    if (tree) {
        memcpy(tree->data, data, size);
        return true;
    }
    return false;

}
//----------------------------------------

// profondeur maximale
size_t ntree_height(NTree tree) {
    if (tree) {
        int     index;
        size_t  maxHeight;

        maxHeight = index = 0;
        while (index < tree->arity && tree->subtrees[index]) {
            if (tree->subtrees[index])
                maxHeight = MAX(maxHeight, ntree_height(tree->subtrees[index]));

            index++;
        }
        return 1 + maxHeight;
    }
    return 0;
}
//----------------------------------------

// nombres d'élement
size_t ntree_size(NTree tree) {
    if (tree) {
        int     index;
        size_t  totalValue;

        totalValue = index = 0;
        while (index < tree->arity)
            totalValue += ntree_size(tree->subtrees[index++]);
        return 1 + totalValue;
    }
    return 0;
}

//----------------------------------------

void ntree_pre_order(NTree tree, void (*func)(void *, void *), void *extra_data) {
    if (tree) {
        int index;

        index = 0;
        func(tree->data, extra_data);
        while (index < tree->arity)
            ntree_pre_order(tree->subtrees[index++], func, extra_data);
    }
}
//----------------------------------------

void ntree_post_order(NTree tree, void (*func)(void *, void *), void *extra_data) {
    if (tree) {
        int index;

        index = 0;
        while (index < tree->arity)
            ntree_post_order(tree->subtrees[index++], func, extra_data);
        func(tree->data, extra_data);
    }
}
//----------------------------------------

void ntree_in_order(NTree tree, void (*func)(void *, void *), void *extra_data, size_t nth) {
    if (tree) {
        int index;

        index = 0;
        while (index < tree->arity) {
            //Le '-1' est ici car nous voulons le xeme element, mais
            //nos pointers commencent a 0.
            //Dans le cas d'une nTree possedant 2 subTree, nth=2
            //donnerai le meme resultat qu'un arbre binaire.
            //tout l'arbre du premier element -> racine -> second element
            if (index == (nth - 1))
                func(tree->data, extra_data);
            ntree_post_order(tree->subtrees[index++], func, extra_data);
        }
    }
}
//----------------------------------------

