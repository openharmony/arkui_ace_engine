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

import { ArkThemeScopeManager } from "#arktheme"
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Alignment, FoldStatus, AppRotation } from "./enums"
import { AttributeModifier, hookFolderStackAttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { default as window } from "@ohos.window"
import { FolderStackModifier } from "./../FolderStackModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkFolderStackPeer extends ArkCommonMethodPeer {
    attributeSet?: FolderStackModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkFolderStackPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._FolderStack_construct(peerId, flags)
        const _peer  = new ArkFolderStackPeer(_peerPtr, peerId, 'FolderStack', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setFolderStackOptionsAttribute(options?: FolderStackOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            FolderStackOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._FolderStackInterface_setFolderStackOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAlignContentAttribute(value: Alignment | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as Alignment)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._FolderStackAttribute_setAlignContent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFolderStateChangeAttribute(value: OnFoldStatusChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._FolderStackAttribute_setOnFolderStateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnHoverStatusChangeAttribute(value: OnHoverStatusChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._FolderStackAttribute_setOnHoverStatusChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableAnimationAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._FolderStackAttribute_setEnableAnimation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAutoHalfFoldAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._FolderStackAttribute_setAutoHalfFold(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type WindowStatusType = window.WindowStatusType;
export interface FolderStackOptions {
    upperItems?: Array<string>;
}
export interface OnFoldStatusChangeInfo {
    foldStatus: FoldStatus;
}
export type OnFoldStatusChangeCallback = (event: OnFoldStatusChangeInfo) => void;
export type OnHoverStatusChangeCallback = (param: HoverEventParam) => void;
export interface FolderStackAttribute extends CommonMethod {
    setFolderStackOptions(options?: FolderStackOptions): this {
        throw new Error("Unimplemented method setFolderStackOptions")
    }
    alignContent(value: Alignment | undefined): this {
        throw new Error("Unimplemented method alignContent")
    }
    onFolderStateChange(value: OnFoldStatusChangeCallback | undefined): this {
        throw new Error("Unimplemented method onFolderStateChange")
    }
    onHoverStatusChange(value: OnHoverStatusChangeCallback | undefined): this {
        throw new Error("Unimplemented method onHoverStatusChange")
    }
    enableAnimation(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableAnimation")
    }
    autoHalfFold(value: boolean | undefined): this {
        throw new Error("Unimplemented method autoHalfFold")
    }
    attributeModifier(value: AttributeModifier<FolderStackAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkFolderStackStyle extends ArkCommonMethodStyle implements FolderStackAttribute {
    alignContent_value?: Alignment | undefined
    onFolderStateChange_value?: OnFoldStatusChangeCallback | undefined
    onHoverStatusChange_value?: OnHoverStatusChangeCallback | undefined
    enableAnimation_value?: boolean | undefined
    autoHalfFold_value?: boolean | undefined
    attributeModifier_value?: AttributeModifier<FolderStackAttribute> | AttributeModifier<CommonMethod> | undefined
    setFolderStackOptions(options?: FolderStackOptions): this {
        return this
    }
    alignContent(value: Alignment | undefined): this {
        return this
    }
    onFolderStateChange(value: OnFoldStatusChangeCallback | undefined): this {
        return this
    }
    onHoverStatusChange(value: OnHoverStatusChangeCallback | undefined): this {
        return this
    }
    enableAnimation(value: boolean | undefined): this {
        return this
    }
    autoHalfFold(value: boolean | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<FolderStackAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export interface HoverEventParam {
    foldStatus: FoldStatus;
    isHoverMode: boolean;
    appRotation: AppRotation;
    windowStatusType: window.WindowStatusType;
}

export class ArkFolderStackComponent extends ArkCommonMethodComponent implements FolderStackAttribute {
    getPeer(): ArkFolderStackPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkFolderStackPeer)
    }
    public setFolderStackOptions(options?: FolderStackOptions): this {
        if (this.checkPriority("setFolderStackOptions")) {
            const options_casted = options as (FolderStackOptions | undefined)
            this.getPeer()?.setFolderStackOptionsAttribute(options_casted)
            this.applyOptionsFinish('FolderStackAttribute');
            return this
        }
        return this
    }
    public alignContent(value: Alignment | undefined): this {
        if (this.checkPriority("alignContent")) {
            const value_casted = value as (Alignment | undefined)
            this.getPeer()?.setAlignContentAttribute(value_casted)
            return this
        }
        return this
    }
    public onFolderStateChange(value: OnFoldStatusChangeCallback | undefined): this {
        if (this.checkPriority("onFolderStateChange")) {
            const value_casted = value as (OnFoldStatusChangeCallback | undefined)
            this.getPeer()?.setOnFolderStateChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onHoverStatusChange(value: OnHoverStatusChangeCallback | undefined): this {
        if (this.checkPriority("onHoverStatusChange")) {
            const value_casted = value as (OnHoverStatusChangeCallback | undefined)
            this.getPeer()?.setOnHoverStatusChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public enableAnimation(value: boolean | undefined): this {
        if (this.checkPriority("enableAnimation")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableAnimationAttribute(value_casted)
            return this
        }
        return this
    }
    public autoHalfFold(value: boolean | undefined): this {
        if (this.checkPriority("autoHalfFold")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setAutoHalfFoldAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<FolderStackAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
          hookFolderStackAttributeModifier(this, value);
        })
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}

@memo
export function FolderStackImpl(
    @memo
    style: ((attributes: FolderStackAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkFolderStackComponent>((): ArkFolderStackComponent => {
        return new ArkFolderStackComponent()
    })
    NodeAttach<ArkFolderStackPeer>((): ArkFolderStackPeer => ArkFolderStackPeer.create(receiver), (peer: ArkFolderStackPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class OnFoldStatusChangeInfo_serializer {
    public static write(buffer: SerializerBase, value: OnFoldStatusChangeInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForFoldStatus  = value.foldStatus
        valueSerializer.writeInt32(valueHolderForFoldStatus.valueOf())
    }
    public static read(buffer: DeserializerBase): OnFoldStatusChangeInfo {
        let valueDeserializer : DeserializerBase = buffer
        const foldStatusTmpResult : FoldStatus = FoldStatus.fromValue(valueDeserializer.readInt32())
        let value : OnFoldStatusChangeInfo = ({foldStatus: foldStatusTmpResult} as OnFoldStatusChangeInfo)
        return value
    }
}
export class FolderStackOptions_serializer {
    public static write(buffer: SerializerBase, value: FolderStackOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForUpperItems  = value.upperItems
        if (valueHolderForUpperItems !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUpperItemsTmpValue  = valueHolderForUpperItems!
            valueSerializer.writeInt32((valueHolderForUpperItemsTmpValue.length).toInt())
            for (let valueHolderForUpperItemsTmpValueCounterI = 0; valueHolderForUpperItemsTmpValueCounterI < valueHolderForUpperItemsTmpValue.length; valueHolderForUpperItemsTmpValueCounterI++) {
                const valueHolderForUpperItemsTmpValueTmpElement : string = valueHolderForUpperItemsTmpValue[valueHolderForUpperItemsTmpValueCounterI]
                valueSerializer.writeString(valueHolderForUpperItemsTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): FolderStackOptions {
        let valueDeserializer : DeserializerBase = buffer
        const upperItemsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let upperItemsTmpBuf : Array<string> | undefined = undefined
        if ((upperItemsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const upperItemsTmpBuf_Length : int32 = valueDeserializer.readInt32()
            let upperItemsTmpBuf_ : Array<string> = new Array<string>(upperItemsTmpBuf_Length)
            for (let upperItemsTmpBuf_BufCounterI = 0; upperItemsTmpBuf_BufCounterI < upperItemsTmpBuf_Length; upperItemsTmpBuf_BufCounterI++) {
                upperItemsTmpBuf_[upperItemsTmpBuf_BufCounterI] = (valueDeserializer.readString() as string)
            }
            upperItemsTmpBuf = upperItemsTmpBuf_
        }
        const upperItemsTmpResult : Array<string> | undefined = upperItemsTmpBuf
        let value : FolderStackOptions = ({upperItems: upperItemsTmpResult} as FolderStackOptions)
        return value
    }
}
export class HoverEventParam_serializer {
    public static write(buffer: SerializerBase, value: HoverEventParam): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForFoldStatus  = value.foldStatus
        valueSerializer.writeInt32(valueHolderForFoldStatus.valueOf())
        const valueHolderForIsHoverMode  = value.isHoverMode
        valueSerializer.writeBoolean(valueHolderForIsHoverMode)
        const valueHolderForAppRotation  = value.appRotation
        valueSerializer.writeInt32(valueHolderForAppRotation.valueOf())
        const valueHolderForWindowStatusType  = value.windowStatusType
        valueSerializer.writeInt32(valueHolderForWindowStatusType.valueOf())
    }
    public static read(buffer: DeserializerBase): HoverEventParam {
        let valueDeserializer : DeserializerBase = buffer
        const foldStatusTmpResult : FoldStatus = FoldStatus.fromValue(valueDeserializer.readInt32())
        const isHoverModeTmpResult : boolean = valueDeserializer.readBoolean()
        const appRotationTmpResult : AppRotation = AppRotation.fromValue(valueDeserializer.readInt32())
        const windowStatusTypeTmpResult : window.WindowStatusType = window.WindowStatusType.fromValue(valueDeserializer.readInt32())
        let value : HoverEventParam = ({foldStatus: foldStatusTmpResult, isHoverMode: isHoverModeTmpResult, appRotation: appRotationTmpResult, windowStatusType: windowStatusTypeTmpResult} as HoverEventParam)
        return value
    }
}
