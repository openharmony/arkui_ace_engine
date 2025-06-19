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
import { ScrollableCommonMethod, CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, NestedScrollOptions, ContentClipMode, EdgeEffectOptions, FadingEdgeOptions, ChildrenMainSize, ItemDragInfo, OnScrollCallback } from "./../../component/common"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, LengthConstrain, PX, VP, FP, LPX, Percentage } from "./../../component/units"
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
import { Callback_Number_Number_Void, Callback_ItemDragInfo_Void, Callback_ItemDragInfo_Number_Number_Void, Callback_ItemDragInfo_Number_Void, Callback_ItemDragInfo_Number_Number_Boolean_Void, Callback_Number_ScrollState_Literal_Number_offsetRemain, Literal_Number_offsetRemain } from "./../../component/grid"
import { ScrollOnWillScrollCallback, ScrollOnScrollCallback } from "./../../component/scroll"
import { ListItemAlign, ListDividerOptions, ChainAnimationOptions, StickyStyle, ScrollSnapAlign, Callback_Number_Number_Number_Void, OnScrollVisibleContentChangeCallback, Callback_Number_Boolean, Callback_Number_Number_Boolean, ScrollState, ListAttribute, ListOptions } from "./../../component/list"
import { onItemDragStart_event_type } from "./../SyntheticDeclarations"
import { CallbackKind } from "./CallbackKind"
import { CallbackTransformer } from "./CallbackTransformer"
import { TypeChecker } from "#components"
import { MaterializedBase, toPeerPtr, wrapCallback } from "@koalaui/interop"
export class ArkListPeer extends ArkScrollableCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkListPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._List_construct(peerId, flags)
        const _peer  = new ArkListPeer(_peerPtr, peerId, "List", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setListOptionsAttribute(options?: ListOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeListOptions(options_value)
        }
        ArkUIGeneratedNativeModule._ListInterface_setListOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    alignListItemAttribute(value: ListItemAlign): void {
        ArkUIGeneratedNativeModule._ListAttribute_alignListItem(this.peer.ptr, value.valueOf())
    }
    listDirectionAttribute(value: Axis): void {
        ArkUIGeneratedNativeModule._ListAttribute_listDirection(this.peer.ptr, value.valueOf())
    }
    scrollBarAttribute(value: BarState): void {
        ArkUIGeneratedNativeModule._ListAttribute_scrollBar(this.peer.ptr, value.valueOf())
    }
    contentStartOffsetAttribute(value: number): void {
        ArkUIGeneratedNativeModule._ListAttribute_contentStartOffset(this.peer.ptr, value)
    }
    contentEndOffsetAttribute(value: number): void {
        ArkUIGeneratedNativeModule._ListAttribute_contentEndOffset(this.peer.ptr, value)
    }
    dividerAttribute(value?: ListDividerOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeListDividerOptions(value_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_divider(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    editModeAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ListAttribute_editMode(this.peer.ptr, value ? 1 : 0)
    }
    multiSelectableAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ListAttribute_multiSelectable(this.peer.ptr, value ? 1 : 0)
    }
    cachedCount0Attribute(value: number): void {
        ArkUIGeneratedNativeModule._ListAttribute_cachedCount0(this.peer.ptr, value)
    }
    cachedCount1Attribute(count: number, show: boolean): void {
        ArkUIGeneratedNativeModule._ListAttribute_cachedCount1(this.peer.ptr, count, show ? 1 : 0)
    }
    chainAnimationAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ListAttribute_chainAnimation(this.peer.ptr, value ? 1 : 0)
    }
    chainAnimationOptionsAttribute(value: ChainAnimationOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeChainAnimationOptions(value)
        ArkUIGeneratedNativeModule._ListAttribute_chainAnimationOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    stickyAttribute(value: StickyStyle): void {
        ArkUIGeneratedNativeModule._ListAttribute_sticky(this.peer.ptr, value.valueOf())
    }
    scrollSnapAlignAttribute(value: ScrollSnapAlign): void {
        ArkUIGeneratedNativeModule._ListAttribute_scrollSnapAlign(this.peer.ptr, value.valueOf())
    }
    nestedScrollAttribute(value: NestedScrollOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeNestedScrollOptions(value)
        ArkUIGeneratedNativeModule._ListAttribute_nestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableScrollInteractionAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ListAttribute_enableScrollInteraction(this.peer.ptr, value ? 1 : 0)
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
        ArkUIGeneratedNativeModule._ListAttribute_friction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    childrenMainSizeAttribute(value: ChildrenMainSize): void {
        ArkUIGeneratedNativeModule._ListAttribute_childrenMainSize(this.peer.ptr, toPeerPtr(value))
    }
    maintainVisibleContentPositionAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ListAttribute_maintainVisibleContentPosition(this.peer.ptr, value ? 1 : 0)
    }
    onScrollAttribute(value: ((first: number,last: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollIndexAttribute(value: ((start: number,end: number,center: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onScrollIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollVisibleContentChangeAttribute(value: OnScrollVisibleContentChangeCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onScrollVisibleContentChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDidScrollAttribute(value: OnScrollCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onDidScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReachStartAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onReachStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReachEndAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onReachEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStartAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onScrollStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStopAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onScrollStop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDeleteAttribute(value: ((index: number) => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onItemDelete(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemMoveAttribute(value: ((from: number,to: number) => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onItemMove(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDragStartAttribute(value: ((event: ItemDragInfo,itemIndex: number) => CustomBuilder)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onItemDragStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDragEnterAttribute(value: ((event: ItemDragInfo) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onItemDragEnter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDragMoveAttribute(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onItemDragMove(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDragLeaveAttribute(value: ((event: ItemDragInfo,itemIndex: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onItemDragLeave(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onItemDropAttribute(value: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onItemDrop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollFrameBeginAttribute(value: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ListAttribute_onScrollFrameBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    lanesAttribute(value: number | LengthConstrain, gutter?: Dimension): void {
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
            const value_1  = value as LengthConstrain
            const value_1_minLength  = value_1.minLength
            thisSerializer.writeLength(value_1_minLength)
            const value_1_maxLength  = value_1.maxLength
            thisSerializer.writeLength(value_1_maxLength)
        }
        let gutter_type : int32 = RuntimeType.UNDEFINED
        gutter_type = runtimeType(gutter)
        thisSerializer.writeInt8(gutter_type as int32)
        if ((RuntimeType.UNDEFINED) != (gutter_type)) {
            const gutter_value  = gutter!
            thisSerializer.writeLength(gutter_value)
        }
        ArkUIGeneratedNativeModule._ListAttribute_lanes(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._ListAttribute_edgeEffect(this.peer.ptr, value.valueOf(), thisSerializer.asBuffer(), thisSerializer.length())
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
    onScroll?: ((first: number,last: number) => void)
    onScrollIndex?: ((start: number,end: number,center: number) => void)
    onScrollVisibleContentChange?: OnScrollVisibleContentChangeCallback
    onDidScroll: OnScrollCallback
    onReachStart?: (() => void)
    onReachEnd?: (() => void)
    onScrollStart?: (() => void)
    onScrollStop?: (() => void)
    onItemDelete?: ((index: number) => boolean)
    onItemMove?: ((from: number,to: number) => boolean)
    onItemDragStart?: ((event: ItemDragInfo,itemIndex: number) => CustomBuilder)
    onItemDragEnter?: ((event: ItemDragInfo) => void)
    onItemDragMove?: ((event: ItemDragInfo,itemIndex: number,insertIndex: number) => void)
    onItemDragLeave?: ((event: ItemDragInfo,itemIndex: number) => void)
    onItemDrop?: ((event: ItemDragInfo,itemIndex: number,insertIndex: number,isSuccess: boolean) => void)
    onScrollFrameBegin?: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)
}
