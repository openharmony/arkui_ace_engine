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

import { int32, float32, unsafeCast } from "@koalaui/common"
import { KStringPtr, KBoolean, RuntimeType, runtimeType, isInstanceOf } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ComponentBase } from "./../ComponentBase"
import { isResource, isPadding } from "./../utils"
import { ArkSecurityComponentMethodComponent } from "./ArkSecurityComponent"
import { ArkLocationButtonPeer } from "./peers/ArkLocationButtonPeer"
import { SecurityComponentMethod, SecurityComponentLayoutDirection } from "./ArkSecurityComponentInterfaces"
import { Dimension, Position, Edges, LocalizedEdges, ResourceColor, Padding, Length, SizeOptions, ConstraintSizeOptions, PX, VP, FP, LPX, Percentage, Area } from "./ArkUnitsInterfaces"
import { FontStyle, FontWeight, BorderStyle, Color } from "./ArkEnumsInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { ClickEvent } from "./ArkClickEventMaterialized"
import { LocationButtonOnClickResult, LocationButtonAttribute, LocationButtonOptions, LocationIconStyle, LocationDescription } from "./ArkLocationButtonInterfaces"
import { LengthUnit } from "./ArkArkuiExternalInterfaces"
import { BaseEvent } from "./ArkBaseEventMaterialized"
import { EventTarget, SourceType, SourceTool } from "./ArkCommonInterfaces"
import { ButtonType } from "./ArkButtonInterfaces"
/** @memo:stable */
export class ArkLocationButtonComponent extends ArkSecurityComponentMethodComponent {
    protected getPeer(): ArkLocationButtonPeer {
        return (this.peer as ArkLocationButtonPeer)
    }
    /** @memo */
    public setLocationButtonOptions(options?: LocationButtonOptions): this {
        if (this.checkPriority("setLocationButtonOptions")) {
            const options_type = runtimeType(options)
            if (RuntimeType.UNDEFINED == options_type) {
                this.getPeer()?.setLocationButtonOptions0Attribute()
                return this
            }
            if (RuntimeType.OBJECT == options_type) {
                const options_casted = options as (LocationButtonOptions)
                this.getPeer()?.setLocationButtonOptions1Attribute(options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public onClick(value: ((event: ClickEvent, result: LocationButtonOnClickResult) => void)): this {
        if (this.checkPriority("onClick")) {
            const value_casted = value as (((event: ClickEvent, result: LocationButtonOnClickResult) => void))
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
export function ArkLocationButton(
  /** @memo */
  style: ((attributes: ArkLocationButtonComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  options?: LocationButtonOptions | undefined
) {
    const receiver = remember(() => {
        return new ArkLocationButtonComponent()
    })
    NodeAttach<ArkLocationButtonPeer>((): ArkLocationButtonPeer => ArkLocationButtonPeer.create(receiver), (_: ArkLocationButtonPeer) => {
        receiver.setLocationButtonOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
