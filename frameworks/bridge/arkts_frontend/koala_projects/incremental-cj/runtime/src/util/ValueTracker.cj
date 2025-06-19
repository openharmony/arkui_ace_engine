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
package KoalaRuntime.util

/**
 * The interface allows to track the values assigned to a state.
 */
public interface ValueTracker<Value> {
    /**
     * Tracks state creation.
     * @param value - an initial state value
     * @returns the same value or a modified one
     */
    func onCreate(value: Value): Value
    /**
     * Tracks state updates.
     * @param value - a value to set to state
     * @returns the same value or a modified one
     */
    func onUpdate(value: Value): Value
}

public func equalValues<Value>(v1: Value, v2: Value): Bool {
    if (v1 is Unit && v2 is Unit) {
        return true
    }
    if (let Some(e) <- (v1 as Equatable<Value>)) {
        return e == v2 // Value is Equatable
    }
    if (let Some(o1) <- (v1 as Object)) {
        if (let Some(o2) <- (v2 as Object)) {
            return refEq(o1, o2)
        }
    }
    // values of unsupported type are always different
    false // throw IllegalStateException("unsupported type")
}
