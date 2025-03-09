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
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Area, Bias, Font } from "./../ArkUnitsInterfaces"
import { DrawModifier } from "./../ArkDrawModifierMaterialized"
import { Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, CustomBuilder, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, SourceTool, RectResult, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason, CommonMethod, CommonAttribute, NestedScrollOptions, ContentClipMode, EdgeEffectOptions, FadingEdgeOptions } from "./../ArkCommonInterfaces"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, FontWeight, FontStyle, LineCapStyle, LineJoinStyle, BarState, EdgeEffect, NestedScrollMode } from "./../ArkEnumsInterfaces"
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
import { ScrollOnWillScrollCallback, ScrollOnScrollCallback } from "./../ArkScrollInterfaces"
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
export class ArkCommonMethodPeer extends PeerNode {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkCommonMethodPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._CommonMethod_construct(peerId, flags)
        const _peer = new ArkCommonMethodPeer(_peerPtr, peerId, "CommonMethod", flags)
        component?.setPeer(_peer)
        return _peer
    }
    widthAttribute(value: Length): void {
        ArkUIGeneratedNativeModule._CommonMethod_width(this.peer.ptr, value)
    }
    heightAttribute(value: Length): void {
        ArkUIGeneratedNativeModule._CommonMethod_height(this.peer.ptr, value)
    }
    drawModifierAttribute(value?: DrawModifier): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            thisSerializer.writeDrawModifier(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_drawModifier(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    responseRegionAttribute(value: Array<Rectangle> | Rectangle): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.OBJECT) == (value_type)) && (value instanceof Array<Rectangle>)) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<Array<Rectangle>>(value)
            thisSerializer.writeInt32(value_0.length)
            for (let i = 0; i < value_0.length; i++) {
                const value_0_element: Rectangle = value_0[i]
                thisSerializer.writeRectangle(value_0_element)
            }
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (((value!.hasOwnProperty("x")) || (value!.hasOwnProperty("y")) || (value!.hasOwnProperty("width")) || (value!.hasOwnProperty("height"))))) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<Rectangle>(value)
            thisSerializer.writeRectangle(value_1)
        }
        ArkUIGeneratedNativeModule._CommonMethod_responseRegion(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    mouseResponseRegionAttribute(value: Array<Rectangle> | Rectangle): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.OBJECT) == (value_type)) && (value instanceof Array<Rectangle>)) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<Array<Rectangle>>(value)
            thisSerializer.writeInt32(value_0.length)
            for (let i = 0; i < value_0.length; i++) {
                const value_0_element: Rectangle = value_0[i]
                thisSerializer.writeRectangle(value_0_element)
            }
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (((value!.hasOwnProperty("x")) || (value!.hasOwnProperty("y")) || (value!.hasOwnProperty("width")) || (value!.hasOwnProperty("height"))))) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<Rectangle>(value)
            thisSerializer.writeRectangle(value_1)
        }
        ArkUIGeneratedNativeModule._CommonMethod_mouseResponseRegion(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    sizeAttribute(value: SizeOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeSizeOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_size(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    constraintSizeAttribute(value: ConstraintSizeOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeConstraintSizeOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_constraintSize(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    touchableAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_touchable(this.peer.ptr, +value)
    }
    hitTestBehaviorAttribute(value: HitTestMode): void {
        ArkUIGeneratedNativeModule._CommonMethod_hitTestBehavior(this.peer.ptr, value)
    }
    onChildTouchTestAttribute(value: ((value: Array<TouchTestInfo>) => TouchResult)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onChildTouchTest(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    layoutWeightAttribute(value: number | string): void {
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
        ArkUIGeneratedNativeModule._CommonMethod_layoutWeight(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    chainWeightAttribute(value: ChainWeightOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeChainWeightOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_chainWeight(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    paddingAttribute(value: Padding | Length | LocalizedPadding): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (isPadding(value)) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<Padding>(value)
            const value_0_top = value_0.top
            let value_0_top_type: int32 = RuntimeType.UNDEFINED
            value_0_top_type = runtimeType(value_0_top)
            thisSerializer.writeInt8(value_0_top_type)
            if ((RuntimeType.UNDEFINED) != (value_0_top_type)) {
                const value_0_top_value = value_0_top!
                thisSerializer.writeLength(value_0_top_value)
            }
            const value_0_right = value_0.right
            let value_0_right_type: int32 = RuntimeType.UNDEFINED
            value_0_right_type = runtimeType(value_0_right)
            thisSerializer.writeInt8(value_0_right_type)
            if ((RuntimeType.UNDEFINED) != (value_0_right_type)) {
                const value_0_right_value = value_0_right!
                thisSerializer.writeLength(value_0_right_value)
            }
            const value_0_bottom = value_0.bottom
            let value_0_bottom_type: int32 = RuntimeType.UNDEFINED
            value_0_bottom_type = runtimeType(value_0_bottom)
            thisSerializer.writeInt8(value_0_bottom_type)
            if ((RuntimeType.UNDEFINED) != (value_0_bottom_type)) {
                const value_0_bottom_value = value_0_bottom!
                thisSerializer.writeLength(value_0_bottom_value)
            }
            const value_0_left = value_0.left
            let value_0_left_type: int32 = RuntimeType.UNDEFINED
            value_0_left_type = runtimeType(value_0_left)
            thisSerializer.writeInt8(value_0_left_type)
            if ((RuntimeType.UNDEFINED) != (value_0_left_type)) {
                const value_0_left_value = value_0_left!
                thisSerializer.writeLength(value_0_left_value)
            }
        }
        else if (((RuntimeType.NUMBER) == (value_type)) || ((RuntimeType.STRING) == (value_type)) || (((RuntimeType.OBJECT) == (value_type)) && (isResource(value)))) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<Length>(value)
            thisSerializer.writeLength(value_1)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (((value!.hasOwnProperty("end")) || (value!.hasOwnProperty("start"))))) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<LocalizedPadding>(value)
            thisSerializer.writeLocalizedPadding(value_2)
        }
        ArkUIGeneratedNativeModule._CommonMethod_padding(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    safeAreaPaddingAttribute(value: Padding | LengthMetrics | LocalizedPadding): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (isPadding(value)) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<Padding>(value)
            const value_0_top = value_0.top
            let value_0_top_type: int32 = RuntimeType.UNDEFINED
            value_0_top_type = runtimeType(value_0_top)
            thisSerializer.writeInt8(value_0_top_type)
            if ((RuntimeType.UNDEFINED) != (value_0_top_type)) {
                const value_0_top_value = value_0_top!
                thisSerializer.writeLength(value_0_top_value)
            }
            const value_0_right = value_0.right
            let value_0_right_type: int32 = RuntimeType.UNDEFINED
            value_0_right_type = runtimeType(value_0_right)
            thisSerializer.writeInt8(value_0_right_type)
            if ((RuntimeType.UNDEFINED) != (value_0_right_type)) {
                const value_0_right_value = value_0_right!
                thisSerializer.writeLength(value_0_right_value)
            }
            const value_0_bottom = value_0.bottom
            let value_0_bottom_type: int32 = RuntimeType.UNDEFINED
            value_0_bottom_type = runtimeType(value_0_bottom)
            thisSerializer.writeInt8(value_0_bottom_type)
            if ((RuntimeType.UNDEFINED) != (value_0_bottom_type)) {
                const value_0_bottom_value = value_0_bottom!
                thisSerializer.writeLength(value_0_bottom_value)
            }
            const value_0_left = value_0.left
            let value_0_left_type: int32 = RuntimeType.UNDEFINED
            value_0_left_type = runtimeType(value_0_left)
            thisSerializer.writeInt8(value_0_left_type)
            if ((RuntimeType.UNDEFINED) != (value_0_left_type)) {
                const value_0_left_value = value_0_left!
                thisSerializer.writeLength(value_0_left_value)
            }
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (value instanceof LengthMetrics)) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<LengthMetrics>(value)
            thisSerializer.writeLengthMetrics(value_1)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (((value!.hasOwnProperty("end")) || (value!.hasOwnProperty("start"))))) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<LocalizedPadding>(value)
            thisSerializer.writeLocalizedPadding(value_2)
        }
        ArkUIGeneratedNativeModule._CommonMethod_safeAreaPadding(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    marginAttribute(value: Margin | Length | LocalizedMargin): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (isPadding(value)) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<Margin>(value)
            const value_0_top = value_0.top
            let value_0_top_type: int32 = RuntimeType.UNDEFINED
            value_0_top_type = runtimeType(value_0_top)
            thisSerializer.writeInt8(value_0_top_type)
            if ((RuntimeType.UNDEFINED) != (value_0_top_type)) {
                const value_0_top_value = value_0_top!
                thisSerializer.writeLength(value_0_top_value)
            }
            const value_0_right = value_0.right
            let value_0_right_type: int32 = RuntimeType.UNDEFINED
            value_0_right_type = runtimeType(value_0_right)
            thisSerializer.writeInt8(value_0_right_type)
            if ((RuntimeType.UNDEFINED) != (value_0_right_type)) {
                const value_0_right_value = value_0_right!
                thisSerializer.writeLength(value_0_right_value)
            }
            const value_0_bottom = value_0.bottom
            let value_0_bottom_type: int32 = RuntimeType.UNDEFINED
            value_0_bottom_type = runtimeType(value_0_bottom)
            thisSerializer.writeInt8(value_0_bottom_type)
            if ((RuntimeType.UNDEFINED) != (value_0_bottom_type)) {
                const value_0_bottom_value = value_0_bottom!
                thisSerializer.writeLength(value_0_bottom_value)
            }
            const value_0_left = value_0.left
            let value_0_left_type: int32 = RuntimeType.UNDEFINED
            value_0_left_type = runtimeType(value_0_left)
            thisSerializer.writeInt8(value_0_left_type)
            if ((RuntimeType.UNDEFINED) != (value_0_left_type)) {
                const value_0_left_value = value_0_left!
                thisSerializer.writeLength(value_0_left_value)
            }
        }
        else if (((RuntimeType.NUMBER) == (value_type)) || ((RuntimeType.STRING) == (value_type)) || (((RuntimeType.OBJECT) == (value_type)) && (isResource(value)))) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<Length>(value)
            thisSerializer.writeLength(value_1)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (((value!.hasOwnProperty("end")) || (value!.hasOwnProperty("start"))))) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<LocalizedMargin>(value)
            thisSerializer.writeLocalizedPadding(value_2)
        }
        ArkUIGeneratedNativeModule._CommonMethod_margin(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundColorAttribute(value: ResourceColor): void {
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
        ArkUIGeneratedNativeModule._CommonMethod_backgroundColor(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    pixelRoundAttribute(value: PixelRoundPolicy): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writePixelRoundPolicy(value)
        ArkUIGeneratedNativeModule._CommonMethod_pixelRound(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundImageSizeAttribute(value: SizeOptions | ImageSize): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<SizeOptions>(value)
            thisSerializer.writeSizeOptions(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<ImageSize>(value)
            thisSerializer.writeInt32(value_1)
        }
        ArkUIGeneratedNativeModule._CommonMethod_backgroundImageSize(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundImagePositionAttribute(value: Position | Alignment): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<Position>(value)
            thisSerializer.writePosition(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<Alignment>(value)
            thisSerializer.writeInt32(value_1)
        }
        ArkUIGeneratedNativeModule._CommonMethod_backgroundImagePosition(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundEffectAttribute(value: BackgroundEffectOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeBackgroundEffectOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_backgroundEffect(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundImageResizableAttribute(value: ResizableOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeResizableOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_backgroundImageResizable(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    foregroundEffectAttribute(value: ForegroundEffectOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeForegroundEffectOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_foregroundEffect(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    visualEffectAttribute(value: VisualEffect): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeVisualEffect(value)
        ArkUIGeneratedNativeModule._CommonMethod_visualEffect(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundFilterAttribute(value: Filter): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeFilter(value)
        ArkUIGeneratedNativeModule._CommonMethod_backgroundFilter(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    foregroundFilterAttribute(value: Filter): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeFilter(value)
        ArkUIGeneratedNativeModule._CommonMethod_foregroundFilter(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    compositingFilterAttribute(value: Filter): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeFilter(value)
        ArkUIGeneratedNativeModule._CommonMethod_compositingFilter(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    opacityAttribute(value: number | Resource): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_1)
        }
        ArkUIGeneratedNativeModule._CommonMethod_opacity(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    borderAttribute(value: BorderOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeBorderOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_border(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    borderStyleAttribute(value: BorderStyle | EdgeStyles): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<BorderStyle>(value)
            thisSerializer.writeInt32(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<EdgeStyles>(value)
            const value_1_top = value_1.top
            let value_1_top_type: int32 = RuntimeType.UNDEFINED
            value_1_top_type = runtimeType(value_1_top)
            thisSerializer.writeInt8(value_1_top_type)
            if ((RuntimeType.UNDEFINED) != (value_1_top_type)) {
                const value_1_top_value = value_1_top!
                thisSerializer.writeInt32(value_1_top_value)
            }
            const value_1_right = value_1.right
            let value_1_right_type: int32 = RuntimeType.UNDEFINED
            value_1_right_type = runtimeType(value_1_right)
            thisSerializer.writeInt8(value_1_right_type)
            if ((RuntimeType.UNDEFINED) != (value_1_right_type)) {
                const value_1_right_value = value_1_right!
                thisSerializer.writeInt32(value_1_right_value)
            }
            const value_1_bottom = value_1.bottom
            let value_1_bottom_type: int32 = RuntimeType.UNDEFINED
            value_1_bottom_type = runtimeType(value_1_bottom)
            thisSerializer.writeInt8(value_1_bottom_type)
            if ((RuntimeType.UNDEFINED) != (value_1_bottom_type)) {
                const value_1_bottom_value = value_1_bottom!
                thisSerializer.writeInt32(value_1_bottom_value)
            }
            const value_1_left = value_1.left
            let value_1_left_type: int32 = RuntimeType.UNDEFINED
            value_1_left_type = runtimeType(value_1_left)
            thisSerializer.writeInt8(value_1_left_type)
            if ((RuntimeType.UNDEFINED) != (value_1_left_type)) {
                const value_1_left_value = value_1_left!
                thisSerializer.writeInt32(value_1_left_value)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_borderStyle(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    borderWidthAttribute(value: Length | EdgeWidths | LocalizedEdgeWidths): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.NUMBER) == (value_type)) || ((RuntimeType.STRING) == (value_type)) || (((RuntimeType.OBJECT) == (value_type)) && (isResource(value)))) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<Length>(value)
            thisSerializer.writeLength(value_0)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (((value!.hasOwnProperty("right")) || (value!.hasOwnProperty("left"))))) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<EdgeWidths>(value)
            const value_1_top = value_1.top
            let value_1_top_type: int32 = RuntimeType.UNDEFINED
            value_1_top_type = runtimeType(value_1_top)
            thisSerializer.writeInt8(value_1_top_type)
            if ((RuntimeType.UNDEFINED) != (value_1_top_type)) {
                const value_1_top_value = value_1_top!
                thisSerializer.writeLength(value_1_top_value)
            }
            const value_1_right = value_1.right
            let value_1_right_type: int32 = RuntimeType.UNDEFINED
            value_1_right_type = runtimeType(value_1_right)
            thisSerializer.writeInt8(value_1_right_type)
            if ((RuntimeType.UNDEFINED) != (value_1_right_type)) {
                const value_1_right_value = value_1_right!
                thisSerializer.writeLength(value_1_right_value)
            }
            const value_1_bottom = value_1.bottom
            let value_1_bottom_type: int32 = RuntimeType.UNDEFINED
            value_1_bottom_type = runtimeType(value_1_bottom)
            thisSerializer.writeInt8(value_1_bottom_type)
            if ((RuntimeType.UNDEFINED) != (value_1_bottom_type)) {
                const value_1_bottom_value = value_1_bottom!
                thisSerializer.writeLength(value_1_bottom_value)
            }
            const value_1_left = value_1.left
            let value_1_left_type: int32 = RuntimeType.UNDEFINED
            value_1_left_type = runtimeType(value_1_left)
            thisSerializer.writeInt8(value_1_left_type)
            if ((RuntimeType.UNDEFINED) != (value_1_left_type)) {
                const value_1_left_value = value_1_left!
                thisSerializer.writeLength(value_1_left_value)
            }
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (((value!.hasOwnProperty("end")) || (value!.hasOwnProperty("start"))))) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<LocalizedEdgeWidths>(value)
            thisSerializer.writeLocalizedEdgeWidths(value_2)
        }
        ArkUIGeneratedNativeModule._CommonMethod_borderWidth(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    borderColorAttribute(value: ResourceColor | EdgeColors | LocalizedEdgeColors): void {
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
        else if (((RuntimeType.OBJECT) == (value_type)) && (((value!.hasOwnProperty("right")) || (value!.hasOwnProperty("left"))))) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<EdgeColors>(value)
            const value_1_top = value_1.top
            let value_1_top_type: int32 = RuntimeType.UNDEFINED
            value_1_top_type = runtimeType(value_1_top)
            thisSerializer.writeInt8(value_1_top_type)
            if ((RuntimeType.UNDEFINED) != (value_1_top_type)) {
                const value_1_top_value = value_1_top!
                let value_1_top_value_type: int32 = RuntimeType.UNDEFINED
                value_1_top_value_type = runtimeType(value_1_top_value)
                if (((RuntimeType.NUMBER) == (value_1_top_value_type)) && ((unsafeCast<int32>(value_1_top_value)) >= (0)) && ((unsafeCast<int32>(value_1_top_value)) <= (11))) {
                    thisSerializer.writeInt8(0)
                    const value_1_top_value_0 = unsafeCast<Color>(value_1_top_value)
                    thisSerializer.writeInt32(value_1_top_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_top_value_type) {
                    thisSerializer.writeInt8(1)
                    const value_1_top_value_1 = unsafeCast<number>(value_1_top_value)
                    thisSerializer.writeNumber(value_1_top_value_1)
                }
                else if (RuntimeType.STRING == value_1_top_value_type) {
                    thisSerializer.writeInt8(2)
                    const value_1_top_value_2 = unsafeCast<string>(value_1_top_value)
                    thisSerializer.writeString(value_1_top_value_2)
                }
                else if (RuntimeType.OBJECT == value_1_top_value_type) {
                    thisSerializer.writeInt8(3)
                    const value_1_top_value_3 = unsafeCast<Resource>(value_1_top_value)
                    thisSerializer.writeResource(value_1_top_value_3)
                }
            }
            const value_1_right = value_1.right
            let value_1_right_type: int32 = RuntimeType.UNDEFINED
            value_1_right_type = runtimeType(value_1_right)
            thisSerializer.writeInt8(value_1_right_type)
            if ((RuntimeType.UNDEFINED) != (value_1_right_type)) {
                const value_1_right_value = value_1_right!
                let value_1_right_value_type: int32 = RuntimeType.UNDEFINED
                value_1_right_value_type = runtimeType(value_1_right_value)
                if (((RuntimeType.NUMBER) == (value_1_right_value_type)) && ((unsafeCast<int32>(value_1_right_value)) >= (0)) && ((unsafeCast<int32>(value_1_right_value)) <= (11))) {
                    thisSerializer.writeInt8(0)
                    const value_1_right_value_0 = unsafeCast<Color>(value_1_right_value)
                    thisSerializer.writeInt32(value_1_right_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_right_value_type) {
                    thisSerializer.writeInt8(1)
                    const value_1_right_value_1 = unsafeCast<number>(value_1_right_value)
                    thisSerializer.writeNumber(value_1_right_value_1)
                }
                else if (RuntimeType.STRING == value_1_right_value_type) {
                    thisSerializer.writeInt8(2)
                    const value_1_right_value_2 = unsafeCast<string>(value_1_right_value)
                    thisSerializer.writeString(value_1_right_value_2)
                }
                else if (RuntimeType.OBJECT == value_1_right_value_type) {
                    thisSerializer.writeInt8(3)
                    const value_1_right_value_3 = unsafeCast<Resource>(value_1_right_value)
                    thisSerializer.writeResource(value_1_right_value_3)
                }
            }
            const value_1_bottom = value_1.bottom
            let value_1_bottom_type: int32 = RuntimeType.UNDEFINED
            value_1_bottom_type = runtimeType(value_1_bottom)
            thisSerializer.writeInt8(value_1_bottom_type)
            if ((RuntimeType.UNDEFINED) != (value_1_bottom_type)) {
                const value_1_bottom_value = value_1_bottom!
                let value_1_bottom_value_type: int32 = RuntimeType.UNDEFINED
                value_1_bottom_value_type = runtimeType(value_1_bottom_value)
                if (((RuntimeType.NUMBER) == (value_1_bottom_value_type)) && ((unsafeCast<int32>(value_1_bottom_value)) >= (0)) && ((unsafeCast<int32>(value_1_bottom_value)) <= (11))) {
                    thisSerializer.writeInt8(0)
                    const value_1_bottom_value_0 = unsafeCast<Color>(value_1_bottom_value)
                    thisSerializer.writeInt32(value_1_bottom_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_bottom_value_type) {
                    thisSerializer.writeInt8(1)
                    const value_1_bottom_value_1 = unsafeCast<number>(value_1_bottom_value)
                    thisSerializer.writeNumber(value_1_bottom_value_1)
                }
                else if (RuntimeType.STRING == value_1_bottom_value_type) {
                    thisSerializer.writeInt8(2)
                    const value_1_bottom_value_2 = unsafeCast<string>(value_1_bottom_value)
                    thisSerializer.writeString(value_1_bottom_value_2)
                }
                else if (RuntimeType.OBJECT == value_1_bottom_value_type) {
                    thisSerializer.writeInt8(3)
                    const value_1_bottom_value_3 = unsafeCast<Resource>(value_1_bottom_value)
                    thisSerializer.writeResource(value_1_bottom_value_3)
                }
            }
            const value_1_left = value_1.left
            let value_1_left_type: int32 = RuntimeType.UNDEFINED
            value_1_left_type = runtimeType(value_1_left)
            thisSerializer.writeInt8(value_1_left_type)
            if ((RuntimeType.UNDEFINED) != (value_1_left_type)) {
                const value_1_left_value = value_1_left!
                let value_1_left_value_type: int32 = RuntimeType.UNDEFINED
                value_1_left_value_type = runtimeType(value_1_left_value)
                if (((RuntimeType.NUMBER) == (value_1_left_value_type)) && ((unsafeCast<int32>(value_1_left_value)) >= (0)) && ((unsafeCast<int32>(value_1_left_value)) <= (11))) {
                    thisSerializer.writeInt8(0)
                    const value_1_left_value_0 = unsafeCast<Color>(value_1_left_value)
                    thisSerializer.writeInt32(value_1_left_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_left_value_type) {
                    thisSerializer.writeInt8(1)
                    const value_1_left_value_1 = unsafeCast<number>(value_1_left_value)
                    thisSerializer.writeNumber(value_1_left_value_1)
                }
                else if (RuntimeType.STRING == value_1_left_value_type) {
                    thisSerializer.writeInt8(2)
                    const value_1_left_value_2 = unsafeCast<string>(value_1_left_value)
                    thisSerializer.writeString(value_1_left_value_2)
                }
                else if (RuntimeType.OBJECT == value_1_left_value_type) {
                    thisSerializer.writeInt8(3)
                    const value_1_left_value_3 = unsafeCast<Resource>(value_1_left_value)
                    thisSerializer.writeResource(value_1_left_value_3)
                }
            }
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (((value!.hasOwnProperty("end")) || (value!.hasOwnProperty("start"))))) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<LocalizedEdgeColors>(value)
            thisSerializer.writeLocalizedEdgeColors(value_2)
        }
        ArkUIGeneratedNativeModule._CommonMethod_borderColor(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    borderRadiusAttribute(value: Length | BorderRadiuses | LocalizedBorderRadiuses): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.NUMBER) == (value_type)) || ((RuntimeType.STRING) == (value_type)) || (((RuntimeType.OBJECT) == (value_type)) && (isResource(value)))) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<Length>(value)
            thisSerializer.writeLength(value_0)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (((value!.hasOwnProperty("topLeft")) || (value!.hasOwnProperty("topRight")) || (value!.hasOwnProperty("bottomLeft")) || (value!.hasOwnProperty("bottomRight"))))) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<BorderRadiuses>(value)
            const value_1_topLeft = value_1.topLeft
            let value_1_topLeft_type: int32 = RuntimeType.UNDEFINED
            value_1_topLeft_type = runtimeType(value_1_topLeft)
            thisSerializer.writeInt8(value_1_topLeft_type)
            if ((RuntimeType.UNDEFINED) != (value_1_topLeft_type)) {
                const value_1_topLeft_value = value_1_topLeft!
                thisSerializer.writeLength(value_1_topLeft_value)
            }
            const value_1_topRight = value_1.topRight
            let value_1_topRight_type: int32 = RuntimeType.UNDEFINED
            value_1_topRight_type = runtimeType(value_1_topRight)
            thisSerializer.writeInt8(value_1_topRight_type)
            if ((RuntimeType.UNDEFINED) != (value_1_topRight_type)) {
                const value_1_topRight_value = value_1_topRight!
                thisSerializer.writeLength(value_1_topRight_value)
            }
            const value_1_bottomLeft = value_1.bottomLeft
            let value_1_bottomLeft_type: int32 = RuntimeType.UNDEFINED
            value_1_bottomLeft_type = runtimeType(value_1_bottomLeft)
            thisSerializer.writeInt8(value_1_bottomLeft_type)
            if ((RuntimeType.UNDEFINED) != (value_1_bottomLeft_type)) {
                const value_1_bottomLeft_value = value_1_bottomLeft!
                thisSerializer.writeLength(value_1_bottomLeft_value)
            }
            const value_1_bottomRight = value_1.bottomRight
            let value_1_bottomRight_type: int32 = RuntimeType.UNDEFINED
            value_1_bottomRight_type = runtimeType(value_1_bottomRight)
            thisSerializer.writeInt8(value_1_bottomRight_type)
            if ((RuntimeType.UNDEFINED) != (value_1_bottomRight_type)) {
                const value_1_bottomRight_value = value_1_bottomRight!
                thisSerializer.writeLength(value_1_bottomRight_value)
            }
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (((value!.hasOwnProperty("topStart")) || (value!.hasOwnProperty("topEnd")) || (value!.hasOwnProperty("bottomStart")) || (value!.hasOwnProperty("bottomEnd"))))) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<LocalizedBorderRadiuses>(value)
            thisSerializer.writeLocalizedBorderRadiuses(value_2)
        }
        ArkUIGeneratedNativeModule._CommonMethod_borderRadius(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    borderImageAttribute(value: BorderImageOption): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeBorderImageOption(value)
        ArkUIGeneratedNativeModule._CommonMethod_borderImage(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    outlineAttribute(value: OutlineOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeOutlineOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_outline(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    outlineStyleAttribute(value: OutlineStyle | EdgeOutlineStyles): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<OutlineStyle>(value)
            thisSerializer.writeInt32(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<EdgeOutlineStyles>(value)
            const value_1_top = value_1.top
            let value_1_top_type: int32 = RuntimeType.UNDEFINED
            value_1_top_type = runtimeType(value_1_top)
            thisSerializer.writeInt8(value_1_top_type)
            if ((RuntimeType.UNDEFINED) != (value_1_top_type)) {
                const value_1_top_value = value_1_top!
                thisSerializer.writeInt32(value_1_top_value)
            }
            const value_1_right = value_1.right
            let value_1_right_type: int32 = RuntimeType.UNDEFINED
            value_1_right_type = runtimeType(value_1_right)
            thisSerializer.writeInt8(value_1_right_type)
            if ((RuntimeType.UNDEFINED) != (value_1_right_type)) {
                const value_1_right_value = value_1_right!
                thisSerializer.writeInt32(value_1_right_value)
            }
            const value_1_bottom = value_1.bottom
            let value_1_bottom_type: int32 = RuntimeType.UNDEFINED
            value_1_bottom_type = runtimeType(value_1_bottom)
            thisSerializer.writeInt8(value_1_bottom_type)
            if ((RuntimeType.UNDEFINED) != (value_1_bottom_type)) {
                const value_1_bottom_value = value_1_bottom!
                thisSerializer.writeInt32(value_1_bottom_value)
            }
            const value_1_left = value_1.left
            let value_1_left_type: int32 = RuntimeType.UNDEFINED
            value_1_left_type = runtimeType(value_1_left)
            thisSerializer.writeInt8(value_1_left_type)
            if ((RuntimeType.UNDEFINED) != (value_1_left_type)) {
                const value_1_left_value = value_1_left!
                thisSerializer.writeInt32(value_1_left_value)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_outlineStyle(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    outlineWidthAttribute(value: Dimension | EdgeOutlineWidths): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.NUMBER) == (value_type)) || ((RuntimeType.STRING) == (value_type)) || (((RuntimeType.OBJECT) == (value_type)) && (isResource(value)))) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<Dimension>(value)
            thisSerializer.writeLength(value_0)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (((value!.hasOwnProperty("top")) || (value!.hasOwnProperty("right")) || (value!.hasOwnProperty("bottom")) || (value!.hasOwnProperty("left"))))) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<EdgeOutlineWidths>(value)
            const value_1_top = value_1.top
            let value_1_top_type: int32 = RuntimeType.UNDEFINED
            value_1_top_type = runtimeType(value_1_top)
            thisSerializer.writeInt8(value_1_top_type)
            if ((RuntimeType.UNDEFINED) != (value_1_top_type)) {
                const value_1_top_value = value_1_top!
                thisSerializer.writeLength(value_1_top_value)
            }
            const value_1_right = value_1.right
            let value_1_right_type: int32 = RuntimeType.UNDEFINED
            value_1_right_type = runtimeType(value_1_right)
            thisSerializer.writeInt8(value_1_right_type)
            if ((RuntimeType.UNDEFINED) != (value_1_right_type)) {
                const value_1_right_value = value_1_right!
                thisSerializer.writeLength(value_1_right_value)
            }
            const value_1_bottom = value_1.bottom
            let value_1_bottom_type: int32 = RuntimeType.UNDEFINED
            value_1_bottom_type = runtimeType(value_1_bottom)
            thisSerializer.writeInt8(value_1_bottom_type)
            if ((RuntimeType.UNDEFINED) != (value_1_bottom_type)) {
                const value_1_bottom_value = value_1_bottom!
                thisSerializer.writeLength(value_1_bottom_value)
            }
            const value_1_left = value_1.left
            let value_1_left_type: int32 = RuntimeType.UNDEFINED
            value_1_left_type = runtimeType(value_1_left)
            thisSerializer.writeInt8(value_1_left_type)
            if ((RuntimeType.UNDEFINED) != (value_1_left_type)) {
                const value_1_left_value = value_1_left!
                thisSerializer.writeLength(value_1_left_value)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_outlineWidth(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    outlineColorAttribute(value: ResourceColor | EdgeColors | LocalizedEdgeColors): void {
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
        else if (((RuntimeType.OBJECT) == (value_type)) && (((value!.hasOwnProperty("right")) || (value!.hasOwnProperty("left"))))) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<EdgeColors>(value)
            const value_1_top = value_1.top
            let value_1_top_type: int32 = RuntimeType.UNDEFINED
            value_1_top_type = runtimeType(value_1_top)
            thisSerializer.writeInt8(value_1_top_type)
            if ((RuntimeType.UNDEFINED) != (value_1_top_type)) {
                const value_1_top_value = value_1_top!
                let value_1_top_value_type: int32 = RuntimeType.UNDEFINED
                value_1_top_value_type = runtimeType(value_1_top_value)
                if (((RuntimeType.NUMBER) == (value_1_top_value_type)) && ((unsafeCast<int32>(value_1_top_value)) >= (0)) && ((unsafeCast<int32>(value_1_top_value)) <= (11))) {
                    thisSerializer.writeInt8(0)
                    const value_1_top_value_0 = unsafeCast<Color>(value_1_top_value)
                    thisSerializer.writeInt32(value_1_top_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_top_value_type) {
                    thisSerializer.writeInt8(1)
                    const value_1_top_value_1 = unsafeCast<number>(value_1_top_value)
                    thisSerializer.writeNumber(value_1_top_value_1)
                }
                else if (RuntimeType.STRING == value_1_top_value_type) {
                    thisSerializer.writeInt8(2)
                    const value_1_top_value_2 = unsafeCast<string>(value_1_top_value)
                    thisSerializer.writeString(value_1_top_value_2)
                }
                else if (RuntimeType.OBJECT == value_1_top_value_type) {
                    thisSerializer.writeInt8(3)
                    const value_1_top_value_3 = unsafeCast<Resource>(value_1_top_value)
                    thisSerializer.writeResource(value_1_top_value_3)
                }
            }
            const value_1_right = value_1.right
            let value_1_right_type: int32 = RuntimeType.UNDEFINED
            value_1_right_type = runtimeType(value_1_right)
            thisSerializer.writeInt8(value_1_right_type)
            if ((RuntimeType.UNDEFINED) != (value_1_right_type)) {
                const value_1_right_value = value_1_right!
                let value_1_right_value_type: int32 = RuntimeType.UNDEFINED
                value_1_right_value_type = runtimeType(value_1_right_value)
                if (((RuntimeType.NUMBER) == (value_1_right_value_type)) && ((unsafeCast<int32>(value_1_right_value)) >= (0)) && ((unsafeCast<int32>(value_1_right_value)) <= (11))) {
                    thisSerializer.writeInt8(0)
                    const value_1_right_value_0 = unsafeCast<Color>(value_1_right_value)
                    thisSerializer.writeInt32(value_1_right_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_right_value_type) {
                    thisSerializer.writeInt8(1)
                    const value_1_right_value_1 = unsafeCast<number>(value_1_right_value)
                    thisSerializer.writeNumber(value_1_right_value_1)
                }
                else if (RuntimeType.STRING == value_1_right_value_type) {
                    thisSerializer.writeInt8(2)
                    const value_1_right_value_2 = unsafeCast<string>(value_1_right_value)
                    thisSerializer.writeString(value_1_right_value_2)
                }
                else if (RuntimeType.OBJECT == value_1_right_value_type) {
                    thisSerializer.writeInt8(3)
                    const value_1_right_value_3 = unsafeCast<Resource>(value_1_right_value)
                    thisSerializer.writeResource(value_1_right_value_3)
                }
            }
            const value_1_bottom = value_1.bottom
            let value_1_bottom_type: int32 = RuntimeType.UNDEFINED
            value_1_bottom_type = runtimeType(value_1_bottom)
            thisSerializer.writeInt8(value_1_bottom_type)
            if ((RuntimeType.UNDEFINED) != (value_1_bottom_type)) {
                const value_1_bottom_value = value_1_bottom!
                let value_1_bottom_value_type: int32 = RuntimeType.UNDEFINED
                value_1_bottom_value_type = runtimeType(value_1_bottom_value)
                if (((RuntimeType.NUMBER) == (value_1_bottom_value_type)) && ((unsafeCast<int32>(value_1_bottom_value)) >= (0)) && ((unsafeCast<int32>(value_1_bottom_value)) <= (11))) {
                    thisSerializer.writeInt8(0)
                    const value_1_bottom_value_0 = unsafeCast<Color>(value_1_bottom_value)
                    thisSerializer.writeInt32(value_1_bottom_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_bottom_value_type) {
                    thisSerializer.writeInt8(1)
                    const value_1_bottom_value_1 = unsafeCast<number>(value_1_bottom_value)
                    thisSerializer.writeNumber(value_1_bottom_value_1)
                }
                else if (RuntimeType.STRING == value_1_bottom_value_type) {
                    thisSerializer.writeInt8(2)
                    const value_1_bottom_value_2 = unsafeCast<string>(value_1_bottom_value)
                    thisSerializer.writeString(value_1_bottom_value_2)
                }
                else if (RuntimeType.OBJECT == value_1_bottom_value_type) {
                    thisSerializer.writeInt8(3)
                    const value_1_bottom_value_3 = unsafeCast<Resource>(value_1_bottom_value)
                    thisSerializer.writeResource(value_1_bottom_value_3)
                }
            }
            const value_1_left = value_1.left
            let value_1_left_type: int32 = RuntimeType.UNDEFINED
            value_1_left_type = runtimeType(value_1_left)
            thisSerializer.writeInt8(value_1_left_type)
            if ((RuntimeType.UNDEFINED) != (value_1_left_type)) {
                const value_1_left_value = value_1_left!
                let value_1_left_value_type: int32 = RuntimeType.UNDEFINED
                value_1_left_value_type = runtimeType(value_1_left_value)
                if (((RuntimeType.NUMBER) == (value_1_left_value_type)) && ((unsafeCast<int32>(value_1_left_value)) >= (0)) && ((unsafeCast<int32>(value_1_left_value)) <= (11))) {
                    thisSerializer.writeInt8(0)
                    const value_1_left_value_0 = unsafeCast<Color>(value_1_left_value)
                    thisSerializer.writeInt32(value_1_left_value_0)
                }
                else if (RuntimeType.NUMBER == value_1_left_value_type) {
                    thisSerializer.writeInt8(1)
                    const value_1_left_value_1 = unsafeCast<number>(value_1_left_value)
                    thisSerializer.writeNumber(value_1_left_value_1)
                }
                else if (RuntimeType.STRING == value_1_left_value_type) {
                    thisSerializer.writeInt8(2)
                    const value_1_left_value_2 = unsafeCast<string>(value_1_left_value)
                    thisSerializer.writeString(value_1_left_value_2)
                }
                else if (RuntimeType.OBJECT == value_1_left_value_type) {
                    thisSerializer.writeInt8(3)
                    const value_1_left_value_3 = unsafeCast<Resource>(value_1_left_value)
                    thisSerializer.writeResource(value_1_left_value_3)
                }
            }
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (((value!.hasOwnProperty("end")) || (value!.hasOwnProperty("start"))))) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<LocalizedEdgeColors>(value)
            thisSerializer.writeLocalizedEdgeColors(value_2)
        }
        ArkUIGeneratedNativeModule._CommonMethod_outlineColor(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    outlineRadiusAttribute(value: Dimension | OutlineRadiuses): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.NUMBER) == (value_type)) || ((RuntimeType.STRING) == (value_type)) || (((RuntimeType.OBJECT) == (value_type)) && (isResource(value)))) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<Dimension>(value)
            thisSerializer.writeLength(value_0)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (((value!.hasOwnProperty("topLeft")) || (value!.hasOwnProperty("topRight")) || (value!.hasOwnProperty("bottomLeft")) || (value!.hasOwnProperty("bottomRight"))))) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<OutlineRadiuses>(value)
            const value_1_topLeft = value_1.topLeft
            let value_1_topLeft_type: int32 = RuntimeType.UNDEFINED
            value_1_topLeft_type = runtimeType(value_1_topLeft)
            thisSerializer.writeInt8(value_1_topLeft_type)
            if ((RuntimeType.UNDEFINED) != (value_1_topLeft_type)) {
                const value_1_topLeft_value = value_1_topLeft!
                thisSerializer.writeLength(value_1_topLeft_value)
            }
            const value_1_topRight = value_1.topRight
            let value_1_topRight_type: int32 = RuntimeType.UNDEFINED
            value_1_topRight_type = runtimeType(value_1_topRight)
            thisSerializer.writeInt8(value_1_topRight_type)
            if ((RuntimeType.UNDEFINED) != (value_1_topRight_type)) {
                const value_1_topRight_value = value_1_topRight!
                thisSerializer.writeLength(value_1_topRight_value)
            }
            const value_1_bottomLeft = value_1.bottomLeft
            let value_1_bottomLeft_type: int32 = RuntimeType.UNDEFINED
            value_1_bottomLeft_type = runtimeType(value_1_bottomLeft)
            thisSerializer.writeInt8(value_1_bottomLeft_type)
            if ((RuntimeType.UNDEFINED) != (value_1_bottomLeft_type)) {
                const value_1_bottomLeft_value = value_1_bottomLeft!
                thisSerializer.writeLength(value_1_bottomLeft_value)
            }
            const value_1_bottomRight = value_1.bottomRight
            let value_1_bottomRight_type: int32 = RuntimeType.UNDEFINED
            value_1_bottomRight_type = runtimeType(value_1_bottomRight)
            thisSerializer.writeInt8(value_1_bottomRight_type)
            if ((RuntimeType.UNDEFINED) != (value_1_bottomRight_type)) {
                const value_1_bottomRight_value = value_1_bottomRight!
                thisSerializer.writeLength(value_1_bottomRight_value)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_outlineRadius(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    foregroundColorAttribute(value: ResourceColor | ColoringStrategy): void {
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
        else if (((RuntimeType.STRING) == (value_type)) && ((Object.values(ColoringStrategy).indexOf((value as ColoringStrategy))) >= (0)) && ((Object.values(ColoringStrategy).indexOf((value as ColoringStrategy))) <= (2))) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<ColoringStrategy>(value)
            thisSerializer.writeInt32(Object.values(ColoringStrategy).indexOf(value_1))
        }
        ArkUIGeneratedNativeModule._CommonMethod_foregroundColor(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onClick0Attribute(value: ((event: ClickEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onClick0(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onClick1Attribute(event: ((event: ClickEvent) => void), distanceThreshold: number): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(event)
        ArkUIGeneratedNativeModule._CommonMethod_onClick1(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length(), distanceThreshold)
        thisSerializer.release()
    }
    onHoverAttribute(value: ((isHover: boolean, event: HoverEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onHover(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onAccessibilityHoverAttribute(value: AccessibilityCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onAccessibilityHover(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    hoverEffectAttribute(value: HoverEffect): void {
        ArkUIGeneratedNativeModule._CommonMethod_hoverEffect(this.peer.ptr, value)
    }
    onMouseAttribute(value: ((event: MouseEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onMouse(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onTouchAttribute(value: ((event: TouchEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onTouch(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onKeyEventAttribute(value: ((event: KeyEvent) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onKeyEvent(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onKeyPreImeAttribute(value: ((parameter: KeyEvent) => boolean)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onKeyPreIme(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    focusableAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_focusable(this.peer.ptr, +value)
    }
    onFocusAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onFocus(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onBlurAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onBlur(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    tabIndexAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_tabIndex(this.peer.ptr, value)
    }
    defaultFocusAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_defaultFocus(this.peer.ptr, +value)
    }
    groupDefaultFocusAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_groupDefaultFocus(this.peer.ptr, +value)
    }
    focusOnTouchAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_focusOnTouch(this.peer.ptr, +value)
    }
    focusBoxAttribute(value: FocusBoxStyle): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeFocusBoxStyle(value)
        ArkUIGeneratedNativeModule._CommonMethod_focusBox(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    animationAttribute(value: AnimateParam): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeAnimateParam(value)
        ArkUIGeneratedNativeModule._CommonMethod_animation(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    transition0Attribute(value: TransitionOptions | TransitionEffect): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.OBJECT) == (value_type)) && (((value!.hasOwnProperty("type")) || (value!.hasOwnProperty("opacity")) || (value!.hasOwnProperty("translate")) || (value!.hasOwnProperty("scale")) || (value!.hasOwnProperty("rotate"))))) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<TransitionOptions>(value)
            thisSerializer.writeTransitionOptions(value_0)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (value instanceof TransitionEffect)) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<TransitionEffect>(value)
            thisSerializer.writeTransitionEffect(value_1)
        }
        ArkUIGeneratedNativeModule._CommonMethod_transition0(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    transition1Attribute(effect: TransitionEffect, onFinish?: TransitionFinishCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        let onFinish_type: int32 = RuntimeType.UNDEFINED
        onFinish_type = runtimeType(onFinish)
        thisSerializer.writeInt8(onFinish_type)
        if ((RuntimeType.UNDEFINED) != (onFinish_type)) {
            const onFinish_value = onFinish!
            thisSerializer.holdAndWriteCallback(onFinish_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_transition1(this.peer.ptr, toPeerPtr(effect), thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    motionBlurAttribute(value: MotionBlurOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeMotionBlurOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_motionBlur(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    brightnessAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_brightness(this.peer.ptr, value)
    }
    contrastAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_contrast(this.peer.ptr, value)
    }
    grayscaleAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_grayscale(this.peer.ptr, value)
    }
    colorBlendAttribute(value: Color | string | Resource): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<Color>(value)
            thisSerializer.writeInt32(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<string>(value)
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._CommonMethod_colorBlend(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    saturateAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_saturate(this.peer.ptr, value)
    }
    sepiaAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_sepia(this.peer.ptr, value)
    }
    invertAttribute(value: number | InvertOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<InvertOptions>(value)
            thisSerializer.writeInvertOptions(value_1)
        }
        ArkUIGeneratedNativeModule._CommonMethod_invert(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    hueRotateAttribute(value: number | string): void {
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
        ArkUIGeneratedNativeModule._CommonMethod_hueRotate(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    useShadowBatchingAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_useShadowBatching(this.peer.ptr, +value)
    }
    useEffect0Attribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_useEffect0(this.peer.ptr, +value)
    }
    useEffect1Attribute(useEffect: boolean, effectType: EffectType): void {
        ArkUIGeneratedNativeModule._CommonMethod_useEffect1(this.peer.ptr, +useEffect, effectType)
    }
    renderGroupAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_renderGroup(this.peer.ptr, +value)
    }
    freezeAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_freeze(this.peer.ptr, +value)
    }
    translateAttribute(value: TranslateOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeTranslateOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_translate(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    scaleAttribute(value: ScaleOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeScaleOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_scale(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    gridSpanAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_gridSpan(this.peer.ptr, value)
    }
    gridOffsetAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_gridOffset(this.peer.ptr, value)
    }
    rotateAttribute(value: RotateOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeRotateOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_rotate(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    transformAttribute(value: Object): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeCustomObject("Object", value)
        ArkUIGeneratedNativeModule._CommonMethod_transform(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onAppearAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onAppear(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onDisAppearAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onDisAppear(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onAttachAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onAttach(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onDetachAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onDetach(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onAreaChangeAttribute(value: ((oldValue: Area, newValue: Area) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onAreaChange(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    visibilityAttribute(value: Visibility): void {
        ArkUIGeneratedNativeModule._CommonMethod_visibility(this.peer.ptr, value)
    }
    flexGrowAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_flexGrow(this.peer.ptr, value)
    }
    flexShrinkAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_flexShrink(this.peer.ptr, value)
    }
    flexBasisAttribute(value: number | string): void {
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
        ArkUIGeneratedNativeModule._CommonMethod_flexBasis(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    alignSelfAttribute(value: ItemAlign): void {
        ArkUIGeneratedNativeModule._CommonMethod_alignSelf(this.peer.ptr, value)
    }
    displayPriorityAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_displayPriority(this.peer.ptr, value)
    }
    zIndexAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_zIndex(this.peer.ptr, value)
    }
    directionAttribute(value: Direction): void {
        ArkUIGeneratedNativeModule._CommonMethod_direction(this.peer.ptr, value)
    }
    alignAttribute(value: Alignment): void {
        ArkUIGeneratedNativeModule._CommonMethod_align(this.peer.ptr, value)
    }
    positionAttribute(value: Position | Edges | LocalizedEdges): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.OBJECT) == (value_type)) && (((value!.hasOwnProperty("x")) || (value!.hasOwnProperty("y"))))) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<Position>(value)
            thisSerializer.writePosition(value_0)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (((value!.hasOwnProperty("left")) || (value!.hasOwnProperty("right"))))) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<Edges>(value)
            thisSerializer.writeEdges(value_1)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (((value!.hasOwnProperty("start")) || (value!.hasOwnProperty("end"))))) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<LocalizedEdges>(value)
            thisSerializer.writeLocalizedEdges(value_2)
        }
        ArkUIGeneratedNativeModule._CommonMethod_position(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    markAnchorAttribute(value: Position | LocalizedPosition): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.OBJECT) == (value_type)) && (((value!.hasOwnProperty("x")) || (value!.hasOwnProperty("y"))))) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<Position>(value)
            thisSerializer.writePosition(value_0)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (((value!.hasOwnProperty("start")) || (value!.hasOwnProperty("top"))))) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<LocalizedPosition>(value)
            thisSerializer.writeLocalizedPosition(value_1)
        }
        ArkUIGeneratedNativeModule._CommonMethod_markAnchor(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    offsetAttribute(value: Position | Edges | LocalizedEdges): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.OBJECT) == (value_type)) && (((value!.hasOwnProperty("x")) || (value!.hasOwnProperty("y"))))) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<Position>(value)
            thisSerializer.writePosition(value_0)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (((value!.hasOwnProperty("left")) || (value!.hasOwnProperty("right"))))) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<Edges>(value)
            thisSerializer.writeEdges(value_1)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (((value!.hasOwnProperty("start")) || (value!.hasOwnProperty("end"))))) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<LocalizedEdges>(value)
            thisSerializer.writeLocalizedEdges(value_2)
        }
        ArkUIGeneratedNativeModule._CommonMethod_offset(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    enabledAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_enabled(this.peer.ptr, +value)
    }
    useSizeTypeAttribute(value: { xs?: number | { span: number, offset: number }, sm?: number | { span: number, offset: number }, md?: number | { span: number, offset: number }, lg?: number | { span: number, offset: number } }): void {
        const thisSerializer: Serializer = Serializer.hold()
        const value_xs = value.xs
        let value_xs_type: int32 = RuntimeType.UNDEFINED
        value_xs_type = runtimeType(value_xs)
        thisSerializer.writeInt8(value_xs_type)
        if ((RuntimeType.UNDEFINED) != (value_xs_type)) {
            const value_xs_value = value_xs!
            let value_xs_value_type: int32 = RuntimeType.UNDEFINED
            value_xs_value_type = runtimeType(value_xs_value)
            if (RuntimeType.NUMBER == value_xs_value_type) {
                thisSerializer.writeInt8(0)
                const value_xs_value_0 = unsafeCast<number>(value_xs_value)
                thisSerializer.writeNumber(value_xs_value_0)
            }
            else if (RuntimeType.OBJECT == value_xs_value_type) {
                thisSerializer.writeInt8(1)
                const value_xs_value_1 = unsafeCast<{ span: number, offset: number }>(value_xs_value)
                const value_xs_value_1_span = value_xs_value_1.span
                thisSerializer.writeNumber(value_xs_value_1_span)
                const value_xs_value_1_offset = value_xs_value_1.offset
                thisSerializer.writeNumber(value_xs_value_1_offset)
            }
        }
        const value_sm = value.sm
        let value_sm_type: int32 = RuntimeType.UNDEFINED
        value_sm_type = runtimeType(value_sm)
        thisSerializer.writeInt8(value_sm_type)
        if ((RuntimeType.UNDEFINED) != (value_sm_type)) {
            const value_sm_value = value_sm!
            let value_sm_value_type: int32 = RuntimeType.UNDEFINED
            value_sm_value_type = runtimeType(value_sm_value)
            if (RuntimeType.NUMBER == value_sm_value_type) {
                thisSerializer.writeInt8(0)
                const value_sm_value_0 = unsafeCast<number>(value_sm_value)
                thisSerializer.writeNumber(value_sm_value_0)
            }
            else if (RuntimeType.OBJECT == value_sm_value_type) {
                thisSerializer.writeInt8(1)
                const value_sm_value_1 = unsafeCast<{ span: number, offset: number }>(value_sm_value)
                const value_sm_value_1_span = value_sm_value_1.span
                thisSerializer.writeNumber(value_sm_value_1_span)
                const value_sm_value_1_offset = value_sm_value_1.offset
                thisSerializer.writeNumber(value_sm_value_1_offset)
            }
        }
        const value_md = value.md
        let value_md_type: int32 = RuntimeType.UNDEFINED
        value_md_type = runtimeType(value_md)
        thisSerializer.writeInt8(value_md_type)
        if ((RuntimeType.UNDEFINED) != (value_md_type)) {
            const value_md_value = value_md!
            let value_md_value_type: int32 = RuntimeType.UNDEFINED
            value_md_value_type = runtimeType(value_md_value)
            if (RuntimeType.NUMBER == value_md_value_type) {
                thisSerializer.writeInt8(0)
                const value_md_value_0 = unsafeCast<number>(value_md_value)
                thisSerializer.writeNumber(value_md_value_0)
            }
            else if (RuntimeType.OBJECT == value_md_value_type) {
                thisSerializer.writeInt8(1)
                const value_md_value_1 = unsafeCast<{ span: number, offset: number }>(value_md_value)
                const value_md_value_1_span = value_md_value_1.span
                thisSerializer.writeNumber(value_md_value_1_span)
                const value_md_value_1_offset = value_md_value_1.offset
                thisSerializer.writeNumber(value_md_value_1_offset)
            }
        }
        const value_lg = value.lg
        let value_lg_type: int32 = RuntimeType.UNDEFINED
        value_lg_type = runtimeType(value_lg)
        thisSerializer.writeInt8(value_lg_type)
        if ((RuntimeType.UNDEFINED) != (value_lg_type)) {
            const value_lg_value = value_lg!
            let value_lg_value_type: int32 = RuntimeType.UNDEFINED
            value_lg_value_type = runtimeType(value_lg_value)
            if (RuntimeType.NUMBER == value_lg_value_type) {
                thisSerializer.writeInt8(0)
                const value_lg_value_0 = unsafeCast<number>(value_lg_value)
                thisSerializer.writeNumber(value_lg_value_0)
            }
            else if (RuntimeType.OBJECT == value_lg_value_type) {
                thisSerializer.writeInt8(1)
                const value_lg_value_1 = unsafeCast<{ span: number, offset: number }>(value_lg_value)
                const value_lg_value_1_span = value_lg_value_1.span
                thisSerializer.writeNumber(value_lg_value_1_span)
                const value_lg_value_1_offset = value_lg_value_1.offset
                thisSerializer.writeNumber(value_lg_value_1_offset)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_useSizeType(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    alignRules0Attribute(value: AlignRuleOption): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeAlignRuleOption(value)
        ArkUIGeneratedNativeModule._CommonMethod_alignRules0(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    alignRules1Attribute(value: LocalizedAlignRuleOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeLocalizedAlignRuleOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_alignRules1(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    aspectRatioAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_aspectRatio(this.peer.ptr, value)
    }
    clickEffectAttribute(value?: ClickEffect): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            thisSerializer.writeClickEffect(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_clickEffect(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onDragStartAttribute(value: ((event: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onDragStart(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onDragEnterAttribute(value: ((event: DragEvent, extraParams?: string) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onDragEnter(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onDragMoveAttribute(value: ((event: DragEvent, extraParams?: string) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onDragMove(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onDragLeaveAttribute(value: ((event: DragEvent, extraParams?: string) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onDragLeave(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onDropAttribute(value: ((event: DragEvent, extraParams?: string) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onDrop(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onDragEndAttribute(value: ((event: DragEvent, extraParams?: string) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onDragEnd(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    allowDropAttribute(value?: Array<UniformDataType>): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            thisSerializer.writeInt32(value_value.length)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element: UniformDataType = value_value[i]
                thisSerializer.writeUniformDataType(value_value_element)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_allowDrop(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    draggableAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_draggable(this.peer.ptr, +value)
    }
    dragPreviewAttribute(value: CustomBuilder | DragItemInfo | string): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.FUNCTION == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<CustomBuilder>(value)
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_0))
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<DragItemInfo>(value)
            thisSerializer.writeDragItemInfo(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<string>(value)
            thisSerializer.writeString(value_2)
        }
        ArkUIGeneratedNativeModule._CommonMethod_dragPreview(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onPreDragAttribute(value: ((parameter: PreDragStatus) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onPreDrag(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    linearGradientAttribute(value: { angle?: number | string, direction?: GradientDirection, colors: Array<[ ResourceColor, number ]>, repeating?: boolean }): void {
        const thisSerializer: Serializer = Serializer.hold()
        const value_angle = value.angle
        let value_angle_type: int32 = RuntimeType.UNDEFINED
        value_angle_type = runtimeType(value_angle)
        thisSerializer.writeInt8(value_angle_type)
        if ((RuntimeType.UNDEFINED) != (value_angle_type)) {
            const value_angle_value = value_angle!
            let value_angle_value_type: int32 = RuntimeType.UNDEFINED
            value_angle_value_type = runtimeType(value_angle_value)
            if (RuntimeType.NUMBER == value_angle_value_type) {
                thisSerializer.writeInt8(0)
                const value_angle_value_0 = unsafeCast<number>(value_angle_value)
                thisSerializer.writeNumber(value_angle_value_0)
            }
            else if (RuntimeType.STRING == value_angle_value_type) {
                thisSerializer.writeInt8(1)
                const value_angle_value_1 = unsafeCast<string>(value_angle_value)
                thisSerializer.writeString(value_angle_value_1)
            }
        }
        const value_direction = value.direction
        let value_direction_type: int32 = RuntimeType.UNDEFINED
        value_direction_type = runtimeType(value_direction)
        thisSerializer.writeInt8(value_direction_type)
        if ((RuntimeType.UNDEFINED) != (value_direction_type)) {
            const value_direction_value = value_direction!
            thisSerializer.writeInt32(value_direction_value)
        }
        const value_colors = value.colors
        thisSerializer.writeInt32(value_colors.length)
        for (let i = 0; i < value_colors.length; i++) {
            const value_colors_element: [ ResourceColor, number ] = value_colors[i]
            const value_colors_element_0 = value_colors_element[0]
            let value_colors_element_0_type: int32 = RuntimeType.UNDEFINED
            value_colors_element_0_type = runtimeType(value_colors_element_0)
            if (((RuntimeType.NUMBER) == (value_colors_element_0_type)) && ((unsafeCast<int32>(value_colors_element_0)) >= (0)) && ((unsafeCast<int32>(value_colors_element_0)) <= (11))) {
                thisSerializer.writeInt8(0)
                const value_colors_element_0_0 = unsafeCast<Color>(value_colors_element_0)
                thisSerializer.writeInt32(value_colors_element_0_0)
            }
            else if (RuntimeType.NUMBER == value_colors_element_0_type) {
                thisSerializer.writeInt8(1)
                const value_colors_element_0_1 = unsafeCast<number>(value_colors_element_0)
                thisSerializer.writeNumber(value_colors_element_0_1)
            }
            else if (RuntimeType.STRING == value_colors_element_0_type) {
                thisSerializer.writeInt8(2)
                const value_colors_element_0_2 = unsafeCast<string>(value_colors_element_0)
                thisSerializer.writeString(value_colors_element_0_2)
            }
            else if (RuntimeType.OBJECT == value_colors_element_0_type) {
                thisSerializer.writeInt8(3)
                const value_colors_element_0_3 = unsafeCast<Resource>(value_colors_element_0)
                thisSerializer.writeResource(value_colors_element_0_3)
            }
            const value_colors_element_1 = value_colors_element[1]
            thisSerializer.writeNumber(value_colors_element_1)
        }
        const value_repeating = value.repeating
        let value_repeating_type: int32 = RuntimeType.UNDEFINED
        value_repeating_type = runtimeType(value_repeating)
        thisSerializer.writeInt8(value_repeating_type)
        if ((RuntimeType.UNDEFINED) != (value_repeating_type)) {
            const value_repeating_value = value_repeating!
            thisSerializer.writeBoolean(value_repeating_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_linearGradient(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    sweepGradientAttribute(value: { center: [ Length, Length ], start?: number | string, end?: number | string, rotation?: number | string, colors: Array<[ ResourceColor, number ]>, repeating?: boolean }): void {
        const thisSerializer: Serializer = Serializer.hold()
        const value_center = value.center
        const value_center_0 = value_center[0]
        thisSerializer.writeLength(value_center_0)
        const value_center_1 = value_center[1]
        thisSerializer.writeLength(value_center_1)
        const value_start = value.start
        let value_start_type: int32 = RuntimeType.UNDEFINED
        value_start_type = runtimeType(value_start)
        thisSerializer.writeInt8(value_start_type)
        if ((RuntimeType.UNDEFINED) != (value_start_type)) {
            const value_start_value = value_start!
            let value_start_value_type: int32 = RuntimeType.UNDEFINED
            value_start_value_type = runtimeType(value_start_value)
            if (RuntimeType.NUMBER == value_start_value_type) {
                thisSerializer.writeInt8(0)
                const value_start_value_0 = unsafeCast<number>(value_start_value)
                thisSerializer.writeNumber(value_start_value_0)
            }
            else if (RuntimeType.STRING == value_start_value_type) {
                thisSerializer.writeInt8(1)
                const value_start_value_1 = unsafeCast<string>(value_start_value)
                thisSerializer.writeString(value_start_value_1)
            }
        }
        const value_end = value.end
        let value_end_type: int32 = RuntimeType.UNDEFINED
        value_end_type = runtimeType(value_end)
        thisSerializer.writeInt8(value_end_type)
        if ((RuntimeType.UNDEFINED) != (value_end_type)) {
            const value_end_value = value_end!
            let value_end_value_type: int32 = RuntimeType.UNDEFINED
            value_end_value_type = runtimeType(value_end_value)
            if (RuntimeType.NUMBER == value_end_value_type) {
                thisSerializer.writeInt8(0)
                const value_end_value_0 = unsafeCast<number>(value_end_value)
                thisSerializer.writeNumber(value_end_value_0)
            }
            else if (RuntimeType.STRING == value_end_value_type) {
                thisSerializer.writeInt8(1)
                const value_end_value_1 = unsafeCast<string>(value_end_value)
                thisSerializer.writeString(value_end_value_1)
            }
        }
        const value_rotation = value.rotation
        let value_rotation_type: int32 = RuntimeType.UNDEFINED
        value_rotation_type = runtimeType(value_rotation)
        thisSerializer.writeInt8(value_rotation_type)
        if ((RuntimeType.UNDEFINED) != (value_rotation_type)) {
            const value_rotation_value = value_rotation!
            let value_rotation_value_type: int32 = RuntimeType.UNDEFINED
            value_rotation_value_type = runtimeType(value_rotation_value)
            if (RuntimeType.NUMBER == value_rotation_value_type) {
                thisSerializer.writeInt8(0)
                const value_rotation_value_0 = unsafeCast<number>(value_rotation_value)
                thisSerializer.writeNumber(value_rotation_value_0)
            }
            else if (RuntimeType.STRING == value_rotation_value_type) {
                thisSerializer.writeInt8(1)
                const value_rotation_value_1 = unsafeCast<string>(value_rotation_value)
                thisSerializer.writeString(value_rotation_value_1)
            }
        }
        const value_colors = value.colors
        thisSerializer.writeInt32(value_colors.length)
        for (let i = 0; i < value_colors.length; i++) {
            const value_colors_element: [ ResourceColor, number ] = value_colors[i]
            const value_colors_element_0 = value_colors_element[0]
            let value_colors_element_0_type: int32 = RuntimeType.UNDEFINED
            value_colors_element_0_type = runtimeType(value_colors_element_0)
            if (((RuntimeType.NUMBER) == (value_colors_element_0_type)) && ((unsafeCast<int32>(value_colors_element_0)) >= (0)) && ((unsafeCast<int32>(value_colors_element_0)) <= (11))) {
                thisSerializer.writeInt8(0)
                const value_colors_element_0_0 = unsafeCast<Color>(value_colors_element_0)
                thisSerializer.writeInt32(value_colors_element_0_0)
            }
            else if (RuntimeType.NUMBER == value_colors_element_0_type) {
                thisSerializer.writeInt8(1)
                const value_colors_element_0_1 = unsafeCast<number>(value_colors_element_0)
                thisSerializer.writeNumber(value_colors_element_0_1)
            }
            else if (RuntimeType.STRING == value_colors_element_0_type) {
                thisSerializer.writeInt8(2)
                const value_colors_element_0_2 = unsafeCast<string>(value_colors_element_0)
                thisSerializer.writeString(value_colors_element_0_2)
            }
            else if (RuntimeType.OBJECT == value_colors_element_0_type) {
                thisSerializer.writeInt8(3)
                const value_colors_element_0_3 = unsafeCast<Resource>(value_colors_element_0)
                thisSerializer.writeResource(value_colors_element_0_3)
            }
            const value_colors_element_1 = value_colors_element[1]
            thisSerializer.writeNumber(value_colors_element_1)
        }
        const value_repeating = value.repeating
        let value_repeating_type: int32 = RuntimeType.UNDEFINED
        value_repeating_type = runtimeType(value_repeating)
        thisSerializer.writeInt8(value_repeating_type)
        if ((RuntimeType.UNDEFINED) != (value_repeating_type)) {
            const value_repeating_value = value_repeating!
            thisSerializer.writeBoolean(value_repeating_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_sweepGradient(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    radialGradientAttribute(value: { center: [ Length, Length ], radius: number | string, colors: Array<[ ResourceColor, number ]>, repeating?: boolean }): void {
        const thisSerializer: Serializer = Serializer.hold()
        const value_center = value.center
        const value_center_0 = value_center[0]
        thisSerializer.writeLength(value_center_0)
        const value_center_1 = value_center[1]
        thisSerializer.writeLength(value_center_1)
        const value_radius = value.radius
        let value_radius_type: int32 = RuntimeType.UNDEFINED
        value_radius_type = runtimeType(value_radius)
        if (RuntimeType.NUMBER == value_radius_type) {
            thisSerializer.writeInt8(0)
            const value_radius_0 = unsafeCast<number>(value_radius)
            thisSerializer.writeNumber(value_radius_0)
        }
        else if (RuntimeType.STRING == value_radius_type) {
            thisSerializer.writeInt8(1)
            const value_radius_1 = unsafeCast<string>(value_radius)
            thisSerializer.writeString(value_radius_1)
        }
        const value_colors = value.colors
        thisSerializer.writeInt32(value_colors.length)
        for (let i = 0; i < value_colors.length; i++) {
            const value_colors_element: [ ResourceColor, number ] = value_colors[i]
            const value_colors_element_0 = value_colors_element[0]
            let value_colors_element_0_type: int32 = RuntimeType.UNDEFINED
            value_colors_element_0_type = runtimeType(value_colors_element_0)
            if (((RuntimeType.NUMBER) == (value_colors_element_0_type)) && ((unsafeCast<int32>(value_colors_element_0)) >= (0)) && ((unsafeCast<int32>(value_colors_element_0)) <= (11))) {
                thisSerializer.writeInt8(0)
                const value_colors_element_0_0 = unsafeCast<Color>(value_colors_element_0)
                thisSerializer.writeInt32(value_colors_element_0_0)
            }
            else if (RuntimeType.NUMBER == value_colors_element_0_type) {
                thisSerializer.writeInt8(1)
                const value_colors_element_0_1 = unsafeCast<number>(value_colors_element_0)
                thisSerializer.writeNumber(value_colors_element_0_1)
            }
            else if (RuntimeType.STRING == value_colors_element_0_type) {
                thisSerializer.writeInt8(2)
                const value_colors_element_0_2 = unsafeCast<string>(value_colors_element_0)
                thisSerializer.writeString(value_colors_element_0_2)
            }
            else if (RuntimeType.OBJECT == value_colors_element_0_type) {
                thisSerializer.writeInt8(3)
                const value_colors_element_0_3 = unsafeCast<Resource>(value_colors_element_0)
                thisSerializer.writeResource(value_colors_element_0_3)
            }
            const value_colors_element_1 = value_colors_element[1]
            thisSerializer.writeNumber(value_colors_element_1)
        }
        const value_repeating = value.repeating
        let value_repeating_type: int32 = RuntimeType.UNDEFINED
        value_repeating_type = runtimeType(value_repeating)
        thisSerializer.writeInt8(value_repeating_type)
        if ((RuntimeType.UNDEFINED) != (value_repeating_type)) {
            const value_repeating_value = value_repeating!
            thisSerializer.writeBoolean(value_repeating_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_radialGradient(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    motionPathAttribute(value: MotionPathOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeMotionPathOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_motionPath(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    shadowAttribute(value: ShadowOptions | ShadowStyle): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<ShadowOptions>(value)
            thisSerializer.writeShadowOptions(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<ShadowStyle>(value)
            thisSerializer.writeInt32(value_1)
        }
        ArkUIGeneratedNativeModule._CommonMethod_shadow(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    clip0Attribute(value?: boolean): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_clip0(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    clip1Attribute(value?: boolean): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_clip1(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    clipShapeAttribute(value: CircleShape | EllipseShape | PathShape | RectShape): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.OBJECT) == (value_type)) && (value instanceof CircleShape)) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<CircleShape>(value)
            thisSerializer.writeCircleShape(value_0)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (value instanceof EllipseShape)) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<EllipseShape>(value)
            thisSerializer.writeEllipseShape(value_1)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (value instanceof PathShape)) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<PathShape>(value)
            thisSerializer.writePathShape(value_2)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (value instanceof RectShape)) {
            thisSerializer.writeInt8(3)
            const value_3 = unsafeCast<RectShape>(value)
            thisSerializer.writeRectShape(value_3)
        }
        ArkUIGeneratedNativeModule._CommonMethod_clipShape(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    mask0Attribute(value?: ProgressMask): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            thisSerializer.writeProgressMask(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_mask0(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    mask1Attribute(value?: ProgressMask): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            thisSerializer.writeProgressMask(value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_mask1(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    maskShapeAttribute(value: CircleShape | EllipseShape | PathShape | RectShape): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (((RuntimeType.OBJECT) == (value_type)) && (value instanceof CircleShape)) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<CircleShape>(value)
            thisSerializer.writeCircleShape(value_0)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (value instanceof EllipseShape)) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<EllipseShape>(value)
            thisSerializer.writeEllipseShape(value_1)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (value instanceof PathShape)) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<PathShape>(value)
            thisSerializer.writePathShape(value_2)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (value instanceof RectShape)) {
            thisSerializer.writeInt8(3)
            const value_3 = unsafeCast<RectShape>(value)
            thisSerializer.writeRectShape(value_3)
        }
        ArkUIGeneratedNativeModule._CommonMethod_maskShape(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    keyAttribute(value: string): void {
        ArkUIGeneratedNativeModule._CommonMethod_key(this.peer.ptr, value)
    }
    idAttribute(value: string): void {
        ArkUIGeneratedNativeModule._CommonMethod_id(this.peer.ptr, value)
    }
    geometryTransition0Attribute(value: string): void {
        ArkUIGeneratedNativeModule._CommonMethod_geometryTransition0(this.peer.ptr, value)
    }
    geometryTransition1Attribute(id: string, options?: GeometryTransitionOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeGeometryTransitionOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_geometryTransition1(this.peer.ptr, id, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    stateStylesAttribute(value: StateStyles): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeStateStyles(value)
        ArkUIGeneratedNativeModule._CommonMethod_stateStyles(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    restoreIdAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_restoreId(this.peer.ptr, value)
    }
    sphericalEffectAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_sphericalEffect(this.peer.ptr, value)
    }
    lightUpEffectAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CommonMethod_lightUpEffect(this.peer.ptr, value)
    }
    pixelStretchEffectAttribute(value: PixelStretchEffectOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writePixelStretchEffectOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_pixelStretchEffect(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilityGroup0Attribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityGroup0(this.peer.ptr, +value)
    }
    accessibilityGroup1Attribute(isGroup: boolean, accessibilityOptions: AccessibilityOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeAccessibilityOptions(accessibilityOptions)
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityGroup1(this.peer.ptr, +isGroup, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilityText0Attribute(value: string): void {
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityText0(this.peer.ptr, value)
    }
    accessibilityText1Attribute(value: Resource): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeResource(value)
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityText1(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilityTextHintAttribute(value: string): void {
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityTextHint(this.peer.ptr, value)
    }
    accessibilityDescription0Attribute(value: string): void {
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityDescription0(this.peer.ptr, value)
    }
    accessibilityDescription1Attribute(value: Resource): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeResource(value)
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityDescription1(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilityLevelAttribute(value: string): void {
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityLevel(this.peer.ptr, value)
    }
    accessibilityVirtualNodeAttribute(value: CustomBuilder): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value))
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityVirtualNode(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    accessibilityCheckedAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_accessibilityChecked(this.peer.ptr, +value)
    }
    accessibilitySelectedAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_accessibilitySelected(this.peer.ptr, +value)
    }
    obscuredAttribute(value: Array<ObscuredReasons>): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeInt32(value.length)
        for (let i = 0; i < value.length; i++) {
            const value_element: ObscuredReasons = value[i]
            thisSerializer.writeInt32(value_element)
        }
        ArkUIGeneratedNativeModule._CommonMethod_obscured(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    reuseIdAttribute(value: string): void {
        ArkUIGeneratedNativeModule._CommonMethod_reuseId(this.peer.ptr, value)
    }
    renderFitAttribute(value: RenderFit): void {
        ArkUIGeneratedNativeModule._CommonMethod_renderFit(this.peer.ptr, value)
    }
    gestureModifierAttribute(value: GestureModifier): void {
        ArkUIGeneratedNativeModule._CommonMethod_gestureModifier(this.peer.ptr, toPeerPtr(value))
    }
    backgroundBrightnessAttribute(value: BackgroundBrightnessOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeBackgroundBrightnessOptions(value)
        ArkUIGeneratedNativeModule._CommonMethod_backgroundBrightness(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onGestureJudgeBeginAttribute(value: ((gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onGestureJudgeBegin(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onGestureRecognizerJudgeBegin0Attribute(value: GestureRecognizerJudgeBeginCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onGestureRecognizerJudgeBegin0(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onGestureRecognizerJudgeBegin1Attribute(callback_: GestureRecognizerJudgeBeginCallback, exposeInnerGesture: boolean): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._CommonMethod_onGestureRecognizerJudgeBegin1(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length(), +exposeInnerGesture)
        thisSerializer.release()
    }
    shouldBuiltInRecognizerParallelWithAttribute(value: ShouldBuiltInRecognizerParallelWithCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_shouldBuiltInRecognizerParallelWith(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    monopolizeEventsAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonMethod_monopolizeEvents(this.peer.ptr, +value)
    }
    onTouchInterceptAttribute(value: ((parameter: TouchEvent) => HitTestMode)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onTouchIntercept(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onSizeChangeAttribute(value: SizeChangeCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CommonMethod_onSizeChange(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    customPropertyAttribute(name: string, value?: Object): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            thisSerializer.writeCustomObject("Object", value_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_customProperty(this.peer.ptr, name, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    expandSafeAreaAttribute(types?: Array<SafeAreaType>, edges?: Array<SafeAreaEdge>): void {
        const thisSerializer: Serializer = Serializer.hold()
        let types_type: int32 = RuntimeType.UNDEFINED
        types_type = runtimeType(types)
        thisSerializer.writeInt8(types_type)
        if ((RuntimeType.UNDEFINED) != (types_type)) {
            const types_value = types!
            thisSerializer.writeInt32(types_value.length)
            for (let i = 0; i < types_value.length; i++) {
                const types_value_element: SafeAreaType = types_value[i]
                thisSerializer.writeInt32(types_value_element)
            }
        }
        let edges_type: int32 = RuntimeType.UNDEFINED
        edges_type = runtimeType(edges)
        thisSerializer.writeInt8(edges_type)
        if ((RuntimeType.UNDEFINED) != (edges_type)) {
            const edges_value = edges!
            thisSerializer.writeInt32(edges_value.length)
            for (let i = 0; i < edges_value.length; i++) {
                const edges_value_element: SafeAreaEdge = edges_value[i]
                thisSerializer.writeInt32(edges_value_element)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_expandSafeArea(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundAttribute(builder: CustomBuilder, options?: { align?: Alignment }): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(builder))
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            const options_value_align = options_value.align
            let options_value_align_type: int32 = RuntimeType.UNDEFINED
            options_value_align_type = runtimeType(options_value_align)
            thisSerializer.writeInt8(options_value_align_type)
            if ((RuntimeType.UNDEFINED) != (options_value_align_type)) {
                const options_value_align_value = options_value_align!
                thisSerializer.writeInt32(options_value_align_value)
            }
        }
        ArkUIGeneratedNativeModule._CommonMethod_background(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundImageAttribute(src: ResourceStr | PixelMap, repeat?: ImageRepeat): void {
        const thisSerializer: Serializer = Serializer.hold()
        let src_type: int32 = RuntimeType.UNDEFINED
        src_type = runtimeType(src)
        if ((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type)) {
            thisSerializer.writeInt8(0)
            const src_0 = unsafeCast<ResourceStr>(src)
            let src_0_type: int32 = RuntimeType.UNDEFINED
            src_0_type = runtimeType(src_0)
            if (RuntimeType.STRING == src_0_type) {
                thisSerializer.writeInt8(0)
                const src_0_0 = unsafeCast<string>(src_0)
                thisSerializer.writeString(src_0_0)
            }
            else if (RuntimeType.OBJECT == src_0_type) {
                thisSerializer.writeInt8(1)
                const src_0_1 = unsafeCast<Resource>(src_0)
                thisSerializer.writeResource(src_0_1)
            }
        }
        else if (((RuntimeType.OBJECT) == (src_type)) && ((src!.hasOwnProperty("isEditable")))) {
            thisSerializer.writeInt8(1)
            const src_1 = unsafeCast<PixelMap>(src)
            thisSerializer.writePixelMap(src_1)
        }
        let repeat_type: int32 = RuntimeType.UNDEFINED
        repeat_type = runtimeType(repeat)
        thisSerializer.writeInt8(repeat_type)
        if ((RuntimeType.UNDEFINED) != (repeat_type)) {
            const repeat_value = repeat!
            thisSerializer.writeInt32(repeat_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_backgroundImage(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    backgroundBlurStyleAttribute(value: BlurStyle, options?: BackgroundBlurStyleOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeBackgroundBlurStyleOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_backgroundBlurStyle(this.peer.ptr, value, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    foregroundBlurStyleAttribute(value: BlurStyle, options?: ForegroundBlurStyleOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeForegroundBlurStyleOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_foregroundBlurStyle(this.peer.ptr, value, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    focusScopeId0Attribute(id: string, isGroup?: boolean): void {
        const thisSerializer: Serializer = Serializer.hold()
        let isGroup_type: int32 = RuntimeType.UNDEFINED
        isGroup_type = runtimeType(isGroup)
        thisSerializer.writeInt8(isGroup_type)
        if ((RuntimeType.UNDEFINED) != (isGroup_type)) {
            const isGroup_value = isGroup!
            thisSerializer.writeBoolean(isGroup_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_focusScopeId0(this.peer.ptr, id, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    focusScopeId1Attribute(id: string, isGroup?: boolean, arrowStepOut?: boolean): void {
        const thisSerializer: Serializer = Serializer.hold()
        let isGroup_type: int32 = RuntimeType.UNDEFINED
        isGroup_type = runtimeType(isGroup)
        thisSerializer.writeInt8(isGroup_type)
        if ((RuntimeType.UNDEFINED) != (isGroup_type)) {
            const isGroup_value = isGroup!
            thisSerializer.writeBoolean(isGroup_value)
        }
        let arrowStepOut_type: int32 = RuntimeType.UNDEFINED
        arrowStepOut_type = runtimeType(arrowStepOut)
        thisSerializer.writeInt8(arrowStepOut_type)
        if ((RuntimeType.UNDEFINED) != (arrowStepOut_type)) {
            const arrowStepOut_value = arrowStepOut!
            thisSerializer.writeBoolean(arrowStepOut_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_focusScopeId1(this.peer.ptr, id, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    focusScopePriorityAttribute(scopeId: string, priority?: FocusPriority): void {
        const thisSerializer: Serializer = Serializer.hold()
        let priority_type: int32 = RuntimeType.UNDEFINED
        priority_type = runtimeType(priority)
        thisSerializer.writeInt8(priority_type)
        if ((RuntimeType.UNDEFINED) != (priority_type)) {
            const priority_value = priority!
            thisSerializer.writeInt32(priority_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_focusScopePriority(this.peer.ptr, scopeId, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    gestureAttribute(gesture: GestureType, mask?: GestureMask): void {
        const thisSerializer: Serializer = Serializer.hold()
        let gesture_type: int32 = RuntimeType.UNDEFINED
        gesture_type = runtimeType(gesture)
        if ((unsafeCast<GestureComponent<Object>>(gesture).type) === (GestureName.Tap)) {
            thisSerializer.writeInt8(0)
            const gesture_0 = unsafeCast<TapGestureInterface>(gesture)
            thisSerializer.writeTapGestureInterface(gesture_0)
        }
        else if ((unsafeCast<GestureComponent<Object>>(gesture).type) === (GestureName.LongPress)) {
            thisSerializer.writeInt8(1)
            const gesture_1 = unsafeCast<LongPressGestureInterface>(gesture)
            thisSerializer.writeLongPressGestureInterface(gesture_1)
        }
        else if ((unsafeCast<GestureComponent<Object>>(gesture).type) === (GestureName.Pan)) {
            thisSerializer.writeInt8(2)
            const gesture_2 = unsafeCast<PanGestureInterface>(gesture)
            thisSerializer.writePanGestureInterface(gesture_2)
        }
        else if ((unsafeCast<GestureComponent<Object>>(gesture).type) === (GestureName.Pinch)) {
            thisSerializer.writeInt8(3)
            const gesture_3 = unsafeCast<PinchGestureInterface>(gesture)
            thisSerializer.writePinchGestureInterface(gesture_3)
        }
        else if ((unsafeCast<GestureComponent<Object>>(gesture).type) === (GestureName.Swipe)) {
            thisSerializer.writeInt8(4)
            const gesture_4 = unsafeCast<SwipeGestureInterface>(gesture)
            thisSerializer.writeSwipeGestureInterface(gesture_4)
        }
        else if ((unsafeCast<GestureComponent<Object>>(gesture).type) === (GestureName.Rotation)) {
            thisSerializer.writeInt8(5)
            const gesture_5 = unsafeCast<RotationGestureInterface>(gesture)
            thisSerializer.writeRotationGestureInterface(gesture_5)
        }
        else if ((unsafeCast<GestureComponent<Object>>(gesture).type) === (GestureName.Group)) {
            thisSerializer.writeInt8(6)
            const gesture_6 = unsafeCast<GestureGroupInterface>(gesture)
            thisSerializer.writeGestureGroupInterface(gesture_6)
        }
        let mask_type: int32 = RuntimeType.UNDEFINED
        mask_type = runtimeType(mask)
        thisSerializer.writeInt8(mask_type)
        if ((RuntimeType.UNDEFINED) != (mask_type)) {
            const mask_value = mask!
            thisSerializer.writeInt32(mask_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_gesture(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    priorityGestureAttribute(gesture: GestureType, mask?: GestureMask): void {
        const thisSerializer: Serializer = Serializer.hold()
        let gesture_type: int32 = RuntimeType.UNDEFINED
        gesture_type = runtimeType(gesture)
        if ((unsafeCast<GestureComponent<Object>>(gesture).type) === (GestureName.Tap)) {
            thisSerializer.writeInt8(0)
            const gesture_0 = unsafeCast<TapGestureInterface>(gesture)
            thisSerializer.writeTapGestureInterface(gesture_0)
        }
        else if ((unsafeCast<GestureComponent<Object>>(gesture).type) === (GestureName.LongPress)) {
            thisSerializer.writeInt8(1)
            const gesture_1 = unsafeCast<LongPressGestureInterface>(gesture)
            thisSerializer.writeLongPressGestureInterface(gesture_1)
        }
        else if ((unsafeCast<GestureComponent<Object>>(gesture).type) === (GestureName.Pan)) {
            thisSerializer.writeInt8(2)
            const gesture_2 = unsafeCast<PanGestureInterface>(gesture)
            thisSerializer.writePanGestureInterface(gesture_2)
        }
        else if ((unsafeCast<GestureComponent<Object>>(gesture).type) === (GestureName.Pinch)) {
            thisSerializer.writeInt8(3)
            const gesture_3 = unsafeCast<PinchGestureInterface>(gesture)
            thisSerializer.writePinchGestureInterface(gesture_3)
        }
        else if ((unsafeCast<GestureComponent<Object>>(gesture).type) === (GestureName.Swipe)) {
            thisSerializer.writeInt8(4)
            const gesture_4 = unsafeCast<SwipeGestureInterface>(gesture)
            thisSerializer.writeSwipeGestureInterface(gesture_4)
        }
        else if ((unsafeCast<GestureComponent<Object>>(gesture).type) === (GestureName.Rotation)) {
            thisSerializer.writeInt8(5)
            const gesture_5 = unsafeCast<RotationGestureInterface>(gesture)
            thisSerializer.writeRotationGestureInterface(gesture_5)
        }
        else if ((unsafeCast<GestureComponent<Object>>(gesture).type) === (GestureName.Group)) {
            thisSerializer.writeInt8(6)
            const gesture_6 = unsafeCast<GestureGroupInterface>(gesture)
            thisSerializer.writeGestureGroupInterface(gesture_6)
        }
        let mask_type: int32 = RuntimeType.UNDEFINED
        mask_type = runtimeType(mask)
        thisSerializer.writeInt8(mask_type)
        if ((RuntimeType.UNDEFINED) != (mask_type)) {
            const mask_value = mask!
            thisSerializer.writeInt32(mask_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_priorityGesture(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    parallelGestureAttribute(gesture: GestureType, mask?: GestureMask): void {
        const thisSerializer: Serializer = Serializer.hold()
        let gesture_type: int32 = RuntimeType.UNDEFINED
        gesture_type = runtimeType(gesture)
        if ((unsafeCast<GestureComponent<Object>>(gesture).type) === (GestureName.Tap)) {
            thisSerializer.writeInt8(0)
            const gesture_0 = unsafeCast<TapGestureInterface>(gesture)
            thisSerializer.writeTapGestureInterface(gesture_0)
        }
        else if ((unsafeCast<GestureComponent<Object>>(gesture).type) === (GestureName.LongPress)) {
            thisSerializer.writeInt8(1)
            const gesture_1 = unsafeCast<LongPressGestureInterface>(gesture)
            thisSerializer.writeLongPressGestureInterface(gesture_1)
        }
        else if ((unsafeCast<GestureComponent<Object>>(gesture).type) === (GestureName.Pan)) {
            thisSerializer.writeInt8(2)
            const gesture_2 = unsafeCast<PanGestureInterface>(gesture)
            thisSerializer.writePanGestureInterface(gesture_2)
        }
        else if ((unsafeCast<GestureComponent<Object>>(gesture).type) === (GestureName.Pinch)) {
            thisSerializer.writeInt8(3)
            const gesture_3 = unsafeCast<PinchGestureInterface>(gesture)
            thisSerializer.writePinchGestureInterface(gesture_3)
        }
        else if ((unsafeCast<GestureComponent<Object>>(gesture).type) === (GestureName.Swipe)) {
            thisSerializer.writeInt8(4)
            const gesture_4 = unsafeCast<SwipeGestureInterface>(gesture)
            thisSerializer.writeSwipeGestureInterface(gesture_4)
        }
        else if ((unsafeCast<GestureComponent<Object>>(gesture).type) === (GestureName.Rotation)) {
            thisSerializer.writeInt8(5)
            const gesture_5 = unsafeCast<RotationGestureInterface>(gesture)
            thisSerializer.writeRotationGestureInterface(gesture_5)
        }
        else if ((unsafeCast<GestureComponent<Object>>(gesture).type) === (GestureName.Group)) {
            thisSerializer.writeInt8(6)
            const gesture_6 = unsafeCast<GestureGroupInterface>(gesture)
            thisSerializer.writeGestureGroupInterface(gesture_6)
        }
        let mask_type: int32 = RuntimeType.UNDEFINED
        mask_type = runtimeType(mask)
        thisSerializer.writeInt8(mask_type)
        if ((RuntimeType.UNDEFINED) != (mask_type)) {
            const mask_value = mask!
            thisSerializer.writeInt32(mask_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_parallelGesture(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    blurAttribute(value: number, options?: BlurOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeBlurOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_blur(this.peer.ptr, value, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    linearGradientBlurAttribute(value: number, options: LinearGradientBlurOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeLinearGradientBlurOptions(options)
        ArkUIGeneratedNativeModule._CommonMethod_linearGradientBlur(this.peer.ptr, value, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    systemBarEffectAttribute(): void {
        ArkUIGeneratedNativeModule._CommonMethod_systemBarEffect(this.peer.ptr)
    }
    backdropBlurAttribute(value: number, options?: BlurOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeBlurOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_backdropBlur(this.peer.ptr, value, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    sharedTransitionAttribute(id: string, options?: sharedTransitionOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writesharedTransitionOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_sharedTransition(this.peer.ptr, id, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    chainModeAttribute(direction: Axis, style: ChainStyle): void {
        ArkUIGeneratedNativeModule._CommonMethod_chainMode(this.peer.ptr, direction, style)
    }
    dragPreviewOptionsAttribute(value: DragPreviewOptions, options?: DragInteractionOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeDragPreviewOptions(value)
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeDragInteractionOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_dragPreviewOptions(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    overlayAttribute(value: string | CustomBuilder | ComponentContent, options?: OverlayOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<string>(value)
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.FUNCTION == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<CustomBuilder>(value)
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_1))
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2 = unsafeCast<ComponentContent>(value)
            thisSerializer.writeComponentContent(value_2)
        }
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeOverlayOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_overlay(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    blendModeAttribute(value: BlendMode, type?: BlendApplyType): void {
        const thisSerializer: Serializer = Serializer.hold()
        let type_type: int32 = RuntimeType.UNDEFINED
        type_type = runtimeType(type)
        thisSerializer.writeInt8(type_type)
        if ((RuntimeType.UNDEFINED) != (type_type)) {
            const type_value = type!
            thisSerializer.writeInt32(type_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_blendMode(this.peer.ptr, value, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    advancedBlendModeAttribute(effect: BlendMode | Blender, type?: BlendApplyType): void {
        const thisSerializer: Serializer = Serializer.hold()
        let effect_type: int32 = RuntimeType.UNDEFINED
        effect_type = runtimeType(effect)
        if (RuntimeType.NUMBER == effect_type) {
            thisSerializer.writeInt8(0)
            const effect_0 = unsafeCast<BlendMode>(effect)
            thisSerializer.writeInt32(effect_0)
        }
        else if (RuntimeType.OBJECT == effect_type) {
            thisSerializer.writeInt8(1)
            const effect_1 = unsafeCast<Blender>(effect)
            thisSerializer.writeBlender(effect_1)
        }
        let type_type: int32 = RuntimeType.UNDEFINED
        type_type = runtimeType(type)
        thisSerializer.writeInt8(type_type)
        if ((RuntimeType.UNDEFINED) != (type_type)) {
            const type_value = type!
            thisSerializer.writeInt32(type_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_advancedBlendMode(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    bindPopupAttribute(show: boolean, popup: PopupOptions | CustomPopupOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let popup_type: int32 = RuntimeType.UNDEFINED
        popup_type = runtimeType(popup)
        if (((RuntimeType.OBJECT) == (popup_type)) && ((popup!.hasOwnProperty("message")))) {
            thisSerializer.writeInt8(0)
            const popup_0 = unsafeCast<PopupOptions>(popup)
            thisSerializer.writePopupOptions(popup_0)
        }
        else if (((RuntimeType.OBJECT) == (popup_type)) && ((popup!.hasOwnProperty("builder")))) {
            thisSerializer.writeInt8(1)
            const popup_1 = unsafeCast<CustomPopupOptions>(popup)
            thisSerializer.writeCustomPopupOptions(popup_1)
        }
        ArkUIGeneratedNativeModule._CommonMethod_bindPopup(this.peer.ptr, +show, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    bindMenu0Attribute(content: Array<MenuElement> | CustomBuilder, options?: MenuOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let content_type: int32 = RuntimeType.UNDEFINED
        content_type = runtimeType(content)
        if (RuntimeType.OBJECT == content_type) {
            thisSerializer.writeInt8(0)
            const content_0 = unsafeCast<Array<MenuElement>>(content)
            thisSerializer.writeInt32(content_0.length)
            for (let i = 0; i < content_0.length; i++) {
                const content_0_element: MenuElement = content_0[i]
                thisSerializer.writeMenuElement(content_0_element)
            }
        }
        else if (RuntimeType.FUNCTION == content_type) {
            thisSerializer.writeInt8(1)
            const content_1 = unsafeCast<CustomBuilder>(content)
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(content_1))
        }
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeMenuOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_bindMenu0(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    bindMenu1Attribute(isShow: boolean, content: Array<MenuElement> | CustomBuilder, options?: MenuOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let content_type: int32 = RuntimeType.UNDEFINED
        content_type = runtimeType(content)
        if (RuntimeType.OBJECT == content_type) {
            thisSerializer.writeInt8(0)
            const content_0 = unsafeCast<Array<MenuElement>>(content)
            thisSerializer.writeInt32(content_0.length)
            for (let i = 0; i < content_0.length; i++) {
                const content_0_element: MenuElement = content_0[i]
                thisSerializer.writeMenuElement(content_0_element)
            }
        }
        else if (RuntimeType.FUNCTION == content_type) {
            thisSerializer.writeInt8(1)
            const content_1 = unsafeCast<CustomBuilder>(content)
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(content_1))
        }
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeMenuOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_bindMenu1(this.peer.ptr, +isShow, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    bindContextMenu0Attribute(content: CustomBuilder, responseType: ResponseType, options?: ContextMenuOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(content))
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeContextMenuOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_bindContextMenu0(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length(), responseType)
        thisSerializer.release()
    }
    bindContextMenu1Attribute(isShown: boolean, content: CustomBuilder, options?: ContextMenuOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(content))
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeContextMenuOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_bindContextMenu1(this.peer.ptr, +isShown, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    bindContentCover0Attribute(isShow: boolean | undefined, builder: CustomBuilder, type?: ModalTransition): void {
        const thisSerializer: Serializer = Serializer.hold()
        let isShow_type: int32 = RuntimeType.UNDEFINED
        isShow_type = runtimeType(isShow)
        thisSerializer.writeInt8(isShow_type)
        if ((RuntimeType.UNDEFINED) != (isShow_type)) {
            const isShow_value = isShow!
            thisSerializer.writeBoolean(isShow_value)
        }
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(builder))
        let type_type: int32 = RuntimeType.UNDEFINED
        type_type = runtimeType(type)
        thisSerializer.writeInt8(type_type)
        if ((RuntimeType.UNDEFINED) != (type_type)) {
            const type_value = type!
            thisSerializer.writeInt32(type_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_bindContentCover0(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    bindContentCover1Attribute(isShow: boolean | undefined, builder: CustomBuilder, options?: ContentCoverOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let isShow_type: int32 = RuntimeType.UNDEFINED
        isShow_type = runtimeType(isShow)
        thisSerializer.writeInt8(isShow_type)
        if ((RuntimeType.UNDEFINED) != (isShow_type)) {
            const isShow_value = isShow!
            thisSerializer.writeBoolean(isShow_value)
        }
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(builder))
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeContentCoverOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_bindContentCover1(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    bindSheetAttribute(isShow: boolean | undefined, builder: CustomBuilder, options?: SheetOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let isShow_type: int32 = RuntimeType.UNDEFINED
        isShow_type = runtimeType(isShow)
        thisSerializer.writeInt8(isShow_type)
        if ((RuntimeType.UNDEFINED) != (isShow_type)) {
            const isShow_value = isShow!
            thisSerializer.writeBoolean(isShow_value)
        }
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(builder))
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeSheetOptions(options_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_bindSheet(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onVisibleAreaChangeAttribute(ratios: Array<number>, event: VisibleAreaChangeCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeInt32(ratios.length)
        for (let i = 0; i < ratios.length; i++) {
            const ratios_element: number = ratios[i]
            thisSerializer.writeNumber(ratios_element)
        }
        thisSerializer.holdAndWriteCallback(event)
        ArkUIGeneratedNativeModule._CommonMethod_onVisibleAreaChange(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    keyboardShortcutAttribute(value: string | FunctionKey, keys: Array<ModifierKey>, action?: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<string>(value)
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<FunctionKey>(value)
            thisSerializer.writeInt32(value_1)
        }
        thisSerializer.writeInt32(keys.length)
        for (let i = 0; i < keys.length; i++) {
            const keys_element: ModifierKey = keys[i]
            thisSerializer.writeInt32(keys_element)
        }
        let action_type: int32 = RuntimeType.UNDEFINED
        action_type = runtimeType(action)
        thisSerializer.writeInt8(action_type)
        if ((RuntimeType.UNDEFINED) != (action_type)) {
            const action_value = action!
            thisSerializer.holdAndWriteCallback(action_value)
        }
        ArkUIGeneratedNativeModule._CommonMethod_keyboardShortcut(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ArkCommonMethodAttributes {
    width?: Length
    height?: Length
    drawModifier?: DrawModifier | undefined
    responseRegion?: Array<Rectangle> | Rectangle
    mouseResponseRegion?: Array<Rectangle> | Rectangle
    size?: SizeOptions
    constraintSize?: ConstraintSizeOptions
    touchable?: boolean
    hitTestBehavior?: HitTestMode
    onChildTouchTest?: ((value: Array<TouchTestInfo>) => TouchResult)
    layoutWeight?: number | string
    chainWeight?: ChainWeightOptions
    padding?: Padding | Length | LocalizedPadding
    safeAreaPadding?: Padding | LengthMetrics | LocalizedPadding
    margin?: Margin | Length | LocalizedMargin
    backgroundColor?: ResourceColor
    pixelRound?: PixelRoundPolicy
    backgroundImageSize?: SizeOptions | ImageSize
    backgroundImagePosition?: Position | Alignment
    backgroundEffect?: BackgroundEffectOptions
    backgroundImageResizable?: ResizableOptions
    foregroundEffect?: ForegroundEffectOptions
    visualEffect?: VisualEffect
    backgroundFilter?: Filter
    foregroundFilter?: Filter
    compositingFilter?: Filter
    opacity?: number | Resource
    border?: BorderOptions
    borderStyle?: BorderStyle | EdgeStyles
    borderWidth?: Length | EdgeWidths | LocalizedEdgeWidths
    borderColor?: ResourceColor | EdgeColors | LocalizedEdgeColors
    borderRadius?: Length | BorderRadiuses | LocalizedBorderRadiuses
    borderImage?: BorderImageOption
    outline?: OutlineOptions
    outlineStyle?: OutlineStyle | EdgeOutlineStyles
    outlineWidth?: Dimension | EdgeOutlineWidths
    outlineColor?: ResourceColor | EdgeColors | LocalizedEdgeColors
    outlineRadius?: Dimension | OutlineRadiuses
    foregroundColor?: ResourceColor | ColoringStrategy
    onClick?: ((event: ClickEvent) => void)
    onHover?: ((isHover: boolean, event: HoverEvent) => void)
    onAccessibilityHover?: AccessibilityCallback
    hoverEffect?: HoverEffect
    onMouse?: ((event: MouseEvent) => void)
    onTouch?: ((event: TouchEvent) => void)
    onKeyEvent?: ((event: KeyEvent) => void)
    onKeyPreIme?: ((parameter: KeyEvent) => boolean)
    focusable?: boolean
    onFocus?: (() => void)
    onBlur?: (() => void)
    tabIndex?: number
    defaultFocus?: boolean
    groupDefaultFocus?: boolean
    focusOnTouch?: boolean
    focusBox?: FocusBoxStyle
    animation?: AnimateParam
    transition?: TransitionOptions | TransitionEffect
    motionBlur?: MotionBlurOptions
    brightness?: number
    contrast?: number
    grayscale?: number
    colorBlend?: Color | string | Resource
    saturate?: number
    sepia?: number
    invert?: number | InvertOptions
    hueRotate?: number | string
    useShadowBatching?: boolean
    useEffect?: boolean
    renderGroup?: boolean
    freeze?: boolean
    translate?: TranslateOptions
    scale?: ScaleOptions
    gridSpan?: number
    gridOffset?: number
    rotate?: RotateOptions
    transform?: Object
    onAppear?: (() => void)
    onDisAppear?: (() => void)
    onAttach?: (() => void)
    onDetach?: (() => void)
    onAreaChange?: ((oldValue: Area, newValue: Area) => void)
    visibility?: Visibility
    flexGrow?: number
    flexShrink?: number
    flexBasis?: number | string
    alignSelf?: ItemAlign
    displayPriority?: number
    zIndex?: number
    direction?: Direction
    align?: Alignment
    position?: Position | Edges | LocalizedEdges
    markAnchor?: Position | LocalizedPosition
    offset?: Position | Edges | LocalizedEdges
    enabled?: boolean
    useSizeType?: { xs?: number | { span: number, offset: number }, sm?: number | { span: number, offset: number }, md?: number | { span: number, offset: number }, lg?: number | { span: number, offset: number } }
    alignRules?: AlignRuleOption
    aspectRatio?: number
    clickEffect?: ClickEffect | undefined
    onDragStart?: ((event: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo)
    onDragEnter?: ((event: DragEvent, extraParams?: string) => void)
    onDragMove?: ((event: DragEvent, extraParams?: string) => void)
    onDragLeave?: ((event: DragEvent, extraParams?: string) => void)
    onDrop?: ((event: DragEvent, extraParams?: string) => void)
    onDragEnd?: ((event: DragEvent, extraParams?: string) => void)
    allowDrop?: Array<UniformDataType> | undefined
    draggable?: boolean
    dragPreview?: CustomBuilder | DragItemInfo | string
    onPreDrag?: ((parameter: PreDragStatus) => void)
    linearGradient?: { angle?: number | string, direction?: GradientDirection, colors: Array<[ ResourceColor, number ]>, repeating?: boolean }
    sweepGradient?: { center: [ Length, Length ], start?: number | string, end?: number | string, rotation?: number | string, colors: Array<[ ResourceColor, number ]>, repeating?: boolean }
    radialGradient?: { center: [ Length, Length ], radius: number | string, colors: Array<[ ResourceColor, number ]>, repeating?: boolean }
    motionPath?: MotionPathOptions
    shadow?: ShadowOptions | ShadowStyle
    clip?: boolean | undefined
    clipShape?: CircleShape | EllipseShape | PathShape | RectShape
    mask?: ProgressMask | undefined
    maskShape?: CircleShape | EllipseShape | PathShape | RectShape
    key?: string
    id?: string
    geometryTransition?: string
    stateStyles?: StateStyles
    restoreId?: number
    sphericalEffect?: number
    lightUpEffect?: number
    pixelStretchEffect?: PixelStretchEffectOptions
    accessibilityGroup?: boolean
    accessibilityText?: string
    accessibilityTextHint?: string
    accessibilityDescription?: string
    accessibilityLevel?: string
    accessibilityVirtualNode?: CustomBuilder
    accessibilityChecked?: boolean
    accessibilitySelected?: boolean
    obscured?: Array<ObscuredReasons>
    reuseId?: string
    renderFit?: RenderFit
    attributeModifier?: AttributeModifier<object>
    gestureModifier?: GestureModifier
    backgroundBrightness?: BackgroundBrightnessOptions
    onGestureJudgeBegin?: ((gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult)
    onGestureRecognizerJudgeBegin?: GestureRecognizerJudgeBeginCallback
    shouldBuiltInRecognizerParallelWith?: ShouldBuiltInRecognizerParallelWithCallback
    monopolizeEvents?: boolean
    onTouchIntercept?: ((parameter: TouchEvent) => HitTestMode)
    onSizeChange?: SizeChangeCallback
}
export class ArkCommonShapeMethodPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkCommonShapeMethodPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._CommonShapeMethod_construct(peerId, flags)
        const _peer = new ArkCommonShapeMethodPeer(_peerPtr, peerId, "CommonShapeMethod", flags)
        component?.setPeer(_peer)
        return _peer
    }
    strokeAttribute(value: ResourceColor): void {
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
        ArkUIGeneratedNativeModule._CommonShapeMethod_stroke(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    fillAttribute(value: ResourceColor): void {
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
        ArkUIGeneratedNativeModule._CommonShapeMethod_fill(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeDashOffsetAttribute(value: number | string): void {
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
        ArkUIGeneratedNativeModule._CommonShapeMethod_strokeDashOffset(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeLineCapAttribute(value: LineCapStyle): void {
        ArkUIGeneratedNativeModule._CommonShapeMethod_strokeLineCap(this.peer.ptr, value)
    }
    strokeLineJoinAttribute(value: LineJoinStyle): void {
        ArkUIGeneratedNativeModule._CommonShapeMethod_strokeLineJoin(this.peer.ptr, value)
    }
    strokeMiterLimitAttribute(value: number | string): void {
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
        ArkUIGeneratedNativeModule._CommonShapeMethod_strokeMiterLimit(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeOpacityAttribute(value: number | string | Resource): void {
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
            const value_2 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._CommonShapeMethod_strokeOpacity(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    fillOpacityAttribute(value: number | string | Resource): void {
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
            const value_2 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._CommonShapeMethod_fillOpacity(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeWidthAttribute(value: Length): void {
        ArkUIGeneratedNativeModule._CommonShapeMethod_strokeWidth(this.peer.ptr, value)
    }
    antiAliasAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CommonShapeMethod_antiAlias(this.peer.ptr, +value)
    }
    strokeDashArrayAttribute(value: Array<Length>): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeInt32(value.length)
        for (let i = 0; i < value.length; i++) {
            const value_element: Length = value[i]
            thisSerializer.writeLength(value_element)
        }
        ArkUIGeneratedNativeModule._CommonShapeMethod_strokeDashArray(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ArkCommonShapeMethodAttributes extends ArkCommonMethodAttributes {
    stroke?: ResourceColor
    fill?: ResourceColor
    strokeDashOffset?: number | string
    strokeLineCap?: LineCapStyle
    strokeLineJoin?: LineJoinStyle
    strokeMiterLimit?: number | string
    strokeOpacity?: number | string | Resource
    fillOpacity?: number | string | Resource
    strokeWidth?: Length
    antiAlias?: boolean
    strokeDashArray?: Array<Length>
}
export class ArkCommonPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkCommonPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._Common_construct(peerId, flags)
        const _peer = new ArkCommonPeer(_peerPtr, peerId, "Common", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setCommonOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._CommonInterface_setCommonOptions(this.peer.ptr)
    }
}
export interface ArkCommonAttributes extends ArkCommonMethodAttributes {
}
export class ArkScrollableCommonMethodPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkScrollableCommonMethodPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._ScrollableCommonMethod_construct(peerId, flags)
        const _peer = new ArkScrollableCommonMethodPeer(_peerPtr, peerId, "ScrollableCommonMethod", flags)
        component?.setPeer(_peer)
        return _peer
    }
    scrollBarAttribute(value: BarState): void {
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_scrollBar(this.peer.ptr, value)
    }
    scrollBarColorAttribute(value: Color | number | string): void {
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
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_scrollBarColor(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollBarWidthAttribute(value: number | string): void {
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
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_scrollBarWidth(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    nestedScrollAttribute(value: NestedScrollOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeNestedScrollOptions(value)
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_nestedScroll(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    enableScrollInteractionAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_enableScrollInteraction(this.peer.ptr, +value)
    }
    frictionAttribute(value: number | Resource): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<number>(value)
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<Resource>(value)
            thisSerializer.writeResource(value_1)
        }
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_friction(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollAttribute(value: ((first: number, last: number) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_onScroll(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillScrollAttribute(value?: ScrollOnWillScrollCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_onWillScroll(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onDidScrollAttribute(value: ScrollOnScrollCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_onDidScroll(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onReachStartAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_onReachStart(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onReachEndAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_onReachEnd(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStartAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_onScrollStart(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStopAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_onScrollStop(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    flingSpeedLimitAttribute(value: number): void {
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_flingSpeedLimit(this.peer.ptr, value)
    }
    clipContentAttribute(value: ContentClipMode | RectShape): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0 = unsafeCast<ContentClipMode>(value)
            thisSerializer.writeInt32(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1)
            const value_1 = unsafeCast<RectShape>(value)
            thisSerializer.writeRectShape(value_1)
        }
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_clipContent(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    edgeEffectAttribute(edgeEffect: EdgeEffect, options?: EdgeEffectOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeEdgeEffectOptions(options_value)
        }
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_edgeEffect(this.peer.ptr, edgeEffect, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    fadingEdgeAttribute(enabled?: boolean, options?: FadingEdgeOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let enabled_type: int32 = RuntimeType.UNDEFINED
        enabled_type = runtimeType(enabled)
        thisSerializer.writeInt8(enabled_type)
        if ((RuntimeType.UNDEFINED) != (enabled_type)) {
            const enabled_value = enabled!
            thisSerializer.writeBoolean(enabled_value)
        }
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeFadingEdgeOptions(options_value)
        }
        ArkUIGeneratedNativeModule._ScrollableCommonMethod_fadingEdge(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ArkScrollableCommonMethodAttributes extends ArkCommonMethodAttributes {
}
