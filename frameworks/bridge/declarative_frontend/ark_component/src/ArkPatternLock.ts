/// <reference path="./import.ts" />
class ArkPatternLockComponent extends ArkComponent implements PatternLockAttribute {
  sideLength(value: any): this {
    throw new Error("Method not implemented.");
  }
  circleRadius(value: any): this {
    throw new Error("Method not implemented.");
  }
  regularColor(value: any): this {
    throw new Error("Method not implemented.");
  }
  selectedColor(value: any): this {
    throw new Error("Method not implemented.");
  }
  activeColor(value: any): this {
    throw new Error("Method not implemented.");
  }
  pathColor(value: any): this {
    throw new Error("Method not implemented.");
  }
  pathStrokeWidth(value: string | number): this {
    throw new Error("Method not implemented.");
  }
  onPatternComplete(callback: (input: number[]) => void): this {
    throw new Error("Method not implemented.");
  }
  autoReset(value: boolean): this {
    throw new Error("Method not implemented.");
  }
  onDotConnect(callback: any): this {
    throw new Error("Method not implemented.");
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}

// @ts-ignore
globalThis.PatternLock.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkPatternLockComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
