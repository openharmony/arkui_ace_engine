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
import { ArkSymbolGlyphPeer } from "./peers/ArkSymbolglyphPeer"
import { CommonMethod, Rectangle, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, CustomBuilder, DragItemInfo, UniformDataType, PreDragStatus, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./ArkCommonInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions } from "./ArkUnitsInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, FontWeight } from "./ArkEnumsInterfaces"
import { Callback_Array_TouchTestInfo_TouchResult, Callback_ClickEvent_Void, Callback_Boolean_HoverEvent_Void, Callback_MouseEvent_Void, Callback_TouchEvent_Void, Callback_KeyEvent_Void, Callback_KeyEvent_Boolean, Callback_Void, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, Callback_DragEvent_String_Void, Callback_PreDragStatus_Void, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, Callback_TouchEvent_HitTestMode, Literal_Alignment_align } from "./SyntheticDeclarations"
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
import { SymbolEffectStrategy, SymbolRenderingStrategy, SymbolGlyphAttribute } from "./ArkSymbolglyphInterfaces"
import { SymbolEffect } from "./ArkSymbolEffectMaterialized"
import { AttributeUpdater } from "../handwritten/modifiers/ArkAttributeUpdater"
import { ArkSymbolGlyphNode } from "../handwritten/modifiers/ArkSymbolGlyphNode"
import { ArkSymbolGlyphAttributeSet, SymbolGlyphModifier } from "../handwritten/modifiers/ArkSymbolGlyphModifier"
import { applyUIAttributes } from "../handwritten/modifiers/ArkCommonModifier"
/** @memo:stable */
export class ArkSymbolGlyphComponent extends ArkCommonMethodComponent {
    getPeer(): ArkSymbolGlyphPeer {
        return (this.peer as ArkSymbolGlyphPeer)
    }
    getModifierHost(): ArkSymbolGlyphNode {
        if (this._modifierHost === undefined || this._modifierHost === null) {
            this._modifierHost = new ArkSymbolGlyphNode()
            this._modifierHost!.setPeer(this.getPeer())
        }
        return this._modifierHost as ArkSymbolGlyphNode
    }
    /** @memo */
    public setSymbolGlyphOptions(value?: Resource): this {
        if (this.checkPriority("setSymbolGlyphOptions")) {
            const value_casted = value as (Resource | undefined)
            this.getPeer()?.setSymbolGlyphOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontSize(value: number | string | Resource): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.fontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontColor(value: Array<ResourceColor>): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (Array<ResourceColor>)
            this.getPeer()?.fontColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fontWeight(value: number | FontWeight | string): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (number | FontWeight | string)
            this.getPeer()?.fontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public effectStrategy(value: SymbolEffectStrategy): this {
        if (this.checkPriority("effectStrategy")) {
            const value_casted = value as (SymbolEffectStrategy)
            this.getPeer()?.effectStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public renderingStrategy(value: SymbolRenderingStrategy): this {
        if (this.checkPriority("renderingStrategy")) {
            const value_casted = value as (SymbolRenderingStrategy)
            this.getPeer()?.renderingStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public symbolEffect(symbolEffect: SymbolEffect, isActive?: boolean | undefined | number | undefined): this {
        if (this.checkPriority("symbolEffect")) {
            const symbolEffect_type = runtimeType(symbolEffect)
            const isActive_type = runtimeType(isActive)
            if ((RuntimeType.BOOLEAN == isActive_type) || (RuntimeType.UNDEFINED == isActive_type)) {
                const symbolEffect_casted = symbolEffect as (SymbolEffect)
                const isActive_casted = isActive as (boolean | undefined)
                this.getPeer()?.symbolEffect0Attribute(symbolEffect_casted, isActive_casted)
                return this
            }
            if ((RuntimeType.NUMBER == isActive_type) || (RuntimeType.UNDEFINED == isActive_type)) {
                const symbolEffect_casted = symbolEffect as (SymbolEffect)
                const triggerValue_casted = isActive as (number | undefined)
                this.getPeer()?.symbolEffect1Attribute(symbolEffect_casted, triggerValue_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    attributeModifier(modifier: AttributeModifier<SymbolGlyphAttribute>): this {
        let peerNode = this.getPeer();
        let attributeSet = peerNode._attributeSet;
        let isAttributeUpdater = modifier instanceof AttributeUpdater
        if (isAttributeUpdater) {
            let attributeUpdater = modifier as AttributeUpdater<SymbolGlyphAttribute>;
            attributeUpdater.attribute = this.getModifierHost();
            if (!attributeSet) {
                attributeSet = new ArkSymbolGlyphAttributeSet();
                peerNode._attributeSet = attributeSet;
            }
            attributeUpdater.initializeModifier((peerNode._attributeSet as Object) as SymbolGlyphAttribute)
        } else {
            let attributeModifier = ((modifier as Object) as AttributeModifier<SymbolGlyphAttribute>);
            let symbolGlyphModifier = (attributeModifier as Object) as SymbolGlyphModifier;
            if (!attributeSet) {
                attributeSet = new ArkSymbolGlyphAttributeSet();
                attributeSet._modifiersWithKeys = symbolGlyphModifier._modifiersWithKeys;
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
export function ArkSymbolGlyph(
  /** @memo */
  style: ((attributes: ArkSymbolGlyphComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  value?: Resource | undefined
) {
    const receiver = remember(() => {
        return new ArkSymbolGlyphComponent()
    })
    NodeAttach<ArkSymbolGlyphPeer>((): ArkSymbolGlyphPeer => ArkSymbolGlyphPeer.create(receiver), (_: ArkSymbolGlyphPeer) => {
        receiver.setSymbolGlyphOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
