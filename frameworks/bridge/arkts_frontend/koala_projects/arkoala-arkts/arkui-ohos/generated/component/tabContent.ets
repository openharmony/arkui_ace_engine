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

import { SerializerBase, DeserializerBase, Finalizable, RuntimeType, toPeerPtr, KPointer, MaterializedBase, MaterializedBaseTag, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { global_resource_Resource_serializer } from './../framework/resource'
import { Padding_serializer, LocalizedPadding_serializer, ResourceStr as arkui_component_units_ResourceStr, Resource as arkui_component_units_Resource, Padding, Dimension, LocalizedPadding, VoidCallback, ResourceColor, Length, Font as arkui_component_units_Font, arkui_component_units_Font_serializer } from './units'
import { Resource as global_resource_Resource } from 'global.resource'
import { VerticalAlign, Color as arkui_component_enums_Color, TextOverflow, TextHeightAdaptivePolicy } from './enums'
import { unsafeCast, int32, int64, float32 } from '@koalaui/common'
import { ArkUIGeneratedNativeModule } from '#components'
import { CallbackTransformer } from './../CallbackTransformer'
import { ComponentContent_serializer } from './../framework/ComponentContent'
import { extractors, AttributeModifier, hookTabContentAttributeModifier, AttributeUpdater } from '#handwritten'
import { ComponentContent } from '@arkui.ComponentContent'
import { SymbolGlyphModifier_serializer } from './../framework/SymbolGlyphModifier'
import { SymbolGlyphModifier } from '@arkui.SymbolGlyphModifier'
import { ArkThemeScopeManager } from '#arktheme'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent } from './common'
import { CustomBuilder } from './builder'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { TabContentModifier } from './../TabContentModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class BottomTabBarStyleInternal {
    public static fromPtr(ptr: KPointer): BottomTabBarStyle {
        return new BottomTabBarStyle(MaterializedBaseTag.NOP, ptr)
    }
}
export class BottomTabBarStyle implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, BottomTabBarStyle.getFinalizer())
    }
    constructor(icon: arkui_component_units_ResourceStr | TabBarSymbol, text: arkui_component_units_ResourceStr) {
        this(MaterializedBaseTag.NOP, BottomTabBarStyle.construct(icon, text))
    }
    static construct(icon: arkui_component_units_ResourceStr | TabBarSymbol, text: arkui_component_units_ResourceStr): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (icon instanceof arkui_component_units_ResourceStr) {
            thisSerializer.writeInt8((0).toByte())
            const iconForIdx0  = icon as arkui_component_units_ResourceStr
            if (iconForIdx0 instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const iconForIdx0ForIdx0  = iconForIdx0 as string
                thisSerializer.writeString(iconForIdx0ForIdx0)
            } else if (iconForIdx0 instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((1).toByte())
                const iconForIdx0ForIdx1  = iconForIdx0 as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, iconForIdx0ForIdx1)
            }
        } else if (icon instanceof TabBarSymbol) {
            thisSerializer.writeInt8((1).toByte())
            const iconForIdx1  = icon as TabBarSymbol
            TabBarSymbol_serializer.write(thisSerializer, iconForIdx1)
        }
        if (text instanceof string) {
            thisSerializer.writeInt8((0).toByte())
            const textForIdx0  = text as string
            thisSerializer.writeString(textForIdx0)
        } else if (text instanceof arkui_component_units_Resource) {
            thisSerializer.writeInt8((1).toByte())
            const textForIdx1  = text as arkui_component_units_Resource
            global_resource_Resource_serializer.write(thisSerializer, textForIdx1)
        }
        const retval  = ArkUIGeneratedNativeModule._BottomTabBarStyle_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._BottomTabBarStyle_getFinalizer()
    }
    public static of(icon: arkui_component_units_ResourceStr | TabBarSymbol, text: arkui_component_units_ResourceStr): BottomTabBarStyle {
        const icon_casted = icon as (arkui_component_units_ResourceStr | TabBarSymbol)
        const text_casted = text as (arkui_component_units_ResourceStr)
        return BottomTabBarStyle.of_serialize(icon_casted, text_casted)
    }
    private static of_serialize(icon: arkui_component_units_ResourceStr | TabBarSymbol, text: arkui_component_units_ResourceStr): BottomTabBarStyle {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (icon instanceof arkui_component_units_ResourceStr) {
            thisSerializer.writeInt8((0).toByte())
            const iconForIdx0  = icon as arkui_component_units_ResourceStr
            if (iconForIdx0 instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const iconForIdx0ForIdx0  = iconForIdx0 as string
                thisSerializer.writeString(iconForIdx0ForIdx0)
            } else if (iconForIdx0 instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((1).toByte())
                const iconForIdx0ForIdx1  = iconForIdx0 as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, iconForIdx0ForIdx1)
            }
        } else if (icon instanceof TabBarSymbol) {
            thisSerializer.writeInt8((1).toByte())
            const iconForIdx1  = icon as TabBarSymbol
            TabBarSymbol_serializer.write(thisSerializer, iconForIdx1)
        }
        if (text instanceof string) {
            thisSerializer.writeInt8((0).toByte())
            const textForIdx0  = text as string
            thisSerializer.writeString(textForIdx0)
        } else if (text instanceof arkui_component_units_Resource) {
            thisSerializer.writeInt8((1).toByte())
            const textForIdx1  = text as arkui_component_units_Resource
            global_resource_Resource_serializer.write(thisSerializer, textForIdx1)
        }
        const retval  = ArkUIGeneratedNativeModule._BottomTabBarStyle_of(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : BottomTabBarStyle = BottomTabBarStyleInternal.fromPtr(retval)
        return obj
    }
    public labelStyle(style: TabBarLabelStyle): BottomTabBarStyle {
        const style_casted = style as (TabBarLabelStyle)
        return this.labelStyle_serialize(style_casted)
    }
    public padding(value: Padding | Dimension | LocalizedPadding): BottomTabBarStyle {
        const value_casted = value as (Padding | Dimension | LocalizedPadding)
        return this.padding_serialize(value_casted)
    }
    public layoutMode(value: LayoutMode): BottomTabBarStyle {
        const value_casted = value as (LayoutMode)
        return this.layoutMode_serialize(value_casted)
    }
    public verticalAlign(value: VerticalAlign): BottomTabBarStyle {
        const value_casted = value as (VerticalAlign)
        return this.verticalAlign_serialize(value_casted)
    }
    public symmetricExtensible(value: boolean): BottomTabBarStyle {
        const value_casted = value as (boolean)
        return this.symmetricExtensible_serialize(value_casted)
    }
    public id(value: string): BottomTabBarStyle {
        const value_casted = value as (string)
        return this.id_serialize(value_casted)
    }
    public iconStyle(style: TabBarIconStyle): BottomTabBarStyle {
        const style_casted = style as (TabBarIconStyle)
        return this.iconStyle_serialize(style_casted)
    }
    private labelStyle_serialize(style: TabBarLabelStyle): BottomTabBarStyle {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        TabBarLabelStyle_serializer.write(thisSerializer, style)
        const retval  = ArkUIGeneratedNativeModule._BottomTabBarStyle_labelStyle(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : BottomTabBarStyle = BottomTabBarStyleInternal.fromPtr(retval)
        return obj
    }
    private padding_serialize(value: Padding | Dimension | LocalizedPadding): BottomTabBarStyle {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value instanceof Padding) {
            thisSerializer.writeInt8((0).toByte())
            const valueForIdx0  = value as Padding
            Padding_serializer.write(thisSerializer, valueForIdx0)
        } else if (value instanceof Dimension) {
            thisSerializer.writeInt8((1).toByte())
            const valueForIdx1  = value as Dimension
            if (valueForIdx1 instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueForIdx1ForIdx0  = valueForIdx1 as string
                thisSerializer.writeString(valueForIdx1ForIdx0)
            } else if (valueForIdx1 instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueForIdx1ForIdx1  = valueForIdx1 as number
                thisSerializer.writeNumber(valueForIdx1ForIdx1)
            } else if (valueForIdx1 instanceof global_resource_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueForIdx1ForIdx2  = valueForIdx1 as global_resource_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueForIdx1ForIdx2)
            }
        } else if (value instanceof LocalizedPadding) {
            thisSerializer.writeInt8((2).toByte())
            const valueForIdx2  = value as LocalizedPadding
            LocalizedPadding_serializer.write(thisSerializer, valueForIdx2)
        }
        const retval  = ArkUIGeneratedNativeModule._BottomTabBarStyle_padding(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : BottomTabBarStyle = BottomTabBarStyleInternal.fromPtr(retval)
        return obj
    }
    private layoutMode_serialize(value: LayoutMode): BottomTabBarStyle {
        const retval  = ArkUIGeneratedNativeModule._BottomTabBarStyle_layoutMode(this.peer!.ptr, value.valueOf())
        const obj : BottomTabBarStyle = BottomTabBarStyleInternal.fromPtr(retval)
        return obj
    }
    private verticalAlign_serialize(value: VerticalAlign): BottomTabBarStyle {
        const retval  = ArkUIGeneratedNativeModule._BottomTabBarStyle_verticalAlign(this.peer!.ptr, value.valueOf())
        const obj : BottomTabBarStyle = BottomTabBarStyleInternal.fromPtr(retval)
        return obj
    }
    private symmetricExtensible_serialize(value: boolean): BottomTabBarStyle {
        const retval  = ArkUIGeneratedNativeModule._BottomTabBarStyle_symmetricExtensible(this.peer!.ptr, value ? true : false)
        const obj : BottomTabBarStyle = BottomTabBarStyleInternal.fromPtr(retval)
        return obj
    }
    private id_serialize(value: string): BottomTabBarStyle {
        const retval  = ArkUIGeneratedNativeModule._BottomTabBarStyle_id(this.peer!.ptr, value)
        const obj : BottomTabBarStyle = BottomTabBarStyleInternal.fromPtr(retval)
        return obj
    }
    private iconStyle_serialize(style: TabBarIconStyle): BottomTabBarStyle {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        TabBarIconStyle_serializer.write(thisSerializer, style)
        const retval  = ArkUIGeneratedNativeModule._BottomTabBarStyle_iconStyle(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : BottomTabBarStyle = BottomTabBarStyleInternal.fromPtr(retval)
        return obj
    }
}
export class SubTabBarStyleInternal {
    public static fromPtr(ptr: KPointer): SubTabBarStyle {
        return new SubTabBarStyle(MaterializedBaseTag.NOP, ptr)
    }
}
export class SubTabBarStyle implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, SubTabBarStyle.getFinalizer())
    }
    constructor(content: arkui_component_units_ResourceStr | ComponentContent<undefined>) {
        this(MaterializedBaseTag.NOP, SubTabBarStyle.construct(content))
    }
    static construct(content: arkui_component_units_ResourceStr | ComponentContent<undefined>): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (content instanceof arkui_component_units_ResourceStr) {
            thisSerializer.writeInt8((0).toByte())
            const contentForIdx0  = content as arkui_component_units_ResourceStr
            if (contentForIdx0 instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const contentForIdx0ForIdx0  = contentForIdx0 as string
                thisSerializer.writeString(contentForIdx0ForIdx0)
            } else if (contentForIdx0 instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((1).toByte())
                const contentForIdx0ForIdx1  = contentForIdx0 as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, contentForIdx0ForIdx1)
            }
        } else if (content instanceof ComponentContent) {
            thisSerializer.writeInt8((1).toByte())
            const contentForIdx1  = content as ComponentContent
            ComponentContent_serializer.write(thisSerializer, contentForIdx1)
        }
        const retval  = ArkUIGeneratedNativeModule._SubTabBarStyle_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SubTabBarStyle_getFinalizer()
    }
    public static of(content: arkui_component_units_ResourceStr | ComponentContent<undefined>): SubTabBarStyle {
        const content_casted = content as (arkui_component_units_ResourceStr | ComponentContent<undefined>)
        return SubTabBarStyle.of_serialize(content_casted)
    }
    private static of_serialize(content: arkui_component_units_ResourceStr | ComponentContent<undefined>): SubTabBarStyle {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (content instanceof arkui_component_units_ResourceStr) {
            thisSerializer.writeInt8((0).toByte())
            const contentForIdx0  = content as arkui_component_units_ResourceStr
            if (contentForIdx0 instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const contentForIdx0ForIdx0  = contentForIdx0 as string
                thisSerializer.writeString(contentForIdx0ForIdx0)
            } else if (contentForIdx0 instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((1).toByte())
                const contentForIdx0ForIdx1  = contentForIdx0 as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, contentForIdx0ForIdx1)
            }
        } else if (content instanceof ComponentContent) {
            thisSerializer.writeInt8((1).toByte())
            const contentForIdx1  = content as ComponentContent
            ComponentContent_serializer.write(thisSerializer, contentForIdx1)
        }
        const retval  = ArkUIGeneratedNativeModule._SubTabBarStyle_of(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : SubTabBarStyle = SubTabBarStyleInternal.fromPtr(retval)
        return obj
    }
    public indicator(style: SubTabBarIndicatorStyle): SubTabBarStyle {
        const style_casted = style as (SubTabBarIndicatorStyle)
        return this.indicator_serialize(style_casted)
    }
    public selectedMode(value: SelectedMode): SubTabBarStyle {
        const value_casted = value as (SelectedMode)
        return this.selectedMode_serialize(value_casted)
    }
    public board(value: BoardStyle): SubTabBarStyle {
        const value_casted = value as (BoardStyle)
        return this.board_serialize(value_casted)
    }
    public labelStyle(style: TabBarLabelStyle): SubTabBarStyle {
        const style_casted = style as (TabBarLabelStyle)
        return this.labelStyle_serialize(style_casted)
    }
    public padding(value: Padding | Dimension): SubTabBarStyle {
        const value_casted = value as (Padding | Dimension)
        return this.padding0_serialize(value_casted)
    }
    public padding(padding: LocalizedPadding): SubTabBarStyle {
        const padding_casted = padding as (LocalizedPadding)
        return this.padding1_serialize(padding_casted)
    }
    public id(value: string): SubTabBarStyle {
        const value_casted = value as (string)
        return this.id_serialize(value_casted)
    }
    private indicator_serialize(style: SubTabBarIndicatorStyle): SubTabBarStyle {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        SubTabBarIndicatorStyle_serializer.write(thisSerializer, style)
        const retval  = ArkUIGeneratedNativeModule._SubTabBarStyle_indicator(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : SubTabBarStyle = SubTabBarStyleInternal.fromPtr(retval)
        return obj
    }
    private selectedMode_serialize(value: SelectedMode): SubTabBarStyle {
        const retval  = ArkUIGeneratedNativeModule._SubTabBarStyle_selectedMode(this.peer!.ptr, value.valueOf())
        const obj : SubTabBarStyle = SubTabBarStyleInternal.fromPtr(retval)
        return obj
    }
    private board_serialize(value: BoardStyle): SubTabBarStyle {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        BoardStyle_serializer.write(thisSerializer, value)
        const retval  = ArkUIGeneratedNativeModule._SubTabBarStyle_board(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : SubTabBarStyle = SubTabBarStyleInternal.fromPtr(retval)
        return obj
    }
    private labelStyle_serialize(style: TabBarLabelStyle): SubTabBarStyle {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        TabBarLabelStyle_serializer.write(thisSerializer, style)
        const retval  = ArkUIGeneratedNativeModule._SubTabBarStyle_labelStyle(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : SubTabBarStyle = SubTabBarStyleInternal.fromPtr(retval)
        return obj
    }
    private padding0_serialize(value: Padding | Dimension): SubTabBarStyle {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value instanceof Padding) {
            thisSerializer.writeInt8((0).toByte())
            const valueForIdx0  = value as Padding
            Padding_serializer.write(thisSerializer, valueForIdx0)
        } else if (value instanceof Dimension) {
            thisSerializer.writeInt8((1).toByte())
            const valueForIdx1  = value as Dimension
            if (valueForIdx1 instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueForIdx1ForIdx0  = valueForIdx1 as string
                thisSerializer.writeString(valueForIdx1ForIdx0)
            } else if (valueForIdx1 instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueForIdx1ForIdx1  = valueForIdx1 as number
                thisSerializer.writeNumber(valueForIdx1ForIdx1)
            } else if (valueForIdx1 instanceof global_resource_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueForIdx1ForIdx2  = valueForIdx1 as global_resource_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueForIdx1ForIdx2)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._SubTabBarStyle_padding0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : SubTabBarStyle = SubTabBarStyleInternal.fromPtr(retval)
        return obj
    }
    private padding1_serialize(padding: LocalizedPadding): SubTabBarStyle {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        LocalizedPadding_serializer.write(thisSerializer, padding)
        const retval  = ArkUIGeneratedNativeModule._SubTabBarStyle_padding1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : SubTabBarStyle = SubTabBarStyleInternal.fromPtr(retval)
        return obj
    }
    private id_serialize(value: string): SubTabBarStyle {
        const retval  = ArkUIGeneratedNativeModule._SubTabBarStyle_id(this.peer!.ptr, value)
        const obj : SubTabBarStyle = SubTabBarStyleInternal.fromPtr(retval)
        return obj
    }
}
export class TabBarSymbolInternal {
    public static fromPtr(ptr: KPointer): TabBarSymbol {
        return new TabBarSymbol(MaterializedBaseTag.NOP, ptr)
    }
}
export class TabBarSymbol implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    public normal: SymbolGlyphModifier
    public selected?: SymbolGlyphModifier | undefined
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, TabBarSymbol.getFinalizer())
        this.normal = this.getNormal()
        this.selected = this.getSelected()
    }
    constructor() {
        this(MaterializedBaseTag.NOP, TabBarSymbol.construct())
        this.normal = this.getNormal()
        this.selected = this.getSelected()
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TabBarSymbol_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TabBarSymbol_getFinalizer()
    }
    private getNormal(): SymbolGlyphModifier {
        return this.getNormal_serialize()
    }
    private setNormal(normal: SymbolGlyphModifier): void {
        const normal_casted = normal as (SymbolGlyphModifier)
        this.setNormal_serialize(normal_casted)
        return
    }
    private getSelected(): SymbolGlyphModifier | undefined {
        return this.getSelected_serialize()
    }
    private setSelected(selected: SymbolGlyphModifier | undefined): void {
        const selected_casted = selected as (SymbolGlyphModifier | undefined)
        this.setSelected_serialize(selected_casted)
        return
    }
    private getNormal_serialize(): SymbolGlyphModifier {
        const retval  = ArkUIGeneratedNativeModule._TabBarSymbol_getNormal(this.peer!.ptr)
        const obj : SymbolGlyphModifier = extractors.fromSymbolGlyphModifierPtr(retval)
        return obj
    }
    private setNormal_serialize(normal: SymbolGlyphModifier): void {
        ArkUIGeneratedNativeModule._TabBarSymbol_setNormal(this.peer!.ptr, extractors.toSymbolGlyphModifierPtr(normal))
    }
    private getSelected_serialize(): SymbolGlyphModifier | undefined {
        const retval  = ArkUIGeneratedNativeModule._TabBarSymbol_getSelected(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : SymbolGlyphModifier | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = (SymbolGlyphModifier_serializer.read(retvalDeserializer) as SymbolGlyphModifier)
        }
        const returnResult : SymbolGlyphModifier | undefined = buffer
        return returnResult
    }
    private setSelected_serialize(selected: SymbolGlyphModifier | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (selected !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const selectedTmpValue  = selected!
            SymbolGlyphModifier_serializer.write(thisSerializer, selectedTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabBarSymbol_setSelected(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkTabContentPeer extends ArkCommonMethodPeer {
    attributeSet?: TabContentModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkTabContentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._TabContent_construct(peerId, flags)
        const _peer  = new ArkTabContentPeer(_peerPtr, peerId, 'TabContent', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTabContentOptionsAttribute(): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        ArkUIGeneratedNativeModule._TabContentInterface_setTabContentOptions(this.peer.ptr)
    }
    setTabBarAttribute(value: ComponentContent<undefined> | SubTabBarStyle | BottomTabBarStyle | string | arkui_component_units_Resource | CustomBuilder | TabBarOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof ComponentContent) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as ComponentContent
                ComponentContent_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof SubTabBarStyle) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as SubTabBarStyle
                SubTabBarStyle_serializer.write(thisSerializer, valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof BottomTabBarStyle) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as BottomTabBarStyle
                BottomTabBarStyle_serializer.write(thisSerializer, valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx3)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((4).toByte())
                const valueTmpValueForIdx4  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx4)
            } else if (valueTmpValue instanceof CustomBuilder) {
                thisSerializer.writeInt8((5).toByte())
                const valueTmpValueForIdx5  = valueTmpValue as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueTmpValueForIdx5))
            } else if (valueTmpValue instanceof TabBarOptions) {
                thisSerializer.writeInt8((6).toByte())
                const valueTmpValueForIdx6  = valueTmpValue as TabBarOptions
                TabBarOptions_serializer.write(thisSerializer, valueTmpValueForIdx6)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabContentAttribute_setTabBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillShowAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabContentAttribute_setOnWillShow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillHideAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TabContentAttribute_setOnWillHide(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum SelectedMode {
    INDICATOR = 0,
    BOARD = 1
}
export enum LayoutMode {
    AUTO = 0,
    VERTICAL = 1,
    HORIZONTAL = 2
}
export interface SubTabBarIndicatorStyle {
    color?: ResourceColor;
    height?: Length;
    width?: Length;
    borderRadius?: Length;
    marginTop?: Length;
}
export interface BoardStyle {
    borderRadius?: Length;
}
export interface TabBarLabelStyle {
    overflow?: TextOverflow;
    maxLines?: int32;
    minFontSize?: double | arkui_component_units_ResourceStr;
    maxFontSize?: double | arkui_component_units_ResourceStr;
    heightAdaptivePolicy?: TextHeightAdaptivePolicy;
    font?: arkui_component_units_Font;
    selectedColor?: ResourceColor;
    unselectedColor?: ResourceColor;
}
export interface TabBarIconStyle {
    selectedColor?: ResourceColor;
    unselectedColor?: ResourceColor;
}
export interface TabBarOptions {
    icon?: string | arkui_component_units_Resource;
    text?: string | arkui_component_units_Resource;
}
export interface TabContentAttribute extends CommonMethod {
    setTabContentOptions(): this {
        throw new Error('Unimplemented method setTabContentOptions')
    }
    tabBar(value: ComponentContent<undefined> | SubTabBarStyle | BottomTabBarStyle | string | arkui_component_units_Resource | CustomBuilder | TabBarOptions | undefined): this {
        throw new Error('Unimplemented method tabBar')
    }
    onWillShow(value: VoidCallback | undefined): this {
        throw new Error('Unimplemented method onWillShow')
    }
    onWillHide(value: VoidCallback | undefined): this {
        throw new Error('Unimplemented method onWillHide')
    }
    attributeModifier(value: AttributeModifier<TabContentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkTabContentComponent extends ArkCommonMethodComponent implements TabContentAttribute {
    getPeer(): ArkTabContentPeer {
        return (this.peer as ArkTabContentPeer)
    }
    public setTabContentOptions(): this {
        if (this.checkPriority('setTabContentOptions')) {
            this.getPeer()?.setTabContentOptionsAttribute()
            this.applyOptionsFinish('TabContentAttribute');
            return this
        }
        return this
    }
    public tabBar(value: ComponentContent<undefined> | SubTabBarStyle | BottomTabBarStyle | string | arkui_component_units_Resource | CustomBuilder | TabBarOptions | undefined): this {
        if (this.checkPriority('tabBar')) {
            const value_casted = value as (ComponentContent<undefined> | SubTabBarStyle | BottomTabBarStyle | string | arkui_component_units_Resource | CustomBuilder | TabBarOptions | undefined)
            this.getPeer()?.setTabBarAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillShow(value: VoidCallback | undefined): this {
        if (this.checkPriority('onWillShow')) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnWillShowAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillHide(value: VoidCallback | undefined): this {
        if (this.checkPriority('onWillHide')) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnWillHideAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<TabContentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookTabContentAttributeModifier(this, value);
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
export class BottomTabBarStyle_serializer {
    public static write(buffer: SerializerBase, value: BottomTabBarStyle): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): BottomTabBarStyle {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return BottomTabBarStyleInternal.fromPtr(ptr)
    }
}
export class SubTabBarStyle_serializer {
    public static write(buffer: SerializerBase, value: SubTabBarStyle): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): SubTabBarStyle {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return SubTabBarStyleInternal.fromPtr(ptr)
    }
}
export class TabBarSymbol_serializer {
    public static write(buffer: SerializerBase, value: TabBarSymbol): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): TabBarSymbol {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return TabBarSymbolInternal.fromPtr(ptr)
    }
}
export class TabBarIconStyle_serializer {
    public static write(buffer: SerializerBase, value: TabBarIconStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSelectedColor  = value.selectedColor
        if (valueHolderForSelectedColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSelectedColorTmpValue  = valueHolderForSelectedColor!
            if (valueHolderForSelectedColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSelectedColorTmpValueForIdx0  = valueHolderForSelectedColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForSelectedColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForSelectedColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSelectedColorTmpValueForIdx1  = valueHolderForSelectedColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForSelectedColorTmpValueForIdx1)
            } else if (valueHolderForSelectedColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForSelectedColorTmpValueForIdx2  = valueHolderForSelectedColorTmpValue as string
                valueSerializer.writeString(valueHolderForSelectedColorTmpValueForIdx2)
            } else if (valueHolderForSelectedColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForSelectedColorTmpValueForIdx3  = valueHolderForSelectedColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForSelectedColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForUnselectedColor  = value.unselectedColor
        if (valueHolderForUnselectedColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUnselectedColorTmpValue  = valueHolderForUnselectedColor!
            if (valueHolderForUnselectedColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx0  = valueHolderForUnselectedColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForUnselectedColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForUnselectedColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx1  = valueHolderForUnselectedColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForUnselectedColorTmpValueForIdx1)
            } else if (valueHolderForUnselectedColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx2  = valueHolderForUnselectedColorTmpValue as string
                valueSerializer.writeString(valueHolderForUnselectedColorTmpValueForIdx2)
            } else if (valueHolderForUnselectedColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx3  = valueHolderForUnselectedColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForUnselectedColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TabBarIconStyle {
        let valueDeserializer : DeserializerBase = buffer
        const selectedColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let selectedColorTmpBuf : ResourceColor | undefined = undefined
        if ((selectedColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const selectedColorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let selectedColorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (selectedColorTmpBufOptUnionSelector == (0).toByte()) {
                selectedColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (selectedColorTmpBufOptUnionSelector == (1).toByte()) {
                selectedColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (selectedColorTmpBufOptUnionSelector == (2).toByte()) {
                selectedColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (selectedColorTmpBufOptUnionSelector == (3).toByte()) {
                selectedColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for selectedColorTmpBufOpt has to be chosen through deserialisation.')
            }
            selectedColorTmpBuf = (selectedColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const selectedColorTmpResult : ResourceColor | undefined = selectedColorTmpBuf
        const unselectedColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let unselectedColorTmpBuf : ResourceColor | undefined = undefined
        if ((unselectedColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const unselectedColorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let unselectedColorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (unselectedColorTmpBufOptUnionSelector == (0).toByte()) {
                unselectedColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (unselectedColorTmpBufOptUnionSelector == (1).toByte()) {
                unselectedColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (unselectedColorTmpBufOptUnionSelector == (2).toByte()) {
                unselectedColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (unselectedColorTmpBufOptUnionSelector == (3).toByte()) {
                unselectedColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for unselectedColorTmpBufOpt has to be chosen through deserialisation.')
            }
            unselectedColorTmpBuf = (unselectedColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const unselectedColorTmpResult : ResourceColor | undefined = unselectedColorTmpBuf
        let value : TabBarIconStyle = ({selectedColor: selectedColorTmpResult, unselectedColor: unselectedColorTmpResult} as TabBarIconStyle)
        return value
    }
}
export class TabBarOptions_serializer {
    public static write(buffer: SerializerBase, value: TabBarOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForIcon  = value.icon
        if (valueHolderForIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIconTmpValue  = valueHolderForIcon!
            if (valueHolderForIconTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForIconTmpValueForIdx0  = valueHolderForIconTmpValue as string
                valueSerializer.writeString(valueHolderForIconTmpValueForIdx0)
            } else if (valueHolderForIconTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForIconTmpValueForIdx1  = valueHolderForIconTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForIconTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForText  = value.text
        if (valueHolderForText !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextTmpValue  = valueHolderForText!
            if (valueHolderForTextTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForTextTmpValueForIdx0  = valueHolderForTextTmpValue as string
                valueSerializer.writeString(valueHolderForTextTmpValueForIdx0)
            } else if (valueHolderForTextTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForTextTmpValueForIdx1  = valueHolderForTextTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForTextTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TabBarOptions {
        let valueDeserializer : DeserializerBase = buffer
        const iconTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let iconTmpBuf : string | arkui_component_units_Resource | undefined = undefined
        if ((iconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const iconTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let iconTmpBufOpt : string | arkui_component_units_Resource | undefined
            if (iconTmpBufOptUnionSelector == (0).toByte()) {
                iconTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (iconTmpBufOptUnionSelector == (1).toByte()) {
                iconTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for iconTmpBufOpt has to be chosen through deserialisation.')
            }
            iconTmpBuf = (iconTmpBufOpt as string | arkui_component_units_Resource)
        }
        const iconTmpResult : string | arkui_component_units_Resource | undefined = iconTmpBuf
        const textTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let textTmpBuf : string | arkui_component_units_Resource | undefined = undefined
        if ((textTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const textTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let textTmpBufOpt : string | arkui_component_units_Resource | undefined
            if (textTmpBufOptUnionSelector == (0).toByte()) {
                textTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (textTmpBufOptUnionSelector == (1).toByte()) {
                textTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for textTmpBufOpt has to be chosen through deserialisation.')
            }
            textTmpBuf = (textTmpBufOpt as string | arkui_component_units_Resource)
        }
        const textTmpResult : string | arkui_component_units_Resource | undefined = textTmpBuf
        let value : TabBarOptions = ({icon: iconTmpResult, text: textTmpResult} as TabBarOptions)
        return value
    }
}
export class BoardStyle_serializer {
    public static write(buffer: SerializerBase, value: BoardStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForBorderRadius  = value.borderRadius
        if (valueHolderForBorderRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderRadiusTmpValue  = valueHolderForBorderRadius!
            if (valueHolderForBorderRadiusTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderRadiusTmpValueForIdx0  = valueHolderForBorderRadiusTmpValue as string
                valueSerializer.writeString(valueHolderForBorderRadiusTmpValueForIdx0)
            } else if (valueHolderForBorderRadiusTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderRadiusTmpValueForIdx1  = valueHolderForBorderRadiusTmpValue as double
                valueSerializer.writeFloat64(valueHolderForBorderRadiusTmpValueForIdx1)
            } else if (valueHolderForBorderRadiusTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBorderRadiusTmpValueForIdx2  = valueHolderForBorderRadiusTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForBorderRadiusTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): BoardStyle {
        let valueDeserializer : DeserializerBase = buffer
        const borderRadiusTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let borderRadiusTmpBuf : Length | undefined = undefined
        if ((borderRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderRadiusTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let borderRadiusTmpBufOpt : string | double | arkui_component_units_Resource | undefined
            if (borderRadiusTmpBufOptUnionSelector == (0).toByte()) {
                borderRadiusTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (borderRadiusTmpBufOptUnionSelector == (1).toByte()) {
                borderRadiusTmpBufOpt = valueDeserializer.readFloat64()
            } else if (borderRadiusTmpBufOptUnionSelector == (2).toByte()) {
                borderRadiusTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for borderRadiusTmpBufOpt has to be chosen through deserialisation.')
            }
            borderRadiusTmpBuf = (borderRadiusTmpBufOpt as string | double | arkui_component_units_Resource)
        }
        const borderRadiusTmpResult : Length | undefined = borderRadiusTmpBuf
        let value : BoardStyle = ({borderRadius: borderRadiusTmpResult} as BoardStyle)
        return value
    }
}
export class SubTabBarIndicatorStyle_serializer {
    public static write(buffer: SerializerBase, value: SubTabBarIndicatorStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForColor  = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue  = valueHolderForColor!
            if (valueHolderForColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForColorTmpValueForIdx0  = valueHolderForColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForColorTmpValueForIdx1  = valueHolderForColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx1)
            } else if (valueHolderForColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForColorTmpValueForIdx2  = valueHolderForColorTmpValue as string
                valueSerializer.writeString(valueHolderForColorTmpValueForIdx2)
            } else if (valueHolderForColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForColorTmpValueForIdx3  = valueHolderForColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeight  = value.height
        if (valueHolderForHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightTmpValue  = valueHolderForHeight!
            if (valueHolderForHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForHeightTmpValueForIdx0  = valueHolderForHeightTmpValue as string
                valueSerializer.writeString(valueHolderForHeightTmpValueForIdx0)
            } else if (valueHolderForHeightTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForHeightTmpValueForIdx1  = valueHolderForHeightTmpValue as double
                valueSerializer.writeFloat64(valueHolderForHeightTmpValueForIdx1)
            } else if (valueHolderForHeightTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForHeightTmpValueForIdx2  = valueHolderForHeightTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForHeightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as string
                valueSerializer.writeString(valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForWidthTmpValueForIdx1  = valueHolderForWidthTmpValue as double
                valueSerializer.writeFloat64(valueHolderForWidthTmpValueForIdx1)
            } else if (valueHolderForWidthTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForWidthTmpValueForIdx2  = valueHolderForWidthTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderRadius  = value.borderRadius
        if (valueHolderForBorderRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderRadiusTmpValue  = valueHolderForBorderRadius!
            if (valueHolderForBorderRadiusTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderRadiusTmpValueForIdx0  = valueHolderForBorderRadiusTmpValue as string
                valueSerializer.writeString(valueHolderForBorderRadiusTmpValueForIdx0)
            } else if (valueHolderForBorderRadiusTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderRadiusTmpValueForIdx1  = valueHolderForBorderRadiusTmpValue as double
                valueSerializer.writeFloat64(valueHolderForBorderRadiusTmpValueForIdx1)
            } else if (valueHolderForBorderRadiusTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBorderRadiusTmpValueForIdx2  = valueHolderForBorderRadiusTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForBorderRadiusTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMarginTop  = value.marginTop
        if (valueHolderForMarginTop !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMarginTopTmpValue  = valueHolderForMarginTop!
            if (valueHolderForMarginTopTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForMarginTopTmpValueForIdx0  = valueHolderForMarginTopTmpValue as string
                valueSerializer.writeString(valueHolderForMarginTopTmpValueForIdx0)
            } else if (valueHolderForMarginTopTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForMarginTopTmpValueForIdx1  = valueHolderForMarginTopTmpValue as double
                valueSerializer.writeFloat64(valueHolderForMarginTopTmpValueForIdx1)
            } else if (valueHolderForMarginTopTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForMarginTopTmpValueForIdx2  = valueHolderForMarginTopTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForMarginTopTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SubTabBarIndicatorStyle {
        let valueDeserializer : DeserializerBase = buffer
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let colorTmpBuf : ResourceColor | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (colorTmpBufOptUnionSelector == (0).toByte()) {
                colorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (colorTmpBufOptUnionSelector == (1).toByte()) {
                colorTmpBufOpt = valueDeserializer.readInt32()
            } else if (colorTmpBufOptUnionSelector == (2).toByte()) {
                colorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (colorTmpBufOptUnionSelector == (3).toByte()) {
                colorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for colorTmpBufOpt has to be chosen through deserialisation.')
            }
            colorTmpBuf = (colorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const colorTmpResult : ResourceColor | undefined = colorTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let heightTmpBuf : Length | undefined = undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBufOpt : string | double | arkui_component_units_Resource | undefined
            if (heightTmpBufOptUnionSelector == (0).toByte()) {
                heightTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (heightTmpBufOptUnionSelector == (1).toByte()) {
                heightTmpBufOpt = valueDeserializer.readFloat64()
            } else if (heightTmpBufOptUnionSelector == (2).toByte()) {
                heightTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for heightTmpBufOpt has to be chosen through deserialisation.')
            }
            heightTmpBuf = (heightTmpBufOpt as string | double | arkui_component_units_Resource)
        }
        const heightTmpResult : Length | undefined = heightTmpBuf
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let widthTmpBuf : Length | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBufOpt : string | double | arkui_component_units_Resource | undefined
            if (widthTmpBufOptUnionSelector == (0).toByte()) {
                widthTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (widthTmpBufOptUnionSelector == (1).toByte()) {
                widthTmpBufOpt = valueDeserializer.readFloat64()
            } else if (widthTmpBufOptUnionSelector == (2).toByte()) {
                widthTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for widthTmpBufOpt has to be chosen through deserialisation.')
            }
            widthTmpBuf = (widthTmpBufOpt as string | double | arkui_component_units_Resource)
        }
        const widthTmpResult : Length | undefined = widthTmpBuf
        const borderRadiusTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let borderRadiusTmpBuf : Length | undefined = undefined
        if ((borderRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderRadiusTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let borderRadiusTmpBufOpt : string | double | arkui_component_units_Resource | undefined
            if (borderRadiusTmpBufOptUnionSelector == (0).toByte()) {
                borderRadiusTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (borderRadiusTmpBufOptUnionSelector == (1).toByte()) {
                borderRadiusTmpBufOpt = valueDeserializer.readFloat64()
            } else if (borderRadiusTmpBufOptUnionSelector == (2).toByte()) {
                borderRadiusTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for borderRadiusTmpBufOpt has to be chosen through deserialisation.')
            }
            borderRadiusTmpBuf = (borderRadiusTmpBufOpt as string | double | arkui_component_units_Resource)
        }
        const borderRadiusTmpResult : Length | undefined = borderRadiusTmpBuf
        const marginTopTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let marginTopTmpBuf : Length | undefined = undefined
        if ((marginTopTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const marginTopTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let marginTopTmpBufOpt : string | double | arkui_component_units_Resource | undefined
            if (marginTopTmpBufOptUnionSelector == (0).toByte()) {
                marginTopTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (marginTopTmpBufOptUnionSelector == (1).toByte()) {
                marginTopTmpBufOpt = valueDeserializer.readFloat64()
            } else if (marginTopTmpBufOptUnionSelector == (2).toByte()) {
                marginTopTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for marginTopTmpBufOpt has to be chosen through deserialisation.')
            }
            marginTopTmpBuf = (marginTopTmpBufOpt as string | double | arkui_component_units_Resource)
        }
        const marginTopTmpResult : Length | undefined = marginTopTmpBuf
        let value : SubTabBarIndicatorStyle = ({color: colorTmpResult, height: heightTmpResult, width: widthTmpResult, borderRadius: borderRadiusTmpResult, marginTop: marginTopTmpResult} as SubTabBarIndicatorStyle)
        return value
    }
}
export class TabBarLabelStyle_serializer {
    public static write(buffer: SerializerBase, value: TabBarLabelStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForOverflow  = value.overflow
        if (valueHolderForOverflow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOverflowTmpValue  = (valueHolderForOverflow as TextOverflow)
            valueSerializer.writeInt32(valueHolderForOverflowTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMaxLines  = value.maxLines
        if (valueHolderForMaxLines !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaxLinesTmpValue  = valueHolderForMaxLines!
            valueSerializer.writeInt32(valueHolderForMaxLinesTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMinFontSize  = value.minFontSize
        if (valueHolderForMinFontSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMinFontSizeTmpValue  = valueHolderForMinFontSize!
            if (valueHolderForMinFontSizeTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForMinFontSizeTmpValueForIdx0  = valueHolderForMinFontSizeTmpValue as double
                valueSerializer.writeFloat64(valueHolderForMinFontSizeTmpValueForIdx0)
            } else if (valueHolderForMinFontSizeTmpValue instanceof arkui_component_units_ResourceStr) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForMinFontSizeTmpValueForIdx1  = valueHolderForMinFontSizeTmpValue as arkui_component_units_ResourceStr
                if (valueHolderForMinFontSizeTmpValueForIdx1 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForMinFontSizeTmpValueForIdx1ForIdx0  = valueHolderForMinFontSizeTmpValueForIdx1 as string
                    valueSerializer.writeString(valueHolderForMinFontSizeTmpValueForIdx1ForIdx0)
                } else if (valueHolderForMinFontSizeTmpValueForIdx1 instanceof arkui_component_units_Resource) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForMinFontSizeTmpValueForIdx1ForIdx1  = valueHolderForMinFontSizeTmpValueForIdx1 as arkui_component_units_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForMinFontSizeTmpValueForIdx1ForIdx1)
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMaxFontSize  = value.maxFontSize
        if (valueHolderForMaxFontSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaxFontSizeTmpValue  = valueHolderForMaxFontSize!
            if (valueHolderForMaxFontSizeTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForMaxFontSizeTmpValueForIdx0  = valueHolderForMaxFontSizeTmpValue as double
                valueSerializer.writeFloat64(valueHolderForMaxFontSizeTmpValueForIdx0)
            } else if (valueHolderForMaxFontSizeTmpValue instanceof arkui_component_units_ResourceStr) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForMaxFontSizeTmpValueForIdx1  = valueHolderForMaxFontSizeTmpValue as arkui_component_units_ResourceStr
                if (valueHolderForMaxFontSizeTmpValueForIdx1 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForMaxFontSizeTmpValueForIdx1ForIdx0  = valueHolderForMaxFontSizeTmpValueForIdx1 as string
                    valueSerializer.writeString(valueHolderForMaxFontSizeTmpValueForIdx1ForIdx0)
                } else if (valueHolderForMaxFontSizeTmpValueForIdx1 instanceof arkui_component_units_Resource) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForMaxFontSizeTmpValueForIdx1ForIdx1  = valueHolderForMaxFontSizeTmpValueForIdx1 as arkui_component_units_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForMaxFontSizeTmpValueForIdx1ForIdx1)
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeightAdaptivePolicy  = value.heightAdaptivePolicy
        if (valueHolderForHeightAdaptivePolicy !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightAdaptivePolicyTmpValue  = (valueHolderForHeightAdaptivePolicy as TextHeightAdaptivePolicy)
            valueSerializer.writeInt32(valueHolderForHeightAdaptivePolicyTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFont  = value.font
        if (valueHolderForFont !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontTmpValue  = valueHolderForFont!
            arkui_component_units_Font_serializer.write(valueSerializer, valueHolderForFontTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSelectedColor  = value.selectedColor
        if (valueHolderForSelectedColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSelectedColorTmpValue  = valueHolderForSelectedColor!
            if (valueHolderForSelectedColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSelectedColorTmpValueForIdx0  = valueHolderForSelectedColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForSelectedColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForSelectedColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSelectedColorTmpValueForIdx1  = valueHolderForSelectedColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForSelectedColorTmpValueForIdx1)
            } else if (valueHolderForSelectedColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForSelectedColorTmpValueForIdx2  = valueHolderForSelectedColorTmpValue as string
                valueSerializer.writeString(valueHolderForSelectedColorTmpValueForIdx2)
            } else if (valueHolderForSelectedColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForSelectedColorTmpValueForIdx3  = valueHolderForSelectedColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForSelectedColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForUnselectedColor  = value.unselectedColor
        if (valueHolderForUnselectedColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUnselectedColorTmpValue  = valueHolderForUnselectedColor!
            if (valueHolderForUnselectedColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx0  = valueHolderForUnselectedColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForUnselectedColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForUnselectedColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx1  = valueHolderForUnselectedColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForUnselectedColorTmpValueForIdx1)
            } else if (valueHolderForUnselectedColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx2  = valueHolderForUnselectedColorTmpValue as string
                valueSerializer.writeString(valueHolderForUnselectedColorTmpValueForIdx2)
            } else if (valueHolderForUnselectedColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForUnselectedColorTmpValueForIdx3  = valueHolderForUnselectedColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForUnselectedColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TabBarLabelStyle {
        let valueDeserializer : DeserializerBase = buffer
        const overflowTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let overflowTmpBuf : TextOverflow | undefined = undefined
        if ((overflowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            overflowTmpBuf = TextOverflow.fromValue(valueDeserializer.readInt32())
        }
        const overflowTmpResult : TextOverflow | undefined = overflowTmpBuf
        const maxLinesTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let maxLinesTmpBuf : int32 | undefined = undefined
        if ((maxLinesTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maxLinesTmpBuf = valueDeserializer.readInt32()
        }
        const maxLinesTmpResult : int32 | undefined = maxLinesTmpBuf
        const minFontSizeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let minFontSizeTmpBuf : double | arkui_component_units_ResourceStr | undefined = undefined
        if ((minFontSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const minFontSizeTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let minFontSizeTmpBufOpt : double | arkui_component_units_ResourceStr | undefined
            if (minFontSizeTmpBufOptUnionSelector == (0).toByte()) {
                minFontSizeTmpBufOpt = valueDeserializer.readFloat64()
            } else if (minFontSizeTmpBufOptUnionSelector == (1).toByte()) {
                const minFontSizeTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let minFontSizeTmpBufOptBufU : string | arkui_component_units_Resource | undefined
                if (minFontSizeTmpBufOptBufUUnionSelector == (0).toByte()) {
                    minFontSizeTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (minFontSizeTmpBufOptBufUUnionSelector == (1).toByte()) {
                    minFontSizeTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for minFontSizeTmpBufOptBufU has to be chosen through deserialisation.')
                }
                minFontSizeTmpBufOpt = (minFontSizeTmpBufOptBufU as string | arkui_component_units_Resource)
            } else {
                throw new Error('One of the branches for minFontSizeTmpBufOpt has to be chosen through deserialisation.')
            }
            minFontSizeTmpBuf = (minFontSizeTmpBufOpt as double | arkui_component_units_ResourceStr)
        }
        const minFontSizeTmpResult : double | arkui_component_units_ResourceStr | undefined = minFontSizeTmpBuf
        const maxFontSizeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let maxFontSizeTmpBuf : double | arkui_component_units_ResourceStr | undefined = undefined
        if ((maxFontSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const maxFontSizeTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let maxFontSizeTmpBufOpt : double | arkui_component_units_ResourceStr | undefined
            if (maxFontSizeTmpBufOptUnionSelector == (0).toByte()) {
                maxFontSizeTmpBufOpt = valueDeserializer.readFloat64()
            } else if (maxFontSizeTmpBufOptUnionSelector == (1).toByte()) {
                const maxFontSizeTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let maxFontSizeTmpBufOptBufU : string | arkui_component_units_Resource | undefined
                if (maxFontSizeTmpBufOptBufUUnionSelector == (0).toByte()) {
                    maxFontSizeTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (maxFontSizeTmpBufOptBufUUnionSelector == (1).toByte()) {
                    maxFontSizeTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for maxFontSizeTmpBufOptBufU has to be chosen through deserialisation.')
                }
                maxFontSizeTmpBufOpt = (maxFontSizeTmpBufOptBufU as string | arkui_component_units_Resource)
            } else {
                throw new Error('One of the branches for maxFontSizeTmpBufOpt has to be chosen through deserialisation.')
            }
            maxFontSizeTmpBuf = (maxFontSizeTmpBufOpt as double | arkui_component_units_ResourceStr)
        }
        const maxFontSizeTmpResult : double | arkui_component_units_ResourceStr | undefined = maxFontSizeTmpBuf
        const heightAdaptivePolicyTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let heightAdaptivePolicyTmpBuf : TextHeightAdaptivePolicy | undefined = undefined
        if ((heightAdaptivePolicyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            heightAdaptivePolicyTmpBuf = TextHeightAdaptivePolicy.fromValue(valueDeserializer.readInt32())
        }
        const heightAdaptivePolicyTmpResult : TextHeightAdaptivePolicy | undefined = heightAdaptivePolicyTmpBuf
        const fontTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontTmpBuf : arkui_component_units_Font | undefined = undefined
        if ((fontTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fontTmpBuf = arkui_component_units_Font_serializer.read(valueDeserializer)
        }
        const fontTmpResult : arkui_component_units_Font | undefined = fontTmpBuf
        const selectedColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let selectedColorTmpBuf : ResourceColor | undefined = undefined
        if ((selectedColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const selectedColorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let selectedColorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (selectedColorTmpBufOptUnionSelector == (0).toByte()) {
                selectedColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (selectedColorTmpBufOptUnionSelector == (1).toByte()) {
                selectedColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (selectedColorTmpBufOptUnionSelector == (2).toByte()) {
                selectedColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (selectedColorTmpBufOptUnionSelector == (3).toByte()) {
                selectedColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for selectedColorTmpBufOpt has to be chosen through deserialisation.')
            }
            selectedColorTmpBuf = (selectedColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const selectedColorTmpResult : ResourceColor | undefined = selectedColorTmpBuf
        const unselectedColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let unselectedColorTmpBuf : ResourceColor | undefined = undefined
        if ((unselectedColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const unselectedColorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let unselectedColorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (unselectedColorTmpBufOptUnionSelector == (0).toByte()) {
                unselectedColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (unselectedColorTmpBufOptUnionSelector == (1).toByte()) {
                unselectedColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (unselectedColorTmpBufOptUnionSelector == (2).toByte()) {
                unselectedColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (unselectedColorTmpBufOptUnionSelector == (3).toByte()) {
                unselectedColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for unselectedColorTmpBufOpt has to be chosen through deserialisation.')
            }
            unselectedColorTmpBuf = (unselectedColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const unselectedColorTmpResult : ResourceColor | undefined = unselectedColorTmpBuf
        let value : TabBarLabelStyle = ({overflow: overflowTmpResult, maxLines: maxLinesTmpResult, minFontSize: minFontSizeTmpResult, maxFontSize: maxFontSizeTmpResult, heightAdaptivePolicy: heightAdaptivePolicyTmpResult, font: fontTmpResult, selectedColor: selectedColorTmpResult, unselectedColor: unselectedColorTmpResult} as TabBarLabelStyle)
        return value
    }
}
