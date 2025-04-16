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

import { StyledString, StyledStringInternal, DecorationStyleInterface } from "./styledString"
import { LayoutManager, LayoutManagerInternal, TextDataDetectorConfig, EditMenuOptions, FontSettingOptions } from "./textCommon"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, float32, int64 } from "@koalaui/common"
import { Serializer } from "./../generated/peers/Serializer"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { Deserializer } from "./../generated/peers/Deserializer"
import { CallbackTransformer } from "./../generated/peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { TextOverflow, HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, FontStyle, FontWeight, TextAlign, TextCase, CopyOptions, TextHeightAdaptivePolicy, WordBreak, LineBreakStrategy, EllipsisMode, TextSelectableMode } from "./enums"
import { Resource } from "global/resource";
import { CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./common"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, Font } from "./units"
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
import { Callback_String_Void } from "./gridRow"
import { Callback_Number_Number_Void } from "./grid"
import { SelectionMenuOptions } from "./richEditor"
import { ArkTextComponent } from "./../generated/ArkText"
import { ArkTextPeer } from "./../generated/peers/ArkTextPeer"
export class TextControllerInternal {
    public static fromPtr(ptr: KPointer): TextController {
        const obj : TextController = new TextController()
        obj.peer = new Finalizable(ptr, TextController.getFinalizer())
        return obj
    }
}
export class TextController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_textcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._TextController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = TextController.ctor_textcontroller()
        this.peer = new Finalizable(ctorPtr, TextController.getFinalizer())
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
export interface TextOverflowOptions {
    overflow: TextOverflow;
}
export enum TextSpanType {
    TEXT = 0,
    IMAGE = 1,
    MIXED = 2
}
export enum TextResponseType {
    RIGHT_CLICK = 0,
    LONG_PRESS = 1,
    SELECT = 2
}
export interface TextOptions {
    controller: TextController;
}
/** @memo:stable */
export interface TextAttribute extends CommonMethod {
    /** @memo */
    setTextOptions(content?: string | Resource, value?: TextOptions): this
    /** @memo */
    font(fontValue: Font, options?: FontSettingOptions): this
    /** @memo */
    fontColor(value: ResourceColor): this
    /** @memo */
    fontSize(value: number | string | Resource): this
    /** @memo */
    minFontSize(value: number | string | Resource): this
    /** @memo */
    maxFontSize(value: number | string | Resource): this
    /** @memo */
    minFontScale(value: number | Resource): this
    /** @memo */
    maxFontScale(value: number | Resource): this
    /** @memo */
    fontStyle(value: FontStyle): this
    /** @memo */
    fontWeight(weight: number | FontWeight | string, options?: FontSettingOptions): this
    /** @memo */
    lineSpacing(value: LengthMetrics): this
    /** @memo */
    textAlign(value: TextAlign): this
    /** @memo */
    lineHeight(value: number | string | Resource): this
    /** @memo */
    textOverflow(value: TextOverflowOptions): this
    /** @memo */
    fontFamily(value: string | Resource): this
    /** @memo */
    maxLines(value: number): this
    /** @memo */
    decoration(value: DecorationStyleInterface): this
    /** @memo */
    letterSpacing(value: number | string): this
    /** @memo */
    textCase(value: TextCase): this
    /** @memo */
    baselineOffset(value: number | string): this
    /** @memo */
    copyOption(value: CopyOptions): this
    /** @memo */
    draggable(value: boolean): this
    /** @memo */
    textShadow(value: ShadowOptions | Array<ShadowOptions>): this
    /** @memo */
    heightAdaptivePolicy(value: TextHeightAdaptivePolicy): this
    /** @memo */
    textIndent(value: Length): this
    /** @memo */
    wordBreak(value: WordBreak): this
    /** @memo */
    lineBreakStrategy(value: LineBreakStrategy): this
    /** @memo */
    onCopy(value: ((breakpoints: string) => void)): this
    /** @memo */
    caretColor(value: ResourceColor): this
    /** @memo */
    selectedBackgroundColor(value: ResourceColor): this
    /** @memo */
    ellipsisMode(value: EllipsisMode): this
    /** @memo */
    enableDataDetector(value: boolean): this
    /** @memo */
    dataDetectorConfig(value: TextDataDetectorConfig): this
    /** @memo */
    onTextSelectionChange(value: ((first: number,last: number) => void)): this
    /** @memo */
    fontFeature(value: string): this
    /** @memo */
    privacySensitive(value: boolean): this
    /** @memo */
    textSelectable(value: TextSelectableMode): this
    /** @memo */
    editMenuOptions(value: EditMenuOptions): this
    /** @memo */
    halfLeading(value: boolean): this
    /** @memo */
    enableHapticFeedback(value: boolean): this
    /** @memo */
    selection(selectionStart: number, selectionEnd: number): this
    /** @memo */
    bindSelectionMenu(spanType: TextSpanType, content: CustomBuilder, responseType: TextResponseType, options?: SelectionMenuOptions): this
}
/** @memo */
export function Text(
  /** @memo */
  style: ((attributes: TextAttribute) => void) | undefined,
  content?: string | Resource | undefined, value?: TextOptions | undefined, 
  /** @memo */
  content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkTextComponent()
    })
    NodeAttach<ArkTextPeer>((): ArkTextPeer => ArkTextPeer.create(receiver), (_: ArkTextPeer) => {
        receiver.setTextOptions(content,value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
