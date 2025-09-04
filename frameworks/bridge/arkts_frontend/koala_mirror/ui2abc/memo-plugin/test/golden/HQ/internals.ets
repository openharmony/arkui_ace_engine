
import { __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type, __hash as __hash } from "@koalaui/runtime";

import { memo as memo } from "@koalaui/runtime/annotations";

import { __context as __context, __id as __id } from "@koalaui/runtime";

function main(): void {}



class Test {
  @memo() public method_with_internals(__memo_context: __memo_context_type, __memo_id: __memo_id_type): void {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_method_with_internals_@test/HQ/internals.ets"))), 1);
    const __memo_parameter_this = __memo_scope.param(0, this);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
      return;
    }
    __memo_context;
    __memo_id;
    {
      __memo_scope.recache();
      return;
    }
  }
  
  public constructor() {}
  
}

