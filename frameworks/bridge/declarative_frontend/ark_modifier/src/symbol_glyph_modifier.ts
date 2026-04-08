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

class LazyArkSymbolGlyphComponent extends ArkComponent {
  static module: SymbolGlyphComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
   super(nativePtr, classType);
   if (LazyArkSymbolGlyphComponent.module === undefined) {
     LazyArkSymbolGlyphComponent.module = globalThis.requireNapi('arkui.components.arksymbolglyph');
   }

   this.lazyComponent = LazyArkSymbolGlyphComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  initialize(value: [Resource | undefined]): this {
   this.lazyComponent.initialize(value);
   return this;
  }

  fontColor(value: Array<ResourceColor>): this {
   this.lazyComponent.fontColor(value);
   return this;
  }

  fontSize(value: number | string | Resource): this {
   this.lazyComponent.fontSize(value);
   return this;
  }

  fontWeight(value: number | FontWeight | string): this {
   this.lazyComponent.fontWeight(value);
   return this;
  }

  renderingStrategy(value: SymbolRenderingStrategy): this {
   this.lazyComponent.renderingStrategy(value);
   return this;
  }

  effectStrategy(value: SymbolEffectStrategy): this {
   this.lazyComponent.effectStrategy(value);
   return this;
  }

  symbolEffect(effect: SymbolEffect, action?: boolean | number): this {
   this.lazyComponent.symbolEffect(effect, action);
   return this;
  }

  shaderStyle(value: Array<ShaderStyle | undefined> | ShaderStyle): this {
   this.lazyComponent.shaderStyle(value);
   return this;
  }

  symbolShadow(value: ShadowOptions): this {
   this.lazyComponent.symbolShadow(value);
   return this;
  }

  minFontScale(value: number | Resource): this {
   this.lazyComponent.minFontScale(value);
   return this;
  }

  maxFontScale(value: number | Resource): this {
   this.lazyComponent.maxFontScale(value);
   return this;
  }
}

class SymbolGlyphModifier extends LazyArkSymbolGlyphComponent implements AttributeModifier<SymbolGlyphAttribute> {
    constructor(src: Resource, nativePtr: KNode, classType: ModifierType) {
      super(nativePtr, classType);
      this._modifiersWithKeys = new ModifierMap();
    this.setMap();
      if (src !== undefined) {
        this.initialize([src]);
      }
    }

    applyNormalAttribute(instance: SymbolGlyphAttribute): void {
      ModifierUtils.applySetOnChange(this);
      // @ts-ignore
      ModifierUtils.applyAndMergeModifier<SymbolGlyphAttribute, ArkSymbolGlyphComponent, ArkSymbolGlyphComponent>(instance, this);
    }
  }
