import { memo, memo_entry } from "@koalaui/runtime/annotations"
import { __context, __id, __memo_context_type, __memo_id_type } from "@koalaui/runtime"

class Test {
    @memo_entry memoEntry<R>(__memo_context: __memo_context_type, __memo_id: __memo_id_type, @memo entry: () => R): R {
        const getContext = () => {
            return __context()
        }
        const getId = () => {
            return __id()
        }
        {
            const __memo_context = getContext()
            const __memo_id = getId()
            return entry()
        }
    }
}
