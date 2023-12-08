/// <reference path='./import.ts' />
class ArkStepperItemComponent extends ArkComponent implements StepperItemAttribute {
  prevLabel(value: string): this {
    throw new Error('Method not implemented.');
  }
  nextLabel(value: string): this {
    modifier(this._modifiers, NextLabelModifier, value);
    return this;
  }
  status(value?: ItemState | undefined): this {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}

class NextLabelModifier extends Modifier<string> {
  static identity: Symbol = Symbol('NextLabel');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().stepperItem.resetNextLabel(node);
    } else {
      GetUINativeModule().stepperItem.setNextLabel(node, this.value);
    }
  }
}

// @ts-ignore
globalThis.StepperItem.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkStepperItemComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
