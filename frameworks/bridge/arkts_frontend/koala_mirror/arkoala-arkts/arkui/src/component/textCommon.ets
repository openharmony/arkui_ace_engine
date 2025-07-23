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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, DeserializerBase, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { StyledString, StyledStringInternal, MutableStyledString, MutableStyledStringInternal, DecorationStyleInterface, StyledString_serializer, DecorationStyleInterface_serializer } from "./styledString"
import { SelectionOptions_serializer, SelectionOptions } from "./common"
import { Resource_serializer, Resource } from "./../generated/resource"
import { ResourceStr, ResourceColor, Length } from "./units"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { Color, TextDecorationType, TextDecorationStyle } from "./enums"
export interface LayoutManager {
    getLineCount(): number
    getGlyphPositionAtCoordinate(x: number, y: number): PositionWithAffinity
}
export class LayoutManagerInternal implements MaterializedBase,LayoutManager {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, LayoutManagerInternal.getFinalizer())
    }
    constructor() {
        this(LayoutManagerInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LayoutManager_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LayoutManager_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): LayoutManagerInternal {
        return new LayoutManagerInternal(ptr)
    }
    public getLineCount(): number {
        return this.getLineCount_serialize()
    }
    public getGlyphPositionAtCoordinate(x: number, y: number): PositionWithAffinity {
        const x_casted = x as (number)
        const y_casted = y as (number)
        return this.getGlyphPositionAtCoordinate_serialize(x_casted, y_casted)
    }
    private getLineCount_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._LayoutManager_getLineCount(this.peer!.ptr)
        return retval
    }
    private getGlyphPositionAtCoordinate_serialize(x: number, y: number): PositionWithAffinity {
        const retval  = ArkUIGeneratedNativeModule._LayoutManager_getGlyphPositionAtCoordinate(this.peer!.ptr, x, y)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : PositionWithAffinity = PositionWithAffinity_serializer.read(retvalDeserializer)
        return returnResult
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
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, StyledStringControllerInternal.getFinalizer())
    }
    constructor() {
        this(StyledStringControllerInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._StyledStringController_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._StyledStringController_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): StyledStringControllerInternal {
        return new StyledStringControllerInternal(ptr)
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
}
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
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, TextBaseControllerInternal.getFinalizer())
    }
    constructor() {
        this(TextBaseControllerInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextBaseController_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextBaseController_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): TextBaseControllerInternal {
        return new TextBaseControllerInternal(ptr)
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            SelectionOptions_serializer.write(thisSerializer, options_value)
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
}
export class TextMenuItemIdInternal {
    public static fromPtr(ptr: KPointer): TextMenuItemId {
        return new TextMenuItemId(ptr)
    }
}
export class TextMenuItemId implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static readonly CUT: TextMenuItemId = TextMenuItemId.getCUT()
    static readonly COPY: TextMenuItemId = TextMenuItemId.getCOPY()
    static readonly PASTE: TextMenuItemId = TextMenuItemId.getPASTE()
    static readonly SELECT_ALL: TextMenuItemId = TextMenuItemId.getSELECT_ALL()
    static readonly COLLABORATION_SERVICE: TextMenuItemId = TextMenuItemId.getCOLLABORATION_SERVICE()
    static readonly CAMERA_INPUT: TextMenuItemId = TextMenuItemId.getCAMERA_INPUT()
    static readonly AI_WRITER: TextMenuItemId = TextMenuItemId.getAI_WRITER()
    static readonly TRANSLATE: TextMenuItemId = TextMenuItemId.getTRANSLATE()
    static readonly SEARCH: TextMenuItemId = TextMenuItemId.getSEARCH()
    static readonly SHARE: TextMenuItemId = TextMenuItemId.getSHARE()
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, TextMenuItemId.getFinalizer())
    }
    constructor() {
        this(TextMenuItemId.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextMenuItemId_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextMenuItemId_getFinalizer()
    }
    private static of_serialize(id: ResourceStr): TextMenuItemId {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let id_type : int32 = RuntimeType.UNDEFINED
        id_type = runtimeType(id)
        if (RuntimeType.STRING == id_type) {
            thisSerializer.writeInt8((0).toChar())
            const id_0  = id as string
            thisSerializer.writeString(id_0)
        }
        else if (RuntimeType.OBJECT == id_type) {
            thisSerializer.writeInt8((1).toChar())
            const id_1  = id as Resource
            Resource_serializer.write(thisSerializer, id_1)
        }
        const retval  = ArkUIGeneratedNativeModule._TextMenuItemId_of(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : TextMenuItemId = TextMenuItemIdInternal.fromPtr(retval)
        return obj
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
    private equals_serialize(id: TextMenuItemId): boolean {
        const retval  = ArkUIGeneratedNativeModule._TextMenuItemId_equals(this.peer!.ptr, toPeerPtr(id))
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
    types: Array<TextDataDetectorType>;
    onDetectResultUpdate?: ((value0: string) => void);
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
export interface StyledStringChangedListener {
    onWillChange?: ((value0: StyledStringChangeValue) => boolean);
    onDidChange?: OnDidChangeCallback;
}
export interface StyledStringChangeValue {
    range: TextRange;
    replacementString: StyledString;
    previewText?: StyledString;
}
export interface PositionWithAffinity {
    position: number;
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
export type OnCreateMenuCallback = (menuItems: Array<TextMenuItem>) => Array<TextMenuItem>;
export type OnMenuItemClickCallback = (menuItem: TextMenuItem, range: TextRange) => boolean;
export interface EditMenuOptions {
    onCreateMenu: OnCreateMenuCallback;
    onMenuItemClick: OnMenuItemClickCallback;
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
export class LayoutManager_serializer {
    public static write(buffer: SerializerBase, value: LayoutManager): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): LayoutManager {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return LayoutManagerInternal.fromPtr(ptr)
    }
}
export class PositionWithAffinity_serializer {
    public static write(buffer: SerializerBase, value: PositionWithAffinity): void {
        let valueSerializer : SerializerBase = buffer
        const value_position  = value.position
        valueSerializer.writeNumber(value_position)
    }
    public static read(buffer: DeserializerBase): PositionWithAffinity {
        let valueDeserializer : DeserializerBase = buffer
        const position_result : number = (valueDeserializer.readNumber() as number)
        let value : PositionWithAffinity = ({position: position_result} as PositionWithAffinity)
        return value
    }
}
export class StyledStringController_serializer {
    public static write(buffer: SerializerBase, value: StyledStringController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): StyledStringController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return StyledStringControllerInternal.fromPtr(ptr)
    }
}
export class TextBaseController_serializer {
    public static write(buffer: SerializerBase, value: TextBaseController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): TextBaseController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return TextBaseControllerInternal.fromPtr(ptr)
    }
}
export class TextEditControllerEx_serializer {
    public static write(buffer: SerializerBase, value: TextEditControllerEx): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): TextEditControllerEx {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return TextEditControllerExInternal.fromPtr(ptr)
    }
}
export class TextMenuItemId_serializer {
    public static write(buffer: SerializerBase, value: TextMenuItemId): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): TextMenuItemId {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return TextMenuItemIdInternal.fromPtr(ptr)
    }
}
export class DeleteValue_serializer {
    public static write(buffer: SerializerBase, value: DeleteValue): void {
        let valueSerializer : SerializerBase = buffer
        const value_deleteOffset  = value.deleteOffset
        valueSerializer.writeNumber(value_deleteOffset)
        const value_direction  = value.direction
        valueSerializer.writeInt32(TypeChecker.TextDeleteDirection_ToNumeric(value_direction))
        const value_deleteValue  = value.deleteValue
        valueSerializer.writeString(value_deleteValue)
    }
    public static read(buffer: DeserializerBase): DeleteValue {
        let valueDeserializer : DeserializerBase = buffer
        const deleteOffset_result : number = (valueDeserializer.readNumber() as number)
        const direction_result : TextDeleteDirection = TypeChecker.TextDeleteDirection_FromNumeric(valueDeserializer.readInt32())
        const deleteValue_result : string = (valueDeserializer.readString() as string)
        let value : DeleteValue = ({deleteOffset: deleteOffset_result, direction: direction_result, deleteValue: deleteValue_result} as DeleteValue)
        return value
    }
}
export class EditMenuOptions_serializer {
    public static write(buffer: SerializerBase, value: EditMenuOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_onCreateMenu  = value.onCreateMenu
        valueSerializer.holdAndWriteCallback(value_onCreateMenu)
        const value_onMenuItemClick  = value.onMenuItemClick
        valueSerializer.holdAndWriteCallback(value_onMenuItemClick)
    }
    public static read(buffer: DeserializerBase): EditMenuOptions {
        let valueDeserializer : DeserializerBase = buffer
        const onCreateMenu_buf_resource : CallbackResource = valueDeserializer.readCallbackResource()
        const onCreateMenu_buf_call : KPointer = valueDeserializer.readPointer()
        const onCreateMenu_buf_callSync : KPointer = valueDeserializer.readPointer()
        const onCreateMenu_result : OnCreateMenuCallback = (menuItems: Array<TextMenuItem>):Array<TextMenuItem> => { 
    const onCreateMenu_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    onCreateMenu_buf_argsSerializer.writeInt32(onCreateMenu_buf_resource.resourceId);
    onCreateMenu_buf_argsSerializer.writePointer(onCreateMenu_buf_call);
    onCreateMenu_buf_argsSerializer.writePointer(onCreateMenu_buf_callSync);
    onCreateMenu_buf_argsSerializer.writeInt32((menuItems.length).toInt());
    for (let menuItems_counter_i = 0; menuItems_counter_i < menuItems.length; menuItems_counter_i++) {
        const menuItems_element : TextMenuItem = menuItems[menuItems_counter_i];
        TextMenuItem_serializer.write(onCreateMenu_buf_argsSerializer, menuItems_element);
    }
    let onCreateMenu_buf_continuationValue : Array<TextMenuItem> | undefined;
    const onCreateMenu_buf_continuationCallback : ((value: Array<TextMenuItem>) => void) = (value: Array<TextMenuItem>):void => {     onCreateMenu_buf_continuationValue = value; }
    onCreateMenu_buf_argsSerializer.holdAndWriteCallback(onCreateMenu_buf_continuationCallback);
    InteropNativeModule._CallCallback(312701677, onCreateMenu_buf_argsSerializer.asBuffer(), onCreateMenu_buf_argsSerializer.length());
    onCreateMenu_buf_argsSerializer.release();
    return (onCreateMenu_buf_continuationValue as Array<TextMenuItem>); }
        const onMenuItemClick_buf_resource : CallbackResource = valueDeserializer.readCallbackResource()
        const onMenuItemClick_buf_call : KPointer = valueDeserializer.readPointer()
        const onMenuItemClick_buf_callSync : KPointer = valueDeserializer.readPointer()
        const onMenuItemClick_result : OnMenuItemClickCallback = (menuItem: TextMenuItem, range: TextRange):boolean => { 
    const onMenuItemClick_buf_argsSerializer : SerializerBase = SerializerBase.hold();
    onMenuItemClick_buf_argsSerializer.writeInt32(onMenuItemClick_buf_resource.resourceId);
    onMenuItemClick_buf_argsSerializer.writePointer(onMenuItemClick_buf_call);
    onMenuItemClick_buf_argsSerializer.writePointer(onMenuItemClick_buf_callSync);
    TextMenuItem_serializer.write(onMenuItemClick_buf_argsSerializer, menuItem);
    TextRange_serializer.write(onMenuItemClick_buf_argsSerializer, range);
    let onMenuItemClick_buf_continuationValue : boolean | undefined;
    const onMenuItemClick_buf_continuationCallback : ((value0: boolean) => void) = (value: boolean):void => {     onMenuItemClick_buf_continuationValue = value; }
    onMenuItemClick_buf_argsSerializer.holdAndWriteCallback(onMenuItemClick_buf_continuationCallback);
    InteropNativeModule._CallCallback(-1106041422, onMenuItemClick_buf_argsSerializer.asBuffer(), onMenuItemClick_buf_argsSerializer.length());
    onMenuItemClick_buf_argsSerializer.release();
    return (onMenuItemClick_buf_continuationValue as boolean); }
        let value : EditMenuOptions = ({onCreateMenu: onCreateMenu_result, onMenuItemClick: onMenuItemClick_result} as EditMenuOptions)
        return value
    }
}
export class FontSettingOptions_serializer {
    public static write(buffer: SerializerBase, value: FontSettingOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_enableVariableFontWeight  = value.enableVariableFontWeight
        let value_enableVariableFontWeight_type : int32 = RuntimeType.UNDEFINED
        value_enableVariableFontWeight_type = runtimeType(value_enableVariableFontWeight)
        valueSerializer.writeInt8((value_enableVariableFontWeight_type).toChar())
        if ((value_enableVariableFontWeight_type) != (RuntimeType.UNDEFINED)) {
            const value_enableVariableFontWeight_value  = value_enableVariableFontWeight!
            valueSerializer.writeBoolean(value_enableVariableFontWeight_value)
        }
    }
    public static read(buffer: DeserializerBase): FontSettingOptions {
        let valueDeserializer : DeserializerBase = buffer
        const enableVariableFontWeight_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableVariableFontWeight_buf : boolean | undefined
        if ((enableVariableFontWeight_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            enableVariableFontWeight_buf = valueDeserializer.readBoolean()
        }
        const enableVariableFontWeight_result : boolean | undefined = enableVariableFontWeight_buf
        let value : FontSettingOptions = ({enableVariableFontWeight: enableVariableFontWeight_result} as FontSettingOptions)
        return value
    }
}
export class InsertValue_serializer {
    public static write(buffer: SerializerBase, value: InsertValue): void {
        let valueSerializer : SerializerBase = buffer
        const value_insertOffset  = value.insertOffset
        valueSerializer.writeNumber(value_insertOffset)
        const value_insertValue  = value.insertValue
        valueSerializer.writeString(value_insertValue)
    }
    public static read(buffer: DeserializerBase): InsertValue {
        let valueDeserializer : DeserializerBase = buffer
        const insertOffset_result : number = (valueDeserializer.readNumber() as number)
        const insertValue_result : string = (valueDeserializer.readString() as string)
        let value : InsertValue = ({insertOffset: insertOffset_result, insertValue: insertValue_result} as InsertValue)
        return value
    }
}
export class PreviewText_serializer {
    public static write(buffer: SerializerBase, value: PreviewText): void {
        let valueSerializer : SerializerBase = buffer
        const value_offset  = value.offset
        valueSerializer.writeNumber(value_offset)
        const value_value  = value.value
        valueSerializer.writeString(value_value)
    }
    public static read(buffer: DeserializerBase): PreviewText {
        let valueDeserializer : DeserializerBase = buffer
        const offset_result : number = (valueDeserializer.readNumber() as number)
        const value_result : string = (valueDeserializer.readString() as string)
        let value : PreviewText = ({offset: offset_result, value: value_result} as PreviewText)
        return value
    }
}
export class StyledStringChangedListener_serializer {
    public static write(buffer: SerializerBase, value: StyledStringChangedListener): void {
        let valueSerializer : SerializerBase = buffer
        const value_onWillChange  = value.onWillChange
        let value_onWillChange_type : int32 = RuntimeType.UNDEFINED
        value_onWillChange_type = runtimeType(value_onWillChange)
        valueSerializer.writeInt8((value_onWillChange_type).toChar())
        if ((value_onWillChange_type) != (RuntimeType.UNDEFINED)) {
            const value_onWillChange_value  = value_onWillChange!
            valueSerializer.holdAndWriteCallback(value_onWillChange_value)
        }
        const value_onDidChange  = value.onDidChange
        let value_onDidChange_type : int32 = RuntimeType.UNDEFINED
        value_onDidChange_type = runtimeType(value_onDidChange)
        valueSerializer.writeInt8((value_onDidChange_type).toChar())
        if ((value_onDidChange_type) != (RuntimeType.UNDEFINED)) {
            const value_onDidChange_value  = value_onDidChange!
            valueSerializer.holdAndWriteCallback(value_onDidChange_value)
        }
    }
    public static read(buffer: DeserializerBase): StyledStringChangedListener {
        let valueDeserializer : DeserializerBase = buffer
        const onWillChange_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillChange_buf : ((value0: StyledStringChangeValue) => boolean) | undefined
        if ((onWillChange_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onWillChange_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillChange_buf__call : KPointer = valueDeserializer.readPointer()
            const onWillChange_buf__callSync : KPointer = valueDeserializer.readPointer()
            onWillChange_buf = (value0: StyledStringChangeValue):boolean => { 
    const onWillChange_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onWillChange_buf__argsSerializer.writeInt32(onWillChange_buf__resource.resourceId);
    onWillChange_buf__argsSerializer.writePointer(onWillChange_buf__call);
    onWillChange_buf__argsSerializer.writePointer(onWillChange_buf__callSync);
    StyledStringChangeValue_serializer.write(onWillChange_buf__argsSerializer, value0);
    let onWillChange_buf__continuationValue : boolean | undefined;
    const onWillChange_buf__continuationCallback : ((value0: boolean) => void) = (value: boolean):void => {     onWillChange_buf__continuationValue = value; }
    onWillChange_buf__argsSerializer.holdAndWriteCallback(onWillChange_buf__continuationCallback);
    InteropNativeModule._CallCallback(2116745428, onWillChange_buf__argsSerializer.asBuffer(), onWillChange_buf__argsSerializer.length());
    onWillChange_buf__argsSerializer.release();
    return (onWillChange_buf__continuationValue as boolean); }
        }
        const onWillChange_result : ((value0: StyledStringChangeValue) => boolean) | undefined = onWillChange_buf
        const onDidChange_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDidChange_buf : OnDidChangeCallback | undefined
        if ((onDidChange_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onDidChange_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidChange_buf__call : KPointer = valueDeserializer.readPointer()
            const onDidChange_buf__callSync : KPointer = valueDeserializer.readPointer()
            onDidChange_buf = (rangeBefore: TextRange, rangeAfter: TextRange):void => { 
    const onDidChange_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onDidChange_buf__argsSerializer.writeInt32(onDidChange_buf__resource.resourceId);
    onDidChange_buf__argsSerializer.writePointer(onDidChange_buf__call);
    onDidChange_buf__argsSerializer.writePointer(onDidChange_buf__callSync);
    TextRange_serializer.write(onDidChange_buf__argsSerializer, rangeBefore);
    TextRange_serializer.write(onDidChange_buf__argsSerializer, rangeAfter);
    InteropNativeModule._CallCallback(1648184341, onDidChange_buf__argsSerializer.asBuffer(), onDidChange_buf__argsSerializer.length());
    onDidChange_buf__argsSerializer.release();
    return; }
        }
        const onDidChange_result : OnDidChangeCallback | undefined = onDidChange_buf
        let value : StyledStringChangedListener = ({onWillChange: onWillChange_result, onDidChange: onDidChange_result} as StyledStringChangedListener)
        return value
    }
}
export class TextMenuOptions_serializer {
    public static write(buffer: SerializerBase, value: TextMenuOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_showMode  = value.showMode
        let value_showMode_type : int32 = RuntimeType.UNDEFINED
        value_showMode_type = runtimeType(value_showMode)
        valueSerializer.writeInt8((value_showMode_type).toChar())
        if ((value_showMode_type) != (RuntimeType.UNDEFINED)) {
            const value_showMode_value  = (value_showMode as TextMenuShowMode)
            valueSerializer.writeInt32(TypeChecker.TextMenuShowMode_ToNumeric(value_showMode_value))
        }
    }
    public static read(buffer: DeserializerBase): TextMenuOptions {
        let valueDeserializer : DeserializerBase = buffer
        const showMode_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let showMode_buf : TextMenuShowMode | undefined
        if ((showMode_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            showMode_buf = TypeChecker.TextMenuShowMode_FromNumeric(valueDeserializer.readInt32())
        }
        const showMode_result : TextMenuShowMode | undefined = showMode_buf
        let value : TextMenuOptions = ({showMode: showMode_result} as TextMenuOptions)
        return value
    }
}
export class TextRange_serializer {
    public static write(buffer: SerializerBase, value: TextRange): void {
        let valueSerializer : SerializerBase = buffer
        const value_start  = value.start
        let value_start_type : int32 = RuntimeType.UNDEFINED
        value_start_type = runtimeType(value_start)
        valueSerializer.writeInt8((value_start_type).toChar())
        if ((value_start_type) != (RuntimeType.UNDEFINED)) {
            const value_start_value  = value_start!
            valueSerializer.writeNumber(value_start_value)
        }
        const value_end  = value.end
        let value_end_type : int32 = RuntimeType.UNDEFINED
        value_end_type = runtimeType(value_end)
        valueSerializer.writeInt8((value_end_type).toChar())
        if ((value_end_type) != (RuntimeType.UNDEFINED)) {
            const value_end_value  = value_end!
            valueSerializer.writeNumber(value_end_value)
        }
    }
    public static read(buffer: DeserializerBase): TextRange {
        let valueDeserializer : DeserializerBase = buffer
        const start_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let start_buf : number | undefined
        if ((start_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            start_buf = (valueDeserializer.readNumber() as number)
        }
        const start_result : number | undefined = start_buf
        const end_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let end_buf : number | undefined
        if ((end_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            end_buf = (valueDeserializer.readNumber() as number)
        }
        const end_result : number | undefined = end_buf
        let value : TextRange = ({start: start_result, end: end_result} as TextRange)
        return value
    }
}
export class DecorationStyleResult_serializer {
    public static write(buffer: SerializerBase, value: DecorationStyleResult): void {
        let valueSerializer : SerializerBase = buffer
        const value_type  = value.type
        valueSerializer.writeInt32(TypeChecker.TextDecorationType_ToNumeric(value_type))
        const value_color  = value.color
        let value_color_type : int32 = RuntimeType.UNDEFINED
        value_color_type = runtimeType(value_color)
        if (TypeChecker.isColor(value_color)) {
            valueSerializer.writeInt8((0).toChar())
            const value_color_0  = value_color as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_color_0))
        }
        else if (RuntimeType.NUMBER == value_color_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_color_1  = value_color as number
            valueSerializer.writeNumber(value_color_1)
        }
        else if (RuntimeType.STRING == value_color_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_color_2  = value_color as string
            valueSerializer.writeString(value_color_2)
        }
        else if (RuntimeType.OBJECT == value_color_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_color_3  = value_color as Resource
            Resource_serializer.write(valueSerializer, value_color_3)
        }
        const value_style  = value.style
        let value_style_type : int32 = RuntimeType.UNDEFINED
        value_style_type = runtimeType(value_style)
        valueSerializer.writeInt8((value_style_type).toChar())
        if ((value_style_type) != (RuntimeType.UNDEFINED)) {
            const value_style_value  = (value_style as TextDecorationStyle)
            valueSerializer.writeInt32(TypeChecker.TextDecorationStyle_ToNumeric(value_style_value))
        }
    }
    public static read(buffer: DeserializerBase): DecorationStyleResult {
        let valueDeserializer : DeserializerBase = buffer
        const type_result : TextDecorationType = TypeChecker.TextDecorationType_FromNumeric(valueDeserializer.readInt32())
        const color_buf_selector : int32 = valueDeserializer.readInt8()
        let color_buf : Color | number | string | Resource | undefined
        if (color_buf_selector == (0).toChar()) {
            color_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (color_buf_selector == (1).toChar()) {
            color_buf = (valueDeserializer.readNumber() as number)
        }
        else if (color_buf_selector == (2).toChar()) {
            color_buf = (valueDeserializer.readString() as string)
        }
        else if (color_buf_selector == (3).toChar()) {
            color_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for color_buf has to be chosen through deserialisation.")
        }
        const color_result : ResourceColor = (color_buf as Color | number | string | Resource)
        const style_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let style_buf : TextDecorationStyle | undefined
        if ((style_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            style_buf = TypeChecker.TextDecorationStyle_FromNumeric(valueDeserializer.readInt32())
        }
        const style_result : TextDecorationStyle | undefined = style_buf
        let value : DecorationStyleResult = ({type: type_result, color: color_result, style: style_result} as DecorationStyleResult)
        return value
    }
}
export class StyledStringChangeValue_serializer {
    public static write(buffer: SerializerBase, value: StyledStringChangeValue): void {
        let valueSerializer : SerializerBase = buffer
        const value_range  = value.range
        TextRange_serializer.write(valueSerializer, value_range)
        const value_replacementString  = value.replacementString
        StyledString_serializer.write(valueSerializer, value_replacementString)
        const value_previewText  = value.previewText
        let value_previewText_type : int32 = RuntimeType.UNDEFINED
        value_previewText_type = runtimeType(value_previewText)
        valueSerializer.writeInt8((value_previewText_type).toChar())
        if ((value_previewText_type) != (RuntimeType.UNDEFINED)) {
            const value_previewText_value  = value_previewText!
            StyledString_serializer.write(valueSerializer, value_previewText_value)
        }
    }
    public static read(buffer: DeserializerBase): StyledStringChangeValue {
        let valueDeserializer : DeserializerBase = buffer
        const range_result : TextRange = TextRange_serializer.read(valueDeserializer)
        const replacementString_result : StyledString = (StyledString_serializer.read(valueDeserializer) as StyledString)
        const previewText_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let previewText_buf : StyledString | undefined
        if ((previewText_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            previewText_buf = (StyledString_serializer.read(valueDeserializer) as StyledString)
        }
        const previewText_result : StyledString | undefined = previewText_buf
        let value : StyledStringChangeValue = ({range: range_result, replacementString: replacementString_result, previewText: previewText_result} as StyledStringChangeValue)
        return value
    }
}
export class TextChangeOptions_serializer {
    public static write(buffer: SerializerBase, value: TextChangeOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_rangeBefore  = value.rangeBefore
        TextRange_serializer.write(valueSerializer, value_rangeBefore)
        const value_rangeAfter  = value.rangeAfter
        TextRange_serializer.write(valueSerializer, value_rangeAfter)
        const value_oldContent  = value.oldContent
        valueSerializer.writeString(value_oldContent)
        const value_oldPreviewText  = value.oldPreviewText
        PreviewText_serializer.write(valueSerializer, value_oldPreviewText)
    }
    public static read(buffer: DeserializerBase): TextChangeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const rangeBefore_result : TextRange = TextRange_serializer.read(valueDeserializer)
        const rangeAfter_result : TextRange = TextRange_serializer.read(valueDeserializer)
        const oldContent_result : string = (valueDeserializer.readString() as string)
        const oldPreviewText_result : PreviewText = PreviewText_serializer.read(valueDeserializer)
        let value : TextChangeOptions = ({rangeBefore: rangeBefore_result, rangeAfter: rangeAfter_result, oldContent: oldContent_result, oldPreviewText: oldPreviewText_result} as TextChangeOptions)
        return value
    }
}
export class TextMenuItem_serializer {
    public static write(buffer: SerializerBase, value: TextMenuItem): void {
        let valueSerializer : SerializerBase = buffer
        const value_content  = value.content
        let value_content_type : int32 = RuntimeType.UNDEFINED
        value_content_type = runtimeType(value_content)
        if (RuntimeType.STRING == value_content_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_content_0  = value_content as string
            valueSerializer.writeString(value_content_0)
        }
        else if (RuntimeType.OBJECT == value_content_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_content_1  = value_content as Resource
            Resource_serializer.write(valueSerializer, value_content_1)
        }
        const value_icon  = value.icon
        let value_icon_type : int32 = RuntimeType.UNDEFINED
        value_icon_type = runtimeType(value_icon)
        valueSerializer.writeInt8((value_icon_type).toChar())
        if ((value_icon_type) != (RuntimeType.UNDEFINED)) {
            const value_icon_value  = value_icon!
            let value_icon_value_type : int32 = RuntimeType.UNDEFINED
            value_icon_value_type = runtimeType(value_icon_value)
            if (RuntimeType.STRING == value_icon_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_icon_value_0  = value_icon_value as string
                valueSerializer.writeString(value_icon_value_0)
            }
            else if (RuntimeType.OBJECT == value_icon_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_icon_value_1  = value_icon_value as Resource
                Resource_serializer.write(valueSerializer, value_icon_value_1)
            }
        }
        const value_id  = value.id
        TextMenuItemId_serializer.write(valueSerializer, value_id)
        const value_labelInfo  = value.labelInfo
        let value_labelInfo_type : int32 = RuntimeType.UNDEFINED
        value_labelInfo_type = runtimeType(value_labelInfo)
        valueSerializer.writeInt8((value_labelInfo_type).toChar())
        if ((value_labelInfo_type) != (RuntimeType.UNDEFINED)) {
            const value_labelInfo_value  = value_labelInfo!
            let value_labelInfo_value_type : int32 = RuntimeType.UNDEFINED
            value_labelInfo_value_type = runtimeType(value_labelInfo_value)
            if (RuntimeType.STRING == value_labelInfo_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_labelInfo_value_0  = value_labelInfo_value as string
                valueSerializer.writeString(value_labelInfo_value_0)
            }
            else if (RuntimeType.OBJECT == value_labelInfo_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_labelInfo_value_1  = value_labelInfo_value as Resource
                Resource_serializer.write(valueSerializer, value_labelInfo_value_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): TextMenuItem {
        let valueDeserializer : DeserializerBase = buffer
        const content_buf_selector : int32 = valueDeserializer.readInt8()
        let content_buf : string | Resource | undefined
        if (content_buf_selector == (0).toChar()) {
            content_buf = (valueDeserializer.readString() as string)
        }
        else if (content_buf_selector == (1).toChar()) {
            content_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for content_buf has to be chosen through deserialisation.")
        }
        const content_result : ResourceStr = (content_buf as string | Resource)
        const icon_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let icon_buf : ResourceStr | undefined
        if ((icon_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const icon_buf__selector : int32 = valueDeserializer.readInt8()
            let icon_buf_ : string | Resource | undefined
            if (icon_buf__selector == (0).toChar()) {
                icon_buf_ = (valueDeserializer.readString() as string)
            }
            else if (icon_buf__selector == (1).toChar()) {
                icon_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for icon_buf_ has to be chosen through deserialisation.")
            }
            icon_buf = (icon_buf_ as string | Resource)
        }
        const icon_result : ResourceStr | undefined = icon_buf
        const id_result : TextMenuItemId = (TextMenuItemId_serializer.read(valueDeserializer) as TextMenuItemId)
        const labelInfo_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let labelInfo_buf : ResourceStr | undefined
        if ((labelInfo_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const labelInfo_buf__selector : int32 = valueDeserializer.readInt8()
            let labelInfo_buf_ : string | Resource | undefined
            if (labelInfo_buf__selector == (0).toChar()) {
                labelInfo_buf_ = (valueDeserializer.readString() as string)
            }
            else if (labelInfo_buf__selector == (1).toChar()) {
                labelInfo_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for labelInfo_buf_ has to be chosen through deserialisation.")
            }
            labelInfo_buf = (labelInfo_buf_ as string | Resource)
        }
        const labelInfo_result : ResourceStr | undefined = labelInfo_buf
        let value : TextMenuItem = ({content: content_result, icon: icon_result, id: id_result, labelInfo: labelInfo_result} as TextMenuItem)
        return value
    }
}
export class CaretStyle_serializer {
    public static write(buffer: SerializerBase, value: CaretStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_width  = value.width
        let value_width_type : int32 = RuntimeType.UNDEFINED
        value_width_type = runtimeType(value_width)
        valueSerializer.writeInt8((value_width_type).toChar())
        if ((value_width_type) != (RuntimeType.UNDEFINED)) {
            const value_width_value  = value_width!
            let value_width_value_type : int32 = RuntimeType.UNDEFINED
            value_width_value_type = runtimeType(value_width_value)
            if (RuntimeType.STRING == value_width_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_width_value_0  = value_width_value as string
                valueSerializer.writeString(value_width_value_0)
            }
            else if (RuntimeType.NUMBER == value_width_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_width_value_1  = value_width_value as number
                valueSerializer.writeNumber(value_width_value_1)
            }
            else if (RuntimeType.OBJECT == value_width_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_width_value_2  = value_width_value as Resource
                Resource_serializer.write(valueSerializer, value_width_value_2)
            }
        }
        const value_color  = value.color
        let value_color_type : int32 = RuntimeType.UNDEFINED
        value_color_type = runtimeType(value_color)
        valueSerializer.writeInt8((value_color_type).toChar())
        if ((value_color_type) != (RuntimeType.UNDEFINED)) {
            const value_color_value  = value_color!
            let value_color_value_type : int32 = RuntimeType.UNDEFINED
            value_color_value_type = runtimeType(value_color_value)
            if (TypeChecker.isColor(value_color_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_color_value_0  = value_color_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_color_value_0))
            }
            else if (RuntimeType.NUMBER == value_color_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_color_value_1  = value_color_value as number
                valueSerializer.writeNumber(value_color_value_1)
            }
            else if (RuntimeType.STRING == value_color_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_color_value_2  = value_color_value as string
                valueSerializer.writeString(value_color_value_2)
            }
            else if (RuntimeType.OBJECT == value_color_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_color_value_3  = value_color_value as Resource
                Resource_serializer.write(valueSerializer, value_color_value_3)
            }
        }
    }
    public static read(buffer: DeserializerBase): CaretStyle {
        let valueDeserializer : DeserializerBase = buffer
        const width_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let width_buf : Length | undefined
        if ((width_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const width_buf__selector : int32 = valueDeserializer.readInt8()
            let width_buf_ : string | number | Resource | undefined
            if (width_buf__selector == (0).toChar()) {
                width_buf_ = (valueDeserializer.readString() as string)
            }
            else if (width_buf__selector == (1).toChar()) {
                width_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (width_buf__selector == (2).toChar()) {
                width_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for width_buf_ has to be chosen through deserialisation.")
            }
            width_buf = (width_buf_ as string | number | Resource)
        }
        const width_result : Length | undefined = width_buf
        const color_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let color_buf : ResourceColor | undefined
        if ((color_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const color_buf__selector : int32 = valueDeserializer.readInt8()
            let color_buf_ : Color | number | string | Resource | undefined
            if (color_buf__selector == (0).toChar()) {
                color_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (color_buf__selector == (1).toChar()) {
                color_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (color_buf__selector == (2).toChar()) {
                color_buf_ = (valueDeserializer.readString() as string)
            }
            else if (color_buf__selector == (3).toChar()) {
                color_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for color_buf_ has to be chosen through deserialisation.")
            }
            color_buf = (color_buf_ as Color | number | string | Resource)
        }
        const color_result : ResourceColor | undefined = color_buf
        let value : CaretStyle = ({width: width_result, color: color_result} as CaretStyle)
        return value
    }
}
export class EditableTextChangeValue_serializer {
    public static write(buffer: SerializerBase, value: EditableTextChangeValue): void {
        let valueSerializer : SerializerBase = buffer
        const value_content  = value.content
        valueSerializer.writeString(value_content)
        const value_previewText  = value.previewText
        let value_previewText_type : int32 = RuntimeType.UNDEFINED
        value_previewText_type = runtimeType(value_previewText)
        valueSerializer.writeInt8((value_previewText_type).toChar())
        if ((value_previewText_type) != (RuntimeType.UNDEFINED)) {
            const value_previewText_value  = value_previewText!
            PreviewText_serializer.write(valueSerializer, value_previewText_value)
        }
        const value_options  = value.options
        let value_options_type : int32 = RuntimeType.UNDEFINED
        value_options_type = runtimeType(value_options)
        valueSerializer.writeInt8((value_options_type).toChar())
        if ((value_options_type) != (RuntimeType.UNDEFINED)) {
            const value_options_value  = value_options!
            TextChangeOptions_serializer.write(valueSerializer, value_options_value)
        }
    }
    public static read(buffer: DeserializerBase): EditableTextChangeValue {
        let valueDeserializer : DeserializerBase = buffer
        const content_result : string = (valueDeserializer.readString() as string)
        const previewText_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let previewText_buf : PreviewText | undefined
        if ((previewText_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            previewText_buf = PreviewText_serializer.read(valueDeserializer)
        }
        const previewText_result : PreviewText | undefined = previewText_buf
        const options_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let options_buf : TextChangeOptions | undefined
        if ((options_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            options_buf = TextChangeOptions_serializer.read(valueDeserializer)
        }
        const options_result : TextChangeOptions | undefined = options_buf
        let value : EditableTextChangeValue = ({content: content_result, previewText: previewText_result, options: options_result} as EditableTextChangeValue)
        return value
    }
}
export class TextDataDetectorConfig_serializer {
    public static write(buffer: SerializerBase, value: TextDataDetectorConfig): void {
        let valueSerializer : SerializerBase = buffer
        const value_types  = value.types
        valueSerializer.writeInt32((value_types.length).toInt())
        for (let value_types_counter_i = 0; value_types_counter_i < value_types.length; value_types_counter_i++) {
            const value_types_element : TextDataDetectorType = value_types[value_types_counter_i]
            valueSerializer.writeInt32(TypeChecker.TextDataDetectorType_ToNumeric(value_types_element))
        }
        const value_onDetectResultUpdate  = value.onDetectResultUpdate
        let value_onDetectResultUpdate_type : int32 = RuntimeType.UNDEFINED
        value_onDetectResultUpdate_type = runtimeType(value_onDetectResultUpdate)
        valueSerializer.writeInt8((value_onDetectResultUpdate_type).toChar())
        if ((value_onDetectResultUpdate_type) != (RuntimeType.UNDEFINED)) {
            const value_onDetectResultUpdate_value  = value_onDetectResultUpdate!
            valueSerializer.holdAndWriteCallback(value_onDetectResultUpdate_value)
        }
        const value_color  = value.color
        let value_color_type : int32 = RuntimeType.UNDEFINED
        value_color_type = runtimeType(value_color)
        valueSerializer.writeInt8((value_color_type).toChar())
        if ((value_color_type) != (RuntimeType.UNDEFINED)) {
            const value_color_value  = value_color!
            let value_color_value_type : int32 = RuntimeType.UNDEFINED
            value_color_value_type = runtimeType(value_color_value)
            if (TypeChecker.isColor(value_color_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_color_value_0  = value_color_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_color_value_0))
            }
            else if (RuntimeType.NUMBER == value_color_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_color_value_1  = value_color_value as number
                valueSerializer.writeNumber(value_color_value_1)
            }
            else if (RuntimeType.STRING == value_color_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_color_value_2  = value_color_value as string
                valueSerializer.writeString(value_color_value_2)
            }
            else if (RuntimeType.OBJECT == value_color_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_color_value_3  = value_color_value as Resource
                Resource_serializer.write(valueSerializer, value_color_value_3)
            }
        }
        const value_decoration  = value.decoration
        let value_decoration_type : int32 = RuntimeType.UNDEFINED
        value_decoration_type = runtimeType(value_decoration)
        valueSerializer.writeInt8((value_decoration_type).toChar())
        if ((value_decoration_type) != (RuntimeType.UNDEFINED)) {
            const value_decoration_value  = value_decoration!
            DecorationStyleInterface_serializer.write(valueSerializer, value_decoration_value)
        }
    }
    public static read(buffer: DeserializerBase): TextDataDetectorConfig {
        let valueDeserializer : DeserializerBase = buffer
        const types_buf_length : int32 = valueDeserializer.readInt32()
        let types_buf : Array<TextDataDetectorType> = new Array<TextDataDetectorType>(types_buf_length)
        for (let types_buf_i = 0; types_buf_i < types_buf_length; types_buf_i++) {
            types_buf[types_buf_i] = TypeChecker.TextDataDetectorType_FromNumeric(valueDeserializer.readInt32())
        }
        const types_result : Array<TextDataDetectorType> = types_buf
        const onDetectResultUpdate_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDetectResultUpdate_buf : ((value0: string) => void) | undefined
        if ((onDetectResultUpdate_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onDetectResultUpdate_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDetectResultUpdate_buf__call : KPointer = valueDeserializer.readPointer()
            const onDetectResultUpdate_buf__callSync : KPointer = valueDeserializer.readPointer()
            onDetectResultUpdate_buf = (value0: string):void => { 
    const onDetectResultUpdate_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onDetectResultUpdate_buf__argsSerializer.writeInt32(onDetectResultUpdate_buf__resource.resourceId);
    onDetectResultUpdate_buf__argsSerializer.writePointer(onDetectResultUpdate_buf__call);
    onDetectResultUpdate_buf__argsSerializer.writePointer(onDetectResultUpdate_buf__callSync);
    onDetectResultUpdate_buf__argsSerializer.writeString(value0);
    InteropNativeModule._CallCallback(814634522, onDetectResultUpdate_buf__argsSerializer.asBuffer(), onDetectResultUpdate_buf__argsSerializer.length());
    onDetectResultUpdate_buf__argsSerializer.release();
    return; }
        }
        const onDetectResultUpdate_result : ((value0: string) => void) | undefined = onDetectResultUpdate_buf
        const color_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let color_buf : ResourceColor | undefined
        if ((color_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const color_buf__selector : int32 = valueDeserializer.readInt8()
            let color_buf_ : Color | number | string | Resource | undefined
            if (color_buf__selector == (0).toChar()) {
                color_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (color_buf__selector == (1).toChar()) {
                color_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (color_buf__selector == (2).toChar()) {
                color_buf_ = (valueDeserializer.readString() as string)
            }
            else if (color_buf__selector == (3).toChar()) {
                color_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for color_buf_ has to be chosen through deserialisation.")
            }
            color_buf = (color_buf_ as Color | number | string | Resource)
        }
        const color_result : ResourceColor | undefined = color_buf
        const decoration_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let decoration_buf : DecorationStyleInterface | undefined
        if ((decoration_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            decoration_buf = DecorationStyleInterface_serializer.read(valueDeserializer)
        }
        const decoration_result : DecorationStyleInterface | undefined = decoration_buf
        let value : TextDataDetectorConfig = ({types: types_result, onDetectResultUpdate: onDetectResultUpdate_result, color: color_result, decoration: decoration_result} as TextDataDetectorConfig)
        return value
    }
}
export interface TextEditControllerEx {
    isEditing(): boolean
    stopEditing(): void
    setCaretOffset(offset: number): boolean
    getCaretOffset(): number
    getPreviewText(): PreviewText
}
export class TextEditControllerExInternal extends TextBaseControllerInternal implements MaterializedBase,TextEditControllerEx {
    constructor(peerPtr: KPointer) {
        super(peerPtr)
    }
    constructor() {
        this(TextEditControllerExInternal.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextEditControllerEx_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextEditControllerEx_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): TextEditControllerExInternal {
        return new TextEditControllerExInternal(ptr)
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
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : PreviewText = PreviewText_serializer.read(retvalDeserializer)
        return returnResult
    }
}
