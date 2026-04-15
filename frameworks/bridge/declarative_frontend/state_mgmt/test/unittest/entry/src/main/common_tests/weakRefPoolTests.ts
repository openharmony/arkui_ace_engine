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

import { eq, ITestFile } from '../lib/testRunner';

declare interface CleanupInfo {
  id2gcFunc?: Map<unknown, () => void>;
  computedId?: Set<number>;
  monitorId?: Set<number>;
}

declare interface ObservedV2ClassInfo {
  weakRef: WeakRef<object>;
  cleanupInfo: CleanupInfo;
}

declare class WeakRefPool {
  static wmap_: WeakMap<object, ObservedV2ClassInfo>;
  static getWeakRef<T extends object>(obj: T): WeakRef<T>;
  static addMonitorComputedId<T extends object>(obj: T): void;
  static addTagCallback<T extends object>(obj: T, tag: unknown, callback: () => void): void;
  static addMonitorId<T extends object>(obj: T, id: number): void;
  static clearMonitorId<T extends object>(obj: T, id: number): void;
  static removeTagCallback<T extends object>(obj: T, tag: unknown): void;
}

declare class MonitorV2 {
  static getMonitorIds(obj: object): number[];
}

declare class ComputedV2 {
  static getComputedIds(obj: object): number[];
}

export class WeakRefPoolTests implements ITestFile {
  private idString: string = '';

  constructor(str: string) {
    this.idString = str;
  }

  public beforeAll(): void {}

  public beforeEach(): void {
    WeakRefPool.wmap_ = new WeakMap<object, ObservedV2ClassInfo>();
    MonitorV2.getMonitorIds = (obj: object): number[] => [1, 2];
    ComputedV2.getComputedIds = (obj: object): number[] => [3, 4];
  }

  public afterAll(): void {}

  public afterEach(): void {}

  public getId(): string {
    return this.idString;
  }

  public testGetWeakRefReturnsSameWeakRefForSameObject(): void {
    const obj = {};
    const weakRef1 = WeakRefPool.getWeakRef(obj);
    const weakRef2 = WeakRefPool.getWeakRef(obj);

    eq(weakRef1, weakRef2);
    eq(weakRef1.deref(), obj);
  }

  public testAddMonitorComputedIdInitializesCleanupInfo(): void {
    const obj = {};

    WeakRefPool.addMonitorComputedId(obj);

    const cleanupInfo = WeakRefPool.wmap_.get(obj)?.cleanupInfo;
    eq(JSON.stringify(Array.from(cleanupInfo?.monitorId ?? [])), JSON.stringify([1, 2]));
    eq(JSON.stringify(Array.from(cleanupInfo?.computedId ?? [])), JSON.stringify([3, 4]));
  }

  public testAddMonitorComputedIdMergesIds(): void {
    const obj = {};

    MonitorV2.getMonitorIds = (target: object): number[] => [1, 2];
    ComputedV2.getComputedIds = (target: object): number[] => [3, 4];
    WeakRefPool.addMonitorComputedId(obj);

    MonitorV2.getMonitorIds = (target: object): number[] => [2, 5];
    ComputedV2.getComputedIds = (target: object): number[] => [4, 6];
    WeakRefPool.addMonitorComputedId(obj);

    const cleanupInfo = WeakRefPool.wmap_.get(obj)?.cleanupInfo;
    eq(JSON.stringify(Array.from(cleanupInfo?.monitorId ?? []).sort()), JSON.stringify([1, 2, 5]));
    eq(JSON.stringify(Array.from(cleanupInfo?.computedId ?? []).sort()), JSON.stringify([3, 4, 6]));
  }

  public testAddAndRemoveTagCallback(): void {
    const obj = {};
    const callback = (): void => {};

    WeakRefPool.addTagCallback(obj, 'tag1', callback);
    eq(WeakRefPool.wmap_.get(obj)?.cleanupInfo.id2gcFunc?.get('tag1'), callback);

    WeakRefPool.removeTagCallback(obj, 'tag1');
    eq(WeakRefPool.wmap_.get(obj)?.cleanupInfo.id2gcFunc?.has('tag1'), false);
  }

  public testAddAndClearMonitorId(): void {
    const obj = {};

    WeakRefPool.addMonitorId(obj, 10);
    WeakRefPool.addMonitorId(obj, 20);
    eq(JSON.stringify(Array.from(WeakRefPool.wmap_.get(obj)?.cleanupInfo.monitorId ?? [])), JSON.stringify([10, 20]));

    WeakRefPool.clearMonitorId(obj, 10);
    eq(JSON.stringify(Array.from(WeakRefPool.wmap_.get(obj)?.cleanupInfo.monitorId ?? [])), JSON.stringify([20]));
  }
}
