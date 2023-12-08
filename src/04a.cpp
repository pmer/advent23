#include "os/c.h"
#include "os/os.h"
#include "util/compiler.h"
#include "util/int.h"
#include "util/io.h"
#include "util/string2.h"
#include "util/string-view.h"

static I32
readInt(StringView view) noexcept {
    if (view[0] != ' ')
        return (view.data[0] - '0') * 10 + view.data[1] - '0';
    else
        return view.data[1] - '0';
}

int
main() noexcept {
    Flusher f1(sout);
    Flusher f2(serr);

    ReadLines lines("04");
    if (!lines) {
        serr << "Could not read input\n";
        return 1;
    }

    I32 sum = 0;
    bool winning[100];

    for (StringView line = lines.next(); line.data; line = lines.next()) {
        I32 score = 0;
        memset(winning, 0, sizeof(winning));
        for (I32 i = 0; i < 10; i++) {
            I32 have = readInt(line.substr(10 + i * 3, 2));
            winning[have] = 1;
        }
        for (I32 i = 0; i < 25; i++) {
            I32 have = readInt(line.substr(42 + i * 3, 2));
            if (winning[have])
                score++;
        }
        sum += score ? 1 << (score - 1) : 0;
    }

    sout << sum << '\n';

    return 0;
}
