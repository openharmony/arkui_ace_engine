/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

class LazyArkImageAnimatorComponent extends ArkComponent {
  static module: ImageAnimatorComponentModule | undefined = undefined;

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkImageAnimatorComponent.module === undefined) {
      LazyArkImageAnimatorComponent.module = globalThis.requireNapi('arkui.components.arkimageanimator');
    }

    this.lazyComponent = LazyArkImageAnimatorComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  images(value: Array<ImageFrameInfo>): this {
    this.lazyComponent.images(value);
    return this;
  }

  state(value: AnimationStatus): this {
    this.lazyComponent.state(value);
    return this;
  }

  duration(value: number): this {
    this.lazyComponent.duration(value);
    return this;
  }

  reverse(value: boolean): this {
    this.lazyComponent.reverse(value);
    return this;
  }

  fixedSize(value: boolean): this {
    this.lazyComponent.fixedSize(value);
    return this;
  }

  preDecode(value: number): this {
    throw new Error('preDecode function not supported in attributeModifier scenario.');
  }

  fillMode(value: FillMode): this {
    this.lazyComponent.fillMode(value);
    return this;
  }

  iterations(value: number): this {
    this.lazyComponent.iterations(value);
    return this;
  }

  monitorInvisibleArea(value: boolean): this {
    this.lazyComponent.monitorInvisibleArea(value);
    return this;
  }
}

class ImageAnimatorModifier extends LazyArkImageAnimatorComponent implements AttributeModifier<ImageAnimatorAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: ImageAnimatorAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<ImageAnimatorAttribute, ArkImageAnimatorComponent, ArkComponent>(instance, this);
  }
}
