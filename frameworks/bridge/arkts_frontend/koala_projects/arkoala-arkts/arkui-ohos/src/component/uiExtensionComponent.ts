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
import { ComponentContent, CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./common"
import { Want, ErrorCallback } from "./../generated/ArkArkuiExternalInterfaces"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions } from "./units"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey } from "./enums"
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
import { Callback_Number_Void } from "./alphabetIndexer"
import { Callback_TerminationInfo_Void, TerminationInfo } from "./embeddedComponent"
import { ArkUIExtensionComponentComponent } from "./../generated/ArkUiExtensionComponent"
import { ArkUIExtensionComponentPeer } from "./../generated/peers/ArkUiExtensionComponentPeer"
export interface UIExtensionProxy {
    send(data: Map<string, Object>): void
    sendSync(data: Map<string, Object>): Map<string, Object>
    onAsyncReceiverRegister(callback_: ((parameter: UIExtensionProxy) => void)): void
    onSyncReceiverRegister(callback_: ((parameter: UIExtensionProxy) => void)): void
    offAsyncReceiverRegister(callback_: ((parameter: UIExtensionProxy) => void)): void
    offSyncReceiverRegister(callback_: ((parameter: UIExtensionProxy) => void)): void
}
export class UIExtensionProxyInternal implements MaterializedBase,UIExtensionProxy {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_uiextensionproxy(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._UIExtensionProxy_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = UIExtensionProxyInternal.ctor_uiextensionproxy()
        this.peer = new Finalizable(ctorPtr, UIExtensionProxyInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._UIExtensionProxy_getFinalizer()
    }
    public send(data: Map<string, Object>): void {
        const data_casted = data as (Map<string, Object>)
        this.send_serialize(data_casted)
        return
    }
    public sendSync(data: Map<string, Object>): Map<string, Object> {
        const data_casted = data as (Map<string, Object>)
        return this.sendSync_serialize(data_casted)
    }
    public onAsyncReceiverRegister(callback_: ((parameter: UIExtensionProxy) => void)): void {
        const callback__casted = callback_ as (((parameter: UIExtensionProxy) => void))
        this.onAsyncReceiverRegister_serialize(callback__casted)
        return
    }
    public onSyncReceiverRegister(callback_: ((parameter: UIExtensionProxy) => void)): void {
        const callback__casted = callback_ as (((parameter: UIExtensionProxy) => void))
        this.onSyncReceiverRegister_serialize(callback__casted)
        return
    }
    public offAsyncReceiverRegister(callback_?: ((parameter: UIExtensionProxy) => void)): void {
        const callback__casted = callback_ as (((parameter: UIExtensionProxy) => void) | undefined)
        this.offAsyncReceiverRegister_serialize(callback__casted)
        return
    }
    public offSyncReceiverRegister(callback_?: ((parameter: UIExtensionProxy) => void)): void {
        const callback__casted = callback_ as (((parameter: UIExtensionProxy) => void) | undefined)
        this.offSyncReceiverRegister_serialize(callback__casted)
        return
    }
    on(type: string, callback_: ((parameter: UIExtensionProxy) => void)): void {
        throw new Error("TBD")
    }
    off(type: string, callback_: ((parameter: UIExtensionProxy) => void)): void {
        throw new Error("TBD")
    }
    private send_serialize(data: Map<string, Object>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(data.size as int32 as int32)
        for (const pair of data) {
            const data_key = pair[0]
            const data_value = pair[1]
            thisSerializer.writeString(data_key)
            thisSerializer.writeCustomObject("Object", data_value)
        }
        ArkUIGeneratedNativeModule._UIExtensionProxy_send(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private sendSync_serialize(data: Map<string, Object>): Map<string, Object> {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(data.size as int32 as int32)
        for (const pair of data) {
            const data_key = pair[0]
            const data_value = pair[1]
            thisSerializer.writeString(data_key)
            thisSerializer.writeCustomObject("Object", data_value)
        }
        const retval  = ArkUIGeneratedNativeModule._UIExtensionProxy_sendSync(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const buffer_size : int32 = retvalDeserializer.readInt32()
        let buffer : Map<string, Object> = new Map<string, Object>()
        // TODO: TS map resize
        for (let buffer_i = 0; buffer_i < buffer_size; buffer_i++) {
            const buffer_key : string = (retvalDeserializer.readString() as string)
            const buffer_value : Object = (retvalDeserializer.readCustomObject("Object") as Object)
            buffer.set(buffer_key, buffer_value)
        }
        const returnResult : Map<string, Object> = buffer
        return returnResult
    }
    private onAsyncReceiverRegister_serialize(callback_: ((parameter: UIExtensionProxy) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._UIExtensionProxy_onAsyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private onSyncReceiverRegister_serialize(callback_: ((parameter: UIExtensionProxy) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(callback_)
        ArkUIGeneratedNativeModule._UIExtensionProxy_onSyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private offAsyncReceiverRegister_serialize(callback_?: ((parameter: UIExtensionProxy) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UIExtensionProxy_offAsyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private offSyncReceiverRegister_serialize(callback_?: ((parameter: UIExtensionProxy) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8(callback__type as int32)
        if ((RuntimeType.UNDEFINED) != (callback__type)) {
            const callback__value  = callback_!
            thisSerializer.holdAndWriteCallback(callback__value)
        }
        ArkUIGeneratedNativeModule._UIExtensionProxy_offSyncReceiverRegister(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static fromPtr(ptr: KPointer): UIExtensionProxyInternal {
        const obj : UIExtensionProxyInternal = new UIExtensionProxyInternal()
        obj.peer = new Finalizable(ptr, UIExtensionProxyInternal.getFinalizer())
        return obj
    }
}
export enum DpiFollowStrategy {
    FOLLOW_HOST_DPI = 0,
    FOLLOW_UI_EXTENSION_ABILITY_DPI = 1
}
export interface UIExtensionOptions {
    isTransferringCaller?: boolean;
    placeholder?: ComponentContent;
    areaChangePlaceholder?: Map<string, ComponentContent>;
    dpiFollowStrategy?: DpiFollowStrategy;
}
export interface ReceiveCallback {
    _ReceiveCallbackStub: string;
}
export type Callback_UIExtensionProxy_Void = (parameter: UIExtensionProxy) => void;
export interface Literal_Number_code_Want_want {
    code: number;
    want?: Want;
}
export type Callback_Literal_Number_code_Want_want_Void = (parameter: Literal_Number_code_Want_want) => void;
/** @memo:stable */
export interface UIExtensionComponentAttribute extends CommonMethod {
    /** @memo */
    setUIExtensionComponentOptions(want: Want, options?: UIExtensionOptions): this
    /** @memo */
    onRemoteReady(value: ((parameter: UIExtensionProxy) => void)): this
    /** @memo */
    onReceive(value: ReceiveCallback): this
    /** @memo */
    onResult(value: ((parameter: Literal_Number_code_Want_want) => void)): this
    /** @memo */
    onRelease(value: ((index: number) => void)): this
    /** @memo */
    onError(value: ErrorCallback): this
    /** @memo */
    onTerminated(value: ((parameter: TerminationInfo) => void)): this
}
/** @memo */
export function UIExtensionComponent(
  /** @memo */
  style: ((attributes: UIExtensionComponentAttribute) => void) | undefined,
  want: Want, options?: UIExtensionOptions | undefined, 
  /** @memo */
  content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkUIExtensionComponentComponent()
    })
    NodeAttach<ArkUIExtensionComponentPeer>((): ArkUIExtensionComponentPeer => ArkUIExtensionComponentPeer.create(receiver), (_: ArkUIExtensionComponentPeer) => {
        receiver.setUIExtensionComponentOptions(want,options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
