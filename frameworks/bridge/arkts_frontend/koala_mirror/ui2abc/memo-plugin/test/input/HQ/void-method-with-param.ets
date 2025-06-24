import { memo } from "@koalaui/runtime/annotations"

class Test {
    @memo void_method_with_arg(arg: string) {
    }
}

class Use {
    @memo test() {
        const test = new Test()
   
        test.void_method_with_arg("an arg")
    }
}
