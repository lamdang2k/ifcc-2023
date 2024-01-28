int main() {
    int a = 10;
    int b = 20;
    int c = 30;
    int d = ((a^15)&c)|((b&c)^(a&(c|25)));
    return d;
}
