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

import { int32, int64, float32 } from "@koalaui/common"
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { Serializer } from "./peers/Serializer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { ErrorCallback } from "./ohos.base"
import { BusinessError } from "./base"
import { Want } from "./ohos.app.ability"
import { EmbeddedType } from "./enums"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkEmbeddedComponentPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkEmbeddedComponentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._EmbeddedComponent_construct(peerId, flags)
        const _peer  = new ArkEmbeddedComponentPeer(_peerPtr, peerId, "EmbeddedComponent", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setEmbeddedComponentOptionsAttribute(loader: Want, type: EmbeddedType): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeWant(loader)
        ArkUIGeneratedNativeModule._EmbeddedComponentInterface_setEmbeddedComponentOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length(), TypeChecker.EmbeddedType_ToNumeric(type))
        thisSerializer.release()
    }
    onTerminatedAttribute(value: ((parameter: TerminationInfo) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._EmbeddedComponentAttribute_onTerminated(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onErrorAttribute(value: ErrorCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._EmbeddedComponentAttribute_onError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}

export interface TerminationInfo {
    code: number;
    want?: Want;
}
export interface EmbeddedComponentAttribute extends CommonMethod {
    onTerminated(value: ((parameter: TerminationInfo) => void)): this
    onError(value: ErrorCallback): this
    attributeModifier(value: AttributeModifier<EmbeddedComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIEmbeddedComponentAttribute extends UICommonMethod {
    /** @memo */
    onTerminated(value: ((parameter: TerminationInfo) => void)): this
    /** @memo */
    onError(value: ErrorCallback): this
    /** @memo */
    attributeModifier(value: AttributeModifier<EmbeddedComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkEmbeddedComponentStyle extends ArkCommonMethodStyle implements EmbeddedComponentAttribute {
    onTerminated_value?: ((parameter: TerminationInfo) => void)
    onError_value?: ErrorCallback
    public onTerminated(value: ((parameter: TerminationInfo) => void)): this {
        return this
    }
    public onError(value: ErrorCallback): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<EmbeddedComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export type Callback_TerminationInfo_Void = (parameter: TerminationInfo) => void;
/** @memo:stable */
export class ArkEmbeddedComponentComponent extends ArkCommonMethodComponent implements UIEmbeddedComponentAttribute {
    getPeer(): ArkEmbeddedComponentPeer {
        return (this.peer as ArkEmbeddedComponentPeer)
    }
    /** @memo */
    public setEmbeddedComponentOptions(loader: Want, type: EmbeddedType): this {
        if (this.checkPriority("setEmbeddedComponentOptions")) {
            const loader_casted = loader as (Want)
            const type_casted = type as (EmbeddedType)
            this.getPeer()?.setEmbeddedComponentOptionsAttribute(loader_casted, type_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onTerminated(value: ((parameter: TerminationInfo) => void)): this {
        if (this.checkPriority("onTerminated")) {
            const value_casted = value as (((parameter: TerminationInfo) => void))
            this.getPeer()?.onTerminatedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onError(value: ErrorCallback): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (ErrorCallback)
            this.getPeer()?.onErrorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<EmbeddedComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkEmbeddedComponent(
    /** @memo */
    style: ((attributes: UIEmbeddedComponentAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    loader: Want, type: EmbeddedType,
): void {
    const receiver = remember(() => {
        return new ArkEmbeddedComponentComponent()
    })
    NodeAttach<ArkEmbeddedComponentPeer>((): ArkEmbeddedComponentPeer => ArkEmbeddedComponentPeer.create(receiver), (_: ArkEmbeddedComponentPeer) => {
        receiver.setEmbeddedComponentOptions(loader,type)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
