import { ArkRadioComponent, RadioConfiguration } from "../component/radio";
import { ContentModifierHelper } from "../component/arkui-contentmodifier"
import { ContentModifier, CustomBuilderT } from "../component/common";
import { KPointer, nullptr, toPeerPtr } from "@koalaui/interop";
import { UIContextUtil } from "arkui/handwritten/UIContextUtil"
import { BuilderNode } from "../BuilderNode"
import { FrameNode } from '../FrameNode'
import { int32 } from "@koalaui/common"
import { WrappedBuilder } from '../component/builder'

export class HookContentModifier {
    static radioNodeMap_: Map<int32, BuilderNode<RadioConfiguration>> = new Map<int32, BuilderNode<RadioConfiguration>>();
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

