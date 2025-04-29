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

const overrideMap = new Map<string, Map<string,
  new (value: string | number | boolean | object) => ModifierWithKey<string | number | boolean | object>>>();


overrideMap.set('ArkCheckboxComponent', new Map([
  ['Symbol(width)', CheckboxWidthModifier],
  ['Symbol(height)', CheckboxHeightModifier]
]));

overrideMap.set('ArkTextComponent', new Map([
  ['Symbol(foregroundColor)', TextForegroundColorModifier]
]));

function applyAndMergeModifier<T, M extends ArkComponent, C extends ArkComponent>(instance: T, modifier: M): void {
  let myMap = modifier._modifiersWithKeys as ModifierMap;
  myMap.setOnChange((key: Symbol, value: AttributeModifierWithKey) => {
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

function mergeMaps(stageMap: Map<Symbol, AttributeModifierWithKey>,
  newMap: Map<Symbol, AttributeModifierWithKey>): Map<Symbol, AttributeModifierWithKey> {
  newMap.forEach((value, key) => {
    stageMap.set(key, copyModifierWithKey(value));
  });

  return stageMap;
}

class ModifierUtils {
  static dirtyComponentSet: Set<ArkComponent | ArkSpanComponent> = new Set();
  static dirtyFlag = false;
  static timeoutId = -1;

  static copyModifierWithKey(obj: ModifierWithKey<string | number | boolean | object>): ModifierWithKey<string | number | boolean | object> {
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

  static mergeMaps(stageMap: Map<Symbol, AttributeModifierWithKey>,
    newMap: Map<Symbol, AttributeModifierWithKey>): void {
    newMap.forEach((value, key) => {
      stageMap.set(key, this.copyModifierWithKey(value));
    });
  }

  static mergeMapsEmplace<T0 extends string | number | boolean | object, M0 extends ModifierWithKey<T0>>(
    stageMap: Map<Symbol, AttributeModifierWithKey>,
    newMap: Map<Symbol, AttributeModifierWithKey>,
    componentOverrideMap: Map<string, new (value: T0) => M0>): void {
      newMap.forEach((value, key) => {
        if (!key) {
          ArkLogConsole.info('key of modifier map is undefined, ModifierWithKey is ' +
            (value ? value.constructor.name.toString() : 'undefined'));
        } else {
          if (componentOverrideMap.has(key.toString())) {
            //@ts-ignore
            const newValue = new (componentOverrideMap.get(key.toString()))(value.stageValue);
            stageMap.set(key, newValue);
          } else {
            stageMap.set(key, this.copyModifierWithKey(value));
          }
        }
      });
  }

  static applyAndMergeModifier<T, M extends ArkComponent | ArkSpanComponent, C extends ArkComponent | ArkSpanComponent>(instance: T, modifier: M): void {
    // @ts-ignore
    let component: C = instance as C;
    if (component.constructor.name && overrideMap.has(component.constructor.name)) {
      const componentOverrideMap = overrideMap.get(component.constructor.name);
      this.mergeMapsEmplace(component._modifiersWithKeys, modifier._modifiersWithKeys,
        componentOverrideMap);
    } else {
      this.mergeMaps(component._modifiersWithKeys, modifier._modifiersWithKeys);
    }
  }

  static applySetOnChange<T, M extends ArkComponent | ArkSpanComponent, C extends ArkComponent | ArkSpanComponent>(modifier: M): void {
    // It is to make the stateMgmt can addRef of _changed,
    // so that the modifier change can be observed by makeObserved when modifier._changed changed.
    modifier._changed;
    let myMap = modifier._modifiersWithKeys as ModifierMap;
    if (modifier._classType === ModifierType.STATE) {
      myMap.setOnChange((key: Symbol, value: AttributeModifierWithKey) => {
        this.putDirtyModifier(modifier, value);
      });
    } else {
      myMap.setOnChange((key: Symbol, value: AttributeModifierWithKey) => {
        modifier._changed = !modifier._changed;
      });
    }
  }

  static putDirtyModifier<M extends ArkComponent | ArkSpanComponent>(
    arkModifier: M, attributeModifierWithKey: ModifierWithKey<string | number | boolean | object>): void {
    attributeModifierWithKey.value = attributeModifierWithKey.stageValue;
    if (!arkModifier._weakPtr.invalid()) {
      attributeModifierWithKey.applyPeer(arkModifier.nativePtr,
        (attributeModifierWithKey.value === undefined || attributeModifierWithKey.value === null));
    } else {
      ArkLogConsole.info('pointer is invalid when putDirtyModifier in ' + (arkModifier ?
        arkModifier.constructor.name.toString() : 'undefined') + ' of ' + (attributeModifierWithKey ?
        attributeModifierWithKey.constructor.name.toString() : 'undefined'));
    }
    this.dirtyComponentSet.add(arkModifier);
    if (!this.dirtyFlag) {
      this.dirtyFlag = true;
      this.requestFrame();
    }
  }

  static requestFrame(): void {
    const frameCallback = () => {
      if (this.timeoutId !== -1) {
        clearTimeout(this.timeoutId);
      }
      this.dirtyComponentSet.forEach(item => {
        const nativePtrValid = !item._weakPtr.invalid();
        if (item._nativePtrChanged && nativePtrValid) {
          item._modifiersWithKeys.forEach((value, key) => {
            value.applyPeer(item.nativePtr,
              (value.value === undefined || value.value === null));
          });
          item._nativePtrChanged = false;
        }
        if (nativePtrValid) {
          getUINativeModule().frameNode.markDirty(item.nativePtr, 0b100);
        }
      });
      this.dirtyComponentSet.clear();
      this.dirtyFlag = false;
      this.timeoutId = -1;
    };
    if (this.timeoutId !== -1) {
      clearTimeout(this.timeoutId);
    }
    this.timeoutId = setTimeout(frameCallback, 100);
    getUINativeModule().frameNode.registerFrameCallback(frameCallback);
  }
}

class ModifierMap {
  private map_: Map<Symbol, AttributeModifierWithKey>;
  private changeCallback: ((key: Symbol, value: AttributeModifierWithKey) => void) | undefined;

  constructor() {
    this.map_ = new Map();
  }

  public clear(): void {
    this.map_.clear();
  }

  public delete(key: Symbol): boolean {
    return this.map_.delete(key);
  }

  public forEach(callbackfn: (value: AttributeModifierWithKey, key: Symbol, 
    map: Map<Symbol, AttributeModifierWithKey>) => void, thisArg?: any): void {
    this.map_.forEach(callbackfn, thisArg);
  }
  public get(key: Symbol): AttributeModifierWithKey | undefined {
    return this.map_.get(key);
  }
  public has(key: Symbol): boolean {
    return this.map_.has(key);
  }
  public set(key: Symbol, value: AttributeModifierWithKey): this {
    const _a = this.changeCallback;
    this.map_.set(key, value);
    _a?.call(this, value);
    return this;
  }
  public get size(): number {
    return this.map_.size;
  }
  public entries(): IterableIterator<[Symbol, AttributeModifierWithKey]> {
    return this.map_.entries();
  }
  public keys(): IterableIterator<Symbol> {
    return this.map_.keys();
  }
  public values(): IterableIterator<AttributeModifierWithKey> {
    return this.map_.values();
  }
  public [Symbol.iterator](): IterableIterator<[Symbol, AttributeModifierWithKey]> {
    return this.map_.entries();
  }
  public get [Symbol.toStringTag](): string {
    return 'ModifierMapTag';
  }
  public setOnChange(callback: (key: Symbol, value: AttributeModifierWithKey) => void): void {
    this.changeCallback = callback;
  }
}

class AttributeUpdater {
  private _state: number;
  private _attribute: ArkComponent;
  private _isAttributeUpdater: boolean;

  static StateEnum = {
    INIT: 0,
    UPDATE: 1
  };

  constructor() {
    this._state = AttributeUpdater.StateEnum.INIT;
    this._attribute = null;
    this._isAttributeUpdater = true;
  }

  public get isAttributeUpdater(): boolean {
    return this._isAttributeUpdater;
  }

  public get attribute(): ArkComponent {
    return this._attribute;
  }

  public set attribute(value: ArkComponent) {
    if (!this._attribute && value) {
      this._attribute = value;
    }
  }

  public get modifierState(): number {
    return this._state;
  }

  public set modifierState(value: number) {
    this._state = value;
  }

  initializeModifier(instance: ArkComponent): void {}

  updateConstructorParams(...args: Object[]): void {
    if (!this.attribute) {
      ArkLogConsole.info('AttributeUpdater has not been initialized before updateConstructorParams.');
      return;
    }
    this.attribute.initialize(args);
  }
}