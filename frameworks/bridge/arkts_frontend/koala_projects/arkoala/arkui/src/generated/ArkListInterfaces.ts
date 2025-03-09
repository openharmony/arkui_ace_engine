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

import { int32, int64, float32 } from "@koalaui/common"
import { KInt, KPointer, KBoolean, KStringPtr, wrapCallback } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Area, Bias, Font, LengthConstrain } from "./ArkUnitsInterfaces"
import { Scroller } from "./ArkScrollerMaterialized"
import { ScrollOptions, ScrollEdgeOptions, ScrollPageOptions, OffsetResult, ScrollAlign, ScrollToIndexOptions, ScrollAnimationOptions, ScrollOnWillScrollCallback, ScrollOnScrollCallback } from "./ArkScrollInterfaces"
import { Edge, Axis, Curve, HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, FontWeight, FontStyle, BarState, EdgeEffect, NestedScrollMode } from "./ArkEnumsInterfaces"
import { RectResult, ScrollableCommonMethod, CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, CustomBuilder, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, SourceTool, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason, NestedScrollOptions, ContentClipMode, EdgeEffectOptions, FadingEdgeOptions, ItemDragInfo } from "./ArkCommonInterfaces"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { ICurve } from "./ArkICurveMaterialized"
import { LengthUnit, ShapeSize, PathShapeOptions, RectShapeOptions, RoundRectShapeOptions } from "./ArkArkuiExternalInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { ResizableOptions, DrawingLattice } from "./ArkImageInterfaces"
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
import { ClickEvent } from "./ArkClickEventMaterialized"
import { HoverEvent } from "./ArkHoverEventMaterialized"
import { MouseEvent } from "./ArkMouseEventMaterialized"
import { TouchEvent } from "./ArkTouchEventMaterialized"
import { KeyEvent } from "./ArkKeyEventMaterialized"
import { ColorMetrics } from "./ArkColorMetricsMaterialized"
import { DragEvent } from "./ArkDragEventMaterialized"
import { BaseGestureEvent } from "./ArkBaseGestureEventMaterialized"
import { PanGestureOptions } from "./ArkPanGestureOptionsMaterialized"
import { BaseEvent } from "./ArkBaseEventMaterialized"
import { UnifiedData } from "./ArkUnifiedDataMaterialized"
import { GestureControl } from "./ArkGestureControlNamespace"
import { GestureEvent } from "./ArkGestureEventMaterialized"
import { ChildrenMainSize } from "./ArkChildrenMainSizeMaterialized"
export enum ScrollState {
    IDLE,
    Idle = IDLE,
    SCROLL = 1,
    Scroll = SCROLL,
    FLING = 2,
    Fling = FLING,
}
export enum ListItemAlign {
    START,
    Start = START,
    CENTER = 1,
    Center = CENTER,
    END = 2,
    End = END,
}
export enum ListItemGroupArea {
    NONE,
    IN_LIST_ITEM_AREA = 1,
    IN_HEADER_AREA = 2,
    IN_FOOTER_AREA = 3,
}
export enum StickyStyle {
    NONE,
    None = NONE,
    HEADER = 1,
    Header = HEADER,
    FOOTER = 2,
    Footer = FOOTER,
}
export enum ChainEdgeEffect {
    DEFAULT,
    STRETCH = 1,
}
export enum ScrollSnapAlign {
    NONE,
    START = 1,
    CENTER = 2,
    END = 3,
}
export interface ChainAnimationOptions {
    minSpace: Length;
    maxSpace: Length;
    conductivity?: number;
    intensity?: number;
    edgeEffect?: ChainEdgeEffect;
    stiffness?: number;
    damping?: number;
}
export interface CloseSwipeActionOptions {
    onFinish?: (() => void);
}
export interface VisibleListContentInfo {
    index: number;
    itemGroupArea?: ListItemGroupArea;
    itemIndexInGroup?: number;
}
export type OnScrollVisibleContentChangeCallback = (start: VisibleListContentInfo, end: VisibleListContentInfo) => void;
export interface ListOptions {
    initialIndex?: number;
    space?: number | string;
    scroller?: Scroller;
}
export type ListInterface = (options?: ListOptions) => ListAttribute;
export interface ListDividerOptions {
    strokeWidth: Length;
    color?: ResourceColor;
    startMargin?: Length;
    endMargin?: Length;
}
export interface ListAttribute extends ScrollableCommonMethod<ListAttribute> {
    alignListItem: ListItemAlign;
    listDirection: Axis;
    scrollBar: BarState;
    contentStartOffset: number;
    contentEndOffset: number;
    divider: ListDividerOptions | undefined;
    editMode: boolean;
    multiSelectable: boolean;
    cachedCount: number;
    chainAnimation: boolean;
    chainAnimationOptions: ChainAnimationOptions;
    sticky: StickyStyle;
    scrollSnapAlign: ScrollSnapAlign;
    nestedScroll: NestedScrollOptions;
    enableScrollInteraction: boolean;
    friction: number | Resource;
    childrenMainSize: ChildrenMainSize;
    maintainVisibleContentPosition: boolean;
    onScroll: ((first: number, last: number) => void);
    onScrollIndex: ((start: number, end: number, center: number) => void);
    onScrollVisibleContentChange: OnScrollVisibleContentChangeCallback;
    onReachStart: (() => void);
    onReachEnd: (() => void);
    onScrollStart: (() => void);
    onScrollStop: (() => void);
    onItemDelete: ((index: number) => boolean);
    onItemMove: ((from: number, to: number) => boolean);
    onItemDragStart: ((event: ItemDragInfo, itemIndex: number) => CustomBuilder);
    onItemDragEnter: ((event: ItemDragInfo) => void);
    onItemDragMove: ((event: ItemDragInfo, itemIndex: number, insertIndex: number) => void);
    onItemDragLeave: ((event: ItemDragInfo, itemIndex: number) => void);
    onItemDrop: ((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void);
    onScrollFrameBegin: ((offset: number, state: ScrollState) => { offsetRemain: number });

}
