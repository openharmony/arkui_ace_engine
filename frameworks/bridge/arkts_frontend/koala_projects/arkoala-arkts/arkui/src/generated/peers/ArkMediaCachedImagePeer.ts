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
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback } from "@koalaui/interop"
import { Serializer } from "./Serializer"
import { ComponentBase } from "./../../ComponentBase"
import { PeerNode } from "./../../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkImagePeer, ArkImageAttributes } from "./ArkImagePeer"
import { ImageAttribute, ResizableOptions, ImageRenderMode, DynamicRangeMode, ImageInterpolation, ImageSourceSize, DrawingColorFilter, ImageErrorCallback, ResolutionQuality } from "./../ArkImageInterfaces"
import { CommonMethod, Rectangle, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, CustomBuilder, DragItemInfo, UniformDataType, PreDragStatus, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, PointLightStyle } from "./../ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage } from "./../ArkUnitsInterfaces"
import { DrawModifier } from "./../ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, ImageFit, CopyOptions } from "./../ArkEnumsInterfaces"
import { Callback_Array_TouchTestInfo_TouchResult, Callback_ClickEvent_Void, Callback_Boolean_HoverEvent_Void, Callback_MouseEvent_Void, Callback_TouchEvent_Void, Callback_KeyEvent_Void, Callback_KeyEvent_Boolean, Callback_Void, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, Callback_DragEvent_String_Void, Callback_PreDragStatus_Void, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, Callback_TouchEvent_HitTestMode, Literal_Alignment_align, Callback_Type_ImageAttribute_onComplete_callback_event_Void, Type_ImageAttribute_onComplete_callback_event } from "./../SyntheticDeclarations"
import { LengthMetrics } from "./../ArkLengthMetricsMaterialized"
import { Resource } from "./../ArkResourceInterfaces"
import { ClickEvent } from "./../ArkClickEventMaterialized"
import { HoverEvent } from "./../ArkHoverEventMaterialized"
import { MouseEvent } from "./../ArkMouseEventMaterialized"
import { TouchEvent } from "./../ArkTouchEventMaterialized"
import { KeyEvent } from "./../ArkKeyEventMaterialized"
import { FocusBoxStyle, FocusPriority } from "./../ArkFocusInterfaces"
import { TransitionEffect } from "./../ArkTransitionEffectMaterialized"
import { DragEvent } from "./../ArkDragEventMaterialized"
import { CircleShape } from "./../ArkCircleShapeMaterialized"
import { EllipseShape } from "./../ArkEllipseShapeMaterialized"
import { PathShape } from "./../ArkPathShapeMaterialized"
import { RectShape } from "./../ArkRectShapeMaterialized"
import { ProgressMask } from "./../ArkProgressMaskMaterialized"
import { AttributeModifier } from "./../../handwritten"
import { GestureModifier } from "./../ArkGestureModifierMaterialized"
import { GestureInfo, GestureJudgeResult, GestureType, GestureMask } from "./../ArkGestureInterfaces"
import { BaseGestureEvent } from "./../ArkBaseGestureEventMaterialized"
import { PixelMap } from "./../ArkPixelMapMaterialized"
import { ColorFilter } from "./../ArkColorFilterMaterialized"
import { ImageAnalyzerConfig } from "./../ArkImageCommonInterfaces"
import { TapGestureInterface } from "./../ArkTapGestureInterfaceMaterialized"
import { LongPressGestureInterface } from "./../ArkLongPressGestureInterfaceMaterialized"
import { PanGestureInterface } from "./../ArkPanGestureInterfaceMaterialized"
import { PinchGestureInterface } from "./../ArkPinchGestureInterfaceMaterialized"
import { SwipeGestureInterface } from "./../ArkSwipeGestureInterfaceMaterialized"
import { RotationGestureInterface } from "./../ArkRotationGestureInterfaceMaterialized"
import { GestureGroupInterface } from "./../ArkGestureGroupInterfaceMaterialized"
import { DrawableDescriptor } from "./../ArkDrawableDescriptorMaterialized"
import { ASTCResource, MediaCachedImageAttribute } from "./../ArkMediaCachedImageInterfaces"
import { CallbackKind } from "./CallbackKind"
import { CallbackTransformer } from "./CallbackTransformer"
import { DotIndicator } from "./../ArkDotIndicatorBuilder"
import { DigitIndicator } from "./../ArkDigitIndicatorBuilder"
import { SubTabBarStyle } from "./../ArkSubTabBarStyleBuilder"
import { BottomTabBarStyle } from "./../ArkBottomTabBarStyleBuilder"
export class ArkMediaCachedImagePeer extends ArkImagePeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkMediaCachedImagePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._MediaCachedImage_construct(peerId, flags)
        const _peer  = new ArkMediaCachedImagePeer(_peerPtr, peerId, "MediaCachedImage", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setMediaCachedImageOptionsAttribute(src: PixelMap | ResourceStr | DrawableDescriptor | ASTCResource): void {
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
        else if (TypeChecker.isDrawableDescriptor(src)) {
            thisSerializer.writeInt8(2 as int32)
            const src_2  = src as DrawableDescriptor
            thisSerializer.writeDrawableDescriptor(src_2)
        }
        else if (TypeChecker.isASTCResource(src, false, false)) {
            thisSerializer.writeInt8(3 as int32)
            const src_3  = src as ASTCResource
            thisSerializer.writeASTCResource(src_3)
        }
        ArkUIGeneratedNativeModule._MediaCachedImageInterface_setMediaCachedImageOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ArkMediaCachedImageAttributes extends ArkImageAttributes {
}
