/// <reference path='./import.ts' />
class ArkStepperItemComponent extends ArkComponent implements StepperItemAttribute {
  prevLabel(value: string): this {
    throw new Error('Method not implemented.');
  }
  nextLabel(value: string): StepperItemAttribute {
    modifier(this._modifiers, NextLabelModifier, undefined);
    return this;
    }
    status(value ?: ItemState | undefined): this {
      throw new Error('Method not implemented.');
    }
    monopolizeEvents(monopolize: boolean): this {
      throw new Error('Method not implemented.');
    }
  }
  
class NextLabelModifier extends Modifier<ArkDivider> {
  static identity: Symbol = Symbol('NextLabel');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().tabs.resetNextLabel(node);
    } else {
      GetUINativeModule().tabs.setNextLabel(node, this.value);
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
