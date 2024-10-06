#include <stdio.h>
int main()
{
    int a, b, c; // Store the number of students in classes A, B, and C.
	int max;
 
    printf("How many students are in classes A, B, and C, respectively?\n");
    scanf("%d%d%d", &a, &b, &c);

    if(a >= b && a >= c)
    {
        max = a;
        printf("Class A has the most students, ");
	}	
    else if(b > a && b >= c)
    {
        max = b;
        printf("Class B has the most students, ");
    }
    else{
        max = c;
        printf("Class C has the most students, ");
	}
    int total = a + b + c;
    // A class can accept at most half of all students. 
    if(max > total / 2){
        printf("and is overly enrolled!\n");
    }
    else if(max < total / 2||max == (total-1) / 2){
        printf("and still has open seats!\n");
    }
    else{
        printf("and is full!\n");
	}
    return 0;
}
