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
class ArkStepperComponent extends ArkComponent implements StepperAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
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
}

// @ts-ignore
globalThis.Stepper.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkStepperComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.CommonModifier(nativePtr, classType);
  });
};
