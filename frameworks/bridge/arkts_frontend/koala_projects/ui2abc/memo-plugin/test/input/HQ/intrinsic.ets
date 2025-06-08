import { memo_intrinsic } from "@koalaui/runtime/annotations"

class Test {
    @memo_intrinsic intrinsic_method(): int {
        return 0
    }
}
