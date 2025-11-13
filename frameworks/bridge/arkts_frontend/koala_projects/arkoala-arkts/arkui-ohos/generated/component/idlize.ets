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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { ActionSheetOptions_serializer, ActionSheetOptions, DismissDialogAction, DismissDialogAction_serializer } from "./actionSheet"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
import { AlertDialogParamWithConfirm_serializer, AlertDialogParamWithButtons_serializer, AlertDialogParamWithOptions_serializer, AlertDialogParamWithConfirm, AlertDialogParamWithButtons, AlertDialogParamWithOptions, DialogAlignment } from "./alertDialog"
import { AnimateParam_serializer, TranslateOptions_serializer, KeyframeAnimateParam_serializer, KeyframeState_serializer, AnimateParam, TranslateOptions, KeyframeAnimateParam, KeyframeState, TouchEvent, TouchEventInternal, ClickEvent, ClickEventInternal, UICommonEvent, UICommonEventInternal, ItemDragEventHandler_serializer, OnMoveHandler, ItemDragEventHandler, PopupCommonOptions_serializer, MenuOptions_serializer, PopupCommonOptions, MenuOptions, ThemeColorMode, GeometryInfo, Measurable, Layoutable, Rectangle, ShadowOptions, ShadowStyle, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, KeyboardAvoidMode, HoverModeAreaType, SizeResult, TouchObject, KeyEvent, KeyEventInternal, MouseEvent, MouseEventInternal, SourceTool, Rectangle_serializer, ShadowOptions_serializer, BackgroundBlurStyleOptions_serializer, BackgroundEffectOptions_serializer, ChildrenMainSize_serializer, ChildrenMainSize, ChildrenMainSizeInternal, OnWillScrollCallback, OnScrollCallback } from "./common"
import { ArkListOptions_serializer } from "./../framework/ohos.arkui.ArcList"
import { ArkListOptions, ArcScrollIndexHandler } from "@ohos.arkui.ArcList"
import { SwipeActionOptions_serializer, SwipeActionOptions } from "./listItem"
import { ArcScrollBarOptions_serializer } from "./../framework/ohos.arkui.ArcScrollBar"
import { ArcScrollBarOptions } from "@ohos.arkui.ArcScrollBar"
import { Resource_serializer } from "./../framework/resource"
import { VoidCallback, SizeOptions_serializer, Length, SizeOptions, Position_serializer, Position, ResourceColor, ConstraintSizeOptions, Offset, Dimension, BorderRadiuses, EdgeWidths, EdgeColors, EdgeStyles, Offset_serializer, BorderRadiuses_serializer, EdgeWidths_serializer, EdgeColors_serializer, EdgeStyles_serializer } from "./units"
import { Resource } from "global.resource"
import { CrownSensitivity, BarState, Color, BorderStyle, AnimationPropertyType } from "./enums"
import { ContentModifier, extractors, hookRootAttributeModifier, AttributeModifier, AttributeUpdater, hookComponentRootAttributeModifier, hookCustomBuilderRootAttributeModifier, hookCustomLayoutRootAttributeModifier } from "#handwritten"
import { ButtonConfiguration } from "./button"
import { CheckBoxConfiguration } from "./checkbox"
import { DataPanelConfiguration } from "./dataPanel"
import { GaugeConfiguration } from "./gauge"
import { LoadingProgressConfiguration } from "./loadingProgress"
import { ProgressConfiguration } from "./progress"
import { RadioConfiguration } from "./radio"
import { RatingConfiguration } from "./rating"
import { MenuItemConfiguration } from "./select"
import { SliderConfiguration } from "./slider"
import { TextClockConfiguration } from "./textClock"
import { TextTimerConfiguration } from "./textTimer"
import { ToggleConfiguration } from "./toggle"
import { Size_serializer, Frame_serializer, LengthMetrics_serializer, ColorMetrics_serializer, Vector2_serializer, Vector3_serializer, Circle_serializer, RoundRect_serializer, CommandPath_serializer } from "./../Graphics"
import { LayoutConstraint_serializer } from "./../FrameNode"
import { FrameNode, LayoutConstraint } from "arkui.FrameNode"
import { Size, Frame, LengthMetrics, ColorMetrics, Vector2, Vector3, Matrix4, Circle, RoundRect, CommandPath } from "arkui.Graphics"
import { RenderNode } from "arkui.RenderNode"
import { default as common2D } from "@ohos.graphics.common2D"
import { PanDirection, SwipeDirection, GestureMode, GestureEvent, GestureEventInternal, GestureMask } from "./gesture"
import { default as image } from "@ohos.multimedia.image"
import { font_FontOptions_serializer, font_FontInfo_serializer } from "./../framework/ohos.font"
import { font_UIFontConfig_serializer } from "./../framework/ohos.font.custom"
import { default as font } from "@ohos.font"
import { MeasureOptions_serializer } from "./../framework/ohos.measure"
import { MeasureOptions } from "@ohos.measure"
import { TextMenuOptions_serializer, TextMenuOptions } from "./textCommon"
import { CustomBuilder } from "./builder"
import { NavigationOptions_serializer, NavPathStack, NavPathStackInternal, NavPathInfo, NavPathInfoInternal, NavigationOptions } from "./navigation"
import { TargetInfo_serializer } from "./../framework/ohos.arkui.UIContext"
import { TargetInfo } from "@ohos.arkui.UIContext"
import { uiObserver_NavigationInfo_serializer } from "./../framework/ohos.arkui.observer"
import { default as uiObserver } from "@ohos.arkui.observer"
import { router_RouterOptions_serializer, router_RouterState_serializer } from "./../framework/ohos.router"
import { AsyncCallback, BusinessError } from "@ohos.base"
import { default as router } from "@ohos.router"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { default as curves } from "@ohos.curves"
import { Scroller, Scroller_serializer } from "./scroll"
import { ComponentContentBase } from "arkui.ComponentContent"
import { CustomDialogController } from "./customDialogController"
import { LevelMode, ImmersiveMode } from "@ohos.promptAction"
import { ParticleUpdater, ParticleColorOptions, VelocityOptions, EmitterParticleOptions, ParticleEmitterShape, DistributionType, DisturbanceFieldShape, ParticleColorOptions_serializer, EmitterParticleOptions_serializer, VelocityOptions_serializer } from "./particle"
import { RootModifier } from "./../RootModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ComponentRootModifier } from "./../ComponentRootModifier"
import { CustomBuilderRootModifier } from "./../CustomBuilderRootModifier"
import { CustomLayoutRootModifier } from "./../CustomLayoutRootModifier"
import { GlobalScope } from "./../framework/GlobalScope"
import { ComponentContentBase_serializer } from "./../ComponentContent"
import { curves_ICurve_serializer } from "./../framework/ohos.curves"
import { TimePickerDialogOptions_serializer, TimePickerDialogOptions } from "./timePicker"
import { TextPickerDialogOptions_serializer, TextPickerDialogOptions,DividerOptions_serializer, DividerOptions } from "./textPicker"
import { DatePickerDialogOptions_serializer, DatePickerDialogOptions } from "./datePicker"
import { common2D_Rect_serializer } from "./../framework/ohos.graphics.common2D"
export class ActionSheet {
    static show_serialize(options: ActionSheetOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        ActionSheetOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._ActionSheet_show(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static show(options: ActionSheetOptions): void {
        const options_casted = options as (ActionSheetOptions)
        ActionSheet.show_serialize(options_casted)
        return
    }
}
export class AlertDialog {
    static show_serialize(options: AlertDialogParamWithConfirm | AlertDialogParamWithButtons | AlertDialogParamWithOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options instanceof AlertDialogParamWithConfirm) {
            thisSerializer.writeInt8((0).toByte())
            const optionsForIdx0  = options as AlertDialogParamWithConfirm
            AlertDialogParamWithConfirm_serializer.write(thisSerializer, optionsForIdx0)
        } else if (options instanceof AlertDialogParamWithButtons) {
            thisSerializer.writeInt8((1).toByte())
            const optionsForIdx1  = options as AlertDialogParamWithButtons
            AlertDialogParamWithButtons_serializer.write(thisSerializer, optionsForIdx1)
        } else if (options instanceof AlertDialogParamWithOptions) {
            thisSerializer.writeInt8((2).toByte())
            const optionsForIdx2  = options as AlertDialogParamWithOptions
            AlertDialogParamWithOptions_serializer.write(thisSerializer, optionsForIdx2)
        }
        ArkUIGeneratedNativeModule._AlertDialog_show(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static show(options: AlertDialogParamWithConfirm | AlertDialogParamWithButtons | AlertDialogParamWithOptions): void {
        const options_casted = options as (AlertDialogParamWithConfirm | AlertDialogParamWithButtons | AlertDialogParamWithOptions)
        AlertDialog.show_serialize(options_casted)
        return
    }
}
export class DialogExtender {
    static showTimePickerDialog_serialize(options: TimePickerDialogOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        TimePickerDialogOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._DialogExtender_showTimePickerDialog(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static showTextPickerDialog_serialize(options: TextPickerDialogOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        TextPickerDialogOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._DialogExtender_showTextPickerDialog(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static showDatePickerDialog_serialize(options: DatePickerDialogOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        DatePickerDialogOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._DialogExtender_showDatePickerDialog(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static showTimePickerDialog(options: TimePickerDialogOptions): void {
        const options_casted = options as (TimePickerDialogOptions)
        DialogExtender.showTimePickerDialog_serialize(options_casted)
        return
    }
    public static showTextPickerDialog(options: TextPickerDialogOptions): void {
        const options_casted = options as (TextPickerDialogOptions)
        DialogExtender.showTextPickerDialog_serialize(options_casted)
        return
    }
    public static showDatePickerDialog(options: DatePickerDialogOptions): void {
        const options_casted = options as (DatePickerDialogOptions)
        DialogExtender.showDatePickerDialog_serialize(options_casted)
        return
    }
}
export class AnimationExtender {
    static SetClipRect_serialize(node: KPointer, x: float, y: float, width: float, height: float): void {
        ArkUIGeneratedNativeModule._AnimationExtender_SetClipRect(node, x, y, width, height)
    }
    static OpenImplicitAnimation_serialize(param: AnimateParam): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        AnimateParam_serializer.write(thisSerializer, param)
        ArkUIGeneratedNativeModule._AnimationExtender_OpenImplicitAnimation(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static CloseImplicitAnimation_serialize(): void {
        ArkUIGeneratedNativeModule._AnimationExtender_CloseImplicitAnimation()
    }
    static OpenImplicitAnimationForAnimation_serialize(node: KPointer, param: AnimateParam | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (param !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const paramTmpValue  = param!
            AnimateParam_serializer.write(thisSerializer, paramTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AnimationExtender_OpenImplicitAnimationForAnimation(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static CloseImplicitAnimationForAnimation_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._AnimationExtender_CloseImplicitAnimationForAnimation(node)
    }
    static StartDoubleAnimation_serialize(node: KPointer, param: DoubleAnimationParam): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        DoubleAnimationParam_serializer.write(thisSerializer, param)
        ArkUIGeneratedNativeModule._AnimationExtender_StartDoubleAnimation(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static AnimationTranslate_serialize(node: KPointer, options: TranslateOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        TranslateOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._AnimationExtender_AnimationTranslate(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static AnimateToImmediatelyImpl_serialize(param: AnimateParam, event: (() => void), immediately: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        AnimateParam_serializer.write(thisSerializer, param)
        thisSerializer.holdAndWriteCallback(event)
        ArkUIGeneratedNativeModule._AnimationExtender_AnimateToImmediatelyImpl(thisSerializer.asBuffer(), thisSerializer.length(), immediately ? 1 : 0)
        thisSerializer.release()
    }
    static KeyframeAnimationImpl_serialize(param: KeyframeAnimateParam, keyfames: Array<KeyframeState>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        KeyframeAnimateParam_serializer.write(thisSerializer, param)
        thisSerializer.writeInt32((keyfames.length).toInt())
        for (let keyfamesCounterI = 0; keyfamesCounterI < keyfames.length; keyfamesCounterI++) {
            const keyfamesTmpElement : KeyframeState = keyfames[keyfamesCounterI]
            KeyframeState_serializer.write(thisSerializer, keyfamesTmpElement)
        }
        ArkUIGeneratedNativeModule._AnimationExtender_KeyframeAnimationImpl(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static SetClipRect(node: KPointer, x: float, y: float, width: float, height: float): void {
        const node_casted = node as (KPointer)
        const x_casted = x as (float)
        const y_casted = y as (float)
        const width_casted = width as (float)
        const height_casted = height as (float)
        AnimationExtender.SetClipRect_serialize(node_casted, x_casted, y_casted, width_casted, height_casted)
        return
    }
    public static OpenImplicitAnimation(param: AnimateParam): void {
        const param_casted = param as (AnimateParam)
        AnimationExtender.OpenImplicitAnimation_serialize(param_casted)
        return
    }
    public static CloseImplicitAnimation(): void {
        AnimationExtender.CloseImplicitAnimation_serialize()
        return
    }
    public static OpenImplicitAnimationForAnimation(node: KPointer, param: AnimateParam | undefined): void {
        const node_casted = node as (KPointer)
        const param_casted = param as (AnimateParam | undefined)
        AnimationExtender.OpenImplicitAnimationForAnimation_serialize(node_casted, param_casted)
        return
    }
    public static CloseImplicitAnimationForAnimation(node: KPointer): void {
        const node_casted = node as (KPointer)
        AnimationExtender.CloseImplicitAnimationForAnimation_serialize(node_casted)
        return
    }
    public static StartDoubleAnimation(node: KPointer, param: DoubleAnimationParam): void {
        const node_casted = node as (KPointer)
        const param_casted = param as (DoubleAnimationParam)
        AnimationExtender.StartDoubleAnimation_serialize(node_casted, param_casted)
        return
    }
    public static AnimationTranslate(node: KPointer, options: TranslateOptions): void {
        const node_casted = node as (KPointer)
        const options_casted = options as (TranslateOptions)
        AnimationExtender.AnimationTranslate_serialize(node_casted, options_casted)
        return
    }
    public static AnimateToImmediatelyImpl(param: AnimateParam, event: (() => void), immediately: boolean): void {
        const param_casted = param as (AnimateParam)
        const event_casted = event as ((() => void))
        const immediately_casted = immediately as (boolean)
        AnimationExtender.AnimateToImmediatelyImpl_serialize(param_casted, event_casted, immediately_casted)
        return
    }
    public static KeyframeAnimationImpl(param: KeyframeAnimateParam, keyfames: Array<KeyframeState>): void {
        const param_casted = param as (KeyframeAnimateParam)
        const keyfames_casted = keyfames as (Array<KeyframeState>)
        AnimationExtender.KeyframeAnimationImpl_serialize(param_casted, keyfames_casted)
        return
    }
}
export class ArcListExtender {
    static arcListConstructor_serialize(id: int32): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ArcListExtender_arcListConstructor(id)
        return retval
    }
    static setArkListOptions_serialize(node: KPointer, options?: ArkListOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            ArkListOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_setArkListOptions(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static digitalCrownSensitivity_serialize(node: KPointer, sensitivity?: CrownSensitivity): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (sensitivity !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const sensitivityTmpValue  = (sensitivity as CrownSensitivity)
            thisSerializer.writeInt32(sensitivityTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_digitalCrownSensitivity(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static space_serialize(node: KPointer, space?: LengthMetrics): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (space !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const spaceTmpValue  = space!
            LengthMetrics_serializer.write(thisSerializer, spaceTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_space(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static scrollBar_serialize(node: KPointer, status?: BarState): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (status !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const statusTmpValue  = (status as BarState)
            thisSerializer.writeInt32(statusTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_scrollBar(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static scrollBarColor_serialize(node: KPointer, color?: ColorMetrics): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (color !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const colorTmpValue  = color!
            ColorMetrics_serializer.write(thisSerializer, colorTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_scrollBarColor(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static scrollBarWidth_serialize(node: KPointer, width?: LengthMetrics): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (width !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const widthTmpValue  = width!
            LengthMetrics_serializer.write(thisSerializer, widthTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_scrollBarWidth(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static cachedCount_serialize(node: KPointer, count?: int32): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (count !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const countTmpValue  = count!
            thisSerializer.writeInt32(countTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_cachedCount(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static chainAnimation_serialize(node: KPointer, enable?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (enable !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const enableTmpValue  = enable!
            thisSerializer.writeBoolean(enableTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_chainAnimation(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static childrenMainSize_serialize(node: KPointer, size?: ChildrenMainSize): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (size !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const sizeTmpValue  = size!
            ChildrenMainSize_serializer.write(thisSerializer, sizeTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_childrenMainSize(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static enableScrollInteraction_serialize(node: KPointer, enable?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (enable !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const enableTmpValue  = enable!
            thisSerializer.writeBoolean(enableTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_enableScrollInteraction(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static fadingEdge_serialize(node: KPointer, enable?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (enable !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const enableTmpValue  = enable!
            thisSerializer.writeBoolean(enableTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_fadingEdge(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static friction_serialize(node: KPointer, friction?: double): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (friction !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const frictionTmpValue  = friction!
            thisSerializer.writeFloat64(frictionTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_friction(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static flingSpeedLimit_serialize(node: KPointer, speed?: double): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (speed !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const speedTmpValue  = speed!
            thisSerializer.writeFloat64(speedTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_flingSpeedLimit(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static onScrollIndex_serialize(node: KPointer, handler?: ArcScrollIndexHandler): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (handler !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const handlerTmpValue  = handler!
            thisSerializer.holdAndWriteCallback(handlerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_onScrollIndex(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static onReachStart_serialize(node: KPointer, handler?: VoidCallback): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (handler !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const handlerTmpValue  = handler!
            thisSerializer.holdAndWriteCallback(handlerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_onReachStart(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static onReachEnd_serialize(node: KPointer, handler?: VoidCallback): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (handler !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const handlerTmpValue  = handler!
            thisSerializer.holdAndWriteCallback(handlerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_onReachEnd(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static onScrollStart_serialize(node: KPointer, handler?: VoidCallback): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (handler !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const handlerTmpValue  = handler!
            thisSerializer.holdAndWriteCallback(handlerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_onScrollStart(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static onScrollStop_serialize(node: KPointer, handler?: VoidCallback): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (handler !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const handlerTmpValue  = handler!
            thisSerializer.holdAndWriteCallback(handlerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_onScrollStop(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static onWillScroll_serialize(node: KPointer, handler?: OnWillScrollCallback): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (handler !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const handlerTmpValue  = handler!
            thisSerializer.holdAndWriteCallback(handlerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_onWillScroll(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static onDidScroll_serialize(node: KPointer, handler?: OnScrollCallback): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (handler !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const handlerTmpValue  = handler!
            thisSerializer.holdAndWriteCallback(handlerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_onDidScroll(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static arcListConstructor(id: int32): KPointer {
        const id_casted = id as (int32)
        return ArcListExtender.arcListConstructor_serialize(id_casted)
    }
    public static setArkListOptions(node: KPointer, options?: ArkListOptions): void {
        const node_casted = node as (KPointer)
        const options_casted = options as (ArkListOptions | undefined)
        ArcListExtender.setArkListOptions_serialize(node_casted, options_casted)
        return
    }
    public static digitalCrownSensitivity(node: KPointer, sensitivity?: CrownSensitivity): void {
        const node_casted = node as (KPointer)
        const sensitivity_casted = sensitivity as (CrownSensitivity | undefined)
        ArcListExtender.digitalCrownSensitivity_serialize(node_casted, sensitivity_casted)
        return
    }
    public static space(node: KPointer, space?: LengthMetrics): void {
        const node_casted = node as (KPointer)
        const space_casted = space as (LengthMetrics | undefined)
        ArcListExtender.space_serialize(node_casted, space_casted)
        return
    }
    public static scrollBar(node: KPointer, status?: BarState): void {
        const node_casted = node as (KPointer)
        const status_casted = status as (BarState | undefined)
        ArcListExtender.scrollBar_serialize(node_casted, status_casted)
        return
    }
    public static scrollBarColor(node: KPointer, color?: ColorMetrics): void {
        const node_casted = node as (KPointer)
        const color_casted = color as (ColorMetrics | undefined)
        ArcListExtender.scrollBarColor_serialize(node_casted, color_casted)
        return
    }
    public static scrollBarWidth(node: KPointer, width?: LengthMetrics): void {
        const node_casted = node as (KPointer)
        const width_casted = width as (LengthMetrics | undefined)
        ArcListExtender.scrollBarWidth_serialize(node_casted, width_casted)
        return
    }
    public static cachedCount(node: KPointer, count?: int32): void {
        const node_casted = node as (KPointer)
        const count_casted = count as (int32 | undefined)
        ArcListExtender.cachedCount_serialize(node_casted, count_casted)
        return
    }
    public static chainAnimation(node: KPointer, enable?: boolean): void {
        const node_casted = node as (KPointer)
        const enable_casted = enable as (boolean | undefined)
        ArcListExtender.chainAnimation_serialize(node_casted, enable_casted)
        return
    }
    public static childrenMainSize(node: KPointer, size?: ChildrenMainSize): void {
        const node_casted = node as (KPointer)
        const size_casted = size as (ChildrenMainSize | undefined)
        ArcListExtender.childrenMainSize_serialize(node_casted, size_casted)
        return
    }
    public static enableScrollInteraction(node: KPointer, enable?: boolean): void {
        const node_casted = node as (KPointer)
        const enable_casted = enable as (boolean | undefined)
        ArcListExtender.enableScrollInteraction_serialize(node_casted, enable_casted)
        return
    }
    public static fadingEdge(node: KPointer, enable?: boolean): void {
        const node_casted = node as (KPointer)
        const enable_casted = enable as (boolean | undefined)
        ArcListExtender.fadingEdge_serialize(node_casted, enable_casted)
        return
    }
    public static friction(node: KPointer, friction?: double): void {
        const node_casted = node as (KPointer)
        const friction_casted = friction as (double | undefined)
        ArcListExtender.friction_serialize(node_casted, friction_casted)
        return
    }
    public static flingSpeedLimit(node: KPointer, speed?: double): void {
        const node_casted = node as (KPointer)
        const speed_casted = speed as (double | undefined)
        ArcListExtender.flingSpeedLimit_serialize(node_casted, speed_casted)
        return
    }
    public static onScrollIndex(node: KPointer, handler?: ArcScrollIndexHandler): void {
        const node_casted = node as (KPointer)
        const handler_casted = handler as (ArcScrollIndexHandler | undefined)
        ArcListExtender.onScrollIndex_serialize(node_casted, handler_casted)
        return
    }
    public static onReachStart(node: KPointer, handler?: VoidCallback): void {
        const node_casted = node as (KPointer)
        const handler_casted = handler as (VoidCallback | undefined)
        ArcListExtender.onReachStart_serialize(node_casted, handler_casted)
        return
    }
    public static onReachEnd(node: KPointer, handler?: VoidCallback): void {
        const node_casted = node as (KPointer)
        const handler_casted = handler as (VoidCallback | undefined)
        ArcListExtender.onReachEnd_serialize(node_casted, handler_casted)
        return
    }
    public static onScrollStart(node: KPointer, handler?: VoidCallback): void {
        const node_casted = node as (KPointer)
        const handler_casted = handler as (VoidCallback | undefined)
        ArcListExtender.onScrollStart_serialize(node_casted, handler_casted)
        return
    }
    public static onScrollStop(node: KPointer, handler?: VoidCallback): void {
        const node_casted = node as (KPointer)
        const handler_casted = handler as (VoidCallback | undefined)
        ArcListExtender.onScrollStop_serialize(node_casted, handler_casted)
        return
    }
    public static onWillScroll(node: KPointer, handler?: OnWillScrollCallback): void {
        const node_casted = node as (KPointer)
        const handler_casted = handler as (OnWillScrollCallback | undefined)
        ArcListExtender.onWillScroll_serialize(node_casted, handler_casted)
        return
    }
    public static onDidScroll(node: KPointer, handler?: OnScrollCallback): void {
        const node_casted = node as (KPointer)
        const handler_casted = handler as (OnScrollCallback | undefined)
        ArcListExtender.onDidScroll_serialize(node_casted, handler_casted)
        return
    }
}
export class ArcListItemExtender {
    static arcListItemConstructor_serialize(id: int32): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ArcListItemExtender_arcListItemConstructor(id)
        return retval
    }
    static autoScale_serialize(node: KPointer, enable?: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (enable !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const enableTmpValue  = enable!
            thisSerializer.writeBoolean(enableTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListItemExtender_autoScale(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static swipeAction_serialize(node: KPointer, options?: SwipeActionOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            SwipeActionOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListItemExtender_swipeAction(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static arcListItemConstructor(id: int32): KPointer {
        const id_casted = id as (int32)
        return ArcListItemExtender.arcListItemConstructor_serialize(id_casted)
    }
    public static autoScale(node: KPointer, enable?: boolean): void {
        const node_casted = node as (KPointer)
        const enable_casted = enable as (boolean | undefined)
        ArcListItemExtender.autoScale_serialize(node_casted, enable_casted)
        return
    }
    public static swipeAction(node: KPointer, options?: SwipeActionOptions): void {
        const node_casted = node as (KPointer)
        const options_casted = options as (SwipeActionOptions | undefined)
        ArcListItemExtender.swipeAction_serialize(node_casted, options_casted)
        return
    }
}
export class ArcScrollBarExtender {
    static arcScrollBarConstructor_serialize(id: int32): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ArcScrollBarExtender_arcScrollBarConstructor(id)
        return retval
    }
    static setArcScrollBarOptions_serialize(node: KPointer, options: ArcScrollBarOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        ArcScrollBarOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._ArcScrollBarExtender_setArcScrollBarOptions(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static arcScrollBarConstructor(id: int32): KPointer {
        const id_casted = id as (int32)
        return ArcScrollBarExtender.arcScrollBarConstructor_serialize(id_casted)
    }
    public static setArcScrollBarOptions(node: KPointer, options: ArcScrollBarOptions): void {
        const node_casted = node as (KPointer)
        const options_casted = options as (ArcScrollBarOptions)
        ArcScrollBarExtender.setArcScrollBarOptions_serialize(node_casted, options_casted)
        return
    }
}

export class BaseShapeInternal {
    public static fromPtr(ptr: KPointer): BaseShape {
        return new BaseShape(ptr)
    }
}
export class BaseShape implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, BaseShape.getFinalizer())
    }
    constructor() {
        this(BaseShape.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._BaseShape_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._BaseShape_getFinalizer()
    }
    public width(width: Length): BaseShape {
        const width_casted = width as (Length)
        return this.width_serialize(width_casted)
    }
    public height(height: Length): BaseShape {
        const height_casted = height as (Length)
        return this.height_serialize(height_casted)
    }
    public size(size: SizeOptions): BaseShape {
        const size_casted = size as (SizeOptions)
        return this.size_serialize(size_casted)
    }
    width_serialize(width: Length): BaseShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (width instanceof string) {
            thisSerializer.writeInt8((0).toByte())
            const widthForIdx0  = width as string
            thisSerializer.writeString(widthForIdx0)
        } else if (width instanceof number) {
            thisSerializer.writeInt8((1).toByte())
            const widthForIdx1  = width as number
            thisSerializer.writeNumber(widthForIdx1)
        } else if (width instanceof Resource) {
            thisSerializer.writeInt8((2).toByte())
            const widthForIdx2  = width as Resource
            Resource_serializer.write(thisSerializer, widthForIdx2)
        }
        const retval  = ArkUIGeneratedNativeModule._BaseShape_width(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : BaseShape = BaseShapeInternal.fromPtr(retval)
        return obj
    }
    height_serialize(height: Length): BaseShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (height instanceof string) {
            thisSerializer.writeInt8((0).toByte())
            const heightForIdx0  = height as string
            thisSerializer.writeString(heightForIdx0)
        } else if (height instanceof number) {
            thisSerializer.writeInt8((1).toByte())
            const heightForIdx1  = height as number
            thisSerializer.writeNumber(heightForIdx1)
        } else if (height instanceof Resource) {
            thisSerializer.writeInt8((2).toByte())
            const heightForIdx2  = height as Resource
            Resource_serializer.write(thisSerializer, heightForIdx2)
        }
        const retval  = ArkUIGeneratedNativeModule._BaseShape_height(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : BaseShape = BaseShapeInternal.fromPtr(retval)
        return obj
    }
    size_serialize(size: SizeOptions): BaseShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        SizeOptions_serializer.write(thisSerializer, size)
        const retval  = ArkUIGeneratedNativeModule._BaseShape_size(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : BaseShape = BaseShapeInternal.fromPtr(retval)
        return obj
    }
}
export class BuilderNodeOpsInternal {
    public static fromPtr(ptr: KPointer): BuilderNodeOps {
        return new BuilderNodeOps(ptr)
    }
}
export class BuilderNodeOps implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, BuilderNodeOps.getFinalizer())
    }
    constructor() {
        this(BuilderNodeOps.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._BuilderNodeOps_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._BuilderNodeOps_getFinalizer()
    }
    public create(buildFunc: (() => void)): void {
        const buildFunc_casted = buildFunc as ((() => void))
        this.create_serialize(buildFunc_casted)
        return
    }
    public disposeNode(): void {
        this.disposeNode_serialize()
        return
    }
    public setUpdateConfigurationCallback(configurationUpdateFunc: (() => void)): void {
        const configurationUpdateFunc_casted = configurationUpdateFunc as ((() => void))
        this.setUpdateConfigurationCallback_serialize(configurationUpdateFunc_casted)
        return
    }
    public setOptions(options: BuilderNodeOptions): void {
        const options_casted = options as (BuilderNodeOptions)
        this.setOptions_serialize(options_casted)
        return
    }
    public postTouchEvent(event: TouchEvent): boolean {
        const event_casted = event as (TouchEvent)
        return this.postTouchEvent_serialize(event_casted)
    }
    public setRootFrameNodeInBuilderNode(node: KPointer): KPointer {
        const node_casted = node as (KPointer)
        return this.setRootFrameNodeInBuilderNode_serialize(node_casted)
    }
    create_serialize(buildFunc: (() => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(buildFunc)
        ArkUIGeneratedNativeModule._BuilderNodeOps_create(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    disposeNode_serialize(): void {
        ArkUIGeneratedNativeModule._BuilderNodeOps_disposeNode(this.peer!.ptr)
    }
    setUpdateConfigurationCallback_serialize(configurationUpdateFunc: (() => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(configurationUpdateFunc)
        ArkUIGeneratedNativeModule._BuilderNodeOps_setUpdateConfigurationCallback(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOptions_serialize(options: BuilderNodeOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        BuilderNodeOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._BuilderNodeOps_setOptions(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    postTouchEvent_serialize(event: TouchEvent): boolean {
        const retval  = ArkUIGeneratedNativeModule._BuilderNodeOps_postTouchEvent(this.peer!.ptr, toPeerPtr(event))
        return retval
    }
    setRootFrameNodeInBuilderNode_serialize(node: KPointer): KPointer {
        const retval  = ArkUIGeneratedNativeModule._BuilderNodeOps_setRootFrameNodeInBuilderNode(this.peer!.ptr, node)
        return retval
    }
}
export class CommonShapeInternal {
    public static fromPtr(ptr: KPointer): CommonShape {
        return new CommonShape(ptr)
    }
}
export class CommonShape implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, CommonShape.getFinalizer())
    }
    constructor() {
        this(CommonShape.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._CommonShape_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CommonShape_getFinalizer()
    }
    public offset(offset: Position): CommonShape {
        const offset_casted = offset as (Position)
        return this.offset_serialize(offset_casted)
    }
    public fill(color: ResourceColor): CommonShape {
        const color_casted = color as (ResourceColor)
        return this.fill_serialize(color_casted)
    }
    public position(position: Position): CommonShape {
        const position_casted = position as (Position)
        return this.position_serialize(position_casted)
    }
    offset_serialize(offset: Position): CommonShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Position_serializer.write(thisSerializer, offset)
        const retval  = ArkUIGeneratedNativeModule._CommonShape_offset(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : CommonShape = CommonShapeInternal.fromPtr(retval)
        return obj
    }
    fill_serialize(color: ResourceColor): CommonShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (color instanceof Color) {
            thisSerializer.writeInt8((0).toByte())
            const colorForIdx0  = color as Color
            thisSerializer.writeInt32(colorForIdx0.getOrdinal())
        } else if (color instanceof number) {
            thisSerializer.writeInt8((1).toByte())
            const colorForIdx1  = color as number
            thisSerializer.writeNumber(colorForIdx1)
        } else if (color instanceof string) {
            thisSerializer.writeInt8((2).toByte())
            const colorForIdx2  = color as string
            thisSerializer.writeString(colorForIdx2)
        } else if (color instanceof Resource) {
            thisSerializer.writeInt8((3).toByte())
            const colorForIdx3  = color as Resource
            Resource_serializer.write(thisSerializer, colorForIdx3)
        }
        const retval  = ArkUIGeneratedNativeModule._CommonShape_fill(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : CommonShape = CommonShapeInternal.fromPtr(retval)
        return obj
    }
    position_serialize(position: Position): CommonShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Position_serializer.write(thisSerializer, position)
        const retval  = ArkUIGeneratedNativeModule._CommonShape_position(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : CommonShape = CommonShapeInternal.fromPtr(retval)
        return obj
    }
}
export class ContentModifierHelper {
    static contentModifierButton_serialize(node: KPointer, contentModifier: ContentModifier<ButtonConfiguration>, builder: ((parentNode: KPointer,config: ButtonConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierButton(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static resetContentModifierButton_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierButton(node)
    }
    static contentModifierCheckBox_serialize(node: KPointer, contentModifier: ContentModifier<CheckBoxConfiguration>, builder: ((parentNode: KPointer,config: CheckBoxConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierCheckBox(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static resetContentModifierCheckBox_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierCheckBox(node)
    }
    static contentModifierDataPanel_serialize(node: KPointer, contentModifier: ContentModifier<DataPanelConfiguration>, builder: ((parentNode: KPointer,config: DataPanelConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierDataPanel(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static resetContentModifierDataPanel_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierDataPanel(node)
    }
    static contentModifierGauge_serialize(node: KPointer, contentModifier: ContentModifier<GaugeConfiguration>, builder: ((parentNode: KPointer,config: GaugeConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierGauge(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static resetContentModifierGauge_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierGauge(node)
    }
    static contentModifierLoadingProgress_serialize(node: KPointer, contentModifier: ContentModifier<LoadingProgressConfiguration>, builder: ((parentNode: KPointer,config: LoadingProgressConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierLoadingProgress(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static resetContentModifierLoadingProgress_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierLoadingProgress(node)
    }
    static contentModifierProgress_serialize(node: KPointer, contentModifier: ContentModifier<ProgressConfiguration>, builder: ((parentNode: KPointer,config: ProgressConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierProgress(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static resetContentModifierProgress_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierProgress(node)
    }
    static contentModifierRadio_serialize(node: KPointer, contentModifier: ContentModifier<RadioConfiguration>, builder: ((parentNode: KPointer,config: RadioConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierRadio(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static resetContentModifierRadio_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierRadio(node)
    }
    static contentModifierRating_serialize(node: KPointer, contentModifier: ContentModifier<RatingConfiguration>, builder: ((parentNode: KPointer,config: RatingConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierRating(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static resetContentModifierRating_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierRating(node)
    }
    static contentModifierMenuItem_serialize(node: KPointer, contentModifier: ContentModifier<MenuItemConfiguration>, builder: ((parentNode: KPointer,config: MenuItemConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierMenuItem(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static resetContentModifierMenuItem_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierMenuItem(node)
    }
    static contentModifierSlider_serialize(node: KPointer, contentModifier: ContentModifier<SliderConfiguration>, builder: ((parentNode: KPointer,config: SliderConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierSlider(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static resetContentModifierSlider_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierSlider(node)
    }
    static contentModifierTextClock_serialize(node: KPointer, contentModifier: ContentModifier<TextClockConfiguration>, builder: ((parentNode: KPointer,config: TextClockConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierTextClock(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static resetContentModifierTextClock_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierTextClock(node)
    }
    static contentModifierTextTimer_serialize(node: KPointer, contentModifier: ContentModifier<TextTimerConfiguration>, builder: ((parentNode: KPointer,config: TextTimerConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierTextTimer(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static resetContentModifierTextTimer_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierTextTimer(node)
    }
    static contentModifierToggle_serialize(node: KPointer, contentModifier: ContentModifier<ToggleConfiguration>, builder: ((parentNode: KPointer,config: ToggleConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierToggle(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static resetContentModifierToggle_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierToggle(node)
    }
    public static contentModifierButton(node: KPointer, contentModifier: ContentModifier<ButtonConfiguration>, builder: ((parentNode: KPointer,config: ButtonConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<ButtonConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: ButtonConfiguration) => KPointer))
        ContentModifierHelper.contentModifierButton_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }
    public static resetContentModifierButton(node: KPointer): void {
        const node_casted = node as (KPointer)
        ContentModifierHelper.resetContentModifierButton_serialize(node_casted)
        return
    }
    public static contentModifierCheckBox(node: KPointer, contentModifier: ContentModifier<CheckBoxConfiguration>, builder: ((parentNode: KPointer,config: CheckBoxConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<CheckBoxConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: CheckBoxConfiguration) => KPointer))
        ContentModifierHelper.contentModifierCheckBox_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }
    public static resetContentModifierCheckBox(node: KPointer): void {
        const node_casted = node as (KPointer)
        ContentModifierHelper.resetContentModifierCheckBox_serialize(node_casted)
        return
    }
    public static contentModifierDataPanel(node: KPointer, contentModifier: ContentModifier<DataPanelConfiguration>, builder: ((parentNode: KPointer,config: DataPanelConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<DataPanelConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: DataPanelConfiguration) => KPointer))
        ContentModifierHelper.contentModifierDataPanel_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }
    public static resetContentModifierDataPanel(node: KPointer): void {
        const node_casted = node as (KPointer)
        ContentModifierHelper.resetContentModifierDataPanel_serialize(node_casted)
        return
    }
    public static contentModifierGauge(node: KPointer, contentModifier: ContentModifier<GaugeConfiguration>, builder: ((parentNode: KPointer,config: GaugeConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<GaugeConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: GaugeConfiguration) => KPointer))
        ContentModifierHelper.contentModifierGauge_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }
    public static resetContentModifierGauge(node: KPointer): void {
        const node_casted = node as (KPointer)
        ContentModifierHelper.resetContentModifierGauge_serialize(node_casted)
        return
    }
    public static contentModifierLoadingProgress(node: KPointer, contentModifier: ContentModifier<LoadingProgressConfiguration>, builder: ((parentNode: KPointer,config: LoadingProgressConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<LoadingProgressConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: LoadingProgressConfiguration) => KPointer))
        ContentModifierHelper.contentModifierLoadingProgress_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }
    public static resetContentModifierLoadingProgress(node: KPointer): void {
        const node_casted = node as (KPointer)
        ContentModifierHelper.resetContentModifierLoadingProgress_serialize(node_casted)
        return
    }
    public static contentModifierProgress(node: KPointer, contentModifier: ContentModifier<ProgressConfiguration>, builder: ((parentNode: KPointer,config: ProgressConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<ProgressConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: ProgressConfiguration) => KPointer))
        ContentModifierHelper.contentModifierProgress_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }
    public static resetContentModifierProgress(node: KPointer): void {
        const node_casted = node as (KPointer)
        ContentModifierHelper.resetContentModifierProgress_serialize(node_casted)
        return
    }
    public static contentModifierRadio(node: KPointer, contentModifier: ContentModifier<RadioConfiguration>, builder: ((parentNode: KPointer,config: RadioConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<RadioConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: RadioConfiguration) => KPointer))
        ContentModifierHelper.contentModifierRadio_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }
    public static resetContentModifierRadio(node: KPointer): void {
        const node_casted = node as (KPointer)
        ContentModifierHelper.resetContentModifierRadio_serialize(node_casted)
        return
    }
    public static contentModifierRating(node: KPointer, contentModifier: ContentModifier<RatingConfiguration>, builder: ((parentNode: KPointer,config: RatingConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<RatingConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: RatingConfiguration) => KPointer))
        ContentModifierHelper.contentModifierRating_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }
    public static resetContentModifierRating(node: KPointer): void {
        const node_casted = node as (KPointer)
        ContentModifierHelper.resetContentModifierRating_serialize(node_casted)
        return
    }
    public static contentModifierMenuItem(node: KPointer, contentModifier: ContentModifier<MenuItemConfiguration>, builder: ((parentNode: KPointer,config: MenuItemConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<MenuItemConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: MenuItemConfiguration) => KPointer))
        ContentModifierHelper.contentModifierMenuItem_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }
    public static resetContentModifierMenuItem(node: KPointer): void {
        const node_casted = node as (KPointer)
        ContentModifierHelper.resetContentModifierMenuItem_serialize(node_casted)
        return
    }
    public static contentModifierSlider(node: KPointer, contentModifier: ContentModifier<SliderConfiguration>, builder: ((parentNode: KPointer,config: SliderConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<SliderConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: SliderConfiguration) => KPointer))
        ContentModifierHelper.contentModifierSlider_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }
    public static resetContentModifierSlider(node: KPointer): void {
        const node_casted = node as (KPointer)
        ContentModifierHelper.resetContentModifierSlider_serialize(node_casted)
        return
    }
    public static contentModifierTextClock(node: KPointer, contentModifier: ContentModifier<TextClockConfiguration>, builder: ((parentNode: KPointer,config: TextClockConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<TextClockConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: TextClockConfiguration) => KPointer))
        ContentModifierHelper.contentModifierTextClock_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }
    public static resetContentModifierTextClock(node: KPointer): void {
        const node_casted = node as (KPointer)
        ContentModifierHelper.resetContentModifierTextClock_serialize(node_casted)
        return
    }
    public static contentModifierTextTimer(node: KPointer, contentModifier: ContentModifier<TextTimerConfiguration>, builder: ((parentNode: KPointer,config: TextTimerConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<TextTimerConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: TextTimerConfiguration) => KPointer))
        ContentModifierHelper.contentModifierTextTimer_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }
    public static resetContentModifierTextTimer(node: KPointer): void {
        const node_casted = node as (KPointer)
        ContentModifierHelper.resetContentModifierTextTimer_serialize(node_casted)
        return
    }
    public static contentModifierToggle(node: KPointer, contentModifier: ContentModifier<ToggleConfiguration>, builder: ((parentNode: KPointer,config: ToggleConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<ToggleConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: ToggleConfiguration) => KPointer))
        ContentModifierHelper.contentModifierToggle_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }
    public static resetContentModifierToggle(node: KPointer): void {
        const node_casted = node as (KPointer)
        ContentModifierHelper.resetContentModifierToggle_serialize(node_casted)
        return
    }
}
export class CustomDialogControllerExtenderInternal {
    public static fromPtr(ptr: KPointer): CustomDialogControllerExtender {
        return new CustomDialogControllerExtender(false, ptr)
    }
}
export class CustomDialogControllerExtender implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, CustomDialogControllerExtender.getFinalizer())
    }
    constructor(value: CustomDialogControllerOptionsExtender) {
        this(false, CustomDialogControllerExtender.construct(value))
    }
    static construct(value: CustomDialogControllerOptionsExtender): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        CustomDialogControllerOptionsExtender_serializer.write(thisSerializer, value)
        const retval  = ArkUIGeneratedNativeModule._CustomDialogControllerExtender_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CustomDialogControllerExtender_getFinalizer()
    }
    public open(): void {
        this.open_serialize()
        return
    }
    public close(): void {
        this.close_serialize()
        return
    }
    public setOwnerView(content: KPointer): void {
        const content_casted = content as (KPointer)
        this.setOwnerView_serialize(content_casted)
        return
    }
    public getExternalOptions(): CustomDialogControllerExternalOptionsExtender {
        return this.getExternalOptions_serialize()
    }
    open_serialize(): void {
        ArkUIGeneratedNativeModule._CustomDialogControllerExtender_open(this.peer!.ptr)
    }
    close_serialize(): void {
        ArkUIGeneratedNativeModule._CustomDialogControllerExtender_close(this.peer!.ptr)
    }
    setOwnerView_serialize(content: KPointer): void {
        ArkUIGeneratedNativeModule._CustomDialogControllerExtender_setOwnerView(this.peer!.ptr, content)
    }
    getExternalOptions_serialize(): CustomDialogControllerExternalOptionsExtender {
        const retval  = ArkUIGeneratedNativeModule._CustomDialogControllerExtender_getExternalOptions(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : CustomDialogControllerExternalOptionsExtender = CustomDialogControllerExternalOptionsExtender_serializer.read(retvalDeserializer)
        return returnResult
    }
}
export class EventEmulator {
    static emitClickEvent_serialize(node: KPointer, event: ClickEvent): void {
        ArkUIGeneratedNativeModule._EventEmulator_emitClickEvent(node, toPeerPtr(event))
    }
    static emitTextInputEvent_serialize(node: KPointer, text: string): void {
        ArkUIGeneratedNativeModule._EventEmulator_emitTextInputEvent(node, text)
    }
    public static emitClickEvent(node: KPointer, event: ClickEvent): void {
        const node_casted = node as (KPointer)
        const event_casted = event as (ClickEvent)
        EventEmulator.emitClickEvent_serialize(node_casted, event_casted)
        return
    }
    public static emitTextInputEvent(node: KPointer, text: string): void {
        const node_casted = node as (KPointer)
        const text_casted = text as (string)
        EventEmulator.emitTextInputEvent_serialize(node_casted, text_casted)
        return
    }
}
export class FocusController {
    static requestFocus_serialize(key: string): void {
        ArkUIGeneratedNativeModule._FocusController_requestFocus(key)
    }
    public static requestFocus(key: string): void {
        const key_casted = key as (string)
        FocusController.requestFocus_serialize(key_casted)
        return
    }
}
export class ForEachOps {
    static SyncOnMoveOps_serialize(node: KPointer, additionalChild: Array<KPointer>, onMoveOps: OnMoveHandler | undefined, onMoveDragEventOps: ItemDragEventHandler | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((additionalChild.length).toInt())
        for (let additionalChildCounterI = 0; additionalChildCounterI < additionalChild.length; additionalChildCounterI++) {
            const additionalChildTmpElement : KPointer = additionalChild[additionalChildCounterI]
            thisSerializer.writePointer(additionalChildTmpElement)
        }
        if (onMoveOps !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const onMoveOpsTmpValue  = onMoveOps!
            thisSerializer.holdAndWriteCallback(onMoveOpsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (onMoveDragEventOps !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const onMoveDragEventOpsTmpValue  = onMoveDragEventOps!
            ItemDragEventHandler_serializer.write(thisSerializer, onMoveDragEventOpsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ForEachOps_SyncOnMoveOps(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static SyncOnMoveOps(node: KPointer, additionalChild: Array<KPointer>, onMoveOps: OnMoveHandler | undefined, onMoveDragEventOps: ItemDragEventHandler | undefined): void {
        const node_casted = node as (KPointer)
        const additionalChild_casted = additionalChild as (Array<KPointer>)
        const onMoveOps_casted = onMoveOps as (OnMoveHandler | undefined)
        const onMoveDragEventOps_casted = onMoveDragEventOps as (ItemDragEventHandler | undefined)
        ForEachOps.SyncOnMoveOps_serialize(node_casted, additionalChild_casted, onMoveOps_casted, onMoveDragEventOps_casted)
        return
    }
}
export class FrameNodeExtender {
    static constructorFrameNode_serialize(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_constructorFrameNode()
        return retval
    }
    static getDestroy_serialize(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getDestroy()
        return retval
    }
    static destroyPeer_serialize(peer: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNodeExtender_destroyPeer(extractors.toFrameNodePtr(peer))
    }
    static isModifiable_serialize(peer: KPointer): boolean {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_isModifiable(peer)
        return retval
    }
    static appendChild_serialize(peer: FrameNode, child: FrameNode): int32 {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_appendChild(extractors.toFrameNodePtr(peer), extractors.toFrameNodePtr(child))
        return retval
    }
    static insertChildAfter_serialize(peer: KPointer, child: KPointer, sibling: KPointer): int32 {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_insertChildAfter(peer, child, sibling)
        return retval
    }
    static removeChild_serialize(peer: FrameNode, child: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNodeExtender_removeChild(extractors.toFrameNodePtr(peer), extractors.toFrameNodePtr(child))
    }
    static clearChildren_serialize(peer: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNodeExtender_clearChildren(extractors.toFrameNodePtr(peer))
    }
    static getChild_serialize(peer: FrameNode, index: number, expandMode: number): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getChild(extractors.toFrameNodePtr(peer), index, expandMode)
        return retval
    }
    static getFirstChild_serialize(peer: FrameNode): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getFirstChild(extractors.toFrameNodePtr(peer))
        return retval
    }
    static getNextSibling_serialize(peer: FrameNode): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getNextSibling(extractors.toFrameNodePtr(peer))
        return retval
    }
    static getPreviousSibling_serialize(peer: FrameNode): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getPreviousSibling(extractors.toFrameNodePtr(peer))
        return retval
    }
    static getParent_serialize(peer: FrameNode): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getParent(extractors.toFrameNodePtr(peer))
        return retval
    }
    static getChildrenCount_serialize(peer: FrameNode): int32 {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getChildrenCount(extractors.toFrameNodePtr(peer))
        return retval
    }
    static dispose_serialize(peer: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNodeExtender_dispose(extractors.toFrameNodePtr(peer))
    }
    static getPositionToWindow_serialize(peer: FrameNode): Vector2 {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getPositionToWindow(extractors.toFrameNodePtr(peer))
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Vector2 = Vector2_serializer.read(retvalDeserializer)
        return returnResult
    }
    static getPositionToParent_serialize(peer: FrameNode): Vector2 {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getPositionToParent(extractors.toFrameNodePtr(peer))
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Vector2 = Vector2_serializer.read(retvalDeserializer)
        return returnResult
    }
    static getMeasuredSize_serialize(peer: FrameNode): Size {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getMeasuredSize(extractors.toFrameNodePtr(peer))
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Size = Size_serializer.read(retvalDeserializer)
        return returnResult
    }
    static getLayoutPosition_serialize(peer: FrameNode): Vector2 {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getLayoutPosition(extractors.toFrameNodePtr(peer))
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Vector2 = Vector2_serializer.read(retvalDeserializer)
        return returnResult
    }
    static getId_serialize(peer: FrameNode): string {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getId(extractors.toFrameNodePtr(peer))
        return retval
    }
    static getUniqueId_serialize(peer: FrameNode): number {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getUniqueId(extractors.toFrameNodePtr(peer))
        return retval
    }
    static getNodeType_serialize(peer: FrameNode): string {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getNodeType(extractors.toFrameNodePtr(peer))
        return retval
    }
    static getOpacity_serialize(peer: FrameNode): number {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getOpacity(extractors.toFrameNodePtr(peer))
        return retval
    }
    static isVisible_serialize(peer: FrameNode): boolean {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_isVisible(extractors.toFrameNodePtr(peer))
        return retval
    }
    static isClipToFrame_serialize(peer: FrameNode): boolean {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_isClipToFrame(extractors.toFrameNodePtr(peer))
        return retval
    }
    static isAttached_serialize(peer: FrameNode): boolean {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_isAttached(extractors.toFrameNodePtr(peer))
        return retval
    }
    static getInspectorInfo_serialize(peer: FrameNode): string {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getInspectorInfo(extractors.toFrameNodePtr(peer))
        return retval
    }
    static invalidate_serialize(peer: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNodeExtender_invalidate(extractors.toFrameNodePtr(peer))
    }
    static disposeTree_serialize(peer: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNodeExtender_disposeTree(extractors.toFrameNodePtr(peer))
    }
    static setCrossLanguageOptions_serialize(peer: FrameNode, options: boolean): boolean {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_setCrossLanguageOptions(extractors.toFrameNodePtr(peer), options ? 1 : 0)
        return retval
    }
    static getCrossLanguageOptions_serialize(peer: FrameNode): boolean {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getCrossLanguageOptions(extractors.toFrameNodePtr(peer))
        return retval
    }
    static setMeasuredSize_serialize(peer: FrameNode, size: Size): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Size_serializer.write(thisSerializer, size)
        ArkUIGeneratedNativeModule._FrameNodeExtender_setMeasuredSize(extractors.toFrameNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static setLayoutPosition_serialize(peer: FrameNode, position: Vector2): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Vector2_serializer.write(thisSerializer, position)
        ArkUIGeneratedNativeModule._FrameNodeExtender_setLayoutPosition(extractors.toFrameNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static measure_serialize(peer: FrameNode, constraint: LayoutConstraint): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        LayoutConstraint_serializer.write(thisSerializer, constraint)
        ArkUIGeneratedNativeModule._FrameNodeExtender_measure(extractors.toFrameNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static layout_serialize(peer: FrameNode, position: Vector2): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Vector2_serializer.write(thisSerializer, position)
        ArkUIGeneratedNativeModule._FrameNodeExtender_layout(extractors.toFrameNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static setNeedsLayout_serialize(peer: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNodeExtender_setNeedsLayout(extractors.toFrameNodePtr(peer))
    }
    static getPositionToScreen_serialize(peer: FrameNode): Vector2 {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getPositionToScreen(extractors.toFrameNodePtr(peer))
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Vector2 = Vector2_serializer.read(retvalDeserializer)
        return returnResult
    }
    static getPositionToWindowWithTransform_serialize(peer: FrameNode): Vector2 {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getPositionToWindowWithTransform(extractors.toFrameNodePtr(peer))
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Vector2 = Vector2_serializer.read(retvalDeserializer)
        return returnResult
    }
    static getPositionToParentWithTransform_serialize(peer: FrameNode): Vector2 {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getPositionToParentWithTransform(extractors.toFrameNodePtr(peer))
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Vector2 = Vector2_serializer.read(retvalDeserializer)
        return returnResult
    }
    static getPositionToScreenWithTransform_serialize(peer: FrameNode): Vector2 {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getPositionToScreenWithTransform(extractors.toFrameNodePtr(peer))
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Vector2 = Vector2_serializer.read(retvalDeserializer)
        return returnResult
    }
    static getUserConfigBorderWidth_serialize(peer: FrameNode): NodeEdgesLengthMetrics {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getUserConfigBorderWidth(extractors.toFrameNodePtr(peer))
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : NodeEdgesLengthMetrics = NodeEdgesLengthMetrics_serializer.read(retvalDeserializer)
        return returnResult
    }
    static getUserConfigPadding_serialize(peer: FrameNode): NodeEdgesLengthMetrics {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getUserConfigPadding(extractors.toFrameNodePtr(peer))
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : NodeEdgesLengthMetrics = NodeEdgesLengthMetrics_serializer.read(retvalDeserializer)
        return returnResult
    }
    static getUserConfigMargin_serialize(peer: FrameNode): NodeEdgesLengthMetrics {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getUserConfigMargin(extractors.toFrameNodePtr(peer))
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : NodeEdgesLengthMetrics = NodeEdgesLengthMetrics_serializer.read(retvalDeserializer)
        return returnResult
    }
    static getUserConfigSize_serialize(peer: FrameNode): SizeTLengthMetrics {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getUserConfigSize(extractors.toFrameNodePtr(peer))
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : SizeTLengthMetrics = SizeTLengthMetrics_serializer.read(retvalDeserializer)
        return returnResult
    }
    static getFrameNodeByKey_serialize(name: string): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getFrameNodeByKey(name)
        return retval
    }
    static getIdByFrameNode_serialize(node: KPointer): number {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getIdByFrameNode(node)
        return retval
    }
    static moveTo_serialize(peer: FrameNode, targetParent: FrameNode, index: number): int32 {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_moveTo(extractors.toFrameNodePtr(peer), extractors.toFrameNodePtr(targetParent), index)
        return retval
    }
    static getFirstChildIndexWithoutExpand_serialize(peer: FrameNode): number {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getFirstChildIndexWithoutExpand(extractors.toFrameNodePtr(peer))
        return retval
    }
    static getLastChildIndexWithoutExpand_serialize(peer: FrameNode): number {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getLastChildIndexWithoutExpand(extractors.toFrameNodePtr(peer))
        return retval
    }
    static getAttachedFrameNodeById_serialize(id: string): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getAttachedFrameNodeById(id)
        return retval
    }
    static getFrameNodeById_serialize(id: number): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getFrameNodeById(id)
        return retval
    }
    static getFrameNodeByUniqueId_serialize(id: number): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getFrameNodeByUniqueId(id)
        return retval
    }
    static reuse_serialize(peer: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNodeExtender_reuse(extractors.toFrameNodePtr(peer))
    }
    static recycle_serialize(peer: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNodeExtender_recycle(extractors.toFrameNodePtr(peer))
    }
    static createAnimation_serialize(peer: FrameNode, property: AnimationPropertyType, startValue: Array<double> | undefined, endValue: Array<double>, param: AnimateParam): boolean {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (startValue !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const startValueTmpValue  = startValue!
            thisSerializer.writeInt32((startValueTmpValue.length).toInt())
            for (let startValueTmpValueCounterI = 0; startValueTmpValueCounterI < startValueTmpValue.length; startValueTmpValueCounterI++) {
                const startValueTmpValueTmpElement : double = startValueTmpValue[startValueTmpValueCounterI]
                thisSerializer.writeFloat64(startValueTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        thisSerializer.writeInt32((endValue.length).toInt())
        for (let endValueCounterI = 0; endValueCounterI < endValue.length; endValueCounterI++) {
            const endValueTmpElement : double = endValue[endValueCounterI]
            thisSerializer.writeFloat64(endValueTmpElement)
        }
        AnimateParam_serializer.write(thisSerializer, param)
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_createAnimation(extractors.toFrameNodePtr(peer), property.valueOf(), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static cancelAnimations_serialize(peer: FrameNode, properties: Array<AnimationPropertyType>): boolean {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((properties.length).toInt())
        for (let propertiesCounterI = 0; propertiesCounterI < properties.length; propertiesCounterI++) {
            const propertiesTmpElement : AnimationPropertyType = properties[propertiesCounterI]
            thisSerializer.writeInt32(propertiesTmpElement.valueOf())
        }
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_cancelAnimations(extractors.toFrameNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getNodePropertyValue_serialize(peer: FrameNode, property: AnimationPropertyType): Array<double> {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getNodePropertyValue(extractors.toFrameNodePtr(peer), property.valueOf())
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength : int32 = retvalDeserializer.readInt32()
        let buffer : Array<double> = new Array<double>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = retvalDeserializer.readFloat64()
        }
        const returnResult : Array<double> = buffer
        return returnResult
    }
    static getFrameNodePtr_serialize(node: FrameNode): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getFrameNodePtr(extractors.toFrameNodePtr(node))
        return retval
    }
    static createTypedFrameNode_serialize(type: string): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_createTypedFrameNode(type)
        return retval
    }
    static createByRawPtr_serialize(ptr: KPointer): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_createByRawPtr(ptr)
        return retval
    }
    static unWrapRawPtr_serialize(ptr: KPointer): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_unWrapRawPtr(ptr)
        return retval
    }
    static getCommonEvent_serialize(peer: FrameNode): UICommonEvent {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getCommonEvent(extractors.toFrameNodePtr(peer))
        const obj : UICommonEvent = UICommonEventInternal.fromPtr(retval)
        return obj
    }
    static getRenderNode_serialize(peer: KPointer): KPointer {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_getRenderNode(peer)
        return retval
    }
    static convertPoint_serialize(peer: FrameNode, node: FrameNode, vector2: Vector2): Array<double> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Vector2_serializer.write(thisSerializer, vector2)
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_convertPoint(extractors.toFrameNodePtr(peer), extractors.toFrameNodePtr(node), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength : int32 = retvalDeserializer.readInt32()
        let buffer : Array<double> = new Array<double>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = retvalDeserializer.readFloat64()
        }
        const returnResult : Array<double> = buffer
        return returnResult
    }
    static adoptChild_serialize(peer: FrameNode, child: FrameNode): int32 {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_adoptChild(extractors.toFrameNodePtr(peer), extractors.toFrameNodePtr(child))
        return retval
    }
    static isOnRenderTree_serialize(peer: FrameNode): boolean {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_isOnRenderTree(extractors.toFrameNodePtr(peer))
        return retval
    }
    static removeAdoptedChild_serialize(peer: FrameNode, child: FrameNode): int32 {
        const retval  = ArkUIGeneratedNativeModule._FrameNodeExtender_removeAdoptedChild(extractors.toFrameNodePtr(peer), extractors.toFrameNodePtr(child))
        return retval
    }
    public static constructorFrameNode(): KPointer {
        return FrameNodeExtender.constructorFrameNode_serialize()
    }
    public static getDestroy(): KPointer {
        return FrameNodeExtender.getDestroy_serialize()
    }
    public static destroyPeer(peer: FrameNode): void {
        const peer_casted = peer as (FrameNode)
        FrameNodeExtender.destroyPeer_serialize(peer_casted)
        return
    }
    public static isModifiable(peer: KPointer): boolean {
        const peer_casted = peer as (KPointer)
        return FrameNodeExtender.isModifiable_serialize(peer_casted)
    }
    public static appendChild(peer: FrameNode, child: FrameNode): int32 {
        const peer_casted = peer as (FrameNode)
        const child_casted = child as (FrameNode)
        return FrameNodeExtender.appendChild_serialize(peer_casted, child_casted)
    }
    public static insertChildAfter(peer: KPointer, child: KPointer, sibling: KPointer): int32 {
        const peer_casted = peer as (KPointer)
        const child_casted = child as (KPointer)
        const sibling_casted = sibling as (KPointer)
        return FrameNodeExtender.insertChildAfter_serialize(peer_casted, child_casted, sibling_casted)
    }
    public static removeChild(peer: FrameNode, child: FrameNode): void {
        const peer_casted = peer as (FrameNode)
        const child_casted = child as (FrameNode)
        FrameNodeExtender.removeChild_serialize(peer_casted, child_casted)
        return
    }
    public static clearChildren(peer: FrameNode): void {
        const peer_casted = peer as (FrameNode)
        FrameNodeExtender.clearChildren_serialize(peer_casted)
        return
    }
    public static getChild(peer: FrameNode, index: number, expandMode: number): KPointer {
        const peer_casted = peer as (FrameNode)
        const index_casted = index as (number)
        const expandMode_casted = expandMode as (number)
        return FrameNodeExtender.getChild_serialize(peer_casted, index_casted, expandMode_casted)
    }
    public static getFirstChild(peer: FrameNode): KPointer {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getFirstChild_serialize(peer_casted)
    }
    public static getNextSibling(peer: FrameNode): KPointer {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getNextSibling_serialize(peer_casted)
    }
    public static getPreviousSibling(peer: FrameNode): KPointer {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getPreviousSibling_serialize(peer_casted)
    }
    public static getParent(peer: FrameNode): KPointer {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getParent_serialize(peer_casted)
    }
    public static getChildrenCount(peer: FrameNode): int32 {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getChildrenCount_serialize(peer_casted)
    }
    public static dispose(peer: FrameNode): void {
        const peer_casted = peer as (FrameNode)
        FrameNodeExtender.dispose_serialize(peer_casted)
        return
    }
    public static getPositionToWindow(peer: FrameNode): Vector2 {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getPositionToWindow_serialize(peer_casted)
    }
    public static getPositionToParent(peer: FrameNode): Vector2 {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getPositionToParent_serialize(peer_casted)
    }
    public static getMeasuredSize(peer: FrameNode): Size {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getMeasuredSize_serialize(peer_casted)
    }
    public static getLayoutPosition(peer: FrameNode): Vector2 {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getLayoutPosition_serialize(peer_casted)
    }
    public static getId(peer: FrameNode): string {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getId_serialize(peer_casted)
    }
    public static getUniqueId(peer: FrameNode): number {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getUniqueId_serialize(peer_casted)
    }
    public static getNodeType(peer: FrameNode): string {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getNodeType_serialize(peer_casted)
    }
    public static getOpacity(peer: FrameNode): number {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getOpacity_serialize(peer_casted)
    }
    public static isVisible(peer: FrameNode): boolean {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.isVisible_serialize(peer_casted)
    }
    public static isClipToFrame(peer: FrameNode): boolean {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.isClipToFrame_serialize(peer_casted)
    }
    public static isAttached(peer: FrameNode): boolean {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.isAttached_serialize(peer_casted)
    }
    public static getInspectorInfo(peer: FrameNode): string {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getInspectorInfo_serialize(peer_casted)
    }
    public static invalidate(peer: FrameNode): void {
        const peer_casted = peer as (FrameNode)
        FrameNodeExtender.invalidate_serialize(peer_casted)
        return
    }
    public static disposeTree(peer: FrameNode): void {
        const peer_casted = peer as (FrameNode)
        FrameNodeExtender.disposeTree_serialize(peer_casted)
        return
    }
    public static setCrossLanguageOptions(peer: FrameNode, options: boolean): boolean {
        const peer_casted = peer as (FrameNode)
        const options_casted = options as (boolean)
        return FrameNodeExtender.setCrossLanguageOptions_serialize(peer_casted, options_casted)
    }
    public static getCrossLanguageOptions(peer: FrameNode): boolean {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getCrossLanguageOptions_serialize(peer_casted)
    }
    public static setMeasuredSize(peer: FrameNode, size: Size): void {
        const peer_casted = peer as (FrameNode)
        const size_casted = size as (Size)
        FrameNodeExtender.setMeasuredSize_serialize(peer_casted, size_casted)
        return
    }
    public static setLayoutPosition(peer: FrameNode, position: Vector2): void {
        const peer_casted = peer as (FrameNode)
        const position_casted = position as (Vector2)
        FrameNodeExtender.setLayoutPosition_serialize(peer_casted, position_casted)
        return
    }
    public static measure(peer: FrameNode, constraint: LayoutConstraint): void {
        const peer_casted = peer as (FrameNode)
        const constraint_casted = constraint as (LayoutConstraint)
        FrameNodeExtender.measure_serialize(peer_casted, constraint_casted)
        return
    }
    public static layout(peer: FrameNode, position: Vector2): void {
        const peer_casted = peer as (FrameNode)
        const position_casted = position as (Vector2)
        FrameNodeExtender.layout_serialize(peer_casted, position_casted)
        return
    }
    public static setNeedsLayout(peer: FrameNode): void {
        const peer_casted = peer as (FrameNode)
        FrameNodeExtender.setNeedsLayout_serialize(peer_casted)
        return
    }
    public static getPositionToScreen(peer: FrameNode): Vector2 {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getPositionToScreen_serialize(peer_casted)
    }
    public static getPositionToWindowWithTransform(peer: FrameNode): Vector2 {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getPositionToWindowWithTransform_serialize(peer_casted)
    }
    public static getPositionToParentWithTransform(peer: FrameNode): Vector2 {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getPositionToParentWithTransform_serialize(peer_casted)
    }
    public static getPositionToScreenWithTransform(peer: FrameNode): Vector2 {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getPositionToScreenWithTransform_serialize(peer_casted)
    }
    public static getUserConfigBorderWidth(peer: FrameNode): NodeEdgesLengthMetrics {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getUserConfigBorderWidth_serialize(peer_casted)
    }
    public static getUserConfigPadding(peer: FrameNode): NodeEdgesLengthMetrics {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getUserConfigPadding_serialize(peer_casted)
    }
    public static getUserConfigMargin(peer: FrameNode): NodeEdgesLengthMetrics {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getUserConfigMargin_serialize(peer_casted)
    }
    public static getUserConfigSize(peer: FrameNode): SizeTLengthMetrics {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getUserConfigSize_serialize(peer_casted)
    }
    public static getFrameNodeByKey(name: string): KPointer {
        const name_casted = name as (string)
        return FrameNodeExtender.getFrameNodeByKey_serialize(name_casted)
    }
    public static getIdByFrameNode(node: KPointer): number {
        const node_casted = node as (KPointer)
        return FrameNodeExtender.getIdByFrameNode_serialize(node_casted)
    }
    public static moveTo(peer: FrameNode, targetParent: FrameNode, index: number): int32 {
        const peer_casted = peer as (FrameNode)
        const targetParent_casted = targetParent as (FrameNode)
        const index_casted = index as (number)
        return FrameNodeExtender.moveTo_serialize(peer_casted, targetParent_casted, index_casted)
    }
    public static getFirstChildIndexWithoutExpand(peer: FrameNode): number {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getFirstChildIndexWithoutExpand_serialize(peer_casted)
    }
    public static getLastChildIndexWithoutExpand(peer: FrameNode): number {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getLastChildIndexWithoutExpand_serialize(peer_casted)
    }
    public static getAttachedFrameNodeById(id: string): KPointer {
        const id_casted = id as (string)
        return FrameNodeExtender.getAttachedFrameNodeById_serialize(id_casted)
    }
    public static getFrameNodeById(id: number): KPointer {
        const id_casted = id as (number)
        return FrameNodeExtender.getFrameNodeById_serialize(id_casted)
    }
    public static getFrameNodeByUniqueId(id: number): KPointer {
        const id_casted = id as (number)
        return FrameNodeExtender.getFrameNodeByUniqueId_serialize(id_casted)
    }
    public static reuse(peer: FrameNode): void {
        const peer_casted = peer as (FrameNode)
        FrameNodeExtender.reuse_serialize(peer_casted)
        return
    }
    public static recycle(peer: FrameNode): void {
        const peer_casted = peer as (FrameNode)
        FrameNodeExtender.recycle_serialize(peer_casted)
        return
    }
    public static createAnimation(peer: FrameNode, property: AnimationPropertyType, startValue: Array<double> | undefined, endValue: Array<double>, param: AnimateParam): boolean {
        const peer_casted = peer as (FrameNode)
        const property_casted = property as (AnimationPropertyType)
        const startValue_casted = startValue as (Array<double> | undefined)
        const endValue_casted = endValue as (Array<double>)
        const param_casted = param as (AnimateParam)
        return FrameNodeExtender.createAnimation_serialize(peer_casted, property_casted, startValue_casted, endValue_casted, param_casted)
    }
    public static cancelAnimations(peer: FrameNode, properties: Array<AnimationPropertyType>): boolean {
        const peer_casted = peer as (FrameNode)
        const properties_casted = properties as (Array<AnimationPropertyType>)
        return FrameNodeExtender.cancelAnimations_serialize(peer_casted, properties_casted)
    }
    public static getNodePropertyValue(peer: FrameNode, property: AnimationPropertyType): Array<double> {
        const peer_casted = peer as (FrameNode)
        const property_casted = property as (AnimationPropertyType)
        return FrameNodeExtender.getNodePropertyValue_serialize(peer_casted, property_casted)
    }
    public static getFrameNodePtr(node: FrameNode): KPointer {
        const node_casted = node as (FrameNode)
        return FrameNodeExtender.getFrameNodePtr_serialize(node_casted)
    }
    public static createTypedFrameNode(type: string): KPointer {
        const type_casted = type as (string)
        return FrameNodeExtender.createTypedFrameNode_serialize(type_casted)
    }
    public static createByRawPtr(ptr: KPointer): KPointer {
        return FrameNodeExtender.createByRawPtr_serialize(ptr)
    }
    public static unWrapRawPtr(pointer: KPointer): KPointer {
        return FrameNodeExtender.unWrapRawPtr_serialize(pointer)
    }
    public static getCommonEvent(peer: FrameNode): UICommonEvent {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getCommonEvent_serialize(peer_casted)
    }
    public static getRenderNode(peer: KPointer): KPointer {
        const peer_casted = peer as (KPointer)
        return FrameNodeExtender.getRenderNode_serialize(peer_casted)
    }
    public static convertPoint(peer: FrameNode, node: FrameNode, vector2: Vector2): Array<double> {
        const peer_casted = peer as (FrameNode)
        const node_casted = node as (FrameNode)
        const vector2_casted = vector2 as (Vector2)
        return FrameNodeExtender.convertPoint_serialize(peer_casted, node_casted, vector2_casted)
    }
    public static adoptChild(peer: FrameNode, child: FrameNode): int32 {
        const peer_casted = peer as (FrameNode)
        const child_casted = child as (FrameNode)
        return FrameNodeExtender.adoptChild_serialize(peer_casted, child_casted)
    }
    public static removeAdoptedChild(peer: FrameNode, child: FrameNode): int32 {
        const peer_casted = peer as (FrameNode)
        const child_casted = child as (FrameNode)
        return FrameNodeExtender.removeAdoptedChild_serialize(peer_casted, child_casted)
    }
    public static isOnRenderTree(peer: FrameNode): boolean {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.isOnRenderTree_serialize(peer_casted)
    }
}
export class GestureOps {
    static createTapGesture_serialize(fingers: number, count: number, distanceThreshold: number, isFingerCountLimited: boolean): KPointer {
        console.log("zcb createTapGesture_serialize");
        const retval  = ArkUIGeneratedNativeModule._GestureOps_createTapGesture(fingers, count, distanceThreshold, isFingerCountLimited ? 1 : 0)
        return retval
    }
    static createLongPressGesture_serialize(fingers: number, repeat: boolean, duration: number, isFingerCountLimited: boolean): KPointer {
        const retval  = ArkUIGeneratedNativeModule._GestureOps_createLongPressGesture(fingers, repeat ? 1 : 0, duration, isFingerCountLimited ? 1 : 0)
        return retval
    }
    static createPanGesture_serialize(fingers: number, direction: PanDirection, distance: number, isFingerCountLimited: boolean): KPointer {
        const retval  = ArkUIGeneratedNativeModule._GestureOps_createPanGesture(fingers, direction.valueOf(), distance, isFingerCountLimited ? 1 : 0)
        return retval
    }
    static createPanGestureWithPanGestureOptions_serialize(panGestureOptions: KPointer): KPointer {
        const retval  = ArkUIGeneratedNativeModule._GestureOps_createPanGestureWithPanGestureOptions(panGestureOptions)
        return retval
    }
    static createPinchGesture_serialize(fingers: number, distance: number, isFingerCountLimited: boolean): KPointer {
        const retval  = ArkUIGeneratedNativeModule._GestureOps_createPinchGesture(fingers, distance, isFingerCountLimited ? 1 : 0)
        return retval
    }
    static createRotationGesture_serialize(fingers: number, angle: number, isFingerCountLimited: boolean): KPointer {
        const retval  = ArkUIGeneratedNativeModule._GestureOps_createRotationGesture(fingers, angle, isFingerCountLimited ? 1 : 0)
        return retval
    }
    static createSwipeGesture_serialize(fingers: number, direction: SwipeDirection, speed: number, isFingerCountLimited: boolean): KPointer {
        const retval  = ArkUIGeneratedNativeModule._GestureOps_createSwipeGesture(fingers, direction.valueOf(), speed, isFingerCountLimited ? 1 : 0)
        return retval
    }
    static createGestureGroup_serialize(mode: GestureMode): KPointer {
        const retval  = ArkUIGeneratedNativeModule._GestureOps_createGestureGroup(mode.valueOf())
        return retval
    }
    static setOnAction_serialize(gesture: KPointer, onAction: ((value0: GestureEvent) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onAction)
        ArkUIGeneratedNativeModule._GestureOps_setOnAction(gesture, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static setOnActionStart_serialize(gesture: KPointer, onActionStart: ((value0: GestureEvent) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onActionStart)
        ArkUIGeneratedNativeModule._GestureOps_setOnActionStart(gesture, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static setOnActionUpdate_serialize(gesture: KPointer, onActionUpdate: ((value0: GestureEvent) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onActionUpdate)
        ArkUIGeneratedNativeModule._GestureOps_setOnActionUpdate(gesture, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static setOnActionEnd_serialize(gesture: KPointer, onActionEnd: ((value0: GestureEvent) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onActionEnd)
        ArkUIGeneratedNativeModule._GestureOps_setOnActionEnd(gesture, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static setOnActionCancel_serialize(gesture: KPointer, onActionCancel: ((value0: GestureEvent) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onActionCancel)
        ArkUIGeneratedNativeModule._GestureOps_setOnActionCancel(gesture, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static setOnCancel_serialize(gesture: KPointer, onCancel: (() => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onCancel)
        ArkUIGeneratedNativeModule._GestureOps_setOnCancel(gesture, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static setGestureTag_serialize(gesture: KPointer, tag: string): void {
        ArkUIGeneratedNativeModule._GestureOps_setGestureTag(gesture, tag)
    }
    static setAllowedTypes_serialize(gesture: KPointer, types: Array<SourceTool>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((types.length).toInt())
        for (let typesCounterI = 0; typesCounterI < types.length; typesCounterI++) {
            const typesTmpElement : SourceTool = types[typesCounterI]
            thisSerializer.writeInt32(typesTmpElement.valueOf())
        }
        ArkUIGeneratedNativeModule._GestureOps_setAllowedTypes(gesture, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static addGestureToNode_serialize(node: KPointer, priority: number, mask: GestureMask, gesture: KPointer, isModifier: boolean): void {
        ArkUIGeneratedNativeModule._GestureOps_addGestureToNode(node, priority, mask.valueOf(), gesture, isModifier ? 1 : 0)
    }
    static addGestureToGroup_serialize(group: KPointer, gesture: KPointer): void {
        ArkUIGeneratedNativeModule._GestureOps_addGestureToGroup(group, gesture)
    }
    static removeGestureByTag_serialize(node: KPointer, tag: string): void {
        ArkUIGeneratedNativeModule._GestureOps_removeGestureByTag(node, tag)
    }
    static clearGestures_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._GestureOps_clearGestures(node)
    }
    static getGestureEventType_serialize(event: KPointer): number {
        const retval  = ArkUIGeneratedNativeModule._GestureOps_getGestureEventType(event)
        return retval
    }
    static isScrollableComponent_serialize(event: KPointer): boolean {
        const retval  = ArkUIGeneratedNativeModule._GestureOps_isScrollableComponent(event)
        return retval
    }
    public static createTapGesture(fingers: number, count: number, distanceThreshold: number, isFingerCountLimited: boolean): KPointer {
        const fingers_casted = fingers as (number)
        const count_casted = count as (number)
        const distanceThreshold_casted = distanceThreshold as (number)
        const isFingerCountLimited_casted = isFingerCountLimited as (boolean)
        return GestureOps.createTapGesture_serialize(fingers_casted, count_casted, distanceThreshold_casted, isFingerCountLimited_casted)
    }
    public static createLongPressGesture(fingers: number, repeat: boolean, duration: number, isFingerCountLimited: boolean): KPointer {
        const fingers_casted = fingers as (number)
        const repeat_casted = repeat as (boolean)
        const duration_casted = duration as (number)
        const isFingerCountLimited_casted = isFingerCountLimited as (boolean)
        return GestureOps.createLongPressGesture_serialize(fingers_casted, repeat_casted, duration_casted, isFingerCountLimited_casted)
    }
    public static createPanGesture(fingers: number, direction: PanDirection, distance: number, isFingerCountLimited: boolean): KPointer {
        const fingers_casted = fingers as (number)
        const direction_casted = direction as (PanDirection)
        const distance_casted = distance as (number)
        const isFingerCountLimited_casted = isFingerCountLimited as (boolean)
        return GestureOps.createPanGesture_serialize(fingers_casted, direction_casted, distance_casted, isFingerCountLimited_casted)
    }
    public static createPanGestureWithPanGestureOptions(panGestureOptions: KPointer): KPointer {
        const panGestureOptions_casted = panGestureOptions as (KPointer)
        return GestureOps.createPanGestureWithPanGestureOptions_serialize(panGestureOptions_casted)
    }
    public static createPinchGesture(fingers: number, distance: number, isFingerCountLimited: boolean): KPointer {
        const fingers_casted = fingers as (number)
        const distance_casted = distance as (number)
        const isFingerCountLimited_casted = isFingerCountLimited as (boolean)
        return GestureOps.createPinchGesture_serialize(fingers_casted, distance_casted, isFingerCountLimited_casted)
    }
    public static createRotationGesture(fingers: number, angle: number, isFingerCountLimited: boolean): KPointer {
        const fingers_casted = fingers as (number)
        const angle_casted = angle as (number)
        const isFingerCountLimited_casted = isFingerCountLimited as (boolean)
        return GestureOps.createRotationGesture_serialize(fingers_casted, angle_casted, isFingerCountLimited_casted)
    }
    public static createSwipeGesture(fingers: number, direction: SwipeDirection, speed: number, isFingerCountLimited: boolean): KPointer {
        const fingers_casted = fingers as (number)
        const direction_casted = direction as (SwipeDirection)
        const speed_casted = speed as (number)
        const isFingerCountLimited_casted = isFingerCountLimited as (boolean)
        return GestureOps.createSwipeGesture_serialize(fingers_casted, direction_casted, speed_casted, isFingerCountLimited_casted)
    }
    public static createGestureGroup(mode: GestureMode): KPointer {
        const mode_casted = mode as (GestureMode)
        return GestureOps.createGestureGroup_serialize(mode_casted)
    }
    public static setOnAction(gesture: KPointer, onAction: ((value0: GestureEvent) => void)): void {
        const gesture_casted = gesture as (KPointer)
        const onAction_casted = onAction as (((value0: GestureEvent) => void))
        GestureOps.setOnAction_serialize(gesture_casted, onAction_casted)
        return
    }
    public static setOnActionStart(gesture: KPointer, onActionStart: ((value0: GestureEvent) => void)): void {
        const gesture_casted = gesture as (KPointer)
        const onActionStart_casted = onActionStart as (((value0: GestureEvent) => void))
        GestureOps.setOnActionStart_serialize(gesture_casted, onActionStart_casted)
        return
    }
    public static setOnActionUpdate(gesture: KPointer, onActionUpdate: ((value0: GestureEvent) => void)): void {
        const gesture_casted = gesture as (KPointer)
        const onActionUpdate_casted = onActionUpdate as (((value0: GestureEvent) => void))
        GestureOps.setOnActionUpdate_serialize(gesture_casted, onActionUpdate_casted)
        return
    }
    public static setOnActionEnd(gesture: KPointer, onActionEnd: ((value0: GestureEvent) => void)): void {
        const gesture_casted = gesture as (KPointer)
        const onActionEnd_casted = onActionEnd as (((value0: GestureEvent) => void))
        GestureOps.setOnActionEnd_serialize(gesture_casted, onActionEnd_casted)
        return
    }
    public static setOnActionCancel(gesture: KPointer, onActionCancel: ((value0: GestureEvent) => void)): void {
        const gesture_casted = gesture as (KPointer)
        const onActionCancel_casted = onActionCancel as (((value0: GestureEvent) => void))
        GestureOps.setOnActionCancel_serialize(gesture_casted, onActionCancel_casted)
        return
    }
    public static setOnCancel(gesture: KPointer, onCancel: (() => void)): void {
        const gesture_casted = gesture as (KPointer)
        const onCancel_casted = onCancel as ((() => void))
        GestureOps.setOnCancel_serialize(gesture_casted, onCancel_casted)
        return
    }
    public static setGestureTag(gesture: KPointer, tag: string): void {
        const gesture_casted = gesture as (KPointer)
        const tag_casted = tag as (string)
        GestureOps.setGestureTag_serialize(gesture_casted, tag_casted)
        return
    }
    public static setAllowedTypes(gesture: KPointer, types: Array<SourceTool>): void {
        const gesture_casted = gesture as (KPointer)
        const types_casted = types as (Array<SourceTool>)
        GestureOps.setAllowedTypes_serialize(gesture_casted, types_casted)
        return
    }
    public static addGestureToNode(node: KPointer, priority: number, mask: GestureMask, gesture: KPointer, isModifier: boolean): void {
        console.log("zcb addGestureToNode");
        const node_casted = node as (KPointer)
        const priority_casted = priority as (number)
        const mask_casted = mask as (GestureMask)
        const gesture_casted = gesture as (KPointer)
        const isModifier_casted = isModifier as (boolean)
        GestureOps.addGestureToNode_serialize(node_casted, priority_casted, mask_casted, gesture_casted, isModifier_casted)
        return
    }
    public static addGestureToGroup(group: KPointer, gesture: KPointer): void {
        const group_casted = group as (KPointer)
        const gesture_casted = gesture as (KPointer)
        GestureOps.addGestureToGroup_serialize(group_casted, gesture_casted)
        return
    }
    public static removeGestureByTag(node: KPointer, tag: string): void {
        const node_casted = node as (KPointer)
        const tag_casted = tag as (string)
        GestureOps.removeGestureByTag_serialize(node_casted, tag_casted)
        return
    }
    public static clearGestures(node: KPointer): void {
        const node_casted = node as (KPointer)
        GestureOps.clearGestures_serialize(node_casted)
        return
    }
    public static getGestureEventType(event: KPointer): number {
        const event_casted = event as (KPointer)
        return GestureOps.getGestureEventType_serialize(event_casted)
    }
    public static isScrollableComponent(event: KPointer): boolean {
        const event_casted = event as (KPointer)
        return GestureOps.isScrollableComponent_serialize(event_casted)
    }
}
export class GlobalScope_ohos_arkui_componentSnapshot {
    static get_serialize(id: string, callback: ((result: image.PixelMap) => void), options?: SnapshotOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback)
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            SnapshotOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GlobalScope_ohos_arkui_componentSnapshot_get(id, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static get(id: string, callback: ((result: image.PixelMap) => void), options?: SnapshotOptions): void {
        const id_casted = id as (string)
        const callback_casted = callback as (((result: image.PixelMap) => void))
        const options_casted = options as (SnapshotOptions | undefined)
        GlobalScope_ohos_arkui_componentSnapshot.get_serialize(id_casted, callback_casted, options_casted)
        return
    }
}
export class GlobalScope_ohos_arkui_performanceMonitor {
    static begin_serialize(scene: string, startInputType: PerfMonitorActionType, note?: string): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (note !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const noteTmpValue  = note!
            thisSerializer.writeString(noteTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GlobalScope_ohos_arkui_performanceMonitor_begin(scene, startInputType.valueOf(), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static end_serialize(scene: string): void {
        ArkUIGeneratedNativeModule._GlobalScope_ohos_arkui_performanceMonitor_end(scene)
    }
    static recordInputEventTime_serialize(actionType: PerfMonitorActionType, sourceType: PerfMonitorSourceType, time: int64): void {
        ArkUIGeneratedNativeModule._GlobalScope_ohos_arkui_performanceMonitor_recordInputEventTime(actionType.valueOf(), sourceType.valueOf(), time)
    }
    public static begin(scene: string, startInputType: PerfMonitorActionType, note?: string): void {
        const scene_casted = scene as (string)
        const startInputType_casted = startInputType as (PerfMonitorActionType)
        const note_casted = note as (string | undefined)
        GlobalScope_ohos_arkui_performanceMonitor.begin_serialize(scene_casted, startInputType_casted, note_casted)
        return
    }
    public static end(scene: string): void {
        const scene_casted = scene as (string)
        GlobalScope_ohos_arkui_performanceMonitor.end_serialize(scene_casted)
        return
    }
    public static recordInputEventTime(actionType: PerfMonitorActionType, sourceType: PerfMonitorSourceType, time: int64): void {
        const actionType_casted = actionType as (PerfMonitorActionType)
        const sourceType_casted = sourceType as (PerfMonitorSourceType)
        const time_casted = time as (int64)
        GlobalScope_ohos_arkui_performanceMonitor.recordInputEventTime_serialize(actionType_casted, sourceType_casted, time_casted)
        return
    }
}
export class GlobalScope_ohos_font {
    static registerFont_serialize(options: font.FontOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        font_FontOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._GlobalScope_ohos_font_registerFont(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static getSystemFontList_serialize(): Array<string> {
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_ohos_font_getSystemFontList()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength : int32 = retvalDeserializer.readInt32()
        let buffer : Array<string> = new Array<string>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = (retvalDeserializer.readString() as string)
        }
        const returnResult : Array<string> = buffer
        return returnResult
    }
    static getFontByName_serialize(fontName: string): font.FontInfo {
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_ohos_font_getFontByName(fontName)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : font.FontInfo = font_FontInfo_serializer.read(retvalDeserializer)
        return returnResult
    }
    static getUIFontConfig_serialize(): font.UIFontConfig {
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_ohos_font_getUIFontConfig()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : font.UIFontConfig = font_UIFontConfig_serializer.read(retvalDeserializer)
        return returnResult
    }
    public static registerFont(options: font.FontOptions): void {
        const options_casted = options as (font.FontOptions)
        GlobalScope_ohos_font.registerFont_serialize(options_casted)
        return
    }
    public static getSystemFontList(): Array<string> {
        return GlobalScope_ohos_font.getSystemFontList_serialize()
    }
    public static getFontByName(fontName: string): font.FontInfo {
        const fontName_casted = fontName as (string)
        return GlobalScope_ohos_font.getFontByName_serialize(fontName_casted)
    }
    public static getUIFontConfig(): font.UIFontConfig {
        return GlobalScope_ohos_font.getUIFontConfig_serialize()
    }
}
export class GlobalScope_ohos_measure_utils {
    static measureText_serialize(options: MeasureOptions): double {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        MeasureOptions_serializer.write(thisSerializer, options)
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_ohos_measure_utils_measureText(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static measureTextSize_serialize(options: MeasureOptions): SizeOptions {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        MeasureOptions_serializer.write(thisSerializer, options)
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_ohos_measure_utils_measureTextSize(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : SizeOptions = SizeOptions_serializer.read(retvalDeserializer)
        return returnResult
    }
    public static measureText(options: MeasureOptions): double {
        const options_casted = options as (MeasureOptions)
        return GlobalScope_ohos_measure_utils.measureText_serialize(options_casted)
    }
    public static measureTextSize(options: MeasureOptions): SizeOptions {
        const options_casted = options as (MeasureOptions)
        return GlobalScope_ohos_measure_utils.measureTextSize_serialize(options_casted)
    }
}
export class GlobalScopeUicontextFontScale {
    static isFollowingSystemFontScale_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._GlobalScopeUicontextFontScale_isFollowingSystemFontScale()
        return retval
    }
    static getMaxFontScale_serialize(): double {
        const retval  = ArkUIGeneratedNativeModule._GlobalScopeUicontextFontScale_getMaxFontScale()
        return retval
    }
    public static isFollowingSystemFontScale(): boolean {
        return GlobalScopeUicontextFontScale.isFollowingSystemFontScale_serialize()
    }
    public static getMaxFontScale(): double {
        return GlobalScopeUicontextFontScale.getMaxFontScale_serialize()
    }
}
export class GlobalScopeUicontextTextMenu {
    static setMenuOptions_serialize(options: TextMenuOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        TextMenuOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._GlobalScopeUicontextTextMenu_setMenuOptions(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static setMenuOptions(options: TextMenuOptions): void {
        const options_casted = options as (TextMenuOptions)
        GlobalScopeUicontextTextMenu.setMenuOptions_serialize(options_casted)
        return
    }
}
export class IUIContext {
    static freezeUINode0_serialize(id: string, isFrozen: boolean): void {
        ArkUIGeneratedNativeModule._IUIContext_freezeUINode0(id, isFrozen ? 1 : 0)
    }
    static freezeUINode1_serialize(id: number, isFrozen: boolean): void {
        ArkUIGeneratedNativeModule._IUIContext_freezeUINode1(id, isFrozen ? 1 : 0)
    }
    static dispatchKeyEvent_serialize(node: number | string, event: KeyEvent): boolean {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (node instanceof number) {
            thisSerializer.writeInt8((0).toByte())
            const nodeForIdx0  = node as number
            thisSerializer.writeNumber(nodeForIdx0)
        } else if (node instanceof string) {
            thisSerializer.writeInt8((1).toByte())
            const nodeForIdx1  = node as string
            thisSerializer.writeString(nodeForIdx1)
        }
        const retval  = ArkUIGeneratedNativeModule._IUIContext_dispatchKeyEvent(thisSerializer.asBuffer(), thisSerializer.length(), toPeerPtr(event))
        thisSerializer.release()
        return retval
    }
    public static freezeUINode(id: string, isFrozen: boolean): void {
        const id_casted = id as (string)
        const isFrozen_casted = isFrozen as (boolean)
        IUIContext.freezeUINode0_serialize(id_casted, isFrozen_casted)
        return
    }
    public static freezeUINode(id: number, isFrozen: boolean): void {
        const id_casted = id as (number)
        const isFrozen_casted = isFrozen as (boolean)
        IUIContext.freezeUINode1_serialize(id_casted, isFrozen_casted)
        return
    }
    public static dispatchKeyEvent(node: number | string, event: KeyEvent): boolean {
        const node_casted = node as (number | string)
        const event_casted = event as (KeyEvent)
        return IUIContext.dispatchKeyEvent_serialize(node_casted, event_casted)
    }
}
export class LazyBuild {
    static ApplyLazyBuilder_serialize(): void {
        ArkUIGeneratedNativeModule._LazyBuild_ApplyLazyBuilder()
    }
    static SetListItemLazyBuilder_serialize(node: KPointer, builder: CustomBuilder): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(builder))
        ArkUIGeneratedNativeModule._LazyBuild_SetListItemLazyBuilder(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static SetTabContentLazyBuilder_serialize(node: KPointer, builder: CustomBuilder): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(builder))
        ArkUIGeneratedNativeModule._LazyBuild_SetTabContentLazyBuilder(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static ApplyLazyBuilder(): void {
        LazyBuild.ApplyLazyBuilder_serialize()
        return
    }
    public static SetListItemLazyBuilder(node: KPointer, builder: CustomBuilder): void {
        const node_casted = node as (KPointer)
        const builder_casted = builder as (CustomBuilder)
        LazyBuild.SetListItemLazyBuilder_serialize(node_casted, builder_casted)
        return
    }
    public static SetTabContentLazyBuilder(node: KPointer, builder: CustomBuilder): void {
        const node_casted = node as (KPointer)
        const builder_casted = builder as (CustomBuilder)
        LazyBuild.SetTabContentLazyBuilder_serialize(node_casted, builder_casted)
        return
    }
}
export class LazyForEachOps {
    static NotifyChange_serialize(node: KPointer, startIndex: int32, endIndex: int32, count: int32): void {
        ArkUIGeneratedNativeModule._LazyForEachOps_NotifyChange(node, startIndex, endIndex, count)
    }
    static Sync_serialize(node: KPointer, totalCount: int32, creator: Callback_CreateItem, updater: Callback_RangeUpdate): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(creator)
        thisSerializer.holdAndWriteCallback(updater)
        ArkUIGeneratedNativeModule._LazyForEachOps_Sync(node, totalCount, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static SyncOnMoveOps_serialize(node: KPointer, onMoveFromToOps: Callback_OnMoveFromTo, onMoveOps: OnMoveHandler | undefined, onMoveDragEventOps: ItemDragEventHandler | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onMoveFromToOps)
        if (onMoveOps !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const onMoveOpsTmpValue  = onMoveOps!
            thisSerializer.holdAndWriteCallback(onMoveOpsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (onMoveDragEventOps !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const onMoveDragEventOpsTmpValue  = onMoveDragEventOps!
            ItemDragEventHandler_serializer.write(thisSerializer, onMoveDragEventOpsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._LazyForEachOps_SyncOnMoveOps(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static NotifyChange(node: KPointer, startIndex: int32, endIndex: int32, count: int32): void {
        const node_casted = node as (KPointer)
        const startIndex_casted = startIndex as (int32)
        const endIndex_casted = endIndex as (int32)
        const count_casted = count as (int32)
        LazyForEachOps.NotifyChange_serialize(node_casted, startIndex_casted, endIndex_casted, count_casted)
        return
    }
    public static Sync(node: KPointer, totalCount: int32, creator: Callback_CreateItem, updater: Callback_RangeUpdate): void {
        const node_casted = node as (KPointer)
        const totalCount_casted = totalCount as (int32)
        const creator_casted = creator as (Callback_CreateItem)
        const updater_casted = updater as (Callback_RangeUpdate)
        LazyForEachOps.Sync_serialize(node_casted, totalCount_casted, creator_casted, updater_casted)
        return
    }
    public static SyncOnMoveOps(node: KPointer, onMoveFromToOps: Callback_OnMoveFromTo, onMoveOps: OnMoveHandler | undefined, onMoveDragEventOps: ItemDragEventHandler | undefined): void {
        const node_casted = node as (KPointer)
        const onMoveFromToOps_casted = onMoveFromToOps as (Callback_OnMoveFromTo)
        const onMoveOps_casted = onMoveOps as (OnMoveHandler | undefined)
        const onMoveDragEventOps_casted = onMoveDragEventOps as (ItemDragEventHandler | undefined)
        LazyForEachOps.SyncOnMoveOps_serialize(node_casted, onMoveFromToOps_casted, onMoveOps_casted, onMoveDragEventOps_casted)
        return
    }
}
export class LevelOrderExtenderInternal {
    public static fromPtr(ptr: KPointer): LevelOrderExtender {
        return new LevelOrderExtender(ptr)
    }
}
export class LevelOrderExtender implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, LevelOrderExtender.getFinalizer())
    }
    constructor() {
        this(LevelOrderExtender.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._LevelOrderExtender_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LevelOrderExtender_getFinalizer()
    }
    static clamp_serialize(order: number): LevelOrderExtender {
        const retval  = ArkUIGeneratedNativeModule._LevelOrderExtender_clamp(order)
        const obj : LevelOrderExtender = LevelOrderExtenderInternal.fromPtr(retval)
        return obj
    }
    public static clamp(order: number): LevelOrderExtender {
        const order_casted = order as (number)
        return LevelOrderExtender.clamp_serialize(order_casted)
    }
    public getOrder(): number {
        return this.getOrder_serialize()
    }
    getOrder_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._LevelOrderExtender_getOrder(this.peer!.ptr)
        return retval
    }
}
export class NavExtender {
    static setNavigationOptions_serialize(ptr: KPointer, pathStack: NavPathStack): void {
        ArkUIGeneratedNativeModule._NavExtender_setNavigationOptions(ptr, toPeerPtr(pathStack))
    }
    static setUpdateStackCallback_serialize(peer: NavPathStack, callback: NavExtender_OnUpdateStack): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._NavExtender_setUpdateStackCallback(toPeerPtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static syncStack_serialize(peer: NavPathStack): void {
        ArkUIGeneratedNativeModule._NavExtender_syncStack(toPeerPtr(peer))
    }
    static checkNeedCreate_serialize(navigation: KPointer, index: int32): boolean {
        const retval  = ArkUIGeneratedNativeModule._NavExtender_checkNeedCreate(navigation, index)
        return retval
    }
    static setNavDestinationNode_serialize(peer: NavPathStack, index: int32, node: KPointer): void {
        ArkUIGeneratedNativeModule._NavExtender_setNavDestinationNode(toPeerPtr(peer), index, node)
    }
    static pushPath_serialize(pathStack: NavPathStack, info: NavPathInfo, options: NavigationOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        NavigationOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._NavExtender_pushPath(toPeerPtr(pathStack), toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static replacePath_serialize(pathStack: NavPathStack, info: NavPathInfo, options: NavigationOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        NavigationOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._NavExtender_replacePath(toPeerPtr(pathStack), toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static pop_serialize(pathStack: NavPathStack, animated: boolean): string {
        const retval  = ArkUIGeneratedNativeModule._NavExtender_pop(toPeerPtr(pathStack), animated ? 1 : 0)
        return retval
    }
    static setOnPopCallback_serialize(pathStack: NavPathStack, popCallback: ((breakpoints: string) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(popCallback)
        ArkUIGeneratedNativeModule._NavExtender_setOnPopCallback(toPeerPtr(pathStack), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static getIdByIndex_serialize(pathStack: NavPathStack, index: int32): string {
        const retval  = ArkUIGeneratedNativeModule._NavExtender_getIdByIndex(toPeerPtr(pathStack), index)
        return retval
    }
    static getIdByName_serialize(pathStack: NavPathStack, name: string): Array<string> {
        const retval  = ArkUIGeneratedNativeModule._NavExtender_getIdByName(toPeerPtr(pathStack), name)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength : int32 = retvalDeserializer.readInt32()
        let buffer : Array<string> = new Array<string>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = (retvalDeserializer.readString() as string)
        }
        const returnResult : Array<string> = buffer
        return returnResult
    }
    static popToIndex_serialize(pathStack: NavPathStack, index: int32, animated: boolean): void {
        ArkUIGeneratedNativeModule._NavExtender_popToIndex(toPeerPtr(pathStack), index, animated ? 1 : 0)
    }
    static popToName_serialize(pathStack: NavPathStack, name: string, animated: boolean): int32 {
        const retval  = ArkUIGeneratedNativeModule._NavExtender_popToName(toPeerPtr(pathStack), name, animated ? 1 : 0)
        return retval
    }
    static setCreateNavDestinationCallback_serialize(peer: NavPathStack, callback: NavExtender_CreateNavDestination): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._NavExtender_setCreateNavDestinationCallback(toPeerPtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static setNavigationOptions(ptr: KPointer, pathStack: NavPathStack): void {
        const ptr_casted = ptr as (KPointer)
        const pathStack_casted = pathStack as (NavPathStack)
        NavExtender.setNavigationOptions_serialize(ptr_casted, pathStack_casted)
        return
    }
    public static setUpdateStackCallback(peer: NavPathStack, callback: NavExtender_OnUpdateStack): void {
        const peer_casted = peer as (NavPathStack)
        const callback_casted = callback as (NavExtender_OnUpdateStack)
        NavExtender.setUpdateStackCallback_serialize(peer_casted, callback_casted)
        return
    }
    public static syncStack(peer: NavPathStack): void {
        const peer_casted = peer as (NavPathStack)
        NavExtender.syncStack_serialize(peer_casted)
        return
    }
    public static checkNeedCreate(navigation: KPointer, index: int32): boolean {
        const navigation_casted = navigation as (KPointer)
        const index_casted = index as (int32)
        return NavExtender.checkNeedCreate_serialize(navigation_casted, index_casted)
    }
    public static setNavDestinationNode(peer: NavPathStack, index: int32, node: KPointer): void {
        const peer_casted = peer as (NavPathStack)
        const index_casted = index as (int32)
        const node_casted = node as (KPointer)
        NavExtender.setNavDestinationNode_serialize(peer_casted, index_casted, node_casted)
        return
    }
    public static pushPath(pathStack: NavPathStack, info: NavPathInfo, options: NavigationOptions): void {
        const pathStack_casted = pathStack as (NavPathStack)
        const info_casted = info as (NavPathInfo)
        const options_casted = options as (NavigationOptions)
        NavExtender.pushPath_serialize(pathStack_casted, info_casted, options_casted)
        return
    }
    public static replacePath(pathStack: NavPathStack, info: NavPathInfo, options: NavigationOptions): void {
        const pathStack_casted = pathStack as (NavPathStack)
        const info_casted = info as (NavPathInfo)
        const options_casted = options as (NavigationOptions)
        NavExtender.replacePath_serialize(pathStack_casted, info_casted, options_casted)
        return
    }
    public static pop(pathStack: NavPathStack, animated: boolean): string {
        const pathStack_casted = pathStack as (NavPathStack)
        const animated_casted = animated as (boolean)
        return NavExtender.pop_serialize(pathStack_casted, animated_casted)
    }
    public static setOnPopCallback(pathStack: NavPathStack, popCallback: ((breakpoints: string) => void)): void {
        const pathStack_casted = pathStack as (NavPathStack)
        const popCallback_casted = popCallback as (((breakpoints: string) => void))
        NavExtender.setOnPopCallback_serialize(pathStack_casted, popCallback_casted)
        return
    }
    public static getIdByIndex(pathStack: NavPathStack, index: int32): string {
        const pathStack_casted = pathStack as (NavPathStack)
        const index_casted = index as (int32)
        return NavExtender.getIdByIndex_serialize(pathStack_casted, index_casted)
    }
    public static getIdByName(pathStack: NavPathStack, name: string): Array<string> {
        const pathStack_casted = pathStack as (NavPathStack)
        const name_casted = name as (string)
        return NavExtender.getIdByName_serialize(pathStack_casted, name_casted)
    }
    public static popToIndex(pathStack: NavPathStack, index: int32, animated: boolean): void {
        const pathStack_casted = pathStack as (NavPathStack)
        const index_casted = index as (int32)
        const animated_casted = animated as (boolean)
        NavExtender.popToIndex_serialize(pathStack_casted, index_casted, animated_casted)
        return
    }
    public static popToName(pathStack: NavPathStack, name: string, animated: boolean): int32 {
        const pathStack_casted = pathStack as (NavPathStack)
        const name_casted = name as (string)
        const animated_casted = animated as (boolean)
        return NavExtender.popToName_serialize(pathStack_casted, name_casted, animated_casted)
    }
    public static setCreateNavDestinationCallback(peer: NavPathStack, callback: NavExtender_CreateNavDestination): void {
        const peer_casted = peer as (NavPathStack)
        const callback_casted = callback as (NavExtender_CreateNavDestination)
        NavExtender.setCreateNavDestinationCallback_serialize(peer_casted, callback_casted)
        return
    }
}
export class NodeContainerOps {
    static nodeContainerOpsConstruct_serialize(id: int32, flags: int32): KPointer {
        const retval  = ArkUIGeneratedNativeModule._NodeContainerOps_nodeContainerOpsConstruct(id, flags)
        return retval
    }
    static nodeContainerSetNodeContainerOptions_serialize(ptr: KPointer, controller: KPointer): void {
        ArkUIGeneratedNativeModule._NodeContainerOps_nodeContainerSetNodeContainerOptions(ptr, controller)
    }
    static addNodeContainerRootNode_serialize(self: KPointer, child: KPointer): void {
        ArkUIGeneratedNativeModule._NodeContainerOps_addNodeContainerRootNode(self, child)
    }
    static setAboutToAppear_serialize(self: KPointer, value: (() => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NodeContainerOps_setAboutToAppear(self, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static setAboutToDisappear_serialize(self: KPointer, value: (() => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NodeContainerOps_setAboutToDisappear(self, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static setAboutToResize_serialize(self: KPointer, value: Callback_Size_Void): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NodeContainerOps_setAboutToResize(self, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static setOnAttach_serialize(self: KPointer, value: (() => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NodeContainerOps_setOnAttach(self, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static setOnDetach_serialize(self: KPointer, value: (() => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NodeContainerOps_setOnDetach(self, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static setOnTouchEvent_serialize(self: KPointer, value?: ((event: TouchEvent) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NodeContainerOps_setOnTouchEvent(self, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static setOnDestoryEvent_serialize(self: KPointer, value: Callback_OnDestory_Void): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NodeContainerOps_setOnDestoryEvent(self, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static nodeContainerOpsConstruct(id: int32, flags: int32): KPointer {
        const id_casted = id as (int32)
        const flags_casted = flags as (int32)
        return NodeContainerOps.nodeContainerOpsConstruct_serialize(id_casted, flags_casted)
    }
    public static nodeContainerSetNodeContainerOptions(ptr: KPointer, controller: KPointer): void {
        const ptr_casted = ptr as (KPointer)
        const controller_casted = controller as (KPointer)
        NodeContainerOps.nodeContainerSetNodeContainerOptions_serialize(ptr_casted, controller_casted)
        return
    }
    public static addNodeContainerRootNode(self: KPointer, child: KPointer): void {
        const self_casted = self as (KPointer)
        const child_casted = child as (KPointer)
        NodeContainerOps.addNodeContainerRootNode_serialize(self_casted, child_casted)
        return
    }
    public static setAboutToAppear(self: KPointer, value: (() => void)): void {
        const self_casted = self as (KPointer)
        const value_casted = value as ((() => void))
        NodeContainerOps.setAboutToAppear_serialize(self_casted, value_casted)
        return
    }
    public static setAboutToDisappear(self: KPointer, value: (() => void)): void {
        const self_casted = self as (KPointer)
        const value_casted = value as ((() => void))
        NodeContainerOps.setAboutToDisappear_serialize(self_casted, value_casted)
        return
    }
    public static setAboutToResize(self: KPointer, value: Callback_Size_Void): void {
        const self_casted = self as (KPointer)
        const value_casted = value as (Callback_Size_Void)
        NodeContainerOps.setAboutToResize_serialize(self_casted, value_casted)
        return
    }
    public static setOnAttach(self: KPointer, value: (() => void)): void {
        const self_casted = self as (KPointer)
        const value_casted = value as ((() => void))
        NodeContainerOps.setOnAttach_serialize(self_casted, value_casted)
        return
    }
    public static setOnDetach(self: KPointer, value: (() => void)): void {
        const self_casted = self as (KPointer)
        const value_casted = value as ((() => void))
        NodeContainerOps.setOnDetach_serialize(self_casted, value_casted)
        return
    }
    public static setOnTouchEvent(self: KPointer, value?: ((event: TouchEvent) => void)): void {
        const self_casted = self as (KPointer)
        const value_casted = value as (((event: TouchEvent) => void) | undefined)
        NodeContainerOps.setOnTouchEvent_serialize(self_casted, value_casted)
        return
    }
    public static setOnDestoryEvent(self: KPointer, value: Callback_OnDestory_Void): void {
        const self_casted = self as (KPointer)
        const value_casted = value as (Callback_OnDestory_Void)
        NodeContainerOps.setOnDestoryEvent_serialize(self_casted, value_casted)
        return
    }
}
export class ParticleHelper {
    static SetDisturbanceFields_serialize(node: KPointer, disturbanceFields: Array<DisturbanceFieldOptionsInner> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (disturbanceFields !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const disturbanceFieldsTmpValue  = disturbanceFields!
            thisSerializer.writeInt32((disturbanceFieldsTmpValue.length).toInt())
            for (let disturbanceFieldsTmpValueCounterI = 0; disturbanceFieldsTmpValueCounterI < disturbanceFieldsTmpValue.length; disturbanceFieldsTmpValueCounterI++) {
                const disturbanceFieldsTmpValueTmpElement : DisturbanceFieldOptionsInner = disturbanceFieldsTmpValue[disturbanceFieldsTmpValueCounterI]
                DisturbanceFieldOptionsInner_serializer.write(thisSerializer, disturbanceFieldsTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ParticleHelper_SetDisturbanceFields(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static SetEmitterProperty_serialize(node: KPointer, emitter: Array<EmitterPropertyInner> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (emitter !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const emitterTmpValue  = emitter!
            thisSerializer.writeInt32((emitterTmpValue.length).toInt())
            for (let emitterTmpValueCounterI = 0; emitterTmpValueCounterI < emitterTmpValue.length; emitterTmpValueCounterI++) {
                const emitterTmpValueTmpElement : EmitterPropertyInner = emitterTmpValue[emitterTmpValueCounterI]
                EmitterPropertyInner_serializer.write(thisSerializer, emitterTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ParticleHelper_SetEmitterProperty(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static ParticleConstruct_serialize(id: int32, flags: int32): KPointer {
        const retval  = ArkUIGeneratedNativeModule._ParticleHelper_ParticleConstruct(id, flags)
        return retval
    }
    static SetParticleOptions_serialize(node: KPointer, particles: ParticlesInner): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        ParticlesInner_serializer.write(thisSerializer, particles)
        ArkUIGeneratedNativeModule._ParticleHelper_SetParticleOptions(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static SetDisturbanceFields(node: KPointer, disturbanceFields: Array<DisturbanceFieldOptionsInner> | undefined): void {
        const node_casted = node as (KPointer)
        const disturbanceFields_casted = disturbanceFields as (Array<DisturbanceFieldOptionsInner> | undefined)
        ParticleHelper.SetDisturbanceFields_serialize(node_casted, disturbanceFields_casted)
        return
    }
    public static SetEmitterProperty(node: KPointer, emitter: Array<EmitterPropertyInner> | undefined): void {
        const node_casted = node as (KPointer)
        const emitter_casted = emitter as (Array<EmitterPropertyInner> | undefined)
        ParticleHelper.SetEmitterProperty_serialize(node_casted, emitter_casted)
        return
    }
    public static ParticleConstruct(id: int32, flags: int32): KPointer {
        const id_casted = id as (int32)
        const flags_casted = flags as (int32)
        return ParticleHelper.ParticleConstruct_serialize(id_casted, flags_casted)
    }
    public static SetParticleOptions(node: KPointer, particles: ParticlesInner): void {
        const node_casted = node as (KPointer)
        const particles_casted = particles as (ParticlesInner)
        ParticleHelper.SetParticleOptions_serialize(node_casted, particles_casted)
        return
    }
}
export class NodeContentExtender {
    static constructorNodeContent_serialize(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._NodeContentExtender_constructorNodeContent()
        return retval
    }
    static getDestroy_serialize(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._NodeContentExtender_getDestroy()
        return retval
    }
    static addFrameNode_serialize(content: KPointer, node: KPointer): int32 {
        const retval  = ArkUIGeneratedNativeModule._NodeContentExtender_addFrameNode(content, node)
        return retval
    }
    static removeFrameNode_serialize(content: KPointer, node: KPointer): boolean {
        const retval  = ArkUIGeneratedNativeModule._NodeContentExtender_removeFrameNode(content, node)
        return retval
    }
    public static constructorNodeContent(): KPointer {
        return NodeContentExtender.constructorNodeContent_serialize()
    }
    public static getDestroy(): KPointer {
        return NodeContentExtender.getDestroy_serialize()
    }
    public static addFrameNode(content: KPointer, node: KPointer): int32 {
        const content_casted = content as (KPointer)
        const node_casted = node as (KPointer)
        return NodeContentExtender.addFrameNode_serialize(content_casted, node_casted)
    }
    public static removeFrameNode(content: KPointer, node: KPointer): boolean {
        const content_casted = content as (KPointer)
        const node_casted = node as (KPointer)
        return NodeContentExtender.removeFrameNode_serialize(content_casted, node_casted)
    }
}
export class PromptActionExtender {
    static openPopup_serialize(content: KPointer, target: TargetInfo, options?: PopupCommonOptions): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        TargetInfo_serializer.write(thisSerializer, target)
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            PopupCommonOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._PromptActionExtender_openPopup(content, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static updatePopup_serialize(content: KPointer, options: PopupCommonOptions, partialUpdate?: boolean): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        PopupCommonOptions_serializer.write(thisSerializer, options)
        if (partialUpdate !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const partialUpdateTmpValue  = partialUpdate!
            thisSerializer.writeBoolean(partialUpdateTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._PromptActionExtender_updatePopup(content, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static closePopup_serialize(content: KPointer): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._PromptActionExtender_closePopup(content, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static openMenu_serialize(content: KPointer, target: TargetInfo, options?: MenuOptions): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        TargetInfo_serializer.write(thisSerializer, target)
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            MenuOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._PromptActionExtender_openMenu(content, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static updateMenu_serialize(content: KPointer, options: MenuOptions, partialUpdate?: boolean): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        MenuOptions_serializer.write(thisSerializer, options)
        if (partialUpdate !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const partialUpdateTmpValue  = partialUpdate!
            thisSerializer.writeBoolean(partialUpdateTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._PromptActionExtender_updateMenu(content, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static closeMenu_serialize(content: KPointer): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._PromptActionExtender_closeMenu(content, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    public static openPopup(content: KPointer, target: TargetInfo, options?: PopupCommonOptions): Promise<void> {
        const content_casted = content as (KPointer)
        const target_casted = target as (TargetInfo)
        const options_casted = options as (PopupCommonOptions | undefined)
        return PromptActionExtender.openPopup_serialize(content_casted, target_casted, options_casted)
    }
    public static updatePopup(content: KPointer, options: PopupCommonOptions, partialUpdate?: boolean): Promise<void> {
        const content_casted = content as (KPointer)
        const options_casted = options as (PopupCommonOptions)
        const partialUpdate_casted = partialUpdate as (boolean | undefined)
        return PromptActionExtender.updatePopup_serialize(content_casted, options_casted, partialUpdate_casted)
    }
    public static closePopup(content: KPointer): Promise<void> {
        const content_casted = content as (KPointer)
        return PromptActionExtender.closePopup_serialize(content_casted)
    }
    public static openMenu(content: KPointer, target: TargetInfo, options?: MenuOptions): Promise<void> {
        const content_casted = content as (KPointer)
        const target_casted = target as (TargetInfo)
        const options_casted = options as (MenuOptions | undefined)
        return PromptActionExtender.openMenu_serialize(content_casted, target_casted, options_casted)
    }
    public static updateMenu(content: KPointer, options: MenuOptions, partialUpdate?: boolean): Promise<void> {
        const content_casted = content as (KPointer)
        const options_casted = options as (MenuOptions)
        const partialUpdate_casted = partialUpdate as (boolean | undefined)
        return PromptActionExtender.updateMenu_serialize(content_casted, options_casted, partialUpdate_casted)
    }
    public static closeMenu(content: KPointer): Promise<void> {
        const content_casted = content as (KPointer)
        return PromptActionExtender.closeMenu_serialize(content_casted)
    }
}
export class RenderNodeExtender {
    static constructorRenderNode_serialize(nodeId: int32): KPointer {
        const retval  = ArkUIGeneratedNativeModule._RenderNodeExtender_constructorRenderNode(nodeId)
        return retval
    }
    static getDestroy_serialize(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._RenderNodeExtender_getDestroy()
        return retval
    }
    static destroyPeer_serialize(peer: RenderNode): void {
        ArkUIGeneratedNativeModule._RenderNodeExtender_destroyPeer(extractors.toRenderNodePtr(peer))
    }
    static setBackgroundColor_serialize(peer: RenderNode, backgroundColor: number): void {
        ArkUIGeneratedNativeModule._RenderNodeExtender_setBackgroundColor(extractors.toRenderNodePtr(peer), backgroundColor)
    }
    static setClipToFrame_serialize(peer: RenderNode, clipToFrame: boolean): void {
        ArkUIGeneratedNativeModule._RenderNodeExtender_setClipToFrame(extractors.toRenderNodePtr(peer), clipToFrame ? 1 : 0)
    }
    static setOpacity_serialize(peer: RenderNode, opacity: number): void {
        ArkUIGeneratedNativeModule._RenderNodeExtender_setOpacity(extractors.toRenderNodePtr(peer), opacity)
    }
    static setSize_serialize(peer: RenderNode, size: Size, unitValue: int32): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Size_serializer.write(thisSerializer, size)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setSize(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length(), unitValue)
        thisSerializer.release()
    }
    static setPosition_serialize(peer: RenderNode, position: Vector2, unitValue: int32): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Vector2_serializer.write(thisSerializer, position)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setPosition(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length(), unitValue)
        thisSerializer.release()
    }
    static setPivot_serialize(peer: RenderNode, pivot: Vector2): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Vector2_serializer.write(thisSerializer, pivot)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setPivot(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static setScale_serialize(peer: RenderNode, scale: Vector2): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Vector2_serializer.write(thisSerializer, scale)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setScale(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static setTranslation_serialize(peer: RenderNode, translation: Vector2): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Vector2_serializer.write(thisSerializer, translation)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setTranslation(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static setRotation_serialize(peer: RenderNode, rotation: Vector3, unitValue: int32): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Vector3_serializer.write(thisSerializer, rotation)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setRotation(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length(), unitValue)
        thisSerializer.release()
    }
    static setTransform_serialize(peer: RenderNode, transform: Matrix4): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        const transform_0  = transform[0]
        thisSerializer.writeNumber(transform_0)
        const transform_1  = transform[1]
        thisSerializer.writeNumber(transform_1)
        const transform_2  = transform[2]
        thisSerializer.writeNumber(transform_2)
        const transform_3  = transform[3]
        thisSerializer.writeNumber(transform_3)
        const transform_4  = transform[4]
        thisSerializer.writeNumber(transform_4)
        const transform_5  = transform[5]
        thisSerializer.writeNumber(transform_5)
        const transform_6  = transform[6]
        thisSerializer.writeNumber(transform_6)
        const transform_7  = transform[7]
        thisSerializer.writeNumber(transform_7)
        const transform_8  = transform[8]
        thisSerializer.writeNumber(transform_8)
        const transform_9  = transform[9]
        thisSerializer.writeNumber(transform_9)
        const transform_10  = transform[10]
        thisSerializer.writeNumber(transform_10)
        const transform_11  = transform[11]
        thisSerializer.writeNumber(transform_11)
        const transform_12  = transform[12]
        thisSerializer.writeNumber(transform_12)
        const transform_13  = transform[13]
        thisSerializer.writeNumber(transform_13)
        const transform_14  = transform[14]
        thisSerializer.writeNumber(transform_14)
        const transform_15  = transform[15]
        thisSerializer.writeNumber(transform_15)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setTransform(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static setShadowColor_serialize(peer: RenderNode, shadowColor: number): void {
        ArkUIGeneratedNativeModule._RenderNodeExtender_setShadowColor(extractors.toRenderNodePtr(peer), shadowColor)
    }
    static setShadowOffset_serialize(peer: RenderNode, shadowOffset: Vector2, unitValue: int32): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Vector2_serializer.write(thisSerializer, shadowOffset)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setShadowOffset(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length(), unitValue)
        thisSerializer.release()
    }
    static setLabel_serialize(peer: RenderNode, label: string): void {
        ArkUIGeneratedNativeModule._RenderNodeExtender_setLabel(extractors.toRenderNodePtr(peer), label)
    }
    static setShadowAlpha_serialize(peer: RenderNode, shadowAlpha: number): void {
        ArkUIGeneratedNativeModule._RenderNodeExtender_setShadowAlpha(extractors.toRenderNodePtr(peer), shadowAlpha)
    }
    static setShadowElevation_serialize(peer: RenderNode, shadowElevation: number): void {
        ArkUIGeneratedNativeModule._RenderNodeExtender_setShadowElevation(extractors.toRenderNodePtr(peer), shadowElevation)
    }
    static setShadowRadius_serialize(peer: RenderNode, shadowRadius: number): void {
        ArkUIGeneratedNativeModule._RenderNodeExtender_setShadowRadius(extractors.toRenderNodePtr(peer), shadowRadius)
    }
    static setBorderStyle_serialize(peer: RenderNode, borderStyle: NodeEdgeStyles): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        NodeEdgeStyles_serializer.write(thisSerializer, borderStyle)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setBorderStyle(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static setBorderWidth_serialize(peer: RenderNode, borderWidth: EdgeNumber, unitValue: int32): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        EdgeNumber_serializer.write(thisSerializer, borderWidth)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setBorderWidth(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length(), unitValue)
        thisSerializer.release()
    }
    static setBorderColor_serialize(peer: RenderNode, borderColor: EdgeNumber): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        EdgeNumber_serializer.write(thisSerializer, borderColor)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setBorderColor(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static setBorderRadius_serialize(peer: RenderNode, borderRadius: BorderRadiuses_graphics, unitValue: int32): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        BorderRadiuses_graphics_serializer.write(thisSerializer, borderRadius)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setBorderRadius(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length(), unitValue)
        thisSerializer.release()
    }
    static setMarkNodeGroup_serialize(peer: RenderNode, markNodeGroup: boolean): void {
        ArkUIGeneratedNativeModule._RenderNodeExtender_setMarkNodeGroup(extractors.toRenderNodePtr(peer), markNodeGroup ? 1 : 0)
    }
    static setRectMask_serialize(peer: RenderNode, rect: common2D.Rect, fillColor: number, strokeColor: number, strokeWidth: number): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        common2D_Rect_serializer.write(thisSerializer, rect)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setRectMask(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length(), fillColor, strokeColor, strokeWidth)
        thisSerializer.release()
    }
    static setCircleMask_serialize(peer: RenderNode, circle: Circle, fillColor: number, strokeColor: number, strokeWidth: number): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Circle_serializer.write(thisSerializer, circle)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setCircleMask(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length(), fillColor, strokeColor, strokeWidth)
        thisSerializer.release()
    }
    static setRoundRectMask_serialize(peer: RenderNode, roundRect: RoundRect, fillColor: number, strokeColor: number, strokeWidth: number): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        RoundRect_serializer.write(thisSerializer, roundRect)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setRoundRectMask(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length(), fillColor, strokeColor, strokeWidth)
        thisSerializer.release()
    }
    static setOvalMask_serialize(peer: RenderNode, rect: common2D.Rect, fillColor: number, strokeColor: number, strokeWidth: number): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        common2D_Rect_serializer.write(thisSerializer, rect)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setOvalMask(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length(), fillColor, strokeColor, strokeWidth)
        thisSerializer.release()
    }
    static setPath_serialize(peer: RenderNode, path: CommandPath, fillColor: number, strokeColor: number, strokeWidth: number): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        CommandPath_serializer.write(thisSerializer, path)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setPath(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length(), fillColor, strokeColor, strokeWidth)
        thisSerializer.release()
    }
    static setRectClip_serialize(peer: RenderNode, rect: common2D.Rect): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        common2D_Rect_serializer.write(thisSerializer, rect)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setRectClip(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static setCircleClip_serialize(peer: RenderNode, circle: Circle): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Circle_serializer.write(thisSerializer, circle)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setCircleClip(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static setRoundRectClip_serialize(peer: RenderNode, roundRect: RoundRect): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        RoundRect_serializer.write(thisSerializer, roundRect)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setRoundRectClip(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static setOvalClip_serialize(peer: RenderNode, rect: common2D.Rect): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        common2D_Rect_serializer.write(thisSerializer, rect)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setOvalClip(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static setPathClip_serialize(peer: RenderNode, path: CommandPath): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        CommandPath_serializer.write(thisSerializer, path)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setPathClip(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static appendChild_serialize(peer: RenderNode, node: RenderNode): int32 {
        const retval  = ArkUIGeneratedNativeModule._RenderNodeExtender_appendChild(extractors.toRenderNodePtr(peer), extractors.toRenderNodePtr(node))
        return retval
    }
    static insertChildAfter_serialize(peer: RenderNode, child: RenderNode, sibling: RenderNode): int32 {
        const retval  = ArkUIGeneratedNativeModule._RenderNodeExtender_insertChildAfter(extractors.toRenderNodePtr(peer), extractors.toRenderNodePtr(child), extractors.toRenderNodePtr(sibling))
        return retval
    }
    static removeChild_serialize(peer: RenderNode, node: RenderNode): void {
        ArkUIGeneratedNativeModule._RenderNodeExtender_removeChild(extractors.toRenderNodePtr(peer), extractors.toRenderNodePtr(node))
    }
    static clearChildren_serialize(peer: RenderNode): void {
        ArkUIGeneratedNativeModule._RenderNodeExtender_clearChildren(extractors.toRenderNodePtr(peer))
    }
    static invalidate_serialize(peer: RenderNode): void {
        ArkUIGeneratedNativeModule._RenderNodeExtender_invalidate(extractors.toRenderNodePtr(peer))
    }
    public static constructorRenderNode(nodeId: int32): KPointer {
        const nodeId_casted = nodeId as (int32)
        return RenderNodeExtender.constructorRenderNode_serialize(nodeId_casted)
    }
    public static getDestroy(): KPointer {
        return RenderNodeExtender.getDestroy_serialize()
    }
    public static destroyPeer(peer: RenderNode): void {
        const peer_casted = peer as (RenderNode)
        RenderNodeExtender.destroyPeer_serialize(peer_casted)
        return
    }
    public static setBackgroundColor(peer: RenderNode, backgroundColor: number): void {
        const peer_casted = peer as (RenderNode)
        const backgroundColor_casted = backgroundColor as (number)
        RenderNodeExtender.setBackgroundColor_serialize(peer_casted, backgroundColor_casted)
        return
    }
    public static setClipToFrame(peer: RenderNode, clipToFrame: boolean): void {
        const peer_casted = peer as (RenderNode)
        const clipToFrame_casted = clipToFrame as (boolean)
        RenderNodeExtender.setClipToFrame_serialize(peer_casted, clipToFrame_casted)
        return
    }
    public static setOpacity(peer: RenderNode, opacity: number): void {
        const peer_casted = peer as (RenderNode)
        const opacity_casted = opacity as (number)
        RenderNodeExtender.setOpacity_serialize(peer_casted, opacity_casted)
        return
    }
    public static setSize(peer: RenderNode, size: Size, unitValue: int32): void {
        const peer_casted = peer as (RenderNode)
        const size_casted = size as (Size)
        const unitValue_casted = unitValue as (int32)
        RenderNodeExtender.setSize_serialize(peer_casted, size_casted, unitValue_casted)
        return
    }
    public static setPosition(peer: RenderNode, position: Vector2, unitValue: int32): void {
        const peer_casted = peer as (RenderNode)
        const position_casted = position as (Vector2)
        const unitValue_casted = unitValue as (int32)
        RenderNodeExtender.setPosition_serialize(peer_casted, position_casted, unitValue_casted)
        return
    }
    public static setPivot(peer: RenderNode, pivot: Vector2): void {
        const peer_casted = peer as (RenderNode)
        const pivot_casted = pivot as (Vector2)
        RenderNodeExtender.setPivot_serialize(peer_casted, pivot_casted)
        return
    }
    public static setScale(peer: RenderNode, scale: Vector2): void {
        const peer_casted = peer as (RenderNode)
        const scale_casted = scale as (Vector2)
        RenderNodeExtender.setScale_serialize(peer_casted, scale_casted)
        return
    }
    public static setTranslation(peer: RenderNode, translation: Vector2): void {
        const peer_casted = peer as (RenderNode)
        const translation_casted = translation as (Vector2)
        RenderNodeExtender.setTranslation_serialize(peer_casted, translation_casted)
        return
    }
    public static setRotation(peer: RenderNode, rotation: Vector3, unitValue: int32): void {
        const peer_casted = peer as (RenderNode)
        const rotation_casted = rotation as (Vector3)
        const unitValue_casted = unitValue as (int32)
        RenderNodeExtender.setRotation_serialize(peer_casted, rotation_casted, unitValue_casted)
        return
    }
    public static setTransform(peer: RenderNode, transform: Matrix4): void {
        const peer_casted = peer as (RenderNode)
        const transform_casted = transform as (Matrix4)
        RenderNodeExtender.setTransform_serialize(peer_casted, transform_casted)
        return
    }
    public static setShadowColor(peer: RenderNode, shadowColor: number): void {
        const peer_casted = peer as (RenderNode)
        const shadowColor_casted = shadowColor as (number)
        RenderNodeExtender.setShadowColor_serialize(peer_casted, shadowColor_casted)
        return
    }
    public static setShadowOffset(peer: RenderNode, shadowOffset: Vector2, unitValue: int32): void {
        const peer_casted = peer as (RenderNode)
        const shadowOffset_casted = shadowOffset as (Vector2)
        const unitValue_casted = unitValue as (int32)
        RenderNodeExtender.setShadowOffset_serialize(peer_casted, shadowOffset_casted, unitValue_casted)
        return
    }
    public static setLabel(peer: RenderNode, label: string): void {
        const peer_casted = peer as (RenderNode)
        const label_casted = label as (string)
        RenderNodeExtender.setLabel_serialize(peer_casted, label_casted)
        return
    }
    public static setShadowAlpha(peer: RenderNode, shadowAlpha: number): void {
        const peer_casted = peer as (RenderNode)
        const shadowAlpha_casted = shadowAlpha as (number)
        RenderNodeExtender.setShadowAlpha_serialize(peer_casted, shadowAlpha_casted)
        return
    }
    public static setShadowElevation(peer: RenderNode, shadowElevation: number): void {
        const peer_casted = peer as (RenderNode)
        const shadowElevation_casted = shadowElevation as (number)
        RenderNodeExtender.setShadowElevation_serialize(peer_casted, shadowElevation_casted)
        return
    }
    public static setShadowRadius(peer: RenderNode, shadowRadius: number): void {
        const peer_casted = peer as (RenderNode)
        const shadowRadius_casted = shadowRadius as (number)
        RenderNodeExtender.setShadowRadius_serialize(peer_casted, shadowRadius_casted)
        return
    }
    public static setBorderStyle(peer: RenderNode, borderStyle: NodeEdgeStyles): void {
        const peer_casted = peer as (RenderNode)
        const borderStyle_casted = borderStyle as (NodeEdgeStyles)
        RenderNodeExtender.setBorderStyle_serialize(peer_casted, borderStyle_casted)
        return
    }
    public static setBorderWidth(peer: RenderNode, borderWidth: EdgeNumber, unitValue: int32): void {
        const peer_casted = peer as (RenderNode)
        const borderWidth_casted = borderWidth as (EdgeNumber)
        const unitValue_casted = unitValue as (int32)
        RenderNodeExtender.setBorderWidth_serialize(peer_casted, borderWidth_casted, unitValue_casted)
        return
    }
    public static setBorderColor(peer: RenderNode, borderColor: EdgeNumber): void {
        const peer_casted = peer as (RenderNode)
        const borderColor_casted = borderColor as (EdgeNumber)
        RenderNodeExtender.setBorderColor_serialize(peer_casted, borderColor_casted)
        return
    }
    public static setBorderRadius(peer: RenderNode, borderRadius: BorderRadiuses_graphics, unitValue: int32): void {
        const peer_casted = peer as (RenderNode)
        const borderRadius_casted = borderRadius as (BorderRadiuses_graphics)
        const unitValue_casted = unitValue as (int32)
        RenderNodeExtender.setBorderRadius_serialize(peer_casted, borderRadius_casted, unitValue_casted)
        return
    }
    public static setMarkNodeGroup(peer: RenderNode, markNodeGroup: boolean): void {
        const peer_casted = peer as (RenderNode)
        const markNodeGroup_casted = markNodeGroup as (boolean)
        RenderNodeExtender.setMarkNodeGroup_serialize(peer_casted, markNodeGroup_casted)
        return
    }
    public static setRectMask(peer: RenderNode, rect: common2D.Rect, fillColor: number, strokeColor: number, strokeWidth: number): void {
        const peer_casted = peer as (RenderNode)
        const rect_casted = rect as (common2D.Rect)
        const fillColor_casted = fillColor as (number)
        const strokeColor_casted = strokeColor as (number)
        const strokeWidth_casted = strokeWidth as (number)
        RenderNodeExtender.setRectMask_serialize(peer_casted, rect_casted, fillColor_casted, strokeColor_casted, strokeWidth_casted)
        return
    }
    public static setCircleMask(peer: RenderNode, circle: Circle, fillColor: number, strokeColor: number, strokeWidth: number): void {
        const peer_casted = peer as (RenderNode)
        const circle_casted = circle as (Circle)
        const fillColor_casted = fillColor as (number)
        const strokeColor_casted = strokeColor as (number)
        const strokeWidth_casted = strokeWidth as (number)
        RenderNodeExtender.setCircleMask_serialize(peer_casted, circle_casted, fillColor_casted, strokeColor_casted, strokeWidth_casted)
        return
    }
    public static setRoundRectMask(peer: RenderNode, roundRect: RoundRect, fillColor: number, strokeColor: number, strokeWidth: number): void {
        const peer_casted = peer as (RenderNode)
        const roundRect_casted = roundRect as (RoundRect)
        const fillColor_casted = fillColor as (number)
        const strokeColor_casted = strokeColor as (number)
        const strokeWidth_casted = strokeWidth as (number)
        RenderNodeExtender.setRoundRectMask_serialize(peer_casted, roundRect_casted, fillColor_casted, strokeColor_casted, strokeWidth_casted)
        return
    }
    public static setOvalMask(peer: RenderNode, rect: common2D.Rect, fillColor: number, strokeColor: number, strokeWidth: number): void {
        const peer_casted = peer as (RenderNode)
        const rect_casted = rect as (common2D.Rect)
        const fillColor_casted = fillColor as (number)
        const strokeColor_casted = strokeColor as (number)
        const strokeWidth_casted = strokeWidth as (number)
        RenderNodeExtender.setOvalMask_serialize(peer_casted, rect_casted, fillColor_casted, strokeColor_casted, strokeWidth_casted)
        return
    }
    public static setPath(peer: RenderNode, path: CommandPath, fillColor: number, strokeColor: number, strokeWidth: number): void {
        const peer_casted = peer as (RenderNode)
        const path_casted = path as (CommandPath)
        const fillColor_casted = fillColor as (number)
        const strokeColor_casted = strokeColor as (number)
        const strokeWidth_casted = strokeWidth as (number)
        RenderNodeExtender.setPath_serialize(peer_casted, path_casted, fillColor_casted, strokeColor_casted, strokeWidth_casted)
        return
    }
    public static setRectClip(peer: RenderNode, rect: common2D.Rect): void {
        const peer_casted = peer as (RenderNode)
        const rect_casted = rect as (common2D.Rect)
        RenderNodeExtender.setRectClip_serialize(peer_casted, rect_casted)
        return
    }
    public static setCircleClip(peer: RenderNode, circle: Circle): void {
        const peer_casted = peer as (RenderNode)
        const circle_casted = circle as (Circle)
        RenderNodeExtender.setCircleClip_serialize(peer_casted, circle_casted)
        return
    }
    public static setRoundRectClip(peer: RenderNode, roundRect: RoundRect): void {
        const peer_casted = peer as (RenderNode)
        const roundRect_casted = roundRect as (RoundRect)
        RenderNodeExtender.setRoundRectClip_serialize(peer_casted, roundRect_casted)
        return
    }
    public static setOvalClip(peer: RenderNode, rect: common2D.Rect): void {
        const peer_casted = peer as (RenderNode)
        const rect_casted = rect as (common2D.Rect)
        RenderNodeExtender.setOvalClip_serialize(peer_casted, rect_casted)
        return
    }
    public static setPathClip(peer: RenderNode, path: CommandPath): void {
        const peer_casted = peer as (RenderNode)
        const path_casted = path as (CommandPath)
        RenderNodeExtender.setPathClip_serialize(peer_casted, path_casted)
        return
    }
    public static appendChild(peer: RenderNode, node: RenderNode): int32 {
        const peer_casted = peer as (RenderNode)
        const node_casted = node as (RenderNode)
        return RenderNodeExtender.appendChild_serialize(peer_casted, node_casted)
    }
    public static insertChildAfter(peer: RenderNode, child: RenderNode, sibling: RenderNode): int32 {
        const peer_casted = peer as (RenderNode)
        const child_casted = child as (RenderNode)
        const sibling_casted = sibling as (RenderNode)
        return RenderNodeExtender.insertChildAfter_serialize(peer_casted, child_casted, sibling_casted)
    }
    public static removeChild(peer: RenderNode, node: RenderNode): void {
        const peer_casted = peer as (RenderNode)
        const node_casted = node as (RenderNode)
        RenderNodeExtender.removeChild_serialize(peer_casted, node_casted)
        return
    }
    public static clearChildren(peer: RenderNode): void {
        const peer_casted = peer as (RenderNode)
        RenderNodeExtender.clearChildren_serialize(peer_casted)
        return
    }
    public static invalidate(peer: RenderNode): void {
        const peer_casted = peer as (RenderNode)
        RenderNodeExtender.invalidate_serialize(peer_casted)
        return
    }
}
export class RenderServiceNode {
    static getNodeId_serialize(nodeId: string): int32 {
        const retval  = ArkUIGeneratedNativeModule._RenderServiceNode_getNodeId(nodeId)
        return retval
    }
    public static getNodeId(nodeId: string): int32 {
        const nodeId_casted = nodeId as (string)
        return RenderServiceNode.getNodeId_serialize(nodeId_casted)
    }
}
export class RestrictedWorkerInternal {
    public static fromPtr(ptr: KPointer): RestrictedWorker {
        return new RestrictedWorker(false, false, ptr)
    }
}
export class RestrictedWorker implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get onexit(): RestrictedWorker_onexit_Callback | undefined {
        return this.getOnexit()
    }
    set onexit(onexit: RestrictedWorker_onexit_Callback | undefined) {
        const onexit_NonNull  = (onexit as RestrictedWorker_onexit_Callback)
        this.setOnexit(onexit_NonNull)
    }
    get onerror(): RestrictedWorker_onerror_Callback | undefined {
        return this.getOnerror()
    }
    set onerror(onerror: RestrictedWorker_onerror_Callback | undefined) {
        const onerror_NonNull  = (onerror as RestrictedWorker_onerror_Callback)
        this.setOnerror(onerror_NonNull)
    }
    get onmessage(): RestrictedWorker_onmessage_Callback | undefined {
        return this.getOnmessage()
    }
    set onmessage(onmessage: RestrictedWorker_onmessage_Callback | undefined) {
        const onmessage_NonNull  = (onmessage as RestrictedWorker_onmessage_Callback)
        this.setOnmessage(onmessage_NonNull)
    }
    get onmessageerror(): RestrictedWorker_onmessage_Callback | undefined {
        return this.getOnmessageerror()
    }
    set onmessageerror(onmessageerror: RestrictedWorker_onmessage_Callback | undefined) {
        const onmessageerror_NonNull  = (onmessageerror as RestrictedWorker_onmessage_Callback)
        this.setOnmessageerror(onmessageerror_NonNull)
    }
    constructor(_0: boolean, _1: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, RestrictedWorker.getFinalizer())
    }
    constructor(scriptURL: string, options?: WorkerOptions) {
        this(false, false, RestrictedWorker.construct(scriptURL, options))
    }
    static construct(scriptURL: string, options?: WorkerOptions): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            WorkerOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._RestrictedWorker_construct(scriptURL, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._RestrictedWorker_getFinalizer()
    }
    public postMessage(message: Object, transfer: Array<ArrayBuffer>): void {
        const message_casted = message as (Object)
        const transfer_casted = transfer as (Array<ArrayBuffer>)
        this.postMessage0_serialize(message_casted, transfer_casted)
        return
    }
    public postMessage(message: Object, options?: PostMessageOptions): void {
        const message_casted = message as (Object)
        const options_casted = options as (PostMessageOptions | undefined)
        this.postMessage1_serialize(message_casted, options_casted)
        return
    }
    public postMessageWithSharedSendable(message: Object, transfer?: Array<ArrayBuffer>): void {
        const message_casted = message as (Object)
        const transfer_casted = transfer as (Array<ArrayBuffer> | undefined)
        this.postMessageWithSharedSendable_serialize(message_casted, transfer_casted)
        return
    }
    public on(Type: string, listener: WorkerEventListener): void {
        const Type_casted = Type as (string)
        const listener_casted = listener as (WorkerEventListener)
        this.on_serialize(Type_casted, listener_casted)
        return
    }
    public once(Type: string, listener: WorkerEventListener): void {
        const Type_casted = Type as (string)
        const listener_casted = listener as (WorkerEventListener)
        this.once_serialize(Type_casted, listener_casted)
        return
    }
    public off(Type: string, listener?: WorkerEventListener): void {
        const Type_casted = Type as (string)
        const listener_casted = listener as (WorkerEventListener | undefined)
        this.off_serialize(Type_casted, listener_casted)
        return
    }
    public terminate(): void {
        this.terminate_serialize()
        return
    }
    public addEventListener(Type: string, listener: WorkerEventListener): void {
        const Type_casted = Type as (string)
        const listener_casted = listener as (WorkerEventListener)
        this.addEventListener_serialize(Type_casted, listener_casted)
        return
    }
    public dispatchEvent(event: Event): boolean {
        const event_casted = event as (Event)
        return this.dispatchEvent_serialize(event_casted)
    }
    public removeEventListener(Type: string, callback_?: WorkerEventListener): void {
        const Type_casted = Type as (string)
        const callback__casted = callback_ as (WorkerEventListener | undefined)
        this.removeEventListener_serialize(Type_casted, callback__casted)
        return
    }
    public removeAllListener(): void {
        this.removeAllListener_serialize()
        return
    }
    public registerGlobalCallObject(instanceName: string, globalCallObject: Object): void {
        const instanceName_casted = instanceName as (string)
        const globalCallObject_casted = globalCallObject as (Object)
        this.registerGlobalCallObject_serialize(instanceName_casted, globalCallObject_casted)
        return
    }
    public unregisterGlobalCallObject(instanceName?: string): void {
        const instanceName_casted = instanceName as (string | undefined)
        this.unregisterGlobalCallObject_serialize(instanceName_casted)
        return
    }
    private getOnexit(): RestrictedWorker_onexit_Callback | undefined {
        return this.getOnexit_serialize()
    }
    private setOnexit(onexit: RestrictedWorker_onexit_Callback | undefined): void {
        const onexit_casted = onexit as (RestrictedWorker_onexit_Callback | undefined)
        this.setOnexit_serialize(onexit_casted)
        return
    }
    private getOnerror(): RestrictedWorker_onerror_Callback | undefined {
        return this.getOnerror_serialize()
    }
    private setOnerror(onerror: RestrictedWorker_onerror_Callback | undefined): void {
        const onerror_casted = onerror as (RestrictedWorker_onerror_Callback | undefined)
        this.setOnerror_serialize(onerror_casted)
        return
    }
    private getOnmessage(): RestrictedWorker_onmessage_Callback | undefined {
        return this.getOnmessage_serialize()
    }
    private setOnmessage(onmessage: RestrictedWorker_onmessage_Callback | undefined): void {
        const onmessage_casted = onmessage as (RestrictedWorker_onmessage_Callback | undefined)
        this.setOnmessage_serialize(onmessage_casted)
        return
    }
    private getOnmessageerror(): RestrictedWorker_onmessage_Callback | undefined {
        return this.getOnmessageerror_serialize()
    }
    private setOnmessageerror(onmessageerror: RestrictedWorker_onmessage_Callback | undefined): void {
        const onmessageerror_casted = onmessageerror as (RestrictedWorker_onmessage_Callback | undefined)
        this.setOnmessageerror_serialize(onmessageerror_casted)
        return
    }
    postMessage0_serialize(message: Object, transfer: Array<ArrayBuffer>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(message)
        thisSerializer.writeInt32((transfer.length).toInt())
        for (let transferCounterI = 0; transferCounterI < transfer.length; transferCounterI++) {
            const transferTmpElement : ArrayBuffer = transfer[transferCounterI]
            thisSerializer.writeBuffer(transferTmpElement)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_postMessage0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    postMessage1_serialize(message: Object, options?: PostMessageOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(message)
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            PostMessageOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_postMessage1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    postMessageWithSharedSendable_serialize(message: Object, transfer?: Array<ArrayBuffer>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(message)
        if (transfer !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const transferTmpValue  = transfer!
            thisSerializer.writeInt32((transferTmpValue.length).toInt())
            for (let transferTmpValueCounterI = 0; transferTmpValueCounterI < transferTmpValue.length; transferTmpValueCounterI++) {
                const transferTmpValueTmpElement : ArrayBuffer = transferTmpValue[transferTmpValueCounterI]
                thisSerializer.writeBuffer(transferTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_postMessageWithSharedSendable(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    on_serialize(Type: string, listener: WorkerEventListener): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(listener)
        ArkUIGeneratedNativeModule._RestrictedWorker_on(this.peer!.ptr, Type, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    once_serialize(Type: string, listener: WorkerEventListener): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(listener)
        ArkUIGeneratedNativeModule._RestrictedWorker_once(this.peer!.ptr, Type, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    off_serialize(Type: string, listener?: WorkerEventListener): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (listener !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const listenerTmpValue  = listener!
            thisSerializer.holdAndWriteCallback(listenerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_off(this.peer!.ptr, Type, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    terminate_serialize(): void {
        ArkUIGeneratedNativeModule._RestrictedWorker_terminate(this.peer!.ptr)
    }
    addEventListener_serialize(Type: string, listener: WorkerEventListener): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(listener)
        ArkUIGeneratedNativeModule._RestrictedWorker_addEventListener(this.peer!.ptr, Type, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    dispatchEvent_serialize(event: Event): boolean {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Event_serializer.write(thisSerializer, event)
        const retval  = ArkUIGeneratedNativeModule._RestrictedWorker_dispatchEvent(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    removeEventListener_serialize(Type: string, callback_?: WorkerEventListener): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (callback_ !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const callback_TmpValue  = callback_!
            thisSerializer.holdAndWriteCallback(callback_TmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_removeEventListener(this.peer!.ptr, Type, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    removeAllListener_serialize(): void {
        ArkUIGeneratedNativeModule._RestrictedWorker_removeAllListener(this.peer!.ptr)
    }
    registerGlobalCallObject_serialize(instanceName: string, globalCallObject: Object): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(globalCallObject)
        ArkUIGeneratedNativeModule._RestrictedWorker_registerGlobalCallObject(this.peer!.ptr, instanceName, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    unregisterGlobalCallObject_serialize(instanceName?: string): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (instanceName !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const instanceNameTmpValue  = instanceName!
            thisSerializer.writeString(instanceNameTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_unregisterGlobalCallObject(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnexit_serialize(): RestrictedWorker_onexit_Callback | undefined {
        const retval  = ArkUIGeneratedNativeModule._RestrictedWorker_getOnexit(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : RestrictedWorker_onexit_Callback | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const buffer_BufResource : CallbackResource = retvalDeserializer.readCallbackResource()
            const buffer_BufCall : KPointer = retvalDeserializer.readPointer()
            const buffer_BufCallSync : KPointer = retvalDeserializer.readPointer()
            buffer = (code: number):void => {
                const buffer_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                buffer_BufArgsSerializer.writeInt32(buffer_BufResource.resourceId);
                buffer_BufArgsSerializer.writePointer(buffer_BufCall);
                buffer_BufArgsSerializer.writePointer(buffer_BufCallSync);
                buffer_BufArgsSerializer.writeNumber(code);
                InteropNativeModule._CallCallbackSync(10, -2095497263, buffer_BufArgsSerializer.asBuffer(), buffer_BufArgsSerializer.length());
                buffer_BufArgsSerializer.release();
                return;
            }
        }
        const returnResult : RestrictedWorker_onexit_Callback | undefined = buffer
        return returnResult
    }
    private setOnexit_serialize(onexit: RestrictedWorker_onexit_Callback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (onexit !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const onexitTmpValue  = onexit!
            thisSerializer.holdAndWriteCallback(onexitTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_setOnexit(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnerror_serialize(): RestrictedWorker_onerror_Callback | undefined {
        const retval  = ArkUIGeneratedNativeModule._RestrictedWorker_getOnerror(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : RestrictedWorker_onerror_Callback | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const buffer_BufResource : CallbackResource = retvalDeserializer.readCallbackResource()
            const buffer_BufCall : KPointer = retvalDeserializer.readPointer()
            const buffer_BufCallSync : KPointer = retvalDeserializer.readPointer()
            buffer = (ev: ErrorEvent):void => {
                const buffer_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                buffer_BufArgsSerializer.writeInt32(buffer_BufResource.resourceId);
                buffer_BufArgsSerializer.writePointer(buffer_BufCall);
                buffer_BufArgsSerializer.writePointer(buffer_BufCallSync);
                ErrorEvent_serializer.write(buffer_BufArgsSerializer, ev);
                InteropNativeModule._CallCallbackSync(10, -1213708823, buffer_BufArgsSerializer.asBuffer(), buffer_BufArgsSerializer.length());
                buffer_BufArgsSerializer.release();
                return;
            }
        }
        const returnResult : RestrictedWorker_onerror_Callback | undefined = buffer
        return returnResult
    }
    private setOnerror_serialize(onerror: RestrictedWorker_onerror_Callback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (onerror !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const onerrorTmpValue  = onerror!
            thisSerializer.holdAndWriteCallback(onerrorTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_setOnerror(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnmessage_serialize(): RestrictedWorker_onmessage_Callback | undefined {
        const retval  = ArkUIGeneratedNativeModule._RestrictedWorker_getOnmessage(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : RestrictedWorker_onmessage_Callback | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const buffer_BufResource : CallbackResource = retvalDeserializer.readCallbackResource()
            const buffer_BufCall : KPointer = retvalDeserializer.readPointer()
            const buffer_BufCallSync : KPointer = retvalDeserializer.readPointer()
            buffer = (event: MessageEvents):void => {
                const buffer_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                buffer_BufArgsSerializer.writeInt32(buffer_BufResource.resourceId);
                buffer_BufArgsSerializer.writePointer(buffer_BufCall);
                buffer_BufArgsSerializer.writePointer(buffer_BufCallSync);
                MessageEvents_serializer.write(buffer_BufArgsSerializer, event);
                InteropNativeModule._CallCallbackSync(10, 1614214490, buffer_BufArgsSerializer.asBuffer(), buffer_BufArgsSerializer.length());
                buffer_BufArgsSerializer.release();
                return;
            }
        }
        const returnResult : RestrictedWorker_onmessage_Callback | undefined = buffer
        return returnResult
    }
    private setOnmessage_serialize(onmessage: RestrictedWorker_onmessage_Callback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (onmessage !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const onmessageTmpValue  = onmessage!
            thisSerializer.holdAndWriteCallback(onmessageTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_setOnmessage(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnmessageerror_serialize(): RestrictedWorker_onmessage_Callback | undefined {
        const retval  = ArkUIGeneratedNativeModule._RestrictedWorker_getOnmessageerror(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : RestrictedWorker_onmessage_Callback | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const buffer_BufResource : CallbackResource = retvalDeserializer.readCallbackResource()
            const buffer_BufCall : KPointer = retvalDeserializer.readPointer()
            const buffer_BufCallSync : KPointer = retvalDeserializer.readPointer()
            buffer = (event: MessageEvents):void => {
                const buffer_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                buffer_BufArgsSerializer.writeInt32(buffer_BufResource.resourceId);
                buffer_BufArgsSerializer.writePointer(buffer_BufCall);
                buffer_BufArgsSerializer.writePointer(buffer_BufCallSync);
                MessageEvents_serializer.write(buffer_BufArgsSerializer, event);
                InteropNativeModule._CallCallbackSync(10, 1614214490, buffer_BufArgsSerializer.asBuffer(), buffer_BufArgsSerializer.length());
                buffer_BufArgsSerializer.release();
                return;
            }
        }
        const returnResult : RestrictedWorker_onmessage_Callback | undefined = buffer
        return returnResult
    }
    private setOnmessageerror_serialize(onmessageerror: RestrictedWorker_onmessage_Callback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (onmessageerror !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const onmessageerrorTmpValue  = onmessageerror!
            thisSerializer.holdAndWriteCallback(onmessageerrorTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_setOnmessageerror(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class RouterExtender {
    static push_serialize(jsView: KPointer, url: string, recover?: boolean, finishCallback?: RouterFinishCallback): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (recover !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const recoverTmpValue  = recover!
            thisSerializer.writeBoolean(recoverTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (finishCallback !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const finishCallbackTmpValue  = finishCallback!
            thisSerializer.holdAndWriteCallback(finishCallbackTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._RouterExtender_push(jsView, url, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static replace_serialize(jsView: KPointer, url: string, recover?: boolean, enterFinishCallback?: RouterFinishCallback): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (recover !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const recoverTmpValue  = recover!
            thisSerializer.writeBoolean(recoverTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (enterFinishCallback !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const enterFinishCallbackTmpValue  = enterFinishCallback!
            thisSerializer.holdAndWriteCallback(enterFinishCallbackTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._RouterExtender_replace(jsView, url, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static moveCommonUnderPageNode_serialize(commonNode: KPointer, pageNode: KPointer): void {
        ArkUIGeneratedNativeModule._RouterExtender_moveCommonUnderPageNode(commonNode, pageNode)
    }
    static back_serialize(): void {
        ArkUIGeneratedNativeModule._RouterExtender_back()
    }
    static backWithOptions_serialize(url: string, params?: Object): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (params !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const paramsTmpValue  = params!
            thisSerializer.holdAndWriteObject(paramsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RouterExtender_backWithOptions(url, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static runPage_serialize(jsView: KPointer, url: string, recover?: boolean, finishCallback?: RouterFinishCallback): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (recover !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const recoverTmpValue  = recover!
            thisSerializer.writeBoolean(recoverTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (finishCallback !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const finishCallbackTmpValue  = finishCallback!
            thisSerializer.holdAndWriteCallback(finishCallbackTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._RouterExtender_runPage(jsView, url, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static clear_serialize(): void {
        ArkUIGeneratedNativeModule._RouterExtender_clear()
    }
    static showAlertBeforeBackPage_serialize(message: string): void {
        ArkUIGeneratedNativeModule._RouterExtender_showAlertBeforeBackPage(message)
    }
    static hideAlertBeforeBackPage_serialize(): void {
        ArkUIGeneratedNativeModule._RouterExtender_hideAlertBeforeBackPage()
    }
    static pushNamedRoute0_serialize(jsView: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        PageRouterOptions_serializer.write(thisSerializer, options)
        if (finishCallback !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const finishCallbackTmpValue  = finishCallback!
            thisSerializer.holdAndWriteCallback(finishCallbackTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._RouterExtender_pushNamedRoute0(jsView, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static pushNamedRoute1_serialize(jsView: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback, callback_?: AsyncCallback<void>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        PageRouterOptions_serializer.write(thisSerializer, options)
        if (finishCallback !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const finishCallbackTmpValue  = finishCallback!
            thisSerializer.holdAndWriteCallback(finishCallbackTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (callback_ !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const callback_TmpValue  = callback_!
            thisSerializer.holdAndWriteCallback(callback_TmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RouterExtender_pushNamedRoute1(jsView, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static replaceNamedRoute0_serialize(jsView: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback): Promise<void> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        PageRouterOptions_serializer.write(thisSerializer, options)
        if (finishCallback !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const finishCallbackTmpValue  = finishCallback!
            thisSerializer.holdAndWriteCallback(finishCallbackTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._RouterExtender_replaceNamedRoute0(jsView, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static replaceNamedRoute1_serialize(jsView: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback, callback_?: AsyncCallback<void>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        PageRouterOptions_serializer.write(thisSerializer, options)
        if (finishCallback !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const finishCallbackTmpValue  = finishCallback!
            thisSerializer.holdAndWriteCallback(finishCallbackTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (callback_ !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const callback_TmpValue  = callback_!
            thisSerializer.holdAndWriteCallback(callback_TmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RouterExtender_replaceNamedRoute1(jsView, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    static createDynamic_serialize(url: string, recover?: boolean): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (recover !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const recoverTmpValue  = recover!
            thisSerializer.writeBoolean(recoverTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._RouterExtender_createDynamic(url, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static pushDynamic_serialize(pageNode: KPointer, url: string, recover?: boolean, finishCallback?: RouterFinishCallback): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (recover !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const recoverTmpValue  = recover!
            thisSerializer.writeBoolean(recoverTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (finishCallback !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const finishCallbackTmpValue  = finishCallback!
            thisSerializer.holdAndWriteCallback(finishCallbackTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._RouterExtender_pushDynamic(pageNode, url, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static replaceDynamic_serialize(pageNode: KPointer, url: string, recover?: boolean, finishCallback?: RouterFinishCallback): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (recover !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const recoverTmpValue  = recover!
            thisSerializer.writeBoolean(recoverTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (finishCallback !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const finishCallbackTmpValue  = finishCallback!
            thisSerializer.holdAndWriteCallback(finishCallbackTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = ArkUIGeneratedNativeModule._RouterExtender_replaceDynamic(pageNode, url, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    public static push(jsView: KPointer, url: string, recover?: boolean, finishCallback?: RouterFinishCallback): KPointer {
        const jsView_casted = jsView as (KPointer)
        const url_casted = url as (string)
        const recover_casted = recover as (boolean | undefined)
        const finishCallback_casted = finishCallback as (RouterFinishCallback | undefined)
        return RouterExtender.push_serialize(jsView_casted, url_casted, recover_casted, finishCallback_casted)
    }
    public static replace(jsView: KPointer, url: string, recover?: boolean, enterFinishCallback?: RouterFinishCallback): KPointer {
        const jsView_casted = jsView as (KPointer)
        const url_casted = url as (string)
        const recover_casted = recover as (boolean | undefined)
        const enterFinishCallback_casted = enterFinishCallback as (RouterFinishCallback | undefined)
        return RouterExtender.replace_serialize(jsView_casted, url_casted, recover_casted, enterFinishCallback_casted)
    }
    public static moveCommonUnderPageNode(commonNode: KPointer, pageNode: KPointer): void {
        const commonNode_casted = commonNode as (KPointer)
        const pageNode_casted = pageNode as (KPointer)
        RouterExtender.moveCommonUnderPageNode_serialize(commonNode_casted, pageNode_casted)
        return
    }
    public static back(): void {
        RouterExtender.back_serialize()
        return
    }
    public static backWithOptions(url: string, params?: Object): void {
        const url_casted = url as (string)
        const params_casted = params as (Object | undefined)
        RouterExtender.backWithOptions_serialize(url_casted, params_casted)
        return
    }
    public static runPage(jsView: KPointer, url: string, recover?: boolean, finishCallback?: RouterFinishCallback): KPointer {
        const jsView_casted = jsView as (KPointer)
        const url_casted = url as (string)
        const recover_casted = recover as (boolean | undefined)
        const finishCallback_casted = finishCallback as (RouterFinishCallback | undefined)
        return RouterExtender.runPage_serialize(jsView_casted, url_casted, recover_casted, finishCallback_casted)
    }
    public static clear(): void {
        RouterExtender.clear_serialize()
        return
    }
    public static showAlertBeforeBackPage(message: string): void {
        const message_casted = message as (string)
        RouterExtender.showAlertBeforeBackPage_serialize(message_casted)
        return
    }
    public static hideAlertBeforeBackPage(): void {
        RouterExtender.hideAlertBeforeBackPage_serialize()
        return
    }
    public static pushNamedRoute(jsView: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback): Promise<void> {
        const jsView_casted = jsView as (KPointer)
        const options_casted = options as (PageRouterOptions)
        const finishCallback_casted = finishCallback as (RouterFinishCallback | undefined)
        return RouterExtender.pushNamedRoute0_serialize(jsView_casted, options_casted, finishCallback_casted)
    }
    public static pushNamedRoute(jsView: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback, callback_?: AsyncCallback<void>): void {
        const jsView_casted = jsView as (KPointer)
        const options_casted = options as (PageRouterOptions)
        const finishCallback_casted = finishCallback as (RouterFinishCallback | undefined)
        const callback__casted = callback_ as (AsyncCallback<void> | undefined)
        RouterExtender.pushNamedRoute1_serialize(jsView_casted, options_casted, finishCallback_casted, callback__casted)
        return
    }
    public static replaceNamedRoute(jsView: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback): Promise<void> {
        const jsView_casted = jsView as (KPointer)
        const options_casted = options as (PageRouterOptions)
        const finishCallback_casted = finishCallback as (RouterFinishCallback | undefined)
        return RouterExtender.replaceNamedRoute0_serialize(jsView_casted, options_casted, finishCallback_casted)
    }
    public static replaceNamedRoute(jsView: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback, callback_?: AsyncCallback<void>): void {
        const jsView_casted = jsView as (KPointer)
        const options_casted = options as (PageRouterOptions)
        const finishCallback_casted = finishCallback as (RouterFinishCallback | undefined)
        const callback__casted = callback_ as (AsyncCallback<void> | undefined)
        RouterExtender.replaceNamedRoute1_serialize(jsView_casted, options_casted, finishCallback_casted, callback__casted)
        return
    }
    public static createDynamic(url: string, recover?: boolean): KPointer {
        const url_casted = url as (string)
        const recover_casted = recover as (boolean | undefined)
        return RouterExtender.createDynamic_serialize(url_casted, recover_casted)
    }
    public static pushDynamic(pageNode: KPointer, url: string, recover?: boolean, finishCallback?: RouterFinishCallback): KPointer {
        const pageNode_casted = pageNode as (KPointer)
        const url_casted = url as (string)
        const recover_casted = recover as (boolean | undefined)
        const finishCallback_casted = finishCallback as (RouterFinishCallback | undefined)
        return RouterExtender.pushDynamic_serialize(pageNode_casted, url_casted, recover_casted, finishCallback_casted)
    }
    public static replaceDynamic(pageNode: KPointer, url: string, recover?: boolean, finishCallback?: RouterFinishCallback): KPointer {
        const pageNode_casted = pageNode as (KPointer)
        const url_casted = url as (string)
        const recover_casted = recover as (boolean | undefined)
        const finishCallback_casted = finishCallback as (RouterFinishCallback | undefined)
        return RouterExtender.replaceDynamic_serialize(pageNode_casted, url_casted, recover_casted, finishCallback_casted)
    }
}
export class ScreenshotService {
    static requestScreenshot_serialize(target: string, name: string): boolean {
        const retval  = ArkUIGeneratedNativeModule._ScreenshotService_requestScreenshot(target, name)
        return retval
    }
    public static requestScreenshot(target: string, name: string): boolean {
        const target_casted = target as (string)
        const name_casted = name as (string)
        return ScreenshotService.requestScreenshot_serialize(target_casted, name_casted)
    }
}
export class SelectExtender {
    static setDivider_serialize(node: KPointer, options?: DividerOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            DividerOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectExtender_setDivider(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static setDivider(node: KPointer, options?: DividerOptions): void {
        const node_casted = node as (KPointer)
        const options_casted = options as (DividerOptions | undefined)
        SelectExtender.setDivider_serialize(node_casted, options_casted)
        return
    }
}
export class StateStylesOps {
    static onStateStyleChange_serialize(node: KPointer, stateStyleChange: Callback_StateStylesChange, allState: int32): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(stateStyleChange)
        ArkUIGeneratedNativeModule._StateStylesOps_onStateStyleChange(node, thisSerializer.asBuffer(), thisSerializer.length(), allState)
        thisSerializer.release()
    }
    public static onStateStyleChange(node: KPointer, stateStyleChange: Callback_StateStylesChange, allState: int32): void {
        const node_casted = node as (KPointer)
        const stateStyleChange_casted = stateStyleChange as (Callback_StateStylesChange)
        const allState_casted = allState as (int32)
        StateStylesOps.onStateStyleChange_serialize(node_casted, stateStyleChange_casted, allState_casted)
        return
    }
}
export class SystemOps {
    static StartFrame_serialize(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SystemOps_StartFrame()
        return retval
    }
    static EndFrame_serialize(root: KPointer): void {
        ArkUIGeneratedNativeModule._SystemOps_EndFrame(root)
    }
    static syncInstanceId_serialize(instanceId: int32): void {
        ArkUIGeneratedNativeModule._SystemOps_syncInstanceId(instanceId)
    }
    static restoreInstanceId_serialize(): void {
        ArkUIGeneratedNativeModule._SystemOps_restoreInstanceId()
    }
    static getResourceId_serialize(bundleName: string, moduleName: string, params: Array<string>): int32 {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((params.length).toInt())
        for (let paramsCounterI = 0; paramsCounterI < params.length; paramsCounterI++) {
            const paramsTmpElement : string = params[paramsCounterI]
            thisSerializer.writeString(paramsTmpElement)
        }
        const retval  = ArkUIGeneratedNativeModule._SystemOps_getResourceId(bundleName, moduleName, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static resourceManagerReset_serialize(): void {
        ArkUIGeneratedNativeModule._SystemOps_resourceManagerReset()
    }
    static setFrameCallback_serialize(onFrameCallback: ((value0: number) => void), onIdleCallback: ((value0: number) => void), delayTime: number): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onFrameCallback)
        thisSerializer.holdAndWriteCallback(onIdleCallback)
        ArkUIGeneratedNativeModule._SystemOps_setFrameCallback(thisSerializer.asBuffer(), thisSerializer.length(), delayTime)
        thisSerializer.release()
    }
    static colorMetricsResourceColor_serialize(color: Resource): Array<number> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Resource_serializer.write(thisSerializer, color)
        const retval  = ArkUIGeneratedNativeModule._SystemOps_colorMetricsResourceColor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength : int32 = retvalDeserializer.readInt32()
        let buffer : Array<number> = new Array<number>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = (retvalDeserializer.readNumber() as number)
        }
        const returnResult : Array<number> = buffer
        return returnResult
    }
    static resourceToLengthMetrics_serialize(res: Resource): LengthMetricsCustom {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Resource_serializer.write(thisSerializer, res)
        const retval  = ArkUIGeneratedNativeModule._SystemOps_resourceToLengthMetrics(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : LengthMetricsCustom = LengthMetricsCustom_serializer.read(retvalDeserializer)
        return returnResult
    }
    static blendColorByColorMetrics_serialize(color: number, overlayColor: number): Array<number> {
        const retval  = ArkUIGeneratedNativeModule._SystemOps_blendColorByColorMetrics(color, overlayColor)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength : int32 = retvalDeserializer.readInt32()
        let buffer : Array<number> = new Array<number>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = (retvalDeserializer.readNumber() as number)
        }
        const returnResult : Array<number> = buffer
        return returnResult
    }
    public static StartFrame(): KPointer {
        return SystemOps.StartFrame_serialize()
    }
    public static EndFrame(root: KPointer): void {
        const root_casted = root as (KPointer)
        SystemOps.EndFrame_serialize(root_casted)
        return
    }
    public static syncInstanceId(instanceId: int32): void {
        const instanceId_casted = instanceId as (int32)
        SystemOps.syncInstanceId_serialize(instanceId_casted)
        return
    }
    public static restoreInstanceId(): void {
        SystemOps.restoreInstanceId_serialize()
        return
    }
    public static getResourceId(bundleName: string, moduleName: string, params: Array<string>): int32 {
        const bundleName_casted = bundleName as (string)
        const moduleName_casted = moduleName as (string)
        const params_casted = params as (Array<string>)
        return SystemOps.getResourceId_serialize(bundleName_casted, moduleName_casted, params_casted)
    }
    public static resourceManagerReset(): void {
        SystemOps.resourceManagerReset_serialize()
        return
    }
    public static setFrameCallback(onFrameCallback: ((value0: number) => void), onIdleCallback: ((value0: number) => void), delayTime: number): void {
        const onFrameCallback_casted = onFrameCallback as (((value0: number) => void))
        const onIdleCallback_casted = onIdleCallback as (((value0: number) => void))
        const delayTime_casted = delayTime as (number)
        SystemOps.setFrameCallback_serialize(onFrameCallback_casted, onIdleCallback_casted, delayTime_casted)
        return
    }
    public static colorMetricsResourceColor(color: Resource): Array<number> {
        const color_casted = color as (Resource)
        return SystemOps.colorMetricsResourceColor_serialize(color_casted)
    }
    public static resourceToLengthMetrics(res: Resource): LengthMetricsCustom {
        const res_casted = res as (Resource)
        return SystemOps.resourceToLengthMetrics_serialize(res_casted)
    }
    public static blendColorByColorMetrics(color: number, overlayColor: number): Array<number> {
        const color_casted = color as (number)
        const overlayColor_casted = overlayColor as (number)
        return SystemOps.blendColorByColorMetrics_serialize(color_casted, overlayColor_casted)
    }
}
export class ThemeOps {
    static sendThemeToNative_serialize(colorArray: Array<ResourceColor>, elmtId: int32): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((colorArray.length).toInt())
        for (let colorArrayCounterI = 0; colorArrayCounterI < colorArray.length; colorArrayCounterI++) {
            const colorArrayTmpElement : ResourceColor = colorArray[colorArrayCounterI]
            if (colorArrayTmpElement instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const colorArrayTmpElementForIdx0  = colorArrayTmpElement as Color
                thisSerializer.writeInt32(colorArrayTmpElementForIdx0.getOrdinal())
            } else if (colorArrayTmpElement instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const colorArrayTmpElementForIdx1  = colorArrayTmpElement as number
                thisSerializer.writeNumber(colorArrayTmpElementForIdx1)
            } else if (colorArrayTmpElement instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const colorArrayTmpElementForIdx2  = colorArrayTmpElement as string
                thisSerializer.writeString(colorArrayTmpElementForIdx2)
            } else if (colorArrayTmpElement instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const colorArrayTmpElementForIdx3  = colorArrayTmpElement as Resource
                Resource_serializer.write(thisSerializer, colorArrayTmpElementForIdx3)
            }
        }
        ArkUIGeneratedNativeModule._ThemeOps_sendThemeToNative(thisSerializer.asBuffer(), thisSerializer.length(), elmtId)
        thisSerializer.release()
    }
    static setDefaultTheme_serialize(colorArray: Array<ResourceColor>, isDark: boolean): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((colorArray.length).toInt())
        for (let colorArrayCounterI = 0; colorArrayCounterI < colorArray.length; colorArrayCounterI++) {
            const colorArrayTmpElement : ResourceColor = colorArray[colorArrayCounterI]
            if (colorArrayTmpElement instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const colorArrayTmpElementForIdx0  = colorArrayTmpElement as Color
                thisSerializer.writeInt32(colorArrayTmpElementForIdx0.getOrdinal())
            } else if (colorArrayTmpElement instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const colorArrayTmpElementForIdx1  = colorArrayTmpElement as number
                thisSerializer.writeNumber(colorArrayTmpElementForIdx1)
            } else if (colorArrayTmpElement instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const colorArrayTmpElementForIdx2  = colorArrayTmpElement as string
                thisSerializer.writeString(colorArrayTmpElementForIdx2)
            } else if (colorArrayTmpElement instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const colorArrayTmpElementForIdx3  = colorArrayTmpElement as Resource
                Resource_serializer.write(thisSerializer, colorArrayTmpElementForIdx3)
            }
        }
        ArkUIGeneratedNativeModule._ThemeOps_setDefaultTheme(thisSerializer.asBuffer(), thisSerializer.length(), isDark ? 1 : 0)
        thisSerializer.release()
    }
    static createAndBindTheme_serialize(themeScopeId: int32, themeId: int32, colorArray: Array<ResourceColor>, colorMode: ThemeColorMode, onThemeScopeDestroy: (() => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((colorArray.length).toInt())
        for (let colorArrayCounterI = 0; colorArrayCounterI < colorArray.length; colorArrayCounterI++) {
            const colorArrayTmpElement : ResourceColor = colorArray[colorArrayCounterI]
            if (colorArrayTmpElement instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const colorArrayTmpElementForIdx0  = colorArrayTmpElement as Color
                thisSerializer.writeInt32(colorArrayTmpElementForIdx0.getOrdinal())
            } else if (colorArrayTmpElement instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const colorArrayTmpElementForIdx1  = colorArrayTmpElement as number
                thisSerializer.writeNumber(colorArrayTmpElementForIdx1)
            } else if (colorArrayTmpElement instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const colorArrayTmpElementForIdx2  = colorArrayTmpElement as string
                thisSerializer.writeString(colorArrayTmpElementForIdx2)
            } else if (colorArrayTmpElement instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const colorArrayTmpElementForIdx3  = colorArrayTmpElement as Resource
                Resource_serializer.write(thisSerializer, colorArrayTmpElementForIdx3)
            }
        }
        thisSerializer.holdAndWriteCallback(onThemeScopeDestroy)
        ArkUIGeneratedNativeModule._ThemeOps_createAndBindTheme(themeScopeId, themeId, thisSerializer.asBuffer(), thisSerializer.length(), colorMode.valueOf())
        thisSerializer.release()
    }
    static applyThemeScopeIdToNode_serialize(ptr: KPointer, themeScopeId: int32): void {
        ArkUIGeneratedNativeModule._ThemeOps_applyThemeScopeIdToNode(ptr, themeScopeId)
    }
    public static sendThemeToNative(colorArray: Array<ResourceColor>, elmtId: int32): void {
        const colorArray_casted = colorArray as (Array<ResourceColor>)
        const elmtId_casted = elmtId as (int32)
        ThemeOps.sendThemeToNative_serialize(colorArray_casted, elmtId_casted)
        return
    }
    public static setDefaultTheme(colorArray: Array<ResourceColor>, isDark: boolean): void {
        const colorArray_casted = colorArray as (Array<ResourceColor>)
        const isDark_casted = isDark as (boolean)
        ThemeOps.setDefaultTheme_serialize(colorArray_casted, isDark_casted)
        return
    }
    public static createAndBindTheme(themeScopeId: int32, themeId: int32, colorArray: Array<ResourceColor>, colorMode: ThemeColorMode, onThemeScopeDestroy: (() => void)): void {
        const themeScopeId_casted = themeScopeId as (int32)
        const themeId_casted = themeId as (int32)
        const colorArray_casted = colorArray as (Array<ResourceColor>)
        const colorMode_casted = colorMode as (ThemeColorMode)
        const onThemeScopeDestroy_casted = onThemeScopeDestroy as ((() => void))
        ThemeOps.createAndBindTheme_serialize(themeScopeId_casted, themeId_casted, colorArray_casted, colorMode_casted, onThemeScopeDestroy_casted)
        return
    }
    public static applyThemeScopeIdToNode(ptr: int64, themeScopeId: int32): void {
        const ptr_casted = ptr as (int64)
        const themeScopeId_casted = themeScopeId as (int32)
        ThemeOps.applyThemeScopeIdToNode_serialize(ptr_casted, themeScopeId_casted)
        return
    }
}
export class TabsExtender {
    static ApplyAttributesFinish_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._TabsExtender_ApplyAttributesFinish(node)
    }
    public static ApplyAttributesFinish(node: KPointer): void {
        const node_casted = node as (KPointer)
        TabsExtender.ApplyAttributesFinish_serialize(node_casted)
        return
    }
}
export class UIContextAtomicServiceBar {
    static getBarRect_serialize(): Frame {
        const retval  = ArkUIGeneratedNativeModule._UIContextAtomicServiceBar_getBarRect()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Frame = Frame_serializer.read(retvalDeserializer)
        return returnResult
    }
    public static getBarRect(): Frame {
        return UIContextAtomicServiceBar.getBarRect_serialize()
    }
}
export class UIContextGetInfo {
    static getNavigationInfoByUniqueId_serialize(id: int64): uiObserver.NavigationInfo | undefined {
        const retval  = ArkUIGeneratedNativeModule._UIContextGetInfo_getNavigationInfoByUniqueId(id)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : uiObserver.NavigationInfo | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = uiObserver_NavigationInfo_serializer.read(retvalDeserializer)
        }
        const returnResult : uiObserver.NavigationInfo | undefined = buffer
        return returnResult
    }
    static enableSwipeBack_serialize(enabled: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (enabled !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const enabledTmpValue  = enabled!
            thisSerializer.writeBoolean(enabledTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._UIContextGetInfo_enableSwipeBack(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static getNavigationInfoByUniqueId(id: int64): uiObserver.NavigationInfo | undefined {
        const id_casted = id as (int64)
        return UIContextGetInfo.getNavigationInfoByUniqueId_serialize(id_casted)
    }
    public static enableSwipeBack(enabled: boolean | undefined): void {
        const enabled_cast = enabled as (boolean | undefined)
        UIContextGetInfo.enableSwipeBack_serialize(enabled_cast)
        return
    }
}
export class ArkRootPeer extends PeerNode {
    attributeSet?: RootModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRootPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Root_construct(peerId, flags)
        const _peer  = new ArkRootPeer(_peerPtr, peerId, 'Root', flags)
        component?.setPeer(_peer)
        return _peer
    }
}
export class ArkComponentRootPeer extends PeerNode {
    attributeSet?: ComponentRootModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkComponentRootPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._ComponentRoot_construct(peerId, flags)
        const _peer  = new ArkComponentRootPeer(_peerPtr, peerId, 'ComponentRoot', flags)
        component?.setPeer(_peer)
        return _peer
    }
}
export class ArkCustomBuilderRootPeer extends PeerNode {
    attributeSet?: CustomBuilderRootModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkCustomBuilderRootPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._CustomBuilderRoot_construct(peerId, flags)
        const _peer  = new ArkCustomBuilderRootPeer(_peerPtr, peerId, 'CustomBuilderRoot', flags)
        component?.setPeer(_peer)
        return _peer
    }
}
export class ArkCustomLayoutRootPeer extends PeerNode {
    attributeSet?: CustomLayoutRootModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkCustomLayoutRootPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._CustomLayoutRoot_construct(peerId, flags)
        const _peer  = new ArkCustomLayoutRootPeer(_peerPtr, peerId, 'CustomLayoutRoot', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSubscribeOnMeasureSizeAttribute(value: Callback_onMeasureSize_SizeResult): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CustomLayoutRoot_setSubscribeOnMeasureSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSubscribeOnPlaceChildrenAttribute(value: Callback_onPlaceChildren_Void): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CustomLayoutRoot_setSubscribeOnPlaceChildren(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type RouterFinishCallback = (value: KPointer) => void;
export interface PageRouterOptions {
    options: router.RouterOptions;
    mode?: router.RouterMode;
}
export type Callback_Extender_OnProgress = (value: float) => void;
export type Callback_Extender_OnFinish = () => void;
export interface DoubleAnimationParam {
    propertyName: string;
    startValue: float;
    endValue: float;
    duration: int32;
    delay: int32;
    curve: curves.Curve | string | curves.ICurve;
    onProgress?: Callback_Extender_OnProgress;
    onFinish?: Callback_Extender_OnFinish;
}
export interface ComponentInfo {
    size: Size;
    localOffset: Offset_componentutils;
    windowOffset: Offset_componentutils;
    screenOffset: Offset_componentutils;
    translate: TranslateResult;
    scale: ScaleResult;
    rotate: RotateResult;
    transform: Matrix4Result;
}
export interface Offset_componentutils {
    x: number;
    y: number;
}
export interface TranslateResult {
    x: number;
    y: number;
    z: number;
}
export interface ScaleResult {
    x: number;
    y: number;
    z: number;
    centerX: number;
    centerY: number;
}
export interface RotateResult {
    x: number;
    y: number;
    z: number;
    centerX: number;
    centerY: number;
    angle: number;
}
export type Matrix4Result = [
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number,
    number
]
export interface CustomDialogBuildOptions {
    controller?: CustomDialogController;
}
export interface CustomDialogControllerBuilder {
    buildOptions: CustomDialogBuildOptions;
    build: CustomBuilder;
}
export interface CustomDialogControllerOptionsExtender {
    builder: CustomBuilder;
    cancel?: (() => void);
    autoCancel?: boolean;
    alignment?: DialogAlignment;
    offset?: Offset;
    customStyle?: boolean;
    gridCount?: int32;
    maskColor?: ResourceColor;
    maskRect?: Rectangle;
    openAnimation?: AnimateParam;
    closeAnimation?: AnimateParam;
    showInSubWindow?: boolean;
    backgroundColor?: ResourceColor;
    cornerRadius?: Dimension | BorderRadiuses;
    isModal?: boolean;
    onWillDismiss?: ((value0: DismissDialogAction) => void);
    width?: Dimension;
    height?: Dimension;
    borderWidth?: Dimension | EdgeWidths;
    borderColor?: ResourceColor | EdgeColors;
    borderStyle?: BorderStyle | EdgeStyles;
    shadow?: ShadowOptions | ShadowStyle;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    keyboardAvoidMode?: KeyboardAvoidMode;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
    onDidAppear?: (() => void);
    onDidDisappear?: (() => void);
    onWillAppear?: (() => void);
    onWillDisappear?: (() => void);
    keyboardAvoidDistance?: LengthMetrics;
    levelMode?: LevelMode;
    levelUniqueId?: int32;
    immersiveMode?: ImmersiveMode;
    levelOrderExtender?: LevelOrderExtender;
    focusable?: boolean;
}
export interface CustomDialogControllerExternalOptionsExtender {
    customStyle?: boolean;
}
export type Callback_RangeUpdate = (start: int32, end: int32, cacheStart: int32, cacheEnd: int32, isLoop: boolean) => void;
export type Callback_CreateItem = (index: int32) => KPointer;
export type Callback_OnMoveFromTo = (from: int32, to: int32) => void;
export interface LengthMetricsCustom {
    unit: number;
    value: number;
}
export interface CustomColors {
    brand?: ResourceColor;
    warning?: ResourceColor;
    alert?: ResourceColor;
    confirm?: ResourceColor;
    fontPrimary?: ResourceColor;
    fontSecondary?: ResourceColor;
    fontTertiary?: ResourceColor;
    fontFourth?: ResourceColor;
    fontEmphasize?: ResourceColor;
    fontOnPrimary?: ResourceColor;
    fontOnSecondary?: ResourceColor;
    fontOnTertiary?: ResourceColor;
    fontOnFourth?: ResourceColor;
    iconPrimary?: ResourceColor;
    iconSecondary?: ResourceColor;
    iconTertiary?: ResourceColor;
    iconFourth?: ResourceColor;
    iconEmphasize?: ResourceColor;
    iconSubEmphasize?: ResourceColor;
    iconOnPrimary?: ResourceColor;
    iconOnSecondary?: ResourceColor;
    iconOnTertiary?: ResourceColor;
    iconOnFourth?: ResourceColor;
    backgroundPrimary?: ResourceColor;
    backgroundSecondary?: ResourceColor;
    backgroundTertiary?: ResourceColor;
    backgroundFourth?: ResourceColor;
    backgroundEmphasize?: ResourceColor;
    compForegroundPrimary?: ResourceColor;
    compBackgroundPrimary?: ResourceColor;
    compBackgroundPrimaryTran?: ResourceColor;
    compBackgroundPrimaryContrary?: ResourceColor;
    compBackgroundGray?: ResourceColor;
    compBackgroundSecondary?: ResourceColor;
    compBackgroundTertiary?: ResourceColor;
    compBackgroundEmphasize?: ResourceColor;
    compBackgroundNeutral?: ResourceColor;
    compEmphasizeSecondary?: ResourceColor;
    compEmphasizeTertiary?: ResourceColor;
    compDivider?: ResourceColor;
    compCommonContrary?: ResourceColor;
    compBackgroundFocus?: ResourceColor;
    compFocusedPrimary?: ResourceColor;
    compFocusedSecondary?: ResourceColor;
    compFocusedTertiary?: ResourceColor;
    interactiveHover?: ResourceColor;
    interactivePressed?: ResourceColor;
    interactiveFocus?: ResourceColor;
    interactiveActive?: ResourceColor;
    interactiveSelect?: ResourceColor;
    interactiveClick?: ResourceColor;
}
export interface WorkerOptions {
    type?: string;
    name?: string;
    shared?: boolean;
}
export interface Event {
    readonly type: string;
    readonly timeStamp: int64;
}
export interface ErrorEvent extends Event {
    readonly message: string;
    readonly filename: string;
    readonly lineno: number;
    readonly colno: number;
    readonly error: Object;
}
export interface MessageEvents extends Event {
    readonly data: object;
}
export type WorkerEventListener = (event: Event) => void;
export interface PostMessageOptions {
    transfer?: Array<Object>;
}
export type RestrictedWorker_onexit_Callback = (code: number) => void;
export type RestrictedWorker_onerror_Callback = (ev: ErrorEvent) => void;
export type RestrictedWorker_onmessage_Callback = (event: MessageEvents) => void;
export type Callback_StateStylesChange = (currentState: int32) => void;
export interface BuilderNodeOptions {
    selfIdealSize?: Size;
    type?: number;
    surfaceId?: string;
}
export type Callback_Size_Void = (size: Size) => void;
export type Callback_OnDestory_Void = (nodeId: int64) => void;
export interface WebHeader {
    headerKey: string;
    headerValue: string;
}
export interface SnapshotOptions {
    scale?: number;
    waitUntilRenderFinished?: boolean;
}
export enum PerfMonitorActionType {
    LAST_DOWN = 0,
    LAST_UP = 1,
    FIRST_MOVE = 2
}
export enum PerfMonitorSourceType {
    PERF_TOUCH_EVENT = 0,
    PERF_MOUSE_EVENT = 1,
    PERF_TOUCHPAD_EVENT = 2,
    PERF_JOYSTICK_EVENT = 3,
    PERF_KEY_EVENT = 4
}
export interface IndicatorStyle {
    height?: Length;
    width?: Length;
    borderRadius?: Length;
    marginTop?: Length;
    color?: ResourceColor;
    selectedColor?: ResourceColor;
    left?: Length;
    top?: Length;
    right?: Length;
    bottom?: Length;
    size?: Length;
    mask?: boolean;
}
export type CustomNodeBuilder = (parentNode: KPointer) => KPointer;
export interface NodeEdgesLengthMetrics {
    top: LengthMetrics | undefined;
    left: LengthMetrics | undefined;
    bottom: LengthMetrics | undefined;
    right: LengthMetrics | undefined;
}
export interface SizeTLengthMetrics {
    width: LengthMetrics;
    height: LengthMetrics;
}
export type NavExtender_OnUpdateStack = () => void;
export type NavExtender_CreateNavDestination = (index: int32) => KPointer;
export interface BorderRadiuses_graphics {
    topLeft: number;
    topRight: number;
    bottomLeft: number;
    bottomRight: number;
}
export interface NodeEdgeStyles {
    top: BorderStyle;
    right: BorderStyle;
    bottom: BorderStyle;
    left: BorderStyle;
}
export interface EdgeNumber {
    top: number;
    right: number;
    bottom: number;
    left: number;
}
export interface SizeNumberInner {
    width: number;
    height: number;
}
export interface PositionNumberInner {
    x: number;
    y: number;
}
export interface PositionLengthMetricsInner {
    x: LengthMetrics;
    y: LengthMetrics;
}
export interface ParticlePropertyAnimationNumberInner {
    from: number;
    to: number;
    startMillis: number;
    endMillis: number;
    curve?: curves.Curve | curves.ICurve;
}
export interface ParticlePropertyAnimationColorInner {
    from: ResourceColor;
    to: ResourceColor;
    startMillis: number;
    endMillis: number;
    curve?: curves.Curve | curves.ICurve;
}
export type ParticlePropertyUpdaterConfigsInner = [ number, number ] | Array<ParticlePropertyAnimationNumberInner> | undefined;
export interface ParticleUpdaterOptionsInner {
    type: ParticleUpdater;
    config: ParticlePropertyUpdaterConfigsInner;
}
export interface ParticlePropertyOptionsInner {
    range: [ number, number ];
    updater?: ParticleUpdaterOptionsInner;
}
export interface ParticleColorUpdaterOptionsInner {
    type: ParticleUpdater;
    config: ParticleColorPropertyUpdaterConfigsInner;
}
export type ParticleColorPropertyUpdaterConfigsInner = ParticleColorOptions | Array<ParticlePropertyAnimationColorInner> | undefined;
export interface AccelerationOptionsInner {
    speed?: ParticlePropertyOptionsInner;
    angle?: ParticlePropertyOptionsInner;
}
export interface ParticleOptionsInner {
    emitter: EmitterOptionsInner;
    color?: ParticleColorPropertyOptionsInner;
    opacity?: ParticlePropertyOptionsInner;
    scale?: ParticlePropertyOptionsInner;
    velocity?: VelocityOptions;
    acceleration?: AccelerationOptionsInner;
    spin?: ParticlePropertyOptionsInner;
}
export interface ParticleAnnulusRegionInner {
    center?: PositionLengthMetricsInner;
    outerRadius: LengthMetrics;
    innerRadius: LengthMetrics;
    startAngle?: number;
    endAngle?: number;
}
export interface EmitterPropertyInner {
    index: number;
    emitRate?: number;
    position?: PositionNumberInner;
    size?: SizeNumberInner;
    annulusRegion?: ParticleAnnulusRegionInner;
}
export interface EmitterOptionsInner {
    particle: EmitterParticleOptions;
    emitRate?: number;
    shape?: ParticleEmitterShape;
    position?: [ Dimension, Dimension ];
    size?: [ Dimension, Dimension ];
    annulusRegion?: ParticleAnnulusRegionInner;
}
export interface ParticleColorPropertyOptionsInner {
    range: [ ResourceColor, ResourceColor ];
    distributionType?: DistributionType;
    updater?: ParticleColorUpdaterOptionsInner;
}
export interface ParticlesInner {
    particles: Array<ParticleOptionsInner>;
}
export interface DisturbanceFieldOptionsInner {
    strength?: number;
    shape?: DisturbanceFieldShape;
    size?: SizeNumberInner;
    position?: PositionNumberInner;
    feather?: number;
    noiseScale?: number;
    noiseFrequency?: number;
    noiseAmplitude?: number;
}
export interface Root {
    attributeModifier(value: AttributeModifier<Root> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkRootStyle implements Root {
    public attributeModifier(value: AttributeModifier<Root> | undefined): this {
        throw new Error("Not implemented")
    }
}
export interface ComponentRoot {
    attributeModifier(value: AttributeModifier<ComponentRoot> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkComponentRootStyle implements ComponentRoot {
    public attributeModifier(value: AttributeModifier<ComponentRoot> | undefined): this {
        throw new Error("Not implemented")
    }
}
export interface CustomBuilderRoot {
    attributeModifier(value: AttributeModifier<CustomBuilderRoot> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkCustomBuilderRootStyle implements CustomBuilderRoot {
    public attributeModifier(value: AttributeModifier<CustomBuilderRoot> | undefined): this {
        throw new Error("Not implemented")
    }
}
export type Callback_onMeasureSize_SizeResult = (selfLayoutInfo: GeometryInfo, children: Array<Measurable>, constraint: ConstraintSizeOptions) => SizeResult;
export type Callback_onPlaceChildren_Void = (selfLayoutInfo: GeometryInfo, children: Array<Layoutable>, constraint: ConstraintSizeOptions) => void;
export interface CustomLayoutRoot {
    subscribeOnMeasureSize(value: Callback_onMeasureSize_SizeResult): this {
        throw new Error("Unimplemented method subscribeOnMeasureSize")
    }
    subscribeOnPlaceChildren(value: Callback_onPlaceChildren_Void): this {
        throw new Error("Unimplemented method subscribeOnPlaceChildren")
    }
    attributeModifier(value: AttributeModifier<CustomLayoutRoot> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkCustomLayoutRootStyle implements CustomLayoutRoot {
    subscribeOnMeasureSize_value?: Callback_onMeasureSize_SizeResult
    subscribeOnPlaceChildren_value?: Callback_onPlaceChildren_Void
    subscribeOnMeasureSize(value: Callback_onMeasureSize_SizeResult): this {
        return this
    }
    subscribeOnPlaceChildren(value: Callback_onPlaceChildren_Void): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<CustomLayoutRoot> | undefined): this {
        throw new Error("Not implemented")
    }
}
export interface TransformationMatrix {
    matrix4x4: Array<number>;
}
export class ArkRootComponent extends ComponentBase implements Root {
    getPeer(): ArkRootPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkRootPeer)
    }
    public attributeModifier(value: AttributeModifier<Root> | undefined): this {
        hookRootAttributeModifier(this, value);
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export class ArkComponentRootComponent extends ComponentBase implements ComponentRoot {
    getPeer(): ArkComponentRootPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkComponentRootPeer)
    }
    public attributeModifier(value: AttributeModifier<ComponentRoot> | undefined): this {
        hookComponentRootAttributeModifier(this, value);
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export class ArkCustomBuilderRootComponent extends ComponentBase implements CustomBuilderRoot {
    getPeer(): ArkCustomBuilderRootPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkCustomBuilderRootPeer)
    }
    public attributeModifier(value: AttributeModifier<CustomBuilderRoot> | undefined): this {
        hookCustomBuilderRootAttributeModifier(this, value);
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export class ArkCustomLayoutRootComponent extends ComponentBase implements CustomLayoutRoot {
    getPeer(): ArkCustomLayoutRootPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkCustomLayoutRootPeer)
    }
    public subscribeOnMeasureSize(value: Callback_onMeasureSize_SizeResult): this {
        if (this.checkPriority("subscribeOnMeasureSize")) {
            const value_casted = value as (Callback_onMeasureSize_SizeResult)
            this.getPeer()?.setSubscribeOnMeasureSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public subscribeOnPlaceChildren(value: Callback_onPlaceChildren_Void): this {
        if (this.checkPriority("subscribeOnPlaceChildren")) {
            const value_casted = value as (Callback_onPlaceChildren_Void)
            this.getPeer()?.setSubscribeOnPlaceChildrenAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<CustomLayoutRoot> | undefined): this {
        hookCustomLayoutRootAttributeModifier(this, value);
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function getRectangleById(id: string): ComponentInfo {
    return GlobalScope.getRectangleById(id)
}
export class BaseShape_serializer {
    public static write(buffer: SerializerBase, value: BaseShape): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): BaseShape {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return BaseShapeInternal.fromPtr(ptr)
    }
}
export class BuilderNodeOps_serializer {
    public static write(buffer: SerializerBase, value: BuilderNodeOps): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): BuilderNodeOps {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return BuilderNodeOpsInternal.fromPtr(ptr)
    }
}
export class CommonShape_serializer {
    public static write(buffer: SerializerBase, value: CommonShape): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): CommonShape {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return CommonShapeInternal.fromPtr(ptr)
    }
}
export class CustomDialogControllerExtender_serializer {
    public static write(buffer: SerializerBase, value: CustomDialogControllerExtender): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): CustomDialogControllerExtender {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return CustomDialogControllerExtenderInternal.fromPtr(ptr)
    }
}
export class LevelOrderExtender_serializer {
    public static write(buffer: SerializerBase, value: LevelOrderExtender): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): LevelOrderExtender {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return LevelOrderExtenderInternal.fromPtr(ptr)
    }
}
export class NodeEdgeStyles_serializer {
    public static write(buffer: SerializerBase, value: NodeEdgeStyles): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTop  = value.top
        valueSerializer.writeInt32(valueHolderForTop.valueOf())
        const valueHolderForRight  = value.right
        valueSerializer.writeInt32(valueHolderForRight.valueOf())
        const valueHolderForBottom  = value.bottom
        valueSerializer.writeInt32(valueHolderForBottom.valueOf())
        const valueHolderForLeft  = value.left
        valueSerializer.writeInt32(valueHolderForLeft.valueOf())
    }
    public static read(buffer: DeserializerBase): NodeEdgeStyles {
        let valueDeserializer : DeserializerBase = buffer
        const topTmpResult : BorderStyle = BorderStyle.fromValue(valueDeserializer.readInt32())
        const rightTmpResult : BorderStyle = BorderStyle.fromValue(valueDeserializer.readInt32())
        const bottomTmpResult : BorderStyle = BorderStyle.fromValue(valueDeserializer.readInt32())
        const leftTmpResult : BorderStyle = BorderStyle.fromValue(valueDeserializer.readInt32())
        let value : NodeEdgeStyles = ({top: topTmpResult, right: rightTmpResult, bottom: bottomTmpResult, left: leftTmpResult} as NodeEdgeStyles)
        return value
    }
}
export class Offset_componentutils_serializer {
    public static write(buffer: SerializerBase, value: Offset_componentutils): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForX  = value.x
        valueSerializer.writeNumber(valueHolderForX)
        const valueHolderForY  = value.y
        valueSerializer.writeNumber(valueHolderForY)
    }
    public static read(buffer: DeserializerBase): Offset_componentutils {
        let valueDeserializer : DeserializerBase = buffer
        const xTmpResult : number = (valueDeserializer.readNumber() as number)
        const yTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : Offset_componentutils = ({x: xTmpResult, y: yTmpResult} as Offset_componentutils)
        return value
    }
}
export class PositionNumberInner_serializer {
    public static write(buffer: SerializerBase, value: PositionNumberInner): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForX  = value.x
        valueSerializer.writeNumber(valueHolderForX)
        const valueHolderForY  = value.y
        valueSerializer.writeNumber(valueHolderForY)
    }
    public static read(buffer: DeserializerBase): PositionNumberInner {
        let valueDeserializer : DeserializerBase = buffer
        const xTmpResult : number = (valueDeserializer.readNumber() as number)
        const yTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : PositionNumberInner = ({x: xTmpResult, y: yTmpResult} as PositionNumberInner)
        return value
    }
}
export class RotateResult_serializer {
    public static write(buffer: SerializerBase, value: RotateResult): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForX  = value.x
        valueSerializer.writeNumber(valueHolderForX)
        const valueHolderForY  = value.y
        valueSerializer.writeNumber(valueHolderForY)
        const valueHolderForZ  = value.z
        valueSerializer.writeNumber(valueHolderForZ)
        const valueHolderForCenterX  = value.centerX
        valueSerializer.writeNumber(valueHolderForCenterX)
        const valueHolderForCenterY  = value.centerY
        valueSerializer.writeNumber(valueHolderForCenterY)
        const valueHolderForAngle  = value.angle
        valueSerializer.writeNumber(valueHolderForAngle)
    }
    public static read(buffer: DeserializerBase): RotateResult {
        let valueDeserializer : DeserializerBase = buffer
        const xTmpResult : number = (valueDeserializer.readNumber() as number)
        const yTmpResult : number = (valueDeserializer.readNumber() as number)
        const zTmpResult : number = (valueDeserializer.readNumber() as number)
        const centerXTmpResult : number = (valueDeserializer.readNumber() as number)
        const centerYTmpResult : number = (valueDeserializer.readNumber() as number)
        const angleTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : RotateResult = ({x: xTmpResult, y: yTmpResult, z: zTmpResult, centerX: centerXTmpResult, centerY: centerYTmpResult, angle: angleTmpResult} as RotateResult)
        return value
    }
}
export class ScaleResult_serializer {
    public static write(buffer: SerializerBase, value: ScaleResult): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForX  = value.x
        valueSerializer.writeNumber(valueHolderForX)
        const valueHolderForY  = value.y
        valueSerializer.writeNumber(valueHolderForY)
        const valueHolderForZ  = value.z
        valueSerializer.writeNumber(valueHolderForZ)
        const valueHolderForCenterX  = value.centerX
        valueSerializer.writeNumber(valueHolderForCenterX)
        const valueHolderForCenterY  = value.centerY
        valueSerializer.writeNumber(valueHolderForCenterY)
    }
    public static read(buffer: DeserializerBase): ScaleResult {
        let valueDeserializer : DeserializerBase = buffer
        const xTmpResult : number = (valueDeserializer.readNumber() as number)
        const yTmpResult : number = (valueDeserializer.readNumber() as number)
        const zTmpResult : number = (valueDeserializer.readNumber() as number)
        const centerXTmpResult : number = (valueDeserializer.readNumber() as number)
        const centerYTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : ScaleResult = ({x: xTmpResult, y: yTmpResult, z: zTmpResult, centerX: centerXTmpResult, centerY: centerYTmpResult} as ScaleResult)
        return value
    }
}
export class SizeNumberInner_serializer {
    public static write(buffer: SerializerBase, value: SizeNumberInner): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWidth  = value.width
        valueSerializer.writeNumber(valueHolderForWidth)
        const valueHolderForHeight  = value.height
        valueSerializer.writeNumber(valueHolderForHeight)
    }
    public static read(buffer: DeserializerBase): SizeNumberInner {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpResult : number = (valueDeserializer.readNumber() as number)
        const heightTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : SizeNumberInner = ({width: widthTmpResult, height: heightTmpResult} as SizeNumberInner)
        return value
    }
}
export class TranslateResult_serializer {
    public static write(buffer: SerializerBase, value: TranslateResult): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForX  = value.x
        valueSerializer.writeNumber(valueHolderForX)
        const valueHolderForY  = value.y
        valueSerializer.writeNumber(valueHolderForY)
        const valueHolderForZ  = value.z
        valueSerializer.writeNumber(valueHolderForZ)
    }
    public static read(buffer: DeserializerBase): TranslateResult {
        let valueDeserializer : DeserializerBase = buffer
        const xTmpResult : number = (valueDeserializer.readNumber() as number)
        const yTmpResult : number = (valueDeserializer.readNumber() as number)
        const zTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : TranslateResult = ({x: xTmpResult, y: yTmpResult, z: zTmpResult} as TranslateResult)
        return value
    }
}
export class BorderRadiuses_graphics_serializer {
    public static write(buffer: SerializerBase, value: BorderRadiuses_graphics): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTopLeft  = value.topLeft
        valueSerializer.writeNumber(valueHolderForTopLeft)
        const valueHolderForTopRight  = value.topRight
        valueSerializer.writeNumber(valueHolderForTopRight)
        const valueHolderForBottomLeft  = value.bottomLeft
        valueSerializer.writeNumber(valueHolderForBottomLeft)
        const valueHolderForBottomRight  = value.bottomRight
        valueSerializer.writeNumber(valueHolderForBottomRight)
    }
}
export class BuilderNodeOptions_serializer {
    public static write(buffer: SerializerBase, value: BuilderNodeOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSelfIdealSize  = value.selfIdealSize
        if (valueHolderForSelfIdealSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSelfIdealSizeTmpValue  = valueHolderForSelfIdealSize!
            Size_serializer.write(valueSerializer, valueHolderForSelfIdealSizeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForType  = value.type
        if (valueHolderForType !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTypeTmpValue  = valueHolderForType!
            valueSerializer.writeNumber(valueHolderForTypeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSurfaceId  = value.surfaceId
        if (valueHolderForSurfaceId !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSurfaceIdTmpValue  = valueHolderForSurfaceId!
            valueSerializer.writeString(valueHolderForSurfaceIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): BuilderNodeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const selfIdealSizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let selfIdealSizeTmpBuf : Size | undefined = undefined
        if ((selfIdealSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            selfIdealSizeTmpBuf = Size_serializer.read(valueDeserializer)
        }
        const selfIdealSizeTmpResult : Size | undefined = selfIdealSizeTmpBuf
        const typeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let typeTmpBuf : number | undefined = undefined
        if ((typeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            typeTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const typeTmpResult : number | undefined = typeTmpBuf
        const surfaceIdTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let surfaceIdTmpBuf : string | undefined = undefined
        if ((surfaceIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            surfaceIdTmpBuf = (valueDeserializer.readString() as string)
        }
        const surfaceIdTmpResult : string | undefined = surfaceIdTmpBuf
        let value : BuilderNodeOptions = ({selfIdealSize: selfIdealSizeTmpResult, type: typeTmpResult, surfaceId: surfaceIdTmpResult} as BuilderNodeOptions)
        return value
    }
}
export class CustomDialogControllerExternalOptionsExtender_serializer {
    public static write(buffer: SerializerBase, value: CustomDialogControllerExternalOptionsExtender): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForCustomStyle  = value.customStyle
        if (valueHolderForCustomStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCustomStyleTmpValue  = valueHolderForCustomStyle!
            valueSerializer.writeBoolean(valueHolderForCustomStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): CustomDialogControllerExternalOptionsExtender {
        let valueDeserializer : DeserializerBase = buffer
        const customStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let customStyleTmpBuf : boolean | undefined = undefined
        if ((customStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            customStyleTmpBuf = valueDeserializer.readBoolean()
        }
        const customStyleTmpResult : boolean | undefined = customStyleTmpBuf
        let value : CustomDialogControllerExternalOptionsExtender = ({customStyle: customStyleTmpResult} as CustomDialogControllerExternalOptionsExtender)
        return value
    }
}
export class DisturbanceFieldOptionsInner_serializer {
    public static write(buffer: SerializerBase, value: DisturbanceFieldOptionsInner): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStrength  = value.strength
        if (valueHolderForStrength !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStrengthTmpValue  = valueHolderForStrength!
            valueSerializer.writeNumber(valueHolderForStrengthTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShape  = value.shape
        if (valueHolderForShape !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShapeTmpValue  = (valueHolderForShape as DisturbanceFieldShape)
            valueSerializer.writeInt32(valueHolderForShapeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSize  = value.size
        if (valueHolderForSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSizeTmpValue  = valueHolderForSize!
            SizeNumberInner_serializer.write(valueSerializer, valueHolderForSizeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPosition  = value.position
        if (valueHolderForPosition !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPositionTmpValue  = valueHolderForPosition!
            PositionNumberInner_serializer.write(valueSerializer, valueHolderForPositionTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFeather  = value.feather
        if (valueHolderForFeather !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFeatherTmpValue  = valueHolderForFeather!
            valueSerializer.writeNumber(valueHolderForFeatherTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForNoiseScale  = value.noiseScale
        if (valueHolderForNoiseScale !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForNoiseScaleTmpValue  = valueHolderForNoiseScale!
            valueSerializer.writeNumber(valueHolderForNoiseScaleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForNoiseFrequency  = value.noiseFrequency
        if (valueHolderForNoiseFrequency !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForNoiseFrequencyTmpValue  = valueHolderForNoiseFrequency!
            valueSerializer.writeNumber(valueHolderForNoiseFrequencyTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForNoiseAmplitude  = value.noiseAmplitude
        if (valueHolderForNoiseAmplitude !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForNoiseAmplitudeTmpValue  = valueHolderForNoiseAmplitude!
            valueSerializer.writeNumber(valueHolderForNoiseAmplitudeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): DisturbanceFieldOptionsInner {
        let valueDeserializer : DeserializerBase = buffer
        const strengthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strengthTmpBuf : number | undefined = undefined
        if ((strengthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            strengthTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const strengthTmpResult : number | undefined = strengthTmpBuf
        const shapeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let shapeTmpBuf : DisturbanceFieldShape | undefined = undefined
        if ((shapeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            shapeTmpBuf = DisturbanceFieldShape.fromValue(valueDeserializer.readInt32())
        }
        const shapeTmpResult : DisturbanceFieldShape | undefined = shapeTmpBuf
        const sizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let sizeTmpBuf : SizeNumberInner | undefined = undefined
        if ((sizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            sizeTmpBuf = SizeNumberInner_serializer.read(valueDeserializer)
        }
        const sizeTmpResult : SizeNumberInner | undefined = sizeTmpBuf
        const positionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let positionTmpBuf : PositionNumberInner | undefined = undefined
        if ((positionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            positionTmpBuf = PositionNumberInner_serializer.read(valueDeserializer)
        }
        const positionTmpResult : PositionNumberInner | undefined = positionTmpBuf
        const featherTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let featherTmpBuf : number | undefined = undefined
        if ((featherTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            featherTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const featherTmpResult : number | undefined = featherTmpBuf
        const noiseScaleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let noiseScaleTmpBuf : number | undefined = undefined
        if ((noiseScaleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            noiseScaleTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const noiseScaleTmpResult : number | undefined = noiseScaleTmpBuf
        const noiseFrequencyTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let noiseFrequencyTmpBuf : number | undefined = undefined
        if ((noiseFrequencyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            noiseFrequencyTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const noiseFrequencyTmpResult : number | undefined = noiseFrequencyTmpBuf
        const noiseAmplitudeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let noiseAmplitudeTmpBuf : number | undefined = undefined
        if ((noiseAmplitudeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            noiseAmplitudeTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const noiseAmplitudeTmpResult : number | undefined = noiseAmplitudeTmpBuf
        let value : DisturbanceFieldOptionsInner = ({strength: strengthTmpResult, shape: shapeTmpResult, size: sizeTmpResult, position: positionTmpResult, feather: featherTmpResult, noiseScale: noiseScaleTmpResult, noiseFrequency: noiseFrequencyTmpResult, noiseAmplitude: noiseAmplitudeTmpResult} as DisturbanceFieldOptionsInner)
        return value
    }
}
export class DoubleAnimationParam_serializer {
    public static write(buffer: SerializerBase, value: DoubleAnimationParam): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForPropertyName  = value.propertyName
        valueSerializer.writeString(valueHolderForPropertyName)
        const valueHolderForStartValue  = value.startValue
        valueSerializer.writeFloat32(valueHolderForStartValue)
        const valueHolderForEndValue  = value.endValue
        valueSerializer.writeFloat32(valueHolderForEndValue)
        const valueHolderForDuration  = value.duration
        valueSerializer.writeInt32(valueHolderForDuration)
        const valueHolderForDelay  = value.delay
        valueSerializer.writeInt32(valueHolderForDelay)
        const valueHolderForCurve  = value.curve
        if (valueHolderForCurve instanceof curves.Curve) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForCurveForIdx0  = valueHolderForCurve as curves.Curve
            valueSerializer.writeInt32(valueHolderForCurveForIdx0.valueOf())
        } else if (valueHolderForCurve instanceof string) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForCurveForIdx1  = valueHolderForCurve as string
            valueSerializer.writeString(valueHolderForCurveForIdx1)
        } else if (valueHolderForCurve instanceof curves.ICurve) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForCurveForIdx2  = valueHolderForCurve as curves.ICurve
            curves_ICurve_serializer.write(valueSerializer, valueHolderForCurveForIdx2)
        }
        const valueHolderForOnProgress  = value.onProgress
        if (valueHolderForOnProgress !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnProgressTmpValue  = valueHolderForOnProgress!
            valueSerializer.holdAndWriteCallback(valueHolderForOnProgressTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnFinish  = value.onFinish
        if (valueHolderForOnFinish !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnFinishTmpValue  = valueHolderForOnFinish!
            valueSerializer.holdAndWriteCallback(valueHolderForOnFinishTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): DoubleAnimationParam {
        let valueDeserializer : DeserializerBase = buffer
        const propertyNameTmpResult : string = (valueDeserializer.readString() as string)
        const startValueTmpResult : float = valueDeserializer.readFloat32()
        const endValueTmpResult : float = valueDeserializer.readFloat32()
        const durationTmpResult : int32 = valueDeserializer.readInt32()
        const delayTmpResult : int32 = valueDeserializer.readInt32()
        const curveTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let curveTmpBuf : curves.Curve | string | curves.ICurve | undefined
        if (curveTmpBufUnionSelector == (0).toChar()) {
            curveTmpBuf = curves.Curve.fromValue(valueDeserializer.readInt32())
        } else if (curveTmpBufUnionSelector == (1).toChar()) {
            curveTmpBuf = (valueDeserializer.readString() as string)
        } else if (curveTmpBufUnionSelector == (2).toChar()) {
            curveTmpBuf = (curves_ICurve_serializer.read(valueDeserializer) as curves.ICurve)
        } else {
            throw new Error("One of the branches for curveTmpBuf has to be chosen through deserialisation.")
        }
        const curveTmpResult : curves.Curve | string | curves.ICurve = (curveTmpBuf as curves.Curve | string | curves.ICurve)
        const onProgressTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onProgressTmpBuf : Callback_Extender_OnProgress | undefined = undefined
        if ((onProgressTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onProgressTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onProgressTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onProgressTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onProgressTmpBuf = (value: float):void => {
                const onProgressTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onProgressTmpBuf_BufArgsSerializer.writeInt32(onProgressTmpBuf_BufResource.resourceId);
                onProgressTmpBuf_BufArgsSerializer.writePointer(onProgressTmpBuf_BufCall);
                onProgressTmpBuf_BufArgsSerializer.writePointer(onProgressTmpBuf_BufCallSync);
                onProgressTmpBuf_BufArgsSerializer.writeFloat32(value);
                InteropNativeModule._CallCallbackSync(10, 1264236374, onProgressTmpBuf_BufArgsSerializer.asBuffer(), onProgressTmpBuf_BufArgsSerializer.length());
                onProgressTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onProgressTmpResult : Callback_Extender_OnProgress | undefined = onProgressTmpBuf
        const onFinishTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onFinishTmpBuf : Callback_Extender_OnFinish | undefined = undefined
        if ((onFinishTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onFinishTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onFinishTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onFinishTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onFinishTmpBuf = ():void => {
                const onFinishTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onFinishTmpBuf_BufArgsSerializer.writeInt32(onFinishTmpBuf_BufResource.resourceId);
                onFinishTmpBuf_BufArgsSerializer.writePointer(onFinishTmpBuf_BufCall);
                onFinishTmpBuf_BufArgsSerializer.writePointer(onFinishTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -733525640, onFinishTmpBuf_BufArgsSerializer.asBuffer(), onFinishTmpBuf_BufArgsSerializer.length());
                onFinishTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onFinishTmpResult : Callback_Extender_OnFinish | undefined = onFinishTmpBuf
        let value : DoubleAnimationParam = ({propertyName: propertyNameTmpResult, startValue: startValueTmpResult, endValue: endValueTmpResult, duration: durationTmpResult, delay: delayTmpResult, curve: curveTmpResult, onProgress: onProgressTmpResult, onFinish: onFinishTmpResult} as DoubleAnimationParam)
        return value
    }
}
export class EdgeNumber_serializer {
    public static write(buffer: SerializerBase, value: EdgeNumber): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTop  = value.top
        valueSerializer.writeNumber(valueHolderForTop)
        const valueHolderForRight  = value.right
        valueSerializer.writeNumber(valueHolderForRight)
        const valueHolderForBottom  = value.bottom
        valueSerializer.writeNumber(valueHolderForBottom)
        const valueHolderForLeft  = value.left
        valueSerializer.writeNumber(valueHolderForLeft)
    }
    public static read(buffer: DeserializerBase): EdgeNumber {
        let valueDeserializer : DeserializerBase = buffer
        const topTmpResult : number = (valueDeserializer.readNumber() as number)
        const rightTmpResult : number = (valueDeserializer.readNumber() as number)
        const bottomTmpResult : number = (valueDeserializer.readNumber() as number)
        const leftTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : EdgeNumber = ({top: topTmpResult, right: rightTmpResult, bottom: bottomTmpResult, left: leftTmpResult} as EdgeNumber)
        return value
    }
}
export class ErrorEvent_serializer {
    public static write(buffer: SerializerBase, value: ErrorEvent): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForType  = value.type
        valueSerializer.writeString(valueHolderForType)
        const valueHolderForTimeStamp  = value.timeStamp
        valueSerializer.writeInt64(valueHolderForTimeStamp)
        const valueHolderForMessage  = value.message
        valueSerializer.writeString(valueHolderForMessage)
        const valueHolderForFilename  = value.filename
        valueSerializer.writeString(valueHolderForFilename)
        const valueHolderForLineno  = value.lineno
        valueSerializer.writeNumber(valueHolderForLineno)
        const valueHolderForColno  = value.colno
        valueSerializer.writeNumber(valueHolderForColno)
        const valueHolderForError  = value.error
        valueSerializer.holdAndWriteObject(valueHolderForError)
    }
    public static read(buffer: DeserializerBase): ErrorEvent {
        let valueDeserializer : DeserializerBase = buffer
        const typeTmpResult : string = (valueDeserializer.readString() as string)
        const timeStampTmpResult : int64 = valueDeserializer.readInt64()
        const messageTmpResult : string = (valueDeserializer.readString() as string)
        const filenameTmpResult : string = (valueDeserializer.readString() as string)
        const linenoTmpResult : number = (valueDeserializer.readNumber() as number)
        const colnoTmpResult : number = (valueDeserializer.readNumber() as number)
        const errorTmpResult : Object = (valueDeserializer.readObject() as object)
        let value : ErrorEvent = ({type: typeTmpResult, timeStamp: timeStampTmpResult, message: messageTmpResult, filename: filenameTmpResult, lineno: linenoTmpResult, colno: colnoTmpResult, error: errorTmpResult} as ErrorEvent)
        return value
    }
}
export class Event_serializer {
    public static write(buffer: SerializerBase, value: Event): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForType  = value.type
        valueSerializer.writeString(valueHolderForType)
        const valueHolderForTimeStamp  = value.timeStamp
        valueSerializer.writeInt64(valueHolderForTimeStamp)
    }
    public static read(buffer: DeserializerBase): Event {
        let valueDeserializer : DeserializerBase = buffer
        const typeTmpResult : string = (valueDeserializer.readString() as string)
        const timeStampTmpResult : int64 = valueDeserializer.readInt64()
        let value : Event = ({type: typeTmpResult, timeStamp: timeStampTmpResult} as Event)
        return value
    }
}
export class LengthMetricsCustom_serializer {
    public static write(buffer: SerializerBase, value: LengthMetricsCustom): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForUnit  = value.unit
        valueSerializer.writeNumber(valueHolderForUnit)
        const valueHolderForValue  = value.value
        valueSerializer.writeNumber(valueHolderForValue)
    }
    public static read(buffer: DeserializerBase): LengthMetricsCustom {
        let valueDeserializer : DeserializerBase = buffer
        const unitTmpResult : number = (valueDeserializer.readNumber() as number)
        const valueTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : LengthMetricsCustom = ({unit: unitTmpResult, value: valueTmpResult} as LengthMetricsCustom)
        return value
    }
}
export class MessageEvents_serializer {
    public static write(buffer: SerializerBase, value: MessageEvents): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForType  = value.type
        valueSerializer.writeString(valueHolderForType)
        const valueHolderForTimeStamp  = value.timeStamp
        valueSerializer.writeInt64(valueHolderForTimeStamp)
        const valueHolderForData  = value.data
        valueSerializer.holdAndWriteObject(valueHolderForData)
    }
    public static read(buffer: DeserializerBase): MessageEvents {
        let valueDeserializer : DeserializerBase = buffer
        const typeTmpResult : string = (valueDeserializer.readString() as string)
        const timeStampTmpResult : int64 = valueDeserializer.readInt64()
        const dataTmpResult : object = (valueDeserializer.readObject() as object)
        let value : MessageEvents = ({type: typeTmpResult, timeStamp: timeStampTmpResult, data: dataTmpResult} as MessageEvents)
        return value
    }
}
export class ParticlePropertyAnimationNumberInner_serializer {
    public static write(buffer: SerializerBase, value: ParticlePropertyAnimationNumberInner): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForFrom  = value.from
        valueSerializer.writeNumber(valueHolderForFrom)
        const valueHolderForTo  = value.to
        valueSerializer.writeNumber(valueHolderForTo)
        const valueHolderForStartMillis  = value.startMillis
        valueSerializer.writeNumber(valueHolderForStartMillis)
        const valueHolderForEndMillis  = value.endMillis
        valueSerializer.writeNumber(valueHolderForEndMillis)
        const valueHolderForCurve  = value.curve
        if (valueHolderForCurve !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCurveTmpValue  = valueHolderForCurve!
            if (valueHolderForCurveTmpValue instanceof curves.Curve) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForCurveTmpValueForIdx0  = valueHolderForCurveTmpValue as curves.Curve
                valueSerializer.writeInt32(valueHolderForCurveTmpValueForIdx0.valueOf())
            } else if (valueHolderForCurveTmpValue instanceof curves.ICurve) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForCurveTmpValueForIdx1  = valueHolderForCurveTmpValue as curves.ICurve
                curves_ICurve_serializer.write(valueSerializer, valueHolderForCurveTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ParticlePropertyAnimationNumberInner {
        let valueDeserializer : DeserializerBase = buffer
        const fromTmpResult : number = (valueDeserializer.readNumber() as number)
        const toTmpResult : number = (valueDeserializer.readNumber() as number)
        const startMillisTmpResult : number = (valueDeserializer.readNumber() as number)
        const endMillisTmpResult : number = (valueDeserializer.readNumber() as number)
        const curveTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let curveTmpBuf : curves.Curve | curves.ICurve | undefined = undefined
        if ((curveTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const curveTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let curveTmpBuf_ : curves.Curve | curves.ICurve | undefined
            if (curveTmpBuf_UnionSelector == (0).toChar()) {
                curveTmpBuf_ = curves.Curve.fromValue(valueDeserializer.readInt32())
            } else if (curveTmpBuf_UnionSelector == (1).toChar()) {
                curveTmpBuf_ = (curves_ICurve_serializer.read(valueDeserializer) as curves.ICurve)
            } else {
                throw new Error("One of the branches for curveTmpBuf_ has to be chosen through deserialisation.")
            }
            curveTmpBuf = (curveTmpBuf_ as curves.Curve | curves.ICurve)
        }
        const curveTmpResult : curves.Curve | curves.ICurve | undefined = curveTmpBuf
        let value : ParticlePropertyAnimationNumberInner = ({from: fromTmpResult, to: toTmpResult, startMillis: startMillisTmpResult, endMillis: endMillisTmpResult, curve: curveTmpResult} as ParticlePropertyAnimationNumberInner)
        return value
    }
}
export class ParticlesInner_serializer {
    public static write(buffer: SerializerBase, value: ParticlesInner): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForParticles  = value.particles
        valueSerializer.writeInt32((valueHolderForParticles.length).toInt())
        for (let valueHolderForParticlesCounterI = 0; valueHolderForParticlesCounterI < valueHolderForParticles.length; valueHolderForParticlesCounterI++) {
            const valueHolderForParticlesTmpElement : ParticleOptionsInner = valueHolderForParticles[valueHolderForParticlesCounterI]
            ParticleOptionsInner_serializer.write(valueSerializer, valueHolderForParticlesTmpElement)
        }
    }
    public static read(buffer: DeserializerBase): ParticlesInner {
        let valueDeserializer : DeserializerBase = buffer
        const particlesTmpBufLength : int32 = valueDeserializer.readInt32()
        let particlesTmpBuf : Array<ParticleOptionsInner> = new Array<ParticleOptionsInner>(particlesTmpBufLength)
        for (let particlesTmpBufBufCounterI = 0; particlesTmpBufBufCounterI < particlesTmpBufLength; particlesTmpBufBufCounterI++) {
            particlesTmpBuf[particlesTmpBufBufCounterI] = ParticleOptionsInner_serializer.read(valueDeserializer)
        }
        const particlesTmpResult : Array<ParticleOptionsInner> = particlesTmpBuf
        let value : ParticlesInner = ({particles: particlesTmpResult} as ParticlesInner)
        return value
    }
}
export class PositionLengthMetricsInner_serializer {
    public static write(buffer: SerializerBase, value: PositionLengthMetricsInner): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForX  = value.x
        LengthMetrics_serializer.write(valueSerializer, valueHolderForX)
        const valueHolderForY  = value.y
        LengthMetrics_serializer.write(valueSerializer, valueHolderForY)
    }
    public static read(buffer: DeserializerBase): PositionLengthMetricsInner {
        let valueDeserializer : DeserializerBase = buffer
        const xTmpResult : LengthMetrics = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        const yTmpResult : LengthMetrics = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        let value : PositionLengthMetricsInner = ({x: xTmpResult, y: yTmpResult} as PositionLengthMetricsInner)
        return value
    }
}
export class PostMessageOptions_serializer {
    public static write(buffer: SerializerBase, value: PostMessageOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTransfer  = value.transfer
        if (valueHolderForTransfer !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTransferTmpValue  = valueHolderForTransfer!
            valueSerializer.writeInt32((valueHolderForTransferTmpValue.length).toInt())
            for (let valueHolderForTransferTmpValueCounterI = 0; valueHolderForTransferTmpValueCounterI < valueHolderForTransferTmpValue.length; valueHolderForTransferTmpValueCounterI++) {
                const valueHolderForTransferTmpValueTmpElement : Object = valueHolderForTransferTmpValue[valueHolderForTransferTmpValueCounterI]
                valueSerializer.holdAndWriteObject(valueHolderForTransferTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): PostMessageOptions {
        let valueDeserializer : DeserializerBase = buffer
        const transferTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let transferTmpBuf : Array<Object> | undefined = undefined
        if ((transferTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const transferTmpBuf_Length : int32 = valueDeserializer.readInt32()
            let transferTmpBuf_ : Array<Object> = new Array<Object>(transferTmpBuf_Length)
            for (let transferTmpBuf_BufCounterI = 0; transferTmpBuf_BufCounterI < transferTmpBuf_Length; transferTmpBuf_BufCounterI++) {
                transferTmpBuf_[transferTmpBuf_BufCounterI] = (valueDeserializer.readObject() as object)
            }
            transferTmpBuf = transferTmpBuf_
        }
        const transferTmpResult : Array<Object> | undefined = transferTmpBuf
        let value : PostMessageOptions = ({transfer: transferTmpResult} as PostMessageOptions)
        return value
    }
}
export class SizeTLengthMetrics_serializer {
    public static write(buffer: SerializerBase, value: SizeTLengthMetrics): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForWidth  = value.width
        LengthMetrics_serializer.write(valueSerializer, valueHolderForWidth)
        const valueHolderForHeight  = value.height
        LengthMetrics_serializer.write(valueSerializer, valueHolderForHeight)
    }
    public static read(buffer: DeserializerBase): SizeTLengthMetrics {
        let valueDeserializer : DeserializerBase = buffer
        const widthTmpResult : LengthMetrics = LengthMetrics_serializer.read(valueDeserializer)
        const heightTmpResult : LengthMetrics = LengthMetrics_serializer.read(valueDeserializer)
        let value : SizeTLengthMetrics = ({width: widthTmpResult, height: heightTmpResult} as SizeTLengthMetrics)
        return value
    }
}
export class SnapshotOptions_serializer {
    public static write(buffer: SerializerBase, value: SnapshotOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForScale  = value.scale
        if (valueHolderForScale !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForScaleTmpValue  = valueHolderForScale!
            valueSerializer.writeNumber(valueHolderForScaleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWaitUntilRenderFinished  = value.waitUntilRenderFinished
        if (valueHolderForWaitUntilRenderFinished !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWaitUntilRenderFinishedTmpValue  = valueHolderForWaitUntilRenderFinished!
            valueSerializer.writeBoolean(valueHolderForWaitUntilRenderFinishedTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SnapshotOptions {
        let valueDeserializer : DeserializerBase = buffer
        const scaleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let scaleTmpBuf : number | undefined = undefined
        if ((scaleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            scaleTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const scaleTmpResult : number | undefined = scaleTmpBuf
        const waitUntilRenderFinishedTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let waitUntilRenderFinishedTmpBuf : boolean | undefined = undefined
        if ((waitUntilRenderFinishedTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            waitUntilRenderFinishedTmpBuf = valueDeserializer.readBoolean()
        }
        const waitUntilRenderFinishedTmpResult : boolean | undefined = waitUntilRenderFinishedTmpBuf
        let value : SnapshotOptions = ({scale: scaleTmpResult, waitUntilRenderFinished: waitUntilRenderFinishedTmpResult} as SnapshotOptions)
        return value
    }
}
export class WorkerOptions_serializer {
    public static write(buffer: SerializerBase, value: WorkerOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForType  = value.type
        if (valueHolderForType !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTypeTmpValue  = valueHolderForType!
            valueSerializer.writeString(valueHolderForTypeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForName  = value.name
        if (valueHolderForName !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForNameTmpValue  = valueHolderForName!
            valueSerializer.writeString(valueHolderForNameTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShared  = value.shared
        if (valueHolderForShared !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSharedTmpValue  = valueHolderForShared!
            valueSerializer.writeBoolean(valueHolderForSharedTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): WorkerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const typeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let typeTmpBuf : string | undefined = undefined
        if ((typeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            typeTmpBuf = (valueDeserializer.readString() as string)
        }
        const typeTmpResult : string | undefined = typeTmpBuf
        const nameTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let nameTmpBuf : string | undefined = undefined
        if ((nameTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            nameTmpBuf = (valueDeserializer.readString() as string)
        }
        const nameTmpResult : string | undefined = nameTmpBuf
        const sharedTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let sharedTmpBuf : boolean | undefined = undefined
        if ((sharedTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            sharedTmpBuf = valueDeserializer.readBoolean()
        }
        const sharedTmpResult : boolean | undefined = sharedTmpBuf
        let value : WorkerOptions = ({type: typeTmpResult, name: nameTmpResult, shared: sharedTmpResult} as WorkerOptions)
        return value
    }
}
export class ComponentInfo_serializer {
    public static write(buffer: SerializerBase, value: ComponentInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSize  = value.size
        Size_serializer.write(valueSerializer, valueHolderForSize)
        const valueHolderForLocalOffset  = value.localOffset
        Offset_componentutils_serializer.write(valueSerializer, valueHolderForLocalOffset)
        const valueHolderForWindowOffset  = value.windowOffset
        Offset_componentutils_serializer.write(valueSerializer, valueHolderForWindowOffset)
        const valueHolderForScreenOffset  = value.screenOffset
        Offset_componentutils_serializer.write(valueSerializer, valueHolderForScreenOffset)
        const valueHolderForTranslate  = value.translate
        TranslateResult_serializer.write(valueSerializer, valueHolderForTranslate)
        const valueHolderForScale  = value.scale
        ScaleResult_serializer.write(valueSerializer, valueHolderForScale)
        const valueHolderForRotate  = value.rotate
        RotateResult_serializer.write(valueSerializer, valueHolderForRotate)
        const valueHolderForTransform  = value.transform
        const valueHolderForTransform_0  = valueHolderForTransform[0]
        valueSerializer.writeNumber(valueHolderForTransform_0)
        const valueHolderForTransform_1  = valueHolderForTransform[1]
        valueSerializer.writeNumber(valueHolderForTransform_1)
        const valueHolderForTransform_2  = valueHolderForTransform[2]
        valueSerializer.writeNumber(valueHolderForTransform_2)
        const valueHolderForTransform_3  = valueHolderForTransform[3]
        valueSerializer.writeNumber(valueHolderForTransform_3)
        const valueHolderForTransform_4  = valueHolderForTransform[4]
        valueSerializer.writeNumber(valueHolderForTransform_4)
        const valueHolderForTransform_5  = valueHolderForTransform[5]
        valueSerializer.writeNumber(valueHolderForTransform_5)
        const valueHolderForTransform_6  = valueHolderForTransform[6]
        valueSerializer.writeNumber(valueHolderForTransform_6)
        const valueHolderForTransform_7  = valueHolderForTransform[7]
        valueSerializer.writeNumber(valueHolderForTransform_7)
        const valueHolderForTransform_8  = valueHolderForTransform[8]
        valueSerializer.writeNumber(valueHolderForTransform_8)
        const valueHolderForTransform_9  = valueHolderForTransform[9]
        valueSerializer.writeNumber(valueHolderForTransform_9)
        const valueHolderForTransform_10  = valueHolderForTransform[10]
        valueSerializer.writeNumber(valueHolderForTransform_10)
        const valueHolderForTransform_11  = valueHolderForTransform[11]
        valueSerializer.writeNumber(valueHolderForTransform_11)
        const valueHolderForTransform_12  = valueHolderForTransform[12]
        valueSerializer.writeNumber(valueHolderForTransform_12)
        const valueHolderForTransform_13  = valueHolderForTransform[13]
        valueSerializer.writeNumber(valueHolderForTransform_13)
        const valueHolderForTransform_14  = valueHolderForTransform[14]
        valueSerializer.writeNumber(valueHolderForTransform_14)
        const valueHolderForTransform_15  = valueHolderForTransform[15]
        valueSerializer.writeNumber(valueHolderForTransform_15)
    }
    public static read(buffer: DeserializerBase): ComponentInfo {
        let valueDeserializer : DeserializerBase = buffer
        const sizeTmpResult : Size = Size_serializer.read(valueDeserializer)
        const localOffsetTmpResult : Offset_componentutils = Offset_componentutils_serializer.read(valueDeserializer)
        const windowOffsetTmpResult : Offset_componentutils = Offset_componentutils_serializer.read(valueDeserializer)
        const screenOffsetTmpResult : Offset_componentutils = Offset_componentutils_serializer.read(valueDeserializer)
        const translateTmpResult : TranslateResult = TranslateResult_serializer.read(valueDeserializer)
        const scaleTmpResult : ScaleResult = ScaleResult_serializer.read(valueDeserializer)
        const rotateTmpResult : RotateResult = RotateResult_serializer.read(valueDeserializer)
        const transformTmpBufValue0 : number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue1 : number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue2 : number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue3 : number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue4 : number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue5 : number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue6 : number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue7 : number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue8 : number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue9 : number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue10 : number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue11 : number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue12 : number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue13 : number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue14 : number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue15 : number = (valueDeserializer.readNumber() as number)
        const transformTmpResult : Matrix4Result = ([transformTmpBufValue0, transformTmpBufValue1, transformTmpBufValue2, transformTmpBufValue3, transformTmpBufValue4, transformTmpBufValue5, transformTmpBufValue6, transformTmpBufValue7, transformTmpBufValue8, transformTmpBufValue9, transformTmpBufValue10, transformTmpBufValue11, transformTmpBufValue12, transformTmpBufValue13, transformTmpBufValue14, transformTmpBufValue15] as Matrix4Result)
        let value : ComponentInfo = ({size: sizeTmpResult, localOffset: localOffsetTmpResult, windowOffset: windowOffsetTmpResult, screenOffset: screenOffsetTmpResult, translate: translateTmpResult, scale: scaleTmpResult, rotate: rotateTmpResult, transform: transformTmpResult} as ComponentInfo)
        return value
    }
}
export class NodeEdgesLengthMetrics_serializer {
    public static write(buffer: SerializerBase, value: NodeEdgesLengthMetrics): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTop  = value.top
        if (valueHolderForTop !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTopTmpValue  = valueHolderForTop!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForTopTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLeft  = value.left
        if (valueHolderForLeft !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLeftTmpValue  = valueHolderForLeft!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForLeftTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBottom  = value.bottom
        if (valueHolderForBottom !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBottomTmpValue  = valueHolderForBottom!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForBottomTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRight  = value.right
        if (valueHolderForRight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRightTmpValue  = valueHolderForRight!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForRightTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): NodeEdgesLengthMetrics {
        let valueDeserializer : DeserializerBase = buffer
        const topTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let topTmpBuf : LengthMetrics | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            topTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const topTmpResult : LengthMetrics | undefined = topTmpBuf
        const leftTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let leftTmpBuf : LengthMetrics | undefined = undefined
        if ((leftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            leftTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const leftTmpResult : LengthMetrics | undefined = leftTmpBuf
        const bottomTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let bottomTmpBuf : LengthMetrics | undefined = undefined
        if ((bottomTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            bottomTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const bottomTmpResult : LengthMetrics | undefined = bottomTmpBuf
        const rightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let rightTmpBuf : LengthMetrics | undefined = undefined
        if ((rightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            rightTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const rightTmpResult : LengthMetrics | undefined = rightTmpBuf
        let value : NodeEdgesLengthMetrics = ({top: topTmpResult, left: leftTmpResult, bottom: bottomTmpResult, right: rightTmpResult} as NodeEdgesLengthMetrics)
        return value
    }
}
export class PageRouterOptions_serializer {
    public static write(buffer: SerializerBase, value: PageRouterOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForOptions  = value.options
        router_RouterOptions_serializer.write(valueSerializer, valueHolderForOptions)
        const valueHolderForMode  = value.mode
        if (valueHolderForMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForModeTmpValue  = (valueHolderForMode as router.RouterMode)
            valueSerializer.writeInt32(valueHolderForModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): PageRouterOptions {
        let valueDeserializer : DeserializerBase = buffer
        const optionsTmpResult : router.RouterOptions = router_RouterOptions_serializer.read(valueDeserializer)
        const modeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let modeTmpBuf : router.RouterMode | undefined = undefined
        if ((modeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            modeTmpBuf = router.RouterMode.fromValue(valueDeserializer.readInt32())
        }
        const modeTmpResult : router.RouterMode | undefined = modeTmpBuf
        let value : PageRouterOptions = ({options: optionsTmpResult, mode: modeTmpResult} as PageRouterOptions)
        return value
    }
}
export class ParticleAnnulusRegionInner_serializer {
    public static write(buffer: SerializerBase, value: ParticleAnnulusRegionInner): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForCenter  = value.center
        if (valueHolderForCenter !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCenterTmpValue  = valueHolderForCenter!
            PositionLengthMetricsInner_serializer.write(valueSerializer, valueHolderForCenterTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOuterRadius  = value.outerRadius
        LengthMetrics_serializer.write(valueSerializer, valueHolderForOuterRadius)
        const valueHolderForInnerRadius  = value.innerRadius
        LengthMetrics_serializer.write(valueSerializer, valueHolderForInnerRadius)
        const valueHolderForStartAngle  = value.startAngle
        if (valueHolderForStartAngle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartAngleTmpValue  = valueHolderForStartAngle!
            valueSerializer.writeNumber(valueHolderForStartAngleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEndAngle  = value.endAngle
        if (valueHolderForEndAngle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndAngleTmpValue  = valueHolderForEndAngle!
            valueSerializer.writeNumber(valueHolderForEndAngleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ParticleAnnulusRegionInner {
        let valueDeserializer : DeserializerBase = buffer
        const centerTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let centerTmpBuf : PositionLengthMetricsInner | undefined = undefined
        if ((centerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            centerTmpBuf = PositionLengthMetricsInner_serializer.read(valueDeserializer)
        }
        const centerTmpResult : PositionLengthMetricsInner | undefined = centerTmpBuf
        const outerRadiusTmpResult : LengthMetrics = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        const innerRadiusTmpResult : LengthMetrics = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        const startAngleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let startAngleTmpBuf : number | undefined = undefined
        if ((startAngleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startAngleTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const startAngleTmpResult : number | undefined = startAngleTmpBuf
        const endAngleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let endAngleTmpBuf : number | undefined = undefined
        if ((endAngleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endAngleTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const endAngleTmpResult : number | undefined = endAngleTmpBuf
        let value : ParticleAnnulusRegionInner = ({center: centerTmpResult, outerRadius: outerRadiusTmpResult, innerRadius: innerRadiusTmpResult, startAngle: startAngleTmpResult, endAngle: endAngleTmpResult} as ParticleAnnulusRegionInner)
        return value
    }
}
export class ParticleColorUpdaterOptionsInner_serializer {
    public static write(buffer: SerializerBase, value: ParticleColorUpdaterOptionsInner): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForType  = value.type
        valueSerializer.writeInt32(valueHolderForType.getOrdinal())
        const valueHolderForConfig  = value.config
        if (valueHolderForConfig !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForConfigTmpValue  = valueHolderForConfig!
            if (valueHolderForConfigTmpValue instanceof ParticleColorOptions) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForConfigTmpValueForIdx0  = valueHolderForConfigTmpValue as ParticleColorOptions
                ParticleColorOptions_serializer.write(valueSerializer, valueHolderForConfigTmpValueForIdx0)
            } else if (TypeChecker.isArray_ParticlePropertyAnimationColorInner(valueHolderForConfigTmpValue)) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForConfigTmpValueForIdx1  = valueHolderForConfigTmpValue as Array<ParticlePropertyAnimationColorInner>
                valueSerializer.writeInt32((valueHolderForConfigTmpValueForIdx1.length).toInt())
                for (let valueHolderForConfigTmpValueForIdx1CounterI = 0; valueHolderForConfigTmpValueForIdx1CounterI < valueHolderForConfigTmpValueForIdx1.length; valueHolderForConfigTmpValueForIdx1CounterI++) {
                    const valueHolderForConfigTmpValueForIdx1TmpElement : ParticlePropertyAnimationColorInner = valueHolderForConfigTmpValueForIdx1[valueHolderForConfigTmpValueForIdx1CounterI]
                    ParticlePropertyAnimationColorInner_serializer.write(valueSerializer, valueHolderForConfigTmpValueForIdx1TmpElement)
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ParticleColorUpdaterOptionsInner {
        let valueDeserializer : DeserializerBase = buffer
        const typeTmpResult : ParticleUpdater = ParticleUpdater.values()[valueDeserializer.readInt32()]
        const configTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let configTmpBuf : ParticleColorOptions | Array<ParticlePropertyAnimationColorInner> | undefined = undefined
        if ((configTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const configTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let configTmpBuf_ : ParticleColorOptions | Array<ParticlePropertyAnimationColorInner> | undefined
            if (configTmpBuf_UnionSelector == (0).toChar()) {
                configTmpBuf_ = ParticleColorOptions_serializer.read(valueDeserializer)
            } else if (configTmpBuf_UnionSelector == (1).toChar()) {
                const configTmpBuf_BufULength : int32 = valueDeserializer.readInt32()
                let configTmpBuf_BufU : Array<ParticlePropertyAnimationColorInner> = new Array<ParticlePropertyAnimationColorInner>(configTmpBuf_BufULength)
                for (let configTmpBuf_BufUBufCounterI = 0; configTmpBuf_BufUBufCounterI < configTmpBuf_BufULength; configTmpBuf_BufUBufCounterI++) {
                    configTmpBuf_BufU[configTmpBuf_BufUBufCounterI] = ParticlePropertyAnimationColorInner_serializer.read(valueDeserializer)
                }
                configTmpBuf_ = configTmpBuf_BufU
            } else {
                throw new Error("One of the branches for configTmpBuf_ has to be chosen through deserialisation.")
            }
            configTmpBuf = (configTmpBuf_ as ParticleColorOptions | Array<ParticlePropertyAnimationColorInner>)
        }
        const configTmpResult : ParticleColorPropertyUpdaterConfigsInner = configTmpBuf
        let value : ParticleColorUpdaterOptionsInner = ({type: typeTmpResult, config: configTmpResult} as ParticleColorUpdaterOptionsInner)
        return value
    }
}
export class ParticlePropertyAnimationColorInner_serializer {
    public static write(buffer: SerializerBase, value: ParticlePropertyAnimationColorInner): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForFrom  = value.from
        if (valueHolderForFrom instanceof Color) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForFromForIdx0  = valueHolderForFrom as Color
            valueSerializer.writeInt32(valueHolderForFromForIdx0.getOrdinal())
        } else if (valueHolderForFrom instanceof number) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForFromForIdx1  = valueHolderForFrom as number
            valueSerializer.writeNumber(valueHolderForFromForIdx1)
        } else if (valueHolderForFrom instanceof string) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForFromForIdx2  = valueHolderForFrom as string
            valueSerializer.writeString(valueHolderForFromForIdx2)
        } else if (valueHolderForFrom instanceof Resource) {
            valueSerializer.writeInt8((3).toByte())
            const valueHolderForFromForIdx3  = valueHolderForFrom as Resource
            Resource_serializer.write(valueSerializer, valueHolderForFromForIdx3)
        }
        const valueHolderForTo  = value.to
        if (valueHolderForTo instanceof Color) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForToForIdx0  = valueHolderForTo as Color
            valueSerializer.writeInt32(valueHolderForToForIdx0.getOrdinal())
        } else if (valueHolderForTo instanceof number) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForToForIdx1  = valueHolderForTo as number
            valueSerializer.writeNumber(valueHolderForToForIdx1)
        } else if (valueHolderForTo instanceof string) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForToForIdx2  = valueHolderForTo as string
            valueSerializer.writeString(valueHolderForToForIdx2)
        } else if (valueHolderForTo instanceof Resource) {
            valueSerializer.writeInt8((3).toByte())
            const valueHolderForToForIdx3  = valueHolderForTo as Resource
            Resource_serializer.write(valueSerializer, valueHolderForToForIdx3)
        }
        const valueHolderForStartMillis  = value.startMillis
        valueSerializer.writeNumber(valueHolderForStartMillis)
        const valueHolderForEndMillis  = value.endMillis
        valueSerializer.writeNumber(valueHolderForEndMillis)
        const valueHolderForCurve  = value.curve
        if (valueHolderForCurve !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCurveTmpValue  = valueHolderForCurve!
            if (valueHolderForCurveTmpValue instanceof curves.Curve) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForCurveTmpValueForIdx0  = valueHolderForCurveTmpValue as curves.Curve
                valueSerializer.writeInt32(valueHolderForCurveTmpValueForIdx0.valueOf())
            } else if (valueHolderForCurveTmpValue instanceof curves.ICurve) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForCurveTmpValueForIdx1  = valueHolderForCurveTmpValue as curves.ICurve
                curves_ICurve_serializer.write(valueSerializer, valueHolderForCurveTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ParticlePropertyAnimationColorInner {
        let valueDeserializer : DeserializerBase = buffer
        const fromTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let fromTmpBuf : Color | number | string | Resource | undefined
        if (fromTmpBufUnionSelector == (0).toChar()) {
            fromTmpBuf = Color.values()[valueDeserializer.readInt32()]
        } else if (fromTmpBufUnionSelector == (1).toChar()) {
            fromTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (fromTmpBufUnionSelector == (2).toChar()) {
            fromTmpBuf = (valueDeserializer.readString() as string)
        } else if (fromTmpBufUnionSelector == (3).toChar()) {
            fromTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for fromTmpBuf has to be chosen through deserialisation.")
        }
        const fromTmpResult : ResourceColor = (fromTmpBuf as Color | number | string | Resource)
        const toTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let toTmpBuf : Color | number | string | Resource | undefined
        if (toTmpBufUnionSelector == (0).toChar()) {
            toTmpBuf = Color.values()[valueDeserializer.readInt32()]
        } else if (toTmpBufUnionSelector == (1).toChar()) {
            toTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (toTmpBufUnionSelector == (2).toChar()) {
            toTmpBuf = (valueDeserializer.readString() as string)
        } else if (toTmpBufUnionSelector == (3).toChar()) {
            toTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for toTmpBuf has to be chosen through deserialisation.")
        }
        const toTmpResult : ResourceColor = (toTmpBuf as Color | number | string | Resource)
        const startMillisTmpResult : number = (valueDeserializer.readNumber() as number)
        const endMillisTmpResult : number = (valueDeserializer.readNumber() as number)
        const curveTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let curveTmpBuf : curves.Curve | curves.ICurve | undefined = undefined
        if ((curveTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const curveTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let curveTmpBuf_ : curves.Curve | curves.ICurve | undefined
            if (curveTmpBuf_UnionSelector == (0).toChar()) {
                curveTmpBuf_ = curves.Curve.fromValue(valueDeserializer.readInt32())
            } else if (curveTmpBuf_UnionSelector == (1).toChar()) {
                curveTmpBuf_ = (curves_ICurve_serializer.read(valueDeserializer) as curves.ICurve)
            } else {
                throw new Error("One of the branches for curveTmpBuf_ has to be chosen through deserialisation.")
            }
            curveTmpBuf = (curveTmpBuf_ as curves.Curve | curves.ICurve)
        }
        const curveTmpResult : curves.Curve | curves.ICurve | undefined = curveTmpBuf
        let value : ParticlePropertyAnimationColorInner = ({from: fromTmpResult, to: toTmpResult, startMillis: startMillisTmpResult, endMillis: endMillisTmpResult, curve: curveTmpResult} as ParticlePropertyAnimationColorInner)
        return value
    }
}
export class ParticleUpdaterOptionsInner_serializer {
    public static write(buffer: SerializerBase, value: ParticleUpdaterOptionsInner): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForType  = value.type
        valueSerializer.writeInt32(valueHolderForType.getOrdinal())
        const valueHolderForConfig  = value.config
        if (valueHolderForConfig !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForConfigTmpValue  = valueHolderForConfig!
            if (valueHolderForConfigTmpValue instanceof [ number, number ]) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForConfigTmpValueForIdx0  = valueHolderForConfigTmpValue as [ number, number ]
                const valueHolderForConfigTmpValueForIdx0_0  = valueHolderForConfigTmpValueForIdx0[0]
                valueSerializer.writeNumber(valueHolderForConfigTmpValueForIdx0_0)
                const valueHolderForConfigTmpValueForIdx0_1  = valueHolderForConfigTmpValueForIdx0[1]
                valueSerializer.writeNumber(valueHolderForConfigTmpValueForIdx0_1)
            } else if (TypeChecker.isArray_ParticlePropertyAnimationNumberInner(valueHolderForConfigTmpValue)) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForConfigTmpValueForIdx1  = valueHolderForConfigTmpValue as Array<ParticlePropertyAnimationNumberInner>
                valueSerializer.writeInt32((valueHolderForConfigTmpValueForIdx1.length).toInt())
                for (let valueHolderForConfigTmpValueForIdx1CounterI = 0; valueHolderForConfigTmpValueForIdx1CounterI < valueHolderForConfigTmpValueForIdx1.length; valueHolderForConfigTmpValueForIdx1CounterI++) {
                    const valueHolderForConfigTmpValueForIdx1TmpElement : ParticlePropertyAnimationNumberInner = valueHolderForConfigTmpValueForIdx1[valueHolderForConfigTmpValueForIdx1CounterI]
                    ParticlePropertyAnimationNumberInner_serializer.write(valueSerializer, valueHolderForConfigTmpValueForIdx1TmpElement)
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ParticleUpdaterOptionsInner {
        let valueDeserializer : DeserializerBase = buffer
        const typeTmpResult : ParticleUpdater = ParticleUpdater.values()[valueDeserializer.readInt32()]
        const configTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let configTmpBuf : [ number, number ] | Array<ParticlePropertyAnimationNumberInner> | undefined = undefined
        if ((configTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const configTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let configTmpBuf_ : [ number, number ] | Array<ParticlePropertyAnimationNumberInner> | undefined
            if (configTmpBuf_UnionSelector == (0).toChar()) {
                const configTmpBuf_BufUValue0 : number = (valueDeserializer.readNumber() as number)
                const configTmpBuf_BufUValue1 : number = (valueDeserializer.readNumber() as number)
                configTmpBuf_ = ([configTmpBuf_BufUValue0, configTmpBuf_BufUValue1] as [ number, number ])
            } else if (configTmpBuf_UnionSelector == (1).toChar()) {
                const configTmpBuf_BufULength : int32 = valueDeserializer.readInt32()
                let configTmpBuf_BufU : Array<ParticlePropertyAnimationNumberInner> = new Array<ParticlePropertyAnimationNumberInner>(configTmpBuf_BufULength)
                for (let configTmpBuf_BufUBufCounterI = 0; configTmpBuf_BufUBufCounterI < configTmpBuf_BufULength; configTmpBuf_BufUBufCounterI++) {
                    configTmpBuf_BufU[configTmpBuf_BufUBufCounterI] = ParticlePropertyAnimationNumberInner_serializer.read(valueDeserializer)
                }
                configTmpBuf_ = configTmpBuf_BufU
            } else {
                throw new Error("One of the branches for configTmpBuf_ has to be chosen through deserialisation.")
            }
            configTmpBuf = (configTmpBuf_ as [ number, number ] | Array<ParticlePropertyAnimationNumberInner>)
        }
        const configTmpResult : ParticlePropertyUpdaterConfigsInner = configTmpBuf
        let value : ParticleUpdaterOptionsInner = ({type: typeTmpResult, config: configTmpResult} as ParticleUpdaterOptionsInner)
        return value
    }
}
export class RestrictedWorker_serializer {
    public static write(buffer: SerializerBase, value: RestrictedWorker): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): RestrictedWorker {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return RestrictedWorkerInternal.fromPtr(ptr)
    }
}
export class EmitterPropertyInner_serializer {
    public static write(buffer: SerializerBase, value: EmitterPropertyInner): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForIndex  = value.index
        valueSerializer.writeNumber(valueHolderForIndex)
        const valueHolderForEmitRate  = value.emitRate
        if (valueHolderForEmitRate !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEmitRateTmpValue  = valueHolderForEmitRate!
            valueSerializer.writeNumber(valueHolderForEmitRateTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPosition  = value.position
        if (valueHolderForPosition !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPositionTmpValue  = valueHolderForPosition!
            PositionNumberInner_serializer.write(valueSerializer, valueHolderForPositionTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSize  = value.size
        if (valueHolderForSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSizeTmpValue  = valueHolderForSize!
            SizeNumberInner_serializer.write(valueSerializer, valueHolderForSizeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAnnulusRegion  = value.annulusRegion
        if (valueHolderForAnnulusRegion !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAnnulusRegionTmpValue  = valueHolderForAnnulusRegion!
            ParticleAnnulusRegionInner_serializer.write(valueSerializer, valueHolderForAnnulusRegionTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): EmitterPropertyInner {
        let valueDeserializer : DeserializerBase = buffer
        const indexTmpResult : number = (valueDeserializer.readNumber() as number)
        const emitRateTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let emitRateTmpBuf : number | undefined = undefined
        if ((emitRateTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            emitRateTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const emitRateTmpResult : number | undefined = emitRateTmpBuf
        const positionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let positionTmpBuf : PositionNumberInner | undefined = undefined
        if ((positionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            positionTmpBuf = PositionNumberInner_serializer.read(valueDeserializer)
        }
        const positionTmpResult : PositionNumberInner | undefined = positionTmpBuf
        const sizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let sizeTmpBuf : SizeNumberInner | undefined = undefined
        if ((sizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            sizeTmpBuf = SizeNumberInner_serializer.read(valueDeserializer)
        }
        const sizeTmpResult : SizeNumberInner | undefined = sizeTmpBuf
        const annulusRegionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let annulusRegionTmpBuf : ParticleAnnulusRegionInner | undefined = undefined
        if ((annulusRegionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            annulusRegionTmpBuf = ParticleAnnulusRegionInner_serializer.read(valueDeserializer)
        }
        const annulusRegionTmpResult : ParticleAnnulusRegionInner | undefined = annulusRegionTmpBuf
        let value : EmitterPropertyInner = ({index: indexTmpResult, emitRate: emitRateTmpResult, position: positionTmpResult, size: sizeTmpResult, annulusRegion: annulusRegionTmpResult} as EmitterPropertyInner)
        return value
    }
}
export class ParticleColorPropertyOptionsInner_serializer {
    public static write(buffer: SerializerBase, value: ParticleColorPropertyOptionsInner): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForRange  = value.range
        const valueHolderForRange_0  = valueHolderForRange[0]
        if (valueHolderForRange_0 instanceof Color) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForRange_0ForIdx0  = valueHolderForRange_0 as Color
            valueSerializer.writeInt32(valueHolderForRange_0ForIdx0.getOrdinal())
        } else if (valueHolderForRange_0 instanceof number) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForRange_0ForIdx1  = valueHolderForRange_0 as number
            valueSerializer.writeNumber(valueHolderForRange_0ForIdx1)
        } else if (valueHolderForRange_0 instanceof string) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForRange_0ForIdx2  = valueHolderForRange_0 as string
            valueSerializer.writeString(valueHolderForRange_0ForIdx2)
        } else if (valueHolderForRange_0 instanceof Resource) {
            valueSerializer.writeInt8((3).toByte())
            const valueHolderForRange_0ForIdx3  = valueHolderForRange_0 as Resource
            Resource_serializer.write(valueSerializer, valueHolderForRange_0ForIdx3)
        }
        const valueHolderForRange_1  = valueHolderForRange[1]
        if (valueHolderForRange_1 instanceof Color) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForRange_1ForIdx0  = valueHolderForRange_1 as Color
            valueSerializer.writeInt32(valueHolderForRange_1ForIdx0.getOrdinal())
        } else if (valueHolderForRange_1 instanceof number) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForRange_1ForIdx1  = valueHolderForRange_1 as number
            valueSerializer.writeNumber(valueHolderForRange_1ForIdx1)
        } else if (valueHolderForRange_1 instanceof string) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForRange_1ForIdx2  = valueHolderForRange_1 as string
            valueSerializer.writeString(valueHolderForRange_1ForIdx2)
        } else if (valueHolderForRange_1 instanceof Resource) {
            valueSerializer.writeInt8((3).toByte())
            const valueHolderForRange_1ForIdx3  = valueHolderForRange_1 as Resource
            Resource_serializer.write(valueSerializer, valueHolderForRange_1ForIdx3)
        }
        const valueHolderForDistributionType  = value.distributionType
        if (valueHolderForDistributionType !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDistributionTypeTmpValue  = (valueHolderForDistributionType as DistributionType)
            valueSerializer.writeInt32(valueHolderForDistributionTypeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForUpdater  = value.updater
        if (valueHolderForUpdater !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUpdaterTmpValue  = valueHolderForUpdater!
            ParticleColorUpdaterOptionsInner_serializer.write(valueSerializer, valueHolderForUpdaterTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ParticleColorPropertyOptionsInner {
        let valueDeserializer : DeserializerBase = buffer
        const rangeTmpBufValue0TempBufUnionSelector : int32 = valueDeserializer.readInt8()
        let rangeTmpBufValue0TempBuf : Color | number | string | Resource | undefined
        if (rangeTmpBufValue0TempBufUnionSelector == (0).toChar()) {
            rangeTmpBufValue0TempBuf = Color.values()[valueDeserializer.readInt32()]
        } else if (rangeTmpBufValue0TempBufUnionSelector == (1).toChar()) {
            rangeTmpBufValue0TempBuf = (valueDeserializer.readNumber() as number)
        } else if (rangeTmpBufValue0TempBufUnionSelector == (2).toChar()) {
            rangeTmpBufValue0TempBuf = (valueDeserializer.readString() as string)
        } else if (rangeTmpBufValue0TempBufUnionSelector == (3).toChar()) {
            rangeTmpBufValue0TempBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for rangeTmpBufValue0TempBuf has to be chosen through deserialisation.")
        }
        const rangeTmpBufValue0 : ResourceColor = (rangeTmpBufValue0TempBuf as Color | number | string | Resource)
        const rangeTmpBufValue1TempBufUnionSelector : int32 = valueDeserializer.readInt8()
        let rangeTmpBufValue1TempBuf : Color | number | string | Resource | undefined
        if (rangeTmpBufValue1TempBufUnionSelector == (0).toChar()) {
            rangeTmpBufValue1TempBuf = Color.values()[valueDeserializer.readInt32()]
        } else if (rangeTmpBufValue1TempBufUnionSelector == (1).toChar()) {
            rangeTmpBufValue1TempBuf = (valueDeserializer.readNumber() as number)
        } else if (rangeTmpBufValue1TempBufUnionSelector == (2).toChar()) {
            rangeTmpBufValue1TempBuf = (valueDeserializer.readString() as string)
        } else if (rangeTmpBufValue1TempBufUnionSelector == (3).toChar()) {
            rangeTmpBufValue1TempBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for rangeTmpBufValue1TempBuf has to be chosen through deserialisation.")
        }
        const rangeTmpBufValue1 : ResourceColor = (rangeTmpBufValue1TempBuf as Color | number | string | Resource)
        const rangeTmpResult : [ ResourceColor, ResourceColor ] = ([rangeTmpBufValue0, rangeTmpBufValue1] as [ ResourceColor, ResourceColor ])
        const distributionTypeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let distributionTypeTmpBuf : DistributionType | undefined = undefined
        if ((distributionTypeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            distributionTypeTmpBuf = DistributionType.fromValue(valueDeserializer.readInt32())
        }
        const distributionTypeTmpResult : DistributionType | undefined = distributionTypeTmpBuf
        const updaterTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let updaterTmpBuf : ParticleColorUpdaterOptionsInner | undefined = undefined
        if ((updaterTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            updaterTmpBuf = ParticleColorUpdaterOptionsInner_serializer.read(valueDeserializer)
        }
        const updaterTmpResult : ParticleColorUpdaterOptionsInner | undefined = updaterTmpBuf
        let value : ParticleColorPropertyOptionsInner = ({range: rangeTmpResult, distributionType: distributionTypeTmpResult, updater: updaterTmpResult} as ParticleColorPropertyOptionsInner)
        return value
    }
}
export class ParticlePropertyOptionsInner_serializer {
    public static write(buffer: SerializerBase, value: ParticlePropertyOptionsInner): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForRange  = value.range
        const valueHolderForRange_0  = valueHolderForRange[0]
        valueSerializer.writeNumber(valueHolderForRange_0)
        const valueHolderForRange_1  = valueHolderForRange[1]
        valueSerializer.writeNumber(valueHolderForRange_1)
        const valueHolderForUpdater  = value.updater
        if (valueHolderForUpdater !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUpdaterTmpValue  = valueHolderForUpdater!
            ParticleUpdaterOptionsInner_serializer.write(valueSerializer, valueHolderForUpdaterTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ParticlePropertyOptionsInner {
        let valueDeserializer : DeserializerBase = buffer
        const rangeTmpBufValue0 : number = (valueDeserializer.readNumber() as number)
        const rangeTmpBufValue1 : number = (valueDeserializer.readNumber() as number)
        const rangeTmpResult : [ number, number ] = ([rangeTmpBufValue0, rangeTmpBufValue1] as [ number, number ])
        const updaterTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let updaterTmpBuf : ParticleUpdaterOptionsInner | undefined = undefined
        if ((updaterTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            updaterTmpBuf = ParticleUpdaterOptionsInner_serializer.read(valueDeserializer)
        }
        const updaterTmpResult : ParticleUpdaterOptionsInner | undefined = updaterTmpBuf
        let value : ParticlePropertyOptionsInner = ({range: rangeTmpResult, updater: updaterTmpResult} as ParticlePropertyOptionsInner)
        return value
    }
}
export class AccelerationOptionsInner_serializer {
    public static write(buffer: SerializerBase, value: AccelerationOptionsInner): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSpeed  = value.speed
        if (valueHolderForSpeed !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSpeedTmpValue  = valueHolderForSpeed!
            ParticlePropertyOptionsInner_serializer.write(valueSerializer, valueHolderForSpeedTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAngle  = value.angle
        if (valueHolderForAngle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAngleTmpValue  = valueHolderForAngle!
            ParticlePropertyOptionsInner_serializer.write(valueSerializer, valueHolderForAngleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): AccelerationOptionsInner {
        let valueDeserializer : DeserializerBase = buffer
        const speedTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let speedTmpBuf : ParticlePropertyOptionsInner | undefined = undefined
        if ((speedTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            speedTmpBuf = ParticlePropertyOptionsInner_serializer.read(valueDeserializer)
        }
        const speedTmpResult : ParticlePropertyOptionsInner | undefined = speedTmpBuf
        const angleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let angleTmpBuf : ParticlePropertyOptionsInner | undefined = undefined
        if ((angleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            angleTmpBuf = ParticlePropertyOptionsInner_serializer.read(valueDeserializer)
        }
        const angleTmpResult : ParticlePropertyOptionsInner | undefined = angleTmpBuf
        let value : AccelerationOptionsInner = ({speed: speedTmpResult, angle: angleTmpResult} as AccelerationOptionsInner)
        return value
    }
}
export class CustomDialogControllerOptionsExtender_serializer {
    public static write(buffer: SerializerBase, value: CustomDialogControllerOptionsExtender): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForBuilder  = value.builder
        valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueHolderForBuilder))
        const valueHolderForCancel  = value.cancel
        if (valueHolderForCancel !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCancelTmpValue  = valueHolderForCancel!
            valueSerializer.holdAndWriteCallback(valueHolderForCancelTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAutoCancel  = value.autoCancel
        if (valueHolderForAutoCancel !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAutoCancelTmpValue  = valueHolderForAutoCancel!
            valueSerializer.writeBoolean(valueHolderForAutoCancelTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAlignment  = value.alignment
        if (valueHolderForAlignment !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAlignmentTmpValue  = (valueHolderForAlignment as DialogAlignment)
            valueSerializer.writeInt32(valueHolderForAlignmentTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOffset  = value.offset
        if (valueHolderForOffset !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOffsetTmpValue  = valueHolderForOffset!
            Offset_serializer.write(valueSerializer, valueHolderForOffsetTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCustomStyle  = value.customStyle
        if (valueHolderForCustomStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCustomStyleTmpValue  = valueHolderForCustomStyle!
            valueSerializer.writeBoolean(valueHolderForCustomStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForGridCount  = value.gridCount
        if (valueHolderForGridCount !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForGridCountTmpValue  = valueHolderForGridCount!
            valueSerializer.writeInt32(valueHolderForGridCountTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMaskColor  = value.maskColor
        if (valueHolderForMaskColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaskColorTmpValue  = valueHolderForMaskColor!
            if (valueHolderForMaskColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForMaskColorTmpValueForIdx0  = valueHolderForMaskColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForMaskColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForMaskColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForMaskColorTmpValueForIdx1  = valueHolderForMaskColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForMaskColorTmpValueForIdx1)
            } else if (valueHolderForMaskColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForMaskColorTmpValueForIdx2  = valueHolderForMaskColorTmpValue as string
                valueSerializer.writeString(valueHolderForMaskColorTmpValueForIdx2)
            } else if (valueHolderForMaskColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForMaskColorTmpValueForIdx3  = valueHolderForMaskColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForMaskColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMaskRect  = value.maskRect
        if (valueHolderForMaskRect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaskRectTmpValue  = valueHolderForMaskRect!
            Rectangle_serializer.write(valueSerializer, valueHolderForMaskRectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOpenAnimation  = value.openAnimation
        if (valueHolderForOpenAnimation !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOpenAnimationTmpValue  = valueHolderForOpenAnimation!
            AnimateParam_serializer.write(valueSerializer, valueHolderForOpenAnimationTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCloseAnimation  = value.closeAnimation
        if (valueHolderForCloseAnimation !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCloseAnimationTmpValue  = valueHolderForCloseAnimation!
            AnimateParam_serializer.write(valueSerializer, valueHolderForCloseAnimationTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShowInSubWindow  = value.showInSubWindow
        if (valueHolderForShowInSubWindow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShowInSubWindowTmpValue  = valueHolderForShowInSubWindow!
            valueSerializer.writeBoolean(valueHolderForShowInSubWindowTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundColor  = value.backgroundColor
        if (valueHolderForBackgroundColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundColorTmpValue  = valueHolderForBackgroundColor!
            if (valueHolderForBackgroundColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx0  = valueHolderForBackgroundColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForBackgroundColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForBackgroundColorTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx1  = valueHolderForBackgroundColorTmpValue as number
                valueSerializer.writeNumber(valueHolderForBackgroundColorTmpValueForIdx1)
            } else if (valueHolderForBackgroundColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx2  = valueHolderForBackgroundColorTmpValue as string
                valueSerializer.writeString(valueHolderForBackgroundColorTmpValueForIdx2)
            } else if (valueHolderForBackgroundColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx3  = valueHolderForBackgroundColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForBackgroundColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCornerRadius  = value.cornerRadius
        if (valueHolderForCornerRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCornerRadiusTmpValue  = valueHolderForCornerRadius!
            if (valueHolderForCornerRadiusTmpValue instanceof Dimension) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForCornerRadiusTmpValueForIdx0  = valueHolderForCornerRadiusTmpValue as Dimension
                if (valueHolderForCornerRadiusTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForCornerRadiusTmpValueForIdx0ForIdx0  = valueHolderForCornerRadiusTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForCornerRadiusTmpValueForIdx0ForIdx0)
                } else if (valueHolderForCornerRadiusTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForCornerRadiusTmpValueForIdx0ForIdx1  = valueHolderForCornerRadiusTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForCornerRadiusTmpValueForIdx0ForIdx1)
                } else if (valueHolderForCornerRadiusTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForCornerRadiusTmpValueForIdx0ForIdx2  = valueHolderForCornerRadiusTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForCornerRadiusTmpValueForIdx0ForIdx2)
                }
            } else if (valueHolderForCornerRadiusTmpValue instanceof BorderRadiuses) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForCornerRadiusTmpValueForIdx1  = valueHolderForCornerRadiusTmpValue as BorderRadiuses
                BorderRadiuses_serializer.write(valueSerializer, valueHolderForCornerRadiusTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIsModal  = value.isModal
        if (valueHolderForIsModal !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIsModalTmpValue  = valueHolderForIsModal!
            valueSerializer.writeBoolean(valueHolderForIsModalTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnWillDismiss  = value.onWillDismiss
        if (valueHolderForOnWillDismiss !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnWillDismissTmpValue  = valueHolderForOnWillDismiss!
            valueSerializer.holdAndWriteCallback(valueHolderForOnWillDismissTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWidth  = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue  = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForWidthTmpValueForIdx0  = valueHolderForWidthTmpValue as string
                valueSerializer.writeString(valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForWidthTmpValueForIdx1  = valueHolderForWidthTmpValue as number
                valueSerializer.writeNumber(valueHolderForWidthTmpValueForIdx1)
            } else if (valueHolderForWidthTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForWidthTmpValueForIdx2  = valueHolderForWidthTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeight  = value.height
        if (valueHolderForHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightTmpValue  = valueHolderForHeight!
            if (valueHolderForHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForHeightTmpValueForIdx0  = valueHolderForHeightTmpValue as string
                valueSerializer.writeString(valueHolderForHeightTmpValueForIdx0)
            } else if (valueHolderForHeightTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForHeightTmpValueForIdx1  = valueHolderForHeightTmpValue as number
                valueSerializer.writeNumber(valueHolderForHeightTmpValueForIdx1)
            } else if (valueHolderForHeightTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForHeightTmpValueForIdx2  = valueHolderForHeightTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForHeightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderWidth  = value.borderWidth
        if (valueHolderForBorderWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderWidthTmpValue  = valueHolderForBorderWidth!
            if (valueHolderForBorderWidthTmpValue instanceof Dimension) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderWidthTmpValueForIdx0  = valueHolderForBorderWidthTmpValue as Dimension
                if (valueHolderForBorderWidthTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForBorderWidthTmpValueForIdx0ForIdx0  = valueHolderForBorderWidthTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForBorderWidthTmpValueForIdx0ForIdx0)
                } else if (valueHolderForBorderWidthTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForBorderWidthTmpValueForIdx0ForIdx1  = valueHolderForBorderWidthTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForBorderWidthTmpValueForIdx0ForIdx1)
                } else if (valueHolderForBorderWidthTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForBorderWidthTmpValueForIdx0ForIdx2  = valueHolderForBorderWidthTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForBorderWidthTmpValueForIdx0ForIdx2)
                }
            } else if (valueHolderForBorderWidthTmpValue instanceof EdgeWidths) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderWidthTmpValueForIdx1  = valueHolderForBorderWidthTmpValue as EdgeWidths
                EdgeWidths_serializer.write(valueSerializer, valueHolderForBorderWidthTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderColor  = value.borderColor
        if (valueHolderForBorderColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderColorTmpValue  = valueHolderForBorderColor!
            if (valueHolderForBorderColorTmpValue instanceof ResourceColor) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderColorTmpValueForIdx0  = valueHolderForBorderColorTmpValue as ResourceColor
                if (valueHolderForBorderColorTmpValueForIdx0 instanceof Color) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx0  = valueHolderForBorderColorTmpValueForIdx0 as Color
                    valueSerializer.writeInt32(valueHolderForBorderColorTmpValueForIdx0ForIdx0.getOrdinal())
                } else if (valueHolderForBorderColorTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx1  = valueHolderForBorderColorTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForBorderColorTmpValueForIdx0ForIdx1)
                } else if (valueHolderForBorderColorTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx2  = valueHolderForBorderColorTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForBorderColorTmpValueForIdx0ForIdx2)
                } else if (valueHolderForBorderColorTmpValueForIdx0 instanceof Resource) {
                    valueSerializer.writeInt8((3).toByte())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx3  = valueHolderForBorderColorTmpValueForIdx0 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForBorderColorTmpValueForIdx0ForIdx3)
                }
            } else if (valueHolderForBorderColorTmpValue instanceof EdgeColors) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderColorTmpValueForIdx1  = valueHolderForBorderColorTmpValue as EdgeColors
                EdgeColors_serializer.write(valueSerializer, valueHolderForBorderColorTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderStyle  = value.borderStyle
        if (valueHolderForBorderStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderStyleTmpValue  = valueHolderForBorderStyle!
            if (valueHolderForBorderStyleTmpValue instanceof BorderStyle) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderStyleTmpValueForIdx0  = valueHolderForBorderStyleTmpValue as BorderStyle
                valueSerializer.writeInt32(valueHolderForBorderStyleTmpValueForIdx0.valueOf())
            } else if (valueHolderForBorderStyleTmpValue instanceof EdgeStyles) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderStyleTmpValueForIdx1  = valueHolderForBorderStyleTmpValue as EdgeStyles
                EdgeStyles_serializer.write(valueSerializer, valueHolderForBorderStyleTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShadow  = value.shadow
        if (valueHolderForShadow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShadowTmpValue  = valueHolderForShadow!
            if (valueHolderForShadowTmpValue instanceof ShadowOptions) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForShadowTmpValueForIdx0  = valueHolderForShadowTmpValue as ShadowOptions
                ShadowOptions_serializer.write(valueSerializer, valueHolderForShadowTmpValueForIdx0)
            } else if (valueHolderForShadowTmpValue instanceof ShadowStyle) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForShadowTmpValueForIdx1  = valueHolderForShadowTmpValue as ShadowStyle
                valueSerializer.writeInt32(valueHolderForShadowTmpValueForIdx1.valueOf())
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundBlurStyle  = value.backgroundBlurStyle
        if (valueHolderForBackgroundBlurStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundBlurStyleTmpValue  = (valueHolderForBackgroundBlurStyle as BlurStyle)
            valueSerializer.writeInt32(valueHolderForBackgroundBlurStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundBlurStyleOptions  = value.backgroundBlurStyleOptions
        if (valueHolderForBackgroundBlurStyleOptions !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundBlurStyleOptionsTmpValue  = valueHolderForBackgroundBlurStyleOptions!
            BackgroundBlurStyleOptions_serializer.write(valueSerializer, valueHolderForBackgroundBlurStyleOptionsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundEffect  = value.backgroundEffect
        if (valueHolderForBackgroundEffect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundEffectTmpValue  = valueHolderForBackgroundEffect!
            BackgroundEffectOptions_serializer.write(valueSerializer, valueHolderForBackgroundEffectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForKeyboardAvoidMode  = value.keyboardAvoidMode
        if (valueHolderForKeyboardAvoidMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForKeyboardAvoidModeTmpValue  = (valueHolderForKeyboardAvoidMode as KeyboardAvoidMode)
            valueSerializer.writeInt32(valueHolderForKeyboardAvoidModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnableHoverMode  = value.enableHoverMode
        if (valueHolderForEnableHoverMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableHoverModeTmpValue  = valueHolderForEnableHoverMode!
            valueSerializer.writeBoolean(valueHolderForEnableHoverModeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHoverModeArea  = value.hoverModeArea
        if (valueHolderForHoverModeArea !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHoverModeAreaTmpValue  = (valueHolderForHoverModeArea as HoverModeAreaType)
            valueSerializer.writeInt32(valueHolderForHoverModeAreaTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnDidAppear  = value.onDidAppear
        if (valueHolderForOnDidAppear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnDidAppearTmpValue  = valueHolderForOnDidAppear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnDidAppearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnDidDisappear  = value.onDidDisappear
        if (valueHolderForOnDidDisappear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnDidDisappearTmpValue  = valueHolderForOnDidDisappear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnDidDisappearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnWillAppear  = value.onWillAppear
        if (valueHolderForOnWillAppear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnWillAppearTmpValue  = valueHolderForOnWillAppear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnWillAppearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnWillDisappear  = value.onWillDisappear
        if (valueHolderForOnWillDisappear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnWillDisappearTmpValue  = valueHolderForOnWillDisappear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnWillDisappearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForKeyboardAvoidDistance  = value.keyboardAvoidDistance
        if (valueHolderForKeyboardAvoidDistance !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForKeyboardAvoidDistanceTmpValue  = valueHolderForKeyboardAvoidDistance!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForKeyboardAvoidDistanceTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLevelMode  = value.levelMode
        if (valueHolderForLevelMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLevelModeTmpValue  = (valueHolderForLevelMode as LevelMode)
            valueSerializer.writeInt32(valueHolderForLevelModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLevelUniqueId  = value.levelUniqueId
        if (valueHolderForLevelUniqueId !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLevelUniqueIdTmpValue  = valueHolderForLevelUniqueId!
            valueSerializer.writeInt32(valueHolderForLevelUniqueIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForImmersiveMode  = value.immersiveMode
        if (valueHolderForImmersiveMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForImmersiveModeTmpValue  = (valueHolderForImmersiveMode as ImmersiveMode)
            valueSerializer.writeInt32(valueHolderForImmersiveModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLevelOrderExtender  = value.levelOrderExtender
        if (valueHolderForLevelOrderExtender !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLevelOrderExtenderTmpValue  = valueHolderForLevelOrderExtender!
            LevelOrderExtender_serializer.write(valueSerializer, valueHolderForLevelOrderExtenderTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFocusable  = value.focusable
        if (valueHolderForFocusable !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFocusableTmpValue  = valueHolderForFocusable!
            valueSerializer.writeBoolean(valueHolderForFocusableTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): CustomDialogControllerOptionsExtender {
        let valueDeserializer : DeserializerBase = buffer
        const builderTmpBufBufResource : CallbackResource = valueDeserializer.readCallbackResource()
        const builderTmpBufBufCall : KPointer = valueDeserializer.readPointer()
        const builderTmpBufBufCallSync : KPointer = valueDeserializer.readPointer()
        const builderTmpResult : CustomBuilder = ():void => {
            const builderTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            builderTmpBufBufArgsSerializer.writeInt32(builderTmpBufBufResource.resourceId);
            builderTmpBufBufArgsSerializer.writePointer(builderTmpBufBufCall);
            builderTmpBufBufArgsSerializer.writePointer(builderTmpBufBufCallSync);
            InteropNativeModule._CallCallbackSync(10, 737226752, builderTmpBufBufArgsSerializer.asBuffer(), builderTmpBufBufArgsSerializer.length());
            builderTmpBufBufArgsSerializer.release();
            return;
        }
        const cancelTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let cancelTmpBuf : (() => void) | undefined = undefined
        if ((cancelTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const cancelTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const cancelTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const cancelTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            cancelTmpBuf = ():void => {
                const cancelTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                cancelTmpBuf_BufArgsSerializer.writeInt32(cancelTmpBuf_BufResource.resourceId);
                cancelTmpBuf_BufArgsSerializer.writePointer(cancelTmpBuf_BufCall);
                cancelTmpBuf_BufArgsSerializer.writePointer(cancelTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, cancelTmpBuf_BufArgsSerializer.asBuffer(), cancelTmpBuf_BufArgsSerializer.length());
                cancelTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const cancelTmpResult : (() => void) | undefined = cancelTmpBuf
        const autoCancelTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let autoCancelTmpBuf : boolean | undefined = undefined
        if ((autoCancelTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            autoCancelTmpBuf = valueDeserializer.readBoolean()
        }
        const autoCancelTmpResult : boolean | undefined = autoCancelTmpBuf
        const alignmentTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let alignmentTmpBuf : DialogAlignment | undefined = undefined
        if ((alignmentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            alignmentTmpBuf = DialogAlignment.fromValue(valueDeserializer.readInt32())
        }
        const alignmentTmpResult : DialogAlignment | undefined = alignmentTmpBuf
        const offsetTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let offsetTmpBuf : Offset | undefined = undefined
        if ((offsetTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            offsetTmpBuf = Offset_serializer.read(valueDeserializer)
        }
        const offsetTmpResult : Offset | undefined = offsetTmpBuf
        const customStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let customStyleTmpBuf : boolean | undefined = undefined
        if ((customStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            customStyleTmpBuf = valueDeserializer.readBoolean()
        }
        const customStyleTmpResult : boolean | undefined = customStyleTmpBuf
        const gridCountTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let gridCountTmpBuf : int32 | undefined = undefined
        if ((gridCountTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            gridCountTmpBuf = valueDeserializer.readInt32()
        }
        const gridCountTmpResult : int32 | undefined = gridCountTmpBuf
        const maskColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maskColorTmpBuf : ResourceColor | undefined = undefined
        if ((maskColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const maskColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let maskColorTmpBuf_ : Color | number | string | Resource | undefined
            if (maskColorTmpBuf_UnionSelector == (0).toChar()) {
                maskColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (maskColorTmpBuf_UnionSelector == (1).toChar()) {
                maskColorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (maskColorTmpBuf_UnionSelector == (2).toChar()) {
                maskColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (maskColorTmpBuf_UnionSelector == (3).toChar()) {
                maskColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for maskColorTmpBuf_ has to be chosen through deserialisation.")
            }
            maskColorTmpBuf = (maskColorTmpBuf_ as Color | number | string | Resource)
        }
        const maskColorTmpResult : ResourceColor | undefined = maskColorTmpBuf
        const maskRectTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maskRectTmpBuf : Rectangle | undefined = undefined
        if ((maskRectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maskRectTmpBuf = Rectangle_serializer.read(valueDeserializer)
        }
        const maskRectTmpResult : Rectangle | undefined = maskRectTmpBuf
        const openAnimationTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let openAnimationTmpBuf : AnimateParam | undefined = undefined
        if ((openAnimationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            openAnimationTmpBuf = AnimateParam_serializer.read(valueDeserializer)
        }
        const openAnimationTmpResult : AnimateParam | undefined = openAnimationTmpBuf
        const closeAnimationTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let closeAnimationTmpBuf : AnimateParam | undefined = undefined
        if ((closeAnimationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            closeAnimationTmpBuf = AnimateParam_serializer.read(valueDeserializer)
        }
        const closeAnimationTmpResult : AnimateParam | undefined = closeAnimationTmpBuf
        const showInSubWindowTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let showInSubWindowTmpBuf : boolean | undefined = undefined
        if ((showInSubWindowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            showInSubWindowTmpBuf = valueDeserializer.readBoolean()
        }
        const showInSubWindowTmpResult : boolean | undefined = showInSubWindowTmpBuf
        const backgroundColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundColorTmpBuf : ResourceColor | undefined = undefined
        if ((backgroundColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const backgroundColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let backgroundColorTmpBuf_ : Color | number | string | Resource | undefined
            if (backgroundColorTmpBuf_UnionSelector == (0).toChar()) {
                backgroundColorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (backgroundColorTmpBuf_UnionSelector == (1).toChar()) {
                backgroundColorTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (backgroundColorTmpBuf_UnionSelector == (2).toChar()) {
                backgroundColorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (backgroundColorTmpBuf_UnionSelector == (3).toChar()) {
                backgroundColorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for backgroundColorTmpBuf_ has to be chosen through deserialisation.")
            }
            backgroundColorTmpBuf = (backgroundColorTmpBuf_ as Color | number | string | Resource)
        }
        const backgroundColorTmpResult : ResourceColor | undefined = backgroundColorTmpBuf
        const cornerRadiusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let cornerRadiusTmpBuf : Dimension | BorderRadiuses | undefined = undefined
        if ((cornerRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const cornerRadiusTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let cornerRadiusTmpBuf_ : Dimension | BorderRadiuses | undefined
            if (cornerRadiusTmpBuf_UnionSelector == (0).toChar()) {
                const cornerRadiusTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let cornerRadiusTmpBuf_BufU : string | number | Resource | undefined
                if (cornerRadiusTmpBuf_BufUUnionSelector == (0).toChar()) {
                    cornerRadiusTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (cornerRadiusTmpBuf_BufUUnionSelector == (1).toChar()) {
                    cornerRadiusTmpBuf_BufU = (valueDeserializer.readNumber() as number)
                } else if (cornerRadiusTmpBuf_BufUUnionSelector == (2).toChar()) {
                    cornerRadiusTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for cornerRadiusTmpBuf_BufU has to be chosen through deserialisation.")
                }
                cornerRadiusTmpBuf_ = (cornerRadiusTmpBuf_BufU as string | number | Resource)
            } else if (cornerRadiusTmpBuf_UnionSelector == (1).toChar()) {
                cornerRadiusTmpBuf_ = BorderRadiuses_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for cornerRadiusTmpBuf_ has to be chosen through deserialisation.")
            }
            cornerRadiusTmpBuf = (cornerRadiusTmpBuf_ as Dimension | BorderRadiuses)
        }
        const cornerRadiusTmpResult : Dimension | BorderRadiuses | undefined = cornerRadiusTmpBuf
        const isModalTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let isModalTmpBuf : boolean | undefined = undefined
        if ((isModalTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            isModalTmpBuf = valueDeserializer.readBoolean()
        }
        const isModalTmpResult : boolean | undefined = isModalTmpBuf
        const onWillDismissTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillDismissTmpBuf : ((value0: DismissDialogAction) => void) | undefined = undefined
        if ((onWillDismissTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillDismissTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillDismissTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onWillDismissTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onWillDismissTmpBuf = (value0: DismissDialogAction):void => {
                const onWillDismissTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillDismissTmpBuf_BufArgsSerializer.writeInt32(onWillDismissTmpBuf_BufResource.resourceId);
                onWillDismissTmpBuf_BufArgsSerializer.writePointer(onWillDismissTmpBuf_BufCall);
                onWillDismissTmpBuf_BufArgsSerializer.writePointer(onWillDismissTmpBuf_BufCallSync);
                DismissDialogAction_serializer.write(onWillDismissTmpBuf_BufArgsSerializer, value0);
                InteropNativeModule._CallCallbackSync(10, -2095828093, onWillDismissTmpBuf_BufArgsSerializer.asBuffer(), onWillDismissTmpBuf_BufArgsSerializer.length());
                onWillDismissTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onWillDismissTmpResult : ((value0: DismissDialogAction) => void) | undefined = onWillDismissTmpBuf
        const widthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let widthTmpBuf : Dimension | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let widthTmpBuf_ : string | number | Resource | undefined
            if (widthTmpBuf_UnionSelector == (0).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (widthTmpBuf_UnionSelector == (1).toChar()) {
                widthTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (widthTmpBuf_UnionSelector == (2).toChar()) {
                widthTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for widthTmpBuf_ has to be chosen through deserialisation.")
            }
            widthTmpBuf = (widthTmpBuf_ as string | number | Resource)
        }
        const widthTmpResult : Dimension | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let heightTmpBuf : Dimension | undefined = undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let heightTmpBuf_ : string | number | Resource | undefined
            if (heightTmpBuf_UnionSelector == (0).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (heightTmpBuf_UnionSelector == (1).toChar()) {
                heightTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (heightTmpBuf_UnionSelector == (2).toChar()) {
                heightTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for heightTmpBuf_ has to be chosen through deserialisation.")
            }
            heightTmpBuf = (heightTmpBuf_ as string | number | Resource)
        }
        const heightTmpResult : Dimension | undefined = heightTmpBuf
        const borderWidthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderWidthTmpBuf : Dimension | EdgeWidths | undefined = undefined
        if ((borderWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderWidthTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let borderWidthTmpBuf_ : Dimension | EdgeWidths | undefined
            if (borderWidthTmpBuf_UnionSelector == (0).toChar()) {
                const borderWidthTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let borderWidthTmpBuf_BufU : string | number | Resource | undefined
                if (borderWidthTmpBuf_BufUUnionSelector == (0).toChar()) {
                    borderWidthTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (borderWidthTmpBuf_BufUUnionSelector == (1).toChar()) {
                    borderWidthTmpBuf_BufU = (valueDeserializer.readNumber() as number)
                } else if (borderWidthTmpBuf_BufUUnionSelector == (2).toChar()) {
                    borderWidthTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for borderWidthTmpBuf_BufU has to be chosen through deserialisation.")
                }
                borderWidthTmpBuf_ = (borderWidthTmpBuf_BufU as string | number | Resource)
            } else if (borderWidthTmpBuf_UnionSelector == (1).toChar()) {
                borderWidthTmpBuf_ = EdgeWidths_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for borderWidthTmpBuf_ has to be chosen through deserialisation.")
            }
            borderWidthTmpBuf = (borderWidthTmpBuf_ as Dimension | EdgeWidths)
        }
        const borderWidthTmpResult : Dimension | EdgeWidths | undefined = borderWidthTmpBuf
        const borderColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderColorTmpBuf : ResourceColor | EdgeColors | undefined = undefined
        if ((borderColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderColorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let borderColorTmpBuf_ : ResourceColor | EdgeColors | undefined
            if (borderColorTmpBuf_UnionSelector == (0).toChar()) {
                const borderColorTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let borderColorTmpBuf_BufU : Color | number | string | Resource | undefined
                if (borderColorTmpBuf_BufUUnionSelector == (0).toChar()) {
                    borderColorTmpBuf_BufU = Color.values()[valueDeserializer.readInt32()]
                } else if (borderColorTmpBuf_BufUUnionSelector == (1).toChar()) {
                    borderColorTmpBuf_BufU = (valueDeserializer.readNumber() as number)
                } else if (borderColorTmpBuf_BufUUnionSelector == (2).toChar()) {
                    borderColorTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (borderColorTmpBuf_BufUUnionSelector == (3).toChar()) {
                    borderColorTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for borderColorTmpBuf_BufU has to be chosen through deserialisation.")
                }
                borderColorTmpBuf_ = (borderColorTmpBuf_BufU as Color | number | string | Resource)
            } else if (borderColorTmpBuf_UnionSelector == (1).toChar()) {
                borderColorTmpBuf_ = EdgeColors_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for borderColorTmpBuf_ has to be chosen through deserialisation.")
            }
            borderColorTmpBuf = (borderColorTmpBuf_ as ResourceColor | EdgeColors)
        }
        const borderColorTmpResult : ResourceColor | EdgeColors | undefined = borderColorTmpBuf
        const borderStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let borderStyleTmpBuf : BorderStyle | EdgeStyles | undefined = undefined
        if ((borderStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderStyleTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let borderStyleTmpBuf_ : BorderStyle | EdgeStyles | undefined
            if (borderStyleTmpBuf_UnionSelector == (0).toChar()) {
                borderStyleTmpBuf_ = BorderStyle.fromValue(valueDeserializer.readInt32())
            } else if (borderStyleTmpBuf_UnionSelector == (1).toChar()) {
                borderStyleTmpBuf_ = EdgeStyles_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for borderStyleTmpBuf_ has to be chosen through deserialisation.")
            }
            borderStyleTmpBuf = (borderStyleTmpBuf_ as BorderStyle | EdgeStyles)
        }
        const borderStyleTmpResult : BorderStyle | EdgeStyles | undefined = borderStyleTmpBuf
        const shadowTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let shadowTmpBuf : ShadowOptions | ShadowStyle | undefined = undefined
        if ((shadowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const shadowTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let shadowTmpBuf_ : ShadowOptions | ShadowStyle | undefined
            if (shadowTmpBuf_UnionSelector == (0).toChar()) {
                shadowTmpBuf_ = ShadowOptions_serializer.read(valueDeserializer)
            } else if (shadowTmpBuf_UnionSelector == (1).toChar()) {
                shadowTmpBuf_ = ShadowStyle.fromValue(valueDeserializer.readInt32())
            } else {
                throw new Error("One of the branches for shadowTmpBuf_ has to be chosen through deserialisation.")
            }
            shadowTmpBuf = (shadowTmpBuf_ as ShadowOptions | ShadowStyle)
        }
        const shadowTmpResult : ShadowOptions | ShadowStyle | undefined = shadowTmpBuf
        const backgroundBlurStyleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleTmpBuf : BlurStyle | undefined = undefined
        if ((backgroundBlurStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleTmpBuf = BlurStyle.fromValue(valueDeserializer.readInt32())
        }
        const backgroundBlurStyleTmpResult : BlurStyle | undefined = backgroundBlurStyleTmpBuf
        const backgroundBlurStyleOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundBlurStyleOptionsTmpBuf : BackgroundBlurStyleOptions | undefined = undefined
        if ((backgroundBlurStyleOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleOptionsTmpBuf = BackgroundBlurStyleOptions_serializer.read(valueDeserializer)
        }
        const backgroundBlurStyleOptionsTmpResult : BackgroundBlurStyleOptions | undefined = backgroundBlurStyleOptionsTmpBuf
        const backgroundEffectTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let backgroundEffectTmpBuf : BackgroundEffectOptions | undefined = undefined
        if ((backgroundEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundEffectTmpBuf = BackgroundEffectOptions_serializer.read(valueDeserializer)
        }
        const backgroundEffectTmpResult : BackgroundEffectOptions | undefined = backgroundEffectTmpBuf
        const keyboardAvoidModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let keyboardAvoidModeTmpBuf : KeyboardAvoidMode | undefined = undefined
        if ((keyboardAvoidModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            keyboardAvoidModeTmpBuf = KeyboardAvoidMode.fromValue(valueDeserializer.readInt32())
        }
        const keyboardAvoidModeTmpResult : KeyboardAvoidMode | undefined = keyboardAvoidModeTmpBuf
        const enableHoverModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableHoverModeTmpBuf : boolean | undefined = undefined
        if ((enableHoverModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableHoverModeTmpBuf = valueDeserializer.readBoolean()
        }
        const enableHoverModeTmpResult : boolean | undefined = enableHoverModeTmpBuf
        const hoverModeAreaTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let hoverModeAreaTmpBuf : HoverModeAreaType | undefined = undefined
        if ((hoverModeAreaTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            hoverModeAreaTmpBuf = HoverModeAreaType.fromValue(valueDeserializer.readInt32())
        }
        const hoverModeAreaTmpResult : HoverModeAreaType | undefined = hoverModeAreaTmpBuf
        const onDidAppearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDidAppearTmpBuf : (() => void) | undefined = undefined
        if ((onDidAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidAppearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidAppearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onDidAppearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onDidAppearTmpBuf = ():void => {
                const onDidAppearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDidAppearTmpBuf_BufArgsSerializer.writeInt32(onDidAppearTmpBuf_BufResource.resourceId);
                onDidAppearTmpBuf_BufArgsSerializer.writePointer(onDidAppearTmpBuf_BufCall);
                onDidAppearTmpBuf_BufArgsSerializer.writePointer(onDidAppearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onDidAppearTmpBuf_BufArgsSerializer.asBuffer(), onDidAppearTmpBuf_BufArgsSerializer.length());
                onDidAppearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onDidAppearTmpResult : (() => void) | undefined = onDidAppearTmpBuf
        const onDidDisappearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onDidDisappearTmpBuf : (() => void) | undefined = undefined
        if ((onDidDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidDisappearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onDidDisappearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onDidDisappearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onDidDisappearTmpBuf = ():void => {
                const onDidDisappearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onDidDisappearTmpBuf_BufArgsSerializer.writeInt32(onDidDisappearTmpBuf_BufResource.resourceId);
                onDidDisappearTmpBuf_BufArgsSerializer.writePointer(onDidDisappearTmpBuf_BufCall);
                onDidDisappearTmpBuf_BufArgsSerializer.writePointer(onDidDisappearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onDidDisappearTmpBuf_BufArgsSerializer.asBuffer(), onDidDisappearTmpBuf_BufArgsSerializer.length());
                onDidDisappearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onDidDisappearTmpResult : (() => void) | undefined = onDidDisappearTmpBuf
        const onWillAppearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillAppearTmpBuf : (() => void) | undefined = undefined
        if ((onWillAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillAppearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillAppearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onWillAppearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onWillAppearTmpBuf = ():void => {
                const onWillAppearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillAppearTmpBuf_BufArgsSerializer.writeInt32(onWillAppearTmpBuf_BufResource.resourceId);
                onWillAppearTmpBuf_BufArgsSerializer.writePointer(onWillAppearTmpBuf_BufCall);
                onWillAppearTmpBuf_BufArgsSerializer.writePointer(onWillAppearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onWillAppearTmpBuf_BufArgsSerializer.asBuffer(), onWillAppearTmpBuf_BufArgsSerializer.length());
                onWillAppearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onWillAppearTmpResult : (() => void) | undefined = onWillAppearTmpBuf
        const onWillDisappearTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onWillDisappearTmpBuf : (() => void) | undefined = undefined
        if ((onWillDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillDisappearTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onWillDisappearTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onWillDisappearTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onWillDisappearTmpBuf = ():void => {
                const onWillDisappearTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onWillDisappearTmpBuf_BufArgsSerializer.writeInt32(onWillDisappearTmpBuf_BufResource.resourceId);
                onWillDisappearTmpBuf_BufArgsSerializer.writePointer(onWillDisappearTmpBuf_BufCall);
                onWillDisappearTmpBuf_BufArgsSerializer.writePointer(onWillDisappearTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1867723152, onWillDisappearTmpBuf_BufArgsSerializer.asBuffer(), onWillDisappearTmpBuf_BufArgsSerializer.length());
                onWillDisappearTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onWillDisappearTmpResult : (() => void) | undefined = onWillDisappearTmpBuf
        const keyboardAvoidDistanceTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let keyboardAvoidDistanceTmpBuf : LengthMetrics | undefined = undefined
        if ((keyboardAvoidDistanceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            keyboardAvoidDistanceTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const keyboardAvoidDistanceTmpResult : LengthMetrics | undefined = keyboardAvoidDistanceTmpBuf
        const levelModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let levelModeTmpBuf : LevelMode | undefined = undefined
        if ((levelModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            levelModeTmpBuf = LevelMode.fromValue(valueDeserializer.readInt32())
        }
        const levelModeTmpResult : LevelMode | undefined = levelModeTmpBuf
        const levelUniqueIdTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let levelUniqueIdTmpBuf : int32 | undefined = undefined
        if ((levelUniqueIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            levelUniqueIdTmpBuf = valueDeserializer.readInt32()
        }
        const levelUniqueIdTmpResult : int32 | undefined = levelUniqueIdTmpBuf
        const immersiveModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let immersiveModeTmpBuf : ImmersiveMode | undefined = undefined
        if ((immersiveModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            immersiveModeTmpBuf = ImmersiveMode.fromValue(valueDeserializer.readInt32())
        }
        const immersiveModeTmpResult : ImmersiveMode | undefined = immersiveModeTmpBuf
        const levelOrderExtenderTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let levelOrderExtenderTmpBuf : LevelOrderExtender | undefined = undefined
        if ((levelOrderExtenderTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            levelOrderExtenderTmpBuf = (LevelOrderExtender_serializer.read(valueDeserializer) as LevelOrderExtender)
        }
        const levelOrderExtenderTmpResult : LevelOrderExtender | undefined = levelOrderExtenderTmpBuf
        const focusableTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let focusableTmpBuf : boolean | undefined = undefined
        if ((focusableTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            focusableTmpBuf = valueDeserializer.readBoolean()
        }
        const focusableTmpResult : boolean | undefined = focusableTmpBuf
        let value : CustomDialogControllerOptionsExtender = ({builder: builderTmpResult, cancel: cancelTmpResult, autoCancel: autoCancelTmpResult, alignment: alignmentTmpResult, offset: offsetTmpResult, customStyle: customStyleTmpResult, gridCount: gridCountTmpResult, maskColor: maskColorTmpResult, maskRect: maskRectTmpResult, openAnimation: openAnimationTmpResult, closeAnimation: closeAnimationTmpResult, showInSubWindow: showInSubWindowTmpResult, backgroundColor: backgroundColorTmpResult, cornerRadius: cornerRadiusTmpResult, isModal: isModalTmpResult, onWillDismiss: onWillDismissTmpResult, width: widthTmpResult, height: heightTmpResult, borderWidth: borderWidthTmpResult, borderColor: borderColorTmpResult, borderStyle: borderStyleTmpResult, shadow: shadowTmpResult, backgroundBlurStyle: backgroundBlurStyleTmpResult, backgroundBlurStyleOptions: backgroundBlurStyleOptionsTmpResult, backgroundEffect: backgroundEffectTmpResult, keyboardAvoidMode: keyboardAvoidModeTmpResult, enableHoverMode: enableHoverModeTmpResult, hoverModeArea: hoverModeAreaTmpResult, onDidAppear: onDidAppearTmpResult, onDidDisappear: onDidDisappearTmpResult, onWillAppear: onWillAppearTmpResult, onWillDisappear: onWillDisappearTmpResult, keyboardAvoidDistance: keyboardAvoidDistanceTmpResult, levelMode: levelModeTmpResult, levelUniqueId: levelUniqueIdTmpResult, immersiveMode: immersiveModeTmpResult, levelOrderExtender: levelOrderExtenderTmpResult, focusable: focusableTmpResult} as CustomDialogControllerOptionsExtender)
        return value
    }
}
export class EmitterOptionsInner_serializer {
    public static write(buffer: SerializerBase, value: EmitterOptionsInner): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForParticle  = value.particle
        EmitterParticleOptions_serializer.write(valueSerializer, valueHolderForParticle)
        const valueHolderForEmitRate  = value.emitRate
        if (valueHolderForEmitRate !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEmitRateTmpValue  = valueHolderForEmitRate!
            valueSerializer.writeNumber(valueHolderForEmitRateTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShape  = value.shape
        if (valueHolderForShape !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShapeTmpValue  = (valueHolderForShape as ParticleEmitterShape)
            valueSerializer.writeInt32(valueHolderForShapeTmpValue.getOrdinal())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPosition  = value.position
        if (valueHolderForPosition !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPositionTmpValue  = valueHolderForPosition!
            const valueHolderForPositionTmpValue_0  = valueHolderForPositionTmpValue[0]
            if (valueHolderForPositionTmpValue_0 instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForPositionTmpValue_0ForIdx0  = valueHolderForPositionTmpValue_0 as string
                valueSerializer.writeString(valueHolderForPositionTmpValue_0ForIdx0)
            } else if (valueHolderForPositionTmpValue_0 instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForPositionTmpValue_0ForIdx1  = valueHolderForPositionTmpValue_0 as number
                valueSerializer.writeNumber(valueHolderForPositionTmpValue_0ForIdx1)
            } else if (valueHolderForPositionTmpValue_0 instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForPositionTmpValue_0ForIdx2  = valueHolderForPositionTmpValue_0 as Resource
                Resource_serializer.write(valueSerializer, valueHolderForPositionTmpValue_0ForIdx2)
            }
            const valueHolderForPositionTmpValue_1  = valueHolderForPositionTmpValue[1]
            if (valueHolderForPositionTmpValue_1 instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForPositionTmpValue_1ForIdx0  = valueHolderForPositionTmpValue_1 as string
                valueSerializer.writeString(valueHolderForPositionTmpValue_1ForIdx0)
            } else if (valueHolderForPositionTmpValue_1 instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForPositionTmpValue_1ForIdx1  = valueHolderForPositionTmpValue_1 as number
                valueSerializer.writeNumber(valueHolderForPositionTmpValue_1ForIdx1)
            } else if (valueHolderForPositionTmpValue_1 instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForPositionTmpValue_1ForIdx2  = valueHolderForPositionTmpValue_1 as Resource
                Resource_serializer.write(valueSerializer, valueHolderForPositionTmpValue_1ForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSize  = value.size
        if (valueHolderForSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSizeTmpValue  = valueHolderForSize!
            const valueHolderForSizeTmpValue_0  = valueHolderForSizeTmpValue[0]
            if (valueHolderForSizeTmpValue_0 instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSizeTmpValue_0ForIdx0  = valueHolderForSizeTmpValue_0 as string
                valueSerializer.writeString(valueHolderForSizeTmpValue_0ForIdx0)
            } else if (valueHolderForSizeTmpValue_0 instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSizeTmpValue_0ForIdx1  = valueHolderForSizeTmpValue_0 as number
                valueSerializer.writeNumber(valueHolderForSizeTmpValue_0ForIdx1)
            } else if (valueHolderForSizeTmpValue_0 instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForSizeTmpValue_0ForIdx2  = valueHolderForSizeTmpValue_0 as Resource
                Resource_serializer.write(valueSerializer, valueHolderForSizeTmpValue_0ForIdx2)
            }
            const valueHolderForSizeTmpValue_1  = valueHolderForSizeTmpValue[1]
            if (valueHolderForSizeTmpValue_1 instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSizeTmpValue_1ForIdx0  = valueHolderForSizeTmpValue_1 as string
                valueSerializer.writeString(valueHolderForSizeTmpValue_1ForIdx0)
            } else if (valueHolderForSizeTmpValue_1 instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSizeTmpValue_1ForIdx1  = valueHolderForSizeTmpValue_1 as number
                valueSerializer.writeNumber(valueHolderForSizeTmpValue_1ForIdx1)
            } else if (valueHolderForSizeTmpValue_1 instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForSizeTmpValue_1ForIdx2  = valueHolderForSizeTmpValue_1 as Resource
                Resource_serializer.write(valueSerializer, valueHolderForSizeTmpValue_1ForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAnnulusRegion  = value.annulusRegion
        if (valueHolderForAnnulusRegion !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAnnulusRegionTmpValue  = valueHolderForAnnulusRegion!
            ParticleAnnulusRegionInner_serializer.write(valueSerializer, valueHolderForAnnulusRegionTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): EmitterOptionsInner {
        let valueDeserializer : DeserializerBase = buffer
        const particleTmpResult : EmitterParticleOptions = EmitterParticleOptions_serializer.read(valueDeserializer)
        const emitRateTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let emitRateTmpBuf : number | undefined = undefined
        if ((emitRateTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            emitRateTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const emitRateTmpResult : number | undefined = emitRateTmpBuf
        const shapeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let shapeTmpBuf : ParticleEmitterShape | undefined = undefined
        if ((shapeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            shapeTmpBuf = ParticleEmitterShape.values()[valueDeserializer.readInt32()]
        }
        const shapeTmpResult : ParticleEmitterShape | undefined = shapeTmpBuf
        const positionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let positionTmpBuf : [ Dimension, Dimension ] | undefined = undefined
        if ((positionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const positionTmpBuf_Value0TempBufUnionSelector : int32 = valueDeserializer.readInt8()
            let positionTmpBuf_Value0TempBuf : string | number | Resource | undefined
            if (positionTmpBuf_Value0TempBufUnionSelector == (0).toChar()) {
                positionTmpBuf_Value0TempBuf = (valueDeserializer.readString() as string)
            } else if (positionTmpBuf_Value0TempBufUnionSelector == (1).toChar()) {
                positionTmpBuf_Value0TempBuf = (valueDeserializer.readNumber() as number)
            } else if (positionTmpBuf_Value0TempBufUnionSelector == (2).toChar()) {
                positionTmpBuf_Value0TempBuf = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for positionTmpBuf_Value0TempBuf has to be chosen through deserialisation.")
            }
            const positionTmpBuf_Value0 : Dimension = (positionTmpBuf_Value0TempBuf as string | number | Resource)
            const positionTmpBuf_Value1TempBufUnionSelector : int32 = valueDeserializer.readInt8()
            let positionTmpBuf_Value1TempBuf : string | number | Resource | undefined
            if (positionTmpBuf_Value1TempBufUnionSelector == (0).toChar()) {
                positionTmpBuf_Value1TempBuf = (valueDeserializer.readString() as string)
            } else if (positionTmpBuf_Value1TempBufUnionSelector == (1).toChar()) {
                positionTmpBuf_Value1TempBuf = (valueDeserializer.readNumber() as number)
            } else if (positionTmpBuf_Value1TempBufUnionSelector == (2).toChar()) {
                positionTmpBuf_Value1TempBuf = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for positionTmpBuf_Value1TempBuf has to be chosen through deserialisation.")
            }
            const positionTmpBuf_Value1 : Dimension = (positionTmpBuf_Value1TempBuf as string | number | Resource)
            positionTmpBuf = ([positionTmpBuf_Value0, positionTmpBuf_Value1] as [ Dimension, Dimension ])
        }
        const positionTmpResult : [ Dimension, Dimension ] | undefined = positionTmpBuf
        const sizeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let sizeTmpBuf : [ Dimension, Dimension ] | undefined = undefined
        if ((sizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const sizeTmpBuf_Value0TempBufUnionSelector : int32 = valueDeserializer.readInt8()
            let sizeTmpBuf_Value0TempBuf : string | number | Resource | undefined
            if (sizeTmpBuf_Value0TempBufUnionSelector == (0).toChar()) {
                sizeTmpBuf_Value0TempBuf = (valueDeserializer.readString() as string)
            } else if (sizeTmpBuf_Value0TempBufUnionSelector == (1).toChar()) {
                sizeTmpBuf_Value0TempBuf = (valueDeserializer.readNumber() as number)
            } else if (sizeTmpBuf_Value0TempBufUnionSelector == (2).toChar()) {
                sizeTmpBuf_Value0TempBuf = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for sizeTmpBuf_Value0TempBuf has to be chosen through deserialisation.")
            }
            const sizeTmpBuf_Value0 : Dimension = (sizeTmpBuf_Value0TempBuf as string | number | Resource)
            const sizeTmpBuf_Value1TempBufUnionSelector : int32 = valueDeserializer.readInt8()
            let sizeTmpBuf_Value1TempBuf : string | number | Resource | undefined
            if (sizeTmpBuf_Value1TempBufUnionSelector == (0).toChar()) {
                sizeTmpBuf_Value1TempBuf = (valueDeserializer.readString() as string)
            } else if (sizeTmpBuf_Value1TempBufUnionSelector == (1).toChar()) {
                sizeTmpBuf_Value1TempBuf = (valueDeserializer.readNumber() as number)
            } else if (sizeTmpBuf_Value1TempBufUnionSelector == (2).toChar()) {
                sizeTmpBuf_Value1TempBuf = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for sizeTmpBuf_Value1TempBuf has to be chosen through deserialisation.")
            }
            const sizeTmpBuf_Value1 : Dimension = (sizeTmpBuf_Value1TempBuf as string | number | Resource)
            sizeTmpBuf = ([sizeTmpBuf_Value0, sizeTmpBuf_Value1] as [ Dimension, Dimension ])
        }
        const sizeTmpResult : [ Dimension, Dimension ] | undefined = sizeTmpBuf
        const annulusRegionTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let annulusRegionTmpBuf : ParticleAnnulusRegionInner | undefined = undefined
        if ((annulusRegionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            annulusRegionTmpBuf = ParticleAnnulusRegionInner_serializer.read(valueDeserializer)
        }
        const annulusRegionTmpResult : ParticleAnnulusRegionInner | undefined = annulusRegionTmpBuf
        let value : EmitterOptionsInner = ({particle: particleTmpResult, emitRate: emitRateTmpResult, shape: shapeTmpResult, position: positionTmpResult, size: sizeTmpResult, annulusRegion: annulusRegionTmpResult} as EmitterOptionsInner)
        return value
    }
}
export class ParticleOptionsInner_serializer {
    public static write(buffer: SerializerBase, value: ParticleOptionsInner): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForEmitter  = value.emitter
        EmitterOptionsInner_serializer.write(valueSerializer, valueHolderForEmitter)
        const valueHolderForColor  = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue  = valueHolderForColor!
            ParticleColorPropertyOptionsInner_serializer.write(valueSerializer, valueHolderForColorTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOpacity  = value.opacity
        if (valueHolderForOpacity !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOpacityTmpValue  = valueHolderForOpacity!
            ParticlePropertyOptionsInner_serializer.write(valueSerializer, valueHolderForOpacityTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForScale  = value.scale
        if (valueHolderForScale !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForScaleTmpValue  = valueHolderForScale!
            ParticlePropertyOptionsInner_serializer.write(valueSerializer, valueHolderForScaleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForVelocity  = value.velocity
        if (valueHolderForVelocity !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForVelocityTmpValue  = valueHolderForVelocity!
            VelocityOptions_serializer.write(valueSerializer, valueHolderForVelocityTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAcceleration  = value.acceleration
        if (valueHolderForAcceleration !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAccelerationTmpValue  = valueHolderForAcceleration!
            AccelerationOptionsInner_serializer.write(valueSerializer, valueHolderForAccelerationTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSpin  = value.spin
        if (valueHolderForSpin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSpinTmpValue  = valueHolderForSpin!
            ParticlePropertyOptionsInner_serializer.write(valueSerializer, valueHolderForSpinTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ParticleOptionsInner {
        let valueDeserializer : DeserializerBase = buffer
        const emitterTmpResult : EmitterOptionsInner = EmitterOptionsInner_serializer.read(valueDeserializer)
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colorTmpBuf : ParticleColorPropertyOptionsInner | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            colorTmpBuf = ParticleColorPropertyOptionsInner_serializer.read(valueDeserializer)
        }
        const colorTmpResult : ParticleColorPropertyOptionsInner | undefined = colorTmpBuf
        const opacityTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let opacityTmpBuf : ParticlePropertyOptionsInner | undefined = undefined
        if ((opacityTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            opacityTmpBuf = ParticlePropertyOptionsInner_serializer.read(valueDeserializer)
        }
        const opacityTmpResult : ParticlePropertyOptionsInner | undefined = opacityTmpBuf
        const scaleTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let scaleTmpBuf : ParticlePropertyOptionsInner | undefined = undefined
        if ((scaleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            scaleTmpBuf = ParticlePropertyOptionsInner_serializer.read(valueDeserializer)
        }
        const scaleTmpResult : ParticlePropertyOptionsInner | undefined = scaleTmpBuf
        const velocityTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let velocityTmpBuf : VelocityOptions | undefined = undefined
        if ((velocityTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            velocityTmpBuf = VelocityOptions_serializer.read(valueDeserializer)
        }
        const velocityTmpResult : VelocityOptions | undefined = velocityTmpBuf
        const accelerationTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let accelerationTmpBuf : AccelerationOptionsInner | undefined = undefined
        if ((accelerationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            accelerationTmpBuf = AccelerationOptionsInner_serializer.read(valueDeserializer)
        }
        const accelerationTmpResult : AccelerationOptionsInner | undefined = accelerationTmpBuf
        const spinTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let spinTmpBuf : ParticlePropertyOptionsInner | undefined = undefined
        if ((spinTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            spinTmpBuf = ParticlePropertyOptionsInner_serializer.read(valueDeserializer)
        }
        const spinTmpResult : ParticlePropertyOptionsInner | undefined = spinTmpBuf
        let value : ParticleOptionsInner = ({emitter: emitterTmpResult, color: colorTmpResult, opacity: opacityTmpResult, scale: scaleTmpResult, velocity: velocityTmpResult, acceleration: accelerationTmpResult, spin: spinTmpResult} as ParticleOptionsInner)
        return value
    }
}