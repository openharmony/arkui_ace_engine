import { memo } from "@koalaui/runtime/annotations"

class A {
    arg_memo_type: @memo () => void

    constructor() {
        this.arg_memo_type = () => {};
    }

    @memo
    build() {
        this.arg_memo_type();
    }

}
