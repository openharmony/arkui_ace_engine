import { memo } from "@koalaui/runtime/annotations"

class Test {
    @memo void_method_with_return(arg: string) {
        return
    }
}

class Use {
    @memo test() {
        const test = new Test()
   
        test.void_method_with_return("a value")
    }
}
