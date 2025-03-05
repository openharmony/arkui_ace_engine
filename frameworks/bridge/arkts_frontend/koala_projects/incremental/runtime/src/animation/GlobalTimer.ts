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

import { int64 } from "@koalaui/common"
import { GlobalStateManager } from "../states/GlobalStateManager"
import { MutableState, StateContext } from "../states/State"

const GLOBAL_ANIMATION_TIMER = "ohos.koala.runtime.global.animation.timer"

/**
 * @returns the state for the global animation timer, or `undefined`
 * @internal
 */
export function getAnimationTimer(context: StateContext = GlobalStateManager.instance): MutableState<int64> | undefined {
    return context.stateBy<int64>(GLOBAL_ANIMATION_TIMER, true)
}

/**
 * @param initial - initial timestamp for a timer
 * @returns new state for the global animation timer
 * @throws an error if it is already initialized
 * @internal
 */
export function createAnimationTimer(context: StateContext, initial: int64 = 0): MutableState<int64> {
    if (getAnimationTimer(context)) throw new Error("the global animation timer is already initialized")
    return context.namedState(GLOBAL_ANIMATION_TIMER, () => initial, true)
}
