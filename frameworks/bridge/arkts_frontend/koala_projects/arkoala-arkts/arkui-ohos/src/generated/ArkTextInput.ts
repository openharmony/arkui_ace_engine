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
import { ComponentBase } from "../ComponentBase"
import { TypeChecker } from "#components"
import { ArkCommonMethodComponent } from "./ArkCommon"
import { ArkTextInputPeer } from "./peers/ArkTextInputPeer"
import { CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, TextDecorationOptions, InputCounterOptions } from "./../component/common"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, Font } from "./../component/units"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, TextOverflow, FontStyle, FontWeight, CopyOptions, TextAlign, TextContentStyle, BarState, WordBreak, LineBreakStrategy, TextHeightAdaptivePolicy } from "./../component/enums"
import { LengthMetrics } from "../Graphics"
import { ResizableOptions } from "./../component/image"
import { Resource } from "global/resource";
import { Callback_Void } from "./../component/abilityComponent"
import { FocusBoxStyle, FocusPriority } from "./../component/focus"
import { CircleShape } from "./ArkCircleShapeMaterialized"
import { EllipseShape } from "./ArkEllipseShapeMaterialized"
import { PathShape } from "./ArkPathShapeMaterialized"
import { RectShape } from "./ArkRectShapeMaterialized"
import { AttributeModifier } from "./../component/common" 
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureType, GestureMask } from "./../component/gesture"
import { PixelMap } from "./ArkPixelMapMaterialized"
import { InputType, EnterKeyType, OnSubmitCallback, OnTextSelectionChangeCallback, OnContentScrollCallback, OnPasteCallback, TextInputStyle, PasswordIcon, UnderlineColor, TextInputAttribute, TextInputOptions } from "./../component/textInput"
import { ContentType } from "./../component/textArea"
import { Callback_Boolean_Void } from "./../component/checkbox"
import { EditableTextOnChangeCallback, CaretStyle, InsertValue, DeleteValue, EditMenuOptions } from "./../component/textCommon"
import { Callback_String_Void } from "./../component/gridRow"
import { CancelButtonOptions, CancelButtonSymbolOptions, Callback_InsertValue_Boolean, Callback_InsertValue_Void, Callback_DeleteValue_Boolean, Callback_DeleteValue_Void } from "./../component/search"
import { KeyboardOptions } from "./../component/richEditor"
import { Callback_ResourceStr_Void } from "./../component/select"
/** @memo:stable */
export class ArkTextInputComponent extends ArkCommonMethodComponent implements TextInputAttribute {
    getPeer(): ArkTextInputPeer {
        return (this.peer as ArkTextInputPeer)
    }
    /** @memo */
    public setTextInputOptions(value?: TextInputOptions): this {
        if (this.checkPriority("setTextInputOptions")) {
            const value_casted = value as (TextInputOptions | undefined)
            this.getPeer()?.setTextInputOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public type(value: InputType): this {
        if (this.checkPriority("type")) {
            const value_casted = value as (InputType)
            this.getPeer()?.typeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public contentType(value: ContentType): this {
        if (this.checkPriority("contentType")) {
            const value_casted = value as (ContentType)
            this.getPeer()?.contentTypeAttribute(value_casted)
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
    public textOverflow(value: TextOverflow): this {
        if (this.checkPriority("textOverflow")) {
            const value_casted = value as (TextOverflow)
            this.getPeer()?.textOverflowAttribute(value_casted)
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
    public placeholderFont(value?: Font): this {
        if (this.checkPriority("placeholderFont")) {
            const value_casted = value as (Font | undefined)
            this.getPeer()?.placeholderFontAttribute(value_casted)
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
    public caretColor(value: ResourceColor): this {
        if (this.checkPriority("caretColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.caretColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onEditChanged(value: ((parameter: boolean) => void)): this {
        if (this.checkPriority("onEditChanged")) {
            const value_casted = value as (((parameter: boolean) => void))
            this.getPeer()?.onEditChangedAttribute(value_casted)
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
    public onSubmit(value: OnSubmitCallback): this {
        if (this.checkPriority("onSubmit")) {
            const value_casted = value as (OnSubmitCallback)
            this.getPeer()?.onSubmitAttribute(value_casted)
            return this
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
    public maxLength(value: number): this {
        if (this.checkPriority("maxLength")) {
            const value_casted = value as (number)
            this.getPeer()?.maxLengthAttribute(value_casted)
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
    public fontSize(value: Length): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (Length)
            this.getPeer()?.fontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontStyle(value: FontStyle): this {
        if (this.checkPriority("fontStyle")) {
            const value_casted = value as (FontStyle)
            this.getPeer()?.fontStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontWeight(value: number | FontWeight | string): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (number | FontWeight | string)
            this.getPeer()?.fontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontFamily(value: ResourceStr): this {
        if (this.checkPriority("fontFamily")) {
            const value_casted = value as (ResourceStr)
            this.getPeer()?.fontFamilyAttribute(value_casted)
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
    public showPasswordIcon(value: boolean): this {
        if (this.checkPriority("showPasswordIcon")) {
            const value_casted = value as (boolean)
            this.getPeer()?.showPasswordIconAttribute(value_casted)
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
    public style(value: TextInputStyle | TextContentStyle): this {
        if (this.checkPriority("style")) {
            const value_casted = value as (TextInputStyle | TextContentStyle)
            this.getPeer()?.styleAttribute(value_casted)
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
    public selectedBackgroundColor(value: ResourceColor): this {
        if (this.checkPriority("selectedBackgroundColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.selectedBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public caretPosition(value: number): this {
        if (this.checkPriority("caretPosition")) {
            const value_casted = value as (number)
            this.getPeer()?.caretPositionAttribute(value_casted)
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
    public passwordIcon(value: PasswordIcon): this {
        if (this.checkPriority("passwordIcon")) {
            const value_casted = value as (PasswordIcon)
            this.getPeer()?.passwordIconAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public showError(value?: ResourceStr): this {
        if (this.checkPriority("showError")) {
            const value_casted = value as (ResourceStr | undefined)
            this.getPeer()?.showErrorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public showUnit(value: CustomBuilder): this {
        if (this.checkPriority("showUnit")) {
            const value_casted = value as (CustomBuilder)
            this.getPeer()?.showUnitAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public showUnderline(value: boolean): this {
        if (this.checkPriority("showUnderline")) {
            const value_casted = value as (boolean)
            this.getPeer()?.showUnderlineAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public underlineColor(value?: ResourceColor | UnderlineColor): this {
        if (this.checkPriority("underlineColor")) {
            const value_casted = value as (ResourceColor | UnderlineColor | undefined)
            this.getPeer()?.underlineColorAttribute(value_casted)
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
    public barState(value: BarState): this {
        if (this.checkPriority("barState")) {
            const value_casted = value as (BarState)
            this.getPeer()?.barStateAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public maxLines(value: number): this {
        if (this.checkPriority("maxLines")) {
            const value_casted = value as (number)
            this.getPeer()?.maxLinesAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public wordBreak(value: WordBreak): this {
        if (this.checkPriority("wordBreak")) {
            const value_casted = value as (WordBreak)
            this.getPeer()?.wordBreakAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public lineBreakStrategy(value: LineBreakStrategy): this {
        if (this.checkPriority("lineBreakStrategy")) {
            const value_casted = value as (LineBreakStrategy)
            this.getPeer()?.lineBreakStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public cancelButton(value: CancelButtonOptions | CancelButtonSymbolOptions): this {
        if (this.checkPriority("cancelButton")) {
            const value_type = runtimeType(value)
            if (TypeChecker.isCancelButtonOptions(value, true, true)) {
                const value_casted = value as (CancelButtonOptions)
                this.getPeer()?.cancelButton0Attribute(value_casted)
                return this
            }
            if (TypeChecker.isCancelButtonSymbolOptions(value, true, true)) {
                const value_casted = value as (CancelButtonSymbolOptions)
                this.getPeer()?.cancelButton1Attribute(value_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public selectAll(value: boolean): this {
        if (this.checkPriority("selectAll")) {
            const value_casted = value as (boolean)
            this.getPeer()?.selectAllAttribute(value_casted)
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
    public heightAdaptivePolicy(value: TextHeightAdaptivePolicy): this {
        if (this.checkPriority("heightAdaptivePolicy")) {
            const value_casted = value as (TextHeightAdaptivePolicy)
            this.getPeer()?.heightAdaptivePolicyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableAutoFill(value: boolean): this {
        if (this.checkPriority("enableAutoFill")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableAutoFillAttribute(value_casted)
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
    public passwordRules(value: string): this {
        if (this.checkPriority("passwordRules")) {
            const value_casted = value as (string)
            this.getPeer()?.passwordRulesAttribute(value_casted)
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
    public showPassword(value: boolean): this {
        if (this.checkPriority("showPassword")) {
            const value_casted = value as (boolean)
            this.getPeer()?.showPasswordAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onSecurityStateChange(value: ((parameter: boolean) => void)): this {
        if (this.checkPriority("onSecurityStateChange")) {
            const value_casted = value as (((parameter: boolean) => void))
            this.getPeer()?.onSecurityStateChangeAttribute(value_casted)
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
    public showCounter(value: boolean, options?: InputCounterOptions): this {
        if (this.checkPriority("showCounter")) {
            const value_casted = value as (boolean)
            const options_casted = options as (InputCounterOptions | undefined)
            this.getPeer()?.showCounterAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public _onChangeEvent_text(callback: ((value: ResourceStr) => void)): void {
        if (this.checkPriority("_onChangeEvent_text")) {
            const callback_casted = callback as (((value: ResourceStr) => void))
            this.getPeer()?._onChangeEvent_textAttribute(callback_casted)
            return
        }
        return
    }
    public applyAttributesFinish(): void {
        // we calls this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
