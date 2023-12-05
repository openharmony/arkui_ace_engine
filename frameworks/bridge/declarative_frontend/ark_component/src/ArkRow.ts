/// <reference path="./import.ts" />
class RowAlignItemsModifier extends Modifier<number> {
  static identity: Symbol = Symbol('rowAlignItems');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().row.resetAlignItems(node);
    } else {
      GetUINativeModule().row.setAlignItems(node, this.value!);
    }
  }
}

class RowJustifyContentlModifier extends Modifier<number> {
  static identity: Symbol = Symbol('rowJustifyContent');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().row.resetJustifyContent(node);
    } else {
      GetUINativeModule().row.setJustifyContent(node, this.value!);
    }
  }
}

class ArkRowComponent extends ArkComponent implements RowAttribute {
  alignItems(value: VerticalAlign): RowAttribute {
    if (value === null || value === undefined) {
      modifier(this._modifiers, RowAlignItemsModifier, undefined);
    } else if (!(value in VerticalAlign)) {
      modifier(this._modifiers, RowAlignItemsModifier, undefined);
    } else {
      modifier(this._modifiers, RowAlignItemsModifier, value);
    }
    return this;
  }
  justifyContent(value: FlexAlign): RowAttribute {
    if (value === null || value === undefined) {
      modifier(this._modifiers, RowJustifyContentlModifier, undefined);
    } else if (!(value in FlexAlign)) {
      modifier(this._modifiers, RowJustifyContentlModifier, undefined);
    } else {
      modifier(this._modifiers, RowJustifyContentlModifier, value);
    }
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