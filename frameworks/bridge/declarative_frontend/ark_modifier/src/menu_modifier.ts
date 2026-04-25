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

class LazyArkMenuComponent extends ArkComponent {
  static module: MenuComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
   super(nativePtr, classType);
   if (LazyArkMenuComponent.module === undefined) {
     LazyArkMenuComponent.module = globalThis.requireNapi('arkui.components.arkmenu');
   }

   this.lazyComponent = LazyArkMenuComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  width(value: Length): this {
   this.lazyComponent.width(value);
   return this;
  }

  fontSize(value: Length): this {
   this.lazyComponent.fontSize(value);
   return this;
  }

  font(value: Font): this {
   this.lazyComponent.font(value);
   return this;
  }

  fontColor(value: ResourceColor): this {
   this.lazyComponent.fontColor(value);
   return this;
  }

  radius(value: Dimension | BorderRadiuses): this {
   this.lazyComponent.radius(value);
   return this;
  }

  menuItemDivider(value: DividerStyleOptions | undefined): this {
   this.lazyComponent.menuItemDivider(value);
   return this;
  }

  menuItemGroupDivider(value: DividerStyleOptions | undefined): this {
   this.lazyComponent.menuItemGroupDivider(value);
   return this;
  }

  subMenuExpandingMode(value: SubMenuExpandingMode): this {
   this.lazyComponent.subMenuExpandingMode(value);
   return this;
  }

  subMenuExpandSymbol(value: SymbolGlyphModifier): this {
   this.lazyComponent.subMenuExpandSymbol(value);
   return this;
  }
}
class MenuModifier extends LazyArkMenuComponent implements AttributeModifier<MenuAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: MenuAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<MenuAttribute, ArkMenuComponent, ArkComponent>(instance, this);
  }
}
