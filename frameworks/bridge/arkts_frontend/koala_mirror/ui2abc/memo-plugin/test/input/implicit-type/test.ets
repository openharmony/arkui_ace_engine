import { memo } from "@koalaui/runtime/annotations"

class C {

}

@memo export function function_returning_local_type() {
    return new C()
}
