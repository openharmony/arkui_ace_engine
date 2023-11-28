/// <reference path="./import.ts" />
class ArkImageAnimatorComponent extends ArkComponent implements ImageAnimatorAttribute {
  images(value: ImageFrameInfo[]): this {
    throw new Error("Method not implemented.");
  }
  state(value: AnimationStatus): this {
    throw new Error("Method not implemented.");
  }
  duration(value: number): this {
    throw new Error("Method not implemented.");
  }
  reverse(value: boolean): this {
    throw new Error("Method not implemented.");
  }
  fixedSize(value: boolean): this {
    throw new Error("Method not implemented.");
  }
  preDecode(value: number): this {
    throw new Error("Method not implemented.");
  }
  fillMode(value: FillMode): this {
    throw new Error("Method not implemented.");
  }
  iterations(value: number): this {
    throw new Error("Method not implemented.");
  }
  onStart(event: () => void): this {
    throw new Error("Method not implemented.");
  }
  onPause(event: () => void): this {
    throw new Error("Method not implemented.");
  }
  onRepeat(event: () => void): this {
    throw new Error("Method not implemented.");
  }
  onCancel(event: () => void): this {
    throw new Error("Method not implemented.");
  }
  onFinish(event: () => void): this {
    throw new Error("Method not implemented.");
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}

// @ts-ignore
globalThis.ImageAnimator.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, ()=> {
    return new ArkImageAnimatorComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
