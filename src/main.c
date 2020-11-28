#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "tree.h"
#include "ntree.h"

void monPrintF (void * a, void * b){
    printf("Valeur du noeud : %d\n", *(int*)a);
}

/**
 * Test réalisés pour les arbres binaires
 * Affichage des résultats des tris
 */
void testArbresBinaires(void){
    int i = 5, j = 10, k = 15, m = 20;
    size_t sizeInt = sizeof(int);

    Tree racine = tree_create(&i, sizeInt);
    Tree fils1 = tree_create(&j, sizeInt);
    Tree fils2 = tree_create(&k, sizeInt);

    tree_set_left(racine, fils1);
    tree_set_right(racine, fils2);

    Tree fils1fils1 = tree_create(&m, sizeInt);
    Tree fils2fils1 = tree_create(&i, sizeInt);

    tree_set_left(fils1, fils1fils1);
    tree_set_right(fils1, fils2fils1);

    printf("Tri pre-order : \n");
    tree_pre_order(racine, monPrintF, NULL);

    printf("\nTri post-order : \n");
    tree_post_order(racine, monPrintF, NULL);

    printf("\nTri in-order : \n");
    tree_in_order(racine, monPrintF, NULL);
}

/**
 * Tests réalisés pour les arbres n-aires
 * N'affiche rien mais est basé sur des anticipations de valeurs
 * pour réaliser des pseudos tests unitaires
 * Et affichage final des valeurs des tris
 */
void testArbresNAires(void){
    int i = 5, j = 10, k = 15, m = 20, n = 25, o = 30;
    size_t sizeInt = sizeof(int);
    printf("\ntoto1\n");

    NTree racine = ntree_create(&i, sizeInt, 5);
    NTree fils1 = ntree_create(&j, sizeInt, 2);
    NTree fils2 = ntree_create(&k, sizeInt, 2);
    NTree fils3 = ntree_create(&m, sizeInt, 2);
    NTree fils4 = ntree_create(&n, sizeInt, 2);
    NTree fils5 = ntree_create(&o, sizeInt, 2);

    // Tests d'exemples
    assert(10 == *(int*)fils1->data);
    assert(15 == *(int*)fils2->data);
    assert(20 == *(int*)fils3->data);
    assert(25 == *(int*)fils4->data);

    assert(10 == *(int*)ntree_get_data(fils1));
    assert(15 == *(int*)ntree_get_data(fils2));
    assert(20 == *(int*)ntree_get_data(fils3));
    assert(25 == *(int*)ntree_get_data(fils4));

    assert(racine->arity == 5);

    assert(NULL == racine->subtrees[0]);
    assert(NULL == racine->subtrees[1]);
    assert(NULL == racine->subtrees[2]);
    assert(NULL == racine->subtrees[3]);
    assert(NULL == racine->subtrees[4]);

    ntree_set_nth(racine, fils1, 1);
    ntree_set_nth(racine, fils2, 2);
    ntree_set_nth(racine, fils3, 3);
    ntree_set_nth(racine, fils4, 4);
    ntree_set_nth(racine, fils5, 5);

    assert(*(int*)racine->subtrees[0]->data == 10);
    assert(*(int*)racine->subtrees[1]->data == 15);
    assert(*(int*)racine->subtrees[2]->data == 20);
    assert(*(int*)racine->subtrees[3]->data == 25);
    assert(*(int*)racine->subtrees[4]->data == 30);

    ntree_set_data(fils1, &o ,sizeInt);
    ntree_set_data(fils2, &o ,sizeInt);
    ntree_set_data(fils3, &o ,sizeInt);
    ntree_set_data(fils4, &o ,sizeInt);

    assert(30 == *(int*)ntree_get_data(fils1));
    assert(30 == *(int*)ntree_get_data(fils2));
    assert(30 == *(int*)ntree_get_data(fils3));
    assert(30 == *(int*)ntree_get_data(fils4));

    assert(6 == ntree_size(racine));
    NTree fils1fils1 = ntree_create(&i, sizeInt, 1);
    NTree fils2fils2 = ntree_create(&j, sizeInt, 0);

    ntree_set_nth(fils1, fils1fils1, 1);
    ntree_set_nth(fils1, fils2fils2, 2);

    assert(8 == ntree_size(racine));
    assert(2 == ntree_height(fils1));
    assert(3 == ntree_height(racine));

    NTree fils1fils1fils1 = ntree_create(&i, sizeInt, 0);
    ntree_set_nth(fils1fils1, fils1fils1fils1, 1);
    assert(4 == ntree_height(racine));
    assert(3 == ntree_height(fils1));

    printf("\nTri pre-order : \n");
    ntree_pre_order(racine, monPrintF, NULL);

    printf("\nTri post-order : \n");
    ntree_post_order(racine, monPrintF, NULL);

    printf("\nTri in-order : \n");
    ntree_in_order(racine, monPrintF, NULL, 3);

}

int main(){

    testArbresBinaires();
    testArbresNAires();

    return EXIT_SUCCESS;
}
