import { memo } from "@koalaui/runtime/annotations"

class A {
    x: int
    y: int
}
   
class Test {
    @memo obj_arg(arg: A) {
   
    }
}

class Use {
    @memo test() {
        const test = new Test()
   
        test.obj_arg({ x: 1, y: 2 })
    }
}
