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

class UIUtilsImpl {
    private static instance_: UIUtilsImpl = undefined;

    public getTarget<T extends Object>(source: T): T {
      if (!source || typeof source !== 'object') {
        return source;
      }
      if (ObservedObject.IsObservedObject(source)) {
        // V1 Proxy object
        return ObservedObject.GetRawObject(source);
      } else if (source[ObserveV2.SYMBOL_PROXY_GET_TARGET]) {
        // V2 Proxy object
        return source[ObserveV2.SYMBOL_PROXY_GET_TARGET];
      } else {
        // other situation, not handle
        return source;
      }
    }

    public makeObserved<T extends object>(target: T): T {
      // mark makeObserved using V2 feature
      ConfigureStateMgmt.instance.usingV2ObservedTrack('makeObserved', 'use');
      return RefInfo.get(target)[RefInfo.MAKE_OBSERVED_PROXY] as T;
    }

    public makeV1Observed<T extends object>(target: T): T {
      // Make non-observed data into observed V1 data
      return ObservedObject.makeV1Observed(target);
    }

    public enableV2Compatibility<T extends object>(target: T): T {
      // Enables V2 compatibility for the given object and all its nested objects
      ObservedObject.enableV2Compatible(target);
      return target;
    }

    // Function overloading.
    public makeBinding<T>(getter: () => T): Binding<T>;
    public makeBinding<T>(getter: () => T, setter: (newValue: T) => void): MutableBinding<T>;
    public makeBinding<T>(getter: () => T, setter?:
    (newValue: T) => void): Binding<T> | MutableBinding<T> {
      return setter ? new MutableBinding(getter, setter) : new Binding(getter);
    }

    public addMonitor(target: object, path: string | string[], monitorFunc: MonitorCallback, options?: MonitorOptions): void {
      if (!target || typeof target !== 'object' || !(ObserveV2.IsObservedObjectV2(target) ||  target instanceof ViewV2)) {
        const message = `addMonitor failed because the target is illegal. The target must be an instance of @ObservedV2 (with at least one @Trace, @Computed, or @Monitor inside) or @ComponentV2.`;
        stateMgmtConsole.applicationError(message);
        throw new BusinessError(ADD_MONITOR_FAIL_TARGET_ILLEGAL, message);
      }
      if (!(typeof path === 'string' || Array.isArray(path))) {
        const message = `addMonitor failed because path must be string or Array of string.`;
        stateMgmtConsole.applicationError(message);
        throw new BusinessError(ADD_MONITOR_FAIL_PATH_ILLEGAL, message);
      }
      
      if (typeof monitorFunc !== 'function' || !monitorFunc.name) {
        const message = `addMonitor failed because the monitorFunc is illegal, monitorFunc must be function or but cannot be an anonymous function.`;
        stateMgmtConsole.applicationError(message);
        throw new BusinessError(ADD_MONITOR_FAIL_FUNC_ILLEGAL, message);
      }
      ObserveV2.getObserve().AddMonitorPath(target, path, monitorFunc, options);
    }
        
    public clearMonitor(target: object, path: string | string[], monitorFunc: MonitorCallback): void {
      if (!target || typeof target !== 'object' || !(ObserveV2.IsObservedObjectV2(target) ||  target instanceof ViewV2)) {
        const message = `clearMonitor failed because the target is illegal. The target must be an instance of @ObservedV2 (with at least one @Trace, @Computed, or @Monitor inside) or @ComponentV2.`;
        stateMgmtConsole.applicationError(message);
        throw new BusinessError(ADD_MONITOR_FAIL_TARGET_ILLEGAL, message);
      }
      if (!(typeof path === 'string' || Array.isArray(path))) {
        const message = `clearMonitor failed because path must be string or Array of string.`;
        stateMgmtConsole.applicationError(message);
        throw new BusinessError(ADD_MONITOR_FAIL_PATH_ILLEGAL, message);
      }
      
      if (monitorFunc && (typeof monitorFunc !== 'function' || !monitorFunc.name)) {
        const message = `clearMonitor failed because the monitorFunc is illegal, monitorFunc must be function or but cannot be an anonymous function.`;
        stateMgmtConsole.applicationError(message);
        throw new BusinessError(ADD_MONITOR_FAIL_FUNC_ILLEGAL, message);
      }
      ObserveV2.getObserve().clearMonitorPath(target, path, monitorFunc);
    }

    public static instance(): UIUtilsImpl {
      if (UIUtilsImpl.instance_) {
        return UIUtilsImpl.instance_;
      }
      UIUtilsImpl.instance_ = new UIUtilsImpl();
      return UIUtilsImpl.instance_;
    }
}