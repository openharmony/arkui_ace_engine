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
import {AnimationExtender, AnimateParam} from '../framework'
import { int32 } from "@koalaui/common"
import { runtimeType, RuntimeType, KPointer } from "@koalaui/interop"

export function _animateTo(param: AnimateParam, event: (() => void)): void {
    if (!event) {
        return;
    }
    let newEvent = ()=>{
        AnimationExtender.OpenImplicitAnimation(param);
        event();
    }
    addPartialUpdate(newEvent, param, (before: boolean) => {
        if (!before) {
            AnimationExtender.CloseImplicitAnimation();
        }
    })
}

export function _animationStart(node: KPointer | undefined, param: AnimateParam | undefined, isFirstBuild: boolean) {
    if (isFirstBuild || node === undefined) {
        return
    }
    let ptr: KPointer = node as KPointer;
    AnimationExtender.OpenImplicitAnimationForAnimation(ptr, param);
}

export function _animationStop(node: KPointer | undefined, value: AnimateParam | undefined, isFirstBuild: boolean): void {
    if (isFirstBuild || node === undefined) {
        return
    }
    let ptr: KPointer = node as KPointer;
    AnimationExtender.CloseImplicitAnimationForAnimation(ptr);
}