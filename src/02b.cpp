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

    ReadLines lines("02");
    if (!lines) {
        serr << "Could not read input\n";
        return 1;
    }

    I32 sum = 0;

    for (StringView line = lines.next(); line.data; line = lines.next()) {
        I32 r = 0, g = 0, b = 0;
        StringView hands = line.substr(line.find(':') + 2);
        Splits<';'> splits(hands);
        for (StringView hand = splits.next(); hand.data; hand = splits.next()) {
            Splits<','> splits2(hand);
            for (StringView comp = splits2.next(); comp.data; comp = splits2.next()) {
                comp.ltrim();
                I32 count;
                bool found = parseI32(&count, &comp, comp);
                assert_(found);
                if (comp[1] == 'r')
                    r = max(r, count);
                else if (comp[1] == 'g')
                    g = max(g, count);
                else
                    b = max(b, count);
            }
        }
        sum += r * g * b;
    }

    sout << sum << '\n';

    return 0;
}
