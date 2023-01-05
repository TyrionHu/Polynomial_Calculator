/*
 * @Description: 
 * @Version: 
 * @Author: Tyrion Huu
 * @Date: 2022-09-14 21:45:01
 * @LastEditors: Tyrion Huu
 * @LastEditTime: 2022-09-17 14:53:34
 */
#include "user.h"

Status Count(Node * head)
{
    if(head == NULL) return DONE;
    unsigned int counter = 0;
    Node * p = head->next;
    while(p != NULL)
    {
        p = p->next;
        counter++;
    }
    head->coefficient = counter;
    return DONE;
}
//Return the head pointer.
Node * InitialiseList(void)
{
    Node * head = (Node *)malloc(sizeof(Node));
    if(head == NULL) exit(ERROR);
    head->coefficient = 0;
    head->power = -1;
    head->next = NULL;
    return head;
}

void Swap(Node * p, Node * q) 
{
	int temporary = p->coefficient;
	p->coefficient = q->coefficient;
	q->coefficient = temporary;

    temporary = p->power;
    p->power = q->power;
    q->power = temporary;
    return;
}

void BubbleSort(Node * head) 
{
    if(head == NULL) return;
    Node * p = head;
    for(int i = 0; i < head->coefficient; i++)
    {
        p = head;
        for(int j = 0; j < head->coefficient - i - 1; j++)
        {
            p = p->next;
            if(p->power < p->next->power) Swap(p, p->next); 
        }
    }
    return;
}

//Insert a node and place it with a descending sequence.
Status InsertNode(Node * head, double coefficient, long power)
{
    if(coefficient == 0) return DONE;
    if(head == NULL) head = InitialiseList();

    Node * p = head;
    while(p->next != NULL && p->power < power) p = p->next;
    if(p->power == power)
    {
        p->coefficient += coefficient;
        if(p->coefficient == 0)
        {
            Node * q = head;
            while(q->next != p) q = q->next;
            q->next = p->next;
            delete p;
            head->coefficient--;
        }
        return DONE;
    }

    Node * pNewNode = new Node;
    if(pNewNode == NULL) return OVERFLOW;

    pNewNode->coefficient = coefficient;
    pNewNode->power = power;
    pNewNode->next = NULL;
    if(p->next == NULL) 
    {
        p->next = pNewNode;
        head->coefficient++;
        return DONE;
    }
    else
    {
        pNewNode->next = p->next;
        p->next = pNewNode;
        head->coefficient++;
        return DONE;
    }
}

Status CopyFromA(Node * headA, Node * headB)
{
    if(headB == NULL) Node * headB = InitialiseList();
    if(headA == NULL) return 0;
    Node * p = headA, * q = headB;
    while(p->next != NULL)
    {
        p = p->next;
        q->next = InitialiseList();
        q = q->next;
        q->coefficient = p->coefficient;
        q->power = p->power;
    }
    return DONE;
}

//Input the polynomial with this format: c e c e c e… c is a double, and e is a long. No sequence required.
Status InputAPolynomial(Node * head)
{
    long power = 0;
    double coefficient = 0.0;
    for(int i = 1; ; i++)
    {
        if(!(std::cin >> coefficient)) break;
        int t = getchar();
        if(t == 10 || t == 13) break;
        if(!(std::cin >> power)) break;
        InsertNode(head, coefficient, power);
        t = getchar();
        if(t == 10 || t == 13) break;
    }
    BubbleSort(head);
    return DONE;
}

//Print the polynomial with a descending order.
Status PrintPolynomial(Node * head)
{
    if(head == NULL) 
    {
        std::cout << "NULL" << std::endl;
        return DONE;
    }
    Count(head);
    BubbleSort(head);
    Node * pointer = head->next;
    std::cout << (int) head->coefficient << ", ";
    while(pointer != NULL)
    {
        std::cout << pointer->coefficient << ", " << pointer->power << ", ";
        pointer = pointer->next;
    }
    std::cout << std::endl;
    return DONE;
}

//Return the head of the result linked-list. If it returns NULL, it means it fails to allocate a place.
Status A_Add_B_Polynomial(Node * headA, Node * headB, Node * head_new)
{
    if(headA != NULL && headB == NULL)
    {
        CopyFromA(headA, head_new);
        return DONE;
    }
    else if(headB != NULL && headA == NULL)
    {
        CopyFromA(headB, head_new);
        return DONE;
    }
    else if(headB == headA && headA == NULL)
    {
        return DONE;
    }
    Node * pA = headA->next, * pB = headB->next, * pOut = head_new;
    while(pA != NULL && pB != NULL)
    {
        Node * p = new Node;
        if(pA->power > pB->power)
        {
            *p = *pA;
            pOut->next = p;
            pA = pA->next;
            pOut = pOut->next;
        }
        else if(pA->power < pB->power)
        {
            *p = *pB;
            pOut->next = p;
            pB = pB->next;
            pOut = pOut->next;
        }
        else
        {
            if(pA->coefficient + pB->coefficient != 0)
            {
                p->coefficient = pA->coefficient + pB->coefficient;
                p->power = pA->power;
                pOut->next = p;
                pOut = pOut->next;
            }

            pA = pA->next;
            pB = pB->next;
        }
        pOut->next = NULL;
        if(pOut != p) delete p;

    }

    if(pA != NULL)
    {
        while(pA != NULL)
        {
            Node * p = new Node;
            *p = *pA;
            pOut->next = p;
            pA = pA->next;
            pOut = pOut->next;
            pOut->next = NULL;
        }
    }

    if(pB != NULL)
    {
        while(pB != NULL)
        {
            Node * p = new Node;
            *p = *pB;
            pOut->next = p;
            pB = pB->next;
            pOut = pOut->next;
            pOut->next = NULL;
        }
    }
    return DONE;
}

//Return the head of the result linked-list. If it returns NULL, it means it fails to allocate a place.
Status A_Minus_B_Polynomial(Node * headA, Node * headB, Node * head_new)
{
    head_new->coefficient = 0;
    head_new->next = NULL;
    head_new->power = 0;
    if(head_new == NULL) return OVERFLOW;

    Node * pA = headA->next, * pB = headB->next, * pOut = head_new;
    while(pA != NULL && pB != NULL)
    {
        Node * p = new Node;
        if(pA->power > pB->power)
        {
            *p = *pA;
            pOut->next = p;
            pA = pA->next;
            pOut = pOut->next;
        }
        else if(pA->power < pB->power)
        {
            *p = *pB;
            pOut->next = p;
            pB = pB->next;
            pOut = pOut->next;
        }
        else
        {
            if(pA->coefficient - pB->coefficient != 0)
            {
                p->coefficient = pA->coefficient - pB->coefficient;
                p->power = pA->power;
                pOut->next = p;
                pOut = pOut->next;
            }

            pA = pA->next;
            pB = pB->next;
        }
        pOut->next = NULL;
        if(pOut != p) delete p;

    }

    if(pA != NULL)
    {
        while(pA != NULL)
        {
            Node * p = new Node;
            *p = *pA;
            pOut->next = p;
            pA = pA->next;
            pOut = pOut->next;
            pOut->next = NULL;
        }
    }

    if(pB != NULL)
    {
        while(pB != NULL)
        {
            Node * p = new Node;
            *p = *pB;
            p->coefficient = -p->coefficient;
            pOut->next = p;
            pB = pB->next;
            pOut = pOut->next;
            pOut->next = NULL;
        }
    }
    Count(head_new);
    BubbleSort(head_new);
    return DONE;
}

double CalculateValue(Node * head, double x)
{
    double outcome = 0;
    Node * p = head->next;
    while(p != NULL)
    {
        outcome += p->coefficient * pow(x, p->power);
        p = p->next;
    }
    return outcome;
}

Status CalculateDerivative(Node * head, Node * head_new)
{
    Node * p = head->next;
    while(p!= NULL && p->power != 0)
    {
        InsertNode(head_new, p->coefficient * p->power, p->power - 1);
        p = p->next;
    }
    Count(head_new);
    return DONE;
}

Node * MonomialMultiplyPolynomial(Node * pointer, Node * head)
{
    if(head->next == NULL) return NULL;

    if(pointer == NULL) return NULL;
    Node * head_outcome = InitialiseList(); 
    Node * p = head->next;
    while(p != NULL)
    {
        InsertNode(head_outcome, pointer->coefficient * p->coefficient, pointer->power + p->power);
        p = p->next;
    }
    return head_outcome;
}

Status FreeList(Node * head)
{
    if(head == NULL) return DONE;
    Node * p = head->next;
    while(head->next != NULL)
    {
        p = head->next;
        head->next = head->next->next;
        delete p;
    }
    return DONE;
}

Node * MultiplyPolynomial(Node * headA, Node * headB)
{
    if(headA->next == NULL || headB->next == NULL) return NULL;

    Node * p = headA->next, * head_outcome = InitialiseList(), * head_temporary = NULL;
    while(p != NULL)
    {
        head_temporary = InitialiseList();
        A_Add_B_Polynomial(MonomialMultiplyPolynomial(p, headB), head_outcome, head_temporary);
        CopyFromA(head_temporary, head_outcome);
        // PrintPolynomial(MonomialMultiplyPolynomial(p, headB));
        // PrintPolynomial(head_outcome);
        // PrintPolynomial(head_temporary);
        p = p->next;
        FreeList(head_temporary);
    }
    return head_outcome;
}



