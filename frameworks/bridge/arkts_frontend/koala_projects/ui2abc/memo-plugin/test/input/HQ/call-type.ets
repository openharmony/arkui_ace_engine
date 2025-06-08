import { memo } from "@koalaui/runtime/annotations"

type MemoType = @memo () => void

class Test {
    @memo type_alias(
        arg: MemoType
    ) {
        arg()
    }
}
