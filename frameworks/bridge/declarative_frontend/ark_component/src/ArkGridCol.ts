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
    modifier(this._modifiers, GridColSpanModifier, this.parserGridColColumnOption(value, 1));
    return this;
  }
  gridColOffset(value: number | GridColColumnOption): GridColAttribute {
    modifier(this._modifiers, GridColOffsetModifier, this.parserGridColColumnOption(value, 0));
    return this;
  }
  order(value: number | GridColColumnOption): GridColAttribute {
    modifier(this._modifiers, GridColOrderModifier, this.parserGridColColumnOption(value, 0));
    return this;
  }
  private parserGridColColumnOption(jsValue: any, defaultVal: number) {
    let gridColColumnOption: ArkGridColColumnOption = new ArkGridColColumnOption();
    if (jsValue === null || jsValue === undefined) {
      gridColColumnOption.xs = defaultVal;
      gridColColumnOption.sm = defaultVal;
      gridColColumnOption.md = defaultVal;
      gridColColumnOption.lg = defaultVal;
      gridColColumnOption.xl = defaultVal;
      gridColColumnOption.xxl = defaultVal;
    } else if (isNumber(jsValue) && jsValue >= 0) {
      gridColColumnOption.xs = jsValue;
      gridColColumnOption.sm = jsValue;
      gridColColumnOption.md = jsValue;
      gridColColumnOption.lg = jsValue;
      gridColColumnOption.xl = jsValue;
      gridColColumnOption.xxl = jsValue;
    } else if (isObject(jsValue)) {
      let hasValue = false;
      let attributeNames = ['xs', 'sm', 'md', 'lg', 'xl', 'xxl']
      for (let attributeName of attributeNames) {
        let attributeValue = jsValue[attributeName];
        if (attributeValue === null || attributeValue === undefined) {
          jsValue[attributeName] = defaultVal;
        } else if (isNumber(attributeValue) && <number>attributeValue >= 0) {
          continue;
        } else {
          jsValue[attributeName] = defaultVal;
        }
      }
      gridColColumnOption.xs = jsValue.xs;
      gridColColumnOption.sm = jsValue.sm;
      gridColColumnOption.md = jsValue.md;
      gridColColumnOption.lg = jsValue.lg;
      gridColColumnOption.xl = jsValue.xl;
      gridColColumnOption.xxl = jsValue.xxl;
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
