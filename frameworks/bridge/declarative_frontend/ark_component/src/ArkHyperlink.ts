/// <reference path='./import.ts' />

class ArkHyperlinkComponent extends ArkComponent implements HyperlinkAttribute {
  color(value: Color | number | string | Resource): this {
    if (!!value) {
      let color = new ArkBarBackgroundColor();
      color.value = value;
      modifier(this._modifiers, HyperlinkColorModifier, color);
    } else {
      modifier(this._modifiers, HyperlinkColorModifier, undefined);
    }
    return this;
  }
}

class HyperlinkColorModifier extends Modifier<ArkBarBackgroundColor> {
  static identity: Symbol = Symbol('hyperlinkColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().hyperlink.resetColor(node);
    } else {
      GetUINativeModule().hyperlink.setColor(node, this.value!);
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
