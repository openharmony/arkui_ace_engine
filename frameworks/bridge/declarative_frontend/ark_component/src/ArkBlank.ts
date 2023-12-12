/// <reference path="./import.ts" />
class BlankColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('blankColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().blank.resetColor(node);
    } else {
      GetUINativeModule().blank.setColor(node, this.value!);
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

class ArkBlankComponent extends ArkComponent implements CommonMethod<BlankAttribute> {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  color(value: ResourceColor): BlankAttribute {
    modifierWithKey(this._modifiersWithKeys, BlankColorModifier.identity, BlankColorModifier, value);
    return this;
  }
}

// @ts-ignore
globalThis.Blank.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkBlankComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
