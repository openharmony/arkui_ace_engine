import { memo } from "@koalaui/runtime/annotations"

import { function_returning_local_type } from "./test"

@memo function function_with_implicit_return_type() {
    return function_returning_local_type()
}
