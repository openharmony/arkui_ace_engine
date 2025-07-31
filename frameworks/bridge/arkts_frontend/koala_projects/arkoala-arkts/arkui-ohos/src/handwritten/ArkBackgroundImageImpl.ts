/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { int32 } from "@koalaui/common"
import { contextNode, remember, scheduleCallback } from "@koalaui/runtime"
import { PeerNode, PeerNodeType } from "../PeerNode"
import { rememberMutableState } from '@koalaui/runtime';
import { KPointer } from "@koalaui/interop"
import { ArkCommonMethodComponent, ResourceStr, CommonMethod, StateStylesOps, ArkCommonMethodPeer } from '../component'
import { InteropNativeModule } from "@koalaui/interop"
import { ArkCommonAttributeSet } from "./modifiers/ArkCommonModifier";
import { PointerStyle, UnifiedData, Summary, PixelMap } from "#external"
import { ImageRepeat } from "../component/enums"
import { TypeChecker } from "#components"
import { runtimeType, RuntimeType } from "@koalaui/interop"
import { ArkUIAniModule } from "arkui.ani"

export function hookBackgroundImageImpl(node: ArkCommonMethodComponent, src: ResourceStr | PixelMap | undefined, repeat?: ImageRepeat | undefined): void {
    const src_type = runtimeType(src)
    const repeat_type = runtimeType(repeat)
    if (((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type) || (RuntimeType.OBJECT == src_type) || (RuntimeType.UNDEFINED == src_type)) && ((RuntimeType.NUMBER == repeat_type) || (RuntimeType.OBJECT == repeat_type))) {
        const src_casted = src as (ResourceStr | PixelMap | undefined)
        const repeat_casted = repeat as (ImageRepeat)
        if (TypeChecker.isPixelMap(src_casted, false, false)) {
            const src_0 = src as PixelMap
            let repeatValue: int32 = 0
            let repeat_type: int32 = RuntimeType.UNDEFINED
            repeat_type = runtimeType(repeat)
            if ((RuntimeType.UNDEFINED) != (repeat_type)) {
                const repeat_value = (repeat as ImageRepeat)
                repeatValue = TypeChecker.ImageRepeat_ToNumeric(repeat_value)
            }
            ArkUIAniModule._BackgroundImage_PixelMap(node.getPeer().getPeerPtr(), src_0, repeatValue)
            return
        } else {
            node.getPeer()?.backgroundImage0Attribute(src_casted, repeat_casted)
        }
    }
}

export function hookModifierBackgroundImageImpl(node: ArkCommonMethodPeer, src: ResourceStr | PixelMap | undefined, repeat?: ImageRepeat | undefined): void {
    const src_type = runtimeType(src)
    const repeat_type = runtimeType(repeat)
    if (((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type) || (RuntimeType.OBJECT == src_type) || (RuntimeType.UNDEFINED == src_type)) && ((RuntimeType.NUMBER == repeat_type) || (RuntimeType.OBJECT == repeat_type))) {
        const src_casted = src as (ResourceStr | PixelMap | undefined)
        const repeat_casted = repeat as (ImageRepeat)
        if (TypeChecker.isPixelMap(src_casted, false, false)) {
            const src_0 = src as PixelMap
            let repeatValue: int32 = 0
            let repeat_type: int32 = RuntimeType.UNDEFINED
            repeat_type = runtimeType(repeat)
            if ((RuntimeType.UNDEFINED) != (repeat_type)) {
                const repeat_value = (repeat as ImageRepeat)
                repeatValue = TypeChecker.ImageRepeat_ToNumeric(repeat_value)
            }
            ArkUIAniModule._BackgroundImage_PixelMap(node.peer.ptr, src_0, repeatValue)
            return
        } else {
            node.backgroundImage0Attribute(src_casted, repeat_casted)
        }
    }
}