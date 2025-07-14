
import { __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type, __hash as __hash } from "@koalaui/runtime";

import { memo as memo } from "@koalaui/runtime/annotations";

function main(): void {}



class A {
  public x: int;
  
  public y: int;
  
  public constructor() {}
  
}

class Test {
  @memo() public obj_arg(__memo_context: __memo_context_type, __memo_id: __memo_id_type, arg: A): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_obj_arg_@test/HQ/object-param.ets"))), 2);
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
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_test_@test/HQ/object-param.ets"))), 1);
    const __memo_parameter_this = __memo_scope.param(0, this);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
      return;
    }
    const test = new Test();
    test.obj_arg(__memo_context, ((__memo_id) + (__hash("id_obj_arg_@test/HQ/object-param.ets"))), __memo_context.compute(((__memo_id) + (__hash("id_obj_arg_@test/HQ/object-param.ets"))), ((): A => {
      return ({
        x: 1,
        y: 2,
      } as A);
    })));
    {
      __memo_scope.recache();
      return;
    }
  }
  
  public constructor() {}
  
}

