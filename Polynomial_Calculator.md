## 实验报告： 一元系数多项式简单计算器

## 目录

[toc]

## 需求分析

设计一个一元稀疏多项式简单计算器，其需要实现的基本功能是：

1. 用带头节点的单链表存储多项式，其项数存放在头节点；
2. 输人并建立多项式；
3. 输出多项式，输出形式为整数序列：$n, c_1, e_1, c_2, e_2, …, c_n, e_n,$ 其中$n$是多项式的项数，$c_i$和$e_i$分别是第$i$项的系数和指数，序数按指数降序排列；
4. 多项式$a$和$b$相加，建立多项式$a+b$;
5. 多项式$a$和$b$相减，建立多项式$a-b$。
6. 计算多项式在$x$处的值；
7. 求多项式$a$的导函数$a'$;
8. 多项式$a$和$b$相乘，建立乘积多项式$ab$。

## 概要设计

为实现上述程序功能，应以有序表表示多项式。

本项目包含3个模块：

1. 主程序模块;
2. 函数单元模块；
3. 用户预编译模块；

各模块之间调用关系如下：

用户预编译模块 -> 函数单元模块 -> 主程序模块。

## 详细设计

### 结构

```c++
typedef int Status;
typedef struct Node
{
    double          coefficient;
    long            power;
    struct Node *   next;
}Node;
```

### Main函数

```c++
int main(void)
{
    char choice;
    std::cout << "Which operation do you want? Please enter the letter of that choice." << std::endl;
    std::cout << "A: A plus B;" << std::endl << "B: A minus B;" << std::endl << "C: A multiply B;" << std::endl;
    std::cout << "D: Calculate the derivative;" << std::endl << "E: Calculate the value on x." << std::endl << "F: Just show it." << std::endl;
    std::cin >> choice;
    Node * head = InitialiseList();
    Node * headA = InitialiseList();
    Node * headB = InitialiseList();
    double x = 0;
    switch (choice)
    {
        case 'A': 
            std::cout << "Please enter the first polynomial with this format: c e c e c e… c is a double, and e is a long. No sequence required." << std::endl;
            InputAPolynomial(headA);
            std::cout << "Now please enter the second polynomial." << std::endl;
            InputAPolynomial(headB);
            A_Add_B_Polynomial(headA, headB, head);
            PrintPolynomial(head);
            break;

        case 'B':
            std::cout << "Please enter the first polynomial with this format: c e c e c e… c is a double, and e is a long. No sequence required." << std::endl;
            InputAPolynomial(headA);
            std::cout << "Now please enter the second polynomial." << std::endl;
            InputAPolynomial(headB);
            A_Minus_B_Polynomial(headA, headB, head);
            PrintPolynomial(head);
            break;

        case 'C':
            std::cout << "Please enter the first polynomial with this format: c e c e c e… c is a double, and e is a long. No sequence required." << std::endl;
            InputAPolynomial(headA);
            // PrintPolynomial(headA);
            std::cout << "Now please enter the second polynomial." << std::endl;
            InputAPolynomial(headB);
            // PrintPolynomial(headB);
            head = MultiplyPolynomial(headA, headB);
            PrintPolynomial(head);
            break;

        case 'D':
            std::cout << "Please enter the polynomial with this format: c e c e c e… c is a double, and e is a long. No sequence required." << std::endl;
            InputAPolynomial(headA);
            // PrintPolynomial(headA);
            CalculateDerivative(headA, head);
            PrintPolynomial(head);
            break;

        case 'E':
            std::cout << "Please enter the polynomial with this format: c e c e c e… c is a double, and e is a long. No sequence required." << std::endl;
            InputAPolynomial(headA);
            std::cout << "Please enter the number." << std::endl;
            std::cin >> x;
            std::cout << CalculateValue(headA, x);
            break;

        case 'F':
            std::cout << "Please enter the polynomial with this format: c e c e c e… c is a double, and e is a long. No sequence required." << std::endl;
            InputAPolynomial(head);
            PrintPolynomial(head);
            break;

        default:
            std::cout << "********************What the hell?????????********************" << std::endl;
            break;
    }
    return 0;
}
```

### 部分函数实现

```c++
//计算项数，把项数放入头节点的coefficient。
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

//Return the head of the result linked-list. If it returns NULL, it means it fails to allocate a place.
Status A_Add_B_Polynomial(Node * headA, Node * headB, Node * head_new)
{
    if(headA != NULL && headB == NULL)
    //传入的多项式B不存在时，输出与多项式A相同的多项式。
    {
        CopyFromA(headA, head_new);
        return DONE;
    }
    else if(headB != NULL && headA == NULL)
    //传入的多项式A不存在时，输出与多项式B相同的多项式。
    {
        CopyFromA(headB, head_new);
        return DONE;
    }
    else if(headB == headA && headA == NULL)
    //均不存在，无输出。
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
            //系数和为0，则该次数项的项去除。
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
    //处理剩余的多项式。
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

//输入一个数，求出多项式在此处的值。
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

//求出函数的导数。
Status CalculateDerivative(Node * head, Node * head_new)
{
    Node * p = head->next;
    while(p!= NULL && p->power != 0)
    //指数为0的一项不用计算。
    {
        InsertNode(head_new, p->coefficient * p->power, p->power - 1);
        p = p->next;
    }
    Count(head_new);
    return DONE;
}
```



## 调试分析

调试过程中主要遇到的问题是调用函数时未考虑输入为NULL的情况，导致多次出现了指针访问错误。

算法的时间复杂度分析：

- $O(1):$ InitialiseList, Swap,;
- $O(n):$ Count, InsertNode, PrintPolynomial, A_Add_B_Polynomial, A_Minus_B_Polynomial, CalculateValue, CalculateDerivative, MonomialMultiplyPolynomial;
- $O(n^2):$ BubbleSort, MultiplyPolynomial.

## 测试数据

![截屏2022-09-18 11.06.29](%20%E4%B8%80%E5%85%83%E7%B3%BB%E6%95%B0%E5%A4%9A%E9%A1%B9%E5%BC%8F%E7%AE%80%E5%8D%95%E8%AE%A1%E7%AE%97%E5%99%A8%E5%AE%9E%E9%AA%8C%E6%8A%A5%E5%91%8A.assets/%E6%88%AA%E5%B1%8F2022-09-18%2011.06.29.png)

1. 执行命令"A": 输入"2 1 5 8 -3.1 11", 再输入"7 0 -5 8 11 9"，输出"3, -3.1, 11, 11, 9, 9, 1,"；
2. 执行命令"B": 输入"6 -3 -1 1 4.4 2 -1.2 9", 再输入"-6 -3 5.4 2 -1 2 7.8 15", 输出"4, 7.8, 15, -1.2, 9, -1, 1, 12, -3,";
3. 执行命令"A": 输入"1 0 1 1 1 2 1 3 1 4 1 5", 再输入"-1 3 -1 4", 输出"4, 1, 5, 1, 2, 1, 1, 1, 0,";
4. 执行命令"A": 输入"1 1 1 3", 再输入"-1 1 -1 3", 输出"0,";
5. 执行命令"A": 输入"1 1 1 100", 再输入"1 100 1 200", 输出"3, 1, 200, 2, 100, 1, 1,";
6. 执行命令"A": 输入"1 1 1 2 1 3", 再输入"0 0", 输出"3, 1, 3, 1, 2, 1, 1,";
7. 执行命令"C": 输入"2 1 5 8 -3.1 11", 再输入"7 0 -5 8 11 9"，输出"9, -34.1, 20, 15.5, 19, 55, 17, -25, 16, -21, 11, 22, 10, -10, 9, 35, 8, 14, 1,"；
8. 执行命令"D": 输入"6 -3 -1 1 4.4 2 -1.2 9", 输出"4, -10.8, 8, 8, 1, -1, 0, -18, -4, ";
9. 执行命令"E": 输入"1 0 1 1 1 2 1 3 1 4 1 5", 再输入"4", 输出"3906"。

## 附录

源程序文件名清单：

```c++
function.h																//操作实现模块
user.h																		//预编译等模块
Polynomial_Calculator.cpp									//主程序
```

