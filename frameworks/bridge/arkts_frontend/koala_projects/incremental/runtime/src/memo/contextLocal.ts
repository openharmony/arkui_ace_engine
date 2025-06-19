/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { __context, __id } from "../internals"
import { State } from "../states/State"

/**
 * @param name - a name of a context state
 * @returns the named context state or `undefined` if it does not exist
 */
/** @memo:intrinsic */
export function contextLocal<Value>(name: string): State<Value> | undefined {
    return __context().stateBy<Value>(name)
}

/**
 * @param name - a name of a context state
 * @returns a value of a context state
 * @throws Error if a named context state does not exist
 */
/** @memo:intrinsic */
export function contextLocalValue<Value>(name: string): Value {
    return __context().valueBy<Value>(name)
}

/**
 * Creates a named state with the specified value in the context scope.
 * The specified value will be propagated immediately during recomposition.
 * Note that the state name must not be dynamically changed.
 *
 * @param name - a name of a context state
 * @param value - a value of a named state to share within the given content
 * @param content - a scope content in which a named state is available
 */
/** @memo:intrinsic */
export function contextLocalScope<Value>(
    name: string,
    value: Value,
    /** @memo */
    content: () => void
) {
    const scope = __context().scope<void>(__id(), 1)
    scope.param<Value>(0, value, undefined, name, true) // can be found by name
    if (scope.unchanged) {
        scope.cached
    } else {
        content()
        scope.recache()
    }
}
