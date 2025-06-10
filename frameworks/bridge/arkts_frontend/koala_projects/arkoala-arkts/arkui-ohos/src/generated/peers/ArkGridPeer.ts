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
import { ArkScrollableCommonMethodPeer, ArkScrollableCommonMethodAttributes } from "./ArkCommonPeer"
import { ScrollableCommonMethod, CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, NestedScrollOptions, ContentClipMode, EdgeEffectOptions, FadingEdgeOptions, ItemDragInfo, OnScrollCallback } from "./../../component/common"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage } from "./../../component/units"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, BarState, EdgeEffect } from "./../../component/enums"
import { LengthMetrics } from "../../Graphics"
import { ResizableOptions } from "./../../component/image"
import { Resource } from "global/resource";
import { Callback_Void } from "./../../component/abilityComponent"
import { FocusBoxStyle, FocusPriority } from "./../../component/focus"
import { CircleShape } from "./../ArkCircleShapeMaterialized"
import { EllipseShape } from "./../ArkEllipseShapeMaterialized"
import { PathShape } from "./../ArkPathShapeMaterialized"
import { RectShape } from "./../ArkRectShapeMaterialized"
import { AttributeModifier } from "./../../component/common" 
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureType, GestureMask, TapGestureInterface, LongPressGestureInterface, PanGestureInterface, PinchGestureInterface, SwipeGestureInterface, RotationGestureInterface, GestureGroupInterface } from "./../../component/gesture"
import { PixelMap } from "./../ArkPixelMapMaterialized"
import { Callback_Number_Number_Void, Callback_Number_Number_ComputedBarAttribute, ComputedBarAttribute, GridDirection, Callback_ItemDragInfo_Void, Callback_ItemDragInfo_Number_Number_Void, Callback_ItemDragInfo_Number_Void, Callback_ItemDragInfo_Number_Number_Boolean_Void, GridItemAlignment, Callback_Number_ScrollState_Literal_Number_offsetRemain, Literal_Number_offsetRemain, GridAttribute, GridLayoutOptions } from "./../../component/grid"
import { ScrollOnWillScrollCallback, ScrollOnScrollCallback, Scroller } from "./../../component/scroll"
import { onItemDragStart_event_type } from "./../SyntheticDeclarations"
import { ScrollState } from "./../../component/list"
import { CallbackKind } from "./CallbackKind"
import { CallbackTransformer } from "./CallbackTransformer"
import { TypeChecker } from "#components"
import { MaterializedBase, toPeerPtr, wrapCallback } from "@koalaui/interop"
export class ArkGridPeer extends ArkScrollableCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkGridPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Grid_construct(peerId, flags)
        const _peer  = new ArkGridPeer(_peerPtr, peerId, "Grid", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setGridOptionsAttribute(scroller?: Scroller, layoutOptions?: GridLayoutOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let scroller_type : int32 = RuntimeType.UNDEFINED
        scroller_type = runtimeType(scroller)
        thisSerializer.writeInt8(scroller_type as int32)
        if ((RuntimeType.UNDEFINED) != (scroller_type)) {
            const scroller_value  = scroller!
            thisSerializer.writeScroller(scroller_value)
        }
        let layoutOptions_type : int32 = RuntimeType.UNDEFINED
        layoutOptions_type = runtimeType(layoutOptions)
        thisSerializer.writeInt8(layoutOptions_type as int32)
        if ((RuntimeType.UNDEFINED) != (layoutOptions_type)) {
            const layoutOptions_value  = layoutOptions!
            thisSerializer.writeGridLayoutOptions(layoutOptions_value)
        }
        ArkUIGeneratedNativeModule._GridInterface_setGridOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    columnsTemplateAttribute(value: string): void {
        ArkUIGeneratedNativeModule._GridAttribute_columnsTemplate(this.peer.ptr, value)
    }
    rowsTemplateAttribute(value: string): void {
        ArkUIGeneratedNativeModule._GridAttribute_rowsTemplate(this.peer.ptr, value)
    }
    columnsGapAttribute(value: Length): void {
        ArkUIGeneratedNativeModule._GridAttribute_columnsGap(this.peer.ptr, value)
    }
    rowsGapAttribute(value: Length): void {
        ArkUIGeneratedNativeModule._GridAttribute_rowsGap(this.peer.ptr, value)
    }
    scrollBarWidthAttribute(value: number | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        ArkUIGeneratedNativeModule._GridAttribute_scrollBarWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollBarColorAttribute(value: Color | number | string): void {
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
        ArkUIGeneratedNativeModule._GridAttribute_scrollBarColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollBarAttribute(value: BarState): void {
        ArkUIGeneratedNativeModule._GridAttribute_scrollBar(this.peer.ptr, value.valueOf())
    }
    onScrollBarUpdateAttribute(value: ((index: number,offset: number) => ComputedBarAttribute)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onScrollBarUpdate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollIndexAttribute(value: ((first: number,last: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onScrollIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    cachedCount0Attribute(value: number): void {
        ArkUIGeneratedNativeModule._GridAttribute_cachedCount0(this.peer.ptr, value)
    }
    cachedCount1Attribute(count: number, show: boolean): void {
        ArkUIGeneratedNativeModule._GridAttribute_cachedCount1(this.peer.ptr, count, show ? 1 : 0)
    }
    editModeAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._GridAttribute_editMode(this.peer.ptr, value ? 1 : 0)
    }
    multiSelectableAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._GridAttribute_multiSelectable(this.peer.ptr, value ? 1 : 0)
    }
    maxCountAttribute(value: number): void {
        ArkUIGeneratedNativeModule._GridAttribute_maxCount(this.peer.ptr, value)
    }
    minCountAttribute(value: number): void {
        ArkUIGeneratedNativeModule._GridAttribute_minCount(this.peer.ptr, value)
    }
    cellLengthAttribute(value: number): void {
        ArkUIGeneratedNativeModule._GridAttribute_cellLength(this.peer.ptr, value)
    }
    layoutDirectionAttribute(value: GridDirection): void {
        ArkUIGeneratedNativeModule._GridAttribute_layoutDirection(this.peer.ptr, value.valueOf())
    }
    supportAnimationAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._GridAttribute_supportAnimation(this.peer.ptr, value ? 1 : 0)
    }
    onItemDragStartAttribute(value: ((event: ItemDragInfo,itemIndex: number) => CustomBuilder)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onItemDragStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDragEnterAttribute(value: ((event: ItemDragInfo) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onItemDragEnter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDragMoveAttribute(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onItemDragMove(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDragLeaveAttribute(value: ((event: ItemDragInfo,itemIndex: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onItemDragLeave(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDropAttribute(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onItemDrop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    nestedScrollAttribute(value: NestedScrollOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeNestedScrollOptions(value)
        ArkUIGeneratedNativeModule._GridAttribute_nestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableScrollInteractionAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._GridAttribute_enableScrollInteraction(this.peer.ptr, value ? 1 : 0)
    }
    frictionAttribute(value: number | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Resource
            thisSerializer.writeResource(value_1)
        }
        ArkUIGeneratedNativeModule._GridAttribute_friction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    alignItemsAttribute(value?: GridItemAlignment): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as GridItemAlignment)
            thisSerializer.writeInt32(value_value.valueOf())
        }
        ArkUIGeneratedNativeModule._GridAttribute_alignItems(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollAttribute(value: ((first: number,last: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDidScrollAttribute(value: OnScrollCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onDidScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReachStartAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onReachStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReachEndAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onReachEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStartAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onScrollStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStopAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onScrollStop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollFrameBeginAttribute(value: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._GridAttribute_onScrollFrameBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    edgeEffectAttribute(value: EdgeEffect, options?: EdgeEffectOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeEdgeEffectOptions(options_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_edgeEffect(this.peer.ptr, value.valueOf(), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface ArkGridAttributes extends ArkScrollableCommonMethodAttributes {
    columnsTemplate?: string
    rowsTemplate?: string
    columnsGap?: Length
    rowsGap?: Length
    scrollBarWidth?: number | string
    scrollBarColor?: Color | number | string
    scrollBar?: BarState
    onScrollBarUpdate?: ((index: number,offset: number) => ComputedBarAttribute)
    onScrollIndex?: ((first: number,last: number) => void)
    cachedCount?: number
    editMode?: boolean
    multiSelectable?: boolean
    maxCount?: number
    minCount?: number
    cellLength?: number
    layoutDirection?: GridDirection
    supportAnimation?: boolean
    onItemDragStart?: ((event: ItemDragInfo,itemIndex: number) => CustomBuilder)
    onItemDragEnter?: ((event: ItemDragInfo) => void)
    onItemDragMove?: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void)
    onItemDragLeave?: ((event: ItemDragInfo,itemIndex: number) => void)
    onItemDrop?: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void)
    nestedScroll?: NestedScrollOptions
    enableScrollInteraction?: boolean
    friction?: number | Resource
    alignItems?: GridItemAlignment | undefined
    onScroll?: ((first: number,last: number) => void)
    onDidScroll: OnScrollCallback
    onReachStart?: (() => void)
    onReachEnd?: (() => void)
    onScrollStart?: (() => void)
    onScrollStop?: (() => void)
    onScrollFrameBegin?: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)
}
