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

class LazyArkSymbolSpanComponent extends ArkComponent {
  static module: SymbolSpanComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
   super(nativePtr, classType);
   if (LazyArkSymbolSpanComponent.module === undefined) {
     LazyArkSymbolSpanComponent.module = globalThis.requireNapi('arkui.components.arksymbolspan');
   }

   this.lazyComponent = LazyArkSymbolSpanComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  initialize(value: [Resource | undefined]): this {
   this.lazyComponent.initialize(value);
   return this;
  }

  fontSize(value: number | string | Resource): this {
   this.lazyComponent.fontSize(value);
   return this;
  }

  fontColor(value: Array<ResourceColor | ColorMetrics> | undefined): this {
   this.lazyComponent.fontColor(value);
   return this;
  }

  fontWeight(value: number | FontWeight | ResourceStr, fontWeightConfigs?: FontWeightConfigs): this {
   this.lazyComponent.fontWeight(value, fontWeightConfigs);
   return this;
  }

  effectStrategy(value: SymbolEffectStrategy): this {
   this.lazyComponent.effectStrategy(value);
   return this;
  }

  renderingStrategy(value: SymbolRenderingStrategy): this {
   this.lazyComponent.renderingStrategy(value);
   return this;
  }
}

class SymbolSpanModifier extends LazyArkSymbolSpanComponent implements AttributeModifier<SymbolSpanAttribute> {
    constructor(src: Resource, nativePtr: KNode, classType: ModifierType) {
      super(nativePtr, classType);
      this._modifiersWithKeys = new ModifierMap();
      this.setMap();
      if (src !== undefined) {
        this.initialize([src]);
      }
    }

    applyNormalAttribute(instance: SymbolSpanAttribute): void {
      ModifierUtils.applySetOnChange(this);
      ModifierUtils.applyAndMergeModifier<SymbolSpanAttribute, ArkSymbolSpanComponent, ArkComponent>(instance, this);
    }
  }
