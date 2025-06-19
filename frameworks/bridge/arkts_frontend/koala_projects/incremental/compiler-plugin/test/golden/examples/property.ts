import { __memo_context_type, __memo_id_type } from "./context.test";
/** @memo */
function foo(__memo_context: __memo_context_type, __memo_id: __memo_id_type) {
    const __memo_scope = __memo_context.scope<void>(__memo_id + ("0___key_id_DIRNAME/property.ts" as __memo_id_type));
    if (__memo_scope.unchanged) {
        __memo_scope.cached;
        return;
    }
    {
        __memo_scope.recache();
        return;
    }
}
interface Y {
    /** @memo */
    prop: ((__memo_context: __memo_context_type, __memo_id: __memo_id_type) => void) | ((__memo_context: __memo_context_type, __memo_id: __memo_id_type, p0: number) => number) | undefined;
}
class X implements Y {
    /** @memo */
    prop: ((__memo_context: __memo_context_type, __memo_id: __memo_id_type) => void) | ((__memo_context: __memo_context_type, __memo_id: __memo_id_type, p0: number) => number) = () => { };
}
class Z implements Y {
    /** @memo */
    prop: (__memo_context: __memo_context_type, __memo_id: __memo_id_type) => void = foo;
}

