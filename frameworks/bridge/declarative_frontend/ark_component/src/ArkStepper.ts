/// <reference path='./import.ts' />
class ArkStepperComponent extends ArkComponent implements StepperAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  onFinish(callback: () => void): this {
    throw new Error('Method not implemented.');
  }
  onSkip(callback: () => void): this {
    throw new Error('Method not implemented.');
  }
  onChange(callback: (prevIndex: number, index: number) => void): this {
    throw new Error('Method not implemented.');
  }
  onNext(callback: (index: number, pendingIndex: number) => void): this {
    throw new Error('Method not implemented.');
  }
  onPrevious(callback: (index: number, pendingIndex: number) => void): this {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}

// @ts-ignore
globalThis.Stepper.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkStepperComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
