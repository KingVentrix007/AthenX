void memory_copy(char *source, char *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

int string_length(char s[]) {
    int i = 0;
    while (s[i] != '\0') {
        ++i;
    }
    return i;
}

void append(char s[], char n) {
    int len = string_length(s);
    s[len] = n;
    s[len + 1] = '\0';
}