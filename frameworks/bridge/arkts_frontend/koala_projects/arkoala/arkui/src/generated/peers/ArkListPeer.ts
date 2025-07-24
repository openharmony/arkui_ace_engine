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
import { ScrollableCommonMethod, CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, CustomBuilder, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, SourceTool, RectResult, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason, NestedScrollOptions, ContentClipMode, EdgeEffectOptions, FadingEdgeOptions, ItemDragInfo } from "./../ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Area, Bias, Font, LengthConstrain } from "./../ArkUnitsInterfaces"
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
import { ScrollOnWillScrollCallback, ScrollOnScrollCallback, ScrollOptions, ScrollEdgeOptions, ScrollPageOptions, OffsetResult, ScrollAlign, ScrollToIndexOptions, ScrollAnimationOptions } from "./../ArkScrollInterfaces"
import { ListItemAlign, ListDividerOptions, ChainAnimationOptions, StickyStyle, ScrollSnapAlign, OnScrollVisibleContentChangeCallback, ListAttribute, ChainEdgeEffect, ScrollState, ListOptions } from "./../ArkListInterfaces"
import { ChildrenMainSize } from "./../ArkChildrenMainSizeMaterialized"
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
export class ArkListPeer extends ArkScrollableCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkListPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._List_construct(peerId, flags)
        const _peer = new ArkListPeer(_peerPtr, peerId, "List", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setListOptionsAttribute(options?: ListOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeListOptions(options_value)
        }
        ArkUIGeneratedNativeModule._ListInterface_setListOptions(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    alignListItemAttribute(value: ListItemAlign): void {
        ArkUIGeneratedNativeModule._ListAttribute_alignListItem(this.peer.ptr, value)
    }
    listDirectionAttribute(value: Axis): void {
        ArkUIGeneratedNativeModule._ListAttribute_listDirection(this.peer.ptr, value)
    }
    scrollBarAttribute(value: BarState): void {
        ArkUIGeneratedNativeModule._ListAttribute_scrollBar(this.peer.ptr, value)
    }
    contentStartOffsetAttribute(value: number): void {
        ArkUIGeneratedNativeModule._ListAttribute_contentStartOffset(this.peer.ptr, value)
    }
    contentEndOffsetAttribute(value: number): void {
        ArkUIGeneratedNativeModule._ListAttribute_contentEndOffset(this.peer.ptr, value)
    }
    dividerAttribute(value?: ListDividerOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let value_type: int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!
            thisSerializer.writeListDividerOptions(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_divider(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    editModeAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ListAttribute_editMode(this.peer.ptr, +value)
    }
    multiSelectableAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ListAttribute_multiSelectable(this.peer.ptr, +value)
    }
    cachedCount0Attribute(value: number): void {
        ArkUIGeneratedNativeModule._ListAttribute_cachedCount0(this.peer.ptr, value)
    }
    cachedCount1Attribute(count: number, show: boolean): void {
        ArkUIGeneratedNativeModule._ListAttribute_cachedCount1(this.peer.ptr, count, +show)
    }
    chainAnimationAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ListAttribute_chainAnimation(this.peer.ptr, +value)
    }
    chainAnimationOptionsAttribute(value: ChainAnimationOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeChainAnimationOptions(value)
        ArkUIGeneratedNativeModule._ListAttribute_chainAnimationOptions(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    stickyAttribute(value: StickyStyle): void {
        ArkUIGeneratedNativeModule._ListAttribute_sticky(this.peer.ptr, value)
    }
    scrollSnapAlignAttribute(value: ScrollSnapAlign): void {
        ArkUIGeneratedNativeModule._ListAttribute_scrollSnapAlign(this.peer.ptr, value)
    }
    nestedScrollAttribute(value: NestedScrollOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeNestedScrollOptions(value)
        ArkUIGeneratedNativeModule._ListAttribute_nestedScroll(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    enableScrollInteractionAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ListAttribute_enableScrollInteraction(this.peer.ptr, +value)
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
        ArkUIGeneratedNativeModule._ListAttribute_friction(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    childrenMainSizeAttribute(value: ChildrenMainSize): void {
        ArkUIGeneratedNativeModule._ListAttribute_childrenMainSize(this.peer.ptr, toPeerPtr(value))
    }
    maintainVisibleContentPositionAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ListAttribute_maintainVisibleContentPosition(this.peer.ptr, +value)
    }
    onScrollAttribute(value: ((first: number, last: number) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onScroll(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollIndexAttribute(value: ((start: number, end: number, center: number) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onScrollIndex(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollVisibleContentChangeAttribute(value: OnScrollVisibleContentChangeCallback): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onScrollVisibleContentChange(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onReachStartAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onReachStart(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onReachEndAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onReachEnd(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStartAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onScrollStart(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStopAttribute(value: (() => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onScrollStop(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDeleteAttribute(value: ((index: number) => boolean)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onItemDelete(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemMoveAttribute(value: ((from: number, to: number) => boolean)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onItemMove(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDragStartAttribute(value: ((event: ItemDragInfo, itemIndex: number) => CustomBuilder)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onItemDragStart(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDragEnterAttribute(value: ((event: ItemDragInfo) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onItemDragEnter(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDragMoveAttribute(value: ((event: ItemDragInfo, itemIndex: number, insertIndex: number) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onItemDragMove(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDragLeaveAttribute(value: ((event: ItemDragInfo, itemIndex: number) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onItemDragLeave(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDropAttribute(value: ((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void)): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onItemDrop(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollFrameBeginAttribute(value: ((offset: number, state: ScrollState) => { offsetRemain: number })): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onScrollFrameBegin(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    lanesAttribute(value: number | LengthConstrain, gutter?: Dimension): void {
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
            const value_1 = unsafeCast<LengthConstrain>(value)
            const value_1_minLength = value_1.minLength
            thisSerializer.writeLength(value_1_minLength)
            const value_1_maxLength = value_1.maxLength
            thisSerializer.writeLength(value_1_maxLength)
        }
        let gutter_type: int32 = RuntimeType.UNDEFINED
        gutter_type = runtimeType(gutter)
        thisSerializer.writeInt8(gutter_type)
        if ((RuntimeType.UNDEFINED) != (gutter_type)) {
            const gutter_value = gutter!
            thisSerializer.writeLength(gutter_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_lanes(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    edgeEffectAttribute(value: EdgeEffect, options?: EdgeEffectOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeEdgeEffectOptions(options_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_edgeEffect(this.peer.ptr, value, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ArkListAttributes extends ArkScrollableCommonMethodAttributes {
    alignListItem?: ListItemAlign
    listDirection?: Axis
    scrollBar?: BarState
    contentStartOffset?: number
    contentEndOffset?: number
    divider?: ListDividerOptions | undefined
    editMode?: boolean
    multiSelectable?: boolean
    cachedCount?: number
    chainAnimation?: boolean
    chainAnimationOptions?: ChainAnimationOptions
    sticky?: StickyStyle
    scrollSnapAlign?: ScrollSnapAlign
    nestedScroll?: NestedScrollOptions
    enableScrollInteraction?: boolean
    friction?: number | Resource
    childrenMainSize?: ChildrenMainSize
    maintainVisibleContentPosition?: boolean
    onScroll?: ((first: number, last: number) => void)
    onScrollIndex?: ((start: number, end: number, center: number) => void)
    onScrollVisibleContentChange?: OnScrollVisibleContentChangeCallback
    onReachStart?: (() => void)
    onReachEnd?: (() => void)
    onScrollStart?: (() => void)
    onScrollStop?: (() => void)
    onItemDelete?: ((index: number) => boolean)
    onItemMove?: ((from: number, to: number) => boolean)
    onItemDragStart?: ((event: ItemDragInfo, itemIndex: number) => CustomBuilder)
    onItemDragEnter?: ((event: ItemDragInfo) => void)
    onItemDragMove?: ((event: ItemDragInfo, itemIndex: number, insertIndex: number) => void)
    onItemDragLeave?: ((event: ItemDragInfo, itemIndex: number) => void)
    onItemDrop?: ((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void)
    onScrollFrameBegin?: ((offset: number, state: ScrollState) => { offsetRemain: number })
}
