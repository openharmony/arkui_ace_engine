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

class LazyArkSideBarContainerComponent extends ArkComponent {
  static module: SideBarContainerComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
   super(nativePtr, classType);
   if (LazyArkSideBarContainerComponent.module === undefined) {
     LazyArkSideBarContainerComponent.module = globalThis.requireNapi('arkui.components.arksidebarcontainer');
   }

   this.lazyComponent = LazyArkSideBarContainerComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  onChange(callback: (value: boolean) => void): this {
   this.lazyComponent.onChange(callback);
   return this;
  }

  autoHide(value: boolean): this {
   this.lazyComponent.autoHide(value);
   return this;
  }

  showSideBar(value: boolean): this {
   this.lazyComponent.showSideBar(value);
   return this;
  }

  maxSideBarWidth(value: number | Length): this {
   this.lazyComponent.maxSideBarWidth(value);
   return this;
  }

  minSideBarWidth(value: number | Length): this {
   this.lazyComponent.minSideBarWidth(value);
   return this;
  }

  minContentWidth(value: Dimension): this {
   this.lazyComponent.minContentWidth(value);
   return this;
  }

  controlButton(value: ButtonStyle): this {
   this.lazyComponent.controlButton(value);
   return this;
  }

  divider(value: DividerStyle | null): this {
   this.lazyComponent.divider(value);
   return this;
  }

  sideBarPosition(value: SideBarPosition): this {
   this.lazyComponent.sideBarPosition(value);
   return this;
  }

  sideBarWidth(value: number | Length): this {
   this.lazyComponent.sideBarWidth(value);
   return this;
  }

  showControlButton(value: boolean): this {
   this.lazyComponent.showControlButton(value);
   return this;
  }
}
class SideBarContainerModifier extends LazyArkSideBarContainerComponent implements AttributeModifier<SideBarContainerAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: SideBarContainerAttribute): void {
    ModifierUtils.applySetOnChange(this);
    // @ts-ignore
    ModifierUtils.applyAndMergeModifier<SideBarContainerAttribute, ArkSideBarContainerComponent, ArkComponent>(instance, this);
  }
}
