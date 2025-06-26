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
// TODO: uncomment when ContentModifierHelper is integrated
//import { ContentModifierHelper } from "../generated"
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
    let wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    let buttonBuilder = (parentNode: KPointer, config: ButtonConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, [config]))
    }
    if (value) {
        // TODO: uncomment when ContentModifierHelper is integrated
        //ContentModifierHelper.contentModifierButton(receiver.getPeer().peer.ptr, value!, buttonBuilder)
    }
}

// @memo
export function hookCheckBoxContentModifier(
    receiver: ArkCheckboxComponent, value?: ContentModifier<CheckBoxConfiguration>) {
    let wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    let checkboxBuilder = (parentNode: KPointer, config: CheckBoxConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, [config]))
    }
    if (value) {
        // TODO: uncomment when ContentModifierHelper is integrated
        //ContentModifierHelper.contentModifierCheckBox(receiver.getPeer().peer.ptr, value!, checkboxBuilder)
    }
}

// @memo
export function hookDataPanelContentModifier(
    receiver: ArkDataPanelComponent, value?: ContentModifier<DataPanelConfiguration>) {
    let wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    let dataPanelBuilder = (parentNode: KPointer, config: DataPanelConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, [config]))
    }
    if (value) {
        // TODO: uncomment when ContentModifierHelper is integrated
        //ContentModifierHelper.contentModifierDataPanel(receiver.getPeer().peer.ptr, value!, dataPanelBuilder)
    }
}

// @memo
export function hookGaugeContentModifier(
    receiver: ArkGaugeComponent, value?: ContentModifier<GaugeConfiguration>) {
    let wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    let gaugeBuilder = (parentNode: KPointer, config: GaugeConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, [config]))
    }
    if (value) {
        // TODO: uncomment when ContentModifierHelper is integrated
        //ContentModifierHelper.contentModifierGauge(receiver.getPeer().peer.ptr, value!, gaugeBuilder)
    }
}

// @memo
export function hookLoadingProgressContentModifier(
    receiver: ArkLoadingProgressComponent, value?: ContentModifier<LoadingProgressConfiguration>) {
    let wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    let loadingProgressBuilder = (parentNode: KPointer, config: LoadingProgressConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, [config]))
    }
    if (value) {
        // TODO: uncomment when ContentModifierHelper is integrated
        //ContentModifierHelper.contentModifierLoadingProgress(receiver.getPeer().peer.ptr, value!, loadingProgressBuilder)
    }
}

// @memo
export function hookProgressContentModifier(
    receiver: ArkProgressComponent, value?: ContentModifier<ProgressConfiguration>) {
    let wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    let progressBuilder = (parentNode: KPointer, config: ProgressConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, [config]))
    }
    if (value) {
        // TODO: uncomment when ContentModifierHelper is integrated
        //ContentModifierHelper.contentModifierProgress(receiver.getPeer().peer.ptr, value!, progressBuilder)
    }
}

// @memo
export function hookRadioContentModifier(
    receiver: ArkRadioComponent, value?: ContentModifier<RadioConfiguration>) {
    let wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    let radioBuilder = (parentNode: KPointer, config: RadioConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, [config]))
    }
    if (value) {
        // TODO: uncomment when ContentModifierHelper is integrated
        //ContentModifierHelper.contentModifierRadio(receiver.getPeer().peer.ptr, value!, radioBuilder)
    }
}

// @memo
export function hookRatingContentModifier(
    receiver: ArkRatingComponent, value?: ContentModifier<RatingConfiguration>) {
    let wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    let ratingBuilder = (parentNode: KPointer, config: RatingConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, [config]))
    }
    if (value) {
        // TODO: uncomment when ContentModifierHelper is integrated
        //ContentModifierHelper.contentModifierRating(receiver.getPeer().peer.ptr, value!, ratingBuilder)
    }
}

// @memo
export function hookSelectContentModifier(
    receiver: ArkSelectComponent, value?: ContentModifier<MenuItemConfiguration>) {
    let wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    let menuItemBuilder = (parentNode: KPointer, config: MenuItemConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, [config]))
    }
    if (value) {
        // TODO: uncomment when ContentModifierHelper is integrated
        //ContentModifierHelper.contentModifierMenuItem(receiver.getPeer().peer.ptr, value!, menuItemBuilder)
    }
}

// @memo
export function hookSliderContentModifier(
    receiver: ArkSliderComponent, value?: ContentModifier<SliderConfiguration>) {
    let wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    let sliderBuilder = (parentNode: KPointer, config: SliderConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, [config]))
    }
    if (value) {
        // TODO: uncomment when ContentModifierHelper is integrated
        //ContentModifierHelper.contentModifierSlider(receiver.getPeer().peer.ptr, value!, sliderBuilder)
    }
}

// @memo
export function hookTextClockContentModifier(
    receiver: ArkTextClockComponent, value?: ContentModifier<TextClockConfiguration>) {
    let wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    let textClockBuilder = (parentNode: KPointer, config: TextClockConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, [config]))
    }
    if (value) {
        // TODO: uncomment when ContentModifierHelper is integrated
        //ContentModifierHelper.contentModifierTextClock(receiver.getPeer().peer.ptr, value!, textClockBuilder)
    }
}

// @memo
export function hookTextTimerContentModifier(
    receiver: ArkTextTimerComponent, value?: ContentModifier<TextTimerConfiguration>) {
    let wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    let textTimerBuilder = (parentNode: KPointer, config: TextTimerConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, [config]))
    }
    if (value) {
        // TODO: uncomment when ContentModifierHelper is integrated
        //ContentModifierHelper.contentModifierTextTimer(receiver.getPeer().peer.ptr, value!, textTimerBuilder)
    }
}

// @memo
export function hookToggleContentModifier(
    receiver: ArkToggleComponent, value?: ContentModifier<ToggleConfiguration>) {
    let wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    let toggleBuilder = (parentNode: KPointer, config: ToggleConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, [config]))
    }
    if (value) {
        // TODO: uncomment when ContentModifierHelper is integrated
        //ContentModifierHelper.contentModifierToggle(receiver.getPeer().peer.ptr, value!, toggleBuilder)
    }
}