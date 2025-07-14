import { memo } from "@koalaui/runtime/annotations"

class A {
    arg: () => void

    constructor() {
        this.arg = () => {};
    }

    @memo
    build() {
        this.arg();
    }

}
