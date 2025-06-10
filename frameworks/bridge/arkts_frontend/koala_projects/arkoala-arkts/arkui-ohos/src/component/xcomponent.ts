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

import { ImageAnalyzerConfig, ImageAIOptions } from "./imageCommon"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, float32, int64 } from "@koalaui/common"
import { Serializer } from "./../generated/peers/Serializer"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { Deserializer } from "./../generated/peers/Deserializer"
import { CallbackTransformer } from "./../generated/peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { XComponentType, HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey } from "./enums"
import { CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./common"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, VoidCallback } from "./units"
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
import { ArkXComponentComponent } from "./../generated/ArkXcomponent"
import { ArkXComponentPeer } from "./../generated/peers/ArkXcomponentPeer"
export class XComponentControllerInternal {
    public static fromPtr(ptr: KPointer): XComponentController {
        const obj : XComponentController = new XComponentController()
        obj.peer = new Finalizable(ptr, XComponentController.getFinalizer())
        return obj
    }
}
export class XComponentController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_xcomponentcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._XComponentController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = XComponentController.ctor_xcomponentcontroller()
        this.peer = new Finalizable(ctorPtr, XComponentController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._XComponentController_getFinalizer()
    }
    public getXComponentSurfaceId(): string {
        return this.getXComponentSurfaceId_serialize()
    }
    public getXComponentContext(): Object {
        return this.getXComponentContext_serialize()
    }
    public setXComponentSurfaceSize(value: Literal_Number_surfaceHeight_surfaceWidth): void {
        const value_casted = value as (Literal_Number_surfaceHeight_surfaceWidth)
        this.setXComponentSurfaceSize_serialize(value_casted)
        return
    }
    public setXComponentSurfaceRect(rect: SurfaceRect): void {
        const rect_casted = rect as (SurfaceRect)
        this.setXComponentSurfaceRect_serialize(rect_casted)
        return
    }
    public getXComponentSurfaceRect(): SurfaceRect {
        return this.getXComponentSurfaceRect_serialize()
    }
    public setXComponentSurfaceRotation(rotationOptions: SurfaceRotationOptions): void {
        const rotationOptions_casted = rotationOptions as (SurfaceRotationOptions)
        this.setXComponentSurfaceRotation_serialize(rotationOptions_casted)
        return
    }
    public getXComponentSurfaceRotation(): SurfaceRotationOptions {
        return this.getXComponentSurfaceRotation_serialize()
    }
    public onSurfaceCreated(surfaceId: string): void {
        const surfaceId_casted = surfaceId as (string)
        this.onSurfaceCreated_serialize(surfaceId_casted)
        return
    }
    public onSurfaceChanged(surfaceId: string, rect: SurfaceRect): void {
        const surfaceId_casted = surfaceId as (string)
        const rect_casted = rect as (SurfaceRect)
        this.onSurfaceChanged_serialize(surfaceId_casted, rect_casted)
        return
    }
    public onSurfaceDestroyed(surfaceId: string): void {
        const surfaceId_casted = surfaceId as (string)
        this.onSurfaceDestroyed_serialize(surfaceId_casted)
        return
    }
    public startImageAnalyzer(config: ImageAnalyzerConfig): Promise<void> {
        const config_casted = config as (ImageAnalyzerConfig)
        return this.startImageAnalyzer_serialize(config_casted)
    }
    public stopImageAnalyzer(): void {
        this.stopImageAnalyzer_serialize()
        return
    }
    private getXComponentSurfaceId_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._XComponentController_getXComponentSurfaceId(this.peer!.ptr)
        return retval
    }
    private getXComponentContext_serialize(): Object {
        const retval  = ArkUIGeneratedNativeModule._XComponentController_getXComponentContext(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setXComponentSurfaceSize_serialize(value: Literal_Number_surfaceHeight_surfaceWidth): void {
        const thisSerializer : Serializer = Serializer.hold()
        const value_surfaceWidth  = value.surfaceWidth
        thisSerializer.writeNumber(value_surfaceWidth)
        const value_surfaceHeight  = value.surfaceHeight
        thisSerializer.writeNumber(value_surfaceHeight)
        ArkUIGeneratedNativeModule._XComponentController_setXComponentSurfaceSize(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setXComponentSurfaceRect_serialize(rect: SurfaceRect): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSurfaceRect(rect)
        ArkUIGeneratedNativeModule._XComponentController_setXComponentSurfaceRect(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getXComponentSurfaceRect_serialize(): SurfaceRect {
        const retval  = ArkUIGeneratedNativeModule._XComponentController_getXComponentSurfaceRect(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const returnResult : SurfaceRect = retvalDeserializer.readSurfaceRect()
        return returnResult
    }
    private setXComponentSurfaceRotation_serialize(rotationOptions: SurfaceRotationOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSurfaceRotationOptions(rotationOptions)
        ArkUIGeneratedNativeModule._XComponentController_setXComponentSurfaceRotation(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getXComponentSurfaceRotation_serialize(): SurfaceRotationOptions {
        const retval  = ArkUIGeneratedNativeModule._XComponentController_getXComponentSurfaceRotation(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const returnResult : SurfaceRotationOptions = retvalDeserializer.readSurfaceRotationOptions()
        return returnResult
    }
    private onSurfaceCreated_serialize(surfaceId: string): void {
        ArkUIGeneratedNativeModule._XComponentController_onSurfaceCreated(this.peer!.ptr, surfaceId)
    }
    private onSurfaceChanged_serialize(surfaceId: string, rect: SurfaceRect): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSurfaceRect(rect)
        ArkUIGeneratedNativeModule._XComponentController_onSurfaceChanged(this.peer!.ptr, surfaceId, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private onSurfaceDestroyed_serialize(surfaceId: string): void {
        ArkUIGeneratedNativeModule._XComponentController_onSurfaceDestroyed(this.peer!.ptr, surfaceId)
    }
    private startImageAnalyzer_serialize(config: ImageAnalyzerConfig): Promise<void> {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeImageAnalyzerConfig(config)
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._XComponentController_startImageAnalyzer(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private stopImageAnalyzer_serialize(): void {
        ArkUIGeneratedNativeModule._XComponentController_stopImageAnalyzer(this.peer!.ptr)
    }
}
export interface SurfaceRect {
    offsetX?: number;
    offsetY?: number;
    surfaceWidth: number;
    surfaceHeight: number;
}
export interface SurfaceRotationOptions {
    lock?: boolean;
}
export interface Literal_Number_surfaceHeight_surfaceWidth {
    surfaceWidth: number;
    surfaceHeight: number;
}
export interface XComponentOptions {
    type: XComponentType;
    controller: XComponentController;
    imageAIOptions?: ImageAIOptions;
}
export interface Type_XComponentInterface_value {
    id: string;
    type: string;
    libraryname?: string;
    controller?: XComponentController;
}
export type OnNativeLoadCallback = (event?: Object) => void;
/** @memo:stable */
export interface XComponentAttribute extends CommonMethod {
    /** @memo */
    setXComponentOptions(value: Type_XComponentInterface_value | XComponentOptions): this
    /** @memo */
    onLoad(value: OnNativeLoadCallback): this
    /** @memo */
    onDestroy(value: VoidCallback): this
    /** @memo */
    enableAnalyzer(value: boolean): this
    /** @memo */
    enableSecure(value: boolean): this
}
/** @memo */
export function XComponent(
  /** @memo */
  style: ((attributes: XComponentAttribute) => void) | undefined,
  value: Type_XComponentInterface_value | XComponentOptions, 
  /** @memo */
  content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkXComponentComponent()
    })
    NodeAttach<ArkXComponentPeer>((): ArkXComponentPeer => ArkXComponentPeer.create(receiver), (_: ArkXComponentPeer) => {
        receiver.setXComponentOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
