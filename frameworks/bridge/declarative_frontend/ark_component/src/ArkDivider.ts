/// <reference path="./import.ts" />
class DividerVerticalModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('dividerVertical');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().divider.resetVertical(node);
    } else {
      GetUINativeModule().divider.setVertical(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}
class DividerLineCapModifier extends ModifierWithKey<LineCapStyle> {
  constructor(value: LineCapStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('dividerLineCap');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().divider.resetLineCap(node);
    } else {
      GetUINativeModule().divider.setLineCap(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}
class DividerColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('dividerColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().divider.resetColor(node);
    } else {
      GetUINativeModule().divider.setColor(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class DividerStrokeWidthModifier extends ModifierWithKey<number | string> {
  constructor(value: number | string) {
    super(value);
  }
  static identity: Symbol = Symbol('dividerStrokeWidth');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().divider.resetStrokeWidth(node);
    } else {
      GetUINativeModule().divider.setStrokeWidth(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}
class ArkDividerComponent extends ArkComponent implements DividerAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  vertical(value: boolean): DividerAttribute {
    modifierWithKey(this._modifiersWithKeys, DividerVerticalModifier.identity, DividerVerticalModifier, value);
    return this;
  }
  color(value: ResourceColor): DividerAttribute {
    modifierWithKey(this._modifiersWithKeys, DividerColorModifier.identity, DividerColorModifier, value);
    return this;
  }
  strokeWidth(value: number | string): DividerAttribute {
    modifierWithKey(this._modifiersWithKeys, DividerStrokeWidthModifier.identity, DividerStrokeWidthModifier, value);
    return this;
  }
  lineCap(value: LineCapStyle): DividerAttribute {
    modifierWithKey(this._modifiersWithKeys, DividerLineCapModifier.identity, DividerLineCapModifier, value);
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
