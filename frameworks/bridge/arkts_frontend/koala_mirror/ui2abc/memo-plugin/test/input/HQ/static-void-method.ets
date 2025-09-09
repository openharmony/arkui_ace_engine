import { memo } from "@koalaui/runtime/annotations"

class Test {
    @memo static static_method_with_type_parameter<T>(arg: T): void {
        return
    }
}

class Use {
    @memo test() {

        Test.static_method_with_type_parameter("I'm static")
    }
}
