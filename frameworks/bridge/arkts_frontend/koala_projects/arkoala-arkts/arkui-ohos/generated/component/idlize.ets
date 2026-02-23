/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

import { SerializerBase, DeserializerBase, Finalizable, RuntimeType, toPeerPtr, KPointer, MaterializedBase, MaterializedBaseTag, NativeBuffer, resourceFinalizerRegister, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { ActionSheetOptions_serializer, ActionSheetOptions, DismissDialogAction, DismissDialogAction_serializer } from './actionSheet'
import { unsafeCast, int32, int64, float32 } from '@koalaui/common'
import { ArkUIGeneratedNativeModule } from '#components'
import { CallbackTransformer } from './../CallbackTransformer'
import { AlertDialogParamWithConfirm_serializer, AlertDialogParamWithButtons_serializer, AlertDialogParamWithOptions_serializer, AlertDialogParamWithConfirm, AlertDialogParamWithButtons, AlertDialogParamWithOptions, DialogAlignment } from './alertDialog'
import { AnimateParam_serializer, TranslateOptions_serializer, KeyframeAnimateParam_serializer, KeyframeState_serializer, AnimateParam, TranslateOptions, KeyframeAnimateParam, KeyframeState, Bindable_I32_serializer, Bindable, BlurStyle, OnWillScrollCallback, OnScrollCallback, TouchEvent_serializer, MouseEvent_serializer, AxisEvent_serializer, TouchEvent, TouchEventInternal, MouseEvent, MouseEventInternal, AxisEvent, AxisEventInternal, ClickEvent, ClickEventInternal, ItemDragEventHandler_serializer, OnMoveHandler, ItemDragEventHandler, UICommonEvent, UICommonEventInternal, SourceTool, SheetOptions_serializer, KeyEvent, KeyEventInternal, SheetOptions, PopupCommonOptions_serializer, MenuOptions_serializer, PopupCommonOptions, MenuOptions, ThemeColorMode, UIScrollableCommonEvent, UIScrollableCommonEventInternal, GeometryInfo, Measurable, Layoutable, ICurve, Rectangle, ShadowOptions, ShadowStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, KeyboardAvoidMode as arkui_component_common_KeyboardAvoidMode, HoverModeAreaType, SizeResult, CommonMethod, Rectangle_serializer, ShadowOptions_serializer, BackgroundBlurStyleOptions_serializer, BackgroundEffectOptions_serializer } from './common'
import { extractors, ContentModifier, CustomDialogController, initializers, hookRootAttributeModifier, AttributeModifier, AttributeUpdater, hookComponentRootAttributeModifier, hookCustomBuilderRootAttributeModifier, hookCustomLayoutRootAttributeModifier } from '#handwritten'
import { arkui_component_units_Font_serializer, Font as arkui_component_units_Font, VoidCallback, SizeOptions_serializer, Length, Resource as arkui_component_units_Resource, SizeOptions, Position_serializer, Position, ResourceColor, ConstraintSizeOptions, Offset, Dimension, BorderRadiuses, EdgeWidths, EdgeColors, EdgeStyles, Offset_serializer, BorderRadiuses_serializer, EdgeWidths_serializer, EdgeColors_serializer, EdgeStyles_serializer } from './units'
import { arkui_Graphics_LengthMetrics_serializer, Vector2_serializer, Size_serializer, Vector3_serializer, Circle_serializer, RoundRect_serializer, CommandPath_serializer, Frame_serializer } from './../framework/Graphics'
import { ColorMetrics as arkui_Graphics_ColorMetrics, LengthMetrics as arkui_Graphics_LengthMetrics, Vector2, Size, NodePosition, Vector3, Matrix4, Rect, Circle, RoundRect, CommandPath, Frame } from 'arkui.Graphics'
import { ArkListOptions_serializer } from './../framework/ohos.arkui.ArcList'
import { ArkListOptions, ArcScrollIndexHandler } from '@ohos.arkui.ArcList'
import { CrownSensitivity, BarState, ScrollSource, EdgeEffect, Color as arkui_component_enums_Color, AnimationPropertyType, EventQueryType, Curve, BorderStyle, ColorSpace } from './enums'
import { ScrollState, UIListEvent, UIListEventInternal } from './list'
import { SwipeActionOptions_serializer, SwipeActionOptions } from './listItem'
import { ArcScrollBarOptions_serializer } from './../framework/ohos.arkui.ArcScrollBar'
import { ArcScrollBarOptions } from '@ohos.arkui.ArcScrollBar'
import { SwiperContentAnimatedTransition_serializer, SwiperAnimationEvent, SwiperContentAnimatedTransition } from './swiper'
import { global_resource_Resource_serializer } from './../framework/resource'
import { Resource as global_resource_Resource } from 'global.resource'
import { ImageAnalyzerConfig_serializer, ImageAnalyzerConfig } from './imageCommon'
import { CanvasRenderingContext2D, CanvasRenderingContext2DInternal } from './canvas'
import { ButtonConfiguration } from './button'
import { CheckBoxConfiguration } from './checkbox'
import { DataPanelConfiguration, DataPanelShadowOptions_serializer, DataPanelShadowOptions, LinearGradient, LinearGradient_serializer } from './dataPanel'
import { GaugeConfiguration, GaugeIndicatorOptions_serializer, GaugeShadowOptions_serializer, GaugeIndicatorOptions, GaugeShadowOptions } from './gauge'
import { LoadingProgressConfiguration } from './loadingProgress'
import { ProgressConfiguration } from './progress'
import { RadioConfiguration } from './radio'
import { RatingConfiguration } from './rating'
import { MenuItemConfiguration, MenuItemConfigurationInternal } from './select'
import { SliderConfiguration, SliderPrefixOptions_serializer, SliderSuffixOptions_serializer, SliderPrefixOptions, SliderSuffixOptions } from './slider'
import { TextClockConfiguration } from './textClock'
import { TextTimerConfiguration } from './textTimer'
import { ToggleConfiguration } from './toggle'
import { CheckBoxGroupConfiguration, CheckBoxGroupConfigurationInternal } from './checkboxgroup'
import { default as promptAction, LevelMode, ImmersiveMode } from '@ohos.promptAction'
import { TimePickerDialogOptions_serializer, TimePickerDialogOptions } from './timePicker'
import { TextPickerDialogOptions_serializer, TextPickerDialogOptionsExt_serializer, TextPickerDialogOptions, TextPickerDialogOptionsExt, DividerOptions_serializer, DividerOptions } from './textPicker'
import { DatePickerDialogOptions_serializer, DatePickerDialogOptions } from './datePicker'
import { LayoutConstraint_serializer, InteractionEventBindingInfo_serializer } from './../framework/FrameNode'
import { FrameNode, UIStatesChangeHandler, LayoutConstraint, InteractionEventBindingInfo } from 'arkui.FrameNode'
import { CustomBuilder } from './builder'
import { PanDirection, SwipeDirection, GestureMode, GestureEvent, GestureEventInternal, GestureMask, GestureRecognizer, GestureRecognizerInternal, GestureEvent_serializer, GestureRecognizer_serializer } from './gesture'
import { default as image } from '@ohos.multimedia.image'
import { font_FontOptions_serializer, font_FontInfo_serializer, font_UIFontConfig_serializer } from './../framework/ohos.font'
import { default as font } from '@ohos.font'
import { MeasureOptions_serializer } from './../framework/ohos.measure'
import { MeasureOptions } from '@ohos.measure'
import { TextMenuOptions_serializer, TextMenuOptions } from './textCommon'
import { TabsController, TabsControllerInternal } from './tabs'
import { Scroller, ScrollerInternal, UIScrollEvent, UIScrollEventInternal } from './scroll'
import { CustomKeyboardContinueFeature, TargetInfo, GestureListenerType, GestureActionPhase } from '@ohos.arkui.UIContext'
import { NavigationOptions_serializer, NavPathStack, NavPathStackInternal, NavPathInfo, NavPathInfoInternal, NavigationOptions } from './navigation'
import { TargetInfo_serializer } from './../framework/ohos.arkui.UIContext'
import { common2D_Rect_serializer } from './../framework/ohos.graphics.common2D'
import { RenderNode } from 'arkui.RenderNode'
import { default as common2D } from '@ohos.graphics.common2D'
import { uiObserver_NavigationInfo_serializer } from './../framework/ohos.arkui.observer'
import { default as uiObserver } from '@ohos.arkui.observer'
import { UIGridEvent, UIGridEventInternal } from './grid'
import { UIWaterFlowEvent, UIWaterFlowEventInternal } from './waterFlow'
import { XComponentController, XComponentControllerInternal } from './xcomponent'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { default as curves } from '@ohos.curves'
import { ParticleUpdater, ParticleColorOptions, VelocityOptions, EmitterParticleOptions, ParticleEmitterShape, DistributionType, DisturbanceFieldShape, ParticleColorOptions_serializer, EmitterParticleOptions_serializer, VelocityOptions_serializer } from './particle'
import { default as router } from '@ohos.router'
import { RootModifier } from './../RootModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { ComponentRootModifier } from './../ComponentRootModifier'
import { CustomBuilderRootModifier } from './../CustomBuilderRootModifier'
import { CustomLayoutRootModifier } from './../CustomLayoutRootModifier'
import { GlobalScope } from './../framework/GlobalScope'
import { curves_ICurve_serializer } from './../framework/ohos.curves'
export class ActionSheet {
    public static show(options: ActionSheetOptions): void {
        const options_casted = options as (ActionSheetOptions)
        ActionSheet.show_serialize(options_casted)
        return
    }
    private static show_serialize(options: ActionSheetOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        ActionSheetOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._ActionSheet_show(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class AlertDialog {
    public static show(options: AlertDialogParamWithConfirm | AlertDialogParamWithButtons | AlertDialogParamWithOptions): void {
        const options_casted = options as (AlertDialogParamWithConfirm | AlertDialogParamWithButtons | AlertDialogParamWithOptions)
        AlertDialog.show_serialize(options_casted)
        return
    }
    private static show_serialize(options: AlertDialogParamWithConfirm | AlertDialogParamWithButtons | AlertDialogParamWithOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (options instanceof AlertDialogParamWithConfirm) {
            thisSerializer.writeInt8((0).toByte())
            const optionsForIdx0 = options as AlertDialogParamWithConfirm
            AlertDialogParamWithConfirm_serializer.write(thisSerializer, optionsForIdx0)
        } else if (options instanceof AlertDialogParamWithButtons) {
            thisSerializer.writeInt8((1).toByte())
            const optionsForIdx1 = options as AlertDialogParamWithButtons
            AlertDialogParamWithButtons_serializer.write(thisSerializer, optionsForIdx1)
        } else if (options instanceof AlertDialogParamWithOptions) {
            thisSerializer.writeInt8((2).toByte())
            const optionsForIdx2 = options as AlertDialogParamWithOptions
            AlertDialogParamWithOptions_serializer.write(thisSerializer, optionsForIdx2)
        }
        ArkUIGeneratedNativeModule._AlertDialog_show(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class AnimationExtender {
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
    private static SetClipRect_serialize(node: KPointer, x: float, y: float, width: float, height: float): void {
        ArkUIGeneratedNativeModule._AnimationExtender_SetClipRect(node, x, y, width, height)
    }
    private static OpenImplicitAnimation_serialize(param: AnimateParam): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        AnimateParam_serializer.write(thisSerializer, param)
        ArkUIGeneratedNativeModule._AnimationExtender_OpenImplicitAnimation(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static CloseImplicitAnimation_serialize(): void {
        ArkUIGeneratedNativeModule._AnimationExtender_CloseImplicitAnimation()
    }
    private static OpenImplicitAnimationForAnimation_serialize(node: KPointer, param: AnimateParam | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (param !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const paramTmpValue = param!
            AnimateParam_serializer.write(thisSerializer, paramTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._AnimationExtender_OpenImplicitAnimationForAnimation(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static CloseImplicitAnimationForAnimation_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._AnimationExtender_CloseImplicitAnimationForAnimation(node)
    }
    private static StartDoubleAnimation_serialize(node: KPointer, param: DoubleAnimationParam): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        DoubleAnimationParam_serializer.write(thisSerializer, param)
        ArkUIGeneratedNativeModule._AnimationExtender_StartDoubleAnimation(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static AnimationTranslate_serialize(node: KPointer, options: TranslateOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        TranslateOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._AnimationExtender_AnimationTranslate(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static AnimateToImmediatelyImpl_serialize(param: AnimateParam, event: (() => void), immediately: boolean): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        AnimateParam_serializer.write(thisSerializer, param)
        thisSerializer.holdAndWriteCallback(event)
        ArkUIGeneratedNativeModule._AnimationExtender_AnimateToImmediatelyImpl(thisSerializer.asBuffer(), thisSerializer.length(), immediately ? true : false)
        thisSerializer.release()
    }
    private static KeyframeAnimationImpl_serialize(param: KeyframeAnimateParam, keyfames: Array<KeyframeState>): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        KeyframeAnimateParam_serializer.write(thisSerializer, param)
        thisSerializer.writeInt32((keyfames.length).toInt())
        for (let keyfamesCounterI = 0; keyfamesCounterI < keyfames.length; keyfamesCounterI++) {
            const keyfamesTmpElement: KeyframeState = keyfames[keyfamesCounterI]
            KeyframeState_serializer.write(thisSerializer, keyfamesTmpElement)
        }
        ArkUIGeneratedNativeModule._AnimationExtender_KeyframeAnimationImpl(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArcAlphabetIndexerExtender {
    public static arcAlphabetIndexerConstruct(id: int32, flags: int32): KPointer {
        const id_casted = id as (int32)
        const flags_casted = flags as (int32)
        return ArcAlphabetIndexerExtender.arcAlphabetIndexerConstruct_serialize(id_casted, flags_casted)
    }
    public static setArcAlphabetIndexerInitInfo(node: KPointer, arrayValue: Array<string>, selected: int32 | Bindable<int32>): void {
        const node_casted = node as (KPointer)
        const arrayValue_casted = arrayValue as (Array<string>)
        const selected_casted = selected as (int32 | Bindable<int32>)
        ArcAlphabetIndexerExtender.setArcAlphabetIndexerInitInfo_serialize(node_casted, arrayValue_casted, selected_casted)
        return
    }
    public static color(node: KPointer, color: arkui_Graphics_ColorMetrics | undefined): void {
        const node_casted = node as (KPointer)
        const color_casted = color as (arkui_Graphics_ColorMetrics | undefined)
        ArcAlphabetIndexerExtender.color_serialize(node_casted, color_casted)
        return
    }
    public static selectedColor(node: KPointer, color: arkui_Graphics_ColorMetrics | undefined): void {
        const node_casted = node as (KPointer)
        const color_casted = color as (arkui_Graphics_ColorMetrics | undefined)
        ArcAlphabetIndexerExtender.selectedColor_serialize(node_casted, color_casted)
        return
    }
    public static popupColor(node: KPointer, color: arkui_Graphics_ColorMetrics | undefined): void {
        const node_casted = node as (KPointer)
        const color_casted = color as (arkui_Graphics_ColorMetrics | undefined)
        ArcAlphabetIndexerExtender.popupColor_serialize(node_casted, color_casted)
        return
    }
    public static selectedBackgroundColor(node: KPointer, color: arkui_Graphics_ColorMetrics | undefined): void {
        const node_casted = node as (KPointer)
        const color_casted = color as (arkui_Graphics_ColorMetrics | undefined)
        ArcAlphabetIndexerExtender.selectedBackgroundColor_serialize(node_casted, color_casted)
        return
    }
    public static popupBackground(node: KPointer, color: arkui_Graphics_ColorMetrics | undefined): void {
        const node_casted = node as (KPointer)
        const color_casted = color as (arkui_Graphics_ColorMetrics | undefined)
        ArcAlphabetIndexerExtender.popupBackground_serialize(node_casted, color_casted)
        return
    }
    public static usePopup(node: KPointer, enabled: boolean | undefined): void {
        const node_casted = node as (KPointer)
        const enabled_casted = enabled as (boolean | undefined)
        ArcAlphabetIndexerExtender.usePopup_serialize(node_casted, enabled_casted)
        return
    }
    public static selectedFont(node: KPointer, font: arkui_component_units_Font | undefined): void {
        const node_casted = node as (KPointer)
        const font_casted = font as (arkui_component_units_Font | undefined)
        ArcAlphabetIndexerExtender.selectedFont_serialize(node_casted, font_casted)
        return
    }
    public static popupFont(node: KPointer, font: arkui_component_units_Font | undefined): void {
        const node_casted = node as (KPointer)
        const font_casted = font as (arkui_component_units_Font | undefined)
        ArcAlphabetIndexerExtender.popupFont_serialize(node_casted, font_casted)
        return
    }
    public static font(node: KPointer, font: arkui_component_units_Font | undefined): void {
        const node_casted = node as (KPointer)
        const font_casted = font as (arkui_component_units_Font | undefined)
        ArcAlphabetIndexerExtender.font_serialize(node_casted, font_casted)
        return
    }
    public static itemSize(node: KPointer, size: arkui_Graphics_LengthMetrics | undefined): void {
        const node_casted = node as (KPointer)
        const size_casted = size as (arkui_Graphics_LengthMetrics | undefined)
        ArcAlphabetIndexerExtender.itemSize_serialize(node_casted, size_casted)
        return
    }
    public static selected(node: KPointer, index: int32 | Bindable<int32> | undefined): void {
        const node_casted = node as (KPointer)
        const index_casted = index as (int32 | Bindable<int32> | undefined)
        ArcAlphabetIndexerExtender.selected_serialize(node_casted, index_casted)
        return
    }
    public static autoCollapse(node: KPointer, enable: boolean | undefined): void {
        const node_casted = node as (KPointer)
        const enable_casted = enable as (boolean | undefined)
        ArcAlphabetIndexerExtender.autoCollapse_serialize(node_casted, enable_casted)
        return
    }
    public static onSelect(node: KPointer, handler: Callback_I32_Void | undefined): void {
        const node_casted = node as (KPointer)
        const handler_casted = handler as (Callback_I32_Void | undefined)
        ArcAlphabetIndexerExtender.onSelect_serialize(node_casted, handler_casted)
        return
    }
    public static popupBackgroundBlurStyle(node: KPointer, style: BlurStyle | undefined): void {
        const node_casted = node as (KPointer)
        const style_casted = style as (BlurStyle | undefined)
        ArcAlphabetIndexerExtender.popupBackgroundBlurStyle_serialize(node_casted, style_casted)
        return
    }
    private static arcAlphabetIndexerConstruct_serialize(id: int32, flags: int32): KPointer {
        const retval = ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_arcAlphabetIndexerConstruct(id, flags)
        return retval
    }
    private static setArcAlphabetIndexerInitInfo_serialize(node: KPointer, arrayValue: Array<string>, selected: int32 | Bindable<int32>): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((arrayValue.length).toInt())
        for (let arrayValueCounterI = 0; arrayValueCounterI < arrayValue.length; arrayValueCounterI++) {
            const arrayValueTmpElement: string = arrayValue[arrayValueCounterI]
            thisSerializer.writeString(arrayValueTmpElement)
        }
        if (selected instanceof int32) {
            thisSerializer.writeInt8((0).toByte())
            const selectedForIdx0 = selected as int32
            thisSerializer.writeInt32(selectedForIdx0)
        } else if (selected instanceof Bindable) {
            thisSerializer.writeInt8((1).toByte())
            const selectedForIdx1 = selected as Bindable<int32>
            Bindable_I32_serializer.write(thisSerializer, selectedForIdx1)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_setArcAlphabetIndexerInitInfo(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static color_serialize(node: KPointer, color: arkui_Graphics_ColorMetrics | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (color !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const colorTmpValue = color!
            const colorTmpValueTransformed: ColorMetricsExt = extractors.transform_Ark_ColorMetrics_to_Ark_ColorMetricsExt(colorTmpValue)
            ColorMetricsExt_serializer.write(thisSerializer, colorTmpValueTransformed)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_color(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static selectedColor_serialize(node: KPointer, color: arkui_Graphics_ColorMetrics | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (color !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const colorTmpValue = color!
            const colorTmpValueTransformed: ColorMetricsExt = extractors.transform_Ark_ColorMetrics_to_Ark_ColorMetricsExt(colorTmpValue)
            ColorMetricsExt_serializer.write(thisSerializer, colorTmpValueTransformed)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_selectedColor(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static popupColor_serialize(node: KPointer, color: arkui_Graphics_ColorMetrics | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (color !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const colorTmpValue = color!
            const colorTmpValueTransformed: ColorMetricsExt = extractors.transform_Ark_ColorMetrics_to_Ark_ColorMetricsExt(colorTmpValue)
            ColorMetricsExt_serializer.write(thisSerializer, colorTmpValueTransformed)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_popupColor(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static selectedBackgroundColor_serialize(node: KPointer, color: arkui_Graphics_ColorMetrics | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (color !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const colorTmpValue = color!
            const colorTmpValueTransformed: ColorMetricsExt = extractors.transform_Ark_ColorMetrics_to_Ark_ColorMetricsExt(colorTmpValue)
            ColorMetricsExt_serializer.write(thisSerializer, colorTmpValueTransformed)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_selectedBackgroundColor(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static popupBackground_serialize(node: KPointer, color: arkui_Graphics_ColorMetrics | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (color !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const colorTmpValue = color!
            const colorTmpValueTransformed: ColorMetricsExt = extractors.transform_Ark_ColorMetrics_to_Ark_ColorMetricsExt(colorTmpValue)
            ColorMetricsExt_serializer.write(thisSerializer, colorTmpValueTransformed)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_popupBackground(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static usePopup_serialize(node: KPointer, enabled: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (enabled !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const enabledTmpValue = enabled!
            thisSerializer.writeBoolean(enabledTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_usePopup(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static selectedFont_serialize(node: KPointer, font: arkui_component_units_Font | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (font !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const fontTmpValue = font!
            arkui_component_units_Font_serializer.write(thisSerializer, fontTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_selectedFont(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static popupFont_serialize(node: KPointer, font: arkui_component_units_Font | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (font !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const fontTmpValue = font!
            arkui_component_units_Font_serializer.write(thisSerializer, fontTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_popupFont(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static font_serialize(node: KPointer, font: arkui_component_units_Font | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (font !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const fontTmpValue = font!
            arkui_component_units_Font_serializer.write(thisSerializer, fontTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_font(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static itemSize_serialize(node: KPointer, size: arkui_Graphics_LengthMetrics | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (size !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const sizeTmpValue = size!
            arkui_Graphics_LengthMetrics_serializer.write(thisSerializer, sizeTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_itemSize(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static selected_serialize(node: KPointer, index: int32 | Bindable<int32> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (index !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const indexTmpValue = index!
            if (indexTmpValue instanceof int32) {
                thisSerializer.writeInt8((0).toByte())
                const indexTmpValueForIdx0 = indexTmpValue as int32
                thisSerializer.writeInt32(indexTmpValueForIdx0)
            } else if (indexTmpValue instanceof Bindable) {
                thisSerializer.writeInt8((1).toByte())
                const indexTmpValueForIdx1 = indexTmpValue as Bindable<int32>
                Bindable_I32_serializer.write(thisSerializer, indexTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_selected(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static autoCollapse_serialize(node: KPointer, enable: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (enable !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const enableTmpValue = enable!
            thisSerializer.writeBoolean(enableTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_autoCollapse(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static onSelect_serialize(node: KPointer, handler: Callback_I32_Void | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (handler !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const handlerTmpValue = handler!
            thisSerializer.holdAndWriteCallback(handlerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_onSelect(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static popupBackgroundBlurStyle_serialize(node: KPointer, style: BlurStyle | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (style !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const styleTmpValue = (style as BlurStyle)
            thisSerializer.writeInt32(styleTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcAlphabetIndexerExtender_popupBackgroundBlurStyle(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArcListExtender {
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
    public static space(node: KPointer, space?: arkui_Graphics_LengthMetrics): void {
        const node_casted = node as (KPointer)
        const space_casted = space as (arkui_Graphics_LengthMetrics | undefined)
        ArcListExtender.space_serialize(node_casted, space_casted)
        return
    }
    public static scrollBar(node: KPointer, status?: BarState): void {
        const node_casted = node as (KPointer)
        const status_casted = status as (BarState | undefined)
        ArcListExtender.scrollBar_serialize(node_casted, status_casted)
        return
    }
    public static scrollBarColor(node: KPointer, color?: arkui_Graphics_ColorMetrics): void {
        const node_casted = node as (KPointer)
        const color_casted = color as (arkui_Graphics_ColorMetrics | undefined)
        ArcListExtender.scrollBarColor_serialize(node_casted, color_casted)
        return
    }
    public static scrollBarWidth(node: KPointer, width?: arkui_Graphics_LengthMetrics): void {
        const node_casted = node as (KPointer)
        const width_casted = width as (arkui_Graphics_LengthMetrics | undefined)
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
    private static arcListConstructor_serialize(id: int32): KPointer {
        const retval = ArkUIGeneratedNativeModule._ArcListExtender_arcListConstructor(id)
        return retval
    }
    private static setArkListOptions_serialize(node: KPointer, options?: ArkListOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue = options!
            ArkListOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_setArkListOptions(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static digitalCrownSensitivity_serialize(node: KPointer, sensitivity?: CrownSensitivity): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (sensitivity !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const sensitivityTmpValue = (sensitivity as CrownSensitivity)
            thisSerializer.writeInt32(sensitivityTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_digitalCrownSensitivity(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static space_serialize(node: KPointer, space?: arkui_Graphics_LengthMetrics): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (space !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const spaceTmpValue = space!
            arkui_Graphics_LengthMetrics_serializer.write(thisSerializer, spaceTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_space(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static scrollBar_serialize(node: KPointer, status?: BarState): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (status !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const statusTmpValue = (status as BarState)
            thisSerializer.writeInt32(statusTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_scrollBar(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static scrollBarColor_serialize(node: KPointer, color?: arkui_Graphics_ColorMetrics): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (color !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const colorTmpValue = color!
            const colorTmpValueTransformed: ColorMetricsExt = extractors.transform_Ark_ColorMetrics_to_Ark_ColorMetricsExt(colorTmpValue)
            ColorMetricsExt_serializer.write(thisSerializer, colorTmpValueTransformed)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_scrollBarColor(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static scrollBarWidth_serialize(node: KPointer, width?: arkui_Graphics_LengthMetrics): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (width !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const widthTmpValue = width!
            arkui_Graphics_LengthMetrics_serializer.write(thisSerializer, widthTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_scrollBarWidth(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static cachedCount_serialize(node: KPointer, count?: int32): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (count !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const countTmpValue = count!
            thisSerializer.writeInt32(countTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_cachedCount(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static chainAnimation_serialize(node: KPointer, enable?: boolean): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (enable !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const enableTmpValue = enable!
            thisSerializer.writeBoolean(enableTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_chainAnimation(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static enableScrollInteraction_serialize(node: KPointer, enable?: boolean): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (enable !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const enableTmpValue = enable!
            thisSerializer.writeBoolean(enableTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_enableScrollInteraction(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static fadingEdge_serialize(node: KPointer, enable?: boolean): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (enable !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const enableTmpValue = enable!
            thisSerializer.writeBoolean(enableTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_fadingEdge(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static friction_serialize(node: KPointer, friction?: double): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (friction !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const frictionTmpValue = friction!
            thisSerializer.writeFloat64(frictionTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_friction(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static flingSpeedLimit_serialize(node: KPointer, speed?: double): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (speed !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const speedTmpValue = speed!
            thisSerializer.writeFloat64(speedTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_flingSpeedLimit(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static onScrollIndex_serialize(node: KPointer, handler?: ArcScrollIndexHandler): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (handler !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const handlerTmpValue = handler!
            thisSerializer.holdAndWriteCallback(handlerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_onScrollIndex(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static onReachStart_serialize(node: KPointer, handler?: VoidCallback): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (handler !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const handlerTmpValue = handler!
            thisSerializer.holdAndWriteCallback(handlerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_onReachStart(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static onReachEnd_serialize(node: KPointer, handler?: VoidCallback): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (handler !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const handlerTmpValue = handler!
            thisSerializer.holdAndWriteCallback(handlerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_onReachEnd(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static onScrollStart_serialize(node: KPointer, handler?: VoidCallback): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (handler !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const handlerTmpValue = handler!
            thisSerializer.holdAndWriteCallback(handlerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_onScrollStart(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static onScrollStop_serialize(node: KPointer, handler?: VoidCallback): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (handler !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const handlerTmpValue = handler!
            thisSerializer.holdAndWriteCallback(handlerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_onScrollStop(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static onWillScroll_serialize(node: KPointer, handler?: OnWillScrollCallback): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (handler !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const handlerTmpValue = handler!
            thisSerializer.holdAndWriteCallback(handlerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_onWillScroll(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static onDidScroll_serialize(node: KPointer, handler?: OnScrollCallback): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (handler !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const handlerTmpValue = handler!
            thisSerializer.holdAndWriteCallback(handlerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListExtender_onDidScroll(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArcListItemExtender {
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
    private static arcListItemConstructor_serialize(id: int32): KPointer {
        const retval = ArkUIGeneratedNativeModule._ArcListItemExtender_arcListItemConstructor(id)
        return retval
    }
    private static autoScale_serialize(node: KPointer, enable?: boolean): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (enable !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const enableTmpValue = enable!
            thisSerializer.writeBoolean(enableTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListItemExtender_autoScale(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static swipeAction_serialize(node: KPointer, options?: SwipeActionOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue = options!
            SwipeActionOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcListItemExtender_swipeAction(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArcScrollBarExtender {
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
    private static arcScrollBarConstructor_serialize(id: int32): KPointer {
        const retval = ArkUIGeneratedNativeModule._ArcScrollBarExtender_arcScrollBarConstructor(id)
        return retval
    }
    private static setArcScrollBarOptions_serialize(node: KPointer, options: ArcScrollBarOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        ArcScrollBarOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._ArcScrollBarExtender_setArcScrollBarOptions(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArcSwiperControllerHelperInternal {
    public static fromPtr(ptr: KPointer): ArcSwiperControllerHelper {
        return new ArcSwiperControllerHelper(MaterializedBaseTag.NOP, ptr)
    }
}
export class ArcSwiperControllerHelper implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, ArcSwiperControllerHelper.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, ArcSwiperControllerHelper.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._ArcSwiperControllerHelper_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._ArcSwiperControllerHelper_getFinalizer()
    }
    public static showNext(node: KPointer): void {
        const node_casted = node as (KPointer)
        ArcSwiperControllerHelper.showNext_serialize(node_casted)
        return
    }
    public static showPrevious(node: KPointer): void {
        const node_casted = node as (KPointer)
        ArcSwiperControllerHelper.showPrevious_serialize(node_casted)
        return
    }
    public static finishAnimation(node: KPointer, callback_?: VoidCallback): void {
        const node_casted = node as (KPointer)
        const callback__casted = callback_ as (VoidCallback | undefined)
        ArcSwiperControllerHelper.finishAnimation_serialize(node_casted, callback__casted)
        return
    }
    private static showNext_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ArcSwiperControllerHelper_showNext(node)
    }
    private static showPrevious_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ArcSwiperControllerHelper_showPrevious(node)
    }
    private static finishAnimation_serialize(node: KPointer, callback_?: VoidCallback): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (callback_ !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const callback_TmpValue = callback_!
            thisSerializer.holdAndWriteCallback(callback_TmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcSwiperControllerHelper_finishAnimation(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArcSwiperExtender {
    public static arcSwiperConstruct(id: int32, flags: int32): KPointer {
        const id_casted = id as (int32)
        const flags_casted = flags as (int32)
        return ArcSwiperExtender.arcSwiperConstruct_serialize(id_casted, flags_casted)
    }
    public static setConstructInfo(node: KPointer, controller: ArcSwiperControllerHelper | undefined): void {
        const node_casted = node as (KPointer)
        const controller_casted = controller as (ArcSwiperControllerHelper | undefined)
        ArcSwiperExtender.setConstructInfo_serialize(node_casted, controller_casted)
        return
    }
    public static index(node: KPointer, value: int32 | undefined): void {
        const node_casted = node as (KPointer)
        const value_casted = value as (int32 | undefined)
        ArcSwiperExtender.index_serialize(node_casted, value_casted)
        return
    }
    public static indicator(node: KPointer, style: ArcDotIndicatorInner | boolean | undefined): void {
        const node_casted = node as (KPointer)
        const style_casted = style as (ArcDotIndicatorInner | boolean | undefined)
        ArcSwiperExtender.indicator_serialize(node_casted, style_casted)
        return
    }
    public static duration(node: KPointer, duration: int32 | undefined): void {
        const node_casted = node as (KPointer)
        const duration_casted = duration as (int32 | undefined)
        ArcSwiperExtender.duration_serialize(node_casted, duration_casted)
        return
    }
    public static vertical(node: KPointer, isVertical: boolean | undefined): void {
        const node_casted = node as (KPointer)
        const isVertical_casted = isVertical as (boolean | undefined)
        ArcSwiperExtender.vertical_serialize(node_casted, isVertical_casted)
        return
    }
    public static disableSwipe(node: KPointer, disabled: boolean | undefined): void {
        const node_casted = node as (KPointer)
        const disabled_casted = disabled as (boolean | undefined)
        ArcSwiperExtender.disableSwipe_serialize(node_casted, disabled_casted)
        return
    }
    public static digitalCrownSensitivity(node: KPointer, sensitivity: CrownSensitivity | undefined): void {
        const node_casted = node as (KPointer)
        const sensitivity_casted = sensitivity as (CrownSensitivity | undefined)
        ArcSwiperExtender.digitalCrownSensitivity_serialize(node_casted, sensitivity_casted)
        return
    }
    public static onChange(node: KPointer, handler: Callback_I32_Void | undefined): void {
        const node_casted = node as (KPointer)
        const handler_casted = handler as (Callback_I32_Void | undefined)
        ArcSwiperExtender.onChange_serialize(node_casted, handler_casted)
        return
    }
    public static onAnimationStart(node: KPointer, handler: AnimationStartHandler | undefined): void {
        const node_casted = node as (KPointer)
        const handler_casted = handler as (AnimationStartHandler | undefined)
        ArcSwiperExtender.onAnimationStart_serialize(node_casted, handler_casted)
        return
    }
    public static onAnimationEnd(node: KPointer, handler: AnimationEndHandler | undefined): void {
        const node_casted = node as (KPointer)
        const handler_casted = handler as (AnimationEndHandler | undefined)
        ArcSwiperExtender.onAnimationEnd_serialize(node_casted, handler_casted)
        return
    }
    public static onGestureSwipe(node: KPointer, handler: GestureSwipeHandler | undefined): void {
        const node_casted = node as (KPointer)
        const handler_casted = handler as (GestureSwipeHandler | undefined)
        ArcSwiperExtender.onGestureSwipe_serialize(node_casted, handler_casted)
        return
    }
    public static effectMode(node: KPointer, edgeEffect: EdgeEffect | undefined): void {
        const node_casted = node as (KPointer)
        const edgeEffect_casted = edgeEffect as (EdgeEffect | undefined)
        ArcSwiperExtender.effectMode_serialize(node_casted, edgeEffect_casted)
        return
    }
    public static customContentTransition(node: KPointer, transition: SwiperContentAnimatedTransition | undefined): void {
        const node_casted = node as (KPointer)
        const transition_casted = transition as (SwiperContentAnimatedTransition | undefined)
        ArcSwiperExtender.customContentTransition_serialize(node_casted, transition_casted)
        return
    }
    public static disableTransitionAnimation(node: KPointer, disabled: boolean | undefined): void {
        const node_casted = node as (KPointer)
        const disabled_casted = disabled as (boolean | undefined)
        ArcSwiperExtender.disableTransitionAnimation_serialize(node_casted, disabled_casted)
        return
    }
    private static arcSwiperConstruct_serialize(id: int32, flags: int32): KPointer {
        const retval = ArkUIGeneratedNativeModule._ArcSwiperExtender_arcSwiperConstruct(id, flags)
        return retval
    }
    private static setConstructInfo_serialize(node: KPointer, controller: ArcSwiperControllerHelper | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (controller !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const controllerTmpValue = controller!
            ArcSwiperControllerHelper_serializer.write(thisSerializer, controllerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcSwiperExtender_setConstructInfo(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static index_serialize(node: KPointer, value: int32 | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeInt32(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcSwiperExtender_index(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static indicator_serialize(node: KPointer, style: ArcDotIndicatorInner | boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (style !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const styleTmpValue = style!
            if (styleTmpValue instanceof ArcDotIndicatorInner) {
                thisSerializer.writeInt8((0).toByte())
                const styleTmpValueForIdx0 = styleTmpValue as ArcDotIndicatorInner
                ArcDotIndicatorInner_serializer.write(thisSerializer, styleTmpValueForIdx0)
            } else if (styleTmpValue instanceof boolean) {
                thisSerializer.writeInt8((1).toByte())
                const styleTmpValueForIdx1 = styleTmpValue as boolean
                thisSerializer.writeBoolean(styleTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcSwiperExtender_indicator(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static duration_serialize(node: KPointer, duration: int32 | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (duration !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const durationTmpValue = duration!
            thisSerializer.writeInt32(durationTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcSwiperExtender_duration(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static vertical_serialize(node: KPointer, isVertical: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (isVertical !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const isVerticalTmpValue = isVertical!
            thisSerializer.writeBoolean(isVerticalTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcSwiperExtender_vertical(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static disableSwipe_serialize(node: KPointer, disabled: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (disabled !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const disabledTmpValue = disabled!
            thisSerializer.writeBoolean(disabledTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcSwiperExtender_disableSwipe(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static digitalCrownSensitivity_serialize(node: KPointer, sensitivity: CrownSensitivity | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (sensitivity !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const sensitivityTmpValue = (sensitivity as CrownSensitivity)
            thisSerializer.writeInt32(sensitivityTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcSwiperExtender_digitalCrownSensitivity(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static onChange_serialize(node: KPointer, handler: Callback_I32_Void | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (handler !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const handlerTmpValue = handler!
            thisSerializer.holdAndWriteCallback(handlerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcSwiperExtender_onChange(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static onAnimationStart_serialize(node: KPointer, handler: AnimationStartHandler | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (handler !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const handlerTmpValue = handler!
            thisSerializer.holdAndWriteCallback(handlerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcSwiperExtender_onAnimationStart(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static onAnimationEnd_serialize(node: KPointer, handler: AnimationEndHandler | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (handler !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const handlerTmpValue = handler!
            thisSerializer.holdAndWriteCallback(handlerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcSwiperExtender_onAnimationEnd(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static onGestureSwipe_serialize(node: KPointer, handler: GestureSwipeHandler | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (handler !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const handlerTmpValue = handler!
            thisSerializer.holdAndWriteCallback(handlerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcSwiperExtender_onGestureSwipe(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static effectMode_serialize(node: KPointer, edgeEffect: EdgeEffect | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (edgeEffect !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const edgeEffectTmpValue = (edgeEffect as EdgeEffect)
            thisSerializer.writeInt32(edgeEffectTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcSwiperExtender_effectMode(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static customContentTransition_serialize(node: KPointer, transition: SwiperContentAnimatedTransition | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (transition !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const transitionTmpValue = transition!
            SwiperContentAnimatedTransition_serializer.write(thisSerializer, transitionTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcSwiperExtender_customContentTransition(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static disableTransitionAnimation_serialize(node: KPointer, disabled: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (disabled !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const disabledTmpValue = disabled!
            thisSerializer.writeBoolean(disabledTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ArcSwiperExtender_disableTransitionAnimation(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class BaseShapeInternal {
    public static fromPtr(ptr: KPointer): BaseShape {
        return new BaseShape(MaterializedBaseTag.NOP, ptr)
    }
}
export class BaseShape implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, BaseShape.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, BaseShape.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._BaseShape_construct()
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
    private width_serialize(width: Length): BaseShape {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (width instanceof string) {
            thisSerializer.writeInt8((0).toByte())
            const widthForIdx0 = width as string
            thisSerializer.writeString(widthForIdx0)
        } else if (width instanceof double) {
            thisSerializer.writeInt8((1).toByte())
            const widthForIdx1 = width as double
            thisSerializer.writeFloat64(widthForIdx1)
        } else if (width instanceof arkui_component_units_Resource) {
            thisSerializer.writeInt8((2).toByte())
            const widthForIdx2 = width as arkui_component_units_Resource
            global_resource_Resource_serializer.write(thisSerializer, widthForIdx2)
        }
        const retval = ArkUIGeneratedNativeModule._BaseShape_width(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj: BaseShape = BaseShapeInternal.fromPtr(retval)
        return obj
    }
    private height_serialize(height: Length): BaseShape {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (height instanceof string) {
            thisSerializer.writeInt8((0).toByte())
            const heightForIdx0 = height as string
            thisSerializer.writeString(heightForIdx0)
        } else if (height instanceof double) {
            thisSerializer.writeInt8((1).toByte())
            const heightForIdx1 = height as double
            thisSerializer.writeFloat64(heightForIdx1)
        } else if (height instanceof arkui_component_units_Resource) {
            thisSerializer.writeInt8((2).toByte())
            const heightForIdx2 = height as arkui_component_units_Resource
            global_resource_Resource_serializer.write(thisSerializer, heightForIdx2)
        }
        const retval = ArkUIGeneratedNativeModule._BaseShape_height(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj: BaseShape = BaseShapeInternal.fromPtr(retval)
        return obj
    }
    private size_serialize(size: SizeOptions): BaseShape {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        SizeOptions_serializer.write(thisSerializer, size)
        const retval = ArkUIGeneratedNativeModule._BaseShape_size(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj: BaseShape = BaseShapeInternal.fromPtr(retval)
        return obj
    }
}
export class BuilderNodeOpsInternal {
    public static fromPtr(ptr: KPointer): BuilderNodeOps {
        return new BuilderNodeOps(MaterializedBaseTag.NOP, ptr)
    }
}
export class BuilderNodeOps implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, BuilderNodeOps.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, BuilderNodeOps.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._BuilderNodeOps_construct()
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
    public postInputEvent(event?: InputEventType): boolean {
        const event_casted = event as (InputEventType | undefined)
        return this.postInputEvent_serialize(event_casted)
    }
    public setRootFrameNodeInBuilderNode(node: KPointer): KPointer {
        const node_casted = node as (KPointer)
        return this.setRootFrameNodeInBuilderNode_serialize(node_casted)
    }
    private create_serialize(buildFunc: (() => void)): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(buildFunc)
        ArkUIGeneratedNativeModule._BuilderNodeOps_create(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private disposeNode_serialize(): void {
        ArkUIGeneratedNativeModule._BuilderNodeOps_disposeNode(this.peer!.ptr)
    }
    private setUpdateConfigurationCallback_serialize(configurationUpdateFunc: (() => void)): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(configurationUpdateFunc)
        ArkUIGeneratedNativeModule._BuilderNodeOps_setUpdateConfigurationCallback(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOptions_serialize(options: BuilderNodeOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        BuilderNodeOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._BuilderNodeOps_setOptions(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private postTouchEvent_serialize(event: TouchEvent): boolean {
        const retval = ArkUIGeneratedNativeModule._BuilderNodeOps_postTouchEvent(this.peer!.ptr, toPeerPtr(event))
        return retval
    }
    private postInputEvent_serialize(event?: InputEventType): boolean {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (event !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const eventTmpValue = event!
            if (eventTmpValue instanceof TouchEvent) {
                thisSerializer.writeInt8((0).toByte())
                const eventTmpValueForIdx0 = eventTmpValue as TouchEvent
                TouchEvent_serializer.write(thisSerializer, eventTmpValueForIdx0)
            } else if (eventTmpValue instanceof MouseEvent) {
                thisSerializer.writeInt8((1).toByte())
                const eventTmpValueForIdx1 = eventTmpValue as MouseEvent
                MouseEvent_serializer.write(thisSerializer, eventTmpValueForIdx1)
            } else if (eventTmpValue instanceof AxisEvent) {
                thisSerializer.writeInt8((2).toByte())
                const eventTmpValueForIdx2 = eventTmpValue as AxisEvent
                AxisEvent_serializer.write(thisSerializer, eventTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval = ArkUIGeneratedNativeModule._BuilderNodeOps_postInputEvent(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private setRootFrameNodeInBuilderNode_serialize(node: KPointer): KPointer {
        const retval = ArkUIGeneratedNativeModule._BuilderNodeOps_setRootFrameNodeInBuilderNode(this.peer!.ptr, node)
        return retval
    }
}
export class CanvasRenderingContext2DExtender {
    public static startImageAnalyzer(peer: CanvasRenderingContext2D, config: ImageAnalyzerConfig): Promise<void> {
        const peer_casted = peer as (CanvasRenderingContext2D)
        const config_casted = config as (ImageAnalyzerConfig)
        return CanvasRenderingContext2DExtender.startImageAnalyzer_serialize(peer_casted, config_casted)
    }
    private static startImageAnalyzer_serialize(peer: CanvasRenderingContext2D, config: ImageAnalyzerConfig): Promise<void> {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        ImageAnalyzerConfig_serializer.write(thisSerializer, config)
        const retval = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._CanvasRenderingContext2DExtender_startImageAnalyzer(toPeerPtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
export class CommonShapeInternal {
    public static fromPtr(ptr: KPointer): CommonShape {
        return new CommonShape(MaterializedBaseTag.NOP, ptr)
    }
}
export class CommonShape implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, CommonShape.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, CommonShape.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._CommonShape_construct()
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
    private offset_serialize(offset: Position): CommonShape {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        Position_serializer.write(thisSerializer, offset)
        const retval = ArkUIGeneratedNativeModule._CommonShape_offset(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj: CommonShape = CommonShapeInternal.fromPtr(retval)
        return obj
    }
    private fill_serialize(color: ResourceColor): CommonShape {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (color instanceof arkui_component_enums_Color) {
            thisSerializer.writeInt8((0).toByte())
            const colorForIdx0 = color as arkui_component_enums_Color
            thisSerializer.writeInt32((colorForIdx0.getOrdinal()) % (12))
        } else if (color instanceof int32) {
            thisSerializer.writeInt8((1).toByte())
            const colorForIdx1 = color as int32
            thisSerializer.writeInt32(colorForIdx1)
        } else if (color instanceof string) {
            thisSerializer.writeInt8((2).toByte())
            const colorForIdx2 = color as string
            thisSerializer.writeString(colorForIdx2)
        } else if (color instanceof arkui_component_units_Resource) {
            thisSerializer.writeInt8((3).toByte())
            const colorForIdx3 = color as arkui_component_units_Resource
            global_resource_Resource_serializer.write(thisSerializer, colorForIdx3)
        }
        const retval = ArkUIGeneratedNativeModule._CommonShape_fill(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj: CommonShape = CommonShapeInternal.fromPtr(retval)
        return obj
    }
    private position_serialize(position: Position): CommonShape {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        Position_serializer.write(thisSerializer, position)
        const retval = ArkUIGeneratedNativeModule._CommonShape_position(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj: CommonShape = CommonShapeInternal.fromPtr(retval)
        return obj
    }
}
export class ContentModifierHelper {
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
    public static contentModifierCheckBoxGroup(node: KPointer, contentModifier: ContentModifier<CheckBoxGroupConfiguration>, builder: ((parentNode: KPointer,config: CheckBoxGroupConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<CheckBoxGroupConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: CheckBoxGroupConfiguration) => KPointer))
        ContentModifierHelper.contentModifierCheckBoxGroup_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }
    public static resetContentModifierCheckBoxGroup(node: KPointer): void {
        const node_casted = node as (KPointer)
        ContentModifierHelper.resetContentModifierCheckBoxGroup_serialize(node_casted)
        return
    }
    private static contentModifierButton_serialize(node: KPointer, contentModifier: ContentModifier<ButtonConfiguration>, builder: ((parentNode: KPointer,config: ButtonConfiguration) => KPointer)): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierButton(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierButton_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierButton(node)
    }
    private static contentModifierCheckBox_serialize(node: KPointer, contentModifier: ContentModifier<CheckBoxConfiguration>, builder: ((parentNode: KPointer,config: CheckBoxConfiguration) => KPointer)): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierCheckBox(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierCheckBox_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierCheckBox(node)
    }
    private static contentModifierDataPanel_serialize(node: KPointer, contentModifier: ContentModifier<DataPanelConfiguration>, builder: ((parentNode: KPointer,config: DataPanelConfiguration) => KPointer)): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierDataPanel(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierDataPanel_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierDataPanel(node)
    }
    private static contentModifierGauge_serialize(node: KPointer, contentModifier: ContentModifier<GaugeConfiguration>, builder: ((parentNode: KPointer,config: GaugeConfiguration) => KPointer)): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierGauge(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierGauge_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierGauge(node)
    }
    private static contentModifierLoadingProgress_serialize(node: KPointer, contentModifier: ContentModifier<LoadingProgressConfiguration>, builder: ((parentNode: KPointer,config: LoadingProgressConfiguration) => KPointer)): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierLoadingProgress(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierLoadingProgress_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierLoadingProgress(node)
    }
    private static contentModifierProgress_serialize(node: KPointer, contentModifier: ContentModifier<ProgressConfiguration>, builder: ((parentNode: KPointer,config: ProgressConfiguration) => KPointer)): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierProgress(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierProgress_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierProgress(node)
    }
    private static contentModifierRadio_serialize(node: KPointer, contentModifier: ContentModifier<RadioConfiguration>, builder: ((parentNode: KPointer,config: RadioConfiguration) => KPointer)): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierRadio(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierRadio_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierRadio(node)
    }
    private static contentModifierRating_serialize(node: KPointer, contentModifier: ContentModifier<RatingConfiguration>, builder: ((parentNode: KPointer,config: RatingConfiguration) => KPointer)): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierRating(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierRating_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierRating(node)
    }
    private static contentModifierMenuItem_serialize(node: KPointer, contentModifier: ContentModifier<MenuItemConfiguration>, builder: ((parentNode: KPointer,config: MenuItemConfiguration) => KPointer)): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierMenuItem(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierMenuItem_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierMenuItem(node)
    }
    private static contentModifierSlider_serialize(node: KPointer, contentModifier: ContentModifier<SliderConfiguration>, builder: ((parentNode: KPointer,config: SliderConfiguration) => KPointer)): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierSlider(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierSlider_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierSlider(node)
    }
    private static contentModifierTextClock_serialize(node: KPointer, contentModifier: ContentModifier<TextClockConfiguration>, builder: ((parentNode: KPointer,config: TextClockConfiguration) => KPointer)): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierTextClock(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierTextClock_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierTextClock(node)
    }
    private static contentModifierTextTimer_serialize(node: KPointer, contentModifier: ContentModifier<TextTimerConfiguration>, builder: ((parentNode: KPointer,config: TextTimerConfiguration) => KPointer)): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierTextTimer(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierTextTimer_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierTextTimer(node)
    }
    private static contentModifierToggle_serialize(node: KPointer, contentModifier: ContentModifier<ToggleConfiguration>, builder: ((parentNode: KPointer,config: ToggleConfiguration) => KPointer)): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierToggle(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierToggle_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierToggle(node)
    }
    private static contentModifierCheckBoxGroup_serialize(node: KPointer, contentModifier: ContentModifier<CheckBoxGroupConfiguration>, builder: ((parentNode: KPointer,config: CheckBoxGroupConfiguration) => KPointer)): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierCheckBoxGroup(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierCheckBoxGroup_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierCheckBoxGroup(node)
    }
}
export class ContextMenu {
    public static close(): void {
        ContextMenu.close_serialize()
        return
    }
    private static close_serialize(): void {
        ArkUIGeneratedNativeModule._ContextMenu_close()
    }
}
export class CustomDialogControllerExtenderInternal {
    public static fromPtr(ptr: KPointer): CustomDialogControllerExtender {
        return new CustomDialogControllerExtender(MaterializedBaseTag.NOP, ptr)
    }
}
export class CustomDialogControllerExtender implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, CustomDialogControllerExtender.getFinalizer())
    }
    constructor(value: CustomDialogControllerOptionsExtender) {
        this(MaterializedBaseTag.NOP, CustomDialogControllerExtender.construct(value))
    }
    static construct(value: CustomDialogControllerOptionsExtender): KPointer {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        CustomDialogControllerOptionsExtender_serializer.write(thisSerializer, value)
        const retval = ArkUIGeneratedNativeModule._CustomDialogControllerExtender_construct(thisSerializer.asBuffer(), thisSerializer.length())
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
    public getState(): promptAction.CommonState {
        return this.getState_serialize()
    }
    private open_serialize(): void {
        ArkUIGeneratedNativeModule._CustomDialogControllerExtender_open(this.peer!.ptr)
    }
    private close_serialize(): void {
        ArkUIGeneratedNativeModule._CustomDialogControllerExtender_close(this.peer!.ptr)
    }
    private setOwnerView_serialize(content: KPointer): void {
        ArkUIGeneratedNativeModule._CustomDialogControllerExtender_setOwnerView(this.peer!.ptr, content)
    }
    private getExternalOptions_serialize(): CustomDialogControllerExternalOptionsExtender {
        const retval = ArkUIGeneratedNativeModule._CustomDialogControllerExtender_getExternalOptions(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: CustomDialogControllerExternalOptionsExtender = CustomDialogControllerExternalOptionsExtender_serializer.read(retvalDeserializer)
        return returnResult
    }
    private getState_serialize(): promptAction.CommonState {
        const retval = ArkUIGeneratedNativeModule._CustomDialogControllerExtender_getState(this.peer!.ptr)
        return promptAction.CommonState.fromValue(retval)
    }
}
export class DataPanelExtender {
    public static setTrackShadow(node: KPointer, options?: DataPanelShadowOptions): void {
        const node_casted = node as (KPointer)
        const options_casted = options as (DataPanelShadowOptions | undefined)
        DataPanelExtender.setTrackShadow_serialize(node_casted, options_casted)
        return
    }
    public static nullTrackShadow(node: KPointer): void {
        const node_casted = node as (KPointer)
        DataPanelExtender.nullTrackShadow_serialize(node_casted)
        return
    }
    private static setTrackShadow_serialize(node: KPointer, options?: DataPanelShadowOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue = options!
            DataPanelShadowOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._DataPanelExtender_setTrackShadow(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static nullTrackShadow_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._DataPanelExtender_nullTrackShadow(node)
    }
}
export class DialogExtender {
    public static showTimePickerDialog(options: TimePickerDialogOptions): void {
        const options_casted = options as (TimePickerDialogOptions)
        DialogExtender.showTimePickerDialog_serialize(options_casted)
        return
    }
    public static showTextPickerDialog(options: TextPickerDialogOptions | TextPickerDialogOptionsExt): void {
        const options_casted = options as (TextPickerDialogOptions | TextPickerDialogOptionsExt)
        DialogExtender.showTextPickerDialog_serialize(options_casted)
        return
    }
    public static showDatePickerDialog(options: DatePickerDialogOptions): void {
        const options_casted = options as (DatePickerDialogOptions)
        DialogExtender.showDatePickerDialog_serialize(options_casted)
        return
    }
    private static showTimePickerDialog_serialize(options: TimePickerDialogOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        TimePickerDialogOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._DialogExtender_showTimePickerDialog(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static showTextPickerDialog_serialize(options: TextPickerDialogOptions | TextPickerDialogOptionsExt): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (options instanceof TextPickerDialogOptions) {
            thisSerializer.writeInt8((0).toByte())
            const optionsForIdx0 = options as TextPickerDialogOptions
            TextPickerDialogOptions_serializer.write(thisSerializer, optionsForIdx0)
        } else if (options instanceof TextPickerDialogOptionsExt) {
            thisSerializer.writeInt8((1).toByte())
            const optionsForIdx1 = options as TextPickerDialogOptionsExt
            TextPickerDialogOptionsExt_serializer.write(thisSerializer, optionsForIdx1)
        }
        ArkUIGeneratedNativeModule._DialogExtender_showTextPickerDialog(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static showDatePickerDialog_serialize(options: DatePickerDialogOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        DatePickerDialogOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._DialogExtender_showDatePickerDialog(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class DragUtils {
    public static GetForegroundColorValue(resourceColor: ResourceColor): int64 {
        const resourceColor_casted = resourceColor as (ResourceColor)
        return DragUtils.GetForegroundColorValue_serialize(resourceColor_casted)
    }
    private static GetForegroundColorValue_serialize(resourceColor: ResourceColor): int64 {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (resourceColor instanceof arkui_component_enums_Color) {
            thisSerializer.writeInt8((0).toByte())
            const resourceColorForIdx0 = resourceColor as arkui_component_enums_Color
            thisSerializer.writeInt32((resourceColorForIdx0.getOrdinal()) % (12))
        } else if (resourceColor instanceof int32) {
            thisSerializer.writeInt8((1).toByte())
            const resourceColorForIdx1 = resourceColor as int32
            thisSerializer.writeInt32(resourceColorForIdx1)
        } else if (resourceColor instanceof string) {
            thisSerializer.writeInt8((2).toByte())
            const resourceColorForIdx2 = resourceColor as string
            thisSerializer.writeString(resourceColorForIdx2)
        } else if (resourceColor instanceof arkui_component_units_Resource) {
            thisSerializer.writeInt8((3).toByte())
            const resourceColorForIdx3 = resourceColor as arkui_component_units_Resource
            global_resource_Resource_serializer.write(thisSerializer, resourceColorForIdx3)
        }
        const retval = ArkUIGeneratedNativeModule._DragUtils_GetForegroundColorValue(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
export class EventEmulator {
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
    private static emitClickEvent_serialize(node: KPointer, event: ClickEvent): void {
        ArkUIGeneratedNativeModule._EventEmulator_emitClickEvent(node, toPeerPtr(event))
    }
    private static emitTextInputEvent_serialize(node: KPointer, text: string): void {
        ArkUIGeneratedNativeModule._EventEmulator_emitTextInputEvent(node, text)
    }
}
export class FocusController {
    public static requestFocus(key: string): void {
        const key_casted = key as (string)
        FocusController.requestFocus_serialize(key_casted)
        return
    }
    private static requestFocus_serialize(key: string): void {
        ArkUIGeneratedNativeModule._FocusController_requestFocus(key)
    }
}
export class ForEachOps {
    public static SyncOnMoveOps(node: KPointer, additionalChild: Array<KPointer>, onMoveOps: OnMoveHandler | undefined, onMoveDragEventOps: ItemDragEventHandler | undefined): void {
        const node_casted = node as (KPointer)
        const additionalChild_casted = additionalChild as (Array<KPointer>)
        const onMoveOps_casted = onMoveOps as (OnMoveHandler | undefined)
        const onMoveDragEventOps_casted = onMoveDragEventOps as (ItemDragEventHandler | undefined)
        ForEachOps.SyncOnMoveOps_serialize(node_casted, additionalChild_casted, onMoveOps_casted, onMoveDragEventOps_casted)
        return
    }
    private static SyncOnMoveOps_serialize(node: KPointer, additionalChild: Array<KPointer>, onMoveOps: OnMoveHandler | undefined, onMoveDragEventOps: ItemDragEventHandler | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((additionalChild.length).toInt())
        for (let additionalChildCounterI = 0; additionalChildCounterI < additionalChild.length; additionalChildCounterI++) {
            const additionalChildTmpElement: KPointer = additionalChild[additionalChildCounterI]
            thisSerializer.writePointer(additionalChildTmpElement)
        }
        if (onMoveOps !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const onMoveOpsTmpValue = onMoveOps!
            thisSerializer.holdAndWriteCallback(onMoveOpsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (onMoveDragEventOps !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const onMoveDragEventOpsTmpValue = onMoveDragEventOps!
            ItemDragEventHandler_serializer.write(thisSerializer, onMoveDragEventOpsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ForEachOps_SyncOnMoveOps(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class FrameNodeExtender {
    public static constructorFrameNode(supportMultiThread: boolean): KPointer {
        const supportMultiThread_casted = supportMultiThread as (boolean)
        return FrameNodeExtender.constructorFrameNode_serialize(supportMultiThread_casted)
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
    public static getChild(peer: FrameNode, index: int32, expandMode: number): KPointer {
        const peer_casted = peer as (FrameNode)
        const index_casted = index as (int32)
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
    public static getUniqueId(peer: FrameNode): int32 {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getUniqueId_serialize(peer_casted)
    }
    public static getNodeType(peer: FrameNode): string {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getNodeType_serialize(peer_casted)
    }
    public static getOpacity(peer: FrameNode): double {
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
    public static addSupportedUIStates(peer: FrameNode, uiStates: int32, statesChangeHandler: UIStatesChangeHandler, excludeInner: boolean): void {
        const peer_casted = peer as (FrameNode)
        const uiStates_casted = uiStates as (int32)
        const statesChangeHandler_casted = statesChangeHandler as (UIStatesChangeHandler)
        const excludeInner_casted = excludeInner as (boolean)
        FrameNodeExtender.addSupportedUIStates_serialize(peer_casted, uiStates_casted, statesChangeHandler_casted, excludeInner_casted)
        return
    }
    public static removeSupportedUIStates(peer: FrameNode, uiStates: int32): void {
        const peer_casted = peer as (FrameNode)
        const uiStates_casted = uiStates as (int32)
        FrameNodeExtender.removeSupportedUIStates_serialize(peer_casted, uiStates_casted)
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
    public static getGlobalPositionOnDisplay(peer: FrameNode): Vector2 {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getGlobalPositionOnDisplay_serialize(peer_casted)
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
    public static moveTo(peer: FrameNode, targetParent: FrameNode, index: int32): int32 {
        const peer_casted = peer as (FrameNode)
        const targetParent_casted = targetParent as (FrameNode)
        const index_casted = index as (int32)
        return FrameNodeExtender.moveTo_serialize(peer_casted, targetParent_casted, index_casted)
    }
    public static getFirstChildIndexWithoutExpand(peer: FrameNode): int32 {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getFirstChildIndexWithoutExpand_serialize(peer_casted)
    }
    public static getLastChildIndexWithoutExpand(peer: FrameNode): int32 {
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
    public static getFrameNodeByUniqueId(id: int32): KPointer {
        const id_casted = id as (int32)
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
    public static createTypedFrameNode(type: string, supportMultiThread: boolean): KPointer {
        const type_casted = type as (string)
        const supportMultiThread_casted = supportMultiThread as (boolean)
        return FrameNodeExtender.createTypedFrameNode_serialize(type_casted, supportMultiThread_casted)
    }
    public static createByRawPtr(ptr: KPointer): KPointer {
        const ptr_casted = ptr as (KPointer)
        return FrameNodeExtender.createByRawPtr_serialize(ptr_casted)
    }
    public static unWrapRawPtr(ptr: KPointer): KPointer {
        const ptr_casted = ptr as (KPointer)
        return FrameNodeExtender.unWrapRawPtr_serialize(ptr_casted)
    }
    public static getCommonEvent(peer: FrameNode): UICommonEvent {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.getCommonEvent_serialize(peer_casted)
    }
    public static convertPoint(peer: FrameNode, node: FrameNode, vector2: NodePosition): Array<double> {
        const peer_casted = peer as (FrameNode)
        const node_casted = node as (FrameNode)
        const vector2_casted = vector2 as (NodePosition)
        return FrameNodeExtender.convertPoint_serialize(peer_casted, node_casted, vector2_casted)
    }
    public static getRenderNode(peer: KPointer): KPointer {
        const peer_casted = peer as (KPointer)
        return FrameNodeExtender.getRenderNode_serialize(peer_casted)
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
    public static getInteractionEventBindingInfo(peer: FrameNode, eventType: EventQueryType): InteractionEventBindingInfo {
        const peer_casted = peer as (FrameNode)
        const eventType_casted = eventType as (EventQueryType)
        return FrameNodeExtender.getInteractionEventBindingInfo_serialize(peer_casted, eventType_casted)
    }
    public static isOnRenderTree(peer: FrameNode): boolean {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.isOnRenderTree_serialize(peer_casted)
    }
    public static isOnMainTree(peer: FrameNode): boolean {
        const peer_casted = peer as (FrameNode)
        return FrameNodeExtender.isOnMainTree_serialize(peer_casted)
    }
    public static convertPositionToWindow(peer: FrameNode, positionByLocal: NodePosition): Array<double> {
        const peer_casted = peer as (FrameNode)
        const positionByLocal_casted = positionByLocal as (NodePosition)
        return FrameNodeExtender.convertPositionToWindow_serialize(peer_casted, positionByLocal_casted)
    }
    public static convertPositionFromWindow(peer: FrameNode, positionByWindow: NodePosition): Array<double> {
        const peer_casted = peer as (FrameNode)
        const positionByWindow_casted = positionByWindow as (NodePosition)
        return FrameNodeExtender.convertPositionFromWindow_serialize(peer_casted, positionByWindow_casted)
    }
    public static applyAttributesFinish(peer: FrameNode): void {
        const peer_casted = peer as (FrameNode)
        FrameNodeExtender.applyAttributesFinish_serialize(peer_casted)
        return
    }
    private static constructorFrameNode_serialize(supportMultiThread: boolean): KPointer {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_constructorFrameNode(supportMultiThread ? true : false)
        return retval
    }
    private static getDestroy_serialize(): KPointer {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getDestroy()
        return retval
    }
    private static destroyPeer_serialize(peer: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNodeExtender_destroyPeer(extractors.toFrameNodePtr(peer))
    }
    private static isModifiable_serialize(peer: KPointer): boolean {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_isModifiable(peer)
        return retval
    }
    private static appendChild_serialize(peer: FrameNode, child: FrameNode): int32 {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_appendChild(extractors.toFrameNodePtr(peer), extractors.toFrameNodePtr(child))
        return retval
    }
    private static insertChildAfter_serialize(peer: KPointer, child: KPointer, sibling: KPointer): int32 {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_insertChildAfter(peer, child, sibling)
        return retval
    }
    private static removeChild_serialize(peer: FrameNode, child: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNodeExtender_removeChild(extractors.toFrameNodePtr(peer), extractors.toFrameNodePtr(child))
    }
    private static clearChildren_serialize(peer: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNodeExtender_clearChildren(extractors.toFrameNodePtr(peer))
    }
    private static getChild_serialize(peer: FrameNode, index: int32, expandMode: number): KPointer {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getChild(extractors.toFrameNodePtr(peer), index, expandMode)
        return retval
    }
    private static getFirstChild_serialize(peer: FrameNode): KPointer {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getFirstChild(extractors.toFrameNodePtr(peer))
        return retval
    }
    private static getNextSibling_serialize(peer: FrameNode): KPointer {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getNextSibling(extractors.toFrameNodePtr(peer))
        return retval
    }
    private static getPreviousSibling_serialize(peer: FrameNode): KPointer {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getPreviousSibling(extractors.toFrameNodePtr(peer))
        return retval
    }
    private static getParent_serialize(peer: FrameNode): KPointer {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getParent(extractors.toFrameNodePtr(peer))
        return retval
    }
    private static getChildrenCount_serialize(peer: FrameNode): int32 {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getChildrenCount(extractors.toFrameNodePtr(peer))
        return retval
    }
    private static dispose_serialize(peer: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNodeExtender_dispose(extractors.toFrameNodePtr(peer))
    }
    private static getPositionToWindow_serialize(peer: FrameNode): Vector2 {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getPositionToWindow(extractors.toFrameNodePtr(peer))
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: Vector2 = Vector2_serializer.read(retvalDeserializer)
        return returnResult
    }
    private static getPositionToParent_serialize(peer: FrameNode): Vector2 {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getPositionToParent(extractors.toFrameNodePtr(peer))
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: Vector2 = Vector2_serializer.read(retvalDeserializer)
        return returnResult
    }
    private static getMeasuredSize_serialize(peer: FrameNode): Size {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getMeasuredSize(extractors.toFrameNodePtr(peer))
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: Size = Size_serializer.read(retvalDeserializer)
        return returnResult
    }
    private static getLayoutPosition_serialize(peer: FrameNode): Vector2 {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getLayoutPosition(extractors.toFrameNodePtr(peer))
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: Vector2 = Vector2_serializer.read(retvalDeserializer)
        return returnResult
    }
    private static getId_serialize(peer: FrameNode): string {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getId(extractors.toFrameNodePtr(peer))
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private static getUniqueId_serialize(peer: FrameNode): int32 {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getUniqueId(extractors.toFrameNodePtr(peer))
        return retval
    }
    private static getNodeType_serialize(peer: FrameNode): string {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getNodeType(extractors.toFrameNodePtr(peer))
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private static getOpacity_serialize(peer: FrameNode): double {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getOpacity(extractors.toFrameNodePtr(peer))
        return retval
    }
    private static isVisible_serialize(peer: FrameNode): boolean {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_isVisible(extractors.toFrameNodePtr(peer))
        return retval
    }
    private static isClipToFrame_serialize(peer: FrameNode): boolean {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_isClipToFrame(extractors.toFrameNodePtr(peer))
        return retval
    }
    private static isAttached_serialize(peer: FrameNode): boolean {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_isAttached(extractors.toFrameNodePtr(peer))
        return retval
    }
    private static getInspectorInfo_serialize(peer: FrameNode): string {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getInspectorInfo(extractors.toFrameNodePtr(peer))
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private static invalidate_serialize(peer: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNodeExtender_invalidate(extractors.toFrameNodePtr(peer))
    }
    private static disposeTree_serialize(peer: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNodeExtender_disposeTree(extractors.toFrameNodePtr(peer))
    }
    private static addSupportedUIStates_serialize(peer: FrameNode, uiStates: int32, statesChangeHandler: UIStatesChangeHandler, excludeInner: boolean): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(statesChangeHandler)
        ArkUIGeneratedNativeModule._FrameNodeExtender_addSupportedUIStates(extractors.toFrameNodePtr(peer), uiStates, thisSerializer.asBuffer(), thisSerializer.length(), excludeInner ? true : false)
        thisSerializer.release()
    }
    private static removeSupportedUIStates_serialize(peer: FrameNode, uiStates: int32): void {
        ArkUIGeneratedNativeModule._FrameNodeExtender_removeSupportedUIStates(extractors.toFrameNodePtr(peer), uiStates)
    }
    private static setCrossLanguageOptions_serialize(peer: FrameNode, options: boolean): boolean {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_setCrossLanguageOptions(extractors.toFrameNodePtr(peer), options ? true : false)
        return retval
    }
    private static getCrossLanguageOptions_serialize(peer: FrameNode): boolean {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getCrossLanguageOptions(extractors.toFrameNodePtr(peer))
        return retval
    }
    private static setMeasuredSize_serialize(peer: FrameNode, size: Size): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        Size_serializer.write(thisSerializer, size)
        ArkUIGeneratedNativeModule._FrameNodeExtender_setMeasuredSize(extractors.toFrameNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setLayoutPosition_serialize(peer: FrameNode, position: Vector2): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        Vector2_serializer.write(thisSerializer, position)
        ArkUIGeneratedNativeModule._FrameNodeExtender_setLayoutPosition(extractors.toFrameNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static measure_serialize(peer: FrameNode, constraint: LayoutConstraint): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        LayoutConstraint_serializer.write(thisSerializer, constraint)
        ArkUIGeneratedNativeModule._FrameNodeExtender_measure(extractors.toFrameNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static layout_serialize(peer: FrameNode, position: Vector2): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        Vector2_serializer.write(thisSerializer, position)
        ArkUIGeneratedNativeModule._FrameNodeExtender_layout(extractors.toFrameNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setNeedsLayout_serialize(peer: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNodeExtender_setNeedsLayout(extractors.toFrameNodePtr(peer))
    }
    private static getPositionToScreen_serialize(peer: FrameNode): Vector2 {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getPositionToScreen(extractors.toFrameNodePtr(peer))
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: Vector2 = Vector2_serializer.read(retvalDeserializer)
        return returnResult
    }
    private static getGlobalPositionOnDisplay_serialize(peer: FrameNode): Vector2 {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getGlobalPositionOnDisplay(extractors.toFrameNodePtr(peer))
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: Vector2 = Vector2_serializer.read(retvalDeserializer)
        return returnResult
    }
    private static getPositionToWindowWithTransform_serialize(peer: FrameNode): Vector2 {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getPositionToWindowWithTransform(extractors.toFrameNodePtr(peer))
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: Vector2 = Vector2_serializer.read(retvalDeserializer)
        return returnResult
    }
    private static getPositionToParentWithTransform_serialize(peer: FrameNode): Vector2 {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getPositionToParentWithTransform(extractors.toFrameNodePtr(peer))
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: Vector2 = Vector2_serializer.read(retvalDeserializer)
        return returnResult
    }
    private static getPositionToScreenWithTransform_serialize(peer: FrameNode): Vector2 {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getPositionToScreenWithTransform(extractors.toFrameNodePtr(peer))
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: Vector2 = Vector2_serializer.read(retvalDeserializer)
        return returnResult
    }
    private static getUserConfigBorderWidth_serialize(peer: FrameNode): NodeEdgesLengthMetrics {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getUserConfigBorderWidth(extractors.toFrameNodePtr(peer))
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: NodeEdgesLengthMetrics = NodeEdgesLengthMetrics_serializer.read(retvalDeserializer)
        return returnResult
    }
    private static getUserConfigPadding_serialize(peer: FrameNode): NodeEdgesLengthMetrics {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getUserConfigPadding(extractors.toFrameNodePtr(peer))
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: NodeEdgesLengthMetrics = NodeEdgesLengthMetrics_serializer.read(retvalDeserializer)
        return returnResult
    }
    private static getUserConfigMargin_serialize(peer: FrameNode): NodeEdgesLengthMetrics {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getUserConfigMargin(extractors.toFrameNodePtr(peer))
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: NodeEdgesLengthMetrics = NodeEdgesLengthMetrics_serializer.read(retvalDeserializer)
        return returnResult
    }
    private static getUserConfigSize_serialize(peer: FrameNode): SizeTLengthMetrics {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getUserConfigSize(extractors.toFrameNodePtr(peer))
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: SizeTLengthMetrics = SizeTLengthMetrics_serializer.read(retvalDeserializer)
        return returnResult
    }
    private static getFrameNodeByKey_serialize(name: string): KPointer {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getFrameNodeByKey(name)
        return retval
    }
    private static getIdByFrameNode_serialize(node: KPointer): number {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getIdByFrameNode(node)
        return retval
    }
    private static moveTo_serialize(peer: FrameNode, targetParent: FrameNode, index: int32): int32 {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_moveTo(extractors.toFrameNodePtr(peer), extractors.toFrameNodePtr(targetParent), index)
        return retval
    }
    private static getFirstChildIndexWithoutExpand_serialize(peer: FrameNode): int32 {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getFirstChildIndexWithoutExpand(extractors.toFrameNodePtr(peer))
        return retval
    }
    private static getLastChildIndexWithoutExpand_serialize(peer: FrameNode): int32 {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getLastChildIndexWithoutExpand(extractors.toFrameNodePtr(peer))
        return retval
    }
    private static getAttachedFrameNodeById_serialize(id: string): KPointer {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getAttachedFrameNodeById(id)
        return retval
    }
    private static getFrameNodeById_serialize(id: number): KPointer {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getFrameNodeById(id)
        return retval
    }
    private static getFrameNodeByUniqueId_serialize(id: int32): KPointer {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getFrameNodeByUniqueId(id)
        return retval
    }
    private static reuse_serialize(peer: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNodeExtender_reuse(extractors.toFrameNodePtr(peer))
    }
    private static recycle_serialize(peer: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNodeExtender_recycle(extractors.toFrameNodePtr(peer))
    }
    private static createAnimation_serialize(peer: FrameNode, property: AnimationPropertyType, startValue: Array<double> | undefined, endValue: Array<double>, param: AnimateParam): boolean {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (startValue !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const startValueTmpValue = startValue!
            thisSerializer.writeInt32((startValueTmpValue.length).toInt())
            for (let startValueTmpValueCounterI = 0; startValueTmpValueCounterI < startValueTmpValue.length; startValueTmpValueCounterI++) {
                const startValueTmpValueTmpElement: double = startValueTmpValue[startValueTmpValueCounterI]
                thisSerializer.writeFloat64(startValueTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        thisSerializer.writeInt32((endValue.length).toInt())
        for (let endValueCounterI = 0; endValueCounterI < endValue.length; endValueCounterI++) {
            const endValueTmpElement: double = endValue[endValueCounterI]
            thisSerializer.writeFloat64(endValueTmpElement)
        }
        AnimateParam_serializer.write(thisSerializer, param)
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_createAnimation(extractors.toFrameNodePtr(peer), property.valueOf(), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static cancelAnimations_serialize(peer: FrameNode, properties: Array<AnimationPropertyType>): boolean {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((properties.length).toInt())
        for (let propertiesCounterI = 0; propertiesCounterI < properties.length; propertiesCounterI++) {
            const propertiesTmpElement: AnimationPropertyType = properties[propertiesCounterI]
            thisSerializer.writeInt32(propertiesTmpElement.valueOf())
        }
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_cancelAnimations(extractors.toFrameNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static getNodePropertyValue_serialize(peer: FrameNode, property: AnimationPropertyType): Array<double> {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getNodePropertyValue(extractors.toFrameNodePtr(peer), property.valueOf())
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength: int32 = retvalDeserializer.readInt32()
        let buffer: Array<double> = new Array<double>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = retvalDeserializer.readFloat64()
        }
        const returnResult: Array<double> = buffer
        return returnResult
    }
    private static getFrameNodePtr_serialize(node: FrameNode): KPointer {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getFrameNodePtr(extractors.toFrameNodePtr(node))
        return retval
    }
    private static createTypedFrameNode_serialize(type: string, supportMultiThread: boolean): KPointer {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_createTypedFrameNode(type, supportMultiThread ? true : false)
        return retval
    }
    private static createByRawPtr_serialize(ptr: KPointer): KPointer {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_createByRawPtr(ptr)
        return retval
    }
    private static unWrapRawPtr_serialize(ptr: KPointer): KPointer {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_unWrapRawPtr(ptr)
        return retval
    }
    private static getCommonEvent_serialize(peer: FrameNode): UICommonEvent {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getCommonEvent(extractors.toFrameNodePtr(peer))
        const obj: UICommonEvent = UICommonEventInternal.fromPtr(retval)
        return obj
    }
    private static convertPoint_serialize(peer: FrameNode, node: FrameNode, vector2: NodePosition): Array<double> {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        Vector2_serializer.write(thisSerializer, vector2)
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_convertPoint(extractors.toFrameNodePtr(peer), extractors.toFrameNodePtr(node), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength: int32 = retvalDeserializer.readInt32()
        let buffer: Array<double> = new Array<double>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = retvalDeserializer.readFloat64()
        }
        const returnResult: Array<double> = buffer
        return returnResult
    }
    private static getRenderNode_serialize(peer: KPointer): KPointer {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getRenderNode(peer)
        return retval
    }
    private static adoptChild_serialize(peer: FrameNode, child: FrameNode): int32 {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_adoptChild(extractors.toFrameNodePtr(peer), extractors.toFrameNodePtr(child))
        return retval
    }
    private static removeAdoptedChild_serialize(peer: FrameNode, child: FrameNode): int32 {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_removeAdoptedChild(extractors.toFrameNodePtr(peer), extractors.toFrameNodePtr(child))
        return retval
    }
    private static getInteractionEventBindingInfo_serialize(peer: FrameNode, eventType: EventQueryType): InteractionEventBindingInfo {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_getInteractionEventBindingInfo(extractors.toFrameNodePtr(peer), eventType.valueOf())
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: InteractionEventBindingInfo = InteractionEventBindingInfo_serializer.read(retvalDeserializer)
        return returnResult
    }
    private static isOnRenderTree_serialize(peer: FrameNode): boolean {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_isOnRenderTree(extractors.toFrameNodePtr(peer))
        return retval
    }
    private static isOnMainTree_serialize(peer: FrameNode): boolean {
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_isOnMainTree(extractors.toFrameNodePtr(peer))
        return retval
    }
    private static convertPositionToWindow_serialize(peer: FrameNode, positionByLocal: NodePosition): Array<double> {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        Vector2_serializer.write(thisSerializer, positionByLocal)
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_convertPositionToWindow(extractors.toFrameNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength: int32 = retvalDeserializer.readInt32()
        let buffer: Array<double> = new Array<double>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = retvalDeserializer.readFloat64()
        }
        const returnResult: Array<double> = buffer
        return returnResult
    }
    private static convertPositionFromWindow_serialize(peer: FrameNode, positionByWindow: NodePosition): Array<double> {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        Vector2_serializer.write(thisSerializer, positionByWindow)
        const retval = ArkUIGeneratedNativeModule._FrameNodeExtender_convertPositionFromWindow(extractors.toFrameNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength: int32 = retvalDeserializer.readInt32()
        let buffer: Array<double> = new Array<double>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = retvalDeserializer.readFloat64()
        }
        const returnResult: Array<double> = buffer
        return returnResult
    }
    private static applyAttributesFinish_serialize(peer: FrameNode): void {
        ArkUIGeneratedNativeModule._FrameNodeExtender_applyAttributesFinish(extractors.toFrameNodePtr(peer))
    }
}
export class GaugeExtender {
    public static setIndicator(node: KPointer, options?: GaugeIndicatorOptions): void {
        const node_casted = node as (KPointer)
        const options_casted = options as (GaugeIndicatorOptions | undefined)
        GaugeExtender.setIndicator_serialize(node_casted, options_casted)
        return
    }
    public static nullIndicator(node: KPointer): void {
        const node_casted = node as (KPointer)
        GaugeExtender.nullIndicator_serialize(node_casted)
        return
    }
    public static setTrackShadow(node: KPointer, options?: GaugeShadowOptions): void {
        const node_casted = node as (KPointer)
        const options_casted = options as (GaugeShadowOptions | undefined)
        GaugeExtender.setTrackShadow_serialize(node_casted, options_casted)
        return
    }
    public static nullTrackShadow(node: KPointer): void {
        const node_casted = node as (KPointer)
        GaugeExtender.nullTrackShadow_serialize(node_casted)
        return
    }
    public static setDescription(node: KPointer, builder?: CustomBuilder): void {
        const node_casted = node as (KPointer)
        const builder_casted = builder as (CustomBuilder | undefined)
        GaugeExtender.setDescription_serialize(node_casted, builder_casted)
        return
    }
    public static nullDescription(node: KPointer): void {
        const node_casted = node as (KPointer)
        GaugeExtender.nullDescription_serialize(node_casted)
        return
    }
    private static setIndicator_serialize(node: KPointer, options?: GaugeIndicatorOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue = options!
            GaugeIndicatorOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GaugeExtender_setIndicator(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static nullIndicator_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._GaugeExtender_nullIndicator(node)
    }
    private static setTrackShadow_serialize(node: KPointer, options?: GaugeShadowOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue = options!
            GaugeShadowOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GaugeExtender_setTrackShadow(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static nullTrackShadow_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._GaugeExtender_nullTrackShadow(node)
    }
    private static setDescription_serialize(node: KPointer, builder?: CustomBuilder): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (builder !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const builderTmpValue = builder!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(builderTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GaugeExtender_setDescription(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static nullDescription_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._GaugeExtender_nullDescription(node)
    }
}
export class GestureOps {
    public static createTapGesture(fingers: number, count: number, distanceThreshold: double, isFingerCountLimited: boolean): KPointer {
        const fingers_casted = fingers as (number)
        const count_casted = count as (number)
        const distanceThreshold_casted = distanceThreshold as (double)
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
    public static setOnAction(gesture: KPointer, onAction: GestureEventHandler): void {
        const gesture_casted = gesture as (KPointer)
        const onAction_casted = onAction as (GestureEventHandler)
        GestureOps.setOnAction_serialize(gesture_casted, onAction_casted)
        return
    }
    public static setOnActionStart(gesture: KPointer, onActionStart: GestureEventHandler): void {
        const gesture_casted = gesture as (KPointer)
        const onActionStart_casted = onActionStart as (GestureEventHandler)
        GestureOps.setOnActionStart_serialize(gesture_casted, onActionStart_casted)
        return
    }
    public static setOnActionUpdate(gesture: KPointer, onActionUpdate: GestureEventHandler): void {
        const gesture_casted = gesture as (KPointer)
        const onActionUpdate_casted = onActionUpdate as (GestureEventHandler)
        GestureOps.setOnActionUpdate_serialize(gesture_casted, onActionUpdate_casted)
        return
    }
    public static setOnActionEnd(gesture: KPointer, onActionEnd: GestureEventHandler): void {
        const gesture_casted = gesture as (KPointer)
        const onActionEnd_casted = onActionEnd as (GestureEventHandler)
        GestureOps.setOnActionEnd_serialize(gesture_casted, onActionEnd_casted)
        return
    }
    public static setOnActionCancel(gesture: KPointer, onActionCancel: GestureEventHandler): void {
        const gesture_casted = gesture as (KPointer)
        const onActionCancel_casted = onActionCancel as (GestureEventHandler)
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
    private static createTapGesture_serialize(fingers: number, count: number, distanceThreshold: double, isFingerCountLimited: boolean): KPointer {
        const retval = ArkUIGeneratedNativeModule._GestureOps_createTapGesture(fingers, count, distanceThreshold, isFingerCountLimited ? true : false)
        return retval
    }
    private static createLongPressGesture_serialize(fingers: number, repeat: boolean, duration: number, isFingerCountLimited: boolean): KPointer {
        const retval = ArkUIGeneratedNativeModule._GestureOps_createLongPressGesture(fingers, repeat ? true : false, duration, isFingerCountLimited ? true : false)
        return retval
    }
    private static createPanGesture_serialize(fingers: number, direction: PanDirection, distance: number, isFingerCountLimited: boolean): KPointer {
        const retval = ArkUIGeneratedNativeModule._GestureOps_createPanGesture(fingers, direction.valueOf(), distance, isFingerCountLimited ? true : false)
        return retval
    }
    private static createPanGestureWithPanGestureOptions_serialize(panGestureOptions: KPointer): KPointer {
        const retval = ArkUIGeneratedNativeModule._GestureOps_createPanGestureWithPanGestureOptions(panGestureOptions)
        return retval
    }
    private static createPinchGesture_serialize(fingers: number, distance: number, isFingerCountLimited: boolean): KPointer {
        const retval = ArkUIGeneratedNativeModule._GestureOps_createPinchGesture(fingers, distance, isFingerCountLimited ? true : false)
        return retval
    }
    private static createRotationGesture_serialize(fingers: number, angle: number, isFingerCountLimited: boolean): KPointer {
        const retval = ArkUIGeneratedNativeModule._GestureOps_createRotationGesture(fingers, angle, isFingerCountLimited ? true : false)
        return retval
    }
    private static createSwipeGesture_serialize(fingers: number, direction: SwipeDirection, speed: number, isFingerCountLimited: boolean): KPointer {
        const retval = ArkUIGeneratedNativeModule._GestureOps_createSwipeGesture(fingers, direction.valueOf(), speed, isFingerCountLimited ? true : false)
        return retval
    }
    private static createGestureGroup_serialize(mode: GestureMode): KPointer {
        const retval = ArkUIGeneratedNativeModule._GestureOps_createGestureGroup(mode.valueOf())
        return retval
    }
    private static setOnAction_serialize(gesture: KPointer, onAction: GestureEventHandler): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onAction)
        ArkUIGeneratedNativeModule._GestureOps_setOnAction(gesture, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setOnActionStart_serialize(gesture: KPointer, onActionStart: GestureEventHandler): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onActionStart)
        ArkUIGeneratedNativeModule._GestureOps_setOnActionStart(gesture, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setOnActionUpdate_serialize(gesture: KPointer, onActionUpdate: GestureEventHandler): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onActionUpdate)
        ArkUIGeneratedNativeModule._GestureOps_setOnActionUpdate(gesture, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setOnActionEnd_serialize(gesture: KPointer, onActionEnd: GestureEventHandler): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onActionEnd)
        ArkUIGeneratedNativeModule._GestureOps_setOnActionEnd(gesture, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setOnActionCancel_serialize(gesture: KPointer, onActionCancel: GestureEventHandler): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onActionCancel)
        ArkUIGeneratedNativeModule._GestureOps_setOnActionCancel(gesture, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setOnCancel_serialize(gesture: KPointer, onCancel: (() => void)): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onCancel)
        ArkUIGeneratedNativeModule._GestureOps_setOnCancel(gesture, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setGestureTag_serialize(gesture: KPointer, tag: string): void {
        ArkUIGeneratedNativeModule._GestureOps_setGestureTag(gesture, tag)
    }
    private static setAllowedTypes_serialize(gesture: KPointer, types: Array<SourceTool>): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((types.length).toInt())
        for (let typesCounterI = 0; typesCounterI < types.length; typesCounterI++) {
            const typesTmpElement: SourceTool = types[typesCounterI]
            thisSerializer.writeInt32(typesTmpElement.valueOf())
        }
        ArkUIGeneratedNativeModule._GestureOps_setAllowedTypes(gesture, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static addGestureToNode_serialize(node: KPointer, priority: number, mask: GestureMask, gesture: KPointer, isModifier: boolean): void {
        ArkUIGeneratedNativeModule._GestureOps_addGestureToNode(node, priority, mask.valueOf(), gesture, isModifier ? true : false)
    }
    private static addGestureToGroup_serialize(group: KPointer, gesture: KPointer): void {
        ArkUIGeneratedNativeModule._GestureOps_addGestureToGroup(group, gesture)
    }
    private static removeGestureByTag_serialize(node: KPointer, tag: string): void {
        ArkUIGeneratedNativeModule._GestureOps_removeGestureByTag(node, tag)
    }
    private static clearGestures_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._GestureOps_clearGestures(node)
    }
    private static getGestureEventType_serialize(event: KPointer): number {
        const retval = ArkUIGeneratedNativeModule._GestureOps_getGestureEventType(event)
        return retval
    }
    private static isScrollableComponent_serialize(event: KPointer): boolean {
        const retval = ArkUIGeneratedNativeModule._GestureOps_isScrollableComponent(event)
        return retval
    }
}
export class GlobalScope_ohos_arkui_componentSnapshot {
    public static get(id: string, callback: ((result: image.PixelMap) => void), options?: SnapshotOptions): void {
        const id_casted = id as (string)
        const callback_casted = callback as (((result: image.PixelMap) => void))
        const options_casted = options as (SnapshotOptions | undefined)
        GlobalScope_ohos_arkui_componentSnapshot.get_serialize(id_casted, callback_casted, options_casted)
        return
    }
    private static get_serialize(id: string, callback: ((result: image.PixelMap) => void), options?: SnapshotOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback)
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue = options!
            SnapshotOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GlobalScope_ohos_arkui_componentSnapshot_get(id, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class GlobalScope_ohos_arkui_performanceMonitor {
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
    private static begin_serialize(scene: string, startInputType: PerfMonitorActionType, note?: string): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (note !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const noteTmpValue = note!
            thisSerializer.writeString(noteTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GlobalScope_ohos_arkui_performanceMonitor_begin(scene, startInputType.valueOf(), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static end_serialize(scene: string): void {
        ArkUIGeneratedNativeModule._GlobalScope_ohos_arkui_performanceMonitor_end(scene)
    }
    private static recordInputEventTime_serialize(actionType: PerfMonitorActionType, sourceType: PerfMonitorSourceType, time: int64): void {
        ArkUIGeneratedNativeModule._GlobalScope_ohos_arkui_performanceMonitor_recordInputEventTime(actionType.valueOf(), sourceType.valueOf(), time)
    }
}
export class GlobalScope_ohos_font {
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
    private static registerFont_serialize(options: font.FontOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        font_FontOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._GlobalScope_ohos_font_registerFont(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static getSystemFontList_serialize(): Array<string> {
        const retval = ArkUIGeneratedNativeModule._GlobalScope_ohos_font_getSystemFontList()
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength: int32 = retvalDeserializer.readInt32()
        let buffer: Array<string> = new Array<string>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = (retvalDeserializer.readString() as string)
        }
        const returnResult: Array<string> = buffer
        return returnResult
    }
    private static getFontByName_serialize(fontName: string): font.FontInfo {
        const retval = ArkUIGeneratedNativeModule._GlobalScope_ohos_font_getFontByName(fontName)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: font.FontInfo = font_FontInfo_serializer.read(retvalDeserializer)
        return returnResult
    }
    private static getUIFontConfig_serialize(): font.UIFontConfig {
        const retval = ArkUIGeneratedNativeModule._GlobalScope_ohos_font_getUIFontConfig()
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: font.UIFontConfig = font_UIFontConfig_serializer.read(retvalDeserializer)
        return returnResult
    }
}
export class GlobalScope_ohos_measure_utils {
    public static measureText(options: MeasureOptions): double {
        const options_casted = options as (MeasureOptions)
        return GlobalScope_ohos_measure_utils.measureText_serialize(options_casted)
    }
    public static measureTextSize(options: MeasureOptions): SizeOptions {
        const options_casted = options as (MeasureOptions)
        return GlobalScope_ohos_measure_utils.measureTextSize_serialize(options_casted)
    }
    private static measureText_serialize(options: MeasureOptions): double {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        MeasureOptions_serializer.write(thisSerializer, options)
        const retval = ArkUIGeneratedNativeModule._GlobalScope_ohos_measure_utils_measureText(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static measureTextSize_serialize(options: MeasureOptions): SizeOptions {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        MeasureOptions_serializer.write(thisSerializer, options)
        const retval = ArkUIGeneratedNativeModule._GlobalScope_ohos_measure_utils_measureTextSize(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: SizeOptions = SizeOptions_serializer.read(retvalDeserializer)
        return returnResult
    }
}
export class GlobalScopeUicontextFontScale {
    public static isFollowingSystemFontScale(): boolean {
        return GlobalScopeUicontextFontScale.isFollowingSystemFontScale_serialize()
    }
    public static getMaxFontScale(): double {
        return GlobalScopeUicontextFontScale.getMaxFontScale_serialize()
    }
    private static isFollowingSystemFontScale_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._GlobalScopeUicontextFontScale_isFollowingSystemFontScale()
        return retval
    }
    private static getMaxFontScale_serialize(): double {
        const retval = ArkUIGeneratedNativeModule._GlobalScopeUicontextFontScale_getMaxFontScale()
        return retval
    }
}
export class GlobalScopeUicontextTextMenu {
    public static setMenuOptions(options: TextMenuOptions): void {
        const options_casted = options as (TextMenuOptions)
        GlobalScopeUicontextTextMenu.setMenuOptions_serialize(options_casted)
        return
    }
    private static setMenuOptions_serialize(options: TextMenuOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        TextMenuOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._GlobalScopeUicontextTextMenu_setMenuOptions(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class IUIContext {
    public static freezeUINode(id: string, isFrozen: boolean): void {
        const id_casted = id as (string)
        const isFrozen_casted = isFrozen as (boolean)
        IUIContext.freezeUINode0_serialize(id_casted, isFrozen_casted)
        return
    }
    public static freezeUINode(id: int32, isFrozen: boolean): void {
        const id_casted = id as (int32)
        const isFrozen_casted = isFrozen as (boolean)
        IUIContext.freezeUINode1_serialize(id_casted, isFrozen_casted)
        return
    }
    public static dispatchKeyEvent(node: int32 | string, event: KeyEvent): boolean {
        const node_casted = node as (int32 | string)
        const event_casted = event as (KeyEvent)
        return IUIContext.dispatchKeyEvent_serialize(node_casted, event_casted)
    }
    public static openBindSheet(bindSheetContent: KPointer, sheetOptions?: SheetOptions, targetId?: int32): Promise<void> {
        const bindSheetContent_casted = bindSheetContent as (KPointer)
        const sheetOptions_casted = sheetOptions as (SheetOptions | undefined)
        const targetId_casted = targetId as (int32 | undefined)
        return IUIContext.openBindSheet_serialize(bindSheetContent_casted, sheetOptions_casted, targetId_casted)
    }
    public static updateBindSheet(bindSheetContent: KPointer, sheetOptions: SheetOptions, partialUpdate?: boolean): Promise<void> {
        const bindSheetContent_casted = bindSheetContent as (KPointer)
        const sheetOptions_casted = sheetOptions as (SheetOptions)
        const partialUpdate_casted = partialUpdate as (boolean | undefined)
        return IUIContext.updateBindSheet_serialize(bindSheetContent_casted, sheetOptions_casted, partialUpdate_casted)
    }
    public static closeBindSheet(bindSheetContent: KPointer): Promise<void> {
        const bindSheetContent_casted = bindSheetContent as (KPointer)
        return IUIContext.closeBindSheet_serialize(bindSheetContent_casted)
    }
    public static bindTabsToScrollable(tabsController: TabsController, scroller: Scroller): void {
        const tabsController_casted = tabsController as (TabsController)
        const scroller_casted = scroller as (Scroller)
        IUIContext.bindTabsToScrollable_serialize(tabsController_casted, scroller_casted)
        return
    }
    public static unbindTabsFromScrollable(tabsController: TabsController, scroller: Scroller): void {
        const tabsController_casted = tabsController as (TabsController)
        const scroller_casted = scroller as (Scroller)
        IUIContext.unbindTabsFromScrollable_serialize(tabsController_casted, scroller_casted)
        return
    }
    public static bindTabsToNestedScrollable(tabsController: TabsController, parentScroller: Scroller, scrollerchildScroller: Scroller): void {
        const tabsController_casted = tabsController as (TabsController)
        const parentScroller_casted = parentScroller as (Scroller)
        const scrollerchildScroller_casted = scrollerchildScroller as (Scroller)
        IUIContext.bindTabsToNestedScrollable_serialize(tabsController_casted, parentScroller_casted, scrollerchildScroller_casted)
        return
    }
    public static unbindTabsFromNestedScrollable(tabsController: TabsController, parentScroller: Scroller, childScroller: Scroller): void {
        const tabsController_casted = tabsController as (TabsController)
        const parentScroller_casted = parentScroller as (Scroller)
        const childScroller_casted = childScroller as (Scroller)
        IUIContext.unbindTabsFromNestedScrollable_serialize(tabsController_casted, parentScroller_casted, childScroller_casted)
        return
    }
    public static setCustomKeyboardContinueFeature(feature: CustomKeyboardContinueFeature): void {
        const feature_casted = feature as (CustomKeyboardContinueFeature)
        IUIContext.setCustomKeyboardContinueFeature_serialize(feature_casted)
        return
    }
    private static freezeUINode0_serialize(id: string, isFrozen: boolean): void {
        ArkUIGeneratedNativeModule._IUIContext_freezeUINode0(id, isFrozen ? true : false)
    }
    private static freezeUINode1_serialize(id: int32, isFrozen: boolean): void {
        ArkUIGeneratedNativeModule._IUIContext_freezeUINode1(id, isFrozen ? true : false)
    }
    private static dispatchKeyEvent_serialize(node: int32 | string, event: KeyEvent): boolean {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (node instanceof int32) {
            thisSerializer.writeInt8((0).toByte())
            const nodeForIdx0 = node as int32
            thisSerializer.writeInt32(nodeForIdx0)
        } else if (node instanceof string) {
            thisSerializer.writeInt8((1).toByte())
            const nodeForIdx1 = node as string
            thisSerializer.writeString(nodeForIdx1)
        }
        const retval = ArkUIGeneratedNativeModule._IUIContext_dispatchKeyEvent(thisSerializer.asBuffer(), thisSerializer.length(), toPeerPtr(event))
        thisSerializer.release()
        return retval
    }
    private static openBindSheet_serialize(bindSheetContent: KPointer, sheetOptions?: SheetOptions, targetId?: int32): Promise<void> {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (sheetOptions !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const sheetOptionsTmpValue = sheetOptions!
            SheetOptions_serializer.write(thisSerializer, sheetOptionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (targetId !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const targetIdTmpValue = targetId!
            thisSerializer.writeInt32(targetIdTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._IUIContext_openBindSheet(bindSheetContent, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static updateBindSheet_serialize(bindSheetContent: KPointer, sheetOptions: SheetOptions, partialUpdate?: boolean): Promise<void> {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        SheetOptions_serializer.write(thisSerializer, sheetOptions)
        if (partialUpdate !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const partialUpdateTmpValue = partialUpdate!
            thisSerializer.writeBoolean(partialUpdateTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._IUIContext_updateBindSheet(bindSheetContent, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static closeBindSheet_serialize(bindSheetContent: KPointer): Promise<void> {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        const retval = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._IUIContext_closeBindSheet(bindSheetContent, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static bindTabsToScrollable_serialize(tabsController: TabsController, scroller: Scroller): void {
        ArkUIGeneratedNativeModule._IUIContext_bindTabsToScrollable(toPeerPtr(tabsController), toPeerPtr(scroller))
    }
    private static unbindTabsFromScrollable_serialize(tabsController: TabsController, scroller: Scroller): void {
        ArkUIGeneratedNativeModule._IUIContext_unbindTabsFromScrollable(toPeerPtr(tabsController), toPeerPtr(scroller))
    }
    private static bindTabsToNestedScrollable_serialize(tabsController: TabsController, parentScroller: Scroller, scrollerchildScroller: Scroller): void {
        ArkUIGeneratedNativeModule._IUIContext_bindTabsToNestedScrollable(toPeerPtr(tabsController), toPeerPtr(parentScroller), toPeerPtr(scrollerchildScroller))
    }
    private static unbindTabsFromNestedScrollable_serialize(tabsController: TabsController, parentScroller: Scroller, childScroller: Scroller): void {
        ArkUIGeneratedNativeModule._IUIContext_unbindTabsFromNestedScrollable(toPeerPtr(tabsController), toPeerPtr(parentScroller), toPeerPtr(childScroller))
    }
    private static setCustomKeyboardContinueFeature_serialize(feature: CustomKeyboardContinueFeature): void {
        ArkUIGeneratedNativeModule._IUIContext_setCustomKeyboardContinueFeature(feature.valueOf())
    }
}
export class LazyBuild {
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
    private static ApplyLazyBuilder_serialize(): void {
        ArkUIGeneratedNativeModule._LazyBuild_ApplyLazyBuilder()
    }
    private static SetListItemLazyBuilder_serialize(node: KPointer, builder: CustomBuilder): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(builder))
        ArkUIGeneratedNativeModule._LazyBuild_SetListItemLazyBuilder(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static SetTabContentLazyBuilder_serialize(node: KPointer, builder: CustomBuilder): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(builder))
        ArkUIGeneratedNativeModule._LazyBuild_SetTabContentLazyBuilder(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class LazyForEachOps {
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
    private static NotifyChange_serialize(node: KPointer, startIndex: int32, endIndex: int32, count: int32): void {
        ArkUIGeneratedNativeModule._LazyForEachOps_NotifyChange(node, startIndex, endIndex, count)
    }
    private static Sync_serialize(node: KPointer, totalCount: int32, creator: Callback_CreateItem, updater: Callback_RangeUpdate): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(creator)
        thisSerializer.holdAndWriteCallback(updater)
        ArkUIGeneratedNativeModule._LazyForEachOps_Sync(node, totalCount, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static SyncOnMoveOps_serialize(node: KPointer, onMoveFromToOps: Callback_OnMoveFromTo, onMoveOps: OnMoveHandler | undefined, onMoveDragEventOps: ItemDragEventHandler | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onMoveFromToOps)
        if (onMoveOps !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const onMoveOpsTmpValue = onMoveOps!
            thisSerializer.holdAndWriteCallback(onMoveOpsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (onMoveDragEventOps !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const onMoveDragEventOpsTmpValue = onMoveDragEventOps!
            ItemDragEventHandler_serializer.write(thisSerializer, onMoveDragEventOpsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._LazyForEachOps_SyncOnMoveOps(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class LevelOrderExtenderInternal {
    public static fromPtr(ptr: KPointer): LevelOrderExtender {
        return new LevelOrderExtender(MaterializedBaseTag.NOP, ptr)
    }
}
export class LevelOrderExtender implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, LevelOrderExtender.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, LevelOrderExtender.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._LevelOrderExtender_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LevelOrderExtender_getFinalizer()
    }
    public static clamp(order: number): LevelOrderExtender {
        const order_casted = order as (number)
        return LevelOrderExtender.clamp_serialize(order_casted)
    }
    private static clamp_serialize(order: number): LevelOrderExtender {
        const retval = ArkUIGeneratedNativeModule._LevelOrderExtender_clamp(order)
        const obj: LevelOrderExtender = LevelOrderExtenderInternal.fromPtr(retval)
        return obj
    }
    public getOrder(): number {
        return this.getOrder_serialize()
    }
    private getOrder_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._LevelOrderExtender_getOrder(this.peer!.ptr)
        return retval
    }
}
export class MagnifierExtender {
    static bind_serialize(id: string): void {
        ArkUIGeneratedNativeModule._MagnifierExtender_bind(id)
    }
    static show_serialize(x: double, y: double): void {
        ArkUIGeneratedNativeModule._MagnifierExtender_show(x, y)
    }
    static unbind_serialize(): void {
        ArkUIGeneratedNativeModule._MagnifierExtender_unbind()
    }
    public static bind(id: string): void {
        const id_casted = id as (string)
        MagnifierExtender.bind_serialize(id_casted)
        return
    }
    public static show(x: double, y: double): void {
        const x_casted = x as (double)
        const y_casted = y as (double)
        MagnifierExtender.show_serialize(x_casted, y_casted)
        return
    }
    public static unbind(): void {
        MagnifierExtender.unbind_serialize()
        return
    }
}
export class NavExtender {
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
    public static setNavDestinationBuilderCallback(navigation: KPointer, callback: NavExtender_PageMapNodeBuilder): void {
        const navigation_casted = navigation as (KPointer)
        const callback_casted = callback as (NavExtender_PageMapNodeBuilder)
        NavExtender.setNavDestinationBuilderCallback_serialize(navigation_casted, callback_casted)
        return
    }
    public static syncStack(peer: NavPathStack): void {
        const peer_casted = peer as (NavPathStack)
        NavExtender.syncStack_serialize(peer_casted)
        return
    }
    public static setNavDestinationId(ptr: KPointer, id: string | undefined): void {
        const ptr_casted = ptr as (KPointer)
        const id_casted = id as (string | undefined)
        NavExtender.setNavDestinationId_serialize(ptr_casted, id_casted)
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
    public static setNavDestinationRouterMapBuilderCallback(navigation: KPointer, callback: NavExtender_PageMapNodeBuilder): void {
        const navigation_casted = navigation as (KPointer)
        const callback_casted = callback as (NavExtender_PageMapNodeBuilder)
        NavExtender.setNavDestinationRouterMapBuilderCallback_serialize(navigation_casted, callback_casted)
        return
    }
    public static getRouteMapInConfig(context: KPointer): Array<string> {
        const context_casted = context as (KPointer)
        return NavExtender.getRouteMapInConfig_serialize(context_casted)
    }
    public static setSplitPlaceholder(navigation: KPointer, placeholderNode: KPointer): void {
        const navigation_casted = navigation as (KPointer)
        const placeholderNode_casted = placeholderNode as (KPointer)
        NavExtender.setSplitPlaceholder_serialize(navigation_casted, placeholderNode_casted)
        return
    }
    private static setNavigationOptions_serialize(ptr: KPointer, pathStack: NavPathStack): void {
        ArkUIGeneratedNativeModule._NavExtender_setNavigationOptions(ptr, toPeerPtr(pathStack))
    }
    private static setUpdateStackCallback_serialize(peer: NavPathStack, callback: NavExtender_OnUpdateStack): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._NavExtender_setUpdateStackCallback(toPeerPtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setNavDestinationBuilderCallback_serialize(navigation: KPointer, callback: NavExtender_PageMapNodeBuilder): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._NavExtender_setNavDestinationBuilderCallback(navigation, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static syncStack_serialize(peer: NavPathStack): void {
        ArkUIGeneratedNativeModule._NavExtender_syncStack(toPeerPtr(peer))
    }
    private static setNavDestinationId_serialize(ptr: KPointer, id: string | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (id !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const idTmpValue = id!
            thisSerializer.writeString(idTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NavExtender_setNavDestinationId(ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static pushPath_serialize(pathStack: NavPathStack, info: NavPathInfo, options: NavigationOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        NavigationOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._NavExtender_pushPath(toPeerPtr(pathStack), toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static replacePath_serialize(pathStack: NavPathStack, info: NavPathInfo, options: NavigationOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        NavigationOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._NavExtender_replacePath(toPeerPtr(pathStack), toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static pop_serialize(pathStack: NavPathStack, animated: boolean): string {
        const retval = ArkUIGeneratedNativeModule._NavExtender_pop(toPeerPtr(pathStack), animated ? true : false)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private static setOnPopCallback_serialize(pathStack: NavPathStack, popCallback: ((breakpoints: string) => void)): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(popCallback)
        ArkUIGeneratedNativeModule._NavExtender_setOnPopCallback(toPeerPtr(pathStack), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static getIdByIndex_serialize(pathStack: NavPathStack, index: int32): string {
        const retval = ArkUIGeneratedNativeModule._NavExtender_getIdByIndex(toPeerPtr(pathStack), index)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private static getIdByName_serialize(pathStack: NavPathStack, name: string): Array<string> {
        const retval = ArkUIGeneratedNativeModule._NavExtender_getIdByName(toPeerPtr(pathStack), name)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength: int32 = retvalDeserializer.readInt32()
        let buffer: Array<string> = new Array<string>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = (retvalDeserializer.readString() as string)
        }
        const returnResult: Array<string> = buffer
        return returnResult
    }
    private static popToIndex_serialize(pathStack: NavPathStack, index: int32, animated: boolean): void {
        ArkUIGeneratedNativeModule._NavExtender_popToIndex(toPeerPtr(pathStack), index, animated ? true : false)
    }
    private static popToName_serialize(pathStack: NavPathStack, name: string, animated: boolean): int32 {
        const retval = ArkUIGeneratedNativeModule._NavExtender_popToName(toPeerPtr(pathStack), name, animated ? true : false)
        return retval
    }
    private static setNavDestinationRouterMapBuilderCallback_serialize(navigation: KPointer, callback: NavExtender_PageMapNodeBuilder): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._NavExtender_setNavDestinationRouterMapBuilderCallback(navigation, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static getRouteMapInConfig_serialize(context: KPointer): Array<string> {
        const retval = ArkUIGeneratedNativeModule._NavExtender_getRouteMapInConfig(context)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength: int32 = retvalDeserializer.readInt32()
        let buffer: Array<string> = new Array<string>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = (retvalDeserializer.readString() as string)
        }
        const returnResult: Array<string> = buffer
        return returnResult
    }
    private static setSplitPlaceholder_serialize(navigation: KPointer, placeholderNode: KPointer): void {
        ArkUIGeneratedNativeModule._NavExtender_setSplitPlaceholder(navigation, placeholderNode)
    }
}
export class NodeContainerOps {
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
    private static nodeContainerOpsConstruct_serialize(id: int32, flags: int32): KPointer {
        const retval = ArkUIGeneratedNativeModule._NodeContainerOps_nodeContainerOpsConstruct(id, flags)
        return retval
    }
    private static nodeContainerSetNodeContainerOptions_serialize(ptr: KPointer, controller: KPointer): void {
        ArkUIGeneratedNativeModule._NodeContainerOps_nodeContainerSetNodeContainerOptions(ptr, controller)
    }
    private static addNodeContainerRootNode_serialize(self: KPointer, child: KPointer): void {
        ArkUIGeneratedNativeModule._NodeContainerOps_addNodeContainerRootNode(self, child)
    }
    private static setAboutToAppear_serialize(self: KPointer, value: (() => void)): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NodeContainerOps_setAboutToAppear(self, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setAboutToDisappear_serialize(self: KPointer, value: (() => void)): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NodeContainerOps_setAboutToDisappear(self, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setAboutToResize_serialize(self: KPointer, value: Callback_Size_Void): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NodeContainerOps_setAboutToResize(self, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setOnAttach_serialize(self: KPointer, value: (() => void)): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NodeContainerOps_setOnAttach(self, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setOnDetach_serialize(self: KPointer, value: (() => void)): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NodeContainerOps_setOnDetach(self, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setOnTouchEvent_serialize(self: KPointer, value?: ((event: TouchEvent) => void)): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._NodeContainerOps_setOnTouchEvent(self, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setOnDestoryEvent_serialize(self: KPointer, value: Callback_OnDestory_Void): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NodeContainerOps_setOnDestoryEvent(self, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class NodeContentExtender {
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
    private static constructorNodeContent_serialize(): KPointer {
        const retval = ArkUIGeneratedNativeModule._NodeContentExtender_constructorNodeContent()
        return retval
    }
    private static getDestroy_serialize(): KPointer {
        const retval = ArkUIGeneratedNativeModule._NodeContentExtender_getDestroy()
        return retval
    }
    private static addFrameNode_serialize(content: KPointer, node: KPointer): int32 {
        const retval = ArkUIGeneratedNativeModule._NodeContentExtender_addFrameNode(content, node)
        return retval
    }
    private static removeFrameNode_serialize(content: KPointer, node: KPointer): boolean {
        const retval = ArkUIGeneratedNativeModule._NodeContentExtender_removeFrameNode(content, node)
        return retval
    }
}
export class ParticleHelper {
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
    public static SetRippleFields(node: KPointer, rippleFields: Array<RippleFieldOptionsInner> | undefined): void {
        const node_casted = node as (KPointer)
        const rippleFields_casted = rippleFields as (Array<RippleFieldOptionsInner> | undefined)
        ParticleHelper.SetRippleFields_serialize(node_casted, rippleFields_casted)
        return
    }
    public static SetVelocityFields(node: KPointer, velocityFields: Array<VelocityFieldOptionsInner> | undefined): void {
        const node_casted = node as (KPointer)
        const velocityFields_casted = velocityFields as (Array<VelocityFieldOptionsInner> | undefined)
        ParticleHelper.SetVelocityFields_serialize(node_casted, velocityFields_casted)
        return
    }
    private static SetDisturbanceFields_serialize(node: KPointer, disturbanceFields: Array<DisturbanceFieldOptionsInner> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (disturbanceFields !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const disturbanceFieldsTmpValue = disturbanceFields!
            thisSerializer.writeInt32((disturbanceFieldsTmpValue.length).toInt())
            for (let disturbanceFieldsTmpValueCounterI = 0; disturbanceFieldsTmpValueCounterI < disturbanceFieldsTmpValue.length; disturbanceFieldsTmpValueCounterI++) {
                const disturbanceFieldsTmpValueTmpElement: DisturbanceFieldOptionsInner = disturbanceFieldsTmpValue[disturbanceFieldsTmpValueCounterI]
                DisturbanceFieldOptionsInner_serializer.write(thisSerializer, disturbanceFieldsTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ParticleHelper_SetDisturbanceFields(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static SetEmitterProperty_serialize(node: KPointer, emitter: Array<EmitterPropertyInner> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (emitter !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const emitterTmpValue = emitter!
            thisSerializer.writeInt32((emitterTmpValue.length).toInt())
            for (let emitterTmpValueCounterI = 0; emitterTmpValueCounterI < emitterTmpValue.length; emitterTmpValueCounterI++) {
                const emitterTmpValueTmpElement: EmitterPropertyInner = emitterTmpValue[emitterTmpValueCounterI]
                EmitterPropertyInner_serializer.write(thisSerializer, emitterTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ParticleHelper_SetEmitterProperty(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static ParticleConstruct_serialize(id: int32, flags: int32): KPointer {
        const retval = ArkUIGeneratedNativeModule._ParticleHelper_ParticleConstruct(id, flags)
        return retval
    }
    private static SetParticleOptions_serialize(node: KPointer, particles: ParticlesInner): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        ParticlesInner_serializer.write(thisSerializer, particles)
        ArkUIGeneratedNativeModule._ParticleHelper_SetParticleOptions(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static SetRippleFields_serialize(node: KPointer, rippleFields: Array<RippleFieldOptionsInner> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (rippleFields !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const rippleFieldsTmpValue = rippleFields!
            thisSerializer.writeInt32((rippleFieldsTmpValue.length).toInt())
            for (let rippleFieldsTmpValueCounterI = 0; rippleFieldsTmpValueCounterI < rippleFieldsTmpValue.length; rippleFieldsTmpValueCounterI++) {
                const rippleFieldsTmpValueTmpElement: RippleFieldOptionsInner = rippleFieldsTmpValue[rippleFieldsTmpValueCounterI]
                RippleFieldOptionsInner_serializer.write(thisSerializer, rippleFieldsTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ParticleHelper_SetRippleFields(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static SetVelocityFields_serialize(node: KPointer, velocityFields: Array<VelocityFieldOptionsInner> | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (velocityFields !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const velocityFieldsTmpValue = velocityFields!
            thisSerializer.writeInt32((velocityFieldsTmpValue.length).toInt())
            for (let velocityFieldsTmpValueCounterI = 0; velocityFieldsTmpValueCounterI < velocityFieldsTmpValue.length; velocityFieldsTmpValueCounterI++) {
                const velocityFieldsTmpValueTmpElement: VelocityFieldOptionsInner = velocityFieldsTmpValue[velocityFieldsTmpValueCounterI]
                VelocityFieldOptionsInner_serializer.write(thisSerializer, velocityFieldsTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ParticleHelper_SetVelocityFields(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class PromptActionExtender {
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
    private static openPopup_serialize(content: KPointer, target: TargetInfo, options?: PopupCommonOptions): Promise<void> {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        TargetInfo_serializer.write(thisSerializer, target)
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue = options!
            PopupCommonOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._PromptActionExtender_openPopup(content, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static updatePopup_serialize(content: KPointer, options: PopupCommonOptions, partialUpdate?: boolean): Promise<void> {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        PopupCommonOptions_serializer.write(thisSerializer, options)
        if (partialUpdate !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const partialUpdateTmpValue = partialUpdate!
            thisSerializer.writeBoolean(partialUpdateTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._PromptActionExtender_updatePopup(content, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static closePopup_serialize(content: KPointer): Promise<void> {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        const retval = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._PromptActionExtender_closePopup(content, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static openMenu_serialize(content: KPointer, target: TargetInfo, options?: MenuOptions): Promise<void> {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        TargetInfo_serializer.write(thisSerializer, target)
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue = options!
            MenuOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._PromptActionExtender_openMenu(content, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static updateMenu_serialize(content: KPointer, options: MenuOptions, partialUpdate?: boolean): Promise<void> {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        MenuOptions_serializer.write(thisSerializer, options)
        if (partialUpdate !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const partialUpdateTmpValue = partialUpdate!
            thisSerializer.writeBoolean(partialUpdateTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._PromptActionExtender_updateMenu(content, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static closeMenu_serialize(content: KPointer): Promise<void> {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        const retval = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._PromptActionExtender_closeMenu(content, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
export class RenderNodeExtender {
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
    public static setBackgroundColor(peer: RenderNode, backgroundColor: int32): void {
        const peer_casted = peer as (RenderNode)
        const backgroundColor_casted = backgroundColor as (int32)
        RenderNodeExtender.setBackgroundColor_serialize(peer_casted, backgroundColor_casted)
        return
    }
    public static setClipToFrame(peer: RenderNode, clipToFrame: boolean): void {
        const peer_casted = peer as (RenderNode)
        const clipToFrame_casted = clipToFrame as (boolean)
        RenderNodeExtender.setClipToFrame_serialize(peer_casted, clipToFrame_casted)
        return
    }
    public static setOpacity(peer: RenderNode, opacity: double): void {
        const peer_casted = peer as (RenderNode)
        const opacity_casted = opacity as (double)
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
    public static setShadowColor(peer: RenderNode, shadowColor: int32): void {
        const peer_casted = peer as (RenderNode)
        const shadowColor_casted = shadowColor as (int32)
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
    public static setShadowAlpha(peer: RenderNode, shadowAlpha: double): void {
        const peer_casted = peer as (RenderNode)
        const shadowAlpha_casted = shadowAlpha as (double)
        RenderNodeExtender.setShadowAlpha_serialize(peer_casted, shadowAlpha_casted)
        return
    }
    public static setShadowElevation(peer: RenderNode, shadowElevation: double): void {
        const peer_casted = peer as (RenderNode)
        const shadowElevation_casted = shadowElevation as (double)
        RenderNodeExtender.setShadowElevation_serialize(peer_casted, shadowElevation_casted)
        return
    }
    public static setShadowRadius(peer: RenderNode, shadowRadius: double): void {
        const peer_casted = peer as (RenderNode)
        const shadowRadius_casted = shadowRadius as (double)
        RenderNodeExtender.setShadowRadius_serialize(peer_casted, shadowRadius_casted)
        return
    }
    public static setBorderStyle(peer: RenderNode, borderStyle: NodeEdgeStyles): void {
        const peer_casted = peer as (RenderNode)
        const borderStyle_casted = borderStyle as (NodeEdgeStyles)
        RenderNodeExtender.setBorderStyle_serialize(peer_casted, borderStyle_casted)
        return
    }
    public static setBorderWidth(peer: RenderNode, borderWidth: EdgeF64, unitValue: int32): void {
        const peer_casted = peer as (RenderNode)
        const borderWidth_casted = borderWidth as (EdgeF64)
        const unitValue_casted = unitValue as (int32)
        RenderNodeExtender.setBorderWidth_serialize(peer_casted, borderWidth_casted, unitValue_casted)
        return
    }
    public static setBorderColor(peer: RenderNode, borderColor: EdgeI32): void {
        const peer_casted = peer as (RenderNode)
        const borderColor_casted = borderColor as (EdgeI32)
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
    public static setRectMask(peer: RenderNode, rect: Rect, fillColor: number, strokeColor: number, strokeWidth: number): void {
        const peer_casted = peer as (RenderNode)
        const rect_casted = rect as (Rect)
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
    public static setOvalMask(peer: RenderNode, rect: Rect, fillColor: number, strokeColor: number, strokeWidth: number): void {
        const peer_casted = peer as (RenderNode)
        const rect_casted = rect as (Rect)
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
    public static setRectClip(peer: RenderNode, rect: Rect): void {
        const peer_casted = peer as (RenderNode)
        const rect_casted = rect as (Rect)
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
    public static setOvalClip(peer: RenderNode, rect: Rect): void {
        const peer_casted = peer as (RenderNode)
        const rect_casted = rect as (Rect)
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
    public static insertChild(peer: RenderNode, child: RenderNode): int32 {
        const peer_casted = peer as (RenderNode)
        const child_casted = child as (RenderNode)
        return RenderNodeExtender.insertChild_serialize(peer_casted, child_casted)
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
    private static constructorRenderNode_serialize(nodeId: int32): KPointer {
        const retval = ArkUIGeneratedNativeModule._RenderNodeExtender_constructorRenderNode(nodeId)
        return retval
    }
    private static getDestroy_serialize(): KPointer {
        const retval = ArkUIGeneratedNativeModule._RenderNodeExtender_getDestroy()
        return retval
    }
    private static destroyPeer_serialize(peer: RenderNode): void {
        ArkUIGeneratedNativeModule._RenderNodeExtender_destroyPeer(extractors.toRenderNodePtr(peer))
    }
    private static setBackgroundColor_serialize(peer: RenderNode, backgroundColor: int32): void {
        ArkUIGeneratedNativeModule._RenderNodeExtender_setBackgroundColor(extractors.toRenderNodePtr(peer), backgroundColor)
    }
    private static setClipToFrame_serialize(peer: RenderNode, clipToFrame: boolean): void {
        ArkUIGeneratedNativeModule._RenderNodeExtender_setClipToFrame(extractors.toRenderNodePtr(peer), clipToFrame ? true : false)
    }
    private static setOpacity_serialize(peer: RenderNode, opacity: double): void {
        ArkUIGeneratedNativeModule._RenderNodeExtender_setOpacity(extractors.toRenderNodePtr(peer), opacity)
    }
    private static setSize_serialize(peer: RenderNode, size: Size, unitValue: int32): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        Size_serializer.write(thisSerializer, size)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setSize(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length(), unitValue)
        thisSerializer.release()
    }
    private static setPosition_serialize(peer: RenderNode, position: Vector2, unitValue: int32): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        Vector2_serializer.write(thisSerializer, position)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setPosition(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length(), unitValue)
        thisSerializer.release()
    }
    private static setPivot_serialize(peer: RenderNode, pivot: Vector2): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        Vector2_serializer.write(thisSerializer, pivot)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setPivot(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setScale_serialize(peer: RenderNode, scale: Vector2): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        Vector2_serializer.write(thisSerializer, scale)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setScale(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setTranslation_serialize(peer: RenderNode, translation: Vector2): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        Vector2_serializer.write(thisSerializer, translation)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setTranslation(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setRotation_serialize(peer: RenderNode, rotation: Vector3, unitValue: int32): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        Vector3_serializer.write(thisSerializer, rotation)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setRotation(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length(), unitValue)
        thisSerializer.release()
    }
    private static setTransform_serialize(peer: RenderNode, transform: Matrix4): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        const transform_0 = transform[0]
        thisSerializer.writeFloat64(transform_0)
        const transform_1 = transform[1]
        thisSerializer.writeFloat64(transform_1)
        const transform_2 = transform[2]
        thisSerializer.writeFloat64(transform_2)
        const transform_3 = transform[3]
        thisSerializer.writeFloat64(transform_3)
        const transform_4 = transform[4]
        thisSerializer.writeFloat64(transform_4)
        const transform_5 = transform[5]
        thisSerializer.writeFloat64(transform_5)
        const transform_6 = transform[6]
        thisSerializer.writeFloat64(transform_6)
        const transform_7 = transform[7]
        thisSerializer.writeFloat64(transform_7)
        const transform_8 = transform[8]
        thisSerializer.writeFloat64(transform_8)
        const transform_9 = transform[9]
        thisSerializer.writeFloat64(transform_9)
        const transform_10 = transform[10]
        thisSerializer.writeFloat64(transform_10)
        const transform_11 = transform[11]
        thisSerializer.writeFloat64(transform_11)
        const transform_12 = transform[12]
        thisSerializer.writeFloat64(transform_12)
        const transform_13 = transform[13]
        thisSerializer.writeFloat64(transform_13)
        const transform_14 = transform[14]
        thisSerializer.writeFloat64(transform_14)
        const transform_15 = transform[15]
        thisSerializer.writeFloat64(transform_15)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setTransform(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setShadowColor_serialize(peer: RenderNode, shadowColor: int32): void {
        ArkUIGeneratedNativeModule._RenderNodeExtender_setShadowColor(extractors.toRenderNodePtr(peer), shadowColor)
    }
    private static setShadowOffset_serialize(peer: RenderNode, shadowOffset: Vector2, unitValue: int32): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        Vector2_serializer.write(thisSerializer, shadowOffset)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setShadowOffset(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length(), unitValue)
        thisSerializer.release()
    }
    private static setLabel_serialize(peer: RenderNode, label: string): void {
        ArkUIGeneratedNativeModule._RenderNodeExtender_setLabel(extractors.toRenderNodePtr(peer), label)
    }
    private static setShadowAlpha_serialize(peer: RenderNode, shadowAlpha: double): void {
        ArkUIGeneratedNativeModule._RenderNodeExtender_setShadowAlpha(extractors.toRenderNodePtr(peer), shadowAlpha)
    }
    private static setShadowElevation_serialize(peer: RenderNode, shadowElevation: double): void {
        ArkUIGeneratedNativeModule._RenderNodeExtender_setShadowElevation(extractors.toRenderNodePtr(peer), shadowElevation)
    }
    private static setShadowRadius_serialize(peer: RenderNode, shadowRadius: double): void {
        ArkUIGeneratedNativeModule._RenderNodeExtender_setShadowRadius(extractors.toRenderNodePtr(peer), shadowRadius)
    }
    private static setBorderStyle_serialize(peer: RenderNode, borderStyle: NodeEdgeStyles): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        NodeEdgeStyles_serializer.write(thisSerializer, borderStyle)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setBorderStyle(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setBorderWidth_serialize(peer: RenderNode, borderWidth: EdgeF64, unitValue: int32): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        EdgeF64_serializer.write(thisSerializer, borderWidth)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setBorderWidth(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length(), unitValue)
        thisSerializer.release()
    }
    private static setBorderColor_serialize(peer: RenderNode, borderColor: EdgeI32): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        EdgeI32_serializer.write(thisSerializer, borderColor)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setBorderColor(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setBorderRadius_serialize(peer: RenderNode, borderRadius: BorderRadiuses_graphics, unitValue: int32): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        BorderRadiuses_graphics_serializer.write(thisSerializer, borderRadius)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setBorderRadius(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length(), unitValue)
        thisSerializer.release()
    }
    private static setMarkNodeGroup_serialize(peer: RenderNode, markNodeGroup: boolean): void {
        ArkUIGeneratedNativeModule._RenderNodeExtender_setMarkNodeGroup(extractors.toRenderNodePtr(peer), markNodeGroup ? true : false)
    }
    private static setRectMask_serialize(peer: RenderNode, rect: Rect, fillColor: number, strokeColor: number, strokeWidth: number): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        common2D_Rect_serializer.write(thisSerializer, rect)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setRectMask(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length(), fillColor, strokeColor, strokeWidth)
        thisSerializer.release()
    }
    private static setCircleMask_serialize(peer: RenderNode, circle: Circle, fillColor: number, strokeColor: number, strokeWidth: number): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        Circle_serializer.write(thisSerializer, circle)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setCircleMask(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length(), fillColor, strokeColor, strokeWidth)
        thisSerializer.release()
    }
    private static setRoundRectMask_serialize(peer: RenderNode, roundRect: RoundRect, fillColor: number, strokeColor: number, strokeWidth: number): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        RoundRect_serializer.write(thisSerializer, roundRect)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setRoundRectMask(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length(), fillColor, strokeColor, strokeWidth)
        thisSerializer.release()
    }
    private static setOvalMask_serialize(peer: RenderNode, rect: Rect, fillColor: number, strokeColor: number, strokeWidth: number): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        common2D_Rect_serializer.write(thisSerializer, rect)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setOvalMask(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length(), fillColor, strokeColor, strokeWidth)
        thisSerializer.release()
    }
    private static setPath_serialize(peer: RenderNode, path: CommandPath, fillColor: number, strokeColor: number, strokeWidth: number): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        CommandPath_serializer.write(thisSerializer, path)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setPath(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length(), fillColor, strokeColor, strokeWidth)
        thisSerializer.release()
    }
    private static setRectClip_serialize(peer: RenderNode, rect: Rect): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        common2D_Rect_serializer.write(thisSerializer, rect)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setRectClip(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setCircleClip_serialize(peer: RenderNode, circle: Circle): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        Circle_serializer.write(thisSerializer, circle)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setCircleClip(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setRoundRectClip_serialize(peer: RenderNode, roundRect: RoundRect): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        RoundRect_serializer.write(thisSerializer, roundRect)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setRoundRectClip(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setOvalClip_serialize(peer: RenderNode, rect: Rect): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        common2D_Rect_serializer.write(thisSerializer, rect)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setOvalClip(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setPathClip_serialize(peer: RenderNode, path: CommandPath): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        CommandPath_serializer.write(thisSerializer, path)
        ArkUIGeneratedNativeModule._RenderNodeExtender_setPathClip(extractors.toRenderNodePtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static appendChild_serialize(peer: RenderNode, node: RenderNode): int32 {
        const retval = ArkUIGeneratedNativeModule._RenderNodeExtender_appendChild(extractors.toRenderNodePtr(peer), extractors.toRenderNodePtr(node))
        return retval
    }
    private static insertChildAfter_serialize(peer: RenderNode, child: RenderNode, sibling: RenderNode): int32 {
        const retval = ArkUIGeneratedNativeModule._RenderNodeExtender_insertChildAfter(extractors.toRenderNodePtr(peer), extractors.toRenderNodePtr(child), extractors.toRenderNodePtr(sibling))
        return retval
    }
    private static insertChild_serialize(peer: RenderNode, child: RenderNode): int32 {
        const retval = ArkUIGeneratedNativeModule._RenderNodeExtender_insertChild(extractors.toRenderNodePtr(peer), extractors.toRenderNodePtr(child))
        return retval
    }
    private static removeChild_serialize(peer: RenderNode, node: RenderNode): void {
        ArkUIGeneratedNativeModule._RenderNodeExtender_removeChild(extractors.toRenderNodePtr(peer), extractors.toRenderNodePtr(node))
    }
    private static clearChildren_serialize(peer: RenderNode): void {
        ArkUIGeneratedNativeModule._RenderNodeExtender_clearChildren(extractors.toRenderNodePtr(peer))
    }
    private static invalidate_serialize(peer: RenderNode): void {
        ArkUIGeneratedNativeModule._RenderNodeExtender_invalidate(extractors.toRenderNodePtr(peer))
    }
}
export class RenderServiceNode {
    public static getNodeId(nodeId: string): int32 {
        const nodeId_casted = nodeId as (string)
        return RenderServiceNode.getNodeId_serialize(nodeId_casted)
    }
    private static getNodeId_serialize(nodeId: string): int32 {
        const retval = ArkUIGeneratedNativeModule._RenderServiceNode_getNodeId(nodeId)
        return retval
    }
}
export class RestrictedWorkerInternal {
    public static fromPtr(ptr: KPointer): RestrictedWorker {
        return new RestrictedWorker(MaterializedBaseTag.NOP, ptr)
    }
}
export class RestrictedWorker implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    public onexit?: RestrictedWorker_onexit_Callback | undefined
    public onerror?: RestrictedWorker_onerror_Callback | undefined
    public onmessage?: RestrictedWorker_onmessage_Callback | undefined
    public onmessageerror?: RestrictedWorker_onmessage_Callback | undefined
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, RestrictedWorker.getFinalizer())
        this.onexit = this.getOnexit()
        this.onerror = this.getOnerror()
        this.onmessage = this.getOnmessage()
        this.onmessageerror = this.getOnmessageerror()
    }
    constructor(scriptURL: string, options?: WorkerOptions) {
        this(MaterializedBaseTag.NOP, RestrictedWorker.construct(scriptURL, options))
        this.onexit = this.getOnexit()
        this.onerror = this.getOnerror()
        this.onmessage = this.getOnmessage()
        this.onmessageerror = this.getOnmessageerror()
    }
    static construct(scriptURL: string, options?: WorkerOptions): KPointer {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue = options!
            WorkerOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval = ArkUIGeneratedNativeModule._RestrictedWorker_construct(scriptURL, thisSerializer.asBuffer(), thisSerializer.length())
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
    private postMessage0_serialize(message: Object, transfer: Array<ArrayBuffer>): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(message)
        thisSerializer.writeInt32((transfer.length).toInt())
        for (let transferCounterI = 0; transferCounterI < transfer.length; transferCounterI++) {
            const transferTmpElement: ArrayBuffer = transfer[transferCounterI]
            thisSerializer.writeBuffer(transferTmpElement)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_postMessage0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private postMessage1_serialize(message: Object, options?: PostMessageOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(message)
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue = options!
            PostMessageOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_postMessage1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private postMessageWithSharedSendable_serialize(message: Object, transfer?: Array<ArrayBuffer>): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(message)
        if (transfer !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const transferTmpValue = transfer!
            thisSerializer.writeInt32((transferTmpValue.length).toInt())
            for (let transferTmpValueCounterI = 0; transferTmpValueCounterI < transferTmpValue.length; transferTmpValueCounterI++) {
                const transferTmpValueTmpElement: ArrayBuffer = transferTmpValue[transferTmpValueCounterI]
                thisSerializer.writeBuffer(transferTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_postMessageWithSharedSendable(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private on_serialize(Type: string, listener: WorkerEventListener): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(listener)
        ArkUIGeneratedNativeModule._RestrictedWorker_on(this.peer!.ptr, Type, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private once_serialize(Type: string, listener: WorkerEventListener): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(listener)
        ArkUIGeneratedNativeModule._RestrictedWorker_once(this.peer!.ptr, Type, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private off_serialize(Type: string, listener?: WorkerEventListener): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (listener !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const listenerTmpValue = listener!
            thisSerializer.holdAndWriteCallback(listenerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_off(this.peer!.ptr, Type, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private terminate_serialize(): void {
        ArkUIGeneratedNativeModule._RestrictedWorker_terminate(this.peer!.ptr)
    }
    private addEventListener_serialize(Type: string, listener: WorkerEventListener): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(listener)
        ArkUIGeneratedNativeModule._RestrictedWorker_addEventListener(this.peer!.ptr, Type, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private dispatchEvent_serialize(event: Event): boolean {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        Event_serializer.write(thisSerializer, event)
        const retval = ArkUIGeneratedNativeModule._RestrictedWorker_dispatchEvent(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private removeEventListener_serialize(Type: string, callback_?: WorkerEventListener): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (callback_ !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const callback_TmpValue = callback_!
            thisSerializer.holdAndWriteCallback(callback_TmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_removeEventListener(this.peer!.ptr, Type, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private removeAllListener_serialize(): void {
        ArkUIGeneratedNativeModule._RestrictedWorker_removeAllListener(this.peer!.ptr)
    }
    private registerGlobalCallObject_serialize(instanceName: string, globalCallObject: Object): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(globalCallObject)
        ArkUIGeneratedNativeModule._RestrictedWorker_registerGlobalCallObject(this.peer!.ptr, instanceName, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private unregisterGlobalCallObject_serialize(instanceName?: string): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (instanceName !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const instanceNameTmpValue = instanceName!
            thisSerializer.writeString(instanceNameTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_unregisterGlobalCallObject(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnexit_serialize(): RestrictedWorker_onexit_Callback | undefined {
        const retval = ArkUIGeneratedNativeModule._RestrictedWorker_getOnexit(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType = retvalDeserializer.readInt8()!.toInt()
        let buffer: RestrictedWorker_onexit_Callback | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bufferOptBufResource: CallbackResource = retvalDeserializer.readCallbackResource()
            const bufferOptBufCall: KPointer = retvalDeserializer.readPointer()
            const bufferOptBufCallSync: KPointer = retvalDeserializer.readPointer()
            const bufferOptClosure = (code: number):void => {
                const bufferOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                bufferOptBufArgsSerializer.writeInt32(bufferOptBufResource.resourceId);
                bufferOptBufArgsSerializer.writePointer(bufferOptBufCall);
                bufferOptBufArgsSerializer.writePointer(bufferOptBufCallSync);
                bufferOptBufArgsSerializer.writeNumber(code);
                InteropNativeModule._CallCallbackSync(10, 575674193, bufferOptBufArgsSerializer.asBuffer(), bufferOptBufArgsSerializer.length());
                bufferOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(bufferOptClosure, bufferOptBufResource)
            buffer = bufferOptClosure
        }
        const returnResult: RestrictedWorker_onexit_Callback | undefined = buffer
        return returnResult
    }
    private setOnexit_serialize(onexit: RestrictedWorker_onexit_Callback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (onexit !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const onexitTmpValue = onexit!
            thisSerializer.holdAndWriteCallback(onexitTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_setOnexit(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnerror_serialize(): RestrictedWorker_onerror_Callback | undefined {
        const retval = ArkUIGeneratedNativeModule._RestrictedWorker_getOnerror(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType = retvalDeserializer.readInt8()!.toInt()
        let buffer: RestrictedWorker_onerror_Callback | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bufferOptBufResource: CallbackResource = retvalDeserializer.readCallbackResource()
            const bufferOptBufCall: KPointer = retvalDeserializer.readPointer()
            const bufferOptBufCallSync: KPointer = retvalDeserializer.readPointer()
            const bufferOptClosure = (ev: ErrorEvent):void => {
                const bufferOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                bufferOptBufArgsSerializer.writeInt32(bufferOptBufResource.resourceId);
                bufferOptBufArgsSerializer.writePointer(bufferOptBufCall);
                bufferOptBufArgsSerializer.writePointer(bufferOptBufCallSync);
                ErrorEvent_serializer.write(bufferOptBufArgsSerializer, ev);
                InteropNativeModule._CallCallbackSync(10, -1922518199, bufferOptBufArgsSerializer.asBuffer(), bufferOptBufArgsSerializer.length());
                bufferOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(bufferOptClosure, bufferOptBufResource)
            buffer = bufferOptClosure
        }
        const returnResult: RestrictedWorker_onerror_Callback | undefined = buffer
        return returnResult
    }
    private setOnerror_serialize(onerror: RestrictedWorker_onerror_Callback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (onerror !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const onerrorTmpValue = onerror!
            thisSerializer.holdAndWriteCallback(onerrorTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_setOnerror(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnmessage_serialize(): RestrictedWorker_onmessage_Callback | undefined {
        const retval = ArkUIGeneratedNativeModule._RestrictedWorker_getOnmessage(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType = retvalDeserializer.readInt8()!.toInt()
        let buffer: RestrictedWorker_onmessage_Callback | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bufferOptBufResource: CallbackResource = retvalDeserializer.readCallbackResource()
            const bufferOptBufCall: KPointer = retvalDeserializer.readPointer()
            const bufferOptBufCallSync: KPointer = retvalDeserializer.readPointer()
            const bufferOptClosure = (event: MessageEvents):void => {
                const bufferOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                bufferOptBufArgsSerializer.writeInt32(bufferOptBufResource.resourceId);
                bufferOptBufArgsSerializer.writePointer(bufferOptBufCall);
                bufferOptBufArgsSerializer.writePointer(bufferOptBufCallSync);
                MessageEvents_serializer.write(bufferOptBufArgsSerializer, event);
                InteropNativeModule._CallCallbackSync(10, -1119557574, bufferOptBufArgsSerializer.asBuffer(), bufferOptBufArgsSerializer.length());
                bufferOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(bufferOptClosure, bufferOptBufResource)
            buffer = bufferOptClosure
        }
        const returnResult: RestrictedWorker_onmessage_Callback | undefined = buffer
        return returnResult
    }
    private setOnmessage_serialize(onmessage: RestrictedWorker_onmessage_Callback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (onmessage !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const onmessageTmpValue = onmessage!
            thisSerializer.holdAndWriteCallback(onmessageTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_setOnmessage(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnmessageerror_serialize(): RestrictedWorker_onmessage_Callback | undefined {
        const retval = ArkUIGeneratedNativeModule._RestrictedWorker_getOnmessageerror(this.peer!.ptr)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType = retvalDeserializer.readInt8()!.toInt()
        let buffer: RestrictedWorker_onmessage_Callback | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            const bufferOptBufResource: CallbackResource = retvalDeserializer.readCallbackResource()
            const bufferOptBufCall: KPointer = retvalDeserializer.readPointer()
            const bufferOptBufCallSync: KPointer = retvalDeserializer.readPointer()
            const bufferOptClosure = (event: MessageEvents):void => {
                const bufferOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                bufferOptBufArgsSerializer.writeInt32(bufferOptBufResource.resourceId);
                bufferOptBufArgsSerializer.writePointer(bufferOptBufCall);
                bufferOptBufArgsSerializer.writePointer(bufferOptBufCallSync);
                MessageEvents_serializer.write(bufferOptBufArgsSerializer, event);
                InteropNativeModule._CallCallbackSync(10, -1119557574, bufferOptBufArgsSerializer.asBuffer(), bufferOptBufArgsSerializer.length());
                bufferOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(bufferOptClosure, bufferOptBufResource)
            buffer = bufferOptClosure
        }
        const returnResult: RestrictedWorker_onmessage_Callback | undefined = buffer
        return returnResult
    }
    private setOnmessageerror_serialize(onmessageerror: RestrictedWorker_onmessage_Callback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (onmessageerror !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const onmessageerrorTmpValue = onmessageerror!
            thisSerializer.holdAndWriteCallback(onmessageerrorTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_setOnmessageerror(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class RouterExtender {
    public static push(jsView: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback): Promise<void> {
        const jsView_casted = jsView as (KPointer)
        const options_casted = options as (PageRouterOptions)
        const finishCallback_casted = finishCallback as (RouterFinishCallback | undefined)
        return RouterExtender.push0_serialize(jsView_casted, options_casted, finishCallback_casted)
    }
    public static push(jsView: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback, callback_?: Router_BusinessError_Void): void {
        const jsView_casted = jsView as (KPointer)
        const options_casted = options as (PageRouterOptions)
        const finishCallback_casted = finishCallback as (RouterFinishCallback | undefined)
        const callback__casted = callback_ as (Router_BusinessError_Void | undefined)
        RouterExtender.push1_serialize(jsView_casted, options_casted, finishCallback_casted, callback__casted)
        return
    }
    public static replace(jsView: KPointer, options: PageRouterOptions, enterFinishCallback?: RouterFinishCallback): Promise<void> {
        const jsView_casted = jsView as (KPointer)
        const options_casted = options as (PageRouterOptions)
        const enterFinishCallback_casted = enterFinishCallback as (RouterFinishCallback | undefined)
        return RouterExtender.replace0_serialize(jsView_casted, options_casted, enterFinishCallback_casted)
    }
    public static replace(jsView: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback, callback_?: Router_BusinessError_Void): void {
        const jsView_casted = jsView as (KPointer)
        const options_casted = options as (PageRouterOptions)
        const finishCallback_casted = finishCallback as (RouterFinishCallback | undefined)
        const callback__casted = callback_ as (Router_BusinessError_Void | undefined)
        RouterExtender.replace1_serialize(jsView_casted, options_casted, finishCallback_casted, callback__casted)
        return
    }
    public static back(options?: RouterOptionsInner): void {
        const options_casted = options as (RouterOptionsInner | undefined)
        RouterExtender.back0_serialize(options_casted)
        return
    }
    public static back(index: int32, params?: string): void {
        const index_casted = index as (int32)
        const params_casted = params as (string | undefined)
        RouterExtender.back1_serialize(index_casted, params_casted)
        return
    }
    public static runPage(jsView: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback): void {
        const jsView_casted = jsView as (KPointer)
        const options_casted = options as (PageRouterOptions)
        const finishCallback_casted = finishCallback as (RouterFinishCallback | undefined)
        RouterExtender.runPage_serialize(jsView_casted, options_casted, finishCallback_casted)
        return
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
    public static getLength(): string {
        return RouterExtender.getLength_serialize()
    }
    public static getState(): RouterStateInner {
        return RouterExtender.getState_serialize()
    }
    public static getStateByIndex(index: int32): RouterStateInner | undefined {
        const index_casted = index as (int32)
        return RouterExtender.getStateByIndex_serialize(index_casted)
    }
    public static getStateByUrl(url: string): Array<RouterStateInner> {
        const url_casted = url as (string)
        return RouterExtender.getStateByUrl_serialize(url_casted)
    }
    public static getParams(): string {
        return RouterExtender.getParams_serialize()
    }
    public static pushNamedRoute(jsView: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback): Promise<void> {
        const jsView_casted = jsView as (KPointer)
        const options_casted = options as (PageRouterOptions)
        const finishCallback_casted = finishCallback as (RouterFinishCallback | undefined)
        return RouterExtender.pushNamedRoute0_serialize(jsView_casted, options_casted, finishCallback_casted)
    }
    public static pushNamedRoute(jsView: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback, callback_?: Router_BusinessError_Void): void {
        const jsView_casted = jsView as (KPointer)
        const options_casted = options as (PageRouterOptions)
        const finishCallback_casted = finishCallback as (RouterFinishCallback | undefined)
        const callback__casted = callback_ as (Router_BusinessError_Void | undefined)
        RouterExtender.pushNamedRoute1_serialize(jsView_casted, options_casted, finishCallback_casted, callback__casted)
        return
    }
    public static replaceNamedRoute(jsView: KPointer, options: PageRouterOptions, enterFinishCallback?: RouterFinishCallback): Promise<void> {
        const jsView_casted = jsView as (KPointer)
        const options_casted = options as (PageRouterOptions)
        const enterFinishCallback_casted = enterFinishCallback as (RouterFinishCallback | undefined)
        return RouterExtender.replaceNamedRoute0_serialize(jsView_casted, options_casted, enterFinishCallback_casted)
    }
    public static replaceNamedRoute(jsView: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback, callback_?: Router_BusinessError_Void): void {
        const jsView_casted = jsView as (KPointer)
        const options_casted = options as (PageRouterOptions)
        const finishCallback_casted = finishCallback as (RouterFinishCallback | undefined)
        const callback__casted = callback_ as (Router_BusinessError_Void | undefined)
        RouterExtender.replaceNamedRoute1_serialize(jsView_casted, options_casted, finishCallback_casted, callback__casted)
        return
    }
    public static createDynamic(options: RouterOptionsInner): KPointer {
        const options_casted = options as (RouterOptionsInner)
        return RouterExtender.createDynamic_serialize(options_casted)
    }
    public static pushDynamic(pageNode: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback): Promise<void> {
        const pageNode_casted = pageNode as (KPointer)
        const options_casted = options as (PageRouterOptions)
        const finishCallback_casted = finishCallback as (RouterFinishCallback | undefined)
        return RouterExtender.pushDynamic0_serialize(pageNode_casted, options_casted, finishCallback_casted)
    }
    public static pushDynamic(pageNode: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback, callback_?: Router_BusinessError_Void): void {
        const pageNode_casted = pageNode as (KPointer)
        const options_casted = options as (PageRouterOptions)
        const finishCallback_casted = finishCallback as (RouterFinishCallback | undefined)
        const callback__casted = callback_ as (Router_BusinessError_Void | undefined)
        RouterExtender.pushDynamic1_serialize(pageNode_casted, options_casted, finishCallback_casted, callback__casted)
        return
    }
    public static replaceDynamic(pageNode: KPointer, options: PageRouterOptions, enterFinishCallback?: RouterFinishCallback): Promise<void> {
        const pageNode_casted = pageNode as (KPointer)
        const options_casted = options as (PageRouterOptions)
        const enterFinishCallback_casted = enterFinishCallback as (RouterFinishCallback | undefined)
        return RouterExtender.replaceDynamic0_serialize(pageNode_casted, options_casted, enterFinishCallback_casted)
    }
    public static replaceDynamic(pageNode: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback, callback_?: Router_BusinessError_Void): void {
        const pageNode_casted = pageNode as (KPointer)
        const options_casted = options as (PageRouterOptions)
        const finishCallback_casted = finishCallback as (RouterFinishCallback | undefined)
        const callback__casted = callback_ as (Router_BusinessError_Void | undefined)
        RouterExtender.replaceDynamic1_serialize(pageNode_casted, options_casted, finishCallback_casted, callback__casted)
        return
    }
    private static push0_serialize(jsView: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback): Promise<void> {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        PageRouterOptions_serializer.write(thisSerializer, options)
        if (finishCallback !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const finishCallbackTmpValue = finishCallback!
            thisSerializer.holdAndWriteCallback(finishCallbackTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._RouterExtender_push0(jsView, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static push1_serialize(jsView: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback, callback_?: Router_BusinessError_Void): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        PageRouterOptions_serializer.write(thisSerializer, options)
        if (finishCallback !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const finishCallbackTmpValue = finishCallback!
            thisSerializer.holdAndWriteCallback(finishCallbackTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (callback_ !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const callback_TmpValue = callback_!
            thisSerializer.holdAndWriteCallback(callback_TmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RouterExtender_push1(jsView, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static replace0_serialize(jsView: KPointer, options: PageRouterOptions, enterFinishCallback?: RouterFinishCallback): Promise<void> {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        PageRouterOptions_serializer.write(thisSerializer, options)
        if (enterFinishCallback !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const enterFinishCallbackTmpValue = enterFinishCallback!
            thisSerializer.holdAndWriteCallback(enterFinishCallbackTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._RouterExtender_replace0(jsView, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static replace1_serialize(jsView: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback, callback_?: Router_BusinessError_Void): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        PageRouterOptions_serializer.write(thisSerializer, options)
        if (finishCallback !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const finishCallbackTmpValue = finishCallback!
            thisSerializer.holdAndWriteCallback(finishCallbackTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (callback_ !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const callback_TmpValue = callback_!
            thisSerializer.holdAndWriteCallback(callback_TmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RouterExtender_replace1(jsView, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static back0_serialize(options?: RouterOptionsInner): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue = options!
            RouterOptionsInner_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RouterExtender_back0(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static back1_serialize(index: int32, params?: string): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (params !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const paramsTmpValue = params!
            thisSerializer.writeString(paramsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RouterExtender_back1(index, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static runPage_serialize(jsView: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        PageRouterOptions_serializer.write(thisSerializer, options)
        if (finishCallback !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const finishCallbackTmpValue = finishCallback!
            thisSerializer.holdAndWriteCallback(finishCallbackTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RouterExtender_runPage(jsView, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static clear_serialize(): void {
        ArkUIGeneratedNativeModule._RouterExtender_clear()
    }
    private static showAlertBeforeBackPage_serialize(message: string): void {
        ArkUIGeneratedNativeModule._RouterExtender_showAlertBeforeBackPage(message)
    }
    private static hideAlertBeforeBackPage_serialize(): void {
        ArkUIGeneratedNativeModule._RouterExtender_hideAlertBeforeBackPage()
    }
    private static getLength_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._RouterExtender_getLength()
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private static getState_serialize(): RouterStateInner {
        const retval = ArkUIGeneratedNativeModule._RouterExtender_getState()
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: RouterStateInner = RouterStateInner_serializer.read(retvalDeserializer)
        return returnResult
    }
    private static getStateByIndex_serialize(index: int32): RouterStateInner | undefined {
        const retval = ArkUIGeneratedNativeModule._RouterExtender_getStateByIndex(index)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType = retvalDeserializer.readInt8()!.toInt()
        let buffer: RouterStateInner | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = RouterStateInner_serializer.read(retvalDeserializer)
        }
        const returnResult: RouterStateInner | undefined = buffer
        return returnResult
    }
    private static getStateByUrl_serialize(url: string): Array<RouterStateInner> {
        const retval = ArkUIGeneratedNativeModule._RouterExtender_getStateByUrl(url)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength: int32 = retvalDeserializer.readInt32()
        let buffer: Array<RouterStateInner> = new Array<RouterStateInner>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = RouterStateInner_serializer.read(retvalDeserializer)
        }
        const returnResult: Array<RouterStateInner> = buffer
        return returnResult
    }
    private static getParams_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._RouterExtender_getParams()
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: string = (retvalDeserializer.readString() as string)
        return returnResult
    }
    private static pushNamedRoute0_serialize(jsView: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback): Promise<void> {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        PageRouterOptions_serializer.write(thisSerializer, options)
        if (finishCallback !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const finishCallbackTmpValue = finishCallback!
            thisSerializer.holdAndWriteCallback(finishCallbackTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._RouterExtender_pushNamedRoute0(jsView, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static pushNamedRoute1_serialize(jsView: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback, callback_?: Router_BusinessError_Void): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        PageRouterOptions_serializer.write(thisSerializer, options)
        if (finishCallback !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const finishCallbackTmpValue = finishCallback!
            thisSerializer.holdAndWriteCallback(finishCallbackTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (callback_ !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const callback_TmpValue = callback_!
            thisSerializer.holdAndWriteCallback(callback_TmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RouterExtender_pushNamedRoute1(jsView, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static replaceNamedRoute0_serialize(jsView: KPointer, options: PageRouterOptions, enterFinishCallback?: RouterFinishCallback): Promise<void> {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        PageRouterOptions_serializer.write(thisSerializer, options)
        if (enterFinishCallback !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const enterFinishCallbackTmpValue = enterFinishCallback!
            thisSerializer.holdAndWriteCallback(enterFinishCallbackTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._RouterExtender_replaceNamedRoute0(jsView, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static replaceNamedRoute1_serialize(jsView: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback, callback_?: Router_BusinessError_Void): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        PageRouterOptions_serializer.write(thisSerializer, options)
        if (finishCallback !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const finishCallbackTmpValue = finishCallback!
            thisSerializer.holdAndWriteCallback(finishCallbackTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (callback_ !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const callback_TmpValue = callback_!
            thisSerializer.holdAndWriteCallback(callback_TmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RouterExtender_replaceNamedRoute1(jsView, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static createDynamic_serialize(options: RouterOptionsInner): KPointer {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        RouterOptionsInner_serializer.write(thisSerializer, options)
        const retval = ArkUIGeneratedNativeModule._RouterExtender_createDynamic(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static pushDynamic0_serialize(pageNode: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback): Promise<void> {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        PageRouterOptions_serializer.write(thisSerializer, options)
        if (finishCallback !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const finishCallbackTmpValue = finishCallback!
            thisSerializer.holdAndWriteCallback(finishCallbackTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._RouterExtender_pushDynamic0(pageNode, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static pushDynamic1_serialize(pageNode: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback, callback_?: Router_BusinessError_Void): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        PageRouterOptions_serializer.write(thisSerializer, options)
        if (finishCallback !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const finishCallbackTmpValue = finishCallback!
            thisSerializer.holdAndWriteCallback(finishCallbackTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (callback_ !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const callback_TmpValue = callback_!
            thisSerializer.holdAndWriteCallback(callback_TmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RouterExtender_pushDynamic1(pageNode, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static replaceDynamic0_serialize(pageNode: KPointer, options: PageRouterOptions, enterFinishCallback?: RouterFinishCallback): Promise<void> {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        PageRouterOptions_serializer.write(thisSerializer, options)
        if (enterFinishCallback !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const enterFinishCallbackTmpValue = enterFinishCallback!
            thisSerializer.holdAndWriteCallback(enterFinishCallbackTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._RouterExtender_replaceDynamic0(pageNode, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static replaceDynamic1_serialize(pageNode: KPointer, options: PageRouterOptions, finishCallback?: RouterFinishCallback, callback_?: Router_BusinessError_Void): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        PageRouterOptions_serializer.write(thisSerializer, options)
        if (finishCallback !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const finishCallbackTmpValue = finishCallback!
            thisSerializer.holdAndWriteCallback(finishCallbackTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (callback_ !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const callback_TmpValue = callback_!
            thisSerializer.holdAndWriteCallback(callback_TmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RouterExtender_replaceDynamic1(pageNode, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ScreenshotService {
    public static requestScreenshot(target: string, name: string): boolean {
        const target_casted = target as (string)
        const name_casted = name as (string)
        return ScreenshotService.requestScreenshot_serialize(target_casted, name_casted)
    }
    private static requestScreenshot_serialize(target: string, name: string): boolean {
        const retval = ArkUIGeneratedNativeModule._ScreenshotService_requestScreenshot(target, name)
        return retval
    }
}
export class SelectExtender {
    public static setDivider(node: KPointer, options?: DividerOptions): void {
        const node_casted = node as (KPointer)
        const options_casted = options as (DividerOptions | undefined)
        SelectExtender.setDivider_serialize(node_casted, options_casted)
        return
    }
    private static setDivider_serialize(node: KPointer, options?: DividerOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue = options!
            DividerOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SelectExtender_setDivider(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class SliderExtender {
    public static setPrefix(node: KPointer, prefixNode: KPointer, options?: SliderPrefixOptions): void {
        const node_casted = node as (KPointer)
        const prefixNode_casted = prefixNode as (KPointer)
        const options_casted = options as (SliderPrefixOptions | undefined)
        SliderExtender.setPrefix_serialize(node_casted, prefixNode_casted, options_casted)
        return
    }
    public static setSuffix(node: KPointer, suffixNode: KPointer, options?: SliderSuffixOptions): void {
        const node_casted = node as (KPointer)
        const suffixNode_casted = suffixNode as (KPointer)
        const options_casted = options as (SliderSuffixOptions | undefined)
        SliderExtender.setSuffix_serialize(node_casted, suffixNode_casted, options_casted)
        return
    }
    private static setPrefix_serialize(node: KPointer, prefixNode: KPointer, options?: SliderPrefixOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue = options!
            SliderPrefixOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SliderExtender_setPrefix(node, prefixNode, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static setSuffix_serialize(node: KPointer, suffixNode: KPointer, options?: SliderSuffixOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue = options!
            SliderSuffixOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SliderExtender_setSuffix(node, suffixNode, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class StateStylesOps {
    public static onStateStyleChange(node: KPointer, stateStyleChange: Callback_StateStylesChange, allState: int32): void {
        const node_casted = node as (KPointer)
        const stateStyleChange_casted = stateStyleChange as (Callback_StateStylesChange)
        const allState_casted = allState as (int32)
        StateStylesOps.onStateStyleChange_serialize(node_casted, stateStyleChange_casted, allState_casted)
        return
    }
    private static onStateStyleChange_serialize(node: KPointer, stateStyleChange: Callback_StateStylesChange, allState: int32): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(stateStyleChange)
        ArkUIGeneratedNativeModule._StateStylesOps_onStateStyleChange(node, thisSerializer.asBuffer(), thisSerializer.length(), allState)
        thisSerializer.release()
    }
}
export class SystemOps {
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
    public static setFrameCallback(onFrameCallback: Callback_Long_Void, onIdleCallback: Callback_Long_Void, delayTime: int64): void {
        const onFrameCallback_casted = onFrameCallback as (Callback_Long_Void)
        const onIdleCallback_casted = onIdleCallback as (Callback_Long_Void)
        const delayTime_casted = delayTime as (int64)
        SystemOps.setFrameCallback_serialize(onFrameCallback_casted, onIdleCallback_casted, delayTime_casted)
        return
    }
    public static colorMetricsResourceColor(color: global_resource_Resource): Array<number> {
        const color_casted = color as (global_resource_Resource)
        return SystemOps.colorMetricsResourceColor_serialize(color_casted)
    }
    public static blendColorByColorMetrics(color: number, overlayColor: number): Array<number> {
        const color_casted = color as (number)
        const overlayColor_casted = overlayColor as (number)
        return SystemOps.blendColorByColorMetrics_serialize(color_casted, overlayColor_casted)
    }
    public static resourceToLengthMetrics(res: global_resource_Resource): LengthMetricsCustom {
        const res_casted = res as (global_resource_Resource)
        return SystemOps.resourceToLengthMetrics_serialize(res_casted)
    }
    public static createResourceObject(resource: global_resource_Resource): KPointer {
        const resource_casted = resource as (global_resource_Resource)
        return SystemOps.createResourceObject_serialize(resource_casted)
    }
    private static StartFrame_serialize(): KPointer {
        const retval = ArkUIGeneratedNativeModule._SystemOps_StartFrame()
        return retval
    }
    private static EndFrame_serialize(root: KPointer): void {
        ArkUIGeneratedNativeModule._SystemOps_EndFrame(root)
    }
    private static syncInstanceId_serialize(instanceId: int32): void {
        ArkUIGeneratedNativeModule._SystemOps_syncInstanceId(instanceId)
    }
    private static restoreInstanceId_serialize(): void {
        ArkUIGeneratedNativeModule._SystemOps_restoreInstanceId()
    }
    private static getResourceId_serialize(bundleName: string, moduleName: string, params: Array<string>): int32 {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((params.length).toInt())
        for (let paramsCounterI = 0; paramsCounterI < params.length; paramsCounterI++) {
            const paramsTmpElement: string = params[paramsCounterI]
            thisSerializer.writeString(paramsTmpElement)
        }
        const retval = ArkUIGeneratedNativeModule._SystemOps_getResourceId(bundleName, moduleName, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static resourceManagerReset_serialize(): void {
        ArkUIGeneratedNativeModule._SystemOps_resourceManagerReset()
    }
    private static setFrameCallback_serialize(onFrameCallback: Callback_Long_Void, onIdleCallback: Callback_Long_Void, delayTime: int64): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onFrameCallback)
        thisSerializer.holdAndWriteCallback(onIdleCallback)
        ArkUIGeneratedNativeModule._SystemOps_setFrameCallback(thisSerializer.asBuffer(), thisSerializer.length(), delayTime)
        thisSerializer.release()
    }
    private static colorMetricsResourceColor_serialize(color: global_resource_Resource): Array<number> {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        global_resource_Resource_serializer.write(thisSerializer, color)
        const retval = ArkUIGeneratedNativeModule._SystemOps_colorMetricsResourceColor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength: int32 = retvalDeserializer.readInt32()
        let buffer: Array<number> = new Array<number>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = (retvalDeserializer.readNumber() as number)
        }
        const returnResult: Array<number> = buffer
        return returnResult
    }
    private static blendColorByColorMetrics_serialize(color: number, overlayColor: number): Array<number> {
        const retval = ArkUIGeneratedNativeModule._SystemOps_blendColorByColorMetrics(color, overlayColor)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const bufferLength: int32 = retvalDeserializer.readInt32()
        let buffer: Array<number> = new Array<number>(bufferLength)
        for (let bufferBufCounterI = 0; bufferBufCounterI < bufferLength; bufferBufCounterI++) {
            buffer[bufferBufCounterI] = (retvalDeserializer.readNumber() as number)
        }
        const returnResult: Array<number> = buffer
        return returnResult
    }
    private static resourceToLengthMetrics_serialize(res: global_resource_Resource): LengthMetricsCustom {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        global_resource_Resource_serializer.write(thisSerializer, res)
        const retval = ArkUIGeneratedNativeModule._SystemOps_resourceToLengthMetrics(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: LengthMetricsCustom = LengthMetricsCustom_serializer.read(retvalDeserializer)
        return returnResult
    }
    private static createResourceObject_serialize(resource: global_resource_Resource): KPointer {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        global_resource_Resource_serializer.write(thisSerializer, resource)
        const retval = ArkUIGeneratedNativeModule._SystemOps_createResourceObject(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
export class TabsExtender {
    public static ApplyAttributesFinish(node: KPointer): void {
        const node_casted = node as (KPointer)
        TabsExtender.ApplyAttributesFinish_serialize(node_casted)
        return
    }
    private static ApplyAttributesFinish_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._TabsExtender_ApplyAttributesFinish(node)
    }
}
export class ThemeOps {
    public static sendThemeToNative(colorArray: Array<ResourceColor>, darkColorArray: Array<ResourceColor>, elmtId: int32, darkSetStatus: boolean): void {
        const colorArray_casted = colorArray as (Array<ResourceColor>)
        const darkColorArray_casted = darkColorArray as (Array<ResourceColor>)
        const elmtId_casted = elmtId as (int32)
        const darkSetStatus_casted = darkSetStatus as (boolean)
        ThemeOps.sendThemeToNative_serialize(colorArray_casted, darkColorArray_casted, elmtId_casted, darkSetStatus_casted)
        return
    }
    public static setDefaultTheme(colorArray: Array<ResourceColor>, isDark: boolean): void {
        const colorArray_casted = colorArray as (Array<ResourceColor>)
        const isDark_casted = isDark as (boolean)
        ThemeOps.setDefaultTheme_serialize(colorArray_casted, isDark_casted)
        return
    }
    public static createAndBindTheme(themeScopeId: int32, themeId: int32, colorArray: Array<ResourceColor>, darkColorArray: Array<ResourceColor>, colorMode: ThemeColorMode, onThemeScopeDestroy: (() => void), darkSetStatus: boolean): void {
        const themeScopeId_casted = themeScopeId as (int32)
        const themeId_casted = themeId as (int32)
        const colorArray_casted = colorArray as (Array<ResourceColor>)
        const darkColorArray_casted = darkColorArray as (Array<ResourceColor>)
        const colorMode_casted = colorMode as (ThemeColorMode)
        const onThemeScopeDestroy_casted = onThemeScopeDestroy as ((() => void))
        const darkSetStatus_casted = darkSetStatus as (boolean)
        ThemeOps.createAndBindTheme_serialize(themeScopeId_casted, themeId_casted, colorArray_casted, darkColorArray_casted, colorMode_casted, onThemeScopeDestroy_casted, darkSetStatus_casted)
        return
    }
    public static applyThemeScopeIdToNode(ptr: KPointer, themeScopeId: int32): void {
        const ptr_casted = ptr as (KPointer)
        const themeScopeId_casted = themeScopeId as (int32)
        ThemeOps.applyThemeScopeIdToNode_serialize(ptr_casted, themeScopeId_casted)
        return
    }
    private static sendThemeToNative_serialize(colorArray: Array<ResourceColor>, darkColorArray: Array<ResourceColor>, elmtId: int32, darkSetStatus: boolean): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((colorArray.length).toInt())
        for (let colorArrayCounterI = 0; colorArrayCounterI < colorArray.length; colorArrayCounterI++) {
            const colorArrayTmpElement: ResourceColor = colorArray[colorArrayCounterI]
            if (colorArrayTmpElement instanceof arkui_component_enums_Color) {
                thisSerializer.writeInt8((0).toByte())
                const colorArrayTmpElementForIdx0 = colorArrayTmpElement as arkui_component_enums_Color
                thisSerializer.writeInt32((colorArrayTmpElementForIdx0.getOrdinal()) % (12))
            } else if (colorArrayTmpElement instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const colorArrayTmpElementForIdx1 = colorArrayTmpElement as int32
                thisSerializer.writeInt32(colorArrayTmpElementForIdx1)
            } else if (colorArrayTmpElement instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const colorArrayTmpElementForIdx2 = colorArrayTmpElement as string
                thisSerializer.writeString(colorArrayTmpElementForIdx2)
            } else if (colorArrayTmpElement instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((3).toByte())
                const colorArrayTmpElementForIdx3 = colorArrayTmpElement as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, colorArrayTmpElementForIdx3)
            }
        }
        thisSerializer.writeInt32((darkColorArray.length).toInt())
        for (let darkColorArrayCounterI = 0; darkColorArrayCounterI < darkColorArray.length; darkColorArrayCounterI++) {
            const darkColorArrayTmpElement: ResourceColor = darkColorArray[darkColorArrayCounterI]
            if (darkColorArrayTmpElement instanceof arkui_component_enums_Color) {
                thisSerializer.writeInt8((0).toByte())
                const darkColorArrayTmpElementForIdx0 = darkColorArrayTmpElement as arkui_component_enums_Color
                thisSerializer.writeInt32((darkColorArrayTmpElementForIdx0.getOrdinal()) % (12))
            } else if (darkColorArrayTmpElement instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const darkColorArrayTmpElementForIdx1 = darkColorArrayTmpElement as int32
                thisSerializer.writeInt32(darkColorArrayTmpElementForIdx1)
            } else if (darkColorArrayTmpElement instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const darkColorArrayTmpElementForIdx2 = darkColorArrayTmpElement as string
                thisSerializer.writeString(darkColorArrayTmpElementForIdx2)
            } else if (darkColorArrayTmpElement instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((3).toByte())
                const darkColorArrayTmpElementForIdx3 = darkColorArrayTmpElement as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, darkColorArrayTmpElementForIdx3)
            }
        }
        ArkUIGeneratedNativeModule._ThemeOps_sendThemeToNative(thisSerializer.asBuffer(), thisSerializer.length(), elmtId, darkSetStatus ? true : false)
        thisSerializer.release()
    }
    private static setDefaultTheme_serialize(colorArray: Array<ResourceColor>, isDark: boolean): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((colorArray.length).toInt())
        for (let colorArrayCounterI = 0; colorArrayCounterI < colorArray.length; colorArrayCounterI++) {
            const colorArrayTmpElement: ResourceColor = colorArray[colorArrayCounterI]
            if (colorArrayTmpElement instanceof arkui_component_enums_Color) {
                thisSerializer.writeInt8((0).toByte())
                const colorArrayTmpElementForIdx0 = colorArrayTmpElement as arkui_component_enums_Color
                thisSerializer.writeInt32((colorArrayTmpElementForIdx0.getOrdinal()) % (12))
            } else if (colorArrayTmpElement instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const colorArrayTmpElementForIdx1 = colorArrayTmpElement as int32
                thisSerializer.writeInt32(colorArrayTmpElementForIdx1)
            } else if (colorArrayTmpElement instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const colorArrayTmpElementForIdx2 = colorArrayTmpElement as string
                thisSerializer.writeString(colorArrayTmpElementForIdx2)
            } else if (colorArrayTmpElement instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((3).toByte())
                const colorArrayTmpElementForIdx3 = colorArrayTmpElement as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, colorArrayTmpElementForIdx3)
            }
        }
        ArkUIGeneratedNativeModule._ThemeOps_setDefaultTheme(thisSerializer.asBuffer(), thisSerializer.length(), isDark ? true : false)
        thisSerializer.release()
    }
    private static createAndBindTheme_serialize(themeScopeId: int32, themeId: int32, colorArray: Array<ResourceColor>, darkColorArray: Array<ResourceColor>, colorMode: ThemeColorMode, onThemeScopeDestroy: (() => void), darkSetStatus: boolean): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((colorArray.length).toInt())
        for (let colorArrayCounterI = 0; colorArrayCounterI < colorArray.length; colorArrayCounterI++) {
            const colorArrayTmpElement: ResourceColor = colorArray[colorArrayCounterI]
            if (colorArrayTmpElement instanceof arkui_component_enums_Color) {
                thisSerializer.writeInt8((0).toByte())
                const colorArrayTmpElementForIdx0 = colorArrayTmpElement as arkui_component_enums_Color
                thisSerializer.writeInt32((colorArrayTmpElementForIdx0.getOrdinal()) % (12))
            } else if (colorArrayTmpElement instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const colorArrayTmpElementForIdx1 = colorArrayTmpElement as int32
                thisSerializer.writeInt32(colorArrayTmpElementForIdx1)
            } else if (colorArrayTmpElement instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const colorArrayTmpElementForIdx2 = colorArrayTmpElement as string
                thisSerializer.writeString(colorArrayTmpElementForIdx2)
            } else if (colorArrayTmpElement instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((3).toByte())
                const colorArrayTmpElementForIdx3 = colorArrayTmpElement as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, colorArrayTmpElementForIdx3)
            }
        }
        thisSerializer.writeInt32((darkColorArray.length).toInt())
        for (let darkColorArrayCounterI = 0; darkColorArrayCounterI < darkColorArray.length; darkColorArrayCounterI++) {
            const darkColorArrayTmpElement: ResourceColor = darkColorArray[darkColorArrayCounterI]
            if (darkColorArrayTmpElement instanceof arkui_component_enums_Color) {
                thisSerializer.writeInt8((0).toByte())
                const darkColorArrayTmpElementForIdx0 = darkColorArrayTmpElement as arkui_component_enums_Color
                thisSerializer.writeInt32((darkColorArrayTmpElementForIdx0.getOrdinal()) % (12))
            } else if (darkColorArrayTmpElement instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const darkColorArrayTmpElementForIdx1 = darkColorArrayTmpElement as int32
                thisSerializer.writeInt32(darkColorArrayTmpElementForIdx1)
            } else if (darkColorArrayTmpElement instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const darkColorArrayTmpElementForIdx2 = darkColorArrayTmpElement as string
                thisSerializer.writeString(darkColorArrayTmpElementForIdx2)
            } else if (darkColorArrayTmpElement instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((3).toByte())
                const darkColorArrayTmpElementForIdx3 = darkColorArrayTmpElement as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, darkColorArrayTmpElementForIdx3)
            }
        }
        thisSerializer.holdAndWriteCallback(onThemeScopeDestroy)
        ArkUIGeneratedNativeModule._ThemeOps_createAndBindTheme(themeScopeId, themeId, thisSerializer.asBuffer(), thisSerializer.length(), colorMode.valueOf(), darkSetStatus ? true : false)
        thisSerializer.release()
    }
    private static applyThemeScopeIdToNode_serialize(ptr: KPointer, themeScopeId: int32): void {
        ArkUIGeneratedNativeModule._ThemeOps_applyThemeScopeIdToNode(ptr, themeScopeId)
    }
}
export class ToggleExtender {
    public static constructButton(id: int32, flags: int32): KPointer {
        const id_casted = id as (int32)
        const flags_casted = flags as (int32)
        return ToggleExtender.constructButton_serialize(id_casted, flags_casted)
    }
    public static constructCheckbox(id: int32, flags: int32): KPointer {
        const id_casted = id as (int32)
        const flags_casted = flags as (int32)
        return ToggleExtender.constructCheckbox_serialize(id_casted, flags_casted)
    }
    private static constructButton_serialize(id: int32, flags: int32): KPointer {
        const retval = ArkUIGeneratedNativeModule._ToggleExtender_constructButton(id, flags)
        return retval
    }
    private static constructCheckbox_serialize(id: int32, flags: int32): KPointer {
        const retval = ArkUIGeneratedNativeModule._ToggleExtender_constructCheckbox(id, flags)
        return retval
    }
}
export class UIContextAtomicServiceBar {
    public static getBarRect(): Frame {
        return UIContextAtomicServiceBar.getBarRect_serialize()
    }
    private static getBarRect_serialize(): Frame {
        const retval = ArkUIGeneratedNativeModule._UIContextAtomicServiceBar_getBarRect()
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult: Frame = Frame_serializer.read(retvalDeserializer)
        return returnResult
    }
}
export class UIContextGetInfo {
    public static getNavigationInfoByUniqueId(id: int64): uiObserver.NavigationInfo | undefined {
        const id_casted = id as (int64)
        return UIContextGetInfo.getNavigationInfoByUniqueId_serialize(id_casted)
    }
    public static enableSwipeBack(enabled: boolean | undefined): void {
        const enabled_casted = enabled as (boolean | undefined)
        UIContextGetInfo.enableSwipeBack_serialize(enabled_casted)
        return
    }
    private static getNavigationInfoByUniqueId_serialize(id: int64): uiObserver.NavigationInfo | undefined {
        const retval = ArkUIGeneratedNativeModule._UIContextGetInfo_getNavigationInfoByUniqueId(id)
        let retvalDeserializer: DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType = retvalDeserializer.readInt8()!.toInt()
        let buffer: uiObserver.NavigationInfo | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = uiObserver_NavigationInfo_serializer.read(retvalDeserializer)
        }
        const returnResult: uiObserver.NavigationInfo | undefined = buffer
        return returnResult
    }
    private static enableSwipeBack_serialize(enabled: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (enabled !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const enabledTmpValue = enabled!
            thisSerializer.writeBoolean(enabledTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._UIContextGetInfo_enableSwipeBack(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class UIEventHelper {
    public static constructGridEvent(node: KPointer): UIGridEvent {
        const node_casted = node as (KPointer)
        return UIEventHelper.constructGridEvent_serialize(node_casted)
    }
    public static constructListEvent(node: KPointer): UIListEvent {
        const node_casted = node as (KPointer)
        return UIEventHelper.constructListEvent_serialize(node_casted)
    }
    public static constructScrollableCommonEvent(node: KPointer): UIScrollableCommonEvent {
        const node_casted = node as (KPointer)
        return UIEventHelper.constructScrollableCommonEvent_serialize(node_casted)
    }
    public static constructScrollEvent(node: KPointer): UIScrollEvent {
        const node_casted = node as (KPointer)
        return UIEventHelper.constructScrollEvent_serialize(node_casted)
    }
    public static constructWaterFlowEvent(node: KPointer): UIWaterFlowEvent {
        const node_casted = node as (KPointer)
        return UIEventHelper.constructWaterFlowEvent_serialize(node_casted)
    }
    private static constructGridEvent_serialize(node: KPointer): UIGridEvent {
        const retval = ArkUIGeneratedNativeModule._UIEventHelper_constructGridEvent(node)
        const obj: UIGridEvent = UIGridEventInternal.fromPtr(retval)
        return obj
    }
    private static constructListEvent_serialize(node: KPointer): UIListEvent {
        const retval = ArkUIGeneratedNativeModule._UIEventHelper_constructListEvent(node)
        const obj: UIListEvent = UIListEventInternal.fromPtr(retval)
        return obj
    }
    private static constructScrollableCommonEvent_serialize(node: KPointer): UIScrollableCommonEvent {
        const retval = ArkUIGeneratedNativeModule._UIEventHelper_constructScrollableCommonEvent(node)
        const obj: UIScrollableCommonEvent = UIScrollableCommonEventInternal.fromPtr(retval)
        return obj
    }
    private static constructScrollEvent_serialize(node: KPointer): UIScrollEvent {
        const retval = ArkUIGeneratedNativeModule._UIEventHelper_constructScrollEvent(node)
        const obj: UIScrollEvent = UIScrollEventInternal.fromPtr(retval)
        return obj
    }
    private static constructWaterFlowEvent_serialize(node: KPointer): UIWaterFlowEvent {
        const retval = ArkUIGeneratedNativeModule._UIEventHelper_constructWaterFlowEvent(node)
        const obj: UIWaterFlowEvent = UIWaterFlowEventInternal.fromPtr(retval)
        return obj
    }
}
export class UIObserverGestureEventOps {
    public static setOnBeforePanStart(instanceId: int32, callback: ((event: GestureEvent,current: GestureRecognizer,node?: FrameNode) => void)): int32 {
        const instanceId_casted = instanceId as (int32)
        const callback_casted = callback as (((event: GestureEvent,current: GestureRecognizer,node?: FrameNode) => void))
        return UIObserverGestureEventOps.setOnBeforePanStart_serialize(instanceId_casted, callback_casted)
    }
    public static setOnBeforePanEnd(instanceId: int32, callback: ((event: GestureEvent,current: GestureRecognizer,node?: FrameNode) => void)): int32 {
        const instanceId_casted = instanceId as (int32)
        const callback_casted = callback as (((event: GestureEvent,current: GestureRecognizer,node?: FrameNode) => void))
        return UIObserverGestureEventOps.setOnBeforePanEnd_serialize(instanceId_casted, callback_casted)
    }
    public static setOnAfterPanStart(instanceId: int32, callback: ((event: GestureEvent,current: GestureRecognizer,node?: FrameNode) => void)): int32 {
        const instanceId_casted = instanceId as (int32)
        const callback_casted = callback as (((event: GestureEvent,current: GestureRecognizer,node?: FrameNode) => void))
        return UIObserverGestureEventOps.setOnAfterPanStart_serialize(instanceId_casted, callback_casted)
    }
    public static setOnAfterPanEnd(instanceId: int32, callback: ((event: GestureEvent,current: GestureRecognizer,node?: FrameNode) => void)): int32 {
        const instanceId_casted = instanceId as (int32)
        const callback_casted = callback as (((event: GestureEvent,current: GestureRecognizer,node?: FrameNode) => void))
        return UIObserverGestureEventOps.setOnAfterPanEnd_serialize(instanceId_casted, callback_casted)
    }
    public static setOnWillClick(instanceId: int32, callback: ((event: ClickEvent,node?: FrameNode) => void)): int32 {
        const instanceId_casted = instanceId as (int32)
        const callback_casted = callback as (((event: ClickEvent,node?: FrameNode) => void))
        return UIObserverGestureEventOps.setOnWillClick_serialize(instanceId_casted, callback_casted)
    }
    public static setOnDidClick(instanceId: int32, callback: ((event: ClickEvent,node?: FrameNode) => void)): int32 {
        const instanceId_casted = instanceId as (int32)
        const callback_casted = callback as (((event: ClickEvent,node?: FrameNode) => void))
        return UIObserverGestureEventOps.setOnDidClick_serialize(instanceId_casted, callback_casted)
    }
    public static setOnWillTap(instanceId: int32, callback: ((event: GestureEvent,node?: FrameNode) => void)): int32 {
        const instanceId_casted = instanceId as (int32)
        const callback_casted = callback as (((event: GestureEvent,node?: FrameNode) => void))
        return UIObserverGestureEventOps.setOnWillTap_serialize(instanceId_casted, callback_casted)
    }
    public static setOnDidTap(instanceId: int32, callback: ((event: GestureEvent,node?: FrameNode) => void)): int32 {
        const instanceId_casted = instanceId as (int32)
        const callback_casted = callback as (((event: GestureEvent,node?: FrameNode) => void))
        return UIObserverGestureEventOps.setOnDidTap_serialize(instanceId_casted, callback_casted)
    }
    public static addGlobalGestureListener(type: GestureListenerType, option: InnerGestureObserverConfigs, callback: ((info: InnerGestureTriggerInfo,frameNode?: FrameNode) => void)): int32 {
        const type_casted = type as (GestureListenerType)
        const option_casted = option as (InnerGestureObserverConfigs)
        const callback_casted = callback as (((info: InnerGestureTriggerInfo,frameNode?: FrameNode) => void))
        return UIObserverGestureEventOps.addGlobalGestureListener_serialize(type_casted, option_casted, callback_casted)
    }
    private static setOnBeforePanStart_serialize(instanceId: int32, callback: ((event: GestureEvent,current: GestureRecognizer,node?: FrameNode) => void)): int32 {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback)
        const retval = ArkUIGeneratedNativeModule._UIObserverGestureEventOps_setOnBeforePanStart(instanceId, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static setOnBeforePanEnd_serialize(instanceId: int32, callback: ((event: GestureEvent,current: GestureRecognizer,node?: FrameNode) => void)): int32 {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback)
        const retval = ArkUIGeneratedNativeModule._UIObserverGestureEventOps_setOnBeforePanEnd(instanceId, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static setOnAfterPanStart_serialize(instanceId: int32, callback: ((event: GestureEvent,current: GestureRecognizer,node?: FrameNode) => void)): int32 {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback)
        const retval = ArkUIGeneratedNativeModule._UIObserverGestureEventOps_setOnAfterPanStart(instanceId, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static setOnAfterPanEnd_serialize(instanceId: int32, callback: ((event: GestureEvent,current: GestureRecognizer,node?: FrameNode) => void)): int32 {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback)
        const retval = ArkUIGeneratedNativeModule._UIObserverGestureEventOps_setOnAfterPanEnd(instanceId, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static setOnWillClick_serialize(instanceId: int32, callback: ((event: ClickEvent,node?: FrameNode) => void)): int32 {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback)
        const retval = ArkUIGeneratedNativeModule._UIObserverGestureEventOps_setOnWillClick(instanceId, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static setOnDidClick_serialize(instanceId: int32, callback: ((event: ClickEvent,node?: FrameNode) => void)): int32 {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback)
        const retval = ArkUIGeneratedNativeModule._UIObserverGestureEventOps_setOnDidClick(instanceId, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static setOnWillTap_serialize(instanceId: int32, callback: ((event: GestureEvent,node?: FrameNode) => void)): int32 {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback)
        const retval = ArkUIGeneratedNativeModule._UIObserverGestureEventOps_setOnWillTap(instanceId, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static setOnDidTap_serialize(instanceId: int32, callback: ((event: GestureEvent,node?: FrameNode) => void)): int32 {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback)
        const retval = ArkUIGeneratedNativeModule._UIObserverGestureEventOps_setOnDidTap(instanceId, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static addGlobalGestureListener_serialize(type: GestureListenerType, option: InnerGestureObserverConfigs, callback: ((info: InnerGestureTriggerInfo,frameNode?: FrameNode) => void)): int32 {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        InnerGestureObserverConfigs_serializer.write(thisSerializer, option)
        thisSerializer.holdAndWriteCallback(callback)
        const retval = ArkUIGeneratedNativeModule._UIObserverGestureEventOps_addGlobalGestureListener(type.valueOf(), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
export class XComponentControllerExtender {
    public static startImageAnalyzer(peer: XComponentController, config: ImageAnalyzerConfig): Promise<void> {
        const peer_casted = peer as (XComponentController)
        const config_casted = config as (ImageAnalyzerConfig)
        return XComponentControllerExtender.startImageAnalyzer_serialize(peer_casted, config_casted)
    }
    private static startImageAnalyzer_serialize(peer: XComponentController, config: ImageAnalyzerConfig): Promise<void> {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        ImageAnalyzerConfig_serializer.write(thisSerializer, config)
        const retval = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._XComponentControllerExtender_startImageAnalyzer(toPeerPtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
export class ArkRootPeer extends PeerNode {
    attributeSet?: RootModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRootPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._Root_construct(peerId, flags)
        const _peer = new ArkRootPeer(_peerPtr, peerId, 'Root', flags)
        component?.setPeer(_peer)
        return _peer
    }
}
export class ArkComponentRootPeer extends PeerNode {
    attributeSet?: ComponentRootModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkComponentRootPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._ComponentRoot_construct(peerId, flags)
        const _peer = new ArkComponentRootPeer(_peerPtr, peerId, 'ComponentRoot', flags)
        component?.setPeer(_peer)
        return _peer
    }
}
export class ArkCustomBuilderRootPeer extends PeerNode {
    attributeSet?: CustomBuilderRootModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkCustomBuilderRootPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._CustomBuilderRoot_construct(peerId, flags)
        const _peer = new ArkCustomBuilderRootPeer(_peerPtr, peerId, 'CustomBuilderRoot', flags)
        component?.setPeer(_peer)
        return _peer
    }
}
export class ArkCustomLayoutRootPeer extends PeerNode {
    attributeSet?: CustomLayoutRootModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkCustomLayoutRootPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._CustomLayoutRoot_construct(peerId, flags)
        const _peer = new ArkCustomLayoutRootPeer(_peerPtr, peerId, 'CustomLayoutRoot', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSubscribeOnMeasureSizeAttribute(value: Callback_onMeasureSize_SizeResult): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CustomLayoutRoot_setSubscribeOnMeasureSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSubscribeOnPlaceChildrenAttribute(value: Callback_onPlaceChildren_Void): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CustomLayoutRoot_setSubscribeOnPlaceChildren(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type Callback_Extender_OnProgress = (value: float) => void;
export type Callback_Extender_OnFinish = () => void;
export interface DoubleAnimationParam {
    propertyName: string;
    startValue: float;
    endValue: float;
    duration: int32;
    delay: int32;
    curve: Curve | string | ICurve;
    onProgress?: Callback_Extender_OnProgress;
    onFinish?: Callback_Extender_OnFinish;
}
export type Callback_I32_Void = (index: int32) => void;
export interface ArcDotIndicatorInner {
    _arcDirection?: ArcDirectionInner;
    _itemColor?: ResourceColor;
    _selectedItemColor?: ResourceColor;
    _backgroundColor?: ResourceColor;
    _maskColor?: LinearGradient;
}
export enum ArcDirectionInner {
    THREE_CLOCK_DIRECTION = 0,
    SIX_CLOCK_DIRECTION = 1,
    NINE_CLOCK_DIRECTION = 2
}
export type AnimationStartHandler = (index: int32, targetIndex: int32, extraInfo: SwiperAnimationEvent) => void;
export type AnimationEndHandler = (index: int32, extraInfo: SwiperAnimationEvent) => void;
export type GestureSwipeHandler = (index: int32, extraInfo: SwiperAnimationEvent) => void;
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
    keyboardAvoidMode?: arkui_component_common_KeyboardAvoidMode;
    enableHoverMode?: boolean;
    hoverModeArea?: HoverModeAreaType;
    onDidAppear?: (() => void);
    onDidDisappear?: (() => void);
    onWillAppear?: (() => void);
    onWillDisappear?: (() => void);
    keyboardAvoidDistance?: arkui_Graphics_LengthMetrics;
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
export class LengthMetricsCustom {
    unit: number = initializers.arkui.component.idlize.LengthMetricsCustomNS.unit;
    value: number = initializers.arkui.component.idlize.LengthMetricsCustomNS.value;
}
export type Callback_Long_Void = (value: int64) => void;
export type GestureEventHandler = (event: GestureEvent) => void;
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
export class BuilderNodeOptions {
    selfIdealSize?: Size;
    type?: number;
    surfaceId?: string;
}
export type InputEventType = TouchEvent | MouseEvent | AxisEvent;
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
export interface BusinessErrorInterface<T> {
    name: string;
    message: string;
    stack?: string;
    code: int32;
    data: T;
}
export type PageMapNodeBuilder = (parentNode: KPointer, name: string, param: Object | null | undefined) => KPointer;
export class InnerGestureTriggerInfo {
    event: GestureEvent = initializers.arkui.component.idlize.InnerGestureTriggerInfoNS.event;
    current: GestureRecognizer = initializers.arkui.component.idlize.InnerGestureTriggerInfoNS.current;
    currentPhase: GestureActionPhase = initializers.arkui.component.idlize.InnerGestureTriggerInfoNS.currentPhase;
}
export class InnerGestureObserverConfigs {
    actionPhases: Array<GestureActionPhase> = initializers.arkui.component.idlize.InnerGestureObserverConfigsNS.actionPhases;
}
export class ColorMetricsExt {
    red: int32 = initializers.arkui.component.idlize.ColorMetricsExtNS.red;
    green: int32 = initializers.arkui.component.idlize.ColorMetricsExtNS.green;
    blue: int32 = initializers.arkui.component.idlize.ColorMetricsExtNS.blue;
    alpha: int32 = initializers.arkui.component.idlize.ColorMetricsExtNS.alpha;
    colorSpace: ColorSpace = initializers.arkui.component.idlize.ColorMetricsExtNS.colorSpace;
    resourceId: int32 = initializers.arkui.component.idlize.ColorMetricsExtNS.resourceId;
}
export type CustomNodeBuilder = (parentNode: KPointer) => KPointer;
export type CustomNodeBuilderT<T> = (parentNode: KPointer, t: T) => KPointer;
export interface NodeEdgesLengthMetrics {
    top: arkui_Graphics_LengthMetrics | undefined;
    left: arkui_Graphics_LengthMetrics | undefined;
    bottom: arkui_Graphics_LengthMetrics | undefined;
    right: arkui_Graphics_LengthMetrics | undefined;
}
export interface SizeTLengthMetrics {
    width: arkui_Graphics_LengthMetrics;
    height: arkui_Graphics_LengthMetrics;
}
export type NavExtender_OnUpdateStack = () => void;
export type NavExtender_PageMapNodeBuilder = (url: string, params?: Object) => KPointer;
export interface SizeNumberInner {
    width: number;
    height: number;
}
export interface SizeF64Inner {
    width: double;
    height: double;
}
export interface PositionNumberInner {
    x: number;
    y: number;
}
export interface PositionF64Inner {
    x: double;
    y: double;
}
export interface PositionLengthMetricsInner {
    x: arkui_Graphics_LengthMetrics;
    y: arkui_Graphics_LengthMetrics;
}
export interface Vector2F64 {
    x: double;
    y: double;
}
export interface ParticlePropertyAnimationNumberInner {
    from: number;
    to: number;
    startMillis: int32;
    endMillis: int32;
    curve?: Curve | ICurve;
}
export interface ParticlePropertyAnimationColorInner {
    from: ResourceColor;
    to: ResourceColor;
    startMillis: int32;
    endMillis: int32;
    curve?: Curve | ICurve;
}
export type ParticlePropertyUpdaterConfigsInner = [ double, double ] | Array<ParticlePropertyAnimationNumberInner> | undefined;
export interface ParticleUpdaterOptionsInner {
    type: ParticleUpdater;
    config: ParticlePropertyUpdaterConfigsInner;
}
export interface ParticlePropertyOptionsInner {
    range: [ double, double ];
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
    outerRadius: arkui_Graphics_LengthMetrics;
    innerRadius: arkui_Graphics_LengthMetrics;
    startAngle?: double;
    endAngle?: double;
}
export interface EmitterPropertyInner {
    index: int32;
    emitRate?: int32;
    position?: PositionF64Inner;
    size?: SizeF64Inner;
    annulusRegion?: ParticleAnnulusRegionInner;
}
export interface EmitterOptionsInner {
    particle: EmitterParticleOptions;
    emitRate?: int32;
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
    strength?: double;
    shape?: DisturbanceFieldShape;
    size?: SizeF64Inner;
    position?: PositionF64Inner;
    feather?: int32;
    noiseScale?: double;
    noiseFrequency?: double;
    noiseAmplitude?: double;
}
export interface FieldRegionInner {
    shape?: DisturbanceFieldShape;
    position?: PositionF64Inner;
    size?: SizeF64Inner;
}
export interface RippleFieldOptionsInner {
    amplitude?: double;
    wavelength?: double;
    waveSpeed?: double;
    attenuation?: double;
    center?: PositionF64Inner;
    region?: FieldRegionInner;
}
export interface VelocityFieldOptionsInner {
    velocity?: Vector2F64;
    region?: FieldRegionInner;
}
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
export interface EdgeF64 {
    top: double;
    right: double;
    bottom: double;
    left: double;
}
export interface EdgeI32 {
    top: int32;
    right: int32;
    bottom: int32;
    left: int32;
}
export type RouterFinishCallback = (value: KPointer) => void;
export interface RouterOptionsInner {
    url: string;
    params?: string;
    recoverable?: boolean;
}
export interface RouterStateInner {
    index: int32;
    name: string;
    path: string;
    params: string;
}
export interface PageRouterOptions {
    options: RouterOptionsInner;
    mode?: router.RouterMode;
}
export type Router_BusinessError_Void = (code: int32, message: string) => void;
export interface Root {
    attributeModifier(value: AttributeModifier<Root> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}
export interface ComponentRoot {
    attributeModifier(value: AttributeModifier<ComponentRoot> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}
export interface CustomBuilderRoot {
    attributeModifier(value: AttributeModifier<CustomBuilderRoot> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}
export type Callback_onMeasureSize_SizeResult = (selfLayoutInfo: GeometryInfo, children: Array<Measurable>, constraint: ConstraintSizeOptions) => SizeResult;
export type Callback_onPlaceChildren_Void = (selfLayoutInfo: GeometryInfo, children: Array<Layoutable>, constraint: ConstraintSizeOptions) => void;
export interface CustomLayoutRoot {
    subscribeOnMeasureSize(value: Callback_onMeasureSize_SizeResult): this {
        throw new Error('Unimplemented method subscribeOnMeasureSize')
    }
    subscribeOnPlaceChildren(value: Callback_onPlaceChildren_Void): this {
        throw new Error('Unimplemented method subscribeOnPlaceChildren')
    }
    attributeModifier(value: AttributeModifier<CustomLayoutRoot> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}
export interface TransformationMatrix {
    matrix4x4: Array<number>;
}
export interface WaterFlowSectionsInterface {
    ptr: KPointer;
}
export class ArkRootComponent extends ComponentBase implements Root {
    getPeer(): ArkRootPeer {
        return (this.peer as ArkRootPeer)
    }
    public attributeModifier(value: AttributeModifier<Root> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookRootAttributeModifier(this, value);
        })
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}
export class ArkComponentRootComponent extends ComponentBase implements ComponentRoot {
    getPeer(): ArkComponentRootPeer {
        return (this.peer as ArkComponentRootPeer)
    }
    public attributeModifier(value: AttributeModifier<ComponentRoot> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookComponentRootAttributeModifier(this, value);
        })
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}
export class ArkCustomBuilderRootComponent extends ComponentBase implements CustomBuilderRoot {
    getPeer(): ArkCustomBuilderRootPeer {
        return (this.peer as ArkCustomBuilderRootPeer)
    }
    public attributeModifier(value: AttributeModifier<CustomBuilderRoot> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookCustomBuilderRootAttributeModifier(this, value);
        })
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}
export class ArkCustomLayoutRootComponent extends ComponentBase implements CustomLayoutRoot {
    getPeer(): ArkCustomLayoutRootPeer {
        return (this.peer as ArkCustomLayoutRootPeer)
    }
    public subscribeOnMeasureSize(value: Callback_onMeasureSize_SizeResult): this {
        const value_casted = value as (Callback_onMeasureSize_SizeResult)
        this.getPeer()?.setSubscribeOnMeasureSizeAttribute(value_casted)
        return this
    }
    public subscribeOnPlaceChildren(value: Callback_onPlaceChildren_Void): this {
        const value_casted = value as (Callback_onPlaceChildren_Void)
        this.getPeer()?.setSubscribeOnPlaceChildrenAttribute(value_casted)
        return this
    }
    public attributeModifier(value: AttributeModifier<CustomLayoutRoot> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookCustomLayoutRootAttributeModifier(this, value);
        })
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}
export function getRectangleById(id: string): ComponentInfo {
    return GlobalScope.getRectangleById(id)
}
export class ArcSwiperControllerHelper_serializer {
    public static write(buffer: SerializerBase, value: ArcSwiperControllerHelper): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): ArcSwiperControllerHelper {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return ArcSwiperControllerHelperInternal.fromPtr(ptr)
    }
}
export class arkui_component_idlize_BaseShape_serializer {
    public static write(buffer: SerializerBase, value: BaseShape): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): BaseShape {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return BaseShapeInternal.fromPtr(ptr)
    }
}
export class BuilderNodeOps_serializer {
    public static write(buffer: SerializerBase, value: BuilderNodeOps): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): BuilderNodeOps {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return BuilderNodeOpsInternal.fromPtr(ptr)
    }
}
export class CommonShape_serializer {
    public static write(buffer: SerializerBase, value: CommonShape): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): CommonShape {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return CommonShapeInternal.fromPtr(ptr)
    }
}
export class CustomDialogControllerExtender_serializer {
    public static write(buffer: SerializerBase, value: CustomDialogControllerExtender): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): CustomDialogControllerExtender {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return CustomDialogControllerExtenderInternal.fromPtr(ptr)
    }
}
export class InnerGestureTriggerInfo_serializer {
    public static write(buffer: SerializerBase, value: InnerGestureTriggerInfo): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForEvent = value.event
        GestureEvent_serializer.write(valueSerializer, valueHolderForEvent)
        const valueHolderForCurrent = value.current
        GestureRecognizer_serializer.write(valueSerializer, valueHolderForCurrent)
        const valueHolderForCurrentPhase = value.currentPhase
        valueSerializer.writeInt32(valueHolderForCurrentPhase.valueOf())
    }
    public static read(buffer: DeserializerBase): InnerGestureTriggerInfo {
        let valueDeserializer: DeserializerBase = buffer
        const eventTmpResult: GestureEvent = (GestureEvent_serializer.read(valueDeserializer) as GestureEvent)
        const currentTmpResult: GestureRecognizer = (GestureRecognizer_serializer.read(valueDeserializer) as GestureRecognizer)
        const currentPhaseTmpResult: GestureActionPhase = GestureActionPhase.fromValue(valueDeserializer.readInt32())
        let value: InnerGestureTriggerInfo = ({event: eventTmpResult, current: currentTmpResult, currentPhase: currentPhaseTmpResult} as InnerGestureTriggerInfo)
        return value
    }
}
export class LevelOrderExtender_serializer {
    public static write(buffer: SerializerBase, value: LevelOrderExtender): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): LevelOrderExtender {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return LevelOrderExtenderInternal.fromPtr(ptr)
    }
}
export class NodeEdgeStyles_serializer {
    public static write(buffer: SerializerBase, value: NodeEdgeStyles): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForTop = value.top
        valueSerializer.writeInt32(valueHolderForTop.valueOf())
        const valueHolderForRight = value.right
        valueSerializer.writeInt32(valueHolderForRight.valueOf())
        const valueHolderForBottom = value.bottom
        valueSerializer.writeInt32(valueHolderForBottom.valueOf())
        const valueHolderForLeft = value.left
        valueSerializer.writeInt32(valueHolderForLeft.valueOf())
    }
    public static read(buffer: DeserializerBase): NodeEdgeStyles {
        let valueDeserializer: DeserializerBase = buffer
        const topTmpResult: BorderStyle = BorderStyle.fromValue(valueDeserializer.readInt32())
        const rightTmpResult: BorderStyle = BorderStyle.fromValue(valueDeserializer.readInt32())
        const bottomTmpResult: BorderStyle = BorderStyle.fromValue(valueDeserializer.readInt32())
        const leftTmpResult: BorderStyle = BorderStyle.fromValue(valueDeserializer.readInt32())
        let value: NodeEdgeStyles = ({top: topTmpResult, right: rightTmpResult, bottom: bottomTmpResult, left: leftTmpResult} as NodeEdgeStyles)
        return value
    }
}
export class Offset_componentutils_serializer {
    public static write(buffer: SerializerBase, value: Offset_componentutils): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForX = value.x
        valueSerializer.writeNumber(valueHolderForX)
        const valueHolderForY = value.y
        valueSerializer.writeNumber(valueHolderForY)
    }
    public static read(buffer: DeserializerBase): Offset_componentutils {
        let valueDeserializer: DeserializerBase = buffer
        const xTmpResult: number = (valueDeserializer.readNumber() as number)
        const yTmpResult: number = (valueDeserializer.readNumber() as number)
        let value: Offset_componentutils = ({x: xTmpResult, y: yTmpResult} as Offset_componentutils)
        return value
    }
}
export class PositionF64Inner_serializer {
    public static write(buffer: SerializerBase, value: PositionF64Inner): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForX = value.x
        valueSerializer.writeFloat64(valueHolderForX)
        const valueHolderForY = value.y
        valueSerializer.writeFloat64(valueHolderForY)
    }
    public static read(buffer: DeserializerBase): PositionF64Inner {
        let valueDeserializer: DeserializerBase = buffer
        const xTmpResult: double = valueDeserializer.readFloat64()
        const yTmpResult: double = valueDeserializer.readFloat64()
        let value: PositionF64Inner = ({x: xTmpResult, y: yTmpResult} as PositionF64Inner)
        return value
    }
}
export class RestrictedWorker_serializer {
    public static write(buffer: SerializerBase, value: RestrictedWorker): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): RestrictedWorker {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return RestrictedWorkerInternal.fromPtr(ptr)
    }
}
export class RotateResult_serializer {
    public static write(buffer: SerializerBase, value: RotateResult): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForX = value.x
        valueSerializer.writeNumber(valueHolderForX)
        const valueHolderForY = value.y
        valueSerializer.writeNumber(valueHolderForY)
        const valueHolderForZ = value.z
        valueSerializer.writeNumber(valueHolderForZ)
        const valueHolderForCenterX = value.centerX
        valueSerializer.writeNumber(valueHolderForCenterX)
        const valueHolderForCenterY = value.centerY
        valueSerializer.writeNumber(valueHolderForCenterY)
        const valueHolderForAngle = value.angle
        valueSerializer.writeNumber(valueHolderForAngle)
    }
    public static read(buffer: DeserializerBase): RotateResult {
        let valueDeserializer: DeserializerBase = buffer
        const xTmpResult: number = (valueDeserializer.readNumber() as number)
        const yTmpResult: number = (valueDeserializer.readNumber() as number)
        const zTmpResult: number = (valueDeserializer.readNumber() as number)
        const centerXTmpResult: number = (valueDeserializer.readNumber() as number)
        const centerYTmpResult: number = (valueDeserializer.readNumber() as number)
        const angleTmpResult: number = (valueDeserializer.readNumber() as number)
        let value: RotateResult = ({x: xTmpResult, y: yTmpResult, z: zTmpResult, centerX: centerXTmpResult, centerY: centerYTmpResult, angle: angleTmpResult} as RotateResult)
        return value
    }
}
export class ScaleResult_serializer {
    public static write(buffer: SerializerBase, value: ScaleResult): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForX = value.x
        valueSerializer.writeNumber(valueHolderForX)
        const valueHolderForY = value.y
        valueSerializer.writeNumber(valueHolderForY)
        const valueHolderForZ = value.z
        valueSerializer.writeNumber(valueHolderForZ)
        const valueHolderForCenterX = value.centerX
        valueSerializer.writeNumber(valueHolderForCenterX)
        const valueHolderForCenterY = value.centerY
        valueSerializer.writeNumber(valueHolderForCenterY)
    }
    public static read(buffer: DeserializerBase): ScaleResult {
        let valueDeserializer: DeserializerBase = buffer
        const xTmpResult: number = (valueDeserializer.readNumber() as number)
        const yTmpResult: number = (valueDeserializer.readNumber() as number)
        const zTmpResult: number = (valueDeserializer.readNumber() as number)
        const centerXTmpResult: number = (valueDeserializer.readNumber() as number)
        const centerYTmpResult: number = (valueDeserializer.readNumber() as number)
        let value: ScaleResult = ({x: xTmpResult, y: yTmpResult, z: zTmpResult, centerX: centerXTmpResult, centerY: centerYTmpResult} as ScaleResult)
        return value
    }
}
export class SizeF64Inner_serializer {
    public static write(buffer: SerializerBase, value: SizeF64Inner): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForWidth = value.width
        valueSerializer.writeFloat64(valueHolderForWidth)
        const valueHolderForHeight = value.height
        valueSerializer.writeFloat64(valueHolderForHeight)
    }
    public static read(buffer: DeserializerBase): SizeF64Inner {
        let valueDeserializer: DeserializerBase = buffer
        const widthTmpResult: double = valueDeserializer.readFloat64()
        const heightTmpResult: double = valueDeserializer.readFloat64()
        let value: SizeF64Inner = ({width: widthTmpResult, height: heightTmpResult} as SizeF64Inner)
        return value
    }
}
export class TranslateResult_serializer {
    public static write(buffer: SerializerBase, value: TranslateResult): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForX = value.x
        valueSerializer.writeNumber(valueHolderForX)
        const valueHolderForY = value.y
        valueSerializer.writeNumber(valueHolderForY)
        const valueHolderForZ = value.z
        valueSerializer.writeNumber(valueHolderForZ)
    }
    public static read(buffer: DeserializerBase): TranslateResult {
        let valueDeserializer: DeserializerBase = buffer
        const xTmpResult: number = (valueDeserializer.readNumber() as number)
        const yTmpResult: number = (valueDeserializer.readNumber() as number)
        const zTmpResult: number = (valueDeserializer.readNumber() as number)
        let value: TranslateResult = ({x: xTmpResult, y: yTmpResult, z: zTmpResult} as TranslateResult)
        return value
    }
}
export class Vector2F64_serializer {
    public static write(buffer: SerializerBase, value: Vector2F64): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForX = value.x
        valueSerializer.writeFloat64(valueHolderForX)
        const valueHolderForY = value.y
        valueSerializer.writeFloat64(valueHolderForY)
    }
    public static read(buffer: DeserializerBase): Vector2F64 {
        let valueDeserializer: DeserializerBase = buffer
        const xTmpResult: double = valueDeserializer.readFloat64()
        const yTmpResult: double = valueDeserializer.readFloat64()
        let value: Vector2F64 = ({x: xTmpResult, y: yTmpResult} as Vector2F64)
        return value
    }
}
export class WaterFlowSectionsInterface_serializer {
    public static write(buffer: SerializerBase, value: WaterFlowSectionsInterface): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForPtr = value.ptr
        valueSerializer.writePointer(valueHolderForPtr)
    }
    public static read(buffer: DeserializerBase): WaterFlowSectionsInterface {
        let valueDeserializer: DeserializerBase = buffer
        const ptrTmpResult: KPointer = valueDeserializer.readPointer()
        let value: WaterFlowSectionsInterface = ({ptr: ptrTmpResult} as WaterFlowSectionsInterface)
        return value
    }
}
export class BorderRadiuses_graphics_serializer {
    public static write(buffer: SerializerBase, value: BorderRadiuses_graphics): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForTopLeft = value.topLeft
        valueSerializer.writeNumber(valueHolderForTopLeft)
        const valueHolderForTopRight = value.topRight
        valueSerializer.writeNumber(valueHolderForTopRight)
        const valueHolderForBottomLeft = value.bottomLeft
        valueSerializer.writeNumber(valueHolderForBottomLeft)
        const valueHolderForBottomRight = value.bottomRight
        valueSerializer.writeNumber(valueHolderForBottomRight)
    }
    public static read(buffer: DeserializerBase): BorderRadiuses_graphics {
        let valueDeserializer: DeserializerBase = buffer
        const topLeftTmpResult: number = (valueDeserializer.readNumber() as number)
        const topRightTmpResult: number = (valueDeserializer.readNumber() as number)
        const bottomLeftTmpResult: number = (valueDeserializer.readNumber() as number)
        const bottomRightTmpResult: number = (valueDeserializer.readNumber() as number)
        let value: BorderRadiuses_graphics = ({topLeft: topLeftTmpResult, topRight: topRightTmpResult, bottomLeft: bottomLeftTmpResult, bottomRight: bottomRightTmpResult} as BorderRadiuses_graphics)
        return value
    }
}
export class BuilderNodeOptions_serializer {
    public static write(buffer: SerializerBase, value: BuilderNodeOptions): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForSelfIdealSize = value.selfIdealSize
        if (valueHolderForSelfIdealSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSelfIdealSizeTmpValue = valueHolderForSelfIdealSize!
            Size_serializer.write(valueSerializer, valueHolderForSelfIdealSizeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForType = value.type
        if (valueHolderForType !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTypeTmpValue = valueHolderForType!
            valueSerializer.writeNumber(valueHolderForTypeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSurfaceId = value.surfaceId
        if (valueHolderForSurfaceId !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSurfaceIdTmpValue = valueHolderForSurfaceId!
            valueSerializer.writeString(valueHolderForSurfaceIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): BuilderNodeOptions {
        let valueDeserializer: DeserializerBase = buffer
        const selfIdealSizeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let selfIdealSizeTmpBuf: Size | undefined = undefined
        if ((selfIdealSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            selfIdealSizeTmpBuf = Size_serializer.read(valueDeserializer)
        }
        const selfIdealSizeTmpResult: Size | undefined = selfIdealSizeTmpBuf
        const typeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let typeTmpBuf: number | undefined = undefined
        if ((typeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            typeTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const typeTmpResult: number | undefined = typeTmpBuf
        const surfaceIdTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let surfaceIdTmpBuf: string | undefined = undefined
        if ((surfaceIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            surfaceIdTmpBuf = (valueDeserializer.readString() as string)
        }
        const surfaceIdTmpResult: string | undefined = surfaceIdTmpBuf
        let value: BuilderNodeOptions = ({selfIdealSize: selfIdealSizeTmpResult, type: typeTmpResult, surfaceId: surfaceIdTmpResult} as BuilderNodeOptions)
        return value
    }
}
export class BusinessErrorInterface_Void_serializer {
    public static write(buffer: SerializerBase, value: BusinessErrorInterface<void>): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForName = value.name
        valueSerializer.writeString(valueHolderForName)
        const valueHolderForMessage = value.message
        valueSerializer.writeString(valueHolderForMessage)
        const valueHolderForStack = value.stack
        if (valueHolderForStack !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStackTmpValue = valueHolderForStack!
            valueSerializer.writeString(valueHolderForStackTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCode = value.code
        valueSerializer.writeInt32(valueHolderForCode)
    }
    public static read(buffer: DeserializerBase): BusinessErrorInterface<void> {
        let valueDeserializer: DeserializerBase = buffer
        const nameTmpResult: string = (valueDeserializer.readString() as string)
        const messageTmpResult: string = (valueDeserializer.readString() as string)
        const stackTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let stackTmpBuf: string | undefined = undefined
        if ((stackTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            stackTmpBuf = (valueDeserializer.readString() as string)
        }
        const stackTmpResult: string | undefined = stackTmpBuf
        const codeTmpResult: int32 = valueDeserializer.readInt32()
        let value: BusinessErrorInterface<void> = ({name: nameTmpResult, message: messageTmpResult, stack: stackTmpResult, code: codeTmpResult, data: undefined} as BusinessErrorInterface<void>)
        return value
    }
}
export class ColorMetricsExt_serializer {
    public static write(buffer: SerializerBase, value: ColorMetricsExt): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForRed = value.red
        valueSerializer.writeInt32(valueHolderForRed)
        const valueHolderForGreen = value.green
        valueSerializer.writeInt32(valueHolderForGreen)
        const valueHolderForBlue = value.blue
        valueSerializer.writeInt32(valueHolderForBlue)
        const valueHolderForAlpha = value.alpha
        valueSerializer.writeInt32(valueHolderForAlpha)
        const valueHolderForColorSpace = value.colorSpace
        valueSerializer.writeInt32(valueHolderForColorSpace.valueOf())
        const valueHolderForResourceId = value.resourceId
        valueSerializer.writeInt32(valueHolderForResourceId)
    }
    public static read(buffer: DeserializerBase): ColorMetricsExt {
        let valueDeserializer: DeserializerBase = buffer
        const redTmpResult: int32 = valueDeserializer.readInt32()
        const greenTmpResult: int32 = valueDeserializer.readInt32()
        const blueTmpResult: int32 = valueDeserializer.readInt32()
        const alphaTmpResult: int32 = valueDeserializer.readInt32()
        const colorSpaceTmpResult: ColorSpace = ColorSpace.fromValue(valueDeserializer.readInt32())
        const resourceIdTmpResult: int32 = valueDeserializer.readInt32()
        let value: ColorMetricsExt = ({red: redTmpResult, green: greenTmpResult, blue: blueTmpResult, alpha: alphaTmpResult, colorSpace: colorSpaceTmpResult, resourceId: resourceIdTmpResult} as ColorMetricsExt)
        return value
    }
}
export class CustomDialogControllerExternalOptionsExtender_serializer {
    public static write(buffer: SerializerBase, value: CustomDialogControllerExternalOptionsExtender): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForCustomStyle = value.customStyle
        if (valueHolderForCustomStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCustomStyleTmpValue = valueHolderForCustomStyle!
            valueSerializer.writeBoolean(valueHolderForCustomStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): CustomDialogControllerExternalOptionsExtender {
        let valueDeserializer: DeserializerBase = buffer
        const customStyleTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let customStyleTmpBuf: boolean | undefined = undefined
        if ((customStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            customStyleTmpBuf = valueDeserializer.readBoolean()
        }
        const customStyleTmpResult: boolean | undefined = customStyleTmpBuf
        let value: CustomDialogControllerExternalOptionsExtender = ({customStyle: customStyleTmpResult} as CustomDialogControllerExternalOptionsExtender)
        return value
    }
}
export class DisturbanceFieldOptionsInner_serializer {
    public static write(buffer: SerializerBase, value: DisturbanceFieldOptionsInner): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForStrength = value.strength
        if (valueHolderForStrength !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStrengthTmpValue = valueHolderForStrength!
            valueSerializer.writeFloat64(valueHolderForStrengthTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShape = value.shape
        if (valueHolderForShape !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShapeTmpValue = (valueHolderForShape as DisturbanceFieldShape)
            valueSerializer.writeInt32(valueHolderForShapeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSize = value.size
        if (valueHolderForSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSizeTmpValue = valueHolderForSize!
            SizeF64Inner_serializer.write(valueSerializer, valueHolderForSizeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPosition = value.position
        if (valueHolderForPosition !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPositionTmpValue = valueHolderForPosition!
            PositionF64Inner_serializer.write(valueSerializer, valueHolderForPositionTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFeather = value.feather
        if (valueHolderForFeather !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFeatherTmpValue = valueHolderForFeather!
            valueSerializer.writeInt32(valueHolderForFeatherTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForNoiseScale = value.noiseScale
        if (valueHolderForNoiseScale !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForNoiseScaleTmpValue = valueHolderForNoiseScale!
            valueSerializer.writeFloat64(valueHolderForNoiseScaleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForNoiseFrequency = value.noiseFrequency
        if (valueHolderForNoiseFrequency !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForNoiseFrequencyTmpValue = valueHolderForNoiseFrequency!
            valueSerializer.writeFloat64(valueHolderForNoiseFrequencyTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForNoiseAmplitude = value.noiseAmplitude
        if (valueHolderForNoiseAmplitude !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForNoiseAmplitudeTmpValue = valueHolderForNoiseAmplitude!
            valueSerializer.writeFloat64(valueHolderForNoiseAmplitudeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): DisturbanceFieldOptionsInner {
        let valueDeserializer: DeserializerBase = buffer
        const strengthTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let strengthTmpBuf: double | undefined = undefined
        if ((strengthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            strengthTmpBuf = valueDeserializer.readFloat64()
        }
        const strengthTmpResult: double | undefined = strengthTmpBuf
        const shapeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let shapeTmpBuf: DisturbanceFieldShape | undefined = undefined
        if ((shapeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            shapeTmpBuf = DisturbanceFieldShape.fromValue(valueDeserializer.readInt32())
        }
        const shapeTmpResult: DisturbanceFieldShape | undefined = shapeTmpBuf
        const sizeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let sizeTmpBuf: SizeF64Inner | undefined = undefined
        if ((sizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            sizeTmpBuf = SizeF64Inner_serializer.read(valueDeserializer)
        }
        const sizeTmpResult: SizeF64Inner | undefined = sizeTmpBuf
        const positionTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let positionTmpBuf: PositionF64Inner | undefined = undefined
        if ((positionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            positionTmpBuf = PositionF64Inner_serializer.read(valueDeserializer)
        }
        const positionTmpResult: PositionF64Inner | undefined = positionTmpBuf
        const featherTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let featherTmpBuf: int32 | undefined = undefined
        if ((featherTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            featherTmpBuf = valueDeserializer.readInt32()
        }
        const featherTmpResult: int32 | undefined = featherTmpBuf
        const noiseScaleTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let noiseScaleTmpBuf: double | undefined = undefined
        if ((noiseScaleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            noiseScaleTmpBuf = valueDeserializer.readFloat64()
        }
        const noiseScaleTmpResult: double | undefined = noiseScaleTmpBuf
        const noiseFrequencyTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let noiseFrequencyTmpBuf: double | undefined = undefined
        if ((noiseFrequencyTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            noiseFrequencyTmpBuf = valueDeserializer.readFloat64()
        }
        const noiseFrequencyTmpResult: double | undefined = noiseFrequencyTmpBuf
        const noiseAmplitudeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let noiseAmplitudeTmpBuf: double | undefined = undefined
        if ((noiseAmplitudeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            noiseAmplitudeTmpBuf = valueDeserializer.readFloat64()
        }
        const noiseAmplitudeTmpResult: double | undefined = noiseAmplitudeTmpBuf
        let value: DisturbanceFieldOptionsInner = ({strength: strengthTmpResult, shape: shapeTmpResult, size: sizeTmpResult, position: positionTmpResult, feather: featherTmpResult, noiseScale: noiseScaleTmpResult, noiseFrequency: noiseFrequencyTmpResult, noiseAmplitude: noiseAmplitudeTmpResult} as DisturbanceFieldOptionsInner)
        return value
    }
}
export class DoubleAnimationParam_serializer {
    public static write(buffer: SerializerBase, value: DoubleAnimationParam): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForPropertyName = value.propertyName
        valueSerializer.writeString(valueHolderForPropertyName)
        const valueHolderForStartValue = value.startValue
        valueSerializer.writeFloat32(valueHolderForStartValue)
        const valueHolderForEndValue = value.endValue
        valueSerializer.writeFloat32(valueHolderForEndValue)
        const valueHolderForDuration = value.duration
        valueSerializer.writeInt32(valueHolderForDuration)
        const valueHolderForDelay = value.delay
        valueSerializer.writeInt32(valueHolderForDelay)
        const valueHolderForCurve = value.curve
        if (valueHolderForCurve instanceof Curve) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForCurveForIdx0 = valueHolderForCurve as Curve
            valueSerializer.writeInt32(valueHolderForCurveForIdx0.valueOf())
        } else if (valueHolderForCurve instanceof string) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForCurveForIdx1 = valueHolderForCurve as string
            valueSerializer.writeString(valueHolderForCurveForIdx1)
        } else if (valueHolderForCurve instanceof ICurve) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForCurveForIdx2 = valueHolderForCurve as ICurve
            curves_ICurve_serializer.write(valueSerializer, valueHolderForCurveForIdx2)
        }
        const valueHolderForOnProgress = value.onProgress
        if (valueHolderForOnProgress !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnProgressTmpValue = valueHolderForOnProgress!
            valueSerializer.holdAndWriteCallback(valueHolderForOnProgressTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnFinish = value.onFinish
        if (valueHolderForOnFinish !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnFinishTmpValue = valueHolderForOnFinish!
            valueSerializer.holdAndWriteCallback(valueHolderForOnFinishTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): DoubleAnimationParam {
        let valueDeserializer: DeserializerBase = buffer
        const propertyNameTmpResult: string = (valueDeserializer.readString() as string)
        const startValueTmpResult: float = valueDeserializer.readFloat32()
        const endValueTmpResult: float = valueDeserializer.readFloat32()
        const durationTmpResult: int32 = valueDeserializer.readInt32()
        const delayTmpResult: int32 = valueDeserializer.readInt32()
        const curveTmpBufUnionSelector: int32 = valueDeserializer.readInt8()
        let curveTmpBuf: Curve | string | ICurve | undefined
        if (curveTmpBufUnionSelector == (0).toByte()) {
            curveTmpBuf = curves.Curve.fromValue(valueDeserializer.readInt32())
        } else if (curveTmpBufUnionSelector == (1).toByte()) {
            curveTmpBuf = (valueDeserializer.readString() as string)
        } else if (curveTmpBufUnionSelector == (2).toByte()) {
            curveTmpBuf = (curves_ICurve_serializer.read(valueDeserializer) as curves.ICurve)
        } else {
            throw new Error('One of the branches for curveTmpBuf has to be chosen through deserialisation.')
        }
        const curveTmpResult: Curve | string | ICurve = (curveTmpBuf as Curve | string | ICurve)
        const onProgressTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let onProgressTmpBuf: Callback_Extender_OnProgress | undefined = undefined
        if ((onProgressTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onProgressTmpBufOptBufResource: CallbackResource = valueDeserializer.readCallbackResource()
            const onProgressTmpBufOptBufCall: KPointer = valueDeserializer.readPointer()
            const onProgressTmpBufOptBufCallSync: KPointer = valueDeserializer.readPointer()
            const onProgressTmpBufOptClosure = (value: float):void => {
                const onProgressTmpBufOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                onProgressTmpBufOptBufArgsSerializer.writeInt32(onProgressTmpBufOptBufResource.resourceId);
                onProgressTmpBufOptBufArgsSerializer.writePointer(onProgressTmpBufOptBufCall);
                onProgressTmpBufOptBufArgsSerializer.writePointer(onProgressTmpBufOptBufCallSync);
                onProgressTmpBufOptBufArgsSerializer.writeFloat32(value);
                InteropNativeModule._CallCallbackSync(10, -1121507978, onProgressTmpBufOptBufArgsSerializer.asBuffer(), onProgressTmpBufOptBufArgsSerializer.length());
                onProgressTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onProgressTmpBufOptClosure, onProgressTmpBufOptBufResource)
            onProgressTmpBuf = onProgressTmpBufOptClosure
        }
        const onProgressTmpResult: Callback_Extender_OnProgress | undefined = onProgressTmpBuf
        const onFinishTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let onFinishTmpBuf: Callback_Extender_OnFinish | undefined = undefined
        if ((onFinishTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onFinishTmpBufOptBufResource: CallbackResource = valueDeserializer.readCallbackResource()
            const onFinishTmpBufOptBufCall: KPointer = valueDeserializer.readPointer()
            const onFinishTmpBufOptBufCallSync: KPointer = valueDeserializer.readPointer()
            const onFinishTmpBufOptClosure = ():void => {
                const onFinishTmpBufOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                onFinishTmpBufOptBufArgsSerializer.writeInt32(onFinishTmpBufOptBufResource.resourceId);
                onFinishTmpBufOptBufArgsSerializer.writePointer(onFinishTmpBufOptBufCall);
                onFinishTmpBufOptBufArgsSerializer.writePointer(onFinishTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, 710286488, onFinishTmpBufOptBufArgsSerializer.asBuffer(), onFinishTmpBufOptBufArgsSerializer.length());
                onFinishTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onFinishTmpBufOptClosure, onFinishTmpBufOptBufResource)
            onFinishTmpBuf = onFinishTmpBufOptClosure
        }
        const onFinishTmpResult: Callback_Extender_OnFinish | undefined = onFinishTmpBuf
        let value: DoubleAnimationParam = ({propertyName: propertyNameTmpResult, startValue: startValueTmpResult, endValue: endValueTmpResult, duration: durationTmpResult, delay: delayTmpResult, curve: curveTmpResult, onProgress: onProgressTmpResult, onFinish: onFinishTmpResult} as DoubleAnimationParam)
        return value
    }
}
export class EdgeF64_serializer {
    public static write(buffer: SerializerBase, value: EdgeF64): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForTop = value.top
        valueSerializer.writeFloat64(valueHolderForTop)
        const valueHolderForRight = value.right
        valueSerializer.writeFloat64(valueHolderForRight)
        const valueHolderForBottom = value.bottom
        valueSerializer.writeFloat64(valueHolderForBottom)
        const valueHolderForLeft = value.left
        valueSerializer.writeFloat64(valueHolderForLeft)
    }
    public static read(buffer: DeserializerBase): EdgeF64 {
        let valueDeserializer: DeserializerBase = buffer
        const topTmpResult: double = valueDeserializer.readFloat64()
        const rightTmpResult: double = valueDeserializer.readFloat64()
        const bottomTmpResult: double = valueDeserializer.readFloat64()
        const leftTmpResult: double = valueDeserializer.readFloat64()
        let value: EdgeF64 = ({top: topTmpResult, right: rightTmpResult, bottom: bottomTmpResult, left: leftTmpResult} as EdgeF64)
        return value
    }
}
export class EdgeI32_serializer {
    public static write(buffer: SerializerBase, value: EdgeI32): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForTop = value.top
        valueSerializer.writeInt32(valueHolderForTop)
        const valueHolderForRight = value.right
        valueSerializer.writeInt32(valueHolderForRight)
        const valueHolderForBottom = value.bottom
        valueSerializer.writeInt32(valueHolderForBottom)
        const valueHolderForLeft = value.left
        valueSerializer.writeInt32(valueHolderForLeft)
    }
    public static read(buffer: DeserializerBase): EdgeI32 {
        let valueDeserializer: DeserializerBase = buffer
        const topTmpResult: int32 = valueDeserializer.readInt32()
        const rightTmpResult: int32 = valueDeserializer.readInt32()
        const bottomTmpResult: int32 = valueDeserializer.readInt32()
        const leftTmpResult: int32 = valueDeserializer.readInt32()
        let value: EdgeI32 = ({top: topTmpResult, right: rightTmpResult, bottom: bottomTmpResult, left: leftTmpResult} as EdgeI32)
        return value
    }
}
export class ErrorEvent_serializer {
    public static write(buffer: SerializerBase, value: ErrorEvent): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForType = value.type
        valueSerializer.writeString(valueHolderForType)
        const valueHolderForTimeStamp = value.timeStamp
        valueSerializer.writeInt64(valueHolderForTimeStamp)
        const valueHolderForMessage = value.message
        valueSerializer.writeString(valueHolderForMessage)
        const valueHolderForFilename = value.filename
        valueSerializer.writeString(valueHolderForFilename)
        const valueHolderForLineno = value.lineno
        valueSerializer.writeNumber(valueHolderForLineno)
        const valueHolderForColno = value.colno
        valueSerializer.writeNumber(valueHolderForColno)
        const valueHolderForError = value.error
        valueSerializer.holdAndWriteObject(valueHolderForError)
    }
    public static read(buffer: DeserializerBase): ErrorEvent {
        let valueDeserializer: DeserializerBase = buffer
        const typeTmpResult: string = (valueDeserializer.readString() as string)
        const timeStampTmpResult: int64 = valueDeserializer.readInt64()
        const messageTmpResult: string = (valueDeserializer.readString() as string)
        const filenameTmpResult: string = (valueDeserializer.readString() as string)
        const linenoTmpResult: number = (valueDeserializer.readNumber() as number)
        const colnoTmpResult: number = (valueDeserializer.readNumber() as number)
        const errorTmpResult: Object = (valueDeserializer.readObject() as object)
        let value: ErrorEvent = ({type: typeTmpResult, timeStamp: timeStampTmpResult, message: messageTmpResult, filename: filenameTmpResult, lineno: linenoTmpResult, colno: colnoTmpResult, error: errorTmpResult} as ErrorEvent)
        return value
    }
}
export class Event_serializer {
    public static write(buffer: SerializerBase, value: Event): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForType = value.type
        valueSerializer.writeString(valueHolderForType)
        const valueHolderForTimeStamp = value.timeStamp
        valueSerializer.writeInt64(valueHolderForTimeStamp)
    }
    public static read(buffer: DeserializerBase): Event {
        let valueDeserializer: DeserializerBase = buffer
        const typeTmpResult: string = (valueDeserializer.readString() as string)
        const timeStampTmpResult: int64 = valueDeserializer.readInt64()
        let value: Event = ({type: typeTmpResult, timeStamp: timeStampTmpResult} as Event)
        return value
    }
}
export class FieldRegionInner_serializer {
    public static write(buffer: SerializerBase, value: FieldRegionInner): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForShape = value.shape
        if (valueHolderForShape !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShapeTmpValue = (valueHolderForShape as DisturbanceFieldShape)
            valueSerializer.writeInt32(valueHolderForShapeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPosition = value.position
        if (valueHolderForPosition !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPositionTmpValue = valueHolderForPosition!
            PositionF64Inner_serializer.write(valueSerializer, valueHolderForPositionTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSize = value.size
        if (valueHolderForSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSizeTmpValue = valueHolderForSize!
            SizeF64Inner_serializer.write(valueSerializer, valueHolderForSizeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): FieldRegionInner {
        let valueDeserializer: DeserializerBase = buffer
        const shapeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let shapeTmpBuf: DisturbanceFieldShape | undefined = undefined
        if ((shapeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            shapeTmpBuf = DisturbanceFieldShape.fromValue(valueDeserializer.readInt32())
        }
        const shapeTmpResult: DisturbanceFieldShape | undefined = shapeTmpBuf
        const positionTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let positionTmpBuf: PositionF64Inner | undefined = undefined
        if ((positionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            positionTmpBuf = PositionF64Inner_serializer.read(valueDeserializer)
        }
        const positionTmpResult: PositionF64Inner | undefined = positionTmpBuf
        const sizeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let sizeTmpBuf: SizeF64Inner | undefined = undefined
        if ((sizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            sizeTmpBuf = SizeF64Inner_serializer.read(valueDeserializer)
        }
        const sizeTmpResult: SizeF64Inner | undefined = sizeTmpBuf
        let value: FieldRegionInner = ({shape: shapeTmpResult, position: positionTmpResult, size: sizeTmpResult} as FieldRegionInner)
        return value
    }
}
export class InnerGestureObserverConfigs_serializer {
    public static write(buffer: SerializerBase, value: InnerGestureObserverConfigs): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForActionPhases = value.actionPhases
        valueSerializer.writeInt32((valueHolderForActionPhases.length).toInt())
        for (let valueHolderForActionPhasesCounterI = 0; valueHolderForActionPhasesCounterI < valueHolderForActionPhases.length; valueHolderForActionPhasesCounterI++) {
            const valueHolderForActionPhasesTmpElement: GestureActionPhase = valueHolderForActionPhases[valueHolderForActionPhasesCounterI]
            valueSerializer.writeInt32(valueHolderForActionPhasesTmpElement.valueOf())
        }
    }
    public static read(buffer: DeserializerBase): InnerGestureObserverConfigs {
        let valueDeserializer: DeserializerBase = buffer
        const actionPhasesTmpBufLength: int32 = valueDeserializer.readInt32()
        let actionPhasesTmpBuf: Array<GestureActionPhase> = new Array<GestureActionPhase>(actionPhasesTmpBufLength)
        for (let actionPhasesTmpBufBufCounterI = 0; actionPhasesTmpBufBufCounterI < actionPhasesTmpBufLength; actionPhasesTmpBufBufCounterI++) {
            actionPhasesTmpBuf[actionPhasesTmpBufBufCounterI] = GestureActionPhase.fromValue(valueDeserializer.readInt32())
        }
        const actionPhasesTmpResult: Array<GestureActionPhase> = actionPhasesTmpBuf
        let value: InnerGestureObserverConfigs = ({actionPhases: actionPhasesTmpResult} as InnerGestureObserverConfigs)
        return value
    }
}
export class LengthMetricsCustom_serializer {
    public static write(buffer: SerializerBase, value: LengthMetricsCustom): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForUnit = value.unit
        valueSerializer.writeNumber(valueHolderForUnit)
        const valueHolderForValue = value.value
        valueSerializer.writeNumber(valueHolderForValue)
    }
    public static read(buffer: DeserializerBase): LengthMetricsCustom {
        let valueDeserializer: DeserializerBase = buffer
        const unitTmpResult: number = (valueDeserializer.readNumber() as number)
        const valueTmpResult: number = (valueDeserializer.readNumber() as number)
        let value: LengthMetricsCustom = ({unit: unitTmpResult, value: valueTmpResult} as LengthMetricsCustom)
        return value
    }
}
export class MessageEvents_serializer {
    public static write(buffer: SerializerBase, value: MessageEvents): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForType = value.type
        valueSerializer.writeString(valueHolderForType)
        const valueHolderForTimeStamp = value.timeStamp
        valueSerializer.writeInt64(valueHolderForTimeStamp)
        const valueHolderForData = value.data
        valueSerializer.holdAndWriteObject(valueHolderForData)
    }
    public static read(buffer: DeserializerBase): MessageEvents {
        let valueDeserializer: DeserializerBase = buffer
        const typeTmpResult: string = (valueDeserializer.readString() as string)
        const timeStampTmpResult: int64 = valueDeserializer.readInt64()
        const dataTmpResult: object = (valueDeserializer.readObject() as object)
        let value: MessageEvents = ({type: typeTmpResult, timeStamp: timeStampTmpResult, data: dataTmpResult} as MessageEvents)
        return value
    }
}
export class ParticlePropertyAnimationNumberInner_serializer {
    public static write(buffer: SerializerBase, value: ParticlePropertyAnimationNumberInner): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForFrom = value.from
        valueSerializer.writeNumber(valueHolderForFrom)
        const valueHolderForTo = value.to
        valueSerializer.writeNumber(valueHolderForTo)
        const valueHolderForStartMillis = value.startMillis
        valueSerializer.writeInt32(valueHolderForStartMillis)
        const valueHolderForEndMillis = value.endMillis
        valueSerializer.writeInt32(valueHolderForEndMillis)
        const valueHolderForCurve = value.curve
        if (valueHolderForCurve !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCurveTmpValue = valueHolderForCurve!
            if (valueHolderForCurveTmpValue instanceof Curve) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForCurveTmpValueForIdx0 = valueHolderForCurveTmpValue as Curve
                valueSerializer.writeInt32(valueHolderForCurveTmpValueForIdx0.valueOf())
            } else if (valueHolderForCurveTmpValue instanceof ICurve) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForCurveTmpValueForIdx1 = valueHolderForCurveTmpValue as ICurve
                curves_ICurve_serializer.write(valueSerializer, valueHolderForCurveTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ParticlePropertyAnimationNumberInner {
        let valueDeserializer: DeserializerBase = buffer
        const fromTmpResult: number = (valueDeserializer.readNumber() as number)
        const toTmpResult: number = (valueDeserializer.readNumber() as number)
        const startMillisTmpResult: int32 = valueDeserializer.readInt32()
        const endMillisTmpResult: int32 = valueDeserializer.readInt32()
        const curveTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let curveTmpBuf: Curve | ICurve | undefined = undefined
        if ((curveTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const curveTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let curveTmpBufOpt: Curve | ICurve | undefined
            if (curveTmpBufOptUnionSelector == (0).toByte()) {
                curveTmpBufOpt = curves.Curve.fromValue(valueDeserializer.readInt32())
            } else if (curveTmpBufOptUnionSelector == (1).toByte()) {
                curveTmpBufOpt = (curves_ICurve_serializer.read(valueDeserializer) as curves.ICurve)
            } else {
                throw new Error('One of the branches for curveTmpBufOpt has to be chosen through deserialisation.')
            }
            curveTmpBuf = (curveTmpBufOpt as Curve | ICurve)
        }
        const curveTmpResult: Curve | ICurve | undefined = curveTmpBuf
        let value: ParticlePropertyAnimationNumberInner = ({from: fromTmpResult, to: toTmpResult, startMillis: startMillisTmpResult, endMillis: endMillisTmpResult, curve: curveTmpResult} as ParticlePropertyAnimationNumberInner)
        return value
    }
}
export class ParticlesInner_serializer {
    public static write(buffer: SerializerBase, value: ParticlesInner): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForParticles = value.particles
        valueSerializer.writeInt32((valueHolderForParticles.length).toInt())
        for (let valueHolderForParticlesCounterI = 0; valueHolderForParticlesCounterI < valueHolderForParticles.length; valueHolderForParticlesCounterI++) {
            const valueHolderForParticlesTmpElement: ParticleOptionsInner = valueHolderForParticles[valueHolderForParticlesCounterI]
            ParticleOptionsInner_serializer.write(valueSerializer, valueHolderForParticlesTmpElement)
        }
    }
    public static read(buffer: DeserializerBase): ParticlesInner {
        let valueDeserializer: DeserializerBase = buffer
        const particlesTmpBufLength: int32 = valueDeserializer.readInt32()
        let particlesTmpBuf: Array<ParticleOptionsInner> = new Array<ParticleOptionsInner>(particlesTmpBufLength)
        for (let particlesTmpBufBufCounterI = 0; particlesTmpBufBufCounterI < particlesTmpBufLength; particlesTmpBufBufCounterI++) {
            particlesTmpBuf[particlesTmpBufBufCounterI] = ParticleOptionsInner_serializer.read(valueDeserializer)
        }
        const particlesTmpResult: Array<ParticleOptionsInner> = particlesTmpBuf
        let value: ParticlesInner = ({particles: particlesTmpResult} as ParticlesInner)
        return value
    }
}
export class PositionLengthMetricsInner_serializer {
    public static write(buffer: SerializerBase, value: PositionLengthMetricsInner): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForX = value.x
        arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForX)
        const valueHolderForY = value.y
        arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForY)
    }
    public static read(buffer: DeserializerBase): PositionLengthMetricsInner {
        let valueDeserializer: DeserializerBase = buffer
        const xTmpResult: arkui_Graphics_LengthMetrics = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        const yTmpResult: arkui_Graphics_LengthMetrics = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        let value: PositionLengthMetricsInner = ({x: xTmpResult, y: yTmpResult} as PositionLengthMetricsInner)
        return value
    }
}
export class PostMessageOptions_serializer {
    public static write(buffer: SerializerBase, value: PostMessageOptions): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForTransfer = value.transfer
        if (valueHolderForTransfer !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTransferTmpValue = valueHolderForTransfer!
            valueSerializer.writeInt32((valueHolderForTransferTmpValue.length).toInt())
            for (let valueHolderForTransferTmpValueCounterI = 0; valueHolderForTransferTmpValueCounterI < valueHolderForTransferTmpValue.length; valueHolderForTransferTmpValueCounterI++) {
                const valueHolderForTransferTmpValueTmpElement: Object = valueHolderForTransferTmpValue[valueHolderForTransferTmpValueCounterI]
                valueSerializer.holdAndWriteObject(valueHolderForTransferTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): PostMessageOptions {
        let valueDeserializer: DeserializerBase = buffer
        const transferTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let transferTmpBuf: Array<Object> | undefined = undefined
        if ((transferTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const transferTmpBufOptLength: int32 = valueDeserializer.readInt32()
            let transferTmpBufOpt: Array<Object> = new Array<Object>(transferTmpBufOptLength)
            for (let transferTmpBufOptBufCounterI = 0; transferTmpBufOptBufCounterI < transferTmpBufOptLength; transferTmpBufOptBufCounterI++) {
                transferTmpBufOpt[transferTmpBufOptBufCounterI] = (valueDeserializer.readObject() as object)
            }
            transferTmpBuf = transferTmpBufOpt
        }
        const transferTmpResult: Array<Object> | undefined = transferTmpBuf
        let value: PostMessageOptions = ({transfer: transferTmpResult} as PostMessageOptions)
        return value
    }
}
export class RouterOptionsInner_serializer {
    public static write(buffer: SerializerBase, value: RouterOptionsInner): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForUrl = value.url
        valueSerializer.writeString(valueHolderForUrl)
        const valueHolderForParams = value.params
        if (valueHolderForParams !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForParamsTmpValue = valueHolderForParams!
            valueSerializer.writeString(valueHolderForParamsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRecoverable = value.recoverable
        if (valueHolderForRecoverable !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRecoverableTmpValue = valueHolderForRecoverable!
            valueSerializer.writeBoolean(valueHolderForRecoverableTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RouterOptionsInner {
        let valueDeserializer: DeserializerBase = buffer
        const urlTmpResult: string = (valueDeserializer.readString() as string)
        const paramsTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let paramsTmpBuf: string | undefined = undefined
        if ((paramsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            paramsTmpBuf = (valueDeserializer.readString() as string)
        }
        const paramsTmpResult: string | undefined = paramsTmpBuf
        const recoverableTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let recoverableTmpBuf: boolean | undefined = undefined
        if ((recoverableTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            recoverableTmpBuf = valueDeserializer.readBoolean()
        }
        const recoverableTmpResult: boolean | undefined = recoverableTmpBuf
        let value: RouterOptionsInner = ({url: urlTmpResult, params: paramsTmpResult, recoverable: recoverableTmpResult} as RouterOptionsInner)
        return value
    }
}
export class RouterStateInner_serializer {
    public static write(buffer: SerializerBase, value: RouterStateInner): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForIndex = value.index
        valueSerializer.writeInt32(valueHolderForIndex)
        const valueHolderForName = value.name
        valueSerializer.writeString(valueHolderForName)
        const valueHolderForPath = value.path
        valueSerializer.writeString(valueHolderForPath)
        const valueHolderForParams = value.params
        valueSerializer.writeString(valueHolderForParams)
    }
    public static read(buffer: DeserializerBase): RouterStateInner {
        let valueDeserializer: DeserializerBase = buffer
        const indexTmpResult: int32 = valueDeserializer.readInt32()
        const nameTmpResult: string = (valueDeserializer.readString() as string)
        const pathTmpResult: string = (valueDeserializer.readString() as string)
        const paramsTmpResult: string = (valueDeserializer.readString() as string)
        let value: RouterStateInner = ({index: indexTmpResult, name: nameTmpResult, path: pathTmpResult, params: paramsTmpResult} as RouterStateInner)
        return value
    }
}
export class SizeTLengthMetrics_serializer {
    public static write(buffer: SerializerBase, value: SizeTLengthMetrics): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForWidth = value.width
        arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForWidth)
        const valueHolderForHeight = value.height
        arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForHeight)
    }
    public static read(buffer: DeserializerBase): SizeTLengthMetrics {
        let valueDeserializer: DeserializerBase = buffer
        const widthTmpResult: arkui_Graphics_LengthMetrics = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        const heightTmpResult: arkui_Graphics_LengthMetrics = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        let value: SizeTLengthMetrics = ({width: widthTmpResult, height: heightTmpResult} as SizeTLengthMetrics)
        return value
    }
}
export class SnapshotOptions_serializer {
    public static write(buffer: SerializerBase, value: SnapshotOptions): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForScale = value.scale
        if (valueHolderForScale !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForScaleTmpValue = valueHolderForScale!
            valueSerializer.writeNumber(valueHolderForScaleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWaitUntilRenderFinished = value.waitUntilRenderFinished
        if (valueHolderForWaitUntilRenderFinished !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWaitUntilRenderFinishedTmpValue = valueHolderForWaitUntilRenderFinished!
            valueSerializer.writeBoolean(valueHolderForWaitUntilRenderFinishedTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SnapshotOptions {
        let valueDeserializer: DeserializerBase = buffer
        const scaleTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let scaleTmpBuf: number | undefined = undefined
        if ((scaleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            scaleTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const scaleTmpResult: number | undefined = scaleTmpBuf
        const waitUntilRenderFinishedTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let waitUntilRenderFinishedTmpBuf: boolean | undefined = undefined
        if ((waitUntilRenderFinishedTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            waitUntilRenderFinishedTmpBuf = valueDeserializer.readBoolean()
        }
        const waitUntilRenderFinishedTmpResult: boolean | undefined = waitUntilRenderFinishedTmpBuf
        let value: SnapshotOptions = ({scale: scaleTmpResult, waitUntilRenderFinished: waitUntilRenderFinishedTmpResult} as SnapshotOptions)
        return value
    }
}
export class WorkerOptions_serializer {
    public static write(buffer: SerializerBase, value: WorkerOptions): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForType = value.type
        if (valueHolderForType !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTypeTmpValue = valueHolderForType!
            valueSerializer.writeString(valueHolderForTypeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForName = value.name
        if (valueHolderForName !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForNameTmpValue = valueHolderForName!
            valueSerializer.writeString(valueHolderForNameTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShared = value.shared
        if (valueHolderForShared !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSharedTmpValue = valueHolderForShared!
            valueSerializer.writeBoolean(valueHolderForSharedTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): WorkerOptions {
        let valueDeserializer: DeserializerBase = buffer
        const typeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let typeTmpBuf: string | undefined = undefined
        if ((typeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            typeTmpBuf = (valueDeserializer.readString() as string)
        }
        const typeTmpResult: string | undefined = typeTmpBuf
        const nameTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let nameTmpBuf: string | undefined = undefined
        if ((nameTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            nameTmpBuf = (valueDeserializer.readString() as string)
        }
        const nameTmpResult: string | undefined = nameTmpBuf
        const sharedTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let sharedTmpBuf: boolean | undefined = undefined
        if ((sharedTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            sharedTmpBuf = valueDeserializer.readBoolean()
        }
        const sharedTmpResult: boolean | undefined = sharedTmpBuf
        let value: WorkerOptions = ({type: typeTmpResult, name: nameTmpResult, shared: sharedTmpResult} as WorkerOptions)
        return value
    }
}
export class ArcDotIndicatorInner_serializer {
    public static write(buffer: SerializerBase, value: ArcDotIndicatorInner): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderFor_arcDirection = value._arcDirection
        if (valueHolderFor_arcDirection !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_arcDirectionTmpValue = (valueHolderFor_arcDirection as ArcDirectionInner)
            valueSerializer.writeInt32(valueHolderFor_arcDirectionTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_itemColor = value._itemColor
        if (valueHolderFor_itemColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_itemColorTmpValue = valueHolderFor_itemColor!
            if (valueHolderFor_itemColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderFor_itemColorTmpValueForIdx0 = valueHolderFor_itemColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderFor_itemColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderFor_itemColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderFor_itemColorTmpValueForIdx1 = valueHolderFor_itemColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderFor_itemColorTmpValueForIdx1)
            } else if (valueHolderFor_itemColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderFor_itemColorTmpValueForIdx2 = valueHolderFor_itemColorTmpValue as string
                valueSerializer.writeString(valueHolderFor_itemColorTmpValueForIdx2)
            } else if (valueHolderFor_itemColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderFor_itemColorTmpValueForIdx3 = valueHolderFor_itemColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderFor_itemColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_selectedItemColor = value._selectedItemColor
        if (valueHolderFor_selectedItemColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_selectedItemColorTmpValue = valueHolderFor_selectedItemColor!
            if (valueHolderFor_selectedItemColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderFor_selectedItemColorTmpValueForIdx0 = valueHolderFor_selectedItemColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderFor_selectedItemColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderFor_selectedItemColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderFor_selectedItemColorTmpValueForIdx1 = valueHolderFor_selectedItemColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderFor_selectedItemColorTmpValueForIdx1)
            } else if (valueHolderFor_selectedItemColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderFor_selectedItemColorTmpValueForIdx2 = valueHolderFor_selectedItemColorTmpValue as string
                valueSerializer.writeString(valueHolderFor_selectedItemColorTmpValueForIdx2)
            } else if (valueHolderFor_selectedItemColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderFor_selectedItemColorTmpValueForIdx3 = valueHolderFor_selectedItemColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderFor_selectedItemColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_backgroundColor = value._backgroundColor
        if (valueHolderFor_backgroundColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_backgroundColorTmpValue = valueHolderFor_backgroundColor!
            if (valueHolderFor_backgroundColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderFor_backgroundColorTmpValueForIdx0 = valueHolderFor_backgroundColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderFor_backgroundColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderFor_backgroundColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderFor_backgroundColorTmpValueForIdx1 = valueHolderFor_backgroundColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderFor_backgroundColorTmpValueForIdx1)
            } else if (valueHolderFor_backgroundColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderFor_backgroundColorTmpValueForIdx2 = valueHolderFor_backgroundColorTmpValue as string
                valueSerializer.writeString(valueHolderFor_backgroundColorTmpValueForIdx2)
            } else if (valueHolderFor_backgroundColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderFor_backgroundColorTmpValueForIdx3 = valueHolderFor_backgroundColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderFor_backgroundColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderFor_maskColor = value._maskColor
        if (valueHolderFor_maskColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderFor_maskColorTmpValue = valueHolderFor_maskColor!
            LinearGradient_serializer.write(valueSerializer, valueHolderFor_maskColorTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ArcDotIndicatorInner {
        let valueDeserializer: DeserializerBase = buffer
        const _arcDirectionTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let _arcDirectionTmpBuf: ArcDirectionInner | undefined = undefined
        if ((_arcDirectionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            _arcDirectionTmpBuf = ArcDirectionInner.fromValue(valueDeserializer.readInt32())
        }
        const _arcDirectionTmpResult: ArcDirectionInner | undefined = _arcDirectionTmpBuf
        const _itemColorTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let _itemColorTmpBuf: ResourceColor | undefined = undefined
        if ((_itemColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const _itemColorTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let _itemColorTmpBufOpt: arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (_itemColorTmpBufOptUnionSelector == (0).toByte()) {
                _itemColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (_itemColorTmpBufOptUnionSelector == (1).toByte()) {
                _itemColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (_itemColorTmpBufOptUnionSelector == (2).toByte()) {
                _itemColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (_itemColorTmpBufOptUnionSelector == (3).toByte()) {
                _itemColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for _itemColorTmpBufOpt has to be chosen through deserialisation.')
            }
            _itemColorTmpBuf = (_itemColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const _itemColorTmpResult: ResourceColor | undefined = _itemColorTmpBuf
        const _selectedItemColorTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let _selectedItemColorTmpBuf: ResourceColor | undefined = undefined
        if ((_selectedItemColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const _selectedItemColorTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let _selectedItemColorTmpBufOpt: arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (_selectedItemColorTmpBufOptUnionSelector == (0).toByte()) {
                _selectedItemColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (_selectedItemColorTmpBufOptUnionSelector == (1).toByte()) {
                _selectedItemColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (_selectedItemColorTmpBufOptUnionSelector == (2).toByte()) {
                _selectedItemColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (_selectedItemColorTmpBufOptUnionSelector == (3).toByte()) {
                _selectedItemColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for _selectedItemColorTmpBufOpt has to be chosen through deserialisation.')
            }
            _selectedItemColorTmpBuf = (_selectedItemColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const _selectedItemColorTmpResult: ResourceColor | undefined = _selectedItemColorTmpBuf
        const _backgroundColorTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let _backgroundColorTmpBuf: ResourceColor | undefined = undefined
        if ((_backgroundColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const _backgroundColorTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let _backgroundColorTmpBufOpt: arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (_backgroundColorTmpBufOptUnionSelector == (0).toByte()) {
                _backgroundColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (_backgroundColorTmpBufOptUnionSelector == (1).toByte()) {
                _backgroundColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (_backgroundColorTmpBufOptUnionSelector == (2).toByte()) {
                _backgroundColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (_backgroundColorTmpBufOptUnionSelector == (3).toByte()) {
                _backgroundColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for _backgroundColorTmpBufOpt has to be chosen through deserialisation.')
            }
            _backgroundColorTmpBuf = (_backgroundColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const _backgroundColorTmpResult: ResourceColor | undefined = _backgroundColorTmpBuf
        const _maskColorTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let _maskColorTmpBuf: LinearGradient | undefined = undefined
        if ((_maskColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            _maskColorTmpBuf = (LinearGradient_serializer.read(valueDeserializer) as LinearGradient)
        }
        const _maskColorTmpResult: LinearGradient | undefined = _maskColorTmpBuf
        let value: ArcDotIndicatorInner = ({_arcDirection: _arcDirectionTmpResult, _itemColor: _itemColorTmpResult, _selectedItemColor: _selectedItemColorTmpResult, _backgroundColor: _backgroundColorTmpResult, _maskColor: _maskColorTmpResult} as ArcDotIndicatorInner)
        return value
    }
}
export class ComponentInfo_serializer {
    public static write(buffer: SerializerBase, value: ComponentInfo): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForSize = value.size
        Size_serializer.write(valueSerializer, valueHolderForSize)
        const valueHolderForLocalOffset = value.localOffset
        Offset_componentutils_serializer.write(valueSerializer, valueHolderForLocalOffset)
        const valueHolderForWindowOffset = value.windowOffset
        Offset_componentutils_serializer.write(valueSerializer, valueHolderForWindowOffset)
        const valueHolderForScreenOffset = value.screenOffset
        Offset_componentutils_serializer.write(valueSerializer, valueHolderForScreenOffset)
        const valueHolderForTranslate = value.translate
        TranslateResult_serializer.write(valueSerializer, valueHolderForTranslate)
        const valueHolderForScale = value.scale
        ScaleResult_serializer.write(valueSerializer, valueHolderForScale)
        const valueHolderForRotate = value.rotate
        RotateResult_serializer.write(valueSerializer, valueHolderForRotate)
        const valueHolderForTransform = value.transform
        const valueHolderForTransform_0 = valueHolderForTransform[0]
        valueSerializer.writeNumber(valueHolderForTransform_0)
        const valueHolderForTransform_1 = valueHolderForTransform[1]
        valueSerializer.writeNumber(valueHolderForTransform_1)
        const valueHolderForTransform_2 = valueHolderForTransform[2]
        valueSerializer.writeNumber(valueHolderForTransform_2)
        const valueHolderForTransform_3 = valueHolderForTransform[3]
        valueSerializer.writeNumber(valueHolderForTransform_3)
        const valueHolderForTransform_4 = valueHolderForTransform[4]
        valueSerializer.writeNumber(valueHolderForTransform_4)
        const valueHolderForTransform_5 = valueHolderForTransform[5]
        valueSerializer.writeNumber(valueHolderForTransform_5)
        const valueHolderForTransform_6 = valueHolderForTransform[6]
        valueSerializer.writeNumber(valueHolderForTransform_6)
        const valueHolderForTransform_7 = valueHolderForTransform[7]
        valueSerializer.writeNumber(valueHolderForTransform_7)
        const valueHolderForTransform_8 = valueHolderForTransform[8]
        valueSerializer.writeNumber(valueHolderForTransform_8)
        const valueHolderForTransform_9 = valueHolderForTransform[9]
        valueSerializer.writeNumber(valueHolderForTransform_9)
        const valueHolderForTransform_10 = valueHolderForTransform[10]
        valueSerializer.writeNumber(valueHolderForTransform_10)
        const valueHolderForTransform_11 = valueHolderForTransform[11]
        valueSerializer.writeNumber(valueHolderForTransform_11)
        const valueHolderForTransform_12 = valueHolderForTransform[12]
        valueSerializer.writeNumber(valueHolderForTransform_12)
        const valueHolderForTransform_13 = valueHolderForTransform[13]
        valueSerializer.writeNumber(valueHolderForTransform_13)
        const valueHolderForTransform_14 = valueHolderForTransform[14]
        valueSerializer.writeNumber(valueHolderForTransform_14)
        const valueHolderForTransform_15 = valueHolderForTransform[15]
        valueSerializer.writeNumber(valueHolderForTransform_15)
    }
    public static read(buffer: DeserializerBase): ComponentInfo {
        let valueDeserializer: DeserializerBase = buffer
        const sizeTmpResult: Size = Size_serializer.read(valueDeserializer)
        const localOffsetTmpResult: Offset_componentutils = Offset_componentutils_serializer.read(valueDeserializer)
        const windowOffsetTmpResult: Offset_componentutils = Offset_componentutils_serializer.read(valueDeserializer)
        const screenOffsetTmpResult: Offset_componentutils = Offset_componentutils_serializer.read(valueDeserializer)
        const translateTmpResult: TranslateResult = TranslateResult_serializer.read(valueDeserializer)
        const scaleTmpResult: ScaleResult = ScaleResult_serializer.read(valueDeserializer)
        const rotateTmpResult: RotateResult = RotateResult_serializer.read(valueDeserializer)
        const transformTmpBufValue0: number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue1: number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue2: number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue3: number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue4: number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue5: number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue6: number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue7: number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue8: number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue9: number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue10: number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue11: number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue12: number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue13: number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue14: number = (valueDeserializer.readNumber() as number)
        const transformTmpBufValue15: number = (valueDeserializer.readNumber() as number)
        const transformTmpResult: Matrix4Result = ([transformTmpBufValue0, transformTmpBufValue1, transformTmpBufValue2, transformTmpBufValue3, transformTmpBufValue4, transformTmpBufValue5, transformTmpBufValue6, transformTmpBufValue7, transformTmpBufValue8, transformTmpBufValue9, transformTmpBufValue10, transformTmpBufValue11, transformTmpBufValue12, transformTmpBufValue13, transformTmpBufValue14, transformTmpBufValue15] as Matrix4Result)
        let value: ComponentInfo = ({size: sizeTmpResult, localOffset: localOffsetTmpResult, windowOffset: windowOffsetTmpResult, screenOffset: screenOffsetTmpResult, translate: translateTmpResult, scale: scaleTmpResult, rotate: rotateTmpResult, transform: transformTmpResult} as ComponentInfo)
        return value
    }
}
export class NodeEdgesLengthMetrics_serializer {
    public static write(buffer: SerializerBase, value: NodeEdgesLengthMetrics): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForTop = value.top
        if (valueHolderForTop !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTopTmpValue = valueHolderForTop!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForTopTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLeft = value.left
        if (valueHolderForLeft !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLeftTmpValue = valueHolderForLeft!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForLeftTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBottom = value.bottom
        if (valueHolderForBottom !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBottomTmpValue = valueHolderForBottom!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForBottomTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRight = value.right
        if (valueHolderForRight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRightTmpValue = valueHolderForRight!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForRightTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): NodeEdgesLengthMetrics {
        let valueDeserializer: DeserializerBase = buffer
        const topTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let topTmpBuf: arkui_Graphics_LengthMetrics | undefined = undefined
        if ((topTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            topTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const topTmpResult: arkui_Graphics_LengthMetrics | undefined = topTmpBuf
        const leftTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let leftTmpBuf: arkui_Graphics_LengthMetrics | undefined = undefined
        if ((leftTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            leftTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const leftTmpResult: arkui_Graphics_LengthMetrics | undefined = leftTmpBuf
        const bottomTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let bottomTmpBuf: arkui_Graphics_LengthMetrics | undefined = undefined
        if ((bottomTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            bottomTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const bottomTmpResult: arkui_Graphics_LengthMetrics | undefined = bottomTmpBuf
        const rightTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let rightTmpBuf: arkui_Graphics_LengthMetrics | undefined = undefined
        if ((rightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            rightTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const rightTmpResult: arkui_Graphics_LengthMetrics | undefined = rightTmpBuf
        let value: NodeEdgesLengthMetrics = ({top: topTmpResult, left: leftTmpResult, bottom: bottomTmpResult, right: rightTmpResult} as NodeEdgesLengthMetrics)
        return value
    }
}
export class PageRouterOptions_serializer {
    public static write(buffer: SerializerBase, value: PageRouterOptions): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForOptions = value.options
        RouterOptionsInner_serializer.write(valueSerializer, valueHolderForOptions)
        const valueHolderForMode = value.mode
        if (valueHolderForMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForModeTmpValue = (valueHolderForMode as router.RouterMode)
            valueSerializer.writeInt32(valueHolderForModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): PageRouterOptions {
        let valueDeserializer: DeserializerBase = buffer
        const optionsTmpResult: RouterOptionsInner = RouterOptionsInner_serializer.read(valueDeserializer)
        const modeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let modeTmpBuf: router.RouterMode | undefined = undefined
        if ((modeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            modeTmpBuf = router.RouterMode.fromValue(valueDeserializer.readInt32())
        }
        const modeTmpResult: router.RouterMode | undefined = modeTmpBuf
        let value: PageRouterOptions = ({options: optionsTmpResult, mode: modeTmpResult} as PageRouterOptions)
        return value
    }
}
export class ParticleAnnulusRegionInner_serializer {
    public static write(buffer: SerializerBase, value: ParticleAnnulusRegionInner): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForCenter = value.center
        if (valueHolderForCenter !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCenterTmpValue = valueHolderForCenter!
            PositionLengthMetricsInner_serializer.write(valueSerializer, valueHolderForCenterTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOuterRadius = value.outerRadius
        arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForOuterRadius)
        const valueHolderForInnerRadius = value.innerRadius
        arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForInnerRadius)
        const valueHolderForStartAngle = value.startAngle
        if (valueHolderForStartAngle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStartAngleTmpValue = valueHolderForStartAngle!
            valueSerializer.writeFloat64(valueHolderForStartAngleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEndAngle = value.endAngle
        if (valueHolderForEndAngle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEndAngleTmpValue = valueHolderForEndAngle!
            valueSerializer.writeFloat64(valueHolderForEndAngleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ParticleAnnulusRegionInner {
        let valueDeserializer: DeserializerBase = buffer
        const centerTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let centerTmpBuf: PositionLengthMetricsInner | undefined = undefined
        if ((centerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            centerTmpBuf = PositionLengthMetricsInner_serializer.read(valueDeserializer)
        }
        const centerTmpResult: PositionLengthMetricsInner | undefined = centerTmpBuf
        const outerRadiusTmpResult: arkui_Graphics_LengthMetrics = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        const innerRadiusTmpResult: arkui_Graphics_LengthMetrics = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        const startAngleTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let startAngleTmpBuf: double | undefined = undefined
        if ((startAngleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            startAngleTmpBuf = valueDeserializer.readFloat64()
        }
        const startAngleTmpResult: double | undefined = startAngleTmpBuf
        const endAngleTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let endAngleTmpBuf: double | undefined = undefined
        if ((endAngleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            endAngleTmpBuf = valueDeserializer.readFloat64()
        }
        const endAngleTmpResult: double | undefined = endAngleTmpBuf
        let value: ParticleAnnulusRegionInner = ({center: centerTmpResult, outerRadius: outerRadiusTmpResult, innerRadius: innerRadiusTmpResult, startAngle: startAngleTmpResult, endAngle: endAngleTmpResult} as ParticleAnnulusRegionInner)
        return value
    }
}
export class ParticleColorUpdaterOptionsInner_serializer {
    public static write(buffer: SerializerBase, value: ParticleColorUpdaterOptionsInner): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForType = value.type
        valueSerializer.writeInt32(valueHolderForType.getOrdinal())
        const valueHolderForConfig = value.config
        if (valueHolderForConfig !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForConfigTmpValue = valueHolderForConfig!
            if (valueHolderForConfigTmpValue instanceof ParticleColorOptions) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForConfigTmpValueForIdx0 = valueHolderForConfigTmpValue as ParticleColorOptions
                ParticleColorOptions_serializer.write(valueSerializer, valueHolderForConfigTmpValueForIdx0)
            } else if (valueHolderForConfigTmpValue instanceof Array) {
                if (valueHolderForConfigTmpValue.length == 0) {
                    valueSerializer.writeInt8((1).toByte())
                    valueSerializer.writeInt32(0)
                } else {
                    const valueHolderForConfigTmpValueElem = valueHolderForConfigTmpValue[0]
                    if (valueHolderForConfigTmpValueElem instanceof ParticlePropertyAnimationColorInner) {
                        valueSerializer.writeInt8((1).toByte())
                        const valueHolderForConfigTmpValueForIdx1 = valueHolderForConfigTmpValue as Array<ParticlePropertyAnimationColorInner>
                        valueSerializer.writeInt32((valueHolderForConfigTmpValueForIdx1.length).toInt())
                        for (let valueHolderForConfigTmpValueForIdx1CounterI = 0; valueHolderForConfigTmpValueForIdx1CounterI < valueHolderForConfigTmpValueForIdx1.length; valueHolderForConfigTmpValueForIdx1CounterI++) {
                            const valueHolderForConfigTmpValueForIdx1TmpElement: ParticlePropertyAnimationColorInner = valueHolderForConfigTmpValueForIdx1[valueHolderForConfigTmpValueForIdx1CounterI]
                            ParticlePropertyAnimationColorInner_serializer.write(valueSerializer, valueHolderForConfigTmpValueForIdx1TmpElement)
                        }
                    }
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ParticleColorUpdaterOptionsInner {
        let valueDeserializer: DeserializerBase = buffer
        const typeTmpResult: ParticleUpdater = ParticleUpdater.values()[valueDeserializer.readInt32()]
        const configTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let configTmpBuf: ParticleColorOptions | Array<ParticlePropertyAnimationColorInner> | undefined = undefined
        if ((configTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const configTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let configTmpBufOpt: ParticleColorOptions | Array<ParticlePropertyAnimationColorInner> | undefined
            if (configTmpBufOptUnionSelector == (0).toByte()) {
                configTmpBufOpt = ParticleColorOptions_serializer.read(valueDeserializer)
            } else if (configTmpBufOptUnionSelector == (1).toByte()) {
                const configTmpBufOptBufULength: int32 = valueDeserializer.readInt32()
                let configTmpBufOptBufU: Array<ParticlePropertyAnimationColorInner> = new Array<ParticlePropertyAnimationColorInner>(configTmpBufOptBufULength)
                for (let configTmpBufOptBufUBufCounterI = 0; configTmpBufOptBufUBufCounterI < configTmpBufOptBufULength; configTmpBufOptBufUBufCounterI++) {
                    configTmpBufOptBufU[configTmpBufOptBufUBufCounterI] = ParticlePropertyAnimationColorInner_serializer.read(valueDeserializer)
                }
                configTmpBufOpt = configTmpBufOptBufU
            } else {
                throw new Error('One of the branches for configTmpBufOpt has to be chosen through deserialisation.')
            }
            configTmpBuf = (configTmpBufOpt as ParticleColorOptions | Array<ParticlePropertyAnimationColorInner>)
        }
        const configTmpResult: ParticleColorPropertyUpdaterConfigsInner = configTmpBuf
        let value: ParticleColorUpdaterOptionsInner = ({type: typeTmpResult, config: configTmpResult} as ParticleColorUpdaterOptionsInner)
        return value
    }
}
export class ParticlePropertyAnimationColorInner_serializer {
    public static write(buffer: SerializerBase, value: ParticlePropertyAnimationColorInner): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForFrom = value.from
        if (valueHolderForFrom instanceof arkui_component_enums_Color) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForFromForIdx0 = valueHolderForFrom as arkui_component_enums_Color
            valueSerializer.writeInt32((valueHolderForFromForIdx0.getOrdinal()) % (12))
        } else if (valueHolderForFrom instanceof int32) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForFromForIdx1 = valueHolderForFrom as int32
            valueSerializer.writeInt32(valueHolderForFromForIdx1)
        } else if (valueHolderForFrom instanceof string) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForFromForIdx2 = valueHolderForFrom as string
            valueSerializer.writeString(valueHolderForFromForIdx2)
        } else if (valueHolderForFrom instanceof arkui_component_units_Resource) {
            valueSerializer.writeInt8((3).toByte())
            const valueHolderForFromForIdx3 = valueHolderForFrom as arkui_component_units_Resource
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForFromForIdx3)
        }
        const valueHolderForTo = value.to
        if (valueHolderForTo instanceof arkui_component_enums_Color) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForToForIdx0 = valueHolderForTo as arkui_component_enums_Color
            valueSerializer.writeInt32((valueHolderForToForIdx0.getOrdinal()) % (12))
        } else if (valueHolderForTo instanceof int32) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForToForIdx1 = valueHolderForTo as int32
            valueSerializer.writeInt32(valueHolderForToForIdx1)
        } else if (valueHolderForTo instanceof string) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForToForIdx2 = valueHolderForTo as string
            valueSerializer.writeString(valueHolderForToForIdx2)
        } else if (valueHolderForTo instanceof arkui_component_units_Resource) {
            valueSerializer.writeInt8((3).toByte())
            const valueHolderForToForIdx3 = valueHolderForTo as arkui_component_units_Resource
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForToForIdx3)
        }
        const valueHolderForStartMillis = value.startMillis
        valueSerializer.writeInt32(valueHolderForStartMillis)
        const valueHolderForEndMillis = value.endMillis
        valueSerializer.writeInt32(valueHolderForEndMillis)
        const valueHolderForCurve = value.curve
        if (valueHolderForCurve !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCurveTmpValue = valueHolderForCurve!
            if (valueHolderForCurveTmpValue instanceof Curve) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForCurveTmpValueForIdx0 = valueHolderForCurveTmpValue as Curve
                valueSerializer.writeInt32(valueHolderForCurveTmpValueForIdx0.valueOf())
            } else if (valueHolderForCurveTmpValue instanceof ICurve) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForCurveTmpValueForIdx1 = valueHolderForCurveTmpValue as ICurve
                curves_ICurve_serializer.write(valueSerializer, valueHolderForCurveTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ParticlePropertyAnimationColorInner {
        let valueDeserializer: DeserializerBase = buffer
        const fromTmpBufUnionSelector: int32 = valueDeserializer.readInt8()
        let fromTmpBuf: arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
        if (fromTmpBufUnionSelector == (0).toByte()) {
            fromTmpBuf = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
        } else if (fromTmpBufUnionSelector == (1).toByte()) {
            fromTmpBuf = valueDeserializer.readInt32()
        } else if (fromTmpBufUnionSelector == (2).toByte()) {
            fromTmpBuf = (valueDeserializer.readString() as string)
        } else if (fromTmpBufUnionSelector == (3).toByte()) {
            fromTmpBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for fromTmpBuf has to be chosen through deserialisation.')
        }
        const fromTmpResult: ResourceColor = (fromTmpBuf as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        const toTmpBufUnionSelector: int32 = valueDeserializer.readInt8()
        let toTmpBuf: arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
        if (toTmpBufUnionSelector == (0).toByte()) {
            toTmpBuf = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
        } else if (toTmpBufUnionSelector == (1).toByte()) {
            toTmpBuf = valueDeserializer.readInt32()
        } else if (toTmpBufUnionSelector == (2).toByte()) {
            toTmpBuf = (valueDeserializer.readString() as string)
        } else if (toTmpBufUnionSelector == (3).toByte()) {
            toTmpBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for toTmpBuf has to be chosen through deserialisation.')
        }
        const toTmpResult: ResourceColor = (toTmpBuf as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        const startMillisTmpResult: int32 = valueDeserializer.readInt32()
        const endMillisTmpResult: int32 = valueDeserializer.readInt32()
        const curveTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let curveTmpBuf: Curve | ICurve | undefined = undefined
        if ((curveTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const curveTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let curveTmpBufOpt: Curve | ICurve | undefined
            if (curveTmpBufOptUnionSelector == (0).toByte()) {
                curveTmpBufOpt = curves.Curve.fromValue(valueDeserializer.readInt32())
            } else if (curveTmpBufOptUnionSelector == (1).toByte()) {
                curveTmpBufOpt = (curves_ICurve_serializer.read(valueDeserializer) as curves.ICurve)
            } else {
                throw new Error('One of the branches for curveTmpBufOpt has to be chosen through deserialisation.')
            }
            curveTmpBuf = (curveTmpBufOpt as Curve | ICurve)
        }
        const curveTmpResult: Curve | ICurve | undefined = curveTmpBuf
        let value: ParticlePropertyAnimationColorInner = ({from: fromTmpResult, to: toTmpResult, startMillis: startMillisTmpResult, endMillis: endMillisTmpResult, curve: curveTmpResult} as ParticlePropertyAnimationColorInner)
        return value
    }
}
export class ParticleUpdaterOptionsInner_serializer {
    public static write(buffer: SerializerBase, value: ParticleUpdaterOptionsInner): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForType = value.type
        valueSerializer.writeInt32(valueHolderForType.getOrdinal())
        const valueHolderForConfig = value.config
        if (valueHolderForConfig !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForConfigTmpValue = valueHolderForConfig!
            if (valueHolderForConfigTmpValue instanceof [ double, double ]) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForConfigTmpValueForIdx0 = valueHolderForConfigTmpValue as [ double, double ]
                const valueHolderForConfigTmpValueForIdx0_0 = valueHolderForConfigTmpValueForIdx0[0]
                valueSerializer.writeFloat64(valueHolderForConfigTmpValueForIdx0_0)
                const valueHolderForConfigTmpValueForIdx0_1 = valueHolderForConfigTmpValueForIdx0[1]
                valueSerializer.writeFloat64(valueHolderForConfigTmpValueForIdx0_1)
            } else if (valueHolderForConfigTmpValue instanceof Array) {
                if (valueHolderForConfigTmpValue.length == 0) {
                    valueSerializer.writeInt8((1).toByte())
                    valueSerializer.writeInt32(0)
                } else {
                    const valueHolderForConfigTmpValueElem = valueHolderForConfigTmpValue[0]
                    if (valueHolderForConfigTmpValueElem instanceof ParticlePropertyAnimationNumberInner) {
                        valueSerializer.writeInt8((1).toByte())
                        const valueHolderForConfigTmpValueForIdx1 = valueHolderForConfigTmpValue as Array<ParticlePropertyAnimationNumberInner>
                        valueSerializer.writeInt32((valueHolderForConfigTmpValueForIdx1.length).toInt())
                        for (let valueHolderForConfigTmpValueForIdx1CounterI = 0; valueHolderForConfigTmpValueForIdx1CounterI < valueHolderForConfigTmpValueForIdx1.length; valueHolderForConfigTmpValueForIdx1CounterI++) {
                            const valueHolderForConfigTmpValueForIdx1TmpElement: ParticlePropertyAnimationNumberInner = valueHolderForConfigTmpValueForIdx1[valueHolderForConfigTmpValueForIdx1CounterI]
                            ParticlePropertyAnimationNumberInner_serializer.write(valueSerializer, valueHolderForConfigTmpValueForIdx1TmpElement)
                        }
                    }
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ParticleUpdaterOptionsInner {
        let valueDeserializer: DeserializerBase = buffer
        const typeTmpResult: ParticleUpdater = ParticleUpdater.values()[valueDeserializer.readInt32()]
        const configTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let configTmpBuf: [ double, double ] | Array<ParticlePropertyAnimationNumberInner> | undefined = undefined
        if ((configTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const configTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let configTmpBufOpt: [ double, double ] | Array<ParticlePropertyAnimationNumberInner> | undefined
            if (configTmpBufOptUnionSelector == (0).toByte()) {
                const configTmpBufOptBufUValue0: double = valueDeserializer.readFloat64()
                const configTmpBufOptBufUValue1: double = valueDeserializer.readFloat64()
                configTmpBufOpt = ([configTmpBufOptBufUValue0, configTmpBufOptBufUValue1] as [ double, double ])
            } else if (configTmpBufOptUnionSelector == (1).toByte()) {
                const configTmpBufOptBufULength: int32 = valueDeserializer.readInt32()
                let configTmpBufOptBufU: Array<ParticlePropertyAnimationNumberInner> = new Array<ParticlePropertyAnimationNumberInner>(configTmpBufOptBufULength)
                for (let configTmpBufOptBufUBufCounterI = 0; configTmpBufOptBufUBufCounterI < configTmpBufOptBufULength; configTmpBufOptBufUBufCounterI++) {
                    configTmpBufOptBufU[configTmpBufOptBufUBufCounterI] = ParticlePropertyAnimationNumberInner_serializer.read(valueDeserializer)
                }
                configTmpBufOpt = configTmpBufOptBufU
            } else {
                throw new Error('One of the branches for configTmpBufOpt has to be chosen through deserialisation.')
            }
            configTmpBuf = (configTmpBufOpt as [ double, double ] | Array<ParticlePropertyAnimationNumberInner>)
        }
        const configTmpResult: ParticlePropertyUpdaterConfigsInner = configTmpBuf
        let value: ParticleUpdaterOptionsInner = ({type: typeTmpResult, config: configTmpResult} as ParticleUpdaterOptionsInner)
        return value
    }
}
export class RippleFieldOptionsInner_serializer {
    public static write(buffer: SerializerBase, value: RippleFieldOptionsInner): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForAmplitude = value.amplitude
        if (valueHolderForAmplitude !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAmplitudeTmpValue = valueHolderForAmplitude!
            valueSerializer.writeFloat64(valueHolderForAmplitudeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWavelength = value.wavelength
        if (valueHolderForWavelength !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWavelengthTmpValue = valueHolderForWavelength!
            valueSerializer.writeFloat64(valueHolderForWavelengthTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWaveSpeed = value.waveSpeed
        if (valueHolderForWaveSpeed !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWaveSpeedTmpValue = valueHolderForWaveSpeed!
            valueSerializer.writeFloat64(valueHolderForWaveSpeedTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAttenuation = value.attenuation
        if (valueHolderForAttenuation !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAttenuationTmpValue = valueHolderForAttenuation!
            valueSerializer.writeFloat64(valueHolderForAttenuationTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCenter = value.center
        if (valueHolderForCenter !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCenterTmpValue = valueHolderForCenter!
            PositionF64Inner_serializer.write(valueSerializer, valueHolderForCenterTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRegion = value.region
        if (valueHolderForRegion !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRegionTmpValue = valueHolderForRegion!
            FieldRegionInner_serializer.write(valueSerializer, valueHolderForRegionTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): RippleFieldOptionsInner {
        let valueDeserializer: DeserializerBase = buffer
        const amplitudeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let amplitudeTmpBuf: double | undefined = undefined
        if ((amplitudeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            amplitudeTmpBuf = valueDeserializer.readFloat64()
        }
        const amplitudeTmpResult: double | undefined = amplitudeTmpBuf
        const wavelengthTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let wavelengthTmpBuf: double | undefined = undefined
        if ((wavelengthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            wavelengthTmpBuf = valueDeserializer.readFloat64()
        }
        const wavelengthTmpResult: double | undefined = wavelengthTmpBuf
        const waveSpeedTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let waveSpeedTmpBuf: double | undefined = undefined
        if ((waveSpeedTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            waveSpeedTmpBuf = valueDeserializer.readFloat64()
        }
        const waveSpeedTmpResult: double | undefined = waveSpeedTmpBuf
        const attenuationTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let attenuationTmpBuf: double | undefined = undefined
        if ((attenuationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            attenuationTmpBuf = valueDeserializer.readFloat64()
        }
        const attenuationTmpResult: double | undefined = attenuationTmpBuf
        const centerTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let centerTmpBuf: PositionF64Inner | undefined = undefined
        if ((centerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            centerTmpBuf = PositionF64Inner_serializer.read(valueDeserializer)
        }
        const centerTmpResult: PositionF64Inner | undefined = centerTmpBuf
        const regionTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let regionTmpBuf: FieldRegionInner | undefined = undefined
        if ((regionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            regionTmpBuf = FieldRegionInner_serializer.read(valueDeserializer)
        }
        const regionTmpResult: FieldRegionInner | undefined = regionTmpBuf
        let value: RippleFieldOptionsInner = ({amplitude: amplitudeTmpResult, wavelength: wavelengthTmpResult, waveSpeed: waveSpeedTmpResult, attenuation: attenuationTmpResult, center: centerTmpResult, region: regionTmpResult} as RippleFieldOptionsInner)
        return value
    }
}
export class VelocityFieldOptionsInner_serializer {
    public static write(buffer: SerializerBase, value: VelocityFieldOptionsInner): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForVelocity = value.velocity
        if (valueHolderForVelocity !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForVelocityTmpValue = valueHolderForVelocity!
            Vector2F64_serializer.write(valueSerializer, valueHolderForVelocityTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRegion = value.region
        if (valueHolderForRegion !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRegionTmpValue = valueHolderForRegion!
            FieldRegionInner_serializer.write(valueSerializer, valueHolderForRegionTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): VelocityFieldOptionsInner {
        let valueDeserializer: DeserializerBase = buffer
        const velocityTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let velocityTmpBuf: Vector2F64 | undefined = undefined
        if ((velocityTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            velocityTmpBuf = Vector2F64_serializer.read(valueDeserializer)
        }
        const velocityTmpResult: Vector2F64 | undefined = velocityTmpBuf
        const regionTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let regionTmpBuf: FieldRegionInner | undefined = undefined
        if ((regionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            regionTmpBuf = FieldRegionInner_serializer.read(valueDeserializer)
        }
        const regionTmpResult: FieldRegionInner | undefined = regionTmpBuf
        let value: VelocityFieldOptionsInner = ({velocity: velocityTmpResult, region: regionTmpResult} as VelocityFieldOptionsInner)
        return value
    }
}
export class EmitterPropertyInner_serializer {
    public static write(buffer: SerializerBase, value: EmitterPropertyInner): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForIndex = value.index
        valueSerializer.writeInt32(valueHolderForIndex)
        const valueHolderForEmitRate = value.emitRate
        if (valueHolderForEmitRate !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEmitRateTmpValue = valueHolderForEmitRate!
            valueSerializer.writeInt32(valueHolderForEmitRateTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPosition = value.position
        if (valueHolderForPosition !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPositionTmpValue = valueHolderForPosition!
            PositionF64Inner_serializer.write(valueSerializer, valueHolderForPositionTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSize = value.size
        if (valueHolderForSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSizeTmpValue = valueHolderForSize!
            SizeF64Inner_serializer.write(valueSerializer, valueHolderForSizeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAnnulusRegion = value.annulusRegion
        if (valueHolderForAnnulusRegion !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAnnulusRegionTmpValue = valueHolderForAnnulusRegion!
            ParticleAnnulusRegionInner_serializer.write(valueSerializer, valueHolderForAnnulusRegionTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): EmitterPropertyInner {
        let valueDeserializer: DeserializerBase = buffer
        const indexTmpResult: int32 = valueDeserializer.readInt32()
        const emitRateTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let emitRateTmpBuf: int32 | undefined = undefined
        if ((emitRateTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            emitRateTmpBuf = valueDeserializer.readInt32()
        }
        const emitRateTmpResult: int32 | undefined = emitRateTmpBuf
        const positionTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let positionTmpBuf: PositionF64Inner | undefined = undefined
        if ((positionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            positionTmpBuf = PositionF64Inner_serializer.read(valueDeserializer)
        }
        const positionTmpResult: PositionF64Inner | undefined = positionTmpBuf
        const sizeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let sizeTmpBuf: SizeF64Inner | undefined = undefined
        if ((sizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            sizeTmpBuf = SizeF64Inner_serializer.read(valueDeserializer)
        }
        const sizeTmpResult: SizeF64Inner | undefined = sizeTmpBuf
        const annulusRegionTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let annulusRegionTmpBuf: ParticleAnnulusRegionInner | undefined = undefined
        if ((annulusRegionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            annulusRegionTmpBuf = ParticleAnnulusRegionInner_serializer.read(valueDeserializer)
        }
        const annulusRegionTmpResult: ParticleAnnulusRegionInner | undefined = annulusRegionTmpBuf
        let value: EmitterPropertyInner = ({index: indexTmpResult, emitRate: emitRateTmpResult, position: positionTmpResult, size: sizeTmpResult, annulusRegion: annulusRegionTmpResult} as EmitterPropertyInner)
        return value
    }
}
export class ParticleColorPropertyOptionsInner_serializer {
    public static write(buffer: SerializerBase, value: ParticleColorPropertyOptionsInner): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForRange = value.range
        const valueHolderForRange_0 = valueHolderForRange[0]
        if (valueHolderForRange_0 instanceof arkui_component_enums_Color) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForRange_0ForIdx0 = valueHolderForRange_0 as arkui_component_enums_Color
            valueSerializer.writeInt32((valueHolderForRange_0ForIdx0.getOrdinal()) % (12))
        } else if (valueHolderForRange_0 instanceof int32) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForRange_0ForIdx1 = valueHolderForRange_0 as int32
            valueSerializer.writeInt32(valueHolderForRange_0ForIdx1)
        } else if (valueHolderForRange_0 instanceof string) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForRange_0ForIdx2 = valueHolderForRange_0 as string
            valueSerializer.writeString(valueHolderForRange_0ForIdx2)
        } else if (valueHolderForRange_0 instanceof arkui_component_units_Resource) {
            valueSerializer.writeInt8((3).toByte())
            const valueHolderForRange_0ForIdx3 = valueHolderForRange_0 as arkui_component_units_Resource
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForRange_0ForIdx3)
        }
        const valueHolderForRange_1 = valueHolderForRange[1]
        if (valueHolderForRange_1 instanceof arkui_component_enums_Color) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForRange_1ForIdx0 = valueHolderForRange_1 as arkui_component_enums_Color
            valueSerializer.writeInt32((valueHolderForRange_1ForIdx0.getOrdinal()) % (12))
        } else if (valueHolderForRange_1 instanceof int32) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForRange_1ForIdx1 = valueHolderForRange_1 as int32
            valueSerializer.writeInt32(valueHolderForRange_1ForIdx1)
        } else if (valueHolderForRange_1 instanceof string) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForRange_1ForIdx2 = valueHolderForRange_1 as string
            valueSerializer.writeString(valueHolderForRange_1ForIdx2)
        } else if (valueHolderForRange_1 instanceof arkui_component_units_Resource) {
            valueSerializer.writeInt8((3).toByte())
            const valueHolderForRange_1ForIdx3 = valueHolderForRange_1 as arkui_component_units_Resource
            global_resource_Resource_serializer.write(valueSerializer, valueHolderForRange_1ForIdx3)
        }
        const valueHolderForDistributionType = value.distributionType
        if (valueHolderForDistributionType !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDistributionTypeTmpValue = (valueHolderForDistributionType as DistributionType)
            valueSerializer.writeInt32(valueHolderForDistributionTypeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForUpdater = value.updater
        if (valueHolderForUpdater !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUpdaterTmpValue = valueHolderForUpdater!
            ParticleColorUpdaterOptionsInner_serializer.write(valueSerializer, valueHolderForUpdaterTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ParticleColorPropertyOptionsInner {
        let valueDeserializer: DeserializerBase = buffer
        const rangeTmpBufValue0TempBufUnionSelector: int32 = valueDeserializer.readInt8()
        let rangeTmpBufValue0TempBuf: arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
        if (rangeTmpBufValue0TempBufUnionSelector == (0).toByte()) {
            rangeTmpBufValue0TempBuf = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
        } else if (rangeTmpBufValue0TempBufUnionSelector == (1).toByte()) {
            rangeTmpBufValue0TempBuf = valueDeserializer.readInt32()
        } else if (rangeTmpBufValue0TempBufUnionSelector == (2).toByte()) {
            rangeTmpBufValue0TempBuf = (valueDeserializer.readString() as string)
        } else if (rangeTmpBufValue0TempBufUnionSelector == (3).toByte()) {
            rangeTmpBufValue0TempBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for rangeTmpBufValue0TempBuf has to be chosen through deserialisation.')
        }
        const rangeTmpBufValue0: ResourceColor = (rangeTmpBufValue0TempBuf as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        const rangeTmpBufValue1TempBufUnionSelector: int32 = valueDeserializer.readInt8()
        let rangeTmpBufValue1TempBuf: arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
        if (rangeTmpBufValue1TempBufUnionSelector == (0).toByte()) {
            rangeTmpBufValue1TempBuf = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
        } else if (rangeTmpBufValue1TempBufUnionSelector == (1).toByte()) {
            rangeTmpBufValue1TempBuf = valueDeserializer.readInt32()
        } else if (rangeTmpBufValue1TempBufUnionSelector == (2).toByte()) {
            rangeTmpBufValue1TempBuf = (valueDeserializer.readString() as string)
        } else if (rangeTmpBufValue1TempBufUnionSelector == (3).toByte()) {
            rangeTmpBufValue1TempBuf = global_resource_Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error('One of the branches for rangeTmpBufValue1TempBuf has to be chosen through deserialisation.')
        }
        const rangeTmpBufValue1: ResourceColor = (rangeTmpBufValue1TempBuf as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        const rangeTmpResult: [ ResourceColor, ResourceColor ] = ([rangeTmpBufValue0, rangeTmpBufValue1] as [ ResourceColor, ResourceColor ])
        const distributionTypeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let distributionTypeTmpBuf: DistributionType | undefined = undefined
        if ((distributionTypeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            distributionTypeTmpBuf = DistributionType.fromValue(valueDeserializer.readInt32())
        }
        const distributionTypeTmpResult: DistributionType | undefined = distributionTypeTmpBuf
        const updaterTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let updaterTmpBuf: ParticleColorUpdaterOptionsInner | undefined = undefined
        if ((updaterTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            updaterTmpBuf = ParticleColorUpdaterOptionsInner_serializer.read(valueDeserializer)
        }
        const updaterTmpResult: ParticleColorUpdaterOptionsInner | undefined = updaterTmpBuf
        let value: ParticleColorPropertyOptionsInner = ({range: rangeTmpResult, distributionType: distributionTypeTmpResult, updater: updaterTmpResult} as ParticleColorPropertyOptionsInner)
        return value
    }
}
export class ParticlePropertyOptionsInner_serializer {
    public static write(buffer: SerializerBase, value: ParticlePropertyOptionsInner): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForRange = value.range
        const valueHolderForRange_0 = valueHolderForRange[0]
        valueSerializer.writeFloat64(valueHolderForRange_0)
        const valueHolderForRange_1 = valueHolderForRange[1]
        valueSerializer.writeFloat64(valueHolderForRange_1)
        const valueHolderForUpdater = value.updater
        if (valueHolderForUpdater !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUpdaterTmpValue = valueHolderForUpdater!
            ParticleUpdaterOptionsInner_serializer.write(valueSerializer, valueHolderForUpdaterTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ParticlePropertyOptionsInner {
        let valueDeserializer: DeserializerBase = buffer
        const rangeTmpBufValue0: double = valueDeserializer.readFloat64()
        const rangeTmpBufValue1: double = valueDeserializer.readFloat64()
        const rangeTmpResult: [ double, double ] = ([rangeTmpBufValue0, rangeTmpBufValue1] as [ double, double ])
        const updaterTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let updaterTmpBuf: ParticleUpdaterOptionsInner | undefined = undefined
        if ((updaterTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            updaterTmpBuf = ParticleUpdaterOptionsInner_serializer.read(valueDeserializer)
        }
        const updaterTmpResult: ParticleUpdaterOptionsInner | undefined = updaterTmpBuf
        let value: ParticlePropertyOptionsInner = ({range: rangeTmpResult, updater: updaterTmpResult} as ParticlePropertyOptionsInner)
        return value
    }
}
export class AccelerationOptionsInner_serializer {
    public static write(buffer: SerializerBase, value: AccelerationOptionsInner): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForSpeed = value.speed
        if (valueHolderForSpeed !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSpeedTmpValue = valueHolderForSpeed!
            ParticlePropertyOptionsInner_serializer.write(valueSerializer, valueHolderForSpeedTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAngle = value.angle
        if (valueHolderForAngle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAngleTmpValue = valueHolderForAngle!
            ParticlePropertyOptionsInner_serializer.write(valueSerializer, valueHolderForAngleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): AccelerationOptionsInner {
        let valueDeserializer: DeserializerBase = buffer
        const speedTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let speedTmpBuf: ParticlePropertyOptionsInner | undefined = undefined
        if ((speedTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            speedTmpBuf = ParticlePropertyOptionsInner_serializer.read(valueDeserializer)
        }
        const speedTmpResult: ParticlePropertyOptionsInner | undefined = speedTmpBuf
        const angleTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let angleTmpBuf: ParticlePropertyOptionsInner | undefined = undefined
        if ((angleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            angleTmpBuf = ParticlePropertyOptionsInner_serializer.read(valueDeserializer)
        }
        const angleTmpResult: ParticlePropertyOptionsInner | undefined = angleTmpBuf
        let value: AccelerationOptionsInner = ({speed: speedTmpResult, angle: angleTmpResult} as AccelerationOptionsInner)
        return value
    }
}
export class CustomDialogControllerOptionsExtender_serializer {
    public static write(buffer: SerializerBase, value: CustomDialogControllerOptionsExtender): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForBuilder = value.builder
        valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueHolderForBuilder))
        const valueHolderForCancel = value.cancel
        if (valueHolderForCancel !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCancelTmpValue = valueHolderForCancel!
            valueSerializer.holdAndWriteCallback(valueHolderForCancelTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAutoCancel = value.autoCancel
        if (valueHolderForAutoCancel !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAutoCancelTmpValue = valueHolderForAutoCancel!
            valueSerializer.writeBoolean(valueHolderForAutoCancelTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAlignment = value.alignment
        if (valueHolderForAlignment !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAlignmentTmpValue = (valueHolderForAlignment as DialogAlignment)
            valueSerializer.writeInt32(valueHolderForAlignmentTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOffset = value.offset
        if (valueHolderForOffset !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOffsetTmpValue = valueHolderForOffset!
            Offset_serializer.write(valueSerializer, valueHolderForOffsetTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCustomStyle = value.customStyle
        if (valueHolderForCustomStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCustomStyleTmpValue = valueHolderForCustomStyle!
            valueSerializer.writeBoolean(valueHolderForCustomStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForGridCount = value.gridCount
        if (valueHolderForGridCount !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForGridCountTmpValue = valueHolderForGridCount!
            valueSerializer.writeInt32(valueHolderForGridCountTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMaskColor = value.maskColor
        if (valueHolderForMaskColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaskColorTmpValue = valueHolderForMaskColor!
            if (valueHolderForMaskColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForMaskColorTmpValueForIdx0 = valueHolderForMaskColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForMaskColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForMaskColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForMaskColorTmpValueForIdx1 = valueHolderForMaskColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForMaskColorTmpValueForIdx1)
            } else if (valueHolderForMaskColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForMaskColorTmpValueForIdx2 = valueHolderForMaskColorTmpValue as string
                valueSerializer.writeString(valueHolderForMaskColorTmpValueForIdx2)
            } else if (valueHolderForMaskColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForMaskColorTmpValueForIdx3 = valueHolderForMaskColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForMaskColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMaskRect = value.maskRect
        if (valueHolderForMaskRect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaskRectTmpValue = valueHolderForMaskRect!
            Rectangle_serializer.write(valueSerializer, valueHolderForMaskRectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOpenAnimation = value.openAnimation
        if (valueHolderForOpenAnimation !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOpenAnimationTmpValue = valueHolderForOpenAnimation!
            AnimateParam_serializer.write(valueSerializer, valueHolderForOpenAnimationTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCloseAnimation = value.closeAnimation
        if (valueHolderForCloseAnimation !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCloseAnimationTmpValue = valueHolderForCloseAnimation!
            AnimateParam_serializer.write(valueSerializer, valueHolderForCloseAnimationTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShowInSubWindow = value.showInSubWindow
        if (valueHolderForShowInSubWindow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShowInSubWindowTmpValue = valueHolderForShowInSubWindow!
            valueSerializer.writeBoolean(valueHolderForShowInSubWindowTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundColor = value.backgroundColor
        if (valueHolderForBackgroundColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundColorTmpValue = valueHolderForBackgroundColor!
            if (valueHolderForBackgroundColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx0 = valueHolderForBackgroundColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForBackgroundColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForBackgroundColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx1 = valueHolderForBackgroundColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForBackgroundColorTmpValueForIdx1)
            } else if (valueHolderForBackgroundColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx2 = valueHolderForBackgroundColorTmpValue as string
                valueSerializer.writeString(valueHolderForBackgroundColorTmpValueForIdx2)
            } else if (valueHolderForBackgroundColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForBackgroundColorTmpValueForIdx3 = valueHolderForBackgroundColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForBackgroundColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCornerRadius = value.cornerRadius
        if (valueHolderForCornerRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCornerRadiusTmpValue = valueHolderForCornerRadius!
            if (valueHolderForCornerRadiusTmpValue instanceof Dimension) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForCornerRadiusTmpValueForIdx0 = valueHolderForCornerRadiusTmpValue as Dimension
                if (valueHolderForCornerRadiusTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForCornerRadiusTmpValueForIdx0ForIdx0 = valueHolderForCornerRadiusTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForCornerRadiusTmpValueForIdx0ForIdx0)
                } else if (valueHolderForCornerRadiusTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForCornerRadiusTmpValueForIdx0ForIdx1 = valueHolderForCornerRadiusTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForCornerRadiusTmpValueForIdx0ForIdx1)
                } else if (valueHolderForCornerRadiusTmpValueForIdx0 instanceof global_resource_Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForCornerRadiusTmpValueForIdx0ForIdx2 = valueHolderForCornerRadiusTmpValueForIdx0 as global_resource_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForCornerRadiusTmpValueForIdx0ForIdx2)
                }
            } else if (valueHolderForCornerRadiusTmpValue instanceof BorderRadiuses) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForCornerRadiusTmpValueForIdx1 = valueHolderForCornerRadiusTmpValue as BorderRadiuses
                BorderRadiuses_serializer.write(valueSerializer, valueHolderForCornerRadiusTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForIsModal = value.isModal
        if (valueHolderForIsModal !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIsModalTmpValue = valueHolderForIsModal!
            valueSerializer.writeBoolean(valueHolderForIsModalTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnWillDismiss = value.onWillDismiss
        if (valueHolderForOnWillDismiss !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnWillDismissTmpValue = valueHolderForOnWillDismiss!
            valueSerializer.holdAndWriteCallback(valueHolderForOnWillDismissTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWidth = value.width
        if (valueHolderForWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWidthTmpValue = valueHolderForWidth!
            if (valueHolderForWidthTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForWidthTmpValueForIdx0 = valueHolderForWidthTmpValue as string
                valueSerializer.writeString(valueHolderForWidthTmpValueForIdx0)
            } else if (valueHolderForWidthTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForWidthTmpValueForIdx1 = valueHolderForWidthTmpValue as number
                valueSerializer.writeNumber(valueHolderForWidthTmpValueForIdx1)
            } else if (valueHolderForWidthTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForWidthTmpValueForIdx2 = valueHolderForWidthTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForWidthTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHeight = value.height
        if (valueHolderForHeight !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHeightTmpValue = valueHolderForHeight!
            if (valueHolderForHeightTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForHeightTmpValueForIdx0 = valueHolderForHeightTmpValue as string
                valueSerializer.writeString(valueHolderForHeightTmpValueForIdx0)
            } else if (valueHolderForHeightTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForHeightTmpValueForIdx1 = valueHolderForHeightTmpValue as number
                valueSerializer.writeNumber(valueHolderForHeightTmpValueForIdx1)
            } else if (valueHolderForHeightTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForHeightTmpValueForIdx2 = valueHolderForHeightTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForHeightTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderWidth = value.borderWidth
        if (valueHolderForBorderWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderWidthTmpValue = valueHolderForBorderWidth!
            if (valueHolderForBorderWidthTmpValue instanceof Dimension) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderWidthTmpValueForIdx0 = valueHolderForBorderWidthTmpValue as Dimension
                if (valueHolderForBorderWidthTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForBorderWidthTmpValueForIdx0ForIdx0 = valueHolderForBorderWidthTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForBorderWidthTmpValueForIdx0ForIdx0)
                } else if (valueHolderForBorderWidthTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForBorderWidthTmpValueForIdx0ForIdx1 = valueHolderForBorderWidthTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForBorderWidthTmpValueForIdx0ForIdx1)
                } else if (valueHolderForBorderWidthTmpValueForIdx0 instanceof global_resource_Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForBorderWidthTmpValueForIdx0ForIdx2 = valueHolderForBorderWidthTmpValueForIdx0 as global_resource_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForBorderWidthTmpValueForIdx0ForIdx2)
                }
            } else if (valueHolderForBorderWidthTmpValue instanceof EdgeWidths) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderWidthTmpValueForIdx1 = valueHolderForBorderWidthTmpValue as EdgeWidths
                EdgeWidths_serializer.write(valueSerializer, valueHolderForBorderWidthTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderColor = value.borderColor
        if (valueHolderForBorderColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderColorTmpValue = valueHolderForBorderColor!
            if (valueHolderForBorderColorTmpValue instanceof ResourceColor) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderColorTmpValueForIdx0 = valueHolderForBorderColorTmpValue as ResourceColor
                if (valueHolderForBorderColorTmpValueForIdx0 instanceof arkui_component_enums_Color) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx0 = valueHolderForBorderColorTmpValueForIdx0 as arkui_component_enums_Color
                    valueSerializer.writeInt32((valueHolderForBorderColorTmpValueForIdx0ForIdx0.getOrdinal()) % (12))
                } else if (valueHolderForBorderColorTmpValueForIdx0 instanceof int32) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx1 = valueHolderForBorderColorTmpValueForIdx0 as int32
                    valueSerializer.writeInt32(valueHolderForBorderColorTmpValueForIdx0ForIdx1)
                } else if (valueHolderForBorderColorTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx2 = valueHolderForBorderColorTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForBorderColorTmpValueForIdx0ForIdx2)
                } else if (valueHolderForBorderColorTmpValueForIdx0 instanceof arkui_component_units_Resource) {
                    valueSerializer.writeInt8((3).toByte())
                    const valueHolderForBorderColorTmpValueForIdx0ForIdx3 = valueHolderForBorderColorTmpValueForIdx0 as arkui_component_units_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForBorderColorTmpValueForIdx0ForIdx3)
                }
            } else if (valueHolderForBorderColorTmpValue instanceof EdgeColors) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderColorTmpValueForIdx1 = valueHolderForBorderColorTmpValue as EdgeColors
                EdgeColors_serializer.write(valueSerializer, valueHolderForBorderColorTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBorderStyle = value.borderStyle
        if (valueHolderForBorderStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBorderStyleTmpValue = valueHolderForBorderStyle!
            if (valueHolderForBorderStyleTmpValue instanceof BorderStyle) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForBorderStyleTmpValueForIdx0 = valueHolderForBorderStyleTmpValue as BorderStyle
                valueSerializer.writeInt32(valueHolderForBorderStyleTmpValueForIdx0.valueOf())
            } else if (valueHolderForBorderStyleTmpValue instanceof EdgeStyles) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForBorderStyleTmpValueForIdx1 = valueHolderForBorderStyleTmpValue as EdgeStyles
                EdgeStyles_serializer.write(valueSerializer, valueHolderForBorderStyleTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShadow = value.shadow
        if (valueHolderForShadow !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShadowTmpValue = valueHolderForShadow!
            if (valueHolderForShadowTmpValue instanceof ShadowOptions) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForShadowTmpValueForIdx0 = valueHolderForShadowTmpValue as ShadowOptions
                ShadowOptions_serializer.write(valueSerializer, valueHolderForShadowTmpValueForIdx0)
            } else if (valueHolderForShadowTmpValue instanceof ShadowStyle) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForShadowTmpValueForIdx1 = valueHolderForShadowTmpValue as ShadowStyle
                valueSerializer.writeInt32(valueHolderForShadowTmpValueForIdx1.valueOf())
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundBlurStyle = value.backgroundBlurStyle
        if (valueHolderForBackgroundBlurStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundBlurStyleTmpValue = (valueHolderForBackgroundBlurStyle as BlurStyle)
            valueSerializer.writeInt32(valueHolderForBackgroundBlurStyleTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundBlurStyleOptions = value.backgroundBlurStyleOptions
        if (valueHolderForBackgroundBlurStyleOptions !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundBlurStyleOptionsTmpValue = valueHolderForBackgroundBlurStyleOptions!
            BackgroundBlurStyleOptions_serializer.write(valueSerializer, valueHolderForBackgroundBlurStyleOptionsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForBackgroundEffect = value.backgroundEffect
        if (valueHolderForBackgroundEffect !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForBackgroundEffectTmpValue = valueHolderForBackgroundEffect!
            BackgroundEffectOptions_serializer.write(valueSerializer, valueHolderForBackgroundEffectTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForKeyboardAvoidMode = value.keyboardAvoidMode
        if (valueHolderForKeyboardAvoidMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForKeyboardAvoidModeTmpValue = (valueHolderForKeyboardAvoidMode as arkui_component_common_KeyboardAvoidMode)
            valueSerializer.writeInt32(valueHolderForKeyboardAvoidModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnableHoverMode = value.enableHoverMode
        if (valueHolderForEnableHoverMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableHoverModeTmpValue = valueHolderForEnableHoverMode!
            valueSerializer.writeBoolean(valueHolderForEnableHoverModeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHoverModeArea = value.hoverModeArea
        if (valueHolderForHoverModeArea !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHoverModeAreaTmpValue = (valueHolderForHoverModeArea as HoverModeAreaType)
            valueSerializer.writeInt32(valueHolderForHoverModeAreaTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnDidAppear = value.onDidAppear
        if (valueHolderForOnDidAppear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnDidAppearTmpValue = valueHolderForOnDidAppear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnDidAppearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnDidDisappear = value.onDidDisappear
        if (valueHolderForOnDidDisappear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnDidDisappearTmpValue = valueHolderForOnDidDisappear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnDidDisappearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnWillAppear = value.onWillAppear
        if (valueHolderForOnWillAppear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnWillAppearTmpValue = valueHolderForOnWillAppear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnWillAppearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnWillDisappear = value.onWillDisappear
        if (valueHolderForOnWillDisappear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnWillDisappearTmpValue = valueHolderForOnWillDisappear!
            valueSerializer.holdAndWriteCallback(valueHolderForOnWillDisappearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForKeyboardAvoidDistance = value.keyboardAvoidDistance
        if (valueHolderForKeyboardAvoidDistance !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForKeyboardAvoidDistanceTmpValue = valueHolderForKeyboardAvoidDistance!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForKeyboardAvoidDistanceTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLevelMode = value.levelMode
        if (valueHolderForLevelMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLevelModeTmpValue = (valueHolderForLevelMode as LevelMode)
            valueSerializer.writeInt32(valueHolderForLevelModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLevelUniqueId = value.levelUniqueId
        if (valueHolderForLevelUniqueId !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLevelUniqueIdTmpValue = valueHolderForLevelUniqueId!
            valueSerializer.writeInt32(valueHolderForLevelUniqueIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForImmersiveMode = value.immersiveMode
        if (valueHolderForImmersiveMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForImmersiveModeTmpValue = (valueHolderForImmersiveMode as ImmersiveMode)
            valueSerializer.writeInt32(valueHolderForImmersiveModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLevelOrderExtender = value.levelOrderExtender
        if (valueHolderForLevelOrderExtender !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLevelOrderExtenderTmpValue = valueHolderForLevelOrderExtender!
            LevelOrderExtender_serializer.write(valueSerializer, valueHolderForLevelOrderExtenderTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFocusable = value.focusable
        if (valueHolderForFocusable !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFocusableTmpValue = valueHolderForFocusable!
            valueSerializer.writeBoolean(valueHolderForFocusableTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): CustomDialogControllerOptionsExtender {
        let valueDeserializer: DeserializerBase = buffer
        const builderTmpBufBufResource: CallbackResource = valueDeserializer.readCallbackResource()
        const builderTmpBufBufCall: KPointer = valueDeserializer.readPointer()
        const builderTmpBufBufCallSync: KPointer = valueDeserializer.readPointer()
        const builderTmpBufClosure = ():void => {
            const builderTmpBufBufArgsSerializer: SerializerBase = SerializerBase.hold();
            builderTmpBufBufArgsSerializer.writeInt32(builderTmpBufBufResource.resourceId);
            builderTmpBufBufArgsSerializer.writePointer(builderTmpBufBufCall);
            builderTmpBufBufArgsSerializer.writePointer(builderTmpBufBufCallSync);
            InteropNativeModule._CallCallbackSync(10, -1834072896, builderTmpBufBufArgsSerializer.asBuffer(), builderTmpBufBufArgsSerializer.length());
            builderTmpBufBufArgsSerializer.release();
            return;
        }
        resourceFinalizerRegister(builderTmpBufClosure, builderTmpBufBufResource)
        const builderTmpResult: CustomBuilder = builderTmpBufClosure
        const cancelTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let cancelTmpBuf: (() => void) | undefined = undefined
        if ((cancelTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const cancelTmpBufOptBufResource: CallbackResource = valueDeserializer.readCallbackResource()
            const cancelTmpBufOptBufCall: KPointer = valueDeserializer.readPointer()
            const cancelTmpBufOptBufCallSync: KPointer = valueDeserializer.readPointer()
            const cancelTmpBufOptClosure = ():void => {
                const cancelTmpBufOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                cancelTmpBufOptBufArgsSerializer.writeInt32(cancelTmpBufOptBufResource.resourceId);
                cancelTmpBufOptBufArgsSerializer.writePointer(cancelTmpBufOptBufCall);
                cancelTmpBufOptBufArgsSerializer.writePointer(cancelTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1225416436, cancelTmpBufOptBufArgsSerializer.asBuffer(), cancelTmpBufOptBufArgsSerializer.length());
                cancelTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(cancelTmpBufOptClosure, cancelTmpBufOptBufResource)
            cancelTmpBuf = cancelTmpBufOptClosure
        }
        const cancelTmpResult: (() => void) | undefined = cancelTmpBuf
        const autoCancelTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let autoCancelTmpBuf: boolean | undefined = undefined
        if ((autoCancelTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            autoCancelTmpBuf = valueDeserializer.readBoolean()
        }
        const autoCancelTmpResult: boolean | undefined = autoCancelTmpBuf
        const alignmentTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let alignmentTmpBuf: DialogAlignment | undefined = undefined
        if ((alignmentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            alignmentTmpBuf = DialogAlignment.fromValue(valueDeserializer.readInt32())
        }
        const alignmentTmpResult: DialogAlignment | undefined = alignmentTmpBuf
        const offsetTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let offsetTmpBuf: Offset | undefined = undefined
        if ((offsetTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            offsetTmpBuf = Offset_serializer.read(valueDeserializer)
        }
        const offsetTmpResult: Offset | undefined = offsetTmpBuf
        const customStyleTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let customStyleTmpBuf: boolean | undefined = undefined
        if ((customStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            customStyleTmpBuf = valueDeserializer.readBoolean()
        }
        const customStyleTmpResult: boolean | undefined = customStyleTmpBuf
        const gridCountTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let gridCountTmpBuf: int32 | undefined = undefined
        if ((gridCountTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            gridCountTmpBuf = valueDeserializer.readInt32()
        }
        const gridCountTmpResult: int32 | undefined = gridCountTmpBuf
        const maskColorTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let maskColorTmpBuf: ResourceColor | undefined = undefined
        if ((maskColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const maskColorTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let maskColorTmpBufOpt: arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (maskColorTmpBufOptUnionSelector == (0).toByte()) {
                maskColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (maskColorTmpBufOptUnionSelector == (1).toByte()) {
                maskColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (maskColorTmpBufOptUnionSelector == (2).toByte()) {
                maskColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (maskColorTmpBufOptUnionSelector == (3).toByte()) {
                maskColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for maskColorTmpBufOpt has to be chosen through deserialisation.')
            }
            maskColorTmpBuf = (maskColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const maskColorTmpResult: ResourceColor | undefined = maskColorTmpBuf
        const maskRectTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let maskRectTmpBuf: Rectangle | undefined = undefined
        if ((maskRectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maskRectTmpBuf = Rectangle_serializer.read(valueDeserializer)
        }
        const maskRectTmpResult: Rectangle | undefined = maskRectTmpBuf
        const openAnimationTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let openAnimationTmpBuf: AnimateParam | undefined = undefined
        if ((openAnimationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            openAnimationTmpBuf = AnimateParam_serializer.read(valueDeserializer)
        }
        const openAnimationTmpResult: AnimateParam | undefined = openAnimationTmpBuf
        const closeAnimationTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let closeAnimationTmpBuf: AnimateParam | undefined = undefined
        if ((closeAnimationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            closeAnimationTmpBuf = AnimateParam_serializer.read(valueDeserializer)
        }
        const closeAnimationTmpResult: AnimateParam | undefined = closeAnimationTmpBuf
        const showInSubWindowTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let showInSubWindowTmpBuf: boolean | undefined = undefined
        if ((showInSubWindowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            showInSubWindowTmpBuf = valueDeserializer.readBoolean()
        }
        const showInSubWindowTmpResult: boolean | undefined = showInSubWindowTmpBuf
        const backgroundColorTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let backgroundColorTmpBuf: ResourceColor | undefined = undefined
        if ((backgroundColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const backgroundColorTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let backgroundColorTmpBufOpt: arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (backgroundColorTmpBufOptUnionSelector == (0).toByte()) {
                backgroundColorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (backgroundColorTmpBufOptUnionSelector == (1).toByte()) {
                backgroundColorTmpBufOpt = valueDeserializer.readInt32()
            } else if (backgroundColorTmpBufOptUnionSelector == (2).toByte()) {
                backgroundColorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (backgroundColorTmpBufOptUnionSelector == (3).toByte()) {
                backgroundColorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for backgroundColorTmpBufOpt has to be chosen through deserialisation.')
            }
            backgroundColorTmpBuf = (backgroundColorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const backgroundColorTmpResult: ResourceColor | undefined = backgroundColorTmpBuf
        const cornerRadiusTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let cornerRadiusTmpBuf: Dimension | BorderRadiuses | undefined = undefined
        if ((cornerRadiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const cornerRadiusTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let cornerRadiusTmpBufOpt: Dimension | BorderRadiuses | undefined
            if (cornerRadiusTmpBufOptUnionSelector == (0).toByte()) {
                const cornerRadiusTmpBufOptBufUUnionSelector: int32 = valueDeserializer.readInt8()
                let cornerRadiusTmpBufOptBufU: string | number | global_resource_Resource | undefined
                if (cornerRadiusTmpBufOptBufUUnionSelector == (0).toByte()) {
                    cornerRadiusTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (cornerRadiusTmpBufOptBufUUnionSelector == (1).toByte()) {
                    cornerRadiusTmpBufOptBufU = (valueDeserializer.readNumber() as number)
                } else if (cornerRadiusTmpBufOptBufUUnionSelector == (2).toByte()) {
                    cornerRadiusTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for cornerRadiusTmpBufOptBufU has to be chosen through deserialisation.')
                }
                cornerRadiusTmpBufOpt = (cornerRadiusTmpBufOptBufU as string | number | global_resource_Resource)
            } else if (cornerRadiusTmpBufOptUnionSelector == (1).toByte()) {
                cornerRadiusTmpBufOpt = BorderRadiuses_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for cornerRadiusTmpBufOpt has to be chosen through deserialisation.')
            }
            cornerRadiusTmpBuf = (cornerRadiusTmpBufOpt as Dimension | BorderRadiuses)
        }
        const cornerRadiusTmpResult: Dimension | BorderRadiuses | undefined = cornerRadiusTmpBuf
        const isModalTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let isModalTmpBuf: boolean | undefined = undefined
        if ((isModalTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            isModalTmpBuf = valueDeserializer.readBoolean()
        }
        const isModalTmpResult: boolean | undefined = isModalTmpBuf
        const onWillDismissTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let onWillDismissTmpBuf: ((value0: DismissDialogAction) => void) | undefined = undefined
        if ((onWillDismissTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillDismissTmpBufOptBufResource: CallbackResource = valueDeserializer.readCallbackResource()
            const onWillDismissTmpBufOptBufCall: KPointer = valueDeserializer.readPointer()
            const onWillDismissTmpBufOptBufCallSync: KPointer = valueDeserializer.readPointer()
            const onWillDismissTmpBufOptClosure = (value0: DismissDialogAction):void => {
                const onWillDismissTmpBufOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                onWillDismissTmpBufOptBufArgsSerializer.writeInt32(onWillDismissTmpBufOptBufResource.resourceId);
                onWillDismissTmpBufOptBufArgsSerializer.writePointer(onWillDismissTmpBufOptBufCall);
                onWillDismissTmpBufOptBufArgsSerializer.writePointer(onWillDismissTmpBufOptBufCallSync);
                DismissDialogAction_serializer.write(onWillDismissTmpBufOptBufArgsSerializer, value0);
                InteropNativeModule._CallCallbackSync(10, 120169087, onWillDismissTmpBufOptBufArgsSerializer.asBuffer(), onWillDismissTmpBufOptBufArgsSerializer.length());
                onWillDismissTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onWillDismissTmpBufOptClosure, onWillDismissTmpBufOptBufResource)
            onWillDismissTmpBuf = onWillDismissTmpBufOptClosure
        }
        const onWillDismissTmpResult: ((value0: DismissDialogAction) => void) | undefined = onWillDismissTmpBuf
        const widthTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let widthTmpBuf: Dimension | undefined = undefined
        if ((widthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const widthTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let widthTmpBufOpt: string | number | global_resource_Resource | undefined
            if (widthTmpBufOptUnionSelector == (0).toByte()) {
                widthTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (widthTmpBufOptUnionSelector == (1).toByte()) {
                widthTmpBufOpt = (valueDeserializer.readNumber() as number)
            } else if (widthTmpBufOptUnionSelector == (2).toByte()) {
                widthTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for widthTmpBufOpt has to be chosen through deserialisation.')
            }
            widthTmpBuf = (widthTmpBufOpt as string | number | global_resource_Resource)
        }
        const widthTmpResult: Dimension | undefined = widthTmpBuf
        const heightTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let heightTmpBuf: Dimension | undefined = undefined
        if ((heightTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const heightTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let heightTmpBufOpt: string | number | global_resource_Resource | undefined
            if (heightTmpBufOptUnionSelector == (0).toByte()) {
                heightTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (heightTmpBufOptUnionSelector == (1).toByte()) {
                heightTmpBufOpt = (valueDeserializer.readNumber() as number)
            } else if (heightTmpBufOptUnionSelector == (2).toByte()) {
                heightTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for heightTmpBufOpt has to be chosen through deserialisation.')
            }
            heightTmpBuf = (heightTmpBufOpt as string | number | global_resource_Resource)
        }
        const heightTmpResult: Dimension | undefined = heightTmpBuf
        const borderWidthTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let borderWidthTmpBuf: Dimension | EdgeWidths | undefined = undefined
        if ((borderWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderWidthTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let borderWidthTmpBufOpt: Dimension | EdgeWidths | undefined
            if (borderWidthTmpBufOptUnionSelector == (0).toByte()) {
                const borderWidthTmpBufOptBufUUnionSelector: int32 = valueDeserializer.readInt8()
                let borderWidthTmpBufOptBufU: string | number | global_resource_Resource | undefined
                if (borderWidthTmpBufOptBufUUnionSelector == (0).toByte()) {
                    borderWidthTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (borderWidthTmpBufOptBufUUnionSelector == (1).toByte()) {
                    borderWidthTmpBufOptBufU = (valueDeserializer.readNumber() as number)
                } else if (borderWidthTmpBufOptBufUUnionSelector == (2).toByte()) {
                    borderWidthTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for borderWidthTmpBufOptBufU has to be chosen through deserialisation.')
                }
                borderWidthTmpBufOpt = (borderWidthTmpBufOptBufU as string | number | global_resource_Resource)
            } else if (borderWidthTmpBufOptUnionSelector == (1).toByte()) {
                borderWidthTmpBufOpt = EdgeWidths_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for borderWidthTmpBufOpt has to be chosen through deserialisation.')
            }
            borderWidthTmpBuf = (borderWidthTmpBufOpt as Dimension | EdgeWidths)
        }
        const borderWidthTmpResult: Dimension | EdgeWidths | undefined = borderWidthTmpBuf
        const borderColorTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let borderColorTmpBuf: ResourceColor | EdgeColors | undefined = undefined
        if ((borderColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderColorTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let borderColorTmpBufOpt: ResourceColor | EdgeColors | undefined
            if (borderColorTmpBufOptUnionSelector == (0).toByte()) {
                const borderColorTmpBufOptBufUUnionSelector: int32 = valueDeserializer.readInt8()
                let borderColorTmpBufOptBufU: arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
                if (borderColorTmpBufOptBufUUnionSelector == (0).toByte()) {
                    borderColorTmpBufOptBufU = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
                } else if (borderColorTmpBufOptBufUUnionSelector == (1).toByte()) {
                    borderColorTmpBufOptBufU = valueDeserializer.readInt32()
                } else if (borderColorTmpBufOptBufUUnionSelector == (2).toByte()) {
                    borderColorTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (borderColorTmpBufOptBufUUnionSelector == (3).toByte()) {
                    borderColorTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for borderColorTmpBufOptBufU has to be chosen through deserialisation.')
                }
                borderColorTmpBufOpt = (borderColorTmpBufOptBufU as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
            } else if (borderColorTmpBufOptUnionSelector == (1).toByte()) {
                borderColorTmpBufOpt = EdgeColors_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for borderColorTmpBufOpt has to be chosen through deserialisation.')
            }
            borderColorTmpBuf = (borderColorTmpBufOpt as ResourceColor | EdgeColors)
        }
        const borderColorTmpResult: ResourceColor | EdgeColors | undefined = borderColorTmpBuf
        const borderStyleTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let borderStyleTmpBuf: BorderStyle | EdgeStyles | undefined = undefined
        if ((borderStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const borderStyleTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let borderStyleTmpBufOpt: BorderStyle | EdgeStyles | undefined
            if (borderStyleTmpBufOptUnionSelector == (0).toByte()) {
                borderStyleTmpBufOpt = BorderStyle.fromValue(valueDeserializer.readInt32())
            } else if (borderStyleTmpBufOptUnionSelector == (1).toByte()) {
                borderStyleTmpBufOpt = EdgeStyles_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for borderStyleTmpBufOpt has to be chosen through deserialisation.')
            }
            borderStyleTmpBuf = (borderStyleTmpBufOpt as BorderStyle | EdgeStyles)
        }
        const borderStyleTmpResult: BorderStyle | EdgeStyles | undefined = borderStyleTmpBuf
        const shadowTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let shadowTmpBuf: ShadowOptions | ShadowStyle | undefined = undefined
        if ((shadowTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const shadowTmpBufOptUnionSelector: int32 = valueDeserializer.readInt8()
            let shadowTmpBufOpt: ShadowOptions | ShadowStyle | undefined
            if (shadowTmpBufOptUnionSelector == (0).toByte()) {
                shadowTmpBufOpt = ShadowOptions_serializer.read(valueDeserializer)
            } else if (shadowTmpBufOptUnionSelector == (1).toByte()) {
                shadowTmpBufOpt = ShadowStyle.fromValue(valueDeserializer.readInt32())
            } else {
                throw new Error('One of the branches for shadowTmpBufOpt has to be chosen through deserialisation.')
            }
            shadowTmpBuf = (shadowTmpBufOpt as ShadowOptions | ShadowStyle)
        }
        const shadowTmpResult: ShadowOptions | ShadowStyle | undefined = shadowTmpBuf
        const backgroundBlurStyleTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let backgroundBlurStyleTmpBuf: BlurStyle | undefined = undefined
        if ((backgroundBlurStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleTmpBuf = BlurStyle.fromValue(valueDeserializer.readInt32())
        }
        const backgroundBlurStyleTmpResult: BlurStyle | undefined = backgroundBlurStyleTmpBuf
        const backgroundBlurStyleOptionsTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let backgroundBlurStyleOptionsTmpBuf: BackgroundBlurStyleOptions | undefined = undefined
        if ((backgroundBlurStyleOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundBlurStyleOptionsTmpBuf = BackgroundBlurStyleOptions_serializer.read(valueDeserializer)
        }
        const backgroundBlurStyleOptionsTmpResult: BackgroundBlurStyleOptions | undefined = backgroundBlurStyleOptionsTmpBuf
        const backgroundEffectTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let backgroundEffectTmpBuf: BackgroundEffectOptions | undefined = undefined
        if ((backgroundEffectTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            backgroundEffectTmpBuf = BackgroundEffectOptions_serializer.read(valueDeserializer)
        }
        const backgroundEffectTmpResult: BackgroundEffectOptions | undefined = backgroundEffectTmpBuf
        const keyboardAvoidModeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let keyboardAvoidModeTmpBuf: arkui_component_common_KeyboardAvoidMode | undefined = undefined
        if ((keyboardAvoidModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            keyboardAvoidModeTmpBuf = arkui_component_common_KeyboardAvoidMode.fromValue(valueDeserializer.readInt32())
        }
        const keyboardAvoidModeTmpResult: arkui_component_common_KeyboardAvoidMode | undefined = keyboardAvoidModeTmpBuf
        const enableHoverModeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let enableHoverModeTmpBuf: boolean | undefined = undefined
        if ((enableHoverModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableHoverModeTmpBuf = valueDeserializer.readBoolean()
        }
        const enableHoverModeTmpResult: boolean | undefined = enableHoverModeTmpBuf
        const hoverModeAreaTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let hoverModeAreaTmpBuf: HoverModeAreaType | undefined = undefined
        if ((hoverModeAreaTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            hoverModeAreaTmpBuf = HoverModeAreaType.fromValue(valueDeserializer.readInt32())
        }
        const hoverModeAreaTmpResult: HoverModeAreaType | undefined = hoverModeAreaTmpBuf
        const onDidAppearTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let onDidAppearTmpBuf: (() => void) | undefined = undefined
        if ((onDidAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidAppearTmpBufOptBufResource: CallbackResource = valueDeserializer.readCallbackResource()
            const onDidAppearTmpBufOptBufCall: KPointer = valueDeserializer.readPointer()
            const onDidAppearTmpBufOptBufCallSync: KPointer = valueDeserializer.readPointer()
            const onDidAppearTmpBufOptClosure = ():void => {
                const onDidAppearTmpBufOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                onDidAppearTmpBufOptBufArgsSerializer.writeInt32(onDidAppearTmpBufOptBufResource.resourceId);
                onDidAppearTmpBufOptBufArgsSerializer.writePointer(onDidAppearTmpBufOptBufCall);
                onDidAppearTmpBufOptBufArgsSerializer.writePointer(onDidAppearTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1225416436, onDidAppearTmpBufOptBufArgsSerializer.asBuffer(), onDidAppearTmpBufOptBufArgsSerializer.length());
                onDidAppearTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onDidAppearTmpBufOptClosure, onDidAppearTmpBufOptBufResource)
            onDidAppearTmpBuf = onDidAppearTmpBufOptClosure
        }
        const onDidAppearTmpResult: (() => void) | undefined = onDidAppearTmpBuf
        const onDidDisappearTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let onDidDisappearTmpBuf: (() => void) | undefined = undefined
        if ((onDidDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onDidDisappearTmpBufOptBufResource: CallbackResource = valueDeserializer.readCallbackResource()
            const onDidDisappearTmpBufOptBufCall: KPointer = valueDeserializer.readPointer()
            const onDidDisappearTmpBufOptBufCallSync: KPointer = valueDeserializer.readPointer()
            const onDidDisappearTmpBufOptClosure = ():void => {
                const onDidDisappearTmpBufOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                onDidDisappearTmpBufOptBufArgsSerializer.writeInt32(onDidDisappearTmpBufOptBufResource.resourceId);
                onDidDisappearTmpBufOptBufArgsSerializer.writePointer(onDidDisappearTmpBufOptBufCall);
                onDidDisappearTmpBufOptBufArgsSerializer.writePointer(onDidDisappearTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1225416436, onDidDisappearTmpBufOptBufArgsSerializer.asBuffer(), onDidDisappearTmpBufOptBufArgsSerializer.length());
                onDidDisappearTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onDidDisappearTmpBufOptClosure, onDidDisappearTmpBufOptBufResource)
            onDidDisappearTmpBuf = onDidDisappearTmpBufOptClosure
        }
        const onDidDisappearTmpResult: (() => void) | undefined = onDidDisappearTmpBuf
        const onWillAppearTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let onWillAppearTmpBuf: (() => void) | undefined = undefined
        if ((onWillAppearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillAppearTmpBufOptBufResource: CallbackResource = valueDeserializer.readCallbackResource()
            const onWillAppearTmpBufOptBufCall: KPointer = valueDeserializer.readPointer()
            const onWillAppearTmpBufOptBufCallSync: KPointer = valueDeserializer.readPointer()
            const onWillAppearTmpBufOptClosure = ():void => {
                const onWillAppearTmpBufOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                onWillAppearTmpBufOptBufArgsSerializer.writeInt32(onWillAppearTmpBufOptBufResource.resourceId);
                onWillAppearTmpBufOptBufArgsSerializer.writePointer(onWillAppearTmpBufOptBufCall);
                onWillAppearTmpBufOptBufArgsSerializer.writePointer(onWillAppearTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1225416436, onWillAppearTmpBufOptBufArgsSerializer.asBuffer(), onWillAppearTmpBufOptBufArgsSerializer.length());
                onWillAppearTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onWillAppearTmpBufOptClosure, onWillAppearTmpBufOptBufResource)
            onWillAppearTmpBuf = onWillAppearTmpBufOptClosure
        }
        const onWillAppearTmpResult: (() => void) | undefined = onWillAppearTmpBuf
        const onWillDisappearTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let onWillDisappearTmpBuf: (() => void) | undefined = undefined
        if ((onWillDisappearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onWillDisappearTmpBufOptBufResource: CallbackResource = valueDeserializer.readCallbackResource()
            const onWillDisappearTmpBufOptBufCall: KPointer = valueDeserializer.readPointer()
            const onWillDisappearTmpBufOptBufCallSync: KPointer = valueDeserializer.readPointer()
            const onWillDisappearTmpBufOptClosure = ():void => {
                const onWillDisappearTmpBufOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                onWillDisappearTmpBufOptBufArgsSerializer.writeInt32(onWillDisappearTmpBufOptBufResource.resourceId);
                onWillDisappearTmpBufOptBufArgsSerializer.writePointer(onWillDisappearTmpBufOptBufCall);
                onWillDisappearTmpBufOptBufArgsSerializer.writePointer(onWillDisappearTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1225416436, onWillDisappearTmpBufOptBufArgsSerializer.asBuffer(), onWillDisappearTmpBufOptBufArgsSerializer.length());
                onWillDisappearTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(onWillDisappearTmpBufOptClosure, onWillDisappearTmpBufOptBufResource)
            onWillDisappearTmpBuf = onWillDisappearTmpBufOptClosure
        }
        const onWillDisappearTmpResult: (() => void) | undefined = onWillDisappearTmpBuf
        const keyboardAvoidDistanceTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let keyboardAvoidDistanceTmpBuf: arkui_Graphics_LengthMetrics | undefined = undefined
        if ((keyboardAvoidDistanceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            keyboardAvoidDistanceTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const keyboardAvoidDistanceTmpResult: arkui_Graphics_LengthMetrics | undefined = keyboardAvoidDistanceTmpBuf
        const levelModeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let levelModeTmpBuf: LevelMode | undefined = undefined
        if ((levelModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            levelModeTmpBuf = LevelMode.fromValue(valueDeserializer.readInt32())
        }
        const levelModeTmpResult: LevelMode | undefined = levelModeTmpBuf
        const levelUniqueIdTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let levelUniqueIdTmpBuf: int32 | undefined = undefined
        if ((levelUniqueIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            levelUniqueIdTmpBuf = valueDeserializer.readInt32()
        }
        const levelUniqueIdTmpResult: int32 | undefined = levelUniqueIdTmpBuf
        const immersiveModeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let immersiveModeTmpBuf: ImmersiveMode | undefined = undefined
        if ((immersiveModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            immersiveModeTmpBuf = ImmersiveMode.fromValue(valueDeserializer.readInt32())
        }
        const immersiveModeTmpResult: ImmersiveMode | undefined = immersiveModeTmpBuf
        const levelOrderExtenderTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let levelOrderExtenderTmpBuf: LevelOrderExtender | undefined = undefined
        if ((levelOrderExtenderTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            levelOrderExtenderTmpBuf = (LevelOrderExtender_serializer.read(valueDeserializer) as LevelOrderExtender)
        }
        const levelOrderExtenderTmpResult: LevelOrderExtender | undefined = levelOrderExtenderTmpBuf
        const focusableTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let focusableTmpBuf: boolean | undefined = undefined
        if ((focusableTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            focusableTmpBuf = valueDeserializer.readBoolean()
        }
        const focusableTmpResult: boolean | undefined = focusableTmpBuf
        let value: CustomDialogControllerOptionsExtender = ({builder: builderTmpResult, cancel: cancelTmpResult, autoCancel: autoCancelTmpResult, alignment: alignmentTmpResult, offset: offsetTmpResult, customStyle: customStyleTmpResult, gridCount: gridCountTmpResult, maskColor: maskColorTmpResult, maskRect: maskRectTmpResult, openAnimation: openAnimationTmpResult, closeAnimation: closeAnimationTmpResult, showInSubWindow: showInSubWindowTmpResult, backgroundColor: backgroundColorTmpResult, cornerRadius: cornerRadiusTmpResult, isModal: isModalTmpResult, onWillDismiss: onWillDismissTmpResult, width: widthTmpResult, height: heightTmpResult, borderWidth: borderWidthTmpResult, borderColor: borderColorTmpResult, borderStyle: borderStyleTmpResult, shadow: shadowTmpResult, backgroundBlurStyle: backgroundBlurStyleTmpResult, backgroundBlurStyleOptions: backgroundBlurStyleOptionsTmpResult, backgroundEffect: backgroundEffectTmpResult, keyboardAvoidMode: keyboardAvoidModeTmpResult, enableHoverMode: enableHoverModeTmpResult, hoverModeArea: hoverModeAreaTmpResult, onDidAppear: onDidAppearTmpResult, onDidDisappear: onDidDisappearTmpResult, onWillAppear: onWillAppearTmpResult, onWillDisappear: onWillDisappearTmpResult, keyboardAvoidDistance: keyboardAvoidDistanceTmpResult, levelMode: levelModeTmpResult, levelUniqueId: levelUniqueIdTmpResult, immersiveMode: immersiveModeTmpResult, levelOrderExtender: levelOrderExtenderTmpResult, focusable: focusableTmpResult} as CustomDialogControllerOptionsExtender)
        return value
    }
}
export class EmitterOptionsInner_serializer {
    public static write(buffer: SerializerBase, value: EmitterOptionsInner): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForParticle = value.particle
        EmitterParticleOptions_serializer.write(valueSerializer, valueHolderForParticle)
        const valueHolderForEmitRate = value.emitRate
        if (valueHolderForEmitRate !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEmitRateTmpValue = valueHolderForEmitRate!
            valueSerializer.writeInt32(valueHolderForEmitRateTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForShape = value.shape
        if (valueHolderForShape !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForShapeTmpValue = (valueHolderForShape as ParticleEmitterShape)
            valueSerializer.writeInt32(valueHolderForShapeTmpValue.getOrdinal())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForPosition = value.position
        if (valueHolderForPosition !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForPositionTmpValue = valueHolderForPosition!
            const valueHolderForPositionTmpValue_0 = valueHolderForPositionTmpValue[0]
            if (valueHolderForPositionTmpValue_0 instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForPositionTmpValue_0ForIdx0 = valueHolderForPositionTmpValue_0 as string
                valueSerializer.writeString(valueHolderForPositionTmpValue_0ForIdx0)
            } else if (valueHolderForPositionTmpValue_0 instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForPositionTmpValue_0ForIdx1 = valueHolderForPositionTmpValue_0 as number
                valueSerializer.writeNumber(valueHolderForPositionTmpValue_0ForIdx1)
            } else if (valueHolderForPositionTmpValue_0 instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForPositionTmpValue_0ForIdx2 = valueHolderForPositionTmpValue_0 as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForPositionTmpValue_0ForIdx2)
            }
            const valueHolderForPositionTmpValue_1 = valueHolderForPositionTmpValue[1]
            if (valueHolderForPositionTmpValue_1 instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForPositionTmpValue_1ForIdx0 = valueHolderForPositionTmpValue_1 as string
                valueSerializer.writeString(valueHolderForPositionTmpValue_1ForIdx0)
            } else if (valueHolderForPositionTmpValue_1 instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForPositionTmpValue_1ForIdx1 = valueHolderForPositionTmpValue_1 as number
                valueSerializer.writeNumber(valueHolderForPositionTmpValue_1ForIdx1)
            } else if (valueHolderForPositionTmpValue_1 instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForPositionTmpValue_1ForIdx2 = valueHolderForPositionTmpValue_1 as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForPositionTmpValue_1ForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSize = value.size
        if (valueHolderForSize !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSizeTmpValue = valueHolderForSize!
            const valueHolderForSizeTmpValue_0 = valueHolderForSizeTmpValue[0]
            if (valueHolderForSizeTmpValue_0 instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSizeTmpValue_0ForIdx0 = valueHolderForSizeTmpValue_0 as string
                valueSerializer.writeString(valueHolderForSizeTmpValue_0ForIdx0)
            } else if (valueHolderForSizeTmpValue_0 instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSizeTmpValue_0ForIdx1 = valueHolderForSizeTmpValue_0 as number
                valueSerializer.writeNumber(valueHolderForSizeTmpValue_0ForIdx1)
            } else if (valueHolderForSizeTmpValue_0 instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForSizeTmpValue_0ForIdx2 = valueHolderForSizeTmpValue_0 as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForSizeTmpValue_0ForIdx2)
            }
            const valueHolderForSizeTmpValue_1 = valueHolderForSizeTmpValue[1]
            if (valueHolderForSizeTmpValue_1 instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSizeTmpValue_1ForIdx0 = valueHolderForSizeTmpValue_1 as string
                valueSerializer.writeString(valueHolderForSizeTmpValue_1ForIdx0)
            } else if (valueHolderForSizeTmpValue_1 instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForSizeTmpValue_1ForIdx1 = valueHolderForSizeTmpValue_1 as number
                valueSerializer.writeNumber(valueHolderForSizeTmpValue_1ForIdx1)
            } else if (valueHolderForSizeTmpValue_1 instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForSizeTmpValue_1ForIdx2 = valueHolderForSizeTmpValue_1 as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForSizeTmpValue_1ForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAnnulusRegion = value.annulusRegion
        if (valueHolderForAnnulusRegion !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAnnulusRegionTmpValue = valueHolderForAnnulusRegion!
            ParticleAnnulusRegionInner_serializer.write(valueSerializer, valueHolderForAnnulusRegionTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): EmitterOptionsInner {
        let valueDeserializer: DeserializerBase = buffer
        const particleTmpResult: EmitterParticleOptions = EmitterParticleOptions_serializer.read(valueDeserializer)
        const emitRateTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let emitRateTmpBuf: int32 | undefined = undefined
        if ((emitRateTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            emitRateTmpBuf = valueDeserializer.readInt32()
        }
        const emitRateTmpResult: int32 | undefined = emitRateTmpBuf
        const shapeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let shapeTmpBuf: ParticleEmitterShape | undefined = undefined
        if ((shapeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            shapeTmpBuf = ParticleEmitterShape.values()[valueDeserializer.readInt32()]
        }
        const shapeTmpResult: ParticleEmitterShape | undefined = shapeTmpBuf
        const positionTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let positionTmpBuf: [ Dimension, Dimension ] | undefined = undefined
        if ((positionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const positionTmpBufOptValue0TempBufUnionSelector: int32 = valueDeserializer.readInt8()
            let positionTmpBufOptValue0TempBuf: string | number | global_resource_Resource | undefined
            if (positionTmpBufOptValue0TempBufUnionSelector == (0).toByte()) {
                positionTmpBufOptValue0TempBuf = (valueDeserializer.readString() as string)
            } else if (positionTmpBufOptValue0TempBufUnionSelector == (1).toByte()) {
                positionTmpBufOptValue0TempBuf = (valueDeserializer.readNumber() as number)
            } else if (positionTmpBufOptValue0TempBufUnionSelector == (2).toByte()) {
                positionTmpBufOptValue0TempBuf = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for positionTmpBufOptValue0TempBuf has to be chosen through deserialisation.')
            }
            const positionTmpBufOptValue0: Dimension = (positionTmpBufOptValue0TempBuf as string | number | global_resource_Resource)
            const positionTmpBufOptValue1TempBufUnionSelector: int32 = valueDeserializer.readInt8()
            let positionTmpBufOptValue1TempBuf: string | number | global_resource_Resource | undefined
            if (positionTmpBufOptValue1TempBufUnionSelector == (0).toByte()) {
                positionTmpBufOptValue1TempBuf = (valueDeserializer.readString() as string)
            } else if (positionTmpBufOptValue1TempBufUnionSelector == (1).toByte()) {
                positionTmpBufOptValue1TempBuf = (valueDeserializer.readNumber() as number)
            } else if (positionTmpBufOptValue1TempBufUnionSelector == (2).toByte()) {
                positionTmpBufOptValue1TempBuf = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for positionTmpBufOptValue1TempBuf has to be chosen through deserialisation.')
            }
            const positionTmpBufOptValue1: Dimension = (positionTmpBufOptValue1TempBuf as string | number | global_resource_Resource)
            positionTmpBuf = ([positionTmpBufOptValue0, positionTmpBufOptValue1] as [ Dimension, Dimension ])
        }
        const positionTmpResult: [ Dimension, Dimension ] | undefined = positionTmpBuf
        const sizeTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let sizeTmpBuf: [ Dimension, Dimension ] | undefined = undefined
        if ((sizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const sizeTmpBufOptValue0TempBufUnionSelector: int32 = valueDeserializer.readInt8()
            let sizeTmpBufOptValue0TempBuf: string | number | global_resource_Resource | undefined
            if (sizeTmpBufOptValue0TempBufUnionSelector == (0).toByte()) {
                sizeTmpBufOptValue0TempBuf = (valueDeserializer.readString() as string)
            } else if (sizeTmpBufOptValue0TempBufUnionSelector == (1).toByte()) {
                sizeTmpBufOptValue0TempBuf = (valueDeserializer.readNumber() as number)
            } else if (sizeTmpBufOptValue0TempBufUnionSelector == (2).toByte()) {
                sizeTmpBufOptValue0TempBuf = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for sizeTmpBufOptValue0TempBuf has to be chosen through deserialisation.')
            }
            const sizeTmpBufOptValue0: Dimension = (sizeTmpBufOptValue0TempBuf as string | number | global_resource_Resource)
            const sizeTmpBufOptValue1TempBufUnionSelector: int32 = valueDeserializer.readInt8()
            let sizeTmpBufOptValue1TempBuf: string | number | global_resource_Resource | undefined
            if (sizeTmpBufOptValue1TempBufUnionSelector == (0).toByte()) {
                sizeTmpBufOptValue1TempBuf = (valueDeserializer.readString() as string)
            } else if (sizeTmpBufOptValue1TempBufUnionSelector == (1).toByte()) {
                sizeTmpBufOptValue1TempBuf = (valueDeserializer.readNumber() as number)
            } else if (sizeTmpBufOptValue1TempBufUnionSelector == (2).toByte()) {
                sizeTmpBufOptValue1TempBuf = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for sizeTmpBufOptValue1TempBuf has to be chosen through deserialisation.')
            }
            const sizeTmpBufOptValue1: Dimension = (sizeTmpBufOptValue1TempBuf as string | number | global_resource_Resource)
            sizeTmpBuf = ([sizeTmpBufOptValue0, sizeTmpBufOptValue1] as [ Dimension, Dimension ])
        }
        const sizeTmpResult: [ Dimension, Dimension ] | undefined = sizeTmpBuf
        const annulusRegionTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let annulusRegionTmpBuf: ParticleAnnulusRegionInner | undefined = undefined
        if ((annulusRegionTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            annulusRegionTmpBuf = ParticleAnnulusRegionInner_serializer.read(valueDeserializer)
        }
        const annulusRegionTmpResult: ParticleAnnulusRegionInner | undefined = annulusRegionTmpBuf
        let value: EmitterOptionsInner = ({particle: particleTmpResult, emitRate: emitRateTmpResult, shape: shapeTmpResult, position: positionTmpResult, size: sizeTmpResult, annulusRegion: annulusRegionTmpResult} as EmitterOptionsInner)
        return value
    }
}
export class ParticleOptionsInner_serializer {
    public static write(buffer: SerializerBase, value: ParticleOptionsInner): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForEmitter = value.emitter
        EmitterOptionsInner_serializer.write(valueSerializer, valueHolderForEmitter)
        const valueHolderForColor = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue = valueHolderForColor!
            ParticleColorPropertyOptionsInner_serializer.write(valueSerializer, valueHolderForColorTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOpacity = value.opacity
        if (valueHolderForOpacity !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOpacityTmpValue = valueHolderForOpacity!
            ParticlePropertyOptionsInner_serializer.write(valueSerializer, valueHolderForOpacityTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForScale = value.scale
        if (valueHolderForScale !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForScaleTmpValue = valueHolderForScale!
            ParticlePropertyOptionsInner_serializer.write(valueSerializer, valueHolderForScaleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForVelocity = value.velocity
        if (valueHolderForVelocity !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForVelocityTmpValue = valueHolderForVelocity!
            VelocityOptions_serializer.write(valueSerializer, valueHolderForVelocityTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForAcceleration = value.acceleration
        if (valueHolderForAcceleration !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAccelerationTmpValue = valueHolderForAcceleration!
            AccelerationOptionsInner_serializer.write(valueSerializer, valueHolderForAccelerationTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSpin = value.spin
        if (valueHolderForSpin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSpinTmpValue = valueHolderForSpin!
            ParticlePropertyOptionsInner_serializer.write(valueSerializer, valueHolderForSpinTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ParticleOptionsInner {
        let valueDeserializer: DeserializerBase = buffer
        const emitterTmpResult: EmitterOptionsInner = EmitterOptionsInner_serializer.read(valueDeserializer)
        const colorTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let colorTmpBuf: ParticleColorPropertyOptionsInner | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            colorTmpBuf = ParticleColorPropertyOptionsInner_serializer.read(valueDeserializer)
        }
        const colorTmpResult: ParticleColorPropertyOptionsInner | undefined = colorTmpBuf
        const opacityTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let opacityTmpBuf: ParticlePropertyOptionsInner | undefined = undefined
        if ((opacityTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            opacityTmpBuf = ParticlePropertyOptionsInner_serializer.read(valueDeserializer)
        }
        const opacityTmpResult: ParticlePropertyOptionsInner | undefined = opacityTmpBuf
        const scaleTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let scaleTmpBuf: ParticlePropertyOptionsInner | undefined = undefined
        if ((scaleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            scaleTmpBuf = ParticlePropertyOptionsInner_serializer.read(valueDeserializer)
        }
        const scaleTmpResult: ParticlePropertyOptionsInner | undefined = scaleTmpBuf
        const velocityTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let velocityTmpBuf: VelocityOptions | undefined = undefined
        if ((velocityTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            velocityTmpBuf = VelocityOptions_serializer.read(valueDeserializer)
        }
        const velocityTmpResult: VelocityOptions | undefined = velocityTmpBuf
        const accelerationTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let accelerationTmpBuf: AccelerationOptionsInner | undefined = undefined
        if ((accelerationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            accelerationTmpBuf = AccelerationOptionsInner_serializer.read(valueDeserializer)
        }
        const accelerationTmpResult: AccelerationOptionsInner | undefined = accelerationTmpBuf
        const spinTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let spinTmpBuf: ParticlePropertyOptionsInner | undefined = undefined
        if ((spinTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            spinTmpBuf = ParticlePropertyOptionsInner_serializer.read(valueDeserializer)
        }
        const spinTmpResult: ParticlePropertyOptionsInner | undefined = spinTmpBuf
        let value: ParticleOptionsInner = ({emitter: emitterTmpResult, color: colorTmpResult, opacity: opacityTmpResult, scale: scaleTmpResult, velocity: velocityTmpResult, acceleration: accelerationTmpResult, spin: spinTmpResult} as ParticleOptionsInner)
        return value
    }
}
