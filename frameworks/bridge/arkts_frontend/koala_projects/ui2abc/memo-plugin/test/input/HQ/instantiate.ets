import { memo } from "@koalaui/runtime/annotations"

class C {
    @memo
    static $_instantiate(factory: () => C): C {
        return factory();
    }
}

class D {
    static $_instantiate(factory: () => D, @memo content?: () => void): D {
        return factory();
    }
}

@memo
() => {
    let x: C | D = C();
    x = D();
}
