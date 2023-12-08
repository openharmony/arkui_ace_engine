/// <reference path="./import.ts" />
class GridColSpanModifier extends ModifierWithKey<ArkGridColColumnOption> {
  static identity: Symbol = Symbol('gridColSpan');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().gridCol.resetSpan(node);
    } else {
      if (isNumber(this.value)) {
        GetUINativeModule().gridCol.setSpan(node, this.value,
          this.value, this.value, this.value, this.value, this.value);
      } else {
        GetUINativeModule().gridCol.setSpan(node, this.value.xs,
          this.value.sm, this.value.md, this.value.lg, this.value.xl, this.value.xxl);
      }
    }
  }
  checkObjectDiff(): boolean {
    if(isNumber(this.stageValue)&&isNumber(this.value)) {
      return this.stageValue !== this.value;
    } else if (isObject(this.stageValue)&&isObject(this.value)) {
      return this.stageValue.xs !== this.value.xs ||
      this.stageValue.sm !== this.value.sm ||
      this.stageValue.md !== this.value.md ||
      this.stageValue.lg !== this.value.lg ||
      this.stageValue.xl !== this.value.xl ||
      this.stageValue.xxl !== this.value.xxl;
    } else {
      return true;
    }
  }
}
class GridColOffsetModifier extends ModifierWithKey<ArkGridColColumnOption> {
  static identity: Symbol = Symbol('gridColOffset');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().gridCol.resetGridColOffset(node);
    } else {
      if (isNumber(this.value)) {
        GetUINativeModule().gridCol.setGridColOffset(node, this.value,
          this.value, this.value, this.value, this.value, this.value);
      } else {
        GetUINativeModule().gridCol.setGridColOffset(node, this.value.xs,
          this.value.sm, this.value.md, this.value.lg, this.value.xl, this.value.xxl);
      }
    }
  }
  checkObjectDiff(): boolean {
    if(isNumber(this.stageValue)&&isNumber(this.value)) {
      return this.stageValue !== this.value;
    } else if (isObject(this.stageValue)&&isObject(this.value)) {
      return this.stageValue.xs !== this.value.xs ||
      this.stageValue.sm !== this.value.sm ||
      this.stageValue.md !== this.value.md ||
      this.stageValue.lg !== this.value.lg ||
      this.stageValue.xl !== this.value.xl ||
      this.stageValue.xxl !== this.value.xxl;
    } else {
      return true;
    }
  }
}
class GridColOrderModifier extends ModifierWithKey<ArkGridColColumnOption> {
  static identity: Symbol = Symbol('gridColOrder');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().gridCol.resetOrder(node);
    } else {
      if (isNumber(this.value)) {
        GetUINativeModule().gridCol.setOrder(node, this.value,
          this.value, this.value, this.value, this.value, this.value);
      } else {
        GetUINativeModule().gridCol.setOrder(node, this.value.xs,
          this.value.sm, this.value.md, this.value.lg, this.value.xl, this.value.xxl);
      }
    }
  }
  checkObjectDiff(): boolean {
    if(isNumber(this.stageValue)&&isNumber(this.value)) {
      return this.stageValue !== this.value;
    } else if (isObject(this.stageValue)&&isObject(this.value)) {
      return this.stageValue.xs !== this.value.xs ||
      this.stageValue.sm !== this.value.sm ||
      this.stageValue.md !== this.value.md ||
      this.stageValue.lg !== this.value.lg ||
      this.stageValue.xl !== this.value.xl ||
      this.stageValue.xxl !== this.value.xxl;
    } else {
      return true;
    }
  }
}

class ArkGridColComponent extends ArkComponent implements GridColAttribute {
  span(value: number | GridColColumnOption): GridColAttribute {
    modifierWithKey(this._modifiersWithKeys, GridColSpanModifier.identity, GridColSpanModifier, value);
    return this;
  }
  gridColOffset(value: number | GridColColumnOption): GridColAttribute {
    modifierWithKey(this._modifiersWithKeys, GridColOffsetModifier.identity, GridColOffsetModifier, value);
    return this;
  }
  order(value: number | GridColColumnOption): GridColAttribute {
    modifierWithKey(this._modifiersWithKeys, GridColOrderModifier.identity, GridColOrderModifier, value);
    return this;
  }
}

// @ts-ignore
globalThis.GridCol.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);

  let component = this.createOrGetNode(elmtId, () => {
    return new ArkGridColComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
