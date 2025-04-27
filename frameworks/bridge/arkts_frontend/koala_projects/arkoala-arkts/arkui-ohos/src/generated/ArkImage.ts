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
import { KStringPtr, KBoolean, RuntimeType, runtimeType, InteropNativeModule } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ComponentBase } from "../ComponentBase"
import { TypeChecker } from "#components"
import { ArkCommonMethodComponent } from "./ArkCommon"
import { ArkImagePeer } from "./peers/ArkImagePeer"
import { CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, PointLightStyle } from "./../component/common"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, ColorFilter } from "./../component/units"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, ImageFit, CopyOptions } from "./../component/enums"
import { LengthMetrics } from "../Graphics"
import { ResizableOptions, ImageRenderMode, DynamicRangeMode, ImageInterpolation, ImageSourceSize, DrawingColorFilter, Callback_Type_ImageAttribute_onComplete_callback_event_Void, Type_ImageAttribute_onComplete_callback_event, ImageErrorCallback, ResolutionQuality, DrawableDescriptor, ImageAttribute, ImageContent, ImageInterface } from "./../component/image"
import { Resource } from "global/resource";
import { Callback_Void } from "./../component/abilityComponent"
import { FocusBoxStyle, FocusPriority } from "./../component/focus"
import { CircleShape } from "./ArkCircleShapeMaterialized"
import { EllipseShape } from "./ArkEllipseShapeMaterialized"
import { PathShape } from "./ArkPathShapeMaterialized"
import { RectShape } from "./ArkRectShapeMaterialized"
import { AttributeModifier } from "./../component/common"
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureType, GestureMask } from "./../component/gesture"
import { PixelMap } from "./ArkPixelMapMaterialized"
import { ImageAnalyzerConfig, ImageAIOptions } from "./../component/imageCommon"
import { ArkImageAttributeSet, ImageModifier } from "../handwritten/modifiers/ArkImageModifier"
import { applyUIAttributes, ArkCommonAttributeSet } from "../handwritten/modifiers/ArkCommonModifier"
import { AttributeUpdater } from "../AttributeUpdater"
import { ArkImageNode } from "../handwritten/modifiers/ArkImageNode"
import { ArkBaseNode } from "../handwritten/modifiers/ArkBaseNode"
/** @memo:stable */
export class ArkImageComponent extends ArkCommonMethodComponent implements ImageAttribute {

    getModifierHost(): ArkBaseNode {
        if (this._modifierHost == undefined || this._modifierHost == null) {
            this._modifierHost = new ArkImageNode()
            this._modifierHost!.setPeer(this.getPeer())
        }
        return this._modifierHost!
    }

    getPeer(): ArkImagePeer {
        return (this.peer as ArkImagePeer)
    }
    /** @memo */
    public setImageOptions(src: PixelMap | ResourceStr | DrawableDescriptor | PixelMap | ResourceStr | DrawableDescriptor | ImageContent, imageAIOptions?: ImageAIOptions): this {
        if (this.checkPriority("setImageOptions")) {
            const src_type = runtimeType(src)
            const imageAIOptions_type = runtimeType(imageAIOptions)
            if (((TypeChecker.isPixelMap(src, false, false)) || ((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type)) || (TypeChecker.isDrawableDescriptor(src, false))) && (RuntimeType.UNDEFINED == imageAIOptions_type)) {
                const src_casted = src as (PixelMap | ResourceStr | DrawableDescriptor)
                this.getPeer()?.setImageOptions0Attribute(src_casted)
                return this
            }
            if (((TypeChecker.isPixelMap(src, false, false)) || ((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type)) || (TypeChecker.isDrawableDescriptor(src, false))) && (RuntimeType.OBJECT == imageAIOptions_type)) {
                const src_casted = src as (PixelMap | ResourceStr | DrawableDescriptor)
                const imageAIOptions_casted = imageAIOptions as (ImageAIOptions)
                this.getPeer()?.setImageOptions2Attribute(src_casted, imageAIOptions_casted)
                return this
            }
            if (((TypeChecker.isPixelMap(src, false, false)) || ((RuntimeType.STRING == src_type) || (RuntimeType.OBJECT == src_type)) || (TypeChecker.isDrawableDescriptor(src, false)) || (TypeChecker.isImageContent(src))) && (RuntimeType.UNDEFINED == imageAIOptions_type)) {
                const src_casted = src as (PixelMap | ResourceStr | DrawableDescriptor | ImageContent)
                this.getPeer()?.setImageOptions1Attribute(src_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    /** @memo */
    public alt(value: string | Resource | PixelMap): this {
        if (this.checkPriority("alt")) {
            const value_casted = value as (string | Resource | PixelMap)
            this.getPeer()?.altAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public matchTextDirection(value: boolean): this {
        if (this.checkPriority("matchTextDirection")) {
            const value_casted = value as (boolean)
            this.getPeer()?.matchTextDirectionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fitOriginalSize(value: boolean): this {
        if (this.checkPriority("fitOriginalSize")) {
            const value_casted = value as (boolean)
            this.getPeer()?.fitOriginalSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public fillColor(value: ResourceColor): this {
        if (this.checkPriority("fillColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.fillColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public objectFit(value: ImageFit): this {
        if (this.checkPriority("objectFit")) {
            const value_casted = value as (ImageFit)
            this.getPeer()?.objectFitAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public objectRepeat(value: ImageRepeat): this {
        if (this.checkPriority("objectRepeat")) {
            const value_casted = value as (ImageRepeat)
            this.getPeer()?.objectRepeatAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public autoResize(value: boolean): this {
        if (this.checkPriority("autoResize")) {
            const value_casted = value as (boolean)
            this.getPeer()?.autoResizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public renderMode(value: ImageRenderMode): this {
        if (this.checkPriority("renderMode")) {
            const value_casted = value as (ImageRenderMode)
            this.getPeer()?.renderModeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public dynamicRangeMode(value: DynamicRangeMode): this {
        if (this.checkPriority("dynamicRangeMode")) {
            const value_casted = value as (DynamicRangeMode)
            this.getPeer()?.dynamicRangeModeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public interpolation(value: ImageInterpolation): this {
        if (this.checkPriority("interpolation")) {
            const value_casted = value as (ImageInterpolation)
            this.getPeer()?.interpolationAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public sourceSize(value: ImageSourceSize): this {
        if (this.checkPriority("sourceSize")) {
            const value_casted = value as (ImageSourceSize)
            this.getPeer()?.sourceSizeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public syncLoad(value: boolean): this {
        if (this.checkPriority("syncLoad")) {
            const value_casted = value as (boolean)
            this.getPeer()?.syncLoadAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public colorFilter(value: ColorFilter | DrawingColorFilter): this {
        if (this.checkPriority("colorFilter")) {
            const value_casted = value as (ColorFilter | DrawingColorFilter)
            this.getPeer()?.colorFilterAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public copyOption(value: CopyOptions): this {
        if (this.checkPriority("copyOption")) {
            const value_casted = value as (CopyOptions)
            this.getPeer()?.copyOptionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public draggable(value: boolean): this {
        if (this.checkPriority("draggable")) {
            const value_casted = value as (boolean)
            this.getPeer()?.draggableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public pointLight(value: PointLightStyle): this {
        if (this.checkPriority("pointLight")) {
            const value_casted = value as (PointLightStyle)
            this.getPeer()?.pointLightAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public edgeAntialiasing(value: number): this {
        if (this.checkPriority("edgeAntialiasing")) {
            const value_casted = value as (number)
            this.getPeer()?.edgeAntialiasingAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onComplete(value: ((event?: Type_ImageAttribute_onComplete_callback_event) => void)): this {
        if (this.checkPriority("onComplete")) {
            const value_casted = value as (((event?: Type_ImageAttribute_onComplete_callback_event) => void))
            this.getPeer()?.onCompleteAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onError(value: ImageErrorCallback): this {
        if (this.checkPriority("onError")) {
            const value_casted = value as (ImageErrorCallback)
            this.getPeer()?.onErrorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onFinish(value: (() => void)): this {
        if (this.checkPriority("onFinish")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onFinishAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableAnalyzer(value: boolean): this {
        if (this.checkPriority("enableAnalyzer")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableAnalyzerAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public analyzerConfig(value: ImageAnalyzerConfig): this {
        if (this.checkPriority("analyzerConfig")) {
            const value_casted = value as (ImageAnalyzerConfig)
            this.getPeer()?.analyzerConfigAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public resizable(value: ResizableOptions): this {
        if (this.checkPriority("resizable")) {
            const value_casted = value as (ResizableOptions)
            this.getPeer()?.resizableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public privacySensitive(value: boolean): this {
        if (this.checkPriority("privacySensitive")) {
            const value_casted = value as (boolean)
            this.getPeer()?.privacySensitiveAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enhancedImageQuality(value: ResolutionQuality): this {
        if (this.checkPriority("enhancedImageQuality")) {
            const value_casted = value as (ResolutionQuality)
            this.getPeer()?.enhancedImageQualityAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public attributeModifier<T>(value: AttributeModifier<T>): this {
        let peerNode = this.getPeer()
        if (!peerNode._attributeSet) {
            let isImageModifier: boolean = (value instanceof ImageModifier)
            if (isImageModifier) {
                let imageModifier = value as object as ImageModifier
                peerNode._attributeSet = imageModifier.attribute
            } else {
                peerNode._attributeSet = new ArkCommonAttributeSet()
            }
        }
        applyUIAttributes(value, peerNode)
        let isAttributeUpdater: boolean = (value instanceof AttributeUpdater)
        if (isAttributeUpdater) {
            let attributeUpdater = value as object as AttributeUpdater<ImageAttribute, ImageInterface>
            attributeUpdater.updateConstructorParams = (...params: Object[]) => {
                const node = this.getModifierHost()! as ArkImageNode
                this.getModifierHost()!.constructParam(params)
                return node
            }
        }
        peerNode._attributeSet!.applyModifierPatch(peerNode)
        return this
    }
    public applyAttributesFinish(): void {
        // we calls this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
