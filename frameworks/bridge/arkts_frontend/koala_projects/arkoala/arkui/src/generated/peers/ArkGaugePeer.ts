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
import { CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, CustomBuilder, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, SourceTool, RectResult, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason, ContentModifier, MultiShadowOptions, CommonConfiguration } from "./../ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Area, Bias, Font } from "./../ArkUnitsInterfaces"
import { DrawModifier } from "./../ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, FontWeight, FontStyle } from "./../ArkEnumsInterfaces"
import { LengthMetrics } from "./../ArkLengthMetricsMaterialized"
import { ResizableOptions, DrawingLattice } from "./../ArkImageInterfaces"
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
import { LinearGradient } from "./../ArkLinearGradientMaterialized"
import { GaugeShadowOptions, GaugeIndicatorOptions, GaugeConfiguration, GaugeOptions, GaugeAttribute } from "./../ArkGaugeInterfaces"
import { ColorStop } from "./../ArkDataPanelInterfaces"
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
export class ArkGaugePeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkGaugePeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._Gauge_construct(peerId, flags)
        const _peer = new ArkGaugePeer(_peerPtr, peerId, "Gauge", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setGaugeOptionsAttribute(options: GaugeOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeGaugeOptions(options)
        ArkUIGeneratedNativeModule._GaugeInterface_setGaugeOptions(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    valueAttribute(value: number): void {
        ArkUIGeneratedNativeModule._GaugeAttribute_value(this.peer.ptr, value)
    }
    startAngleAttribute(value: number): void {
        ArkUIGeneratedNativeModule._GaugeAttribute_startAngle(this.peer.ptr, value)
    }
    endAngleAttribute(value: number): void {
        ArkUIGeneratedNativeModule._GaugeAttribute_endAngle(this.peer.ptr, value)
    }
    colorsAttribute(value: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]>): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if ((((RuntimeType.NUMBER) == (value_type)) && ((unsafeCast<int32>(value)) >= (0)) && ((unsafeCast<int32>(value)) <= (11))) || (RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type)) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<ResourceColor>(value)
            let value_0_type: int32 = RuntimeType.UNDEFINED
            value_0_type = runtimeType(value_0)
            if (((RuntimeType.NUMBER) == (value_0_type)) && ((unsafeCast<int32>(value_0)) >= (0)) && ((unsafeCast<int32>(value_0)) <= (11))) {
                thisSerializer.writeInt8(0)
                const value_0_0 = unsafeCast<Color>(value_0)
                thisSerializer.writeInt32(value_0_0)
            }
            else if (RuntimeType.NUMBER == value_0_type) {
                thisSerializer.writeInt8(1)
                const value_0_1 = unsafeCast<number>(value_0)
                thisSerializer.writeNumber(value_0_1)
            }
            else if (RuntimeType.STRING == value_0_type) {
                thisSerializer.writeInt8(2)
                const value_0_2 = unsafeCast<string>(value_0)
                thisSerializer.writeString(value_0_2)
            }
            else if (RuntimeType.OBJECT == value_0_type) {
                thisSerializer.writeInt8(3)
                const value_0_3 = unsafeCast<Resource>(value_0)
                thisSerializer.writeResource(value_0_3)
            }
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (value instanceof LinearGradient)) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<LinearGradient>(value)
            thisSerializer.writeLinearGradient(value_1)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (value instanceof Array<[ ResourceColor | LinearGradient, number ]>)) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<Array<[ ResourceColor | LinearGradient, number ]>>(value)
            thisSerializer.writeInt32(value_2.length)
            for (let i = 0; i < value_2.length; i++) {
                const value_2_element: [ ResourceColor | LinearGradient, number ] = value_2[i]
                const value_2_element_0 = value_2_element[0]
                let value_2_element_0_type: int32 = RuntimeType.UNDEFINED
                value_2_element_0_type = runtimeType(value_2_element_0)
                if ((((RuntimeType.NUMBER) == (value_2_element_0_type)) && ((unsafeCast<int32>(value_2_element_0)) >= (0)) && ((unsafeCast<int32>(value_2_element_0)) <= (11))) || (RuntimeType.NUMBER == value_2_element_0_type) || (RuntimeType.STRING == value_2_element_0_type) || (RuntimeType.OBJECT == value_2_element_0_type)) {
                    thisSerializer.writeInt8(0)
                    const value_2_element_0_0 = unsafeCast<ResourceColor>(value_2_element_0)
                    let value_2_element_0_0_type: int32 = RuntimeType.UNDEFINED
                    value_2_element_0_0_type = runtimeType(value_2_element_0_0)
                    if (((RuntimeType.NUMBER) == (value_2_element_0_0_type)) && ((unsafeCast<int32>(value_2_element_0_0)) >= (0)) && ((unsafeCast<int32>(value_2_element_0_0)) <= (11))) {
                        thisSerializer.writeInt8(0)
                        const value_2_element_0_0_0 = unsafeCast<Color>(value_2_element_0_0)
                        thisSerializer.writeInt32(value_2_element_0_0_0)
                    }
                    else if (RuntimeType.NUMBER == value_2_element_0_0_type) {
                        thisSerializer.writeInt8(1)
                        const value_2_element_0_0_1 = unsafeCast<number>(value_2_element_0_0)
                        thisSerializer.writeNumber(value_2_element_0_0_1)
                    }
                    else if (RuntimeType.STRING == value_2_element_0_0_type) {
                        thisSerializer.writeInt8(2)
                        const value_2_element_0_0_2 = unsafeCast<string>(value_2_element_0_0)
                        thisSerializer.writeString(value_2_element_0_0_2)
                    }
                    else if (RuntimeType.OBJECT == value_2_element_0_0_type) {
                        thisSerializer.writeInt8(3)
                        const value_2_element_0_0_3 = unsafeCast<Resource>(value_2_element_0_0)
                        thisSerializer.writeResource(value_2_element_0_0_3)
                    }
                }
                else if (((RuntimeType.OBJECT) == (value_2_element_0_type)) && (value_2_element_0 instanceof LinearGradient)) {
                    thisSerializer.writeInt8(1)
                    const value_2_element_0_1 = unsafeCast<LinearGradient>(value_2_element_0)
                    thisSerializer.writeLinearGradient(value_2_element_0_1)
                }
                const value_2_element_1 = value_2_element[1]
                thisSerializer.writeNumber(value_2_element_1)
            }
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_colors(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeWidthAttribute(value: Length): void {
        ArkUIGeneratedNativeModule._GaugeAttribute_strokeWidth(this.peer.ptr, value)
    }
    descriptionAttribute(value: CustomBuilder): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value))
        ArkUIGeneratedNativeModule._GaugeAttribute_description(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    trackShadowAttribute(value: GaugeShadowOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeGaugeShadowOptions(value)
        ArkUIGeneratedNativeModule._GaugeAttribute_trackShadow(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    indicatorAttribute(value: GaugeIndicatorOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeGaugeIndicatorOptions(value)
        ArkUIGeneratedNativeModule._GaugeAttribute_indicator(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    privacySensitiveAttribute(value?: boolean): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_privacySensitive(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    contentModifierAttribute(value: ContentModifier<any>): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeCustomObject("ContentModifier", value)
        ArkUIGeneratedNativeModule._GaugeAttribute_contentModifier(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ArkGaugeAttributes extends ArkCommonMethodAttributes {
    value?: number
    startAngle?: number
    endAngle?: number
    colors?: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]>
    strokeWidth?: Length
    description?: CustomBuilder
    trackShadow?: GaugeShadowOptions
    indicator?: GaugeIndicatorOptions
    privacySensitive?: boolean | undefined
    contentModifier?: ContentModifier<any>
}
