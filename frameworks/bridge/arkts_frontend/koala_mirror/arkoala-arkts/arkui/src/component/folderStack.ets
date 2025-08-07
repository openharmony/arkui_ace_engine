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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { Alignment, FoldStatus, AppRotation } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { window } from "./../generated/ohos.window"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkFolderStackPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
            thisSerializer.writeInt32(TypeChecker.Alignment_ToNumeric(valueTmpValue))
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
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class FolderStackModifier extends CommonMethodModifier implements FolderStackAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _alignContent_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _alignContent_0_0value?: Alignment | undefined
    _onFolderStateChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onFolderStateChange_0_0value?: OnFoldStatusChangeCallback | undefined
    _onHoverStatusChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onHoverStatusChange_0_0value?: OnHoverStatusChangeCallback | undefined
    _enableAnimation_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableAnimation_0_0value?: boolean | undefined
    _autoHalfFold_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _autoHalfFold_0_0value?: boolean | undefined
    applyModifierPatch(peer: ArkFolderStackPeer): void {
        super.applyModifierPatch(peer)
        if (this._alignContent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._alignContent_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAlignContentAttribute((this._alignContent_0_0value as Alignment | undefined));
                    this._alignContent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._alignContent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._alignContent_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAlignContentAttribute((undefined as Alignment | undefined));
                }
            }
        }
        if (this._onFolderStateChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onFolderStateChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnFolderStateChangeAttribute((this._onFolderStateChange_0_0value as OnFoldStatusChangeCallback | undefined));
                    this._onFolderStateChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onFolderStateChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onFolderStateChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnFolderStateChangeAttribute((undefined as OnFoldStatusChangeCallback | undefined));
                }
            }
        }
        if (this._onHoverStatusChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onHoverStatusChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnHoverStatusChangeAttribute((this._onHoverStatusChange_0_0value as OnHoverStatusChangeCallback | undefined));
                    this._onHoverStatusChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onHoverStatusChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onHoverStatusChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnHoverStatusChangeAttribute((undefined as OnHoverStatusChangeCallback | undefined));
                }
            }
        }
        if (this._enableAnimation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableAnimation_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableAnimationAttribute((this._enableAnimation_0_0value as boolean | undefined));
                    this._enableAnimation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableAnimation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableAnimation_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableAnimationAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._autoHalfFold_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._autoHalfFold_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAutoHalfFoldAttribute((this._autoHalfFold_0_0value as boolean | undefined));
                    this._autoHalfFold_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._autoHalfFold_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._autoHalfFold_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAutoHalfFoldAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: FolderStackModifier): void {
        super.mergeModifier(modifier)
        if (modifier._alignContent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._alignContent_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.alignContent(modifier._alignContent_0_0value);
                    break;
                }
                default: {
                    this.alignContent((undefined as Alignment | undefined));
                }
            }
        }
        if (modifier._onFolderStateChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onFolderStateChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onFolderStateChange(modifier._onFolderStateChange_0_0value);
                    break;
                }
                default: {
                    this.onFolderStateChange((undefined as OnFoldStatusChangeCallback | undefined));
                }
            }
        }
        if (modifier._onHoverStatusChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onHoverStatusChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onHoverStatusChange(modifier._onHoverStatusChange_0_0value);
                    break;
                }
                default: {
                    this.onHoverStatusChange((undefined as OnHoverStatusChangeCallback | undefined));
                }
            }
        }
        if (modifier._enableAnimation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableAnimation_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableAnimation(modifier._enableAnimation_0_0value);
                    break;
                }
                default: {
                    this.enableAnimation((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._autoHalfFold_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._autoHalfFold_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.autoHalfFold(modifier._autoHalfFold_0_0value);
                    break;
                }
                default: {
                    this.autoHalfFold((undefined as boolean | undefined));
                }
            }
        }
    }
    alignContent(value: Alignment | undefined): this {
        if (((this._alignContent_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._alignContent_0_flag = AttributeUpdaterFlag.UPDATE
            this._alignContent_0_0value = value
        } else
        {
            this._alignContent_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onFolderStateChange(value: OnFoldStatusChangeCallback | undefined): this {
        if (((this._onFolderStateChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onFolderStateChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onFolderStateChange_0_0value = value
        } else
        {
            this._onFolderStateChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onHoverStatusChange(value: OnHoverStatusChangeCallback | undefined): this {
        if (((this._onHoverStatusChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onHoverStatusChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onHoverStatusChange_0_0value = value
        } else
        {
            this._onHoverStatusChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableAnimation(value: boolean | undefined): this {
        if (((this._enableAnimation_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableAnimation_0_0value) !== (value)))
        {
            this._enableAnimation_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableAnimation_0_0value = value
        } else
        {
            this._enableAnimation_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    autoHalfFold(value: boolean | undefined): this {
        if (((this._autoHalfFold_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._autoHalfFold_0_0value) !== (value)))
        {
            this._autoHalfFold_0_flag = AttributeUpdaterFlag.UPDATE
            this._autoHalfFold_0_0value = value
        } else
        {
            this._autoHalfFold_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<FolderStackAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class OnFoldStatusChangeInfo_serializer {
    public static write(buffer: SerializerBase, value: OnFoldStatusChangeInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForFoldStatus  = value.foldStatus
        valueSerializer.writeInt32(TypeChecker.FoldStatus_ToNumeric(valueHolderForFoldStatus))
    }
    public static read(buffer: DeserializerBase): OnFoldStatusChangeInfo {
        let valueDeserializer : DeserializerBase = buffer
        const foldStatusTmpResult : FoldStatus = TypeChecker.FoldStatus_FromNumeric(valueDeserializer.readInt32())
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
        let upperItemsTmpBuf : Array<string> | undefined
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
        valueSerializer.writeInt32(TypeChecker.FoldStatus_ToNumeric(valueHolderForFoldStatus))
        const valueHolderForIsHoverMode  = value.isHoverMode
        valueSerializer.writeBoolean(valueHolderForIsHoverMode)
        const valueHolderForAppRotation  = value.appRotation
        valueSerializer.writeInt32(TypeChecker.AppRotation_ToNumeric(valueHolderForAppRotation))
        const valueHolderForWindowStatusType  = value.windowStatusType
        valueSerializer.writeInt32(TypeChecker.window_WindowStatusType_ToNumeric(valueHolderForWindowStatusType))
    }
    public static read(buffer: DeserializerBase): HoverEventParam {
        let valueDeserializer : DeserializerBase = buffer
        const foldStatusTmpResult : FoldStatus = TypeChecker.FoldStatus_FromNumeric(valueDeserializer.readInt32())
        const isHoverModeTmpResult : boolean = valueDeserializer.readBoolean()
        const appRotationTmpResult : AppRotation = TypeChecker.AppRotation_FromNumeric(valueDeserializer.readInt32())
        const windowStatusTypeTmpResult : window.WindowStatusType = TypeChecker.window_WindowStatusType_FromNumeric(valueDeserializer.readInt32())
        let value : HoverEventParam = ({foldStatus: foldStatusTmpResult, isHoverMode: isHoverModeTmpResult, appRotation: appRotationTmpResult, windowStatusType: windowStatusTypeTmpResult} as HoverEventParam)
        return value
    }
}
