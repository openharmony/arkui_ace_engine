/// <reference path="./import.ts" />
class RowAlignItemsModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('rowAlignItems');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().row.resetAlignItems(node);
    } else {
      GetUINativeModule().row.setAlignItems(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class RowJustifyContentlModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('rowJustifyContent');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().row.resetJustifyContent(node);
    } else {
      GetUINativeModule().row.setJustifyContent(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ArkRowComponent extends ArkComponent implements RowAttribute {
  alignItems(value: VerticalAlign): RowAttribute {
    modifierWithKey(this._modifiersWithKeys, RowAlignItemsModifier.identity, RowAlignItemsModifier, value);
    return this;
  }
  justifyContent(value: FlexAlign): RowAttribute {
    modifierWithKey(this._modifiersWithKeys, RowJustifyContentlModifier.identity, RowJustifyContentlModifier, value);
    return this;
  }
  pointLight(value: PointLightStyle): RowAttribute {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}

// @ts-ignore
globalThis.Row.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkRowComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
