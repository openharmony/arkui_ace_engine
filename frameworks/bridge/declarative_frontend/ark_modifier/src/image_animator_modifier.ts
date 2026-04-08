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

function copyImageAnimatorModifierWithKey(obj) {
  let _a;
  let _b;
  let newObj = { ...obj };
  if (obj.convertImageFrames !== undefined) {
    newObj.convertImageFrames = (_a = obj) === null || _a === void 0 ? void 0 : _a.convertImageFrames;
    newObj.isEqual = (_b = obj) === null || _b === void 0 ? void 0 : _b.isEqual;
  }
  newObj.applyStage = obj === null || obj === void 0 ? void 0 : obj.applyStage;
  newObj.applyPeer = obj === null || obj === void 0 ? void 0 : obj.applyPeer;
  newObj.checkObjectDiff = obj === null || obj === void 0 ? void 0 : obj.checkObjectDiff;
  return newObj;
}

function mergeImageAnimatorMaps(stageMap: Map<Symbol, AttributeModifierWithKey>,
  newMap: Map<Symbol, AttributeModifierWithKey>): Map<Symbol, AttributeModifierWithKey> {
  newMap.forEach((value, key) => {
    stageMap.set(key, copyImageAnimatorModifierWithKey(value));
  });

  return stageMap;
}
class ImageAnimatorModifier extends ArkImageAnimatorComponent implements AttributeModifier<ImageAnimatorAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }

  applyNormalAttribute(instance: ImageAnimatorAttribute): void {
    ModifierUtils.applySetOnChange(this);
    // @ts-ignore
    let component: ArkComponent = instance as ArkComponent;
    mergeImageAnimatorMaps(component._modifiersWithKeys, this._modifiersWithKeys);
  }
}
