import { memo } from "@koalaui/runtime/annotations"

class Test {
    @memo lambda_arg_with_arg(@memo arg: (value: string) => string) {

    }
}

class Use {
    @memo test() {
        const test = new Test()
        test.lambda_arg_with_arg((value: string): string => value)
    }
}
