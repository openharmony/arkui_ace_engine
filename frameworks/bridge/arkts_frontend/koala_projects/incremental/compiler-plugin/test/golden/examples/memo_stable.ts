import { __id } from "../context.test";
import { __memo_context_type, __memo_id_type } from "./context.test";
class X {
    a = this;
    /** @memo */
    methodX(__memo_context: __memo_context_type, __memo_id: __memo_id_type): this {
        const __memo_scope = __memo_context.scope<this>(__memo_id + ("0___key_id_DIRNAME/memo_stable.ts" as __memo_id_type), 1);
        const __memo_parameter_this = __memo_scope.param(0, this);
        if (__memo_scope.unchanged)
            return __memo_scope.cached;
        const b = __memo_parameter_this.value;
        return __memo_scope.recache(__memo_parameter_this.value);
    }
}
/** @memo:stable */
class Y {
    c = this;
    /** @memo */
    methodY(__memo_context: __memo_context_type, __memo_id: __memo_id_type): this {
        const __memo_scope = __memo_context.scope<void>(__memo_id + ("1___key_id_DIRNAME/memo_stable.ts" as __memo_id_type));
        if (__memo_scope.unchanged) {
            __memo_scope.cached;
            return this;
        }
        const d = this;
        {
            __memo_scope.recache();
            return this;
        }
    }
}
/** @memo:stable */
class Z {
    c = this;
    /** @memo */
    methodZ(__memo_context: __memo_context_type, __memo_id: __memo_id_type) {
        const __memo_scope = __memo_context.scope<void>(__memo_id + ("3___key_id_DIRNAME/memo_stable.ts" as __memo_id_type));
        if (__memo_scope.unchanged) {
            __memo_scope.cached;
            return;
        }
        const d = this;
        class W {
            /** @memo */
            methodW(__memo_context: __memo_context_type, __memo_id: __memo_id_type) {
                const __memo_scope = __memo_context.scope<void>(__memo_id + ("2___key_id_DIRNAME/memo_stable.ts" as __memo_id_type), 1);
                const __memo_parameter_this = __memo_scope.param(0, this);
                if (__memo_scope.unchanged) {
                    __memo_scope.cached;
                    return;
                }
                const d = __memo_parameter_this.value;
                {
                    __memo_scope.recache();
                    return;
                }
            }
        }
        {
            __memo_scope.recache();
            return;
        }
    }
}

