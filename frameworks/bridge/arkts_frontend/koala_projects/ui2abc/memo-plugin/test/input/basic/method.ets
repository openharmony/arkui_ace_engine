import { memo } from "@koalaui/runtime/annotations"

class C {
    @memo memo_method(): void {

    }

    non_memo_method(): void {

    }
}
