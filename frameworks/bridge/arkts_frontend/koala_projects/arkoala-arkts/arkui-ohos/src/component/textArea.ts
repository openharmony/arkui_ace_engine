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

import { TextContentControllerBase, TextContentControllerBaseInternal, CaretOffset, RectResult, SelectionOptions, CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, TextDecorationOptions, InputCounterOptions } from "./common"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, float32, int64 } from "@koalaui/common"
import { Serializer } from "./../generated/peers/Serializer"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { Deserializer } from "./../generated/peers/Deserializer"
import { CallbackTransformer } from "./../generated/peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ResourceStr, Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, AccessibilityOptions, Font } from "./units"
import { EnterKeyType, SubmitEvent } from "./textInput"
import { PasteEvent, KeyboardOptions } from "./richEditor"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, TextAlign, FontStyle, FontWeight, TextOverflow, CopyOptions, TextContentStyle, BarState, TextHeightAdaptivePolicy, WordBreak, LineBreakStrategy } from "./enums"
import { LengthMetrics } from "../Graphics"
import { ResizableOptions } from "./image"
import { Resource } from "global/resource";
import { Callback_Void } from "./abilityComponent"
import { FocusBoxStyle, FocusPriority } from "./focus"
import { CircleShape } from "./../generated/ArkCircleShapeMaterialized"
import { EllipseShape } from "./../generated/ArkEllipseShapeMaterialized"
import { PathShape } from "./../generated/ArkPathShapeMaterialized"
import { RectShape } from "./../generated/ArkRectShapeMaterialized"
import { AttributeModifier } from "./../component/common" 
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureType, GestureMask } from "./gesture"
import { PixelMap } from "./../generated/ArkPixelMapMaterialized"
import { CaretStyle, EditableTextOnChangeCallback, InsertValue, DeleteValue, EditMenuOptions } from "./textCommon"
import { Callback_Number_Number_Void } from "./grid"
import { Callback_Boolean_Void } from "./checkbox"
import { Callback_String_Void } from "./gridRow"
import { Callback_InsertValue_Boolean, Callback_InsertValue_Void, Callback_DeleteValue_Boolean, Callback_DeleteValue_Void } from "./search"
import { Callback_ResourceStr_Void } from "./select"
import { ArkTextAreaComponent } from "./../generated/ArkTextArea"
import { ArkTextAreaPeer } from "./../generated/peers/ArkTextAreaPeer"
export class TextAreaControllerInternal {
    public static fromPtr(ptr: KPointer): TextAreaController {
        const obj : TextAreaController = new TextAreaController()
        obj.peer = new Finalizable(ptr, TextAreaController.getFinalizer())
        return obj
    }
}
export class TextAreaController extends TextContentControllerBase implements MaterializedBase {
    static ctor_textareacontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextAreaController_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = TextAreaController.ctor_textareacontroller()
        this.peer = new Finalizable(ctorPtr, TextAreaController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextAreaController_getFinalizer()
    }
    public caretPosition(value: number): void {
        const value_casted = value as (number)
        this.caretPosition_serialize(value_casted)
        return
    }
    public setTextSelection(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void {
        const selectionStart_casted = selectionStart as (number)
        const selectionEnd_casted = selectionEnd as (number)
        const options_casted = options as (SelectionOptions | undefined)
        this.setTextSelection_serialize(selectionStart_casted, selectionEnd_casted, options_casted)
        return
    }
    public stopEditing(): void {
        this.stopEditing_serialize()
        return
    }
    private caretPosition_serialize(value: number): void {
        ArkUIGeneratedNativeModule._TextAreaController_caretPosition(this.peer!.ptr, value)
    }
    private setTextSelection_serialize(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeSelectionOptions(options_value)
        }
        ArkUIGeneratedNativeModule._TextAreaController_setTextSelection(this.peer!.ptr, selectionStart, selectionEnd, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private stopEditing_serialize(): void {
        ArkUIGeneratedNativeModule._TextAreaController_stopEditing(this.peer!.ptr)
    }
}
export interface TextAreaOptions {
    placeholder?: ResourceStr;
    text?: ResourceStr;
    controller?: TextAreaController;
}
export enum TextAreaType {
    NORMAL = 0,
    NUMBER = 2,
    PHONE_NUMBER = 3,
    EMAIL = 5,
    NUMBER_DECIMAL = 12,
    URL = 13
}
export enum ContentType {
    USER_NAME = 0,
    PASSWORD = 1,
    NEW_PASSWORD = 2,
    FULL_STREET_ADDRESS = 3,
    HOUSE_NUMBER = 4,
    DISTRICT_ADDRESS = 5,
    CITY_ADDRESS = 6,
    PROVINCE_ADDRESS = 7,
    COUNTRY_ADDRESS = 8,
    PERSON_FULL_NAME = 9,
    PERSON_LAST_NAME = 10,
    PERSON_FIRST_NAME = 11,
    PHONE_NUMBER = 12,
    PHONE_COUNTRY_CODE = 13,
    FULL_PHONE_NUMBER = 14,
    EMAIL_ADDRESS = 15,
    BANK_CARD_NUMBER = 16,
    ID_CARD_NUMBER = 17,
    NICKNAME = 23,
    DETAIL_INFO_WITHOUT_STREET = 24,
    FORMAT_ADDRESS = 25
}
export type TextAreaSubmitCallback = (enterKeyType: EnterKeyType, event?: SubmitEvent) => void;
export type Callback_EnterKeyType_Void = (enterKey: EnterKeyType) => void;
export type Callback_String_PasteEvent_Void = (value: string, event: PasteEvent) => void;
/** @memo:stable */
export interface TextAreaAttribute extends CommonMethod {
    /** @memo */
    setTextAreaOptions(value?: TextAreaOptions): this
    /** @memo */
    placeholderColor(value: ResourceColor): this
    /** @memo */
    placeholderFont(value: Font): this
    /** @memo */
    enterKeyType(value: EnterKeyType): this
    /** @memo */
    textAlign(value: TextAlign): this
    /** @memo */
    caretColor(value: ResourceColor): this
    /** @memo */
    fontColor(value: ResourceColor): this
    /** @memo */
    fontSize(value: Length): this
    /** @memo */
    fontStyle(value: FontStyle): this
    /** @memo */
    fontWeight(value: number | FontWeight | string): this
    /** @memo */
    fontFamily(value: ResourceStr): this
    /** @memo */
    textOverflow(value: TextOverflow): this
    /** @memo */
    textIndent(value: Dimension): this
    /** @memo */
    caretStyle(value: CaretStyle): this
    /** @memo */
    selectedBackgroundColor(value: ResourceColor): this
    /** @memo */
    onSubmit(value: ((enterKey: EnterKeyType) => void) | TextAreaSubmitCallback): this
    /** @memo */
    onChange(value: EditableTextOnChangeCallback): this
    /** @memo */
    onTextSelectionChange(value: ((first: number,last: number) => void)): this
    /** @memo */
    onContentScroll(value: ((first: number,last: number) => void)): this
    /** @memo */
    onEditChange(value: ((parameter: boolean) => void)): this
    /** @memo */
    onCopy(value: ((breakpoints: string) => void)): this
    /** @memo */
    onCut(value: ((breakpoints: string) => void)): this
    /** @memo */
    onPaste(value: ((value: string,event: PasteEvent) => void)): this
    /** @memo */
    copyOption(value: CopyOptions): this
    /** @memo */
    enableKeyboardOnFocus(value: boolean): this
    /** @memo */
    maxLength(value: number): this
    /** @memo */
    style(value: TextContentStyle): this
    /** @memo */
    barState(value: BarState): this
    /** @memo */
    selectionMenuHidden(value: boolean): this
    /** @memo */
    minFontSize(value: number | string | Resource): this
    /** @memo */
    maxFontSize(value: number | string | Resource): this
    /** @memo */
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy): this
    /** @memo */
    maxLines(value: number): this
    /** @memo */
    wordBreak(value: WordBreak): this
    /** @memo */
    lineBreakStrategy(value: LineBreakStrategy): this
    /** @memo */
    decoration(value: TextDecorationOptions): this
    /** @memo */
    letterSpacing(value: number | string | Resource): this
    /** @memo */
    lineSpacing(value: LengthMetrics): this
    /** @memo */
    lineHeight(value: number | string | Resource): this
    /** @memo */
    type(value: TextAreaType): this
    /** @memo */
    enableAutoFill(value: boolean): this
    /** @memo */
    contentType(value: ContentType): this
    /** @memo */
    fontFeature(value: string): this
    /** @memo */
    onWillInsert(value: ((parameter: InsertValue) => boolean)): this
    /** @memo */
    onDidInsert(value: ((parameter: InsertValue) => void)): this
    /** @memo */
    onWillDelete(value: ((parameter: DeleteValue) => boolean)): this
    /** @memo */
    onDidDelete(value: ((parameter: DeleteValue) => void)): this
    /** @memo */
    editMenuOptions(value: EditMenuOptions): this
    /** @memo */
    enablePreviewText(value: boolean): this
    /** @memo */
    enableHapticFeedback(value: boolean): this
    /** @memo */
    inputFilter(value: ResourceStr, error?: ((breakpoints: string) => void)): this
    /** @memo */
    showCounter(value: boolean, options?: InputCounterOptions): this
    /** @memo */
    customKeyboard(value: CustomBuilder, options?: KeyboardOptions): this
    /** @memo */
    _onChangeEvent_text(callback: ((value: ResourceStr) => void)): void
}
/** @memo */
export function TextArea(
  /** @memo */
  style: ((attributes: TextAreaAttribute) => void) | undefined,
  value?: TextAreaOptions | undefined, 
  /** @memo */
  content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkTextAreaComponent()
    })
    NodeAttach<ArkTextAreaPeer>((): ArkTextAreaPeer => ArkTextAreaPeer.create(receiver), (_: ArkTextAreaPeer) => {
        receiver.setTextAreaOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
