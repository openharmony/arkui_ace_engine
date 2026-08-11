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

class LazyArkTabContentComponent extends ArkComponent {
    static module: TabContentComponentModule | undefined = undefined;

    constructor(nativePtr: KNode, classType: ModifierType) {
      super(nativePtr, classType);
      if (LazyArkTabContentComponent.module === undefined) {
        LazyArkTabContentComponent.module = globalThis.requireNapi('arkui.components.arktabcontent');
      }
      this.lazyComponent = LazyArkTabContentComponent.module.createComponent(nativePtr, classType);
    }

    setMap(): void {
      this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
    }

    allowChildCount(): number {
      return this.lazyComponent.allowChildCount();
    }

    tabBar(value: SubTabBarStyle | BottomTabBarStyle | ComponentContent): this {
      this.lazyComponent.tabBar(value);
      return this;
    }

    size(value: SizeOptions): this {
      this.lazyComponent.size(value);
      return this;
    }

    width(value: Length): this {
      this.lazyComponent.width(value);
      return this;
    }

    height(value: Length): this {
      this.lazyComponent.height(value);
      return this;
    }

    onWillShow(event: VoidCallback): this {
      this.lazyComponent.onWillShow(event);
      return this;
    }

    onWillHide(event: VoidCallback): this {
      this.lazyComponent.onWillHide(event);
      return this;
    }
  }

class TabContentModifier extends LazyArkTabContentComponent implements AttributeModifier<TabContentAttribute> {

    constructor(nativePtr: KNode, classType: ModifierType) {
      super(nativePtr, classType);
      this._modifiersWithKeys = new ModifierMap();
      this.setMap();
    }
    
    applyNormalAttribute(instance: TabContentAttribute): void {
      ModifierUtils.applySetOnChange(this);
      ModifierUtils.applyAndMergeModifier<TabContentAttribute, ArkTabContentComponent, ArkComponent>(instance, this);
    }
  }
   