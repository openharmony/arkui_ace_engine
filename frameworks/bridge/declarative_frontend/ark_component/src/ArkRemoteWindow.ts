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
class ArkRemoteWindowComponent extends ArkComponent implements RemoteWindowAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
}

// @ts-ignore
if (globalThis.RemoteWindow !== undefined) {
  // @ts-ignore
  globalThis.RemoteWindow.attributeModifier = function (modifier: ArkComponent): void: void {
    attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
      return new ArkRemoteWindowComponent(nativePtr);
    }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
      return new modifierJS.CommonModifier(nativePtr, classType);
    });
  };
}