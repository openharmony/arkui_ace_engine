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

class LazyArkLoadingProgressComponent extends ArkComponent {
  static module:  LoadingProgressComponentModule | undefined = undefined;

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkLoadingProgressComponent.module === undefined) {
      LazyArkLoadingProgressComponent.module =
          globalThis.requireNapi('arkui.components.arkloadingprogress');
    }
    this.lazyComponent =
        LazyArkLoadingProgressComponent.module.createComponent(nativePtr, classType);
  }

  setMap() {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
  color(value: ResourceColor) {
    this.lazyComponent.color(value);
    return this;
  }
  enableLoading(value: boolean) {
    this.lazyComponent.enableLoading(value);
    return this;
  }
  foregroundColor(value: ResourceColor) {
    this.lazyComponent.foregroundColor(value);
    return this;
  }
  contentModifier(value: ContentModifier<LoadingProgressConfiguration>) {
    this.lazyComponent.contentModifier(value);
    return this;
  }
}

class LoadingProgressModifier extends LazyArkLoadingProgressComponent {
  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: LoadingProgressAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
