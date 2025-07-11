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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ErrorCallback } from "./ohos.base"
import { BusinessError } from "#external"
import { Want } from "./ohos.app.ability"
import { EmbeddedType } from "./enums"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArkEmbeddedComponentPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkEmbeddedComponentPeer {
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
    onTerminatedAttribute(value: ((parameter: TerminationInfo) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._EmbeddedComponentAttribute_onTerminated(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onErrorAttribute(value: ErrorCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._EmbeddedComponentAttribute_onError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type EmbeddedComponentInterface = (loader: Want, type: EmbeddedType) => EmbeddedComponentAttribute;
export interface TerminationInfo {
    code: number;
    want?: Want;
}
export interface EmbeddedComponentAttribute extends CommonMethod {
    onTerminated(value: ((parameter: TerminationInfo) => void) | undefined): this
    onError(value: ErrorCallback | undefined): this
}
export class ArkEmbeddedComponentStyle extends ArkCommonMethodStyle implements EmbeddedComponentAttribute {
    onTerminated_value?: ((parameter: TerminationInfo) => void) | undefined
    onError_value?: ErrorCallback | undefined
    public onTerminated(value: ((parameter: TerminationInfo) => void) | undefined): this {
        return this
    }
    public onError(value: ErrorCallback | undefined): this {
        return this
        }
}
export type Callback_TerminationInfo_Void = (parameter: TerminationInfo) => void;
export class ArkEmbeddedComponentComponent extends ArkCommonMethodComponent implements EmbeddedComponentAttribute {
    getPeer(): ArkEmbeddedComponentPeer {
        return (this.peer as ArkEmbeddedComponentPeer)
    }
    public setEmbeddedComponentOptions(loader: Want, type: EmbeddedType): this {
        if (this.checkPriority("setEmbeddedComponentOptions")) {
            const loader_casted = loader as (Want)
            const type_casted = type as (EmbeddedType)
            this.getPeer()?.setEmbeddedComponentOptionsAttribute(loader_casted, type_casted)
            return this
        }
        return this
    }
    public onTerminated(value: ((parameter: TerminationInfo) => void) | undefined): this {
        if (this.checkPriority("onTerminated")) {
            const value_casted = value as (((parameter: TerminationInfo) => void) | undefined)
            this.getPeer()?.onTerminatedAttribute(value_casted)
            return this
        }
        return this
    }
    public onError(value: ErrorCallback | undefined): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (ErrorCallback | undefined)
            this.getPeer()?.onErrorAttribute(value_casted)
            return this
        }
        return this
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function EmbeddedComponent(
    /** @memo */
    style: ((attributes: EmbeddedComponentAttribute) => void) | undefined,
    loader: Want, type: EmbeddedType,
    /** @memo */
    content_?: (() => void) | undefined,
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
