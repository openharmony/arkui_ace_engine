
import { __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type, __hash as __hash } from "@koalaui/runtime";

import { memo as memo } from "@koalaui/runtime/annotations";

function main(): void {}



class Test {
  @memo() public void_method_with_return(__memo_context: __memo_context_type, __memo_id: __memo_id_type, arg: string): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_void_method_with_return_@test/HQ/void-method-with-return.ets"))), 2);
    const __memo_parameter_this = __memo_scope.param(0, this), __memo_parameter_arg = __memo_scope.param(1, arg);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
      return;
    }
    {
      __memo_scope.recache();
      return;
    }
  }
  
  public constructor() {}
  
}

class Use {
  @memo() public test(__memo_context: __memo_context_type, __memo_id: __memo_id_type): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_test_@test/HQ/void-method-with-return.ets"))), 1);
    const __memo_parameter_this = __memo_scope.param(0, this);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
      return;
    }
    const test = new Test();
    test.void_method_with_return(__memo_context, ((__memo_id) + (__hash("id_void_method_with_return_@test/HQ/void-method-with-return.ets"))), "a value");
    {
      __memo_scope.recache();
      return;
    }
  }
  
  public constructor() {}
  
}

