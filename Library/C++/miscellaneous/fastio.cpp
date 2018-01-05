namespace FIO {
    const int SZ = 524288;
    char buffer[SZ];
    int p = SZ;
    inline char RC() {
        if(p == SZ) {
            fread(buffer, 1, SZ, stdin);
            p = 0;
        }
        return buffer[p++];
    }
    int RI() {
        char c = RC();
        while ((c < '0' || c > '9') && c != '-') c = RC();
        int x = 0; bool neg = c == '-';
        if (neg) c = RC();
        while (c >= '0' && c <= '9') {
            x = x * 10 + c - '0';
            c = RC();
        }
        return neg ? -x : x;
    }
}