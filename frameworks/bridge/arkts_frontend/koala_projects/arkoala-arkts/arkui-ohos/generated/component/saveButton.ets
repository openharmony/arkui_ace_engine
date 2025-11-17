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
import { Resource_serializer } from "./../framework/resource"
import { SizeOptions_serializer, BorderRadiuses_serializer, Dimension, SizeOptions, BorderRadiuses } from "./units"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkSecurityComponentMethodPeer, SecurityComponentMethod, ArkSecurityComponentMethodComponent, ArkSecurityComponentMethodStyle } from "./securityComponent"
import { ClickEvent } from "./common"
import { extractors, hookSaveButtonAttributeModifier, AttributeModifier, AttributeUpdater } from "#handwritten"
import { BusinessError } from "@ohos.base"
import { Resource } from "global.resource"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { ButtonType } from "./button"
import { SaveButtonModifier } from "./../SaveButtonModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ModifierStateManager } from '../CommonModifier';
export class ArkSaveButtonPeer extends ArkSecurityComponentMethodPeer {
    attributeSet?: SaveButtonModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSaveButtonPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._SaveButton_construct(peerId, flags)
        const _peer  = new ArkSaveButtonPeer(_peerPtr, peerId, 'SaveButton', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSaveButtonOptionsAttribute(options?: SaveButtonOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            SaveButtonOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SaveButtonInterface_setSaveButtonOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnClickAttribute(value: SaveButtonCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SaveButtonAttribute_setOnClick(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSetIconAttribute(value: Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            Resource_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SaveButtonAttribute_setSetIcon(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSetTextAttribute(value: string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SaveButtonAttribute_setSetText(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIconSizeAttribute(value: Dimension | SizeOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Dimension) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Dimension
                if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueForIdx0ForIdx0  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx0)
                } else if (valueTmpValueForIdx0 instanceof number) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as number
                    thisSerializer.writeNumber(valueTmpValueForIdx0ForIdx1)
                } else if (valueTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((2).toByte())
                    const valueTmpValueForIdx0ForIdx2  = valueTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx2)
                }
            } else if (valueTmpValue instanceof SizeOptions) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as SizeOptions
                SizeOptions_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SaveButtonAttribute_setIconSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIconBorderRadiusAttribute(value: Dimension | BorderRadiuses | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Dimension) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Dimension
                if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueForIdx0ForIdx0  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx0)
                } else if (valueTmpValueForIdx0 instanceof number) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as number
                    thisSerializer.writeNumber(valueTmpValueForIdx0ForIdx1)
                } else if (valueTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((2).toByte())
                    const valueTmpValueForIdx0ForIdx2  = valueTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx2)
                }
            } else if (valueTmpValue instanceof BorderRadiuses) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as BorderRadiuses
                BorderRadiuses_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SaveButtonAttribute_setIconBorderRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStateEffectAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SaveButtonAttribute_setStateEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    setSaveButtonOptions(options?: SaveButtonOptions): this {
        throw new Error("Unimplemented method setSaveButtonOptions")
    }
    onClick(value: SaveButtonCallback | undefined): this {
        throw new Error("Unimplemented method onClick")
    }
    setIcon(value: Resource | undefined): this {
        throw new Error("Unimplemented method setIcon")
    }
    setText(value: string | Resource | undefined): this {
        throw new Error("Unimplemented method setText")
    }
    iconSize(value: Dimension | SizeOptions | undefined): this {
        throw new Error("Unimplemented method iconSize")
    }
    iconBorderRadius(value: Dimension | BorderRadiuses | undefined): this {
        throw new Error("Unimplemented method iconBorderRadius")
    }
    stateEffect(value: boolean | undefined): this {
        throw new Error("Unimplemented method stateEffect")
    }
    attributeModifier(value: AttributeModifier<SaveButtonAttribute> | AttributeModifier<SecurityComponentMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkSaveButtonStyle extends ArkSecurityComponentMethodStyle implements SaveButtonAttribute {
    onClick_value?: SaveButtonCallback | undefined
    setIcon_value?: Resource | undefined
    setText_value?: string | Resource | undefined
    iconSize_value?: Dimension | SizeOptions | undefined
    iconBorderRadius_value?: Dimension | BorderRadiuses | undefined
    stateEffect_value?: boolean | undefined
    setSaveButtonOptions(options?: SaveButtonOptions): this {
        return this
    }
    onClick(value: SaveButtonCallback | undefined): this {
        return this
    }
    setIcon(value: Resource | undefined): this {
        return this
    }
    setText(value: string | Resource | undefined): this {
        return this
    }
    iconSize(value: Dimension | SizeOptions | undefined): this {
        return this
    }
    iconBorderRadius(value: Dimension | BorderRadiuses | undefined): this {
        return this
    }
    stateEffect(value: boolean | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<SaveButtonAttribute> | AttributeModifier<SecurityComponentMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkSaveButtonComponent extends ArkSecurityComponentMethodComponent implements SaveButtonAttribute {
    getPeer(): ArkSaveButtonPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkSaveButtonPeer)
    }
    public setSaveButtonOptions(options?: SaveButtonOptions): this {
        if (this.checkPriority("setSaveButtonOptions")) {
            const options_casted = options as (SaveButtonOptions | undefined)
            this.getPeer()?.setSaveButtonOptionsAttribute(options_casted)
            this.applyOptionsFinish('SaveButtonAttribute');
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
    public setIcon(value: Resource | undefined): this {
        if (this.checkPriority("setIcon")) {
            const value_casted = value as (Resource | undefined)
            this.getPeer()?.setSetIconAttribute(value_casted)
            return this
        }
        return this
    }
    public setText(value: string | Resource | undefined): this {
        if (this.checkPriority("setText")) {
            const value_casted = value as (string | Resource | undefined)
            this.getPeer()?.setSetTextAttribute(value_casted)
            return this
        }
        return this
    }
    public iconSize(value: Dimension | SizeOptions | undefined): this {
        if (this.checkPriority("iconSize")) {
            const value_casted = value as (Dimension | SizeOptions | undefined)
            this.getPeer()?.setIconSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public iconBorderRadius(value: Dimension | BorderRadiuses | undefined): this {
        if (this.checkPriority("iconBorderRadius")) {
            const value_casted = value as (Dimension | BorderRadiuses | undefined)
            this.getPeer()?.setIconBorderRadiusAttribute(value_casted)
            return this
        }
        return this
    }
    public stateEffect(value: boolean | undefined): this {
        if (this.checkPriority("stateEffect")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setStateEffectAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SaveButtonAttribute> | AttributeModifier<SecurityComponentMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookSaveButtonAttributeModifier(this, value);
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
export function SaveButtonImpl(
    @memo
    style: ((attributes: SaveButtonAttribute) => void) | undefined,
): void {
    const receiver = remember<ArkSaveButtonComponent>((): ArkSaveButtonComponent => {
        return new ArkSaveButtonComponent()
    })
    NodeAttach<ArkSaveButtonPeer>((): ArkSaveButtonPeer => ArkSaveButtonPeer.create(receiver), (peer: ArkSaveButtonPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.applyAttributesFinish()
        receiver.setPeer(undefined)
    })
}

export class SaveButtonOptions_serializer {
    public static write(buffer: SerializerBase, value: SaveButtonOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForIcon  = value.icon
        if (valueHolderForIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIconTmpValue  = (valueHolderForIcon as SaveIconStyle)
            valueSerializer.writeInt32(valueHolderForIconTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForText  = value.text
        if (valueHolderForText !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextTmpValue  = (valueHolderForText as SaveDescription)
            valueSerializer.writeInt32(valueHolderForTextTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForButtonType  = value.buttonType
        if (valueHolderForButtonType !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForButtonTypeTmpValue  = (valueHolderForButtonType as ButtonType)
            valueSerializer.writeInt32(valueHolderForButtonTypeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SaveButtonOptions {
        let valueDeserializer : DeserializerBase = buffer
        const iconTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let iconTmpBuf : SaveIconStyle | undefined = undefined
        if ((iconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            iconTmpBuf = SaveIconStyle.fromValue(valueDeserializer.readInt32())
        }
        const iconTmpResult : SaveIconStyle | undefined = iconTmpBuf
        const textTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textTmpBuf : SaveDescription | undefined = undefined
        if ((textTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            textTmpBuf = SaveDescription.fromValue(valueDeserializer.readInt32())
        }
        const textTmpResult : SaveDescription | undefined = textTmpBuf
        const buttonTypeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let buttonTypeTmpBuf : ButtonType | undefined = undefined
        if ((buttonTypeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            buttonTypeTmpBuf = ButtonType.fromValue(valueDeserializer.readInt32())
        }
        const buttonTypeTmpResult : ButtonType | undefined = buttonTypeTmpBuf
        let value : SaveButtonOptions = ({icon: iconTmpResult, text: textTmpResult, buttonType: buttonTypeTmpResult} as SaveButtonOptions)
        return value
    }
}
