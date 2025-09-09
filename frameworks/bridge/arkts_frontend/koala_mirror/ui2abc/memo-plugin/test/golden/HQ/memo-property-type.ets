
import { __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type, __hash as __hash } from "@koalaui/runtime";

import { memo as memo } from "@koalaui/runtime/annotations";

function main(): void {}



class A {
  public arg_memo_type: @memo() ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void);
  
  public constructor() {
    this.arg_memo_type = ((): void => {});
  }
  
  @memo() public build(__memo_context: __memo_context_type, __memo_id: __memo_id_type): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_build_@test/HQ/memo-property-type.ets"))), 1);
    const __memo_parameter_this = __memo_scope.param(0, this);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
      return;
    }
    __memo_parameter_this.value.arg_memo_type();
    {
      __memo_scope.recache();
      return;
    }
  }
  
}

