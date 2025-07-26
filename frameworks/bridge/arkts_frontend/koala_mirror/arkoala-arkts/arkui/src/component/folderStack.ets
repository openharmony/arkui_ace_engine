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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { Alignment, FoldStatus, AppRotation } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { window } from "./../generated/ohos.window"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkFolderStackPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkFolderStackPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._FolderStack_construct(peerId, flags)
        const _peer  = new ArkFolderStackPeer(_peerPtr, peerId, "FolderStack", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setFolderStackOptionsAttribute(options?: FolderStackOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            FolderStackOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._FolderStackInterface_setFolderStackOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAlignContentAttribute(value: Alignment | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as Alignment)
            thisSerializer.writeInt32(TypeChecker.Alignment_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._FolderStackAttribute_setAlignContent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnFolderStateChangeAttribute(value: OnFoldStatusChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._FolderStackAttribute_setOnFolderStateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnHoverStatusChangeAttribute(value: OnHoverStatusChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._FolderStackAttribute_setOnHoverStatusChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableAnimationAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._FolderStackAttribute_setEnableAnimation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAutoHalfFoldAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
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
    public alignContent(value: Alignment | undefined): this {
        return this
    }
    public onFolderStateChange(value: OnFoldStatusChangeCallback | undefined): this {
        return this
    }
    public onHoverStatusChange(value: OnHoverStatusChangeCallback | undefined): this {
        return this
    }
    public enableAnimation(value: boolean | undefined): this {
        return this
    }
    public autoHalfFold(value: boolean | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<FolderStackAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: FolderStackAttribute): void {
        super.apply(target)
        if (this.alignContent_value !== undefined)
            target.alignContent(this.alignContent_value!)
        if (this.onFolderStateChange_value !== undefined)
            target.onFolderStateChange(this.onFolderStateChange_value!)
        if (this.onHoverStatusChange_value !== undefined)
            target.onHoverStatusChange(this.onHoverStatusChange_value!)
        if (this.enableAnimation_value !== undefined)
            target.enableAnimation(this.enableAnimation_value!)
        if (this.autoHalfFold_value !== undefined)
            target.autoHalfFold(this.autoHalfFold_value!)
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
        return (this.peer as ArkFolderStackPeer)
    }
    public setFolderStackOptions(options?: FolderStackOptions): this {
        if (this.checkPriority("setFolderStackOptions")) {
            const options_casted = options as (FolderStackOptions | undefined)
            this.getPeer()?.setFolderStackOptionsAttribute(options_casted)
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
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withFolderStackStyle(receiver: FolderStackAttribute, modifier: AttributeModifier<FolderStackAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkFolderStackStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("FolderStack")
// export function FolderStack(
//     options?: FolderStackOptions,
//     @memo
//     content_?: () => void,
// ): FolderStackAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function FolderStack(
    @memo
    style: ((attributes: FolderStackAttribute) => void) | undefined,
    options?: FolderStackOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkFolderStackComponent>((): ArkFolderStackComponent => {
        return new ArkFolderStackComponent()
    })
    NodeAttach<ArkFolderStackPeer>((): ArkFolderStackPeer => ArkFolderStackPeer.create(receiver), (_: ArkFolderStackPeer): void => {
        receiver.setFolderStackOptions(options)
        style?.(receiver)
        withFolderStackStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkFolderStackSet extends ArkCommonMethodSet implements FolderStackAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _alignContent_flag?: boolean
    _alignContent0_value?: Alignment | undefined
    _onFolderStateChange_flag?: boolean
    _onFolderStateChange0_value?: OnFoldStatusChangeCallback | undefined
    _onHoverStatusChange_flag?: boolean
    _onHoverStatusChange0_value?: OnHoverStatusChangeCallback | undefined
    _enableAnimation_flag?: boolean
    _enableAnimation0_value?: boolean | undefined
    _autoHalfFold_flag?: boolean
    _autoHalfFold0_value?: boolean | undefined
    applyModifierPatch(component: FolderStackAttribute): void {
        if (this._alignContent_flag)
            component.alignContent((this._alignContent0_value as Alignment | undefined))
        if (this._onFolderStateChange_flag)
            component.onFolderStateChange((this._onFolderStateChange0_value as OnFoldStatusChangeCallback | undefined))
        if (this._onHoverStatusChange_flag)
            component.onHoverStatusChange((this._onHoverStatusChange0_value as OnHoverStatusChangeCallback | undefined))
        if (this._enableAnimation_flag)
            component.enableAnimation((this._enableAnimation0_value as boolean | undefined))
        if (this._autoHalfFold_flag)
            component.autoHalfFold((this._autoHalfFold0_value as boolean | undefined))
    }
    public alignContent(value: Alignment | undefined): this {
        this._alignContent_flag = true
        this._alignContent0_value = value
        return this
    }
    public onFolderStateChange(value: OnFoldStatusChangeCallback | undefined): this {
        this._onFolderStateChange_flag = true
        this._onFolderStateChange0_value = value
        return this
    }
    public onHoverStatusChange(value: OnHoverStatusChangeCallback | undefined): this {
        this._onHoverStatusChange_flag = true
        this._onHoverStatusChange0_value = value
        return this
    }
    public enableAnimation(value: boolean | undefined): this {
        this._enableAnimation_flag = true
        this._enableAnimation0_value = value
        return this
    }
    public autoHalfFold(value: boolean | undefined): this {
        this._autoHalfFold_flag = true
        this._autoHalfFold0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<FolderStackAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class OnFoldStatusChangeInfo_serializer {
    public static write(buffer: SerializerBase, value: OnFoldStatusChangeInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_foldStatus  = value.foldStatus
        valueSerializer.writeInt32(TypeChecker.FoldStatus_ToNumeric(value_foldStatus))
    }
    public static read(buffer: DeserializerBase): OnFoldStatusChangeInfo {
        let valueDeserializer : DeserializerBase = buffer
        const foldStatus_result : FoldStatus = TypeChecker.FoldStatus_FromNumeric(valueDeserializer.readInt32())
        let value : OnFoldStatusChangeInfo = ({foldStatus: foldStatus_result} as OnFoldStatusChangeInfo)
        return value
    }
}
export class FolderStackOptions_serializer {
    public static write(buffer: SerializerBase, value: FolderStackOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_upperItems  = value.upperItems
        let value_upperItems_type : int32 = RuntimeType.UNDEFINED
        value_upperItems_type = runtimeType(value_upperItems)
        valueSerializer.writeInt8((value_upperItems_type).toChar())
        if ((value_upperItems_type) != (RuntimeType.UNDEFINED)) {
            const value_upperItems_value  = value_upperItems!
            valueSerializer.writeInt32((value_upperItems_value.length).toInt())
            for (let value_upperItems_value_counter_i = 0; value_upperItems_value_counter_i < value_upperItems_value.length; value_upperItems_value_counter_i++) {
                const value_upperItems_value_element : string = value_upperItems_value[value_upperItems_value_counter_i]
                valueSerializer.writeString(value_upperItems_value_element)
            }
        }
    }
    public static read(buffer: DeserializerBase): FolderStackOptions {
        let valueDeserializer : DeserializerBase = buffer
        const upperItems_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let upperItems_buf : Array<string> | undefined
        if ((upperItems_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const upperItems_buf__length : int32 = valueDeserializer.readInt32()
            let upperItems_buf_ : Array<string> = new Array<string>(upperItems_buf__length)
            for (let upperItems_buf__i = 0; upperItems_buf__i < upperItems_buf__length; upperItems_buf__i++) {
                upperItems_buf_[upperItems_buf__i] = (valueDeserializer.readString() as string)
            }
            upperItems_buf = upperItems_buf_
        }
        const upperItems_result : Array<string> | undefined = upperItems_buf
        let value : FolderStackOptions = ({upperItems: upperItems_result} as FolderStackOptions)
        return value
    }
}
export class HoverEventParam_serializer {
    public static write(buffer: SerializerBase, value: HoverEventParam): void {
        let valueSerializer : SerializerBase = buffer
        const value_foldStatus  = value.foldStatus
        valueSerializer.writeInt32(TypeChecker.FoldStatus_ToNumeric(value_foldStatus))
        const value_isHoverMode  = value.isHoverMode
        valueSerializer.writeBoolean(value_isHoverMode)
        const value_appRotation  = value.appRotation
        valueSerializer.writeInt32(TypeChecker.AppRotation_ToNumeric(value_appRotation))
        const value_windowStatusType  = value.windowStatusType
        valueSerializer.writeInt32(TypeChecker.window_WindowStatusType_ToNumeric(value_windowStatusType))
    }
    public static read(buffer: DeserializerBase): HoverEventParam {
        let valueDeserializer : DeserializerBase = buffer
        const foldStatus_result : FoldStatus = TypeChecker.FoldStatus_FromNumeric(valueDeserializer.readInt32())
        const isHoverMode_result : boolean = valueDeserializer.readBoolean()
        const appRotation_result : AppRotation = TypeChecker.AppRotation_FromNumeric(valueDeserializer.readInt32())
        const windowStatusType_result : window.WindowStatusType = TypeChecker.window_WindowStatusType_FromNumeric(valueDeserializer.readInt32())
        let value : HoverEventParam = ({foldStatus: foldStatus_result, isHoverMode: isHoverMode_result, appRotation: appRotation_result, windowStatusType: windowStatusType_result} as HoverEventParam)
        return value
    }
}
