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

import { TextContentControllerBase, TextContentControllerBaseInternal, CaretOffset, RectResult, SelectionOptions, SymbolGlyphModifier, CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, TextDecorationOptions } from "./common"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, float32, int64 } from "@koalaui/common"
import { Serializer } from "./../generated/peers/Serializer"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { Deserializer } from "./../generated/peers/Deserializer"
import { CallbackTransformer } from "./../generated/peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ResourceStr, Length, ResourceColor, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, AccessibilityOptions, Font } from "./units"
import { SubmitEvent, EnterKeyType, OnTextSelectionChangeCallback, OnContentScrollCallback, OnPasteCallback } from "./textInput"
import { InsertValue, DeleteValue, CaretStyle, EditableTextOnChangeCallback, EditMenuOptions } from "./textCommon"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, CopyOptions, TextAlign } from "./enums"
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
import { Callback_Boolean_Void } from "./checkbox"
import { Callback_String_Void } from "./gridRow"
import { KeyboardOptions } from "./richEditor"
import { ArkSearchComponent } from "./../generated/ArkSearch"
import { ArkSearchPeer } from "./../generated/peers/ArkSearchPeer"
export class SearchControllerInternal {
    public static fromPtr(ptr: KPointer): SearchController {
        const obj : SearchController = new SearchController()
        obj.peer = new Finalizable(ptr, SearchController.getFinalizer())
        return obj
    }
}
export class SearchController extends TextContentControllerBase implements MaterializedBase {
    static ctor_searchcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SearchController_ctor()
        return retval
    }
    constructor() {
        super()
        const ctorPtr : KPointer = SearchController.ctor_searchcontroller()
        this.peer = new Finalizable(ctorPtr, SearchController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._SearchController_getFinalizer()
    }
    public caretPosition(value: number): void {
        const value_casted = value as (number)
        this.caretPosition_serialize(value_casted)
        return
    }
    public stopEditing(): void {
        this.stopEditing_serialize()
        return
    }
    public setTextSelection(selectionStart: number, selectionEnd: number, options?: SelectionOptions): void {
        const selectionStart_casted = selectionStart as (number)
        const selectionEnd_casted = selectionEnd as (number)
        const options_casted = options as (SelectionOptions | undefined)
        this.setTextSelection_serialize(selectionStart_casted, selectionEnd_casted, options_casted)
        return
    }
    private caretPosition_serialize(value: number): void {
        ArkUIGeneratedNativeModule._SearchController_caretPosition(this.peer!.ptr, value)
    }
    private stopEditing_serialize(): void {
        ArkUIGeneratedNativeModule._SearchController_stopEditing(this.peer!.ptr)
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
        ArkUIGeneratedNativeModule._SearchController_setTextSelection(this.peer!.ptr, selectionStart, selectionEnd, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum CancelButtonStyle {
    CONSTANT = 0,
    INVISIBLE = 1,
    INPUT = 2
}
export enum SearchType {
    NORMAL = 0,
    NUMBER = 2,
    PHONE_NUMBER = 3,
    EMAIL = 5,
    NUMBER_DECIMAL = 12,
    URL = 13
}
export interface SearchOptions {
    value?: string;
    placeholder?: ResourceStr;
    icon?: string;
    controller?: SearchController;
}
export interface IconOptions {
    size?: Length;
    color?: ResourceColor;
    src?: ResourceStr;
}
export interface SearchButtonOptions {
    fontSize?: Length;
    fontColor?: ResourceColor;
    autoDisable?: boolean;
}
export interface CancelButtonOptions {
    style?: CancelButtonStyle;
    icon?: IconOptions;
}
export interface CancelButtonSymbolOptions {
    style?: CancelButtonStyle;
    icon?: SymbolGlyphModifier;
}
export type SearchSubmitCallback = (searchContent: string, event?: SubmitEvent) => void;
export type Callback_InsertValue_Boolean = (parameter: InsertValue) => boolean;
export type Callback_InsertValue_Void = (parameter: InsertValue) => void;
export type Callback_DeleteValue_Boolean = (parameter: DeleteValue) => boolean;
export type Callback_DeleteValue_Void = (parameter: DeleteValue) => void;
/** @memo:stable */
export interface SearchAttribute extends CommonMethod {
    /** @memo */
    setSearchOptions(options?: SearchOptions): this
    /** @memo */
    fontColor(value: ResourceColor): this
    /** @memo */
    searchIcon(value: IconOptions | SymbolGlyphModifier): this
    /** @memo */
    cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions): this
    /** @memo */
    textIndent(value: Dimension): this
    /** @memo */
    onEditChange(value: ((parameter: boolean) => void)): this
    /** @memo */
    selectedBackgroundColor(value: ResourceColor): this
    /** @memo */
    caretStyle(value: CaretStyle): this
    /** @memo */
    placeholderColor(value: ResourceColor): this
    /** @memo */
    placeholderFont(value?: Font): this
    /** @memo */
    textFont(value?: Font): this
    /** @memo */
    enterKeyType(value: EnterKeyType): this
    /** @memo */
    onSubmit(value: ((breakpoints: string) => void) | SearchSubmitCallback): this
    /** @memo */
    onChange(value: EditableTextOnChangeCallback): this
    /** @memo */
    onTextSelectionChange(value: OnTextSelectionChangeCallback): this
    /** @memo */
    onContentScroll(value: OnContentScrollCallback): this
    /** @memo */
    onCopy(value: ((breakpoints: string) => void)): this
    /** @memo */
    onCut(value: ((breakpoints: string) => void)): this
    /** @memo */
    onPaste(value: OnPasteCallback): this
    /** @memo */
    copyOption(value: CopyOptions): this
    /** @memo */
    maxLength(value: number): this
    /** @memo */
    textAlign(value: TextAlign): this
    /** @memo */
    enableKeyboardOnFocus(value: boolean): this
    /** @memo */
    selectionMenuHidden(value: boolean): this
    /** @memo */
    minFontSize(value: number | string | Resource): this
    /** @memo */
    maxFontSize(value: number | string | Resource): this
    /** @memo */
    decoration(value: TextDecorationOptions): this
    /** @memo */
    letterSpacing(value: number | string | Resource): this
    /** @memo */
    lineHeight(value: number | string | Resource): this
    /** @memo */
    type(value: SearchType): this
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
    searchButton(value: string, option?: SearchButtonOptions): this
    /** @memo */
    inputFilter(value: ResourceStr, error?: ((breakpoints: string) => void)): this
    /** @memo */
    customKeyboard(value: CustomBuilder, options?: KeyboardOptions): this
    /** @memo */
    _onChangeEvent_value(callback: ((breakpoints: string) => void)): void
}
/** @memo */
export function Search(
  /** @memo */
  style: ((attributes: SearchAttribute) => void) | undefined,
  options?: SearchOptions | undefined, 
  /** @memo */
  content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkSearchComponent()
    })
    NodeAttach<ArkSearchPeer>((): ArkSearchPeer => ArkSearchPeer.create(receiver), (_: ArkSearchPeer) => {
        receiver.setSearchOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
