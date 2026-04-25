/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
import { eq, neq, gt, ITestFile } from '../lib/testRunner';

declare type MakeObservedRaw = object | number | string | boolean | bigint | null | undefined;

declare class RefInfo {
  static obj2ref: WeakMap<object, object>;
  static readonly MAKE_OBSERVED_PROXY: string;
  static get(target: MakeObservedRaw): object;
}

declare class ObserveV2 {
  static IsObservedObjectV2(value: MakeObservedRaw): boolean;
  static IsMakeObserved(value: MakeObservedRaw): boolean;
  static readonly SYMBOL_PROXY_GET_TARGET: symbol;
  static readonly SYMBOL_MAKE_OBSERVED: symbol;
  static readonly OB_LENGTH: string;
  getObserve(): ObserveV2;
  addRef(target: object, attrName: string): void;
  fireChange(target: object, attrName: string, excludeSet?: Set<number>, keepMeta?: boolean): void;
}

interface SimpleObject {
  x: number;
  y: string;
  nested?: SimpleObject;
}

interface DateHolder {
  date: Date;
}

export class ObservedProxyTestsV2 implements ITestFile {
  private idString: string = '';

  constructor(str: string) {
    this.idString = str;
  }

  public beforeAll(): void {
  }

  public beforeEach(): void {
  }

  public afterAll(): void {
  }

  public afterEach(): void {
  }

  public getId(): string {
    return this.idString;
  }

  // ==================== ObjectProxyHandler: makeObserved get/set ====================

  public testObjectProxyReadProperty(): void {
    const obj: SimpleObject = { x: 1, y: 'hello' } as SimpleObject;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as SimpleObject;
    eq(px.x, 1, 'object read x');
    eq(px.y, 'hello', 'object read y');
  }

  public testObjectProxyWriteProperty(): void {
    const obj: SimpleObject = { x: 10, y: 'world' } as SimpleObject;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as SimpleObject;
    px.x = 20;
    px.y = 'updated';
    eq(obj.x, 20, 'object write x');
    eq(obj.y, 'updated', 'object write y');
  }

  public testObjectProxySetSameValue(): void {
    const obj: SimpleObject = { x: 5, y: 'same' } as SimpleObject;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as SimpleObject;
    px.x = 5;
    eq(obj.x, 5, 'same value should not change');
  }

  public testObjectProxyReadNestedObject(): void {
    const inner: SimpleObject = { x: 99, y: 'inner' } as SimpleObject;
    const obj: SimpleObject = { x: 1, y: 'outer', nested: inner } as SimpleObject;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as SimpleObject;
    const nestedProxy = px.nested;
    eq(typeof nestedProxy, 'object', 'nested object should be returned via proxy');
    eq(nestedProxy.x, 99, 'nested proxy read x');
  }

  public testObjectProxyWriteNestedProperty(): void {
    const inner: SimpleObject = { x: 50, y: 'inner' } as SimpleObject;
    const obj: SimpleObject = { x: 1, y: 'outer', nested: inner } as SimpleObject;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as SimpleObject;
    const nestedProxy = px.nested;
    nestedProxy.x = 100;
    eq(inner.x, 100, 'nested write through proxy');
  }

  public testObjectProxySymbolIterator(): void {
    const obj = { a: 1, b: 2 };
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as any;
    const iterator = px[Symbol.iterator];
    eq(typeof iterator, 'function', 'Symbol.iterator should return function');
  }

  public testObjectProxySymbolProxyGetTarget(): void {
    const obj = { a: 1 };
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as any;
    const target = px[ObserveV2.SYMBOL_PROXY_GET_TARGET];
    eq(target, obj, 'SYMBOL_PROXY_GET_TARGET should return raw target');
  }

  public testObjectProxySymbolMakeObserved(): void {
    const obj = { a: 1 };
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as any;
    eq(px[ObserveV2.SYMBOL_MAKE_OBSERVED], true, 'SYMBOL_MAKE_OBSERVED should be true');
  }

  public testObjectProxySymbolKeySet(): void {
    const obj: SimpleObject = { x: 1, y: 'test' } as SimpleObject;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as any;
    const customSymbol = Symbol('custom');
    px[customSymbol] = 'symbolValue';
    // makeObserved path: symbol keys are not set on target
    eq(obj[customSymbol as any], undefined, 'symbol set ignored on target in makeObserved');
  }

  public testObjectProxyFunctionProperty(): void {
    const obj: any = { x: 1, greet: function() { return 'hello'; } };
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as any;
    eq(typeof px.greet, 'function', 'function property should be accessible');
    eq(px.greet(), 'hello', 'function should execute correctly');
  }

  // ==================== ObjectProxyHandler: Date ====================

  public testObjectProxyDateGetTime(): void {
    const date = new Date(2025, 0, 1);
    const w = RefInfo.get(date);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Date;
    eq(px.getTime(), date.getTime(), 'date getTime through proxy');
  }

  public testObjectProxyDateSetFunction(): void {
    const date = new Date(2025, 0, 1);
    const originalTime = date.getTime();
    const w = RefInfo.get(date);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Date;
    px.setFullYear(2026);
    eq(date.getFullYear(), 2026, 'date setFullYear through proxy');
    neq(date.getTime(), originalTime, 'date should have changed');
  }

  public testObjectProxyDateSetMonth(): void {
    const date = new Date(2025, 0, 15);
    const w = RefInfo.get(date);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Date;
    px.setMonth(5);
    eq(date.getMonth(), 5, 'date setMonth through proxy');
  }

  public testObjectProxyDateSetDate(): void {
    const date = new Date(2025, 0, 1);
    const w = RefInfo.get(date);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Date;
    px.setDate(20);
    eq(date.getDate(), 20, 'date setDate through proxy');
  }

  public testObjectProxyDateSetHours(): void {
    const date = new Date(2025, 0, 1);
    const w = RefInfo.get(date);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Date;
    px.setHours(14);
    eq(date.getHours(), 14, 'date setHours through proxy');
  }

  public testObjectProxyDateGetFullYear(): void {
    const date = new Date(2025, 5, 15);
    const w = RefInfo.get(date);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Date;
    eq(px.getFullYear(), 2025, 'date getFullYear through proxy');
  }

  public testObjectProxyDateGetMonth(): void {
    const date = new Date(2025, 5, 15);
    const w = RefInfo.get(date);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Date;
    eq(px.getMonth(), 5, 'date getMonth through proxy');
  }

  public testObjectProxyDateSetTime(): void {
    const date = new Date(2025, 0, 1);
    const w = RefInfo.get(date);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Date;
    const newTime = new Date(2026, 6, 4).getTime();
    px.setTime(newTime);
    eq(date.getTime(), newTime, 'date setTime through proxy');
  }

  public testObjectProxyDateNestedInObject(): void {
    const obj: DateHolder = { date: new Date(2025, 0, 1) };
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as DateHolder;
    eq(px.date.getFullYear(), 2025, 'nested date getFullYear');
    px.date.setFullYear(2027);
    eq(obj.date.getFullYear(), 2027, 'nested date setFullYear');
  }

  // ==================== ArrayProxyHandler: makeObserved get/set ====================

  public testArrayProxyReadElement(): void {
    const arr = [10, 20, 30];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 10, 'array read [0]');
    eq(px[1], 20, 'array read [1]');
    eq(px[2], 30, 'array read [2]');
  }

  public testArrayProxyWriteElement(): void {
    const arr = [10, 20, 30];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    px[1] = 99;
    eq(arr[1], 99, 'array write [1]');
    eq(arr[0], 10, 'array [0] unchanged');
  }

  public testArrayProxyLength(): void {
    const arr = [1, 2, 3];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px.length, 3, 'array length');
  }

  public testArrayProxyPush(): void {
    const arr = [1, 2];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    const result = px.push(3);
    eq(arr.length, 3, 'array push increases length');
    eq(arr[2], 3, 'array push value correct');
    eq(result, 3, 'push returns new length');
  }

  public testArrayProxyPop(): void {
    const arr = [1, 2, 3];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    const result = px.pop();
    eq(result, 3, 'pop returns removed element');
    eq(arr.length, 2, 'array pop decreases length');
  }

  public testArrayProxyShift(): void {
    const arr = [10, 20, 30];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    const result = px.shift();
    eq(result, 10, 'shift returns first element');
    eq(arr.length, 2, 'shift decreases length');
    eq(arr[0], 20, 'shift moves elements');
  }

  public testArrayProxyUnshift(): void {
    const arr = [2, 3];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    const result = px.unshift(1);
    eq(result, 3, 'unshift returns new length');
    eq(arr[0], 1, 'unshift adds element at start');
    eq(arr.length, 3, 'unshift increases length');
  }

  public testArrayProxySplice(): void {
    const arr = [1, 2, 3, 4, 5];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    const removed = px.splice(1, 2);
    eq(arr.length, 3, 'splice reduces length');
    eq(arr[0], 1, 'splice keeps first');
    eq(arr[1], 4, 'splice shifts remaining');
    eq(removed[0], 2, 'splice returns removed');
  }

  public testArrayProxySort(): void {
    const arr = [3, 1, 4, 1, 5];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    const result = px.sort();
    eq(arr[0], 1, 'sort orders array');
    eq(arr[4], 5, 'sort orders array last');
  }

  public testArrayProxyReverse(): void {
    const arr = [1, 2, 3];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    const result = px.reverse();
    eq(arr[0], 3, 'reverse swaps elements');
    eq(arr[2], 1, 'reverse swaps elements');
  }

  public testArrayProxyFill(): void {
    const arr = [0, 0, 0, 0, 0];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    px.fill(7, 1, 4);
    eq(arr[0], 0, 'fill start unchanged');
    eq(arr[1], 7, 'fill fills range');
    eq(arr[3], 7, 'fill fills range');
    eq(arr[4], 0, 'fill end unchanged');
  }

  public testArrayProxyCopyWithin(): void {
    const arr = [1, 2, 3, 4, 5];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    px.copyWithin(0, 3, 5);
    eq(arr[0], 4, 'copyWithin copies');
    eq(arr[1], 5, 'copyWithin copies');
  }

  public testArrayProxyForEach(): void {
    const arr = [10, 20, 30];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    let sum = 0;
    px.forEach((v: number) => { sum += v; });
    eq(sum, 60, 'forEach sums correctly');
  }

  public testArrayProxySymbolIterator(): void {
    const arr = [1, 2, 3];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    const iterator = px[Symbol.iterator];
    eq(typeof iterator, 'function', 'Symbol.iterator returns function');
  }

  public testArrayProxySymbolProxyGetTarget(): void {
    const arr = [1, 2, 3];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as any;
    eq(px[ObserveV2.SYMBOL_PROXY_GET_TARGET], arr, 'SYMBOL_PROXY_GET_TARGET returns raw array');
  }

  public testArrayProxySymbolMakeObserved(): void {
    const arr = [1, 2, 3];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as any;
    eq(px[ObserveV2.SYMBOL_MAKE_OBSERVED], true, 'SYMBOL_MAKE_OBSERVED should be true');
  }

  public testArrayProxySetSameValue(): void {
    const arr = [1, 2, 3];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    px[1] = 2;
    eq(arr[1], 2, 'same value no change');
    eq(arr.length, 3, 'length unchanged');
  }

  public testArrayProxySetExtendsArray(): void {
    const arr = [1, 2];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    px[5] = 99;
    eq(arr[5], 99, 'set beyond length');
    eq(arr.length, 6, 'set extends length');
  }

  public testArrayProxyMap(): void {
    const arr = [1, 2, 3];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    const result = px.map((v: number) => v * 2);
    eq(result[0], 2, 'map transforms');
    eq(result[1], 4, 'map transforms');
    eq(result[2], 6, 'map transforms');
  }

  public testArrayProxyFilter(): void {
    const arr = [1, 2, 3, 4, 5];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    const result = px.filter((v: number) => v % 2 === 0);
    eq(result.length, 2, 'filter keeps even');
    eq(result[0], 2, 'filter result[0]');
    eq(result[1], 4, 'filter result[1]');
  }

  public testArrayProxyIndexOf(): void {
    const arr = [10, 20, 30];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px.indexOf(20), 1, 'indexOf finds element');
    eq(px.indexOf(99), -1, 'indexOf returns -1 for missing');
  }

  public testArrayProxyIncludes(): void {
    const arr = [10, 20, 30];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px.includes(20), true, 'includes finds element');
    eq(px.includes(99), false, 'includes returns false for missing');
  }

  public testArrayProxyJoin(): void {
    const arr = [1, 2, 3];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px.join('-'), '1-2-3', 'join works');
  }

  public testArrayProxySlice(): void {
    const arr = [1, 2, 3, 4, 5];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    const result = px.slice(1, 4);
    eq(result.length, 3, 'slice length');
    eq(result[0], 2, 'slice [0]');
    eq(result[2], 4, 'slice [2]');
  }

  public testArrayProxyConcat(): void {
    const arr = [1, 2];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    const result = px.concat([3, 4]);
    eq(result.length, 4, 'concat length');
    eq(result[2], 3, 'concat value');
  }

  public testArrayProxyReduce(): void {
    const arr = [1, 2, 3, 4];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    const sum = px.reduce((acc: number, v: number) => acc + v, 0);
    eq(sum, 10, 'reduce sums');
  }

  public testArrayProxyFindObject(): void {
    const inner1 = { id: 1, name: 'a' };
    const inner2 = { id: 2, name: 'b' };
    const arr = [inner1, inner2];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as any[];
    const found = px.find((item: any) => item.id === 2);
    eq(typeof found, 'object', 'find returns object');
    eq(found.id, 2, 'find returns correct object');
  }

  // ==================== SetMapProxyHandler: Set ====================

  public testSetProxyHas(): void {
    const set = new Set<string>();
    set.add('x');
    set.add('y');
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Set<string>;
    eq(px.has('x'), true, 'set has existing');
    eq(px.has('z'), false, 'set has missing');
  }

  public testSetProxyAdd(): void {
    const set = new Set<number>();
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Set<number>;
    px.add(10);
    px.add(20);
    eq(set.has(10), true, 'set add 10');
    eq(set.has(20), true, 'set add 20');
  }

  public testSetProxyAddDuplicate(): void {
    const set = new Set<number>();
    set.add(10);
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Set<number>;
    const result = px.add(10);
    eq(set.size, 1, 'set add duplicate does not increase size');
    eq(typeof result, 'object', 'set add returns proxy (receiver)');
  }

  public testSetProxyDelete(): void {
    const set = new Set<string>();
    set.add('a');
    set.add('b');
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Set<string>;
    eq(px.delete('a'), true, 'set delete existing returns true');
    eq(set.has('a'), false, 'set delete removes element');
    eq(set.size, 1, 'set delete reduces size');
  }

  public testSetProxyDeleteMissing(): void {
    const set = new Set<string>();
    set.add('a');
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Set<string>;
    eq(px.delete('z'), false, 'set delete missing returns false');
    eq(set.size, 1, 'set size unchanged');
  }

  public testSetProxyClear(): void {
    const set = new Set<number>();
    set.add(1);
    set.add(2);
    set.add(3);
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Set<number>;
    px.clear();
    eq(set.size, 0, 'set clear empties set');
  }

  public testSetProxyClearEmpty(): void {
    const set = new Set<number>();
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Set<number>;
    px.clear();
    eq(set.size, 0, 'clear empty set ok');
  }

  public testSetProxySize(): void {
    const set = new Set<number>();
    set.add(1);
    set.add(2);
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Set<number>;
    eq(px.size, 2, 'set size');
  }

  public testSetProxyKeys(): void {
    const set = new Set<string>();
    set.add('a');
    set.add('b');
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Set<string>;
    const keys = px.keys();
    eq(typeof keys.next, 'function', 'set keys returns iterator');
  }

  public testSetProxyValues(): void {
    const set = new Set<string>();
    set.add('x');
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Set<string>;
    const values = px.values();
    eq(typeof values.next, 'function', 'set values returns iterator');
  }

  public testSetProxyEntries(): void {
    const set = new Set<string>();
    set.add('a');
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Set<string>;
    const entries = px.entries();
    eq(typeof entries.next, 'function', 'set entries returns iterator');
  }

  public testSetProxyForEach(): void {
    const set = new Set<number>();
    set.add(10);
    set.add(20);
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Set<number>;
    let sum = 0;
    px.forEach((v: number) => { sum += v; });
    eq(sum, 30, 'set forEach sums');
  }

  public testSetProxySymbolIterator(): void {
    const set = new Set<number>();
    set.add(1);
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Set<number>;
    const iterator = px[Symbol.iterator];
    eq(typeof iterator, 'function', 'set Symbol.iterator returns function');
  }

  public testSetProxySymbolProxyGetTarget(): void {
    const set = new Set<number>();
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as any;
    eq(px[ObserveV2.SYMBOL_PROXY_GET_TARGET], set, 'set SYMBOL_PROXY_GET_TARGET');
  }

  public testSetProxySymbolMakeObserved(): void {
    const set = new Set<number>();
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as any;
    eq(px[ObserveV2.SYMBOL_MAKE_OBSERVED], true, 'set SYMBOL_MAKE_OBSERVED');
  }

  // ==================== SetMapProxyHandler: Map ====================

  public testMapProxyGetExisting(): void {
    const map = new Map<string, number>();
    map.set('a', 1);
    map.set('b', 2);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    eq(px.get('a'), 1, 'map get existing');
    eq(px.get('b'), 2, 'map get existing b');
  }

  public testMapProxyGetMissing(): void {
    const map = new Map<string, number>();
    map.set('a', 1);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    eq(px.get('z'), undefined, 'map get missing returns undefined');
  }

  public testMapProxySetNewKey(): void {
    const map = new Map<string, number>();
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    px.set('x', 100);
    eq(map.get('x'), 100, 'map set new key');
    eq(map.size, 1, 'map size after set');
  }

  public testMapProxySetExistingKey(): void {
    const map = new Map<string, number>();
    map.set('a', 1);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    px.set('a', 99);
    eq(map.get('a'), 99, 'map set overwrites existing');
  }

  public testMapProxyHas(): void {
    const map = new Map<string, number>();
    map.set('a', 1);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    eq(px.has('a'), true, 'map has existing');
    eq(px.has('z'), false, 'map has missing');
  }

  public testMapProxyDelete(): void {
    const map = new Map<string, number>();
    map.set('a', 1);
    map.set('b', 2);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    eq(px.delete('a'), true, 'map delete existing');
    eq(map.has('a'), false, 'map delete removes key');
    eq(map.size, 1, 'map size after delete');
  }

  public testMapProxyDeleteMissing(): void {
    const map = new Map<string, number>();
    map.set('a', 1);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    eq(px.delete('z'), false, 'map delete missing returns false');
    eq(map.size, 1, 'map size unchanged');
  }

  public testMapProxyClear(): void {
    const map = new Map<string, number>();
    map.set('a', 1);
    map.set('b', 2);
    map.set('c', 3);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    px.clear();
    eq(map.size, 0, 'map clear empties map');
  }

  public testMapProxyClearEmpty(): void {
    const map = new Map<string, number>();
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    px.clear();
    eq(map.size, 0, 'clear empty map ok');
  }

  public testMapProxySize(): void {
    const map = new Map<string, number>();
    map.set('a', 1);
    map.set('b', 2);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    eq(px.size, 2, 'map size');
  }

  public testMapProxyKeys(): void {
    const map = new Map<string, number>();
    map.set('a', 1);
    map.set('b', 2);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    const keys = px.keys();
    eq(typeof keys.next, 'function', 'map keys returns iterator');
  }

  public testMapProxyValues(): void {
    const map = new Map<string, number>();
    map.set('a', 1);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    const values = px.values();
    eq(typeof values.next, 'function', 'map values returns iterator');
  }

  public testMapProxyEntries(): void {
    const map = new Map<string, number>();
    map.set('a', 1);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    const entries = px.entries();
    eq(typeof entries.next, 'function', 'map entries returns iterator');
  }

  public testMapProxyForEach(): void {
    const map = new Map<string, number>();
    map.set('a', 10);
    map.set('b', 20);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    let sum = 0;
    px.forEach((v: number) => { sum += v; });
    eq(sum, 30, 'map forEach sums');
  }

  public testMapProxySymbolIterator(): void {
    const map = new Map<string, number>();
    map.set('a', 1);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    const iterator = px[Symbol.iterator];
    eq(typeof iterator, 'function', 'map Symbol.iterator returns function');
  }

  public testMapProxySymbolProxyGetTarget(): void {
    const map = new Map<string, number>();
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as any;
    eq(px[ObserveV2.SYMBOL_PROXY_GET_TARGET], map, 'map SYMBOL_PROXY_GET_TARGET');
  }

  public testMapProxySymbolMakeObserved(): void {
    const map = new Map<string, number>();
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as any;
    eq(px[ObserveV2.SYMBOL_MAKE_OBSERVED], true, 'map SYMBOL_MAKE_OBSERVED');
  }

  public testMapProxyGetObjectValue(): void {
    const innerObj = { name: 'test', value: 42 };
    const map = new Map<string, object>();
    map.set('item', innerObj);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, any>;
    const item = px.get('item');
    eq(typeof item, 'object', 'map get object value returns proxy');
    eq(item.name, 'test', 'map get object proxy read');
  }

  public testMapProxySetReturnsReceiver(): void {
    const map = new Map<string, number>();
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    const result = px.set('k', 1);
    eq(typeof result, 'object', 'map set returns proxy');
  }

  // ==================== SetMapProxyHandler: set() trap ====================

  public testSetMapProxySetProperty(): void {
    const set = new Set<number>();
    (set as any).customProp = 'original';
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as any;
    px.customProp = 'updated';
    eq((set as any).customProp, 'updated', 'set trap writes to target');
  }

  public testSetMapProxySetSameValue(): void {
    const set = new Set<number>();
    (set as any).val = 10;
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as any;
    px.val = 10;
    eq((set as any).val, 10, 'same value no change');
  }

  public testSetMapProxySetSymbolKey(): void {
    const map = new Map<string, number>();
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as any;
    const sym = Symbol('test');
    px[sym] = 'value';
    // makeObserved path: symbol keys are not set on target
    eq((map as any)[sym], undefined, 'symbol set ignored on target in makeObserved');
  }

  // ==================== Mixed / Edge Cases ====================

  public testObjectProxyMultipleProperties(): void {
    const obj: any = { a: 1, b: 'str', c: true, d: null, e: undefined };
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as any;
    eq(px.a, 1, 'number property');
    eq(px.b, 'str', 'string property');
    eq(px.c, true, 'boolean property');
    eq(px.d, null, 'null property');
    eq(px.e, undefined, 'undefined property');
  }

  public testArrayProxyObjectElements(): void {
    const obj1 = { id: 1 };
    const obj2 = { id: 2 };
    const arr = [obj1, obj2];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as any[];
    const elem = px[0];
    eq(typeof elem, 'object', 'object element returned as proxy');
    eq(elem.id, 1, 'object element read through proxy');
  }

  public testArrayProxySpliceInsert(): void {
    const arr = [1, 2, 5];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    px.splice(2, 0, 3, 4);
    eq(arr.length, 5, 'splice insert increases length');
    eq(arr[2], 3, 'splice insert [2]');
    eq(arr[3], 4, 'splice insert [3]');
    eq(arr[4], 5, 'splice insert [4]');
  }

  public testArrayProxyMultiplePushPop(): void {
    const arr: number[] = [];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    px.push(1);
    px.push(2);
    px.push(3);
    eq(arr.length, 3, 'multiple push length');
    px.pop();
    eq(arr.length, 2, 'pop after multiple push');
    eq(arr[1], 2, 'last element after pop');
  }

  public testMapProxySetOverwriteSameValue(): void {
    const map = new Map<string, number>();
    map.set('a', 1);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    px.set('a', 1);
    eq(map.get('a'), 1, 'same value no change');
  }

  public testSetProxyAddMultipleThenDelete(): void {
    const set = new Set<number>();
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Set<number>;
    px.add(1);
    px.add(2);
    px.add(3);
    eq(set.size, 3, 'add multiple');
    px.delete(2);
    eq(set.size, 2, 'delete after add multiple');
    eq(set.has(1), true, 'still has 1');
    eq(set.has(3), true, 'still has 3');
  }

  public testMapProxyComplexKeyTypes(): void {
    const map = new Map<any, string>();
    const keyObj = { id: 1 };
    map.set(keyObj, 'obj_value');
    map.set(123, 'num_value');
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<any, string>;
    eq(px.get(keyObj), 'obj_value', 'object key');
    eq(px.get(123), 'num_value', 'number key');
  }

  public testObjectProxyWriteNewProperty(): void {
    const obj: any = { x: 1 };
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as any;
    px.newProp = 'added';
    eq(obj.newProp, 'added', 'new property written to target');
  }

  public testArrayProxyFindIndex(): void {
    const arr = [10, 20, 30, 40];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px.findIndex((v: number) => v > 25), 2, 'findIndex returns correct index');
    eq(px.findIndex((v: number) => v > 100), -1, 'findIndex returns -1');
  }

  public testArrayProxyEvery(): void {
    const arr = [2, 4, 6, 8];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px.every((v: number) => v % 2 === 0), true, 'every all even');
  }

  public testArrayProxySome(): void {
    const arr = [1, 3, 5, 6, 7];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px.some((v: number) => v % 2 === 0), true, 'some even');
  }
}
