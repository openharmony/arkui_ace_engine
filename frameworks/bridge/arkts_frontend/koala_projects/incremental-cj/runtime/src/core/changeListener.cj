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
 * Executes the specified function if the given value has changed.
 * Unlike {@link RunEffect}, the specified function is not executed at the first pass during initialization.
 * @param value - a trackable value to listen changes
 * @param listener - a function to perform if the given value has changed
 * @memo:intrinsic
 */
public func OnChange<Value>(value: Value, listener: (value: Value) -> Unit): Unit {
    watch(getCallsiteKey(), false, value, listener)
}

/**
 * Executes the specified function if the given value has changed or initialized.
 * Unlike {@link OnChange} this function is also executed from the first pass.
 * @param value - a value controlling if effect shall run
 * @param effect - a function to perform if the given value has changed or initialized
 * @memo:intrinsic
 */
public func RunEffect<Value>(value: Value, effect: (value: Value) -> Unit): Unit {
    watch(getCallsiteKey(), true, value, effect)
}

func watch<Value>(key: CallsiteKey, modified: Bool, value: Value, callback: (value: Value) -> Unit): Unit {
    let scope = getMemoScope<Unit>(key, 1, None, None, None, false)
    let state = scope.param(0, value)
    if (scope.isUnchanged()) {
        scope.getCached()
    } else {
        if (state.isModified() || modified) {
            scheduleCallback {callback(value)}
        }
        scope.recache(MEMO_UNIT)
    }
}
