import { __id } from "../context.test"

class X {
    a = this
    /** @memo */
    methodX(): this {
        const b = this
        return this
    }
}

/** @memo:stable */
class Y {
    c = this
    /** @memo */
    methodY(): this {
        const d = this
        return this
    }
}

/** @memo:stable */
class Z {
    c = this
    /** @memo */
    methodZ() {
        const d = this

        class W {
            /** @memo */
            methodW() {
                const d = this
            }
        }
    }
}

