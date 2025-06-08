import { memo } from "@koalaui/runtime/annotations"

class Test {
    @memo void_method(): void {
    }

    @memo internal_call() {
        this.void_method()
    }
}
