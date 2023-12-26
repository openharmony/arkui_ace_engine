/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/// <reference path='./import.ts' />
class ArkTextPickerComponent extends ArkComponent implements TextPickerAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
    throw new Error('Method not implemented.');
  }
  defaultPickerItemHeight(value: string | number): this {
    modifierWithKey(
      this._modifiersWithKeys, TextpickerDefaultPickerItemHeightModifier.identity, TextpickerDefaultPickerItemHeightModifier, value);
    return this;
  }
  canLoop(value: boolean): this {
    modifierWithKey(
      this._modifiersWithKeys, TextpickerCanLoopModifier.identity, TextpickerCanLoopModifier, value);
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
    modifierWithKey(
      this._modifiersWithKeys, TextpickerSelectedIndexModifier.identity, TextpickerSelectedIndexModifier, value);
    return this;
  }
}

class TextpickerCanLoopModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('textpickerCanLoop');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textpicker.resetCanLoop(node);
    } else {
      getUINativeModule().textpicker.setCanLoop(node, this.value);
    }
  }
}

class TextpickerSelectedIndexModifier extends ModifierWithKey<number | number[]> {
  constructor(value: number | number[]) {
    super(value);
  }
  static identity: Symbol = Symbol('textpickerSelectedIndex');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textpicker.resetSelectedIndex(node);
    } else {
      getUINativeModule().textpicker.setSelectedIndex(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    if (Array.isArray(this.stageValue) && Array.isArray(this.value)) {
      return !deepCompareArrays(this.stageValue, this.value);
    } else if (Array.isArray(this.stageValue) || Array.isArray(this.value)) {
      return true;
    } else {
      return this.stageValue !== this.value;
    }
  }

}

class TextpickerTextStyleModifier extends ModifierWithKey<PickerTextStyle> {
  constructor(value: PickerTextStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('textpickerTextStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textpicker.resetTextStyle(node);
    } else {
      getUINativeModule().textpicker.setTextStyle(node, this.value?.color ?? undefined,
        this.value?.font?.size ?? undefined,
        this.value?.font?.weight ?? undefined,
        this.value?.font?.family ?? undefined,
        this.value?.font?.style ?? undefined);
    }
  }

  checkObjectDiff(): boolean {
    if (!(this.stageValue?.font?.weight === this.value?.font?.weight &&
      this.stageValue?.font?.style === this.value?.font?.style)) {
      return true;
    } else {
      return !isBaseOrResourceEqual(this.stageValue?.color, this.value?.color) ||
        !isBaseOrResourceEqual(this.stageValue?.font?.size, this.value?.font?.size) ||
        !isBaseOrResourceEqual(this.stageValue?.font?.family, this.value?.font?.family);
    }
  }
}

class TextpickerSelectedTextStyleModifier extends ModifierWithKey<PickerTextStyle> {
  constructor(value: PickerTextStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('textpickerSelectedTextStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textpicker.resetSelectedTextStyle(node);
    } else {
      getUINativeModule().textpicker.setSelectedTextStyle(node, this.value?.color ?? undefined,
        this.value?.font?.size ?? undefined,
        this.value?.font?.weight ?? undefined,
        this.value?.font?.family ?? undefined,
        this.value?.font?.style ?? undefined);
    }
  }

  checkObjectDiff(): boolean {
    if (!(this.stageValue?.font?.weight === this.value?.font?.weight &&
      this.stageValue?.font?.style === this.value?.font?.style)) {
      return true;
    } else {
      return !isBaseOrResourceEqual(this.stageValue?.color, this.value?.color) ||
        !isBaseOrResourceEqual(this.stageValue?.font?.size, this.value?.font?.size) ||
        !isBaseOrResourceEqual(this.stageValue?.font?.family, this.value?.font?.family);
    }
  }
}

class TextpickerDisappearTextStyleModifier extends ModifierWithKey<PickerTextStyle> {
  constructor(value: PickerTextStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('textpickerDisappearTextStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textpicker.resetDisappearTextStyle(node);
    } else {
      getUINativeModule().textpicker.setDisappearTextStyle(node, this.value?.color ?? undefined,
        this.value?.font?.size ?? undefined,
        this.value?.font?.weight ?? undefined,
        this.value?.font?.family ?? undefined,
        this.value?.font?.style ?? undefined);
    }
  }

  checkObjectDiff(): boolean {
    if (!(this.stageValue?.font?.weight === this.value?.font?.weight &&
      this.stageValue?.font?.style === this.value?.font?.style)) {
      return true;
    } else {
      return !isBaseOrResourceEqual(this.stageValue?.color, this.value?.color) ||
        !isBaseOrResourceEqual(this.stageValue?.font?.size, this.value?.font?.size) ||
        !isBaseOrResourceEqual(this.stageValue?.font?.family, this.value?.font?.family);
    }
  }
}

class TextpickerDefaultPickerItemHeightModifier extends ModifierWithKey<number | string> {
  constructor(value: number | string) {
    super(value);
  }
  static identity: Symbol = Symbol('textpickerDefaultPickerItemHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().textpicker.resetDefaultPickerItemHeight(node);
    } else {
      getUINativeModule().textpicker.setDefaultPickerItemHeight(node, this.value);
    }
  }
}

// @ts-ignore
globalThis.TextPicker.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkTextPickerComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};
