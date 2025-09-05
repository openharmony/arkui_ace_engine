
import { __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type, __hash as __hash } from "@koalaui/runtime";

import { memo as memo, memo_intrinsic as memo_intrinsic } from "@koalaui/runtime/annotations";

function main(): void {}



class Test {
  @memo() public void_method(__memo_context: __memo_context_type, __memo_id: __memo_id_type): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_void_method_@test/HQ/intrinsic-call.ets"))), 1);
    const __memo_parameter_this = __memo_scope.param(0, this);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
      return;
    }
    {
      __memo_scope.recache();
      return;
    }
  }
  
  @memo_intrinsic() public intrinsic_method_with_this(__memo_context: __memo_context_type, __memo_id: __memo_id_type): int {
    this.void_method(__memo_context, ((__memo_id) + (__hash("id_void_method_@test/HQ/intrinsic-call.ets"))));
    return 0;
  }
  
  public constructor() {}
  
}

