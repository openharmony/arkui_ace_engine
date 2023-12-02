/// <reference path="./import.ts" />
class ColumnAlignItemsModifier extends Modifier<number> {
  static identity: Symbol = Symbol('columnAlignItems');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().column.resetAlignItems(node);
    } else {
      GetUINativeModule().column.setAlignItems(node, this.value!);
    }
  }
}

class ColumnJustifyContentModifier extends Modifier<number> {
  static identity: Symbol = Symbol('columnJustifyContent');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().column.resetJustifyContent(node);
    } else {
      GetUINativeModule().column.setJustifyContent(node, this.value!);
    }
  }
}

class ArkColumnComponent extends ArkComponent implements CommonMethod<ColumnAttribute>{
  alignItems(value: HorizontalAlign): ColumnAttribute {
    if (value === null || value === undefined) {
      modifier(this._modifiers, ColumnAlignItemsModifier, undefined);
    } else if (!(value in HorizontalAlign)) {
      modifier(this._modifiers, ColumnAlignItemsModifier, undefined);
    } else {
      modifier(this._modifiers, ColumnAlignItemsModifier, value);
    }
    return this;
  }
  justifyContent(value: FlexAlign): ColumnAttribute {
    if (value === null || value === undefined) {
      modifier(this._modifiers, ColumnJustifyContentModifier, undefined);
    } else if (!(value in FlexAlign)) {
      modifier(this._modifiers, ColumnJustifyContentModifier, undefined);
    } else {
      modifier(this._modifiers, ColumnJustifyContentModifier, value);
    }
    return this;
  }
  pointLight(value: PointLightStyle): ColumnAttribute {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}
// @ts-ignore
globalThis.Column.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkColumnComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}