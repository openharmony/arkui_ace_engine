import { KPointer } from "@koalaui/interop";
import { applyUIAttributes } from "./hooks/modifiers/ArkCommonModifier";
import { ArkSymbolGlyphPeer, SymbolGlyphModifier, ArkSymbolGlyphComponent, TextModifier, ArkTextPeer, ArkTextComponent,
    ImageModifier, ArkImagePeer } from "#generated";
import { PeerNode } from "./PeerNode";
import { hookSymbolGlyphAttributeModifier, hookTextAttributeModifier } from "#handwritten"

export function applySymbolGlyphModifierToNode(modifier: SymbolGlyphModifier, nodePtr: KPointer): void {
    let receiver = new ArkSymbolGlyphComponent()
    const peerId = PeerNode.nextId()
    const node = new ArkSymbolGlyphPeer(nodePtr, peerId, "SymbolGlyph")
    receiver.setPeer(node)
    hookSymbolGlyphAttributeModifier(receiver, modifier)
}

export function applyTextModifierToNode(modifier: TextModifier, nodePtr: KPointer): void {
    let receiver = new ArkTextComponent()
    const peerId = PeerNode.nextId()
    const node = new ArkTextPeer(nodePtr, peerId, "Text")
    receiver.setPeer(node)
    hookTextAttributeModifier(receiver, modifier)
}

export function applyImageModifierToNode(modifier: ImageModifier, nodePtr: KPointer): void {
    const peerId = PeerNode.nextId()
    const node = new ArkImagePeer(nodePtr, peerId, "Image")
    const node_casted = node as PeerNode
    let currentState = node_casted.getStateStyleMutable()
    if (currentState === undefined) {
        currentState = node_casted.getOrCreateStateStyleMutable()!
    }
    const imageModifier = new ImageModifier()
    imageModifier.mergeModifier(modifier)
    applyUIAttributes(imageModifier, imageModifier, currentState.value)
    imageModifier.applyModifierPatch(node_casted)
}