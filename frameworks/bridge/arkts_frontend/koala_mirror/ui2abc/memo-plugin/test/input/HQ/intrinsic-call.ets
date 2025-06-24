import { memo, memo_intrinsic } from "@koalaui/runtime/annotations"

class Test {
    @memo void_method(): void {
    }
   
    @memo_intrinsic intrinsic_method_with_this(): int {
        this.void_method()
        return 0
    }
}
