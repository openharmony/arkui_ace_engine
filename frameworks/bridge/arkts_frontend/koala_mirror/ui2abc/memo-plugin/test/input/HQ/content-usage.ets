import { memo } from "@koalaui/runtime/annotations"

class Test {
    @memo memo_content(@memo content: () => void) {
        content()
    }
}
