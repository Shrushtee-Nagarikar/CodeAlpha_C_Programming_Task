#include <stdio.h>
#include <stdlib.h>

void calculator() {
    char opera;
    double num1, num2, result;

    printf("\n\n    Basic Calculator    \n\n");
    printf("Enter an operator (+, -, *, /): ");
    scanf(" %c", &opera);

    printf("Enter two operands: ");
    if (scanf("%lf %lf", &num1, &num2) != 2) {
        printf("Error: Invalid number input.\n");
        return;
    }

    switch (opera) {
        case '+':
            printf("Result: %.0lf + %.0lf = %.2lf\n", num1, num2, num1 + num2);
            break;
        case '-':
            printf("Result: %.2lf - %.2lf = %.2lf\n", num1, num2, num1 - num2);
            break;
        case '*':
            printf("Result: %.2lf * %.2lf = %.2lf\n", num1, num2, num1 * num2);
            break;
        case '/':
            if (num2 != 0)
                printf("Result: %.2lf / %.2lf = %.2lf\n", num1, num2, num1 / num2);
            else
                printf("Error: Division by zero is not allowed.\n");
            break;
        default:
            printf("Error: Invalid operator.\n");
    }
}

int main() {
    char choice;
    do {
        calculator();
        printf("\nDo you want to perform another calculation? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y' || choice == 'yes' || choice == 'Yes');
    return 0;
}
