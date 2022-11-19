#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define BRACKETS "(){}[]<>"
// return position starting from 0 of c in s. or return -1
int strint(char *s, char c) {
    // assume null terminated
    int r = 0;
    while (s[r] != '\0') {
        if (s[r] == c) return r;
        r += 1;
    }
    return -1;
}
// return TRUE if brackets are balanced. else False
// balanced means equal < for >, ( for ), and so on for [] and {} and that the first in the pair preceeds the second
int balanced(char *b) {
    // assume null terminated
    int l = (strlen(b)+1)/2;
    char *s = malloc(l);
    int sl = 0;
    int bl = 0;
    while (b[bl] != '\0') {
        if (sl > l) return FALSE; // at least half must be matching
        int c = strint(BRACKETS, b[bl]);
        if (c == -1) return FALSE; // invalid character found
        if (c % 2 == 0) {
            // if it equals an opening bracket push it on the stack
            s[++sl] = b[bl];
        } else {
            // it's a closing bracket
            if (sl == 0) return FALSE;
            if (s[sl] == BRACKETS[c-1]) {
                sl -= 1;
            } else {
                // top of stack does not equal the value we're expecting
                return FALSE;
            }
        }
        bl += 1;
    }
    return (sl == 0);
}


void assert(int func, int v, char *msg) {
	if (func != v) {
		printf ("Assertion Failure: %s\n", msg);
	}
}

void main(int argc, char *argv) {
    assert(balanced("()"), TRUE, "");
    assert(balanced("[]"), TRUE, "");
    assert(balanced("]["), FALSE, "unbalanced brackets ][");
    assert(balanced("[[[[[[[[[[]]]]]]]]]]"), TRUE, "");
    assert(balanced("(<<<<<<<)"), FALSE, "to many <<<<");
    assert(balanced("([])"), FALSE, " testing that assert works. this should fail"); // checking assert !
    assert(balanced("([])"), TRUE, "balanced");
    assert(balanced("(()[]<()()[{}]>)"), TRUE, "balanced");
    assert(balanced("(()[]<a)()[{}]>)"), FALSE, "unbalanced");
}
