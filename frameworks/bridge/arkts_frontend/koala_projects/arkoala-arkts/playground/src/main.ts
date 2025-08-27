interface A {
    foo(): number
    onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Layoutable[], constraint: ConstraintSizeOptions): void
}

class B implements A {
    foo(): number {
        throw new Error()
    }
    onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Layoutable[], constraint: ConstraintSizeOptions): void {}
}

class C extends B {
    bar(): string {
        return "asd"
    }
}

new C().bar()