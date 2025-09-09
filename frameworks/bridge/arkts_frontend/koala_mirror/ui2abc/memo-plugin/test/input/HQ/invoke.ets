import { memo } from "@koalaui/runtime/annotations"

class A {
    @memo
    static $_invoke(): void {}
}

@memo
() => {
    A();
}
