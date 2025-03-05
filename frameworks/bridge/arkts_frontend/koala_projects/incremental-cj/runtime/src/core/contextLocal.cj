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
package KoalaRuntime.core

/**
 * @param name - a name of a context state
 * @returns the named context state or `undefined` if it does not exist
 * @memo:intrinsic
 */
public func contextLocal<Value>(name: String): ?State<Value> {
    getManagedScope {"get context local state"}
    match (namedStateBy<Value>(name)) {
        case Some(state) => state
        case None => None
    }
}

/**
 * @param name - a name of a context state
 * @returns a value of a context state
 * @throws IllegalStateException if a named context state does not exist
 * @memo:intrinsic
 */
public func contextLocalValue<Value>(name: String): Value {
    getManagedScope {"get context local value"}
    namedValueBy<Value>(name)
}

/**
 * Creates a named state with the specified value in the context scope.
 * The specified value will be propagated immediately during recomposition.
 * Note that the state name must not be dynamically changed.
 *
 * @param name - a name of a context state
 * @param value - a value of a named state to share within the given content
 * @param content - a scope content in which a named state is available
 * @memo:intrinsic
 */
public func contextLocalScope<Value>(name: String, value: Value, content: () -> Unit): Unit {
    let scope = getMemoScope<Unit>(getCallsiteKey(), 1, None, content, None, false)
    scope.param(0, value, name, true)
    scope.getValue()
}
