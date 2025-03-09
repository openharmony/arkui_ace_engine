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

import { int32, float32, unsafeCast } from "@koalaui/common"
import { KStringPtr, KBoolean, RuntimeType, runtimeType, isInstanceOf } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ComponentBase } from "./../ComponentBase"
import { isResource, isPadding } from "./../utils"
import { ArkCommonMethodComponent } from "./ArkCommon"
import { ArkRichEditorPeer } from "./peers/ArkRichEditorPeer"
import { CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, CustomBuilder, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, SourceTool, RectResult, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason, SelectionOptions, MenuPolicy } from "./ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Area, Bias, Font } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, FontWeight, FontStyle, CopyOptions, BarState, TextDecorationType, TextDecorationStyle, TextAlign, WordBreak, LineBreakStrategy, ImageSpanAlignment, ImageFit } from "./ArkEnumsInterfaces"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { ResizableOptions, DrawingLattice } from "./ArkImageInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { FocusBoxStyle, FocusPriority } from "./ArkFocusInterfaces"
import { TransitionEffect } from "./ArkTransitionEffectMaterialized"
import { CircleShape } from "./ArkCircleShapeMaterialized"
import { EllipseShape } from "./ArkEllipseShapeMaterialized"
import { PathShape } from "./ArkPathShapeMaterialized"
import { RectShape } from "./ArkRectShapeMaterialized"
import { ProgressMask } from "./ArkProgressMaskMaterialized"
import { AttributeModifier } from "./../handwritten"
import { GestureModifier } from "./ArkGestureModifierMaterialized"
import { PixelMap } from "./ArkPixelMapMaterialized"
import { GestureType, GestureMask, GestureInfo, GestureJudgeResult, GestureInterface, TapGestureParameters, PanDirection, SwipeDirection, GestureMode, GestureHandler, GesturePriority, FingerInfo } from "./ArkGestureInterfaces"
import { TapGestureInterface } from "./ArkTapGestureInterfaceMaterialized"
import { LongPressGestureInterface } from "./ArkLongPressGestureInterfaceMaterialized"
import { PanGestureInterface } from "./ArkPanGestureInterfaceMaterialized"
import { PinchGestureInterface } from "./ArkPinchGestureInterfaceMaterialized"
import { SwipeGestureInterface } from "./ArkSwipeGestureInterfaceMaterialized"
import { RotationGestureInterface } from "./ArkRotationGestureInterfaceMaterialized"
import { GestureGroupInterface } from "./ArkGestureGroupInterfaceMaterialized"
import { LengthUnit, ShapeSize, PathShapeOptions, RectShapeOptions, RoundRectShapeOptions, RectWidthStyle, RectHeightStyle } from "./ArkArkuiExternalInterfaces"
import { ClickEvent } from "./ArkClickEventMaterialized"
import { HoverEvent } from "./ArkHoverEventMaterialized"
import { MouseEvent } from "./ArkMouseEventMaterialized"
import { TouchEvent } from "./ArkTouchEventMaterialized"
import { KeyEvent } from "./ArkKeyEventMaterialized"
import { ColorMetrics } from "./ArkColorMetricsMaterialized"
import { ICurve } from "./ArkICurveMaterialized"
import { DragEvent } from "./ArkDragEventMaterialized"
import { BaseGestureEvent } from "./ArkBaseGestureEventMaterialized"
import { PanGestureOptions } from "./ArkPanGestureOptionsMaterialized"
import { BaseEvent } from "./ArkBaseEventMaterialized"
import { UnifiedData } from "./ArkUnifiedDataMaterialized"
import { GestureControl } from "./ArkGestureControlNamespace"
import { GestureEvent } from "./ArkGestureEventMaterialized"
import { PasteEventCallback, SubmitCallback, RichEditorSpanType, RichEditorResponseType, SelectionMenuOptions, RichEditorAttribute, KeyboardOptions, PlaceholderStyle, RichEditorSelection, RichEditorRange, RichEditorInsertValue, RichEditorTextSpanResult, RichEditorDeleteValue, RichEditorChangeValue, CutEvent, CopyEvent, MenuOnAppearCallback, RichEditorImageSpanResult, RichEditorSpanPosition, RichEditorTextStyleResult, RichEditorSymbolSpanStyle, RichEditorParagraphStyle, RichEditorDeleteDirection, RichEditorImageSpanStyleResult, LeadingMarginPlaceholder, RichEditorLayoutStyle, RichEditorOptions, RichEditorStyledStringOptions, RichEditorTextStyle, RichEditorTextSpanOptions, RichEditorImageSpanOptions, RichEditorBuilderSpanOptions, RichEditorSymbolSpanOptions, RichEditorUpdateTextSpanStyleOptions, RichEditorUpdateImageSpanStyleOptions, RichEditorUpdateSymbolSpanStyleOptions, RichEditorParagraphStyleOptions, RichEditorParagraphResult, RichEditorSpan, RichEditorGesture, RichEditorImageSpanStyle, RichEditorSpanStyleOptions } from "./ArkRichEditorInterfaces"
import { TextDataDetectorConfig, OnDidChangeCallback, TextRange, TextDataDetectorType, TextMenuItem, MenuType, DecorationStyleResult, PreviewText, StyledStringChangedListener, PositionWithAffinity, LineMetrics, TextBox, Affinity, StyledStringChangeValue } from "./ArkTextCommonInterfaces"
import { EnterKeyType } from "./ArkTextInputInterfaces"
import { EditMenuOptions } from "./ArkEditMenuOptionsMaterialized"
import { DecorationStyleInterface, StyleOptions, StyledStringKey, SpanStyle, ImageAttachmentLayoutStyle, ImageAttachmentInterface, CustomSpanMeasureInfo, CustomSpanMetrics, CustomSpanDrawInfo, StyledStringValue } from "./ArkStyledStringInterfaces"
import { TextMenuItemId } from "./ArkTextMenuItemIdMaterialized"
import { SymbolEffectStrategy, SymbolRenderingStrategy } from "./ArkSymbolglyphInterfaces"
import { RichEditorController } from "./ArkRichEditorControllerMaterialized"
import { RichEditorStyledStringController } from "./ArkRichEditorStyledStringControllerMaterialized"
import { RichEditorBaseController } from "./ArkRichEditorBaseControllerMaterialized"
import { TextEditControllerEx } from "./ArkTextEditControllerExMaterialized"
import { TextBaseController } from "./ArkTextBaseControllerMaterialized"
import { LayoutManager } from "./ArkLayoutManagerMaterialized"
import { StyledString } from "./ArkStyledStringMaterialized"
import { StyledStringController } from "./ArkStyledStringControllerMaterialized"
import { MutableStyledString } from "./ArkMutableStyledStringMaterialized"
import { ImageAttachment } from "./ArkImageAttachmentMaterialized"
import { CustomSpan } from "./ArkCustomSpanMaterialized"
/** @memo:stable */
export class ArkRichEditorComponent extends ArkCommonMethodComponent {
    protected getPeer(): ArkRichEditorPeer {
        return (this.peer as ArkRichEditorPeer)
    }
    /** @memo */
    public setRichEditorOptions(value: RichEditorOptions | RichEditorStyledStringOptions): this {
        if (this.checkPriority("setRichEditorOptions")) {
            const value_type = runtimeType(value)
            if (RuntimeType.OBJECT == value_type) {
                const value_casted = value as (RichEditorOptions)
                this.getPeer()?.setRichEditorOptions0Attribute(value_casted)
                return this
            }
            if (RuntimeType.OBJECT == value_type) {
                const options_casted = value as (RichEditorStyledStringOptions)
                this.getPeer()?.setRichEditorOptions1Attribute(options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public onReady(value: (() => void)): this {
        if (this.checkPriority("onReady")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onReadyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onSelect(value: ((parameter: RichEditorSelection) => void)): this {
        if (this.checkPriority("onSelect")) {
            const value_casted = value as (((parameter: RichEditorSelection) => void))
            this.getPeer()?.onSelectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onSelectionChange(value: ((parameter: RichEditorRange) => void)): this {
        if (this.checkPriority("onSelectionChange")) {
            const value_casted = value as (((parameter: RichEditorRange) => void))
            this.getPeer()?.onSelectionChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public aboutToIMEInput(value: ((parameter: RichEditorInsertValue) => boolean)): this {
        if (this.checkPriority("aboutToIMEInput")) {
            const value_casted = value as (((parameter: RichEditorInsertValue) => boolean))
            this.getPeer()?.aboutToIMEInputAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onIMEInputComplete(value: ((parameter: RichEditorTextSpanResult) => void)): this {
        if (this.checkPriority("onIMEInputComplete")) {
            const value_casted = value as (((parameter: RichEditorTextSpanResult) => void))
            this.getPeer()?.onIMEInputCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDidIMEInput(value: ((parameter: TextRange) => void)): this {
        if (this.checkPriority("onDidIMEInput")) {
            const value_casted = value as (((parameter: TextRange) => void))
            this.getPeer()?.onDidIMEInputAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public aboutToDelete(value: ((parameter: RichEditorDeleteValue) => boolean)): this {
        if (this.checkPriority("aboutToDelete")) {
            const value_casted = value as (((parameter: RichEditorDeleteValue) => boolean))
            this.getPeer()?.aboutToDeleteAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDeleteComplete(value: (() => void)): this {
        if (this.checkPriority("onDeleteComplete")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onDeleteCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public copyOptions(value: CopyOptions): this {
        if (this.checkPriority("copyOptions")) {
            const value_casted = value as (CopyOptions)
            this.getPeer()?.copyOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onPaste(value: PasteEventCallback): this {
        if (this.checkPriority("onPaste")) {
            const value_casted = value as (PasteEventCallback)
            this.getPeer()?.onPasteAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableDataDetector(value: boolean): this {
        if (this.checkPriority("enableDataDetector")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableDataDetectorAttribute(value_casted)
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
    public dataDetectorConfig(value: TextDataDetectorConfig): this {
        if (this.checkPriority("dataDetectorConfig")) {
            const value_casted = value as (TextDataDetectorConfig)
            this.getPeer()?.dataDetectorConfigAttribute(value_casted)
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
    public selectedBackgroundColor(value: ResourceColor): this {
        if (this.checkPriority("selectedBackgroundColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.selectedBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onEditingChange(value: ((parameter: boolean) => void)): this {
        if (this.checkPriority("onEditingChange")) {
            const value_casted = value as (((parameter: boolean) => void))
            this.getPeer()?.onEditingChangeAttribute(value_casted)
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
    public onSubmit(value: SubmitCallback): this {
        if (this.checkPriority("onSubmit")) {
            const value_casted = value as (SubmitCallback)
            this.getPeer()?.onSubmitAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onWillChange(value: ((parameter: RichEditorChangeValue) => boolean)): this {
        if (this.checkPriority("onWillChange")) {
            const value_casted = value as (((parameter: RichEditorChangeValue) => boolean))
            this.getPeer()?.onWillChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDidChange(value: OnDidChangeCallback): this {
        if (this.checkPriority("onDidChange")) {
            const value_casted = value as (OnDidChangeCallback)
            this.getPeer()?.onDidChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onCut(value: ((parameter: CutEvent) => void)): this {
        if (this.checkPriority("onCut")) {
            const value_casted = value as (((parameter: CutEvent) => void))
            this.getPeer()?.onCutAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onCopy(value: ((parameter: CopyEvent) => void)): this {
        if (this.checkPriority("onCopy")) {
            const value_casted = value as (((parameter: CopyEvent) => void))
            this.getPeer()?.onCopyAttribute(value_casted)
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
    public enableKeyboardOnFocus(value: boolean): this {
        if (this.checkPriority("enableKeyboardOnFocus")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableKeyboardOnFocusAttribute(value_casted)
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
    public barState(value: BarState): this {
        if (this.checkPriority("barState")) {
            const value_casted = value as (BarState)
            this.getPeer()?.barStateAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public bindSelectionMenu(spanType: RichEditorSpanType, content: CustomBuilder, responseType: ResponseType | RichEditorResponseType, options?: SelectionMenuOptions): this {
        if (this.checkPriority("bindSelectionMenu")) {
            const spanType_casted = spanType as (RichEditorSpanType)
            const content_casted = content as (CustomBuilder)
            const responseType_casted = responseType as (ResponseType | RichEditorResponseType)
            const options_casted = options as (SelectionMenuOptions | undefined)
            this.getPeer()?.bindSelectionMenuAttribute(spanType_casted, content_casted, responseType_casted, options_casted)
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
    public placeholder(value: ResourceStr, style?: PlaceholderStyle): this {
        if (this.checkPriority("placeholder")) {
            const value_casted = value as (ResourceStr)
            const style_casted = style as (PlaceholderStyle | undefined)
            this.getPeer()?.placeholderAttribute(value_casted, style_casted)
            return this
        }
        return this
    }
    public applyAttributesFinish(): void {
        // we calls this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

/** @memo */
export function ArkRichEditor(
  /** @memo */
  style: ((attributes: ArkRichEditorComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  value: RichEditorOptions | RichEditorStyledStringOptions
) {
    const receiver = remember(() => {
        return new ArkRichEditorComponent()
    })
    NodeAttach<ArkRichEditorPeer>((): ArkRichEditorPeer => ArkRichEditorPeer.create(receiver), (_: ArkRichEditorPeer) => {
        receiver.setRichEditorOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
