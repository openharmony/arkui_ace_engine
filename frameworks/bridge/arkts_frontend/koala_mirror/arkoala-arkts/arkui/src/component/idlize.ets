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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { AnimateParam_serializer, TranslateOptions_serializer, AnimateParam, TranslateOptions, TouchEvent, TouchEventInternal, ClickEvent, ClickEventInternal, GeometryInfo, Measurable, Layoutable, SizeResult } from "./common"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Resource_serializer, Resource } from "./../generated/resource"
import { SizeOptions_serializer, Length, SizeOptions, Position_serializer, Position, ResourceColor, ResourceStr, ConstraintSizeOptions } from "./units"
import { Color, FontStyle, FontWeight, TextOverflow, TextCase } from "./enums"
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
import { NavigationOptions_serializer, NavPathStack, NavPathStackInternal, NavPathInfo, NavPathInfoInternal, NavigationOptions } from "./navigation"
import { Frame_serializer, Frame, Size, Size_serializer } from "./../generated/arkui.Graphics"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { curves, curves_ICurve_serializer } from "./../generated/ohos.curves"
import { CustomDialogController } from "./customDialogController"
import { CustomBuilder } from "./builder"
import { text } from "./../generated/ohos.graphics.text"
import { NodeAttach, remember } from "@koalaui/runtime"
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
        let width_type : int32 = RuntimeType.UNDEFINED
        width_type = runtimeType(width)
        if (RuntimeType.STRING == width_type) {
            thisSerializer.writeInt8((0).toChar())
            const width_0  = width as string
            thisSerializer.writeString(width_0)
        }
        else if (RuntimeType.NUMBER == width_type) {
            thisSerializer.writeInt8((1).toChar())
            const width_1  = width as number
            thisSerializer.writeNumber(width_1)
        }
        else if (RuntimeType.OBJECT == width_type) {
            thisSerializer.writeInt8((2).toChar())
            const width_2  = width as Resource
            Resource_serializer.write(thisSerializer, width_2)
        }
        const retval  = ArkUIGeneratedNativeModule._BaseShape_width(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        const obj : BaseShape = BaseShapeInternal.fromPtr(retval)
        return obj
    }
    private height_serialize(height: Length): BaseShape {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let height_type : int32 = RuntimeType.UNDEFINED
        height_type = runtimeType(height)
        if (RuntimeType.STRING == height_type) {
            thisSerializer.writeInt8((0).toChar())
            const height_0  = height as string
            thisSerializer.writeString(height_0)
        }
        else if (RuntimeType.NUMBER == height_type) {
            thisSerializer.writeInt8((1).toChar())
            const height_1  = height as number
            thisSerializer.writeNumber(height_1)
        }
        else if (RuntimeType.OBJECT == height_type) {
            thisSerializer.writeInt8((2).toChar())
            const height_2  = height as Resource
            Resource_serializer.write(thisSerializer, height_2)
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
        let color_type : int32 = RuntimeType.UNDEFINED
        color_type = runtimeType(color)
        if (TypeChecker.isColor(color)) {
            thisSerializer.writeInt8((0).toChar())
            const color_0  = color as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(color_0))
        }
        else if (RuntimeType.NUMBER == color_type) {
            thisSerializer.writeInt8((1).toChar())
            const color_1  = color as number
            thisSerializer.writeNumber(color_1)
        }
        else if (RuntimeType.STRING == color_type) {
            thisSerializer.writeInt8((2).toChar())
            const color_2  = color as string
            thisSerializer.writeString(color_2)
        }
        else if (RuntimeType.OBJECT == color_type) {
            thisSerializer.writeInt8((3).toChar())
            const color_3  = color as Resource
            Resource_serializer.write(thisSerializer, color_3)
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
    private static contentModifierCheckBox_serialize(node: KPointer, contentModifier: ContentModifier<CheckBoxConfiguration>, builder: ((parentNode: KPointer,config: CheckBoxConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierCheckBox(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static contentModifierDataPanel_serialize(node: KPointer, contentModifier: ContentModifier<DataPanelConfiguration>, builder: ((parentNode: KPointer,config: DataPanelConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierDataPanel(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static contentModifierGauge_serialize(node: KPointer, contentModifier: ContentModifier<GaugeConfiguration>, builder: ((parentNode: KPointer,config: GaugeConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierGauge(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static contentModifierLoadingProgress_serialize(node: KPointer, contentModifier: ContentModifier<LoadingProgressConfiguration>, builder: ((parentNode: KPointer,config: LoadingProgressConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierLoadingProgress(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static contentModifierProgress_serialize(node: KPointer, contentModifier: ContentModifier<ProgressConfiguration>, builder: ((parentNode: KPointer,config: ProgressConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierProgress(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static contentModifierRadio_serialize(node: KPointer, contentModifier: ContentModifier<RadioConfiguration>, builder: ((parentNode: KPointer,config: RadioConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierRadio(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static contentModifierRating_serialize(node: KPointer, contentModifier: ContentModifier<RatingConfiguration>, builder: ((parentNode: KPointer,config: RatingConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierRating(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static contentModifierMenuItem_serialize(node: KPointer, contentModifier: ContentModifier<MenuItemConfiguration>, builder: ((parentNode: KPointer,config: MenuItemConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierMenuItem(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static contentModifierSlider_serialize(node: KPointer, contentModifier: ContentModifier<SliderConfiguration>, builder: ((parentNode: KPointer,config: SliderConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierSlider(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static contentModifierTextClock_serialize(node: KPointer, contentModifier: ContentModifier<TextClockConfiguration>, builder: ((parentNode: KPointer,config: TextClockConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierTextClock(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static contentModifierTextTimer_serialize(node: KPointer, contentModifier: ContentModifier<TextTimerConfiguration>, builder: ((parentNode: KPointer,config: TextTimerConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierTextTimer(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static contentModifierToggle_serialize(node: KPointer, contentModifier: ContentModifier<ToggleConfiguration>, builder: ((parentNode: KPointer,config: ToggleConfiguration) => KPointer)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(contentModifier)
        thisSerializer.holdAndWriteCallback(builder)
        ArkUIGeneratedNativeModule._ContentModifierHelper_contentModifierToggle(node, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public static contentModifierButton(node: KPointer, contentModifier: ContentModifier<ButtonConfiguration>, builder: ((parentNode: KPointer,config: ButtonConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<ButtonConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: ButtonConfiguration) => KPointer))
        ContentModifierHelper.contentModifierButton_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }
    public static contentModifierCheckBox(node: KPointer, contentModifier: ContentModifier<CheckBoxConfiguration>, builder: ((parentNode: KPointer,config: CheckBoxConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<CheckBoxConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: CheckBoxConfiguration) => KPointer))
        ContentModifierHelper.contentModifierCheckBox_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }
    public static contentModifierDataPanel(node: KPointer, contentModifier: ContentModifier<DataPanelConfiguration>, builder: ((parentNode: KPointer,config: DataPanelConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<DataPanelConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: DataPanelConfiguration) => KPointer))
        ContentModifierHelper.contentModifierDataPanel_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }
    public static contentModifierGauge(node: KPointer, contentModifier: ContentModifier<GaugeConfiguration>, builder: ((parentNode: KPointer,config: GaugeConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<GaugeConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: GaugeConfiguration) => KPointer))
        ContentModifierHelper.contentModifierGauge_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }
    public static contentModifierLoadingProgress(node: KPointer, contentModifier: ContentModifier<LoadingProgressConfiguration>, builder: ((parentNode: KPointer,config: LoadingProgressConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<LoadingProgressConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: LoadingProgressConfiguration) => KPointer))
        ContentModifierHelper.contentModifierLoadingProgress_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }
    public static contentModifierProgress(node: KPointer, contentModifier: ContentModifier<ProgressConfiguration>, builder: ((parentNode: KPointer,config: ProgressConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<ProgressConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: ProgressConfiguration) => KPointer))
        ContentModifierHelper.contentModifierProgress_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }
    public static contentModifierRadio(node: KPointer, contentModifier: ContentModifier<RadioConfiguration>, builder: ((parentNode: KPointer,config: RadioConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<RadioConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: RadioConfiguration) => KPointer))
        ContentModifierHelper.contentModifierRadio_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }
    public static contentModifierRating(node: KPointer, contentModifier: ContentModifier<RatingConfiguration>, builder: ((parentNode: KPointer,config: RatingConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<RatingConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: RatingConfiguration) => KPointer))
        ContentModifierHelper.contentModifierRating_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }
    public static contentModifierMenuItem(node: KPointer, contentModifier: ContentModifier<MenuItemConfiguration>, builder: ((parentNode: KPointer,config: MenuItemConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<MenuItemConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: MenuItemConfiguration) => KPointer))
        ContentModifierHelper.contentModifierMenuItem_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }
    public static contentModifierSlider(node: KPointer, contentModifier: ContentModifier<SliderConfiguration>, builder: ((parentNode: KPointer,config: SliderConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<SliderConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: SliderConfiguration) => KPointer))
        ContentModifierHelper.contentModifierSlider_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }
    public static contentModifierTextClock(node: KPointer, contentModifier: ContentModifier<TextClockConfiguration>, builder: ((parentNode: KPointer,config: TextClockConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<TextClockConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: TextClockConfiguration) => KPointer))
        ContentModifierHelper.contentModifierTextClock_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }
    public static contentModifierTextTimer(node: KPointer, contentModifier: ContentModifier<TextTimerConfiguration>, builder: ((parentNode: KPointer,config: TextTimerConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<TextTimerConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: TextTimerConfiguration) => KPointer))
        ContentModifierHelper.contentModifierTextTimer_serialize(node_casted, contentModifier_casted, builder_casted)
        return
    }
    public static contentModifierToggle(node: KPointer, contentModifier: ContentModifier<ToggleConfiguration>, builder: ((parentNode: KPointer,config: ToggleConfiguration) => KPointer)): void {
        const node_casted = node as (KPointer)
        const contentModifier_casted = contentModifier as (ContentModifier<ToggleConfiguration>)
        const builder_casted = builder as (((parentNode: KPointer,config: ToggleConfiguration) => KPointer))
        ContentModifierHelper.contentModifierToggle_serialize(node_casted, contentModifier_casted, builder_casted)
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
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            SnapshotOptions_serializer.write(thisSerializer, options_value)
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
        let note_type : int32 = RuntimeType.UNDEFINED
        note_type = runtimeType(note)
        thisSerializer.writeInt8((note_type).toChar())
        if ((note_type) != (RuntimeType.UNDEFINED)) {
            const note_value  = note!
            thisSerializer.writeString(note_value)
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
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<string> = new Array<string>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readString() as string)
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
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<string> = new Array<string>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readString() as string)
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
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            WorkerOptions_serializer.write(thisSerializer, options_value)
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
        for (let transfer_counter_i = 0; transfer_counter_i < transfer.length; transfer_counter_i++) {
            const transfer_element : NativeBuffer = transfer[transfer_counter_i]
            thisSerializer.writeBuffer(transfer_element)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_postMessage0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private postMessage1_serialize(message: Object, options?: PostMessageOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(message)
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            PostMessageOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_postMessage1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private postMessageWithSharedSendable_serialize(message: Object, transfer?: Array<NativeBuffer>): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteObject(message)
        let transfer_type : int32 = RuntimeType.UNDEFINED
        transfer_type = runtimeType(transfer)
        thisSerializer.writeInt8((transfer_type).toChar())
        if ((transfer_type) != (RuntimeType.UNDEFINED)) {
            const transfer_value  = transfer!
            thisSerializer.writeInt32((transfer_value.length).toInt())
            for (let transfer_value_counter_i = 0; transfer_value_counter_i < transfer_value.length; transfer_value_counter_i++) {
                const transfer_value_element : NativeBuffer = transfer_value[transfer_value_counter_i]
                thisSerializer.writeBuffer(transfer_value_element)
            }
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
        let listener_type : int32 = RuntimeType.UNDEFINED
        listener_type = runtimeType(listener)
        thisSerializer.writeInt8((listener_type).toChar())
        if ((listener_type) != (RuntimeType.UNDEFINED)) {
            const listener_value  = listener!
            WorkerEventListener_serializer.write(thisSerializer, listener_value)
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
        let callback__type : int32 = RuntimeType.UNDEFINED
        callback__type = runtimeType(callback_)
        thisSerializer.writeInt8((callback__type).toChar())
        if ((callback__type) != (RuntimeType.UNDEFINED)) {
            const callback__value  = callback_!
            WorkerEventListener_serializer.write(thisSerializer, callback__value)
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
        let instanceName_type : int32 = RuntimeType.UNDEFINED
        instanceName_type = runtimeType(instanceName)
        thisSerializer.writeInt8((instanceName_type).toChar())
        if ((instanceName_type) != (RuntimeType.UNDEFINED)) {
            const instanceName_value  = instanceName!
            thisSerializer.writeString(instanceName_value)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_unregisterGlobalCallObject(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnexit_serialize(): RestrictedWorker_onexit_Callback | undefined {
        const retval  = ArkUIGeneratedNativeModule._RestrictedWorker_getOnexit(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : RestrictedWorker_onexit_Callback | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const buffer__resource : CallbackResource = retvalDeserializer.readCallbackResource()
            const buffer__call : KPointer = retvalDeserializer.readPointer()
            const buffer__callSync : KPointer = retvalDeserializer.readPointer()
            buffer = (code: number):void => { 
    const buffer__argsSerializer : SerializerBase = SerializerBase.hold();
    buffer__argsSerializer.writeInt32(buffer__resource.resourceId);
    buffer__argsSerializer.writePointer(buffer__call);
    buffer__argsSerializer.writePointer(buffer__callSync);
    buffer__argsSerializer.writeNumber(code);
    InteropNativeModule._CallCallback(-2095497263, buffer__argsSerializer.asBuffer(), buffer__argsSerializer.length());
    buffer__argsSerializer.release();
    return; }
        }
        const returnResult : RestrictedWorker_onexit_Callback | undefined = buffer
        return returnResult
    }
    private setOnexit_serialize(onexit: RestrictedWorker_onexit_Callback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let onexit_type : int32 = RuntimeType.UNDEFINED
        onexit_type = runtimeType(onexit)
        thisSerializer.writeInt8((onexit_type).toChar())
        if ((onexit_type) != (RuntimeType.UNDEFINED)) {
            const onexit_value  = onexit!
            thisSerializer.holdAndWriteCallback(onexit_value)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_setOnexit(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnerror_serialize(): RestrictedWorker_onerror_Callback | undefined {
        const retval  = ArkUIGeneratedNativeModule._RestrictedWorker_getOnerror(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : RestrictedWorker_onerror_Callback | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const buffer__resource : CallbackResource = retvalDeserializer.readCallbackResource()
            const buffer__call : KPointer = retvalDeserializer.readPointer()
            const buffer__callSync : KPointer = retvalDeserializer.readPointer()
            buffer = (ev: ErrorEvent):void => { 
    const buffer__argsSerializer : SerializerBase = SerializerBase.hold();
    buffer__argsSerializer.writeInt32(buffer__resource.resourceId);
    buffer__argsSerializer.writePointer(buffer__call);
    buffer__argsSerializer.writePointer(buffer__callSync);
    ErrorEvent_serializer.write(buffer__argsSerializer, ev);
    InteropNativeModule._CallCallback(-1213708823, buffer__argsSerializer.asBuffer(), buffer__argsSerializer.length());
    buffer__argsSerializer.release();
    return; }
        }
        const returnResult : RestrictedWorker_onerror_Callback | undefined = buffer
        return returnResult
    }
    private setOnerror_serialize(onerror: RestrictedWorker_onerror_Callback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let onerror_type : int32 = RuntimeType.UNDEFINED
        onerror_type = runtimeType(onerror)
        thisSerializer.writeInt8((onerror_type).toChar())
        if ((onerror_type) != (RuntimeType.UNDEFINED)) {
            const onerror_value  = onerror!
            thisSerializer.holdAndWriteCallback(onerror_value)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_setOnerror(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnmessage_serialize(): RestrictedWorker_onmessage_Callback | undefined {
        const retval  = ArkUIGeneratedNativeModule._RestrictedWorker_getOnmessage(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : RestrictedWorker_onmessage_Callback | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const buffer__resource : CallbackResource = retvalDeserializer.readCallbackResource()
            const buffer__call : KPointer = retvalDeserializer.readPointer()
            const buffer__callSync : KPointer = retvalDeserializer.readPointer()
            buffer = (event: MessageEvents):void => { 
    const buffer__argsSerializer : SerializerBase = SerializerBase.hold();
    buffer__argsSerializer.writeInt32(buffer__resource.resourceId);
    buffer__argsSerializer.writePointer(buffer__call);
    buffer__argsSerializer.writePointer(buffer__callSync);
    MessageEvents_serializer.write(buffer__argsSerializer, event);
    InteropNativeModule._CallCallback(1614214490, buffer__argsSerializer.asBuffer(), buffer__argsSerializer.length());
    buffer__argsSerializer.release();
    return; }
        }
        const returnResult : RestrictedWorker_onmessage_Callback | undefined = buffer
        return returnResult
    }
    private setOnmessage_serialize(onmessage: RestrictedWorker_onmessage_Callback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let onmessage_type : int32 = RuntimeType.UNDEFINED
        onmessage_type = runtimeType(onmessage)
        thisSerializer.writeInt8((onmessage_type).toChar())
        if ((onmessage_type) != (RuntimeType.UNDEFINED)) {
            const onmessage_value  = onmessage!
            thisSerializer.holdAndWriteCallback(onmessage_value)
        }
        ArkUIGeneratedNativeModule._RestrictedWorker_setOnmessage(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnmessageerror_serialize(): RestrictedWorker_onmessage_Callback | undefined {
        const retval  = ArkUIGeneratedNativeModule._RestrictedWorker_getOnmessageerror(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8().toInt()
        let buffer : RestrictedWorker_onmessage_Callback | undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const buffer__resource : CallbackResource = retvalDeserializer.readCallbackResource()
            const buffer__call : KPointer = retvalDeserializer.readPointer()
            const buffer__callSync : KPointer = retvalDeserializer.readPointer()
            buffer = (event: MessageEvents):void => { 
    const buffer__argsSerializer : SerializerBase = SerializerBase.hold();
    buffer__argsSerializer.writeInt32(buffer__resource.resourceId);
    buffer__argsSerializer.writePointer(buffer__call);
    buffer__argsSerializer.writePointer(buffer__callSync);
    MessageEvents_serializer.write(buffer__argsSerializer, event);
    InteropNativeModule._CallCallback(1614214490, buffer__argsSerializer.asBuffer(), buffer__argsSerializer.length());
    buffer__argsSerializer.release();
    return; }
        }
        const returnResult : RestrictedWorker_onmessage_Callback | undefined = buffer
        return returnResult
    }
    private setOnmessageerror_serialize(onmessageerror: RestrictedWorker_onmessage_Callback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let onmessageerror_type : int32 = RuntimeType.UNDEFINED
        onmessageerror_type = runtimeType(onmessageerror)
        thisSerializer.writeInt8((onmessageerror_type).toChar())
        if ((onmessageerror_type) != (RuntimeType.UNDEFINED)) {
            const onmessageerror_value  = onmessageerror!
            thisSerializer.holdAndWriteCallback(onmessageerror_value)
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
        let uri_type : int32 = RuntimeType.UNDEFINED
        uri_type = runtimeType(uri)
        thisSerializer.writeInt8((uri_type).toChar())
        if ((uri_type) != (RuntimeType.UNDEFINED)) {
            const uri_value  = uri!
            let uri_value_type : int32 = RuntimeType.UNDEFINED
            uri_value_type = runtimeType(uri_value)
            if (RuntimeType.STRING == uri_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const uri_value_0  = uri_value as string
                thisSerializer.writeString(uri_value_0)
            }
            else if (RuntimeType.OBJECT == uri_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const uri_value_1  = uri_value as Resource
                Resource_serializer.write(thisSerializer, uri_value_1)
            }
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
        for (let params_counter_i = 0; params_counter_i < params.length; params_counter_i++) {
            const params_element : string = params[params_counter_i]
            thisSerializer.writeString(params_element)
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
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<number> = new Array<number>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readNumber() as number)
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
        const _peer  = new ArkRootPeer(_peerPtr, peerId, "Root", flags)
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
        const _peer  = new ArkComponentRootPeer(_peerPtr, peerId, "ComponentRoot", flags)
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
        const _peer  = new ArkCustomLayoutRootPeer(_peerPtr, peerId, "CustomLayoutRoot", flags)
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
export interface FontOptions {
    familyName: string | Resource;
    familySrc: string | Resource;
}
export interface MeasureOptions {
    textContent: string | Resource;
    constraintWidth?: number | string | Resource;
    fontSize?: number | string | Resource;
    fontStyle?: number | FontStyle;
    fontWeight?: number | string | FontWeight;
    fontFamily?: string | Resource;
    letterSpacing?: number | string;
    textAlign?: text.TextAlign;
    overflow?: number | TextOverflow;
    maxLines?: number;
    lineHeight?: number | string | Resource;
    baselineOffset?: number | string;
    textCase?: number | TextCase;
    textIndent?: number | string;
    wordBreak?: text.WordBreak;
}
export interface FontInfo {
    path: string;
    postScriptName: string;
    fullName: string;
    family: string;
    subfamily: string;
    weight: number;
    width: number;
    italic: boolean;
    monoSpace: boolean;
    symbolic: boolean;
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
    public apply(target: Root): void {
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
    public apply(target: ComponentRoot): void {
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
    public apply(target: CustomLayoutRoot): void {
        if (this.subscribeOnMeasureSize_value !== undefined)
            target.subscribeOnMeasureSize(this.subscribeOnMeasureSize_value!)
        if (this.subscribeOnPlaceChildren_value !== undefined)
            target.subscribeOnPlaceChildren(this.subscribeOnPlaceChildren_value!)
    }
}
export interface TransformationMatrix {
    matrix4x4: Array<number>;
}
export class ArkRootComponent extends ComponentBase implements Root {
    getPeer(): ArkRootPeer {
        return (this.peer as ArkRootPeer)
    }
    _modifier?: AttributeModifier<Root> | undefined
    public attributeModifier(value: AttributeModifier<Root> | undefined): this {
        this._modifier = value
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withRootStyle(receiver: Root, modifier: AttributeModifier<Root> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkRootStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<Root>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<Root>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
export class ArkComponentRootComponent extends ComponentBase implements ComponentRoot {
    getPeer(): ArkComponentRootPeer {
        return (this.peer as ArkComponentRootPeer)
    }
    _modifier?: AttributeModifier<ComponentRoot> | undefined
    public attributeModifier(value: AttributeModifier<ComponentRoot> | undefined): this {
        this._modifier = value
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withComponentRootStyle(receiver: ComponentRoot, modifier: AttributeModifier<ComponentRoot> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkComponentRootStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<ComponentRoot>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<ComponentRoot>).applyNormalAttribute(style)
        style.apply(receiver)
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
    _modifier?: AttributeModifier<CustomLayoutRoot> | undefined
    public attributeModifier(value: AttributeModifier<CustomLayoutRoot> | undefined): this {
        this._modifier = value
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withCustomLayoutRootStyle(receiver: CustomLayoutRoot, modifier: AttributeModifier<CustomLayoutRoot> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkCustomLayoutRootStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CustomLayoutRoot>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CustomLayoutRoot>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
export class ArkRootSet implements Root {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyModifierPatch(component: Root): void {
    }
    public attributeModifier(value: AttributeModifier<Root> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ArkComponentRootSet implements ComponentRoot {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyModifierPatch(component: ComponentRoot): void {
    }
    public attributeModifier(value: AttributeModifier<ComponentRoot> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ArkCustomLayoutRootSet implements CustomLayoutRoot {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _subscribeOnMeasureSize_flag?: boolean
    _subscribeOnMeasureSize0_value?: Callback_onMeasureSize_SizeResult
    _subscribeOnPlaceChildren_flag?: boolean
    _subscribeOnPlaceChildren0_value?: Callback_onPlaceChildren_Void
    applyModifierPatch(component: CustomLayoutRoot): void {
        if (this._subscribeOnMeasureSize_flag)
            component.subscribeOnMeasureSize((this._subscribeOnMeasureSize0_value as Callback_onMeasureSize_SizeResult))
        if (this._subscribeOnPlaceChildren_flag)
            component.subscribeOnPlaceChildren((this._subscribeOnPlaceChildren0_value as Callback_onPlaceChildren_Void))
    }
    public subscribeOnMeasureSize(value: Callback_onMeasureSize_SizeResult): this {
        this._subscribeOnMeasureSize_flag = true
        this._subscribeOnMeasureSize0_value = value
        return this
    }
    public subscribeOnPlaceChildren(value: Callback_onPlaceChildren_Void): this {
        this._subscribeOnPlaceChildren_flag = true
        this._subscribeOnPlaceChildren0_value = value
        return this
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
        const value_x  = value.x
        valueSerializer.writeNumber(value_x)
        const value_y  = value.y
        valueSerializer.writeNumber(value_y)
    }
    public static read(buffer: DeserializerBase): Offset_componentutils {
        let valueDeserializer : DeserializerBase = buffer
        const x_result : number = (valueDeserializer.readNumber() as number)
        const y_result : number = (valueDeserializer.readNumber() as number)
        let value : Offset_componentutils = ({x: x_result, y: y_result} as Offset_componentutils)
        return value
    }
}
export class RotateResult_serializer {
    public static write(buffer: SerializerBase, value: RotateResult): void {
        let valueSerializer : SerializerBase = buffer
        const value_x  = value.x
        valueSerializer.writeNumber(value_x)
        const value_y  = value.y
        valueSerializer.writeNumber(value_y)
        const value_z  = value.z
        valueSerializer.writeNumber(value_z)
        const value_centerX  = value.centerX
        valueSerializer.writeNumber(value_centerX)
        const value_centerY  = value.centerY
        valueSerializer.writeNumber(value_centerY)
        const value_angle  = value.angle
        valueSerializer.writeNumber(value_angle)
    }
    public static read(buffer: DeserializerBase): RotateResult {
        let valueDeserializer : DeserializerBase = buffer
        const x_result : number = (valueDeserializer.readNumber() as number)
        const y_result : number = (valueDeserializer.readNumber() as number)
        const z_result : number = (valueDeserializer.readNumber() as number)
        const centerX_result : number = (valueDeserializer.readNumber() as number)
        const centerY_result : number = (valueDeserializer.readNumber() as number)
        const angle_result : number = (valueDeserializer.readNumber() as number)
        let value : RotateResult = ({x: x_result, y: y_result, z: z_result, centerX: centerX_result, centerY: centerY_result, angle: angle_result} as RotateResult)
        return value
    }
}
export class ScaleResult_serializer {
    public static write(buffer: SerializerBase, value: ScaleResult): void {
        let valueSerializer : SerializerBase = buffer
        const value_x  = value.x
        valueSerializer.writeNumber(value_x)
        const value_y  = value.y
        valueSerializer.writeNumber(value_y)
        const value_z  = value.z
        valueSerializer.writeNumber(value_z)
        const value_centerX  = value.centerX
        valueSerializer.writeNumber(value_centerX)
        const value_centerY  = value.centerY
        valueSerializer.writeNumber(value_centerY)
    }
    public static read(buffer: DeserializerBase): ScaleResult {
        let valueDeserializer : DeserializerBase = buffer
        const x_result : number = (valueDeserializer.readNumber() as number)
        const y_result : number = (valueDeserializer.readNumber() as number)
        const z_result : number = (valueDeserializer.readNumber() as number)
        const centerX_result : number = (valueDeserializer.readNumber() as number)
        const centerY_result : number = (valueDeserializer.readNumber() as number)
        let value : ScaleResult = ({x: x_result, y: y_result, z: z_result, centerX: centerX_result, centerY: centerY_result} as ScaleResult)
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
        const value_x  = value.x
        valueSerializer.writeNumber(value_x)
        const value_y  = value.y
        valueSerializer.writeNumber(value_y)
        const value_z  = value.z
        valueSerializer.writeNumber(value_z)
    }
    public static read(buffer: DeserializerBase): TranslateResult {
        let valueDeserializer : DeserializerBase = buffer
        const x_result : number = (valueDeserializer.readNumber() as number)
        const y_result : number = (valueDeserializer.readNumber() as number)
        const z_result : number = (valueDeserializer.readNumber() as number)
        let value : TranslateResult = ({x: x_result, y: y_result, z: z_result} as TranslateResult)
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
        const value_selfIdealSize  = value.selfIdealSize
        let value_selfIdealSize_type : int32 = RuntimeType.UNDEFINED
        value_selfIdealSize_type = runtimeType(value_selfIdealSize)
        valueSerializer.writeInt8((value_selfIdealSize_type).toChar())
        if ((value_selfIdealSize_type) != (RuntimeType.UNDEFINED)) {
            const value_selfIdealSize_value  = value_selfIdealSize!
            Size_serializer.write(valueSerializer, value_selfIdealSize_value)
        }
        const value_type  = value.type
        let value_type_type : int32 = RuntimeType.UNDEFINED
        value_type_type = runtimeType(value_type)
        valueSerializer.writeInt8((value_type_type).toChar())
        if ((value_type_type) != (RuntimeType.UNDEFINED)) {
            const value_type_value  = value_type!
            valueSerializer.writeNumber(value_type_value)
        }
        const value_surfaceId  = value.surfaceId
        let value_surfaceId_type : int32 = RuntimeType.UNDEFINED
        value_surfaceId_type = runtimeType(value_surfaceId)
        valueSerializer.writeInt8((value_surfaceId_type).toChar())
        if ((value_surfaceId_type) != (RuntimeType.UNDEFINED)) {
            const value_surfaceId_value  = value_surfaceId!
            valueSerializer.writeString(value_surfaceId_value)
        }
    }
    public static read(buffer: DeserializerBase): BuilderNodeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const selfIdealSize_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let selfIdealSize_buf : Size | undefined
        if ((selfIdealSize_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            selfIdealSize_buf = Size_serializer.read(valueDeserializer)
        }
        const selfIdealSize_result : Size | undefined = selfIdealSize_buf
        const type_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let type_buf : number | undefined
        if ((type_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            type_buf = (valueDeserializer.readNumber() as number)
        }
        const type_result : number | undefined = type_buf
        const surfaceId_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let surfaceId_buf : string | undefined
        if ((surfaceId_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            surfaceId_buf = (valueDeserializer.readString() as string)
        }
        const surfaceId_result : string | undefined = surfaceId_buf
        let value : BuilderNodeOptions = ({selfIdealSize: selfIdealSize_result, type: type_result, surfaceId: surfaceId_result} as BuilderNodeOptions)
        return value
    }
}
export class DoubleAnimationParam_serializer {
    public static write(buffer: SerializerBase, value: DoubleAnimationParam): void {
        let valueSerializer : SerializerBase = buffer
        const value_propertyName  = value.propertyName
        valueSerializer.writeString(value_propertyName)
        const value_startValue  = value.startValue
        valueSerializer.writeFloat32(value_startValue)
        const value_endValue  = value.endValue
        valueSerializer.writeFloat32(value_endValue)
        const value_duration  = value.duration
        valueSerializer.writeInt32(value_duration)
        const value_delay  = value.delay
        valueSerializer.writeInt32(value_delay)
        const value_curve  = value.curve
        let value_curve_type : int32 = RuntimeType.UNDEFINED
        value_curve_type = runtimeType(value_curve)
        if (TypeChecker.iscurves_Curve(value_curve)) {
            valueSerializer.writeInt8((0).toChar())
            const value_curve_0  = value_curve as curves.Curve
            valueSerializer.writeInt32(TypeChecker.curves_Curve_ToNumeric(value_curve_0))
        }
        else if (RuntimeType.STRING == value_curve_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_curve_1  = value_curve as string
            valueSerializer.writeString(value_curve_1)
        }
        else if (RuntimeType.OBJECT == value_curve_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_curve_2  = value_curve as curves.ICurve
            curves_ICurve_serializer.write(valueSerializer, value_curve_2)
        }
        const value_onProgress  = value.onProgress
        let value_onProgress_type : int32 = RuntimeType.UNDEFINED
        value_onProgress_type = runtimeType(value_onProgress)
        valueSerializer.writeInt8((value_onProgress_type).toChar())
        if ((value_onProgress_type) != (RuntimeType.UNDEFINED)) {
            const value_onProgress_value  = value_onProgress!
            valueSerializer.holdAndWriteCallback(value_onProgress_value)
        }
        const value_onFinish  = value.onFinish
        let value_onFinish_type : int32 = RuntimeType.UNDEFINED
        value_onFinish_type = runtimeType(value_onFinish)
        valueSerializer.writeInt8((value_onFinish_type).toChar())
        if ((value_onFinish_type) != (RuntimeType.UNDEFINED)) {
            const value_onFinish_value  = value_onFinish!
            valueSerializer.holdAndWriteCallback(value_onFinish_value)
        }
    }
    public static read(buffer: DeserializerBase): DoubleAnimationParam {
        let valueDeserializer : DeserializerBase = buffer
        const propertyName_result : string = (valueDeserializer.readString() as string)
        const startValue_result : float = valueDeserializer.readFloat32()
        const endValue_result : float = valueDeserializer.readFloat32()
        const duration_result : int32 = valueDeserializer.readInt32()
        const delay_result : int32 = valueDeserializer.readInt32()
        const curve_buf_selector : int32 = valueDeserializer.readInt8()
        let curve_buf : curves.Curve | string | curves.ICurve | undefined
        if (curve_buf_selector == (0).toChar()) {
            curve_buf = TypeChecker.curves_Curve_FromNumeric(valueDeserializer.readInt32())
        }
        else if (curve_buf_selector == (1).toChar()) {
            curve_buf = (valueDeserializer.readString() as string)
        }
        else if (curve_buf_selector == (2).toChar()) {
            curve_buf = (curves_ICurve_serializer.read(valueDeserializer) as curves.ICurve)
        }
        else {
            throw new Error("One of the branches for curve_buf has to be chosen through deserialisation.")
        }
        const curve_result : curves.Curve | string | curves.ICurve = (curve_buf as curves.Curve | string | curves.ICurve)
        const onProgress_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onProgress_buf : Callback_Extender_OnProgress | undefined
        if ((onProgress_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onProgress_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onProgress_buf__call : KPointer = valueDeserializer.readPointer()
            const onProgress_buf__callSync : KPointer = valueDeserializer.readPointer()
            onProgress_buf = (value: float):void => { 
    const onProgress_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onProgress_buf__argsSerializer.writeInt32(onProgress_buf__resource.resourceId);
    onProgress_buf__argsSerializer.writePointer(onProgress_buf__call);
    onProgress_buf__argsSerializer.writePointer(onProgress_buf__callSync);
    onProgress_buf__argsSerializer.writeFloat32(value);
    InteropNativeModule._CallCallback(1264236374, onProgress_buf__argsSerializer.asBuffer(), onProgress_buf__argsSerializer.length());
    onProgress_buf__argsSerializer.release();
    return; }
        }
        const onProgress_result : Callback_Extender_OnProgress | undefined = onProgress_buf
        const onFinish_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onFinish_buf : Callback_Extender_OnFinish | undefined
        if ((onFinish_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const onFinish_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onFinish_buf__call : KPointer = valueDeserializer.readPointer()
            const onFinish_buf__callSync : KPointer = valueDeserializer.readPointer()
            onFinish_buf = ():void => { 
    const onFinish_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onFinish_buf__argsSerializer.writeInt32(onFinish_buf__resource.resourceId);
    onFinish_buf__argsSerializer.writePointer(onFinish_buf__call);
    onFinish_buf__argsSerializer.writePointer(onFinish_buf__callSync);
    InteropNativeModule._CallCallback(-733525640, onFinish_buf__argsSerializer.asBuffer(), onFinish_buf__argsSerializer.length());
    onFinish_buf__argsSerializer.release();
    return; }
        }
        const onFinish_result : Callback_Extender_OnFinish | undefined = onFinish_buf
        let value : DoubleAnimationParam = ({propertyName: propertyName_result, startValue: startValue_result, endValue: endValue_result, duration: duration_result, delay: delay_result, curve: curve_result, onProgress: onProgress_result, onFinish: onFinish_result} as DoubleAnimationParam)
        return value
    }
}
export class ErrorEvent_serializer {
    public static write(buffer: SerializerBase, value: ErrorEvent): void {
        let valueSerializer : SerializerBase = buffer
        const value_type  = value.type
        valueSerializer.writeString(value_type)
        const value_timeStamp  = value.timeStamp
        valueSerializer.writeInt64(value_timeStamp)
        const value_message  = value.message
        valueSerializer.writeString(value_message)
        const value_filename  = value.filename
        valueSerializer.writeString(value_filename)
        const value_lineno  = value.lineno
        valueSerializer.writeNumber(value_lineno)
        const value_colno  = value.colno
        valueSerializer.writeNumber(value_colno)
        const value_error  = value.error
        valueSerializer.holdAndWriteObject(value_error)
    }
    public static read(buffer: DeserializerBase): ErrorEvent {
        let valueDeserializer : DeserializerBase = buffer
        const type_result : string = (valueDeserializer.readString() as string)
        const timeStamp_result : int64 = valueDeserializer.readInt64()
        const message_result : string = (valueDeserializer.readString() as string)
        const filename_result : string = (valueDeserializer.readString() as string)
        const lineno_result : number = (valueDeserializer.readNumber() as number)
        const colno_result : number = (valueDeserializer.readNumber() as number)
        const error_result : Object = (valueDeserializer.readObject() as object)
        let value : ErrorEvent = ({type: type_result, timeStamp: timeStamp_result, message: message_result, filename: filename_result, lineno: lineno_result, colno: colno_result, error: error_result} as ErrorEvent)
        return value
    }
}
export class Event_serializer {
    public static write(buffer: SerializerBase, value: Event): void {
        let valueSerializer : SerializerBase = buffer
        const value_type  = value.type
        valueSerializer.writeString(value_type)
        const value_timeStamp  = value.timeStamp
        valueSerializer.writeInt64(value_timeStamp)
    }
    public static read(buffer: DeserializerBase): Event {
        let valueDeserializer : DeserializerBase = buffer
        const type_result : string = (valueDeserializer.readString() as string)
        const timeStamp_result : int64 = valueDeserializer.readInt64()
        let value : Event = ({type: type_result, timeStamp: timeStamp_result} as Event)
        return value
    }
}
export class FontInfo_serializer {
    public static write(buffer: SerializerBase, value: FontInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_path  = value.path
        valueSerializer.writeString(value_path)
        const value_postScriptName  = value.postScriptName
        valueSerializer.writeString(value_postScriptName)
        const value_fullName  = value.fullName
        valueSerializer.writeString(value_fullName)
        const value_family  = value.family
        valueSerializer.writeString(value_family)
        const value_subfamily  = value.subfamily
        valueSerializer.writeString(value_subfamily)
        const value_weight  = value.weight
        valueSerializer.writeNumber(value_weight)
        const value_width  = value.width
        valueSerializer.writeNumber(value_width)
        const value_italic  = value.italic
        valueSerializer.writeBoolean(value_italic)
        const value_monoSpace  = value.monoSpace
        valueSerializer.writeBoolean(value_monoSpace)
        const value_symbolic  = value.symbolic
        valueSerializer.writeBoolean(value_symbolic)
    }
    public static read(buffer: DeserializerBase): FontInfo {
        let valueDeserializer : DeserializerBase = buffer
        const path_result : string = (valueDeserializer.readString() as string)
        const postScriptName_result : string = (valueDeserializer.readString() as string)
        const fullName_result : string = (valueDeserializer.readString() as string)
        const family_result : string = (valueDeserializer.readString() as string)
        const subfamily_result : string = (valueDeserializer.readString() as string)
        const weight_result : number = (valueDeserializer.readNumber() as number)
        const width_result : number = (valueDeserializer.readNumber() as number)
        const italic_result : boolean = valueDeserializer.readBoolean()
        const monoSpace_result : boolean = valueDeserializer.readBoolean()
        const symbolic_result : boolean = valueDeserializer.readBoolean()
        let value : FontInfo = ({path: path_result, postScriptName: postScriptName_result, fullName: fullName_result, family: family_result, subfamily: subfamily_result, weight: weight_result, width: width_result, italic: italic_result, monoSpace: monoSpace_result, symbolic: symbolic_result} as FontInfo)
        return value
    }
}
export class MessageEvents_serializer {
    public static write(buffer: SerializerBase, value: MessageEvents): void {
        let valueSerializer : SerializerBase = buffer
        const value_type  = value.type
        valueSerializer.writeString(value_type)
        const value_timeStamp  = value.timeStamp
        valueSerializer.writeInt64(value_timeStamp)
        const value_data  = value.data
        valueSerializer.holdAndWriteObject(value_data)
    }
    public static read(buffer: DeserializerBase): MessageEvents {
        let valueDeserializer : DeserializerBase = buffer
        const type_result : string = (valueDeserializer.readString() as string)
        const timeStamp_result : int64 = valueDeserializer.readInt64()
        const data_result : object = (valueDeserializer.readObject() as object)
        let value : MessageEvents = ({type: type_result, timeStamp: timeStamp_result, data: data_result} as MessageEvents)
        return value
    }
}
export class PostMessageOptions_serializer {
    public static write(buffer: SerializerBase, value: PostMessageOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_transfer  = value.transfer
        let value_transfer_type : int32 = RuntimeType.UNDEFINED
        value_transfer_type = runtimeType(value_transfer)
        valueSerializer.writeInt8((value_transfer_type).toChar())
        if ((value_transfer_type) != (RuntimeType.UNDEFINED)) {
            const value_transfer_value  = value_transfer!
            valueSerializer.writeInt32((value_transfer_value.length).toInt())
            for (let value_transfer_value_counter_i = 0; value_transfer_value_counter_i < value_transfer_value.length; value_transfer_value_counter_i++) {
                const value_transfer_value_element : Object = value_transfer_value[value_transfer_value_counter_i]
                valueSerializer.holdAndWriteObject(value_transfer_value_element)
            }
        }
    }
    public static read(buffer: DeserializerBase): PostMessageOptions {
        let valueDeserializer : DeserializerBase = buffer
        const transfer_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let transfer_buf : Array<Object> | undefined
        if ((transfer_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const transfer_buf__length : int32 = valueDeserializer.readInt32()
            let transfer_buf_ : Array<Object> = new Array<Object>(transfer_buf__length)
            for (let transfer_buf__i = 0; transfer_buf__i < transfer_buf__length; transfer_buf__i++) {
                transfer_buf_[transfer_buf__i] = (valueDeserializer.readObject() as object)
            }
            transfer_buf = transfer_buf_
        }
        const transfer_result : Array<Object> | undefined = transfer_buf
        let value : PostMessageOptions = ({transfer: transfer_result} as PostMessageOptions)
        return value
    }
}
export class SnapshotOptions_serializer {
    public static write(buffer: SerializerBase, value: SnapshotOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_scale  = value.scale
        let value_scale_type : int32 = RuntimeType.UNDEFINED
        value_scale_type = runtimeType(value_scale)
        valueSerializer.writeInt8((value_scale_type).toChar())
        if ((value_scale_type) != (RuntimeType.UNDEFINED)) {
            const value_scale_value  = value_scale!
            valueSerializer.writeNumber(value_scale_value)
        }
        const value_waitUntilRenderFinished  = value.waitUntilRenderFinished
        let value_waitUntilRenderFinished_type : int32 = RuntimeType.UNDEFINED
        value_waitUntilRenderFinished_type = runtimeType(value_waitUntilRenderFinished)
        valueSerializer.writeInt8((value_waitUntilRenderFinished_type).toChar())
        if ((value_waitUntilRenderFinished_type) != (RuntimeType.UNDEFINED)) {
            const value_waitUntilRenderFinished_value  = value_waitUntilRenderFinished!
            valueSerializer.writeBoolean(value_waitUntilRenderFinished_value)
        }
    }
    public static read(buffer: DeserializerBase): SnapshotOptions {
        let valueDeserializer : DeserializerBase = buffer
        const scale_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let scale_buf : number | undefined
        if ((scale_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            scale_buf = (valueDeserializer.readNumber() as number)
        }
        const scale_result : number | undefined = scale_buf
        const waitUntilRenderFinished_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let waitUntilRenderFinished_buf : boolean | undefined
        if ((waitUntilRenderFinished_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            waitUntilRenderFinished_buf = valueDeserializer.readBoolean()
        }
        const waitUntilRenderFinished_result : boolean | undefined = waitUntilRenderFinished_buf
        let value : SnapshotOptions = ({scale: scale_result, waitUntilRenderFinished: waitUntilRenderFinished_result} as SnapshotOptions)
        return value
    }
}
export class WorkerOptions_serializer {
    public static write(buffer: SerializerBase, value: WorkerOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_type  = value.type
        let value_type_type : int32 = RuntimeType.UNDEFINED
        value_type_type = runtimeType(value_type)
        valueSerializer.writeInt8((value_type_type).toChar())
        if ((value_type_type) != (RuntimeType.UNDEFINED)) {
            const value_type_value  = value_type!
            valueSerializer.writeString(value_type_value)
        }
        const value_name  = value.name
        let value_name_type : int32 = RuntimeType.UNDEFINED
        value_name_type = runtimeType(value_name)
        valueSerializer.writeInt8((value_name_type).toChar())
        if ((value_name_type) != (RuntimeType.UNDEFINED)) {
            const value_name_value  = value_name!
            valueSerializer.writeString(value_name_value)
        }
        const value_shared  = value.shared
        let value_shared_type : int32 = RuntimeType.UNDEFINED
        value_shared_type = runtimeType(value_shared)
        valueSerializer.writeInt8((value_shared_type).toChar())
        if ((value_shared_type) != (RuntimeType.UNDEFINED)) {
            const value_shared_value  = value_shared!
            valueSerializer.writeBoolean(value_shared_value)
        }
    }
    public static read(buffer: DeserializerBase): WorkerOptions {
        let valueDeserializer : DeserializerBase = buffer
        const type_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let type_buf : string | undefined
        if ((type_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            type_buf = (valueDeserializer.readString() as string)
        }
        const type_result : string | undefined = type_buf
        const name_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let name_buf : string | undefined
        if ((name_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            name_buf = (valueDeserializer.readString() as string)
        }
        const name_result : string | undefined = name_buf
        const shared_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let shared_buf : boolean | undefined
        if ((shared_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            shared_buf = valueDeserializer.readBoolean()
        }
        const shared_result : boolean | undefined = shared_buf
        let value : WorkerOptions = ({type: type_result, name: name_result, shared: shared_result} as WorkerOptions)
        return value
    }
}
export class ComponentInfo_serializer {
    public static write(buffer: SerializerBase, value: ComponentInfo): void {
        let valueSerializer : SerializerBase = buffer
        const value_size  = value.size
        Size_serializer.write(valueSerializer, value_size)
        const value_localOffset  = value.localOffset
        Offset_componentutils_serializer.write(valueSerializer, value_localOffset)
        const value_windowOffset  = value.windowOffset
        Offset_componentutils_serializer.write(valueSerializer, value_windowOffset)
        const value_screenOffset  = value.screenOffset
        Offset_componentutils_serializer.write(valueSerializer, value_screenOffset)
        const value_translate  = value.translate
        TranslateResult_serializer.write(valueSerializer, value_translate)
        const value_scale  = value.scale
        ScaleResult_serializer.write(valueSerializer, value_scale)
        const value_rotate  = value.rotate
        RotateResult_serializer.write(valueSerializer, value_rotate)
        const value_transform  = value.transform
        const value_transform_0  = value_transform[0]
        valueSerializer.writeNumber(value_transform_0)
        const value_transform_1  = value_transform[1]
        valueSerializer.writeNumber(value_transform_1)
        const value_transform_2  = value_transform[2]
        valueSerializer.writeNumber(value_transform_2)
        const value_transform_3  = value_transform[3]
        valueSerializer.writeNumber(value_transform_3)
        const value_transform_4  = value_transform[4]
        valueSerializer.writeNumber(value_transform_4)
        const value_transform_5  = value_transform[5]
        valueSerializer.writeNumber(value_transform_5)
        const value_transform_6  = value_transform[6]
        valueSerializer.writeNumber(value_transform_6)
        const value_transform_7  = value_transform[7]
        valueSerializer.writeNumber(value_transform_7)
        const value_transform_8  = value_transform[8]
        valueSerializer.writeNumber(value_transform_8)
        const value_transform_9  = value_transform[9]
        valueSerializer.writeNumber(value_transform_9)
        const value_transform_10  = value_transform[10]
        valueSerializer.writeNumber(value_transform_10)
        const value_transform_11  = value_transform[11]
        valueSerializer.writeNumber(value_transform_11)
        const value_transform_12  = value_transform[12]
        valueSerializer.writeNumber(value_transform_12)
        const value_transform_13  = value_transform[13]
        valueSerializer.writeNumber(value_transform_13)
        const value_transform_14  = value_transform[14]
        valueSerializer.writeNumber(value_transform_14)
        const value_transform_15  = value_transform[15]
        valueSerializer.writeNumber(value_transform_15)
    }
    public static read(buffer: DeserializerBase): ComponentInfo {
        let valueDeserializer : DeserializerBase = buffer
        const size_result : Size = Size_serializer.read(valueDeserializer)
        const localOffset_result : Offset_componentutils = Offset_componentutils_serializer.read(valueDeserializer)
        const windowOffset_result : Offset_componentutils = Offset_componentutils_serializer.read(valueDeserializer)
        const screenOffset_result : Offset_componentutils = Offset_componentutils_serializer.read(valueDeserializer)
        const translate_result : TranslateResult = TranslateResult_serializer.read(valueDeserializer)
        const scale_result : ScaleResult = ScaleResult_serializer.read(valueDeserializer)
        const rotate_result : RotateResult = RotateResult_serializer.read(valueDeserializer)
        const transform_buf_value0 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value1 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value2 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value3 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value4 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value5 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value6 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value7 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value8 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value9 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value10 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value11 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value12 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value13 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value14 : number = (valueDeserializer.readNumber() as number)
        const transform_buf_value15 : number = (valueDeserializer.readNumber() as number)
        const transform_result : Matrix4Result = ([transform_buf_value0, transform_buf_value1, transform_buf_value2, transform_buf_value3, transform_buf_value4, transform_buf_value5, transform_buf_value6, transform_buf_value7, transform_buf_value8, transform_buf_value9, transform_buf_value10, transform_buf_value11, transform_buf_value12, transform_buf_value13, transform_buf_value14, transform_buf_value15] as Matrix4Result)
        let value : ComponentInfo = ({size: size_result, localOffset: localOffset_result, windowOffset: windowOffset_result, screenOffset: screenOffset_result, translate: translate_result, scale: scale_result, rotate: rotate_result, transform: transform_result} as ComponentInfo)
        return value
    }
}
export class FontOptions_serializer {
    public static write(buffer: SerializerBase, value: FontOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_familyName  = value.familyName
        let value_familyName_type : int32 = RuntimeType.UNDEFINED
        value_familyName_type = runtimeType(value_familyName)
        if (RuntimeType.STRING == value_familyName_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_familyName_0  = value_familyName as string
            valueSerializer.writeString(value_familyName_0)
        }
        else if (RuntimeType.OBJECT == value_familyName_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_familyName_1  = value_familyName as Resource
            Resource_serializer.write(valueSerializer, value_familyName_1)
        }
        const value_familySrc  = value.familySrc
        let value_familySrc_type : int32 = RuntimeType.UNDEFINED
        value_familySrc_type = runtimeType(value_familySrc)
        if (RuntimeType.STRING == value_familySrc_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_familySrc_0  = value_familySrc as string
            valueSerializer.writeString(value_familySrc_0)
        }
        else if (RuntimeType.OBJECT == value_familySrc_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_familySrc_1  = value_familySrc as Resource
            Resource_serializer.write(valueSerializer, value_familySrc_1)
        }
    }
    public static read(buffer: DeserializerBase): FontOptions {
        let valueDeserializer : DeserializerBase = buffer
        const familyName_buf_selector : int32 = valueDeserializer.readInt8()
        let familyName_buf : string | Resource | undefined
        if (familyName_buf_selector == (0).toChar()) {
            familyName_buf = (valueDeserializer.readString() as string)
        }
        else if (familyName_buf_selector == (1).toChar()) {
            familyName_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for familyName_buf has to be chosen through deserialisation.")
        }
        const familyName_result : string | Resource = (familyName_buf as string | Resource)
        const familySrc_buf_selector : int32 = valueDeserializer.readInt8()
        let familySrc_buf : string | Resource | undefined
        if (familySrc_buf_selector == (0).toChar()) {
            familySrc_buf = (valueDeserializer.readString() as string)
        }
        else if (familySrc_buf_selector == (1).toChar()) {
            familySrc_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for familySrc_buf has to be chosen through deserialisation.")
        }
        const familySrc_result : string | Resource = (familySrc_buf as string | Resource)
        let value : FontOptions = ({familyName: familyName_result, familySrc: familySrc_result} as FontOptions)
        return value
    }
}
export class MeasureOptions_serializer {
    public static write(buffer: SerializerBase, value: MeasureOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_textContent  = value.textContent
        let value_textContent_type : int32 = RuntimeType.UNDEFINED
        value_textContent_type = runtimeType(value_textContent)
        if (RuntimeType.STRING == value_textContent_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_textContent_0  = value_textContent as string
            valueSerializer.writeString(value_textContent_0)
        }
        else if (RuntimeType.OBJECT == value_textContent_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_textContent_1  = value_textContent as Resource
            Resource_serializer.write(valueSerializer, value_textContent_1)
        }
        const value_constraintWidth  = value.constraintWidth
        let value_constraintWidth_type : int32 = RuntimeType.UNDEFINED
        value_constraintWidth_type = runtimeType(value_constraintWidth)
        valueSerializer.writeInt8((value_constraintWidth_type).toChar())
        if ((value_constraintWidth_type) != (RuntimeType.UNDEFINED)) {
            const value_constraintWidth_value  = value_constraintWidth!
            let value_constraintWidth_value_type : int32 = RuntimeType.UNDEFINED
            value_constraintWidth_value_type = runtimeType(value_constraintWidth_value)
            if (RuntimeType.NUMBER == value_constraintWidth_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_constraintWidth_value_0  = value_constraintWidth_value as number
                valueSerializer.writeNumber(value_constraintWidth_value_0)
            }
            else if (RuntimeType.STRING == value_constraintWidth_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_constraintWidth_value_1  = value_constraintWidth_value as string
                valueSerializer.writeString(value_constraintWidth_value_1)
            }
            else if (RuntimeType.OBJECT == value_constraintWidth_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_constraintWidth_value_2  = value_constraintWidth_value as Resource
                Resource_serializer.write(valueSerializer, value_constraintWidth_value_2)
            }
        }
        const value_fontSize  = value.fontSize
        let value_fontSize_type : int32 = RuntimeType.UNDEFINED
        value_fontSize_type = runtimeType(value_fontSize)
        valueSerializer.writeInt8((value_fontSize_type).toChar())
        if ((value_fontSize_type) != (RuntimeType.UNDEFINED)) {
            const value_fontSize_value  = value_fontSize!
            let value_fontSize_value_type : int32 = RuntimeType.UNDEFINED
            value_fontSize_value_type = runtimeType(value_fontSize_value)
            if (RuntimeType.NUMBER == value_fontSize_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_fontSize_value_0  = value_fontSize_value as number
                valueSerializer.writeNumber(value_fontSize_value_0)
            }
            else if (RuntimeType.STRING == value_fontSize_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_fontSize_value_1  = value_fontSize_value as string
                valueSerializer.writeString(value_fontSize_value_1)
            }
            else if (RuntimeType.OBJECT == value_fontSize_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_fontSize_value_2  = value_fontSize_value as Resource
                Resource_serializer.write(valueSerializer, value_fontSize_value_2)
            }
        }
        const value_fontStyle  = value.fontStyle
        let value_fontStyle_type : int32 = RuntimeType.UNDEFINED
        value_fontStyle_type = runtimeType(value_fontStyle)
        valueSerializer.writeInt8((value_fontStyle_type).toChar())
        if ((value_fontStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_fontStyle_value  = value_fontStyle!
            let value_fontStyle_value_type : int32 = RuntimeType.UNDEFINED
            value_fontStyle_value_type = runtimeType(value_fontStyle_value)
            if (RuntimeType.NUMBER == value_fontStyle_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_fontStyle_value_0  = value_fontStyle_value as number
                valueSerializer.writeNumber(value_fontStyle_value_0)
            }
            else if (TypeChecker.isFontStyle(value_fontStyle_value)) {
                valueSerializer.writeInt8((1).toChar())
                const value_fontStyle_value_1  = value_fontStyle_value as FontStyle
                valueSerializer.writeInt32(TypeChecker.FontStyle_ToNumeric(value_fontStyle_value_1))
            }
        }
        const value_fontWeight  = value.fontWeight
        let value_fontWeight_type : int32 = RuntimeType.UNDEFINED
        value_fontWeight_type = runtimeType(value_fontWeight)
        valueSerializer.writeInt8((value_fontWeight_type).toChar())
        if ((value_fontWeight_type) != (RuntimeType.UNDEFINED)) {
            const value_fontWeight_value  = value_fontWeight!
            let value_fontWeight_value_type : int32 = RuntimeType.UNDEFINED
            value_fontWeight_value_type = runtimeType(value_fontWeight_value)
            if (RuntimeType.NUMBER == value_fontWeight_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_fontWeight_value_0  = value_fontWeight_value as number
                valueSerializer.writeNumber(value_fontWeight_value_0)
            }
            else if (RuntimeType.STRING == value_fontWeight_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_fontWeight_value_1  = value_fontWeight_value as string
                valueSerializer.writeString(value_fontWeight_value_1)
            }
            else if (TypeChecker.isFontWeight(value_fontWeight_value)) {
                valueSerializer.writeInt8((2).toChar())
                const value_fontWeight_value_2  = value_fontWeight_value as FontWeight
                valueSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_fontWeight_value_2))
            }
        }
        const value_fontFamily  = value.fontFamily
        let value_fontFamily_type : int32 = RuntimeType.UNDEFINED
        value_fontFamily_type = runtimeType(value_fontFamily)
        valueSerializer.writeInt8((value_fontFamily_type).toChar())
        if ((value_fontFamily_type) != (RuntimeType.UNDEFINED)) {
            const value_fontFamily_value  = value_fontFamily!
            let value_fontFamily_value_type : int32 = RuntimeType.UNDEFINED
            value_fontFamily_value_type = runtimeType(value_fontFamily_value)
            if (RuntimeType.STRING == value_fontFamily_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_fontFamily_value_0  = value_fontFamily_value as string
                valueSerializer.writeString(value_fontFamily_value_0)
            }
            else if (RuntimeType.OBJECT == value_fontFamily_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_fontFamily_value_1  = value_fontFamily_value as Resource
                Resource_serializer.write(valueSerializer, value_fontFamily_value_1)
            }
        }
        const value_letterSpacing  = value.letterSpacing
        let value_letterSpacing_type : int32 = RuntimeType.UNDEFINED
        value_letterSpacing_type = runtimeType(value_letterSpacing)
        valueSerializer.writeInt8((value_letterSpacing_type).toChar())
        if ((value_letterSpacing_type) != (RuntimeType.UNDEFINED)) {
            const value_letterSpacing_value  = value_letterSpacing!
            let value_letterSpacing_value_type : int32 = RuntimeType.UNDEFINED
            value_letterSpacing_value_type = runtimeType(value_letterSpacing_value)
            if (RuntimeType.NUMBER == value_letterSpacing_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_letterSpacing_value_0  = value_letterSpacing_value as number
                valueSerializer.writeNumber(value_letterSpacing_value_0)
            }
            else if (RuntimeType.STRING == value_letterSpacing_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_letterSpacing_value_1  = value_letterSpacing_value as string
                valueSerializer.writeString(value_letterSpacing_value_1)
            }
        }
        const value_textAlign  = value.textAlign
        let value_textAlign_type : int32 = RuntimeType.UNDEFINED
        value_textAlign_type = runtimeType(value_textAlign)
        valueSerializer.writeInt8((value_textAlign_type).toChar())
        if ((value_textAlign_type) != (RuntimeType.UNDEFINED)) {
            const value_textAlign_value  = (value_textAlign as text.TextAlign)
            valueSerializer.writeInt32(TypeChecker.text_TextAlign_ToNumeric(value_textAlign_value))
        }
        const value_overflow  = value.overflow
        let value_overflow_type : int32 = RuntimeType.UNDEFINED
        value_overflow_type = runtimeType(value_overflow)
        valueSerializer.writeInt8((value_overflow_type).toChar())
        if ((value_overflow_type) != (RuntimeType.UNDEFINED)) {
            const value_overflow_value  = value_overflow!
            let value_overflow_value_type : int32 = RuntimeType.UNDEFINED
            value_overflow_value_type = runtimeType(value_overflow_value)
            if (RuntimeType.NUMBER == value_overflow_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_overflow_value_0  = value_overflow_value as number
                valueSerializer.writeNumber(value_overflow_value_0)
            }
            else if (TypeChecker.isTextOverflow(value_overflow_value)) {
                valueSerializer.writeInt8((1).toChar())
                const value_overflow_value_1  = value_overflow_value as TextOverflow
                valueSerializer.writeInt32(TypeChecker.TextOverflow_ToNumeric(value_overflow_value_1))
            }
        }
        const value_maxLines  = value.maxLines
        let value_maxLines_type : int32 = RuntimeType.UNDEFINED
        value_maxLines_type = runtimeType(value_maxLines)
        valueSerializer.writeInt8((value_maxLines_type).toChar())
        if ((value_maxLines_type) != (RuntimeType.UNDEFINED)) {
            const value_maxLines_value  = value_maxLines!
            valueSerializer.writeNumber(value_maxLines_value)
        }
        const value_lineHeight  = value.lineHeight
        let value_lineHeight_type : int32 = RuntimeType.UNDEFINED
        value_lineHeight_type = runtimeType(value_lineHeight)
        valueSerializer.writeInt8((value_lineHeight_type).toChar())
        if ((value_lineHeight_type) != (RuntimeType.UNDEFINED)) {
            const value_lineHeight_value  = value_lineHeight!
            let value_lineHeight_value_type : int32 = RuntimeType.UNDEFINED
            value_lineHeight_value_type = runtimeType(value_lineHeight_value)
            if (RuntimeType.NUMBER == value_lineHeight_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_lineHeight_value_0  = value_lineHeight_value as number
                valueSerializer.writeNumber(value_lineHeight_value_0)
            }
            else if (RuntimeType.STRING == value_lineHeight_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_lineHeight_value_1  = value_lineHeight_value as string
                valueSerializer.writeString(value_lineHeight_value_1)
            }
            else if (RuntimeType.OBJECT == value_lineHeight_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_lineHeight_value_2  = value_lineHeight_value as Resource
                Resource_serializer.write(valueSerializer, value_lineHeight_value_2)
            }
        }
        const value_baselineOffset  = value.baselineOffset
        let value_baselineOffset_type : int32 = RuntimeType.UNDEFINED
        value_baselineOffset_type = runtimeType(value_baselineOffset)
        valueSerializer.writeInt8((value_baselineOffset_type).toChar())
        if ((value_baselineOffset_type) != (RuntimeType.UNDEFINED)) {
            const value_baselineOffset_value  = value_baselineOffset!
            let value_baselineOffset_value_type : int32 = RuntimeType.UNDEFINED
            value_baselineOffset_value_type = runtimeType(value_baselineOffset_value)
            if (RuntimeType.NUMBER == value_baselineOffset_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_baselineOffset_value_0  = value_baselineOffset_value as number
                valueSerializer.writeNumber(value_baselineOffset_value_0)
            }
            else if (RuntimeType.STRING == value_baselineOffset_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_baselineOffset_value_1  = value_baselineOffset_value as string
                valueSerializer.writeString(value_baselineOffset_value_1)
            }
        }
        const value_textCase  = value.textCase
        let value_textCase_type : int32 = RuntimeType.UNDEFINED
        value_textCase_type = runtimeType(value_textCase)
        valueSerializer.writeInt8((value_textCase_type).toChar())
        if ((value_textCase_type) != (RuntimeType.UNDEFINED)) {
            const value_textCase_value  = value_textCase!
            let value_textCase_value_type : int32 = RuntimeType.UNDEFINED
            value_textCase_value_type = runtimeType(value_textCase_value)
            if (RuntimeType.NUMBER == value_textCase_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_textCase_value_0  = value_textCase_value as number
                valueSerializer.writeNumber(value_textCase_value_0)
            }
            else if (TypeChecker.isTextCase(value_textCase_value)) {
                valueSerializer.writeInt8((1).toChar())
                const value_textCase_value_1  = value_textCase_value as TextCase
                valueSerializer.writeInt32(TypeChecker.TextCase_ToNumeric(value_textCase_value_1))
            }
        }
        const value_textIndent  = value.textIndent
        let value_textIndent_type : int32 = RuntimeType.UNDEFINED
        value_textIndent_type = runtimeType(value_textIndent)
        valueSerializer.writeInt8((value_textIndent_type).toChar())
        if ((value_textIndent_type) != (RuntimeType.UNDEFINED)) {
            const value_textIndent_value  = value_textIndent!
            let value_textIndent_value_type : int32 = RuntimeType.UNDEFINED
            value_textIndent_value_type = runtimeType(value_textIndent_value)
            if (RuntimeType.NUMBER == value_textIndent_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_textIndent_value_0  = value_textIndent_value as number
                valueSerializer.writeNumber(value_textIndent_value_0)
            }
            else if (RuntimeType.STRING == value_textIndent_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_textIndent_value_1  = value_textIndent_value as string
                valueSerializer.writeString(value_textIndent_value_1)
            }
        }
        const value_wordBreak  = value.wordBreak
        let value_wordBreak_type : int32 = RuntimeType.UNDEFINED
        value_wordBreak_type = runtimeType(value_wordBreak)
        valueSerializer.writeInt8((value_wordBreak_type).toChar())
        if ((value_wordBreak_type) != (RuntimeType.UNDEFINED)) {
            const value_wordBreak_value  = (value_wordBreak as text.WordBreak)
            valueSerializer.writeInt32(TypeChecker.text_WordBreak_ToNumeric(value_wordBreak_value))
        }
    }
    public static read(buffer: DeserializerBase): MeasureOptions {
        let valueDeserializer : DeserializerBase = buffer
        const textContent_buf_selector : int32 = valueDeserializer.readInt8()
        let textContent_buf : string | Resource | undefined
        if (textContent_buf_selector == (0).toChar()) {
            textContent_buf = (valueDeserializer.readString() as string)
        }
        else if (textContent_buf_selector == (1).toChar()) {
            textContent_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for textContent_buf has to be chosen through deserialisation.")
        }
        const textContent_result : string | Resource = (textContent_buf as string | Resource)
        const constraintWidth_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let constraintWidth_buf : number | string | Resource | undefined
        if ((constraintWidth_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const constraintWidth_buf__selector : int32 = valueDeserializer.readInt8()
            let constraintWidth_buf_ : number | string | Resource | undefined
            if (constraintWidth_buf__selector == (0).toChar()) {
                constraintWidth_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (constraintWidth_buf__selector == (1).toChar()) {
                constraintWidth_buf_ = (valueDeserializer.readString() as string)
            }
            else if (constraintWidth_buf__selector == (2).toChar()) {
                constraintWidth_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for constraintWidth_buf_ has to be chosen through deserialisation.")
            }
            constraintWidth_buf = (constraintWidth_buf_ as number | string | Resource)
        }
        const constraintWidth_result : number | string | Resource | undefined = constraintWidth_buf
        const fontSize_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontSize_buf : number | string | Resource | undefined
        if ((fontSize_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const fontSize_buf__selector : int32 = valueDeserializer.readInt8()
            let fontSize_buf_ : number | string | Resource | undefined
            if (fontSize_buf__selector == (0).toChar()) {
                fontSize_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (fontSize_buf__selector == (1).toChar()) {
                fontSize_buf_ = (valueDeserializer.readString() as string)
            }
            else if (fontSize_buf__selector == (2).toChar()) {
                fontSize_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for fontSize_buf_ has to be chosen through deserialisation.")
            }
            fontSize_buf = (fontSize_buf_ as number | string | Resource)
        }
        const fontSize_result : number | string | Resource | undefined = fontSize_buf
        const fontStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontStyle_buf : number | FontStyle | undefined
        if ((fontStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const fontStyle_buf__selector : int32 = valueDeserializer.readInt8()
            let fontStyle_buf_ : number | FontStyle | undefined
            if (fontStyle_buf__selector == (0).toChar()) {
                fontStyle_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (fontStyle_buf__selector == (1).toChar()) {
                fontStyle_buf_ = TypeChecker.FontStyle_FromNumeric(valueDeserializer.readInt32())
            }
            else {
                throw new Error("One of the branches for fontStyle_buf_ has to be chosen through deserialisation.")
            }
            fontStyle_buf = (fontStyle_buf_ as number | FontStyle)
        }
        const fontStyle_result : number | FontStyle | undefined = fontStyle_buf
        const fontWeight_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontWeight_buf : number | string | FontWeight | undefined
        if ((fontWeight_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const fontWeight_buf__selector : int32 = valueDeserializer.readInt8()
            let fontWeight_buf_ : number | string | FontWeight | undefined
            if (fontWeight_buf__selector == (0).toChar()) {
                fontWeight_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (fontWeight_buf__selector == (1).toChar()) {
                fontWeight_buf_ = (valueDeserializer.readString() as string)
            }
            else if (fontWeight_buf__selector == (2).toChar()) {
                fontWeight_buf_ = TypeChecker.FontWeight_FromNumeric(valueDeserializer.readInt32())
            }
            else {
                throw new Error("One of the branches for fontWeight_buf_ has to be chosen through deserialisation.")
            }
            fontWeight_buf = (fontWeight_buf_ as number | string | FontWeight)
        }
        const fontWeight_result : number | string | FontWeight | undefined = fontWeight_buf
        const fontFamily_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let fontFamily_buf : string | Resource | undefined
        if ((fontFamily_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const fontFamily_buf__selector : int32 = valueDeserializer.readInt8()
            let fontFamily_buf_ : string | Resource | undefined
            if (fontFamily_buf__selector == (0).toChar()) {
                fontFamily_buf_ = (valueDeserializer.readString() as string)
            }
            else if (fontFamily_buf__selector == (1).toChar()) {
                fontFamily_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for fontFamily_buf_ has to be chosen through deserialisation.")
            }
            fontFamily_buf = (fontFamily_buf_ as string | Resource)
        }
        const fontFamily_result : string | Resource | undefined = fontFamily_buf
        const letterSpacing_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let letterSpacing_buf : number | string | undefined
        if ((letterSpacing_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const letterSpacing_buf__selector : int32 = valueDeserializer.readInt8()
            let letterSpacing_buf_ : number | string | undefined
            if (letterSpacing_buf__selector == (0).toChar()) {
                letterSpacing_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (letterSpacing_buf__selector == (1).toChar()) {
                letterSpacing_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for letterSpacing_buf_ has to be chosen through deserialisation.")
            }
            letterSpacing_buf = (letterSpacing_buf_ as number | string)
        }
        const letterSpacing_result : number | string | undefined = letterSpacing_buf
        const textAlign_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textAlign_buf : text.TextAlign | undefined
        if ((textAlign_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            textAlign_buf = TypeChecker.text_TextAlign_FromNumeric(valueDeserializer.readInt32())
        }
        const textAlign_result : text.TextAlign | undefined = textAlign_buf
        const overflow_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let overflow_buf : number | TextOverflow | undefined
        if ((overflow_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const overflow_buf__selector : int32 = valueDeserializer.readInt8()
            let overflow_buf_ : number | TextOverflow | undefined
            if (overflow_buf__selector == (0).toChar()) {
                overflow_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (overflow_buf__selector == (1).toChar()) {
                overflow_buf_ = TypeChecker.TextOverflow_FromNumeric(valueDeserializer.readInt32())
            }
            else {
                throw new Error("One of the branches for overflow_buf_ has to be chosen through deserialisation.")
            }
            overflow_buf = (overflow_buf_ as number | TextOverflow)
        }
        const overflow_result : number | TextOverflow | undefined = overflow_buf
        const maxLines_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxLines_buf : number | undefined
        if ((maxLines_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            maxLines_buf = (valueDeserializer.readNumber() as number)
        }
        const maxLines_result : number | undefined = maxLines_buf
        const lineHeight_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let lineHeight_buf : number | string | Resource | undefined
        if ((lineHeight_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const lineHeight_buf__selector : int32 = valueDeserializer.readInt8()
            let lineHeight_buf_ : number | string | Resource | undefined
            if (lineHeight_buf__selector == (0).toChar()) {
                lineHeight_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (lineHeight_buf__selector == (1).toChar()) {
                lineHeight_buf_ = (valueDeserializer.readString() as string)
            }
            else if (lineHeight_buf__selector == (2).toChar()) {
                lineHeight_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for lineHeight_buf_ has to be chosen through deserialisation.")
            }
            lineHeight_buf = (lineHeight_buf_ as number | string | Resource)
        }
        const lineHeight_result : number | string | Resource | undefined = lineHeight_buf
        const baselineOffset_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let baselineOffset_buf : number | string | undefined
        if ((baselineOffset_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const baselineOffset_buf__selector : int32 = valueDeserializer.readInt8()
            let baselineOffset_buf_ : number | string | undefined
            if (baselineOffset_buf__selector == (0).toChar()) {
                baselineOffset_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (baselineOffset_buf__selector == (1).toChar()) {
                baselineOffset_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for baselineOffset_buf_ has to be chosen through deserialisation.")
            }
            baselineOffset_buf = (baselineOffset_buf_ as number | string)
        }
        const baselineOffset_result : number | string | undefined = baselineOffset_buf
        const textCase_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textCase_buf : number | TextCase | undefined
        if ((textCase_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const textCase_buf__selector : int32 = valueDeserializer.readInt8()
            let textCase_buf_ : number | TextCase | undefined
            if (textCase_buf__selector == (0).toChar()) {
                textCase_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (textCase_buf__selector == (1).toChar()) {
                textCase_buf_ = TypeChecker.TextCase_FromNumeric(valueDeserializer.readInt32())
            }
            else {
                throw new Error("One of the branches for textCase_buf_ has to be chosen through deserialisation.")
            }
            textCase_buf = (textCase_buf_ as number | TextCase)
        }
        const textCase_result : number | TextCase | undefined = textCase_buf
        const textIndent_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let textIndent_buf : number | string | undefined
        if ((textIndent_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const textIndent_buf__selector : int32 = valueDeserializer.readInt8()
            let textIndent_buf_ : number | string | undefined
            if (textIndent_buf__selector == (0).toChar()) {
                textIndent_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (textIndent_buf__selector == (1).toChar()) {
                textIndent_buf_ = (valueDeserializer.readString() as string)
            }
            else {
                throw new Error("One of the branches for textIndent_buf_ has to be chosen through deserialisation.")
            }
            textIndent_buf = (textIndent_buf_ as number | string)
        }
        const textIndent_result : number | string | undefined = textIndent_buf
        const wordBreak_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let wordBreak_buf : text.WordBreak | undefined
        if ((wordBreak_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            wordBreak_buf = TypeChecker.text_WordBreak_FromNumeric(valueDeserializer.readInt32())
        }
        const wordBreak_result : text.WordBreak | undefined = wordBreak_buf
        let value : MeasureOptions = ({textContent: textContent_result, constraintWidth: constraintWidth_result, fontSize: fontSize_result, fontStyle: fontStyle_result, fontWeight: fontWeight_result, fontFamily: fontFamily_result, letterSpacing: letterSpacing_result, textAlign: textAlign_result, overflow: overflow_result, maxLines: maxLines_result, lineHeight: lineHeight_result, baselineOffset: baselineOffset_result, textCase: textCase_result, textIndent: textIndent_result, wordBreak: wordBreak_result} as MeasureOptions)
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
