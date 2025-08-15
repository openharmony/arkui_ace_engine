
import { __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type, __hash as __hash } from "@koalaui/runtime";

import { memo as memo, memo_skip as memo_skip } from "@koalaui/runtime/annotations";

function main() {}

@memo() function memo_function(__memo_context: __memo_context_type, __memo_id: __memo_id_type, @memo_skip() param: (Builder | string)): void {
  const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_memo_function_primitive.ets"))), 0);
  if (__memo_scope.unchanged) {
    __memo_scope.cached;
    return;
  }
  if (((param) instanceof (Builder))) {
    param(__memo_context, ((__memo_id) + (__hash("id_param_primitive.ets"))));
  } else {
    param;
  }
  {
    __memo_scope.recache();
    return;
  }
}

@memo() function callsite(__memo_context: __memo_context_type, __memo_id: __memo_id_type): void {
  const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id_callsite_primitive.ets"))), 0);
  if (__memo_scope.unchanged) {
    __memo_scope.cached;
    return;
  }
  memo_function(__memo_context, ((__memo_id) + (__hash("id_memo_function_primitive.ets"))), ((__memo_context: __memo_context_type, __memo_id: __memo_id_type) => {
    const __memo_scope = __memo_context.scope<void>(((__memo_id) + (__hash("id__primitive.ets"))), 0);
    if (__memo_scope.unchanged) {
      __memo_scope.cached;
      return;
    }
    {
      __memo_scope.recache();
      return;
    }
  }));
  memo_function(__memo_context, ((__memo_id) + (__hash("id_memo_function_primitive.ets"))), "hello");
  {
    __memo_scope.recache();
    return;
  }
}


type Builder = @memo() ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void);

