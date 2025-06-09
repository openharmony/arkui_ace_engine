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
import { ArkUIGeneratedNativeModule } from "#components"
import { ArkCommonMethodPeer, ArkCommonMethodAttributes } from "./ArkCommonPeer"
import { CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, PointLightStyle } from "./../../component/common"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, ColorFilter, PX, VP, FP, LPX, Percentage } from "./../../component/units"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, ImageFit, CopyOptions } from "./../../component/enums"
import { LengthMetrics } from "../../Graphics"
import { ResizableOptions, ImageRenderMode, DynamicRangeMode, ImageInterpolation, ImageSourceSize, DrawingColorFilter, Callback_Type_ImageAttribute_onComplete_callback_event_Void, Type_ImageAttribute_onComplete_callback_event, ImageErrorCallback, ResolutionQuality, DrawableDescriptor, ImageAttribute, ImageContent } from "./../../component/image"
import { Resource } from "global/resource";
import { Callback_Void } from "./../../component/abilityComponent"
import { FocusBoxStyle, FocusPriority } from "./../../component/focus"
import { CircleShape } from "./../ArkCircleShapeMaterialized"
import { EllipseShape } from "./../ArkEllipseShapeMaterialized"
import { PathShape } from "./../ArkPathShapeMaterialized"
import { RectShape } from "./../ArkRectShapeMaterialized"
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureType, GestureMask, TapGestureInterface, LongPressGestureInterface, PanGestureInterface, PinchGestureInterface, SwipeGestureInterface, RotationGestureInterface, GestureGroupInterface } from "./../../component/gesture"
import { PixelMap } from "./../ArkPixelMapMaterialized"
import { ImageAnalyzerConfig, ImageAIOptions } from "./../../component/imageCommon"
import { CallbackKind } from "./CallbackKind"
import { CallbackTransformer } from "./CallbackTransformer"
import { TypeChecker } from "#components"
import { MaterializedBase, toPeerPtr, wrapCallback } from "@koalaui/interop"
export class ArkImagePeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkImagePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Image_construct(peerId, flags)
        const _peer  = new ArkImagePeer(_peerPtr, peerId, "Image", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setImageOptions0Attribute(src: PixelMap | ResourceStr | DrawableDescriptor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let src_type : int32 = RuntimeType.UNDEFINED
        src_type = runtimeType(src)
        if (TypeChecker.isPixelMap(src, false, false)) {
            thisSerializer.writeInt8(0 as int32)
            const src_0  = src as PixelMap
            thisSerializer.writePixelMap(src_0)
        }
        else if ((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type)) {
            thisSerializer.writeInt8(1 as int32)
            const src_1  = src as ResourceStr
            let src_1_type : int32 = RuntimeType.UNDEFINED
            src_1_type = runtimeType(src_1)
            if (RuntimeType.STRING == src_1_type) {
                thisSerializer.writeInt8(0 as int32)
                const src_1_0  = src_1 as string
                thisSerializer.writeString(src_1_0)
            }
            else if (RuntimeType.OBJECT == src_1_type) {
                thisSerializer.writeInt8(1 as int32)
                const src_1_1  = src_1 as Resource
                thisSerializer.writeResource(src_1_1)
            }
        }
        else if (TypeChecker.isDrawableDescriptor(src, false)) {
            thisSerializer.writeInt8(2 as int32)
            const src_2  = src as DrawableDescriptor
            thisSerializer.writeDrawableDescriptor(src_2)
        }
        ArkUIGeneratedNativeModule._ImageInterface_setImageOptions0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setImageOptions1Attribute(src: PixelMap | ResourceStr | DrawableDescriptor | ImageContent): void {
        const thisSerializer : Serializer = Serializer.hold()
        let src_type : int32 = RuntimeType.UNDEFINED
        src_type = runtimeType(src)
        if (TypeChecker.isPixelMap(src, false, false)) {
            thisSerializer.writeInt8(0 as int32)
            const src_0  = src as PixelMap
            thisSerializer.writePixelMap(src_0)
        }
        else if ((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type)) {
            thisSerializer.writeInt8(1 as int32)
            const src_1  = src as ResourceStr
            let src_1_type : int32 = RuntimeType.UNDEFINED
            src_1_type = runtimeType(src_1)
            if (RuntimeType.STRING == src_1_type) {
                thisSerializer.writeInt8(0 as int32)
                const src_1_0  = src_1 as string
                thisSerializer.writeString(src_1_0)
            }
            else if (RuntimeType.OBJECT == src_1_type) {
                thisSerializer.writeInt8(1 as int32)
                const src_1_1  = src_1 as Resource
                thisSerializer.writeResource(src_1_1)
            }
        }
        else if (TypeChecker.isDrawableDescriptor(src, false)) {
            thisSerializer.writeInt8(2 as int32)
            const src_2  = src as DrawableDescriptor
            thisSerializer.writeDrawableDescriptor(src_2)
        }
        else if (TypeChecker.isImageContent(src)) {
            thisSerializer.writeInt8(3 as int32)
            const src_3  = src as ImageContent
            thisSerializer.writeInt32(src_3.valueOf())
        }
        ArkUIGeneratedNativeModule._ImageInterface_setImageOptions1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setImageOptions2Attribute(src: PixelMap | ResourceStr | DrawableDescriptor, imageAIOptions: ImageAIOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let src_type : int32 = RuntimeType.UNDEFINED
        src_type = runtimeType(src)
        if (TypeChecker.isPixelMap(src, false, false)) {
            thisSerializer.writeInt8(0 as int32)
            const src_0  = src as PixelMap
            thisSerializer.writePixelMap(src_0)
        }
        else if ((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type)) {
            thisSerializer.writeInt8(1 as int32)
            const src_1  = src as ResourceStr
            let src_1_type : int32 = RuntimeType.UNDEFINED
            src_1_type = runtimeType(src_1)
            if (RuntimeType.STRING == src_1_type) {
                thisSerializer.writeInt8(0 as int32)
                const src_1_0  = src_1 as string
                thisSerializer.writeString(src_1_0)
            }
            else if (RuntimeType.OBJECT == src_1_type) {
                thisSerializer.writeInt8(1 as int32)
                const src_1_1  = src_1 as Resource
                thisSerializer.writeResource(src_1_1)
            }
        }
        else if (TypeChecker.isDrawableDescriptor(src, false)) {
            thisSerializer.writeInt8(2 as int32)
            const src_2  = src as DrawableDescriptor
            thisSerializer.writeDrawableDescriptor(src_2)
        }
        thisSerializer.writeImageAIOptions(imageAIOptions)
        ArkUIGeneratedNativeModule._ImageInterface_setImageOptions2(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    altAttribute(value: string | Resource | PixelMap): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (TypeChecker.isResource(value, false, false, false, false, false)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Resource
            thisSerializer.writeResource(value_1)
        }
        else if (TypeChecker.isPixelMap(value, false, false)) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as PixelMap
            thisSerializer.writePixelMap(value_2)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_alt(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    matchTextDirectionAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ImageAttribute_matchTextDirection(this.peer.ptr, value ? 1 : 0)
    }
    fitOriginalSizeAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ImageAttribute_fitOriginalSize(this.peer.ptr, value ? 1 : 0)
    }
    fillColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(value_0.valueOf())
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_fillColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    objectFitAttribute(value: ImageFit): void {
        ArkUIGeneratedNativeModule._ImageAttribute_objectFit(this.peer.ptr, value.valueOf())
    }
    objectRepeatAttribute(value: ImageRepeat): void {
        ArkUIGeneratedNativeModule._ImageAttribute_objectRepeat(this.peer.ptr, value.valueOf())
    }
    autoResizeAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ImageAttribute_autoResize(this.peer.ptr, value ? 1 : 0)
    }
    renderModeAttribute(value: ImageRenderMode): void {
        ArkUIGeneratedNativeModule._ImageAttribute_renderMode(this.peer.ptr, value.valueOf())
    }
    dynamicRangeModeAttribute(value: DynamicRangeMode): void {
        ArkUIGeneratedNativeModule._ImageAttribute_dynamicRangeMode(this.peer.ptr, value.valueOf())
    }
    interpolationAttribute(value: ImageInterpolation): void {
        ArkUIGeneratedNativeModule._ImageAttribute_interpolation(this.peer.ptr, value.valueOf())
    }
    sourceSizeAttribute(value: ImageSourceSize): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeImageSourceSize(value)
        ArkUIGeneratedNativeModule._ImageAttribute_sourceSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    syncLoadAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ImageAttribute_syncLoad(this.peer.ptr, value ? 1 : 0)
    }
    colorFilterAttribute(value: ColorFilter | DrawingColorFilter): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColorFilter(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as ColorFilter
            thisSerializer.writeColorFilter(value_0)
        }
        else if (TypeChecker.isDrawingColorFilter(value, false)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as DrawingColorFilter
            thisSerializer.writeDrawingColorFilter(value_1)
        }
        ArkUIGeneratedNativeModule._ImageAttribute_colorFilter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    copyOptionAttribute(value: CopyOptions): void {
        ArkUIGeneratedNativeModule._ImageAttribute_copyOption(this.peer.ptr, value.valueOf())
    }
    draggableAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ImageAttribute_draggable(this.peer.ptr, value ? 1 : 0)
    }
    pointLightAttribute(value: PointLightStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePointLightStyle(value)
        ArkUIGeneratedNativeModule._ImageAttribute_pointLight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    edgeAntialiasingAttribute(value: number): void {
        ArkUIGeneratedNativeModule._ImageAttribute_edgeAntialiasing(this.peer.ptr, value)
    }
    onCompleteAttribute(value: ((event?: Type_ImageAttribute_onComplete_callback_event) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ImageAttribute_onComplete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onErrorAttribute(value: ImageErrorCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ImageAttribute_onError(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onFinishAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ImageAttribute_onFinish(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableAnalyzerAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ImageAttribute_enableAnalyzer(this.peer.ptr, value ? 1 : 0)
    }
    analyzerConfigAttribute(value: ImageAnalyzerConfig): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeImageAnalyzerConfig(value)
        ArkUIGeneratedNativeModule._ImageAttribute_analyzerConfig(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    resizableAttribute(value: ResizableOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeResizableOptions(value)
        ArkUIGeneratedNativeModule._ImageAttribute_resizable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    privacySensitiveAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ImageAttribute_privacySensitive(this.peer.ptr, value ? 1 : 0)
    }
    enhancedImageQualityAttribute(value: ResolutionQuality): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeResolutionQuality(value)
        ArkUIGeneratedNativeModule._ImageAttribute_enhancedImageQuality(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    onComplete?: ((event?: Type_ImageAttribute_onComplete_callback_event) => void)
    onError?: ImageErrorCallback
    onFinish?: (() => void)
    enableAnalyzer?: boolean
    analyzerConfig?: ImageAnalyzerConfig
    resizable?: ResizableOptions
    privacySensitive?: boolean
    enhancedImageQuality?: ResolutionQuality
}
