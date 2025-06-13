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
import { KStringPtr, KBoolean, RuntimeType, runtimeType } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ComponentBase } from "./../ComponentBase"
import { TypeChecker } from "#components"
import { ArkCommonMethodComponent } from "./ArkCommon"
import { ArkGridItemPeer } from "./peers/ArkGridItemPeer"
import { CommonMethod, Rectangle, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, CustomBuilder, DragItemInfo, UniformDataType, PreDragStatus, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey } from "./ArkEnumsInterfaces"
import { Callback_Array_TouchTestInfo_TouchResult, Callback_ClickEvent_Void, Callback_Boolean_HoverEvent_Void, Callback_MouseEvent_Void, Callback_TouchEvent_Void, Callback_KeyEvent_Void, Callback_KeyEvent_Boolean, Callback_Void, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, Callback_DragEvent_String_Void, Callback_PreDragStatus_Void, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, Callback_TouchEvent_HitTestMode, Literal_Alignment_align, Callback_Boolean_Void } from "./SyntheticDeclarations"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { ResizableOptions } from "./ArkImageInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { ClickEvent } from "./ArkClickEventMaterialized"
import { HoverEvent } from "./ArkHoverEventMaterialized"
import { MouseEvent } from "./ArkMouseEventMaterialized"
import { TouchEvent } from "./ArkTouchEventMaterialized"
import { KeyEvent } from "./ArkKeyEventMaterialized"
import { FocusBoxStyle, FocusPriority } from "./ArkFocusInterfaces"
import { TransitionEffect } from "./ArkTransitionEffectMaterialized"
import { DragEvent } from "./ArkDragEventMaterialized"
import { CircleShape } from "./ArkCircleShapeMaterialized"
import { EllipseShape } from "./ArkEllipseShapeMaterialized"
import { PathShape } from "./ArkPathShapeMaterialized"
import { RectShape } from "./ArkRectShapeMaterialized"
import { ProgressMask } from "./ArkProgressMaskMaterialized"
import { AttributeModifier } from "./../handwritten"
import { GestureModifier } from "./ArkGestureModifierMaterialized"
import { GestureInfo, GestureJudgeResult, GestureType, GestureMask } from "./ArkGestureInterfaces"
import { BaseGestureEvent } from "./ArkBaseGestureEventMaterialized"
import { PixelMap } from "./ArkPixelMapMaterialized"
import { GridItemOptions, GridItemAttribute } from "./ArkGridItemInterfaces"
import { AttributeUpdater } from "../handwritten/modifiers/ArkAttributeUpdater"
import { ArkGridItemNode } from "../handwritten/modifiers/ArkGridItemNode"
import { ArkGridItemAttributeSet,GridItemModifier } from "../handwritten/modifiers/ArkGridItemModifier"
import { applyUIAttributes } from "../handwritten/modifiers/ArkCommonModifier"
/** @memo:stable */
export class ArkGridItemComponent extends ArkCommonMethodComponent {
    getPeer(): ArkGridItemPeer {
        return (this.peer as ArkGridItemPeer)
    }
    getModifierHost(): ArkGridItemNode {
        if (this._modifierHost === undefined || this._modifierHost === null) {
            this._modifierHost = new ArkGridItemNode()
            this._modifierHost!.setPeer(this.getPeer())
        }
        return this._modifierHost as ArkGridItemNode
    }
    /** @memo */
    public setGridItemOptions(value?: GridItemOptions): this {
        if (this.checkPriority("setGridItemOptions")) {
            const value_casted = value as (GridItemOptions | undefined)
            this.getPeer()?.setGridItemOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public rowStart(value: number): this {
        if (this.checkPriority("rowStart")) {
            const value_casted = value as (number)
            this.getPeer()?.rowStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public rowEnd(value: number): this {
        if (this.checkPriority("rowEnd")) {
            const value_casted = value as (number)
            this.getPeer()?.rowEndAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public columnStart(value: number): this {
        if (this.checkPriority("columnStart")) {
            const value_casted = value as (number)
            this.getPeer()?.columnStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public columnEnd(value: number): this {
        if (this.checkPriority("columnEnd")) {
            const value_casted = value as (number)
            this.getPeer()?.columnEndAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public forceRebuild(value: boolean): this {
        if (this.checkPriority("forceRebuild")) {
            const value_casted = value as (boolean)
            this.getPeer()?.forceRebuildAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selectable(value: boolean): this {
        if (this.checkPriority("selectable")) {
            const value_casted = value as (boolean)
            this.getPeer()?.selectableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public selected(value: boolean): this {
        if (this.checkPriority("selected")) {
            const value_casted = value as (boolean)
            this.getPeer()?.selectedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onSelect(value: ((parameter: boolean) => void)): this {
        if (this.checkPriority("onSelect")) {
            const value_casted = value as (((parameter: boolean) => void))
            this.getPeer()?.onSelectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public _onChangeEvent_selected(callback: ((parameter: boolean) => void)): void {
        if (this.checkPriority("_onChangeEvent_selected")) {
            const callback_casted = callback as (((parameter: boolean) => void))
            this.getPeer()?._onChangeEvent_selectedAttribute(callback_casted)
            return
        }
        return
    }
    attributeModifier(modifier: AttributeModifier<GridItemAttribute>): this {
        let peerNode = this.getPeer();
        let attributeSet = peerNode._attributeSet;
        let isAttributeUpdater = modifier instanceof AttributeUpdater
        if (isAttributeUpdater) {
            let attributeUpdater = modifier as AttributeUpdater<GridItemAttribute>;
            attributeUpdater.attribute = this.getModifierHost();
            if (!attributeSet) {
                attributeSet = new ArkGridItemAttributeSet();
                peerNode._attributeSet = attributeSet;
            }
            attributeUpdater.initializeModifier((peerNode._attributeSet as Object) as GridItemAttribute)
        } else {
            let attributeModifier = ((modifier as Object) as AttributeModifier<GridItemAttribute>);
            let gridItemModifier = (attributeModifier as Object) as GridItemModifier;
            if (!attributeSet) {
                attributeSet = new ArkGridItemAttributeSet();
                attributeSet._modifiersWithKeys = gridItemModifier._modifiersWithKeys;
                peerNode._attributeSet = attributeSet;
            }
        }
        applyUIAttributes(modifier, peerNode);
        peerNode._attributeSet!.applyModifierPatch(peerNode);
        return this;
    }
    public applyAttributesFinish(): void {
        // we calls this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

/** @memo */
export function ArkGridItem(
  /** @memo */
  style: ((attributes: ArkGridItemComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  value?: GridItemOptions | undefined
) {
    const receiver = remember(() => {
        return new ArkGridItemComponent()
    })
    NodeAttach<ArkGridItemPeer>((): ArkGridItemPeer => ArkGridItemPeer.create(receiver), (_: ArkGridItemPeer) => {
        receiver.setGridItemOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
