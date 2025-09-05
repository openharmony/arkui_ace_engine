
import { __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type, __hash as __hash } from "@koalaui/runtime";

import { memo as memo } from "@koalaui/runtime/annotations";

function main(): void {}

@memo() ((__memo_context: __memo_context_type, __memo_id: __memo_id_type): void => {
  const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id__@test/HQ/non-memo-interface-property.ets"))), 0);
  if (__memo_scope.unchanged) {
    __memo_scope.cached;
    return;
  }
  let a: A = {
    arg: ((): void => {}),
  };
  {
    __memo_scope.recache();
    return;
  }
});

interface A {
  set arg(arg: (()=> void))
  
  get arg(): (()=> void)
  
}

