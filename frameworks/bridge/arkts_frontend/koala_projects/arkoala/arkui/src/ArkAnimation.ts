/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import { addPartialUpdate, wrapCallback } from "@koalaui/arkoala"
import { Access, withFloat32Array, KFloat32ArrayPtr } from "@koalaui/interop"
import { ArkAnimate } from "./shared/basic"
import { int32 } from "@koalaui/common"

export function startImplicitAnimations(param: AnimateParam) {
    console.log("start implicit", param)

    let animate = new ArkAnimate(param)
    withFloat32Array(animate.animateOptions, Access.READ, (value: KFloat32ArrayPtr) => {
        if (value) {
            let methodId = -1
            if (param.onFinish) {
                methodId = wrapCallback((args1: Uint8Array, length: int32) => {
                    param.onFinish!()
                    return 0
                })
            }
            //nativeModule()._OpenImplicitAnimation(animate.curve, value, methodId)
        }
    })
}

export function endImplicitAnimation() {
    console.log("end implicit")
    //nativeModule()._CloseImplicitAnimation()
}

export function animateTo(param: AnimateParam, callback: () => void): void {
    addPartialUpdate(callback, param, (before: boolean) => {
        if (before) {
            startImplicitAnimations(param)
        } else {
            endImplicitAnimation()
        }
    })
}
