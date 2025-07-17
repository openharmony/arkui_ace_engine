
import { __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type, __hash as __hash } from "@koalaui/runtime";

import { memo as memo } from "@koalaui/runtime/annotations";

function main(): void {}

@memo() ((__memo_context: __memo_context_type, __memo_id: __memo_id_type): void => {
  const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id__@test/HQ/instantiate.ets"))), 0);
  if (__memo_scope.unchanged) {
    __memo_scope.cached;
    return;
  }
  let x: (C | D) = C.$_instantiate(__memo_context, ((__memo_id) + (__hash("id_$_instantiate_@test/HQ/instantiate.ets"))), __memo_context.compute(((__memo_id) + (__hash("id_$_instantiate_@test/HQ/instantiate.ets"))), (() => {
    return (() => {
      return new C();
    });
  })));
  x = D.$_instantiate((() => {
    return new D();
  }));
  {
    __memo_scope.recache();
    return;
  }
});

class C {
  @memo() public static $_instantiate(__memo_context: __memo_context_type, __memo_id: __memo_id_type, factory: (()=> C)): C {
    const __memo_scope = __memo_context.scope<C>(((__memo_id) + (__hash("id_$_instantiate_@test/HQ/instantiate.ets"))), 1);
    const __memo_parameter_factory = __memo_scope.param(0, factory);
    if (__memo_scope.unchanged) {
      return __memo_scope.cached;
    }
    return __memo_scope.recache(__memo_parameter_factory.value());
  }
  
  public constructor() {}
  
}

class D {
  public static $_instantiate(factory: (()=> D), @memo() content?: ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void)): D {
    return factory();
  }
  
  public constructor() {}
  
}

