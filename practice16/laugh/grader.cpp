#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "laugh.h"

int main() {
    std::string s;
    std::cin >> s;
    printf("%d\n", longest_laugh(s));
    return 0;
}