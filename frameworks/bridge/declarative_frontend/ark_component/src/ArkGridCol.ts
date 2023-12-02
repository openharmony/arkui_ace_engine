/// <reference path="./import.ts" />
class GridColSpanModifier extends Modifier<ArkGridColColumnOption> {
  static identity: Symbol = Symbol('gridColSpan');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().gridCol.resetSpan(node);
    } else {
      GetUINativeModule().gridCol.setSpan(node, this.value.xs,
        this.value.sm, this.value.md, this.value.lg, this.value.xl, this.value.xxl);
    }
  }
}
class GridColOffsetModifier extends Modifier<ArkGridColColumnOption> {
  static identity: Symbol = Symbol('gridColOffset');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().gridCol.resetGridColOffset(node);
    } else {
      GetUINativeModule().gridCol.setGridColOffset(node, this.value.xs,
        this.value.sm, this.value.md, this.value.lg, this.value.xl, this.value.xxl);
    }
  }
}
class GridColOrderModifier extends Modifier<ArkGridColColumnOption> {
  static identity: Symbol = Symbol('gridColOrder');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().gridCol.resetOrder(node);
    } else {
      GetUINativeModule().gridCol.setOrder(node, this.value.xs,
        this.value.sm, this.value.md, this.value.lg, this.value.xl, this.value.xxl);
    }
  }
}

class ArkGridColComponent extends ArkComponent implements GridColAttribute {
  span(value: number | GridColColumnOption): GridColAttribute {
    modifier(this._modifiers, GridColSpanModifier, this.parserGridColColumnOption(value));
    return this;
  }
  gridColOffset(value: number | GridColColumnOption): GridColAttribute {
    modifier(this._modifiers, GridColOffsetModifier, this.parserGridColColumnOption(value));
    return this;
  }
  order(value: number | GridColColumnOption): GridColAttribute {
    modifier(this._modifiers, GridColOrderModifier, this.parserGridColColumnOption(value));
    return this;
  }
  private parserGridColColumnOption(jsValue: any) {
    let gridColColumnOption = new ArkGridColColumnOption();
    if (isNumber(jsValue) && jsValue >= 0) {
      gridColColumnOption.xs = jsValue;
      gridColColumnOption.sm = jsValue;
      gridColColumnOption.md = jsValue;
      gridColColumnOption.lg = jsValue;
      gridColColumnOption.xl = jsValue;
      gridColColumnOption.xxl = jsValue;
    }
    else if (isObject(jsValue)) {
      if (isNumber(jsValue.xs) && jsValue.xs >= 0) {
        gridColColumnOption.xs = jsValue.xs;
      }
      if (isNumber(jsValue.sm) && jsValue.sm >= 0) {
        gridColColumnOption.sm = jsValue.sm;
      }
      if (isNumber(jsValue.md) && jsValue.md >= 0) {
        gridColColumnOption.md = jsValue.md;
      }
      if (isNumber(jsValue.lg) && jsValue.lg >= 0) {
        gridColColumnOption.lg = jsValue.lg;
      }
      if (isNumber(jsValue.xl) && jsValue.xl >= 0) {
        gridColColumnOption.xl = jsValue.xl;
      }
      if (isNumber(jsValue.xxl) && jsValue.xxl >= 0) {
        gridColColumnOption.xxl = jsValue.xxl;
      }
    }
    return gridColColumnOption;
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
