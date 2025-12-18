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

import { Finalizable, RuntimeType, SerializerBase, DeserializerBase, toPeerPtr, KPointer, MaterializedBase, MaterializedBaseTag, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr, resourceFinalizerRegister } from '@koalaui/interop'
import { unsafeCast, int32, int64, float32 } from '@koalaui/common'
import { ArkUIGeneratedNativeModule } from '#components'
import { CallbackTransformer } from './../CallbackTransformer'
import { SelectionOptions_serializer, RectResult_serializer, SelectionOptions, RectResult, ArkCommonMethodPeer, CommonMethod, Callback as arkui_component_common_Callback, ShadowOptions, PixelMap, ClickEvent, HoverEvent, HapticFeedbackMode, ArkCommonMethodComponent, ClickEvent_serializer, ShadowOptions_serializer, HoverEvent_serializer } from './common'
import { LayoutManager_serializer, PreviewText_serializer, TextEditControllerEx, TextEditControllerExInternal, LayoutManager, LayoutManagerInternal, PreviewText, TextDataDetectorConfig_serializer, EditMenuOptions_serializer, TextRange, TextDataDetectorConfig, OnDidChangeCallback, EditMenuOptions, KeyboardAppearance, MenuType, DecorationStyleResult, TextRange_serializer, DecorationStyleResult_serializer, StyledStringChangedListener_serializer, StyledStringController, StyledStringControllerInternal, StyledStringChangedListener } from './textCommon'
import { ArkThemeScopeManager } from '#arktheme'
import { global_resource_Resource_serializer } from './../framework/resource'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { VoidCallback, ResourceColor, Resource as arkui_component_units_Resource, ResourceStr as arkui_component_units_ResourceStr, Font as arkui_component_units_Font, Length, Dimension, Margin, Padding, BorderRadiuses, arkui_component_units_Font_serializer, Padding_serializer, BorderRadiuses_serializer } from './units'
import { CopyOptions, Color as arkui_component_enums_Color, BarState, ResponseType, FontStyle, FontWeight, TextAlign, WordBreak, LineBreakStrategy, ImageSpanAlignment, ImageFit } from './enums'
import { Resource as global_resource_Resource } from 'global.resource'
import { EnterKeyType, SubmitEvent } from './textInput'
import { AttributeModifier, extractors, hookRichEditorAttributeModifier, AttributeUpdater } from '#handwritten'
import { CustomBuilder } from './builder'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { DecorationStyleInterface, DecorationStyleInterface_serializer, StyledString_serializer, StyledString, StyledStringInternal, MutableStyledString_serializer, MutableStyledString, MutableStyledStringInternal } from './styledString'
import { TextBackgroundStyle, TextBackgroundStyle_serializer } from './span'
import { default as image } from '@ohos.multimedia.image'
import { SymbolEffectStrategy, SymbolRenderingStrategy } from './symbolglyph'
import { GestureEvent, GestureEvent_serializer } from './gesture'
import { ColorMetrics as arkui_Graphics_ColorMetrics } from '@arkui.Graphics'
import { RichEditorModifier } from './../RichEditorModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { arkui_Graphics_ColorMetrics_serializer } from './../framework/Graphics'
import { image_PixelMap_serializer } from './../framework/ohos.multimedia.image'
import { CustomNodeBuilder } from './idlize'
export interface CopyEvent {
    preventDefault(): void
}
export class CopyEventInternal implements MaterializedBase,CopyEvent {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, CopyEventInternal.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, CopyEventInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._CopyEvent_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CopyEvent_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): CopyEventInternal {
        return new CopyEventInternal(MaterializedBaseTag.NOP, ptr)
    }
    public preventDefault(): void {
        this.preventDefault_serialize()
        return
    }
    private preventDefault_serialize(): void {
        ArkUIGeneratedNativeModule._CopyEvent_preventDefault(this.peer!.ptr)
    }
}
export interface CutEvent {
    preventDefault(): void
}
export class CutEventInternal implements MaterializedBase,CutEvent {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, CutEventInternal.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, CutEventInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._CutEvent_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CutEvent_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): CutEventInternal {
        return new CutEventInternal(MaterializedBaseTag.NOP, ptr)
    }
    public preventDefault(): void {
        this.preventDefault_serialize()
        return
    }
    private preventDefault_serialize(): void {
        ArkUIGeneratedNativeModule._CutEvent_preventDefault(this.peer!.ptr)
    }
}
export interface PasteEvent {
    preventDefault(): void
}
export class PasteEventInternal implements MaterializedBase,PasteEvent {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, PasteEventInternal.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, PasteEventInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._PasteEvent_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._PasteEvent_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): PasteEventInternal {
        return new PasteEventInternal(MaterializedBaseTag.NOP, ptr)
    }
    public preventDefault(): void {
        this.preventDefault_serialize()
        return
    }
    private preventDefault_serialize(): void {
        ArkUIGeneratedNativeModule._PasteEvent_preventDefault(this.peer!.ptr)
    }
}
export class RichEditorBaseControllerInternal {
    public static fromPtr(ptr: KPointer): RichEditorBaseController {
        return new RichEditorBaseController(MaterializedBaseTag.NOP, ptr)
    }
}
export class RichEditorBaseController implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, RichEditorBaseController.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, RichEditorBaseController.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._RichEditorBaseController_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RichEditorBaseController_getFinalizer()
    }
    public getCaretOffset(): int32 | undefined {
        return this.getCaretOffset_serialize()
    }
    public setCaretOffset(offset: int32): boolean | undefined {
        const offset_casted = offset as (int32)
        return this.setCaretOffset_serialize(offset_casted)
    }
    public closeSelectionMenu(): void {
        this.closeSelectionMenu_serialize()
        return
    }
    public getTypingStyle(): RichEditorTextStyle | undefined {
        return this.getTypingStyle_serialize()
    }
    public setTypingStyle(value: RichEditorTextStyle): void {
        const value_casted = value as (RichEditorTextStyle)
        this.setTypingStyle_serialize(value_casted)
        return
    }
    public setSelection(selectionStart: int32, selectionEnd: int32, options?: SelectionOptions): void {
        const selectionStart_casted = selectionStart as (int32)
        const selectionEnd_casted = selectionEnd as (int32)
        const options_casted = options as (SelectionOptions | undefined)
        this.setSelection_serialize(selectionStart_casted, selectionEnd_casted, options_casted)
        return
    }
    public isEditing(): boolean | undefined {
        return this.isEditing_serialize()
    }
    public stopEditing(): void {
        this.stopEditing_serialize()
        return
    }
    public getLayoutManager(): LayoutManager | undefined {
        return this.getLayoutManager_serialize()
    }
    public getPreviewText(): PreviewText | undefined {
        return this.getPreviewText_serialize()
    }
    public getCaretRect(): RectResult | undefined {
        return this.getCaretRect_serialize()
    }
    private getCaretOffset_serialize(): int32 | undefined {
        const retval  = ArkUIGeneratedNativeModule._RichEditorBaseController_getCaretOffset(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : int32 | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = retvalDeserializer.readInt32()
        }
        const returnResult : int32 | undefined = buffer
        return returnResult
    }
    private setCaretOffset_serialize(offset: int32): boolean | undefined {
        const retval  = ArkUIGeneratedNativeModule._RichEditorBaseController_setCaretOffset(this.peer!.ptr, offset)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : boolean | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = retvalDeserializer.readBoolean()
        }
        const returnResult : boolean | undefined = buffer
        return returnResult
    }
    private closeSelectionMenu_serialize(): void {
        ArkUIGeneratedNativeModule._RichEditorBaseController_closeSelectionMenu(this.peer!.ptr)
    }
    private getTypingStyle_serialize(): RichEditorTextStyle | undefined {
        const retval  = ArkUIGeneratedNativeModule._RichEditorBaseController_getTypingStyle(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : RichEditorTextStyle | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = RichEditorTextStyle_serializer.read(retvalDeserializer)
        }
        const returnResult : RichEditorTextStyle | undefined = buffer
        return returnResult
    }
    private setTypingStyle_serialize(value: RichEditorTextStyle): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        RichEditorTextStyle_serializer.write(thisSerializer, value)
        ArkUIGeneratedNativeModule._RichEditorBaseController_setTypingStyle(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setSelection_serialize(selectionStart: int32, selectionEnd: int32, options?: SelectionOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            SelectionOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorBaseController_setSelection(this.peer!.ptr, selectionStart, selectionEnd, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private isEditing_serialize(): boolean | undefined {
        const retval  = ArkUIGeneratedNativeModule._RichEditorBaseController_isEditing(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : boolean | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = retvalDeserializer.readBoolean()
        }
        const returnResult : boolean | undefined = buffer
        return returnResult
    }
    private stopEditing_serialize(): void {
        ArkUIGeneratedNativeModule._RichEditorBaseController_stopEditing(this.peer!.ptr)
    }
    private getLayoutManager_serialize(): LayoutManager | undefined {
        const retval  = ArkUIGeneratedNativeModule._RichEditorBaseController_getLayoutManager(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : LayoutManager | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = (LayoutManager_serializer.read(retvalDeserializer) as LayoutManager)
        }
        const returnResult : LayoutManager | undefined = buffer
        return returnResult
    }
    private getPreviewText_serialize(): PreviewText | undefined {
        const retval  = ArkUIGeneratedNativeModule._RichEditorBaseController_getPreviewText(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : PreviewText | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = PreviewText_serializer.read(retvalDeserializer)
        }
        const returnResult : PreviewText | undefined = buffer
        return returnResult
    }
    private getCaretRect_serialize(): RectResult | undefined {
        const retval  = ArkUIGeneratedNativeModule._RichEditorBaseController_getCaretRect(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : RectResult | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = RectResult_serializer.read(retvalDeserializer)
        }
        const returnResult : RectResult | undefined = buffer
        return returnResult
    }
}
export class ArkRichEditorPeer extends ArkCommonMethodPeer {
    attributeSet?: RichEditorModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRichEditorPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._RichEditor_construct(peerId, flags)
        const _peer  = new ArkRichEditorPeer(_peerPtr, peerId, 'RichEditor', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRichEditorOptionsAttribute(options: RichEditorOptions | RichEditorStyledStringOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options instanceof RichEditorOptions) {
            thisSerializer.writeInt8((0).toByte())
            const optionsForIdx0  = options as RichEditorOptions
            RichEditorOptions_serializer.write(thisSerializer, optionsForIdx0)
        } else if (options instanceof RichEditorStyledStringOptions) {
            thisSerializer.writeInt8((1).toByte())
            const optionsForIdx1  = options as RichEditorStyledStringOptions
            RichEditorStyledStringOptions_serializer.write(thisSerializer, optionsForIdx1)
        }
        ArkUIGeneratedNativeModule._RichEditorInterface_setRichEditorOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnReadyAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setOnReady(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSelectAttribute(value: arkui_component_common_Callback<RichEditorSelection, void> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setOnSelect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSelectionChangeAttribute(value: arkui_component_common_Callback<RichEditorRange, void> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setOnSelectionChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAboutToIMEInputAttribute(value: arkui_component_common_Callback<RichEditorInsertValue, boolean> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setAboutToIMEInput(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnIMEInputCompleteAttribute(value: arkui_component_common_Callback<RichEditorTextSpanResult, void> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setOnIMEInputComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDidIMEInputAttribute(value: arkui_component_common_Callback<TextRange, void> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setOnDidIMEInput(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAboutToDeleteAttribute(value: arkui_component_common_Callback<RichEditorDeleteValue, boolean> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setAboutToDelete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDeleteCompleteAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setOnDeleteComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCopyOptionsAttribute(value: CopyOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as CopyOptions)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setCopyOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnPasteAttribute(value: PasteEventCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setOnPaste(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableDataDetectorAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setEnableDataDetector(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnablePreviewTextAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setEnablePreviewText(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDataDetectorConfigAttribute(value: TextDataDetectorConfig | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            TextDataDetectorConfig_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setDataDetectorConfig(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCaretColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof arkui_component_enums_Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as arkui_component_enums_Color
                thisSerializer.writeInt32((valueTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setCaretColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedBackgroundColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof arkui_component_enums_Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as arkui_component_enums_Color
                thisSerializer.writeInt32((valueTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setSelectedBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnEditingChangeAttribute(value: arkui_component_common_Callback<boolean, void> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setOnEditingChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnterKeyTypeAttribute(value: EnterKeyType | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as EnterKeyType)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setEnterKeyType(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSubmitAttribute(value: SubmitCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setOnSubmit(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillChangeAttribute(value: arkui_component_common_Callback<RichEditorChangeValue, boolean> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setOnWillChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDidChangeAttribute(value: OnDidChangeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setOnDidChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnCutAttribute(value: arkui_component_common_Callback<CutEvent, void> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setOnCut(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnCopyAttribute(value: arkui_component_common_Callback<CopyEvent, void> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setOnCopy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEditMenuOptionsAttribute(value: EditMenuOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            EditMenuOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setEditMenuOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableKeyboardOnFocusAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setEnableKeyboardOnFocus(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableHapticFeedbackAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setEnableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBarStateAttribute(value: BarState | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as BarState)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setBarState(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxLengthAttribute(value: int32 | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setMaxLength(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxLinesAttribute(value: int32 | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setMaxLines(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setKeyboardAppearanceAttribute(value: KeyboardAppearance | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as KeyboardAppearance)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setKeyboardAppearance(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStopBackPressAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setStopBackPress(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBindSelectionMenuAttribute(spanType: RichEditorSpanType | undefined, content: CustomBuilder | undefined, responseType: ResponseType | RichEditorResponseType | undefined, options?: SelectionMenuOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (spanType !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const spanTypeTmpValue  = (spanType as RichEditorSpanType)
            thisSerializer.writeInt32(spanTypeTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (content !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const contentTmpValue  = content!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(contentTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (responseType !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const responseTypeTmpValue  = responseType!
            if (responseTypeTmpValue instanceof ResponseType) {
                thisSerializer.writeInt8((0).toByte())
                const responseTypeTmpValueForIdx0  = responseTypeTmpValue as ResponseType
                thisSerializer.writeInt32(responseTypeTmpValueForIdx0.valueOf())
            } else if (responseTypeTmpValue instanceof RichEditorResponseType) {
                thisSerializer.writeInt8((1).toByte())
                const responseTypeTmpValueForIdx1  = responseTypeTmpValue as RichEditorResponseType
                thisSerializer.writeInt32(responseTypeTmpValueForIdx1.valueOf())
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            SelectionMenuOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setBindSelectionMenu(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCustomKeyboardAttribute(value: CustomBuilder | undefined, options?: KeyboardOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            KeyboardOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setCustomKeyboard(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPlaceholderAttribute(value: arkui_component_units_ResourceStr | undefined, style?: PlaceholderStyle): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (style !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const styleTmpValue  = style!
            PlaceholderStyle_serializer.write(thisSerializer, styleTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorAttribute_setPlaceholder(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum RichEditorDeleteDirection {
    BACKWARD = 0,
    FORWARD = 1
}
export enum RichEditorSpanType {
    TEXT = 0,
    IMAGE = 1,
    MIXED = 2,
    BUILDER = 3,
    DEFAULT = 4
}
export enum RichEditorResponseType {
    RIGHT_CLICK = 0,
    LONG_PRESS = 1,
    SELECT = 2,
    DEFAULT = 3
}
export interface RichEditorSpanPosition {
    spanIndex: int32;
    spanRange: [ int32, int32 ];
}
export interface RichEditorTextStyle {
    fontColor?: ResourceColor;
    fontSize?: Length | double;
    fontStyle?: FontStyle;
    fontWeight?: int32 | FontWeight | string;
    fontFamily?: arkui_component_units_ResourceStr;
    decoration?: DecorationStyleInterface;
    textShadow?: ShadowOptions | Array<ShadowOptions>;
    letterSpacing?: double | string;
    lineHeight?: double | string | global_resource_Resource;
    halfLeading?: boolean;
    fontFeature?: string;
    textBackgroundStyle?: TextBackgroundStyle;
}
export interface LeadingMarginPlaceholder {
    pixelMap: PixelMap;
    size: [ Dimension, Dimension ];
}
export interface RichEditorParagraphStyle {
    textAlign?: TextAlign;
    leadingMargin?: Dimension | LeadingMarginPlaceholder;
    wordBreak?: WordBreak;
    lineBreakStrategy?: LineBreakStrategy;
    paragraphSpacing?: double;
}
export interface RichEditorTextSpan {
    spanPosition: RichEditorSpanPosition;
    value: string;
    textStyle?: RichEditorTextStyle;
}
export interface RichEditorLayoutStyle {
    margin?: Dimension | Margin;
    borderRadius?: Dimension | BorderRadiuses;
}
export interface RichEditorImageSpanStyle {
    size?: [ Dimension, Dimension ];
    verticalAlign?: ImageSpanAlignment;
    objectFit?: ImageFit;
    layoutStyle?: RichEditorLayoutStyle;
}
export interface RichEditorSymbolSpanStyle {
    fontSize?: double | string | global_resource_Resource;
    fontColor?: Array<ResourceColor>;
    fontWeight?: int32 | FontWeight | string;
    effectStrategy?: SymbolEffectStrategy;
    renderingStrategy?: SymbolRenderingStrategy;
}
export interface RichEditorTextStyleResult {
    fontColor: ResourceColor;
    fontSize: double;
    fontStyle: FontStyle;
    fontWeight: int32;
    fontFamily: string;
    decoration: DecorationStyleResult;
    textShadow?: Array<ShadowOptions>;
    letterSpacing?: double;
    lineHeight?: double;
    halfLeading?: boolean;
    fontFeature?: string;
    textBackgroundStyle?: TextBackgroundStyle;
}
export interface RichEditorParagraphResult {
    style: RichEditorParagraphStyle;
    range: [ int32, int32 ];
}
export interface RichEditorSymbolSpanStyleResult {
    fontSize: double | string | global_resource_Resource;
    fontColor: Array<ResourceColor>;
    fontWeight: int32 | FontWeight | string;
    effectStrategy: SymbolEffectStrategy;
    renderingStrategy: SymbolRenderingStrategy;
}
export interface RichEditorTextSpanResult {
    spanPosition: RichEditorSpanPosition;
    value: string;
    textStyle: RichEditorTextStyleResult;
    offsetInSpan: [ int32, int32 ];
    symbolSpanStyle?: RichEditorSymbolSpanStyle;
    valueResource?: global_resource_Resource;
    paragraphStyle?: RichEditorParagraphStyle;
    previewText?: string;
    urlStyle?: RichEditorUrlStyle;
}
export interface RichEditorImageSpanStyleResult {
    size: [ int32, int32 ];
    verticalAlign: ImageSpanAlignment;
    objectFit: ImageFit;
    layoutStyle?: RichEditorLayoutStyle;
}
export interface RichEditorImageSpanResult {
    spanPosition: RichEditorSpanPosition;
    valuePixelMap?: PixelMap;
    valueResourceStr?: arkui_component_units_ResourceStr;
    imageStyle: RichEditorImageSpanStyleResult;
    offsetInSpan: [ int32, int32 ];
}
export interface RichEditorImageSpan {
    spanPosition: RichEditorSpanPosition;
    value: PixelMap | arkui_component_units_ResourceStr;
    imageStyle?: RichEditorImageSpanStyle;
}
export interface RichEditorRange {
    start?: int32;
    end?: int32;
}
export interface RichEditorGesture {
    onClick?: ((event: ClickEvent) => void);
    onLongPress?: arkui_component_common_Callback<GestureEvent, void>;
    onDoubleClick?: arkui_component_common_Callback<GestureEvent, void>;
}
export interface RichEditorTextSpanOptions {
    offset?: int32;
    style?: RichEditorTextStyle;
    paragraphStyle?: RichEditorParagraphStyle;
    gesture?: RichEditorGesture;
    urlStyle?: RichEditorUrlStyle;
}
export interface KeyboardOptions {
    supportAvoidance?: boolean;
}
export interface RichEditorImageSpanOptions {
    offset?: int32;
    imageStyle?: RichEditorImageSpanStyle;
    gesture?: RichEditorGesture;
    onHover?: OnHoverCallback;
}
export interface RichEditorBuilderSpanOptions {
    offset?: int32;
    dragBackgroundColor?: arkui_Graphics_ColorMetrics;
    isDragShadowNeeded?: boolean;
}
export interface PlaceholderStyle {
    font?: arkui_component_units_Font;
    fontColor?: ResourceColor;
}
export interface RichEditorSpanStyleOptions extends RichEditorRange {
}
export interface RichEditorParagraphStyleOptions extends RichEditorRange {
    style: RichEditorParagraphStyle;
}
export interface RichEditorUpdateTextSpanStyleOptions extends RichEditorSpanStyleOptions {
    textStyle: RichEditorTextStyle;
    urlStyle?: RichEditorUrlStyle;
}
export interface RichEditorUpdateImageSpanStyleOptions extends RichEditorSpanStyleOptions {
    imageStyle: RichEditorImageSpanStyle;
}
export interface RichEditorUpdateSymbolSpanStyleOptions extends RichEditorSpanStyleOptions {
    symbolStyle: RichEditorSymbolSpanStyle;
}
export interface RichEditorSymbolSpanOptions {
    offset?: int32;
    style?: RichEditorSymbolSpanStyle;
}
export interface RichEditorSelection {
    selection: [ int32, int32 ];
    spans: Array<RichEditorTextSpanResult | RichEditorImageSpanResult>;
}
export interface RichEditorInsertValue {
    insertOffset: int32;
    insertValue: string;
    previewText?: string;
}
export interface RichEditorDeleteValue {
    offset: int32;
    direction: RichEditorDeleteDirection;
    length: int32;
    richEditorDeleteSpans: Array<RichEditorTextSpanResult | RichEditorImageSpanResult>;
}
export interface RichEditorChangeValue {
    rangeBefore: TextRange;
    replacedSpans: Array<RichEditorTextSpanResult>;
    replacedImageSpans: Array<RichEditorImageSpanResult>;
    replacedSymbolSpans: Array<RichEditorTextSpanResult>;
}
export interface RichEditorOptions {
    controller: RichEditorController;
}
export interface RichEditorStyledStringOptions {
    controller: RichEditorStyledStringController;
}
export interface SelectionMenuOptions {
    onAppear?: MenuOnAppearCallback;
    onDisappear?: VoidCallback;
    menuType?: MenuType;
    onMenuShow?: MenuCallback;
    onMenuHide?: MenuCallback;
    previewMenuOptions?: RichEditorPreviewMenuOptions;
}
export interface RichEditorPreviewMenuOptions {
    hapticFeedbackMode?: HapticFeedbackMode;
}
export type RichEditorSpan = RichEditorImageSpanResult | RichEditorTextSpanResult;
export interface RichEditorAttribute extends CommonMethod {
    setRichEditorOptions(options: RichEditorOptions | RichEditorStyledStringOptions): this {
        throw new Error('Unimplemented method setRichEditorOptions')
    }
    onReady(value: VoidCallback | undefined): this {
        throw new Error('Unimplemented method onReady')
    }
    onSelect(value: arkui_component_common_Callback<RichEditorSelection, void> | undefined): this {
        throw new Error('Unimplemented method onSelect')
    }
    onSelectionChange(value: arkui_component_common_Callback<RichEditorRange, void> | undefined): this {
        throw new Error('Unimplemented method onSelectionChange')
    }
    aboutToIMEInput(value: arkui_component_common_Callback<RichEditorInsertValue, boolean> | undefined): this {
        throw new Error('Unimplemented method aboutToIMEInput')
    }
    onIMEInputComplete(value: arkui_component_common_Callback<RichEditorTextSpanResult, void> | undefined): this {
        throw new Error('Unimplemented method onIMEInputComplete')
    }
    onDidIMEInput(value: arkui_component_common_Callback<TextRange, void> | undefined): this {
        throw new Error('Unimplemented method onDidIMEInput')
    }
    aboutToDelete(value: arkui_component_common_Callback<RichEditorDeleteValue, boolean> | undefined): this {
        throw new Error('Unimplemented method aboutToDelete')
    }
    onDeleteComplete(value: VoidCallback | undefined): this {
        throw new Error('Unimplemented method onDeleteComplete')
    }
    copyOptions(value: CopyOptions | undefined): this {
        throw new Error('Unimplemented method copyOptions')
    }
    onPaste(value: PasteEventCallback | undefined): this {
        throw new Error('Unimplemented method onPaste')
    }
    enableDataDetector(value: boolean | undefined): this {
        throw new Error('Unimplemented method enableDataDetector')
    }
    enablePreviewText(value: boolean | undefined): this {
        throw new Error('Unimplemented method enablePreviewText')
    }
    dataDetectorConfig(value: TextDataDetectorConfig | undefined): this {
        throw new Error('Unimplemented method dataDetectorConfig')
    }
    caretColor(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method caretColor')
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method selectedBackgroundColor')
    }
    onEditingChange(value: arkui_component_common_Callback<boolean, void> | undefined): this {
        throw new Error('Unimplemented method onEditingChange')
    }
    enterKeyType(value: EnterKeyType | undefined): this {
        throw new Error('Unimplemented method enterKeyType')
    }
    onSubmit(value: SubmitCallback | undefined): this {
        throw new Error('Unimplemented method onSubmit')
    }
    onWillChange(value: arkui_component_common_Callback<RichEditorChangeValue, boolean> | undefined): this {
        throw new Error('Unimplemented method onWillChange')
    }
    onDidChange(value: OnDidChangeCallback | undefined): this {
        throw new Error('Unimplemented method onDidChange')
    }
    onCut(value: arkui_component_common_Callback<CutEvent, void> | undefined): this {
        throw new Error('Unimplemented method onCut')
    }
    onCopy(value: arkui_component_common_Callback<CopyEvent, void> | undefined): this {
        throw new Error('Unimplemented method onCopy')
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        throw new Error('Unimplemented method editMenuOptions')
    }
    enableKeyboardOnFocus(value: boolean | undefined): this {
        throw new Error('Unimplemented method enableKeyboardOnFocus')
    }
    enableHapticFeedback(value: boolean | undefined): this {
        throw new Error('Unimplemented method enableHapticFeedback')
    }
    barState(value: BarState | undefined): this {
        throw new Error('Unimplemented method barState')
    }
    maxLength(value: int32 | undefined): this {
        throw new Error('Unimplemented method maxLength')
    }
    maxLines(value: int32 | undefined): this {
        throw new Error('Unimplemented method maxLines')
    }
    keyboardAppearance(value: KeyboardAppearance | undefined): this {
        throw new Error('Unimplemented method keyboardAppearance')
    }
    stopBackPress(value: boolean | undefined): this {
        throw new Error('Unimplemented method stopBackPress')
    }
    bindSelectionMenu(spanType: RichEditorSpanType | undefined, content: CustomBuilder | undefined, responseType: ResponseType | RichEditorResponseType | undefined, options?: SelectionMenuOptions): this {
        throw new Error('Unimplemented method bindSelectionMenu')
    }
    customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this {
        throw new Error('Unimplemented method customKeyboard')
    }
    placeholder(value: arkui_component_units_ResourceStr | undefined, style?: PlaceholderStyle): this {
        throw new Error('Unimplemented method placeholder')
    }
    attributeModifier(value: AttributeModifier<RichEditorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}
export interface RichEditorUrlStyle {
    url?: arkui_component_units_ResourceStr;
}
export type SubmitCallback = (enterKey: EnterKeyType, event: SubmitEvent) => void;
export type MenuOnAppearCallback = (start: int32, end: int32) => void;
export type MenuCallback = (start: int32, end: int32) => void;
export type PasteEventCallback = (event?: PasteEvent) => void;
export type OnHoverCallback = (status: boolean, event: HoverEvent) => void;

export class ArkRichEditorComponent extends ArkCommonMethodComponent implements RichEditorAttribute {
    getPeer(): ArkRichEditorPeer {
        return (this.peer as ArkRichEditorPeer)
    }
    public setRichEditorOptions(options: RichEditorOptions | RichEditorStyledStringOptions): this {
        if (this.checkPriority('setRichEditorOptions')) {
            const options_casted = options as (RichEditorOptions | RichEditorStyledStringOptions)
            this.getPeer()?.setRichEditorOptionsAttribute(options_casted)
            this.applyOptionsFinish('RichEditorAttribute');
            return this
        }
        return this
    }
    public onReady(value: VoidCallback | undefined): this {
        if (this.checkPriority('onReady')) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnReadyAttribute(value_casted)
            return this
        }
        return this
    }
    public onSelect(value: arkui_component_common_Callback<RichEditorSelection, void> | undefined): this {
        if (this.checkPriority('onSelect')) {
            const value_casted = value as (arkui_component_common_Callback<RichEditorSelection, void> | undefined)
            this.getPeer()?.setOnSelectAttribute(value_casted)
            return this
        }
        return this
    }
    public onSelectionChange(value: arkui_component_common_Callback<RichEditorRange, void> | undefined): this {
        if (this.checkPriority('onSelectionChange')) {
            const value_casted = value as (arkui_component_common_Callback<RichEditorRange, void> | undefined)
            this.getPeer()?.setOnSelectionChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public aboutToIMEInput(value: arkui_component_common_Callback<RichEditorInsertValue, boolean> | undefined): this {
        if (this.checkPriority('aboutToIMEInput')) {
            const value_casted = value as (arkui_component_common_Callback<RichEditorInsertValue, boolean> | undefined)
            this.getPeer()?.setAboutToIMEInputAttribute(value_casted)
            return this
        }
        return this
    }
    public onIMEInputComplete(value: arkui_component_common_Callback<RichEditorTextSpanResult, void> | undefined): this {
        if (this.checkPriority('onIMEInputComplete')) {
            const value_casted = value as (arkui_component_common_Callback<RichEditorTextSpanResult, void> | undefined)
            this.getPeer()?.setOnIMEInputCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    public onDidIMEInput(value: arkui_component_common_Callback<TextRange, void> | undefined): this {
        if (this.checkPriority('onDidIMEInput')) {
            const value_casted = value as (arkui_component_common_Callback<TextRange, void> | undefined)
            this.getPeer()?.setOnDidIMEInputAttribute(value_casted)
            return this
        }
        return this
    }
    public aboutToDelete(value: arkui_component_common_Callback<RichEditorDeleteValue, boolean> | undefined): this {
        if (this.checkPriority('aboutToDelete')) {
            const value_casted = value as (arkui_component_common_Callback<RichEditorDeleteValue, boolean> | undefined)
            this.getPeer()?.setAboutToDeleteAttribute(value_casted)
            return this
        }
        return this
    }
    public onDeleteComplete(value: VoidCallback | undefined): this {
        if (this.checkPriority('onDeleteComplete')) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnDeleteCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    public copyOptions(value: CopyOptions | undefined): this {
        if (this.checkPriority('copyOptions')) {
            const value_casted = value as (CopyOptions | undefined)
            this.getPeer()?.setCopyOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public onPaste(value: PasteEventCallback | undefined): this {
        if (this.checkPriority('onPaste')) {
            const value_casted = value as (PasteEventCallback | undefined)
            this.getPeer()?.setOnPasteAttribute(value_casted)
            return this
        }
        return this
    }
    public enableDataDetector(value: boolean | undefined): this {
        if (this.checkPriority('enableDataDetector')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableDataDetectorAttribute(value_casted)
            return this
        }
        return this
    }
    public enablePreviewText(value: boolean | undefined): this {
        if (this.checkPriority('enablePreviewText')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnablePreviewTextAttribute(value_casted)
            return this
        }
        return this
    }
    public dataDetectorConfig(value: TextDataDetectorConfig | undefined): this {
        if (this.checkPriority('dataDetectorConfig')) {
            const value_casted = value as (TextDataDetectorConfig | undefined)
            this.getPeer()?.setDataDetectorConfigAttribute(value_casted)
            return this
        }
        return this
    }
    public caretColor(value: ResourceColor | undefined): this {
        if (this.checkPriority('caretColor')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setCaretColorAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedBackgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority('selectedBackgroundColor')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setSelectedBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    public onEditingChange(value: arkui_component_common_Callback<boolean, void> | undefined): this {
        if (this.checkPriority('onEditingChange')) {
            const value_casted = value as (arkui_component_common_Callback<boolean, void> | undefined)
            this.getPeer()?.setOnEditingChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public enterKeyType(value: EnterKeyType | undefined): this {
        if (this.checkPriority('enterKeyType')) {
            const value_casted = value as (EnterKeyType | undefined)
            this.getPeer()?.setEnterKeyTypeAttribute(value_casted)
            return this
        }
        return this
    }
    public onSubmit(value: SubmitCallback | undefined): this {
        if (this.checkPriority('onSubmit')) {
            const value_casted = value as (SubmitCallback | undefined)
            this.getPeer()?.setOnSubmitAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillChange(value: arkui_component_common_Callback<RichEditorChangeValue, boolean> | undefined): this {
        if (this.checkPriority('onWillChange')) {
            const value_casted = value as (arkui_component_common_Callback<RichEditorChangeValue, boolean> | undefined)
            this.getPeer()?.setOnWillChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onDidChange(value: OnDidChangeCallback | undefined): this {
        if (this.checkPriority('onDidChange')) {
            const value_casted = value as (OnDidChangeCallback | undefined)
            this.getPeer()?.setOnDidChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onCut(value: arkui_component_common_Callback<CutEvent, void> | undefined): this {
        if (this.checkPriority('onCut')) {
            const value_casted = value as (arkui_component_common_Callback<CutEvent, void> | undefined)
            this.getPeer()?.setOnCutAttribute(value_casted)
            return this
        }
        return this
    }
    public onCopy(value: arkui_component_common_Callback<CopyEvent, void> | undefined): this {
        if (this.checkPriority('onCopy')) {
            const value_casted = value as (arkui_component_common_Callback<CopyEvent, void> | undefined)
            this.getPeer()?.setOnCopyAttribute(value_casted)
            return this
        }
        return this
    }
    public editMenuOptions(value: EditMenuOptions | undefined): this {
        if (this.checkPriority('editMenuOptions')) {
            const value_casted = value as (EditMenuOptions | undefined)
            this.getPeer()?.setEditMenuOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public enableKeyboardOnFocus(value: boolean | undefined): this {
        if (this.checkPriority('enableKeyboardOnFocus')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableKeyboardOnFocusAttribute(value_casted)
            return this
        }
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        if (this.checkPriority('enableHapticFeedback')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableHapticFeedbackAttribute(value_casted)
            return this
        }
        return this
    }
    public barState(value: BarState | undefined): this {
        if (this.checkPriority('barState')) {
            const value_casted = value as (BarState | undefined)
            this.getPeer()?.setBarStateAttribute(value_casted)
            return this
        }
        return this
    }
    public maxLength(value: int32 | undefined): this {
        if (this.checkPriority('maxLength')) {
            const value_casted = value as (int32 | undefined)
            this.getPeer()?.setMaxLengthAttribute(value_casted)
            return this
        }
        return this
    }
    public maxLines(value: int32 | undefined): this {
        if (this.checkPriority('maxLines')) {
            const value_casted = value as (int32 | undefined)
            this.getPeer()?.setMaxLinesAttribute(value_casted)
            return this
        }
        return this
    }
    public keyboardAppearance(value: KeyboardAppearance | undefined): this {
        if (this.checkPriority('keyboardAppearance')) {
            const value_casted = value as (KeyboardAppearance | undefined)
            this.getPeer()?.setKeyboardAppearanceAttribute(value_casted)
            return this
        }
        return this
    }
    public stopBackPress(value: boolean | undefined): this {
        if (this.checkPriority('stopBackPress')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setStopBackPressAttribute(value_casted)
            return this
        }
        return this
    }
    public bindSelectionMenu(spanType: RichEditorSpanType | undefined, content: CustomBuilder | undefined, responseType: ResponseType | RichEditorResponseType | undefined, options?: SelectionMenuOptions): this {
        if (this.checkPriority('bindSelectionMenu')) {
            const spanType_casted = spanType as (RichEditorSpanType | undefined)
            const content_casted = content as (CustomBuilder | undefined)
            const responseType_casted = responseType as (ResponseType | RichEditorResponseType | undefined)
            const options_casted = options as (SelectionMenuOptions | undefined)
            this.getPeer()?.setBindSelectionMenuAttribute(spanType_casted, content_casted, responseType_casted, options_casted)
            return this
        }
        return this
    }
    public customKeyboard(value: CustomBuilder | undefined, options?: KeyboardOptions): this {
        if (this.checkPriority('customKeyboard')) {
            const value_casted = value as (CustomBuilder | undefined)
            const options_casted = options as (KeyboardOptions | undefined)
            this.getPeer()?.setCustomKeyboardAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    public placeholder(value: arkui_component_units_ResourceStr | undefined, style?: PlaceholderStyle): this {
        if (this.checkPriority('placeholder')) {
            const value_casted = value as (arkui_component_units_ResourceStr | undefined)
            const style_casted = style as (PlaceholderStyle | undefined)
            this.getPeer()?.setPlaceholderAttribute(value_casted, style_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RichEditorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookRichEditorAttributeModifier(this, value);
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
export function RichEditorImpl(
    @memo @memo_skip
    style: ((attributes: RichEditorAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkRichEditorComponent>((): ArkRichEditorComponent => {
        return new ArkRichEditorComponent()
    })
    NodeAttach<ArkRichEditorPeer>((): ArkRichEditorPeer => ArkRichEditorPeer.create(receiver), (_: ArkRichEditorPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class CopyEvent_serializer {
    public static write(buffer: SerializerBase, value: CopyEvent): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): CopyEvent {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return CopyEventInternal.fromPtr(ptr)
    }
}
export class CutEvent_serializer {
    public static write(buffer: SerializerBase, value: CutEvent): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): CutEvent {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return CutEventInternal.fromPtr(ptr)
    }
}
export class PasteEvent_serializer {
    public static write(buffer: SerializerBase, value: PasteEvent): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): PasteEvent {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return PasteEventInternal.fromPtr(ptr)
    }
}
export class RichEditorBaseController_serializer {
    public static write(buffer: SerializerBase, value: RichEditorBaseController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): RichEditorBaseController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return RichEditorBaseControllerInternal.fromPtr(ptr)
    }
}
export class RichEditorController_serializer {
    public static write(buffer: SerializerBase, value: RichEditorController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): RichEditorController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return RichEditorControllerInternal.fromPtr(ptr)
    }
}
export class RichEditorOptions_serializer {
    public static write(buffer: SerializerBase, value: RichEditorOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForController  = value.controller
        RichEditorController_serializer.write(valueSerializer, valueHolderForController)
    }
    public static read(buffer: DeserializerBase): RichEditorOptions {
        let valueDeserializer : DeserializerBase = buffer
        const controllerTmpResult : RichEditorController = (RichEditorController_serializer.read(valueDeserializer) as RichEditorController)
        let value : RichEditorOptions = ({controller: controllerTmpResult} as RichEditorOptions)
        return value
    }
}
export class RichEditorStyledStringController_serializer {
    public static write(buffer: SerializerBase, value: RichEditorStyledStringController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): RichEditorStyledStringController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return RichEditorStyledStringControllerInternal.fromPtr(ptr)
    }
}
export class RichEditorStyledStringOptions_serializer {
    public static write(buffer: SerializerBase, value: RichEditorStyledStringOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForController  = value.controller
        RichEditorStyledStringController_serializer.write(valueSerializer, valueHolderForController)
    }
    public static read(buffer: DeserializerBase): RichEditorStyledStringOptions {
        let valueDeserializer : DeserializerBase = buffer
        const controllerTmpResult : RichEditorStyledStringController = (RichEditorStyledStringController_serializer.read(valueDeserializer) as RichEditorStyledStringController)
        let value : RichEditorStyledStringOptions = ({controller: controllerTmpResult} as RichEditorStyledStringOptions)
        return value
    }
}
export class KeyboardOptions_serializer {
    public static write(buffer: SerializerBase, value: KeyboardOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSupportAvoidance  = value.supportAvoidance
        if (valueHolderForSupportAvoidance !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSupportAvoidanceTmpValue  = valueHolderForSupportAvoidance!
            valueSerializer.writeBoolean(valueHolderForSupportAvoidanceTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): KeyboardOptions {
        let valueDeserializer : DeserializerBase = buffer
        const supportAvoidanceTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let supportAvoidanceTmpBuf : boolean | undefined = undefined
        if ((supportAvoidanceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            supportAvoidanceTmpBuf = valueDeserializer.readBoolean()
        }
        const supportAvoidanceTmpResult : boolean | undefined = supportAvoidanceTmpBuf
        let value : KeyboardOptions = ({supportAvoidance: supportAvoidanceTmpResult} as KeyboardOptions)
        return value
    }
}
export class RichEditorDeleteValue_serializer {
    public static write(buffer: SerializerBase, value: RichEditorDeleteValue): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForOffset  = value.offset
        valueSerializer.writeInt32(valueHolderForOffset)
        const valueHolderForDirection  = value.direction
        valueSerializer.writeInt32(valueHolderForDirection.valueOf())
        const valueHolderForLength  = value.length
        valueSerializer.writeInt32(valueHolderForLength)
        const valueHolderForRichEditorDeleteSpans  = value.richEditorDeleteSpans
        valueSerializer.writeInt32((valueHolderForRichEditorDeleteSpans.length).toInt())
        for (let valueHolderForRichEditorDeleteSpansCounterI = 0; valueHolderForRichEditorDeleteSpansCounterI < valueHolderForRichEditorDeleteSpans.length; valueHolderForRichEditorDeleteSpansCounterI++) {
            const valueHolderForRichEditorDeleteSpansTmpElement : RichEditorTextSpanResult | RichEditorImageSpanResult = valueHolderForRichEditorDeleteSpans[valueHolderForRichEditorDeleteSpansCounterI]
            if (valueHolderForRichEditorDeleteSpansTmpElement instanceof RichEditorTextSpanResult) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForRichEditorDeleteSpansTmpElementForIdx0  = valueHolderForRichEditorDeleteSpansTmpElement as RichEditorTextSpanResult
                RichEditorTextSpanResult_serializer.write(valueSerializer, valueHolderForRichEditorDeleteSpansTmpElementForIdx0)
            } else if (valueHolderForRichEditorDeleteSpansTmpElement instanceof RichEditorImageSpanResult) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForRichEditorDeleteSpansTmpElementForIdx1  = valueHolderForRichEditorDeleteSpansTmpElement as RichEditorImageSpanResult
                RichEditorImageSpanResult_serializer.write(valueSerializer, valueHolderForRichEditorDeleteSpansTmpElementForIdx1)
            }
        }
    }
    public static read(buffer: DeserializerBase): RichEditorDeleteValue {
        let valueDeserializer : DeserializerBase = buffer
        const offsetTmpResult : int32 = valueDeserializer.readInt32()
        const directionTmpResult : RichEditorDeleteDirection = RichEditorDeleteDirection.fromValue(valueDeserializer.readInt32())
        const lengthTmpResult : int32 = valueDeserializer.readInt32()
        const richEditorDeleteSpansTmpBufLength : int32 = valueDeserializer.readInt32()
        let richEditorDeleteSpansTmpBuf : Array<RichEditorTextSpanResult | RichEditorImageSpanResult> = new Array<RichEditorTextSpanResult | RichEditorImageSpanResult>(richEditorDeleteSpansTmpBufLength)
        for (let richEditorDeleteSpansTmpBufBufCounterI = 0; richEditorDeleteSpansTmpBufBufCounterI < richEditorDeleteSpansTmpBufLength; richEditorDeleteSpansTmpBufBufCounterI++) {
            const richEditorDeleteSpansTmpBufTempBufUnionSelector : int32 = valueDeserializer.readInt8()
            let richEditorDeleteSpansTmpBufTempBuf : RichEditorTextSpanResult | RichEditorImageSpanResult | undefined
            if (richEditorDeleteSpansTmpBufTempBufUnionSelector == (0).toByte()) {
                richEditorDeleteSpansTmpBufTempBuf = RichEditorTextSpanResult_serializer.read(valueDeserializer)
            } else if (richEditorDeleteSpansTmpBufTempBufUnionSelector == (1).toByte()) {
                richEditorDeleteSpansTmpBufTempBuf = RichEditorImageSpanResult_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for richEditorDeleteSpansTmpBufTempBuf has to be chosen through deserialisation.')
            }
            richEditorDeleteSpansTmpBuf[richEditorDeleteSpansTmpBufBufCounterI] = (richEditorDeleteSpansTmpBufTempBuf as RichEditorTextSpanResult | RichEditorImageSpanResult)
        }
        const richEditorDeleteSpansTmpResult : Array<RichEditorTextSpanResult | RichEditorImageSpanResult> = richEditorDeleteSpansTmpBuf
        let value : RichEditorDeleteValue = ({offset: offsetTmpResult, direction: directionTmpResult, length: lengthTmpResult, richEditorDeleteSpans: richEditorDeleteSpansTmpResult} as RichEditorDeleteValue)
        return value
    }
}
export class RichEditorGesture_serializer {
    public static write(buffer: SerializerBase, value: RichEditorGesture): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForOnClick  = value.onClick
        if (valueHolderForOnClick !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnClickTmpValue  = valueHolderForOnClick!
            valueSerializer.holdAndWriteCallback(valueHolderForOnClickTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnLongPress  = value.onLongPress
        if (valueHolderForOnLongPress !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnLongPressTmpValue  = valueHolderForOnLongPress!
            valueSerializer.holdAndWriteCallback(valueHolderForOnLongPressTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnDoubleClick  = value.onDoubleClick
        if (valueHolderForOnDoubleClick !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnDoubleClickTmpValue  = valueHolderForOnDoubleClick!
            valueSerializer.holdAndWriteCallback(valueHolderForOnDoubleClickTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorGesture {
        let valueDeserializer : DeserializerBase = buffer
        const onClickTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onClickTmpBuf : ((event: ClickEvent) => void) | undefined = undefined
        if ((onClickTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onClickTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onClickTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onClickTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onClickTmpBufOptClosure  = (event: ClickEvent):void => {
                const onClickTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onClickTmpBufOptBufArgsSerializer.writeInt32(onClickTmpBufOptBufResource.resourceId);
                onClickTmpBufOptBufArgsSerializer.writePointer(onClickTmpBufOptBufCall);
                onClickTmpBufOptBufArgsSerializer.writePointer(onClickTmpBufOptBufCallSync);
                ClickEvent_serializer.write(onClickTmpBufOptBufArgsSerializer, event);
                InteropNativeModule._CallCallbackSync(10, -972351187, onClickTmpBufOptBufArgsSerializer.asBuffer(), onClickTmpBufOptBufArgsSerializer.length());
                onClickTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onClickTmpBufOptClosure, onClickTmpBufOptBufResource)
            onClickTmpBuf = onClickTmpBufOptClosure
        }
        const onClickTmpResult : ((event: ClickEvent) => void) | undefined = onClickTmpBuf
        const onLongPressTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onLongPressTmpBuf : arkui_component_common_Callback<GestureEvent, void> | undefined = undefined
        if ((onLongPressTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onLongPressTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onLongPressTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onLongPressTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onLongPressTmpBufOptClosure  = (data: GestureEvent):void => {
                const onLongPressTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onLongPressTmpBufOptBufArgsSerializer.writeInt32(onLongPressTmpBufOptBufResource.resourceId);
                onLongPressTmpBufOptBufArgsSerializer.writePointer(onLongPressTmpBufOptBufCall);
                onLongPressTmpBufOptBufArgsSerializer.writePointer(onLongPressTmpBufOptBufCallSync);
                GestureEvent_serializer.write(onLongPressTmpBufOptBufArgsSerializer, data);
                InteropNativeModule._CallCallbackSync(10, 1662060708, onLongPressTmpBufOptBufArgsSerializer.asBuffer(), onLongPressTmpBufOptBufArgsSerializer.length());
                onLongPressTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onLongPressTmpBufOptClosure, onLongPressTmpBufOptBufResource)
            onLongPressTmpBuf = onLongPressTmpBufOptClosure
        }
        const onLongPressTmpResult : arkui_component_common_Callback<GestureEvent, void> | undefined = onLongPressTmpBuf
        const onDoubleClickTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onDoubleClickTmpBuf : arkui_component_common_Callback<GestureEvent, void> | undefined = undefined
        if ((onDoubleClickTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDoubleClickTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDoubleClickTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onDoubleClickTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onDoubleClickTmpBufOptClosure  = (data: GestureEvent):void => {
                const onDoubleClickTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDoubleClickTmpBufOptBufArgsSerializer.writeInt32(onDoubleClickTmpBufOptBufResource.resourceId);
                onDoubleClickTmpBufOptBufArgsSerializer.writePointer(onDoubleClickTmpBufOptBufCall);
                onDoubleClickTmpBufOptBufArgsSerializer.writePointer(onDoubleClickTmpBufOptBufCallSync);
                GestureEvent_serializer.write(onDoubleClickTmpBufOptBufArgsSerializer, data);
                InteropNativeModule._CallCallbackSync(10, 1662060708, onDoubleClickTmpBufOptBufArgsSerializer.asBuffer(), onDoubleClickTmpBufOptBufArgsSerializer.length());
                onDoubleClickTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onDoubleClickTmpBufOptClosure, onDoubleClickTmpBufOptBufResource)
            onDoubleClickTmpBuf = onDoubleClickTmpBufOptClosure
        }
        const onDoubleClickTmpResult : arkui_component_common_Callback<GestureEvent, void> | undefined = onDoubleClickTmpBuf
        let value : RichEditorGesture = ({onClick: onClickTmpResult, onLongPress: onLongPressTmpResult, onDoubleClick: onDoubleClickTmpResult} as RichEditorGesture)
        return value
    }
}
export class RichEditorInsertValue_serializer {
    public static write(buffer: SerializerBase, value: RichEditorInsertValue): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForInsertOffset  = value.insertOffset
        valueSerializer.writeInt32(valueHolderForInsertOffset)
        const valueHolderForInsertValue  = value.insertValue
        valueSerializer.writeString(valueHolderForInsertValue)
        const valueHolderForPreviewText  = value.previewText
        if (valueHolderForPreviewText !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPreviewTextTmpValue  = valueHolderForPreviewText!
            valueSerializer.writeString(valueHolderForPreviewTextTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorInsertValue {
        let valueDeserializer : DeserializerBase = buffer
        const insertOffsetTmpResult : int32 = valueDeserializer.readInt32()
        const insertValueTmpResult : string = (valueDeserializer.readString() as string)
        const previewTextTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let previewTextTmpBuf : string | undefined = undefined
        if ((previewTextTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            previewTextTmpBuf = (valueDeserializer.readString() as string)
        }
        const previewTextTmpResult : string | undefined = previewTextTmpBuf
        let value : RichEditorInsertValue = ({insertOffset: insertOffsetTmpResult, insertValue: insertValueTmpResult, previewText: previewTextTmpResult} as RichEditorInsertValue)
        return value
    }
}
export class RichEditorPreviewMenuOptions_serializer {
    public static write(buffer: SerializerBase, value: RichEditorPreviewMenuOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForHapticFeedbackMode  = value.hapticFeedbackMode
        if (valueHolderForHapticFeedbackMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHapticFeedbackModeTmpValue  = (valueHolderForHapticFeedbackMode as HapticFeedbackMode)
            valueSerializer.writeInt32(valueHolderForHapticFeedbackModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorPreviewMenuOptions {
        let valueDeserializer : DeserializerBase = buffer
        const hapticFeedbackModeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let hapticFeedbackModeTmpBuf : HapticFeedbackMode | undefined = undefined
        if ((hapticFeedbackModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            hapticFeedbackModeTmpBuf = HapticFeedbackMode.fromValue(valueDeserializer.readInt32())
        }
        const hapticFeedbackModeTmpResult : HapticFeedbackMode | undefined = hapticFeedbackModeTmpBuf
        let value : RichEditorPreviewMenuOptions = ({hapticFeedbackMode: hapticFeedbackModeTmpResult} as RichEditorPreviewMenuOptions)
        return value
    }
}
export class RichEditorRange_serializer {
    public static write(buffer: SerializerBase, value: RichEditorRange): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStart  = value.start
        if (valueHolderForStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartTmpValue  = valueHolderForStart!
            valueSerializer.writeInt32(valueHolderForStartTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnd  = value.end
        if (valueHolderForEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndTmpValue  = valueHolderForEnd!
            valueSerializer.writeInt32(valueHolderForEndTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorRange {
        let valueDeserializer : DeserializerBase = buffer
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let startTmpBuf : int32 | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startTmpBuf = valueDeserializer.readInt32()
        }
        const startTmpResult : int32 | undefined = startTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let endTmpBuf : int32 | undefined = undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endTmpBuf = valueDeserializer.readInt32()
        }
        const endTmpResult : int32 | undefined = endTmpBuf
        let value : RichEditorRange = ({start: startTmpResult, end: endTmpResult} as RichEditorRange)
        return value
    }
}
export class RichEditorSelection_serializer {
    public static write(buffer: SerializerBase, value: RichEditorSelection): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSelection  = value.selection
        const valueHolderForSelection_0  = valueHolderForSelection[0]
        valueSerializer.writeInt32(valueHolderForSelection_0)
        const valueHolderForSelection_1  = valueHolderForSelection[1]
        valueSerializer.writeInt32(valueHolderForSelection_1)
        const valueHolderForSpans  = value.spans
        valueSerializer.writeInt32((valueHolderForSpans.length).toInt())
        for (let valueHolderForSpansCounterI = 0; valueHolderForSpansCounterI < valueHolderForSpans.length; valueHolderForSpansCounterI++) {
            const valueHolderForSpansTmpElement : RichEditorTextSpanResult | RichEditorImageSpanResult = valueHolderForSpans[valueHolderForSpansCounterI]
            if (valueHolderForSpansTmpElement instanceof RichEditorTextSpanResult) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSpansTmpElementForIdx0  = valueHolderForSpansTmpElement as RichEditorTextSpanResult
                RichEditorTextSpanResult_serializer.write(valueSerializer, valueHolderForSpansTmpElementForIdx0)
            } else if (valueHolderForSpansTmpElement instanceof RichEditorImageSpanResult) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSpansTmpElementForIdx1  = valueHolderForSpansTmpElement as RichEditorImageSpanResult
                RichEditorImageSpanResult_serializer.write(valueSerializer, valueHolderForSpansTmpElementForIdx1)
            }
        }
    }
    public static read(buffer: DeserializerBase): RichEditorSelection {
        let valueDeserializer : DeserializerBase = buffer
        const selectionTmpBufValue0 : int32 = valueDeserializer.readInt32()
        const selectionTmpBufValue1 : int32 = valueDeserializer.readInt32()
        const selectionTmpResult : [ int32, int32 ] = ([selectionTmpBufValue0, selectionTmpBufValue1] as [ int32, int32 ])
        const spansTmpBufLength : int32 = valueDeserializer.readInt32()
        let spansTmpBuf : Array<RichEditorTextSpanResult | RichEditorImageSpanResult> = new Array<RichEditorTextSpanResult | RichEditorImageSpanResult>(spansTmpBufLength)
        for (let spansTmpBufBufCounterI = 0; spansTmpBufBufCounterI < spansTmpBufLength; spansTmpBufBufCounterI++) {
            const spansTmpBufTempBufUnionSelector : int32 = valueDeserializer.readInt8()
            let spansTmpBufTempBuf : RichEditorTextSpanResult | RichEditorImageSpanResult | undefined
            if (spansTmpBufTempBufUnionSelector == (0).toByte()) {
                spansTmpBufTempBuf = RichEditorTextSpanResult_serializer.read(valueDeserializer)
            } else if (spansTmpBufTempBufUnionSelector == (1).toByte()) {
                spansTmpBufTempBuf = RichEditorImageSpanResult_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for spansTmpBufTempBuf has to be chosen through deserialisation.')
            }
            spansTmpBuf[spansTmpBufBufCounterI] = (spansTmpBufTempBuf as RichEditorTextSpanResult | RichEditorImageSpanResult)
        }
        const spansTmpResult : Array<RichEditorTextSpanResult | RichEditorImageSpanResult> = spansTmpBuf
        let value : RichEditorSelection = ({selection: selectionTmpResult, spans: spansTmpResult} as RichEditorSelection)
        return value
    }
}
export class RichEditorSpanPosition_serializer {
    public static write(buffer: SerializerBase, value: RichEditorSpanPosition): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSpanIndex  = value.spanIndex
        valueSerializer.writeInt32(valueHolderForSpanIndex)
        const valueHolderForSpanRange  = value.spanRange
        const valueHolderForSpanRange_0  = valueHolderForSpanRange[0]
        valueSerializer.writeInt32(valueHolderForSpanRange_0)
        const valueHolderForSpanRange_1  = valueHolderForSpanRange[1]
        valueSerializer.writeInt32(valueHolderForSpanRange_1)
    }
    public static read(buffer: DeserializerBase): RichEditorSpanPosition {
        let valueDeserializer : DeserializerBase = buffer
        const spanIndexTmpResult : int32 = valueDeserializer.readInt32()
        const spanRangeTmpBufValue0 : int32 = valueDeserializer.readInt32()
        const spanRangeTmpBufValue1 : int32 = valueDeserializer.readInt32()
        const spanRangeTmpResult : [ int32, int32 ] = ([spanRangeTmpBufValue0, spanRangeTmpBufValue1] as [ int32, int32 ])
        let value : RichEditorSpanPosition = ({spanIndex: spanIndexTmpResult, spanRange: spanRangeTmpResult} as RichEditorSpanPosition)
        return value
    }
}
export class RichEditorBuilderSpanOptions_serializer {
    public static write(buffer: SerializerBase, value: RichEditorBuilderSpanOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForOffset  = value.offset
        if (valueHolderForOffset !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOffsetTmpValue  = valueHolderForOffset!
            valueSerializer.writeInt32(valueHolderForOffsetTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDragBackgroundColor  = value.dragBackgroundColor
        if (valueHolderForDragBackgroundColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDragBackgroundColorTmpValue  = valueHolderForDragBackgroundColor!
            arkui_Graphics_ColorMetrics_serializer.write(valueSerializer, valueHolderForDragBackgroundColorTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIsDragShadowNeeded  = value.isDragShadowNeeded
        if (valueHolderForIsDragShadowNeeded !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIsDragShadowNeededTmpValue  = valueHolderForIsDragShadowNeeded!
            valueSerializer.writeBoolean(valueHolderForIsDragShadowNeededTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorBuilderSpanOptions {
        let valueDeserializer : DeserializerBase = buffer
        const offsetTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let offsetTmpBuf : int32 | undefined = undefined
        if ((offsetTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            offsetTmpBuf = valueDeserializer.readInt32()
        }
        const offsetTmpResult : int32 | undefined = offsetTmpBuf
        const dragBackgroundColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let dragBackgroundColorTmpBuf : arkui_Graphics_ColorMetrics | undefined = undefined
        if ((dragBackgroundColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            dragBackgroundColorTmpBuf = arkui_Graphics_ColorMetrics_serializer.read(valueDeserializer)
        }
        const dragBackgroundColorTmpResult : arkui_Graphics_ColorMetrics | undefined = dragBackgroundColorTmpBuf
        const isDragShadowNeededTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let isDragShadowNeededTmpBuf : boolean | undefined = undefined
        if ((isDragShadowNeededTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            isDragShadowNeededTmpBuf = valueDeserializer.readBoolean()
        }
        const isDragShadowNeededTmpResult : boolean | undefined = isDragShadowNeededTmpBuf
        let value : RichEditorBuilderSpanOptions = ({offset: offsetTmpResult, dragBackgroundColor: dragBackgroundColorTmpResult, isDragShadowNeeded: isDragShadowNeededTmpResult} as RichEditorBuilderSpanOptions)
        return value
    }
}
export class RichEditorChangeValue_serializer {
    public static write(buffer: SerializerBase, value: RichEditorChangeValue): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForRangeBefore  = value.rangeBefore
        TextRange_serializer.write(valueSerializer, valueHolderForRangeBefore)
        const valueHolderForReplacedSpans  = value.replacedSpans
        valueSerializer.writeInt32((valueHolderForReplacedSpans.length).toInt())
        for (let valueHolderForReplacedSpansCounterI = 0; valueHolderForReplacedSpansCounterI < valueHolderForReplacedSpans.length; valueHolderForReplacedSpansCounterI++) {
            const valueHolderForReplacedSpansTmpElement : RichEditorTextSpanResult = valueHolderForReplacedSpans[valueHolderForReplacedSpansCounterI]
            RichEditorTextSpanResult_serializer.write(valueSerializer, valueHolderForReplacedSpansTmpElement)
        }
        const valueHolderForReplacedImageSpans  = value.replacedImageSpans
        valueSerializer.writeInt32((valueHolderForReplacedImageSpans.length).toInt())
        for (let valueHolderForReplacedImageSpansCounterI = 0; valueHolderForReplacedImageSpansCounterI < valueHolderForReplacedImageSpans.length; valueHolderForReplacedImageSpansCounterI++) {
            const valueHolderForReplacedImageSpansTmpElement : RichEditorImageSpanResult = valueHolderForReplacedImageSpans[valueHolderForReplacedImageSpansCounterI]
            RichEditorImageSpanResult_serializer.write(valueSerializer, valueHolderForReplacedImageSpansTmpElement)
        }
        const valueHolderForReplacedSymbolSpans  = value.replacedSymbolSpans
        valueSerializer.writeInt32((valueHolderForReplacedSymbolSpans.length).toInt())
        for (let valueHolderForReplacedSymbolSpansCounterI = 0; valueHolderForReplacedSymbolSpansCounterI < valueHolderForReplacedSymbolSpans.length; valueHolderForReplacedSymbolSpansCounterI++) {
            const valueHolderForReplacedSymbolSpansTmpElement : RichEditorTextSpanResult = valueHolderForReplacedSymbolSpans[valueHolderForReplacedSymbolSpansCounterI]
            RichEditorTextSpanResult_serializer.write(valueSerializer, valueHolderForReplacedSymbolSpansTmpElement)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorChangeValue {
        let valueDeserializer : DeserializerBase = buffer
        const rangeBeforeTmpResult : TextRange = TextRange_serializer.read(valueDeserializer)
        const replacedSpansTmpBufLength : int32 = valueDeserializer.readInt32()
        let replacedSpansTmpBuf : Array<RichEditorTextSpanResult> = new Array<RichEditorTextSpanResult>(replacedSpansTmpBufLength)
        for (let replacedSpansTmpBufBufCounterI = 0; replacedSpansTmpBufBufCounterI < replacedSpansTmpBufLength; replacedSpansTmpBufBufCounterI++) {
            replacedSpansTmpBuf[replacedSpansTmpBufBufCounterI] = RichEditorTextSpanResult_serializer.read(valueDeserializer)
        }
        const replacedSpansTmpResult : Array<RichEditorTextSpanResult> = replacedSpansTmpBuf
        const replacedImageSpansTmpBufLength : int32 = valueDeserializer.readInt32()
        let replacedImageSpansTmpBuf : Array<RichEditorImageSpanResult> = new Array<RichEditorImageSpanResult>(replacedImageSpansTmpBufLength)
        for (let replacedImageSpansTmpBufBufCounterI = 0; replacedImageSpansTmpBufBufCounterI < replacedImageSpansTmpBufLength; replacedImageSpansTmpBufBufCounterI++) {
            replacedImageSpansTmpBuf[replacedImageSpansTmpBufBufCounterI] = RichEditorImageSpanResult_serializer.read(valueDeserializer)
        }
        const replacedImageSpansTmpResult : Array<RichEditorImageSpanResult> = replacedImageSpansTmpBuf
        const replacedSymbolSpansTmpBufLength : int32 = valueDeserializer.readInt32()
        let replacedSymbolSpansTmpBuf : Array<RichEditorTextSpanResult> = new Array<RichEditorTextSpanResult>(replacedSymbolSpansTmpBufLength)
        for (let replacedSymbolSpansTmpBufBufCounterI = 0; replacedSymbolSpansTmpBufBufCounterI < replacedSymbolSpansTmpBufLength; replacedSymbolSpansTmpBufBufCounterI++) {
            replacedSymbolSpansTmpBuf[replacedSymbolSpansTmpBufBufCounterI] = RichEditorTextSpanResult_serializer.read(valueDeserializer)
        }
        const replacedSymbolSpansTmpResult : Array<RichEditorTextSpanResult> = replacedSymbolSpansTmpBuf
        let value : RichEditorChangeValue = ({rangeBefore: rangeBeforeTmpResult, replacedSpans: replacedSpansTmpResult, replacedImageSpans: replacedImageSpansTmpResult, replacedSymbolSpans: replacedSymbolSpansTmpResult} as RichEditorChangeValue)
        return value
    }
}
export class RichEditorSymbolSpanStyle_serializer {
    public static write(buffer: SerializerBase, value: RichEditorSymbolSpanStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForFontSize  = value.fontSize
        if (valueHolderForFontSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontSizeTmpValue  = valueHolderForFontSize!
            if (valueHolderForFontSizeTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForFontSizeTmpValueForIdx0  = valueHolderForFontSizeTmpValue as double
                valueSerializer.writeFloat64(valueHolderForFontSizeTmpValueForIdx0)
            } else if (valueHolderForFontSizeTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForFontSizeTmpValueForIdx1  = valueHolderForFontSizeTmpValue as string
                valueSerializer.writeString(valueHolderForFontSizeTmpValueForIdx1)
            } else if (valueHolderForFontSizeTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForFontSizeTmpValueForIdx2  = valueHolderForFontSizeTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForFontSizeTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontColor  = value.fontColor
        if (valueHolderForFontColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontColorTmpValue  = valueHolderForFontColor!
            valueSerializer.writeInt32((valueHolderForFontColorTmpValue.length).toInt())
            for (let valueHolderForFontColorTmpValueCounterI = 0; valueHolderForFontColorTmpValueCounterI < valueHolderForFontColorTmpValue.length; valueHolderForFontColorTmpValueCounterI++) {
                const valueHolderForFontColorTmpValueTmpElement : ResourceColor = valueHolderForFontColorTmpValue[valueHolderForFontColorTmpValueCounterI]
                if (valueHolderForFontColorTmpValueTmpElement instanceof arkui_component_enums_Color) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForFontColorTmpValueTmpElementForIdx0  = valueHolderForFontColorTmpValueTmpElement as arkui_component_enums_Color
                    valueSerializer.writeInt32((valueHolderForFontColorTmpValueTmpElementForIdx0.getOrdinal()) % (12))
                } else if (valueHolderForFontColorTmpValueTmpElement instanceof int32) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForFontColorTmpValueTmpElementForIdx1  = valueHolderForFontColorTmpValueTmpElement as int32
                    valueSerializer.writeInt32(valueHolderForFontColorTmpValueTmpElementForIdx1)
                } else if (valueHolderForFontColorTmpValueTmpElement instanceof string) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForFontColorTmpValueTmpElementForIdx2  = valueHolderForFontColorTmpValueTmpElement as string
                    valueSerializer.writeString(valueHolderForFontColorTmpValueTmpElementForIdx2)
                } else if (valueHolderForFontColorTmpValueTmpElement instanceof arkui_component_units_Resource) {
                    valueSerializer.writeInt8((3).toByte())
                    const valueHolderForFontColorTmpValueTmpElementForIdx3  = valueHolderForFontColorTmpValueTmpElement as arkui_component_units_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForFontColorTmpValueTmpElementForIdx3)
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontWeight  = value.fontWeight
        if (valueHolderForFontWeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontWeightTmpValue  = valueHolderForFontWeight!
            if (valueHolderForFontWeightTmpValue instanceof int32) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForFontWeightTmpValueForIdx0  = valueHolderForFontWeightTmpValue as int32
                valueSerializer.writeInt32(valueHolderForFontWeightTmpValueForIdx0)
            } else if (valueHolderForFontWeightTmpValue instanceof FontWeight) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForFontWeightTmpValueForIdx1  = valueHolderForFontWeightTmpValue as FontWeight
                valueSerializer.writeInt32(valueHolderForFontWeightTmpValueForIdx1.valueOf())
            } else if (valueHolderForFontWeightTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForFontWeightTmpValueForIdx2  = valueHolderForFontWeightTmpValue as string
                valueSerializer.writeString(valueHolderForFontWeightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEffectStrategy  = value.effectStrategy
        if (valueHolderForEffectStrategy !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEffectStrategyTmpValue  = (valueHolderForEffectStrategy as SymbolEffectStrategy)
            valueSerializer.writeInt32(valueHolderForEffectStrategyTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRenderingStrategy  = value.renderingStrategy
        if (valueHolderForRenderingStrategy !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRenderingStrategyTmpValue  = (valueHolderForRenderingStrategy as SymbolRenderingStrategy)
            valueSerializer.writeInt32(valueHolderForRenderingStrategyTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorSymbolSpanStyle {
        let valueDeserializer : DeserializerBase = buffer
        const fontSizeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontSizeTmpBuf : double | string | global_resource_Resource | undefined = undefined
        if ((fontSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontSizeTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let fontSizeTmpBufOpt : double | string | global_resource_Resource | undefined
            if (fontSizeTmpBufOptUnionSelector == (0).toByte()) {
                fontSizeTmpBufOpt = valueDeserializer.readFloat64()
            } else if (fontSizeTmpBufOptUnionSelector == (1).toByte()) {
                fontSizeTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (fontSizeTmpBufOptUnionSelector == (2).toByte()) {
                fontSizeTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for fontSizeTmpBufOpt has to be chosen through deserialisation.')
            }
            fontSizeTmpBuf = (fontSizeTmpBufOpt as double | string | global_resource_Resource)
        }
        const fontSizeTmpResult : double | string | global_resource_Resource | undefined = fontSizeTmpBuf
        const fontColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontColorTmpBuf : Array<ResourceColor> | undefined = undefined
        if ((fontColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontColorTmpBufOptLength : int32 = valueDeserializer.readInt32()
            let fontColorTmpBufOpt : Array<ResourceColor> = new Array<ResourceColor>(fontColorTmpBufOptLength)
            for (let fontColorTmpBufOptBufCounterI = 0; fontColorTmpBufOptBufCounterI < fontColorTmpBufOptLength; fontColorTmpBufOptBufCounterI++) {
                const fontColorTmpBufOptTempBufUnionSelector : int32 = valueDeserializer.readInt8()
                let fontColorTmpBufOptTempBuf : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
                if (fontColorTmpBufOptTempBufUnionSelector == (0).toByte()) {
                    fontColorTmpBufOptTempBuf = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
                } else if (fontColorTmpBufOptTempBufUnionSelector == (1).toByte()) {
                    fontColorTmpBufOptTempBuf = valueDeserializer.readInt32()
                } else if (fontColorTmpBufOptTempBufUnionSelector == (2).toByte()) {
                    fontColorTmpBufOptTempBuf = (valueDeserializer.readString() as string)
                } else if (fontColorTmpBufOptTempBufUnionSelector == (3).toByte()) {
                    fontColorTmpBufOptTempBuf = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for fontColorTmpBufOptTempBuf has to be chosen through deserialisation.')
                }
                fontColorTmpBufOpt[fontColorTmpBufOptBufCounterI] = (fontColorTmpBufOptTempBuf as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
            }
            fontColorTmpBuf = fontColorTmpBufOpt
        }
        const fontColorTmpResult : Array<ResourceColor> | undefined = fontColorTmpBuf
        const fontWeightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontWeightTmpBuf : int32 | FontWeight | string | undefined = undefined
        if ((fontWeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontWeightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let fontWeightTmpBufOpt : int32 | FontWeight | string | undefined
            if (fontWeightTmpBufOptUnionSelector == (0).toByte()) {
                fontWeightTmpBufOpt = valueDeserializer.readInt32()
            } else if (fontWeightTmpBufOptUnionSelector == (1).toByte()) {
                fontWeightTmpBufOpt = FontWeight.fromValue(valueDeserializer.readInt32())
            } else if (fontWeightTmpBufOptUnionSelector == (2).toByte()) {
                fontWeightTmpBufOpt = (valueDeserializer.readString() as string)
            } else {
                throw new Error('One of the branches for fontWeightTmpBufOpt has to be chosen through deserialisation.')
            }
            fontWeightTmpBuf = (fontWeightTmpBufOpt as int32 | FontWeight | string)
        }
        const fontWeightTmpResult : int32 | FontWeight | string | undefined = fontWeightTmpBuf
        const effectStrategyTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let effectStrategyTmpBuf : SymbolEffectStrategy | undefined = undefined
        if ((effectStrategyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            effectStrategyTmpBuf = SymbolEffectStrategy.fromValue(valueDeserializer.readInt32())
        }
        const effectStrategyTmpResult : SymbolEffectStrategy | undefined = effectStrategyTmpBuf
        const renderingStrategyTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let renderingStrategyTmpBuf : SymbolRenderingStrategy | undefined = undefined
        if ((renderingStrategyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            renderingStrategyTmpBuf = SymbolRenderingStrategy.fromValue(valueDeserializer.readInt32())
        }
        const renderingStrategyTmpResult : SymbolRenderingStrategy | undefined = renderingStrategyTmpBuf
        let value : RichEditorSymbolSpanStyle = ({fontSize: fontSizeTmpResult, fontColor: fontColorTmpResult, fontWeight: fontWeightTmpResult, effectStrategy: effectStrategyTmpResult, renderingStrategy: renderingStrategyTmpResult} as RichEditorSymbolSpanStyle)
        return value
    }
}
export class RichEditorUpdateSymbolSpanStyleOptions_serializer {
    public static write(buffer: SerializerBase, value: RichEditorUpdateSymbolSpanStyleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStart  = value.start
        if (valueHolderForStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartTmpValue  = valueHolderForStart!
            valueSerializer.writeInt32(valueHolderForStartTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnd  = value.end
        if (valueHolderForEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndTmpValue  = valueHolderForEnd!
            valueSerializer.writeInt32(valueHolderForEndTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSymbolStyle  = value.symbolStyle
        RichEditorSymbolSpanStyle_serializer.write(valueSerializer, valueHolderForSymbolStyle)
    }
    public static read(buffer: DeserializerBase): RichEditorUpdateSymbolSpanStyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let startTmpBuf : int32 | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startTmpBuf = valueDeserializer.readInt32()
        }
        const startTmpResult : int32 | undefined = startTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let endTmpBuf : int32 | undefined = undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endTmpBuf = valueDeserializer.readInt32()
        }
        const endTmpResult : int32 | undefined = endTmpBuf
        const symbolStyleTmpResult : RichEditorSymbolSpanStyle = RichEditorSymbolSpanStyle_serializer.read(valueDeserializer)
        let value : RichEditorUpdateSymbolSpanStyleOptions = ({start: startTmpResult, end: endTmpResult, symbolStyle: symbolStyleTmpResult} as RichEditorUpdateSymbolSpanStyleOptions)
        return value
    }
}
export class RichEditorUrlStyle_serializer {
    public static write(buffer: SerializerBase, value: RichEditorUrlStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForUrl  = value.url
        if (valueHolderForUrl !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUrlTmpValue  = valueHolderForUrl!
            if (valueHolderForUrlTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForUrlTmpValueForIdx0  = valueHolderForUrlTmpValue as string
                valueSerializer.writeString(valueHolderForUrlTmpValueForIdx0)
            } else if (valueHolderForUrlTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForUrlTmpValueForIdx1  = valueHolderForUrlTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForUrlTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorUrlStyle {
        let valueDeserializer : DeserializerBase = buffer
        const urlTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let urlTmpBuf : arkui_component_units_ResourceStr | undefined = undefined
        if ((urlTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const urlTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let urlTmpBufOpt : string | arkui_component_units_Resource | undefined
            if (urlTmpBufOptUnionSelector == (0).toByte()) {
                urlTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (urlTmpBufOptUnionSelector == (1).toByte()) {
                urlTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for urlTmpBufOpt has to be chosen through deserialisation.')
            }
            urlTmpBuf = (urlTmpBufOpt as string | arkui_component_units_Resource)
        }
        const urlTmpResult : arkui_component_units_ResourceStr | undefined = urlTmpBuf
        let value : RichEditorUrlStyle = ({url: urlTmpResult} as RichEditorUrlStyle)
        return value
    }
}
export class SelectionMenuOptions_serializer {
    public static write(buffer: SerializerBase, value: SelectionMenuOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForOnAppear  = value.onAppear
        if (valueHolderForOnAppear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnAppearTmpValue  = valueHolderForOnAppear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnAppearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnDisappear  = value.onDisappear
        if (valueHolderForOnDisappear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnDisappearTmpValue  = valueHolderForOnDisappear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnDisappearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMenuType  = value.menuType
        if (valueHolderForMenuType !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMenuTypeTmpValue  = (valueHolderForMenuType as MenuType)
            valueSerializer.writeInt32(valueHolderForMenuTypeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnMenuShow  = value.onMenuShow
        if (valueHolderForOnMenuShow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnMenuShowTmpValue  = valueHolderForOnMenuShow!
            valueSerializer.holdAndWriteCallback(valueHolderForOnMenuShowTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnMenuHide  = value.onMenuHide
        if (valueHolderForOnMenuHide !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnMenuHideTmpValue  = valueHolderForOnMenuHide!
            valueSerializer.holdAndWriteCallback(valueHolderForOnMenuHideTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPreviewMenuOptions  = value.previewMenuOptions
        if (valueHolderForPreviewMenuOptions !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPreviewMenuOptionsTmpValue  = valueHolderForPreviewMenuOptions!
            RichEditorPreviewMenuOptions_serializer.write(valueSerializer, valueHolderForPreviewMenuOptionsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SelectionMenuOptions {
        let valueDeserializer : DeserializerBase = buffer
        const onAppearTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onAppearTmpBuf : MenuOnAppearCallback | undefined = undefined
        if ((onAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onAppearTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onAppearTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onAppearTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onAppearTmpBufOptClosure  = (start: int32, end: int32):void => {
                const onAppearTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onAppearTmpBufOptBufArgsSerializer.writeInt32(onAppearTmpBufOptBufResource.resourceId);
                onAppearTmpBufOptBufArgsSerializer.writePointer(onAppearTmpBufOptBufCall);
                onAppearTmpBufOptBufArgsSerializer.writePointer(onAppearTmpBufOptBufCallSync);
                onAppearTmpBufOptBufArgsSerializer.writeInt32(start);
                onAppearTmpBufOptBufArgsSerializer.writeInt32(end);
                InteropNativeModule._CallCallbackSync(10, 846082462, onAppearTmpBufOptBufArgsSerializer.asBuffer(), onAppearTmpBufOptBufArgsSerializer.length());
                onAppearTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onAppearTmpBufOptClosure, onAppearTmpBufOptBufResource)
            onAppearTmpBuf = onAppearTmpBufOptClosure
        }
        const onAppearTmpResult : MenuOnAppearCallback | undefined = onAppearTmpBuf
        const onDisappearTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onDisappearTmpBuf : VoidCallback | undefined = undefined
        if ((onDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDisappearTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDisappearTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onDisappearTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onDisappearTmpBufOptClosure  = ():void => {
                const onDisappearTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDisappearTmpBufOptBufArgsSerializer.writeInt32(onDisappearTmpBufOptBufResource.resourceId);
                onDisappearTmpBufOptBufArgsSerializer.writePointer(onDisappearTmpBufOptBufCall);
                onDisappearTmpBufOptBufArgsSerializer.writePointer(onDisappearTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, 553494831, onDisappearTmpBufOptBufArgsSerializer.asBuffer(), onDisappearTmpBufOptBufArgsSerializer.length());
                onDisappearTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onDisappearTmpBufOptClosure, onDisappearTmpBufOptBufResource)
            onDisappearTmpBuf = onDisappearTmpBufOptClosure
        }
        const onDisappearTmpResult : VoidCallback | undefined = onDisappearTmpBuf
        const menuTypeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let menuTypeTmpBuf : MenuType | undefined = undefined
        if ((menuTypeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            menuTypeTmpBuf = MenuType.fromValue(valueDeserializer.readInt32())
        }
        const menuTypeTmpResult : MenuType | undefined = menuTypeTmpBuf
        const onMenuShowTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onMenuShowTmpBuf : MenuCallback | undefined = undefined
        if ((onMenuShowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onMenuShowTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onMenuShowTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onMenuShowTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onMenuShowTmpBufOptClosure  = (start: int32, end: int32):void => {
                const onMenuShowTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onMenuShowTmpBufOptBufArgsSerializer.writeInt32(onMenuShowTmpBufOptBufResource.resourceId);
                onMenuShowTmpBufOptBufArgsSerializer.writePointer(onMenuShowTmpBufOptBufCall);
                onMenuShowTmpBufOptBufArgsSerializer.writePointer(onMenuShowTmpBufOptBufCallSync);
                onMenuShowTmpBufOptBufArgsSerializer.writeInt32(start);
                onMenuShowTmpBufOptBufArgsSerializer.writeInt32(end);
                InteropNativeModule._CallCallbackSync(10, -1242887384, onMenuShowTmpBufOptBufArgsSerializer.asBuffer(), onMenuShowTmpBufOptBufArgsSerializer.length());
                onMenuShowTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onMenuShowTmpBufOptClosure, onMenuShowTmpBufOptBufResource)
            onMenuShowTmpBuf = onMenuShowTmpBufOptClosure
        }
        const onMenuShowTmpResult : MenuCallback | undefined = onMenuShowTmpBuf
        const onMenuHideTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onMenuHideTmpBuf : MenuCallback | undefined = undefined
        if ((onMenuHideTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onMenuHideTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onMenuHideTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onMenuHideTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onMenuHideTmpBufOptClosure  = (start: int32, end: int32):void => {
                const onMenuHideTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onMenuHideTmpBufOptBufArgsSerializer.writeInt32(onMenuHideTmpBufOptBufResource.resourceId);
                onMenuHideTmpBufOptBufArgsSerializer.writePointer(onMenuHideTmpBufOptBufCall);
                onMenuHideTmpBufOptBufArgsSerializer.writePointer(onMenuHideTmpBufOptBufCallSync);
                onMenuHideTmpBufOptBufArgsSerializer.writeInt32(start);
                onMenuHideTmpBufOptBufArgsSerializer.writeInt32(end);
                InteropNativeModule._CallCallbackSync(10, -1242887384, onMenuHideTmpBufOptBufArgsSerializer.asBuffer(), onMenuHideTmpBufOptBufArgsSerializer.length());
                onMenuHideTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onMenuHideTmpBufOptClosure, onMenuHideTmpBufOptBufResource)
            onMenuHideTmpBuf = onMenuHideTmpBufOptClosure
        }
        const onMenuHideTmpResult : MenuCallback | undefined = onMenuHideTmpBuf
        const previewMenuOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let previewMenuOptionsTmpBuf : RichEditorPreviewMenuOptions | undefined = undefined
        if ((previewMenuOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            previewMenuOptionsTmpBuf = RichEditorPreviewMenuOptions_serializer.read(valueDeserializer)
        }
        const previewMenuOptionsTmpResult : RichEditorPreviewMenuOptions | undefined = previewMenuOptionsTmpBuf
        let value : SelectionMenuOptions = ({onAppear: onAppearTmpResult, onDisappear: onDisappearTmpResult, menuType: menuTypeTmpResult, onMenuShow: onMenuShowTmpResult, onMenuHide: onMenuHideTmpResult, previewMenuOptions: previewMenuOptionsTmpResult} as SelectionMenuOptions)
        return value
    }
}
export class LeadingMarginPlaceholder_serializer {
    public static write(buffer: SerializerBase, value: LeadingMarginPlaceholder): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForPixelMap  = value.pixelMap
        image_PixelMap_serializer.write(valueSerializer, valueHolderForPixelMap)
        const valueHolderForSize  = value.size
        const valueHolderForSize_0  = valueHolderForSize[0]
        if (valueHolderForSize_0 instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForSize_0ForIdx0  = valueHolderForSize_0 as string
            valueSerializer.writeString(valueHolderForSize_0ForIdx0)
        } else if (valueHolderForSize_0 instanceof number) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForSize_0ForIdx1  = valueHolderForSize_0 as number
            valueSerializer.writeNumber(valueHolderForSize_0ForIdx1)
        } else if (valueHolderForSize_0 instanceof global_resource_Resource) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForSize_0ForIdx2  = valueHolderForSize_0 as global_resource_Resource
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForSize_0ForIdx2)
        }
        const valueHolderForSize_1  = valueHolderForSize[1]
        if (valueHolderForSize_1 instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForSize_1ForIdx0  = valueHolderForSize_1 as string
            valueSerializer.writeString(valueHolderForSize_1ForIdx0)
        } else if (valueHolderForSize_1 instanceof number) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForSize_1ForIdx1  = valueHolderForSize_1 as number
            valueSerializer.writeNumber(valueHolderForSize_1ForIdx1)
        } else if (valueHolderForSize_1 instanceof global_resource_Resource) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForSize_1ForIdx2  = valueHolderForSize_1 as global_resource_Resource
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForSize_1ForIdx2)
        }
    }
    public static read(buffer: DeserializerBase): LeadingMarginPlaceholder {
        let valueDeserializer : DeserializerBase = buffer
        const pixelMapTmpResult : PixelMap = (image_PixelMap_serializer.read(valueDeserializer) as image.PixelMap)
        const sizeTmpBufValue0TempBufUnionSelector : int32 = valueDeserializer.readInt8()
        let sizeTmpBufValue0TempBuf : string | number | global_resource_Resource | undefined
        if (sizeTmpBufValue0TempBufUnionSelector == (0).toByte()) {
            sizeTmpBufValue0TempBuf = (valueDeserializer.readString() as string)
        } else if (sizeTmpBufValue0TempBufUnionSelector == (1).toByte()) {
            sizeTmpBufValue0TempBuf = (valueDeserializer.readNumber() as number)
        } else if (sizeTmpBufValue0TempBufUnionSelector == (2).toByte()) {
            sizeTmpBufValue0TempBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for sizeTmpBufValue0TempBuf has to be chosen through deserialisation.')
        }
        const sizeTmpBufValue0 : Dimension = (sizeTmpBufValue0TempBuf as string | number | global_resource_Resource)
        const sizeTmpBufValue1TempBufUnionSelector : int32 = valueDeserializer.readInt8()
        let sizeTmpBufValue1TempBuf : string | number | global_resource_Resource | undefined
        if (sizeTmpBufValue1TempBufUnionSelector == (0).toByte()) {
            sizeTmpBufValue1TempBuf = (valueDeserializer.readString() as string)
        } else if (sizeTmpBufValue1TempBufUnionSelector == (1).toByte()) {
            sizeTmpBufValue1TempBuf = (valueDeserializer.readNumber() as number)
        } else if (sizeTmpBufValue1TempBufUnionSelector == (2).toByte()) {
            sizeTmpBufValue1TempBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for sizeTmpBufValue1TempBuf has to be chosen through deserialisation.')
        }
        const sizeTmpBufValue1 : Dimension = (sizeTmpBufValue1TempBuf as string | number | global_resource_Resource)
        const sizeTmpResult : [ Dimension, Dimension ] = ([sizeTmpBufValue0, sizeTmpBufValue1] as [ Dimension, Dimension ])
        let value : LeadingMarginPlaceholder = ({pixelMap: pixelMapTmpResult, size: sizeTmpResult} as LeadingMarginPlaceholder)
        return value
    }
}
export class RichEditorSymbolSpanOptions_serializer {
    public static write(buffer: SerializerBase, value: RichEditorSymbolSpanOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForOffset  = value.offset
        if (valueHolderForOffset !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOffsetTmpValue  = valueHolderForOffset!
            valueSerializer.writeInt32(valueHolderForOffsetTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStyle  = value.style
        if (valueHolderForStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStyleTmpValue  = valueHolderForStyle!
            RichEditorSymbolSpanStyle_serializer.write(valueSerializer, valueHolderForStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorSymbolSpanOptions {
        let valueDeserializer : DeserializerBase = buffer
        const offsetTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let offsetTmpBuf : int32 | undefined = undefined
        if ((offsetTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            offsetTmpBuf = valueDeserializer.readInt32()
        }
        const offsetTmpResult : int32 | undefined = offsetTmpBuf
        const styleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let styleTmpBuf : RichEditorSymbolSpanStyle | undefined = undefined
        if ((styleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            styleTmpBuf = RichEditorSymbolSpanStyle_serializer.read(valueDeserializer)
        }
        const styleTmpResult : RichEditorSymbolSpanStyle | undefined = styleTmpBuf
        let value : RichEditorSymbolSpanOptions = ({offset: offsetTmpResult, style: styleTmpResult} as RichEditorSymbolSpanOptions)
        return value
    }
}
export class PlaceholderStyle_serializer {
    public static write(buffer: SerializerBase, value: PlaceholderStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForFont  = value.font
        if (valueHolderForFont !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontTmpValue  = valueHolderForFont!
            arkui_component_units_Font_serializer.write(valueSerializer, valueHolderForFontTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontColor  = value.fontColor
        if (valueHolderForFontColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontColorTmpValue  = valueHolderForFontColor!
            if (valueHolderForFontColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForFontColorTmpValueForIdx0  = valueHolderForFontColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForFontColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForFontColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForFontColorTmpValueForIdx1  = valueHolderForFontColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForFontColorTmpValueForIdx1)
            } else if (valueHolderForFontColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForFontColorTmpValueForIdx2  = valueHolderForFontColorTmpValue as string
                valueSerializer.writeString(valueHolderForFontColorTmpValueForIdx2)
            } else if (valueHolderForFontColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForFontColorTmpValueForIdx3  = valueHolderForFontColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForFontColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): PlaceholderStyle {
        let valueDeserializer : DeserializerBase = buffer
        const fontTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontTmpBuf : arkui_component_units_Font | undefined = undefined
        if ((fontTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fontTmpBuf = arkui_component_units_Font_serializer.read(valueDeserializer)
        }
        const fontTmpResult : arkui_component_units_Font | undefined = fontTmpBuf
        const fontColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontColorTmpBuf : ResourceColor | undefined = undefined
        if ((fontColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontColorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let fontColorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (fontColorTmpBufOptUnionSelector == (0).toByte()) {
                fontColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (fontColorTmpBufOptUnionSelector == (1).toByte()) {
                fontColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (fontColorTmpBufOptUnionSelector == (2).toByte()) {
                fontColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (fontColorTmpBufOptUnionSelector == (3).toByte()) {
                fontColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for fontColorTmpBufOpt has to be chosen through deserialisation.')
            }
            fontColorTmpBuf = (fontColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const fontColorTmpResult : ResourceColor | undefined = fontColorTmpBuf
        let value : PlaceholderStyle = ({font: fontTmpResult, fontColor: fontColorTmpResult} as PlaceholderStyle)
        return value
    }
}
export class RichEditorLayoutStyle_serializer {
    public static write(buffer: SerializerBase, value: RichEditorLayoutStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForMargin  = value.margin
        if (valueHolderForMargin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMarginTmpValue  = valueHolderForMargin!
            if (valueHolderForMarginTmpValue instanceof Dimension) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForMarginTmpValueForIdx0  = valueHolderForMarginTmpValue as Dimension
                if (valueHolderForMarginTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForMarginTmpValueForIdx0ForIdx0  = valueHolderForMarginTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForMarginTmpValueForIdx0ForIdx0)
                } else if (valueHolderForMarginTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForMarginTmpValueForIdx0ForIdx1  = valueHolderForMarginTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForMarginTmpValueForIdx0ForIdx1)
                } else if (valueHolderForMarginTmpValueForIdx0 instanceof global_resource_Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForMarginTmpValueForIdx0ForIdx2  = valueHolderForMarginTmpValueForIdx0 as global_resource_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForMarginTmpValueForIdx0ForIdx2)
                }
            } else if (valueHolderForMarginTmpValue instanceof Margin) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForMarginTmpValueForIdx1  = valueHolderForMarginTmpValue as Margin
                Padding_serializer.write(valueSerializer, valueHolderForMarginTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderRadius  = value.borderRadius
        if (valueHolderForBorderRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderRadiusTmpValue  = valueHolderForBorderRadius!
            if (valueHolderForBorderRadiusTmpValue instanceof Dimension) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderRadiusTmpValueForIdx0  = valueHolderForBorderRadiusTmpValue as Dimension
                if (valueHolderForBorderRadiusTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForBorderRadiusTmpValueForIdx0ForIdx0  = valueHolderForBorderRadiusTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForBorderRadiusTmpValueForIdx0ForIdx0)
                } else if (valueHolderForBorderRadiusTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForBorderRadiusTmpValueForIdx0ForIdx1  = valueHolderForBorderRadiusTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForBorderRadiusTmpValueForIdx0ForIdx1)
                } else if (valueHolderForBorderRadiusTmpValueForIdx0 instanceof global_resource_Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForBorderRadiusTmpValueForIdx0ForIdx2  = valueHolderForBorderRadiusTmpValueForIdx0 as global_resource_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForBorderRadiusTmpValueForIdx0ForIdx2)
                }
            } else if (valueHolderForBorderRadiusTmpValue instanceof BorderRadiuses) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderRadiusTmpValueForIdx1  = valueHolderForBorderRadiusTmpValue as BorderRadiuses
                BorderRadiuses_serializer.write(valueSerializer, valueHolderForBorderRadiusTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorLayoutStyle {
        let valueDeserializer : DeserializerBase = buffer
        const marginTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let marginTmpBuf : Dimension | Margin | undefined = undefined
        if ((marginTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const marginTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let marginTmpBufOpt : Dimension | Margin | undefined
            if (marginTmpBufOptUnionSelector == (0).toByte()) {
                const marginTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let marginTmpBufOptBufU : string | number | global_resource_Resource | undefined
                if (marginTmpBufOptBufUUnionSelector == (0).toByte()) {
                    marginTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (marginTmpBufOptBufUUnionSelector == (1).toByte()) {
                    marginTmpBufOptBufU = (valueDeserializer.readNumber() as number)
                } else if (marginTmpBufOptBufUUnionSelector == (2).toByte()) {
                    marginTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for marginTmpBufOptBufU has to be chosen through deserialisation.')
                }
                marginTmpBufOpt = (marginTmpBufOptBufU as string | number | global_resource_Resource)
            } else if (marginTmpBufOptUnionSelector == (1).toByte()) {
                marginTmpBufOpt = Padding_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for marginTmpBufOpt has to be chosen through deserialisation.')
            }
            marginTmpBuf = (marginTmpBufOpt as Dimension | Margin)
        }
        const marginTmpResult : Dimension | Margin | undefined = marginTmpBuf
        const borderRadiusTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let borderRadiusTmpBuf : Dimension | BorderRadiuses | undefined = undefined
        if ((borderRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderRadiusTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let borderRadiusTmpBufOpt : Dimension | BorderRadiuses | undefined
            if (borderRadiusTmpBufOptUnionSelector == (0).toByte()) {
                const borderRadiusTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let borderRadiusTmpBufOptBufU : string | number | global_resource_Resource | undefined
                if (borderRadiusTmpBufOptBufUUnionSelector == (0).toByte()) {
                    borderRadiusTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (borderRadiusTmpBufOptBufUUnionSelector == (1).toByte()) {
                    borderRadiusTmpBufOptBufU = (valueDeserializer.readNumber() as number)
                } else if (borderRadiusTmpBufOptBufUUnionSelector == (2).toByte()) {
                    borderRadiusTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for borderRadiusTmpBufOptBufU has to be chosen through deserialisation.')
                }
                borderRadiusTmpBufOpt = (borderRadiusTmpBufOptBufU as string | number | global_resource_Resource)
            } else if (borderRadiusTmpBufOptUnionSelector == (1).toByte()) {
                borderRadiusTmpBufOpt = BorderRadiuses_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for borderRadiusTmpBufOpt has to be chosen through deserialisation.')
            }
            borderRadiusTmpBuf = (borderRadiusTmpBufOpt as Dimension | BorderRadiuses)
        }
        const borderRadiusTmpResult : Dimension | BorderRadiuses | undefined = borderRadiusTmpBuf
        let value : RichEditorLayoutStyle = ({margin: marginTmpResult, borderRadius: borderRadiusTmpResult} as RichEditorLayoutStyle)
        return value
    }
}
export class RichEditorParagraphStyle_serializer {
    public static write(buffer: SerializerBase, value: RichEditorParagraphStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTextAlign  = value.textAlign
        if (valueHolderForTextAlign !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextAlignTmpValue  = (valueHolderForTextAlign as TextAlign)
            valueSerializer.writeInt32(valueHolderForTextAlignTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLeadingMargin  = value.leadingMargin
        if (valueHolderForLeadingMargin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLeadingMarginTmpValue  = valueHolderForLeadingMargin!
            if (valueHolderForLeadingMarginTmpValue instanceof Dimension) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForLeadingMarginTmpValueForIdx0  = valueHolderForLeadingMarginTmpValue as Dimension
                if (valueHolderForLeadingMarginTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForLeadingMarginTmpValueForIdx0ForIdx0  = valueHolderForLeadingMarginTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForLeadingMarginTmpValueForIdx0ForIdx0)
                } else if (valueHolderForLeadingMarginTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForLeadingMarginTmpValueForIdx0ForIdx1  = valueHolderForLeadingMarginTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForLeadingMarginTmpValueForIdx0ForIdx1)
                } else if (valueHolderForLeadingMarginTmpValueForIdx0 instanceof global_resource_Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForLeadingMarginTmpValueForIdx0ForIdx2  = valueHolderForLeadingMarginTmpValueForIdx0 as global_resource_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForLeadingMarginTmpValueForIdx0ForIdx2)
                }
            } else if (valueHolderForLeadingMarginTmpValue instanceof LeadingMarginPlaceholder) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForLeadingMarginTmpValueForIdx1  = valueHolderForLeadingMarginTmpValue as LeadingMarginPlaceholder
                LeadingMarginPlaceholder_serializer.write(valueSerializer, valueHolderForLeadingMarginTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWordBreak  = value.wordBreak
        if (valueHolderForWordBreak !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWordBreakTmpValue  = (valueHolderForWordBreak as WordBreak)
            valueSerializer.writeInt32(valueHolderForWordBreakTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLineBreakStrategy  = value.lineBreakStrategy
        if (valueHolderForLineBreakStrategy !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLineBreakStrategyTmpValue  = (valueHolderForLineBreakStrategy as LineBreakStrategy)
            valueSerializer.writeInt32(valueHolderForLineBreakStrategyTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForParagraphSpacing  = value.paragraphSpacing
        if (valueHolderForParagraphSpacing !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForParagraphSpacingTmpValue  = valueHolderForParagraphSpacing!
            valueSerializer.writeFloat64(valueHolderForParagraphSpacingTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorParagraphStyle {
        let valueDeserializer : DeserializerBase = buffer
        const textAlignTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let textAlignTmpBuf : TextAlign | undefined = undefined
        if ((textAlignTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            textAlignTmpBuf = TextAlign.fromValue(valueDeserializer.readInt32())
        }
        const textAlignTmpResult : TextAlign | undefined = textAlignTmpBuf
        const leadingMarginTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let leadingMarginTmpBuf : Dimension | LeadingMarginPlaceholder | undefined = undefined
        if ((leadingMarginTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const leadingMarginTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let leadingMarginTmpBufOpt : Dimension | LeadingMarginPlaceholder | undefined
            if (leadingMarginTmpBufOptUnionSelector == (0).toByte()) {
                const leadingMarginTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let leadingMarginTmpBufOptBufU : string | number | global_resource_Resource | undefined
                if (leadingMarginTmpBufOptBufUUnionSelector == (0).toByte()) {
                    leadingMarginTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (leadingMarginTmpBufOptBufUUnionSelector == (1).toByte()) {
                    leadingMarginTmpBufOptBufU = (valueDeserializer.readNumber() as number)
                } else if (leadingMarginTmpBufOptBufUUnionSelector == (2).toByte()) {
                    leadingMarginTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for leadingMarginTmpBufOptBufU has to be chosen through deserialisation.')
                }
                leadingMarginTmpBufOpt = (leadingMarginTmpBufOptBufU as string | number | global_resource_Resource)
            } else if (leadingMarginTmpBufOptUnionSelector == (1).toByte()) {
                leadingMarginTmpBufOpt = LeadingMarginPlaceholder_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for leadingMarginTmpBufOpt has to be chosen through deserialisation.')
            }
            leadingMarginTmpBuf = (leadingMarginTmpBufOpt as Dimension | LeadingMarginPlaceholder)
        }
        const leadingMarginTmpResult : Dimension | LeadingMarginPlaceholder | undefined = leadingMarginTmpBuf
        const wordBreakTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let wordBreakTmpBuf : WordBreak | undefined = undefined
        if ((wordBreakTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            wordBreakTmpBuf = WordBreak.fromValue(valueDeserializer.readInt32())
        }
        const wordBreakTmpResult : WordBreak | undefined = wordBreakTmpBuf
        const lineBreakStrategyTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let lineBreakStrategyTmpBuf : LineBreakStrategy | undefined = undefined
        if ((lineBreakStrategyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            lineBreakStrategyTmpBuf = LineBreakStrategy.fromValue(valueDeserializer.readInt32())
        }
        const lineBreakStrategyTmpResult : LineBreakStrategy | undefined = lineBreakStrategyTmpBuf
        const paragraphSpacingTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let paragraphSpacingTmpBuf : double | undefined = undefined
        if ((paragraphSpacingTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            paragraphSpacingTmpBuf = valueDeserializer.readFloat64()
        }
        const paragraphSpacingTmpResult : double | undefined = paragraphSpacingTmpBuf
        let value : RichEditorParagraphStyle = ({textAlign: textAlignTmpResult, leadingMargin: leadingMarginTmpResult, wordBreak: wordBreakTmpResult, lineBreakStrategy: lineBreakStrategyTmpResult, paragraphSpacing: paragraphSpacingTmpResult} as RichEditorParagraphStyle)
        return value
    }
}
export class RichEditorParagraphStyleOptions_serializer {
    public static write(buffer: SerializerBase, value: RichEditorParagraphStyleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStart  = value.start
        if (valueHolderForStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartTmpValue  = valueHolderForStart!
            valueSerializer.writeInt32(valueHolderForStartTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnd  = value.end
        if (valueHolderForEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndTmpValue  = valueHolderForEnd!
            valueSerializer.writeInt32(valueHolderForEndTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStyle  = value.style
        RichEditorParagraphStyle_serializer.write(valueSerializer, valueHolderForStyle)
    }
    public static read(buffer: DeserializerBase): RichEditorParagraphStyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let startTmpBuf : int32 | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startTmpBuf = valueDeserializer.readInt32()
        }
        const startTmpResult : int32 | undefined = startTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let endTmpBuf : int32 | undefined = undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endTmpBuf = valueDeserializer.readInt32()
        }
        const endTmpResult : int32 | undefined = endTmpBuf
        const styleTmpResult : RichEditorParagraphStyle = RichEditorParagraphStyle_serializer.read(valueDeserializer)
        let value : RichEditorParagraphStyleOptions = ({start: startTmpResult, end: endTmpResult, style: styleTmpResult} as RichEditorParagraphStyleOptions)
        return value
    }
}
export class RichEditorImageSpanStyle_serializer {
    public static write(buffer: SerializerBase, value: RichEditorImageSpanStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSize  = value.size
        if (valueHolderForSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSizeTmpValue  = valueHolderForSize!
            const valueHolderForSizeTmpValue_0  = valueHolderForSizeTmpValue[0]
            if (valueHolderForSizeTmpValue_0 instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSizeTmpValue_0ForIdx0  = valueHolderForSizeTmpValue_0 as string
                valueSerializer.writeString(valueHolderForSizeTmpValue_0ForIdx0)
            } else if (valueHolderForSizeTmpValue_0 instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSizeTmpValue_0ForIdx1  = valueHolderForSizeTmpValue_0 as number
                valueSerializer.writeNumber(valueHolderForSizeTmpValue_0ForIdx1)
            } else if (valueHolderForSizeTmpValue_0 instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForSizeTmpValue_0ForIdx2  = valueHolderForSizeTmpValue_0 as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForSizeTmpValue_0ForIdx2)
            }
            const valueHolderForSizeTmpValue_1  = valueHolderForSizeTmpValue[1]
            if (valueHolderForSizeTmpValue_1 instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSizeTmpValue_1ForIdx0  = valueHolderForSizeTmpValue_1 as string
                valueSerializer.writeString(valueHolderForSizeTmpValue_1ForIdx0)
            } else if (valueHolderForSizeTmpValue_1 instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSizeTmpValue_1ForIdx1  = valueHolderForSizeTmpValue_1 as number
                valueSerializer.writeNumber(valueHolderForSizeTmpValue_1ForIdx1)
            } else if (valueHolderForSizeTmpValue_1 instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForSizeTmpValue_1ForIdx2  = valueHolderForSizeTmpValue_1 as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForSizeTmpValue_1ForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForVerticalAlign  = value.verticalAlign
        if (valueHolderForVerticalAlign !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForVerticalAlignTmpValue  = (valueHolderForVerticalAlign as ImageSpanAlignment)
            valueSerializer.writeInt32(valueHolderForVerticalAlignTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForObjectFit  = value.objectFit
        if (valueHolderForObjectFit !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForObjectFitTmpValue  = (valueHolderForObjectFit as ImageFit)
            valueSerializer.writeInt32(valueHolderForObjectFitTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLayoutStyle  = value.layoutStyle
        if (valueHolderForLayoutStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLayoutStyleTmpValue  = valueHolderForLayoutStyle!
            RichEditorLayoutStyle_serializer.write(valueSerializer, valueHolderForLayoutStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorImageSpanStyle {
        let valueDeserializer : DeserializerBase = buffer
        const sizeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let sizeTmpBuf : [ Dimension, Dimension ] | undefined = undefined
        if ((sizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const sizeTmpBufOptValue0TempBufUnionSelector : int32 = valueDeserializer.readInt8()
            let sizeTmpBufOptValue0TempBuf : string | number | global_resource_Resource | undefined
            if (sizeTmpBufOptValue0TempBufUnionSelector == (0).toByte()) {
                sizeTmpBufOptValue0TempBuf = (valueDeserializer.readString() as string)
            } else if (sizeTmpBufOptValue0TempBufUnionSelector == (1).toByte()) {
                sizeTmpBufOptValue0TempBuf = (valueDeserializer.readNumber() as number)
            } else if (sizeTmpBufOptValue0TempBufUnionSelector == (2).toByte()) {
                sizeTmpBufOptValue0TempBuf = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for sizeTmpBufOptValue0TempBuf has to be chosen through deserialisation.')
            }
            const sizeTmpBufOptValue0 : Dimension = (sizeTmpBufOptValue0TempBuf as string | number | global_resource_Resource)
            const sizeTmpBufOptValue1TempBufUnionSelector : int32 = valueDeserializer.readInt8()
            let sizeTmpBufOptValue1TempBuf : string | number | global_resource_Resource | undefined
            if (sizeTmpBufOptValue1TempBufUnionSelector == (0).toByte()) {
                sizeTmpBufOptValue1TempBuf = (valueDeserializer.readString() as string)
            } else if (sizeTmpBufOptValue1TempBufUnionSelector == (1).toByte()) {
                sizeTmpBufOptValue1TempBuf = (valueDeserializer.readNumber() as number)
            } else if (sizeTmpBufOptValue1TempBufUnionSelector == (2).toByte()) {
                sizeTmpBufOptValue1TempBuf = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for sizeTmpBufOptValue1TempBuf has to be chosen through deserialisation.')
            }
            const sizeTmpBufOptValue1 : Dimension = (sizeTmpBufOptValue1TempBuf as string | number | global_resource_Resource)
            sizeTmpBuf = ([sizeTmpBufOptValue0, sizeTmpBufOptValue1] as [ Dimension, Dimension ])
        }
        const sizeTmpResult : [ Dimension, Dimension ] | undefined = sizeTmpBuf
        const verticalAlignTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let verticalAlignTmpBuf : ImageSpanAlignment | undefined = undefined
        if ((verticalAlignTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            verticalAlignTmpBuf = ImageSpanAlignment.fromValue(valueDeserializer.readInt32())
        }
        const verticalAlignTmpResult : ImageSpanAlignment | undefined = verticalAlignTmpBuf
        const objectFitTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let objectFitTmpBuf : ImageFit | undefined = undefined
        if ((objectFitTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            objectFitTmpBuf = ImageFit.fromValue(valueDeserializer.readInt32())
        }
        const objectFitTmpResult : ImageFit | undefined = objectFitTmpBuf
        const layoutStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let layoutStyleTmpBuf : RichEditorLayoutStyle | undefined = undefined
        if ((layoutStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            layoutStyleTmpBuf = RichEditorLayoutStyle_serializer.read(valueDeserializer)
        }
        const layoutStyleTmpResult : RichEditorLayoutStyle | undefined = layoutStyleTmpBuf
        let value : RichEditorImageSpanStyle = ({size: sizeTmpResult, verticalAlign: verticalAlignTmpResult, objectFit: objectFitTmpResult, layoutStyle: layoutStyleTmpResult} as RichEditorImageSpanStyle)
        return value
    }
}
export class RichEditorImageSpanStyleResult_serializer {
    public static write(buffer: SerializerBase, value: RichEditorImageSpanStyleResult): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSize  = value.size
        const valueHolderForSize_0  = valueHolderForSize[0]
        valueSerializer.writeInt32(valueHolderForSize_0)
        const valueHolderForSize_1  = valueHolderForSize[1]
        valueSerializer.writeInt32(valueHolderForSize_1)
        const valueHolderForVerticalAlign  = value.verticalAlign
        valueSerializer.writeInt32(valueHolderForVerticalAlign.valueOf())
        const valueHolderForObjectFit  = value.objectFit
        valueSerializer.writeInt32(valueHolderForObjectFit.valueOf())
        const valueHolderForLayoutStyle  = value.layoutStyle
        if (valueHolderForLayoutStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLayoutStyleTmpValue  = valueHolderForLayoutStyle!
            RichEditorLayoutStyle_serializer.write(valueSerializer, valueHolderForLayoutStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorImageSpanStyleResult {
        let valueDeserializer : DeserializerBase = buffer
        const sizeTmpBufValue0 : int32 = valueDeserializer.readInt32()
        const sizeTmpBufValue1 : int32 = valueDeserializer.readInt32()
        const sizeTmpResult : [ int32, int32 ] = ([sizeTmpBufValue0, sizeTmpBufValue1] as [ int32, int32 ])
        const verticalAlignTmpResult : ImageSpanAlignment = ImageSpanAlignment.fromValue(valueDeserializer.readInt32())
        const objectFitTmpResult : ImageFit = ImageFit.fromValue(valueDeserializer.readInt32())
        const layoutStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let layoutStyleTmpBuf : RichEditorLayoutStyle | undefined = undefined
        if ((layoutStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            layoutStyleTmpBuf = RichEditorLayoutStyle_serializer.read(valueDeserializer)
        }
        const layoutStyleTmpResult : RichEditorLayoutStyle | undefined = layoutStyleTmpBuf
        let value : RichEditorImageSpanStyleResult = ({size: sizeTmpResult, verticalAlign: verticalAlignTmpResult, objectFit: objectFitTmpResult, layoutStyle: layoutStyleTmpResult} as RichEditorImageSpanStyleResult)
        return value
    }
}
export class RichEditorParagraphResult_serializer {
    public static write(buffer: SerializerBase, value: RichEditorParagraphResult): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStyle  = value.style
        RichEditorParagraphStyle_serializer.write(valueSerializer, valueHolderForStyle)
        const valueHolderForRange  = value.range
        const valueHolderForRange_0  = valueHolderForRange[0]
        valueSerializer.writeInt32(valueHolderForRange_0)
        const valueHolderForRange_1  = valueHolderForRange[1]
        valueSerializer.writeInt32(valueHolderForRange_1)
    }
    public static read(buffer: DeserializerBase): RichEditorParagraphResult {
        let valueDeserializer : DeserializerBase = buffer
        const styleTmpResult : RichEditorParagraphStyle = RichEditorParagraphStyle_serializer.read(valueDeserializer)
        const rangeTmpBufValue0 : int32 = valueDeserializer.readInt32()
        const rangeTmpBufValue1 : int32 = valueDeserializer.readInt32()
        const rangeTmpResult : [ int32, int32 ] = ([rangeTmpBufValue0, rangeTmpBufValue1] as [ int32, int32 ])
        let value : RichEditorParagraphResult = ({style: styleTmpResult, range: rangeTmpResult} as RichEditorParagraphResult)
        return value
    }
}
export class RichEditorTextStyle_serializer {
    public static write(buffer: SerializerBase, value: RichEditorTextStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForFontColor  = value.fontColor
        if (valueHolderForFontColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontColorTmpValue  = valueHolderForFontColor!
            if (valueHolderForFontColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForFontColorTmpValueForIdx0  = valueHolderForFontColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForFontColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForFontColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForFontColorTmpValueForIdx1  = valueHolderForFontColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForFontColorTmpValueForIdx1)
            } else if (valueHolderForFontColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForFontColorTmpValueForIdx2  = valueHolderForFontColorTmpValue as string
                valueSerializer.writeString(valueHolderForFontColorTmpValueForIdx2)
            } else if (valueHolderForFontColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForFontColorTmpValueForIdx3  = valueHolderForFontColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForFontColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontSize  = value.fontSize
        if (valueHolderForFontSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontSizeTmpValue  = valueHolderForFontSize!
            if (valueHolderForFontSizeTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForFontSizeTmpValueForIdx0  = valueHolderForFontSizeTmpValue as string
                valueSerializer.writeString(valueHolderForFontSizeTmpValueForIdx0)
            } else if (valueHolderForFontSizeTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForFontSizeTmpValueForIdx1  = valueHolderForFontSizeTmpValue as double
                valueSerializer.writeFloat64(valueHolderForFontSizeTmpValueForIdx1)
            } else if (valueHolderForFontSizeTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForFontSizeTmpValueForIdx2  = valueHolderForFontSizeTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForFontSizeTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontStyle  = value.fontStyle
        if (valueHolderForFontStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontStyleTmpValue  = (valueHolderForFontStyle as FontStyle)
            valueSerializer.writeInt32(valueHolderForFontStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontWeight  = value.fontWeight
        if (valueHolderForFontWeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontWeightTmpValue  = valueHolderForFontWeight!
            if (valueHolderForFontWeightTmpValue instanceof int32) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForFontWeightTmpValueForIdx0  = valueHolderForFontWeightTmpValue as int32
                valueSerializer.writeInt32(valueHolderForFontWeightTmpValueForIdx0)
            } else if (valueHolderForFontWeightTmpValue instanceof FontWeight) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForFontWeightTmpValueForIdx1  = valueHolderForFontWeightTmpValue as FontWeight
                valueSerializer.writeInt32(valueHolderForFontWeightTmpValueForIdx1.valueOf())
            } else if (valueHolderForFontWeightTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForFontWeightTmpValueForIdx2  = valueHolderForFontWeightTmpValue as string
                valueSerializer.writeString(valueHolderForFontWeightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontFamily  = value.fontFamily
        if (valueHolderForFontFamily !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontFamilyTmpValue  = valueHolderForFontFamily!
            if (valueHolderForFontFamilyTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForFontFamilyTmpValueForIdx0  = valueHolderForFontFamilyTmpValue as string
                valueSerializer.writeString(valueHolderForFontFamilyTmpValueForIdx0)
            } else if (valueHolderForFontFamilyTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForFontFamilyTmpValueForIdx1  = valueHolderForFontFamilyTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForFontFamilyTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDecoration  = value.decoration
        if (valueHolderForDecoration !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDecorationTmpValue  = valueHolderForDecoration!
            DecorationStyleInterface_serializer.write(valueSerializer, valueHolderForDecorationTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTextShadow  = value.textShadow
        if (valueHolderForTextShadow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextShadowTmpValue  = valueHolderForTextShadow!
            if (valueHolderForTextShadowTmpValue instanceof ShadowOptions) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForTextShadowTmpValueForIdx0  = valueHolderForTextShadowTmpValue as ShadowOptions
                ShadowOptions_serializer.write(valueSerializer, valueHolderForTextShadowTmpValueForIdx0)
            } else if (valueHolderForTextShadowTmpValue instanceof Array) {
                if (valueHolderForTextShadowTmpValue.length == 0) {
                    valueSerializer.writeInt8((1).toByte())
                    valueSerializer.writeInt32(0)
                } else {
                    const valueHolderForTextShadowTmpValueElem  = valueHolderForTextShadowTmpValue[0]
                    if (valueHolderForTextShadowTmpValueElem instanceof ShadowOptions) {
                        valueSerializer.writeInt8((1).toByte())
                        const valueHolderForTextShadowTmpValueForIdx1  = valueHolderForTextShadowTmpValue as Array<ShadowOptions>
                        valueSerializer.writeInt32((valueHolderForTextShadowTmpValueForIdx1.length).toInt())
                        for (let valueHolderForTextShadowTmpValueForIdx1CounterI = 0; valueHolderForTextShadowTmpValueForIdx1CounterI < valueHolderForTextShadowTmpValueForIdx1.length; valueHolderForTextShadowTmpValueForIdx1CounterI++) {
                            const valueHolderForTextShadowTmpValueForIdx1TmpElement : ShadowOptions = valueHolderForTextShadowTmpValueForIdx1[valueHolderForTextShadowTmpValueForIdx1CounterI]
                            ShadowOptions_serializer.write(valueSerializer, valueHolderForTextShadowTmpValueForIdx1TmpElement)
                        }
                    }
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLetterSpacing  = value.letterSpacing
        if (valueHolderForLetterSpacing !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLetterSpacingTmpValue  = valueHolderForLetterSpacing!
            if (valueHolderForLetterSpacingTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForLetterSpacingTmpValueForIdx0  = valueHolderForLetterSpacingTmpValue as double
                valueSerializer.writeFloat64(valueHolderForLetterSpacingTmpValueForIdx0)
            } else if (valueHolderForLetterSpacingTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForLetterSpacingTmpValueForIdx1  = valueHolderForLetterSpacingTmpValue as string
                valueSerializer.writeString(valueHolderForLetterSpacingTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLineHeight  = value.lineHeight
        if (valueHolderForLineHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLineHeightTmpValue  = valueHolderForLineHeight!
            if (valueHolderForLineHeightTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForLineHeightTmpValueForIdx0  = valueHolderForLineHeightTmpValue as double
                valueSerializer.writeFloat64(valueHolderForLineHeightTmpValueForIdx0)
            } else if (valueHolderForLineHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForLineHeightTmpValueForIdx1  = valueHolderForLineHeightTmpValue as string
                valueSerializer.writeString(valueHolderForLineHeightTmpValueForIdx1)
            } else if (valueHolderForLineHeightTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForLineHeightTmpValueForIdx2  = valueHolderForLineHeightTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForLineHeightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHalfLeading  = value.halfLeading
        if (valueHolderForHalfLeading !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHalfLeadingTmpValue  = valueHolderForHalfLeading!
            valueSerializer.writeBoolean(valueHolderForHalfLeadingTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontFeature  = value.fontFeature
        if (valueHolderForFontFeature !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontFeatureTmpValue  = valueHolderForFontFeature!
            valueSerializer.writeString(valueHolderForFontFeatureTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTextBackgroundStyle  = value.textBackgroundStyle
        if (valueHolderForTextBackgroundStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextBackgroundStyleTmpValue  = valueHolderForTextBackgroundStyle!
            TextBackgroundStyle_serializer.write(valueSerializer, valueHolderForTextBackgroundStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorTextStyle {
        let valueDeserializer : DeserializerBase = buffer
        const fontColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontColorTmpBuf : ResourceColor | undefined = undefined
        if ((fontColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontColorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let fontColorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (fontColorTmpBufOptUnionSelector == (0).toByte()) {
                fontColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (fontColorTmpBufOptUnionSelector == (1).toByte()) {
                fontColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (fontColorTmpBufOptUnionSelector == (2).toByte()) {
                fontColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (fontColorTmpBufOptUnionSelector == (3).toByte()) {
                fontColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for fontColorTmpBufOpt has to be chosen through deserialisation.')
            }
            fontColorTmpBuf = (fontColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const fontColorTmpResult : ResourceColor | undefined = fontColorTmpBuf
        const fontSizeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontSizeTmpBuf : string | double | arkui_component_units_Resource | undefined = undefined
        if ((fontSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontSizeTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let fontSizeTmpBufOpt : string | double | arkui_component_units_Resource | undefined
            if (fontSizeTmpBufOptUnionSelector == (0).toByte()) {
                fontSizeTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (fontSizeTmpBufOptUnionSelector == (1).toByte()) {
                fontSizeTmpBufOpt = valueDeserializer.readFloat64()
            } else if (fontSizeTmpBufOptUnionSelector == (2).toByte()) {
                fontSizeTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for fontSizeTmpBufOpt has to be chosen through deserialisation.')
            }
            fontSizeTmpBuf = (fontSizeTmpBufOpt as string | double | arkui_component_units_Resource)
        }
        const fontSizeTmpResult : Length | double | undefined = fontSizeTmpBuf
        const fontStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontStyleTmpBuf : FontStyle | undefined = undefined
        if ((fontStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fontStyleTmpBuf = FontStyle.fromValue(valueDeserializer.readInt32())
        }
        const fontStyleTmpResult : FontStyle | undefined = fontStyleTmpBuf
        const fontWeightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontWeightTmpBuf : int32 | FontWeight | string | undefined = undefined
        if ((fontWeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontWeightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let fontWeightTmpBufOpt : int32 | FontWeight | string | undefined
            if (fontWeightTmpBufOptUnionSelector == (0).toByte()) {
                fontWeightTmpBufOpt = valueDeserializer.readInt32()
            } else if (fontWeightTmpBufOptUnionSelector == (1).toByte()) {
                fontWeightTmpBufOpt = FontWeight.fromValue(valueDeserializer.readInt32())
            } else if (fontWeightTmpBufOptUnionSelector == (2).toByte()) {
                fontWeightTmpBufOpt = (valueDeserializer.readString() as string)
            } else {
                throw new Error('One of the branches for fontWeightTmpBufOpt has to be chosen through deserialisation.')
            }
            fontWeightTmpBuf = (fontWeightTmpBufOpt as int32 | FontWeight | string)
        }
        const fontWeightTmpResult : int32 | FontWeight | string | undefined = fontWeightTmpBuf
        const fontFamilyTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontFamilyTmpBuf : arkui_component_units_ResourceStr | undefined = undefined
        if ((fontFamilyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const fontFamilyTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let fontFamilyTmpBufOpt : string | arkui_component_units_Resource | undefined
            if (fontFamilyTmpBufOptUnionSelector == (0).toByte()) {
                fontFamilyTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (fontFamilyTmpBufOptUnionSelector == (1).toByte()) {
                fontFamilyTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for fontFamilyTmpBufOpt has to be chosen through deserialisation.')
            }
            fontFamilyTmpBuf = (fontFamilyTmpBufOpt as string | arkui_component_units_Resource)
        }
        const fontFamilyTmpResult : arkui_component_units_ResourceStr | undefined = fontFamilyTmpBuf
        const decorationTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let decorationTmpBuf : DecorationStyleInterface | undefined = undefined
        if ((decorationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            decorationTmpBuf = DecorationStyleInterface_serializer.read(valueDeserializer)
        }
        const decorationTmpResult : DecorationStyleInterface | undefined = decorationTmpBuf
        const textShadowTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let textShadowTmpBuf : ShadowOptions | Array<ShadowOptions> | undefined = undefined
        if ((textShadowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const textShadowTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let textShadowTmpBufOpt : ShadowOptions | Array<ShadowOptions> | undefined
            if (textShadowTmpBufOptUnionSelector == (0).toByte()) {
                textShadowTmpBufOpt = ShadowOptions_serializer.read(valueDeserializer)
            } else if (textShadowTmpBufOptUnionSelector == (1).toByte()) {
                const textShadowTmpBufOptBufULength : int32 = valueDeserializer.readInt32()
                let textShadowTmpBufOptBufU : Array<ShadowOptions> = new Array<ShadowOptions>(textShadowTmpBufOptBufULength)
                for (let textShadowTmpBufOptBufUBufCounterI = 0; textShadowTmpBufOptBufUBufCounterI < textShadowTmpBufOptBufULength; textShadowTmpBufOptBufUBufCounterI++) {
                    textShadowTmpBufOptBufU[textShadowTmpBufOptBufUBufCounterI] = ShadowOptions_serializer.read(valueDeserializer)
                }
                textShadowTmpBufOpt = textShadowTmpBufOptBufU
            } else {
                throw new Error('One of the branches for textShadowTmpBufOpt has to be chosen through deserialisation.')
            }
            textShadowTmpBuf = (textShadowTmpBufOpt as ShadowOptions | Array<ShadowOptions>)
        }
        const textShadowTmpResult : ShadowOptions | Array<ShadowOptions> | undefined = textShadowTmpBuf
        const letterSpacingTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let letterSpacingTmpBuf : double | string | undefined = undefined
        if ((letterSpacingTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const letterSpacingTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let letterSpacingTmpBufOpt : double | string | undefined
            if (letterSpacingTmpBufOptUnionSelector == (0).toByte()) {
                letterSpacingTmpBufOpt = valueDeserializer.readFloat64()
            } else if (letterSpacingTmpBufOptUnionSelector == (1).toByte()) {
                letterSpacingTmpBufOpt = (valueDeserializer.readString() as string)
            } else {
                throw new Error('One of the branches for letterSpacingTmpBufOpt has to be chosen through deserialisation.')
            }
            letterSpacingTmpBuf = (letterSpacingTmpBufOpt as double | string)
        }
        const letterSpacingTmpResult : double | string | undefined = letterSpacingTmpBuf
        const lineHeightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let lineHeightTmpBuf : double | string | global_resource_Resource | undefined = undefined
        if ((lineHeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const lineHeightTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let lineHeightTmpBufOpt : double | string | global_resource_Resource | undefined
            if (lineHeightTmpBufOptUnionSelector == (0).toByte()) {
                lineHeightTmpBufOpt = valueDeserializer.readFloat64()
            } else if (lineHeightTmpBufOptUnionSelector == (1).toByte()) {
                lineHeightTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (lineHeightTmpBufOptUnionSelector == (2).toByte()) {
                lineHeightTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for lineHeightTmpBufOpt has to be chosen through deserialisation.')
            }
            lineHeightTmpBuf = (lineHeightTmpBufOpt as double | string | global_resource_Resource)
        }
        const lineHeightTmpResult : double | string | global_resource_Resource | undefined = lineHeightTmpBuf
        const halfLeadingTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let halfLeadingTmpBuf : boolean | undefined = undefined
        if ((halfLeadingTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            halfLeadingTmpBuf = valueDeserializer.readBoolean()
        }
        const halfLeadingTmpResult : boolean | undefined = halfLeadingTmpBuf
        const fontFeatureTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontFeatureTmpBuf : string | undefined = undefined
        if ((fontFeatureTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fontFeatureTmpBuf = (valueDeserializer.readString() as string)
        }
        const fontFeatureTmpResult : string | undefined = fontFeatureTmpBuf
        const textBackgroundStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let textBackgroundStyleTmpBuf : TextBackgroundStyle | undefined = undefined
        if ((textBackgroundStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            textBackgroundStyleTmpBuf = TextBackgroundStyle_serializer.read(valueDeserializer)
        }
        const textBackgroundStyleTmpResult : TextBackgroundStyle | undefined = textBackgroundStyleTmpBuf
        let value : RichEditorTextStyle = ({fontColor: fontColorTmpResult, fontSize: fontSizeTmpResult, fontStyle: fontStyleTmpResult, fontWeight: fontWeightTmpResult, fontFamily: fontFamilyTmpResult, decoration: decorationTmpResult, textShadow: textShadowTmpResult, letterSpacing: letterSpacingTmpResult, lineHeight: lineHeightTmpResult, halfLeading: halfLeadingTmpResult, fontFeature: fontFeatureTmpResult, textBackgroundStyle: textBackgroundStyleTmpResult} as RichEditorTextStyle)
        return value
    }
}
export class RichEditorTextStyleResult_serializer {
    public static write(buffer: SerializerBase, value: RichEditorTextStyleResult): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForFontColor  = value.fontColor
        if (valueHolderForFontColor instanceof arkui_component_enums_Color) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForFontColorForIdx0  = valueHolderForFontColor as arkui_component_enums_Color
            valueSerializer.writeInt32((valueHolderForFontColorForIdx0.getOrdinal()) % (12))
        } else if (valueHolderForFontColor instanceof int32) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForFontColorForIdx1  = valueHolderForFontColor as int32
            valueSerializer.writeInt32(valueHolderForFontColorForIdx1)
        } else if (valueHolderForFontColor instanceof string) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForFontColorForIdx2  = valueHolderForFontColor as string
            valueSerializer.writeString(valueHolderForFontColorForIdx2)
        } else if (valueHolderForFontColor instanceof arkui_component_units_Resource) {
            valueSerializer.writeInt8((3).toByte())
            const valueHolderForFontColorForIdx3  = valueHolderForFontColor as arkui_component_units_Resource
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForFontColorForIdx3)
        }
        const valueHolderForFontSize  = value.fontSize
        valueSerializer.writeFloat64(valueHolderForFontSize)
        const valueHolderForFontStyle  = value.fontStyle
        valueSerializer.writeInt32(valueHolderForFontStyle.valueOf())
        const valueHolderForFontWeight  = value.fontWeight
        valueSerializer.writeInt32(valueHolderForFontWeight)
        const valueHolderForFontFamily  = value.fontFamily
        valueSerializer.writeString(valueHolderForFontFamily)
        const valueHolderForDecoration  = value.decoration
        DecorationStyleResult_serializer.write(valueSerializer, valueHolderForDecoration)
        const valueHolderForTextShadow  = value.textShadow
        if (valueHolderForTextShadow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextShadowTmpValue  = valueHolderForTextShadow!
            valueSerializer.writeInt32((valueHolderForTextShadowTmpValue.length).toInt())
            for (let valueHolderForTextShadowTmpValueCounterI = 0; valueHolderForTextShadowTmpValueCounterI < valueHolderForTextShadowTmpValue.length; valueHolderForTextShadowTmpValueCounterI++) {
                const valueHolderForTextShadowTmpValueTmpElement : ShadowOptions = valueHolderForTextShadowTmpValue[valueHolderForTextShadowTmpValueCounterI]
                ShadowOptions_serializer.write(valueSerializer, valueHolderForTextShadowTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLetterSpacing  = value.letterSpacing
        if (valueHolderForLetterSpacing !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLetterSpacingTmpValue  = valueHolderForLetterSpacing!
            valueSerializer.writeFloat64(valueHolderForLetterSpacingTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLineHeight  = value.lineHeight
        if (valueHolderForLineHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLineHeightTmpValue  = valueHolderForLineHeight!
            valueSerializer.writeFloat64(valueHolderForLineHeightTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHalfLeading  = value.halfLeading
        if (valueHolderForHalfLeading !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHalfLeadingTmpValue  = valueHolderForHalfLeading!
            valueSerializer.writeBoolean(valueHolderForHalfLeadingTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFontFeature  = value.fontFeature
        if (valueHolderForFontFeature !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontFeatureTmpValue  = valueHolderForFontFeature!
            valueSerializer.writeString(valueHolderForFontFeatureTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTextBackgroundStyle  = value.textBackgroundStyle
        if (valueHolderForTextBackgroundStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTextBackgroundStyleTmpValue  = valueHolderForTextBackgroundStyle!
            TextBackgroundStyle_serializer.write(valueSerializer, valueHolderForTextBackgroundStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorTextStyleResult {
        let valueDeserializer : DeserializerBase = buffer
        const fontColorTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let fontColorTmpBuf : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
        if (fontColorTmpBufUnionSelector == (0).toByte()) {
            fontColorTmpBuf = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
        } else if (fontColorTmpBufUnionSelector == (1).toByte()) {
            fontColorTmpBuf = valueDeserializer.readInt32()
        } else if (fontColorTmpBufUnionSelector == (2).toByte()) {
            fontColorTmpBuf = (valueDeserializer.readString() as string)
        } else if (fontColorTmpBufUnionSelector == (3).toByte()) {
            fontColorTmpBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for fontColorTmpBuf has to be chosen through deserialisation.')
        }
        const fontColorTmpResult : ResourceColor = (fontColorTmpBuf as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        const fontSizeTmpResult : double = valueDeserializer.readFloat64()
        const fontStyleTmpResult : FontStyle = FontStyle.fromValue(valueDeserializer.readInt32())
        const fontWeightTmpResult : int32 = valueDeserializer.readInt32()
        const fontFamilyTmpResult : string = (valueDeserializer.readString() as string)
        const decorationTmpResult : DecorationStyleResult = DecorationStyleResult_serializer.read(valueDeserializer)
        const textShadowTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let textShadowTmpBuf : Array<ShadowOptions> | undefined = undefined
        if ((textShadowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const textShadowTmpBufOptLength : int32 = valueDeserializer.readInt32()
            let textShadowTmpBufOpt : Array<ShadowOptions> = new Array<ShadowOptions>(textShadowTmpBufOptLength)
            for (let textShadowTmpBufOptBufCounterI = 0; textShadowTmpBufOptBufCounterI < textShadowTmpBufOptLength; textShadowTmpBufOptBufCounterI++) {
                textShadowTmpBufOpt[textShadowTmpBufOptBufCounterI] = ShadowOptions_serializer.read(valueDeserializer)
            }
            textShadowTmpBuf = textShadowTmpBufOpt
        }
        const textShadowTmpResult : Array<ShadowOptions> | undefined = textShadowTmpBuf
        const letterSpacingTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let letterSpacingTmpBuf : double | undefined = undefined
        if ((letterSpacingTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            letterSpacingTmpBuf = valueDeserializer.readFloat64()
        }
        const letterSpacingTmpResult : double | undefined = letterSpacingTmpBuf
        const lineHeightTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let lineHeightTmpBuf : double | undefined = undefined
        if ((lineHeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            lineHeightTmpBuf = valueDeserializer.readFloat64()
        }
        const lineHeightTmpResult : double | undefined = lineHeightTmpBuf
        const halfLeadingTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let halfLeadingTmpBuf : boolean | undefined = undefined
        if ((halfLeadingTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            halfLeadingTmpBuf = valueDeserializer.readBoolean()
        }
        const halfLeadingTmpResult : boolean | undefined = halfLeadingTmpBuf
        const fontFeatureTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fontFeatureTmpBuf : string | undefined = undefined
        if ((fontFeatureTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fontFeatureTmpBuf = (valueDeserializer.readString() as string)
        }
        const fontFeatureTmpResult : string | undefined = fontFeatureTmpBuf
        const textBackgroundStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let textBackgroundStyleTmpBuf : TextBackgroundStyle | undefined = undefined
        if ((textBackgroundStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            textBackgroundStyleTmpBuf = TextBackgroundStyle_serializer.read(valueDeserializer)
        }
        const textBackgroundStyleTmpResult : TextBackgroundStyle | undefined = textBackgroundStyleTmpBuf
        let value : RichEditorTextStyleResult = ({fontColor: fontColorTmpResult, fontSize: fontSizeTmpResult, fontStyle: fontStyleTmpResult, fontWeight: fontWeightTmpResult, fontFamily: fontFamilyTmpResult, decoration: decorationTmpResult, textShadow: textShadowTmpResult, letterSpacing: letterSpacingTmpResult, lineHeight: lineHeightTmpResult, halfLeading: halfLeadingTmpResult, fontFeature: fontFeatureTmpResult, textBackgroundStyle: textBackgroundStyleTmpResult} as RichEditorTextStyleResult)
        return value
    }
}
export class RichEditorUpdateImageSpanStyleOptions_serializer {
    public static write(buffer: SerializerBase, value: RichEditorUpdateImageSpanStyleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStart  = value.start
        if (valueHolderForStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartTmpValue  = valueHolderForStart!
            valueSerializer.writeInt32(valueHolderForStartTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnd  = value.end
        if (valueHolderForEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndTmpValue  = valueHolderForEnd!
            valueSerializer.writeInt32(valueHolderForEndTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForImageStyle  = value.imageStyle
        RichEditorImageSpanStyle_serializer.write(valueSerializer, valueHolderForImageStyle)
    }
    public static read(buffer: DeserializerBase): RichEditorUpdateImageSpanStyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let startTmpBuf : int32 | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startTmpBuf = valueDeserializer.readInt32()
        }
        const startTmpResult : int32 | undefined = startTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let endTmpBuf : int32 | undefined = undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endTmpBuf = valueDeserializer.readInt32()
        }
        const endTmpResult : int32 | undefined = endTmpBuf
        const imageStyleTmpResult : RichEditorImageSpanStyle = RichEditorImageSpanStyle_serializer.read(valueDeserializer)
        let value : RichEditorUpdateImageSpanStyleOptions = ({start: startTmpResult, end: endTmpResult, imageStyle: imageStyleTmpResult} as RichEditorUpdateImageSpanStyleOptions)
        return value
    }
}
export class RichEditorUpdateTextSpanStyleOptions_serializer {
    public static write(buffer: SerializerBase, value: RichEditorUpdateTextSpanStyleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStart  = value.start
        if (valueHolderForStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartTmpValue  = valueHolderForStart!
            valueSerializer.writeInt32(valueHolderForStartTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnd  = value.end
        if (valueHolderForEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndTmpValue  = valueHolderForEnd!
            valueSerializer.writeInt32(valueHolderForEndTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTextStyle  = value.textStyle
        RichEditorTextStyle_serializer.write(valueSerializer, valueHolderForTextStyle)
        const valueHolderForUrlStyle  = value.urlStyle
        if (valueHolderForUrlStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUrlStyleTmpValue  = valueHolderForUrlStyle!
            RichEditorUrlStyle_serializer.write(valueSerializer, valueHolderForUrlStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorUpdateTextSpanStyleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let startTmpBuf : int32 | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startTmpBuf = valueDeserializer.readInt32()
        }
        const startTmpResult : int32 | undefined = startTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let endTmpBuf : int32 | undefined = undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endTmpBuf = valueDeserializer.readInt32()
        }
        const endTmpResult : int32 | undefined = endTmpBuf
        const textStyleTmpResult : RichEditorTextStyle = RichEditorTextStyle_serializer.read(valueDeserializer)
        const urlStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let urlStyleTmpBuf : RichEditorUrlStyle | undefined = undefined
        if ((urlStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            urlStyleTmpBuf = RichEditorUrlStyle_serializer.read(valueDeserializer)
        }
        const urlStyleTmpResult : RichEditorUrlStyle | undefined = urlStyleTmpBuf
        let value : RichEditorUpdateTextSpanStyleOptions = ({start: startTmpResult, end: endTmpResult, textStyle: textStyleTmpResult, urlStyle: urlStyleTmpResult} as RichEditorUpdateTextSpanStyleOptions)
        return value
    }
}
export class RichEditorImageSpanOptions_serializer {
    public static write(buffer: SerializerBase, value: RichEditorImageSpanOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForOffset  = value.offset
        if (valueHolderForOffset !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOffsetTmpValue  = valueHolderForOffset!
            valueSerializer.writeInt32(valueHolderForOffsetTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForImageStyle  = value.imageStyle
        if (valueHolderForImageStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForImageStyleTmpValue  = valueHolderForImageStyle!
            RichEditorImageSpanStyle_serializer.write(valueSerializer, valueHolderForImageStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForGesture  = value.gesture
        if (valueHolderForGesture !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForGestureTmpValue  = valueHolderForGesture!
            RichEditorGesture_serializer.write(valueSerializer, valueHolderForGestureTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnHover  = value.onHover
        if (valueHolderForOnHover !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnHoverTmpValue  = valueHolderForOnHover!
            valueSerializer.holdAndWriteCallback(valueHolderForOnHoverTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorImageSpanOptions {
        let valueDeserializer : DeserializerBase = buffer
        const offsetTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let offsetTmpBuf : int32 | undefined = undefined
        if ((offsetTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            offsetTmpBuf = valueDeserializer.readInt32()
        }
        const offsetTmpResult : int32 | undefined = offsetTmpBuf
        const imageStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let imageStyleTmpBuf : RichEditorImageSpanStyle | undefined = undefined
        if ((imageStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            imageStyleTmpBuf = RichEditorImageSpanStyle_serializer.read(valueDeserializer)
        }
        const imageStyleTmpResult : RichEditorImageSpanStyle | undefined = imageStyleTmpBuf
        const gestureTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let gestureTmpBuf : RichEditorGesture | undefined = undefined
        if ((gestureTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            gestureTmpBuf = RichEditorGesture_serializer.read(valueDeserializer)
        }
        const gestureTmpResult : RichEditorGesture | undefined = gestureTmpBuf
        const onHoverTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let onHoverTmpBuf : OnHoverCallback | undefined = undefined
        if ((onHoverTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onHoverTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onHoverTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const onHoverTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const onHoverTmpBufOptClosure  = (status: boolean, event: HoverEvent):void => {
                const onHoverTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                onHoverTmpBufOptBufArgsSerializer.writeInt32(onHoverTmpBufOptBufResource.resourceId);
                onHoverTmpBufOptBufArgsSerializer.writePointer(onHoverTmpBufOptBufCall);
                onHoverTmpBufOptBufArgsSerializer.writePointer(onHoverTmpBufOptBufCallSync);
                onHoverTmpBufOptBufArgsSerializer.writeBoolean(status);
                HoverEvent_serializer.write(onHoverTmpBufOptBufArgsSerializer, event);
                InteropNativeModule._CallCallbackSync(10, 863132124, onHoverTmpBufOptBufArgsSerializer.asBuffer(), onHoverTmpBufOptBufArgsSerializer.length());
                onHoverTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onHoverTmpBufOptClosure, onHoverTmpBufOptBufResource)
            onHoverTmpBuf = onHoverTmpBufOptClosure
        }
        const onHoverTmpResult : OnHoverCallback | undefined = onHoverTmpBuf
        let value : RichEditorImageSpanOptions = ({offset: offsetTmpResult, imageStyle: imageStyleTmpResult, gesture: gestureTmpResult, onHover: onHoverTmpResult} as RichEditorImageSpanOptions)
        return value
    }
}
export class RichEditorImageSpanResult_serializer {
    public static write(buffer: SerializerBase, value: RichEditorImageSpanResult): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSpanPosition  = value.spanPosition
        RichEditorSpanPosition_serializer.write(valueSerializer, valueHolderForSpanPosition)
        const valueHolderForValuePixelMap  = value.valuePixelMap
        if (valueHolderForValuePixelMap !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForValuePixelMapTmpValue  = valueHolderForValuePixelMap!
            image_PixelMap_serializer.write(valueSerializer, valueHolderForValuePixelMapTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForValueResourceStr  = value.valueResourceStr
        if (valueHolderForValueResourceStr !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForValueResourceStrTmpValue  = valueHolderForValueResourceStr!
            if (valueHolderForValueResourceStrTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForValueResourceStrTmpValueForIdx0  = valueHolderForValueResourceStrTmpValue as string
                valueSerializer.writeString(valueHolderForValueResourceStrTmpValueForIdx0)
            } else if (valueHolderForValueResourceStrTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForValueResourceStrTmpValueForIdx1  = valueHolderForValueResourceStrTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForValueResourceStrTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForImageStyle  = value.imageStyle
        RichEditorImageSpanStyleResult_serializer.write(valueSerializer, valueHolderForImageStyle)
        const valueHolderForOffsetInSpan  = value.offsetInSpan
        const valueHolderForOffsetInSpan_0  = valueHolderForOffsetInSpan[0]
        valueSerializer.writeInt32(valueHolderForOffsetInSpan_0)
        const valueHolderForOffsetInSpan_1  = valueHolderForOffsetInSpan[1]
        valueSerializer.writeInt32(valueHolderForOffsetInSpan_1)
    }
    public static read(buffer: DeserializerBase): RichEditorImageSpanResult {
        let valueDeserializer : DeserializerBase = buffer
        const spanPositionTmpResult : RichEditorSpanPosition = RichEditorSpanPosition_serializer.read(valueDeserializer)
        const valuePixelMapTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let valuePixelMapTmpBuf : PixelMap | undefined = undefined
        if ((valuePixelMapTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            valuePixelMapTmpBuf = (image_PixelMap_serializer.read(valueDeserializer) as image.PixelMap)
        }
        const valuePixelMapTmpResult : PixelMap | undefined = valuePixelMapTmpBuf
        const valueResourceStrTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let valueResourceStrTmpBuf : arkui_component_units_ResourceStr | undefined = undefined
        if ((valueResourceStrTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const valueResourceStrTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let valueResourceStrTmpBufOpt : string | arkui_component_units_Resource | undefined
            if (valueResourceStrTmpBufOptUnionSelector == (0).toByte()) {
                valueResourceStrTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (valueResourceStrTmpBufOptUnionSelector == (1).toByte()) {
                valueResourceStrTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for valueResourceStrTmpBufOpt has to be chosen through deserialisation.')
            }
            valueResourceStrTmpBuf = (valueResourceStrTmpBufOpt as string | arkui_component_units_Resource)
        }
        const valueResourceStrTmpResult : arkui_component_units_ResourceStr | undefined = valueResourceStrTmpBuf
        const imageStyleTmpResult : RichEditorImageSpanStyleResult = RichEditorImageSpanStyleResult_serializer.read(valueDeserializer)
        const offsetInSpanTmpBufValue0 : int32 = valueDeserializer.readInt32()
        const offsetInSpanTmpBufValue1 : int32 = valueDeserializer.readInt32()
        const offsetInSpanTmpResult : [ int32, int32 ] = ([offsetInSpanTmpBufValue0, offsetInSpanTmpBufValue1] as [ int32, int32 ])
        let value : RichEditorImageSpanResult = ({spanPosition: spanPositionTmpResult, valuePixelMap: valuePixelMapTmpResult, valueResourceStr: valueResourceStrTmpResult, imageStyle: imageStyleTmpResult, offsetInSpan: offsetInSpanTmpResult} as RichEditorImageSpanResult)
        return value
    }
}
export class RichEditorTextSpanOptions_serializer {
    public static write(buffer: SerializerBase, value: RichEditorTextSpanOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForOffset  = value.offset
        if (valueHolderForOffset !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOffsetTmpValue  = valueHolderForOffset!
            valueSerializer.writeInt32(valueHolderForOffsetTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStyle  = value.style
        if (valueHolderForStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStyleTmpValue  = valueHolderForStyle!
            RichEditorTextStyle_serializer.write(valueSerializer, valueHolderForStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForParagraphStyle  = value.paragraphStyle
        if (valueHolderForParagraphStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForParagraphStyleTmpValue  = valueHolderForParagraphStyle!
            RichEditorParagraphStyle_serializer.write(valueSerializer, valueHolderForParagraphStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForGesture  = value.gesture
        if (valueHolderForGesture !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForGestureTmpValue  = valueHolderForGesture!
            RichEditorGesture_serializer.write(valueSerializer, valueHolderForGestureTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForUrlStyle  = value.urlStyle
        if (valueHolderForUrlStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUrlStyleTmpValue  = valueHolderForUrlStyle!
            RichEditorUrlStyle_serializer.write(valueSerializer, valueHolderForUrlStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorTextSpanOptions {
        let valueDeserializer : DeserializerBase = buffer
        const offsetTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let offsetTmpBuf : int32 | undefined = undefined
        if ((offsetTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            offsetTmpBuf = valueDeserializer.readInt32()
        }
        const offsetTmpResult : int32 | undefined = offsetTmpBuf
        const styleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let styleTmpBuf : RichEditorTextStyle | undefined = undefined
        if ((styleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            styleTmpBuf = RichEditorTextStyle_serializer.read(valueDeserializer)
        }
        const styleTmpResult : RichEditorTextStyle | undefined = styleTmpBuf
        const paragraphStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let paragraphStyleTmpBuf : RichEditorParagraphStyle | undefined = undefined
        if ((paragraphStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            paragraphStyleTmpBuf = RichEditorParagraphStyle_serializer.read(valueDeserializer)
        }
        const paragraphStyleTmpResult : RichEditorParagraphStyle | undefined = paragraphStyleTmpBuf
        const gestureTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let gestureTmpBuf : RichEditorGesture | undefined = undefined
        if ((gestureTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            gestureTmpBuf = RichEditorGesture_serializer.read(valueDeserializer)
        }
        const gestureTmpResult : RichEditorGesture | undefined = gestureTmpBuf
        const urlStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let urlStyleTmpBuf : RichEditorUrlStyle | undefined = undefined
        if ((urlStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            urlStyleTmpBuf = RichEditorUrlStyle_serializer.read(valueDeserializer)
        }
        const urlStyleTmpResult : RichEditorUrlStyle | undefined = urlStyleTmpBuf
        let value : RichEditorTextSpanOptions = ({offset: offsetTmpResult, style: styleTmpResult, paragraphStyle: paragraphStyleTmpResult, gesture: gestureTmpResult, urlStyle: urlStyleTmpResult} as RichEditorTextSpanOptions)
        return value
    }
}
export class RichEditorTextSpanResult_serializer {
    public static write(buffer: SerializerBase, value: RichEditorTextSpanResult): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSpanPosition  = value.spanPosition
        RichEditorSpanPosition_serializer.write(valueSerializer, valueHolderForSpanPosition)
        const valueHolderForValue  = value.value
        valueSerializer.writeString(valueHolderForValue)
        const valueHolderForTextStyle  = value.textStyle
        RichEditorTextStyleResult_serializer.write(valueSerializer, valueHolderForTextStyle)
        const valueHolderForOffsetInSpan  = value.offsetInSpan
        const valueHolderForOffsetInSpan_0  = valueHolderForOffsetInSpan[0]
        valueSerializer.writeInt32(valueHolderForOffsetInSpan_0)
        const valueHolderForOffsetInSpan_1  = valueHolderForOffsetInSpan[1]
        valueSerializer.writeInt32(valueHolderForOffsetInSpan_1)
        const valueHolderForSymbolSpanStyle  = value.symbolSpanStyle
        if (valueHolderForSymbolSpanStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSymbolSpanStyleTmpValue  = valueHolderForSymbolSpanStyle!
            RichEditorSymbolSpanStyle_serializer.write(valueSerializer, valueHolderForSymbolSpanStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForValueResource  = value.valueResource
        if (valueHolderForValueResource !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForValueResourceTmpValue  = valueHolderForValueResource!
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForValueResourceTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForParagraphStyle  = value.paragraphStyle
        if (valueHolderForParagraphStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForParagraphStyleTmpValue  = valueHolderForParagraphStyle!
            RichEditorParagraphStyle_serializer.write(valueSerializer, valueHolderForParagraphStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPreviewText  = value.previewText
        if (valueHolderForPreviewText !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPreviewTextTmpValue  = valueHolderForPreviewText!
            valueSerializer.writeString(valueHolderForPreviewTextTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForUrlStyle  = value.urlStyle
        if (valueHolderForUrlStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUrlStyleTmpValue  = valueHolderForUrlStyle!
            RichEditorUrlStyle_serializer.write(valueSerializer, valueHolderForUrlStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RichEditorTextSpanResult {
        let valueDeserializer : DeserializerBase = buffer
        const spanPositionTmpResult : RichEditorSpanPosition = RichEditorSpanPosition_serializer.read(valueDeserializer)
        const valueTmpResult : string = (valueDeserializer.readString() as string)
        const textStyleTmpResult : RichEditorTextStyleResult = RichEditorTextStyleResult_serializer.read(valueDeserializer)
        const offsetInSpanTmpBufValue0 : int32 = valueDeserializer.readInt32()
        const offsetInSpanTmpBufValue1 : int32 = valueDeserializer.readInt32()
        const offsetInSpanTmpResult : [ int32, int32 ] = ([offsetInSpanTmpBufValue0, offsetInSpanTmpBufValue1] as [ int32, int32 ])
        const symbolSpanStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let symbolSpanStyleTmpBuf : RichEditorSymbolSpanStyle | undefined = undefined
        if ((symbolSpanStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            symbolSpanStyleTmpBuf = RichEditorSymbolSpanStyle_serializer.read(valueDeserializer)
        }
        const symbolSpanStyleTmpResult : RichEditorSymbolSpanStyle | undefined = symbolSpanStyleTmpBuf
        const valueResourceTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let valueResourceTmpBuf : global_resource_Resource | undefined = undefined
        if ((valueResourceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            valueResourceTmpBuf = global_resource_Resource_serializer.read(valueDeserializer)
        }
        const valueResourceTmpResult : global_resource_Resource | undefined = valueResourceTmpBuf
        const paragraphStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let paragraphStyleTmpBuf : RichEditorParagraphStyle | undefined = undefined
        if ((paragraphStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            paragraphStyleTmpBuf = RichEditorParagraphStyle_serializer.read(valueDeserializer)
        }
        const paragraphStyleTmpResult : RichEditorParagraphStyle | undefined = paragraphStyleTmpBuf
        const previewTextTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let previewTextTmpBuf : string | undefined = undefined
        if ((previewTextTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            previewTextTmpBuf = (valueDeserializer.readString() as string)
        }
        const previewTextTmpResult : string | undefined = previewTextTmpBuf
        const urlStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let urlStyleTmpBuf : RichEditorUrlStyle | undefined = undefined
        if ((urlStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            urlStyleTmpBuf = RichEditorUrlStyle_serializer.read(valueDeserializer)
        }
        const urlStyleTmpResult : RichEditorUrlStyle | undefined = urlStyleTmpBuf
        let value : RichEditorTextSpanResult = ({spanPosition: spanPositionTmpResult, value: valueTmpResult, textStyle: textStyleTmpResult, offsetInSpan: offsetInSpanTmpResult, symbolSpanStyle: symbolSpanStyleTmpResult, valueResource: valueResourceTmpResult, paragraphStyle: paragraphStyleTmpResult, previewText: previewTextTmpResult, urlStyle: urlStyleTmpResult} as RichEditorTextSpanResult)
        return value
    }
}
export class RichEditorControllerInternal {
    public static fromPtr(ptr: KPointer): RichEditorController {
        return new RichEditorController(MaterializedBaseTag.NOP, ptr)
    }
}
export class RichEditorController extends RichEditorBaseController implements MaterializedBase {
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
    }
    constructor() {
        this(MaterializedBaseTag.NOP, RichEditorController.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RichEditorController_getFinalizer()
    }
    public addTextSpan(content: arkui_component_units_ResourceStr, options?: RichEditorTextSpanOptions): int32 | undefined {
        const content_casted = content as (arkui_component_units_ResourceStr)
        const options_casted = options as (RichEditorTextSpanOptions | undefined)
        return this.addTextSpan_serialize(content_casted, options_casted)
    }
    public addImageSpan(value: PixelMap | arkui_component_units_ResourceStr, options?: RichEditorImageSpanOptions): int32 | undefined {
        const value_casted = value as (PixelMap | arkui_component_units_ResourceStr)
        const options_casted = options as (RichEditorImageSpanOptions | undefined)
        return this.addImageSpan_serialize(value_casted, options_casted)
    }
    public addBuilderSpan(value: CustomBuilder, options?: RichEditorBuilderSpanOptions): int32 | undefined {
        const value_casted = value as (CustomBuilder)
        const options_casted = options as (RichEditorBuilderSpanOptions | undefined)
        return this.addBuilderSpan_serialize(value_casted, options_casted)
    }
    public addSymbolSpan(value: global_resource_Resource, options?: RichEditorSymbolSpanOptions): int32 | undefined {
        const value_casted = value as (global_resource_Resource)
        const options_casted = options as (RichEditorSymbolSpanOptions | undefined)
        return this.addSymbolSpan_serialize(value_casted, options_casted)
    }
    public updateSpanStyle(value: RichEditorUpdateTextSpanStyleOptions | RichEditorUpdateImageSpanStyleOptions | RichEditorUpdateSymbolSpanStyleOptions): void {
        const value_casted = value as (RichEditorUpdateTextSpanStyleOptions | RichEditorUpdateImageSpanStyleOptions | RichEditorUpdateSymbolSpanStyleOptions)
        this.updateSpanStyle_serialize(value_casted)
        return
    }
    public updateParagraphStyle(value: RichEditorParagraphStyleOptions): void {
        const value_casted = value as (RichEditorParagraphStyleOptions)
        this.updateParagraphStyle_serialize(value_casted)
        return
    }
    public deleteSpans(value?: RichEditorRange): void {
        const value_casted = value as (RichEditorRange | undefined)
        this.deleteSpans_serialize(value_casted)
        return
    }
    public getSpans(value?: RichEditorRange): Array<RichEditorImageSpanResult | RichEditorTextSpanResult> | undefined {
        const value_casted = value as (RichEditorRange | undefined)
        return this.getSpans_serialize(value_casted)
    }
    public getParagraphs(value?: RichEditorRange): Array<RichEditorParagraphResult> | undefined {
        const value_casted = value as (RichEditorRange | undefined)
        return this.getParagraphs_serialize(value_casted)
    }
    public getSelection(): RichEditorSelection | undefined {
        return this.getSelection_serialize()
    }
    public fromStyledString(value: StyledString): Array<RichEditorSpan> | undefined {
        const value_casted = value as (StyledString)
        return this.fromStyledString_serialize(value_casted)
    }
    public toStyledString(value: RichEditorRange): StyledString | undefined {
        const value_casted = value as (RichEditorRange)
        return this.toStyledString_serialize(value_casted)
    }
    private addTextSpan_serialize(content: arkui_component_units_ResourceStr, options?: RichEditorTextSpanOptions): int32 | undefined {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (content instanceof string) {
            thisSerializer.writeInt8((0).toByte())
            const contentForIdx0  = content as string
            thisSerializer.writeString(contentForIdx0)
        } else if (content instanceof arkui_component_units_Resource) {
            thisSerializer.writeInt8((1).toByte())
            const contentForIdx1  = content as arkui_component_units_Resource
            global_resource_Resource_serializer.write(thisSerializer, contentForIdx1)
        }
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            RichEditorTextSpanOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_addTextSpan(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : int32 | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = retvalDeserializer.readInt32()
        }
        const returnResult : int32 | undefined = buffer
        return returnResult
    }
    private addImageSpan_serialize(value: PixelMap | arkui_component_units_ResourceStr, options?: RichEditorImageSpanOptions): int32 | undefined {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value instanceof PixelMap) {
            thisSerializer.writeInt8((0).toByte())
            const valueForIdx0  = value as PixelMap
            image_PixelMap_serializer.write(thisSerializer, valueForIdx0)
        } else if (value instanceof arkui_component_units_ResourceStr) {
            thisSerializer.writeInt8((1).toByte())
            const valueForIdx1  = value as arkui_component_units_ResourceStr
            if (valueForIdx1 instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueForIdx1ForIdx0  = valueForIdx1 as string
                thisSerializer.writeString(valueForIdx1ForIdx0)
            } else if (valueForIdx1 instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueForIdx1ForIdx1  = valueForIdx1 as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueForIdx1ForIdx1)
            }
        }
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            RichEditorImageSpanOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_addImageSpan(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : int32 | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = retvalDeserializer.readInt32()
        }
        const returnResult : int32 | undefined = buffer
        return returnResult
    }
    private addBuilderSpan_serialize(value: CustomBuilder, options?: RichEditorBuilderSpanOptions): int32 | undefined {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value))
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            RichEditorBuilderSpanOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_addBuilderSpan(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : int32 | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = retvalDeserializer.readInt32()
        }
        const returnResult : int32 | undefined = buffer
        return returnResult
    }
    private addSymbolSpan_serialize(value: global_resource_Resource, options?: RichEditorSymbolSpanOptions): int32 | undefined {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        global_resource_Resource_serializer.write(thisSerializer, value)
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            RichEditorSymbolSpanOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_addSymbolSpan(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : int32 | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = retvalDeserializer.readInt32()
        }
        const returnResult : int32 | undefined = buffer
        return returnResult
    }
    private updateSpanStyle_serialize(value: RichEditorUpdateTextSpanStyleOptions | RichEditorUpdateImageSpanStyleOptions | RichEditorUpdateSymbolSpanStyleOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value instanceof RichEditorUpdateTextSpanStyleOptions) {
            thisSerializer.writeInt8((0).toByte())
            const valueForIdx0  = value as RichEditorUpdateTextSpanStyleOptions
            RichEditorUpdateTextSpanStyleOptions_serializer.write(thisSerializer, valueForIdx0)
        } else if (value instanceof RichEditorUpdateImageSpanStyleOptions) {
            thisSerializer.writeInt8((1).toByte())
            const valueForIdx1  = value as RichEditorUpdateImageSpanStyleOptions
            RichEditorUpdateImageSpanStyleOptions_serializer.write(thisSerializer, valueForIdx1)
        } else if (value instanceof RichEditorUpdateSymbolSpanStyleOptions) {
            thisSerializer.writeInt8((2).toByte())
            const valueForIdx2  = value as RichEditorUpdateSymbolSpanStyleOptions
            RichEditorUpdateSymbolSpanStyleOptions_serializer.write(thisSerializer, valueForIdx2)
        }
        ArkUIGeneratedNativeModule._RichEditorController_updateSpanStyle(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private updateParagraphStyle_serialize(value: RichEditorParagraphStyleOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        RichEditorParagraphStyleOptions_serializer.write(thisSerializer, value)
        ArkUIGeneratedNativeModule._RichEditorController_updateParagraphStyle(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private deleteSpans_serialize(value?: RichEditorRange): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            RichEditorRange_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RichEditorController_deleteSpans(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getSpans_serialize(value?: RichEditorRange): Array<RichEditorImageSpanResult | RichEditorTextSpanResult> | undefined {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            RichEditorRange_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_getSpans(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : Array<RichEditorImageSpanResult | RichEditorTextSpanResult> | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bufferOptLength : int32 = retvalDeserializer.readInt32()
            let bufferOpt : Array<RichEditorImageSpanResult | RichEditorTextSpanResult> = new Array<RichEditorImageSpanResult | RichEditorTextSpanResult>(bufferOptLength)
            for (let bufferOptBufCounterI = 0; bufferOptBufCounterI < bufferOptLength; bufferOptBufCounterI++) {
                const bufferOptTempBufUnionSelector : int32 = retvalDeserializer.readInt8()
                let bufferOptTempBuf : RichEditorImageSpanResult | RichEditorTextSpanResult | undefined
                if (bufferOptTempBufUnionSelector == (0).toByte()) {
                    bufferOptTempBuf = RichEditorImageSpanResult_serializer.read(retvalDeserializer)
                } else if (bufferOptTempBufUnionSelector == (1).toByte()) {
                    bufferOptTempBuf = RichEditorTextSpanResult_serializer.read(retvalDeserializer)
                } else {
                    throw new Error('One of the branches for bufferOptTempBuf has to be chosen through deserialisation.')
                }
                bufferOpt[bufferOptBufCounterI] = (bufferOptTempBuf as RichEditorImageSpanResult | RichEditorTextSpanResult)
            }
            buffer = bufferOpt
        }
        const returnResult : Array<RichEditorImageSpanResult | RichEditorTextSpanResult> | undefined = buffer
        return returnResult
    }
    private getParagraphs_serialize(value?: RichEditorRange): Array<RichEditorParagraphResult> | undefined {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            RichEditorRange_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_getParagraphs(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : Array<RichEditorParagraphResult> | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bufferOptLength : int32 = retvalDeserializer.readInt32()
            let bufferOpt : Array<RichEditorParagraphResult> = new Array<RichEditorParagraphResult>(bufferOptLength)
            for (let bufferOptBufCounterI = 0; bufferOptBufCounterI < bufferOptLength; bufferOptBufCounterI++) {
                bufferOpt[bufferOptBufCounterI] = RichEditorParagraphResult_serializer.read(retvalDeserializer)
            }
            buffer = bufferOpt
        }
        const returnResult : Array<RichEditorParagraphResult> | undefined = buffer
        return returnResult
    }
    private getSelection_serialize(): RichEditorSelection | undefined {
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_getSelection(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : RichEditorSelection | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = RichEditorSelection_serializer.read(retvalDeserializer)
        }
        const returnResult : RichEditorSelection | undefined = buffer
        return returnResult
    }
    private fromStyledString_serialize(value: StyledString): Array<RichEditorSpan> | undefined {
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_fromStyledString(this.peer!.ptr, toPeerPtr(value))
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : Array<RichEditorSpan> | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bufferOptLength : int32 = retvalDeserializer.readInt32()
            let bufferOpt : Array<RichEditorSpan> = new Array<RichEditorSpan>(bufferOptLength)
            for (let bufferOptBufCounterI = 0; bufferOptBufCounterI < bufferOptLength; bufferOptBufCounterI++) {
                const bufferOptTempBufUnionSelector : int32 = retvalDeserializer.readInt8()
                let bufferOptTempBuf : RichEditorImageSpanResult | RichEditorTextSpanResult | undefined
                if (bufferOptTempBufUnionSelector == (0).toByte()) {
                    bufferOptTempBuf = RichEditorImageSpanResult_serializer.read(retvalDeserializer)
                } else if (bufferOptTempBufUnionSelector == (1).toByte()) {
                    bufferOptTempBuf = RichEditorTextSpanResult_serializer.read(retvalDeserializer)
                } else {
                    throw new Error('One of the branches for bufferOptTempBuf has to be chosen through deserialisation.')
                }
                bufferOpt[bufferOptBufCounterI] = (bufferOptTempBuf as RichEditorImageSpanResult | RichEditorTextSpanResult)
            }
            buffer = bufferOpt
        }
        const returnResult : Array<RichEditorSpan> | undefined = buffer
        return returnResult
    }
    private toStyledString_serialize(value: RichEditorRange): StyledString | undefined {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        RichEditorRange_serializer.write(thisSerializer, value)
        const retval  = ArkUIGeneratedNativeModule._RichEditorController_toStyledString(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : StyledString | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = (StyledString_serializer.read(retvalDeserializer) as StyledString)
        }
        const returnResult : StyledString | undefined = buffer
        return returnResult
    }
}
export class RichEditorStyledStringControllerInternal {
    public static fromPtr(ptr: KPointer): RichEditorStyledStringController {
        return new RichEditorStyledStringController(MaterializedBaseTag.NOP, ptr)
    }
}
export class RichEditorStyledStringController extends RichEditorBaseController implements MaterializedBase {
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
    }
    constructor() {
        this(MaterializedBaseTag.NOP, RichEditorStyledStringController.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._RichEditorStyledStringController_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RichEditorStyledStringController_getFinalizer()
    }
    public setStyledString(styledString: StyledString): void {
        const styledString_casted = styledString as (StyledString)
        this.setStyledString_serialize(styledString_casted)
        return
    }
    public getStyledString(): MutableStyledString | undefined {
        return this.getStyledString_serialize()
    }
    public getSelection(): RichEditorRange | undefined {
        return this.getSelection_serialize()
    }
    public onContentChanged(listener: StyledStringChangedListener): void {
        const listener_casted = listener as (StyledStringChangedListener)
        this.onContentChanged_serialize(listener_casted)
        return
    }
    private setStyledString_serialize(styledString: StyledString): void {
        ArkUIGeneratedNativeModule._RichEditorStyledStringController_setStyledString(this.peer!.ptr, toPeerPtr(styledString))
    }
    private getStyledString_serialize(): MutableStyledString | undefined {
        const retval  = ArkUIGeneratedNativeModule._RichEditorStyledStringController_getStyledString(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : MutableStyledString | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = (MutableStyledString_serializer.read(retvalDeserializer) as MutableStyledString)
        }
        const returnResult : MutableStyledString | undefined = buffer
        return returnResult
    }
    private getSelection_serialize(): RichEditorRange | undefined {
        const retval  = ArkUIGeneratedNativeModule._RichEditorStyledStringController_getSelection(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : RichEditorRange | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = RichEditorRange_serializer.read(retvalDeserializer)
        }
        const returnResult : RichEditorRange | undefined = buffer
        return returnResult
    }
    private onContentChanged_serialize(listener: StyledStringChangedListener): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        StyledStringChangedListener_serializer.write(thisSerializer, listener)
        ArkUIGeneratedNativeModule._RichEditorStyledStringController_onContentChanged(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
