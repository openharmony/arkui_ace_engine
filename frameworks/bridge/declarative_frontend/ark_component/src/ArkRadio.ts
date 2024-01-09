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

class ArkRadioComponent extends ArkComponent implements RadioAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
    throw new Error('Method not implemented.');
  }
  checked(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, RadioCheckedModifier.identity, RadioCheckedModifier, value);
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

class RadioCheckedModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('radioChecked');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().radio.resetRadioChecked(node);
    } else {
      getUINativeModule().radio.setRadioChecked(node, this.value!);
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
      getUINativeModule().radio.resetRadioStyle(node);
    } else {
      getUINativeModule().radio.setRadioStyle(
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
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkRadioComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};
