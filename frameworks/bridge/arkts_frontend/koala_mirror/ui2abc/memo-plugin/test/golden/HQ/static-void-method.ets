
import { __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type, __hash as __hash } from "@koalaui/runtime";

import { memo as memo } from "@koalaui/runtime/annotations";

function main(): void {}



class Test {
  @memo() public static static_method_with_type_parameter<T>(__memo_context: __memo_context_type, __memo_id: __memo_id_type, arg: T): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_static_method_with_type_parameter_@test/HQ/static-void-method.ets"))), 1);
    const __memo_parameter_arg = __memo_scope.param(0, arg);
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
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_test_@test/HQ/static-void-method.ets"))), 1);
    const __memo_parameter_this = __memo_scope.param(0, this);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
      return;
    }
    Test.static_method_with_type_parameter(__memo_context, ((__memo_id) + (__hash("id_static_method_with_type_parameter_@test/HQ/static-void-method.ets"))), "I'm static");
    {
      __memo_scope.recache();
      return;
    }
  }
  
  public constructor() {}
  
}

