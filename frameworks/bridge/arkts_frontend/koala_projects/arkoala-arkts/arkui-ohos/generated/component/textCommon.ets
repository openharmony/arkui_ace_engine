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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, DeserializerBase, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
import { StyledString, StyledStringInternal, MutableStyledString, MutableStyledStringInternal, DecorationStyleInterface, StyledString_serializer, DecorationStyleInterface_serializer } from "./styledString"
import { SelectionOptions_serializer, SelectionOptions } from "./common"
import { Resource_serializer } from "./../framework/resource"
import { ResourceStr, ResourceColor, Length } from "./units"
import { Resource } from "global.resource"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { Color, TextDecorationType, TextDecorationStyle } from "./enums"
export interface LayoutManager {
    getLineCount(): int32
    getGlyphPositionAtCoordinate(x: double, y: double): PositionWithAffinity
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
    public getLineCount(): int32 {
        return this.getLineCount_serialize()
    }
    public getGlyphPositionAtCoordinate(x: double, y: double): PositionWithAffinity {
        const x_casted = x as (double)
        const y_casted = y as (double)
        return this.getGlyphPositionAtCoordinate_serialize(x_casted, y_casted)
    }
    getLineCount_serialize(): int32 {
        const retval  = ArkUIGeneratedNativeModule._LayoutManager_getLineCount(this.peer!.ptr)
        return retval
    }
    getGlyphPositionAtCoordinate_serialize(x: double, y: double): PositionWithAffinity {
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
    setStyledString_serialize(styledString: StyledString): void {
        ArkUIGeneratedNativeModule._StyledStringController_setStyledString(this.peer!.ptr, toPeerPtr(styledString))
    }
    getStyledString_serialize(): MutableStyledString {
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
    setSelection_serialize(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            SelectionOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._TextBaseController_setSelection(this.peer!.ptr, selectionStart, selectionEnd, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    closeSelectionMenu_serialize(): void {
        ArkUIGeneratedNativeModule._TextBaseController_closeSelectionMenu(this.peer!.ptr)
    }
    getLayoutManager_serialize(): LayoutManager {
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
    static of_serialize(id: ResourceStr): TextMenuItemId {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (id instanceof string) {
            thisSerializer.writeInt8((0).toByte())
            const idForIdx0  = id as string
            thisSerializer.writeString(idForIdx0)
        } else if (id instanceof Resource) {
            thisSerializer.writeInt8((1).toByte())
            const idForIdx1  = id as Resource
            Resource_serializer.write(thisSerializer, idForIdx1)
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
    equals_serialize(id: TextMenuItemId): boolean {
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
    types: Array<TextDataDetectorType> | null | undefined;
    onDetectResultUpdate?: ((value0: string) => void);
    color?: ResourceColor;
    decoration?: DecorationStyleInterface;
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
    onWillChange?: ((value0: StyledStringChangeValue) => boolean);
    onDidChange?: OnDidChangeCallback;
}
export interface StyledStringChangeValue {
    range: TextRange;
    replacementString: StyledString;
    previewText?: StyledString;
}
export interface PositionWithAffinity {
    position: int32;
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
        const valueHolderForPosition  = value.position
        valueSerializer.writeInt32(valueHolderForPosition)
    }
    public static read(buffer: DeserializerBase): PositionWithAffinity {
        let valueDeserializer : DeserializerBase = buffer
        const positionTmpResult : int32 = valueDeserializer.readInt32()
        let value : PositionWithAffinity = ({position: positionTmpResult} as PositionWithAffinity)
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
        const valueHolderForDeleteOffset  = value.deleteOffset
        valueSerializer.writeInt32(valueHolderForDeleteOffset)
        const valueHolderForDirection  = value.direction
        valueSerializer.writeInt32(valueHolderForDirection.valueOf())
        const valueHolderForDeleteValue  = value.deleteValue
        valueSerializer.writeString(valueHolderForDeleteValue)
    }
    public static read(buffer: DeserializerBase): DeleteValue {
        let valueDeserializer : DeserializerBase = buffer
        const deleteOffsetTmpResult : int32 = valueDeserializer.readInt32()
        const directionTmpResult : TextDeleteDirection = TextDeleteDirection.fromValue(valueDeserializer.readInt32())
        const deleteValueTmpResult : string = (valueDeserializer.readString() as string)
        let value : DeleteValue = ({deleteOffset: deleteOffsetTmpResult, direction: directionTmpResult, deleteValue: deleteValueTmpResult} as DeleteValue)
        return value
    }
}
export class EditMenuOptions_serializer {
    public static write(buffer: SerializerBase, value: EditMenuOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForOnCreateMenu  = value.onCreateMenu
        valueSerializer.holdAndWriteCallback(valueHolderForOnCreateMenu)
        const valueHolderForOnMenuItemClick  = value.onMenuItemClick
        valueSerializer.holdAndWriteCallback(valueHolderForOnMenuItemClick)
    }
    public static read(buffer: DeserializerBase): EditMenuOptions {
        let valueDeserializer : DeserializerBase = buffer
        const onCreateMenuTmpBufBufResource : CallbackResource = valueDeserializer.readCallbackResource()
        const onCreateMenuTmpBufBufCall : KPointer = valueDeserializer.readPointer()
        const onCreateMenuTmpBufBufCallSync : KPointer = valueDeserializer.readPointer()
        const onCreateMenuTmpResult : OnCreateMenuCallback = (menuItems: Array<TextMenuItem>):Array<TextMenuItem> => {
            const onCreateMenuTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            onCreateMenuTmpBufBufArgsSerializer.writeInt32(onCreateMenuTmpBufBufResource.resourceId);
            onCreateMenuTmpBufBufArgsSerializer.writePointer(onCreateMenuTmpBufBufCall);
            onCreateMenuTmpBufBufArgsSerializer.writePointer(onCreateMenuTmpBufBufCallSync);
            onCreateMenuTmpBufBufArgsSerializer.writeInt32((menuItems.length).toInt());
            for (let menuItemsCounterI = 0; menuItemsCounterI < menuItems.length; menuItemsCounterI++) {
                const menuItemsTmpElement : TextMenuItem = menuItems[menuItemsCounterI];
                TextMenuItem_serializer.write(onCreateMenuTmpBufBufArgsSerializer, menuItemsTmpElement);
            }
            let onCreateMenuTmpBufBufContinuationValue : Array<TextMenuItem> | undefined;
            const onCreateMenuTmpBufBufContinuationCallback : ((value: Array<TextMenuItem>) => void) = (value: Array<TextMenuItem>):void => {
            onCreateMenuTmpBufBufContinuationValue = value;
        }
            onCreateMenuTmpBufBufArgsSerializer.holdAndWriteCallback(onCreateMenuTmpBufBufContinuationCallback);
            InteropNativeModule._CallCallbackSync(10, 312701677, onCreateMenuTmpBufBufArgsSerializer.asBuffer(), onCreateMenuTmpBufBufArgsSerializer.length());
            onCreateMenuTmpBufBufArgsSerializer.release();
            return (onCreateMenuTmpBufBufContinuationValue as Array<TextMenuItem>);
        }
        const onMenuItemClickTmpBufBufResource : CallbackResource = valueDeserializer.readCallbackResource()
        const onMenuItemClickTmpBufBufCall : KPointer = valueDeserializer.readPointer()
        const onMenuItemClickTmpBufBufCallSync : KPointer = valueDeserializer.readPointer()
        const onMenuItemClickTmpResult : OnMenuItemClickCallback = (menuItem: TextMenuItem, range: TextRange):boolean => {
            const onMenuItemClickTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            onMenuItemClickTmpBufBufArgsSerializer.writeInt32(onMenuItemClickTmpBufBufResource.resourceId);
            onMenuItemClickTmpBufBufArgsSerializer.writePointer(onMenuItemClickTmpBufBufCall);
            onMenuItemClickTmpBufBufArgsSerializer.writePointer(onMenuItemClickTmpBufBufCallSync);
            TextMenuItem_serializer.write(onMenuItemClickTmpBufBufArgsSerializer, menuItem);
            TextRange_serializer.write(onMenuItemClickTmpBufBufArgsSerializer, range);
            let onMenuItemClickTmpBufBufContinuationValue : boolean | undefined;
            const onMenuItemClickTmpBufBufContinuationCallback : ((value0: boolean) => void) = (value: boolean):void => {
            onMenuItemClickTmpBufBufContinuationValue = value;
        }
            onMenuItemClickTmpBufBufArgsSerializer.holdAndWriteCallback(onMenuItemClickTmpBufBufContinuationCallback);
            InteropNativeModule._CallCallbackSync(10, -1106041422, onMenuItemClickTmpBufBufArgsSerializer.asBuffer(), onMenuItemClickTmpBufBufArgsSerializer.length());
            onMenuItemClickTmpBufBufArgsSerializer.release();
            return (onMenuItemClickTmpBufBufContinuationValue as boolean);
        }
        let value : EditMenuOptions = ({onCreateMenu: onCreateMenuTmpResult, onMenuItemClick: onMenuItemClickTmpResult} as EditMenuOptions)
        return value
    }
}
export class FontSettingOptions_serializer {
    public static write(buffer: SerializerBase, value: FontSettingOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForEnableVariableFontWeight  = value.enableVariableFontWeight
        if (valueHolderForEnableVariableFontWeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableVariableFontWeightTmpValue  = valueHolderForEnableVariableFontWeight!
            valueSerializer.writeBoolean(valueHolderForEnableVariableFontWeightTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): FontSettingOptions {
        let valueDeserializer : DeserializerBase = buffer
        const enableVariableFontWeightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableVariableFontWeightTmpBuf : boolean | undefined = undefined
        if ((enableVariableFontWeightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableVariableFontWeightTmpBuf = valueDeserializer.readBoolean()
        }
        const enableVariableFontWeightTmpResult : boolean | undefined = enableVariableFontWeightTmpBuf
        let value : FontSettingOptions = ({enableVariableFontWeight: enableVariableFontWeightTmpResult} as FontSettingOptions)
        return value
    }
}
export class InsertValue_serializer {
    public static write(buffer: SerializerBase, value: InsertValue): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForInsertOffset  = value.insertOffset
        valueSerializer.writeInt32(valueHolderForInsertOffset)
        const valueHolderForInsertValue  = value.insertValue
        valueSerializer.writeString(valueHolderForInsertValue)
    }
    public static read(buffer: DeserializerBase): InsertValue {
        let valueDeserializer : DeserializerBase = buffer
        const insertOffsetTmpResult : int32 = valueDeserializer.readInt32()
        const insertValueTmpResult : string = (valueDeserializer.readString() as string)
        let value : InsertValue = ({insertOffset: insertOffsetTmpResult, insertValue: insertValueTmpResult} as InsertValue)
        return value
    }
}
export class PreviewText_serializer {
    public static write(buffer: SerializerBase, value: PreviewText): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForOffset  = value.offset
        valueSerializer.writeInt32(valueHolderForOffset)
        const valueHolderForValue  = value.value
        valueSerializer.writeString(valueHolderForValue)
    }
    public static read(buffer: DeserializerBase): PreviewText {
        let valueDeserializer : DeserializerBase = buffer
        const offsetTmpResult : int32 = valueDeserializer.readInt32()
        const valueTmpResult : string = (valueDeserializer.readString() as string)
        let value : PreviewText = ({offset: offsetTmpResult, value: valueTmpResult} as PreviewText)
        return value
    }
}
export class StyledStringChangedListener_serializer {
    public static write(buffer: SerializerBase, value: StyledStringChangedListener): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForOnWillChange  = value.onWillChange
        if (valueHolderForOnWillChange !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnWillChangeTmpValue  = valueHolderForOnWillChange!
            valueSerializer.holdAndWriteCallback(valueHolderForOnWillChangeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnDidChange  = value.onDidChange
        if (valueHolderForOnDidChange !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnDidChangeTmpValue  = valueHolderForOnDidChange!
            valueSerializer.holdAndWriteCallback(valueHolderForOnDidChangeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): StyledStringChangedListener {
        let valueDeserializer : DeserializerBase = buffer
        const onWillChangeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillChangeTmpBuf : ((value0: StyledStringChangeValue) => boolean) | undefined = undefined
        if ((onWillChangeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillChangeTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillChangeTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onWillChangeTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onWillChangeTmpBuf = (value0: StyledStringChangeValue):boolean => {
                const onWillChangeTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillChangeTmpBuf_BufArgsSerializer.writeInt32(onWillChangeTmpBuf_BufResource.resourceId);
                onWillChangeTmpBuf_BufArgsSerializer.writePointer(onWillChangeTmpBuf_BufCall);
                onWillChangeTmpBuf_BufArgsSerializer.writePointer(onWillChangeTmpBuf_BufCallSync);
                StyledStringChangeValue_serializer.write(onWillChangeTmpBuf_BufArgsSerializer, value0);
                let onWillChangeTmpBuf_BufContinuationValue : boolean | undefined;
                const onWillChangeTmpBuf_BufContinuationCallback : ((value0: boolean) => void) = (value: boolean):void => {
                onWillChangeTmpBuf_BufContinuationValue = value;
            }
                onWillChangeTmpBuf_BufArgsSerializer.holdAndWriteCallback(onWillChangeTmpBuf_BufContinuationCallback);
                InteropNativeModule._CallCallbackSync(10, 2116745428, onWillChangeTmpBuf_BufArgsSerializer.asBuffer(), onWillChangeTmpBuf_BufArgsSerializer.length());
                onWillChangeTmpBuf_BufArgsSerializer.release();
                return (onWillChangeTmpBuf_BufContinuationValue as boolean);
            }
        }
        const onWillChangeTmpResult : ((value0: StyledStringChangeValue) => boolean) | undefined = onWillChangeTmpBuf
        const onDidChangeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDidChangeTmpBuf : OnDidChangeCallback | undefined = undefined
        if ((onDidChangeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidChangeTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidChangeTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onDidChangeTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onDidChangeTmpBuf = (rangeBefore: TextRange, rangeAfter: TextRange):void => {
                const onDidChangeTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDidChangeTmpBuf_BufArgsSerializer.writeInt32(onDidChangeTmpBuf_BufResource.resourceId);
                onDidChangeTmpBuf_BufArgsSerializer.writePointer(onDidChangeTmpBuf_BufCall);
                onDidChangeTmpBuf_BufArgsSerializer.writePointer(onDidChangeTmpBuf_BufCallSync);
                TextRange_serializer.write(onDidChangeTmpBuf_BufArgsSerializer, rangeBefore);
                TextRange_serializer.write(onDidChangeTmpBuf_BufArgsSerializer, rangeAfter);
                InteropNativeModule._CallCallbackSync(10, 1648184341, onDidChangeTmpBuf_BufArgsSerializer.asBuffer(), onDidChangeTmpBuf_BufArgsSerializer.length());
                onDidChangeTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onDidChangeTmpResult : OnDidChangeCallback | undefined = onDidChangeTmpBuf
        let value : StyledStringChangedListener = ({onWillChange: onWillChangeTmpResult, onDidChange: onDidChangeTmpResult} as StyledStringChangedListener)
        return value
    }
}
export class TextMenuOptions_serializer {
    public static write(buffer: SerializerBase, value: TextMenuOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForShowMode  = value.showMode
        if (valueHolderForShowMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShowModeTmpValue  = (valueHolderForShowMode as TextMenuShowMode)
            valueSerializer.writeInt32(valueHolderForShowModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): TextMenuOptions {
        let valueDeserializer : DeserializerBase = buffer
        const showModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let showModeTmpBuf : TextMenuShowMode | undefined = undefined
        if ((showModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            showModeTmpBuf = TextMenuShowMode.fromValue(valueDeserializer.readInt32())
        }
        const showModeTmpResult : TextMenuShowMode | undefined = showModeTmpBuf
        let value : TextMenuOptions = ({showMode: showModeTmpResult} as TextMenuOptions)
        return value
    }
}
export class TextRange_serializer {
    public static write(buffer: SerializerBase, value: TextRange): void {
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
    public static read(buffer: DeserializerBase): TextRange {
        let valueDeserializer : DeserializerBase = buffer
        const startTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let startTmpBuf : int32 | undefined = undefined
        if ((startTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startTmpBuf = valueDeserializer.readInt32()
        }
        const startTmpResult : int32 | undefined = startTmpBuf
        const endTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let endTmpBuf : int32 | undefined = undefined
        if ((endTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endTmpBuf = valueDeserializer.readInt32()
        }
        const endTmpResult : int32 | undefined = endTmpBuf
        let value : TextRange = ({start: startTmpResult, end: endTmpResult} as TextRange)
        return value
    }
}
export class DecorationStyleResult_serializer {
    public static write(buffer: SerializerBase, value: DecorationStyleResult): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForType  = value.type
        valueSerializer.writeInt32(valueHolderForType.valueOf())
        const valueHolderForColor  = value.color
        if (valueHolderForColor instanceof Color) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForColorForIdx0  = valueHolderForColor as Color
            valueSerializer.writeInt32(valueHolderForColorForIdx0.getOrdinal())
        } else if (valueHolderForColor instanceof number) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForColorForIdx1  = valueHolderForColor as number
            valueSerializer.writeNumber(valueHolderForColorForIdx1)
        } else if (valueHolderForColor instanceof string) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForColorForIdx2  = valueHolderForColor as string
            valueSerializer.writeString(valueHolderForColorForIdx2)
        } else if (valueHolderForColor instanceof Resource) {
            valueSerializer.writeInt8((3).toByte())
            const valueHolderForColorForIdx3  = valueHolderForColor as Resource
            Resource_serializer.write(valueSerializer, valueHolderForColorForIdx3)
        }
        const valueHolderForStyle  = value.style
        if (valueHolderForStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStyleTmpValue  = (valueHolderForStyle as TextDecorationStyle)
            valueSerializer.writeInt32(valueHolderForStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): DecorationStyleResult {
        let valueDeserializer : DeserializerBase = buffer
        const typeTmpResult : TextDecorationType = TextDecorationType.fromValue(valueDeserializer.readInt32())
        const colorTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let colorTmpBuf : Color | number | string | Resource | undefined
        if (colorTmpBufUnionSelector == (0).toChar()) {
            colorTmpBuf = Color.values()[valueDeserializer.readInt32()]
        } else if (colorTmpBufUnionSelector == (1).toChar()) {
            colorTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (colorTmpBufUnionSelector == (2).toChar()) {
            colorTmpBuf = (valueDeserializer.readString() as string)
        } else if (colorTmpBufUnionSelector == (3).toChar()) {
            colorTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for colorTmpBuf has to be chosen through deserialisation.")
        }
        const colorTmpResult : ResourceColor = (colorTmpBuf as Color | number | string | Resource)
        const styleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let styleTmpBuf : TextDecorationStyle | undefined = undefined
        if ((styleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            styleTmpBuf = TextDecorationStyle.fromValue(valueDeserializer.readInt32())
        }
        const styleTmpResult : TextDecorationStyle | undefined = styleTmpBuf
        let value : DecorationStyleResult = ({type: typeTmpResult, color: colorTmpResult, style: styleTmpResult} as DecorationStyleResult)
        return value
    }
}
export class StyledStringChangeValue_serializer {
    public static write(buffer: SerializerBase, value: StyledStringChangeValue): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForRange  = value.range
        TextRange_serializer.write(valueSerializer, valueHolderForRange)
        const valueHolderForReplacementString  = value.replacementString
        StyledString_serializer.write(valueSerializer, valueHolderForReplacementString)
        const valueHolderForPreviewText  = value.previewText
        if (valueHolderForPreviewText !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPreviewTextTmpValue  = valueHolderForPreviewText!
            StyledString_serializer.write(valueSerializer, valueHolderForPreviewTextTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): StyledStringChangeValue {
        let valueDeserializer : DeserializerBase = buffer
        const rangeTmpResult : TextRange = TextRange_serializer.read(valueDeserializer)
        const replacementStringTmpResult : StyledString = (StyledString_serializer.read(valueDeserializer) as StyledString)
        const previewTextTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let previewTextTmpBuf : StyledString | undefined = undefined
        if ((previewTextTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            previewTextTmpBuf = (StyledString_serializer.read(valueDeserializer) as StyledString)
        }
        const previewTextTmpResult : StyledString | undefined = previewTextTmpBuf
        let value : StyledStringChangeValue = ({range: rangeTmpResult, replacementString: replacementStringTmpResult, previewText: previewTextTmpResult} as StyledStringChangeValue)
        return value
    }
}
export class TextChangeOptions_serializer {
    public static write(buffer: SerializerBase, value: TextChangeOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForRangeBefore  = value.rangeBefore
        TextRange_serializer.write(valueSerializer, valueHolderForRangeBefore)
        const valueHolderForRangeAfter  = value.rangeAfter
        TextRange_serializer.write(valueSerializer, valueHolderForRangeAfter)
        const valueHolderForOldContent  = value.oldContent
        valueSerializer.writeString(valueHolderForOldContent)
        const valueHolderForOldPreviewText  = value.oldPreviewText
        PreviewText_serializer.write(valueSerializer, valueHolderForOldPreviewText)
    }
    public static read(buffer: DeserializerBase): TextChangeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const rangeBeforeTmpResult : TextRange = TextRange_serializer.read(valueDeserializer)
        const rangeAfterTmpResult : TextRange = TextRange_serializer.read(valueDeserializer)
        const oldContentTmpResult : string = (valueDeserializer.readString() as string)
        const oldPreviewTextTmpResult : PreviewText = PreviewText_serializer.read(valueDeserializer)
        let value : TextChangeOptions = ({rangeBefore: rangeBeforeTmpResult, rangeAfter: rangeAfterTmpResult, oldContent: oldContentTmpResult, oldPreviewText: oldPreviewTextTmpResult} as TextChangeOptions)
        return value
    }
}
export class TextMenuItem_serializer {
    public static write(buffer: SerializerBase, value: TextMenuItem): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForContent  = value.content
        if (valueHolderForContent instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForContentForIdx0  = valueHolderForContent as string
            valueSerializer.writeString(valueHolderForContentForIdx0)
        } else if (valueHolderForContent instanceof Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForContentForIdx1  = valueHolderForContent as Resource
            Resource_serializer.write(valueSerializer, valueHolderForContentForIdx1)
        }
        const valueHolderForIcon  = value.icon
        if (valueHolderForIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIconTmpValue  = valueHolderForIcon!
            if (valueHolderForIconTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForIconTmpValueForIdx0  = valueHolderForIconTmpValue as string
                valueSerializer.writeString(valueHolderForIconTmpValueForIdx0)
            } else if (valueHolderForIconTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForIconTmpValueForIdx1  = valueHolderForIconTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForIconTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForId  = value.id
        TextMenuItemId_serializer.write(valueSerializer, valueHolderForId)
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
    }
    public static read(buffer: DeserializerBase): TextMenuItem {
        let valueDeserializer : DeserializerBase = buffer
        const contentTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let contentTmpBuf : string | Resource | undefined
        if (contentTmpBufUnionSelector == (0).toChar()) {
            contentTmpBuf = (valueDeserializer.readString() as string)
        } else if (contentTmpBufUnionSelector == (1).toChar()) {
            contentTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for contentTmpBuf has to be chosen through deserialisation.")
        }
        const contentTmpResult : ResourceStr = (contentTmpBuf as string | Resource)
        const iconTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let iconTmpBuf : ResourceStr | undefined = undefined
        if ((iconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const iconTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let iconTmpBuf_ : string | Resource | undefined
            if (iconTmpBuf_UnionSelector == (0).toChar()) {
                iconTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (iconTmpBuf_UnionSelector == (1).toChar()) {
                iconTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for iconTmpBuf_ has to be chosen through deserialisation.")
            }
            iconTmpBuf = (iconTmpBuf_ as string | Resource)
        }
        const iconTmpResult : ResourceStr | undefined = iconTmpBuf
        const idTmpResult : TextMenuItemId = (TextMenuItemId_serializer.read(valueDeserializer) as TextMenuItemId)
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
        let value : TextMenuItem = ({content: contentTmpResult, icon: iconTmpResult, id: idTmpResult, labelInfo: labelInfoTmpResult} as TextMenuItem)
        return value
    }
}
export class CaretStyle_serializer {
    public static write(buffer: SerializerBase, value: CaretStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as string
                valueSerializer.writeString(valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForWidthTmpValueForIdx1  = valueHolderForWidthTmpValue as number
                valueSerializer.writeNumber(valueHolderForWidthTmpValueForIdx1)
            } else if (valueHolderForWidthTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForWidthTmpValueForIdx2  = valueHolderForWidthTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForColor  = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue  = valueHolderForColor!
            if (valueHolderForColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForColorTmpValueForIdx0  = valueHolderForColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForColorTmpValueForIdx1  = valueHolderForColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForColorTmpValueForIdx1)
            } else if (valueHolderForColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForColorTmpValueForIdx2  = valueHolderForColorTmpValue as string
                valueSerializer.writeString(valueHolderForColorTmpValueForIdx2)
            } else if (valueHolderForColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForColorTmpValueForIdx3  = valueHolderForColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): CaretStyle {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let widthTmpBuf : Length | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBuf_ : string | number | Resource | undefined
            if (widthTmpBuf_UnionSelector == (0).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (widthTmpBuf_UnionSelector == (1).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (widthTmpBuf_UnionSelector == (2).toChar()) {
                widthTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for widthTmpBuf_ has to be chosen through deserialisation.")
            }
            widthTmpBuf = (widthTmpBuf_ as string | number | Resource)
        }
        const widthTmpResult : Length | undefined = widthTmpBuf
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colorTmpBuf : ResourceColor | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBuf_ : Color | number | string | Resource | undefined
            if (colorTmpBuf_UnionSelector == (0).toChar()) {
                colorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (colorTmpBuf_UnionSelector == (1).toChar()) {
                colorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (colorTmpBuf_UnionSelector == (2).toChar()) {
                colorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (colorTmpBuf_UnionSelector == (3).toChar()) {
                colorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for colorTmpBuf_ has to be chosen through deserialisation.")
            }
            colorTmpBuf = (colorTmpBuf_ as Color | number | string | Resource)
        }
        const colorTmpResult : ResourceColor | undefined = colorTmpBuf
        let value : CaretStyle = ({width: widthTmpResult, color: colorTmpResult} as CaretStyle)
        return value
    }
}
export class EditableTextChangeValue_serializer {
    public static write(buffer: SerializerBase, value: EditableTextChangeValue): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForContent  = value.content
        valueSerializer.writeString(valueHolderForContent)
        const valueHolderForPreviewText  = value.previewText
        if (valueHolderForPreviewText !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPreviewTextTmpValue  = valueHolderForPreviewText!
            PreviewText_serializer.write(valueSerializer, valueHolderForPreviewTextTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOptions  = value.options
        if (valueHolderForOptions !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOptionsTmpValue  = valueHolderForOptions!
            TextChangeOptions_serializer.write(valueSerializer, valueHolderForOptionsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): EditableTextChangeValue {
        let valueDeserializer : DeserializerBase = buffer
        const contentTmpResult : string = (valueDeserializer.readString() as string)
        const previewTextTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let previewTextTmpBuf : PreviewText | undefined = undefined
        if ((previewTextTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            previewTextTmpBuf = PreviewText_serializer.read(valueDeserializer)
        }
        const previewTextTmpResult : PreviewText | undefined = previewTextTmpBuf
        const optionsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let optionsTmpBuf : TextChangeOptions | undefined = undefined
        if ((optionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            optionsTmpBuf = TextChangeOptions_serializer.read(valueDeserializer)
        }
        const optionsTmpResult : TextChangeOptions | undefined = optionsTmpBuf
        let value : EditableTextChangeValue = ({content: contentTmpResult, previewText: previewTextTmpResult, options: optionsTmpResult} as EditableTextChangeValue)
        return value
    }
}
export class TextDataDetectorConfig_serializer {
    public static write(buffer: SerializerBase, value: TextDataDetectorConfig): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTypes  = value.types
        if (valueHolderForTypes !== undefined && valueHolderForTypes !== null) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTypesTmpValue  = valueHolderForTypes!
            valueSerializer.writeInt32((valueHolderForTypesTmpValue.length).toInt())
            for (let valueHolderForTypesTmpValueCounterI = 0; valueHolderForTypesTmpValueCounterI < valueHolderForTypesTmpValue.length; valueHolderForTypesTmpValueCounterI++) {
                const valueHolderForTypesTmpValueTmpElement : TextDataDetectorType = valueHolderForTypesTmpValue[valueHolderForTypesTmpValueCounterI]
                valueSerializer.writeInt32(valueHolderForTypesTmpValueTmpElement.valueOf())
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnDetectResultUpdate  = value.onDetectResultUpdate
        if (valueHolderForOnDetectResultUpdate !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnDetectResultUpdateTmpValue  = valueHolderForOnDetectResultUpdate!
            valueSerializer.holdAndWriteCallback(valueHolderForOnDetectResultUpdateTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForColor  = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue  = valueHolderForColor!
            if (valueHolderForColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForColorTmpValueForIdx0  = valueHolderForColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForColorTmpValueForIdx1  = valueHolderForColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForColorTmpValueForIdx1)
            } else if (valueHolderForColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForColorTmpValueForIdx2  = valueHolderForColorTmpValue as string
                valueSerializer.writeString(valueHolderForColorTmpValueForIdx2)
            } else if (valueHolderForColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForColorTmpValueForIdx3  = valueHolderForColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx3)
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
    }
    public static read(buffer: DeserializerBase): TextDataDetectorConfig {
        let valueDeserializer : DeserializerBase = buffer
        const typesTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let typesTmpBuf : Array<TextDataDetectorType> | null | undefined = undefined
        if ((typesTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const typesTmpBuf_Length : int32 = valueDeserializer.readInt32()
            let typesTmpBuf_ : Array<TextDataDetectorType> = new Array<TextDataDetectorType>(typesTmpBuf_Length)
            for (let typesTmpBuf_BufCounterI = 0; typesTmpBuf_BufCounterI < typesTmpBuf_Length; typesTmpBuf_BufCounterI++) {
                typesTmpBuf_[typesTmpBuf_BufCounterI] = TextDataDetectorType.fromValue(valueDeserializer.readInt32())
            }
            typesTmpBuf = typesTmpBuf_
        }
        const typesTmpResult : Array<TextDataDetectorType> | null | undefined = typesTmpBuf
        const onDetectResultUpdateTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDetectResultUpdateTmpBuf : ((value0: string) => void) | undefined = undefined
        if ((onDetectResultUpdateTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDetectResultUpdateTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDetectResultUpdateTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onDetectResultUpdateTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onDetectResultUpdateTmpBuf = (value0: string):void => {
                const onDetectResultUpdateTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDetectResultUpdateTmpBuf_BufArgsSerializer.writeInt32(onDetectResultUpdateTmpBuf_BufResource.resourceId);
                onDetectResultUpdateTmpBuf_BufArgsSerializer.writePointer(onDetectResultUpdateTmpBuf_BufCall);
                onDetectResultUpdateTmpBuf_BufArgsSerializer.writePointer(onDetectResultUpdateTmpBuf_BufCallSync);
                onDetectResultUpdateTmpBuf_BufArgsSerializer.writeString(value0);
                InteropNativeModule._CallCallbackSync(10, 814634522, onDetectResultUpdateTmpBuf_BufArgsSerializer.asBuffer(), onDetectResultUpdateTmpBuf_BufArgsSerializer.length());
                onDetectResultUpdateTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onDetectResultUpdateTmpResult : ((value0: string) => void) | undefined = onDetectResultUpdateTmpBuf
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colorTmpBuf : ResourceColor | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBuf_ : Color | number | string | Resource | undefined
            if (colorTmpBuf_UnionSelector == (0).toChar()) {
                colorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (colorTmpBuf_UnionSelector == (1).toChar()) {
                colorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (colorTmpBuf_UnionSelector == (2).toChar()) {
                colorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (colorTmpBuf_UnionSelector == (3).toChar()) {
                colorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for colorTmpBuf_ has to be chosen through deserialisation.")
            }
            colorTmpBuf = (colorTmpBuf_ as Color | number | string | Resource)
        }
        const colorTmpResult : ResourceColor | undefined = colorTmpBuf
        const decorationTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let decorationTmpBuf : DecorationStyleInterface | undefined = undefined
        if ((decorationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            decorationTmpBuf = DecorationStyleInterface_serializer.read(valueDeserializer)
        }
        const decorationTmpResult : DecorationStyleInterface | undefined = decorationTmpBuf
        let value : TextDataDetectorConfig = ({types: typesTmpResult, onDetectResultUpdate: onDetectResultUpdateTmpResult, color: colorTmpResult, decoration: decorationTmpResult} as TextDataDetectorConfig)
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
    isEditing_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._TextEditControllerEx_isEditing(this.peer!.ptr)
        return retval
    }
    stopEditing_serialize(): void {
        ArkUIGeneratedNativeModule._TextEditControllerEx_stopEditing(this.peer!.ptr)
    }
    setCaretOffset_serialize(offset: number): boolean {
        const retval  = ArkUIGeneratedNativeModule._TextEditControllerEx_setCaretOffset(this.peer!.ptr, offset)
        return retval
    }
    getCaretOffset_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._TextEditControllerEx_getCaretOffset(this.peer!.ptr)
        return retval
    }
    getPreviewText_serialize(): PreviewText {
        const retval  = ArkUIGeneratedNativeModule._TextEditControllerEx_getPreviewText(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : PreviewText = PreviewText_serializer.read(retvalDeserializer)
        return returnResult
    }
}
