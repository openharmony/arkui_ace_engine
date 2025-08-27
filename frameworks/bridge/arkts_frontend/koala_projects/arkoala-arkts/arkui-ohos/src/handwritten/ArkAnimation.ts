/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import {addPartialUpdate} from '../ArkUIEntry'
import {AnimationExtender, AnimateParam} from '../component'
import { int32 } from "@koalaui/common"
import { runtimeType, RuntimeType } from "@koalaui/interop"

export function _animateTo(param: AnimateParam, event: (() => void)): void {
    if (!event) {
        return;
    }
    AnimationExtender.OpenImplicitAnimation(param);
    event();
    addPartialUpdate(event, param, (before: boolean) => {
        if (!before) {
            AnimationExtender.CloseImplicitAnimation();
        }
    })
}

export function _animationStart(param: AnimateParam | undefined, isFirstBuild: boolean) {
    if (isFirstBuild) {
        return
    }
    let value_type : int32 = RuntimeType.UNDEFINED
    value_type = runtimeType(param)
    if ((RuntimeType.UNDEFINED) != (value_type)) {
        const value_value  = (param as AnimateParam)
        AnimationExtender.OpenImplicitAnimation(value_value);
    }
}

export function _animationStop(value: AnimateParam | undefined, isFirstBuild: boolean, update: (() => void)): void {
    let value_type : int32 = RuntimeType.UNDEFINED
    value_type = runtimeType(value)
    if ((RuntimeType.UNDEFINED) == (value_type)) {
        if (isFirstBuild) {
            update();
        }
        return;
    }

    let param: AnimateParam = {}
    addPartialUpdate(() => {}, param, (before: boolean) => {
        if (before) {
            return
        }
        if (isFirstBuild) {
            update();
            return;
        }
        AnimationExtender.CloseImplicitAnimation()
    })
}