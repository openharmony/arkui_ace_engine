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

public let EMPTY_RUNNABLE: () -> Unit = {=>}
public let MEMO_UNIT: Unit = ()

public interface MemoScope<Value> {
    /** @returns true if internal value can be returned as is */
    func isUnchanged(): Bool
    /** @returns internal value if it is already computed */
    func getCached(): Value
    /** @returns internal value updated after the computation */
    func recache(newValue: Value): Value
}

public func getMemoScope<Value>(id: CallsiteKey, paramCount: Int64): MemoScope<Value> {
    getMemoScope(id, paramCount, None, None, None, false)
}

func getMemoScope<Value>(
    id: CallsiteKey,
    paramCount: Int64,
    create: ?() -> IncrementalNode,
    compute: ?() -> Value,
    cleanup: ?(value: ?Value) -> Unit,
    once: Bool
): ScopeImpl<Value> {
    let scope = getManagedScope {"enter scope(${id.text})"}
    scope.getChildScope<Value>(id, paramCount, create, compute, cleanup, once)
}

/** @returns internal state for parameter */
public func getParameter<Value, Scope>(scope: MemoScope<Scope>, index: Int64, value: Value): State<Value> {
    getParameter<Value, Scope>(scope, index, value, None)
}

public func getParameter<Value, Scope>(scope: MemoScope<Scope>, index: Int64, value: Value, name: ?String): State<Value> {
    if (let Some(scope) <- (scope as ManagedScope)) {
        return scope.param<Value>(index, value, name)
    } else {
        throw IllegalStateException("unexpected scope provided")
    }
}
