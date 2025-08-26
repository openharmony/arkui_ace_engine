
import { __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type, __hash as __hash } from "@koalaui/runtime";

import { memo as memo } from "@koalaui/runtime/annotations";

function main() {}


@memo() function memo_function(__memo_context: __memo_context_type, __memo_id: __memo_id_type, @memo() param: (((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void) | undefined)): void {
  const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_memo_function_@test/input/param-usage/on-param/memo-on-possibly-undefined-param.ets"))), 1);
  const __memo_parameter_param = __memo_scope.param(0, param);
  if (__memo_scope.unchanged) {
    __memo_scope.cached;
    return;
  }
  ({let gensym_XXX = __memo_parameter_param.value;
  (((gensym_XXX) == (null)) ? undefined : gensym_XXX(__memo_context, ((__memo_id) + (__hash("id_param_@test/input/param-usage/on-param/memo-on-possibly-undefined-param.ets")))))});
  {
    __memo_scope.recache();
    return;
  }
}


