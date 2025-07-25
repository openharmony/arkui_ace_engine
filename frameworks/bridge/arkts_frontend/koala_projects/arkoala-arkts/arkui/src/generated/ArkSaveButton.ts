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
import { ArkSecurityComponentMethodComponent } from "./ArkSecurityComponent"
import { ArkSaveButtonPeer } from "./peers/ArkSaveButtonPeer"
import { SecurityComponentMethod, SecurityComponentLayoutDirection } from "./ArkSecurityComponentInterfaces"
import { Dimension, Position, Edges, LocalizedEdges, ResourceColor, Padding, Length, SizeOptions, ConstraintSizeOptions } from "./ArkUnitsInterfaces"
import { FontStyle, FontWeight, BorderStyle } from "./ArkEnumsInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { Callback_ClickEvent_SaveButtonOnClickResult_Void } from "./SyntheticDeclarations"
import { ClickEvent } from "./ArkClickEventMaterialized"
import { SaveButtonOnClickResult, SaveButtonAttribute, SaveButtonOptions } from "./ArkSaveButtonInterfaces"
/** @memo:stable */
export class ArkSaveButtonComponent extends ArkSecurityComponentMethodComponent {
    getPeer(): ArkSaveButtonPeer {
        return (this.peer as ArkSaveButtonPeer)
    }
    /** @memo */
    public setSaveButtonOptions(options?: SaveButtonOptions): this {
        if (this.checkPriority("setSaveButtonOptions")) {
            const options_type = runtimeType(options)
            if (RuntimeType.UNDEFINED == options_type) {
                this.getPeer()?.setSaveButtonOptions0Attribute()
                return this
            }
            if (RuntimeType.OBJECT == options_type) {
                const options_casted = options as (SaveButtonOptions)
                this.getPeer()?.setSaveButtonOptions1Attribute(options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public onClick(value: ((event: ClickEvent,result: SaveButtonOnClickResult) => void)): this {
        if (this.checkPriority("onClick")) {
            const value_casted = value as (((event: ClickEvent,result: SaveButtonOnClickResult) => void))
            this.getPeer()?.onClickAttribute(value_casted)
            return this
        }
        return this
    }
    public applyAttributesFinish(): void {
        // we calls this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

/** @memo */
export function ArkSaveButton(
  /** @memo */
  style: ((attributes: ArkSaveButtonComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  options?: SaveButtonOptions | undefined
) {
    const receiver = remember(() => {
        return new ArkSaveButtonComponent()
    })
    NodeAttach<ArkSaveButtonPeer>((): ArkSaveButtonPeer => ArkSaveButtonPeer.create(receiver), (_: ArkSaveButtonPeer) => {
        receiver.setSaveButtonOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
