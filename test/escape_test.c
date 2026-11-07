void test_strings() {
    "Standard string with newline \n";
    "String with octal newline \012";
    "String with tab \t and null \0";
}

void main() {
    char c;

    c = '\n';
    c = '\t';

    c = '\012';
    c = '\0';

    test_strings();
}