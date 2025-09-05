import { memo } from "@koalaui/runtime/annotations"

class Test {
    @memo method_with_type_parameter<T>(arg: T): T {
        return arg
    }
}

class Use {
    @memo test() {
        const test = new Test()
   
        test.method_with_type_parameter("I'm string")
    }
}
