import { memo } from "@koalaui/runtime/annotations"
import { __context, __id } from "@koalaui/runtime"

class Test {
    @memo method_with_internals() {
        __context()
        __id()
    }
}
