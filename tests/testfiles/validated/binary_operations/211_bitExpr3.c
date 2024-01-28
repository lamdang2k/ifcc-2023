int main() {
    int a = 10;
    int b = 20;
    int c = 30;
    int d= 40;
    int e = (((a^b)&(c^15))|((b&c)^(15&(c|a))))&((d&25)|(d^a));
    return e;
}
