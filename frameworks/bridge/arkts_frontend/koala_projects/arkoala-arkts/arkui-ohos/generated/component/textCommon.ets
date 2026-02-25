/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

import { Finalizable, RuntimeType, SerializerBase, DeserializerBase, toPeerPtr, KPointer, MaterializedBase, MaterializedBaseTag, NativeBuffer, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr, resourceFinalizerRegister } from '@koalaui/interop'
import { unsafeCast, int32, int64, float32 } from '@koalaui/common'
import { ArkUIGeneratedNativeModule } from '#components'
import { CallbackTransformer } from './../CallbackTransformer'
import { extractors } from '#handwritten'
import { InputMethodExtraConfig } from '@ohos.inputMethod.ExtraConfig'
import { text_LineMetrics_serializer, text_TextBox_serializer } from './../framework/ohos.graphics.text'
import { default as text } from '@ohos.graphics.text'
import { MutableStyledString_serializer, StyledString, StyledStringInternal, MutableStyledString, MutableStyledStringInternal, DecorationStyleInterface, StyledString_serializer, DecorationStyleInterface_serializer } from './styledString'
import { SelectionOptions_serializer, SelectionOptions, Callback as arkui_component_common_Callback, LinearGradientOptions_serializer, LinearGradientOptions, RadialGradientOptions_serializer, RadialGradientOptions } from './common'
import { global_resource_Resource_serializer } from './../framework/resource'
import { ResourceStr, Resource as arkui_component_units_Resource, ResourceColor, Length, LengthMetrics as arkui_component_units_LengthMetrics } from './units'
import { Resource as global_resource_Resource } from 'global.resource'
import { memo, memo_stable } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { Color as arkui_component_enums_Color, TextDecorationType, TextDecorationStyle } from './enums'
import { LengthMetrics as arkui_Graphics_LengthMetrics } from 'arkui.Graphics'
export class ContentTransitionInternal {
    public static fromPtr(ptr: KPointer): ContentTransition {
        return new ContentTransition(MaterializedBaseTag.NOP, ptr)
    }
}
export class ContentTransition implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ContentTransition.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, ContentTransition.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._ContentTransition_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ContentTransition_getFinalizer()
    }
}
export interface IMEClient {
    nodeId: int64
    setExtraConfig(config: InputMethodExtraConfig): void
}
export class IMEClientInternal implements MaterializedBase,IMEClient {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    public nodeId: int64
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, IMEClientInternal.getFinalizer())
        this.nodeId = this.getNodeId()
    }
    constructor() {
        this(MaterializedBaseTag.NOP, IMEClientInternal.construct())
        this.nodeId = this.getNodeId()
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._IMEClient_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._IMEClient_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): IMEClientInternal {
        return new IMEClientInternal(MaterializedBaseTag.NOP, ptr)
    }
    public setExtraConfig(config: InputMethodExtraConfig): void {
        const config_casted = config as (InputMethodExtraConfig)
        this.setExtraConfig_serialize(config_casted)
        return
    }
    private getNodeId(): int64 {
        return this.getNodeId_serialize()
    }
    private setNodeId(nodeId: int64): void {
        const nodeId_casted = nodeId as (int64)
        this.setNodeId_serialize(nodeId_casted)
        return
    }
    private setExtraConfig_serialize(config: InputMethodExtraConfig): void {
        ArkUIGeneratedNativeModule._IMEClient_setExtraConfig(this.peer!.ptr, extractors.toInputMethodExtraConfigPtr(config))
    }
    private getNodeId_serialize(): int64 {
        const retval = ArkUIGeneratedNativeModule._IMEClient_getNodeId(this.peer!.ptr)
        return retval
    }
    private setNodeId_serialize(nodeId: int64): void {
        ArkUIGeneratedNativeModule._IMEClient_setNodeId(this.peer!.ptr, nodeId)
    }
}
export interface LayoutManager {
    getLineCount(): int32 | undefined
    getGlyphPositionAtCoordinate(x: double, y: double): PositionWithAffinity | undefined
    getCharacterPositionAtCoordinate(x: double, y: double): PositionWithAffinity | undefined
    getGlyphRangeForCharacterRange(charRange: TextRange): Array<TextRange> | undefined
    getCharacterRangeForGlyphRange(glyphRange: TextRange): Array<TextRange> | undefined
    getLineMetrics(lineNumber: int32): LineMetrics | undefined
    getRectsForRange(range: TextRange, widthStyle: RectWidthStyle, heightStyle: RectHeightStyle): Array<TextBox> | undefined
}
export class LayoutManagerInternal implements MaterializedBase,LayoutManager {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, LayoutManagerInternal.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, LayoutManagerInternal.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._LayoutManager_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LayoutManager_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): LayoutManagerInternal {
        return new LayoutManagerInternal(MaterializedBaseTag.NOP, ptr)
    }
    public getLineCount(): int32 | undefined {
        return this.getLineCount_serialize()
    }
    public getGlyphPositionAtCoordinate(x: double, y: double): PositionWithAffinity | undefined {
        const x_casted = x as (double)
        const y_casted = y as (double)
        return this.getGlyphPositionAtCoordinate_serialize(x_casted, y_casted)
    }
    public getCharacterPositionAtCoordinate(x: double, y: double): PositionWithAffinity | undefined {
        const x_casted = x as (double)
        const y_casted = y as (double)
        return this.getCharacterPositionAtCoordinate_serialize(x_casted, y_casted)
    }
    public getGlyphRangeForCharacterRange(charRange: TextRange): Array<TextRange> | undefined {
        const charRange_casted = charRange as (TextRange)
        return this.getGlyphRangeForCharacterRange_serialize(charRange_casted)
    }
    public getCharacterRangeForGlyphRange(glyphRange: TextRange): Array<TextRange> | undefined {
        const glyphRange_casted = glyphRange as (TextRange)
        return this.getCharacterRangeForGlyphRange_serialize(glyphRange_casted)
    }
    public getLineMetrics(lineNumber: int32): LineMetrics | undefined {
        const lineNumber_casted = lineNumber as (int32)
        return this.getLineMetrics_serialize(lineNumber_casted)
    }
    public getRectsForRange(range: TextRange, widthStyle: RectWidthStyle, heightStyle: RectHeightStyle): Array<TextBox> | undefined {
        const range_casted = range as (TextRange)
        const widthStyle_casted = widthStyle as (RectWidthStyle)
        const heightStyle_casted = heightStyle as (RectHeightStyle)
        return this.getRectsForRange_serialize(range_casted, widthStyle_casted, heightStyle_casted)
    }
    private getLineCount_serialize(): int32 | undefined {
        const retval = ArkUIGeneratedNativeModule._LayoutManager_getLineCount(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType = retvalDeserializer.readInt8()!.toInt()
        let buffer: int32 | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = retvalDeserializer.readInt32()
        }
        const returnResult: int32 | undefined = buffer
        return returnResult
    }
    private getGlyphPositionAtCoordinate_serialize(x: double, y: double): PositionWithAffinity | undefined {
        const retval = ArkUIGeneratedNativeModule._LayoutManager_getGlyphPositionAtCoordinate(this.peer!.ptr, x, y)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType = retvalDeserializer.readInt8()!.toInt()
        let buffer: PositionWithAffinity | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = PositionWithAffinity_serializer.read(retvalDeserializer)
        }
        const returnResult: PositionWithAffinity | undefined = buffer
        return returnResult
    }
    private getCharacterPositionAtCoordinate_serialize(x: double, y: double): PositionWithAffinity | undefined {
        const retval = ArkUIGeneratedNativeModule._LayoutManager_getCharacterPositionAtCoordinate(this.peer!.ptr, x, y)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType = retvalDeserializer.readInt8()!.toInt()
        let buffer: PositionWithAffinity | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = PositionWithAffinity_serializer.read(retvalDeserializer)
        }
        const returnResult: PositionWithAffinity | undefined = buffer
        return returnResult
    }
    private getGlyphRangeForCharacterRange_serialize(charRange: TextRange): Array<TextRange> | undefined {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        TextRange_serializer.write(thisSerializer, charRange)
        const retval = ArkUIGeneratedNativeModule._LayoutManager_getGlyphRangeForCharacterRange(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType = retvalDeserializer.readInt8()!.toInt()
        let buffer: Array<TextRange> | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bufferOptLength: int32 = retvalDeserializer.readInt32()
            let bufferOpt: Array<TextRange> = new Array<TextRange>(bufferOptLength)
            for (let bufferOptBufCounterI = 0; bufferOptBufCounterI < bufferOptLength; bufferOptBufCounterI++) {
                bufferOpt[bufferOptBufCounterI] = TextRange_serializer.read(retvalDeserializer)
            }
            buffer = bufferOpt
        }
        const returnResult: Array<TextRange> | undefined = buffer
        return returnResult
    }
    private getCharacterRangeForGlyphRange_serialize(glyphRange: TextRange): Array<TextRange> | undefined {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        TextRange_serializer.write(thisSerializer, glyphRange)
        const retval = ArkUIGeneratedNativeModule._LayoutManager_getCharacterRangeForGlyphRange(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType = retvalDeserializer.readInt8()!.toInt()
        let buffer: Array<TextRange> | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bufferOptLength: int32 = retvalDeserializer.readInt32()
            let bufferOpt: Array<TextRange> = new Array<TextRange>(bufferOptLength)
            for (let bufferOptBufCounterI = 0; bufferOptBufCounterI < bufferOptLength; bufferOptBufCounterI++) {
                bufferOpt[bufferOptBufCounterI] = TextRange_serializer.read(retvalDeserializer)
            }
            buffer = bufferOpt
        }
        const returnResult: Array<TextRange> | undefined = buffer
        return returnResult
    }
    private getLineMetrics_serialize(lineNumber: int32): LineMetrics | undefined {
        const retval = ArkUIGeneratedNativeModule._LayoutManager_getLineMetrics(this.peer!.ptr, lineNumber)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType = retvalDeserializer.readInt8()!.toInt()
        let buffer: LineMetrics | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = text_LineMetrics_serializer.read(retvalDeserializer)
        }
        const returnResult: LineMetrics | undefined = buffer
        return returnResult
    }
    private getRectsForRange_serialize(range: TextRange, widthStyle: RectWidthStyle, heightStyle: RectHeightStyle): Array<TextBox> | undefined {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        TextRange_serializer.write(thisSerializer, range)
        const retval = ArkUIGeneratedNativeModule._LayoutManager_getRectsForRange(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), widthStyle.valueOf(), heightStyle.valueOf())
        thisSerializer.release()
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType = retvalDeserializer.readInt8()!.toInt()
        let buffer: Array<TextBox> | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bufferOptLength: int32 = retvalDeserializer.readInt32()
            let bufferOpt: Array<TextBox> = new Array<TextBox>(bufferOptLength)
            for (let bufferOptBufCounterI = 0; bufferOptBufCounterI < bufferOptLength; bufferOptBufCounterI++) {
                bufferOpt[bufferOptBufCounterI] = text_TextBox_serializer.read(retvalDeserializer)
            }
            buffer = bufferOpt
        }
        const returnResult: Array<TextBox> | undefined = buffer
        return returnResult
    }
}
export class ShaderStyleInternal {
    public static fromPtr(ptr: KPointer): ShaderStyle {
        return new ShaderStyle(MaterializedBaseTag.NOP, ptr)
    }
}
export class ShaderStyle implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ShaderStyle.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, ShaderStyle.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._ShaderStyle_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ShaderStyle_getFinalizer()
    }
}
export interface StyledStringController {
    setStyledString(styledString: StyledString): void
    getStyledString(): MutableStyledString | undefined
}
export class StyledStringControllerInternal implements MaterializedBase,StyledStringController {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, StyledStringControllerInternal.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, StyledStringControllerInternal.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._StyledStringController_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._StyledStringController_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): StyledStringControllerInternal {
        return new StyledStringControllerInternal(MaterializedBaseTag.NOP, ptr)
    }
    public setStyledString(styledString: StyledString): void {
        const styledString_casted = styledString as (StyledString)
        this.setStyledString_serialize(styledString_casted)
        return
    }
    public getStyledString(): MutableStyledString | undefined {
        return this.getStyledString_serialize()
    }
    private setStyledString_serialize(styledString: StyledString): void {
        ArkUIGeneratedNativeModule._StyledStringController_setStyledString(this.peer!.ptr, toPeerPtr(styledString))
    }
    private getStyledString_serialize(): MutableStyledString | undefined {
        const retval = ArkUIGeneratedNativeModule._StyledStringController_getStyledString(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType = retvalDeserializer.readInt8()!.toInt()
        let buffer: MutableStyledString | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = (MutableStyledString_serializer.read(retvalDeserializer) as MutableStyledString)
        }
        const returnResult: MutableStyledString | undefined = buffer
        return returnResult
    }
}
export interface TextBaseController {
    setSelection(selectionStart: int32, selectionEnd: int32, options: SelectionOptions | undefined): void
    closeSelectionMenu(): void
    getLayoutManager(): LayoutManager | undefined
}
export class TextBaseControllerInternal implements MaterializedBase,TextBaseController {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, TextBaseControllerInternal.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, TextBaseControllerInternal.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._TextBaseController_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextBaseController_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): TextBaseControllerInternal {
        return new TextBaseControllerInternal(MaterializedBaseTag.NOP, ptr)
    }
    public setSelection(selectionStart: int32, selectionEnd: int32, options?: SelectionOptions): void {
        const selectionStart_casted = selectionStart as (int32)
        const selectionEnd_casted = selectionEnd as (int32)
        const options_casted = options as (SelectionOptions | undefined)
        this.setSelection_serialize(selectionStart_casted, selectionEnd_casted, options_casted)
        return
    }
    public closeSelectionMenu(): void {
        this.closeSelectionMenu_serialize()
        return
    }
    public getLayoutManager(): LayoutManager | undefined {
        return this.getLayoutManager_serialize()
    }
    private setSelection_serialize(selectionStart: int32, selectionEnd: int32, options?: SelectionOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue = options!
            SelectionOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextBaseController_setSelection(this.peer!.ptr, selectionStart, selectionEnd, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private closeSelectionMenu_serialize(): void {
        ArkUIGeneratedNativeModule._TextBaseController_closeSelectionMenu(this.peer!.ptr)
    }
    private getLayoutManager_serialize(): LayoutManager | undefined {
        const retval = ArkUIGeneratedNativeModule._TextBaseController_getLayoutManager(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType = retvalDeserializer.readInt8()!.toInt()
        let buffer: LayoutManager | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = (LayoutManager_serializer.read(retvalDeserializer) as LayoutManager)
        }
        const returnResult: LayoutManager | undefined = buffer
        return returnResult
    }
}
export class TextMenuItemIdInternal {
    public static fromPtr(ptr: KPointer): TextMenuItemId {
        return new TextMenuItemId(MaterializedBaseTag.NOP, ptr)
    }
}
export class TextMenuItemId implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    public static readonly CUT: TextMenuItemId = TextMenuItemId.getCUT()
    public static readonly COPY: TextMenuItemId = TextMenuItemId.getCOPY()
    public static readonly PASTE: TextMenuItemId = TextMenuItemId.getPASTE()
    public static readonly SELECT_ALL: TextMenuItemId = TextMenuItemId.getSELECT_ALL()
    public static readonly COLLABORATION_SERVICE: TextMenuItemId = TextMenuItemId.getCOLLABORATION_SERVICE()
    public static readonly CAMERA_INPUT: TextMenuItemId = TextMenuItemId.getCAMERA_INPUT()
    public static readonly AI_WRITER: TextMenuItemId = TextMenuItemId.getAI_WRITER()
    public static readonly TRANSLATE: TextMenuItemId = TextMenuItemId.getTRANSLATE()
    public static readonly SEARCH: TextMenuItemId = TextMenuItemId.getSEARCH()
    public static readonly SHARE: TextMenuItemId = TextMenuItemId.getSHARE()
    public static readonly autoFill: TextMenuItemId = TextMenuItemId.getAutoFill()
    public static readonly passwordVault: TextMenuItemId = TextMenuItemId.getPasswordVault()
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, TextMenuItemId.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, TextMenuItemId.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._TextMenuItemId_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextMenuItemId_getFinalizer()
    }
    public static of(id: ResourceStr): TextMenuItemId {
        const id_casted = id as (ResourceStr)
        return TextMenuItemId.of_serialize(id_casted)
    }
    private static getCUT(): TextMenuItemId {
        return TextMenuItemId.getCUT_serialize()
    }
    private static getCOPY(): TextMenuItemId {
        return TextMenuItemId.getCOPY_serialize()
    }
    private static getPASTE(): TextMenuItemId {
        return TextMenuItemId.getPASTE_serialize()
    }
    private static getSELECT_ALL(): TextMenuItemId {
        return TextMenuItemId.getSELECT_ALL_serialize()
    }
    private static getCOLLABORATION_SERVICE(): TextMenuItemId {
        return TextMenuItemId.getCOLLABORATION_SERVICE_serialize()
    }
    private static getCAMERA_INPUT(): TextMenuItemId {
        return TextMenuItemId.getCAMERA_INPUT_serialize()
    }
    private static getAI_WRITER(): TextMenuItemId {
        return TextMenuItemId.getAI_WRITER_serialize()
    }
    private static getTRANSLATE(): TextMenuItemId {
        return TextMenuItemId.getTRANSLATE_serialize()
    }
    private static getSEARCH(): TextMenuItemId {
        return TextMenuItemId.getSEARCH_serialize()
    }
    private static getSHARE(): TextMenuItemId {
        return TextMenuItemId.getSHARE_serialize()
    }
    private static getAutoFill(): TextMenuItemId {
        return TextMenuItemId.getAutoFill_serialize()
    }
    private static getPasswordVault(): TextMenuItemId {
        return TextMenuItemId.getPasswordVault_serialize()
    }
    private static of_serialize(id: ResourceStr): TextMenuItemId {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (id instanceof string) {
            thisSerializer.writeInt8((0).toByte())
            const idForIdx0 = id as string
            thisSerializer.writeString(idForIdx0)
        } else if (id instanceof arkui_component_units_Resource) {
            thisSerializer.writeInt8((1).toByte())
            const idForIdx1 = id as arkui_component_units_Resource
            global_resource_Resource_serializer.write(thisSerializer, idForIdx1)
        }
        const retval = ArkUIGeneratedNativeModule._TextMenuItemId_of(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj: TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getCUT_serialize(): TextMenuItemId {
        const retval = ArkUIGeneratedNativeModule._TextMenuItemId_getCUT()
        const obj: TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getCOPY_serialize(): TextMenuItemId {
        const retval = ArkUIGeneratedNativeModule._TextMenuItemId_getCOPY()
        const obj: TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getPASTE_serialize(): TextMenuItemId {
        const retval = ArkUIGeneratedNativeModule._TextMenuItemId_getPASTE()
        const obj: TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getSELECT_ALL_serialize(): TextMenuItemId {
        const retval = ArkUIGeneratedNativeModule._TextMenuItemId_getSELECT_ALL()
        const obj: TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getCOLLABORATION_SERVICE_serialize(): TextMenuItemId {
        const retval = ArkUIGeneratedNativeModule._TextMenuItemId_getCOLLABORATION_SERVICE()
        const obj: TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getCAMERA_INPUT_serialize(): TextMenuItemId {
        const retval = ArkUIGeneratedNativeModule._TextMenuItemId_getCAMERA_INPUT()
        const obj: TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getAI_WRITER_serialize(): TextMenuItemId {
        const retval = ArkUIGeneratedNativeModule._TextMenuItemId_getAI_WRITER()
        const obj: TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getTRANSLATE_serialize(): TextMenuItemId {
        const retval = ArkUIGeneratedNativeModule._TextMenuItemId_getTRANSLATE()
        const obj: TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getSEARCH_serialize(): TextMenuItemId {
        const retval = ArkUIGeneratedNativeModule._TextMenuItemId_getSEARCH()
        const obj: TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getSHARE_serialize(): TextMenuItemId {
        const retval = ArkUIGeneratedNativeModule._TextMenuItemId_getSHARE()
        const obj: TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getAutoFill_serialize(): TextMenuItemId {
        const retval = ArkUIGeneratedNativeModule._TextMenuItemId_getAutoFill()
        const obj: TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getPasswordVault_serialize(): TextMenuItemId {
        const retval = ArkUIGeneratedNativeModule._TextMenuItemId_getPasswordVault()
        const obj: TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    public equals(id: TextMenuItemId): boolean {
        const id_casted = id as (TextMenuItemId)
        return this.equals_serialize(id_casted)
    }
    private equals_serialize(id: TextMenuItemId): boolean {
        const retval = ArkUIGeneratedNativeModule._TextMenuItemId_equals(this.peer!.ptr, toPeerPtr(id))
        return retval
    }
}
export enum TextDataDetectorType {
    PHONE_NUMBER = 0,
    URL = 1,
    EMAIL = 2,
    ADDRESS = 3,
    DATE_TIME = 4
}
export interface TextDataDetectorConfig {
    types: Array<TextDataDetectorType> | null | undefined;
    onDetectResultUpdate?: arkui_component_common_Callback<string, void>;
    color?: ResourceColor;
    decoration?: DecorationStyleInterface;
    enablePreviewMenu?: boolean;
}
export interface TextRange {
    start?: int32;
    end?: int32;
}
export interface InsertValue {
    insertOffset: int32;
    insertValue: string;
}
export enum TextDeleteDirection {
    BACKWARD = 0,
    FORWARD = 1
}
export enum MenuType {
    SELECTION_MENU = 0,
    PREVIEW_MENU = 1
}
export enum AutoCapitalizationMode {
    NONE = 0,
    WORDS = 1,
    SENTENCES = 2,
    ALL_CHARACTERS = 3
}
export interface DeleteValue {
    deleteOffset: int32;
    direction: TextDeleteDirection;
    deleteValue: string;
}
export type OnDidChangeCallback = (rangeBefore: TextRange, rangeAfter: TextRange) => void;
export type EditableTextOnChangeCallback = (value: string, previewText?: PreviewText, options?: TextChangeOptions) => void;
export interface PreviewText {
    offset: int32;
    value: string;
}
export interface StyledStringChangedListener {
    onWillChange?: arkui_component_common_Callback<StyledStringChangeValue, boolean>;
    onDidChange?: OnDidChangeCallback;
}
export interface StyledStringChangeValue {
    range: TextRange;
    replacementString: StyledString;
    previewText?: StyledString;
}
export interface PositionWithAffinity {
    position: int32;
    affinity: Affinity;
}
export type Affinity = text.Affinity;
export type LineMetrics = text.LineMetrics;
export type RectWidthStyle = text.RectWidthStyle;
export type RectHeightStyle = text.RectHeightStyle;
export type TextBox = text.TextBox;
export type Paragraph = text.Paragraph;
export interface CaretStyle {
    width?: Length;
    color?: ResourceColor;
}
export interface TextMenuItem {
    content: ResourceStr;
    icon?: ResourceStr;
    id: TextMenuItemId;
    labelInfo?: ResourceStr;
}
export type OnCreateMenuCallback = (menuItems: Array<TextMenuItem>) => Array<TextMenuItem>;
export type OnMenuItemClickCallback = (menuItem: TextMenuItem, range: TextRange) => boolean;
export type OnPrepareMenuCallback = (menuItems: Array<TextMenuItem>) => Array<TextMenuItem>;
export interface EditMenuOptions {
    onCreateMenu: OnCreateMenuCallback | undefined;
    onMenuItemClick: OnMenuItemClickCallback | undefined;
    onPrepareMenu?: OnPrepareMenuCallback;
}
export interface DecorationStyleResult {
    type: TextDecorationType;
    color: ResourceColor;
    style?: TextDecorationStyle;
    thicknessScale?: double;
}
export interface FontSettingOptions {
    enableVariableFontWeight?: boolean;
}
export interface TextChangeOptions {
    rangeBefore: TextRange;
    rangeAfter: TextRange;
    oldContent: string;
    oldPreviewText: PreviewText;
}
export interface EditableTextChangeValue {
    content: string;
    previewText?: PreviewText;
    options?: TextChangeOptions;
}
export enum TextMenuShowMode {
    DEFAULT = 0,
    PREFER_WINDOW = 1
}
export interface TextMenuOptions {
    showMode?: TextMenuShowMode;
}
export enum KeyboardAppearance {
    NONE_IMMERSIVE = 0,
    IMMERSIVE = 1,
    LIGHT_IMMERSIVE = 2,
    DARK_IMMERSIVE = 3
}
export interface AccessibilitySpanOptions {
    accessibilityText?: ResourceStr;
    accessibilityDescription?: ResourceStr;
    accessibilityLevel?: string;
}
export interface SelectedDragPreviewStyle {
    color?: ResourceColor;
}
export enum TextDirection {
    LTR = 0,
    RTL = 1,
    DEFAULT = 2,
    AUTO = 3
}
export enum TextContentAlign {
    TOP = 0,
    CENTER = 1,
    BOTTOM = 2
}
export enum KeyboardGradientMode {
    NONE = 0,
    LINEAR_GRADIENT = 1
}
export enum FlipDirection {
    DOWN = 0,
    UP = 1
}
export enum SuperscriptStyle {
    NORMAL = 0,
    SUPERSCRIPT = 1,
    SUBSCRIPT = 2
}
export enum MaxLinesMode {
    CLIP = 0,
    SCROLL = 1
}
export enum KeyboardFluidLightMode {
    NONE = 0,
    BACKGROUND_FLUID_LIGHT = 1
}
export enum TextChangeReason {
    UNKNOWN = 0,
    INPUT = 1,
    PASTE = 2,
    CUT = 3,
    DRAG = 4,
    AUTO_FILL = 5,
    AI_WRITE = 6,
    REDO = 7,
    UNDO = 8,
    CONTROLLER = 9,
    ACCESSIBILITY = 10,
    COLLABORATION = 11,
    STYLUS = 12
}
export enum TextVerticalAlign {
    BASELINE = 0,
    BOTTOM = 1,
    CENTER = 2,
    TOP = 3
}
export interface MaxLinesOptions {
    overflowMode?: MaxLinesMode;
}
export interface LineSpacingOptions {
    onlyBetweenLines?: boolean;
}
export interface NumericTextTransitionOptions {
    flipDirection?: FlipDirection;
    enableBlur?: boolean;
}
export interface TextLayoutOptions {
    constraintWidth?: arkui_component_units_LengthMetrics;
}
export interface KeyboardAppearanceConfig {
    gradientMode?: KeyboardGradientMode;
    fluidLightMode?: KeyboardFluidLightMode;
}
export interface VoiceButtonOptions {
    enabled?: boolean;
}
export interface FontConfigs {
    fontWeightConfigs?: FontWeightConfigs;
}
export interface FontWeightConfigs {
    enableVariableFontWeight?: boolean;
    enableDeviceFontWeightCategory?: boolean;
}
export class ColorShaderStyle_serializer {
    public static write(buffer: SerializerBase, value: ColorShaderStyle): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ColorShaderStyle {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return ColorShaderStyleInternal.fromPtr(ptr)
    }
}
export class ContentTransition_serializer {
    public static write(buffer: SerializerBase, value: ContentTransition): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ContentTransition {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return ContentTransitionInternal.fromPtr(ptr)
    }
}
export class IMEClient_serializer {
    public static write(buffer: SerializerBase, value: IMEClient): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): IMEClient {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return IMEClientInternal.fromPtr(ptr)
    }
}
export class LayoutManager_serializer {
    public static write(buffer: SerializerBase, value: LayoutManager): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): LayoutManager {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return LayoutManagerInternal.fromPtr(ptr)
    }
}
export class LinearGradientStyle_serializer {
    public static write(buffer: SerializerBase, value: LinearGradientStyle): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): LinearGradientStyle {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return LinearGradientStyleInternal.fromPtr(ptr)
    }
}
export class NumericTextTransition_serializer {
    public static write(buffer: SerializerBase, value: NumericTextTransition): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): NumericTextTransition {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return NumericTextTransitionInternal.fromPtr(ptr)
    }
}
export class RadialGradientStyle_serializer {
    public static write(buffer: SerializerBase, value: RadialGradientStyle): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): RadialGradientStyle {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return RadialGradientStyleInternal.fromPtr(ptr)
    }
}
export class ShaderStyle_serializer {
    public static write(buffer: SerializerBase, value: ShaderStyle): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ShaderStyle {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return ShaderStyleInternal.fromPtr(ptr)
    }
}
export class StyledStringController_serializer {
    public static write(buffer: SerializerBase, value: StyledStringController): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): StyledStringController {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return StyledStringControllerInternal.fromPtr(ptr)
    }
}
export class TextBaseController_serializer {
    public static write(buffer: SerializerBase, value: TextBaseController): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): TextBaseController {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return TextBaseControllerInternal.fromPtr(ptr)
    }
}
export class TextEditControllerEx_serializer {
    public static write(buffer: SerializerBase, value: TextEditControllerEx): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): TextEditControllerEx {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return TextEditControllerExInternal.fromPtr(ptr)
    }
}
export class TextMenuItemId_serializer {
    public static write(buffer: SerializerBase, value: TextMenuItemId): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): TextMenuItemId {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return TextMenuItemIdInternal.fromPtr(ptr)
    }
}
export class DeleteValue_serializer {
    public static write(buffer: SerializerBase, value: DeleteValue): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForDeleteOffset = value.deleteOffset
        valueSerializer.writeInt32(valueHolderForDeleteOffset)
        const valueHolderForDirection = value.direction
        valueSerializer.writeInt32(valueHolderForDirection.valueOf())
        const valueHolderForDeleteValue = value.deleteValue
        valueSerializer.writeString(valueHolderForDeleteValue)
    }
    public static read(buffer: DeserializerBase): DeleteValue {
        let valueDeserializer: DeserializerBase = buffer
        const deleteOffsetTmpResult: int32 = valueDeserializer.readInt32()
        const directionTmpResult: TextDeleteDirection = TextDeleteDirection.fromValue(valueDeserializer.readInt32())
        const deleteValueTmpResult: string = (valueDeserializer.readString() as string)
        let value: DeleteValue = ({deleteOffset: deleteOffsetTmpResult, direction: directionTmpResult, deleteValue: deleteValueTmpResult} as DeleteValue)
        return value
    }
}
export class EditMenuOptions_serializer {
    public static write(buffer: SerializerBase, value: EditMenuOptions): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForOnCreateMenu = value.onCreateMenu
        if (valueHolderForOnCreateMenu !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnCreateMenuTmpValue = valueHolderForOnCreateMenu!
            valueSerializer.holdAndWriteCallback(valueHolderForOnCreateMenuTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnMenuItemClick = value.onMenuItemClick
        if (valueHolderForOnMenuItemClick !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnMenuItemClickTmpValue = valueHolderForOnMenuItemClick!
            valueSerializer.holdAndWriteCallback(valueHolderForOnMenuItemClickTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnPrepareMenu = value.onPrepareMenu
        if (valueHolderForOnPrepareMenu !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnPrepareMenuTmpValue = valueHolderForOnPrepareMenu!
            valueSerializer.holdAndWriteCallback(valueHolderForOnPrepareMenuTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): EditMenuOptions {
        let valueDeserializer: DeserializerBase = buffer
        const onCreateMenuTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let onCreateMenuTmpBuf: OnCreateMenuCallback | undefined = undefined
        if ((onCreateMenuTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onCreateMenuTmpBufOptBufResource: CallbackResource = valueDeserializer.readCallbackResource()
            const onCreateMenuTmpBufOptBufCall: KPointer = valueDeserializer.readPointer()
            const onCreateMenuTmpBufOptBufCallSync: KPointer = valueDeserializer.readPointer()
            const onCreateMenuTmpBufOptClosure = (menuItems: Array<TextMenuItem>):Array<TextMenuItem> => {
                const onCreateMenuTmpBufOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                onCreateMenuTmpBufOptBufArgsSerializer.writeInt32(onCreateMenuTmpBufOptBufResource.resourceId);
                onCreateMenuTmpBufOptBufArgsSerializer.writePointer(onCreateMenuTmpBufOptBufCall);
                onCreateMenuTmpBufOptBufArgsSerializer.writePointer(onCreateMenuTmpBufOptBufCallSync);
                onCreateMenuTmpBufOptBufArgsSerializer.writeInt32((menuItems.length).toInt());
                for (let menuItemsCounterI = 0; menuItemsCounterI < menuItems.length; menuItemsCounterI++) {
                    const menuItemsTmpElement: TextMenuItem = menuItems[menuItemsCounterI];
                    TextMenuItem_serializer.write(onCreateMenuTmpBufOptBufArgsSerializer, menuItemsTmpElement);
                }
                let onCreateMenuTmpBufOptBufContinuationValue: Array<TextMenuItem> | undefined;
                const onCreateMenuTmpBufOptBufContinuationCallback: ((value: Array<TextMenuItem>) => void) = (value: Array<TextMenuItem>):void => {
                onCreateMenuTmpBufOptBufContinuationValue = value;
            }
                onCreateMenuTmpBufOptBufArgsSerializer.holdAndWriteCallback(onCreateMenuTmpBufOptBufContinuationCallback);
                InteropNativeModule._CallCallbackSync(10, 652275661, onCreateMenuTmpBufOptBufArgsSerializer.asBuffer(), onCreateMenuTmpBufOptBufArgsSerializer.length());
                onCreateMenuTmpBufOptBufArgsSerializer.release();
                return (onCreateMenuTmpBufOptBufContinuationValue as Array<TextMenuItem>);
            }
            resourceFinalizerRegister(onCreateMenuTmpBufOptClosure, onCreateMenuTmpBufOptBufResource)
            onCreateMenuTmpBuf = onCreateMenuTmpBufOptClosure
        }
        const onCreateMenuTmpResult: OnCreateMenuCallback | undefined = onCreateMenuTmpBuf
        const onMenuItemClickTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let onMenuItemClickTmpBuf: OnMenuItemClickCallback | undefined = undefined
        if ((onMenuItemClickTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onMenuItemClickTmpBufOptBufResource: CallbackResource = valueDeserializer.readCallbackResource()
            const onMenuItemClickTmpBufOptBufCall: KPointer = valueDeserializer.readPointer()
            const onMenuItemClickTmpBufOptBufCallSync: KPointer = valueDeserializer.readPointer()
            const onMenuItemClickTmpBufOptClosure = (menuItem: TextMenuItem, range: TextRange):boolean => {
                const onMenuItemClickTmpBufOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                onMenuItemClickTmpBufOptBufArgsSerializer.writeInt32(onMenuItemClickTmpBufOptBufResource.resourceId);
                onMenuItemClickTmpBufOptBufArgsSerializer.writePointer(onMenuItemClickTmpBufOptBufCall);
                onMenuItemClickTmpBufOptBufArgsSerializer.writePointer(onMenuItemClickTmpBufOptBufCallSync);
                TextMenuItem_serializer.write(onMenuItemClickTmpBufOptBufArgsSerializer, menuItem);
                TextRange_serializer.write(onMenuItemClickTmpBufOptBufArgsSerializer, range);
                let onMenuItemClickTmpBufOptBufContinuationValue: boolean | undefined;
                const onMenuItemClickTmpBufOptBufContinuationCallback: ((isSelected: boolean) => void) = (value: boolean):void => {
                onMenuItemClickTmpBufOptBufContinuationValue = value;
            }
                onMenuItemClickTmpBufOptBufArgsSerializer.holdAndWriteCallback(onMenuItemClickTmpBufOptBufContinuationCallback);
                InteropNativeModule._CallCallbackSync(10, 1398584914, onMenuItemClickTmpBufOptBufArgsSerializer.asBuffer(), onMenuItemClickTmpBufOptBufArgsSerializer.length());
                onMenuItemClickTmpBufOptBufArgsSerializer.release();
                return (onMenuItemClickTmpBufOptBufContinuationValue as boolean);
            }
            resourceFinalizerRegister(onMenuItemClickTmpBufOptClosure, onMenuItemClickTmpBufOptBufResource)
            onMenuItemClickTmpBuf = onMenuItemClickTmpBufOptClosure
        }
        const onMenuItemClickTmpResult: OnMenuItemClickCallback | undefined = onMenuItemClickTmpBuf
        const onPrepareMenuTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let onPrepareMenuTmpBuf: OnPrepareMenuCallback | undefined = undefined
        if ((onPrepareMenuTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onPrepareMenuTmpBufOptBufResource: CallbackResource = valueDeserializer.readCallbackResource()
            const onPrepareMenuTmpBufOptBufCall: KPointer = valueDeserializer.readPointer()
            const onPrepareMenuTmpBufOptBufCallSync: KPointer = valueDeserializer.readPointer()
            const onPrepareMenuTmpBufOptClosure = (menuItems: Array<TextMenuItem>):Array<TextMenuItem> => {
                const onPrepareMenuTmpBufOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                onPrepareMenuTmpBufOptBufArgsSerializer.writeInt32(onPrepareMenuTmpBufOptBufResource.resourceId);
                onPrepareMenuTmpBufOptBufArgsSerializer.writePointer(onPrepareMenuTmpBufOptBufCall);
                onPrepareMenuTmpBufOptBufArgsSerializer.writePointer(onPrepareMenuTmpBufOptBufCallSync);
                onPrepareMenuTmpBufOptBufArgsSerializer.writeInt32((menuItems.length).toInt());
                for (let menuItemsCounterI = 0; menuItemsCounterI < menuItems.length; menuItemsCounterI++) {
                    const menuItemsTmpElement: TextMenuItem = menuItems[menuItemsCounterI];
                    TextMenuItem_serializer.write(onPrepareMenuTmpBufOptBufArgsSerializer, menuItemsTmpElement);
                }
                let onPrepareMenuTmpBufOptBufContinuationValue: Array<TextMenuItem> | undefined;
                const onPrepareMenuTmpBufOptBufContinuationCallback: ((value: Array<TextMenuItem>) => void) = (value: Array<TextMenuItem>):void => {
                onPrepareMenuTmpBufOptBufContinuationValue = value;
            }
                onPrepareMenuTmpBufOptBufArgsSerializer.holdAndWriteCallback(onPrepareMenuTmpBufOptBufContinuationCallback);
                InteropNativeModule._CallCallbackSync(10, 1160177960, onPrepareMenuTmpBufOptBufArgsSerializer.asBuffer(), onPrepareMenuTmpBufOptBufArgsSerializer.length());
                onPrepareMenuTmpBufOptBufArgsSerializer.release();
                return (onPrepareMenuTmpBufOptBufContinuationValue as Array<TextMenuItem>);
            }
            resourceFinalizerRegister(onPrepareMenuTmpBufOptClosure, onPrepareMenuTmpBufOptBufResource)
            onPrepareMenuTmpBuf = onPrepareMenuTmpBufOptClosure
        }
        const onPrepareMenuTmpResult: OnPrepareMenuCallback | undefined = onPrepareMenuTmpBuf
        let value: EditMenuOptions = ({onCreateMenu: onCreateMenuTmpResult, onMenuItemClick: onMenuItemClickTmpResult, onPrepareMenu: onPrepareMenuTmpResult} as EditMenuOptions)
        return value
    }
}
export class FontSettingOptions_serializer {
    public static write(buffer: SerializerBase, value: FontSettingOptions): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForEnableVariableFontWeight = value.enableVariableFontWeight
        if (valueHolderForEnableVariableFontWeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableVariableFontWeightTmpValue = valueHolderForEnableVariableFontWeight!
            valueSerializer.writeBoolean(valueHolderForEnableVariableFontWeightTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): FontSettingOptions {
        let valueDeserializer: DeserializerBase = buffer
        const enableVariableFontWeightTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let enableVariableFontWeightTmpBuf: boolean | undefined = undefined
        if ((enableVariableFontWeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableVariableFontWeightTmpBuf = valueDeserializer.readBoolean()
        }
        const enableVariableFontWeightTmpResult: boolean | undefined = enableVariableFontWeightTmpBuf
        let value: FontSettingOptions = ({enableVariableFontWeight: enableVariableFontWeightTmpResult} as FontSettingOptions)
        return value
    }
}
export class FontWeightConfigs_serializer {
    public static write(buffer: SerializerBase, value: FontWeightConfigs): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForEnableVariableFontWeight = value.enableVariableFontWeight
        if (valueHolderForEnableVariableFontWeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableVariableFontWeightTmpValue = valueHolderForEnableVariableFontWeight!
            valueSerializer.writeBoolean(valueHolderForEnableVariableFontWeightTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnableDeviceFontWeightCategory = value.enableDeviceFontWeightCategory
        if (valueHolderForEnableDeviceFontWeightCategory !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableDeviceFontWeightCategoryTmpValue = valueHolderForEnableDeviceFontWeightCategory!
            valueSerializer.writeBoolean(valueHolderForEnableDeviceFontWeightCategoryTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): FontWeightConfigs {
        let valueDeserializer: DeserializerBase = buffer
        const enableVariableFontWeightTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let enableVariableFontWeightTmpBuf: boolean | undefined = undefined
        if ((enableVariableFontWeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableVariableFontWeightTmpBuf = valueDeserializer.readBoolean()
        }
        const enableVariableFontWeightTmpResult: boolean | undefined = enableVariableFontWeightTmpBuf
        const enableDeviceFontWeightCategoryTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let enableDeviceFontWeightCategoryTmpBuf: boolean | undefined = undefined
        if ((enableDeviceFontWeightCategoryTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableDeviceFontWeightCategoryTmpBuf = valueDeserializer.readBoolean()
        }
        const enableDeviceFontWeightCategoryTmpResult: boolean | undefined = enableDeviceFontWeightCategoryTmpBuf
        let value: FontWeightConfigs = ({enableVariableFontWeight: enableVariableFontWeightTmpResult, enableDeviceFontWeightCategory: enableDeviceFontWeightCategoryTmpResult} as FontWeightConfigs)
        return value
    }
}
export class InsertValue_serializer {
    public static write(buffer: SerializerBase, value: InsertValue): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForInsertOffset = value.insertOffset
        valueSerializer.writeInt32(valueHolderForInsertOffset)
        const valueHolderForInsertValue = value.insertValue
        valueSerializer.writeString(valueHolderForInsertValue)
    }
    public static read(buffer: DeserializerBase): InsertValue {
        let valueDeserializer: DeserializerBase = buffer
        const insertOffsetTmpResult: int32 = valueDeserializer.readInt32()
        const insertValueTmpResult: string = (valueDeserializer.readString() as string)
        let value: InsertValue = ({insertOffset: insertOffsetTmpResult, insertValue: insertValueTmpResult} as InsertValue)
        return value
    }
}
export class LineSpacingOptions_serializer {
    public static write(buffer: SerializerBase, value: LineSpacingOptions): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForOnlyBetweenLines = value.onlyBetweenLines
        if (valueHolderForOnlyBetweenLines !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnlyBetweenLinesTmpValue = valueHolderForOnlyBetweenLines!
            valueSerializer.writeBoolean(valueHolderForOnlyBetweenLinesTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): LineSpacingOptions {
        let valueDeserializer: DeserializerBase = buffer
        const onlyBetweenLinesTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let onlyBetweenLinesTmpBuf: boolean | undefined = undefined
        if ((onlyBetweenLinesTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            onlyBetweenLinesTmpBuf = valueDeserializer.readBoolean()
        }
        const onlyBetweenLinesTmpResult: boolean | undefined = onlyBetweenLinesTmpBuf
        let value: LineSpacingOptions = ({onlyBetweenLines: onlyBetweenLinesTmpResult} as LineSpacingOptions)
        return value
    }
}
export class MaxLinesOptions_serializer {
    public static write(buffer: SerializerBase, value: MaxLinesOptions): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForOverflowMode = value.overflowMode
        if (valueHolderForOverflowMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOverflowModeTmpValue = (valueHolderForOverflowMode as MaxLinesMode)
            valueSerializer.writeInt32(valueHolderForOverflowModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): MaxLinesOptions {
        let valueDeserializer: DeserializerBase = buffer
        const overflowModeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let overflowModeTmpBuf: MaxLinesMode | undefined = undefined
        if ((overflowModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            overflowModeTmpBuf = MaxLinesMode.fromValue(valueDeserializer.readInt32())
        }
        const overflowModeTmpResult: MaxLinesMode | undefined = overflowModeTmpBuf
        let value: MaxLinesOptions = ({overflowMode: overflowModeTmpResult} as MaxLinesOptions)
        return value
    }
}
export class NumericTextTransitionOptions_serializer {
    public static write(buffer: SerializerBase, value: NumericTextTransitionOptions): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForFlipDirection = value.flipDirection
        if (valueHolderForFlipDirection !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFlipDirectionTmpValue = (valueHolderForFlipDirection as FlipDirection)
            valueSerializer.writeInt32(valueHolderForFlipDirectionTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnableBlur = value.enableBlur
        if (valueHolderForEnableBlur !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableBlurTmpValue = valueHolderForEnableBlur!
            valueSerializer.writeBoolean(valueHolderForEnableBlurTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): NumericTextTransitionOptions {
        let valueDeserializer: DeserializerBase = buffer
        const flipDirectionTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let flipDirectionTmpBuf: FlipDirection | undefined = undefined
        if ((flipDirectionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            flipDirectionTmpBuf = FlipDirection.fromValue(valueDeserializer.readInt32())
        }
        const flipDirectionTmpResult: FlipDirection | undefined = flipDirectionTmpBuf
        const enableBlurTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let enableBlurTmpBuf: boolean | undefined = undefined
        if ((enableBlurTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableBlurTmpBuf = valueDeserializer.readBoolean()
        }
        const enableBlurTmpResult: boolean | undefined = enableBlurTmpBuf
        let value: NumericTextTransitionOptions = ({flipDirection: flipDirectionTmpResult, enableBlur: enableBlurTmpResult} as NumericTextTransitionOptions)
        return value
    }
}
export class PositionWithAffinity_serializer {
    public static write(buffer: SerializerBase, value: PositionWithAffinity): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForPosition = value.position
        valueSerializer.writeInt32(valueHolderForPosition)
        const valueHolderForAffinity = value.affinity
        valueSerializer.writeInt32(valueHolderForAffinity.valueOf())
    }
    public static read(buffer: DeserializerBase): PositionWithAffinity {
        let valueDeserializer: DeserializerBase = buffer
        const positionTmpResult: int32 = valueDeserializer.readInt32()
        const affinityTmpResult: Affinity = text.Affinity.fromValue(valueDeserializer.readInt32())
        let value: PositionWithAffinity = ({position: positionTmpResult, affinity: affinityTmpResult} as PositionWithAffinity)
        return value
    }
}
export class PreviewText_serializer {
    public static write(buffer: SerializerBase, value: PreviewText): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForOffset = value.offset
        valueSerializer.writeInt32(valueHolderForOffset)
        const valueHolderForValue = value.value
        valueSerializer.writeString(valueHolderForValue)
    }
    public static read(buffer: DeserializerBase): PreviewText {
        let valueDeserializer: DeserializerBase = buffer
        const offsetTmpResult: int32 = valueDeserializer.readInt32()
        const valueTmpResult: string = (valueDeserializer.readString() as string)
        let value: PreviewText = ({offset: offsetTmpResult, value: valueTmpResult} as PreviewText)
        return value
    }
}
export class StyledStringChangedListener_serializer {
    public static write(buffer: SerializerBase, value: StyledStringChangedListener): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForOnWillChange = value.onWillChange
        if (valueHolderForOnWillChange !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnWillChangeTmpValue = valueHolderForOnWillChange!
            valueSerializer.holdAndWriteCallback(valueHolderForOnWillChangeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnDidChange = value.onDidChange
        if (valueHolderForOnDidChange !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnDidChangeTmpValue = valueHolderForOnDidChange!
            valueSerializer.holdAndWriteCallback(valueHolderForOnDidChangeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): StyledStringChangedListener {
        let valueDeserializer: DeserializerBase = buffer
        const onWillChangeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let onWillChangeTmpBuf: arkui_component_common_Callback<StyledStringChangeValue, boolean> | undefined = undefined
        if ((onWillChangeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillChangeTmpBufOptBufResource: CallbackResource = valueDeserializer.readCallbackResource()
            const onWillChangeTmpBufOptBufCall: KPointer = valueDeserializer.readPointer()
            const onWillChangeTmpBufOptBufCallSync: KPointer = valueDeserializer.readPointer()
            const onWillChangeTmpBufOptClosure = (data: StyledStringChangeValue):boolean => {
                const onWillChangeTmpBufOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                onWillChangeTmpBufOptBufArgsSerializer.writeInt32(onWillChangeTmpBufOptBufResource.resourceId);
                onWillChangeTmpBufOptBufArgsSerializer.writePointer(onWillChangeTmpBufOptBufCall);
                onWillChangeTmpBufOptBufArgsSerializer.writePointer(onWillChangeTmpBufOptBufCallSync);
                StyledStringChangeValue_serializer.write(onWillChangeTmpBufOptBufArgsSerializer, data);
                let onWillChangeTmpBufOptBufContinuationValue: boolean | undefined;
                const onWillChangeTmpBufOptBufContinuationCallback: ((isSelected: boolean) => void) = (value: boolean):void => {
                onWillChangeTmpBufOptBufContinuationValue = value;
            }
                onWillChangeTmpBufOptBufArgsSerializer.holdAndWriteCallback(onWillChangeTmpBufOptBufContinuationCallback);
                InteropNativeModule._CallCallbackSync(10, 295315188, onWillChangeTmpBufOptBufArgsSerializer.asBuffer(), onWillChangeTmpBufOptBufArgsSerializer.length());
                onWillChangeTmpBufOptBufArgsSerializer.release();
                return (onWillChangeTmpBufOptBufContinuationValue as boolean);
            }
            resourceFinalizerRegister(onWillChangeTmpBufOptClosure, onWillChangeTmpBufOptBufResource)
            onWillChangeTmpBuf = onWillChangeTmpBufOptClosure
        }
        const onWillChangeTmpResult: arkui_component_common_Callback<StyledStringChangeValue, boolean> | undefined = onWillChangeTmpBuf
        const onDidChangeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let onDidChangeTmpBuf: OnDidChangeCallback | undefined = undefined
        if ((onDidChangeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidChangeTmpBufOptBufResource: CallbackResource = valueDeserializer.readCallbackResource()
            const onDidChangeTmpBufOptBufCall: KPointer = valueDeserializer.readPointer()
            const onDidChangeTmpBufOptBufCallSync: KPointer = valueDeserializer.readPointer()
            const onDidChangeTmpBufOptClosure = (rangeBefore: TextRange, rangeAfter: TextRange):void => {
                const onDidChangeTmpBufOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                onDidChangeTmpBufOptBufArgsSerializer.writeInt32(onDidChangeTmpBufOptBufResource.resourceId);
                onDidChangeTmpBufOptBufArgsSerializer.writePointer(onDidChangeTmpBufOptBufCall);
                onDidChangeTmpBufOptBufArgsSerializer.writePointer(onDidChangeTmpBufOptBufCallSync);
                TextRange_serializer.write(onDidChangeTmpBufOptBufArgsSerializer, rangeBefore);
                TextRange_serializer.write(onDidChangeTmpBufOptBufArgsSerializer, rangeAfter);
                InteropNativeModule._CallCallbackSync(10, 1673645397, onDidChangeTmpBufOptBufArgsSerializer.asBuffer(), onDidChangeTmpBufOptBufArgsSerializer.length());
                onDidChangeTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onDidChangeTmpBufOptClosure, onDidChangeTmpBufOptBufResource)
            onDidChangeTmpBuf = onDidChangeTmpBufOptClosure
        }
        const onDidChangeTmpResult: OnDidChangeCallback | undefined = onDidChangeTmpBuf
        let value: StyledStringChangedListener = ({onWillChange: onWillChangeTmpResult, onDidChange: onDidChangeTmpResult} as StyledStringChangedListener)
        return value
    }
}
export class TextMenuOptions_serializer {
    public static write(buffer: SerializerBase, value: TextMenuOptions): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForShowMode = value.showMode
        if (valueHolderForShowMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShowModeTmpValue = (valueHolderForShowMode as TextMenuShowMode)
            valueSerializer.writeInt32(valueHolderForShowModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TextMenuOptions {
        let valueDeserializer: DeserializerBase = buffer
        const showModeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let showModeTmpBuf: TextMenuShowMode | undefined = undefined
        if ((showModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            showModeTmpBuf = TextMenuShowMode.fromValue(valueDeserializer.readInt32())
        }
        const showModeTmpResult: TextMenuShowMode | undefined = showModeTmpBuf
        let value: TextMenuOptions = ({showMode: showModeTmpResult} as TextMenuOptions)
        return value
    }
}
export class TextRange_serializer {
    public static write(buffer: SerializerBase, value: TextRange): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForStart = value.start
        if (valueHolderForStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartTmpValue = valueHolderForStart!
            valueSerializer.writeInt32(valueHolderForStartTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnd = value.end
        if (valueHolderForEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndTmpValue = valueHolderForEnd!
            valueSerializer.writeInt32(valueHolderForEndTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TextRange {
        let valueDeserializer: DeserializerBase = buffer
        const startTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let startTmpBuf: int32 | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startTmpBuf = valueDeserializer.readInt32()
        }
        const startTmpResult: int32 | undefined = startTmpBuf
        const endTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let endTmpBuf: int32 | undefined = undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endTmpBuf = valueDeserializer.readInt32()
        }
        const endTmpResult: int32 | undefined = endTmpBuf
        let value: TextRange = ({start: startTmpResult, end: endTmpResult} as TextRange)
        return value
    }
}
export class VoiceButtonOptions_serializer {
    public static write(buffer: SerializerBase, value: VoiceButtonOptions): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForEnabled = value.enabled
        if (valueHolderForEnabled !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnabledTmpValue = valueHolderForEnabled!
            valueSerializer.writeBoolean(valueHolderForEnabledTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): VoiceButtonOptions {
        let valueDeserializer: DeserializerBase = buffer
        const enabledTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let enabledTmpBuf: boolean | undefined = undefined
        if ((enabledTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enabledTmpBuf = valueDeserializer.readBoolean()
        }
        const enabledTmpResult: boolean | undefined = enabledTmpBuf
        let value: VoiceButtonOptions = ({enabled: enabledTmpResult} as VoiceButtonOptions)
        return value
    }
}
export class AccessibilitySpanOptions_serializer {
    public static write(buffer: SerializerBase, value: AccessibilitySpanOptions): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForAccessibilityText = value.accessibilityText
        if (valueHolderForAccessibilityText !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAccessibilityTextTmpValue = valueHolderForAccessibilityText!
            if (valueHolderForAccessibilityTextTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForAccessibilityTextTmpValueForIdx0 = valueHolderForAccessibilityTextTmpValue as string
                valueSerializer.writeString(valueHolderForAccessibilityTextTmpValueForIdx0)
            } else if (valueHolderForAccessibilityTextTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForAccessibilityTextTmpValueForIdx1 = valueHolderForAccessibilityTextTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForAccessibilityTextTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAccessibilityDescription = value.accessibilityDescription
        if (valueHolderForAccessibilityDescription !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAccessibilityDescriptionTmpValue = valueHolderForAccessibilityDescription!
            if (valueHolderForAccessibilityDescriptionTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForAccessibilityDescriptionTmpValueForIdx0 = valueHolderForAccessibilityDescriptionTmpValue as string
                valueSerializer.writeString(valueHolderForAccessibilityDescriptionTmpValueForIdx0)
            } else if (valueHolderForAccessibilityDescriptionTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForAccessibilityDescriptionTmpValueForIdx1 = valueHolderForAccessibilityDescriptionTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForAccessibilityDescriptionTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAccessibilityLevel = value.accessibilityLevel
        if (valueHolderForAccessibilityLevel !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAccessibilityLevelTmpValue = valueHolderForAccessibilityLevel!
            valueSerializer.writeString(valueHolderForAccessibilityLevelTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): AccessibilitySpanOptions {
        let valueDeserializer: DeserializerBase = buffer
        const accessibilityTextTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let accessibilityTextTmpBuf: ResourceStr | undefined = undefined
        if ((accessibilityTextTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const accessibilityTextTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let accessibilityTextTmpBufOpt: string | arkui_component_units_Resource | undefined
            if (accessibilityTextTmpBufOptUnionSelector == (0).toByte()) {
                accessibilityTextTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (accessibilityTextTmpBufOptUnionSelector == (1).toByte()) {
                accessibilityTextTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for accessibilityTextTmpBufOpt has to be chosen through deserialisation.')
            }
            accessibilityTextTmpBuf = (accessibilityTextTmpBufOpt as string | arkui_component_units_Resource)
        }
        const accessibilityTextTmpResult: ResourceStr | undefined = accessibilityTextTmpBuf
        const accessibilityDescriptionTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let accessibilityDescriptionTmpBuf: ResourceStr | undefined = undefined
        if ((accessibilityDescriptionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const accessibilityDescriptionTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let accessibilityDescriptionTmpBufOpt: string | arkui_component_units_Resource | undefined
            if (accessibilityDescriptionTmpBufOptUnionSelector == (0).toByte()) {
                accessibilityDescriptionTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (accessibilityDescriptionTmpBufOptUnionSelector == (1).toByte()) {
                accessibilityDescriptionTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for accessibilityDescriptionTmpBufOpt has to be chosen through deserialisation.')
            }
            accessibilityDescriptionTmpBuf = (accessibilityDescriptionTmpBufOpt as string | arkui_component_units_Resource)
        }
        const accessibilityDescriptionTmpResult: ResourceStr | undefined = accessibilityDescriptionTmpBuf
        const accessibilityLevelTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let accessibilityLevelTmpBuf: string | undefined = undefined
        if ((accessibilityLevelTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            accessibilityLevelTmpBuf = (valueDeserializer.readString() as string)
        }
        const accessibilityLevelTmpResult: string | undefined = accessibilityLevelTmpBuf
        let value: AccessibilitySpanOptions = ({accessibilityText: accessibilityTextTmpResult, accessibilityDescription: accessibilityDescriptionTmpResult, accessibilityLevel: accessibilityLevelTmpResult} as AccessibilitySpanOptions)
        return value
    }
}
export class DecorationStyleResult_serializer {
    public static write(buffer: SerializerBase, value: DecorationStyleResult): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForType = value.type
        valueSerializer.writeInt32(valueHolderForType.valueOf())
        const valueHolderForColor = value.color
        if (valueHolderForColor instanceof arkui_component_enums_Color) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForColorForIdx0 = valueHolderForColor as arkui_component_enums_Color
            valueSerializer.writeInt32((valueHolderForColorForIdx0.getOrdinal()) % (12))
        } else if (valueHolderForColor instanceof int32) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForColorForIdx1 = valueHolderForColor as int32
            valueSerializer.writeInt32(valueHolderForColorForIdx1)
        } else if (valueHolderForColor instanceof string) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForColorForIdx2 = valueHolderForColor as string
            valueSerializer.writeString(valueHolderForColorForIdx2)
        } else if (valueHolderForColor instanceof arkui_component_units_Resource) {
            valueSerializer.writeInt8((3).toByte())
            const valueHolderForColorForIdx3 = valueHolderForColor as arkui_component_units_Resource
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForColorForIdx3)
        }
        const valueHolderForStyle = value.style
        if (valueHolderForStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStyleTmpValue = (valueHolderForStyle as TextDecorationStyle)
            valueSerializer.writeInt32(valueHolderForStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForThicknessScale = value.thicknessScale
        if (valueHolderForThicknessScale !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForThicknessScaleTmpValue = valueHolderForThicknessScale!
            valueSerializer.writeFloat64(valueHolderForThicknessScaleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): DecorationStyleResult {
        let valueDeserializer: DeserializerBase = buffer
        const typeTmpResult: TextDecorationType = TextDecorationType.fromValue(valueDeserializer.readInt32())
        const colorTmpBufUnionSelector: int32 = valueDeserializer.readInt8()
        let colorTmpBuf: arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
        if (colorTmpBufUnionSelector == (0).toByte()) {
            colorTmpBuf = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
        } else if (colorTmpBufUnionSelector == (1).toByte()) {
            colorTmpBuf = valueDeserializer.readInt32()
        } else if (colorTmpBufUnionSelector == (2).toByte()) {
            colorTmpBuf = (valueDeserializer.readString() as string)
        } else if (colorTmpBufUnionSelector == (3).toByte()) {
            colorTmpBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for colorTmpBuf has to be chosen through deserialisation.')
        }
        const colorTmpResult: ResourceColor = (colorTmpBuf as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        const styleTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let styleTmpBuf: TextDecorationStyle | undefined = undefined
        if ((styleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            styleTmpBuf = TextDecorationStyle.fromValue(valueDeserializer.readInt32())
        }
        const styleTmpResult: TextDecorationStyle | undefined = styleTmpBuf
        const thicknessScaleTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let thicknessScaleTmpBuf: double | undefined = undefined
        if ((thicknessScaleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            thicknessScaleTmpBuf = valueDeserializer.readFloat64()
        }
        const thicknessScaleTmpResult: double | undefined = thicknessScaleTmpBuf
        let value: DecorationStyleResult = ({type: typeTmpResult, color: colorTmpResult, style: styleTmpResult, thicknessScale: thicknessScaleTmpResult} as DecorationStyleResult)
        return value
    }
}
export class FontConfigs_serializer {
    public static write(buffer: SerializerBase, value: FontConfigs): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForFontWeightConfigs = value.fontWeightConfigs
        if (valueHolderForFontWeightConfigs !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFontWeightConfigsTmpValue = valueHolderForFontWeightConfigs!
            FontWeightConfigs_serializer.write(valueSerializer, valueHolderForFontWeightConfigsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): FontConfigs {
        let valueDeserializer: DeserializerBase = buffer
        const fontWeightConfigsTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let fontWeightConfigsTmpBuf: FontWeightConfigs | undefined = undefined
        if ((fontWeightConfigsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fontWeightConfigsTmpBuf = FontWeightConfigs_serializer.read(valueDeserializer)
        }
        const fontWeightConfigsTmpResult: FontWeightConfigs | undefined = fontWeightConfigsTmpBuf
        let value: FontConfigs = ({fontWeightConfigs: fontWeightConfigsTmpResult} as FontConfigs)
        return value
    }
}
export class SelectedDragPreviewStyle_serializer {
    public static write(buffer: SerializerBase, value: SelectedDragPreviewStyle): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForColor = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue = valueHolderForColor!
            if (valueHolderForColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForColorTmpValueForIdx0 = valueHolderForColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForColorTmpValueForIdx1 = valueHolderForColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx1)
            } else if (valueHolderForColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForColorTmpValueForIdx2 = valueHolderForColorTmpValue as string
                valueSerializer.writeString(valueHolderForColorTmpValueForIdx2)
            } else if (valueHolderForColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForColorTmpValueForIdx3 = valueHolderForColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SelectedDragPreviewStyle {
        let valueDeserializer: DeserializerBase = buffer
        const colorTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let colorTmpBuf: ResourceColor | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let colorTmpBufOpt: arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
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
        const colorTmpResult: ResourceColor | undefined = colorTmpBuf
        let value: SelectedDragPreviewStyle = ({color: colorTmpResult} as SelectedDragPreviewStyle)
        return value
    }
}
export class StyledStringChangeValue_serializer {
    public static write(buffer: SerializerBase, value: StyledStringChangeValue): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForRange = value.range
        TextRange_serializer.write(valueSerializer, valueHolderForRange)
        const valueHolderForReplacementString = value.replacementString
        StyledString_serializer.write(valueSerializer, valueHolderForReplacementString)
        const valueHolderForPreviewText = value.previewText
        if (valueHolderForPreviewText !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPreviewTextTmpValue = valueHolderForPreviewText!
            StyledString_serializer.write(valueSerializer, valueHolderForPreviewTextTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): StyledStringChangeValue {
        let valueDeserializer: DeserializerBase = buffer
        const rangeTmpResult: TextRange = TextRange_serializer.read(valueDeserializer)
        const replacementStringTmpResult: StyledString = (StyledString_serializer.read(valueDeserializer) as StyledString)
        const previewTextTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let previewTextTmpBuf: StyledString | undefined = undefined
        if ((previewTextTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            previewTextTmpBuf = (StyledString_serializer.read(valueDeserializer) as StyledString)
        }
        const previewTextTmpResult: StyledString | undefined = previewTextTmpBuf
        let value: StyledStringChangeValue = ({range: rangeTmpResult, replacementString: replacementStringTmpResult, previewText: previewTextTmpResult} as StyledStringChangeValue)
        return value
    }
}
export class TextChangeOptions_serializer {
    public static write(buffer: SerializerBase, value: TextChangeOptions): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForRangeBefore = value.rangeBefore
        TextRange_serializer.write(valueSerializer, valueHolderForRangeBefore)
        const valueHolderForRangeAfter = value.rangeAfter
        TextRange_serializer.write(valueSerializer, valueHolderForRangeAfter)
        const valueHolderForOldContent = value.oldContent
        valueSerializer.writeString(valueHolderForOldContent)
        const valueHolderForOldPreviewText = value.oldPreviewText
        PreviewText_serializer.write(valueSerializer, valueHolderForOldPreviewText)
    }
    public static read(buffer: DeserializerBase): TextChangeOptions {
        let valueDeserializer: DeserializerBase = buffer
        const rangeBeforeTmpResult: TextRange = TextRange_serializer.read(valueDeserializer)
        const rangeAfterTmpResult: TextRange = TextRange_serializer.read(valueDeserializer)
        const oldContentTmpResult: string = (valueDeserializer.readString() as string)
        const oldPreviewTextTmpResult: PreviewText = PreviewText_serializer.read(valueDeserializer)
        let value: TextChangeOptions = ({rangeBefore: rangeBeforeTmpResult, rangeAfter: rangeAfterTmpResult, oldContent: oldContentTmpResult, oldPreviewText: oldPreviewTextTmpResult} as TextChangeOptions)
        return value
    }
}
export class TextMenuItem_serializer {
    public static write(buffer: SerializerBase, value: TextMenuItem): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForContent = value.content
        if (valueHolderForContent instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForContentForIdx0 = valueHolderForContent as string
            valueSerializer.writeString(valueHolderForContentForIdx0)
        } else if (valueHolderForContent instanceof arkui_component_units_Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForContentForIdx1 = valueHolderForContent as arkui_component_units_Resource
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForContentForIdx1)
        }
        const valueHolderForIcon = value.icon
        if (valueHolderForIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIconTmpValue = valueHolderForIcon!
            if (valueHolderForIconTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForIconTmpValueForIdx0 = valueHolderForIconTmpValue as string
                valueSerializer.writeString(valueHolderForIconTmpValueForIdx0)
            } else if (valueHolderForIconTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForIconTmpValueForIdx1 = valueHolderForIconTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForIconTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForId = value.id
        TextMenuItemId_serializer.write(valueSerializer, valueHolderForId)
        const valueHolderForLabelInfo = value.labelInfo
        if (valueHolderForLabelInfo !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLabelInfoTmpValue = valueHolderForLabelInfo!
            if (valueHolderForLabelInfoTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForLabelInfoTmpValueForIdx0 = valueHolderForLabelInfoTmpValue as string
                valueSerializer.writeString(valueHolderForLabelInfoTmpValueForIdx0)
            } else if (valueHolderForLabelInfoTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForLabelInfoTmpValueForIdx1 = valueHolderForLabelInfoTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForLabelInfoTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TextMenuItem {
        let valueDeserializer: DeserializerBase = buffer
        const contentTmpBufUnionSelector: int32 = valueDeserializer.readInt8()
        let contentTmpBuf: string | arkui_component_units_Resource | undefined
        if (contentTmpBufUnionSelector == (0).toByte()) {
            contentTmpBuf = (valueDeserializer.readString() as string)
        } else if (contentTmpBufUnionSelector == (1).toByte()) {
            contentTmpBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for contentTmpBuf has to be chosen through deserialisation.')
        }
        const contentTmpResult: ResourceStr = (contentTmpBuf as string | arkui_component_units_Resource)
        const iconTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let iconTmpBuf: ResourceStr | undefined = undefined
        if ((iconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const iconTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let iconTmpBufOpt: string | arkui_component_units_Resource | undefined
            if (iconTmpBufOptUnionSelector == (0).toByte()) {
                iconTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (iconTmpBufOptUnionSelector == (1).toByte()) {
                iconTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for iconTmpBufOpt has to be chosen through deserialisation.')
            }
            iconTmpBuf = (iconTmpBufOpt as string | arkui_component_units_Resource)
        }
        const iconTmpResult: ResourceStr | undefined = iconTmpBuf
        const idTmpResult: TextMenuItemId = (TextMenuItemId_serializer.read(valueDeserializer) as TextMenuItemId)
        const labelInfoTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let labelInfoTmpBuf: ResourceStr | undefined = undefined
        if ((labelInfoTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const labelInfoTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let labelInfoTmpBufOpt: string | arkui_component_units_Resource | undefined
            if (labelInfoTmpBufOptUnionSelector == (0).toByte()) {
                labelInfoTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (labelInfoTmpBufOptUnionSelector == (1).toByte()) {
                labelInfoTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for labelInfoTmpBufOpt has to be chosen through deserialisation.')
            }
            labelInfoTmpBuf = (labelInfoTmpBufOpt as string | arkui_component_units_Resource)
        }
        const labelInfoTmpResult: ResourceStr | undefined = labelInfoTmpBuf
        let value: TextMenuItem = ({content: contentTmpResult, icon: iconTmpResult, id: idTmpResult, labelInfo: labelInfoTmpResult} as TextMenuItem)
        return value
    }
}
export class CaretStyle_serializer {
    public static write(buffer: SerializerBase, value: CaretStyle): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForWidth = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForWidthTmpValueForIdx0 = valueHolderForWidthTmpValue as string
                valueSerializer.writeString(valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForWidthTmpValueForIdx1 = valueHolderForWidthTmpValue as double
                valueSerializer.writeFloat64(valueHolderForWidthTmpValueForIdx1)
            } else if (valueHolderForWidthTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForWidthTmpValueForIdx2 = valueHolderForWidthTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForColor = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue = valueHolderForColor!
            if (valueHolderForColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForColorTmpValueForIdx0 = valueHolderForColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForColorTmpValueForIdx1 = valueHolderForColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx1)
            } else if (valueHolderForColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForColorTmpValueForIdx2 = valueHolderForColorTmpValue as string
                valueSerializer.writeString(valueHolderForColorTmpValueForIdx2)
            } else if (valueHolderForColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForColorTmpValueForIdx3 = valueHolderForColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): CaretStyle {
        let valueDeserializer: DeserializerBase = buffer
        const widthTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let widthTmpBuf: Length | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let widthTmpBufOpt: string | double | arkui_component_units_Resource | undefined
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
        const widthTmpResult: Length | undefined = widthTmpBuf
        const colorTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let colorTmpBuf: ResourceColor | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let colorTmpBufOpt: arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
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
        const colorTmpResult: ResourceColor | undefined = colorTmpBuf
        let value: CaretStyle = ({width: widthTmpResult, color: colorTmpResult} as CaretStyle)
        return value
    }
}
export class EditableTextChangeValue_serializer {
    public static write(buffer: SerializerBase, value: EditableTextChangeValue): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForContent = value.content
        valueSerializer.writeString(valueHolderForContent)
        const valueHolderForPreviewText = value.previewText
        if (valueHolderForPreviewText !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPreviewTextTmpValue = valueHolderForPreviewText!
            PreviewText_serializer.write(valueSerializer, valueHolderForPreviewTextTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOptions = value.options
        if (valueHolderForOptions !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOptionsTmpValue = valueHolderForOptions!
            TextChangeOptions_serializer.write(valueSerializer, valueHolderForOptionsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): EditableTextChangeValue {
        let valueDeserializer: DeserializerBase = buffer
        const contentTmpResult: string = (valueDeserializer.readString() as string)
        const previewTextTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let previewTextTmpBuf: PreviewText | undefined = undefined
        if ((previewTextTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            previewTextTmpBuf = PreviewText_serializer.read(valueDeserializer)
        }
        const previewTextTmpResult: PreviewText | undefined = previewTextTmpBuf
        const optionsTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let optionsTmpBuf: TextChangeOptions | undefined = undefined
        if ((optionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            optionsTmpBuf = TextChangeOptions_serializer.read(valueDeserializer)
        }
        const optionsTmpResult: TextChangeOptions | undefined = optionsTmpBuf
        let value: EditableTextChangeValue = ({content: contentTmpResult, previewText: previewTextTmpResult, options: optionsTmpResult} as EditableTextChangeValue)
        return value
    }
}
export class TextDataDetectorConfig_serializer {
    public static write(buffer: SerializerBase, value: TextDataDetectorConfig): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForTypes = value.types
        if (valueHolderForTypes !== undefined && valueHolderForTypes !== null) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTypesTmpValue = valueHolderForTypes!
            valueSerializer.writeInt32((valueHolderForTypesTmpValue.length).toInt())
            for (let valueHolderForTypesTmpValueCounterI = 0; valueHolderForTypesTmpValueCounterI < valueHolderForTypesTmpValue.length; valueHolderForTypesTmpValueCounterI++) {
                const valueHolderForTypesTmpValueTmpElement: TextDataDetectorType = valueHolderForTypesTmpValue[valueHolderForTypesTmpValueCounterI]
                valueSerializer.writeInt32(valueHolderForTypesTmpValueTmpElement.valueOf())
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnDetectResultUpdate = value.onDetectResultUpdate
        if (valueHolderForOnDetectResultUpdate !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnDetectResultUpdateTmpValue = valueHolderForOnDetectResultUpdate!
            valueSerializer.holdAndWriteCallback(valueHolderForOnDetectResultUpdateTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForColor = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue = valueHolderForColor!
            if (valueHolderForColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForColorTmpValueForIdx0 = valueHolderForColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForColorTmpValueForIdx1 = valueHolderForColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx1)
            } else if (valueHolderForColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForColorTmpValueForIdx2 = valueHolderForColorTmpValue as string
                valueSerializer.writeString(valueHolderForColorTmpValueForIdx2)
            } else if (valueHolderForColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForColorTmpValueForIdx3 = valueHolderForColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDecoration = value.decoration
        if (valueHolderForDecoration !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDecorationTmpValue = valueHolderForDecoration!
            DecorationStyleInterface_serializer.write(valueSerializer, valueHolderForDecorationTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnablePreviewMenu = value.enablePreviewMenu
        if (valueHolderForEnablePreviewMenu !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnablePreviewMenuTmpValue = valueHolderForEnablePreviewMenu!
            valueSerializer.writeBoolean(valueHolderForEnablePreviewMenuTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TextDataDetectorConfig {
        let valueDeserializer: DeserializerBase = buffer
        const typesTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let typesTmpBuf: Array<TextDataDetectorType> | null | undefined = undefined
        if ((typesTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const typesTmpBufOptLength: int32 = valueDeserializer.readInt32()
            let typesTmpBufOpt: Array<TextDataDetectorType> = new Array<TextDataDetectorType>(typesTmpBufOptLength)
            for (let typesTmpBufOptBufCounterI = 0; typesTmpBufOptBufCounterI < typesTmpBufOptLength; typesTmpBufOptBufCounterI++) {
                typesTmpBufOpt[typesTmpBufOptBufCounterI] = TextDataDetectorType.fromValue(valueDeserializer.readInt32())
            }
            typesTmpBuf = typesTmpBufOpt
        }
        const typesTmpResult: Array<TextDataDetectorType> | null | undefined = typesTmpBuf
        const onDetectResultUpdateTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let onDetectResultUpdateTmpBuf: arkui_component_common_Callback<string, void> | undefined = undefined
        if ((onDetectResultUpdateTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDetectResultUpdateTmpBufOptBufResource: CallbackResource = valueDeserializer.readCallbackResource()
            const onDetectResultUpdateTmpBufOptBufCall: KPointer = valueDeserializer.readPointer()
            const onDetectResultUpdateTmpBufOptBufCallSync: KPointer = valueDeserializer.readPointer()
            const onDetectResultUpdateTmpBufOptClosure = (data: string):void => {
                const onDetectResultUpdateTmpBufOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                onDetectResultUpdateTmpBufOptBufArgsSerializer.writeInt32(onDetectResultUpdateTmpBufOptBufResource.resourceId);
                onDetectResultUpdateTmpBufOptBufArgsSerializer.writePointer(onDetectResultUpdateTmpBufOptBufCall);
                onDetectResultUpdateTmpBufOptBufArgsSerializer.writePointer(onDetectResultUpdateTmpBufOptBufCallSync);
                onDetectResultUpdateTmpBufOptBufArgsSerializer.writeString(data);
                InteropNativeModule._CallCallbackSync(10, 657413210, onDetectResultUpdateTmpBufOptBufArgsSerializer.asBuffer(), onDetectResultUpdateTmpBufOptBufArgsSerializer.length());
                onDetectResultUpdateTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onDetectResultUpdateTmpBufOptClosure, onDetectResultUpdateTmpBufOptBufResource)
            onDetectResultUpdateTmpBuf = onDetectResultUpdateTmpBufOptClosure
        }
        const onDetectResultUpdateTmpResult: arkui_component_common_Callback<string, void> | undefined = onDetectResultUpdateTmpBuf
        const colorTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let colorTmpBuf: ResourceColor | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let colorTmpBufOpt: arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
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
        const colorTmpResult: ResourceColor | undefined = colorTmpBuf
        const decorationTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let decorationTmpBuf: DecorationStyleInterface | undefined = undefined
        if ((decorationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            decorationTmpBuf = DecorationStyleInterface_serializer.read(valueDeserializer)
        }
        const decorationTmpResult: DecorationStyleInterface | undefined = decorationTmpBuf
        const enablePreviewMenuTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let enablePreviewMenuTmpBuf: boolean | undefined = undefined
        if ((enablePreviewMenuTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enablePreviewMenuTmpBuf = valueDeserializer.readBoolean()
        }
        const enablePreviewMenuTmpResult: boolean | undefined = enablePreviewMenuTmpBuf
        let value: TextDataDetectorConfig = ({types: typesTmpResult, onDetectResultUpdate: onDetectResultUpdateTmpResult, color: colorTmpResult, decoration: decorationTmpResult, enablePreviewMenu: enablePreviewMenuTmpResult} as TextDataDetectorConfig)
        return value
    }
}
export class ColorShaderStyleInternal {
    public static fromPtr(ptr: KPointer): ColorShaderStyle {
        return new ColorShaderStyle(MaterializedBaseTag.NOP, ptr)
    }
}
export class ColorShaderStyle extends ShaderStyle implements MaterializedBase {
    public color: ResourceColor
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
        this.color = this.getColor()
    }
    constructor(color: ResourceColor) {
        this(MaterializedBaseTag.NOP, ColorShaderStyle.construct(color))
        this.color = this.getColor()
    }
    static construct(color: ResourceColor): KPointer {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (color instanceof arkui_component_enums_Color) {
            thisSerializer.writeInt8((0).toByte())
            const colorForIdx0 = color as arkui_component_enums_Color
            thisSerializer.writeInt32((colorForIdx0.getOrdinal()) % (12))
        } else if (color instanceof int32) {
            thisSerializer.writeInt8((1).toByte())
            const colorForIdx1 = color as int32
            thisSerializer.writeInt32(colorForIdx1)
        } else if (color instanceof string) {
            thisSerializer.writeInt8((2).toByte())
            const colorForIdx2 = color as string
            thisSerializer.writeString(colorForIdx2)
        } else if (color instanceof arkui_component_units_Resource) {
            thisSerializer.writeInt8((3).toByte())
            const colorForIdx3 = color as arkui_component_units_Resource
            global_resource_Resource_serializer.write(thisSerializer, colorForIdx3)
        }
        const retval = ArkUIGeneratedNativeModule._ColorShaderStyle_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ColorShaderStyle_getFinalizer()
    }
    private getColor(): ResourceColor {
        return this.getColor_serialize()
    }
    private setColor(color: ResourceColor): void {
        const color_casted = color as (ResourceColor)
        this.setColor_serialize(color_casted)
        return
    }
    private getColor_serialize(): ResourceColor {
        const retval = ArkUIGeneratedNativeModule._ColorShaderStyle_getColor(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferUnionSelector: int32 = retvalDeserializer.readInt8()
        let buffer: arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
        if (bufferUnionSelector == (0).toByte()) {
            buffer = arkui_component_enums_Color.values()[retvalDeserializer.readInt32()]
        } else if (bufferUnionSelector == (1).toByte()) {
            buffer = retvalDeserializer.readInt32()
        } else if (bufferUnionSelector == (2).toByte()) {
            buffer = (retvalDeserializer.readString() as string)
        } else if (bufferUnionSelector == (3).toByte()) {
            buffer = global_resource_Resource_serializer.read(retvalDeserializer)
        } else {
            throw new Error('One of the branches for buffer has to be chosen through deserialisation.')
        }
        const returnResult: ResourceColor = (buffer as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        return returnResult
    }
    private setColor_serialize(color: ResourceColor): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (color instanceof arkui_component_enums_Color) {
            thisSerializer.writeInt8((0).toByte())
            const colorForIdx0 = color as arkui_component_enums_Color
            thisSerializer.writeInt32((colorForIdx0.getOrdinal()) % (12))
        } else if (color instanceof int32) {
            thisSerializer.writeInt8((1).toByte())
            const colorForIdx1 = color as int32
            thisSerializer.writeInt32(colorForIdx1)
        } else if (color instanceof string) {
            thisSerializer.writeInt8((2).toByte())
            const colorForIdx2 = color as string
            thisSerializer.writeString(colorForIdx2)
        } else if (color instanceof arkui_component_units_Resource) {
            thisSerializer.writeInt8((3).toByte())
            const colorForIdx3 = color as arkui_component_units_Resource
            global_resource_Resource_serializer.write(thisSerializer, colorForIdx3)
        }
        ArkUIGeneratedNativeModule._ColorShaderStyle_setColor(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class LinearGradientStyleInternal {
    public static fromPtr(ptr: KPointer): LinearGradientStyle {
        return new LinearGradientStyle(MaterializedBaseTag.NOP, ptr)
    }
}
export class LinearGradientStyle extends ShaderStyle implements MaterializedBase {
    public options: LinearGradientOptions
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
        this.options = this.getOptions()
    }
    constructor(options: LinearGradientOptions) {
        this(MaterializedBaseTag.NOP, LinearGradientStyle.construct(options))
        this.options = this.getOptions()
    }
    static construct(options: LinearGradientOptions): KPointer {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        LinearGradientOptions_serializer.write(thisSerializer, options)
        const retval = ArkUIGeneratedNativeModule._LinearGradientStyle_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LinearGradientStyle_getFinalizer()
    }
    private getOptions(): LinearGradientOptions {
        return this.getOptions_serialize()
    }
    private setOptions(options: LinearGradientOptions): void {
        const options_casted = options as (LinearGradientOptions)
        this.setOptions_serialize(options_casted)
        return
    }
    private getOptions_serialize(): LinearGradientOptions {
        const retval = ArkUIGeneratedNativeModule._LinearGradientStyle_getOptions(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: LinearGradientOptions = LinearGradientOptions_serializer.read(retvalDeserializer)
        return returnResult
    }
    private setOptions_serialize(options: LinearGradientOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        LinearGradientOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._LinearGradientStyle_setOptions(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class NumericTextTransitionInternal {
    public static fromPtr(ptr: KPointer): NumericTextTransition {
        return new NumericTextTransition(MaterializedBaseTag.NOP, ptr)
    }
}
export class NumericTextTransition extends ContentTransition implements MaterializedBase {
    public flipDirection?: FlipDirection | undefined
    public enableBlur?: boolean | undefined
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
        this.flipDirection = this.getFlipDirection()
        this.enableBlur = this.getEnableBlur()
    }
    constructor(options?: NumericTextTransitionOptions) {
        this(MaterializedBaseTag.NOP, NumericTextTransition.construct(options))
        this.flipDirection = this.getFlipDirection()
        this.enableBlur = this.getEnableBlur()
    }
    static construct(options?: NumericTextTransitionOptions): KPointer {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue = options!
            NumericTextTransitionOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval = ArkUIGeneratedNativeModule._NumericTextTransition_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._NumericTextTransition_getFinalizer()
    }
    private getFlipDirection(): FlipDirection | undefined {
        return this.getFlipDirection_serialize()
    }
    private setFlipDirection(flipDirection: FlipDirection | undefined): void {
        const flipDirection_casted = flipDirection as (FlipDirection | undefined)
        this.setFlipDirection_serialize(flipDirection_casted)
        return
    }
    private getEnableBlur(): boolean | undefined {
        return this.getEnableBlur_serialize()
    }
    private setEnableBlur(enableBlur: boolean | undefined): void {
        const enableBlur_casted = enableBlur as (boolean | undefined)
        this.setEnableBlur_serialize(enableBlur_casted)
        return
    }
    private getFlipDirection_serialize(): FlipDirection | undefined {
        const retval = ArkUIGeneratedNativeModule._NumericTextTransition_getFlipDirection(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType = retvalDeserializer.readInt8()!.toInt()
        let buffer: FlipDirection | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = FlipDirection.fromValue(retvalDeserializer.readInt32())
        }
        const returnResult: FlipDirection | undefined = buffer
        return returnResult
    }
    private setFlipDirection_serialize(flipDirection: FlipDirection | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (flipDirection !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const flipDirectionTmpValue = (flipDirection as FlipDirection)
            thisSerializer.writeInt32(flipDirectionTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NumericTextTransition_setFlipDirection(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getEnableBlur_serialize(): boolean | undefined {
        const retval = ArkUIGeneratedNativeModule._NumericTextTransition_getEnableBlur(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType = retvalDeserializer.readInt8()!.toInt()
        let buffer: boolean | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = retvalDeserializer.readBoolean()
        }
        const returnResult: boolean | undefined = buffer
        return returnResult
    }
    private setEnableBlur_serialize(enableBlur: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (enableBlur !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const enableBlurTmpValue = enableBlur!
            thisSerializer.writeBoolean(enableBlurTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NumericTextTransition_setEnableBlur(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class RadialGradientStyleInternal {
    public static fromPtr(ptr: KPointer): RadialGradientStyle {
        return new RadialGradientStyle(MaterializedBaseTag.NOP, ptr)
    }
}
export class RadialGradientStyle extends ShaderStyle implements MaterializedBase {
    public options: RadialGradientOptions
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
        this.options = this.getOptions()
    }
    constructor(options: RadialGradientOptions) {
        this(MaterializedBaseTag.NOP, RadialGradientStyle.construct(options))
        this.options = this.getOptions()
    }
    static construct(options: RadialGradientOptions): KPointer {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        RadialGradientOptions_serializer.write(thisSerializer, options)
        const retval = ArkUIGeneratedNativeModule._RadialGradientStyle_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RadialGradientStyle_getFinalizer()
    }
    private getOptions(): RadialGradientOptions {
        return this.getOptions_serialize()
    }
    private setOptions(options: RadialGradientOptions): void {
        const options_casted = options as (RadialGradientOptions)
        this.setOptions_serialize(options_casted)
        return
    }
    private getOptions_serialize(): RadialGradientOptions {
        const retval = ArkUIGeneratedNativeModule._RadialGradientStyle_getOptions(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: RadialGradientOptions = RadialGradientOptions_serializer.read(retvalDeserializer)
        return returnResult
    }
    private setOptions_serialize(options: RadialGradientOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        RadialGradientOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._RadialGradientStyle_setOptions(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface TextEditControllerEx extends TextBaseController {
    isEditing(): boolean | undefined
    stopEditing(): void
    setCaretOffset(offset: int32): boolean | undefined
    getCaretOffset(): int32 | undefined
    getPreviewText(): PreviewText | undefined
}
export class TextEditControllerExInternal extends TextBaseControllerInternal implements MaterializedBase,TextEditControllerEx {
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
    }
    constructor() {
        this(MaterializedBaseTag.NOP, TextEditControllerExInternal.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._TextEditControllerEx_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextEditControllerEx_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): TextEditControllerExInternal {
        return new TextEditControllerExInternal(MaterializedBaseTag.NOP, ptr)
    }
    public isEditing(): boolean | undefined {
        return this.isEditing_serialize()
    }
    public stopEditing(): void {
        this.stopEditing_serialize()
        return
    }
    public setCaretOffset(offset: int32): boolean | undefined {
        const offset_casted = offset as (int32)
        return this.setCaretOffset_serialize(offset_casted)
    }
    public getCaretOffset(): int32 | undefined {
        return this.getCaretOffset_serialize()
    }
    public getPreviewText(): PreviewText | undefined {
        return this.getPreviewText_serialize()
    }
    private isEditing_serialize(): boolean | undefined {
        const retval = ArkUIGeneratedNativeModule._TextEditControllerEx_isEditing(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType = retvalDeserializer.readInt8()!.toInt()
        let buffer: boolean | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = retvalDeserializer.readBoolean()
        }
        const returnResult: boolean | undefined = buffer
        return returnResult
    }
    private stopEditing_serialize(): void {
        ArkUIGeneratedNativeModule._TextEditControllerEx_stopEditing(this.peer!.ptr)
    }
    private setCaretOffset_serialize(offset: int32): boolean | undefined {
        const retval = ArkUIGeneratedNativeModule._TextEditControllerEx_setCaretOffset(this.peer!.ptr, offset)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType = retvalDeserializer.readInt8()!.toInt()
        let buffer: boolean | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = retvalDeserializer.readBoolean()
        }
        const returnResult: boolean | undefined = buffer
        return returnResult
    }
    private getCaretOffset_serialize(): int32 | undefined {
        const retval = ArkUIGeneratedNativeModule._TextEditControllerEx_getCaretOffset(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType = retvalDeserializer.readInt8()!.toInt()
        let buffer: int32 | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = retvalDeserializer.readInt32()
        }
        const returnResult: int32 | undefined = buffer
        return returnResult
    }
    private getPreviewText_serialize(): PreviewText | undefined {
        const retval = ArkUIGeneratedNativeModule._TextEditControllerEx_getPreviewText(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType = retvalDeserializer.readInt8()!.toInt()
        let buffer: PreviewText | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = PreviewText_serializer.read(retvalDeserializer)
        }
        const returnResult: PreviewText | undefined = buffer
        return returnResult
    }
}
