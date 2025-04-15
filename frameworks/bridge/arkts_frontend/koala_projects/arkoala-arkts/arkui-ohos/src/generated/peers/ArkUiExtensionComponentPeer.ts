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
import { ArkCommonMethodPeer, ArkCommonMethodAttributes } from "./ArkCommonPeer"
import { CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./../../component/common"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, PX, VP, FP, LPX, Percentage } from "./../../component/units"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey } from "./../../component/enums"
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
import { Callback_UIExtensionProxy_Void, UIExtensionProxy, ReceiveCallback, Callback_Literal_Number_code_Want_want_Void, Literal_Number_code_Want_want, UIExtensionOptions, UIExtensionComponentAttribute, DpiFollowStrategy } from "./../../component/uiExtensionComponent"
import { ErrorCallback } from "./../ArkArkuiExternalInterfaces"
import { AbilityWant, BusinessError } from "#external"
import { ArkUIAniUiextensionModal, ArkUIAniUIExtensionOptions, ArkUIAniModule } from "arkui.ani"
import { Callback_Number_Void } from "./../../component/alphabetIndexer"
import { Callback_TerminationInfo_Void, TerminationInfo } from "./../../component/embeddedComponent"
import { CallbackKind } from "./CallbackKind"
import { CallbackTransformer } from "./CallbackTransformer"
import { TypeChecker } from "#components"
import { MaterializedBase, toPeerPtr, wrapCallback, InteropNativeModule } from "@koalaui/interop"
export class ArkUIExtensionCallbackHelp {
    onRemoteReady?: ((parameter: UIExtensionProxy) => void)
    onReceive?: ((param: Record<string, Object>) => void)
    onResult?: ((parameter: Literal_Number_code_Want_want) => void)
    onRelease?: ((index: number) => void)
    onError?: ((e: BusinessError) => void)
    onTerminated?: ((parameter: TerminationInfo) => void)
    constructor() {
        this.onRemoteReady = undefined;
        this.onReceive = undefined;
        this.onResult = undefined;
        this.onRelease = undefined;
        this.onError = undefined;
        this.onTerminated = undefined;
    }
}

export class ArkUIExtensionComponentPeer extends ArkCommonMethodPeer {
    _callbackHelp?: ArkUIExtensionCallbackHelp;
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
        this.InitArkUIExtensionCallbackHelp();
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkUIExtensionComponentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._UIExtensionComponent_construct(peerId, flags)
        const _peer  = new ArkUIExtensionComponentPeer(_peerPtr, peerId, "UIExtensionComponent", flags)
        component?.setPeer(_peer)
        return _peer
    }
    InitArkUIExtensionCallbackHelp(): void {
        InteropNativeModule._NativeLog("[AceUiExtensionComponent] InitArkUIExtensionCallbackHelp entry");
        this._callbackHelp = new ArkUIExtensionCallbackHelp();
    }
    setUIExtensionComponentOptionsAttribute(want: AbilityWant, options?: UIExtensionOptions): void {
        InteropNativeModule._NativeLog("[AceUiExtensionComponent] setUIExtensionComponentOptionsAttribute entry");
        if (options != undefined) {
            let innerOption : ArkUIAniUIExtensionOptions = new ArkUIAniUIExtensionOptions();
            if (options.isTransferringCaller != undefined) {
                innerOption.isTransferringCaller = (options.isTransferringCaller) as boolean;
            }

            if (options.dpiFollowStrategy != undefined) {
                innerOption.dpiFollowStrategy = (options.dpiFollowStrategy as DpiFollowStrategy).valueOf();
            }
            ArkUIAniUiextensionModal._Uiextension_Set_Option(this.peer.ptr, innerOption);
        }

        ArkUIAniUiextensionModal._Uiextension_Set_Want(this.peer.ptr, want);
    }
    onRemoteReadyAttribute(value: ((parameter: UIExtensionProxy) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._UIExtensionComponentAttribute_onRemoteReady(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReceiveAttribute(value: (param: Record<string, Object>) => void): void {
        const help = this._callbackHelp;
        if (help != undefined && help != null) {
            help.onReceive = value;
            ArkUIAniUiextensionModal._Uiextension_Set_OnReciveCallback(this.peer.ptr, (param: Record<string, Object>) => {
                const onReceive = this._callbackHelp?.onReceive;
                if (onReceive !== undefined && onReceive !== null) {
                    const innerParam = param;
                    onReceive(innerParam);
                }
            });
        }
    }
    onResultAttribute(value: ((parameter: Literal_Number_code_Want_want) => void)): void {
        const help = this._callbackHelp;
        if (help != undefined && help != null) {
            help.onResult = value;
            ArkUIAniUiextensionModal._Uiextension_Set_OnResultCallback(
                this.peer.ptr, (code1: number, want1 : AbilityWant) => {
                    const onResult = this._callbackHelp?.onResult;
                    if (onResult !== undefined && onResult !== null) {
                        const param = {
                            code: code1,
                            want: want1
                        } as Literal_Number_code_Want_want
                        onResult(param);
                    }
                });
        }
    }
    onReleaseAttribute(value: ((index: number) => void)): void {
        const help = this._callbackHelp;
        if (help != undefined && help != null) {
            help.onRelease = value;
            ArkUIAniUiextensionModal._Uiextension_Set_OnReleaseCallback(
                this.peer.ptr, (code: number) => {
                    const onRelease = this._callbackHelp?.onRelease;
                    if (onRelease !== undefined && onRelease !== null) {
                        onRelease(code);
                    }
                });
        }
    }
    onErrorAttribute(value: (e: BusinessError) => void): void {
        const help = this._callbackHelp;
        if (help != undefined && help != null) {
            help.onError = value;
            ArkUIAniUiextensionModal._Uiextension_Set_OnErrorCallback(
                this.peer.ptr, (code1: number, name1: string, message1: string) => {
                    const onError = this._callbackHelp?.onError;
                    if (onError !== undefined && onError !== null) {
                        const param = {
                            code: code1,
                            name: name1,
                            message: message1
                        } as BusinessError
                        onError(param);
                    }
                });
        }
    }
    onTerminatedAttribute(value: ((parameter: TerminationInfo) => void)): void {
        const help = this._callbackHelp;
        if (help != undefined && help != null) {
            help.onTerminated = value;
            ArkUIAniUiextensionModal._Uiextension_Set_OnTerminationCallback(
                this.peer.ptr, (code1: number, want1 : AbilityWant) => {
                    const onTerminated = this._callbackHelp?.onTerminated;
                    if (onTerminated !== undefined && onTerminated !== null) {
                        const param = {
                            code: code1,
                            want: want1
                        } as TerminationInfo
                        onTerminated(param);
                    }
                });
        }
    }
}
export interface ArkUIExtensionComponentAttributes extends ArkCommonMethodAttributes {
    onRemoteReady?: ((parameter: UIExtensionProxy) => void)
    onReceive?: (param: Record<string, Object>) => void
    onResult?: ((parameter: Literal_Number_code_Want_want) => void)
    onRelease?: ((index: number) => void)
    onError?: ErrorCallback
    onTerminated?: ((parameter: TerminationInfo) => void)
}