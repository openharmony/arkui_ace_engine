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
import { Bindable_Boolean_serializer, ArkCommonMethodPeer, CommonMethod, Bindable, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Resource_serializer } from "./../framework/resource"
import { SymbolGlyphModifier_serializer } from "./../SymbolGlyphModifier"
import { Font_serializer, ResourceStr, Font, ResourceColor } from "./units"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { Resource } from "global.resource"
import { extractors, AttributeModifier, hookMenuItemAttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { SymbolGlyphModifier } from "arkui.SymbolGlyphModifier"
import { Color } from "./enums"
import { CustomBuilder } from "./builder"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { MenuItemModifier } from "./../MenuItemModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkMenuItemPeer extends ArkCommonMethodPeer {
    attributeSet?: MenuItemModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkMenuItemPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._MenuItem_construct(peerId, flags)
        const _peer  = new ArkMenuItemPeer(_peerPtr, peerId, 'MenuItem', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setMenuItemOptionsAttribute(value?: MenuItemOptions | CustomBuilder): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof MenuItemOptions) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as MenuItemOptions
                MenuItemOptions_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof CustomBuilder) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueTmpValueForIdx1))
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._MenuItemInterface_setMenuItemOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedAttribute(value: boolean | Bindable<boolean> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof boolean) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as boolean
                thisSerializer.writeBoolean(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Bindable<boolean>) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Bindable<boolean>
                Bindable_Boolean_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._MenuItemAttribute_setSelected(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectIconAttribute(value: boolean | ResourceStr | SymbolGlyphModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof boolean) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as boolean
                thisSerializer.writeBoolean(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof ResourceStr) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as ResourceStr
                if (valueTmpValueForIdx1 instanceof string) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueForIdx1ForIdx0  = valueTmpValueForIdx1 as string
                    thisSerializer.writeString(valueTmpValueForIdx1ForIdx0)
                } else if (valueTmpValueForIdx1 instanceof Resource) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx1ForIdx1  = valueTmpValueForIdx1 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx1ForIdx1)
                }
            } else if (valueTmpValue instanceof SymbolGlyphModifier) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as SymbolGlyphModifier
                SymbolGlyphModifier_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._MenuItemAttribute_setSelectIcon(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnChangeAttribute(value: ((selected: boolean) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._MenuItemAttribute_setOnChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            Font_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._MenuItemAttribute_setContentFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentFontColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._MenuItemAttribute_setContentFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLabelFontAttribute(value: Font | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            Font_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._MenuItemAttribute_setLabelFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLabelFontColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._MenuItemAttribute_setLabelFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface MenuItemOptions {
    startIcon?: ResourceStr;
    symbolStartIcon?: SymbolGlyphModifier;
    content?: ResourceStr;
    endIcon?: ResourceStr;
    symbolEndIcon?: SymbolGlyphModifier;
    labelInfo?: ResourceStr;
    builder?: CustomBuilder;
}
export interface MenuItemAttribute extends CommonMethod {
    setMenuItemOptions(value?: MenuItemOptions | CustomBuilder): this {
        throw new Error("Unimplemented method setMenuItemOptions")
    }
    selected(value: boolean | Bindable<boolean> | undefined): this {
        throw new Error("Unimplemented method selected")
    }
    selectIcon(value: boolean | ResourceStr | SymbolGlyphModifier | undefined): this {
        throw new Error("Unimplemented method selectIcon")
    }
    onChange(value: ((selected: boolean) => void) | undefined): this {
        throw new Error("Unimplemented method onChange")
    }
    contentFont(value: Font | undefined): this {
        throw new Error("Unimplemented method contentFont")
    }
    contentFontColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method contentFontColor")
    }
    labelFont(value: Font | undefined): this {
        throw new Error("Unimplemented method labelFont")
    }
    labelFontColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method labelFontColor")
    }
    attributeModifier(value: AttributeModifier<MenuItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkMenuItemStyle extends ArkCommonMethodStyle implements MenuItemAttribute {
    selected_value?: boolean | Bindable<boolean> | undefined
    selectIcon_value?: boolean | ResourceStr | SymbolGlyphModifier | undefined
    onChange_value?: ((selected: boolean) => void) | undefined
    contentFont_value?: Font | undefined
    contentFontColor_value?: ResourceColor | undefined
    labelFont_value?: Font | undefined
    labelFontColor_value?: ResourceColor | undefined
    attributeModifier_value?: AttributeModifier<MenuItemAttribute> | AttributeModifier<CommonMethod> | undefined
    setMenuItemOptions(value?: MenuItemOptions | CustomBuilder): this {
        return this
    }
    selected(value: boolean | Bindable<boolean> | undefined): this {
        return this
    }
    selectIcon(value: boolean | ResourceStr | SymbolGlyphModifier | undefined): this {
        return this
    }
    onChange(value: ((selected: boolean) => void) | undefined): this {
        return this
    }
    contentFont(value: Font | undefined): this {
        return this
    }
    contentFontColor(value: ResourceColor | undefined): this {
        return this
    }
    labelFont(value: Font | undefined): this {
        return this
    }
    labelFontColor(value: ResourceColor | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<MenuItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkMenuItemComponent extends ArkCommonMethodComponent implements MenuItemAttribute {
    getPeer(): ArkMenuItemPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkMenuItemPeer)
    }
    public setMenuItemOptions(value?: MenuItemOptions | CustomBuilder): this {
        if (this.checkPriority("setMenuItemOptions")) {
            const value_casted = value as (MenuItemOptions | CustomBuilder | undefined)
            this.getPeer()?.setMenuItemOptionsAttribute(value_casted)
            this.applyOptionsFinish('MenuItemAttribute');
            return this
        }
        return this
    }
    public selected(value: boolean | Bindable<boolean> | undefined): this {
        if (this.checkPriority("selected")) {
            const value_casted = value as (boolean | Bindable<boolean> | undefined)
            this.getPeer()?.setSelectedAttribute(value_casted)
            return this
        }
        return this
    }
    public selectIcon(value: boolean | ResourceStr | SymbolGlyphModifier | undefined): this {
        if (this.checkPriority("selectIcon")) {
            const value_casted = value as (boolean | ResourceStr | SymbolGlyphModifier | undefined)
            this.getPeer()?.setSelectIconAttribute(value_casted)
            return this
        }
        return this
    }
    public onChange(value: ((selected: boolean) => void) | undefined): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (((selected: boolean) => void) | undefined)
            this.getPeer()?.setOnChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public contentFont(value: Font | undefined): this {
        if (this.checkPriority("contentFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.setContentFontAttribute(value_casted)
            return this
        }
        return this
    }
    public contentFontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("contentFontColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setContentFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public labelFont(value: Font | undefined): this {
        if (this.checkPriority("labelFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.setLabelFontAttribute(value_casted)
            return this
        }
        return this
    }
    public labelFontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("labelFontColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setLabelFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<MenuItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
          hookMenuItemAttributeModifier(this, value);
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
export function MenuItemImpl(
    @memo
    style: ((attributes: MenuItemAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkMenuItemComponent>((): ArkMenuItemComponent => {
        return new ArkMenuItemComponent()
    })
    NodeAttach<ArkMenuItemPeer>((): ArkMenuItemPeer => ArkMenuItemPeer.create(receiver), (peer: ArkMenuItemPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

export class MenuItemOptions_serializer {
    public static write(buffer: SerializerBase, value: MenuItemOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStartIcon  = value.startIcon
        if (valueHolderForStartIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartIconTmpValue  = valueHolderForStartIcon!
            if (valueHolderForStartIconTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForStartIconTmpValueForIdx0  = valueHolderForStartIconTmpValue as string
                valueSerializer.writeString(valueHolderForStartIconTmpValueForIdx0)
            } else if (valueHolderForStartIconTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForStartIconTmpValueForIdx1  = valueHolderForStartIconTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForStartIconTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSymbolStartIcon  = value.symbolStartIcon
        if (valueHolderForSymbolStartIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSymbolStartIconTmpValue  = valueHolderForSymbolStartIcon!
            SymbolGlyphModifier_serializer.write(valueSerializer, valueHolderForSymbolStartIconTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForContent  = value.content
        if (valueHolderForContent !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForContentTmpValue  = valueHolderForContent!
            if (valueHolderForContentTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForContentTmpValueForIdx0  = valueHolderForContentTmpValue as string
                valueSerializer.writeString(valueHolderForContentTmpValueForIdx0)
            } else if (valueHolderForContentTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForContentTmpValueForIdx1  = valueHolderForContentTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForContentTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEndIcon  = value.endIcon
        if (valueHolderForEndIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndIconTmpValue  = valueHolderForEndIcon!
            if (valueHolderForEndIconTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForEndIconTmpValueForIdx0  = valueHolderForEndIconTmpValue as string
                valueSerializer.writeString(valueHolderForEndIconTmpValueForIdx0)
            } else if (valueHolderForEndIconTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForEndIconTmpValueForIdx1  = valueHolderForEndIconTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForEndIconTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSymbolEndIcon  = value.symbolEndIcon
        if (valueHolderForSymbolEndIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSymbolEndIconTmpValue  = valueHolderForSymbolEndIcon!
            SymbolGlyphModifier_serializer.write(valueSerializer, valueHolderForSymbolEndIconTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLabelInfo  = value.labelInfo
        if (valueHolderForLabelInfo !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLabelInfoTmpValue  = valueHolderForLabelInfo!
            if (valueHolderForLabelInfoTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForLabelInfoTmpValueForIdx0  = valueHolderForLabelInfoTmpValue as string
                valueSerializer.writeString(valueHolderForLabelInfoTmpValueForIdx0)
            } else if (valueHolderForLabelInfoTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForLabelInfoTmpValueForIdx1  = valueHolderForLabelInfoTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForLabelInfoTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBuilder  = value.builder
        if (valueHolderForBuilder !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBuilderTmpValue  = valueHolderForBuilder!
            valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueHolderForBuilderTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): MenuItemOptions {
        let valueDeserializer : DeserializerBase = buffer
        const startIconTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let startIconTmpBuf : ResourceStr | undefined = undefined
        if ((startIconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const startIconTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let startIconTmpBuf_ : string | Resource | undefined
            if (startIconTmpBuf_UnionSelector == (0).toChar()) {
                startIconTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (startIconTmpBuf_UnionSelector == (1).toChar()) {
                startIconTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for startIconTmpBuf_ has to be chosen through deserialisation.")
            }
            startIconTmpBuf = (startIconTmpBuf_ as string | Resource)
        }
        const startIconTmpResult : ResourceStr | undefined = startIconTmpBuf
        const symbolStartIconTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let symbolStartIconTmpBuf : SymbolGlyphModifier | undefined = undefined
        if ((symbolStartIconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            symbolStartIconTmpBuf = (SymbolGlyphModifier_serializer.read(valueDeserializer) as SymbolGlyphModifier)
        }
        const symbolStartIconTmpResult : SymbolGlyphModifier | undefined = symbolStartIconTmpBuf
        const contentTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let contentTmpBuf : ResourceStr | undefined = undefined
        if ((contentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const contentTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let contentTmpBuf_ : string | Resource | undefined
            if (contentTmpBuf_UnionSelector == (0).toChar()) {
                contentTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (contentTmpBuf_UnionSelector == (1).toChar()) {
                contentTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for contentTmpBuf_ has to be chosen through deserialisation.")
            }
            contentTmpBuf = (contentTmpBuf_ as string | Resource)
        }
        const contentTmpResult : ResourceStr | undefined = contentTmpBuf
        const endIconTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let endIconTmpBuf : ResourceStr | undefined = undefined
        if ((endIconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const endIconTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let endIconTmpBuf_ : string | Resource | undefined
            if (endIconTmpBuf_UnionSelector == (0).toChar()) {
                endIconTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (endIconTmpBuf_UnionSelector == (1).toChar()) {
                endIconTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for endIconTmpBuf_ has to be chosen through deserialisation.")
            }
            endIconTmpBuf = (endIconTmpBuf_ as string | Resource)
        }
        const endIconTmpResult : ResourceStr | undefined = endIconTmpBuf
        const symbolEndIconTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let symbolEndIconTmpBuf : SymbolGlyphModifier | undefined = undefined
        if ((symbolEndIconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            symbolEndIconTmpBuf = (SymbolGlyphModifier_serializer.read(valueDeserializer) as SymbolGlyphModifier)
        }
        const symbolEndIconTmpResult : SymbolGlyphModifier | undefined = symbolEndIconTmpBuf
        const labelInfoTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let labelInfoTmpBuf : ResourceStr | undefined = undefined
        if ((labelInfoTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const labelInfoTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let labelInfoTmpBuf_ : string | Resource | undefined
            if (labelInfoTmpBuf_UnionSelector == (0).toChar()) {
                labelInfoTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (labelInfoTmpBuf_UnionSelector == (1).toChar()) {
                labelInfoTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for labelInfoTmpBuf_ has to be chosen through deserialisation.")
            }
            labelInfoTmpBuf = (labelInfoTmpBuf_ as string | Resource)
        }
        const labelInfoTmpResult : ResourceStr | undefined = labelInfoTmpBuf
        const builderTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let builderTmpBuf : CustomBuilder | undefined = undefined
        if ((builderTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const builderTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const builderTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const builderTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            builderTmpBuf = ():void => {
                const builderTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                builderTmpBuf_BufArgsSerializer.writeInt32(builderTmpBuf_BufResource.resourceId);
                builderTmpBuf_BufArgsSerializer.writePointer(builderTmpBuf_BufCall);
                builderTmpBuf_BufArgsSerializer.writePointer(builderTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, 737226752, builderTmpBuf_BufArgsSerializer.asBuffer(), builderTmpBuf_BufArgsSerializer.length());
                builderTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const builderTmpResult : CustomBuilder | undefined = builderTmpBuf
        let value : MenuItemOptions = ({startIcon: startIconTmpResult, symbolStartIcon: symbolStartIconTmpResult, content: contentTmpResult, endIcon: endIconTmpResult, symbolEndIcon: symbolEndIconTmpResult, labelInfo: labelInfoTmpResult, builder: builderTmpResult} as MenuItemOptions)
        return value
    }
}
