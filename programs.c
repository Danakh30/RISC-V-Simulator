#include <stdio.h> 

int Fibonacci(int k)
{
    int result=1;
    int previous=1;
    int temp=0;
    for(int i = 1; i < k; i++ )  
    {
        result=temp+previous;
        temp=previous;
        previous=result;
    }
    return result;

}
int GCD (int a, int b) {
    while(a!=b) {
        if (a > b)
            a -= b;
        else
            b -= a;
        }
return a;
}


int Sum(int n)
{
    int result=0;
    for(int i=1; i<=n; i++)
    {   
        result+=i;
    }
    return result;
}

int SumofArray (int A[], int size)
{
    int result=0;
    for(int i=0; i< size ;i++)
    {
        result+=A[i];
    }
}
 
int maxNum(int A[], int size)
{   
    int maximum=0;
    for(int i=0; i<size; i++)
    {
        if(maximum < A[i])
        {
            maximum=A[i];
        }

    }
    return maximum;

}
void swap(int v[], int k)
{
    int temp = v[k];
    v[k] = v[k+1];
    v[k+1] = temp;
}




