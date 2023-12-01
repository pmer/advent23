#include "os/os.h"
#include "util/compiler.h"
#include "util/int.h"
#include "util/string2.h"

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
        for (Size i = 0; ; i++) {
            char c = line[i];
            if ('0' <= c && c <= '9') {
                first = c - '0';
                break;
            }
        }
        for (Size i = line.size - 1; ; i--) {
            char c = line[i];
            if ('0' <= c && c <= '9') {
                last = c - '0';
                break;
            }
        }
        sum += first * 10 + last;
    }

    sout << sum << '\n';

    return 0;
}
