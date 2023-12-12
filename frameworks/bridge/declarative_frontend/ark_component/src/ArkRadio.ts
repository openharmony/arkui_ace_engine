/// <reference path='./import.ts' />

class ArkRadioComponent extends ArkComponent implements RadioAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
    throw new Error('Method not implemented.');
  }
  checked(value: boolean): this {
    if (!!value) {
      modifier(this._modifiers, RadioCheckedModifier, value);
    } else {
      modifier(this._modifiers, RadioCheckedModifier, undefined);
    }
    return this;
  }
  onChange(callback: (isChecked: boolean) => void): this {
    throw new Error('Method not implemented.');
  }
  radioStyle(value: RadioStyle): this {
    modifierWithKey(this._modifiersWithKeys, RadioStyleModifier.identity, RadioStyleModifier, value);
    return this;
  }
}

class RadioCheckedModifier extends Modifier<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('radioChecked');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().radio.resetRadioChecked(node);
    } else {
      GetUINativeModule().radio.setRadioChecked(node, this.value!);
    }
  }
}

class RadioStyleModifier extends ModifierWithKey<RadioStyle> {
  constructor(value: RadioStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('radioStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().radio.resetRadioStyle(node);
    } else {
      GetUINativeModule().radio.setRadioStyle(
        node, this.value.checkedBackgroundColor, this.value.uncheckedBorderColor, this.value.indicatorColor);
    }
  }

  checkObjectDiff(): boolean {
    let checkedBackgroundColorEQ =
      isBaseOrResourceEqual(this.stageValue.checkedBackgroundColor,
        this.value.checkedBackgroundColor);
    let uncheckedBorderColorEQ =
      isBaseOrResourceEqual(this.stageValue.uncheckedBorderColor,
        this.value.uncheckedBorderColor);
    let indicatorColorEQ =
      isBaseOrResourceEqual(this.stageValue.indicatorColor,
        this.value.indicatorColor);
    return !checkedBackgroundColorEQ ||
      !uncheckedBorderColorEQ ||
      !indicatorColorEQ;
  }
}

// @ts-ignore
globalThis.Radio.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkRadioComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}
