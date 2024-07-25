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

type TypeConstructor<T> = { new(): T };
type FactoryConstructor<T> = (json: object) => TypeConstructor<T>;
type JSONAny = object | number | string | boolean | undefined | null;

const V2_STATE_PREFIX = '__ob_';
const V2_PREFIX_LENGTH = V2_STATE_PREFIX.length;

interface TransformOptions<T> {
  factory?: FactoryConstructor<T>;
  alias?: string;
  disabled?: boolean;
};

class Meta {
  private static proto2props: WeakMap<object, object> = new WeakMap();

  public static define(proto: object, prop: string, value: any) {
    const meta = Meta.proto2props.get(proto);
    if (!meta) {
      Meta.proto2props.set(proto, { [prop]: value });
    } else {
      meta[prop] = value;
    }
  }

  public static get(obj: any, prop: string): any {
    let proto = obj.__proto__;
    while (proto) {
      let meta = Meta.proto2props.get(proto);
      if (meta && meta[prop]) {
        return meta[prop];
      }
      proto = proto.__proto__;
    }
    return undefined;
  }

  public static gets(obj: any): object {
    const ret = {};
    let proto = obj.__proto__;
    while (proto) {
      let meta = Meta.proto2props.get(proto);
      Object.assign(ret, meta);
      proto = proto.__proto__;
    }
    return ret;
  }

  public static getOwn(obj: any, prop: string): any {
    const meta = Meta.proto2props.get(obj.__proto__);
    return meta && meta[prop];
  }
}

function __Type__<T>(type: TypeConstructor<T> | TransformOptions<T> | string, alias?: string) {
  const options: TransformOptions<T> = JSONCoder.getOptions(type);

  if (alias) {
    options.alias = alias;
  }

  return (target: any, prop: string) => {
    const tar = typeof target === 'function' ? target.prototype : target;
    Meta.define(tar, prop, options);
  };
}

function ObservedReplacer(replacer: any) {
  const defaultReplacer = function (key: string, value: any) {
    return value;
  }

  const realReplacer = replacer || defaultReplacer;
  return function (this: any, key: string, value: any) {
    if (typeof value !== 'object' || Array.isArray(value)) {
      return realReplacer.call(this, key, value);
    }
    if (value instanceof Set) {
      return realReplacer.call(this, key, Array.from(value));
    }
    if (value instanceof Map) {
      return realReplacer.call(this, key, Array.from(value.entries()));
    }

    const ret: any = {};
    const meta = Meta.gets(value);
    Object.keys(value).forEach(key => {
      let saveKey = key.startsWith(V2_STATE_PREFIX) ? key.substring(V2_PREFIX_LENGTH) : key;
      let options = meta && meta[saveKey];
      if (options && options.disabled) {
        return;
      }
      ret[(options && options.alias) || saveKey] = value[saveKey];
    });
    return realReplacer.call(this, key, ret);
  }
}

/**
 * JSONCoder
 *
 * The JSONCoder utility enhances the serialization and deserialization capabilities beyond
 * the standard JSON.stringify and JSON.parse methods. While JSON.stringify serializes
 * object properties and their values, it drops functions, class, property, and function decorators,
 * and does not support Map, Set, or Date serialization. JSONCoder addresses these limitations,
 * providing robust support for a wider range of JavaScript features.
 *
 * Main Features:
 * - Adds support for serializing and deserializing class instances, including methods and decorators.
 * - Supports serialization of complex data structures like Map, Set, and Date.
 * - Provides full reconstruction of class instances through the JSONCoder.parseTo method.
 *
 * Usage Scenarios:
 * - Serializing class instances to JSON for network transmission or storage.
 * - Deserializing JSON data back into fully functional class instances, preserving methods and decorators.
 * - Converting JSON data received from network or database into state management observable view models (e.g., @ObservedV2 class objects).
 *
 * The name 'JSONCoder' is derived from the 'JSON stringify/parse', reflecting its purpose to enhance JSON serialization and deserialization for classes.
 *
 */
class JSONCoder {
  /**
   * Serializes the given object into a string. This string includes additional meta info
   * allowing `stringify` to fully reconstruct the original object, including its class
   * type and properties.
   *
   * @template T - The type of the object being serialized.
   * @param { T } value - The object to serialize.
   * @param { (this: JSONAny, key: string, value: JSONAny) => JSONAny } [replacer] - A function that alters the behavior when stringify
   * @param { string | number } [space] - For format
   * @returns { string } The serialized string representation of the object.
   */
  public static stringify<T>(value: T, replacer?: (this: JSONAny, key: string, value: JSONAny) => JSONAny,
    space?: string | number): string {
    return JSON.stringify(value, ObservedReplacer(replacer), space);
  }

  /**
   * Parses a JSON string or object and applies the nested key-values to a class object.
   * The main usage scenario is to convert JSON data received from a network or database
   * to a state management observable view model.
   *
   * @template T - The type of the object being parsed.
   * @param { TypeConstructor<T> | TransformOptions<T> } type - The class prototype or constructor function that has no parameters.
   * @param { object | string } source - The JSON string or JSON object.
   * @returns { T | T[] } The parsed object of type T or T[].
   */
  public static parse<T extends object>(type: TypeConstructor<T> | TransformOptions<T>, source: object | string): T | T[] {
    const json = typeof source === 'string' ? JSON.parse(source) : source;
    const options: TransformOptions<T> = JSONCoder.getOptions(type);
    return Array.isArray(json) ?
      JSONCoder.parseIntoArray([], json, options) :
      JSONCoder.parseInto(JSONCoder.newItem(json, options), json);
  }

  /**
   * Deserializes a string produced by `parseTo` back into the original object,
   * fully reconstructing its class type and properties.
   *
   * @template T - The original object being parsed.
   * @param { T | T[] } type - The original object.
   * @param { object | string } source - The JSON string or JSON object.
   * @param { TypeConstructor<T> | TransformOptions<T> } [type] - The class prototype or constructor function that has no parameters.
   * @returns { T | T[] } The parsed object of type T or T[].
   */
  public static parseTo<T extends object>(target: T | T[], source: object | string,
    type?: TypeConstructor<T> | TransformOptions<T>): T | T[] {
    const json = typeof source === 'string' ? JSON.parse(source) : source;
    const t1 = Array.isArray(json);
    const t2 = Array.isArray(target);
    const options: TransformOptions<T> = JSONCoder.getOptions(type);
    if (t1 && t2) {
      JSONCoder.parseIntoArray(target, json, options);
    } else if (!t1 && !t2) {
      JSONCoder.parseInto(target, json);
    } else {
      throw new Error(`The type of target '${t2}' mismatches the type of source '${t1}'`);
    }
    return target;
  }

  /**
   * Get the type options from the object creator.
   *
   * @template T - The object being parsed.
   * @param { TypeConstructor<T> | TransformOptions<T> | string } [type] - The type info of the object creator.
   * @returns { TransformOptions<T> } The options of the type info.
   */
  public static getOptions<T>(type?: TypeConstructor<T> | TransformOptions<T> | string): TransformOptions<T> {
    const paramType = typeof type;
    const options: TransformOptions<T> = {};
    if (paramType === 'object') {
      Object.assign(options, type);
    } else if (paramType === 'function') {
      options.factory = (_: object) => type as TypeConstructor<T>;
    } else if (paramType === 'string') {
      options.alias = type as string;
    }
    return options;
  }

  private static getAlias2Prop(meta: any, target: any): Map<string, string> {
    const ret = new Map<string, string>();
    Object.keys(meta).forEach(prop => {
      const options = meta[prop];
      ret.set(options.alias || prop, prop);
    });
    return ret;
  }

  private static parseInto(target: any, source: any): any {
    if (typeof source !== 'object') {
      throw new Error(`The type of target '${typeof target}' mismatches the type of source '${typeof source}'`);
    }

    const meta = Meta.gets(target);
    const alias2prop = JSONCoder.getAlias2Prop(meta, target);

    Object.keys(source).forEach((key: string) => {
      const prop = alias2prop.get(key) || key;
      const options = meta && meta[prop];
      if (options && options.disabled) {
        return;
      }
      JSONCoder.parseItemInto(target, prop, source, options);
    });

    return target;
  }

  private static parseItemInto(target: any, targetKey: string, source: any, options: any) {
    if (source === null || source === undefined) {
      return;
    }

    let tarType = typeof target[targetKey];
    if (tarType === 'function') {
      return;
    }

    const sourceKey = options?.alias || targetKey;
    // Handling invalid values
    const value = JSONCoder.getTargetValue(source[sourceKey], options);
    if (value === undefined || value === null) {
      if (tarType === 'object') {
        if (target[targetKey] instanceof Map || target[targetKey] instanceof Set) {
          target[targetKey].clear();
        } else if (Array.isArray(target[targetKey])) {
          target[targetKey].splice(0, target[targetKey].length);
        } else if (options && options.factory) {
          // if options.factory exists, can be assigned to undefined or null
          target[targetKey] = value;
        }
      }
      // other scene ignore all
      return;
    }

    // value is array, it maybe array or map or set
    if (Array.isArray(value)) {
      target[targetKey] = JSONCoder.parseIntoArray(target[targetKey], value, options);
      return;
    }

    // if target[targetKey] invalid, then attempt create
    if (target[targetKey] === null || target[targetKey] === undefined) {
      target[targetKey] = JSONCoder.newItem(value, options);
      tarType = typeof target[targetKey];
    }

    if (typeof value !== 'object') {
      // value is Primitive Type
      if (target[targetKey] instanceof Date) {
        target[targetKey] = new Date(value);
      } else if (tarType === 'string') {
        target[targetKey] = value.toString();
      } else if (tarType === typeof value) {
        target[targetKey] = value;
      } else if (target[targetKey] !== undefined) {
        throw new Error(`The type of target '${tarType}' mismatches the type of source '${typeof value}'`);
      }
      return;
    }

    // value is object, target[targetKey] is undefined or null
    if (target[targetKey] === null) {
      throw new Error(`Miss @Type in object defined, the property name is ${targetKey}`);
    } else if (target[targetKey] === undefined) {
      // ignore target[targetKey] undefined
      return;
    }
    this.parseInto(target[targetKey], value);
  }

  private static newItem(json: any, options: any): any {
    const type = options?.factory(json);
    return type && new type();
  }

  private static getTargetValue(value: any, options: any) {
    // future can convert the value to different type or value
    return value;
  }

  private static parseIntoArray(target: any, source: any, options: TransformOptions<any>): any {
    if (typeof target !== 'object') {
      throw new Error(`The type of target '${typeof target}' mismatches the type of source '${typeof source}'`);
    }
    // here, source maybe a array or map or set
    if (target instanceof Map) {
      target.clear();
      for (let i = 0; i < source.length; ++i) {
        // If target is a map, item must be an array. Otherwise, ignore it
        const item = source[i];
        if (!Array.isArray(item) || item.length < 2 || typeof item[0] !== 'string') {
          continue;
        }
        target.set(item[0], typeof item[1] !== 'object' ? item[1] : JSONCoder.parse(options, item[1]));
      }
      return target;
    }

    if (target instanceof Set) {
      target.clear();
      for (let i = 0; i < source.length; ++i) {
        const item = source[i];
        target.add(typeof item !== 'object' ? item : JSONCoder.parse(options, item));
      }
      return target;
    }

    target.length = source.length;
    for (let i = 0; i < source.length; ++i) {
      const item = source[i];
      if (typeof item !== 'object') {
        target[i] = item;
        continue;
      }

      if (i === 0) {
        if (!options?.factory) {
          target.length = 0;
          throw new Error(`Miss @Type in array defined`);
        }
      }

      target[i] = Array.isArray(item) ?
        JSONCoder.parseIntoArray(target[i] || [], item, options) :
        JSONCoder.parseInto(target[i] || JSONCoder.newItem(item, options), item);
    }
    return target;
  }
}
