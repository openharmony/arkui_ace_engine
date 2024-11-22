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

class RefInfo {
  private static obj2ref: WeakMap<object, object> = new WeakMap();
  private static setMapProxy: SetMapProxyHandler = new SetMapProxyHandler(true);
  private static arrayProxy: ArrayProxyHandler = new ArrayProxyHandler(true);
  private static objectProxy: ObjectProxyHandler = new ObjectProxyHandler(true);

  static get(target: Object): any {
    if (!target || typeof target !== 'object') {
      stateMgmtConsole.warn(`makeObserved target is not a valid object, return target directly`);
      return { proxy: target };
    }
    // makeObserved does not support @Observed, @ObservedV2/@Trace class or makeObserved proxy, will return target directly
    if (ObservedObject.IsObservedObject(target) || ObserveV2.IsObservedObjectV2(target) || ObserveV2.IsMakeObserved(target)) {
      stateMgmtConsole.warn(`${target.constructor.name} is Observed ${ObservedObject.IsObservedObject(target)}, IsObservedV2 ${ObserveV2.IsObservedObjectV2(target)} or makeObserved proxy value ${ObserveV2.IsMakeObserved(target)}. makeObserved will stop work`);
      return { proxy: target };
    }
    let ret = RefInfo.obj2ref.get(target);
    if (!ret) {
      if (Array.isArray(target) || SendableType.isArray(target)) {
        ret = { proxy: new Proxy(target, RefInfo.arrayProxy) };
      } else if (target instanceof Set || SendableType.isSet(target) ||
        target instanceof Map || SendableType.isMap(target)) {
        ret = { proxy: new Proxy(target, RefInfo.setMapProxy) };
      } else {
        ret = { proxy: new Proxy(target, RefInfo.objectProxy) };
      }
      RefInfo.obj2ref.set(target, ret);
    }
    return ret;
  }
}