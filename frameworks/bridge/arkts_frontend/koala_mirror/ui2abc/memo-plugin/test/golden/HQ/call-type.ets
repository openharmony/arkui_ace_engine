
import { __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type, __hash as __hash } from "@koalaui/runtime";

import { memo as memo } from "@koalaui/runtime/annotations";

function main(): void {}



type MemoType = @memo() ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void);

class Test {
  @memo() public type_alias(__memo_context: __memo_context_type, __memo_id: __memo_id_type, arg: MemoType): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_type_alias_@test/HQ/call-type.ets"))), 2);
    const __memo_parameter_this = __memo_scope.param(0, this), __memo_parameter_arg = __memo_scope.param(1, arg);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
      return;
    }
    __memo_parameter_arg.value(__memo_context, ((__memo_id) + (__hash("id_arg_@test/HQ/call-type.ets"))));
    {
      __memo_scope.recache();
      return;
    }
  }
  
  public constructor() {}
  
}

