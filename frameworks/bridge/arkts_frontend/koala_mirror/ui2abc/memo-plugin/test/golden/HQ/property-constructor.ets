
import { __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type, __hash as __hash } from "@koalaui/runtime";

import { memo as memo } from "@koalaui/runtime/annotations";

function main(): void {}

@memo() ((__memo_context: __memo_context_type, __memo_id: __memo_id_type): void => {
  const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id__@test/HQ/property-constructor.ets"))), 0);
  if (__memo_scope.unchanged) {
    __memo_scope.cached;
    return;
  }
  let a = new AA({
    a: ((): void => {}),
  });
  {
    __memo_scope.recache();
    return;
  }
});

interface A {
  @memo() set a(a: ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void))
  
  @memo() get a(): ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void)
  
}

class AA {
  @memo() public a: (((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void) | undefined);
  
  constructor() {
    this(undefined);
  }
  
  public constructor(arg: (A | undefined)) {
    this.a = ({let gensym_XXX = arg;
    (((gensym_XXX) == (null)) ? undefined : gensym_XXX.a)});
  }
  
  @memo() public build(__memo_context: __memo_context_type, __memo_id: __memo_id_type): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_build_@test/HQ/property-constructor.ets"))), 1);
    const __memo_parameter_this = __memo_scope.param(0, this);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
      return;
    }
    ({let gensym_XXX = __memo_parameter_this.value.a;
    (((gensym_XXX) == (null)) ? undefined : gensym_XXX(__memo_context, ((__memo_id) + (__hash("id_a_@test/HQ/property-constructor.ets")))))});
    {
      __memo_scope.recache();
      return;
    }
  }
  
}

