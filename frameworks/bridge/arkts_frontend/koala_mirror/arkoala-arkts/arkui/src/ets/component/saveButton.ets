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
import { ArkSecurityComponentMethodPeer, SecurityComponentMethod, ArkSecurityComponentMethodComponent, ArkSecurityComponentMethodStyle, ArkSecurityComponentMethodSet } from "./securityComponent"
import { ClickEvent, CommonMethod } from "./common"
import { BusinessError } from "./../generated/ohos.base"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { ButtonType } from "./button"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkSaveButtonPeer extends ArkSecurityComponentMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSaveButtonPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._SaveButton_construct(peerId, flags)
        const _peer  = new ArkSaveButtonPeer(_peerPtr, peerId, "SaveButton", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSaveButtonOptions0Attribute(): void {
        ArkUIGeneratedNativeModule._SaveButtonInterface_setSaveButtonOptions0(this.peer.ptr)
    }
    setSaveButtonOptions1Attribute(options: SaveButtonOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        SaveButtonOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._SaveButtonInterface_setSaveButtonOptions1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnClickAttribute(value: SaveButtonCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._SaveButtonAttribute_setOnClick(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum SaveIconStyle {
    FULL_FILLED = 0,
    LINES = 1,
    PICTURE = 2
}
export enum SaveDescription {
    DOWNLOAD = 0,
    DOWNLOAD_FILE = 1,
    SAVE = 2,
    SAVE_IMAGE = 3,
    SAVE_FILE = 4,
    DOWNLOAD_AND_SHARE = 5,
    RECEIVE = 6,
    CONTINUE_TO_RECEIVE = 7,
    SAVE_TO_GALLERY = 8,
    EXPORT_TO_GALLERY = 9,
    QUICK_SAVE_TO_GALLERY = 10,
    RESAVE_TO_GALLERY = 11,
    SAVE_ALL = 12
}
export interface SaveButtonOptions {
    icon?: SaveIconStyle;
    text?: SaveDescription;
    buttonType?: ButtonType;
}
export enum SaveButtonOnClickResult {
    SUCCESS = 0,
    TEMPORARY_AUTHORIZATION_FAILED = 1
}
export type SaveButtonCallback = (event: ClickEvent, result: SaveButtonOnClickResult, error?: BusinessError) => void;
export interface SaveButtonAttribute extends SecurityComponentMethod {
    onClick(value: SaveButtonCallback | undefined): this
    attributeModifier(value: AttributeModifier<SaveButtonAttribute> | AttributeModifier<SecurityComponentMethod> | undefined): this
}
export class ArkSaveButtonStyle extends ArkSecurityComponentMethodStyle implements SaveButtonAttribute {
    onClick_value?: SaveButtonCallback | undefined
    attributeModifier_value?: AttributeModifier<SaveButtonAttribute> | AttributeModifier<CommonMethod> | undefined
    public onClick(value: SaveButtonCallback | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<SaveButtonAttribute> | AttributeModifier<SecurityComponentMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: SaveButtonAttribute): void {
        super.apply(target)
        if (this.onClick_value !== undefined)
            target.onClick(this.onClick_value!)
    }
}

export class ArkSaveButtonComponent extends ArkSecurityComponentMethodComponent implements SaveButtonAttribute {
    getPeer(): ArkSaveButtonPeer {
        return (this.peer as ArkSaveButtonPeer)
    }
    public setSaveButtonOptions(): this {
        if (this.checkPriority("setSaveButtonOptions")) {
            this.getPeer()?.setSaveButtonOptions0Attribute()
            return this
        }
        return this
    }
    public setSaveButtonOptions(options: SaveButtonOptions): this {
        if (this.checkPriority("setSaveButtonOptions")) {
            const options_casted = options as (SaveButtonOptions)
            this.getPeer()?.setSaveButtonOptions1Attribute(options_casted)
            return this
        }
        return this
    }
    public onClick(value: SaveButtonCallback | undefined): this {
        if (this.checkPriority("onClick")) {
            const value_casted = value as (SaveButtonCallback | undefined)
            this.getPeer()?.setOnClickAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SaveButtonAttribute> | AttributeModifier<SecurityComponentMethod> | undefined): this {
        this._modifier = value as AttributeModifier<SecurityComponentMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withSaveButtonStyle(receiver: SaveButtonAttribute, modifier: AttributeModifier<SaveButtonAttribute> | AttributeModifier<SecurityComponentMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkSaveButtonStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<SecurityComponentMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<SecurityComponentMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("SaveButton")
// export function SaveButton(
//     
//     @memo
//     content_?: () => void,
// ): SaveButtonAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function SaveButton(
    @memo
    style: ((attributes: SaveButtonAttribute) => void) | undefined,
    
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkSaveButtonComponent>((): ArkSaveButtonComponent => {
        return new ArkSaveButtonComponent()
    })
    NodeAttach<ArkSaveButtonPeer>((): ArkSaveButtonPeer => ArkSaveButtonPeer.create(receiver), (_: ArkSaveButtonPeer): void => {
        receiver.setSaveButtonOptions()
        style?.(receiver)
        withSaveButtonStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

// @memo
// @BuilderLambda("SaveButton")
// export function SaveButton(
//     options: SaveButtonOptions,
//     @memo
//     content_?: () => void,
// ): SaveButtonAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function SaveButton(
    @memo
    style: ((attributes: SaveButtonAttribute) => void) | undefined,
    options: SaveButtonOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkSaveButtonComponent>((): ArkSaveButtonComponent => {
        return new ArkSaveButtonComponent()
    })
    NodeAttach<ArkSaveButtonPeer>((): ArkSaveButtonPeer => ArkSaveButtonPeer.create(receiver), (_: ArkSaveButtonPeer): void => {
        receiver.setSaveButtonOptions(options)
        style?.(receiver)
        withSaveButtonStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkSaveButtonSet extends ArkSecurityComponentMethodSet implements SaveButtonAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _onClick_flag?: boolean
    _onClick0_value?: SaveButtonCallback | undefined
    applyModifierPatch(component: SaveButtonAttribute): void {
        if (this._onClick_flag)
            component.onClick((this._onClick0_value as SaveButtonCallback | undefined))
    }
    public onClick(value: SaveButtonCallback | undefined): this {
        this._onClick_flag = true
        this._onClick0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<SaveButtonAttribute> | AttributeModifier<SecurityComponentMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class SaveButtonOptions_serializer {
    public static write(buffer: SerializerBase, value: SaveButtonOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_icon  = value.icon
        let value_icon_type : int32 = RuntimeType.UNDEFINED
        value_icon_type = runtimeType(value_icon)
        valueSerializer.writeInt8((value_icon_type).toChar())
        if ((RuntimeType.UNDEFINED) != (value_icon_type)) {
            const value_icon_value  = (value_icon as SaveIconStyle)
            valueSerializer.writeInt32(TypeChecker.SaveIconStyle_ToNumeric(value_icon_value))
        }
        const value_text  = value.text
        let value_text_type : int32 = RuntimeType.UNDEFINED
        value_text_type = runtimeType(value_text)
        valueSerializer.writeInt8((value_text_type).toChar())
        if ((RuntimeType.UNDEFINED) != (value_text_type)) {
            const value_text_value  = (value_text as SaveDescription)
            valueSerializer.writeInt32(TypeChecker.SaveDescription_ToNumeric(value_text_value))
        }
        const value_buttonType  = value.buttonType
        let value_buttonType_type : int32 = RuntimeType.UNDEFINED
        value_buttonType_type = runtimeType(value_buttonType)
        valueSerializer.writeInt8((value_buttonType_type).toChar())
        if ((RuntimeType.UNDEFINED) != (value_buttonType_type)) {
            const value_buttonType_value  = (value_buttonType as ButtonType)
            valueSerializer.writeInt32(TypeChecker.ButtonType_ToNumeric(value_buttonType_value))
        }
    }
    public static read(buffer: DeserializerBase): SaveButtonOptions {
        let valueDeserializer : DeserializerBase = buffer
        const icon_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let icon_buf : SaveIconStyle | undefined
        if ((RuntimeType.UNDEFINED) != (icon_buf_runtimeType))
        {
            icon_buf = TypeChecker.SaveIconStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const icon_result : SaveIconStyle | undefined = icon_buf
        const text_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let text_buf : SaveDescription | undefined
        if ((RuntimeType.UNDEFINED) != (text_buf_runtimeType))
        {
            text_buf = TypeChecker.SaveDescription_FromNumeric(valueDeserializer.readInt32())
        }
        const text_result : SaveDescription | undefined = text_buf
        const buttonType_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let buttonType_buf : ButtonType | undefined
        if ((RuntimeType.UNDEFINED) != (buttonType_buf_runtimeType))
        {
            buttonType_buf = TypeChecker.ButtonType_FromNumeric(valueDeserializer.readInt32())
        }
        const buttonType_result : ButtonType | undefined = buttonType_buf
        let value : SaveButtonOptions = ({icon: icon_result, text: text_result, buttonType: buttonType_result} as SaveButtonOptions)
        return value
    }
}
