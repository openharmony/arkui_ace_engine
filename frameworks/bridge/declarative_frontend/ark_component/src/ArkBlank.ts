/// <reference path="import.ts" />

class BlankColorModifier extends Modifier<number | undefined> {
  static identity: Symbol = Symbol('blankColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().blank.resetColor(node);
    } else {
      GetUINativeModule().blank.setColor(node, this.value!);
    }
  }
}

class ArkBlankComponent extends ArkComponent implements CommonMethod<BlankAttribute> {
  color(value: ResourceColor): BlankAttribute {
    let arkColor = new ArkColor();
    if (arkColor.parseColorValue(value)) {
      modifier(this._modifiers, BlankColorModifier, arkColor.color);
    } else {
      modifier(this._modifiers, BlankColorModifier, undefined);
    }
    return this;
  }
}

globalThis.Blank.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);

  let component = this.createOrGetNode(elmtId, () => {
    return new ArkBlankComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();

}
