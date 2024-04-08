/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

/// <reference path='./import.ts' />

class ArkUIExtensionComponentComponent extends ArkComponent implements UIExtensionComponentAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  onRemoteReady(callback: any): UIExtensionComponentAttribute {
    throw new Error('Method not implemented.');
  }
  onReceive(callback: any): UIExtensionComponentAttribute {
    throw new Error('Method not implemented.');
  }
  onResult(callback: any): UIExtensionComponentAttribute {
    throw new Error('Method not implemented.');
  }
  onRelease(callback: any): UIExtensionComponentAttribute {
    throw new Error('Method not implemented.');
  }
  onError(callback: any): UIExtensionComponentAttribute {
    throw new Error('Method not implemented.');
  }
}

// @ts-ignore
globalThis.UIExtensionComponent.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkUIExtensionComponentComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.CommonModifier(nativePtr, classType);
  });
};
