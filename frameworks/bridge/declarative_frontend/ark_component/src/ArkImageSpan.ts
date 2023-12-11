
/// <reference path="./import.ts" />
class ImageSpanObjectFitModifier extends ModifierWithKey<number> {
    constructor(value: number) {
      super(value);
    }
    static identity: Symbol = Symbol('imageSpanObjectFit');
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().imageSpan.resetObjectFit(node);
        } else {
            GetUINativeModule().imageSpan.setObjectFit(node, this.value!);
        }
    }
    checkObjectDiff(): boolean {
        return this.stageValue !== this.value;
    }
}
class ImageSpanVerticalAlignModifier extends ModifierWithKey<number> {
    constructor(value: number) {
      super(value);
    }
    static identity: Symbol = Symbol('imageSpanVerticalAlign');
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().imageSpan.resetVerticalAlign(node);
        } else {
            GetUINativeModule().imageSpan.setVerticalAlign(node, this.value!);
        }
    }
    checkObjectDiff(): boolean {
        return this.stageValue !== this.value;
    }
}
class ArkImageSpanComponent extends ArkComponent implements ImageSpanAttribute {
    constructor(nativePtr: KNode) {
      super(nativePtr);
    }
    objectFit(value: ImageFit): ImageSpanAttribute {
        modifierWithKey(this._modifiersWithKeys, ImageSpanObjectFitModifier.identity, ImageSpanObjectFitModifier, value);
        return this;
    }
    verticalAlign(value: ImageSpanAlignment): ImageSpanAttribute {
        modifierWithKey(this._modifiersWithKeys, ImageSpanVerticalAlignModifier.identity, ImageSpanVerticalAlignModifier, value);
        return this;
    }
}
// @ts-ignore
globalThis.ImageSpan.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);

    let component = this.createOrGetNode(elmtId, () => {
        return new ArkImageSpanComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();

}
