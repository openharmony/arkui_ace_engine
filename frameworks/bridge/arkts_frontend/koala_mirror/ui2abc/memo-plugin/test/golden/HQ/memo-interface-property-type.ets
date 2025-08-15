
import { __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type, __hash as __hash } from "@koalaui/runtime";

import { memo as memo } from "@koalaui/runtime/annotations";

function main() {}


interface A {
  set arg_memo_type(arg_memo_type: @memo() ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void))
  
  get arg_memo_type(): @memo() ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> void)
  
}

