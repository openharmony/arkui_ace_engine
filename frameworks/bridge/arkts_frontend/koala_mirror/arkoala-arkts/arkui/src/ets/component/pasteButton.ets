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
export class ArkPasteButtonPeer extends ArkSecurityComponentMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkPasteButtonPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._PasteButton_construct(peerId, flags)
        const _peer  = new ArkPasteButtonPeer(_peerPtr, peerId, "PasteButton", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setPasteButtonOptions0Attribute(): void {
        ArkUIGeneratedNativeModule._PasteButtonInterface_setPasteButtonOptions0(this.peer.ptr)
    }
    setPasteButtonOptions1Attribute(options: PasteButtonOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        PasteButtonOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._PasteButtonInterface_setPasteButtonOptions1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnClickAttribute(value: PasteButtonCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._PasteButtonAttribute_setOnClick(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum PasteIconStyle {
    LINES = 0
}
export enum PasteDescription {
    PASTE = 0
}
export interface PasteButtonOptions {
    icon?: PasteIconStyle;
    text?: PasteDescription;
    buttonType?: ButtonType;
}
export enum PasteButtonOnClickResult {
    SUCCESS = 0,
    TEMPORARY_AUTHORIZATION_FAILED = 1
}
export type PasteButtonCallback = (event: ClickEvent, result: PasteButtonOnClickResult, error?: BusinessError) => void;
export interface PasteButtonAttribute extends SecurityComponentMethod {
    onClick(value: PasteButtonCallback | undefined): this {
        throw new Error("Unimplemented method onClick")
    }
    attributeModifier(value: AttributeModifier<PasteButtonAttribute> | AttributeModifier<SecurityComponentMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkPasteButtonStyle extends ArkSecurityComponentMethodStyle implements PasteButtonAttribute {
    onClick_value?: PasteButtonCallback | undefined
    attributeModifier_value?: AttributeModifier<PasteButtonAttribute> | AttributeModifier<CommonMethod> | undefined
    public onClick(value: PasteButtonCallback | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<PasteButtonAttribute> | AttributeModifier<SecurityComponentMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: PasteButtonAttribute): void {
        super.apply(target)
        if (this.onClick_value !== undefined)
            target.onClick(this.onClick_value!)
    }
}

export class ArkPasteButtonComponent extends ArkSecurityComponentMethodComponent implements PasteButtonAttribute {
    getPeer(): ArkPasteButtonPeer {
        return (this.peer as ArkPasteButtonPeer)
    }
    public setPasteButtonOptions(): this {
        if (this.checkPriority("setPasteButtonOptions")) {
            this.getPeer()?.setPasteButtonOptions0Attribute()
            return this
        }
        return this
    }
    public setPasteButtonOptions(options: PasteButtonOptions): this {
        if (this.checkPriority("setPasteButtonOptions")) {
            const options_casted = options as (PasteButtonOptions)
            this.getPeer()?.setPasteButtonOptions1Attribute(options_casted)
            return this
        }
        return this
    }
    public onClick(value: PasteButtonCallback | undefined): this {
        if (this.checkPriority("onClick")) {
            const value_casted = value as (PasteButtonCallback | undefined)
            this.getPeer()?.setOnClickAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<PasteButtonAttribute> | AttributeModifier<SecurityComponentMethod> | undefined): this {
        this._modifier = value as AttributeModifier<SecurityComponentMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withPasteButtonStyle(receiver: PasteButtonAttribute, modifier: AttributeModifier<PasteButtonAttribute> | AttributeModifier<SecurityComponentMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkPasteButtonStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<SecurityComponentMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<SecurityComponentMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("PasteButton")
// export function PasteButton(
//     
//     @memo
//     content_?: () => void,
// ): PasteButtonAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function PasteButton(
    @memo
    style: ((attributes: PasteButtonAttribute) => void) | undefined,
    
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkPasteButtonComponent>((): ArkPasteButtonComponent => {
        return new ArkPasteButtonComponent()
    })
    NodeAttach<ArkPasteButtonPeer>((): ArkPasteButtonPeer => ArkPasteButtonPeer.create(receiver), (_: ArkPasteButtonPeer): void => {
        receiver.setPasteButtonOptions()
        style?.(receiver)
        withPasteButtonStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

// @memo
// @BuilderLambda("PasteButton")
// export function PasteButton(
//     options: PasteButtonOptions,
//     @memo
//     content_?: () => void,
// ): PasteButtonAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function PasteButton(
    @memo
    style: ((attributes: PasteButtonAttribute) => void) | undefined,
    options: PasteButtonOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkPasteButtonComponent>((): ArkPasteButtonComponent => {
        return new ArkPasteButtonComponent()
    })
    NodeAttach<ArkPasteButtonPeer>((): ArkPasteButtonPeer => ArkPasteButtonPeer.create(receiver), (_: ArkPasteButtonPeer): void => {
        receiver.setPasteButtonOptions(options)
        style?.(receiver)
        withPasteButtonStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkPasteButtonSet extends ArkSecurityComponentMethodSet implements PasteButtonAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _onClick_flag?: boolean
    _onClick0_value?: PasteButtonCallback | undefined
    applyModifierPatch(component: PasteButtonAttribute): void {
        if (this._onClick_flag)
            component.onClick((this._onClick0_value as PasteButtonCallback | undefined))
    }
    public onClick(value: PasteButtonCallback | undefined): this {
        this._onClick_flag = true
        this._onClick0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<PasteButtonAttribute> | AttributeModifier<SecurityComponentMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class PasteButtonOptions_serializer {
    public static write(buffer: SerializerBase, value: PasteButtonOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_icon  = value.icon
        let value_icon_type : int32 = RuntimeType.UNDEFINED
        value_icon_type = runtimeType(value_icon)
        valueSerializer.writeInt8((value_icon_type).toChar())
        if ((value_icon_type) != (RuntimeType.UNDEFINED)) {
            const value_icon_value  = (value_icon as PasteIconStyle)
            valueSerializer.writeInt32(TypeChecker.PasteIconStyle_ToNumeric(value_icon_value))
        }
        const value_text  = value.text
        let value_text_type : int32 = RuntimeType.UNDEFINED
        value_text_type = runtimeType(value_text)
        valueSerializer.writeInt8((value_text_type).toChar())
        if ((value_text_type) != (RuntimeType.UNDEFINED)) {
            const value_text_value  = (value_text as PasteDescription)
            valueSerializer.writeInt32(TypeChecker.PasteDescription_ToNumeric(value_text_value))
        }
        const value_buttonType  = value.buttonType
        let value_buttonType_type : int32 = RuntimeType.UNDEFINED
        value_buttonType_type = runtimeType(value_buttonType)
        valueSerializer.writeInt8((value_buttonType_type).toChar())
        if ((value_buttonType_type) != (RuntimeType.UNDEFINED)) {
            const value_buttonType_value  = (value_buttonType as ButtonType)
            valueSerializer.writeInt32(TypeChecker.ButtonType_ToNumeric(value_buttonType_value))
        }
    }
    public static read(buffer: DeserializerBase): PasteButtonOptions {
        let valueDeserializer : DeserializerBase = buffer
        const icon_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let icon_buf : PasteIconStyle | undefined
        if ((icon_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            icon_buf = TypeChecker.PasteIconStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const icon_result : PasteIconStyle | undefined = icon_buf
        const text_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let text_buf : PasteDescription | undefined
        if ((text_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            text_buf = TypeChecker.PasteDescription_FromNumeric(valueDeserializer.readInt32())
        }
        const text_result : PasteDescription | undefined = text_buf
        const buttonType_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let buttonType_buf : ButtonType | undefined
        if ((buttonType_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            buttonType_buf = TypeChecker.ButtonType_FromNumeric(valueDeserializer.readInt32())
        }
        const buttonType_result : ButtonType | undefined = buttonType_buf
        let value : PasteButtonOptions = ({icon: icon_result, text: text_result, buttonType: buttonType_result} as PasteButtonOptions)
        return value
    }
}
