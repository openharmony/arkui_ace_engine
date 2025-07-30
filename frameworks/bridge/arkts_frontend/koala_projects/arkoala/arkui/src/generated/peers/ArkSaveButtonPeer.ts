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
import { nullptr, KPointer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { runtimeType, RuntimeType } from "@koalaui/interop"
import { Serializer } from "./Serializer"
import { ComponentBase } from "../../ComponentBase"
import { PeerNode } from "../../PeerNode"
import { isInstanceOf } from "@koalaui/interop"
import { isResource, isPadding } from "../../utils"
import { ArkUIGeneratedNativeModule } from "../ArkUIGeneratedNativeModule"
import { ArkSecurityComponentMethodPeer, ArkSecurityComponentMethodAttributes } from "./ArkSecurityComponentPeer"
import { SecurityComponentMethod, SecurityComponentLayoutDirection } from "./../ArkSecurityComponentInterfaces"
import { Dimension, Position, Edges, LocalizedEdges, ResourceColor, Padding, Length, SizeOptions, ConstraintSizeOptions, PX, VP, FP, LPX, Percentage, Area } from "./../ArkUnitsInterfaces"
import { FontStyle, FontWeight, BorderStyle, Color } from "./../ArkEnumsInterfaces"
import { Resource } from "./../ArkResourceInterfaces"
import { LengthMetrics } from "./../ArkLengthMetricsMaterialized"
import { ClickEvent } from "./../ArkClickEventMaterialized"
import { SaveButtonOnClickResult, SaveButtonAttribute, SaveButtonOptions, SaveIconStyle, SaveDescription } from "./../ArkSaveButtonInterfaces"
import { LengthUnit } from "./../ArkArkuiExternalInterfaces"
import { BaseEvent } from "./../ArkBaseEventMaterialized"
import { EventTarget, SourceType, SourceTool } from "./../ArkCommonInterfaces"
import { ButtonType } from "./../ArkButtonInterfaces"
import { GestureName, GestureComponent } from "./../shared/generated-utils"
import { CallbackKind } from "./CallbackKind"
import { CallbackTransformer } from "./CallbackTransformer"
import { unsafeCast } from "@koalaui/common"
import { Deserializer, createDeserializer } from "./Deserializer"
import { MaterializedBase, toPeerPtr, wrapCallback } from "@koalaui/interop"
import { DotIndicator } from "./../ArkDotIndicatorBuilder"
import { DigitIndicator } from "./../ArkDigitIndicatorBuilder"
import { SubTabBarStyle } from "./../ArkSubTabBarStyleBuilder"
import { BottomTabBarStyle } from "./../ArkBottomTabBarStyleBuilder"
export class ArkSaveButtonPeer extends ArkSecurityComponentMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSaveButtonPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._SaveButton_construct(peerId, flags)
        const _peer = new ArkSaveButtonPeer(_peerPtr, peerId, "SaveButton", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSaveButtonOptions0Attribute(): void {
        ArkUIGeneratedNativeModule._SaveButtonInterface_setSaveButtonOptions0(this.peer.ptr)
    }
    setSaveButtonOptions1Attribute(options: SaveButtonOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeSaveButtonOptions(options)
        ArkUIGeneratedNativeModule._SaveButtonInterface_setSaveButtonOptions1(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onClickAttribute(value: ((event: ClickEvent, result: SaveButtonOnClickResult) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SaveButtonAttribute_onClick(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ArkSaveButtonAttributes extends ArkSecurityComponentMethodAttributes {
    onClick?: ((event: ClickEvent, result: SaveButtonOnClickResult) => void)
}
