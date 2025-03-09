/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { int32, float32 } from "@koalaui/common"
import { KStringPtr, KBoolean, RuntimeType, runtimeType } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ComponentBase } from "./../ComponentBase"
import { TypeChecker } from "#components"
import { ArkContainerSpanPeer } from "./peers/ArkContainerSpanPeer"
import { TextBackgroundStyle } from "./ArkSpanInterfaces"
import { AttributeModifier } from "./../handwritten"
import { ContainerSpanAttribute } from "./ArkContainerSpanInterfaces"
/** @memo:stable */
export class ArkContainerSpanComponent extends ComponentBase {
    getPeer(): ArkContainerSpanPeer {
        return (this.peer as ArkContainerSpanPeer)
    }
    /** @memo */
    public setContainerSpanOptions(): this {
        if (this.checkPriority("setContainerSpanOptions")) {
            this.getPeer()?.setContainerSpanOptionsAttribute()
            return this
        }
        return this
    }
    /** @memo */
    public textBackgroundStyle(value: TextBackgroundStyle): this {
        if (this.checkPriority("textBackgroundStyle")) {
            const value_casted = value as (TextBackgroundStyle)
            this.getPeer()?.textBackgroundStyleAttribute(value_casted)
            return this
        }
        return this
    }
    attributeModifier(modifier: AttributeModifier<object>): this { throw new Error("not implemented") }
    public applyAttributesFinish(): void {
        // we calls this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

/** @memo */
export function ArkContainerSpan(
  /** @memo */
  style: ((attributes: ArkContainerSpanComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  
) {
    const receiver = remember(() => {
        return new ArkContainerSpanComponent()
    })
    NodeAttach<ArkContainerSpanPeer>((): ArkContainerSpanPeer => ArkContainerSpanPeer.create(receiver), (_: ArkContainerSpanPeer) => {
        receiver.setContainerSpanOptions()
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
