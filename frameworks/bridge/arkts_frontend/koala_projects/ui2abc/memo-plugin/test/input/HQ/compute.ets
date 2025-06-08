import { memo } from "@koalaui/runtime/annotations"

class Test {
    @memo compute_test(
        @memo arg1: (() => void) | undefined,
        arg2: (() => void) | undefined,
        content: (() => void) | undefined
    ): void {

    }
}

class Use {
    @memo test() {
        const test = new Test()
        test.compute_test(() => {}, () => {}, () => {})
    }
}
