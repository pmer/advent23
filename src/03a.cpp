#include "os/os.h"
#include "util/compiler.h"
#include "util/int.h"
#include "util/io.h"
#include "util/math2.h"
#include "util/string2.h"
#include "util/string-view.h"
#include "util/vector.h"

bool
containsSymbol(StringView segment) noexcept {
    for (char c : segment) {
        switch (c) {
            case '#':
            case '$':
            case '%':
            case '&':
            case '*':
            case '+':
            case '-':
            case '/':
            case '=':
            case '@':
                return true;
        }
    }
    return false;
}

int
main() noexcept {
    Flusher f1(sout);
    Flusher f2(serr);

    String data;
    if (!readFile("03", data)) {
        serr << "Could not read input\n";
        return 1;
    }

    // Parse the integers.
    Vector<StringView> lines;
    splitStr(lines, data, "\n");

    I32 sum = 0;

    for (Size lineNum = 0; lineNum < lines.size; lineNum++) {
        StringView line = lines[lineNum];
        for (Size i = 0; i < line.size; ) {
            if ('0' <= line[i] && line[i] <= '9') {
                I32 x = 0;
                StringView rest;
                bool ok = parseI32(&x, &rest, line.substr(i));
                assert_(ok);
                Size length = line.size - i - rest.size;
                Size start = i == 0 ? 0 : i - 1;
                Size end = i == 0 ? length + 1 : length + 2;
                end = min(end, line.size - start);
                bool isAdjacent = false;
                if (lineNum > 0) {
                    StringView segment = lines[lineNum - 1].substr(start, end);
                    isAdjacent = containsSymbol(segment);
                }
                if (!isAdjacent) {
                    StringView segment = line.substr(start, end);
                    isAdjacent = containsSymbol(segment);
                }
                if (!isAdjacent && lineNum + 1 < lines.size) {
                    StringView segment = lines[lineNum + 1].substr(start, end);
                    isAdjacent = containsSymbol(segment);
                }
                if (isAdjacent) {
                    sum += x;
                }
                i += length;
            }
            else
                i++;
        }
    }

    sout << sum << '\n';

    return 0;
}
