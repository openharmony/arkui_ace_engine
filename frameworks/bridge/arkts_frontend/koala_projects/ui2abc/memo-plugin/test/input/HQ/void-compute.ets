import { memo } from "@koalaui/runtime/annotations"

class Test {
    @memo lambda_arg(@memo arg: () => void) {

    }
}

class Use {
    @memo test() {
        const test = new Test()
        test.lambda_arg((): void => {})
    }
}
