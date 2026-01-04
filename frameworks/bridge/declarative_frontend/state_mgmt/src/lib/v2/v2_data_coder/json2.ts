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
 */

class JSON2 {
  /**
   * JSON-like stringify with refs, cycles, and special types (Map, Set, Date, etc.)
   */
  static stringify<T>(value: T): string {
    // visited objects along with their assigned refIDs
    const visited = new Map<object, string>();

    const serialize = (value: unknown): string => {
      const root = value;
      return JSON.stringify(value, function(key: string, value: unknown) {
        return replace.call(this, key, value, root);
      });
    };

    const serializeSendable = (value: unknown): string => {
      // Sendables can only be deserialized via JSON.parseSendable, which skips the
      // reviver, so encoding types and using Meta aliases is useless.
      JSON2.throwIfNotJSONSafe(value);
      return (JSON as any).stringifySendable(value);
    };

    const replace = function (key: string, val: any, root: any): any {
      // don't trust JSON replacer's arg 'val' (it turns Date objects into strings)
      const value = this[key];

      if (typeof value === 'string') { return `st????${value}`; }
      if (typeof value === 'bigint') { return `bi????${value.toString()}`; }
      if (typeof value === 'undefined') { return `re????`; }
      if (typeof value !== 'object' || value === null) {
        return value;
      }

      let refId = visited.get(value);
      if (refId) {
        return `re${refId}`;
      }

      refId = visited.size.toString(32).padStart(4, '0');
      visited.set(value, refId);

      if (value instanceof Boolean) { return `Bo${refId}${value.toString()}`; }
      if (value instanceof Date) { return `Da${refId}${value.toISOString()}`; }
      if (value instanceof Number) { return `Nu${refId}${value.toString()}`; }
      if (value instanceof String) { return `St${refId}${value}`; }
      if (value instanceof Map) { return `Ma${refId}${serialize([...value])}`; }
      if (value instanceof Set) { return `Se${refId}${serialize([...value])}`; }
      if (value instanceof SendableArray) { return `SA${refId}${serializeSendable([...value])}`; }
      if (value instanceof SendableMap) { return `SM${refId}${serializeSendable([...value])}`; }
      if (value instanceof SendableSet) { return `SS${refId}${serializeSendable([...value])}`; }
      if (globalThis.isSendable(value)) { return `SO${refId}${serializeSendable(value)}`; }

      if (value instanceof Array) {
        // serialize each item, then put them back together
        const items = value.map(item => JSON.parse(serialize(item)));
        // and stringify
        return `Ar${refId}${JSON.stringify(items)}`;
      }

      // replace property names with their aliases if any, skip disabled ones
      const aliased = JSON2.toAliasedObject(value);

      // skip root to prevent recursion
      if (root === value) {
        return aliased;
      }

      return `Ob${refId}${serialize(aliased)}`;
    }

    // wrap value to ensure the root is always a regular object
    const ret =  serialize({ $: value });
    return ret;
  }

  /**
   * JSON-like parse, restores types and circular referenses
   */
  static parse(text: string): any {
    const objects = new Map<string, object>();
    const visited = new Set<object>();

    const resolveRefs = (obj: any): unknown => {
      JSON2.forEach(obj as object, (value, key) => {
        if (typeof value === 'object' && visited.has(value as object)) {
          return;
        }

        if (typeof value === 'object') {
          visited.add(value as object);
          resolveRefs(value);
          return;
        }

        if (typeof value !== 'string') { return; }
        const { type, refId, payload } = JSON2.parseTRP(value);

        if (type === 're') {
          if (obj instanceof Array || obj instanceof SendableArray) {
            obj[key] = objects.get(refId);
            return;
          }
          if (obj instanceof Map || obj instanceof SendableMap) {
            obj.set(key, objects.get(refId));
            return;
          }
          if (obj instanceof Set || obj instanceof SendableSet) {
            obj.add(objects.get(refId));
            return;
          }
          obj[key] = objects.get(refId);
        }

        if (type === 'st') {
          obj[key] = payload;
          return;
        }

      })

      return obj;
    }

    // parse main structure, gathering objects
    let root = JSON2.parseStructure(text, objects);
    // then resolve all references
    return resolveRefs((root as any).$);
  }

  // Convert object properties to their aliased names according to Meta, skip disabled ones
  static toAliasedObject<T extends object>(value: T): T {
    const meta: any = Meta.gets(value);
    const result: any = {};

    Object.keys(value).forEach(key => {
      const baseKey = key.replace(new RegExp('^' + V2_STATE_PREFIX), '');
      const options = meta?.[baseKey];
      if (options?.disabled) { return; }
      result[options?.alias || baseKey] = (value as Record<string, unknown>)[baseKey];
    });
    return result;
  }

  // Parse JSON string with special types, gathering objects and their refIDs
  static parseStructure(text: string, objects: Map<string, object>): unknown {
    const parse = (str: string): any =>
      JSON.parse(str, reviver)

    const parseSendable = (str: string): any =>
      // reviver is not supported by parseSendable()
      (JSON as any)?.parseSendable(str)?? ''

    const reviver = function(key: string, value: unknown): any {
      const { type, refId, payload } = JSON2.parseTRP(value as string);

      let result = value;
      if (type === 'Da') { result = new Date(payload); }
      if (type === 'Bo') { result = new Boolean(parse(payload)); }
      if (type === 'Nu') { result = new Number(payload); }
      if (type === 'St') { result = new String(payload); }
      if (type === 'Ar') { result = parse(payload); }
      if (type === 'Ma') { result = new Map(parse(payload)); }
      if (type === 'Se') { result = new Set(parse(payload)); }
      if (type === 'SO') { result = parseSendable(payload); }
      if (type === 'SA') { result = new SendableArray(...parseSendable(payload)); }
      if (type === 'SM') { result = new SendableMap(parseSendable(payload)); }
      if (type === 'SS') { result = new SendableSet(parseSendable(payload)); }
      if (type === 'Ob') { result = parse(payload); }
      if (type === 'bi') { result = BigInt(payload); }

      // don't process 're' (references) and 'st' (plain strings) here
      // we return them as-is, and process them after parsing the full structure

      if (typeof result === 'object') {
        objects.set(refId!, result);
      }

      return result;
    }

    return parse(text);
  }

  // Parse <typetag, refId, payload> from string
  static parseTRP(str: string): { type?: string, refId?: string, payload?: string } {
    if (!str || str.length < 6) {
      return {};
    }
    const t = str?.slice?.(0, 2);
    const r = str?.slice?.(2, 6);
    const p = str?.slice?.(6);
    return { type: t, refId: r, payload: p };
  }

  // Iterate any collection, callback(value, key)
  static forEach(col: object, callback: (val: unknown, key: string|number) => void): void {
    if (col instanceof Array) {
      for (const [key, val] of col.entries()) {
        callback(val, key);
      }
    }

    if (col instanceof Map) {
      for (const [key, val] of col.entries()) { 
        callback(val, key);
      }
    }

    if (col instanceof Set) {
      for (const val of col) { 
        callback(val, val);
      }
    }

    if (col instanceof SendableArray) {
      for (const [key, val] of col.entries()) { 
        callback(val, key);
      }
    }

    if (col instanceof SendableMap) {
      for (const [key, val] of col) { 
        callback(val, key);
      }
    }

    if (col instanceof SendableSet) {
      for (const val of col) { 
        callback(val, val);
      }
    }

    if (col instanceof Object) {
      for (const [key, val] of Object.entries(col)) { 
        callback(val, key);
      }
    }
  }

  // Ensure value contains only JSON safe props
  private static throwIfNotJSONSafe(value: unknown): void {
    // allow plain types
    if (typeof value !== 'object' || value === null) {
      return;
    }

    // allow collections
    if ([Array, Map, Set, SendableArray, SendableMap, SendableSet].some(clazz => value instanceof clazz)) {
      return;
    }

    for (const [key, val] of Object.entries(value)) {
      if (typeof val === 'object' && val !== null) {
        throw new BusinessError(PERSISTENCE_V2_APPSTORAGE_V2_UNSUPPORTED_TYPE, `Not supported type! PersistenceV2: @Sendable only allows plain property types. Invalid key: ${key}`);
      }
    }
  }

}
