import { memo } from "@koalaui/runtime/annotations"

declare abstract class A {
    @memo 
    x(): void;

    test_signature(
        @memo arg1: () => void,
        @memo arg2: (() => void) | undefined,
        @memo arg3: ((() => void) | undefined) | ((() => int) | undefined),
        @memo x: (y: (z: @memo () => void) => void) => void,
    ): @memo () => void;
}

class AA extends A {
    @memo x(): void {}
}

@memo
() => {
    new AA().x();

    const a: A = new AA();
    a.x();
}
