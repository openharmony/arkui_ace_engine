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
import {AnimationExtender, AnimateParam} from '../generated'

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

export function _animationStart(param: AnimateParam, isFirstBuild: boolean) {
    if (isFirstBuild) {
        return
    }
    AnimationExtender.OpenImplicitAnimation(param);
}

export function _animationEnd(isFirstBuild: boolean, update: (() => void)): void {
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