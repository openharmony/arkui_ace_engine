/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

import { KoalaCallsiteKey } from "@koalaui/common"
import { scheduleCallback } from "../states/GlobalStateManager"
import { StateContext } from "../states/State"
import { __context, __id } from "../internals"

/**
 * Executes the specified function if the given value has changed.
 * Unlike {@link RunEffect}, the specified function is not executed at the first pass during initialization.
 * @param value - a trackable value to listen changes
 * @param listener - a function to perform if the given value has changed
 */
/** @memo:intrinsic */
export function OnChange<Value>(value: Value, listener: (value: Value) => void): void {
    watch(__context(), __id(), false, value, listener)
}

/**
 * Executes the specified function if the given value has changed or initialized.
 * Unlike {@link OnChange} this function is also executed from the first pass.
 * @param value - a value controlling if effect shall run
 * @param effect - a function to perform if the given value has changed or initialized
 */
/** @memo:intrinsic */
export function RunEffect<Value>(value: Value, effect: (value: Value) => void): void {
    watch(__context(), __id(), true, value, effect)
}

function watch<Value>(context: StateContext, id: KoalaCallsiteKey, modified: boolean, value: Value, listener: (value: Value) => void) {
    const scope = context.scope<void>(id, 1)
    const state = scope.param<Value>(0, value)
    if (scope.unchanged) {
        scope.cached
    } else {
        if (state.modified || modified) scheduleCallback(() => listener(value))
        scope.recache()
    }
}
