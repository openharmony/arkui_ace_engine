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

interface ObservedV2ClassInfo {
  // obj -> weakRef
  weakRef: WeakRef<object>;
  cleanupInfo: CleanupInfo;
}

interface CleanupInfo {
  // id -> gc-callback.
  // to unregister from id2targets when observedV2 class gc
  id2gcFunc?: Map<unknown, () => void>;
  // computed id inside the observedV2 class
  computedId?: Set<number>;
  // monitor id including monitor value path id inside the observed class
  monitorId?: Set<number>;
}
class WeakRefPool {
  // map objects -> ObservedV2ClassInfo
  private static wmap_ = new WeakMap();
  // FinalizationRegistry to ObservedV2 class
  private static freg_ = new FinalizationRegistry((cleanupInfo) => {
    stateMgmtConsole.debug(`FinalizationRegistry begin 
      computedId ${JSON.stringify(Array.from(cleanupInfo.computedId ? cleanupInfo.computedId : []))} 
      monitorId: ${JSON.stringify(Array.from(cleanupInfo.monitorId ? cleanupInfo.monitorId : []))}`);
    cleanupInfo.computedId?.forEach((id) => {
      // remove from the ID_REFS, SYMBOL_REFS and id2targets
      ObserveV2.getObserve().clearBinding(id);
      // remove from id2Others
      delete ObserveV2.getObserve().id2Others_[id];
    });

    cleanupInfo.monitorId?.forEach((id) => {
      ObserveV2.getObserve().clearWatch(id);
      delete ObserveV2.getObserve().id2Others_[id];
    });
    cleanupInfo.id2gcFunc?.forEach(fn => fn());
  });

  // Create a WeakRef for the given object and put it into the pool, or get
  // existing WeakRef from the pool if the object is already there. WeakRefs
  // for the same object are always identical.
  public static getWeakRef<T extends object>(obj: T): WeakRef<T> {
    let observedV2ClassInfo = WeakRefPool.wmap_.get(obj);
    if (observedV2ClassInfo === undefined) {
      WeakRefPool.wmap_.set(obj, observedV2ClassInfo = { weakRef: new WeakRef(obj), cleanupInfo: {} });
      WeakRefPool.freg_.register(obj, observedV2ClassInfo.cleanupInfo);
    } else if (!observedV2ClassInfo.weakRef) {
      observedV2ClassInfo.weakRef = new WeakRef(obj);
    }
    return observedV2ClassInfo.weakRef;
  }

  public static asyncRegisterToFinalizationRegistry<T extends object>(obj: T): void {
    Promise.resolve(true)
      .then(() => {
        stateMgmtConsole.debug(`asyncRegisterToFinalizationRegistry ${obj.constructor.name} `);
        WeakRefPool.getOrCreateCleanupInfo(obj);
        WeakRefPool.addMonitorComputedId(obj);
      })
      .catch(error => {
        stateMgmtConsole.applicationError(`Exception caught in registerToFinalizationRegistry ${obj.constructor.name}`, error);
        _arkUIUncaughtPromiseError(error);
      });
  }

  private static getOrCreateCleanupInfo<T extends object>(obj: T): CleanupInfo {
    let observedV2ClassInfo = WeakRefPool.wmap_.get(obj);
    if (observedV2ClassInfo === undefined) {
      observedV2ClassInfo = { weakRef: new WeakRef(obj), cleanupInfo: {} };
      WeakRefPool.wmap_.set(obj, observedV2ClassInfo);
      WeakRefPool.freg_.register(obj, observedV2ClassInfo.cleanupInfo);
    }
    return observedV2ClassInfo.cleanupInfo;
  }

  public static addMonitorComputedId<T extends object>(obj: T): void {
    const cleanupInfo = WeakRefPool.getOrCreateCleanupInfo(obj);
    const monitorIds = MonitorV2.getMonitorIds(obj);
    const computedIds = ComputedV2.getComputedIds(obj);
    
    if (cleanupInfo.computedId) {
      stateMgmtConsole.debug(`addMonitorComputedId: addComputedId ${obj.constructor.name} add ${JSON.stringify(computedIds)} to ${JSON.stringify(Array.from(cleanupInfo.computedId))}`);
      computedIds.forEach(id => {
        cleanupInfo.computedId.add(id);
      });
    } else {
      cleanupInfo.computedId = new Set(computedIds);
    }

    if (cleanupInfo.monitorId) {
      stateMgmtConsole.debug(`addMonitorComputedId: addMonitorId ${obj.constructor.name} add ${JSON.stringify(monitorIds)} to ${JSON.stringify(Array.from(cleanupInfo.monitorId))}`);
      monitorIds.forEach(id => {
        cleanupInfo.monitorId.add(id);
      });
    } else {
      cleanupInfo.monitorId = new Set(monitorIds);
    }
    stateMgmtConsole.debug(`addMonitorComputedId monitorId: ${JSON.stringify(Array.from(cleanupInfo.monitorId))} computedId: ${JSON.stringify(Array.from(cleanupInfo.computedId))}`);
  }

  public static addTagCallback<T extends object>(obj: T, tag: unknown, callback: () => void): void {
    const cleanupInfo = WeakRefPool.getOrCreateCleanupInfo(obj);
    cleanupInfo.id2gcFunc ??= new Map<unknown, () => void>();
    cleanupInfo.id2gcFunc.set(tag, callback);
  }

  public static addMonitorId<T extends object>(obj: T, id: number): void {
    const cleanupInfo = WeakRefPool.getOrCreateCleanupInfo(obj);
    cleanupInfo.monitorId ??= new Set<number>();
    cleanupInfo.monitorId.add(id);
  }

  public static clearMonitorId<T extends object>(obj: T, id: number): void {
    const cleanupInfo = WeakRefPool.getOrCreateCleanupInfo(obj);
    if (cleanupInfo.monitorId) {
      cleanupInfo.monitorId.delete(id);
    }
  }

  public static removeTagCallback<T extends object>(obj: T, tag: unknown): void {
    const cleanupInfo = WeakRefPool.getOrCreateCleanupInfo(obj);
    if (cleanupInfo.id2gcFunc) {
      cleanupInfo.id2gcFunc.delete(tag);
    }
  }
}
