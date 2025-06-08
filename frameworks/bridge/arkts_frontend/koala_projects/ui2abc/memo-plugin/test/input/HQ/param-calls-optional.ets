import { memo } from "@koalaui/runtime/annotations"

class Test {
    @memo optional_args(
     arg1?: int,
     arg2?: () => int
    ) {
     console.log(arg1)
     console.log(arg2)
     console.log(arg2?.())
    }
}
