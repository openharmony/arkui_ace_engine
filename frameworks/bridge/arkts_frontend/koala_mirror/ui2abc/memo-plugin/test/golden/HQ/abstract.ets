
import { __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type, __hash as __hash } from "@koalaui/runtime";

import { memo as memo } from "@koalaui/runtime/annotations";

function main(): void {}

@memo() ((__memo_context: __memo_context_type, __memo_id: __memo_id_type): void => {
  const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id__@test/HQ/abstract.ets"))), 0);
  if (__memo_scope.unchanged) {
    __memo_scope.cached;
    return;
  }
  new AA().x(__memo_context, ((__memo_id) + (__hash("id_x_@test/HQ/abstract.ets"))));
  const a: A = new AA();
  a.x(__memo_context, ((__memo_id) + (__hash("id_x_@test/HQ/abstract.ets"))));
  {
    __memo_scope.recache();
    return;
  }
});

declare abstract class A {
  @memo() public x(__memo_context: __memo_context_type, __memo_id: __memo_id_type): void
  
  public test_signature(@memo() arg1: ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void), @memo() arg2: (((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void) | undefined), @memo() arg3: ((((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void) | undefined) | (((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> int) | undefined)), @memo() x: ((__memo_context: __memo_context_type, __memo_id: __memo_id_type, y: ((z: @memo() ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void))=> void))=> void)): @memo() ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void)
  
  public constructor() {}
  
}

class AA extends A {
  @memo() public x(__memo_context: __memo_context_type, __memo_id: __memo_id_type): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_x_@test/HQ/abstract.ets"))), 1);
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
  
  public constructor() {}
  
}

