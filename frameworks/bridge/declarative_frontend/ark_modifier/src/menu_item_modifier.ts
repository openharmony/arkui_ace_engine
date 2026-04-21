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

class LazyArkMenuItemComponent extends ArkComponent {
  static module: MenuItemComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
   super(nativePtr, classType);
   if (LazyArkMenuItemComponent.module === undefined) {
     LazyArkMenuItemComponent.module = globalThis.requireNapi('arkui.components.arkmenuitem');
   }

   this.lazyComponent = LazyArkMenuItemComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  selected(value: boolean): this {
   this.lazyComponent.selected(value);
   return this;
  }

  selectIcon(value: boolean | ResourceStr | SymbolGlyphModifier): this {
   this.lazyComponent.selectIcon(value);
   return this;
  }

  onChange(callback: (selected: boolean) => void): this {
   this.lazyComponent.onChange(callback);
   return this;
  }

  contentFont(value: Font): this {
   this.lazyComponent.contentFont(value);
   return this;
  }

  contentFontColor(value: ResourceColor): this {
   this.lazyComponent.contentFontColor(value);
   return this;
  }

  labelFont(value: Font): this {
   this.lazyComponent.labelFont(value);
   return this;
  }

  labelFontColor(value: ResourceColor): this {
   this.lazyComponent.labelFontColor(value);
   return this;
  }
}
class MenuItemModifier extends LazyArkMenuItemComponent implements AttributeModifier<MenuItemAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: MenuItemAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<MenuItemAttribute, ArkMenuItemComponent, ArkComponent>(instance, this);
  }
}
