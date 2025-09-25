import { KPointer } from "@koalaui/interop";
import { applyUIAttributes } from "./hooks/modifiers/ArkCommonModifier";
import { ArkSymbolGlyphPeer, SymbolGlyphModifier } from "#generated";
import { PeerNode } from "./PeerNode";

export function applySymbolGlyphModifierToNode(modifier: SymbolGlyphModifier, nodePtr: KPointer): void {
    const peerId = PeerNode.nextId()
    const node = new ArkSymbolGlyphPeer(nodePtr, peerId, "SymbolGlyph")
    const node_casted = node as PeerNode
    let currentState = node_casted.getStateStyleMutable()
    if (currentState === undefined) {
        currentState = node_casted.getOrCreateStateStyleMutable()!
    }
    applyUIAttributes(modifier, modifier, currentState.value)
    modifier.applyModifierPatch(node_casted)
}