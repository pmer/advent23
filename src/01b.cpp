#include "os/os.h"
#include "util/compiler.h"
#include "util/int.h"
#include "util/io.h"
#include "util/string2.h"
#include "util/string-view.h"

static StringView one("one", 3);
static StringView two("two", 3);
static StringView three("three", 5);
static StringView four("four", 4);
static StringView five("five", 4);
static StringView six("six", 3);
static StringView seven("seven", 5);
static StringView eight("eight", 5);
static StringView nine("nine", 4);

int
main() noexcept {
    Flusher f1(sout);
    Flusher f2(serr);

    ReadLines lines("01");
    if (!lines) {
        serr << "Could not read input\n";
        return 1;
    }

    int sum = 0;

    for (StringView line = lines.next(); line.data; line = lines.next()) {
        int first, last;
        StringView rest;
        for (Size i = 0; ; i++) {
            char c = line[i];
            if ('0' <= c && c <= '9') {
                first = c - '0';
                goto foundFirst;
            }
            switch (c) {
                case 'o':
                    rest = line.substr(i);
                    if (rest.startsWith(one)) {
                        first = 1;
                        goto foundFirst;
                    }
                case 't':
                    rest = line.substr(i);
                    if (rest.startsWith(two)) {
                        first = 2;
                        goto foundFirst;
                    }
                    if (rest.startsWith(three)) {
                        first = 3;
                        goto foundFirst;
                    }
                case 'f':
                    rest = line.substr(i);
                    if (rest.startsWith(four)) {
                        first = 4;
                        goto foundFirst;
                    }
                    if (rest.startsWith(five)) {
                        first = 5;
                        goto foundFirst;
                    }
                case 's':
                    rest = line.substr(i);
                    if (rest.startsWith(six)) {
                        first = 6;
                        goto foundFirst;
                    }
                    if (rest.startsWith(seven)) {
                        first = 7;
                        goto foundFirst;
                    }
                case 'e':
                    rest = line.substr(i);
                    if (rest.startsWith(eight)) {
                        first = 8;
                        goto foundFirst;
                    }
                case 'n':
                    rest = line.substr(i);
                    if (rest.startsWith(nine)) {
                        first = 9;
                        goto foundFirst;
                    }
                default:
                    break;
            }
        }
    foundFirst:

        for (Size i = line.size - 1; ; i--) {
            char c = line[i];
            if ('0' <= c && c <= '9') {
                last = c - '0';
                break;
            }
            switch (c) {
                case 'o':
                    rest = line.substr(i);
                    if (rest.startsWith(one)) {
                        last = 1;
                        goto foundLast;
                    }
                case 't':
                    rest = line.substr(i);
                    if (rest.startsWith(two)) {
                        last = 2;
                        goto foundLast;
                    }
                    if (rest.startsWith(three)) {
                        last = 3;
                        goto foundLast;
                    }
                case 'f':
                    rest = line.substr(i);
                    if (rest.startsWith(four)) {
                        last = 4;
                        goto foundLast;
                    }
                    if (rest.startsWith(five)) {
                        last = 5;
                        goto foundLast;
                    }
                case 's':
                    rest = line.substr(i);
                    if (rest.startsWith(six)) {
                        last = 6;
                        goto foundLast;
                    }
                    if (rest.startsWith(seven)) {
                        last = 7;
                        goto foundLast;
                    }
                case 'e':
                    rest = line.substr(i);
                    if (rest.startsWith(eight)) {
                        last = 8;
                        goto foundLast;
                    }
                case 'n':
                    rest = line.substr(i);
                    if (rest.startsWith(nine)) {
                        last = 9;
                        goto foundLast;
                    }
                default:
                    break;
            }
        }
    foundLast:

        sum += first * 10 + last;
    }

    sout << sum << '\n';

    return 0;
}
