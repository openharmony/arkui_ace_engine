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

class LazyArkQRCodeComponent extends ArkComponent {
  static module: QRCodeComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
   super(nativePtr, classType);
   if (LazyArkQRCodeComponent.module === undefined) {
     LazyArkQRCodeComponent.module = globalThis.requireNapi('arkui.components.arkqrcode');
   }

   this.lazyComponent = LazyArkQRCodeComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  color(value: ResourceColor): LazyArkQRCodeComponent {
   this.lazyComponent.color(value);
   return this;
  }

  backgroundColor(value: ResourceColor): this {
    this.lazyComponent.backgroundColor(value);
    return this;
  }

  contentOpacity(value: number | Resource): LazyArkQRCodeComponent {
   this.lazyComponent.contentOpacity(value);
   return this;
  }
}

class QRCodeModifier extends LazyArkQRCodeComponent implements AttributeModifier<QRCodeAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: QRCodeAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<QRCodeAttribute, ArkQRCodeComponent, ArkComponent>(instance, this);
  }
}
