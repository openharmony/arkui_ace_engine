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

function applyAndMergeModifier<T, M extends ArkComponent, C extends ArkComponent>(instance: T, modifier: M) {
  let myMap = modifier._modifiersWithKeys as ModifierMap;
  myMap.setOnChange(() => {
    modifier._changed = !modifier._changed;
  });

  // @ts-ignore
  let component: C = instance as C;
  mergeMaps(component._modifiersWithKeys, modifier._modifiersWithKeys);
}

function copyModifierWithKey(obj: ModifierWithKey<string | number | boolean | object>): ModifierWithKey<string | number | boolean | object> {
  let newObj: ModifierWithKey<string | number | boolean | object> = {
    ...obj,
    applyStage: function (node: number): boolean {
      throw new Error('Function not implemented.');
    },
    applyPeer: function (node: number, reset: boolean): void {
      throw new Error('Function not implemented.');
    },
    checkObjectDiff: function (): boolean {
      throw new Error('Function not implemented.');
    }
  };
  newObj.applyStage = obj?.applyStage;
  newObj.applyPeer = obj?.applyPeer;
  newObj.checkObjectDiff = obj?.checkObjectDiff;
  return newObj;
}

function mergeMaps(stageMap: Map<Symbol, ModifierWithKey<number | string | boolean | object>>,
  newMap: Map<Symbol, ModifierWithKey<number | string | boolean | object>>) {
  newMap.forEach((value, key) => {
    stageMap.set(key, copyModifierWithKey(value));
  });

  return stageMap;
}

class ModifierMap {
  private map_: Map<Symbol, ModifierWithKey<number | string | boolean | object>>;
  private changeCallback: (() => void) | undefined

  constructor() {
    this.map_ = new Map();
  }

  public clear(): void {
    this.map_.clear();
  }

  public delete(key: Symbol): boolean {
    return this.map_.delete(key);
  }

  public forEach(callbackfn: (value: ModifierWithKey<number | string | boolean | object>, key: Symbol, map: Map<Symbol, ModifierWithKey<number | string | boolean | object>>) => void, thisArg?: any): void {
    this.map_.forEach(callbackfn, thisArg);
  }
  public get(key: Symbol): ModifierWithKey<number | string | boolean | object> | undefined {
    return this.map_.get(key);
  }
  public has(key: Symbol): boolean {
    return this.map_.has(key);
  }
  public set(key: Symbol, value: ModifierWithKey<number | string | boolean | object>): this {
    const _a = this.changeCallback;
    this.map_.set(key, value);
    _a?.call(this);
    return this;
  }
  public get size(): number {
    return this.map_.size;
  }
  public entries(): IterableIterator<[Symbol, ModifierWithKey<number | string | boolean | object>]> {
    return this.map_.entries();
  }
  public keys(): IterableIterator<Symbol> {
    return this.map_.keys();
  }
  public values(): IterableIterator<ModifierWithKey<number | string | boolean | object>> {
    return this.map_.values();
  }
  public [Symbol.iterator](): IterableIterator<[Symbol, ModifierWithKey<number | string | boolean | object>]> {
    return this.map_.entries();
  }
  public get [Symbol.toStringTag](): string {
    return 'ModifierMapTag';
  }
  public setOnChange(callback: () => void): void {
    if (this.changeCallback === undefined) {
      this.changeCallback = callback;
    }
  }
}