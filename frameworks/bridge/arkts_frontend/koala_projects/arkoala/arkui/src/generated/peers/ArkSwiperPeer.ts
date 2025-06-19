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
import { CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, CustomBuilder, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, SourceTool, RectResult, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason } from "./../ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Area, Bias, Font, VoidCallback } from "./../ArkUnitsInterfaces"
import { DrawModifier } from "./../ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, FontWeight, FontStyle, EdgeEffect } from "./../ArkEnumsInterfaces"
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
import { DotIndicator } from "./../ArkDotIndicatorBuilder"
import { DigitIndicator } from "./../ArkDigitIndicatorBuilder"
import { IndicatorComponentController } from "./../ArkIndicatorComponentControllerMaterialized"
import { SwiperDisplayMode, IndicatorStyle, OnSwiperAnimationStartCallback, OnSwiperAnimationEndCallback, OnSwiperGestureSwipeCallback, SwiperNestedScrollMode, SwiperContentAnimatedTransition, ContentDidScrollCallback, ArrowStyle, SwiperAttribute, SwiperAutoFill } from "./../ArkSwiperInterfaces"
import { Indicator } from "./../ArkIndicatorBuilder"
import { SwiperContentTransitionProxy } from "./../ArkSwiperContentTransitionProxyMaterialized"
import { SwiperController } from "./../ArkSwiperControllerMaterialized"
import { GestureName, GestureComponent } from "./../shared/generated-utils"
import { CallbackKind } from "./CallbackKind"
import { CallbackTransformer } from "./CallbackTransformer"
import { unsafeCast } from "@koalaui/common"
import { Deserializer, createDeserializer } from "./Deserializer"
import { MaterializedBase, toPeerPtr, wrapCallback } from "@koalaui/interop"
import { SubTabBarStyle } from "./../ArkSubTabBarStyleBuilder"
import { BottomTabBarStyle } from "./../ArkBottomTabBarStyleBuilder"
export class ArkSwiperPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSwiperPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._Swiper_construct(peerId, flags)
        const _peer = new ArkSwiperPeer(_peerPtr, peerId, "Swiper", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSwiperOptionsAttribute(controller?: SwiperController): void {
        const thisSerializer: Serializer = Serializer.hold()
        let controller_type: int32 = RuntimeType.UNDEFINED
        controller_type = runtimeType(controller)
        thisSerializer.writeInt8(controller_type)
        if ((RuntimeType.UNDEFINED) != (controller_type)) {
            const controller_value = controller!
            thisSerializer.writeSwiperController(controller_value)
        }
        ArkUIGeneratedNativeModule._SwiperInterface_setSwiperOptions(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    indexAttribute(value: number): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_index(this.peer.ptr, value)
    }
    autoPlayAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_autoPlay(this.peer.ptr, +value)
    }
    intervalAttribute(value: number): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_interval(this.peer.ptr, value)
    }
    indicator0Attribute(value: DotIndicator | DigitIndicator | boolean): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.OBJECT) == (value_type)) && (value instanceof DotIndicator)) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<DotIndicator>(value)
            thisSerializer.writeDotIndicator(value_0)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (value instanceof DigitIndicator)) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<DigitIndicator>(value)
            thisSerializer.writeDigitIndicator(value_1)
        }
        else if (RuntimeType.BOOLEAN == value_type) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<boolean>(value)
            thisSerializer.writeBoolean(value_2)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_indicator0(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    indicator1Attribute(value: IndicatorComponentController): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_indicator1(this.peer.ptr, toPeerPtr(value))
    }
    loopAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_loop(this.peer.ptr, +value)
    }
    durationAttribute(value: number): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_duration(this.peer.ptr, value)
    }
    verticalAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_vertical(this.peer.ptr, +value)
    }
    itemSpaceAttribute(value: number | string): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<string>(value)
            thisSerializer.writeString(value_1)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_itemSpace(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    displayModeAttribute(value: SwiperDisplayMode): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_displayMode(this.peer.ptr, value)
    }
    cachedCountAttribute(value: number): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_cachedCount(this.peer.ptr, value)
    }
    effectModeAttribute(value: EdgeEffect): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_effectMode(this.peer.ptr, value)
    }
    disableSwipeAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_disableSwipe(this.peer.ptr, +value)
    }
    curveAttribute(value: Curve | string | ICurve): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<Curve>(value)
            thisSerializer.writeInt32(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<string>(value)
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<ICurve>(value)
            thisSerializer.writeICurve(value_2)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_curve(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onChangeAttribute(value: ((index: number) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SwiperAttribute_onChange(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    indicatorStyleAttribute(value?: IndicatorStyle): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            thisSerializer.writeIndicatorStyle(value_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_indicatorStyle(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onAnimationStartAttribute(value: OnSwiperAnimationStartCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SwiperAttribute_onAnimationStart(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onAnimationEndAttribute(value: OnSwiperAnimationEndCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SwiperAttribute_onAnimationEnd(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onGestureSwipeAttribute(value: OnSwiperGestureSwipeCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SwiperAttribute_onGestureSwipe(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    nestedScrollAttribute(value: SwiperNestedScrollMode): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_nestedScroll(this.peer.ptr, value)
    }
    customContentTransitionAttribute(value: SwiperContentAnimatedTransition): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeSwiperContentAnimatedTransition(value)
        ArkUIGeneratedNativeModule._SwiperAttribute_customContentTransition(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onContentDidScrollAttribute(value: ContentDidScrollCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._SwiperAttribute_onContentDidScroll(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    indicatorInteractiveAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._SwiperAttribute_indicatorInteractive(this.peer.ptr, +value)
    }
    displayArrowAttribute(value: ArrowStyle | boolean, isHoverShow?: boolean): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<ArrowStyle>(value)
            thisSerializer.writeArrowStyle(value_0)
        }
        else if (RuntimeType.BOOLEAN == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<boolean>(value)
            thisSerializer.writeBoolean(value_1)
        }
        let isHoverShow_type: int32 = RuntimeType.UNDEFINED
        isHoverShow_type = runtimeType(isHoverShow)
        thisSerializer.writeInt8(isHoverShow_type)
        if ((RuntimeType.UNDEFINED) != (isHoverShow_type)) {
            const isHoverShow_value = isHoverShow!
            thisSerializer.writeBoolean(isHoverShow_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_displayArrow(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    displayCountAttribute(value: number | string | SwiperAutoFill, swipeByGroup?: boolean): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<string>(value)
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<SwiperAutoFill>(value)
            thisSerializer.writeSwiperAutoFill(value_2)
        }
        let swipeByGroup_type: int32 = RuntimeType.UNDEFINED
        swipeByGroup_type = runtimeType(swipeByGroup)
        thisSerializer.writeInt8(swipeByGroup_type)
        if ((RuntimeType.UNDEFINED) != (swipeByGroup_type)) {
            const swipeByGroup_value = swipeByGroup!
            thisSerializer.writeBoolean(swipeByGroup_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_displayCount(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    prevMarginAttribute(value: Length, ignoreBlank?: boolean): void {
        const thisSerializer: Serializer = Serializer.hold()
        let ignoreBlank_type: int32 = RuntimeType.UNDEFINED
        ignoreBlank_type = runtimeType(ignoreBlank)
        thisSerializer.writeInt8(ignoreBlank_type)
        if ((RuntimeType.UNDEFINED) != (ignoreBlank_type)) {
            const ignoreBlank_value = ignoreBlank!
            thisSerializer.writeBoolean(ignoreBlank_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_prevMargin(this.peer.ptr, value, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    nextMarginAttribute(value: Length, ignoreBlank?: boolean): void {
        const thisSerializer: Serializer = Serializer.hold()
        let ignoreBlank_type: int32 = RuntimeType.UNDEFINED
        ignoreBlank_type = runtimeType(ignoreBlank)
        thisSerializer.writeInt8(ignoreBlank_type)
        if ((RuntimeType.UNDEFINED) != (ignoreBlank_type)) {
            const ignoreBlank_value = ignoreBlank!
            thisSerializer.writeBoolean(ignoreBlank_value)
        }
        ArkUIGeneratedNativeModule._SwiperAttribute_nextMargin(this.peer.ptr, value, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    _onChangeEvent_indexAttribute(callback: ((index: number) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._SwiperAttribute__onChangeEvent_index(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ArkSwiperAttributes extends ArkCommonMethodAttributes {
    index?: number
    autoPlay?: boolean
    interval?: number
    indicator?: DotIndicator | DigitIndicator | boolean
    loop?: boolean
    duration?: number
    vertical?: boolean
    itemSpace?: number | string
    displayMode?: SwiperDisplayMode
    cachedCount?: number
    effectMode?: EdgeEffect
    disableSwipe?: boolean
    curve?: Curve | string | ICurve
    onChange?: ((index: number) => void)
    indicatorStyle?: IndicatorStyle
    onAnimationStart?: OnSwiperAnimationStartCallback
    onAnimationEnd?: OnSwiperAnimationEndCallback
    onGestureSwipe?: OnSwiperGestureSwipeCallback
    nestedScroll?: SwiperNestedScrollMode
    customContentTransition?: SwiperContentAnimatedTransition
    onContentDidScroll?: ContentDidScrollCallback
    indicatorInteractive?: boolean
}
