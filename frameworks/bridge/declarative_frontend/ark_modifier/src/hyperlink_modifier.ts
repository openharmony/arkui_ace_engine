/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

class LazyArkHyperlinkComponent extends ArkComponent {
  static module: HyperlinkComponentModule | undefined = undefined;

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkHyperlinkComponent.module === undefined) {
      LazyArkHyperlinkComponent.module = globalThis.requireNapi('arkui.components.arkhyperlink');
    }

    this.lazyComponent = LazyArkHyperlinkComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  color(color: Color | number | string | Resource): this {
    this.lazyComponent.color(color);
    return this;
  }

  draggable(draggable: boolean): this {
    this.lazyComponent.draggable(draggable);
    return this;
  }

  responseRegion(region: Array<Rectangle> | Rectangle): this {
    this.lazyComponent.responseRegion(region);
    return this;
  }
}

class HyperlinkModifier extends LazyArkHyperlinkComponent implements AttributeModifier<HyperlinkAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: HyperlinkAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<HyperlinkAttribute, ArkHyperlinkComponent, ArkComponent>(instance, this);
  }
}
