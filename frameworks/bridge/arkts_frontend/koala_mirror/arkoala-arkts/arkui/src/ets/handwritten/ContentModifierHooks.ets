/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { memo } from "@koalaui/runtime/annotations"
import { ContentModifierHelper } from "../generated"
import { ArkButtonComponent, ButtonConfiguration} from "../generated"
import { ArkCheckboxComponent, CheckBoxConfiguration } from "../generated"
import { ArkDataPanelComponent, DataPanelConfiguration } from "../generated"
import { ArkGaugeComponent, GaugeConfiguration } from "../generated"
import { ArkLoadingProgressComponent, LoadingProgressConfiguration } from "../generated"
import { ArkProgressComponent, ProgressConfiguration } from "../generated"
import { ArkRadioComponent, RadioConfiguration } from "../generated"
import { ArkRatingComponent, RatingConfiguration } from "../generated"
import { ArkSelectComponent, MenuItemConfiguration } from "../generated"
import { ArkSliderComponent, SliderConfiguration } from "../generated"
import { ArkTextClockComponent, TextClockConfiguration } from "../generated"
import { ArkTextTimerComponent, TextTimerConfiguration } from "../generated"
import { ArkToggleComponent, ToggleConfiguration } from "../generated"
import { CustomBuilder } from "../generated"
import { CallbackTransformer } from "./../CallbackTransformer"
import { KPointer } from "@koalaui/interop"

export class WrappedBuilder<Args> {
    constructor(
        // @memo
        builder: (args: Args) => void) {
        this.builder = builder;
    }
    // @memo
    builder: ((args: Args) => void);
}

export function wrapBuilder<Args>(
    // @memo
    builder: (args: Args) => void
): WrappedBuilder<Args> {
    return new WrappedBuilder<Args>(builder);
}

export interface ContentModifier<T> {
  applyContent(): WrappedBuilder<Array<T>>
}

function memoWrapper<Args>(
    // @memo
    builder: ((args: Args) => void), args: Args
): CustomBuilder {
    // @memo
    const wrapper = () => { builder(args) }
    return wrapper
}

// @memo
export function hookButtonContentModifier(
    receiver: ArkButtonComponent, value?: ContentModifier<ButtonConfiguration>) {
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const buttonBuilder = (parentNode: KPointer, config: ButtonConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, [config]))
    }
    if (value) {
        ContentModifierHelper.contentModifierButton(receiver.getPeer().peer.ptr, value!, buttonBuilder)
    }
}

// @memo
export function hookCheckBoxContentModifier(
    receiver: ArkCheckboxComponent, value?: ContentModifier<CheckBoxConfiguration>) {
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const checkboxBuilder = (parentNode: KPointer, config: CheckBoxConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, [config]))
    }
    if (value) {
        ContentModifierHelper.contentModifierCheckBox(receiver.getPeer().peer.ptr, value!, checkboxBuilder)
    }
}

// @memo
export function hookDataPanelContentModifier(
    receiver: ArkDataPanelComponent, value?: ContentModifier<DataPanelConfiguration>) {
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const dataPanelBuilder = (parentNode: KPointer, config: DataPanelConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, [config]))
    }
    if (value) {
        ContentModifierHelper.contentModifierDataPanel(receiver.getPeer().peer.ptr, value!, dataPanelBuilder)
    }
}

// @memo
export function hookGaugeContentModifier(
    receiver: ArkGaugeComponent, value?: ContentModifier<GaugeConfiguration>) {
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const gaugeBuilder = (parentNode: KPointer, config: GaugeConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, [config]))
    }
    if (value) {
        ContentModifierHelper.contentModifierGauge(receiver.getPeer().peer.ptr, value!, gaugeBuilder)
    }
}

// @memo
export function hookLoadingProgressContentModifier(
    receiver: ArkLoadingProgressComponent, value?: ContentModifier<LoadingProgressConfiguration>) {
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const loadingProgressBuilder = (parentNode: KPointer, config: LoadingProgressConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, [config]))
    }
    if (value) {
        ContentModifierHelper.contentModifierLoadingProgress(receiver.getPeer().peer.ptr, value!, loadingProgressBuilder)
    }
}

// @memo
export function hookProgressContentModifier(
    receiver: ArkProgressComponent, value?: ContentModifier<ProgressConfiguration>) {
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const progressBuilder = (parentNode: KPointer, config: ProgressConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, [config]))
    }
    if (value) {
        ContentModifierHelper.contentModifierProgress(receiver.getPeer().peer.ptr, value!, progressBuilder)
    }
}

// @memo
export function hookRadioContentModifier(
    receiver: ArkRadioComponent, value?: ContentModifier<RadioConfiguration>) {
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const radioBuilder = (parentNode: KPointer, config: RadioConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, [config]))
    }
    if (value) {
        ContentModifierHelper.contentModifierRadio(receiver.getPeer().peer.ptr, value!, radioBuilder)
    }
}

// @memo
export function hookRatingContentModifier(
    receiver: ArkRatingComponent, value?: ContentModifier<RatingConfiguration>) {
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const ratingBuilder = (parentNode: KPointer, config: RatingConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, [config]))
    }
    if (value) {
        ContentModifierHelper.contentModifierRating(receiver.getPeer().peer.ptr, value!, ratingBuilder)
    }
}

// @memo
export function hookSelectContentModifier(
    receiver: ArkSelectComponent, value?: ContentModifier<MenuItemConfiguration>) {
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const menuItemBuilder = (parentNode: KPointer, config: MenuItemConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, [config]))
    }
    if (value) {
        ContentModifierHelper.contentModifierMenuItem(receiver.getPeer().peer.ptr, value!, menuItemBuilder)
    }
}

// @memo
export function hookSliderContentModifier(
    receiver: ArkSliderComponent, value?: ContentModifier<SliderConfiguration>) {
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const sliderBuilder = (parentNode: KPointer, config: SliderConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, [config]))
    }
    if (value) {
        ContentModifierHelper.contentModifierSlider(receiver.getPeer().peer.ptr, value!, sliderBuilder)
    }
}

// @memo
export function hookTextClockContentModifier(
    receiver: ArkTextClockComponent, value?: ContentModifier<TextClockConfiguration>) {
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const textClockBuilder = (parentNode: KPointer, config: TextClockConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, [config]))
    }
    if (value) {
        ContentModifierHelper.contentModifierTextClock(receiver.getPeer().peer.ptr, value!, textClockBuilder)
    }
}

// @memo
export function hookTextTimerContentModifier(
    receiver: ArkTextTimerComponent, value?: ContentModifier<TextTimerConfiguration>) {
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const textTimerBuilder = (parentNode: KPointer, config: TextTimerConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, [config]))
    }
    if (value) {
        ContentModifierHelper.contentModifierTextTimer(receiver.getPeer().peer.ptr, value!, textTimerBuilder)
    }
}

// @memo
export function hookToggleContentModifier(
    receiver: ArkToggleComponent, value?: ContentModifier<ToggleConfiguration>) {
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const toggleBuilder = (parentNode: KPointer, config: ToggleConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, [config]))
    }
    if (value) {
        ContentModifierHelper.contentModifierToggle(receiver.getPeer().peer.ptr, value!, toggleBuilder)
    }
}