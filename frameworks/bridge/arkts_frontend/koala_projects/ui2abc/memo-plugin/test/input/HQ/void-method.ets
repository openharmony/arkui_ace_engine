import { memo } from "@koalaui/runtime/annotations"

class Test {
    @memo void_method(): void {
    }
}

class Use {
    @memo test() {
        const test = new Test()
   
        test.void_method()
    }
}
