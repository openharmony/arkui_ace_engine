import { memo } from "@koalaui/runtime/annotations"

class Test {
    @memo args_with_default_values(
        arg1: int = 10,
        arg2: () => int = () => { return 20 },
        arg3: int = arg1,
        arg4?: int
    ): void {
        console.log(arg1, arg2, arg3, arg4)
        console.log(arg2())
    }
}
