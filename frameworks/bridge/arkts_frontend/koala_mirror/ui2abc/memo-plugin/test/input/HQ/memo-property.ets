import { memo } from "@koalaui/runtime/annotations"

class A {
    @memo memo_arg: () => void

    constructor() {
        this.memo_arg = () => {};
    }

    @memo
    build() {
        this.memo_arg();
    }

}
