int helloworld = 0 ;
char iamachar ;

int main()
{
    int n;
    int i=0,j=0;
    printf("please  input a number (1<=n<=20):\n");

    while (!scanf("%d",&n) || n>20 || n<1)
    {
        fflush(stdin);
        printf("Input error ! enter again:\n");
    }

    for (i=1;i<=n;i++)
    {
        for (j=0;j<2*n;j++)
        {
            if (j<n)
            {
                if (j<i)
                    putchar('*');
                else
                    putchar(' ');
            }
            else
            {
                if (j<2*n-i)
                    putchar(' ');
                else
                    putchar('*');

            }
        }
        putchar('\n');
    }
    return 0;
}

const int iamattheend ;
