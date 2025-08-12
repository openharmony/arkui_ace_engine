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
import { TextBackgroundStyle } from "./../ArkSpanInterfaces"
import { AttributeModifier } from "./../../handwritten"
import { ContainerSpanAttribute } from "./../ArkContainerSpanInterfaces"
import { ResourceColor, Dimension, BorderRadiuses, Length } from "./../ArkUnitsInterfaces"
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
export class ArkContainerSpanPeer extends PeerNode {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkContainerSpanPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._ContainerSpan_construct(peerId, flags)
        const _peer = new ArkContainerSpanPeer(_peerPtr, peerId, "ContainerSpan", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setContainerSpanOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._ContainerSpanInterface_setContainerSpanOptions(this.peer.ptr)
    }
    textBackgroundStyleAttribute(value: TextBackgroundStyle): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeTextBackgroundStyle(value)
        ArkUIGeneratedNativeModule._ContainerSpanAttribute_textBackgroundStyle(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ArkContainerSpanAttributes {
    textBackgroundStyle?: TextBackgroundStyle
    attributeModifier?: AttributeModifier<object>
}
