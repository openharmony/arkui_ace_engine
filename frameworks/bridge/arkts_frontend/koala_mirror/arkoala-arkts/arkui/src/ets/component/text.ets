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

import { StyledString, StyledStringInternal, DecorationStyleInterface_serializer, DecorationStyleInterface } from "./styledString"
import { LayoutManager, LayoutManagerInternal, TextDataDetectorConfig_serializer, EditMenuOptions_serializer, FontSettingOptions_serializer, TextDataDetectorConfig, EditMenuOptions, FontSettingOptions, MenuType } from "./textCommon"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, DeserializerBase, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Resource_serializer, Resource } from "./../generated/resource"
import { LengthMetrics_serializer, LengthMetrics } from "./../generated/arkui.Graphics"
import { ShadowOptions_serializer, ArkCommonMethodPeer, CommonMethod, ShadowOptions, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { Font_serializer, ResourceColor, Length, Font, VoidCallback } from "./units"
import { SelectionMenuOptions_serializer, SelectionMenuOptions, MenuOnAppearCallback, MenuCallback, PreviewMenuOptions } from "./richEditor"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { Color, FontStyle, TextAlign, TextCase, CopyOptions, TextHeightAdaptivePolicy, WordBreak, LineBreakStrategy, EllipsisMode, TextSelectableMode, FontWeight, TextOverflow } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CustomBuilder } from "./builder"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class TextControllerInternal {
    public static fromPtr(ptr: KPointer): TextController {
        return new TextController(ptr)
    }
}
export class TextController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, TextController.getFinalizer())
    }
    constructor() {
        this(TextController.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextController_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextController_getFinalizer()
    }
    public closeSelectionMenu(): void {
        this.closeSelectionMenu_serialize()
        return
    }
    public setStyledString(value: StyledString): void {
        const value_casted = value as (StyledString)
        this.setStyledString_serialize(value_casted)
        return
    }
    public getLayoutManager(): LayoutManager {
        return this.getLayoutManager_serialize()
    }
    private closeSelectionMenu_serialize(): void {
        ArkUIGeneratedNativeModule._TextController_closeSelectionMenu(this.peer!.ptr)
    }
    private setStyledString_serialize(value: StyledString): void {
        ArkUIGeneratedNativeModule._TextController_setStyledString(this.peer!.ptr, toPeerPtr(value))
    }
    private getLayoutManager_serialize(): LayoutManager {
        const retval  = ArkUIGeneratedNativeModule._TextController_getLayoutManager(this.peer!.ptr)
        const obj : LayoutManager = LayoutManagerInternal.fromPtr(retval)
        return obj
    }
}
export class ArkTextPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkTextPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Text_construct(peerId, flags)
        const _peer  = new ArkTextPeer(_peerPtr, peerId, "Text", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setTextOptionsAttribute(content?: string | Resource, value?: TextOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let content_type : int32 = RuntimeType.UNDEFINED
        content_type = runtimeType(content)
        thisSerializer.writeInt8((content_type).toChar())
        if ((content_type) != (RuntimeType.UNDEFINED)) {
            const content_value  = content!
            let content_value_type : int32 = RuntimeType.UNDEFINED
            content_value_type = runtimeType(content_value)
            if (RuntimeType.STRING == content_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const content_value_0  = content_value as string
                thisSerializer.writeString(content_value_0)
            }
            else if (RuntimeType.OBJECT == content_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const content_value_1  = content_value as Resource
                Resource_serializer.write(thisSerializer, content_value_1)
            }
        }
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            TextOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TextInterface_setTextOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontSizeAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_setFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinFontSizeAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_setMinFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxFontSizeAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_setMaxFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinFontScaleAttribute(value: number | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_setMinFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxFontScaleAttribute(value: number | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_setMaxFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontStyleAttribute(value: FontStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as FontStyle)
            thisSerializer.writeInt32(TypeChecker.FontStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAttribute_setFontStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLineSpacingAttribute(value: LengthMetrics | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            LengthMetrics_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setLineSpacing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextAlignAttribute(value: TextAlign | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as TextAlign)
            thisSerializer.writeInt32(TypeChecker.TextAlign_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAttribute_setTextAlign(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLineHeightAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_setLineHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextOverflowAttribute(value: TextOverflowOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            TextOverflowOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setTextOverflow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontFamilyAttribute(value: string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_setFontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxLinesAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setMaxLines(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDecorationAttribute(value: DecorationStyleInterface | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            DecorationStyleInterface_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setDecoration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLetterSpacingAttribute(value: number | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_setLetterSpacing(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextCaseAttribute(value: TextCase | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as TextCase)
            thisSerializer.writeInt32(TypeChecker.TextCase_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAttribute_setTextCase(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBaselineOffsetAttribute(value: number | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_setBaselineOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCopyOptionAttribute(value: CopyOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as CopyOptions)
            thisSerializer.writeInt32(TypeChecker.CopyOptions_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAttribute_setCopyOption(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDraggableAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setDraggable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextShadowAttribute(value: ShadowOptions | Array<ShadowOptions> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isShadowOptions(value_value, false, false, false, false, false, false)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as ShadowOptions
                ShadowOptions_serializer.write(thisSerializer, value_value_0)
            }
            else if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isArray_ShadowOptions(value_value))) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as Array<ShadowOptions>
                thisSerializer.writeInt32((value_value_1.length).toInt())
                for (let value_value_1_counter_i = 0; value_value_1_counter_i < value_value_1.length; value_value_1_counter_i++) {
                    const value_value_1_element : ShadowOptions = value_value_1[value_value_1_counter_i]
                    ShadowOptions_serializer.write(thisSerializer, value_value_1_element)
                }
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_setTextShadow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHeightAdaptivePolicyAttribute(value: TextHeightAdaptivePolicy | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as TextHeightAdaptivePolicy)
            thisSerializer.writeInt32(TypeChecker.TextHeightAdaptivePolicy_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAttribute_setHeightAdaptivePolicy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextIndentAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_setTextIndent(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setWordBreakAttribute(value: WordBreak | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as WordBreak)
            thisSerializer.writeInt32(TypeChecker.WordBreak_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAttribute_setWordBreak(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLineBreakStrategyAttribute(value: LineBreakStrategy | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as LineBreakStrategy)
            thisSerializer.writeInt32(TypeChecker.LineBreakStrategy_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAttribute_setLineBreakStrategy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnCopyAttribute(value: ((value: string) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setOnCopy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCaretColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_setCaretColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectedBackgroundColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._TextAttribute_setSelectedBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEllipsisModeAttribute(value: EllipsisMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as EllipsisMode)
            thisSerializer.writeInt32(TypeChecker.EllipsisMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAttribute_setEllipsisMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableDataDetectorAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setEnableDataDetector(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDataDetectorConfigAttribute(value: TextDataDetectorConfig | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            TextDataDetectorConfig_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setDataDetectorConfig(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnTextSelectionChangeAttribute(value: ((selectionStart: number,selectionEnd: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setOnTextSelectionChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontFeatureAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setFontFeature(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMarqueeOptionsAttribute(value: TextMarqueeOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            TextMarqueeOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setMarqueeOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnMarqueeStateChangeAttribute(value: ((value0: MarqueeState) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setOnMarqueeStateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPrivacySensitiveAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setPrivacySensitive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextSelectableAttribute(value: TextSelectableMode | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as TextSelectableMode)
            thisSerializer.writeInt32(TypeChecker.TextSelectableMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._TextAttribute_setTextSelectable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEditMenuOptionsAttribute(value: EditMenuOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            EditMenuOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setEditMenuOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHalfLeadingAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setHalfLeading(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableHapticFeedbackAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setEnableHapticFeedback(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontAttribute(fontValue: Font | undefined, options?: FontSettingOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let fontValue_type : int32 = RuntimeType.UNDEFINED
        fontValue_type = runtimeType(fontValue)
        thisSerializer.writeInt8((fontValue_type).toChar())
        if ((fontValue_type) != (RuntimeType.UNDEFINED)) {
            const fontValue_value  = fontValue!
            Font_serializer.write(thisSerializer, fontValue_value)
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            FontSettingOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setFont(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontWeightAttribute(weight: number | FontWeight | string | undefined, options?: FontSettingOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let weight_type : int32 = RuntimeType.UNDEFINED
        weight_type = runtimeType(weight)
        thisSerializer.writeInt8((weight_type).toChar())
        if ((weight_type) != (RuntimeType.UNDEFINED)) {
            const weight_value  = weight!
            let weight_value_type : int32 = RuntimeType.UNDEFINED
            weight_value_type = runtimeType(weight_value)
            if (RuntimeType.NUMBER == weight_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const weight_value_0  = weight_value as number
                thisSerializer.writeNumber(weight_value_0)
            }
            else if (TypeChecker.isFontWeight(weight_value)) {
                thisSerializer.writeInt8((1).toChar())
                const weight_value_1  = weight_value as FontWeight
                thisSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(weight_value_1))
            }
            else if (RuntimeType.STRING == weight_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const weight_value_2  = weight_value as string
                thisSerializer.writeString(weight_value_2)
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            FontSettingOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setFontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSelectionAttribute(selectionStart: number | undefined, selectionEnd: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let selectionStart_type : int32 = RuntimeType.UNDEFINED
        selectionStart_type = runtimeType(selectionStart)
        thisSerializer.writeInt8((selectionStart_type).toChar())
        if ((selectionStart_type) != (RuntimeType.UNDEFINED)) {
            const selectionStart_value  = selectionStart!
            thisSerializer.writeNumber(selectionStart_value)
        }
        let selectionEnd_type : int32 = RuntimeType.UNDEFINED
        selectionEnd_type = runtimeType(selectionEnd)
        thisSerializer.writeInt8((selectionEnd_type).toChar())
        if ((selectionEnd_type) != (RuntimeType.UNDEFINED)) {
            const selectionEnd_value  = selectionEnd!
            thisSerializer.writeNumber(selectionEnd_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setSelection(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBindSelectionMenuAttribute(spanType: TextSpanType | undefined, content: CustomBuilder | undefined, responseType: TextResponseType | undefined, options?: SelectionMenuOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let spanType_type : int32 = RuntimeType.UNDEFINED
        spanType_type = runtimeType(spanType)
        thisSerializer.writeInt8((spanType_type).toChar())
        if ((spanType_type) != (RuntimeType.UNDEFINED)) {
            const spanType_value  = (spanType as TextSpanType)
            thisSerializer.writeInt32(TypeChecker.TextSpanType_ToNumeric(spanType_value))
        }
        let content_type : int32 = RuntimeType.UNDEFINED
        content_type = runtimeType(content)
        thisSerializer.writeInt8((content_type).toChar())
        if ((content_type) != (RuntimeType.UNDEFINED)) {
            const content_value  = content!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(content_value))
        }
        let responseType_type : int32 = RuntimeType.UNDEFINED
        responseType_type = runtimeType(responseType)
        thisSerializer.writeInt8((responseType_type).toChar())
        if ((responseType_type) != (RuntimeType.UNDEFINED)) {
            const responseType_value  = (responseType as TextResponseType)
            thisSerializer.writeInt32(TypeChecker.TextResponseType_ToNumeric(responseType_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            SelectionMenuOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._TextAttribute_setBindSelectionMenu(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface TextOverflowOptions {
    overflow: TextOverflow;
}
export interface TextAttribute extends CommonMethod {
    fontColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method fontColor")
    }
    fontSize(value: number | string | Resource | undefined): this {
        throw new Error("Unimplemented method fontSize")
    }
    minFontSize(value: number | string | Resource | undefined): this {
        throw new Error("Unimplemented method minFontSize")
    }
    maxFontSize(value: number | string | Resource | undefined): this {
        throw new Error("Unimplemented method maxFontSize")
    }
    minFontScale(value: number | Resource | undefined): this {
        throw new Error("Unimplemented method minFontScale")
    }
    maxFontScale(value: number | Resource | undefined): this {
        throw new Error("Unimplemented method maxFontScale")
    }
    fontStyle(value: FontStyle | undefined): this {
        throw new Error("Unimplemented method fontStyle")
    }
    lineSpacing(value: LengthMetrics | undefined): this {
        throw new Error("Unimplemented method lineSpacing")
    }
    textAlign(value: TextAlign | undefined): this {
        throw new Error("Unimplemented method textAlign")
    }
    lineHeight(value: number | string | Resource | undefined): this {
        throw new Error("Unimplemented method lineHeight")
    }
    textOverflow(value: TextOverflowOptions | undefined): this {
        throw new Error("Unimplemented method textOverflow")
    }
    fontFamily(value: string | Resource | undefined): this {
        throw new Error("Unimplemented method fontFamily")
    }
    maxLines(value: number | undefined): this {
        throw new Error("Unimplemented method maxLines")
    }
    decoration(value: DecorationStyleInterface | undefined): this {
        throw new Error("Unimplemented method decoration")
    }
    letterSpacing(value: number | string | undefined): this {
        throw new Error("Unimplemented method letterSpacing")
    }
    textCase(value: TextCase | undefined): this {
        throw new Error("Unimplemented method textCase")
    }
    baselineOffset(value: number | string | undefined): this {
        throw new Error("Unimplemented method baselineOffset")
    }
    copyOption(value: CopyOptions | undefined): this {
        throw new Error("Unimplemented method copyOption")
    }
    draggable(value: boolean | undefined): this
    textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        throw new Error("Unimplemented method textShadow")
    }
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        throw new Error("Unimplemented method heightAdaptivePolicy")
    }
    textIndent(value: Length | undefined): this {
        throw new Error("Unimplemented method textIndent")
    }
    wordBreak(value: WordBreak | undefined): this {
        throw new Error("Unimplemented method wordBreak")
    }
    lineBreakStrategy(value: LineBreakStrategy | undefined): this {
        throw new Error("Unimplemented method lineBreakStrategy")
    }
    onCopy(value: ((value: string) => void) | undefined): this {
        throw new Error("Unimplemented method onCopy")
    }
    caretColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method caretColor")
    }
    selectedBackgroundColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method selectedBackgroundColor")
    }
    ellipsisMode(value: EllipsisMode | undefined): this {
        throw new Error("Unimplemented method ellipsisMode")
    }
    enableDataDetector(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableDataDetector")
    }
    dataDetectorConfig(value: TextDataDetectorConfig | undefined): this {
        throw new Error("Unimplemented method dataDetectorConfig")
    }
    onTextSelectionChange(value: ((selectionStart: number,selectionEnd: number) => void) | undefined): this {
        throw new Error("Unimplemented method onTextSelectionChange")
    }
    fontFeature(value: string | undefined): this {
        throw new Error("Unimplemented method fontFeature")
    }
    marqueeOptions(value: TextMarqueeOptions | undefined): this {
        throw new Error("Unimplemented method marqueeOptions")
    }
    onMarqueeStateChange(value: ((value0: MarqueeState) => void) | undefined): this {
        throw new Error("Unimplemented method onMarqueeStateChange")
    }
    privacySensitive(value: boolean | undefined): this {
        throw new Error("Unimplemented method privacySensitive")
    }
    textSelectable(value: TextSelectableMode | undefined): this {
        throw new Error("Unimplemented method textSelectable")
    }
    editMenuOptions(value: EditMenuOptions | undefined): this {
        throw new Error("Unimplemented method editMenuOptions")
    }
    halfLeading(value: boolean | undefined): this {
        throw new Error("Unimplemented method halfLeading")
    }
    enableHapticFeedback(value: boolean | undefined): this {
        throw new Error("Unimplemented method enableHapticFeedback")
    }
    font(fontValue: Font | undefined, options?: FontSettingOptions): this {
        throw new Error("Unimplemented method font")
    }
    fontWeight(weight: number | FontWeight | string | undefined, options?: FontSettingOptions): this {
        throw new Error("Unimplemented method fontWeight")
    }
    selection(selectionStart: number | undefined, selectionEnd: number | undefined): this {
        throw new Error("Unimplemented method selection")
    }
    bindSelectionMenu(spanType: TextSpanType | undefined, content: CustomBuilder | undefined, responseType: TextResponseType | undefined, options?: SelectionMenuOptions): this {
        throw new Error("Unimplemented method bindSelectionMenu")
    }
    attributeModifier(value: AttributeModifier<TextAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkTextStyle extends ArkCommonMethodStyle implements TextAttribute {
    fontColor_value?: ResourceColor | undefined
    fontSize_value?: number | string | Resource | undefined
    minFontSize_value?: number | string | Resource | undefined
    maxFontSize_value?: number | string | Resource | undefined
    minFontScale_value?: number | Resource | undefined
    maxFontScale_value?: number | Resource | undefined
    fontStyle_value?: FontStyle | undefined
    lineSpacing_value?: LengthMetrics | undefined
    textAlign_value?: TextAlign | undefined
    lineHeight_value?: number | string | Resource | undefined
    textOverflow_value?: TextOverflowOptions | undefined
    fontFamily_value?: string | Resource | undefined
    maxLines_value?: number | undefined
    decoration_value?: DecorationStyleInterface | undefined
    letterSpacing_value?: number | string | undefined
    textCase_value?: TextCase | undefined
    baselineOffset_value?: number | string | undefined
    copyOption_value?: CopyOptions | undefined
    draggable_value?: boolean | undefined
    textShadow_value?: ShadowOptions | Array<ShadowOptions> | undefined
    heightAdaptivePolicy_value?: TextHeightAdaptivePolicy | undefined
    textIndent_value?: Length | undefined
    wordBreak_value?: WordBreak | undefined
    lineBreakStrategy_value?: LineBreakStrategy | undefined
    onCopy_value?: ((value: string) => void) | undefined
    caretColor_value?: ResourceColor | undefined
    selectedBackgroundColor_value?: ResourceColor | undefined
    ellipsisMode_value?: EllipsisMode | undefined
    enableDataDetector_value?: boolean | undefined
    dataDetectorConfig_value?: TextDataDetectorConfig | undefined
    onTextSelectionChange_value?: ((selectionStart: number,selectionEnd: number) => void) | undefined
    fontFeature_value?: string | undefined
    marqueeOptions_value?: TextMarqueeOptions | undefined
    onMarqueeStateChange_value?: ((value0: MarqueeState) => void) | undefined
    privacySensitive_value?: boolean | undefined
    textSelectable_value?: TextSelectableMode | undefined
    editMenuOptions_value?: EditMenuOptions | undefined
    halfLeading_value?: boolean | undefined
    enableHapticFeedback_value?: boolean | undefined
    attributeModifier_value?: AttributeModifier<TextAttribute> | AttributeModifier<CommonMethod> | undefined
    public fontColor(value: ResourceColor | undefined): this {
        return this
    }
    public fontSize(value: number | string | Resource | undefined): this {
        return this
    }
    public minFontSize(value: number | string | Resource | undefined): this {
        return this
    }
    public maxFontSize(value: number | string | Resource | undefined): this {
        return this
    }
    public minFontScale(value: number | Resource | undefined): this {
        return this
    }
    public maxFontScale(value: number | Resource | undefined): this {
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        return this
    }
    public lineSpacing(value: LengthMetrics | undefined): this {
        return this
    }
    public textAlign(value: TextAlign | undefined): this {
        return this
    }
    public lineHeight(value: number | string | Resource | undefined): this {
        return this
    }
    public textOverflow(value: TextOverflowOptions | undefined): this {
        return this
    }
    public fontFamily(value: string | Resource | undefined): this {
        return this
    }
    public maxLines(value: number | undefined): this {
        return this
    }
    public decoration(value: DecorationStyleInterface | undefined): this {
        return this
    }
    public letterSpacing(value: number | string | undefined): this {
        return this
    }
    public textCase(value: TextCase | undefined): this {
        return this
    }
    public baselineOffset(value: number | string | undefined): this {
        return this
    }
    public copyOption(value: CopyOptions | undefined): this {
        return this
    }
    public draggable(value: boolean | undefined): this {
        return this
    }
    public textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        return this
    }
    public heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        return this
    }
    public textIndent(value: Length | undefined): this {
        return this
    }
    public wordBreak(value: WordBreak | undefined): this {
        return this
    }
    public lineBreakStrategy(value: LineBreakStrategy | undefined): this {
        return this
    }
    public onCopy(value: ((value: string) => void) | undefined): this {
        return this
    }
    public caretColor(value: ResourceColor | undefined): this {
        return this
    }
    public selectedBackgroundColor(value: ResourceColor | undefined): this {
        return this
    }
    public ellipsisMode(value: EllipsisMode | undefined): this {
        return this
    }
    public enableDataDetector(value: boolean | undefined): this {
        return this
    }
    public dataDetectorConfig(value: TextDataDetectorConfig | undefined): this {
        return this
    }
    public onTextSelectionChange(value: ((selectionStart: number,selectionEnd: number) => void) | undefined): this {
        return this
    }
    public fontFeature(value: string | undefined): this {
        return this
    }
    public marqueeOptions(value: TextMarqueeOptions | undefined): this {
        return this
    }
    public onMarqueeStateChange(value: ((value0: MarqueeState) => void) | undefined): this {
        return this
    }
    public privacySensitive(value: boolean | undefined): this {
        return this
    }
    public textSelectable(value: TextSelectableMode | undefined): this {
        return this
    }
    public editMenuOptions(value: EditMenuOptions | undefined): this {
        return this
    }
    public halfLeading(value: boolean | undefined): this {
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        return this
    }
    public font(fontValue: Font | undefined, options?: FontSettingOptions): this {
        return this
    }
    public fontWeight(weight: number | FontWeight | string | undefined, options?: FontSettingOptions): this {
        return this
    }
    public selection(selectionStart: number | undefined, selectionEnd: number | undefined): this {
        return this
    }
    public bindSelectionMenu(spanType: TextSpanType | undefined, content: CustomBuilder | undefined, responseType: TextResponseType | undefined, options?: SelectionMenuOptions): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<TextAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: TextAttribute): void {
        super.apply(target)
        if (this.fontColor_value !== undefined)
            target.fontColor(this.fontColor_value!)
        if (this.fontSize_value !== undefined)
            target.fontSize(this.fontSize_value!)
        if (this.minFontSize_value !== undefined)
            target.minFontSize(this.minFontSize_value!)
        if (this.maxFontSize_value !== undefined)
            target.maxFontSize(this.maxFontSize_value!)
        if (this.minFontScale_value !== undefined)
            target.minFontScale(this.minFontScale_value!)
        if (this.maxFontScale_value !== undefined)
            target.maxFontScale(this.maxFontScale_value!)
        if (this.fontStyle_value !== undefined)
            target.fontStyle(this.fontStyle_value!)
        if (this.lineSpacing_value !== undefined)
            target.lineSpacing(this.lineSpacing_value!)
        if (this.textAlign_value !== undefined)
            target.textAlign(this.textAlign_value!)
        if (this.lineHeight_value !== undefined)
            target.lineHeight(this.lineHeight_value!)
        if (this.textOverflow_value !== undefined)
            target.textOverflow(this.textOverflow_value!)
        if (this.fontFamily_value !== undefined)
            target.fontFamily(this.fontFamily_value!)
        if (this.maxLines_value !== undefined)
            target.maxLines(this.maxLines_value!)
        if (this.decoration_value !== undefined)
            target.decoration(this.decoration_value!)
        if (this.letterSpacing_value !== undefined)
            target.letterSpacing(this.letterSpacing_value!)
        if (this.textCase_value !== undefined)
            target.textCase(this.textCase_value!)
        if (this.baselineOffset_value !== undefined)
            target.baselineOffset(this.baselineOffset_value!)
        if (this.copyOption_value !== undefined)
            target.copyOption(this.copyOption_value!)
        if (this.draggable_value !== undefined)
            target.draggable(this.draggable_value!)
        if (this.textShadow_value !== undefined)
            target.textShadow(this.textShadow_value!)
        if (this.heightAdaptivePolicy_value !== undefined)
            target.heightAdaptivePolicy(this.heightAdaptivePolicy_value!)
        if (this.textIndent_value !== undefined)
            target.textIndent(this.textIndent_value!)
        if (this.wordBreak_value !== undefined)
            target.wordBreak(this.wordBreak_value!)
        if (this.lineBreakStrategy_value !== undefined)
            target.lineBreakStrategy(this.lineBreakStrategy_value!)
        if (this.onCopy_value !== undefined)
            target.onCopy(this.onCopy_value!)
        if (this.caretColor_value !== undefined)
            target.caretColor(this.caretColor_value!)
        if (this.selectedBackgroundColor_value !== undefined)
            target.selectedBackgroundColor(this.selectedBackgroundColor_value!)
        if (this.ellipsisMode_value !== undefined)
            target.ellipsisMode(this.ellipsisMode_value!)
        if (this.enableDataDetector_value !== undefined)
            target.enableDataDetector(this.enableDataDetector_value!)
        if (this.dataDetectorConfig_value !== undefined)
            target.dataDetectorConfig(this.dataDetectorConfig_value!)
        if (this.onTextSelectionChange_value !== undefined)
            target.onTextSelectionChange(this.onTextSelectionChange_value!)
        if (this.fontFeature_value !== undefined)
            target.fontFeature(this.fontFeature_value!)
        if (this.marqueeOptions_value !== undefined)
            target.marqueeOptions(this.marqueeOptions_value!)
        if (this.onMarqueeStateChange_value !== undefined)
            target.onMarqueeStateChange(this.onMarqueeStateChange_value!)
        if (this.privacySensitive_value !== undefined)
            target.privacySensitive(this.privacySensitive_value!)
        if (this.textSelectable_value !== undefined)
            target.textSelectable(this.textSelectable_value!)
        if (this.editMenuOptions_value !== undefined)
            target.editMenuOptions(this.editMenuOptions_value!)
        if (this.halfLeading_value !== undefined)
            target.halfLeading(this.halfLeading_value!)
        if (this.enableHapticFeedback_value !== undefined)
            target.enableHapticFeedback(this.enableHapticFeedback_value!)
    }
}
export enum TextSpanType {
    TEXT = 0,
    IMAGE = 1,
    MIXED = 2,
    DEFAULT = 3
}
export enum TextResponseType {
    RIGHT_CLICK = 0,
    LONG_PRESS = 1,
    SELECT = 2,
    DEFAULT = 3
}
export enum MarqueeState {
    START = 0,
    BOUNCE = 1,
    FINISH = 2
}
export enum MarqueeStartPolicy {
    DEFAULT = 0,
    ON_FOCUS = 1
}
export interface TextOptions {
    controller: TextController;
}
export interface TextMarqueeOptions {
    start: boolean;
    step?: number;
    loop?: number;
    fromStart?: boolean;
    delay?: number;
    fadeout?: boolean;
    marqueeStartPolicy?: MarqueeStartPolicy;
}

export class ArkTextComponent extends ArkCommonMethodComponent implements TextAttribute {
    getPeer(): ArkTextPeer {
        return (this.peer as ArkTextPeer)
    }
    public setTextOptions(content?: string | Resource, value?: TextOptions): this {
        if (this.checkPriority("setTextOptions")) {
            const content_casted = content as (string | Resource | undefined)
            const value_casted = value as (TextOptions | undefined)
            this.getPeer()?.setTextOptionsAttribute(content_casted, value_casted)
            return this
        }
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public fontSize(value: number | string | Resource | undefined): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.setFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public minFontSize(value: number | string | Resource | undefined): this {
        if (this.checkPriority("minFontSize")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.setMinFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public maxFontSize(value: number | string | Resource | undefined): this {
        if (this.checkPriority("maxFontSize")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.setMaxFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public minFontScale(value: number | Resource | undefined): this {
        if (this.checkPriority("minFontScale")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.setMinFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public maxFontScale(value: number | Resource | undefined): this {
        if (this.checkPriority("maxFontScale")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.setMaxFontScaleAttribute(value_casted)
            return this
        }
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        if (this.checkPriority("fontStyle")) {
            const value_casted = value as (FontStyle | undefined)
            this.getPeer()?.setFontStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public lineSpacing(value: LengthMetrics | undefined): this {
        if (this.checkPriority("lineSpacing")) {
            const value_casted = value as (LengthMetrics | undefined)
            this.getPeer()?.setLineSpacingAttribute(value_casted)
            return this
        }
        return this
    }
    public textAlign(value: TextAlign | undefined): this {
        if (this.checkPriority("textAlign")) {
            const value_casted = value as (TextAlign | undefined)
            this.getPeer()?.setTextAlignAttribute(value_casted)
            return this
        }
        return this
    }
    public lineHeight(value: number | string | Resource | undefined): this {
        if (this.checkPriority("lineHeight")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.setLineHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public textOverflow(value: TextOverflowOptions | undefined): this {
        if (this.checkPriority("textOverflow")) {
            const value_casted = value as (TextOverflowOptions | undefined)
            this.getPeer()?.setTextOverflowAttribute(value_casted)
            return this
        }
        return this
    }
    public fontFamily(value: string | Resource | undefined): this {
        if (this.checkPriority("fontFamily")) {
            const value_casted = value as (string | Resource | undefined)
            this.getPeer()?.setFontFamilyAttribute(value_casted)
            return this
        }
        return this
    }
    public maxLines(value: number | undefined): this {
        if (this.checkPriority("maxLines")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setMaxLinesAttribute(value_casted)
            return this
        }
        return this
    }
    public decoration(value: DecorationStyleInterface | undefined): this {
        if (this.checkPriority("decoration")) {
            const value_casted = value as (DecorationStyleInterface | undefined)
            this.getPeer()?.setDecorationAttribute(value_casted)
            return this
        }
        return this
    }
    public letterSpacing(value: number | string | undefined): this {
        if (this.checkPriority("letterSpacing")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.setLetterSpacingAttribute(value_casted)
            return this
        }
        return this
    }
    public textCase(value: TextCase | undefined): this {
        if (this.checkPriority("textCase")) {
            const value_casted = value as (TextCase | undefined)
            this.getPeer()?.setTextCaseAttribute(value_casted)
            return this
        }
        return this
    }
    public baselineOffset(value: number | string | undefined): this {
        if (this.checkPriority("baselineOffset")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.setBaselineOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public copyOption(value: CopyOptions | undefined): this {
        if (this.checkPriority("copyOption")) {
            const value_casted = value as (CopyOptions | undefined)
            this.getPeer()?.setCopyOptionAttribute(value_casted)
            return this
        }
        return this
    }
    public draggable(value: boolean | undefined): this {
        if (this.checkPriority("draggable")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setDraggableAttribute(value_casted)
            return this
        }
        return this
    }
    public textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        if (this.checkPriority("textShadow")) {
            const value_casted = value as (ShadowOptions | Array<ShadowOptions> | undefined)
            this.getPeer()?.setTextShadowAttribute(value_casted)
            return this
        }
        return this
    }
    public heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        if (this.checkPriority("heightAdaptivePolicy")) {
            const value_casted = value as (TextHeightAdaptivePolicy | undefined)
            this.getPeer()?.setHeightAdaptivePolicyAttribute(value_casted)
            return this
        }
        return this
    }
    public textIndent(value: Length | undefined): this {
        if (this.checkPriority("textIndent")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setTextIndentAttribute(value_casted)
            return this
        }
        return this
    }
    public wordBreak(value: WordBreak | undefined): this {
        if (this.checkPriority("wordBreak")) {
            const value_casted = value as (WordBreak | undefined)
            this.getPeer()?.setWordBreakAttribute(value_casted)
            return this
        }
        return this
    }
    public lineBreakStrategy(value: LineBreakStrategy | undefined): this {
        if (this.checkPriority("lineBreakStrategy")) {
            const value_casted = value as (LineBreakStrategy | undefined)
            this.getPeer()?.setLineBreakStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    public onCopy(value: ((value: string) => void) | undefined): this {
        if (this.checkPriority("onCopy")) {
            const value_casted = value as (((value: string) => void) | undefined)
            this.getPeer()?.setOnCopyAttribute(value_casted)
            return this
        }
        return this
    }
    public caretColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("caretColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setCaretColorAttribute(value_casted)
            return this
        }
        return this
    }
    public selectedBackgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("selectedBackgroundColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setSelectedBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    public ellipsisMode(value: EllipsisMode | undefined): this {
        if (this.checkPriority("ellipsisMode")) {
            const value_casted = value as (EllipsisMode | undefined)
            this.getPeer()?.setEllipsisModeAttribute(value_casted)
            return this
        }
        return this
    }
    public enableDataDetector(value: boolean | undefined): this {
        if (this.checkPriority("enableDataDetector")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableDataDetectorAttribute(value_casted)
            return this
        }
        return this
    }
    public dataDetectorConfig(value: TextDataDetectorConfig | undefined): this {
        if (this.checkPriority("dataDetectorConfig")) {
            const value_casted = value as (TextDataDetectorConfig | undefined)
            this.getPeer()?.setDataDetectorConfigAttribute(value_casted)
            return this
        }
        return this
    }
    public onTextSelectionChange(value: ((selectionStart: number,selectionEnd: number) => void) | undefined): this {
        if (this.checkPriority("onTextSelectionChange")) {
            const value_casted = value as (((selectionStart: number,selectionEnd: number) => void) | undefined)
            this.getPeer()?.setOnTextSelectionChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public fontFeature(value: string | undefined): this {
        if (this.checkPriority("fontFeature")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setFontFeatureAttribute(value_casted)
            return this
        }
        return this
    }
    public marqueeOptions(value: TextMarqueeOptions | undefined): this {
        if (this.checkPriority("marqueeOptions")) {
            const value_casted = value as (TextMarqueeOptions | undefined)
            this.getPeer()?.setMarqueeOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public onMarqueeStateChange(value: ((value0: MarqueeState) => void) | undefined): this {
        if (this.checkPriority("onMarqueeStateChange")) {
            const value_casted = value as (((value0: MarqueeState) => void) | undefined)
            this.getPeer()?.setOnMarqueeStateChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public privacySensitive(value: boolean | undefined): this {
        if (this.checkPriority("privacySensitive")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setPrivacySensitiveAttribute(value_casted)
            return this
        }
        return this
    }
    public textSelectable(value: TextSelectableMode | undefined): this {
        if (this.checkPriority("textSelectable")) {
            const value_casted = value as (TextSelectableMode | undefined)
            this.getPeer()?.setTextSelectableAttribute(value_casted)
            return this
        }
        return this
    }
    public editMenuOptions(value: EditMenuOptions | undefined): this {
        if (this.checkPriority("editMenuOptions")) {
            const value_casted = value as (EditMenuOptions | undefined)
            this.getPeer()?.setEditMenuOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public halfLeading(value: boolean | undefined): this {
        if (this.checkPriority("halfLeading")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setHalfLeadingAttribute(value_casted)
            return this
        }
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        if (this.checkPriority("enableHapticFeedback")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableHapticFeedbackAttribute(value_casted)
            return this
        }
        return this
    }
    public font(fontValue: Font | undefined, options?: FontSettingOptions): this {
        if (this.checkPriority("font")) {
            const fontValue_casted = fontValue as (Font | undefined)
            const options_casted = options as (FontSettingOptions | undefined)
            this.getPeer()?.setFontAttribute(fontValue_casted, options_casted)
            return this
        }
        return this
    }
    public fontWeight(weight: number | FontWeight | string | undefined, options?: FontSettingOptions): this {
        if (this.checkPriority("fontWeight")) {
            const weight_casted = weight as (number | FontWeight | string | undefined)
            const options_casted = options as (FontSettingOptions | undefined)
            this.getPeer()?.setFontWeightAttribute(weight_casted, options_casted)
            return this
        }
        return this
    }
    public selection(selectionStart: number | undefined, selectionEnd: number | undefined): this {
        if (this.checkPriority("selection")) {
            const selectionStart_casted = selectionStart as (number | undefined)
            const selectionEnd_casted = selectionEnd as (number | undefined)
            this.getPeer()?.setSelectionAttribute(selectionStart_casted, selectionEnd_casted)
            return this
        }
        return this
    }
    public bindSelectionMenu(spanType: TextSpanType | undefined, content: CustomBuilder | undefined, responseType: TextResponseType | undefined, options?: SelectionMenuOptions): this {
        if (this.checkPriority("bindSelectionMenu")) {
            const spanType_casted = spanType as (TextSpanType | undefined)
            const content_casted = content as (CustomBuilder | undefined)
            const responseType_casted = responseType as (TextResponseType | undefined)
            const options_casted = options as (SelectionMenuOptions | undefined)
            this.getPeer()?.setBindSelectionMenuAttribute(spanType_casted, content_casted, responseType_casted, options_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<TextAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withTextStyle(receiver: TextAttribute, modifier: AttributeModifier<TextAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkTextStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Text")
// export function Text(
//     content?: string | Resource, value?: TextOptions,
//     @memo
//     content_?: () => void,
// ): TextAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Text(
    @memo
    style: ((attributes: TextAttribute) => void) | undefined,
    content?: string | Resource, value?: TextOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkTextComponent>((): ArkTextComponent => {
        return new ArkTextComponent()
    })
    NodeAttach<ArkTextPeer>((): ArkTextPeer => ArkTextPeer.create(receiver), (_: ArkTextPeer): void => {
        receiver.setTextOptions(content,value)
        style?.(receiver)
        withTextStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkTextSet extends ArkCommonMethodSet implements TextAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _fontColor_flag?: boolean
    _fontColor0_value?: ResourceColor | undefined
    _fontSize_flag?: boolean
    _fontSize0_value?: number | string | Resource | undefined
    _minFontSize_flag?: boolean
    _minFontSize0_value?: number | string | Resource | undefined
    _maxFontSize_flag?: boolean
    _maxFontSize0_value?: number | string | Resource | undefined
    _minFontScale_flag?: boolean
    _minFontScale0_value?: number | Resource | undefined
    _maxFontScale_flag?: boolean
    _maxFontScale0_value?: number | Resource | undefined
    _fontStyle_flag?: boolean
    _fontStyle0_value?: FontStyle | undefined
    _lineSpacing_flag?: boolean
    _lineSpacing0_value?: LengthMetrics | undefined
    _textAlign_flag?: boolean
    _textAlign0_value?: TextAlign | undefined
    _lineHeight_flag?: boolean
    _lineHeight0_value?: number | string | Resource | undefined
    _textOverflow_flag?: boolean
    _textOverflow0_value?: TextOverflowOptions | undefined
    _fontFamily_flag?: boolean
    _fontFamily0_value?: string | Resource | undefined
    _maxLines_flag?: boolean
    _maxLines0_value?: number | undefined
    _decoration_flag?: boolean
    _decoration0_value?: DecorationStyleInterface | undefined
    _letterSpacing_flag?: boolean
    _letterSpacing0_value?: number | string | undefined
    _textCase_flag?: boolean
    _textCase0_value?: TextCase | undefined
    _baselineOffset_flag?: boolean
    _baselineOffset0_value?: number | string | undefined
    _copyOption_flag?: boolean
    _copyOption0_value?: CopyOptions | undefined
    _draggable_flag?: boolean
    _draggable0_value?: boolean | undefined
    _textShadow_flag?: boolean
    _textShadow0_value?: ShadowOptions | Array<ShadowOptions> | undefined
    _heightAdaptivePolicy_flag?: boolean
    _heightAdaptivePolicy0_value?: TextHeightAdaptivePolicy | undefined
    _textIndent_flag?: boolean
    _textIndent0_value?: Length | undefined
    _wordBreak_flag?: boolean
    _wordBreak0_value?: WordBreak | undefined
    _lineBreakStrategy_flag?: boolean
    _lineBreakStrategy0_value?: LineBreakStrategy | undefined
    _onCopy_flag?: boolean
    _onCopy0_value?: ((value: string) => void) | undefined
    _caretColor_flag?: boolean
    _caretColor0_value?: ResourceColor | undefined
    _selectedBackgroundColor_flag?: boolean
    _selectedBackgroundColor0_value?: ResourceColor | undefined
    _ellipsisMode_flag?: boolean
    _ellipsisMode0_value?: EllipsisMode | undefined
    _enableDataDetector_flag?: boolean
    _enableDataDetector0_value?: boolean | undefined
    _dataDetectorConfig_flag?: boolean
    _dataDetectorConfig0_value?: TextDataDetectorConfig | undefined
    _onTextSelectionChange_flag?: boolean
    _onTextSelectionChange0_value?: ((selectionStart: number,selectionEnd: number) => void) | undefined
    _fontFeature_flag?: boolean
    _fontFeature0_value?: string | undefined
    _marqueeOptions_flag?: boolean
    _marqueeOptions0_value?: TextMarqueeOptions | undefined
    _onMarqueeStateChange_flag?: boolean
    _onMarqueeStateChange0_value?: ((value0: MarqueeState) => void) | undefined
    _privacySensitive_flag?: boolean
    _privacySensitive0_value?: boolean | undefined
    _textSelectable_flag?: boolean
    _textSelectable0_value?: TextSelectableMode | undefined
    _editMenuOptions_flag?: boolean
    _editMenuOptions0_value?: EditMenuOptions | undefined
    _halfLeading_flag?: boolean
    _halfLeading0_value?: boolean | undefined
    _enableHapticFeedback_flag?: boolean
    _enableHapticFeedback0_value?: boolean | undefined
    _font_flag?: boolean
    _font0_value?: Font | undefined
    _font1_value?: FontSettingOptions | undefined
    _fontWeight_flag?: boolean
    _fontWeight0_value?: number | FontWeight | string | undefined
    _fontWeight1_value?: FontSettingOptions | undefined
    _selection_flag?: boolean
    _selection0_value?: number | undefined
    _selection1_value?: number | undefined
    _bindSelectionMenu_flag?: boolean
    _bindSelectionMenu0_value?: TextSpanType | undefined
    _bindSelectionMenu1_value?: CustomBuilder | undefined
    _bindSelectionMenu2_value?: TextResponseType | undefined
    _bindSelectionMenu3_value?: SelectionMenuOptions | undefined
    applyModifierPatch(component: TextAttribute): void {
        if (this._fontColor_flag)
            component.fontColor((this._fontColor0_value as ResourceColor | undefined))
        if (this._fontSize_flag)
            component.fontSize((this._fontSize0_value as number | string | Resource | undefined))
        if (this._minFontSize_flag)
            component.minFontSize((this._minFontSize0_value as number | string | Resource | undefined))
        if (this._maxFontSize_flag)
            component.maxFontSize((this._maxFontSize0_value as number | string | Resource | undefined))
        if (this._minFontScale_flag)
            component.minFontScale((this._minFontScale0_value as number | Resource | undefined))
        if (this._maxFontScale_flag)
            component.maxFontScale((this._maxFontScale0_value as number | Resource | undefined))
        if (this._fontStyle_flag)
            component.fontStyle((this._fontStyle0_value as FontStyle | undefined))
        if (this._lineSpacing_flag)
            component.lineSpacing((this._lineSpacing0_value as LengthMetrics | undefined))
        if (this._textAlign_flag)
            component.textAlign((this._textAlign0_value as TextAlign | undefined))
        if (this._lineHeight_flag)
            component.lineHeight((this._lineHeight0_value as number | string | Resource | undefined))
        if (this._textOverflow_flag)
            component.textOverflow((this._textOverflow0_value as TextOverflowOptions | undefined))
        if (this._fontFamily_flag)
            component.fontFamily((this._fontFamily0_value as string | Resource | undefined))
        if (this._maxLines_flag)
            component.maxLines((this._maxLines0_value as number | undefined))
        if (this._decoration_flag)
            component.decoration((this._decoration0_value as DecorationStyleInterface | undefined))
        if (this._letterSpacing_flag)
            component.letterSpacing((this._letterSpacing0_value as number | string | undefined))
        if (this._textCase_flag)
            component.textCase((this._textCase0_value as TextCase | undefined))
        if (this._baselineOffset_flag)
            component.baselineOffset((this._baselineOffset0_value as number | string | undefined))
        if (this._copyOption_flag)
            component.copyOption((this._copyOption0_value as CopyOptions | undefined))
        if (this._draggable_flag)
            component.draggable((this._draggable0_value as boolean | undefined))
        if (this._textShadow_flag)
            component.textShadow((this._textShadow0_value as ShadowOptions | Array<ShadowOptions> | undefined))
        if (this._heightAdaptivePolicy_flag)
            component.heightAdaptivePolicy((this._heightAdaptivePolicy0_value as TextHeightAdaptivePolicy | undefined))
        if (this._textIndent_flag)
            component.textIndent((this._textIndent0_value as Length | undefined))
        if (this._wordBreak_flag)
            component.wordBreak((this._wordBreak0_value as WordBreak | undefined))
        if (this._lineBreakStrategy_flag)
            component.lineBreakStrategy((this._lineBreakStrategy0_value as LineBreakStrategy | undefined))
        if (this._onCopy_flag)
            component.onCopy((this._onCopy0_value as ((value: string) => void) | undefined))
        if (this._caretColor_flag)
            component.caretColor((this._caretColor0_value as ResourceColor | undefined))
        if (this._selectedBackgroundColor_flag)
            component.selectedBackgroundColor((this._selectedBackgroundColor0_value as ResourceColor | undefined))
        if (this._ellipsisMode_flag)
            component.ellipsisMode((this._ellipsisMode0_value as EllipsisMode | undefined))
        if (this._enableDataDetector_flag)
            component.enableDataDetector((this._enableDataDetector0_value as boolean | undefined))
        if (this._dataDetectorConfig_flag)
            component.dataDetectorConfig((this._dataDetectorConfig0_value as TextDataDetectorConfig | undefined))
        if (this._onTextSelectionChange_flag)
            component.onTextSelectionChange((this._onTextSelectionChange0_value as ((selectionStart: number,selectionEnd: number) => void) | undefined))
        if (this._fontFeature_flag)
            component.fontFeature((this._fontFeature0_value as string | undefined))
        if (this._marqueeOptions_flag)
            component.marqueeOptions((this._marqueeOptions0_value as TextMarqueeOptions | undefined))
        if (this._onMarqueeStateChange_flag)
            component.onMarqueeStateChange((this._onMarqueeStateChange0_value as ((value0: MarqueeState) => void) | undefined))
        if (this._privacySensitive_flag)
            component.privacySensitive((this._privacySensitive0_value as boolean | undefined))
        if (this._textSelectable_flag)
            component.textSelectable((this._textSelectable0_value as TextSelectableMode | undefined))
        if (this._editMenuOptions_flag)
            component.editMenuOptions((this._editMenuOptions0_value as EditMenuOptions | undefined))
        if (this._halfLeading_flag)
            component.halfLeading((this._halfLeading0_value as boolean | undefined))
        if (this._enableHapticFeedback_flag)
            component.enableHapticFeedback((this._enableHapticFeedback0_value as boolean | undefined))
        if (this._font_flag)
            component.font((this._font0_value as Font | undefined), (this._font1_value as FontSettingOptions | undefined))
        if (this._fontWeight_flag)
            component.fontWeight((this._fontWeight0_value as number | FontWeight | string | undefined), (this._fontWeight1_value as FontSettingOptions | undefined))
        if (this._selection_flag)
            component.selection((this._selection0_value as number | undefined), (this._selection1_value as number | undefined))
        if (this._bindSelectionMenu_flag)
            component.bindSelectionMenu((this._bindSelectionMenu0_value as TextSpanType | undefined), (this._bindSelectionMenu1_value as CustomBuilder | undefined), (this._bindSelectionMenu2_value as TextResponseType | undefined), (this._bindSelectionMenu3_value as SelectionMenuOptions | undefined))
    }
    public fontColor(value: ResourceColor | undefined): this {
        this._fontColor_flag = true
        this._fontColor0_value = value
        return this
    }
    public fontSize(value: number | string | Resource | undefined): this {
        this._fontSize_flag = true
        this._fontSize0_value = value
        return this
    }
    public minFontSize(value: number | string | Resource | undefined): this {
        this._minFontSize_flag = true
        this._minFontSize0_value = value
        return this
    }
    public maxFontSize(value: number | string | Resource | undefined): this {
        this._maxFontSize_flag = true
        this._maxFontSize0_value = value
        return this
    }
    public minFontScale(value: number | Resource | undefined): this {
        this._minFontScale_flag = true
        this._minFontScale0_value = value
        return this
    }
    public maxFontScale(value: number | Resource | undefined): this {
        this._maxFontScale_flag = true
        this._maxFontScale0_value = value
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        this._fontStyle_flag = true
        this._fontStyle0_value = value
        return this
    }
    public lineSpacing(value: LengthMetrics | undefined): this {
        this._lineSpacing_flag = true
        this._lineSpacing0_value = value
        return this
    }
    public textAlign(value: TextAlign | undefined): this {
        this._textAlign_flag = true
        this._textAlign0_value = value
        return this
    }
    public lineHeight(value: number | string | Resource | undefined): this {
        this._lineHeight_flag = true
        this._lineHeight0_value = value
        return this
    }
    public textOverflow(value: TextOverflowOptions | undefined): this {
        this._textOverflow_flag = true
        this._textOverflow0_value = value
        return this
    }
    public fontFamily(value: string | Resource | undefined): this {
        this._fontFamily_flag = true
        this._fontFamily0_value = value
        return this
    }
    public maxLines(value: number | undefined): this {
        this._maxLines_flag = true
        this._maxLines0_value = value
        return this
    }
    public decoration(value: DecorationStyleInterface | undefined): this {
        this._decoration_flag = true
        this._decoration0_value = value
        return this
    }
    public letterSpacing(value: number | string | undefined): this {
        this._letterSpacing_flag = true
        this._letterSpacing0_value = value
        return this
    }
    public textCase(value: TextCase | undefined): this {
        this._textCase_flag = true
        this._textCase0_value = value
        return this
    }
    public baselineOffset(value: number | string | undefined): this {
        this._baselineOffset_flag = true
        this._baselineOffset0_value = value
        return this
    }
    public copyOption(value: CopyOptions | undefined): this {
        this._copyOption_flag = true
        this._copyOption0_value = value
        return this
    }
    public draggable(value: boolean | undefined): this {
        this._draggable_flag = true
        this._draggable0_value = value
        return this
    }
    public textShadow(value: ShadowOptions | Array<ShadowOptions> | undefined): this {
        this._textShadow_flag = true
        this._textShadow0_value = value
        return this
    }
    public heightAdaptivePolicy(value: TextHeightAdaptivePolicy | undefined): this {
        this._heightAdaptivePolicy_flag = true
        this._heightAdaptivePolicy0_value = value
        return this
    }
    public textIndent(value: Length | undefined): this {
        this._textIndent_flag = true
        this._textIndent0_value = value
        return this
    }
    public wordBreak(value: WordBreak | undefined): this {
        this._wordBreak_flag = true
        this._wordBreak0_value = value
        return this
    }
    public lineBreakStrategy(value: LineBreakStrategy | undefined): this {
        this._lineBreakStrategy_flag = true
        this._lineBreakStrategy0_value = value
        return this
    }
    public onCopy(value: ((value: string) => void) | undefined): this {
        this._onCopy_flag = true
        this._onCopy0_value = value
        return this
    }
    public caretColor(value: ResourceColor | undefined): this {
        this._caretColor_flag = true
        this._caretColor0_value = value
        return this
    }
    public selectedBackgroundColor(value: ResourceColor | undefined): this {
        this._selectedBackgroundColor_flag = true
        this._selectedBackgroundColor0_value = value
        return this
    }
    public ellipsisMode(value: EllipsisMode | undefined): this {
        this._ellipsisMode_flag = true
        this._ellipsisMode0_value = value
        return this
    }
    public enableDataDetector(value: boolean | undefined): this {
        this._enableDataDetector_flag = true
        this._enableDataDetector0_value = value
        return this
    }
    public dataDetectorConfig(value: TextDataDetectorConfig | undefined): this {
        this._dataDetectorConfig_flag = true
        this._dataDetectorConfig0_value = value
        return this
    }
    public onTextSelectionChange(value: ((selectionStart: number,selectionEnd: number) => void) | undefined): this {
        this._onTextSelectionChange_flag = true
        this._onTextSelectionChange0_value = value
        return this
    }
    public fontFeature(value: string | undefined): this {
        this._fontFeature_flag = true
        this._fontFeature0_value = value
        return this
    }
    public marqueeOptions(value: TextMarqueeOptions | undefined): this {
        this._marqueeOptions_flag = true
        this._marqueeOptions0_value = value
        return this
    }
    public onMarqueeStateChange(value: ((value0: MarqueeState) => void) | undefined): this {
        this._onMarqueeStateChange_flag = true
        this._onMarqueeStateChange0_value = value
        return this
    }
    public privacySensitive(value: boolean | undefined): this {
        this._privacySensitive_flag = true
        this._privacySensitive0_value = value
        return this
    }
    public textSelectable(value: TextSelectableMode | undefined): this {
        this._textSelectable_flag = true
        this._textSelectable0_value = value
        return this
    }
    public editMenuOptions(value: EditMenuOptions | undefined): this {
        this._editMenuOptions_flag = true
        this._editMenuOptions0_value = value
        return this
    }
    public halfLeading(value: boolean | undefined): this {
        this._halfLeading_flag = true
        this._halfLeading0_value = value
        return this
    }
    public enableHapticFeedback(value: boolean | undefined): this {
        this._enableHapticFeedback_flag = true
        this._enableHapticFeedback0_value = value
        return this
    }
    public font(fontValue: Font | undefined, options?: FontSettingOptions): this {
        this._font_flag = true
        this._font0_value = fontValue
        this._font1_value = options
        return this
    }
    public fontWeight(weight: number | FontWeight | string | undefined, options?: FontSettingOptions): this {
        this._fontWeight_flag = true
        this._fontWeight0_value = weight
        this._fontWeight1_value = options
        return this
    }
    public selection(selectionStart: number | undefined, selectionEnd: number | undefined): this {
        this._selection_flag = true
        this._selection0_value = selectionStart
        this._selection1_value = selectionEnd
        return this
    }
    public bindSelectionMenu(spanType: TextSpanType | undefined, content: CustomBuilder | undefined, responseType: TextResponseType | undefined, options?: SelectionMenuOptions): this {
        this._bindSelectionMenu_flag = true
        this._bindSelectionMenu0_value = spanType
        this._bindSelectionMenu1_value = content
        this._bindSelectionMenu2_value = responseType
        this._bindSelectionMenu3_value = options
        return this
    }
    public attributeModifier(value: AttributeModifier<TextAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class TextController_serializer {
    public static write(buffer: SerializerBase, value: TextController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): TextController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return TextControllerInternal.fromPtr(ptr)
    }
}
export class TextOptions_serializer {
    public static write(buffer: SerializerBase, value: TextOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_controller  = value.controller
        TextController_serializer.write(valueSerializer, value_controller)
    }
    public static read(buffer: DeserializerBase): TextOptions {
        let valueDeserializer : DeserializerBase = buffer
        const controller_result : TextController = (TextController_serializer.read(valueDeserializer) as TextController)
        let value : TextOptions = ({controller: controller_result} as TextOptions)
        return value
    }
}
export class TextOverflowOptions_serializer {
    public static write(buffer: SerializerBase, value: TextOverflowOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_overflow  = value.overflow
        valueSerializer.writeInt32(TypeChecker.TextOverflow_ToNumeric(value_overflow))
    }
    public static read(buffer: DeserializerBase): TextOverflowOptions {
        let valueDeserializer : DeserializerBase = buffer
        const overflow_result : TextOverflow = TypeChecker.TextOverflow_FromNumeric(valueDeserializer.readInt32())
        let value : TextOverflowOptions = ({overflow: overflow_result} as TextOverflowOptions)
        return value
    }
}
export class TextMarqueeOptions_serializer {
    public static write(buffer: SerializerBase, value: TextMarqueeOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_start  = value.start
        valueSerializer.writeBoolean(value_start)
        const value_step  = value.step
        let value_step_type : int32 = RuntimeType.UNDEFINED
        value_step_type = runtimeType(value_step)
        valueSerializer.writeInt8((value_step_type).toChar())
        if ((value_step_type) != (RuntimeType.UNDEFINED)) {
            const value_step_value  = value_step!
            valueSerializer.writeNumber(value_step_value)
        }
        const value_loop  = value.loop
        let value_loop_type : int32 = RuntimeType.UNDEFINED
        value_loop_type = runtimeType(value_loop)
        valueSerializer.writeInt8((value_loop_type).toChar())
        if ((value_loop_type) != (RuntimeType.UNDEFINED)) {
            const value_loop_value  = value_loop!
            valueSerializer.writeNumber(value_loop_value)
        }
        const value_fromStart  = value.fromStart
        let value_fromStart_type : int32 = RuntimeType.UNDEFINED
        value_fromStart_type = runtimeType(value_fromStart)
        valueSerializer.writeInt8((value_fromStart_type).toChar())
        if ((value_fromStart_type) != (RuntimeType.UNDEFINED)) {
            const value_fromStart_value  = value_fromStart!
            valueSerializer.writeBoolean(value_fromStart_value)
        }
        const value_delay  = value.delay
        let value_delay_type : int32 = RuntimeType.UNDEFINED
        value_delay_type = runtimeType(value_delay)
        valueSerializer.writeInt8((value_delay_type).toChar())
        if ((value_delay_type) != (RuntimeType.UNDEFINED)) {
            const value_delay_value  = value_delay!
            valueSerializer.writeNumber(value_delay_value)
        }
        const value_fadeout  = value.fadeout
        let value_fadeout_type : int32 = RuntimeType.UNDEFINED
        value_fadeout_type = runtimeType(value_fadeout)
        valueSerializer.writeInt8((value_fadeout_type).toChar())
        if ((value_fadeout_type) != (RuntimeType.UNDEFINED)) {
            const value_fadeout_value  = value_fadeout!
            valueSerializer.writeBoolean(value_fadeout_value)
        }
        const value_marqueeStartPolicy  = value.marqueeStartPolicy
        let value_marqueeStartPolicy_type : int32 = RuntimeType.UNDEFINED
        value_marqueeStartPolicy_type = runtimeType(value_marqueeStartPolicy)
        valueSerializer.writeInt8((value_marqueeStartPolicy_type).toChar())
        if ((value_marqueeStartPolicy_type) != (RuntimeType.UNDEFINED)) {
            const value_marqueeStartPolicy_value  = (value_marqueeStartPolicy as MarqueeStartPolicy)
            valueSerializer.writeInt32(TypeChecker.MarqueeStartPolicy_ToNumeric(value_marqueeStartPolicy_value))
        }
    }
    public static read(buffer: DeserializerBase): TextMarqueeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const start_result : boolean = valueDeserializer.readBoolean()
        const step_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let step_buf : number | undefined
        if ((step_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            step_buf = (valueDeserializer.readNumber() as number)
        }
        const step_result : number | undefined = step_buf
        const loop_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let loop_buf : number | undefined
        if ((loop_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            loop_buf = (valueDeserializer.readNumber() as number)
        }
        const loop_result : number | undefined = loop_buf
        const fromStart_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fromStart_buf : boolean | undefined
        if ((fromStart_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            fromStart_buf = valueDeserializer.readBoolean()
        }
        const fromStart_result : boolean | undefined = fromStart_buf
        const delay_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let delay_buf : number | undefined
        if ((delay_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            delay_buf = (valueDeserializer.readNumber() as number)
        }
        const delay_result : number | undefined = delay_buf
        const fadeout_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fadeout_buf : boolean | undefined
        if ((fadeout_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            fadeout_buf = valueDeserializer.readBoolean()
        }
        const fadeout_result : boolean | undefined = fadeout_buf
        const marqueeStartPolicy_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let marqueeStartPolicy_buf : MarqueeStartPolicy | undefined
        if ((marqueeStartPolicy_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            marqueeStartPolicy_buf = TypeChecker.MarqueeStartPolicy_FromNumeric(valueDeserializer.readInt32())
        }
        const marqueeStartPolicy_result : MarqueeStartPolicy | undefined = marqueeStartPolicy_buf
        let value : TextMarqueeOptions = ({start: start_result, step: step_result, loop: loop_result, fromStart: fromStart_result, delay: delay_result, fadeout: fadeout_result, marqueeStartPolicy: marqueeStartPolicy_result} as TextMarqueeOptions)
        return value
    }
}
