#include "os/os.h"
#include "util/compiler.h"
#include "util/int.h"
#include "util/string2.h"

static StringView red(" red", 4);
static StringView green(" green", 6);
static StringView blue(" blue", 5);

#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14

int
main() noexcept {
    Flusher f1(sout);
    Flusher f2(serr);

    ReadLines lines("02");
    if (!lines) {
        serr << "Could not read input\n";
        return 1;
    }

    int sum = 0;

    int game = 1;
    for (StringView line = lines.next(); line.data; line = lines.next(), game++) {
        bool ok = true;
        StringView hands = line.substr(line.find(':') + 2);
        Splits<';'> splits(hands);
        for (StringView hand = splits.next(); hand.data && ok; hand = splits.next()) {
            Splits<','> splits2(hand);
            for (StringView comp = splits2.next(); comp.data && ok; comp = splits2.next()) {
                comp.ltrim();
                I32 count;
                bool found = parseI32(&count, &comp, comp);
                assert_(found);
                ok =
                    (comp == red && count <= MAX_RED) ||
                    (comp == green && count <= MAX_GREEN) ||
                    (comp == blue && count <= MAX_BLUE);
            }
        }
        if (ok)
            sum += game;
    }

    sout << sum << '\n';

    return 0;
}
