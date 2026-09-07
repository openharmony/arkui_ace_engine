#include "../parse_resource_uint32.h"
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <string>

static void Expect(bool cond, const char *msg)
{
    if (!cond) {
        std::fprintf(stderr, "FAIL: %s\n", msg);
        std::exit(1);
    }
}

int main()
{
    uint32_t v = 99;
    Expect(!ParseResourceUint32("", v), "empty");
    Expect(v == 99, "empty-unchanged");

    Expect(!ParseResourceUint32("abc", v), "abc");
    Expect(v == 99, "abc-unchanged");

    Expect(!ParseResourceUint32("12a", v), "12a");
    Expect(v == 99, "12a-unchanged");

    Expect(!ParseResourceUint32("4294967296", v), "overflow");
    Expect(v == 99, "overflow-unchanged");

    Expect(!ParseResourceUint32("-1", v), "neg");
    Expect(v == 99, "neg-unchanged");

    Expect(!ParseResourceUint32(" 1", v), "lead-space");
    Expect(v == 99, "lead-space-unchanged");

    Expect(!ParseResourceUint32("99999999999999999999", v), "huge");
    Expect(v == 99, "huge-unchanged");

    Expect(ParseResourceUint32("0", v) && v == 0, "zero");
    Expect(ParseResourceUint32("42", v) && v == 42, "res-id");
    Expect(ParseResourceUint32("4294967295", v) && v == std::numeric_limits<uint32_t>::max(), "u32-max");

    std::puts("ok");
    return 0;
}
