
import { __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type, __hash as __hash } from "@koalaui/runtime";

import { memo as memo } from "@koalaui/runtime/annotations";

function main(): void {}



class Test {
  @memo() public lambda_arg(__memo_context: __memo_context_type, __memo_id: __memo_id_type, @memo() arg: ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void)): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_lambda_arg_@test/HQ/void-compute.ets"))), 2);
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
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_test_@test/HQ/void-compute.ets"))), 1);
    const __memo_parameter_this = __memo_scope.param(0, this);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
      return;
    }
    const test = new Test();
    test.lambda_arg(__memo_context, ((__memo_id) + (__hash("id_lambda_arg_@test/HQ/void-compute.ets"))), __memo_context.compute(((__memo_id) + (__hash("id_lambda_arg_@test/HQ/void-compute.ets"))), ((): ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void) => {
      return ((__memo_context: __memo_context_type, __memo_id: __memo_id_type): void => {
        const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id__@test/HQ/void-compute.ets"))), 0);
        if (__memo_scope.unchanged) {
          __memo_scope.cached;
          return;
        }
        {
          __memo_scope.recache();
          return;
        }
      });
    })));
    {
      __memo_scope.recache();
      return;
    }
  }
  
  public constructor() {}
  
}

