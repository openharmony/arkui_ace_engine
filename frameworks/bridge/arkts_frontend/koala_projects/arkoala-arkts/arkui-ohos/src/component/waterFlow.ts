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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, float32, int64 } from "@koalaui/common"
import { Serializer } from "./../generated/peers/Serializer"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { Deserializer } from "./../generated/peers/Deserializer"
import { CallbackTransformer } from "./../generated/peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { Dimension, Margin, Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions } from "./units"
import { CustomBuilder, ScrollableCommonMethod, CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, NestedScrollOptions, ContentClipMode, EdgeEffectOptions, FadingEdgeOptions, OnScrollCallback } from "./common"
import { Scroller, ScrollOnWillScrollCallback, ScrollOnScrollCallback } from "./scroll"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, BarState, EdgeEffect, FlexDirection } from "./enums"
import { LengthMetrics } from "../Graphics"
import { ResizableOptions } from "./image"
import { Resource } from "global/resource";
import { Callback_Void } from "./abilityComponent"
import { FocusBoxStyle, FocusPriority } from "./focus"
import { CircleShape } from "./../generated/ArkCircleShapeMaterialized"
import { EllipseShape } from "./../generated/ArkEllipseShapeMaterialized"
import { PathShape } from "./../generated/ArkPathShapeMaterialized"
import { RectShape } from "./../generated/ArkRectShapeMaterialized"
import { AttributeModifier } from "./../component/common" 
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureType, GestureMask } from "./gesture"
import { PixelMap } from "./../generated/ArkPixelMapMaterialized"
import { Callback_Number_Number_Void, Callback_Number_ScrollState_Literal_Number_offsetRemain, Literal_Number_offsetRemain } from "./grid"
import { ScrollState } from "./list"
import { ArkWaterFlowComponent } from "./../generated/ArkWaterFlow"
import { ArkWaterFlowPeer } from "./../generated/peers/ArkWaterFlowPeer"
export class WaterFlowSectionsInternal {
    public static fromPtr(ptr: KPointer): WaterFlowSections {
        const obj : WaterFlowSections = new WaterFlowSections()
        obj.peer = new Finalizable(ptr, WaterFlowSections.getFinalizer())
        return obj
    }
}
export class WaterFlowSections implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_waterflowsections(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._WaterFlowSections_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = WaterFlowSections.ctor_waterflowsections()
        this.peer = new Finalizable(ctorPtr, WaterFlowSections.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WaterFlowSections_getFinalizer()
    }
    public splice(start: number, deleteCount?: number, sections?: Array<SectionOptions>): boolean {
        const start_casted = start as (number)
        const deleteCount_casted = deleteCount as (number | undefined)
        const sections_casted = sections as (Array<SectionOptions> | undefined)
        return this.splice_serialize(start_casted, deleteCount_casted, sections_casted)
    }
    public push(section: SectionOptions): boolean {
        const section_casted = section as (SectionOptions)
        return this.push_serialize(section_casted)
    }
    public update(sectionIndex: number, section: SectionOptions): boolean {
        const sectionIndex_casted = sectionIndex as (number)
        const section_casted = section as (SectionOptions)
        return this.update_serialize(sectionIndex_casted, section_casted)
    }
    public values(): Array<SectionOptions> {
        return this.values_serialize()
    }
    public length(): number {
        return this.length_serialize()
    }
    private splice_serialize(start: number, deleteCount?: number, sections?: Array<SectionOptions>): boolean {
        const thisSerializer : Serializer = Serializer.hold()
        let deleteCount_type : int32 = RuntimeType.UNDEFINED
        deleteCount_type = runtimeType(deleteCount)
        thisSerializer.writeInt8(deleteCount_type as int32)
        if ((RuntimeType.UNDEFINED) != (deleteCount_type)) {
            const deleteCount_value  = deleteCount!
            thisSerializer.writeNumber(deleteCount_value)
        }
        let sections_type : int32 = RuntimeType.UNDEFINED
        sections_type = runtimeType(sections)
        thisSerializer.writeInt8(sections_type as int32)
        if ((RuntimeType.UNDEFINED) != (sections_type)) {
            const sections_value  = sections!
            thisSerializer.writeInt32(sections_value.length as int32)
            for (let i = 0; i < sections_value.length; i++) {
                const sections_value_element : SectionOptions = sections_value[i]
                thisSerializer.writeSectionOptions(sections_value_element)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._WaterFlowSections_splice(this.peer!.ptr, start, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private push_serialize(section: SectionOptions): boolean {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSectionOptions(section)
        const retval  = ArkUIGeneratedNativeModule._WaterFlowSections_push(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private update_serialize(sectionIndex: number, section: SectionOptions): boolean {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSectionOptions(section)
        const retval  = ArkUIGeneratedNativeModule._WaterFlowSections_update(this.peer!.ptr, sectionIndex, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private values_serialize(): Array<SectionOptions> {
        const retval  = ArkUIGeneratedNativeModule._WaterFlowSections_values(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<SectionOptions> = new Array<SectionOptions>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = retvalDeserializer.readSectionOptions()
        }
        const returnResult : Array<SectionOptions> = buffer
        return returnResult
    }
    private length_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._WaterFlowSections_length(this.peer!.ptr)
        return retval
    }
}
export type GetItemMainSizeByIndex = (index: number) => number;
export interface SectionOptions {
    itemsCount: number;
    crossCount?: number;
    onGetItemMainSizeByIndex?: GetItemMainSizeByIndex;
    columnsGap?: Dimension;
    rowsGap?: Dimension;
    margin?: Margin | Dimension;
}
export enum WaterFlowLayoutMode {
    ALWAYS_TOP_DOWN = 0,
    SLIDING_WINDOW = 1
}
export interface WaterFlowOptions {
    footer?: CustomBuilder;
    scroller?: Scroller;
    sections?: WaterFlowSections;
    layoutMode?: WaterFlowLayoutMode;
}
/** @memo:stable */
export interface WaterFlowAttribute extends ScrollableCommonMethod {
    /** @memo */
    setWaterFlowOptions(options?: WaterFlowOptions): this
    /** @memo */
    columnsTemplate(value: string): this
    /** @memo */
    itemConstraintSize(value: ConstraintSizeOptions): this
    /** @memo */
    rowsTemplate(value: string): this
    /** @memo */
    columnsGap(value: Length): this
    /** @memo */
    rowsGap(value: Length): this
    /** @memo */
    layoutDirection(value: FlexDirection): this
    /** @memo */
    nestedScroll(value: NestedScrollOptions): this
    /** @memo */
    enableScrollInteraction(value: boolean): this
    /** @memo */
    friction(value: number | Resource): this
    /** @memo */
    cachedCount(count: number, show?: boolean): this
    /** @memo */
    onDidScroll(value: OnScrollCallback): this
    /** @memo */
    onReachStart(value: (() => void)): this
    /** @memo */
    onReachEnd(value: (() => void)): this
    /** @memo */
    onScrollFrameBegin(value: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)): this
    /** @memo */
    onScrollIndex(value: ((first: number,last: number) => void)): this
}
/** @memo */
export function WaterFlow(
  /** @memo */
  style: ((attributes: WaterFlowAttribute) => void) | undefined,
  options?: WaterFlowOptions | undefined, 
  /** @memo */
  content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkWaterFlowComponent()
    })
    NodeAttach<ArkWaterFlowPeer>((): ArkWaterFlowPeer => ArkWaterFlowPeer.create(receiver), (_: ArkWaterFlowPeer) => {
        receiver.setWaterFlowOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
