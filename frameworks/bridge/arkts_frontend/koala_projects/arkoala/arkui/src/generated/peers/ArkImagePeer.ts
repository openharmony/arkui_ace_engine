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
import { nullptr, KPointer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { runtimeType, RuntimeType } from "@koalaui/interop"
import { Serializer } from "./Serializer"
import { ComponentBase } from "../../ComponentBase"
import { PeerNode } from "../../PeerNode"
import { isInstanceOf } from "@koalaui/interop"
import { isResource, isPadding } from "../../utils"
import { ArkUIGeneratedNativeModule } from "../ArkUIGeneratedNativeModule"
import { ArkCommonMethodPeer, ArkCommonMethodAttributes } from "./ArkCommonPeer"
import { CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, CustomBuilder, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, SourceTool, RectResult, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason, PointLightStyle, LightSource } from "./../ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Area, Bias, Font } from "./../ArkUnitsInterfaces"
import { DrawModifier } from "./../ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, FontWeight, FontStyle, ImageFit, CopyOptions, IlluminatedType } from "./../ArkEnumsInterfaces"
import { LengthMetrics } from "./../ArkLengthMetricsMaterialized"
import { ResizableOptions, DrawingLattice, ImageRenderMode, DynamicRangeMode, ImageInterpolation, ImageSourceSize, DrawingColorFilter, ImageErrorCallback, ResolutionQuality, DrawableDescriptor, ImageAttribute, ImageContent } from "./../ArkImageInterfaces"
import { Resource } from "./../ArkResourceInterfaces"
import { FocusBoxStyle, FocusPriority } from "./../ArkFocusInterfaces"
import { TransitionEffect } from "./../ArkTransitionEffectMaterialized"
import { CircleShape } from "./../ArkCircleShapeMaterialized"
import { EllipseShape } from "./../ArkEllipseShapeMaterialized"
import { PathShape } from "./../ArkPathShapeMaterialized"
import { RectShape } from "./../ArkRectShapeMaterialized"
import { ProgressMask } from "./../ArkProgressMaskMaterialized"
import { AttributeModifier } from "./../../handwritten"
import { GestureModifier } from "./../ArkGestureModifierMaterialized"
import { PixelMap } from "./../ArkPixelMapMaterialized"
import { GestureType, GestureMask, GestureInfo, GestureJudgeResult, GestureInterface, TapGestureParameters, PanDirection, SwipeDirection, GestureMode, GestureHandler, GesturePriority, FingerInfo } from "./../ArkGestureInterfaces"
import { TapGestureInterface } from "./../ArkTapGestureInterfaceMaterialized"
import { LongPressGestureInterface } from "./../ArkLongPressGestureInterfaceMaterialized"
import { PanGestureInterface } from "./../ArkPanGestureInterfaceMaterialized"
import { PinchGestureInterface } from "./../ArkPinchGestureInterfaceMaterialized"
import { SwipeGestureInterface } from "./../ArkSwipeGestureInterfaceMaterialized"
import { RotationGestureInterface } from "./../ArkRotationGestureInterfaceMaterialized"
import { GestureGroupInterface } from "./../ArkGestureGroupInterfaceMaterialized"
import { LengthUnit, ShapeSize, PathShapeOptions, RectShapeOptions, RoundRectShapeOptions } from "./../ArkArkuiExternalInterfaces"
import { ClickEvent } from "./../ArkClickEventMaterialized"
import { HoverEvent } from "./../ArkHoverEventMaterialized"
import { MouseEvent } from "./../ArkMouseEventMaterialized"
import { TouchEvent } from "./../ArkTouchEventMaterialized"
import { KeyEvent } from "./../ArkKeyEventMaterialized"
import { ColorMetrics } from "./../ArkColorMetricsMaterialized"
import { ICurve } from "./../ArkICurveMaterialized"
import { DragEvent } from "./../ArkDragEventMaterialized"
import { BaseGestureEvent } from "./../ArkBaseGestureEventMaterialized"
import { PanGestureOptions } from "./../ArkPanGestureOptionsMaterialized"
import { BaseEvent } from "./../ArkBaseEventMaterialized"
import { UnifiedData } from "./../ArkUnifiedDataMaterialized"
import { GestureControl } from "./../ArkGestureControlNamespace"
import { GestureEvent } from "./../ArkGestureEventMaterialized"
import { ColorFilter } from "./../ArkColorFilterMaterialized"
import { ImageAnalyzerConfig, ImageAnalyzerType, ImageAIOptions } from "./../ArkImageCommonInterfaces"
import { ImageAnalyzerController } from "./../ArkImageAnalyzerControllerMaterialized"
import { GestureName, GestureComponent } from "./../shared/generated-utils"
import { CallbackKind } from "./CallbackKind"
import { CallbackTransformer } from "./CallbackTransformer"
import { unsafeCast } from "@koalaui/common"
import { Deserializer, createDeserializer } from "./Deserializer"
import { MaterializedBase, toPeerPtr, wrapCallback } from "@koalaui/interop"
import { DotIndicator } from "./../ArkDotIndicatorBuilder"
import { DigitIndicator } from "./../ArkDigitIndicatorBuilder"
import { SubTabBarStyle } from "./../ArkSubTabBarStyleBuilder"
import { BottomTabBarStyle } from "./../ArkBottomTabBarStyleBuilder"
export class ArkImagePeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkImagePeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._Image_construct(peerId, flags)
        const _peer = new ArkImagePeer(_peerPtr, peerId, "Image", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setImageOptions0Attribute(src: PixelMap | ResourceStr | DrawableDescriptor): void {
        const thisSerializer: Serializer = Serializer.hold()
        let src_type: int32 = RuntimeType.UNDEFINED
        src_type = runtimeType(src)
        if (((RuntimeType.OBJECT) == (src_type)) && ((src!.hasOwnProperty("isEditable")))) {
            thisSerializer.writeInt8(0)
            const src_0 = unsafeCast<PixelMap>(src)
            thisSerializer.writePixelMap(src_0)
        }
        else if ((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type)) {
            thisSerializer.writeInt8(1)
            const src_1 = unsafeCast<ResourceStr>(src)
            let src_1_type: int32 = RuntimeType.UNDEFINED
            src_1_type = runtimeType(src_1)
            if (RuntimeType.STRING == src_1_type) {
                thisSerializer.writeInt8(0)
                const src_1_0 = unsafeCast<string>(src_1)
                thisSerializer.writeString(src_1_0)
            }
            else if (RuntimeType.OBJECT == src_1_type) {
                thisSerializer.writeInt8(1)
                const src_1_1 = unsafeCast<Resource>(src_1)
                thisSerializer.writeResource(src_1_1)
            }
        }
        else if (((RuntimeType.OBJECT) == (src_type)) && ((src!.hasOwnProperty("_DrawableDescriptorStub")))) {
            thisSerializer.writeInt8(2)
            const src_2 = unsafeCast<DrawableDescriptor>(src)
            thisSerializer.writeDrawableDescriptor(src_2)
        }
        ArkUIGeneratedNativeModule._ImageInterface_setImageOptions0(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    setImageOptions1Attribute(src: PixelMap | ResourceStr | DrawableDescriptor | ImageContent): void {
        const thisSerializer: Serializer = Serializer.hold()
        let src_type: int32 = RuntimeType.UNDEFINED
        src_type = runtimeType(src)
        if (((RuntimeType.OBJECT) == (src_type)) && ((src!.hasOwnProperty("isEditable")))) {
            thisSerializer.writeInt8(0)
            const src_0 = unsafeCast<PixelMap>(src)
            thisSerializer.writePixelMap(src_0)
        }
        else if ((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type)) {
            thisSerializer.writeInt8(1)
            const src_1 = unsafeCast<ResourceStr>(src)
            let src_1_type: int32 = RuntimeType.UNDEFINED
            src_1_type = runtimeType(src_1)
            if (RuntimeType.STRING == src_1_type) {
                thisSerializer.writeInt8(0)
                const src_1_0 = unsafeCast<string>(src_1)
                thisSerializer.writeString(src_1_0)
            }
            else if (RuntimeType.OBJECT == src_1_type) {
                thisSerializer.writeInt8(1)
                const src_1_1 = unsafeCast<Resource>(src_1)
                thisSerializer.writeResource(src_1_1)
            }
        }
        else if (((RuntimeType.OBJECT) == (src_type)) && ((src!.hasOwnProperty("_DrawableDescriptorStub")))) {
            thisSerializer.writeInt8(2)
            const src_2 = unsafeCast<DrawableDescriptor>(src)
            thisSerializer.writeDrawableDescriptor(src_2)
        }
        else if (RuntimeType.NUMBER == src_type) {
            thisSerializer.writeInt8(3)
            const src_3 = unsafeCast<ImageContent>(src)
            thisSerializer.writeInt32(src_3)
        }
        ArkUIGeneratedNativeModule._ImageInterface_setImageOptions1(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    setImageOptions2Attribute(src: PixelMap | ResourceStr | DrawableDescriptor, imageAIOptions: ImageAIOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let src_type: int32 = RuntimeType.UNDEFINED
        src_type = runtimeType(src)
        if (((RuntimeType.OBJECT) == (src_type)) && ((src!.hasOwnProperty("isEditable")))) {
            thisSerializer.writeInt8(0)
            const src_0 = unsafeCast<PixelMap>(src)
            thisSerializer.writePixelMap(src_0)
        }
        else if ((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type)) {
            thisSerializer.writeInt8(1)
            const src_1 = unsafeCast<ResourceStr>(src)
            let src_1_type: int32 = RuntimeType.UNDEFINED
            src_1_type = runtimeType(src_1)
            if (RuntimeType.STRING == src_1_type) {
                thisSerializer.writeInt8(0)
                const src_1_0 = unsafeCast<string>(src_1)
                thisSerializer.writeString(src_1_0)
            }
            else if (RuntimeType.OBJECT == src_1_type) {
                thisSerializer.writeInt8(1)
                const src_1_1 = unsafeCast<Resource>(src_1)
                thisSerializer.writeResource(src_1_1)
            }
        }
        else if (((RuntimeType.OBJECT) == (src_type)) && ((src!.hasOwnProperty("_DrawableDescriptorStub")))) {
            thisSerializer.writeInt8(2)
            const src_2 = unsafeCast<DrawableDescriptor>(src)
            thisSerializer.writeDrawableDescriptor(src_2)
        }
        thisSerializer.writeImageAIOptions(imageAIOptions)
        ArkUIGeneratedNativeModule._ImageInterface_setImageOptions2(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    altAttribute(value: string | Resource | PixelMap): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<string>(value)
            thisSerializer.writeString(value_0)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && ((value!.hasOwnProperty("bundleName")))) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_1)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && ((value!.hasOwnProperty("isEditable")))) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<PixelMap>(value)
            thisSerializer.writePixelMap(value_2)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_alt(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    matchTextDirectionAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ImageAttribute_matchTextDirection(this.peer.ptr, +value)
    }
    fitOriginalSizeAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ImageAttribute_fitOriginalSize(this.peer.ptr, +value)
    }
    fillColorAttribute(value: ResourceColor): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.NUMBER) == (value_type)) && ((unsafeCast<int32>(value)) >= (0)) && ((unsafeCast<int32>(value)) <= (11))) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<Color>(value)
            thisSerializer.writeInt32(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<string>(value)
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_fillColor(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    objectFitAttribute(value: ImageFit): void {
        ArkUIGeneratedNativeModule._ImageAttribute_objectFit(this.peer.ptr, value)
    }
    objectRepeatAttribute(value: ImageRepeat): void {
        ArkUIGeneratedNativeModule._ImageAttribute_objectRepeat(this.peer.ptr, value)
    }
    autoResizeAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ImageAttribute_autoResize(this.peer.ptr, +value)
    }
    renderModeAttribute(value: ImageRenderMode): void {
        ArkUIGeneratedNativeModule._ImageAttribute_renderMode(this.peer.ptr, value)
    }
    dynamicRangeModeAttribute(value: DynamicRangeMode): void {
        ArkUIGeneratedNativeModule._ImageAttribute_dynamicRangeMode(this.peer.ptr, value)
    }
    interpolationAttribute(value: ImageInterpolation): void {
        ArkUIGeneratedNativeModule._ImageAttribute_interpolation(this.peer.ptr, value)
    }
    sourceSizeAttribute(value: ImageSourceSize): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeImageSourceSize(value)
        ArkUIGeneratedNativeModule._ImageAttribute_sourceSize(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    syncLoadAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ImageAttribute_syncLoad(this.peer.ptr, +value)
    }
    colorFilterAttribute(value: ColorFilter | DrawingColorFilter): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.OBJECT) == (value_type)) && (value instanceof ColorFilter)) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<ColorFilter>(value)
            thisSerializer.writeColorFilter(value_0)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && ((value!.hasOwnProperty("_DrawingColorFilterStub")))) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<DrawingColorFilter>(value)
            thisSerializer.writeDrawingColorFilter(value_1)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_colorFilter(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    copyOptionAttribute(value: CopyOptions): void {
        ArkUIGeneratedNativeModule._ImageAttribute_copyOption(this.peer.ptr, value)
    }
    draggableAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ImageAttribute_draggable(this.peer.ptr, +value)
    }
    pointLightAttribute(value: PointLightStyle): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writePointLightStyle(value)
        ArkUIGeneratedNativeModule._ImageAttribute_pointLight(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    edgeAntialiasingAttribute(value: number): void {
        ArkUIGeneratedNativeModule._ImageAttribute_edgeAntialiasing(this.peer.ptr, value)
    }
    onCompleteAttribute(value: ((event?: { width: number, height: number, componentWidth: number, componentHeight: number, loadingStatus: number, contentWidth: number, contentHeight: number, contentOffsetX: number, contentOffsetY: number }) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ImageAttribute_onComplete(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onErrorAttribute(value: ImageErrorCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ImageAttribute_onError(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onFinishAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ImageAttribute_onFinish(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    enableAnalyzerAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ImageAttribute_enableAnalyzer(this.peer.ptr, +value)
    }
    analyzerConfigAttribute(value: ImageAnalyzerConfig): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeImageAnalyzerConfig(value)
        ArkUIGeneratedNativeModule._ImageAttribute_analyzerConfig(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    resizableAttribute(value: ResizableOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeResizableOptions(value)
        ArkUIGeneratedNativeModule._ImageAttribute_resizable(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    privacySensitiveAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ImageAttribute_privacySensitive(this.peer.ptr, +value)
    }
    enhancedImageQualityAttribute(value: ResolutionQuality): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeResolutionQuality(value)
        ArkUIGeneratedNativeModule._ImageAttribute_enhancedImageQuality(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ArkImageAttributes extends ArkCommonMethodAttributes {
    alt?: string | Resource | PixelMap
    matchTextDirection?: boolean
    fitOriginalSize?: boolean
    fillColor?: ResourceColor
    objectFit?: ImageFit
    objectRepeat?: ImageRepeat
    autoResize?: boolean
    renderMode?: ImageRenderMode
    dynamicRangeMode?: DynamicRangeMode
    interpolation?: ImageInterpolation
    sourceSize?: ImageSourceSize
    syncLoad?: boolean
    colorFilter?: ColorFilter | DrawingColorFilter
    copyOption?: CopyOptions
    draggable?: boolean
    pointLight?: PointLightStyle
    edgeAntialiasing?: number
    onComplete?: ((event?: { width: number, height: number, componentWidth: number, componentHeight: number, loadingStatus: number, contentWidth: number, contentHeight: number, contentOffsetX: number, contentOffsetY: number }) => void)
    onError?: ImageErrorCallback
    onFinish?: (() => void)
    enableAnalyzer?: boolean
    analyzerConfig?: ImageAnalyzerConfig
    resizable?: ResizableOptions
    privacySensitive?: boolean
    enhancedImageQuality?: ResolutionQuality
}
