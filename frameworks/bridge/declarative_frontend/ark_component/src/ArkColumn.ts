/// <reference path="./import.ts" />
class ColumnAlignItemsModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('columnAlignItems');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().column.resetAlignItems(node);
    } else {
      GetUINativeModule().column.setAlignItems(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ColumnJustifyContentModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('columnJustifyContent');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().column.resetJustifyContent(node);
    } else {
      GetUINativeModule().column.setJustifyContent(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ArkColumnComponent extends ArkComponent implements CommonMethod<ColumnAttribute>{
  alignItems(value: HorizontalAlign): ColumnAttribute {
    modifierWithKey(this._modifiersWithKeys, ColumnAlignItemsModifier.identity, ColumnAlignItemsModifier, value);
    return this;
  }
  justifyContent(value: FlexAlign): ColumnAttribute {
    modifierWithKey(this._modifiersWithKeys, ColumnJustifyContentModifier.identity, ColumnJustifyContentModifier, value);
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