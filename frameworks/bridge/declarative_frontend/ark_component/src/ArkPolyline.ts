/// <reference path='./import.ts' />
/// <reference path='./ArkCommonShape.ts' />
const ARRAY_LENGTH = 2;
class ArkPolylineComponent extends ArkCommonShapeComponent implements PolylineAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  points(value: Array<any>): this {
    modifierWithKey(this._modifiersWithKeys, PolylinePointsModifier.identity, PolylinePointsModifier, value);
    return this;
  }
}

class PolylinePointsModifier extends ModifierWithKey<Array<any>> {
  constructor(value: Array<any>) {
    super(value);
  }
  static identity: Symbol = Symbol('points');
  applyPeer(node: KNode, reset: boolean): void {
    let xPoint = [];
    let yPoint = [];
    if (Array.isArray(this.value)) {
      for (let i = 0; i <= this.value.length; i++) {
        let item = this.value[i];
        if (!Array.isArray(item)) {
          continue;
        }

        if (item.length < ARRAY_LENGTH || isUndefined(item[0]) || isUndefined(item[1])) {
          reset = true;
          break;
        }
        
        xPoint.push(item[0]);
        yPoint.push(item[1]);
      }
    } else {
      reset = true;
    }

    if (reset) {
      GetUINativeModule().polyline.resetPoints(node);
    } else {
      GetUINativeModule().polyline.setPoints(node, xPoint, yPoint);
    }
  }

  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

// @ts-ignore
globalThis.Polyline.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkPolylineComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
