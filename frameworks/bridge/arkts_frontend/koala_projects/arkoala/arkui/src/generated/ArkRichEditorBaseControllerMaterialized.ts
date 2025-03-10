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

import { TextEditControllerEx, TextEditControllerExInternal } from "./ArkTextEditControllerExMaterialized"
import { TextBaseController, TextBaseControllerInternal } from "./ArkTextBaseControllerMaterialized"
import { SelectionOptions, MenuPolicy, ShadowOptions, ShadowType } from "./ArkCommonInterfaces"
import { LayoutManager, LayoutManagerInternal } from "./ArkLayoutManagerMaterialized"
import { PreviewText, PositionWithAffinity, LineMetrics, TextRange, TextBox, Affinity } from "./ArkTextCommonInterfaces"
import { RichEditorTextStyle } from "./ArkRichEditorInterfaces"
import { RectWidthStyle, RectHeightStyle } from "./ArkArkuiExternalInterfaces"
import { ResourceColor, Length, ResourceStr } from "./ArkUnitsInterfaces"
import { FontStyle, FontWeight, TextDecorationType, TextDecorationStyle, Color, ColoringStrategy } from "./ArkEnumsInterfaces"
import { DecorationStyleInterface } from "./ArkStyledStringInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class RichEditorBaseControllerInternal {
    public static fromPtr(ptr: KPointer): RichEditorBaseController {
        const obj: RichEditorBaseController = new RichEditorBaseController()
        obj.peer = new Finalizable(ptr, RichEditorBaseController.getFinalizer())
        return obj
    }
}
export class RichEditorBaseController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_richeditorbasecontroller(): KPointer {
        const retval = ArkUIGeneratedNativeModule._RichEditorBaseController_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = RichEditorBaseController.ctor_richeditorbasecontroller()
        this.peer = new Finalizable(ctorPtr, RichEditorBaseController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RichEditorBaseController_getFinalizer()
    }
    public getCaretOffset(): number {
        return this.getCaretOffset_serialize()
    }
    public setCaretOffset(offset: number): boolean {
        const offset_casted = offset as (number)
        return this.setCaretOffset_serialize(offset_casted)
    }
    public closeSelectionMenu(): void {
        this?.closeSelectionMenu_serialize()
        return
    }
    public getTypingStyle(): RichEditorTextStyle {
        return this.getTypingStyle_serialize()
    }
    public setTypingStyle(value: RichEditorTextStyle): void {
        const value_casted = value as (RichEditorTextStyle)
        this?.setTypingStyle_serialize(value_casted)
        return
    }
    public setSelection(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void {
        const selectionStart_casted = selectionStart as (number)
        const selectionEnd_casted = selectionEnd as (number)
        const options_casted = options as (SelectionOptions | undefined)
        this?.setSelection_serialize(selectionStart_casted, selectionEnd_casted, options_casted)
        return
    }
    public isEditing(): boolean {
        return this.isEditing_serialize()
    }
    public stopEditing(): void {
        this?.stopEditing_serialize()
        return
    }
    public getLayoutManager(): LayoutManager {
        return this.getLayoutManager_serialize()
    }
    public getPreviewText(): PreviewText {
        return this.getPreviewText_serialize()
    }
    private getCaretOffset_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._RichEditorBaseController_getCaretOffset(this.peer!.ptr)
        return retval
    }
    private setCaretOffset_serialize(offset: number): boolean {
        const retval = ArkUIGeneratedNativeModule._RichEditorBaseController_setCaretOffset(this.peer!.ptr, offset)
        return retval
    }
    private closeSelectionMenu_serialize(): void {
        ArkUIGeneratedNativeModule._RichEditorBaseController_closeSelectionMenu(this.peer!.ptr)
    }
    private getTypingStyle_serialize(): RichEditorTextStyle {
        const retval = ArkUIGeneratedNativeModule._RichEditorBaseController_getTypingStyle(this.peer!.ptr)
        let retvalDeserializer: Deserializer = new Deserializer(retval.buffer, retval.byteLength)
        const returnResult: RichEditorTextStyle = retvalDeserializer.readRichEditorTextStyle()
        return returnResult
    }
    private setTypingStyle_serialize(value: RichEditorTextStyle): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeRichEditorTextStyle(value)
        ArkUIGeneratedNativeModule._RichEditorBaseController_setTypingStyle(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private setSelection_serialize(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeSelectionOptions(options_value)
        }
        ArkUIGeneratedNativeModule._RichEditorBaseController_setSelection(this.peer!.ptr, selectionStart, selectionEnd, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private isEditing_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._RichEditorBaseController_isEditing(this.peer!.ptr)
        return retval
    }
    private stopEditing_serialize(): void {
        ArkUIGeneratedNativeModule._RichEditorBaseController_stopEditing(this.peer!.ptr)
    }
    private getLayoutManager_serialize(): LayoutManager {
        const retval = ArkUIGeneratedNativeModule._RichEditorBaseController_getLayoutManager(this.peer!.ptr)
        const obj: LayoutManager = LayoutManagerInternal.fromPtr(retval)
        return obj
    }
    private getPreviewText_serialize(): PreviewText {
        const retval = ArkUIGeneratedNativeModule._RichEditorBaseController_getPreviewText(this.peer!.ptr)
        let retvalDeserializer: Deserializer = new Deserializer(retval.buffer, retval.byteLength)
        const returnResult: PreviewText = retvalDeserializer.readPreviewText()
        return returnResult
    }
}
