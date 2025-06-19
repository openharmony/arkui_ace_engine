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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, float32, int64 } from "@koalaui/common"
import { Serializer } from "./../generated/peers/Serializer"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { Deserializer } from "./../generated/peers/Deserializer"
import { CallbackTransformer } from "./../generated/peers/CallbackTransformer"
import { TextContentControllerBase, TextContentControllerBaseInternal, CaretOffset, RectResult, SelectionOptions, CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, TextDecorationOptions, InputCounterOptions } from "./common"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ResourceColor, ResourceStr, Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, AccessibilityOptions, Font } from "./units"
import { Resource } from "global/resource";
import { PasteEvent, KeyboardOptions } from "./richEditor"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, TextOverflow, FontStyle, FontWeight, CopyOptions, TextAlign, TextContentStyle, BarState, WordBreak, LineBreakStrategy, TextHeightAdaptivePolicy } from "./enums"
import { LengthMetrics } from "../Graphics"
import { ResizableOptions } from "./image"
import { Callback_Void } from "./abilityComponent"
import { FocusBoxStyle, FocusPriority } from "./focus"
import { CircleShape } from "./../generated/ArkCircleShapeMaterialized"
import { EllipseShape } from "./../generated/ArkEllipseShapeMaterialized"
import { PathShape } from "./../generated/ArkPathShapeMaterialized"
import { RectShape } from "./../generated/ArkRectShapeMaterialized"
import { AttributeModifier } from "./../component/common" 
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureType, GestureMask } from "./gesture"
import { PixelMap } from "./../generated/ArkPixelMapMaterialized"
import { ContentType } from "./textArea"
import { Callback_Boolean_Void } from "./checkbox"
import { EditableTextOnChangeCallback, CaretStyle, InsertValue, DeleteValue, EditMenuOptions } from "./textCommon"
import { Callback_String_Void } from "./gridRow"
import { CancelButtonOptions, CancelButtonSymbolOptions, Callback_InsertValue_Boolean, Callback_InsertValue_Void, Callback_DeleteValue_Boolean, Callback_DeleteValue_Void } from "./search"
import { Callback_ResourceStr_Void } from "./select"
import { ArkTextInputComponent } from "./../generated/ArkTextInput"
import { ArkTextInputPeer } from "./../generated/peers/ArkTextInputPeer"
export interface SubmitEvent {
    text: string
    keepEditableState(): void
}
export class SubmitEventInternal implements MaterializedBase,SubmitEvent {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get text(): string {
        return this.getText()
    }
    set text(text: string) {
        this.setText(text)
    }
    static ctor_submitevent(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SubmitEvent_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = SubmitEventInternal.ctor_submitevent()
        this.peer = new Finalizable(ctorPtr, SubmitEventInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SubmitEvent_getFinalizer()
    }
    public keepEditableState(): void {
        this.keepEditableState_serialize()
        return
    }
    private getText(): string {
        return this.getText_serialize()
    }
    private setText(text: string): void {
        const text_casted = text as (string)
        this.setText_serialize(text_casted)
        return
    }
    private keepEditableState_serialize(): void {
        ArkUIGeneratedNativeModule._SubmitEvent_keepEditableState(this.peer!.ptr)
    }
    private getText_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._SubmitEvent_getText(this.peer!.ptr)
        return retval
    }
    private setText_serialize(text: string): void {
        ArkUIGeneratedNativeModule._SubmitEvent_setText(this.peer!.ptr, text)
    }
    public static fromPtr(ptr: KPointer): SubmitEventInternal {
        const obj : SubmitEventInternal = new SubmitEventInternal()
        obj.peer = new Finalizable(ptr, SubmitEventInternal.getFinalizer())
        return obj
    }
}
export class TextInputControllerInternal {
    public static fromPtr(ptr: KPointer): TextInputController {
        const obj : TextInputController = new TextInputController()
        obj.peer = new Finalizable(ptr, TextInputController.getFinalizer())
        return obj
    }
}
export class TextInputController extends TextContentControllerBase implements MaterializedBase {
    static ctor_textinputcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextInputController_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = TextInputController.ctor_textinputcontroller()
        this.peer = new Finalizable(ctorPtr, TextInputController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._TextInputController_getFinalizer()
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
        ArkUIGeneratedNativeModule._TextInputController_caretPosition(this.peer!.ptr, value)
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
        ArkUIGeneratedNativeModule._TextInputController_setTextSelection(this.peer!.ptr, selectionStart, selectionEnd, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private stopEditing_serialize(): void {
        ArkUIGeneratedNativeModule._TextInputController_stopEditing(this.peer!.ptr)
    }
}
export enum InputType {
    NORMAL = 0,
    Normal = 0,
    NUMBER = 1,
    Number = 1,
    PHONE_NUMBER = 2,
    PhoneNumber = 2,
    EMAIL = 3,
    Email = 3,
    PASSWORD = 4,
    Password = 4,
    NUMBER_PASSWORD = 8,
    SCREEN_LOCK_PASSWORD = 9,
    USER_NAME = 10,
    NEW_PASSWORD = 11,
    NUMBER_DECIMAL = 12,
    URL = 13
}
export enum EnterKeyType {
    GO = 2,
    Go = 2,
    SEARCH = 3,
    Search = 3,
    SEND = 4,
    Send = 4,
    NEXT = 5,
    Next = 5,
    DONE = 6,
    Done = 6,
    PREVIOUS = 7,
    NEW_LINE = 8
}
export interface UnderlineColor {
    typing?: ResourceColor | undefined;
    normal?: ResourceColor | undefined;
    error?: ResourceColor | undefined;
    disable?: ResourceColor | undefined;
}
export interface TextInputOptions {
    placeholder?: ResourceStr;
    text?: ResourceStr;
    controller?: TextInputController;
}
export enum TextInputStyle {
    DEFAULT = 0,
    Default = 0,
    INLINE = 1,
    Inline = 1
}
export interface PasswordIcon {
    onIconSrc?: string | Resource;
    offIconSrc?: string | Resource;
}
export type OnSubmitCallback = (enterKey: EnterKeyType, event: SubmitEvent) => void;
export type OnTextSelectionChangeCallback = (selectionStart: number, selectionEnd: number) => void;
export type OnContentScrollCallback = (totalOffsetX: number, totalOffsetY: number) => void;
export type OnPasteCallback = (content: string, event: PasteEvent) => void;
/** @memo:stable */
export interface TextInputAttribute extends CommonMethod {
    /** @memo */
    setTextInputOptions(value?: TextInputOptions): this
    /** @memo */
    type(value: InputType): this
    /** @memo */
    contentType(value: ContentType): this
    /** @memo */
    placeholderColor(value: ResourceColor): this
    /** @memo */
    textOverflow(value: TextOverflow): this
    /** @memo */
    textIndent(value: Dimension): this
    /** @memo */
    placeholderFont(value?: Font): this
    /** @memo */
    enterKeyType(value: EnterKeyType): this
    /** @memo */
    caretColor(value: ResourceColor): this
    /** @memo */
    onEditChanged(value: ((parameter: boolean) => void)): this
    /** @memo */
    onEditChange(value: ((parameter: boolean) => void)): this
    /** @memo */
    onSubmit(value: OnSubmitCallback): this
    /** @memo */
    onChange(value: EditableTextOnChangeCallback): this
    /** @memo */
    onTextSelectionChange(value: OnTextSelectionChangeCallback): this
    /** @memo */
    onContentScroll(value: OnContentScrollCallback): this
    /** @memo */
    maxLength(value: number): this
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
    onCopy(value: ((breakpoints: string) => void)): this
    /** @memo */
    onCut(value: ((breakpoints: string) => void)): this
    /** @memo */
    onPaste(value: OnPasteCallback): this
    /** @memo */
    copyOption(value: CopyOptions): this
    /** @memo */
    showPasswordIcon(value: boolean): this
    /** @memo */
    textAlign(value: TextAlign): this
    /** @memo */
    style(value: TextInputStyle | TextContentStyle): this
    /** @memo */
    caretStyle(value: CaretStyle): this
    /** @memo */
    selectedBackgroundColor(value: ResourceColor): this
    /** @memo */
    caretPosition(value: number): this
    /** @memo */
    enableKeyboardOnFocus(value: boolean): this
    /** @memo */
    passwordIcon(value: PasswordIcon): this
    /** @memo */
    showError(value?: ResourceStr): this
    /** @memo */
    showUnit(value: CustomBuilder): this
    /** @memo */
    showUnderline(value: boolean): this
    /** @memo */
    underlineColor(value?: ResourceColor | UnderlineColor): this
    /** @memo */
    selectionMenuHidden(value: boolean): this
    /** @memo */
    barState(value: BarState): this
    /** @memo */
    maxLines(value: number): this
    /** @memo */
    wordBreak(value: WordBreak): this
    /** @memo */
    lineBreakStrategy(value: LineBreakStrategy): this
    /** @memo */
    cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions): this
    /** @memo */
    selectAll(value: boolean): this
    /** @memo */
    minFontSize(value: number | string | Resource): this
    /** @memo */
    maxFontSize(value: number | string | Resource): this
    /** @memo */
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy): this
    /** @memo */
    enableAutoFill(value: boolean): this
    /** @memo */
    decoration(value: TextDecorationOptions): this
    /** @memo */
    letterSpacing(value: number | string | Resource): this
    /** @memo */
    lineHeight(value: number | string | Resource): this
    /** @memo */
    passwordRules(value: string): this
    /** @memo */
    fontFeature(value: string): this
    /** @memo */
    showPassword(value: boolean): this
    /** @memo */
    onSecurityStateChange(value: ((parameter: boolean) => void)): this
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
    customKeyboard(value: CustomBuilder, options?: KeyboardOptions): this
    /** @memo */
    showCounter(value: boolean, options?: InputCounterOptions): this
    /** @memo */
    _onChangeEvent_text(callback: ((value: ResourceStr) => void)): void
}
/** @memo */
export function TextInput(
  /** @memo */
  style: ((attributes: TextInputAttribute) => void) | undefined,
  value?: TextInputOptions | undefined, 
  /** @memo */
  content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkTextInputComponent()
    })
    NodeAttach<ArkTextInputPeer>((): ArkTextInputPeer => ArkTextInputPeer.create(receiver), (_: ArkTextInputPeer) => {
        receiver.setTextInputOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
