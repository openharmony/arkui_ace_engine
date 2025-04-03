/** @memo */
function foo() {}

interface Y {
    /** @memo */
    prop: (() => void) | ((p0: number) => number) | undefined
}

class X implements Y {
    /** @memo */
    prop: (() => void) | ((p0: number) => number) = () => {}
}

class Z implements Y {
    /** @memo */
    prop: () => void = foo
}