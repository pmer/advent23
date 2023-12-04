#include "os/os.h"
#include "util/compiler.h"
#include "util/int.h"
#include "util/io.h"
#include "util/math2.h"
#include "util/string2.h"
#include "util/string-view.h"

int
main() noexcept {
    Flusher f1(sout);
    Flusher f2(serr);

    ReadLines lines("03");
    if (!lines) {
        serr << "Could not read input\n";
        return 1;
    }

    I32 sum = 0;

    for (StringView line = lines.next(); line.data; line = lines.next()) {
        sum += 1;
    }

    sout << sum << '\n';

    return 0;
}
