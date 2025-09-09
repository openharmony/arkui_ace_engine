
import { __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type, __hash as __hash } from "@koalaui/runtime";

import { memo as memo } from "@koalaui/runtime/annotations";

function main(): void {}



class A {
  @memo() public memo_arg: ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void);
  
  public constructor() {
    this.memo_arg = ((): void => {});
  }
  
  @memo() public build(__memo_context: __memo_context_type, __memo_id: __memo_id_type): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_build_@test/HQ/memo-property.ets"))), 1);
    const __memo_parameter_this = __memo_scope.param(0, this);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
      return;
    }
    __memo_parameter_this.value.memo_arg(__memo_context, ((__memo_id) + (__hash("id_memo_arg_@test/HQ/memo-property.ets"))));
    {
      __memo_scope.recache();
      return;
    }
  }
  
}

