/// <reference path="./import.ts" />
class DividerVerticalModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('dividerVertical');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().divider.resetVertical(node);
    } else {
      GetUINativeModule().divider.setVertical(node, this.value!);
    }
  }
}
class DividerLineCapModifier extends Modifier<LineCapStyle> {
  static identity: Symbol = Symbol('dividerLineCap');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().divider.resetLineCap(node);
    } else {
      GetUINativeModule().divider.setLineCap(node, this.value!);
    }
  }
}
class DividerColorModifier extends ModifierWithKey<ResourceColor> {
  static identity: Symbol = Symbol('dividerColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().divider.resetColor(node);
    } else {
      GetUINativeModule().divider.setColor(node, this.value!);
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
class DividerStrokeWidthModifier extends Modifier<number | string> {
  static identity: Symbol = Symbol('dividerStrokeWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().divider.resetStrokeWidth(node);
    } else {
      GetUINativeModule().divider.setStrokeWidth(node, this.value!);
    }
  }
}
class ArkDividerComponent extends ArkComponent implements DividerAttribute {
  vertical(value: boolean): DividerAttribute {
    if (value) {
      modifier(this._modifiers, DividerVerticalModifier, value);
    } else {
      modifier(this._modifiers, DividerVerticalModifier, undefined);
    }
    return this;
  }
  color(value: ResourceColor): DividerAttribute {
    modifierWithKey(this._modifiersWithKeys, DividerColorModifier.identity, DividerColorModifier, value);
    return this;
  }
  strokeWidth(value: number | string): DividerAttribute {
    if (isNumber(value) || isString(value)) {
      modifier(this._modifiers, DividerStrokeWidthModifier, value);
    } else {
      modifier(this._modifiers, DividerStrokeWidthModifier, undefined);
    }
    return this;
  }
  lineCap(value: LineCapStyle): DividerAttribute {
    if (value) {
      modifier(this._modifiers, DividerLineCapModifier, value);
    } else {
      modifier(this._modifiers, DividerLineCapModifier, undefined);
    }
    return this;
  }
}
// @ts-ignore
globalThis.Divider.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);

  let component = this.createOrGetNode(elmtId, () => {
    return new ArkDividerComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
