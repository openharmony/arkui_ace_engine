
import { __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type, __hash as __hash } from "@koalaui/runtime";

import { memo as memo } from "@koalaui/runtime/annotations";

function main(): void {}



class Test {
  @memo() public args_with_default_values(__memo_context: __memo_context_type, __memo_id: __memo_id_type, gensym_XXX?: int, gensym_XXX?: (()=> int), gensym_XXX?: int, arg4?: int): void {
    let arg1: int = (((gensym_XXX) !== (undefined)) ? gensym_XXX : (10 as int));
    let arg2: (()=> int) = (((gensym_XXX) !== (undefined)) ? gensym_XXX : ((() => {
      return 20;
    }) as (()=> int)));
    let arg3: int = (((gensym_XXX) !== (undefined)) ? gensym_XXX : (arg1 as int));
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_args_with_default_values_@test/HQ/param-calls.ets"))), 5);
    const __memo_parameter_this = __memo_scope.param(0, this), __memo_parameter_arg1 = __memo_scope.param(1, arg1), __memo_parameter_arg2 = __memo_scope.param(2, arg2), __memo_parameter_arg3 = __memo_scope.param(3, arg3), __memo_parameter_arg4 = __memo_scope.param(4, arg4);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
      return;
    }
    console.log(__memo_parameter_arg1.value, __memo_parameter_arg2.value, __memo_parameter_arg3.value, __memo_parameter_arg4.value);
    console.log(__memo_parameter_arg2.value());
    {
      __memo_scope.recache();
      return;
    }
  }
  
  public constructor() {}
  
}

