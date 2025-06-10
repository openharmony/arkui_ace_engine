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

import { int32, float32 } from "@koalaui/common"
import { KStringPtr, KBoolean, RuntimeType, runtimeType } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ComponentBase } from "./../ComponentBase"
import { TypeChecker } from "#components"
import { ArkCommonMethodComponent } from "./ArkCommon"
import { ArkSearchPeer } from "./peers/ArkSearchPeer"
import { CommonMethod, Rectangle, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, CustomBuilder, DragItemInfo, UniformDataType, PreDragStatus, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, SymbolGlyphModifier, TextDecorationOptions } from "./ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, Font } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, CopyOptions, TextAlign } from "./ArkEnumsInterfaces"
import { Callback_Array_TouchTestInfo_TouchResult, Callback_ClickEvent_Void, Callback_Boolean_HoverEvent_Void, Callback_MouseEvent_Void, Callback_TouchEvent_Void, Callback_KeyEvent_Void, Callback_KeyEvent_Boolean, Callback_Void, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, Callback_DragEvent_String_Void, Callback_PreDragStatus_Void, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, Callback_TouchEvent_HitTestMode, Literal_Alignment_align, Callback_Boolean_Void, Callback_String_Void, Callback_InsertValue_Boolean, Callback_InsertValue_Void, Callback_DeleteValue_Boolean, Callback_DeleteValue_Void } from "./SyntheticDeclarations"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { ResizableOptions } from "./ArkImageInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { ClickEvent } from "./ArkClickEventMaterialized"
import { HoverEvent } from "./ArkHoverEventMaterialized"
import { MouseEvent } from "./ArkMouseEventMaterialized"
import { TouchEvent } from "./ArkTouchEventMaterialized"
import { KeyEvent } from "./ArkKeyEventMaterialized"
import { FocusBoxStyle, FocusPriority } from "./ArkFocusInterfaces"
import { TransitionEffect } from "./ArkTransitionEffectMaterialized"
import { DragEvent } from "./ArkDragEventMaterialized"
import { CircleShape } from "./ArkCircleShapeMaterialized"
import { EllipseShape } from "./ArkEllipseShapeMaterialized"
import { PathShape } from "./ArkPathShapeMaterialized"
import { RectShape } from "./ArkRectShapeMaterialized"
import { ProgressMask } from "./ArkProgressMaskMaterialized"
import { AttributeModifier } from "./../handwritten"
import { GestureModifier } from "./ArkGestureModifierMaterialized"
import { GestureInfo, GestureJudgeResult, GestureType, GestureMask } from "./ArkGestureInterfaces"
import { BaseGestureEvent } from "./ArkBaseGestureEventMaterialized"
import { PixelMap } from "./ArkPixelMapMaterialized"
import { IconOptions, CancelButtonOptions, CancelButtonSymbolOptions, SearchSubmitCallback, SearchType, SearchButtonOptions, SearchAttribute, SearchOptions } from "./ArkSearchInterfaces"
import { CaretStyle, EditableTextOnChangeCallback, InsertValue, DeleteValue } from "./ArkTextCommonInterfaces"
import { EnterKeyType, OnTextSelectionChangeCallback, OnContentScrollCallback, OnPasteCallback } from "./ArkTextInputInterfaces"
import { EditMenuOptions } from "./ArkEditMenuOptionsMaterialized"
import { KeyboardOptions } from "./ArkRichEditorInterfaces"
/** @memo:stable */
export class ArkSearchComponent extends ArkCommonMethodComponent {
    getPeer(): ArkSearchPeer {
        return (this.peer as ArkSearchPeer)
    }
    /** @memo */
    public setSearchOptions(options?: SearchOptions): this {
        if (this.checkPriority("setSearchOptions")) {
            const options_casted = options as (SearchOptions | undefined)
            this.getPeer()?.setSearchOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontColor(value: ResourceColor): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.fontColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public searchIcon(value: IconOptions | SymbolGlyphModifier): this {
        if (this.checkPriority("searchIcon")) {
            const value_casted = value as (IconOptions | SymbolGlyphModifier)
            this.getPeer()?.searchIconAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions): this {
        if (this.checkPriority("cancelButton")) {
            const value_casted = value as (CancelButtonOptions | CancelButtonSymbolOptions)
            this.getPeer()?.cancelButtonAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public textIndent(value: Dimension): this {
        if (this.checkPriority("textIndent")) {
            const value_casted = value as (Dimension)
            this.getPeer()?.textIndentAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onEditChange(value: ((parameter: boolean) => void)): this {
        if (this.checkPriority("onEditChange")) {
            const value_casted = value as (((parameter: boolean) => void))
            this.getPeer()?.onEditChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selectedBackgroundColor(value: ResourceColor): this {
        if (this.checkPriority("selectedBackgroundColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.selectedBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public caretStyle(value: CaretStyle): this {
        if (this.checkPriority("caretStyle")) {
            const value_casted = value as (CaretStyle)
            this.getPeer()?.caretStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public placeholderColor(value: ResourceColor): this {
        if (this.checkPriority("placeholderColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.placeholderColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public placeholderFont(value?: Font): this {
        if (this.checkPriority("placeholderFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.placeholderFontAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public textFont(value?: Font): this {
        if (this.checkPriority("textFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.textFontAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enterKeyType(value: EnterKeyType): this {
        if (this.checkPriority("enterKeyType")) {
            const value_casted = value as (EnterKeyType)
            this.getPeer()?.enterKeyTypeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onSubmit(value: ((breakpoints: string) => void) | SearchSubmitCallback): this {
        if (this.checkPriority("onSubmit")) {
            const value_type = runtimeType(value)
            if (RuntimeType.FUNCTION == value_type) {
                const value_casted = value as (((breakpoints: string) => void))
                this.getPeer()?.onSubmit0Attribute(value_casted)
                return this
            }
            if (RuntimeType.FUNCTION == value_type) {
                const value_casted = value as (SearchSubmitCallback)
                this.getPeer()?.onSubmit1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public onChange(value: EditableTextOnChangeCallback): this {
        if (this.checkPriority("onChange")) {
            const value_casted = value as (EditableTextOnChangeCallback)
            this.getPeer()?.onChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onTextSelectionChange(value: OnTextSelectionChangeCallback): this {
        if (this.checkPriority("onTextSelectionChange")) {
            const value_casted = value as (OnTextSelectionChangeCallback)
            this.getPeer()?.onTextSelectionChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onContentScroll(value: OnContentScrollCallback): this {
        if (this.checkPriority("onContentScroll")) {
            const value_casted = value as (OnContentScrollCallback)
            this.getPeer()?.onContentScrollAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onCopy(value: ((breakpoints: string) => void)): this {
        if (this.checkPriority("onCopy")) {
            const value_casted = value as (((breakpoints: string) => void))
            this.getPeer()?.onCopyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onCut(value: ((breakpoints: string) => void)): this {
        if (this.checkPriority("onCut")) {
            const value_casted = value as (((breakpoints: string) => void))
            this.getPeer()?.onCutAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onPaste(value: OnPasteCallback): this {
        if (this.checkPriority("onPaste")) {
            const value_casted = value as (OnPasteCallback)
            this.getPeer()?.onPasteAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public copyOption(value: CopyOptions): this {
        if (this.checkPriority("copyOption")) {
            const value_casted = value as (CopyOptions)
            this.getPeer()?.copyOptionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public maxLength(value: number): this {
        if (this.checkPriority("maxLength")) {
            const value_casted = value as (number)
            this.getPeer()?.maxLengthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public textAlign(value: TextAlign): this {
        if (this.checkPriority("textAlign")) {
            const value_casted = value as (TextAlign)
            this.getPeer()?.textAlignAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableKeyboardOnFocus(value: boolean): this {
        if (this.checkPriority("enableKeyboardOnFocus")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableKeyboardOnFocusAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selectionMenuHidden(value: boolean): this {
        if (this.checkPriority("selectionMenuHidden")) {
            const value_casted = value as (boolean)
            this.getPeer()?.selectionMenuHiddenAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public minFontSize(value: number | string | Resource): this {
        if (this.checkPriority("minFontSize")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.minFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public maxFontSize(value: number | string | Resource): this {
        if (this.checkPriority("maxFontSize")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.maxFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public decoration(value: TextDecorationOptions): this {
        if (this.checkPriority("decoration")) {
            const value_casted = value as (TextDecorationOptions)
            this.getPeer()?.decorationAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public letterSpacing(value: number | string | Resource): this {
        if (this.checkPriority("letterSpacing")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.letterSpacingAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public lineHeight(value: number | string | Resource): this {
        if (this.checkPriority("lineHeight")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.lineHeightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public type(value: SearchType): this {
        if (this.checkPriority("type")) {
            const value_casted = value as (SearchType)
            this.getPeer()?.typeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontFeature(value: string): this {
        if (this.checkPriority("fontFeature")) {
            const value_casted = value as (string)
            this.getPeer()?.fontFeatureAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onWillInsert(value: ((parameter: InsertValue) => boolean)): this {
        if (this.checkPriority("onWillInsert")) {
            const value_casted = value as (((parameter: InsertValue) => boolean))
            this.getPeer()?.onWillInsertAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDidInsert(value: ((parameter: InsertValue) => void)): this {
        if (this.checkPriority("onDidInsert")) {
            const value_casted = value as (((parameter: InsertValue) => void))
            this.getPeer()?.onDidInsertAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onWillDelete(value: ((parameter: DeleteValue) => boolean)): this {
        if (this.checkPriority("onWillDelete")) {
            const value_casted = value as (((parameter: DeleteValue) => boolean))
            this.getPeer()?.onWillDeleteAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDidDelete(value: ((parameter: DeleteValue) => void)): this {
        if (this.checkPriority("onDidDelete")) {
            const value_casted = value as (((parameter: DeleteValue) => void))
            this.getPeer()?.onDidDeleteAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public editMenuOptions(value: EditMenuOptions): this {
        if (this.checkPriority("editMenuOptions")) {
            const value_casted = value as (EditMenuOptions)
            this.getPeer()?.editMenuOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enablePreviewText(value: boolean): this {
        if (this.checkPriority("enablePreviewText")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enablePreviewTextAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableHapticFeedback(value: boolean): this {
        if (this.checkPriority("enableHapticFeedback")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableHapticFeedbackAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public searchButton(value: string, option?: SearchButtonOptions): this {
        if (this.checkPriority("searchButton")) {
            const value_casted = value as (string)
            const option_casted = option as (SearchButtonOptions | undefined)
            this.getPeer()?.searchButtonAttribute(value_casted, option_casted)
            return this
        }
        return this
    }
    /** @memo */
    public inputFilter(value: ResourceStr, error?: ((breakpoints: string) => void)): this {
        if (this.checkPriority("inputFilter")) {
            const value_casted = value as (ResourceStr)
            const error_casted = error as (((breakpoints: string) => void) | undefined)
            this.getPeer()?.inputFilterAttribute(value_casted, error_casted)
            return this
        }
        return this
    }
    /** @memo */
    public customKeyboard(value: CustomBuilder, options?: KeyboardOptions): this {
        if (this.checkPriority("customKeyboard")) {
            const value_casted = value as (CustomBuilder)
            const options_casted = options as (KeyboardOptions | undefined)
            this.getPeer()?.customKeyboardAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public _onChangeEvent_value(callback: ((breakpoints: string) => void)): void {
        if (this.checkPriority("_onChangeEvent_value")) {
            const callback_casted = callback as (((breakpoints: string) => void))
            this.getPeer()?._onChangeEvent_valueAttribute(callback_casted)
            return
        }
        return
    }
    public applyAttributesFinish(): void {
        // we calls this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

/** @memo */
export function ArkSearch(
  /** @memo */
  style: ((attributes: ArkSearchComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  options?: SearchOptions | undefined
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
