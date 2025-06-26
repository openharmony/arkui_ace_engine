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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Alignment, FoldStatus, AppRotation } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { window } from "./ohos.window"
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
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            FolderStackOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._FolderStackInterface_setFolderStackOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    alignContentAttribute(value: Alignment | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as Alignment)
            thisSerializer.writeInt32(TypeChecker.Alignment_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._FolderStackAttribute_alignContent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFolderStateChangeAttribute(value: OnFoldStatusChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._FolderStackAttribute_onFolderStateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onHoverStatusChangeAttribute(value: OnHoverStatusChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._FolderStackAttribute_onHoverStatusChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableAnimationAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._FolderStackAttribute_enableAnimation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    autoHalfFoldAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._FolderStackAttribute_autoHalfFold(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    alignContent(value: Alignment | undefined): this
    onFolderStateChange(value: OnFoldStatusChangeCallback | undefined): this
    onHoverStatusChange(value: OnHoverStatusChangeCallback | undefined): this
    enableAnimation(value: boolean | undefined): this
    autoHalfFold(value: boolean | undefined): this
    attributeModifier(value: AttributeModifier<FolderStackAttribute> | AttributeModifier<CommonMethod> | undefined): this
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
            this.getPeer()?.alignContentAttribute(value_casted)
            return this
        }
        return this
    }
    public onFolderStateChange(value: OnFoldStatusChangeCallback | undefined): this {
        if (this.checkPriority("onFolderStateChange")) {
            const value_casted = value as (OnFoldStatusChangeCallback | undefined)
            this.getPeer()?.onFolderStateChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onHoverStatusChange(value: OnHoverStatusChangeCallback | undefined): this {
        if (this.checkPriority("onHoverStatusChange")) {
            const value_casted = value as (OnHoverStatusChangeCallback | undefined)
            this.getPeer()?.onHoverStatusChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public enableAnimation(value: boolean | undefined): this {
        if (this.checkPriority("enableAnimation")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableAnimationAttribute(value_casted)
            return this
        }
        return this
    }
    public autoHalfFold(value: boolean | undefined): this {
        if (this.checkPriority("autoHalfFold")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.autoHalfFoldAttribute(value_casted)
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
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
@memo
@BuilderLambda("FolderStackImpl")
export function FolderStack(
    options?: FolderStackOptions | undefined,
    @memo
    content_?: () => void,
): FolderStackAttribute {
    throw new Error("Not implemented")
}

@memo
export function FolderStackImpl(
    @memo
    style: ((attributes: FolderStackAttribute) => void) | undefined,
    options?: FolderStackOptions | undefined,
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
        valueSerializer.writeInt8(value_upperItems_type)
        if ((RuntimeType.UNDEFINED) != (value_upperItems_type)) {
            const value_upperItems_value  = value_upperItems!
            valueSerializer.writeInt32(value_upperItems_value.length as int32)
            for (let i = 0; i < value_upperItems_value.length; i++) {
                const value_upperItems_value_element : string = value_upperItems_value[i]
                valueSerializer.writeString(value_upperItems_value_element)
            }
        }
    }
    public static read(buffer: DeserializerBase): FolderStackOptions {
        let valueDeserializer : DeserializerBase = buffer
        const upperItems_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let upperItems_buf : Array<string> | undefined
        if ((RuntimeType.UNDEFINED) != (upperItems_buf_runtimeType))
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
