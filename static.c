char staticFunc()
{
    static int count = 0;
    printf("count :%d \n",count);
    count++;
}

int main()
{
    staticFunc();
    staticFunc();
    staticFunc();
    staticFunc();
}