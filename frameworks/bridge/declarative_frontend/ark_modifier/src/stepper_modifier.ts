/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

class LazyArkStepperComponent extends ArkComponent {
  static module: StepperComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
   super(nativePtr, classType);
   if (LazyArkStepperComponent.module === undefined) {
     LazyArkStepperComponent.module = globalThis.requireNapi('arkui.components.arkstepper');
   }

   this.lazyComponent = LazyArkStepperComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  onFinish(callback: () => void): this {
   this.lazyComponent.onFinish(callback);
   return this;
  }

  onSkip(callback: () => void): this {
   this.lazyComponent.onSkip(callback);
   return this;
  }

  onChange(callback: (prevIndex: number, index: number) => void): this {
   this.lazyComponent.onChange(callback);
   return this;
  }

  onNext(callback: (index: number, pendingIndex: number) => void): this {
   this.lazyComponent.onNext(callback);
   return this;
  }

  onPrevious(callback: (index: number, pendingIndex: number) => void): this {
   this.lazyComponent.onPrevious(callback);
   return this;
  }
}class StepperModifier extends LazyArkStepperComponent implements AttributeModifier<StepperAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: StepperAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<StepperAttribute, ArkStepperComponent, ArkComponent>(instance, this);
  }
}
