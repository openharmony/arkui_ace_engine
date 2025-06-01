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

import { SelectionOptions } from "./common"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { StyledString, StyledStringInternal, MutableStyledString, MutableStyledStringInternal, DecorationStyleInterface } from "./styledString"
import { LineMetrics, TextBox, Affinity } from "./arkui-graphics-text"
import { RectWidthStyle, RectHeightStyle } from "./arkui-external"
import { ResourceStr, ResourceColor, Length } from "./units"
import { Resource } from "global/resource"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Callback_String_Void } from "./gridRow"
import { TextDecorationType, TextDecorationStyle } from "./enums"
export interface TextBaseController {
    setSelection(selectionStart: number, selectionEnd: number, options: SelectionOptions | undefined): void
    closeSelectionMenu(): void
    getLayoutManager(): LayoutManager
}
export class TextBaseControllerInternal implements MaterializedBase,TextBaseController {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_textbasecontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextBaseController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = TextBaseControllerInternal.ctor_textbasecontroller()
        this.peer = new Finalizable(ctorPtr, TextBaseControllerInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextBaseController_getFinalizer()
    }
    public setSelection(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void {
        const selectionStart_casted = selectionStart as (number)
        const selectionEnd_casted = selectionEnd as (number)
        const options_casted = options as (SelectionOptions | undefined)
        this.setSelection_serialize(selectionStart_casted, selectionEnd_casted, options_casted)
        return
    }
    public closeSelectionMenu(): void {
        this.closeSelectionMenu_serialize()
        return
    }
    public getLayoutManager(): LayoutManager {
        return this.getLayoutManager_serialize()
    }
    private setSelection_serialize(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeSelectionOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TextBaseController_setSelection(this.peer!.ptr, selectionStart, selectionEnd, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private closeSelectionMenu_serialize(): void {
        ArkUIGeneratedNativeModule._TextBaseController_closeSelectionMenu(this.peer!.ptr)
    }
    private getLayoutManager_serialize(): LayoutManager {
        const retval  = ArkUIGeneratedNativeModule._TextBaseController_getLayoutManager(this.peer!.ptr)
        const obj : LayoutManager = LayoutManagerInternal.fromPtr(retval)
        return obj
    }
    public static fromPtr(ptr: KPointer): TextBaseControllerInternal {
        const obj : TextBaseControllerInternal = new TextBaseControllerInternal()
        obj.peer = new Finalizable(ptr, TextBaseControllerInternal.getFinalizer())
        return obj
    }
}
export interface StyledStringController {
    setStyledString(styledString: StyledString): void
    getStyledString(): MutableStyledString
}
export class StyledStringControllerInternal implements MaterializedBase,StyledStringController {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_styledstringcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._StyledStringController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = StyledStringControllerInternal.ctor_styledstringcontroller()
        this.peer = new Finalizable(ctorPtr, StyledStringControllerInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._StyledStringController_getFinalizer()
    }
    public setStyledString(styledString: StyledString): void {
        const styledString_casted = styledString as (StyledString)
        this.setStyledString_serialize(styledString_casted)
        return
    }
    public getStyledString(): MutableStyledString {
        return this.getStyledString_serialize()
    }
    private setStyledString_serialize(styledString: StyledString): void {
        ArkUIGeneratedNativeModule._StyledStringController_setStyledString(this.peer!.ptr, toPeerPtr(styledString))
    }
    private getStyledString_serialize(): MutableStyledString {
        const retval  = ArkUIGeneratedNativeModule._StyledStringController_getStyledString(this.peer!.ptr)
        const obj : MutableStyledString = MutableStyledStringInternal.fromPtr(retval)
        return obj
    }
    public static fromPtr(ptr: KPointer): StyledStringControllerInternal {
        const obj : StyledStringControllerInternal = new StyledStringControllerInternal()
        obj.peer = new Finalizable(ptr, StyledStringControllerInternal.getFinalizer())
        return obj
    }
}
export interface LayoutManager {
    getLineCount(): number
    getGlyphPositionAtCoordinate(x: number, y: number): PositionWithAffinity
    getLineMetrics(lineNumber: number): LineMetrics
    getRectsForRange(range: TextRange, widthStyle: RectWidthStyle, heightStyle: RectHeightStyle): Array<TextBox>
}
export class LayoutManagerInternal implements MaterializedBase,LayoutManager {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_layoutmanager(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LayoutManager_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = LayoutManagerInternal.ctor_layoutmanager()
        this.peer = new Finalizable(ctorPtr, LayoutManagerInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LayoutManager_getFinalizer()
    }
    public getLineCount(): number {
        return this.getLineCount_serialize()
    }
    public getGlyphPositionAtCoordinate(x: number, y: number): PositionWithAffinity {
        const x_casted = x as (number)
        const y_casted = y as (number)
        return this.getGlyphPositionAtCoordinate_serialize(x_casted, y_casted)
    }
    public getLineMetrics(lineNumber: number): LineMetrics {
        const lineNumber_casted = lineNumber as (number)
        return this.getLineMetrics_serialize(lineNumber_casted)
    }
    public getRectsForRange(range: TextRange, widthStyle: RectWidthStyle, heightStyle: RectHeightStyle): Array<TextBox> {
        const range_casted = range as (TextRange)
        const widthStyle_casted = widthStyle as (RectWidthStyle)
        const heightStyle_casted = heightStyle as (RectHeightStyle)
        return this.getRectsForRange_serialize(range_casted, widthStyle_casted, heightStyle_casted)
    }
    private getLineCount_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._LayoutManager_getLineCount(this.peer!.ptr)
        return retval
    }
    private getGlyphPositionAtCoordinate_serialize(x: number, y: number): PositionWithAffinity {
        const retval  = ArkUIGeneratedNativeModule._LayoutManager_getGlyphPositionAtCoordinate(this.peer!.ptr, x, y)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : PositionWithAffinity = retvalDeserializer.readPositionWithAffinity()
        return returnResult
    }
    private getLineMetrics_serialize(lineNumber: number): LineMetrics {
        const retval  = ArkUIGeneratedNativeModule._LayoutManager_getLineMetrics(this.peer!.ptr, lineNumber)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : LineMetrics = retvalDeserializer.readLineMetrics()
        return returnResult
    }
    private getRectsForRange_serialize(range: TextRange, widthStyle: RectWidthStyle, heightStyle: RectHeightStyle): Array<TextBox> {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeTextRange(range)
        const retval  = ArkUIGeneratedNativeModule._LayoutManager_getRectsForRange(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length(), TypeChecker.RectWidthStyle_ToNumeric(widthStyle), TypeChecker.RectHeightStyle_ToNumeric(heightStyle))
        thisSerializer.release()
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<TextBox> = new Array<TextBox>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = retvalDeserializer.readTextBox()
        }
        const returnResult : Array<TextBox> = buffer
        return returnResult
    }
    public static fromPtr(ptr: KPointer): LayoutManagerInternal {
        const obj : LayoutManagerInternal = new LayoutManagerInternal()
        obj.peer = new Finalizable(ptr, LayoutManagerInternal.getFinalizer())
        return obj
    }
}
export class TextMenuItemIdInternal {
    public static fromPtr(ptr: KPointer): TextMenuItemId {
        const obj : TextMenuItemId = new TextMenuItemId()
        obj.peer = new Finalizable(ptr, TextMenuItemId.getFinalizer())
        return obj
    }
}
export class TextMenuItemId implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    static readonly CUT : TextMenuItemId = TextMenuItemId.getCUT()
    static readonly COPY : TextMenuItemId = TextMenuItemId.getCOPY()
    static readonly PASTE : TextMenuItemId = TextMenuItemId.getPASTE()
    static readonly SELECT_ALL : TextMenuItemId = TextMenuItemId.getSELECT_ALL()
    static readonly COLLABORATION_SERVICE : TextMenuItemId = TextMenuItemId.getCOLLABORATION_SERVICE()
    static readonly CAMERA_INPUT : TextMenuItemId = TextMenuItemId.getCAMERA_INPUT()
    static readonly AI_WRITER : TextMenuItemId = TextMenuItemId.getAI_WRITER()
    static readonly TRANSLATE : TextMenuItemId = TextMenuItemId.getTRANSLATE()
    static readonly SEARCH : TextMenuItemId = TextMenuItemId.getSEARCH()
    static readonly SHARE : TextMenuItemId = TextMenuItemId.getSHARE()
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_textmenuitemid(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextMenuItemId_ctor()
        return retval
    }
    constructor() {
        // Constructor does not have parameters.
        // It means that the static method call invokes ctor method as well
        // when all arguments are undefined.
        const ctorPtr : KPointer = TextMenuItemId.ctor_textmenuitemid()
        this.peer = new Finalizable(ctorPtr, TextMenuItemId.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextMenuItemId_getFinalizer()
    }
    public static of(id: ResourceStr): TextMenuItemId {
        const id_casted = id as (ResourceStr)
        return TextMenuItemId.of_serialize(id_casted)
    }
    public equals(id: TextMenuItemId): boolean {
        const id_casted = id as (TextMenuItemId)
        return this.equals_serialize(id_casted)
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
    private static of_serialize(id: ResourceStr): TextMenuItemId {
        const thisSerializer : Serializer = Serializer.hold()
        let id_type : int32 = RuntimeType.UNDEFINED
        id_type = runtimeType(id)
        if (RuntimeType.STRING == id_type) {
            thisSerializer.writeInt8(0 as int32)
            const id_0  = id as string
            thisSerializer.writeString(id_0)
        }
        else if (RuntimeType.OBJECT == id_type) {
            thisSerializer.writeInt8(1 as int32)
            const id_1  = id as Resource
            thisSerializer.writeResource(id_1)
        }
        const retval  = ArkUIGeneratedNativeModule._TextMenuItemId_of(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private equals_serialize(id: TextMenuItemId): boolean {
        const retval  = ArkUIGeneratedNativeModule._TextMenuItemId_equals(this.peer!.ptr, toPeerPtr(id))
        return retval
    }
    private static getCUT_serialize(): TextMenuItemId {
        const retval  = ArkUIGeneratedNativeModule._TextMenuItemId_getCUT()
        const obj : TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getCOPY_serialize(): TextMenuItemId {
        const retval  = ArkUIGeneratedNativeModule._TextMenuItemId_getCOPY()
        const obj : TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getPASTE_serialize(): TextMenuItemId {
        const retval  = ArkUIGeneratedNativeModule._TextMenuItemId_getPASTE()
        const obj : TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getSELECT_ALL_serialize(): TextMenuItemId {
        const retval  = ArkUIGeneratedNativeModule._TextMenuItemId_getSELECT_ALL()
        const obj : TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getCOLLABORATION_SERVICE_serialize(): TextMenuItemId {
        const retval  = ArkUIGeneratedNativeModule._TextMenuItemId_getCOLLABORATION_SERVICE()
        const obj : TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getCAMERA_INPUT_serialize(): TextMenuItemId {
        const retval  = ArkUIGeneratedNativeModule._TextMenuItemId_getCAMERA_INPUT()
        const obj : TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getAI_WRITER_serialize(): TextMenuItemId {
        const retval  = ArkUIGeneratedNativeModule._TextMenuItemId_getAI_WRITER()
        const obj : TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getTRANSLATE_serialize(): TextMenuItemId {
        const retval  = ArkUIGeneratedNativeModule._TextMenuItemId_getTRANSLATE()
        const obj : TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getSEARCH_serialize(): TextMenuItemId {
        const retval  = ArkUIGeneratedNativeModule._TextMenuItemId_getSEARCH()
        const obj : TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
    }
    private static getSHARE_serialize(): TextMenuItemId {
        const retval  = ArkUIGeneratedNativeModule._TextMenuItemId_getSHARE()
        const obj : TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
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
    types: Array<TextDataDetectorType>;
    onDetectResultUpdate?: ((breakpoints: string) => void);
    color?: ResourceColor;
    decoration?: DecorationStyleInterface;
}
export interface TextRange {
    start?: number;
    end?: number;
}
export interface InsertValue {
    insertOffset: number;
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
    deleteOffset: number;
    direction: TextDeleteDirection;
    deleteValue: string;
}
export type OnDidChangeCallback = (rangeBefore: TextRange, rangeAfter: TextRange) => void;
export type EditableTextOnChangeCallback = (value: string, previewText?: PreviewText, options?: TextChangeOptions) => void;
export interface PreviewText {
    offset: number;
    value: string;
}
export type Callback_StyledStringChangeValue_Boolean = (parameter: StyledStringChangeValue) => boolean;
export interface StyledStringChangedListener {
    onWillChange?: ((parameter: StyledStringChangeValue) => boolean);
    onDidChange?: OnDidChangeCallback;
}
export interface StyledStringChangeValue {
    range: TextRange;
    replacementString: StyledString;
    previewText?: StyledString;
}
export interface PositionWithAffinity {
    position: number;
    affinity: Affinity;
}
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
export type AsyncCallback_Array_TextMenuItem_Array_TextMenuItem = (menuItems: Array<TextMenuItem>) => Array<TextMenuItem>;
export type AsyncCallback_TextMenuItem_TextRange_Boolean = (menuItem: TextMenuItem, range: TextRange) => boolean;
export interface EditMenuOptions {
    onCreateMenu: ((menuItems: Array<TextMenuItem>) => Array<TextMenuItem>);
    onMenuItemClick: ((menuItem: TextMenuItem,range: TextRange) => boolean);
}
export interface DecorationStyleResult {
    type: TextDecorationType;
    color: ResourceColor;
    style?: TextDecorationStyle;
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
export interface TextEditControllerEx {
    isEditing(): boolean
    stopEditing(): void
    setCaretOffset(offset: number): boolean
    getCaretOffset(): number
    getPreviewText(): PreviewText
}
export class TextEditControllerExInternal extends TextBaseControllerInternal implements MaterializedBase,TextEditControllerEx {
    static ctor_texteditcontrollerex(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextEditControllerEx_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = TextEditControllerExInternal.ctor_texteditcontrollerex()
        this.peer = new Finalizable(ctorPtr, TextEditControllerExInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextEditControllerEx_getFinalizer()
    }
    public isEditing(): boolean {
        return this.isEditing_serialize()
    }
    public stopEditing(): void {
        this.stopEditing_serialize()
        return
    }
    public setCaretOffset(offset: number): boolean {
        const offset_casted = offset as (number)
        return this.setCaretOffset_serialize(offset_casted)
    }
    public getCaretOffset(): number {
        return this.getCaretOffset_serialize()
    }
    public getPreviewText(): PreviewText {
        return this.getPreviewText_serialize()
    }
    private isEditing_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._TextEditControllerEx_isEditing(this.peer!.ptr)
        return retval
    }
    private stopEditing_serialize(): void {
        ArkUIGeneratedNativeModule._TextEditControllerEx_stopEditing(this.peer!.ptr)
    }
    private setCaretOffset_serialize(offset: number): boolean {
        const retval  = ArkUIGeneratedNativeModule._TextEditControllerEx_setCaretOffset(this.peer!.ptr, offset)
        return retval
    }
    private getCaretOffset_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._TextEditControllerEx_getCaretOffset(this.peer!.ptr)
        return retval
    }
    private getPreviewText_serialize(): PreviewText {
        const retval  = ArkUIGeneratedNativeModule._TextEditControllerEx_getPreviewText(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : PreviewText = retvalDeserializer.readPreviewText()
        return returnResult
    }
    public static fromPtr(ptr: KPointer): TextEditControllerExInternal {
        const obj : TextEditControllerExInternal = new TextEditControllerExInternal()
        obj.peer = new Finalizable(ptr, TextEditControllerExInternal.getFinalizer())
        return obj
    }
}
