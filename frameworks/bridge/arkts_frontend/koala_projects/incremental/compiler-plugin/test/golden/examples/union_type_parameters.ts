import { __id } from "../context.test";
import { __memo_context_type, __memo_id_type } from "./context.test";
/** @memo */
function foo(__memo_context: __memo_context_type, __memo_id: __memo_id_type, 
/** @memo */
param1: undefined | ((__memo_context: __memo_context_type, __memo_id: __memo_id_type) => void) | ((__memo_context: __memo_context_type, __memo_id: __memo_id_type, x?: number) => number), 
/** @memo */
param2: ((__memo_context: __memo_context_type, __memo_id: __memo_id_type) => void) | undefined | ((__memo_context: __memo_context_type, __memo_id: __memo_id_type, x?: number) => number), 
/** @memo */
param3: ((__memo_context: __memo_context_type, __memo_id: __memo_id_type) => void) | ((__memo_context: __memo_context_type, __memo_id: __memo_id_type, x?: number) => number) | undefined) {
    const __memo_scope = __memo_context.scope<void>(__memo_id + ("3___key_id_DIRNAME/union_type_parameters.ts" as __memo_id_type), 3);
    const __memo_parameter_param1 = __memo_scope.param(0, param1);
    const __memo_parameter_param2 = __memo_scope.param(1, param2);
    const __memo_parameter_param3 = __memo_scope.param(2, param3);
    if (__memo_scope.unchanged) {
        __memo_scope.cached;
        return;
    }
    __memo_parameter_param1.value?.(__memo_context, __memo_id + ("0___key_id_DIRNAME/union_type_parameters.ts" as __memo_id_type));
    __memo_parameter_param2.value?.(__memo_context, __memo_id + ("1___key_id_DIRNAME/union_type_parameters.ts" as __memo_id_type));
    __memo_parameter_param3.value?.(__memo_context, __memo_id + ("2___key_id_DIRNAME/union_type_parameters.ts" as __memo_id_type));
    {
        __memo_scope.recache();
        return;
    }
}

