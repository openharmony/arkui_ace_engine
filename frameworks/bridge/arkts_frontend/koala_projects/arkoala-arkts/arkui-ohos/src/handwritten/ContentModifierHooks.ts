import { ArkRadioComponent, RadioConfiguration } from "../component/radio";
import { ContentModifierHelper } from "../component/arkui-contentmodifier"
import { ContentModifier, CustomBuilderT } from "../component/common";
import { KPointer, nullptr, toPeerPtr } from "@koalaui/interop";
import { UIContextUtil } from "arkui/handwritten/UIContextUtil"
import { BuilderNode } from "../BuilderNode"
import { FrameNode } from '../FrameNode'
import { int32 } from "@koalaui/common"
import { WrappedBuilder } from '../component/builder'
import { ArkButtonComponent, ButtonConfiguration } from "../component/button";
import { ArkCheckboxComponent, CheckBoxConfiguration } from "../component/checkbox";
import { ArkToggleComponent, ToggleConfiguration } from "../component/toggle";
import { ArkRatingComponent, RatingConfiguration } from "../component/rating";
import { ArkSliderComponent, SliderConfiguration } from "../component/slider";

export class HookContentModifier {
    static radioNodeMap_: Map<int32, BuilderNode<RadioConfiguration>> = new Map<int32, BuilderNode<RadioConfiguration>>();
    static buttonNodeMap_: Map<int32, BuilderNode<ButtonConfiguration>> = new Map<int32, BuilderNode<ButtonConfiguration>>();
    static checkboxNodeMap_: Map<int32, BuilderNode<CheckBoxConfiguration>> = new Map<int32, BuilderNode<CheckBoxConfiguration>>();
    static toggleNodeMap_: Map<int32, BuilderNode<ToggleConfiguration>> = new Map<int32, BuilderNode<ToggleConfiguration>>();
    static ratingNodeMap_: Map<int32, BuilderNode<RatingConfiguration>> = new Map<int32, BuilderNode<RatingConfiguration>>();
    static sliderNodeMap_: Map<int32, BuilderNode<SliderConfiguration>> = new Map<int32, BuilderNode<SliderConfiguration>>();
    //Radio
    static getRadioBuilderNode(peerId: int32, builder: WrappedBuilder<CustomBuilderT<RadioConfiguration>>, config: RadioConfiguration): BuilderNode<RadioConfiguration> {
        if (HookContentModifier.radioNodeMap_.has(peerId)) {
            let builderNode = HookContentModifier.radioNodeMap_.get(peerId)!
            builderNode.update(config)
            return builderNode
        }
        let uiContext = UIContextUtil.getOrCreateCurrentUIContext()
        let builderNode = new BuilderNode<RadioConfiguration>(uiContext)
        HookContentModifier.radioNodeMap_.set(peerId, builderNode)
        builderNode!.build(builder, config)
        return builderNode
    }

    static removeRadioBuilderNode(peerId: int32): void {
        if (HookContentModifier.radioNodeMap_.has(peerId)) {
            let builderNode = HookContentModifier.radioNodeMap_.get(peerId)!
            HookContentModifier.radioNodeMap_.delete(peerId)
            builderNode.dispose()
        }
    }
    //Button
    static getButtonBuilderNode(peerId: int32, builder: WrappedBuilder<CustomBuilderT<ButtonConfiguration>>, config: ButtonConfiguration): BuilderNode<ButtonConfiguration> {
        if (HookContentModifier.buttonNodeMap_.has(peerId)) {
            let builderNode = HookContentModifier.buttonNodeMap_.get(peerId)!
            builderNode.update(config)
            return builderNode
        }
        let uiContext = UIContextUtil.getOrCreateCurrentUIContext()
        let builderNode = new BuilderNode<ButtonConfiguration>(uiContext)
        HookContentModifier.buttonNodeMap_.set(peerId, builderNode)
        builderNode!.build(builder, config)
        return builderNode
    }

    static removeButtonBuilderNode(peerId: int32): void {
        if (HookContentModifier.buttonNodeMap_.has(peerId)) {
            let builderNode = HookContentModifier.buttonNodeMap_.get(peerId)!
            HookContentModifier.buttonNodeMap_.delete(peerId)
            builderNode.dispose()
        }
    }
    //Checkbox
    static getCheckboxBuilderNode(peerId: int32, builder: WrappedBuilder<CustomBuilderT<CheckBoxConfiguration>>, config: CheckBoxConfiguration): BuilderNode<CheckBoxConfiguration> {
        if (HookContentModifier.checkboxNodeMap_.has(peerId)) {
            let builderNode = HookContentModifier.checkboxNodeMap_.get(peerId)!
            builderNode.update(config)
            return builderNode
        }
        let uiContext = UIContextUtil.getOrCreateCurrentUIContext()
        let builderNode = new BuilderNode<CheckBoxConfiguration>(uiContext)
        HookContentModifier.checkboxNodeMap_.set(peerId, builderNode)
        builderNode!.build(builder, config)
        return builderNode
    }

    static removeCheckboxBuilderNode(peerId: int32): void {
        if (HookContentModifier.checkboxNodeMap_.has(peerId)) {
            let builderNode = HookContentModifier.checkboxNodeMap_.get(peerId)!
            HookContentModifier.checkboxNodeMap_.delete(peerId)
            builderNode.dispose()
        }
    }
    //Toggle
    static getToggleBuilderNode(peerId: int32, builder: WrappedBuilder<CustomBuilderT<ToggleConfiguration>>, config: ToggleConfiguration): BuilderNode<ToggleConfiguration> {
        if (HookContentModifier.toggleNodeMap_.has(peerId)) {
            let builderNode = HookContentModifier.toggleNodeMap_.get(peerId)!
            builderNode.update(config)
            return builderNode
        }
        let uiContext = UIContextUtil.getOrCreateCurrentUIContext()
        let builderNode = new BuilderNode<ToggleConfiguration>(uiContext)
        HookContentModifier.toggleNodeMap_.set(peerId, builderNode)
        builderNode!.build(builder, config)
        return builderNode
    }

    static removeToggleBuilderNode(peerId: int32): void {
        if (HookContentModifier.toggleNodeMap_.has(peerId)) {
            let builderNode = HookContentModifier.toggleNodeMap_.get(peerId)!
            HookContentModifier.toggleNodeMap_.delete(peerId)
            builderNode.dispose()
        }
    }
    //Rating
    static getRatingBuilderNode(peerId: int32, builder: WrappedBuilder<CustomBuilderT<RatingConfiguration>>, config: RatingConfiguration): BuilderNode<RatingConfiguration> {
        if (HookContentModifier.ratingNodeMap_.has(peerId)) {
            let builderNode = HookContentModifier.ratingNodeMap_.get(peerId)!
            builderNode.update(config)
            return builderNode
        }
        let uiContext = UIContextUtil.getOrCreateCurrentUIContext()
        let builderNode = new BuilderNode<RatingConfiguration>(uiContext)
        HookContentModifier.ratingNodeMap_.set(peerId, builderNode)
        builderNode!.build(builder, config)
        return builderNode
    }

    static removeRatingBuilderNode(peerId: int32): void {
        if (HookContentModifier.ratingNodeMap_.has(peerId)) {
            let builderNode = HookContentModifier.ratingNodeMap_.get(peerId)!
            HookContentModifier.ratingNodeMap_.delete(peerId)
            builderNode.dispose()
        }
    }
    //Slider
    static getSliderBuilderNode(peerId: int32, builder: WrappedBuilder<CustomBuilderT<SliderConfiguration>>, config: SliderConfiguration): BuilderNode<SliderConfiguration> {
        if (HookContentModifier.sliderNodeMap_.has(peerId)) {
            let builderNode = HookContentModifier.sliderNodeMap_.get(peerId)!
            builderNode.update(config)
            return builderNode
        }
        let uiContext = UIContextUtil.getOrCreateCurrentUIContext()
        let builderNode = new BuilderNode<SliderConfiguration>(uiContext)
        HookContentModifier.sliderNodeMap_.set(peerId, builderNode)
        builderNode!.build(builder, config)
        return builderNode
    }

    static removeSliderBuilderNode(peerId: int32): void {
        if (HookContentModifier.sliderNodeMap_.has(peerId)) {
            let builderNode = HookContentModifier.sliderNodeMap_.get(peerId)!
            HookContentModifier.sliderNodeMap_.delete(peerId)
            builderNode.dispose()
        }
    }
}

export function hookRadioContentModifier(
    receiver: ArkRadioComponent, value: ContentModifier<RadioConfiguration> | undefined): void {
    let peerId = receiver.getPeer().getId()
    if (!value) {
        HookContentModifier.removeRadioBuilderNode(peerId);
        ContentModifierHelper.resetContentModifierRadio(receiver.getPeer().peer.ptr)
    }
    let wrappedBuilder = value!.applyContent()
    if (!wrappedBuilder) {
        return
    }
    let radioBuilder = (parentNode: KPointer, config: RadioConfiguration): KPointer => {
        config.contentModifier = value!
        let builderNode = HookContentModifier.getRadioBuilderNode(peerId, wrappedBuilder!, config)
        let returnNode = builderNode!.getFrameNode()
        if (returnNode) {
            return toPeerPtr(returnNode as FrameNode)
        }
        return nullptr
    }
    ContentModifierHelper.contentModifierRadio(receiver.getPeer().peer.ptr, value!, radioBuilder)
}

export function hookButtonContentModifier(
    receiver: ArkButtonComponent, value: ContentModifier<ButtonConfiguration> | undefined): void {
    let peerId = receiver.getPeer().getId()
    if (!value) {
        HookContentModifier.removeButtonBuilderNode(peerId);
        ContentModifierHelper.resetContentModifierButton(receiver.getPeer().peer.ptr)
    }

    let wrappedBuilder = value!.applyContent()
    if (!wrappedBuilder) {
        return
    }
    let buttonBuilder = (parentNode: KPointer, config: ButtonConfiguration): KPointer => {
        config.contentModifier = value!
        let builderNode = HookContentModifier.getButtonBuilderNode(peerId, wrappedBuilder!, config)
        let returnNode = builderNode!.getFrameNode()
        if (returnNode) {
            return toPeerPtr(returnNode as FrameNode)
        }
        return nullptr
    }
    ContentModifierHelper.contentModifierButton(receiver.getPeer().peer.ptr, value!, buttonBuilder)
}

export function hookCheckboxContentModifier(
    receiver: ArkCheckboxComponent, value: ContentModifier<CheckBoxConfiguration> | undefined): void {
    let peerId = receiver.getPeer().getId()
    if (!value) {
        HookContentModifier.removeCheckboxBuilderNode(peerId);
        ContentModifierHelper.resetContentModifierCheckbox(receiver.getPeer().peer.ptr)
    }

    let wrappedBuilder = value!.applyContent()
    if (!wrappedBuilder) {
        return
    }
    let checkboxBuilder = (parentNode: KPointer, config: CheckBoxConfiguration): KPointer => {
        config.contentModifier = value!
        let builderNode = HookContentModifier.getCheckboxBuilderNode(peerId, wrappedBuilder!, config)
        let returnNode = builderNode!.getFrameNode()
        if (returnNode) {
            return toPeerPtr(returnNode as FrameNode)
        }
        return nullptr
    }
    ContentModifierHelper.contentModifierCheckbox(receiver.getPeer().peer.ptr, value!, checkboxBuilder)
}

export function hookToggleContentModifier(
    receiver: ArkToggleComponent, value: ContentModifier<ToggleConfiguration> | undefined): void {
    let peerId = receiver.getPeer().getId()
    if (!value) {
        HookContentModifier.removeRadioBuilderNode(peerId);
        ContentModifierHelper.resetContentModifierToggle(receiver.getPeer().peer.ptr)
    }

    let wrappedBuilder = value!.applyContent()
    if (!wrappedBuilder) {
        return
    }
    let toggleBuilder = (parentNode: KPointer, config: ToggleConfiguration): KPointer => {
        config.contentModifier = value!
        let builderNode = HookContentModifier.getToggleBuilderNode(peerId, wrappedBuilder!, config)
        let returnNode = builderNode!.getFrameNode()
        if (returnNode) {
            return toPeerPtr(returnNode as FrameNode)
        }
        return nullptr
    }
    ContentModifierHelper.contentModifierToggle(receiver.getPeer().peer.ptr, value!, toggleBuilder)
}

export function hookRatingContentModifier(
    receiver: ArkRatingComponent, value: ContentModifier<RatingConfiguration> | undefined): void {
    let peerId = receiver.getPeer().getId()
    if (!value) {
        HookContentModifier.removeRatingBuilderNode(peerId);
        ContentModifierHelper.resetContentModifierRating(receiver.getPeer().peer.ptr)
    }

    let wrappedBuilder = value!.applyContent()
    if (!wrappedBuilder) {
        return
    }
    let ratingBuilder = (parentNode: KPointer, config: RatingConfiguration): KPointer => {
        config.contentModifier = value!
        let builderNode = HookContentModifier.getRatingBuilderNode(peerId, wrappedBuilder!, config)
        let returnNode = builderNode!.getFrameNode()
        if (returnNode) {
            return toPeerPtr(returnNode as FrameNode)
        }
        return nullptr
    }
    ContentModifierHelper.contentModifierRating(receiver.getPeer().peer.ptr, value!, ratingBuilder)
}

export function hookSliderContentModifier(
    receiver: ArkSliderComponent, value: ContentModifier<SliderConfiguration> | undefined): void {
    let peerId = receiver.getPeer().getId()
    if (!value) {
        HookContentModifier.removeSliderBuilderNode(peerId);
        ContentModifierHelper.resetContentModifierSlider(receiver.getPeer().peer.ptr)
    }

    let wrappedBuilder = value!.applyContent()
    if (!wrappedBuilder) {
        return
    }
    let sliderBuilder = (parentNode: KPointer, config: SliderConfiguration): KPointer => {
        config.contentModifier = value!
        let builderNode = HookContentModifier.getSliderBuilderNode(peerId, wrappedBuilder!, config)
        let returnNode = builderNode!.getFrameNode()
        if (returnNode) {
            return toPeerPtr(returnNode as FrameNode)
        }
        return nullptr
    }
    ContentModifierHelper.contentModifierSlider(receiver.getPeer().peer.ptr, value!, sliderBuilder)
}
