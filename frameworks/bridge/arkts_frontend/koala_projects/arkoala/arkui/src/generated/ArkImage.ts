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
import { ArkImagePeer } from "./peers/ArkImagePeer"
import { CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, CustomBuilder, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, SourceTool, RectResult, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason, PointLightStyle, LightSource } from "./ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Area, Bias, Font } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, FontWeight, FontStyle, ImageFit, CopyOptions, IlluminatedType } from "./ArkEnumsInterfaces"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { ResizableOptions, DrawingLattice, ImageRenderMode, DynamicRangeMode, ImageInterpolation, ImageSourceSize, DrawingColorFilter, ImageErrorCallback, ResolutionQuality, DrawableDescriptor, ImageAttribute, ImageContent } from "./ArkImageInterfaces"
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
import { ColorFilter } from "./ArkColorFilterMaterialized"
import { ImageAnalyzerConfig, ImageAnalyzerType, ImageAIOptions } from "./ArkImageCommonInterfaces"
import { ImageAnalyzerController } from "./ArkImageAnalyzerControllerMaterialized"
/** @memo:stable */
export class ArkImageComponent extends ArkCommonMethodComponent {
    protected getPeer(): ArkImagePeer {
        return (this.peer as ArkImagePeer)
    }
    /** @memo */
    public setImageOptions(src: PixelMap | ResourceStr | DrawableDescriptor | PixelMap | ResourceStr | DrawableDescriptor | ImageContent, imageAIOptions?: ImageAIOptions): this {
        if (this.checkPriority("setImageOptions")) {
            const src_type = runtimeType(src)
            const imageAIOptions_type = runtimeType(imageAIOptions)
            if (((((RuntimeType.OBJECT) == (src_type)) && ((src!.hasOwnProperty("isEditable")))) || ((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type)) || (((RuntimeType.OBJECT) == (src_type)) && ((src!.hasOwnProperty("_DrawableDescriptorStub"))))) && (RuntimeType.UNDEFINED == imageAIOptions_type)) {
                const src_casted = src as (PixelMap | ResourceStr | DrawableDescriptor)
                this.getPeer()?.setImageOptions0Attribute(src_casted)
                return this
            }
            if (((((RuntimeType.OBJECT) == (src_type)) && ((src!.hasOwnProperty("isEditable")))) || ((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type)) || (((RuntimeType.OBJECT) == (src_type)) && ((src!.hasOwnProperty("_DrawableDescriptorStub"))))) && (RuntimeType.OBJECT == imageAIOptions_type)) {
                const src_casted = src as (PixelMap | ResourceStr | DrawableDescriptor)
                const imageAIOptions_casted = imageAIOptions as (ImageAIOptions)
                this.getPeer()?.setImageOptions2Attribute(src_casted, imageAIOptions_casted)
                return this
            }
            if (((((RuntimeType.OBJECT) == (src_type)) && ((src!.hasOwnProperty("isEditable")))) || ((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type)) || (((RuntimeType.OBJECT) == (src_type)) && ((src!.hasOwnProperty("_DrawableDescriptorStub")))) || (RuntimeType.NUMBER == src_type)) && (RuntimeType.UNDEFINED == imageAIOptions_type)) {
                const src_casted = src as (PixelMap | ResourceStr | DrawableDescriptor | ImageContent)
                this.getPeer()?.setImageOptions1Attribute(src_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public alt(value: string | Resource | PixelMap): this {
        if (this.checkPriority("alt")) {
            const value_casted = value as (string | Resource | PixelMap)
            this.getPeer()?.altAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public matchTextDirection(value: boolean): this {
        if (this.checkPriority("matchTextDirection")) {
            const value_casted = value as (boolean)
            this.getPeer()?.matchTextDirectionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fitOriginalSize(value: boolean): this {
        if (this.checkPriority("fitOriginalSize")) {
            const value_casted = value as (boolean)
            this.getPeer()?.fitOriginalSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fillColor(value: ResourceColor): this {
        if (this.checkPriority("fillColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.fillColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public objectFit(value: ImageFit): this {
        if (this.checkPriority("objectFit")) {
            const value_casted = value as (ImageFit)
            this.getPeer()?.objectFitAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public objectRepeat(value: ImageRepeat): this {
        if (this.checkPriority("objectRepeat")) {
            const value_casted = value as (ImageRepeat)
            this.getPeer()?.objectRepeatAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public autoResize(value: boolean): this {
        if (this.checkPriority("autoResize")) {
            const value_casted = value as (boolean)
            this.getPeer()?.autoResizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public renderMode(value: ImageRenderMode): this {
        if (this.checkPriority("renderMode")) {
            const value_casted = value as (ImageRenderMode)
            this.getPeer()?.renderModeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public dynamicRangeMode(value: DynamicRangeMode): this {
        if (this.checkPriority("dynamicRangeMode")) {
            const value_casted = value as (DynamicRangeMode)
            this.getPeer()?.dynamicRangeModeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public interpolation(value: ImageInterpolation): this {
        if (this.checkPriority("interpolation")) {
            const value_casted = value as (ImageInterpolation)
            this.getPeer()?.interpolationAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public sourceSize(value: ImageSourceSize): this {
        if (this.checkPriority("sourceSize")) {
            const value_casted = value as (ImageSourceSize)
            this.getPeer()?.sourceSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public syncLoad(value: boolean): this {
        if (this.checkPriority("syncLoad")) {
            const value_casted = value as (boolean)
            this.getPeer()?.syncLoadAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public colorFilter(value: ColorFilter | DrawingColorFilter): this {
        if (this.checkPriority("colorFilter")) {
            const value_casted = value as (ColorFilter | DrawingColorFilter)
            this.getPeer()?.colorFilterAttribute(value_casted)
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
    public draggable(value: boolean): this {
        if (this.checkPriority("draggable")) {
            const value_casted = value as (boolean)
            this.getPeer()?.draggableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public pointLight(value: PointLightStyle): this {
        if (this.checkPriority("pointLight")) {
            const value_casted = value as (PointLightStyle)
            this.getPeer()?.pointLightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public edgeAntialiasing(value: number): this {
        if (this.checkPriority("edgeAntialiasing")) {
            const value_casted = value as (number)
            this.getPeer()?.edgeAntialiasingAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onComplete(value: ((event?: { width: number, height: number, componentWidth: number, componentHeight: number, loadingStatus: number, contentWidth: number, contentHeight: number, contentOffsetX: number, contentOffsetY: number }) => void)): this {
        if (this.checkPriority("onComplete")) {
            const value_casted = value as (((event?: { width: number, height: number, componentWidth: number, componentHeight: number, loadingStatus: number, contentWidth: number, contentHeight: number, contentOffsetX: number, contentOffsetY: number }) => void))
            this.getPeer()?.onCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onError(value: ImageErrorCallback): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (ImageErrorCallback)
            this.getPeer()?.onErrorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onFinish(value: (() => void)): this {
        if (this.checkPriority("onFinish")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onFinishAttribute(value_casted)
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
    /** @memo */
    public analyzerConfig(value: ImageAnalyzerConfig): this {
        if (this.checkPriority("analyzerConfig")) {
            const value_casted = value as (ImageAnalyzerConfig)
            this.getPeer()?.analyzerConfigAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public resizable(value: ResizableOptions): this {
        if (this.checkPriority("resizable")) {
            const value_casted = value as (ResizableOptions)
            this.getPeer()?.resizableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public privacySensitive(value: boolean): this {
        if (this.checkPriority("privacySensitive")) {
            const value_casted = value as (boolean)
            this.getPeer()?.privacySensitiveAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enhancedImageQuality(value: ResolutionQuality): this {
        if (this.checkPriority("enhancedImageQuality")) {
            const value_casted = value as (ResolutionQuality)
            this.getPeer()?.enhancedImageQualityAttribute(value_casted)
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
export function ArkImage(
  /** @memo */
  style: ((attributes: ArkImageComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  src: PixelMap | ResourceStr | DrawableDescriptor | PixelMap | ResourceStr | DrawableDescriptor | ImageContent, imageAIOptions?: ImageAIOptions | undefined
) {
    const receiver = remember(() => {
        return new ArkImageComponent()
    })
    NodeAttach<ArkImagePeer>((): ArkImagePeer => ArkImagePeer.create(receiver), (_: ArkImagePeer) => {
        receiver.setImageOptions(src,imageAIOptions)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
