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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { ContentModifier } from "./../handwritten"
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
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
export class ContentModifierHelper {
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
}
