import { memo } from "@koalaui/runtime/annotations"

interface A {
    @memo a: () => void
}

class AA {

    @memo a: (() => void) | undefined

    constructor(arg?: A) {
        this.a = arg?.a;
    }

    @memo
    build() {
        this.a?.();
    }
}

@memo
() => {
    let a = new AA({ a: () => {} })
}
