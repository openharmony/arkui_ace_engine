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
import { ArkCanvasPeer } from "./peers/ArkCanvasPeer"
import { CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, CustomBuilder, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, SourceTool, RectResult, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason } from "./ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, VoidCallback, PX, VP, FP, LPX, Percentage, Area, Bias, Font, LengthMetricsUnit } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, FontWeight, FontStyle } from "./ArkEnumsInterfaces"
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
import { LengthUnit, ShapeSize, PathShapeOptions, RectShapeOptions, RoundRectShapeOptions } from "./ArkArkuiExternalInterfaces"
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
import { CanvasRenderingContext2D } from "./ArkCanvasRenderingContext2DMaterialized"
import { DrawingRenderingContext } from "./ArkDrawingRenderingContextMaterialized"
import { CanvasAttribute, ImageSmoothingQuality, CanvasLineCap, CanvasLineJoin, CanvasDirection, CanvasTextAlign, CanvasTextBaseline, CanvasFillRule, TextMetrics, Size } from "./ArkCanvasInterfaces"
import { ImageAIOptions, ImageAnalyzerConfig, ImageAnalyzerType } from "./ArkImageCommonInterfaces"
import { CanvasRenderer } from "./ArkCanvasRendererMaterialized"
import { CanvasPath } from "./ArkCanvasPathMaterialized"
import { CanvasGradient } from "./ArkCanvasGradientMaterialized"
import { CanvasPattern } from "./ArkCanvasPatternMaterialized"
import { ImageBitmap } from "./ArkImageBitmapMaterialized"
import { Path2D } from "./ArkPath2DMaterialized"
import { ImageData } from "./ArkImageDataMaterialized"
import { Matrix2D } from "./ArkMatrix2DMaterialized"
import { FrameNode } from "./ArkFrameNodeMaterialized"
import { RenderingContextSettings } from "./ArkRenderingContextSettingsMaterialized"
import { DrawingCanvas } from "./ArkDrawingCanvasMaterialized"
import { ImageAnalyzerController } from "./ArkImageAnalyzerControllerMaterialized"
/** @memo:stable */
export class ArkCanvasComponent extends ArkCommonMethodComponent {
    protected getPeer(): ArkCanvasPeer {
        return (this.peer as ArkCanvasPeer)
    }
    /** @memo */
    public setCanvasOptions(context?: CanvasRenderingContext2D | DrawingRenderingContext | CanvasRenderingContext2D | DrawingRenderingContext | undefined, imageAIOptions?: ImageAIOptions): this {
        if (this.checkPriority("setCanvasOptions")) {
            const context_type = runtimeType(context)
            const imageAIOptions_type = runtimeType(imageAIOptions)
            if (((((RuntimeType.OBJECT) == (context_type)) && (context instanceof CanvasRenderingContext2D)) || (((RuntimeType.OBJECT) == (context_type)) && (context instanceof DrawingRenderingContext))) && (RuntimeType.OBJECT == imageAIOptions_type)) {
                const context_casted = context as (CanvasRenderingContext2D | DrawingRenderingContext)
                const imageAIOptions_casted = imageAIOptions as (ImageAIOptions)
                this.getPeer()?.setCanvasOptions1Attribute(context_casted, imageAIOptions_casted)
                return this
            }
            if (((RuntimeType.OBJECT == context_type) || (RuntimeType.OBJECT == context_type) || (RuntimeType.UNDEFINED == context_type)) && (RuntimeType.UNDEFINED == imageAIOptions_type)) {
                const context_casted = context as (CanvasRenderingContext2D | DrawingRenderingContext | undefined)
                this.getPeer()?.setCanvasOptions0Attribute(context_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public onReady(value: VoidCallback): this {
        if (this.checkPriority("onReady")) {
            const value_casted = value as (VoidCallback)
            this.getPeer()?.onReadyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableAnalyzer(value: boolean): this {
        if (this.checkPriority("enableAnalyzer")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableAnalyzerAttribute(value_casted)
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
export function ArkCanvas(
  /** @memo */
  style: ((attributes: ArkCanvasComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  context?: CanvasRenderingContext2D | DrawingRenderingContext | undefined | CanvasRenderingContext2D | DrawingRenderingContext | undefined, imageAIOptions?: ImageAIOptions | undefined
) {
    const receiver = remember(() => {
        return new ArkCanvasComponent()
    })
    NodeAttach<ArkCanvasPeer>((): ArkCanvasPeer => ArkCanvasPeer.create(receiver), (_: ArkCanvasPeer) => {
        receiver.setCanvasOptions(context,imageAIOptions)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
