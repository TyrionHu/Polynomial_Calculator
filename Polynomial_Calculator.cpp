/*
 * @Description: 
 * @Version: 
 * @Author: Tyrion Huu
 * @Date: 2022-09-14 21:28:45
 * @LastEditors: Tyrion Huu
 * @LastEditTime: 2022-09-17 10:07:38
 */

#include "functions.h"

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