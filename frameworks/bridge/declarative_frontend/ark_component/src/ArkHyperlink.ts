/// <reference path='./import.ts' />

class ArkHyperlinkComponent extends ArkComponent implements HyperlinkAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  color(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, HyperlinkColorModifier.identity, HyperlinkColorModifier, value);
    return this;
  }
}

class HyperlinkColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('hyperlinkColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().hyperlink.resetColor(node);
    } else {
      GetUINativeModule().hyperlink.setColor(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}

// @ts-ignore
globalThis.Hyperlink.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkHyperlinkComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
