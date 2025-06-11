import { __id } from "../context.test"

/** @memo */
function foo(
    /** @memo */
    param1: undefined | (() => void) | ((x?:number)=>number),
    /** @memo */
    param2: (() => void) | undefined | ((x?:number)=>number),
    /** @memo */
    param3: (() => void) | ((x?:number)=>number) | undefined
) {
    param1?.()
    param2?.()
    param3?.()
}
