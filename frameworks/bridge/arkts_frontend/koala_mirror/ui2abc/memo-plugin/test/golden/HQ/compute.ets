
import { __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type, __hash as __hash } from "@koalaui/runtime";

import { memo as memo } from "@koalaui/runtime/annotations";

function main(): void {}



class Test {
  @memo() public compute_test(__memo_context: __memo_context_type, __memo_id: __memo_id_type, @memo() arg1: (((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void) | undefined), arg2: ((()=> void) | undefined), content: ((()=> void) | undefined)): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_compute_test_@test/HQ/compute.ets"))), 3);
    const __memo_parameter_this = __memo_scope.param(0, this), __memo_parameter_arg1 = __memo_scope.param(1, arg1), __memo_parameter_arg2 = __memo_scope.param(2, arg2);
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
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_test_@test/HQ/compute.ets"))), 1);
    const __memo_parameter_this = __memo_scope.param(0, this);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
      return;
    }
    const test = new Test();
    test.compute_test(__memo_context, ((__memo_id) + (__hash("id_compute_test_@test/HQ/compute.ets"))), __memo_context.compute(((__memo_id) + (__hash("id_compute_test_@test/HQ/compute.ets"))), ((): ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void) => {
      return ((__memo_context: __memo_context_type, __memo_id: __memo_id_type): void => {
        const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id__@test/HQ/compute.ets"))), 0);
        if (__memo_scope.unchanged) {
          __memo_scope.cached;
          return;
        }
        {
          __memo_scope.recache();
          return;
        }
      });
    })), __memo_context.compute(((__memo_id) + (__hash("id_compute_test_@test/HQ/compute.ets"))), ((): (()=> void) => {
      return ((): void => {});
    })), ((): void => {}));
    {
      __memo_scope.recache();
      return;
    }
  }
  
  public constructor() {}
  
}

