
/// <reference path="./import.ts" />
class ImageSpanObjectFitModifier extends Modifier<number> {
    static identity: Symbol = Symbol('imageSpanObjectFit');
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().imageSpan.resetObjectFit(node);
        } else {
            GetUINativeModule().imageSpan.setObjectFit(node, this.value!);
        }
    }
}
class ImageSpanVerticalAlignModifier extends Modifier<number> {
    static identity: Symbol = Symbol('imageSpanVerticalAlign');
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().imageSpan.resetVerticalAlign(node);
        } else {
            GetUINativeModule().imageSpan.setVerticalAlign(node, this.value!);
        }
    }
}
class ArkImageSpanComponent extends ArkComponent implements ImageSpanAttribute {
    objectFit(value: ImageFit): ImageSpanAttribute {
        if (value) {
            modifier(this._modifiers, ImageSpanObjectFitModifier, value);
        } else {
            modifier(this._modifiers, ImageSpanObjectFitModifier, undefined);
        }
        return this;
    }
    verticalAlign(value: ImageSpanAlignment): ImageSpanAttribute {
        if (value) {
            modifier(this._modifiers, ImageSpanVerticalAlignModifier, value);
        } else {
            modifier(this._modifiers, ImageSpanVerticalAlignModifier, undefined);
        }
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