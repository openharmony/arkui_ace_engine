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
import { ContentModifierHelper } from "#generated"
import { ContentModifier } from "#generated"
import { KPointer, pointer } from "@koalaui/interop";
import { ArkButtonComponent, ArkButtonPeer, ButtonConfiguration } from '#generated'
import { ArkCheckboxComponent, ArkCheckboxPeer, CheckBoxConfiguration } from '#generated'
import { ArkDataPanelComponent, ArkDataPanelPeer, DataPanelConfiguration } from "#generated"
import { ArkGaugeComponent, ArkGaugePeer, GaugeConfiguration } from "#generated"
import { ArkLoadingProgressComponent, ArkLoadingProgressPeer, LoadingProgressConfiguration } from "#generated"
import { ArkProgressComponent, ArkProgressPeer, ProgressConfiguration } from "#generated"
import { ArkRadioComponent, ArkRadioPeer, RadioConfiguration } from '#generated'
import { ArkRatingComponent, ArkRatingPeer, RatingConfiguration } from '#generated'
import { ArkSelectComponent, ArkSelectPeer, MenuItemConfiguration } from '#generated'
import { ArkSliderComponent, ArkSliderPeer, SliderConfiguration } from '#generated'
import { ArkTextClockComponent, ArkTextClockPeer, TextClockConfiguration } from "#generated"
import { ArkTextTimerComponent, ArkTextTimerPeer, TextTimerConfiguration } from "#generated"
import { ArkToggleComponent, ArkTogglePeer, ToggleConfiguration } from '#generated'
import { ArkCheckboxGroupComponent, CheckBoxGroupConfiguration } from "#generated"
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
    receiver: ArkButtonComponent | ArkButtonPeer, value?: ContentModifier<ButtonConfiguration>) {
    let ptr: pointer;
    if (receiver instanceof ArkButtonComponent) {
        ptr = receiver.getPeer().peer.ptr
    } else if (receiver instanceof ArkButtonPeer) {
        ptr = receiver.peer.ptr
    } else {
        throw new Error('hookButtonContentModifier unsupported receiver type');
    }
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
    receiver: ArkCheckboxComponent | ArkCheckboxPeer, value?: ContentModifier<CheckBoxConfiguration>) {
    let ptr: pointer;
    if (receiver instanceof ArkCheckboxComponent) {
        ptr = receiver.getPeer().peer.ptr
    } else if (receiver instanceof ArkCheckboxPeer) {
        ptr = receiver.peer.ptr
    } else {
        throw new Error('hookCheckBoxContentModifier unsupported receiver type');
    }
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
    receiver: ArkDataPanelComponent | ArkDataPanelPeer, value?: ContentModifier<DataPanelConfiguration>) {
    let ptr: pointer;
    if (receiver instanceof ArkDataPanelComponent) {
        ptr = receiver.getPeer().peer.ptr
    } else if (receiver instanceof ArkDataPanelPeer) {
        ptr = receiver.peer.ptr
    } else {
        throw new Error("hookDataPanelContentModifier unsupported receiver type");
    }
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
    receiver: ArkGaugeComponent | ArkGaugePeer, value?: ContentModifier<GaugeConfiguration>) {
    let ptr: pointer;
    if (receiver instanceof ArkGaugeComponent) {
        ptr = receiver.getPeer().peer.ptr
    } else if (receiver instanceof ArkGaugePeer) {
        ptr = receiver.peer.ptr
    } else {
        throw new Error("hookGaugeContentModifier unsupported receiver type");
    }
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
    receiver: ArkLoadingProgressComponent | ArkLoadingProgressPeer, value?: ContentModifier<LoadingProgressConfiguration>) {
    let ptr: pointer;
    if (receiver instanceof ArkLoadingProgressComponent) {
        ptr = receiver.getPeer().peer.ptr
    } else if (receiver instanceof ArkLoadingProgressPeer) {
        ptr = receiver.peer.ptr
    } else {
        throw new Error("hookLoadingProgressContentModifier unsupported receiver type");
    }
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
    receiver: ArkProgressComponent | ArkProgressPeer, value?: ContentModifier<ProgressConfiguration>) {
    let ptr: pointer;
    if (receiver instanceof ArkProgressComponent) {
        ptr = receiver.getPeer().peer.ptr
    } else if (receiver instanceof ArkProgressPeer) {
        ptr = receiver.peer.ptr
    } else {
        throw new Error("hookProgressContentModifier unsupported receiver type");
    }
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
    receiver: ArkRadioComponent | ArkRadioPeer, value?: ContentModifier<RadioConfiguration>) {
    let ptr: pointer;
    if (receiver instanceof ArkRadioComponent) {
        ptr = receiver.getPeer().peer.ptr
    } else if (receiver instanceof ArkRadioPeer) {
        ptr = receiver.peer.ptr
    } else {
        throw new Error('hookRadioContentModifier unsupported receiver type');
    }
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
    receiver: ArkRatingComponent | ArkRatingPeer, value?: ContentModifier<RatingConfiguration>) {
    let ptr: pointer;
    if (receiver instanceof ArkRatingComponent) {
        ptr = receiver.getPeer().peer.ptr
    } else if (receiver instanceof ArkRatingPeer) {
        ptr = receiver.peer.ptr
    } else {
        throw new Error('hookRatingContentModifier unsupported receiver type');
    }
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
    receiver: ArkSelectComponent | ArkSelectPeer, value?: ContentModifier<MenuItemConfiguration>) {
    let ptr: pointer;
    if (receiver instanceof ArkSelectComponent) {
        ptr = receiver.getPeer().peer.ptr
    } else if (receiver instanceof ArkSelectPeer) {
        ptr = receiver.peer.ptr
    } else {
        throw new Error('hookSelectContentModifier unsupported receiver type');
    }
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
    receiver: ArkSliderComponent | ArkSliderPeer, value?: ContentModifier<SliderConfiguration>) {
    let ptr: pointer;
    if (receiver instanceof ArkSliderComponent) {
        ptr = receiver.getPeer().peer.ptr
    } else if (receiver instanceof ArkSliderPeer) {
        ptr = receiver.peer.ptr
    } else {
        throw new Error('hookSliderContentModifier unsupported receiver type');
    }
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
    receiver: ArkTextClockComponent | ArkTextClockPeer, value?: ContentModifier<TextClockConfiguration>) {
    let ptr: pointer;
    if (receiver instanceof ArkTextClockComponent) {
        ptr = receiver.getPeer().peer.ptr
    } else if (receiver instanceof ArkTextClockPeer) {
        ptr = receiver.peer.ptr
    } else {
        throw new Error("hookTextClockContentModifier unsupported receiver type");
    }
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
    receiver: ArkTextTimerComponent | ArkTextTimerPeer, value?: ContentModifier<TextTimerConfiguration>) {
    let ptr: pointer;
    if (receiver instanceof ArkTextTimerComponent) {
        ptr = receiver.getPeer().peer.ptr
    } else if (receiver instanceof ArkTextTimerPeer) {
        ptr = receiver.peer.ptr
    } else {
        throw new Error("hookTextTimerContentModifier unsupported receiver type");
    }
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
    receiver: ArkToggleComponent | ArkTogglePeer, value?: ContentModifier<ToggleConfiguration>) {
    let ptr: pointer;
    if (receiver instanceof ArkToggleComponent) {
        ptr = receiver.getPeer().peer.ptr
    } else if (receiver instanceof ArkTogglePeer) {
        ptr = receiver.peer.ptr
    } else {
        throw new Error('hookToggleContentModifier unsupported receiver type');
    }
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

export function hookCheckBoxGroupContentModifier(
    receiver: ArkCheckboxGroupComponent, value?: ContentModifier<CheckBoxGroupConfiguration>) {
    const ptr = receiver.getPeer().peer.ptr
    if (!value) {
        ContentModifierHelper.resetContentModifierCheckBoxGroup(ptr)
        return
    }
    const wrappedBuilder = value?.applyContent()
    if (!wrappedBuilder) {
        return
    }
    const checkboxGroupBuilder = (parentNode: KPointer, config: CheckBoxGroupConfiguration): KPointer => {
        return CallbackTransformer.transformToPeerFromCustomBuilder(
            memoWrapper(wrappedBuilder!.builder, config))
    }
    if (value) {
        ContentModifierHelper.contentModifierCheckBoxGroup(ptr, value!, checkboxGroupBuilder)
    }
}
