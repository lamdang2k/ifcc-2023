int main()
{
    int x =999;
    int y =100;
    int z = 1000;
    while(x>1) {
        x = x-6;
        while (y>5) {
            if (z >6) {
                y=y-10;
            }else{
                y =y-11;
            }
            y = y-2;
        }
        y =y-3;
    }
    return y;
}