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

class WeakRefPool {
  // map objects -> weakrefs
  private static wmap_ = new WeakMap();
  // map weakref -> gc callbacks (list of functions)
  private static fmap_ = new Map();
  //
  private static freg_ = new FinalizationRegistry(weakRef => {
    WeakRefPool.fmap_.get(weakRef)?.forEach(fn => fn());
    WeakRefPool.fmap_.delete(weakRef);
  });

  // Create a WeakRef for the given object and put it into the pool, or get
  // existing WeakRef from the pool if the object is already there. WeakRefs
  // for the same object are always identical.
  public static get<T extends Object | Symbol>(obj: T): WeakRef<T>
  {
    let weakRef = WeakRefPool.wmap_.get(obj);
    if (weakRef === undefined) {
      WeakRefPool.wmap_.set(obj, weakRef = new WeakRef(obj));
    }
    return weakRef;
  }

  // Add handler to track when the given object is GC'ed
  public static onGC<T extends Object | Symbol>(obj: T, onGarbageCollect: () => void) {
    // list of functions is faster alternative to multiple FinalizationRegistry.register calls
    const weakRef= WeakRefPool.get(obj);
    const fnList = WeakRefPool.fmap_.get(weakRef);

    if (fnList == undefined) {
      WeakRefPool.fmap_.set(weakRef, [onGarbageCollect]);
      WeakRefPool.freg_.register(obj, weakRef);
    } else {
      fnList.push(onGarbageCollect);
    }
  }
}