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
import { AnimateParam_serializer, TranslateOptions_serializer, AnimateParam, TranslateOptions, TouchEvent, TouchEventInternal, ClickEvent, ClickEventInternal, GeometryInfo, Measurable, Layoutable, SizeResult } from "./common"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Resource_serializer, Resource } from "./../generated/resource"
import { SizeOptions_serializer, Length, SizeOptions, Position_serializer, Position, ResourceColor, ResourceStr, ConstraintSizeOptions } from "./units"
import { Color } from "./enums"
import { ContentModifier, UICommonBase, AttributeModifier, AttributeUpdater } from "./../handwritten"
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
import { image } from "./../generated/ohos.multimedia.image"
import { FontOptions_serializer, FontInfo_serializer, FontOptions, FontInfo } from "./../generated/ohos.font"
import { MeasureOptions_serializer, MeasureOptions } from "./../generated/ohos.measure"
import { NavigationOptions_serializer, NavPathStack, NavPathStackInternal, NavPathInfo, NavPathInfoInternal, NavigationOptions } from "./navigation"
import { Frame_serializer, Frame, Size, Size_serializer } from "./../generated/arkui.Graphics"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { curves, curves_ICurve_serializer } from "./../generated/ohos.curves"
import { CustomDialogController } from "./customDialogController"
import { CustomBuilder } from "./builder"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
import { GlobalScope } from "./../generated/GlobalScope"
export class AnimationExtender {
    private static SetClipRect_serialize(node: KPointer, x: float, y: float, width: float, height: float): void {
        ArkUIGeneratedNativeModule._AnimationExtender_SetClipRect(node, x, y, width, height)
    }
    private static OpenImplicitAnimation_serialize(param: AnimateParam): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        AnimateParam_serializer.write(thisSerializer, param)
        ArkUIGeneratedNativeModule._AnimationExtender_OpenImplicitAnimation(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static CloseImplicitAnimation_serialize(): void {
        ArkUIGeneratedNativeModule._AnimationExtender_CloseImplicitAnimation()
    }
    private static StartDoubleAnimation_serialize(node: KPointer, param: DoubleAnimationParam): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        DoubleAnimationParam_serializer.write(thisSerializer, param)
        ArkUIGeneratedNativeModule._AnimationExtender_StartDoubleAnimation(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static AnimationTranslate_serialize(node: KPointer, options: TranslateOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        TranslateOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._AnimationExtender_AnimationTranslate(node, thisSerializer.asBuffer(), thisSerializer.length())
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
    private width_serialize(width: Length): BaseShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (width instanceof string) {
            thisSerializer.writeInt8((0).toChar())
            const widthForIdx0  = width as string
            thisSerializer.writeString(widthForIdx0)
        } else if (width instanceof number) {
            thisSerializer.writeInt8((1).toChar())
            const widthForIdx1  = width as number
            thisSerializer.writeNumber(widthForIdx1)
        } else if (width instanceof Resource) {
            thisSerializer.writeInt8((2).toChar())
            const widthForIdx2  = width as Resource
            Resource_serializer.write(thisSerializer, widthForIdx2)
        }
        const retval  = ArkUIGeneratedNativeModule._BaseShape_width(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : BaseShape = BaseShapeInternal.fromPtr(retval)
        return obj
    }
    private height_serialize(height: Length): BaseShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (height instanceof string) {
            thisSerializer.writeInt8((0).toChar())
            const heightForIdx0  = height as string
            thisSerializer.writeString(heightForIdx0)
        } else if (height instanceof number) {
            thisSerializer.writeInt8((1).toChar())
            const heightForIdx1  = height as number
            thisSerializer.writeNumber(heightForIdx1)
        } else if (height instanceof Resource) {
            thisSerializer.writeInt8((2).toChar())
            const heightForIdx2  = height as Resource
            Resource_serializer.write(thisSerializer, heightForIdx2)
        }
        const retval  = ArkUIGeneratedNativeModule._BaseShape_height(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : BaseShape = BaseShapeInternal.fromPtr(retval)
        return obj
    }
    private size_serialize(size: SizeOptions): BaseShape {
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
    private create_serialize(buildFunc: (() => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(buildFunc)
        ArkUIGeneratedNativeModule._BuilderNodeOps_create(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private disposeNode_serialize(): void {
        ArkUIGeneratedNativeModule._BuilderNodeOps_disposeNode(this.peer!.ptr)
    }
    private setUpdateConfigurationCallback_serialize(configurationUpdateFunc: (() => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(configurationUpdateFunc)
        ArkUIGeneratedNativeModule._BuilderNodeOps_setUpdateConfigurationCallback(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOptions_serialize(options: BuilderNodeOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        BuilderNodeOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._BuilderNodeOps_setOptions(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private postTouchEvent_serialize(event: TouchEvent): boolean {
        const retval  = ArkUIGeneratedNativeModule._BuilderNodeOps_postTouchEvent(this.peer!.ptr, toPeerPtr(event))
        return retval
    }
    private setRootFrameNodeInBuilderNode_serialize(node: KPointer): KPointer {
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
    private offset_serialize(offset: Position): CommonShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Position_serializer.write(thisSerializer, offset)
        const retval  = ArkUIGeneratedNativeModule._CommonShape_offset(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : CommonShape = CommonShapeInternal.fromPtr(retval)
        return obj
    }
    private fill_serialize(color: ResourceColor): CommonShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (color instanceof Color) {
            thisSerializer.writeInt8((0).toChar())
            const colorForIdx0  = color as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(colorForIdx0))
        } else if (color instanceof number) {
            thisSerializer.writeInt8((1).toChar())
            const colorForIdx1  = color as number
            thisSerializer.writeNumber(colorForIdx1)
        } else if (color instanceof string) {
            thisSerializer.writeInt8((2).toChar())
            const colorForIdx2  = color as string
            thisSerializer.writeString(colorForIdx2)
        } else if (color instanceof Resource) {
            thisSerializer.writeInt8((3).toChar())
            const colorForIdx3  = color as Resource
            Resource_serializer.write(thisSerializer, colorForIdx3)
        }
        const retval  = ArkUIGeneratedNativeModule._CommonShape_fill(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : CommonShape = CommonShapeInternal.fromPtr(retval)
        return obj
    }
    private position_serialize(position: Position): CommonShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Position_serializer.write(thisSerializer, position)
        const retval  = ArkUIGeneratedNativeModule._CommonShape_position(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : CommonShape = CommonShapeInternal.fromPtr(retval)
        return obj
    }
}
export class ContentModifierHelper {
    private static contentModifierButton_serialize(node: KPointer, contentModifier: ContentModifier<ButtonConfiguration>, builder: ((parentNode: KPointer,config: ButtonConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierButton(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierButton_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierButton(node)
    }
    private static contentModifierCheckBox_serialize(node: KPointer, contentModifier: ContentModifier<CheckBoxConfiguration>, builder: ((parentNode: KPointer,config: CheckBoxConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierCheckBox(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierCheckBox_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierCheckBox(node)
    }
    private static contentModifierDataPanel_serialize(node: KPointer, contentModifier: ContentModifier<DataPanelConfiguration>, builder: ((parentNode: KPointer,config: DataPanelConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierDataPanel(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierDataPanel_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierDataPanel(node)
    }
    private static contentModifierGauge_serialize(node: KPointer, contentModifier: ContentModifier<GaugeConfiguration>, builder: ((parentNode: KPointer,config: GaugeConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierGauge(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierGauge_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierGauge(node)
    }
    private static contentModifierLoadingProgress_serialize(node: KPointer, contentModifier: ContentModifier<LoadingProgressConfiguration>, builder: ((parentNode: KPointer,config: LoadingProgressConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierLoadingProgress(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierLoadingProgress_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierLoadingProgress(node)
    }
    private static contentModifierProgress_serialize(node: KPointer, contentModifier: ContentModifier<ProgressConfiguration>, builder: ((parentNode: KPointer,config: ProgressConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierProgress(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierProgress_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierProgress(node)
    }
    private static contentModifierRadio_serialize(node: KPointer, contentModifier: ContentModifier<RadioConfiguration>, builder: ((parentNode: KPointer,config: RadioConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierRadio(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierRadio_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierRadio(node)
    }
    private static contentModifierRating_serialize(node: KPointer, contentModifier: ContentModifier<RatingConfiguration>, builder: ((parentNode: KPointer,config: RatingConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierRating(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierRating_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierRating(node)
    }
    private static contentModifierMenuItem_serialize(node: KPointer, contentModifier: ContentModifier<MenuItemConfiguration>, builder: ((parentNode: KPointer,config: MenuItemConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierMenuItem(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierMenuItem_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierMenuItem(node)
    }
    private static contentModifierSlider_serialize(node: KPointer, contentModifier: ContentModifier<SliderConfiguration>, builder: ((parentNode: KPointer,config: SliderConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierSlider(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierSlider_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierSlider(node)
    }
    private static contentModifierTextClock_serialize(node: KPointer, contentModifier: ContentModifier<TextClockConfiguration>, builder: ((parentNode: KPointer,config: TextClockConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierTextClock(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierTextClock_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierTextClock(node)
    }
    private static contentModifierTextTimer_serialize(node: KPointer, contentModifier: ContentModifier<TextTimerConfiguration>, builder: ((parentNode: KPointer,config: TextTimerConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierTextTimer(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierTextTimer_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._ContentModifierHelper_resetContentModifierTextTimer(node)
    }
    private static contentModifierToggle_serialize(node: KPointer, contentModifier: ContentModifier<ToggleConfiguration>, builder: ((parentNode: KPointer,config: ToggleConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierToggle(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static resetContentModifierToggle_serialize(node: KPointer): void {
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
export class EventEmulator {
    private static emitClickEvent_serialize(node: KPointer, event: ClickEvent): void {
        ArkUIGeneratedNativeModule._EventEmulator_emitClickEvent(node, toPeerPtr(event))
    }
    private static emitTextInputEvent_serialize(node: KPointer, text: string): void {
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
    private static requestFocus_serialize(key: string): void {
        ArkUIGeneratedNativeModule._FocusController_requestFocus(key)
    }
    public static requestFocus(key: string): void {
        const key_casted = key as (string)
        FocusController.requestFocus_serialize(key_casted)
        return
    }
}
export class GlobalScope_ohos_arkui_componentSnapshot {
    private static get_serialize(id: string, callback: ((result: image.PixelMap) => void), options?: SnapshotOptions): void {
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
    private static begin_serialize(scene: string, startInputType: PerfMonitorActionType, note?: string): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (note !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const noteTmpValue  = note!
            thisSerializer.writeString(noteTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GlobalScope_ohos_arkui_performanceMonitor_begin(scene, TypeChecker.PerfMonitorActionType_ToNumeric(startInputType), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static end_serialize(scene: string): void {
        ArkUIGeneratedNativeModule._GlobalScope_ohos_arkui_performanceMonitor_end(scene)
    }
    private static recordInputEventTime_serialize(actionType: PerfMonitorActionType, sourceType: PerfMonitorSourceType, time: int64): void {
        ArkUIGeneratedNativeModule._GlobalScope_ohos_arkui_performanceMonitor_recordInputEventTime(TypeChecker.PerfMonitorActionType_ToNumeric(actionType), TypeChecker.PerfMonitorSourceType_ToNumeric(sourceType), time)
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
    private static registerFont_serialize(options: FontOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        FontOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._GlobalScope_ohos_font_registerFont(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static getSystemFontList_serialize(): Array<string> {
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
    private static getFontByName_serialize(fontName: string): FontInfo {
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_ohos_font_getFontByName(fontName)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : FontInfo = FontInfo_serializer.read(retvalDeserializer)
        return returnResult
    }
    public static registerFont(options: FontOptions): void {
        const options_casted = options as (FontOptions)
        GlobalScope_ohos_font.registerFont_serialize(options_casted)
        return
    }
    public static getSystemFontList(): Array<string> {
        return GlobalScope_ohos_font.getSystemFontList_serialize()
    }
    public static getFontByName(fontName: string): FontInfo {
        const fontName_casted = fontName as (string)
        return GlobalScope_ohos_font.getFontByName_serialize(fontName_casted)
    }
}
export class GlobalScope_ohos_measure_utils {
    private static measureText_serialize(options: MeasureOptions): number {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        MeasureOptions_serializer.write(thisSerializer, options)
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_ohos_measure_utils_measureText(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private static measureTextSize_serialize(options: MeasureOptions): SizeOptions {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        MeasureOptions_serializer.write(thisSerializer, options)
        const retval  = ArkUIGeneratedNativeModule._GlobalScope_ohos_measure_utils_measureTextSize(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : SizeOptions = SizeOptions_serializer.read(retvalDeserializer)
        return returnResult
    }
    public static measureText(options: MeasureOptions): number {
        const options_casted = options as (MeasureOptions)
        return GlobalScope_ohos_measure_utils.measureText_serialize(options_casted)
    }
    public static measureTextSize(options: MeasureOptions): SizeOptions {
        const options_casted = options as (MeasureOptions)
        return GlobalScope_ohos_measure_utils.measureTextSize_serialize(options_casted)
    }
}
export class IUIContext {
    private static freezeUINode0_serialize(id: string, isFrozen: boolean): void {
        ArkUIGeneratedNativeModule._IUIContext_freezeUINode0(id, isFrozen ? 1 : 0)
    }
    private static freezeUINode1_serialize(id: number, isFrozen: boolean): void {
        ArkUIGeneratedNativeModule._IUIContext_freezeUINode1(id, isFrozen ? 1 : 0)
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
}
export class LazyForEachOps {
    private static Sync_serialize(node: KPointer, totalCount: int32, creator: Callback_CreateItem, updater: Callback_RangeUpdate): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(creator)
        thisSerializer.holdAndWriteCallback(updater)
        ArkUIGeneratedNativeModule._LazyForEachOps_Sync(node, totalCount, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static Sync(node: KPointer, totalCount: int32, creator: Callback_CreateItem, updater: Callback_RangeUpdate): void {
        const node_casted = node as (KPointer)
        const totalCount_casted = totalCount as (int32)
        const creator_casted = creator as (Callback_CreateItem)
        const updater_casted = updater as (Callback_RangeUpdate)
        LazyForEachOps.Sync_serialize(node_casted, totalCount_casted, creator_casted, updater_casted)
        return
    }
}
export class NavExtender {
    private static setNavigationOptions_serialize(ptr: KPointer, pathStack: NavPathStack): void {
        ArkUIGeneratedNativeModule._NavExtender_setNavigationOptions(ptr, toPeerPtr(pathStack))
    }
    private static setUpdateStackCallback_serialize(peer: NavPathStack, callback: NavExtender_OnUpdateStack): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._NavExtender_setUpdateStackCallback(toPeerPtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static syncStack_serialize(peer: NavPathStack): void {
        ArkUIGeneratedNativeModule._NavExtender_syncStack(toPeerPtr(peer))
    }
    private static checkNeedCreate_serialize(navigation: KPointer, index: int32): boolean {
        const retval  = ArkUIGeneratedNativeModule._NavExtender_checkNeedCreate(navigation, index)
        return retval
    }
    private static setNavDestinationNode_serialize(peer: NavPathStack, index: int32, node: KPointer): void {
        ArkUIGeneratedNativeModule._NavExtender_setNavDestinationNode(toPeerPtr(peer), index, node)
    }
    private static pushPath_serialize(pathStack: NavPathStack, info: NavPathInfo, options: NavigationOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        NavigationOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._NavExtender_pushPath(toPeerPtr(pathStack), toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static replacePath_serialize(pathStack: NavPathStack, info: NavPathInfo, options: NavigationOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        NavigationOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._NavExtender_replacePath(toPeerPtr(pathStack), toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static pop_serialize(pathStack: NavPathStack, animated: boolean): string {
        const retval  = ArkUIGeneratedNativeModule._NavExtender_pop(toPeerPtr(pathStack), animated ? 1 : 0)
        return retval
    }
    private static setOnPopCallback_serialize(pathStack: NavPathStack, popCallback: ((breakpoints: string) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(popCallback)
        ArkUIGeneratedNativeModule._NavExtender_setOnPopCallback(toPeerPtr(pathStack), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static getIdByIndex_serialize(pathStack: NavPathStack, index: int32): string {
        const retval  = ArkUIGeneratedNativeModule._NavExtender_getIdByIndex(toPeerPtr(pathStack), index)
        return retval
    }
    private static getIdByName_serialize(pathStack: NavPathStack, name: string): Array<string> {
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
    private static popToIndex_serialize(pathStack: NavPathStack, index: int32, animated: boolean): void {
        ArkUIGeneratedNativeModule._NavExtender_popToIndex(toPeerPtr(pathStack), index, animated ? 1 : 0)
    }
    private static popToName_serialize(pathStack: NavPathStack, name: string, animated: boolean): number {
        const retval  = ArkUIGeneratedNativeModule._NavExtender_popToName(toPeerPtr(pathStack), name, animated ? 1 : 0)
        return retval
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
    public static popToName(pathStack: NavPathStack, name: string, animated: boolean): number {
        const pathStack_casted = pathStack as (NavPathStack)
        const name_casted = name as (string)
        const animated_casted = animated as (boolean)
        return NavExtender.popToName_serialize(pathStack_casted, name_casted, animated_casted)
    }
}
export class RenderServiceNode {
    private static getNodeId_serialize(nodeId: string): int32 {
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
    public postMessage(message: Object, transfer: Array<NativeBuffer>): void {
        const message_casted = message as (Object)
        const transfer_casted = transfer as (Array<NativeBuffer>)
        this.postMessage0_serialize(message_casted, transfer_casted)
        return
    }
    public postMessage(message: Object, options?: PostMessageOptions): void {
        const message_casted = message as (Object)
        const options_casted = options as (PostMessageOptions | undefined)
        this.postMessage1_serialize(message_casted, options_casted)
        return
    }
    public postMessageWithSharedSendable(message: Object, transfer?: Array<NativeBuffer>): void {
        const message_casted = message as (Object)
        const transfer_casted = transfer as (Array<NativeBuffer> | undefined)
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
    private postMessage0_serialize(message: Object, transfer: Array<NativeBuffer>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(message)
        thisSerializer.writeInt32((transfer.length).toInt())
        for (let transferCounterI = 0; transferCounterI < transfer.length; transferCounterI++) {
            const transferTmpElement : NativeBuffer = transfer[transferCounterI]
            thisSerializer.writeBuffer(transferTmpElement)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_postMessage0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private postMessage1_serialize(message: Object, options?: PostMessageOptions): void {
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
    private postMessageWithSharedSendable_serialize(message: Object, transfer?: Array<NativeBuffer>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(message)
        if (transfer !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const transferTmpValue  = transfer!
            thisSerializer.writeInt32((transferTmpValue.length).toInt())
            for (let transferTmpValueCounterI = 0; transferTmpValueCounterI < transferTmpValue.length; transferTmpValueCounterI++) {
                const transferTmpValueTmpElement : NativeBuffer = transferTmpValue[transferTmpValueCounterI]
                thisSerializer.writeBuffer(transferTmpValueTmpElement)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_postMessageWithSharedSendable(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private on_serialize(Type: string, listener: WorkerEventListener): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        WorkerEventListener_serializer.write(thisSerializer, listener)
        ArkUIGeneratedNativeModule._RestrictedWorker_on(this.peer!.ptr, Type, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private once_serialize(Type: string, listener: WorkerEventListener): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        WorkerEventListener_serializer.write(thisSerializer, listener)
        ArkUIGeneratedNativeModule._RestrictedWorker_once(this.peer!.ptr, Type, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private off_serialize(Type: string, listener?: WorkerEventListener): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (listener !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const listenerTmpValue  = listener!
            WorkerEventListener_serializer.write(thisSerializer, listenerTmpValue)
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        WorkerEventListener_serializer.write(thisSerializer, listener)
        ArkUIGeneratedNativeModule._RestrictedWorker_addEventListener(this.peer!.ptr, Type, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private dispatchEvent_serialize(event: Event): boolean {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Event_serializer.write(thisSerializer, event)
        const retval  = ArkUIGeneratedNativeModule._RestrictedWorker_dispatchEvent(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private removeEventListener_serialize(Type: string, callback_?: WorkerEventListener): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (callback_ !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const callback_TmpValue  = callback_!
            WorkerEventListener_serializer.write(thisSerializer, callback_TmpValue)
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(globalCallObject)
        ArkUIGeneratedNativeModule._RestrictedWorker_registerGlobalCallObject(this.peer!.ptr, instanceName, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private unregisterGlobalCallObject_serialize(instanceName?: string): void {
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
        let buffer : RestrictedWorker_onexit_Callback | undefined
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
                InteropNativeModule._CallCallback(-2095497263, buffer_BufArgsSerializer.asBuffer(), buffer_BufArgsSerializer.length());
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
        let buffer : RestrictedWorker_onerror_Callback | undefined
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
                InteropNativeModule._CallCallback(-1213708823, buffer_BufArgsSerializer.asBuffer(), buffer_BufArgsSerializer.length());
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
        let buffer : RestrictedWorker_onmessage_Callback | undefined
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
                InteropNativeModule._CallCallback(1614214490, buffer_BufArgsSerializer.asBuffer(), buffer_BufArgsSerializer.length());
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
        let buffer : RestrictedWorker_onmessage_Callback | undefined
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
                InteropNativeModule._CallCallback(1614214490, buffer_BufArgsSerializer.asBuffer(), buffer_BufArgsSerializer.length());
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
export class SceneInternal {
    public static fromPtr(ptr: KPointer): Scene {
        return new Scene(ptr)
    }
}
export class Scene implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, Scene.getFinalizer())
    }
    constructor() {
        this(Scene.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._Scene_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._Scene_getFinalizer()
    }
    private static load_serialize(uri?: ResourceStr): Promise<Scene> {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (uri !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const uriTmpValue  = uri!
            if (uriTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toChar())
                const uriTmpValueForIdx0  = uriTmpValue as string
                thisSerializer.writeString(uriTmpValueForIdx0)
            } else if (uriTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toChar())
                const uriTmpValueForIdx1  = uriTmpValue as Resource
                Resource_serializer.write(thisSerializer, uriTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromise<Scene>()[0]
        ArkUIGeneratedNativeModule._Scene_load(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    public static load(uri?: ResourceStr): Promise<Scene> {
        const uri_casted = uri as (ResourceStr | undefined)
        return Scene.load_serialize(uri_casted)
    }
    public destroy(): void {
        this.destroy_serialize()
        return
    }
    private destroy_serialize(): void {
        ArkUIGeneratedNativeModule._Scene_destroy(this.peer!.ptr)
    }
}
export class ScreenshotService {
    private static requestScreenshot_serialize(target: string, name: string): boolean {
        const retval  = ArkUIGeneratedNativeModule._ScreenshotService_requestScreenshot(target, name)
        return retval
    }
    public static requestScreenshot(target: string, name: string): boolean {
        const target_casted = target as (string)
        const name_casted = name as (string)
        return ScreenshotService.requestScreenshot_serialize(target_casted, name_casted)
    }
}
export class StateStylesOps {
    private static onStateStyleChange_serialize(node: KPointer, stateStyleChange: Callback_StateStylesChange): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(stateStyleChange)
        ArkUIGeneratedNativeModule._StateStylesOps_onStateStyleChange(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static onStateStyleChange(node: KPointer, stateStyleChange: Callback_StateStylesChange): void {
        const node_casted = node as (KPointer)
        const stateStyleChange_casted = stateStyleChange as (Callback_StateStylesChange)
        StateStylesOps.onStateStyleChange_serialize(node_casted, stateStyleChange_casted)
        return
    }
}
export class SystemOps {
    private static StartFrame_serialize(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._SystemOps_StartFrame()
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
    private static resourceManagerReset_serialize(): void {
        ArkUIGeneratedNativeModule._SystemOps_resourceManagerReset()
    }
    private static setFrameCallback_serialize(onFrameCallback: ((value0: number) => void), onIdleCallback: ((value0: number) => void), delayTime: number): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(onFrameCallback)
        thisSerializer.holdAndWriteCallback(onIdleCallback)
        ArkUIGeneratedNativeModule._SystemOps_setFrameCallback(thisSerializer.asBuffer(), thisSerializer.length(), delayTime)
        thisSerializer.release()
    }
    private static colorMetricsResourceColor_serialize(color: Resource): Array<number> {
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
}
export class UIContextAtomicServiceBar {
    private static getBarRect_serialize(): Frame {
        const retval  = ArkUIGeneratedNativeModule._UIContextAtomicServiceBar_getBarRect()
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : Frame = Frame_serializer.read(retvalDeserializer)
        return returnResult
    }
    public static getBarRect(): Frame {
        return UIContextAtomicServiceBar.getBarRect_serialize()
    }
}
export class ArkRootPeer extends PeerNode {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
export class ArkCustomLayoutRootPeer extends PeerNode {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
export type Callback_RangeUpdate = (start: int32, end: int32) => void;
export type Callback_CreateItem = (index: int32) => KPointer;
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
export type WorkerEventListener = (event: Event) => Promise<void>;
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
export type NavExtender_OnUpdateStack = () => void;
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
    public subscribeOnMeasureSize(value: Callback_onMeasureSize_SizeResult): this {
        return this
    }
    public subscribeOnPlaceChildren(value: Callback_onPlaceChildren_Void): this {
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
        return (this.peer as ArkRootPeer)
    }
    public attributeModifier(value: AttributeModifier<Root> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export class ArkComponentRootComponent extends ComponentBase implements ComponentRoot {
    getPeer(): ArkComponentRootPeer {
        return (this.peer as ArkComponentRootPeer)
    }
    public attributeModifier(value: AttributeModifier<ComponentRoot> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export class ArkCustomLayoutRootComponent extends ComponentBase implements CustomLayoutRoot {
    getPeer(): ArkCustomLayoutRootPeer {
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
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export class RootModifier implements Root {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyModifierPatch(peer: ArkRootPeer): void {
    }
    mergeModifier(modifier: RootModifier): void {
    }
    public attributeModifier(value: AttributeModifier<Root> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ComponentRootModifier implements ComponentRoot {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyModifierPatch(peer: ArkComponentRootPeer): void {
    }
    mergeModifier(modifier: ComponentRootModifier): void {
    }
    public attributeModifier(value: AttributeModifier<ComponentRoot> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class CustomLayoutRootModifier implements CustomLayoutRoot {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _subscribeOnMeasureSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _subscribeOnMeasureSize_0_0value?: Callback_onMeasureSize_SizeResult
    _subscribeOnPlaceChildren_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _subscribeOnPlaceChildren_0_0value?: Callback_onPlaceChildren_Void
    applyModifierPatch(peer: ArkCustomLayoutRootPeer): void {
    }
    mergeModifier(modifier: CustomLayoutRootModifier): void {
    }
    subscribeOnMeasureSize(value: Callback_onMeasureSize_SizeResult): this {
        throw new Error("Not implemented")
    }
    subscribeOnPlaceChildren(value: Callback_onPlaceChildren_Void): this {
        throw new Error("Not implemented")
    }
    public attributeModifier(value: AttributeModifier<CustomLayoutRoot> | undefined): this {
        throw new Error("Not implemented")
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
export class Scene_serializer {
    public static write(buffer: SerializerBase, value: Scene): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): Scene {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return SceneInternal.fromPtr(ptr)
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
export class WorkerEventListener_serializer {
    public static write(buffer: SerializerBase, value: WorkerEventListener): void {
    }
    public static read(buffer: DeserializerBase): WorkerEventListener {
        throw new Error("Interface with functions is not supported")
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
        let selfIdealSizeTmpBuf : Size | undefined
        if ((selfIdealSizeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            selfIdealSizeTmpBuf = Size_serializer.read(valueDeserializer)
        }
        const selfIdealSizeTmpResult : Size | undefined = selfIdealSizeTmpBuf
        const typeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let typeTmpBuf : number | undefined
        if ((typeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            typeTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const typeTmpResult : number | undefined = typeTmpBuf
        const surfaceIdTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let surfaceIdTmpBuf : string | undefined
        if ((surfaceIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            surfaceIdTmpBuf = (valueDeserializer.readString() as string)
        }
        const surfaceIdTmpResult : string | undefined = surfaceIdTmpBuf
        let value : BuilderNodeOptions = ({selfIdealSize: selfIdealSizeTmpResult, type: typeTmpResult, surfaceId: surfaceIdTmpResult} as BuilderNodeOptions)
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
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForCurveForIdx0  = valueHolderForCurve as curves.Curve
            valueSerializer.writeInt32(TypeChecker.curves_Curve_ToNumeric(valueHolderForCurveForIdx0))
        } else if (valueHolderForCurve instanceof string) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForCurveForIdx1  = valueHolderForCurve as string
            valueSerializer.writeString(valueHolderForCurveForIdx1)
        } else if (valueHolderForCurve instanceof curves.ICurve) {
            valueSerializer.writeInt8((2).toChar())
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
            curveTmpBuf = TypeChecker.curves_Curve_FromNumeric(valueDeserializer.readInt32())
        } else if (curveTmpBufUnionSelector == (1).toChar()) {
            curveTmpBuf = (valueDeserializer.readString() as string)
        } else if (curveTmpBufUnionSelector == (2).toChar()) {
            curveTmpBuf = (curves_ICurve_serializer.read(valueDeserializer) as curves.ICurve)
        } else {
            throw new Error("One of the branches for curveTmpBuf has to be chosen through deserialisation.")
        }
        const curveTmpResult : curves.Curve | string | curves.ICurve = (curveTmpBuf as curves.Curve | string | curves.ICurve)
        const onProgressTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onProgressTmpBuf : Callback_Extender_OnProgress | undefined
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
                InteropNativeModule._CallCallback(1264236374, onProgressTmpBuf_BufArgsSerializer.asBuffer(), onProgressTmpBuf_BufArgsSerializer.length());
                onProgressTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onProgressTmpResult : Callback_Extender_OnProgress | undefined = onProgressTmpBuf
        const onFinishTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onFinishTmpBuf : Callback_Extender_OnFinish | undefined
        if ((onFinishTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onFinishTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onFinishTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onFinishTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onFinishTmpBuf = ():void => {
                const onFinishTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onFinishTmpBuf_BufArgsSerializer.writeInt32(onFinishTmpBuf_BufResource.resourceId);
                onFinishTmpBuf_BufArgsSerializer.writePointer(onFinishTmpBuf_BufCall);
                onFinishTmpBuf_BufArgsSerializer.writePointer(onFinishTmpBuf_BufCallSync);
                InteropNativeModule._CallCallback(-733525640, onFinishTmpBuf_BufArgsSerializer.asBuffer(), onFinishTmpBuf_BufArgsSerializer.length());
                onFinishTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const onFinishTmpResult : Callback_Extender_OnFinish | undefined = onFinishTmpBuf
        let value : DoubleAnimationParam = ({propertyName: propertyNameTmpResult, startValue: startValueTmpResult, endValue: endValueTmpResult, duration: durationTmpResult, delay: delayTmpResult, curve: curveTmpResult, onProgress: onProgressTmpResult, onFinish: onFinishTmpResult} as DoubleAnimationParam)
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
        let transferTmpBuf : Array<Object> | undefined
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
        let scaleTmpBuf : number | undefined
        if ((scaleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            scaleTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const scaleTmpResult : number | undefined = scaleTmpBuf
        const waitUntilRenderFinishedTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let waitUntilRenderFinishedTmpBuf : boolean | undefined
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
        let typeTmpBuf : string | undefined
        if ((typeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            typeTmpBuf = (valueDeserializer.readString() as string)
        }
        const typeTmpResult : string | undefined = typeTmpBuf
        const nameTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let nameTmpBuf : string | undefined
        if ((nameTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            nameTmpBuf = (valueDeserializer.readString() as string)
        }
        const nameTmpResult : string | undefined = nameTmpBuf
        const sharedTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let sharedTmpBuf : boolean | undefined
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
