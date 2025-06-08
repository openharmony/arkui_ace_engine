import { memo } from "@koalaui/runtime/annotations"

interface A {
    @memo prop: (() => void) | undefined
}

class AA implements A {
    @memo prop: (() => void) | undefined
}
