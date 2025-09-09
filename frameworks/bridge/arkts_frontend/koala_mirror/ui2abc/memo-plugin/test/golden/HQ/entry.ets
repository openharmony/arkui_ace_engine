
import { __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type, __hash as __hash } from "@koalaui/runtime";

import { memo as memo, memo_entry as memo_entry } from "@koalaui/runtime/annotations";

import { __context as __context, __id as __id, __memo_context_type as __memo_context_type, __memo_id_type as __memo_id_type } from "@koalaui/runtime";

function main(): void {}



class Test {
  @memo_entry() public memoEntry<R>(__memo_context: __memo_context_type, __memo_id: __memo_id_type, @memo() entry: ((__memo_context: __memo_context_type, __memo_id: __memo_id_type)=> R)): R {
    const getContext = (() => {
      return __memo_context;
    });
    const getId = (() => {
      return __memo_id;
    });
    {
      const __memo_context = getContext();
      const __memo_id = getId();
      return entry(__memo_context, ((__memo_id) + (__hash("id_entry_@test/HQ/entry.ets"))));
    }
  }
  
  public constructor() {}
  
}

