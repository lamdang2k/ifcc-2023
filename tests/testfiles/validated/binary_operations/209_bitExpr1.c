int main() {
    int a =10;
    int b = 20;
    int c = ((a^25) | (30&b)) & (a|b); /*test fails if no parentheses*/
    return c;
}
