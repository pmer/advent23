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

    Size indexes[140][140] = {};
    Vector<I32> numbers;
    numbers.push(0);

    I32 sum = 0;

    for (Size lineNum = 0; lineNum < lines.size; lineNum++) {
        StringView line = lines[lineNum];
        for (Size i = 0; i < line.size; ) {
            char c = line[i];
            if ('0' <= c && c <= '9') {
                I32 x = 0;
                StringView rest;
                bool ok = parseI32(&x, &rest, line.substr(i));
                assert_(ok);
                Size length = line.size - i - rest.size;
                Size numbersIdx = numbers.size;
                numbers.push(x);
                for (Size j = i; j < i + length; j++)
                    indexes[lineNum][j] = numbersIdx;
                i += length;
            }
            else
                i++;
        }
    }

    for (Size lineNum = 0; lineNum < lines.size; lineNum++) {
        StringView line = lines[lineNum];
        for (Size i = 0; i < line.size; i++) {
            char c = line[i];
            if (c != '*')
                continue;

            Size x1 = bound((SSize)i - 1, 0ll, (SSize)line.size - 1);
            Size x2 = bound((SSize)i + 1, 0ll, (SSize)line.size - 1);
            Size y1 = bound((SSize)lineNum - 1, 0ll, (SSize)lines.size - 1);
            Size y2 = bound((SSize)lineNum + 1, 0ll, (SSize)lines.size - 1);

            I32 first = -1;
            I32 second = -1;
            bool third = false;

            for (Size y = y1; y <= y2; y++) {
                for (Size x = x1; x <= x2; x++) {
                    Size i = indexes[y][x];
                    if (i) {
                        if (first == -1)
                            first = i;
                        else if (second == -1) {
                            if (i != first)
                                second = i;
                        }
                        else {
                            if (i != first && i != second)
                                third = true;
                        }
                    }
                }
            }

            if (first != -1 && second != -1 && !third)
                sum += numbers[first] * numbers[second];
        }
    }

    sout << sum << '\n';

    return 0;
}
