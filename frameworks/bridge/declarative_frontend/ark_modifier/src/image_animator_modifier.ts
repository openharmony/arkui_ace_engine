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

/// <reference path='./import.ts' />

function copyImageAnimatorModifierWithKey(obj: ModifierWithKey<string | number | boolean | object> | ImageAnimatorImagesModifier):
  ModifierWithKey<string | number | boolean | object> {

  let newObj: ModifierWithKey<string | number | boolean | object> | ImageAnimatorImagesModifier = {
    ...obj,
    applyStage: function (node: number): boolean {
      throw new Error('Function not implemented.');
    },
    applyPeer: function (node: number, reset: boolean): void {
      throw new Error('Function not implemented.');
    },
    checkObjectDiff: function (): boolean {
      throw new Error('Function not implemented.');
    },
  };

  if ((obj as ImageAnimatorImagesModifier)!.convertImageFrames !== undefined) {
    (newObj as ImageAnimatorImagesModifier).convertImageFrames = (obj as ImageAnimatorImagesModifier)?.convertImageFrames;
    (newObj as ImageAnimatorImagesModifier).isEqual = (obj as ImageAnimatorImagesModifier)?.isEqual;
  }

  newObj.applyStage = obj?.applyStage;
  newObj.applyPeer = obj?.applyPeer;
  newObj.checkObjectDiff = obj?.checkObjectDiff;
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
