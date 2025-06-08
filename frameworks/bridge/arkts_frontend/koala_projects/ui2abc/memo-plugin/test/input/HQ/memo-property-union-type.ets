import { memo } from "@koalaui/runtime/annotations"

class A {
    @memo memo_union_arg: (() => void) | undefined = () => {}
}
