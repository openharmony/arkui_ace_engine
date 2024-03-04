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
function applyAndMergeModifier(instance, modifier) {
  let myMap = modifier._modifiersWithKeys;
  myMap.setOnChange(() => {
    modifier._changed = !modifier._changed;
  });
  // @ts-ignore
  let component = instance;
  mergeMaps(component._modifiersWithKeys, modifier._modifiersWithKeys);
}
function copyModifierWithKey(obj) {
  let newObj = { ...obj };
  newObj.applyStage = obj === null || obj === void 0 ? void 0 : obj.applyStage;
  newObj.applyPeer = obj === null || obj === void 0 ? void 0 : obj.applyPeer;
  newObj.checkObjectDiff = obj === null || obj === void 0 ? void 0 : obj.checkObjectDiff;
  return newObj;
}
function mergeMaps(stageMap, newMap) {
  newMap.forEach((value, key) => {
    stageMap.set(key, copyModifierWithKey(value));
  });
  return stageMap;
}
class ModifierMap {
  constructor() {
    this.map_ = new Map();
  }
  clear() {
    this.map_.clear();
  }
  delete(key) {
    return this.map_.delete(key);
  }
  forEach(callbackfn, thisArg) {
    this.map_.forEach(callbackfn, thisArg);
  }
  get(key) {
    return this.map_.get(key);
  }
  has(key) {
    return this.map_.has(key);
  }
  set(key, value) {
    const _a = this.changeCallback;
    this.map_.set(key, value);
    _a === null || _a === void 0 ? void 0 : _a.call(this);
    return this;
  }
  get size() {
    return this.map_.size;
  }
  entries() {
    return this.map_.entries();
  }
  keys() {
    return this.map_.keys();
  }
  values() {
    return this.map_.values();
  }
  [Symbol.iterator]() {
    return this.map_.entries();
  }
  get [Symbol.toStringTag]() {
    return 'ModifierMapTag';
  }
  setOnChange(callback) {
    if (this.changeCallback === undefined) {
      this.changeCallback = callback;
    }
  }
}
class CommonModifier extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class ButtonModifier extends ArkButtonComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class ImageModifier extends ArkImageComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class ListModifier extends ArkListComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class ListItemModifier extends ArkListItemComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class ListItemGroupModifier extends ArkListItemGroupComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class ScrollModifier extends ArkScrollComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class TextModifier extends ArkTextComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}

export default { CommonModifier, ButtonModifier, ImageModifier, ListModifier, ListItemModifier, ListItemGroupModifier, ScrollModifier, TextModifier }