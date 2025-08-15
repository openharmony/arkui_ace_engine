
import { __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type, __hash as __hash } from "@koalaui/runtime";

import { memo as memo } from "@koalaui/runtime/annotations";

function main() {}


interface A {
  @memo() set memo_optional_arg(memo_optional_arg: (((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void) | undefined))
  
  @memo() get memo_optional_arg(): (((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void) | undefined)
  
}

