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
import { ArkScrollableCommonMethodPeer, ArkScrollableCommonMethodAttributes } from "./ArkCommonPeer"
import { ScrollableCommonMethod, CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, CustomBuilder, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, SourceTool, RectResult, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason, NestedScrollOptions, ContentClipMode, EdgeEffectOptions, FadingEdgeOptions } from "./../ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Area, Bias, Font, VoidCallback } from "./../ArkUnitsInterfaces"
import { DrawModifier } from "./../ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, FontWeight, FontStyle, BarState, EdgeEffect, NestedScrollMode, Edge } from "./../ArkEnumsInterfaces"
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
import { ScrollOnWillScrollCallback, ScrollOnScrollCallback, ScrollDirection, OnScrollEdgeCallback, OnScrollFrameBeginCallback, ScrollSnapOptions, OffsetOptions, ScrollAttribute, ScrollOptions, ScrollEdgeOptions, ScrollPageOptions, OffsetResult, ScrollAlign, ScrollToIndexOptions, ScrollAnimationOptions } from "./../ArkScrollInterfaces"
import { ScrollSnapAlign } from "./../ArkListInterfaces"
import { Scroller } from "./../ArkScrollerMaterialized"
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
export class ArkScrollPeer extends ArkScrollableCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkScrollPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._Scroll_construct(peerId, flags)
        const _peer = new ArkScrollPeer(_peerPtr, peerId, "Scroll", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setScrollOptionsAttribute(scroller?: Scroller): void {
        const thisSerializer: Serializer = Serializer.hold()
        let scroller_type: int32 = RuntimeType.UNDEFINED
        scroller_type = runtimeType(scroller)
        thisSerializer.writeInt8(scroller_type)
        if ((RuntimeType.UNDEFINED) != (scroller_type)) {
            const scroller_value = scroller!
            thisSerializer.writeScroller(scroller_value)
        }
        ArkUIGeneratedNativeModule._ScrollInterface_setScrollOptions(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollableAttribute(value: ScrollDirection): void {
        ArkUIGeneratedNativeModule._ScrollAttribute_scrollable(this.peer.ptr, value)
    }
    onScrollAttribute(value: ((first: number, last: number) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ScrollAttribute_onScroll(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ScrollAttribute_onWillScroll(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onDidScrollAttribute(value: ScrollOnScrollCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ScrollAttribute_onDidScroll(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollEdgeAttribute(value: OnScrollEdgeCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ScrollAttribute_onScrollEdge(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStartAttribute(value: VoidCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ScrollAttribute_onScrollStart(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollEndAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ScrollAttribute_onScrollEnd(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStopAttribute(value: VoidCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ScrollAttribute_onScrollStop(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollBarAttribute(value: BarState): void {
        ArkUIGeneratedNativeModule._ScrollAttribute_scrollBar(this.peer.ptr, value)
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
        ArkUIGeneratedNativeModule._ScrollAttribute_scrollBarColor(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ScrollAttribute_scrollBarWidth(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollFrameBeginAttribute(value: OnScrollFrameBeginCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ScrollAttribute_onScrollFrameBegin(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    nestedScrollAttribute(value: NestedScrollOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeNestedScrollOptions(value)
        ArkUIGeneratedNativeModule._ScrollAttribute_nestedScroll(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    enableScrollInteractionAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ScrollAttribute_enableScrollInteraction(this.peer.ptr, +value)
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
        ArkUIGeneratedNativeModule._ScrollAttribute_friction(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollSnapAttribute(value: ScrollSnapOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeScrollSnapOptions(value)
        ArkUIGeneratedNativeModule._ScrollAttribute_scrollSnap(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    enablePagingAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ScrollAttribute_enablePaging(this.peer.ptr, +value)
    }
    initialOffsetAttribute(value: OffsetOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeOffsetOptions(value)
        ArkUIGeneratedNativeModule._ScrollAttribute_initialOffset(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ScrollAttribute_edgeEffect(this.peer.ptr, edgeEffect, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ArkScrollAttributes extends ArkScrollableCommonMethodAttributes {
    scrollable?: ScrollDirection
    onScroll?: ((first: number, last: number) => void)
    onWillScroll?: ScrollOnWillScrollCallback | undefined
    onDidScroll?: ScrollOnScrollCallback
    onScrollEdge?: OnScrollEdgeCallback
    onScrollStart?: VoidCallback
    onScrollEnd?: (() => void)
    onScrollStop?: VoidCallback
    scrollBar?: BarState
    scrollBarColor?: Color | number | string
    scrollBarWidth?: number | string
    onScrollFrameBegin?: OnScrollFrameBeginCallback
    nestedScroll?: NestedScrollOptions
    enableScrollInteraction?: boolean
    friction?: number | Resource
    scrollSnap?: ScrollSnapOptions
    enablePaging?: boolean
    initialOffset?: OffsetOptions
}
