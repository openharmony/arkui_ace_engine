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
  // map weakref -> Map<tag, gc-callback>
  private static fmap_ = new Map();
  //
  private static freg_ = new FinalizationRegistry((weakRef: WeakRef<object>) => {
    WeakRefPool.getTaggedCallbacks(weakRef).forEach(fn => fn());
    WeakRefPool.fmap_.delete(weakRef);
  });

  // Create a WeakRef for the given object and put it into the pool, or get
  // existing WeakRef from the pool if the object is already there. WeakRefs
  // for the same object are always identical.
  public static get<T extends object>(obj: T): WeakRef<T>
  {
    let weakRef = WeakRefPool.wmap_.get(obj);
    if (weakRef === undefined) {
      WeakRefPool.wmap_.set(obj, weakRef = new WeakRef(obj));
    }
    return weakRef;
  }

  // Add handler to track when the given object is GC'ed.
  // Tag is used by unregister() only. Pair <obj, tag> should be unique per callback
  public static register<T extends object>(obj: T, tag: unknown, callback: () => void): void {
    const weakRef = WeakRefPool.get(obj);
    const tagMap = WeakRefPool.getTaggedCallbacks(weakRef);
    tagMap.size || WeakRefPool.freg_.register(obj, weakRef);
    tagMap.set(tag, callback);
  }

  public static unregister<T extends object>(obj: T, tag: unknown): void {
    const weakRef = WeakRefPool.get(obj);
    const tagMap = WeakRefPool.getTaggedCallbacks(weakRef);
    tagMap.delete(tag);
    tagMap.size || WeakRefPool.freg_.unregister(weakRef);
    tagMap.size || WeakRefPool.fmap_.delete(weakRef);
  }

  private static getTaggedCallbacks<T extends object>(weakRef: WeakRef<T>): Map<unknown, () => void> {
    let tagMap = WeakRefPool.fmap_.get(weakRef);
    if (tagMap === undefined) {
      WeakRefPool.fmap_.set(weakRef, tagMap = new Map());
    }
    return tagMap;
  }

  // debug only
  private static getTaggedCallbacksSize(): number {
    let size = 0;
    WeakRefPool.fmap_.forEach(tagMap => size += tagMap.size);
    return size;
  }
}