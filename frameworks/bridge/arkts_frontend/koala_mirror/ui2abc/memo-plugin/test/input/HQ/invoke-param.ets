import { memo } from "@koalaui/runtime/annotations"

class B {
    static $_invoke(@memo p?: () => void): void {}
}

@memo
() => {
    B(() => {});
}
