
import { __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type, __hash as __hash } from "@koalaui/runtime";

import { memo as memo } from "@koalaui/runtime/annotations";

import { function_returning_local_type as function_returning_local_type } from "./test";

function main() {}


@memo() function function_with_implicit_return_type(__memo_context: __memo_context_type, __memo_id: __memo_id_type) {
  const __memo_scope = __memo_context.scope<C>(((__memo_id) + (__hash("id_function_with_implicit_return_type_@test/input/implicit-type/main.ets"))), 0);
  if (__memo_scope.unchanged) {
    return __memo_scope.cached;
  }
  return __memo_scope.recache(function_returning_local_type(__memo_context, ((__memo_id) + (__hash("id_function_returning_local_type_@test/input/implicit-type/main.ets")))));
}


