
import { __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type, __hash as __hash } from "@koalaui/runtime";

import { memo as memo } from "@koalaui/runtime/annotations";

function main() {}

@memo() ((__memo_context: __memo_context_type, __memo_id: __memo_id_type) => {
  const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id__@test/input/HQ/memo-interface-property-union-type.ets"))), 0);
  if (__memo_scope.unchanged) {
    __memo_scope.cached;
    return;
  }
  let a: A = {
    memo_union_arg: (() => {}),
  };
  {
    __memo_scope.recache();
    return;
  }
});

interface A {
  @memo() set memo_union_arg(memo_union_arg: (((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void) | undefined))
  
  @memo() get memo_union_arg(): (((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void) | undefined)
  
}

