import { memo } from "@koalaui/runtime/annotations"

class Test {
    @memo string_method_with_return(arg: string): string {
        return arg
    }
}

class Use {
    @memo test() {
        const test = new Test()

        test.string_method_with_return("a string")
    }
}
