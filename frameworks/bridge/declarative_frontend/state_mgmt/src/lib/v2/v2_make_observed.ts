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
  public static readonly MAKE_OBSERVED_PROXY = Symbol('__make_observed_proxy');

  static get(target: Object): any {
    //console.log("### RefInfo.get start");
    if (!target || typeof target !== 'object') {
      stateMgmtConsole.warn(`makeObserved target is not a valid object, return target directly`);
      console.log("### RefInfo.get exit ont an object");
      return { [RefInfo.MAKE_OBSERVED_PROXY]: target };
    }
    // makeObserved does not support @Observed, @ObservedV2/@Trace class or makeObserved proxy, will return target directly
    if (ObservedObject.IsObservedObject(target) || ObserveV2.IsObservedObjectV2(target) || ObserveV2.IsMakeObserved(target)) {
      console.log("### RefInfo.get exit already observed");
      stateMgmtConsole.frequentWarn(`${target.constructor.name} is Observed ${ObservedObject.IsObservedObject(target)}, IsObservedV2 ${ObserveV2.IsObservedObjectV2(target)} or makeObserved proxy value ${ObserveV2.IsMakeObserved(target)}. makeObserved will stop work`);
      return { [RefInfo.MAKE_OBSERVED_PROXY]: target };
    }
    let ret = RefInfo.obj2ref.get(target);
    if (!ret) {
      //console.log("### RefInfo.get not yet proxied " + JSON.stringify(target));
      if (Array.isArray(target) || SendableType.isArray(target)) {
        console.log("### RefInfo.get not yet - array");
        ret = { [RefInfo.MAKE_OBSERVED_PROXY]: new Proxy(target, RefInfo.arrayProxy) };
      } else if (target instanceof Set || SendableType.isSet(target) ||
        target instanceof Map || SendableType.isMap(target)) {
        console.log("### RefInfo.get not yet - set");
        ret = { [RefInfo.MAKE_OBSERVED_PROXY]: new Proxy(target, RefInfo.setMapProxy) };
      } else {
        console.log("### RefInfo.get not yet - some object");
        ret = { [RefInfo.MAKE_OBSERVED_PROXY]: new Proxy(target, RefInfo.objectProxy) };
      }
      RefInfo.obj2ref.set(target, ret);
    }
    console.log("### RefInfo.get end, target: " + JSON.stringify(target) + " ret: " + JSON.stringify(ret));
    return ret;
  }
}