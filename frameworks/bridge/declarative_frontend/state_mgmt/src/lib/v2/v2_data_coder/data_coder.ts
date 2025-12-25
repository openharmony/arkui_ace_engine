/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 *
 */

function nullOrUndef(value: unknown): boolean {
  return value === null || value === undefined;
}

class DataCoder {
  // Tag to detect payload format
  public static readonly FORMAT_TAG = 'JSON2';

  // Track visited objects to prevent recursion in restoreObject()
  private static visited_ = new Set<string>();

  /**
   * Serialize an object to a JSON2
   */
  public static stringify<T>(value: T): string {
    return this.FORMAT_TAG + JSON2.stringify(value);
  }

  /**
   * Parse a JSON2/JSON string to an object
   */
  public static parse<T extends object>(text: string): T | T[] {
    return text.startsWith(this.FORMAT_TAG)
      ? JSON2.parse(text.slice(this.FORMAT_TAG.length))
      : JSON.parse(text); // fallback to legacy format;
  }

  /**
   * Restore the state of 'source' object into 'target' object(s), restore aliased prop names
   */
  public static restoreTo<T extends object, S extends object>(
    target: T | T[], source: T | T[], defaultSubCreator?: StorageDefaultCreator<S>
  ): T | T[] {
    const origTarget = ObserveV2.IsMakeObserved(target)
      ? UIUtilsImpl.instance().getTarget(target)
      : target;

    let factory: FactoryConstructor<S> | undefined = undefined;

    if (defaultSubCreator) {
      factory = (_: object): TypeConstructor<S> => {
        return class {
          constructor() {
            return defaultSubCreator();
          }
        } as TypeConstructor<S>;
      };
    }

    try {
      const dst = { root: origTarget };
      const src = { root: source };
      this.restorePropValue(dst, 'root', src, 'root', { factory });
    } finally {
      this.visited_.clear();
    }

    // Regular or @ObservedV2 target, return as-is
    if (!ObserveV2.IsMakeObserved(target)) {
      return target;
    }

    // Touch the makeObserved collection items so its getter records dependencies
    if ([Array, Map, Set, SendableArray, SendableMap, SendableSet].some(clazz => target instanceof clazz)) {
      (target as any)?.forEach?.(() => {});
    }

    // Touch the makeObserved Object props to record dependencies
    if (typeof target === 'object' && target != null) {
      Object.entries(target).forEach(() => {});
    }

    // Touch the makeObserved Date so its getter records dependencies
    if (target instanceof Date) {
      target.getTime();
    }

    return target;
  }

  // Recursively restore object 'source' into 'target' considering TransformOptions
  // opts = { alias?, factory?, disabled? }
  private static restoreObject(target: any, source: any, opts: TransformOptions<any>): void {
    // meta = { [prop]: { alias, factory, disabled } }
    const meta = Meta.gets(target) as Record<string, TransformOptions<any>>;

    // reversed map of meta = { [alias]: prop }
    const alias2prop = new Map<string, string>(
      Object.entries(meta).map(([prop, opts]) => [opts.alias ?? prop, prop])
    );

    // clone or copy an array/map/set item value
    const cloneOrCopy = (value: any): any => {
      if (typeof value !== 'object') {
        return value;
      }

      if (opts?.factory === undefined) {
        return value;
      }

      const type = opts.factory(value);
      const newValue = type ? new type() : value;

      // don't allow collections as items of a collection
      this.throwIfCollection(newValue);

      this.restoreObject(newValue, value, opts);
      return newValue;
    };

    // ignore already visited
    if (typeof target === 'object' && target != null) {
      if (this.visited_.has(target)) {
        return;
      }
      this.visited_.add(target);
    }

    if (source instanceof Array) {
      this.throwIfNotInstanceOf(target, Array);
      target.length = source.length;
      source.forEach((item, idx) => { target[idx] = cloneOrCopy(item); });
      return;
    }

    if (source instanceof Set) {
      this.throwIfNotInstanceOf(target, Set);
      target.clear();
      source.forEach(item => { target.add(cloneOrCopy(item)); });
      return;
    }

    if (source instanceof Map) {
      this.throwIfNotInstanceOf(target, Map);
      target.clear();
      source.forEach((item, key) => { target.set(key, cloneOrCopy(item)); });
      return;
    }

    // collections.Array
    if (source instanceof SendableArray) {
      this.throwIfNotInstanceOf(target, SendableArray);
      const items = [...source].map(cloneOrCopy);
      target.splice(0, target.length, ...items);
      return;
    }

    // collections.Map
    if (source instanceof SendableMap) {
      this.throwIfNotInstanceOf(target, SendableMap);
      target.clear();
      for (let [key, item] of source) { target.set(key, cloneOrCopy(item)); }
      return;
    }

    // collections.Set
    if (source instanceof SendableSet) {
      this.throwIfNotInstanceOf(target, SendableSet);
      target.clear();
      for (let item of source) { target.add(cloneOrCopy(item)); }
      return;
    }

    // restore target properties from source (incl. undefined)
    if (source && typeof source === 'object') {
      for (const [key, val] of Object.entries(source)) {
        const targetProp = alias2prop.get(key) ?? key;
        const sourceProp = meta[targetProp]?.alias ?? targetProp;
        const propOptions = meta[targetProp] || {};
        this.restorePropValue(target, targetProp, source, sourceProp, propOptions);
      }
    }
  }

  // Restore an property value from 'source' to 'target' considering TransformOptions
  // opts = { alias, factory, disabled }
  private static restorePropValue(
    target: any, targetProp: string, source: any, sourceProp: string, opts: TransformOptions<any> = {}
  ): void {
    const srcVal = source[sourceProp];
    const tgtVal = target[targetProp];

    if (opts.disabled) {
      return;
    }

    if (typeof tgtVal === 'function') {
      return;
    }

    if (['string','number','boolean','bigint'].includes(typeof srcVal)) {
      target[targetProp] = srcVal;
      return;
    }

    // try to restore the Date without replacing the existing instance
    if (srcVal instanceof Date && tgtVal instanceof Date) {
      target[targetProp].setTime(srcVal.getTime())
      return;
    }

    if ([Boolean, Date, Number, String].includes(srcVal?.constructor)) {
      target[targetProp] = srcVal;
      return;
    }

    if ([Array, Map, Set, SendableArray, SendableMap, SendableSet].includes(srcVal?.constructor)) {
      this.restoreObject(tgtVal, srcVal, opts);
      return;
    }

    if (!nullOrUndef(srcVal) && globalThis.isSendable(srcVal)) {
      this.throwIfNotSendable(tgtVal);
      target[targetProp] = srcVal;
      return;
    }

    if (nullOrUndef(srcVal) && tgtVal instanceof Array) {
      target[targetProp].length = 0;
      return;
    }

    if (nullOrUndef(srcVal) && tgtVal instanceof Map) {
      target[targetProp].clear();
      return;
    }

    if (nullOrUndef(srcVal) && tgtVal instanceof Set) {
      target[targetProp].clear();
      return;
    }

    if (nullOrUndef(srcVal)) {
      target[targetProp] = srcVal;
      return;
    }

    if (nullOrUndef(tgtVal) && opts.factory) {
      const type = opts.factory(srcVal);
      target[targetProp] = type ? new type() : {};
      this.restoreObject(target[targetProp], srcVal, {});
      return;
    }

    if (tgtVal === undefined) {
      target[targetProp] = srcVal;
      return;
    }

    if (tgtVal === null) {
      this.throwNoFactory(targetProp);
    }

    if (tgtVal.constructor !== srcVal.constructor && opts.factory !== undefined) {
      const type = opts.factory(srcVal)
      target[targetProp] = type ? new type() : {};
      this.restoreObject(target[targetProp], srcVal, {});
      return;
    }

    this.restoreObject(tgtVal, srcVal, opts);
  }

  // Ensure target is instanceof the clazz
  private static throwIfNotInstanceOf(target: unknown, clazz: new (...args: unknown[]) => unknown): void {
    if (target instanceof clazz === false) {
      const type = target?.constructor?.name ?? typeof target;
      throw new Error(`The class of target (${type}) mismatches '${clazz.name}'`);
    }
  }

  // Ensure target has given type
  private static throwIfNotTypeOf(target: unknown, type: string): void {
    if (typeof target !== type) {
      throw new Error(`The type of target ('${typeof target}') mismatches '${type}'`);
    }
  }

  // Ensure target is Sendable
  private static throwIfNotSendable(target: unknown): void {
    if (target != null && globalThis.isSendable(target) === false) {
      const type = target.constructor?.name ?? typeof target
      throw new Error(`The target (${type}) is not @Sendable`);
    }
  }

  // Ensure value is not collection
  private static throwIfCollection(value: unknown): void {
    if ([Array, Map, Set, SendableArray, SendableMap, SendableSet].some(clazz => value instanceof clazz)) {
      throw new Error(`Array, Map, Set, or collections.Array/Map/Set cannot be used as collection items`);
    }
  }

  private static throwNoFactory<T>(targetProp: string): void {
    throw new Error(`Miss @Type in object defined, the property name is ${targetProp}`);
  }

}

