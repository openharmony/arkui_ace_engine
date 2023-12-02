/// <reference path='./import.ts' />
class ArkTextPickerComponent extends ArkComponent implements TextPickerAttribute {
  onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
    throw new Error('Method not implemented.');
  }
  defaultPickerItemHeight(value: string | number): this {
    if (isResource(value)) {
      modifier(this._modifiers, TextpickerDefaultPickerItemHeightModifier, undefined);
    }
    else {
      modifier(this._modifiers, TextpickerDefaultPickerItemHeightModifier, value);
    }
    return this;
  }
  canLoop(value: boolean): this {
    if (isUndefined(value)) {
      modifier(this._modifiers, TextpickerCanLoopModifier, undefined);
    } else {
      modifier(this._modifiers, TextpickerCanLoopModifier, value);
    }
    return this;
  }
  disappearTextStyle(value: PickerTextStyle): this {
    modifierWithKey(
      this._modifiersWithKeys, TextpickerDisappearTextStyleModifier.identity, TextpickerDisappearTextStyleModifier, value);
    return this;
  }
  textStyle(value: PickerTextStyle): this {
    modifierWithKey(
      this._modifiersWithKeys, TextpickerTextStyleModifier.identity, TextpickerTextStyleModifier, value);
    return this;
  }
  selectedTextStyle(value: PickerTextStyle): this {
    modifierWithKey(
      this._modifiersWithKeys, TextpickerSelectedTextStyleModifier.identity, TextpickerSelectedTextStyleModifier, value);
    return this;
  }
  onAccept(callback: (value: string, index: number) => void): this {
    throw new Error('Method not implemented.');
  }
  onCancel(callback: () => void): this {
    throw new Error('Method not implemented.');
  }
  onChange(callback: (value: string | string[], index: number | number[]) => void): this {
    throw new Error('Method not implemented.');
  }
  selectedIndex(value: number | number[]): this {
    let input = new ArkSelectedIndices();

    if (!Array.isArray(value)) {
      if (!isNumber(value)) {
        modifier(this._modifiers, TextpickerSelectedIndexModifier, undefined);
        return this;
      }
      input.selectedValues[0] = value;
    } else {
      input.selectedValues = value;
    }

    modifier(this._modifiers, TextpickerSelectedIndexModifier, input);
    return this;
  }
}

class TextpickerCanLoopModifier extends Modifier<boolean> {
  static identity: Symbol = Symbol('textpickerCanLoop');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textpicker.resetCanLoop(node);
    }
    else {
      GetUINativeModule().textpicker.setCanLoop(node, this.value);
    }
  }
}

class TextpickerSelectedIndexModifier extends Modifier<ArkSelectedIndices> {
  static identity: Symbol = Symbol('textpickerSelectedIndex');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textpicker.resetSelectedIndex(node);
    }
    else {
      GetUINativeModule().textpicker.setSelectedIndex(node, this.value.selectedValues);
    }
  }
}

class TextpickerTextStyleModifier extends ModifierWithKey<PickerTextStyle> {
  static identity: Symbol = Symbol('textpickerTextStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textpicker.resetTextStyle(node);
    }
    else {
      GetUINativeModule().textpicker.setTextStyle(node,
        this.value.color, this.value.font?.size, this.value.font?.weight, this.value.font?.family, this.value.font?.style);
    }
  }
}

class TextpickerSelectedTextStyleModifier extends ModifierWithKey<PickerTextStyle> {
  static identity: Symbol = Symbol('textpickerSelectedTextStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textpicker.resetSelectedTextStyle(node);
    }
    else {
      GetUINativeModule().textpicker.setSelectedTextStyle(node,
        this.value.color, this.value.font?.size, this.value.font?.weight, this.value.font?.family, this.value.font?.style);
    }
  }
}

class TextpickerDisappearTextStyleModifier extends ModifierWithKey<PickerTextStyle> {
  static identity: Symbol = Symbol('textpickerDisappearTextStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textpicker.resetDisappearTextStyle(node);
    }
    else {
      GetUINativeModule().textpicker.setDisappearTextStyle(node,
        this.value.color, this.value.font?.size, this.value.font?.weight, this.value.font?.family, this.value.font?.style);
    }
  }
}

class TextpickerDefaultPickerItemHeightModifier extends Modifier<number | string> {
  static identity: Symbol = Symbol('textpickerDefaultPickerItemHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().textpicker.resetDefaultPickerItemHeight(node);
    }
    else {
      GetUINativeModule().textpicker.setDefaultPickerItemHeight(node, this.value);
    }
  }
}

// @ts-ignore
globalThis.TextPicker.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkTextPickerComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
};
