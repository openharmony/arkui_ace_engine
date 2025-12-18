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

import { memo } from "arkui.stateManagement.runtime"
import { ContentModifierHelper } from "#generated"
import { ContentModifier } from "#generated"
import { KPointer } from "@koalaui/interop"
import { ArkButtonComponent, ArkButtonPeer, ButtonConfiguration} from "#generated"
import { ArkCheckboxComponent, ArkCheckboxPeer, CheckBoxConfiguration } from "#generated"
import { ArkDataPanelComponent, ArkDataPanelPeer, DataPanelConfiguration } from "#generated"
import { ArkGaugeComponent, ArkGaugePeer, GaugeConfiguration } from "#generated"
import { ArkLoadingProgressComponent, ArkLoadingProgressPeer, LoadingProgressConfiguration } from "#generated"
import { ArkProgressComponent, ArkProgressPeer, ProgressConfiguration } from "#generated"
import { ArkRadioComponent, ArkRadioPeer, RadioConfiguration } from "#generated"
import { ArkRatingComponent, ArkRatingPeer, RatingConfiguration } from "#generated"
import { ArkSelectComponent, ArkSelectPeer, MenuItemConfiguration } from "#generated"
import { ArkSliderComponent, ArkSliderPeer, SliderConfiguration } from "#generated"
import { ArkTextClockComponent, ArkTextClockPeer, TextClockConfiguration } from "#generated"
import { ArkTextTimerComponent, ArkTextTimerPeer, TextTimerConfiguration } from "#generated"
import { ArkToggleComponent, ArkTogglePeer, ToggleConfiguration } from "#generated"
import { CustomBuilder } from "#generated"
import { CallbackTransformer } from "../../CallbackTransformer"

function memoWrapper<Args>(
    @memo
    builder: ((args: Args) => void), args: Args
): CustomBuilder {
    @memo
    const wrapper = () => { builder(args) }
    return wrapper
}

export function hookButtonContentModifier(
    receiver: ArkButtonComponent, value?: ContentModifier<ButtonConfiguration>) {
    hookButtonContentModifier(receiver.getPeer(), value);
}

export function hookButtonContentModifier(
    peer: ArkButtonPeer, value?: ContentModifier<ButtonConfiguration>) {
    hookButtonContentModifier(peer.peer.ptr, value);
}

function hookButtonContentModifier(
    ptr: KPointer, value?: ContentModifier<ButtonConfiguration>) {
    if (!value) {
        ContentModifierHelper.resetContentModifierButton(ptr)
        return
    }
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const buttonBuilder = (parentNode: KPointer, config: ButtonConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, config))
    }
    if (value) {
        ContentModifierHelper.contentModifierButton(ptr, value!, buttonBuilder)
    }
}

export function hookCheckBoxContentModifier(
    receiver: ArkCheckboxComponent, value?: ContentModifier<CheckBoxConfiguration>) {
    hookCheckBoxContentModifier(receiver.getPeer(), value);
}

export function hookCheckBoxContentModifier(
    peer: ArkCheckboxPeer, value?: ContentModifier<CheckBoxConfiguration>) {
    hookCheckBoxContentModifier(peer.peer.ptr, value)
}

function hookCheckBoxContentModifier(
    ptr: KPointer, value?: ContentModifier<CheckBoxConfiguration>) {
    if (!value) {
        ContentModifierHelper.resetContentModifierCheckBox(ptr)
        return
    }
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const checkboxBuilder = (parentNode: KPointer, config: CheckBoxConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, config))
    }
    if (value) {
        ContentModifierHelper.contentModifierCheckBox(ptr, value!, checkboxBuilder)
    }
}

export function hookDataPanelContentModifier(
    receiver: ArkDataPanelComponent, value?: ContentModifier<DataPanelConfiguration>) {
    hookDataPanelContentModifier(receiver.getPeer(), value)
}

export function hookDataPanelContentModifier(
    peer: ArkDataPanelPeer, value?: ContentModifier<DataPanelConfiguration>) {
    hookDataPanelContentModifier(peer.peer.ptr, value)
}

function hookDataPanelContentModifier(
    ptr: KPointer, value?: ContentModifier<DataPanelConfiguration>) {
    if (!value) {
        ContentModifierHelper.resetContentModifierDataPanel(ptr)
        return
    }
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const dataPanelBuilder = (parentNode: KPointer, config: DataPanelConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, config))
    }
    if (value) {
        ContentModifierHelper.contentModifierDataPanel(ptr, value!, dataPanelBuilder)
    }
}

export function hookGaugeContentModifier(
    receiver: ArkGaugeComponent, value?: ContentModifier<GaugeConfiguration>) {
    hookGaugeContentModifier(receiver.getPeer(), value)
}

export function hookGaugeContentModifier(
    peer: ArkGaugePeer, value?: ContentModifier<GaugeConfiguration>) {
    hookGaugeContentModifier(peer.peer.ptr, value)
}

function hookGaugeContentModifier(
    ptr: KPointer, value?: ContentModifier<GaugeConfiguration>) {
    if (!value) {
        ContentModifierHelper.resetContentModifierGauge(ptr)
        return
    }
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const gaugeBuilder = (parentNode: KPointer, config: GaugeConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, config))
    }
    if (value) {
        ContentModifierHelper.contentModifierGauge(ptr, value!, gaugeBuilder)
    }
}

export function hookLoadingProgressContentModifier(
    receiver: ArkLoadingProgressComponent, value?: ContentModifier<LoadingProgressConfiguration>) {
    hookLoadingProgressContentModifier(receiver.getPeer(), value)
}

export function hookLoadingProgressContentModifier(
    peer: ArkLoadingProgressPeer, value?: ContentModifier<LoadingProgressConfiguration>) {
    hookLoadingProgressContentModifier(peer.peer.ptr, value)
}

function hookLoadingProgressContentModifier(
    ptr: KPointer, value?: ContentModifier<LoadingProgressConfiguration>) {
    if (!value) {
        ContentModifierHelper.resetContentModifierLoadingProgress(ptr)
        return
    }
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const loadingProgressBuilder = (parentNode: KPointer, config: LoadingProgressConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, config))
    }
    if (value) {
        ContentModifierHelper.contentModifierLoadingProgress(ptr, value!, loadingProgressBuilder)
    }
}

export function hookProgressContentModifier(
    receiver: ArkProgressComponent, value?: ContentModifier<ProgressConfiguration>) {
    hookProgressContentModifier(receiver.getPeer(), value)
}

export function hookProgressContentModifier(
    peer: ArkProgressPeer, value?: ContentModifier<ProgressConfiguration>) {
    hookProgressContentModifier(peer.peer.ptr, value)
}

function hookProgressContentModifier(
    ptr: KPointer, value?: ContentModifier<ProgressConfiguration>) {
    if (!value) {
        ContentModifierHelper.resetContentModifierProgress(ptr)
        return
    }
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const progressBuilder = (parentNode: KPointer, config: ProgressConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, config))
    }
    if (value) {
        ContentModifierHelper.contentModifierProgress(ptr, value!, progressBuilder)
    }
}

export function hookRadioContentModifier(
    receiver: ArkRadioComponent, value?: ContentModifier<RadioConfiguration>) {
    hookRadioContentModifier(receiver.getPeer(), value)
}

export function hookRadioContentModifier(
    peer: ArkRadioPeer, value?: ContentModifier<RadioConfiguration>) {
    hookRadioContentModifier(peer.peer.ptr, value)
}

function hookRadioContentModifier(
    ptr: KPointer, value?: ContentModifier<RadioConfiguration>) {
    if (!value) {
        ContentModifierHelper.resetContentModifierRadio(ptr)
        return
    }
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const radioBuilder = (parentNode: KPointer, config: RadioConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, config))
    }
    if (value) {
        ContentModifierHelper.contentModifierRadio(ptr, value!, radioBuilder)
    }
}

export function hookRatingContentModifier(
    receiver: ArkRatingComponent, value?: ContentModifier<RatingConfiguration>) {
    hookRatingContentModifier(receiver.getPeer(), value)
}

export function hookRatingContentModifier(
    peer: ArkRatingPeer, value?: ContentModifier<RatingConfiguration>) {
    hookRatingContentModifier(peer.peer.ptr, value)
}

function hookRatingContentModifier(
    ptr: KPointer, value?: ContentModifier<RatingConfiguration>) {
    if (!value) {
        ContentModifierHelper.resetContentModifierRating(ptr)
        return
    }
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const ratingBuilder = (parentNode: KPointer, config: RatingConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, config))
    }
    if (value) {
        ContentModifierHelper.contentModifierRating(ptr, value!, ratingBuilder)
    }
}

export function hookSelectContentModifier(
    receiver: ArkSelectComponent, value?: ContentModifier<MenuItemConfiguration>) {
    hookSelectContentModifier(receiver.getPeer(), value)
}

export function hookSelectContentModifier(
    peer: ArkSelectPeer, value?: ContentModifier<MenuItemConfiguration>) {
    hookSelectContentModifier(peer.peer.ptr, value)
}

function hookSelectContentModifier(
    ptr: KPointer, value?: ContentModifier<MenuItemConfiguration>) {
    if (!value) {
        ContentModifierHelper.resetContentModifierMenuItem(ptr)
        return
    }
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const menuItemBuilder = (parentNode: KPointer, config: MenuItemConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, config))
    }
    if (value) {
        ContentModifierHelper.contentModifierMenuItem(ptr, value!, menuItemBuilder)
    }
}

export function hookSliderContentModifier(
    receiver: ArkSliderComponent, value?: ContentModifier<SliderConfiguration>) {
    hookSliderContentModifier(receiver.getPeer(), value)
}

export function hookSliderContentModifier(
    peer: ArkSliderPeer, value?: ContentModifier<SliderConfiguration>) {
    hookSliderContentModifier(peer.peer.ptr, value)
}

function hookSliderContentModifier(
    ptr: KPointer, value?: ContentModifier<SliderConfiguration>) {
    if (!value) {
        ContentModifierHelper.resetContentModifierSlider(ptr)
        return
    }
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const sliderBuilder = (parentNode: KPointer, config: SliderConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, config))
    }
    if (value) {
        ContentModifierHelper.contentModifierSlider(ptr, value!, sliderBuilder)
    }
}

export function hookTextClockContentModifier(
    receiver: ArkTextClockComponent, value?: ContentModifier<TextClockConfiguration>) {
    hookTextClockContentModifier(receiver.getPeer(), value)
}

export function hookTextClockContentModifier(
    peer: ArkTextClockPeer, value?: ContentModifier<TextClockConfiguration>) {
    hookTextClockContentModifier(peer.peer.ptr, value)
}

function hookTextClockContentModifier(
    ptr: KPointer, value?: ContentModifier<TextClockConfiguration>) {
    if (!value) {
        ContentModifierHelper.resetContentModifierTextClock(ptr)
        return
    }
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const textClockBuilder = (parentNode: KPointer, config: TextClockConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, config))
    }
    if (value) {
        ContentModifierHelper.contentModifierTextClock(ptr, value!, textClockBuilder)
    }
}

export function hookTextTimerContentModifier(
    receiver: ArkTextTimerComponent, value?: ContentModifier<TextTimerConfiguration>) {
    hookTextTimerContentModifier(receiver.getPeer(), value)
}

export function hookTextTimerContentModifier(
    peer: ArkTextTimerPeer, value?: ContentModifier<TextTimerConfiguration>) {
    hookTextTimerContentModifier(peer.peer.ptr, value)
}

function hookTextTimerContentModifier(
    ptr: KPointer, value?: ContentModifier<TextTimerConfiguration>) {
    if (!value) {
        ContentModifierHelper.resetContentModifierTextTimer(ptr)
        return
    }
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const textTimerBuilder = (parentNode: KPointer, config: TextTimerConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, config))
    }
    if (value) {
        ContentModifierHelper.contentModifierTextTimer(ptr, value!, textTimerBuilder)
    }
}

export function hookToggleContentModifier(
    receiver: ArkToggleComponent, value?: ContentModifier<ToggleConfiguration>) {
    hookToggleContentModifier(receiver.getPeer(), value)
}

export function hookToggleContentModifier(
    peer: ArkTogglePeer, value?: ContentModifier<ToggleConfiguration>) {
    hookToggleContentModifier(peer.peer.ptr, value)
}

export function hookToggleContentModifier(
    ptr: KPointer, value?: ContentModifier<ToggleConfiguration>) {
    if (!value) {
        ContentModifierHelper.resetContentModifierToggle(ptr)
        return
    }
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const toggleBuilder = (parentNode: KPointer, config: ToggleConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, config))
    }
    if (value) {
        ContentModifierHelper.contentModifierToggle(ptr, value!, toggleBuilder)
    }
}