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
import { ArkScrollableCommonMethodComponent } from "./ArkCommon"
import { ArkListPeer } from "./peers/ArkListPeer"
import { ScrollableCommonMethod, CommonMethod, Rectangle, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, UniformDataType, CustomBuilder, DragItemInfo, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, DrawContext, TouchTestInfo, TouchResult, AdaptiveColor, BlurStyleActivePolicy, RepeatMode, LinearGradient_common, FinishCallbackType, ExpectedFrameRateRange, TransitionEffects, TransitionEdge, MotionBlurAnchor, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam, PreDragStatus, ShadowType, UIGestureEvent, BlurStyleOptions, ThemeColorMode, FractionStop, DragPreviewMode, ImageModifier, OverlayOffset, TransitionHierarchyStrategy, PopupMessageOptions, SymbolGlyphModifier, MenuPreviewMode, ContextMenuAnimationOptions, BindOptions, SheetSize, SheetType, SheetTitleOptions, SheetMode, ScrollSizeMode, UIContext, SheetKeyboardAvoidMode, SourceTool, RectResult, TouchTestStrategy, EventTarget, SourceType, TouchObject, HistoricalPoint, IntentionCode, DragBehavior, Summary, DragResult, DismissPopupAction, DismissContentCoverAction, SheetDismiss, DismissSheetAction, SpringBackAction, DismissReason, NestedScrollOptions, ContentClipMode, EdgeEffectOptions, FadingEdgeOptions, ItemDragInfo } from "./ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage, Area, Bias, Font, LengthConstrain } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, PixelRoundCalcPolicy, Curve, PlayMode, TransitionType, HorizontalAlign, VerticalAlign, ClickEffectLevel, SharedTransitionEffectType, Placement, ArrowPointPosition, MouseButton, MouseAction, TouchType, KeyType, KeySource, FontWeight, FontStyle, BarState, EdgeEffect, NestedScrollMode, Edge } from "./ArkEnumsInterfaces"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { ResizableOptions, DrawingLattice } from "./ArkImageInterfaces"
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
import { ScrollOnWillScrollCallback, ScrollOnScrollCallback, ScrollOptions, ScrollEdgeOptions, ScrollPageOptions, OffsetResult, ScrollAlign, ScrollToIndexOptions, ScrollAnimationOptions } from "./ArkScrollInterfaces"
import { ListItemAlign, ListDividerOptions, ChainAnimationOptions, StickyStyle, ScrollSnapAlign, OnScrollVisibleContentChangeCallback, ListAttribute, ChainEdgeEffect, ScrollState, ListOptions } from "./ArkListInterfaces"
import { ChildrenMainSize } from "./ArkChildrenMainSizeMaterialized"
import { Scroller } from "./ArkScrollerMaterialized"
/** @memo:stable */
export class ArkListComponent extends ArkScrollableCommonMethodComponent {
    protected getPeer(): ArkListPeer {
        return (this.peer as ArkListPeer)
    }
    /** @memo */
    public setListOptions(options?: ListOptions): this {
        if (this.checkPriority("setListOptions")) {
            const options_casted = options as (ListOptions | undefined)
            this.getPeer()?.setListOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public alignListItem(value: ListItemAlign): this {
        if (this.checkPriority("alignListItem")) {
            const value_casted = value as (ListItemAlign)
            this.getPeer()?.alignListItemAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public listDirection(value: Axis): this {
        if (this.checkPriority("listDirection")) {
            const value_casted = value as (Axis)
            this.getPeer()?.listDirectionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public scrollBar(value: BarState): this {
        if (this.checkPriority("scrollBar")) {
            const value_casted = value as (BarState)
            this.getPeer()?.scrollBarAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public contentStartOffset(value: number): this {
        if (this.checkPriority("contentStartOffset")) {
            const value_casted = value as (number)
            this.getPeer()?.contentStartOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public contentEndOffset(value: number): this {
        if (this.checkPriority("contentEndOffset")) {
            const value_casted = value as (number)
            this.getPeer()?.contentEndOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public divider(value?: ListDividerOptions): this {
        if (this.checkPriority("divider")) {
            const value_casted = value as (ListDividerOptions | undefined)
            this.getPeer()?.dividerAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public editMode(value: boolean): this {
        if (this.checkPriority("editMode")) {
            const value_casted = value as (boolean)
            this.getPeer()?.editModeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public multiSelectable(value: boolean): this {
        if (this.checkPriority("multiSelectable")) {
            const value_casted = value as (boolean)
            this.getPeer()?.multiSelectableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public cachedCount(count: number, show?: boolean): this {
        if (this.checkPriority("cachedCount")) {
            const count_type = runtimeType(count)
            const show_type = runtimeType(show)
            if (RuntimeType.UNDEFINED == show_type) {
                const value_casted = count as (number)
                this.getPeer()?.cachedCount0Attribute(value_casted)
                return this
            }
            if (RuntimeType.BOOLEAN == show_type) {
                const count_casted = count as (number)
                const show_casted = show as (boolean)
                this.getPeer()?.cachedCount1Attribute(count_casted, show_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public chainAnimation(value: boolean): this {
        if (this.checkPriority("chainAnimation")) {
            const value_casted = value as (boolean)
            this.getPeer()?.chainAnimationAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public chainAnimationOptions(value: ChainAnimationOptions): this {
        if (this.checkPriority("chainAnimationOptions")) {
            const value_casted = value as (ChainAnimationOptions)
            this.getPeer()?.chainAnimationOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public sticky(value: StickyStyle): this {
        if (this.checkPriority("sticky")) {
            const value_casted = value as (StickyStyle)
            this.getPeer()?.stickyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public scrollSnapAlign(value: ScrollSnapAlign): this {
        if (this.checkPriority("scrollSnapAlign")) {
            const value_casted = value as (ScrollSnapAlign)
            this.getPeer()?.scrollSnapAlignAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public nestedScroll(value: NestedScrollOptions): this {
        if (this.checkPriority("nestedScroll")) {
            const value_casted = value as (NestedScrollOptions)
            this.getPeer()?.nestedScrollAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableScrollInteraction(value: boolean): this {
        if (this.checkPriority("enableScrollInteraction")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableScrollInteractionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public friction(value: number | Resource): this {
        if (this.checkPriority("friction")) {
            const value_casted = value as (number | Resource)
            this.getPeer()?.frictionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public childrenMainSize(value: ChildrenMainSize): this {
        if (this.checkPriority("childrenMainSize")) {
            const value_casted = value as (ChildrenMainSize)
            this.getPeer()?.childrenMainSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public maintainVisibleContentPosition(value: boolean): this {
        if (this.checkPriority("maintainVisibleContentPosition")) {
            const value_casted = value as (boolean)
            this.getPeer()?.maintainVisibleContentPositionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScroll(value: ((first: number, last: number) => void)): this {
        if (this.checkPriority("onScroll")) {
            const value_casted = value as (((first: number, last: number) => void))
            this.getPeer()?.onScrollAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollIndex(value: ((start: number, end: number, center: number) => void)): this {
        if (this.checkPriority("onScrollIndex")) {
            const value_casted = value as (((start: number, end: number, center: number) => void))
            this.getPeer()?.onScrollIndexAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollVisibleContentChange(value: OnScrollVisibleContentChangeCallback): this {
        if (this.checkPriority("onScrollVisibleContentChange")) {
            const value_casted = value as (OnScrollVisibleContentChangeCallback)
            this.getPeer()?.onScrollVisibleContentChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onReachStart(value: (() => void)): this {
        if (this.checkPriority("onReachStart")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onReachStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onReachEnd(value: (() => void)): this {
        if (this.checkPriority("onReachEnd")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onReachEndAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollStart(value: (() => void)): this {
        if (this.checkPriority("onScrollStart")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onScrollStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollStop(value: (() => void)): this {
        if (this.checkPriority("onScrollStop")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onScrollStopAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onItemDelete(value: ((index: number) => boolean)): this {
        if (this.checkPriority("onItemDelete")) {
            const value_casted = value as (((index: number) => boolean))
            this.getPeer()?.onItemDeleteAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onItemMove(value: ((from: number, to: number) => boolean)): this {
        if (this.checkPriority("onItemMove")) {
            const value_casted = value as (((from: number, to: number) => boolean))
            this.getPeer()?.onItemMoveAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onItemDragStart(value: ((event: ItemDragInfo, itemIndex: number) => CustomBuilder)): this {
        if (this.checkPriority("onItemDragStart")) {
            const value_casted = value as (((event: ItemDragInfo, itemIndex: number) => CustomBuilder))
            this.getPeer()?.onItemDragStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onItemDragEnter(value: ((event: ItemDragInfo) => void)): this {
        if (this.checkPriority("onItemDragEnter")) {
            const value_casted = value as (((event: ItemDragInfo) => void))
            this.getPeer()?.onItemDragEnterAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onItemDragMove(value: ((event: ItemDragInfo, itemIndex: number, insertIndex: number) => void)): this {
        if (this.checkPriority("onItemDragMove")) {
            const value_casted = value as (((event: ItemDragInfo, itemIndex: number, insertIndex: number) => void))
            this.getPeer()?.onItemDragMoveAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onItemDragLeave(value: ((event: ItemDragInfo, itemIndex: number) => void)): this {
        if (this.checkPriority("onItemDragLeave")) {
            const value_casted = value as (((event: ItemDragInfo, itemIndex: number) => void))
            this.getPeer()?.onItemDragLeaveAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onItemDrop(value: ((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void)): this {
        if (this.checkPriority("onItemDrop")) {
            const value_casted = value as (((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => void))
            this.getPeer()?.onItemDropAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollFrameBegin(value: ((offset: number, state: ScrollState) => { offsetRemain: number })): this {
        if (this.checkPriority("onScrollFrameBegin")) {
            const value_casted = value as (((offset: number, state: ScrollState) => { offsetRemain: number }))
            this.getPeer()?.onScrollFrameBeginAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public lanes(value: number | LengthConstrain, gutter?: Dimension): this {
        if (this.checkPriority("lanes")) {
            const value_casted = value as (number | LengthConstrain)
            const gutter_casted = gutter as (Dimension | undefined)
            this.getPeer()?.lanesAttribute(value_casted, gutter_casted)
            return this
        }
        return this
    }
    /** @memo */
    public edgeEffect(value: EdgeEffect, options?: EdgeEffectOptions): this {
        if (this.checkPriority("edgeEffect")) {
            const value_casted = value as (EdgeEffect)
            const options_casted = options as (EdgeEffectOptions | undefined)
            this.getPeer()?.edgeEffectAttribute(value_casted, options_casted)
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
export function ArkList(
  /** @memo */
  style: ((attributes: ArkListComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  options?: ListOptions | undefined
) {
    const receiver = remember(() => {
        return new ArkListComponent()
    })
    NodeAttach<ArkListPeer>((): ArkListPeer => ArkListPeer.create(receiver), (_: ArkListPeer) => {
        receiver.setListOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
