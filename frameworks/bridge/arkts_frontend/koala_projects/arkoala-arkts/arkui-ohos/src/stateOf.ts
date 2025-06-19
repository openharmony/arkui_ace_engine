import { mutableState, MutableState } from "@koalaui/runtime";
import { observableProxy } from "@koalaui/common"
import { ArkCustomComponent } from "./ArkCustomComponent"

/**
 * So what's going on here? We need to create states that persists across
 * routing and lifecycle events. To achieve that we create `ValueStorage`
 * instance and make it a router-local variable. As these variables persists
 * across routing, so we'll get stable values.
 */
export function stateOf<Value>(value: Value, instance?: ArkCustomComponent, index?: number): MutableState<Value> {
    return mutableState(observableProxy(value))
}
