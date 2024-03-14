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



/**
 * @monitor function decorator implementation and supporting classes MonitorV3 and AsyncMonitorV3
 */

/**
 * MonitorV3
 * one MonitorV3 object per @monitor function
 * watchId - similar to elmtId, identify one MonitorV3 in Observe.idToCmp Map
 * observeObjectAccess = get each object on the 'path' to create dependency and add them with Observe.addRef
 * fireChange - exec @monitor function and re-new dependencies with observeObjectAccess
 */
class MonitorV3 {
  //0x1.0000.0000.0000,
  // start with high number to avoid same id as elmtId for components.
  public static readonly MIN_WATCH_ID = 0x1000000000000;
  public static nextWatchId_ = MonitorV3.MIN_WATCH_ID;

  private value_: any; 
  private props_: string[]; 
  private target_: WeakRef<object>;
  private func_: (val: any) => void; 
  private watchId_: number; 

  // added to the prototype of target, 
  // ViewPU extended class prototype, or @Observed class proto
  public static readonly WATCH_PREFIX = "__wa_";

  // added to target, ie. to extended ViewPU or @Observed class object instance
  private static readonly WATCH_INSTANCE_PREFIX = Symbol("__wa_instance_");

  constructor(target: object, props: string, func: (val: any) => void) {
    ConfigureStateMgmt.instance.intentUsingV3(`@monitor`, props);
    this.target_ = new WeakRef<Object>(target);
    this.func_ = func;
    this.watchId_ = ++MonitorV3.nextWatchId_;
    this.props_ = props.split(".");
    const meta = target[MonitorV3.WATCH_INSTANCE_PREFIX]??={};
    meta[props]=this.watchId_;
  }

  public getTarget() : Object {
    return this.target_;
  }

  public InitRun(): number {
    this.value_ = this.observeObjectAccess(true);
    return this.watchId_;
  }

  public fireChange(): void {
    let newVal = this.observeObjectAccess();
    if (this.value_ !== newVal) {
      let target: Object | undefined;
      if (target=this.target_.deref()) {
        stateMgmtConsole.debug(`@monitor(${this.props_.toString()}) function exec ...`);
        this.func_.call(target, newVal, this.value_)
      }
      this.value_ = newVal
    }
  }

  // register current watchId while exec. analysisPath
  private observeObjectAccess(isInit: boolean = false): Object | undefined {
    ObserveV3.getObserve().startBind(this, this.watchId_);
    let ret = this.analysisPath(isInit);
    ObserveV3.getObserve().startBind(null, 0);
    return ret;
  }

  // traverse objects on the given monitor path and add dependency for
  // watchId to each of the,
  // this needs to be done at @monitor init and repeated every time
  // one of the objects has changes
  private analysisPath(isInit: boolean): Object | undefined {
    let obj = this.target_.deref();
    for (const prop of this.props_) {
      if (obj && typeof obj=="object" && Reflect.has(obj, prop)) {
        obj = obj[prop]
      } else {
        isInit && stateMgmtConsole.warn(`@monitor("${this.props_.join(".")}"): path currently does not exist (can be ok when monitoring union type values)`)
        return undefined;
      }
    }
    return obj
  }

  public static clearWatchesFromTarget(target: Object): void {
    let meta: Object;
    if (!target || typeof target !== "object"
      || !(meta = target[MonitorV3.WATCH_INSTANCE_PREFIX]) || typeof meta != "object") {
      return;
    }

    stateMgmtConsole.debug(`MonitorV3: clearWatchesFromTarget: from target ${target.constructor?.name} watchIds to clear ${JSON.stringify(Array.from(Object.values(meta)))}`);
    Array.from(Object.values(meta)).forEach((watchId) => ObserveV3.getObserve().clearWatch(watchId));
  }
}

/**
 * @monitor("variable.path.expression") function decorator
 */

 const monitor = function (key) {
  return function (target, _, descriptor) {
    stateMgmtConsole.debug(`@monitor('${key}')`);
    let watchProp = Symbol.for(MonitorV3.WATCH_PREFIX + target.constructor.name)
    target[watchProp] ? target[watchProp][key] = descriptor.value 
                      : target[watchProp] = { [key]: descriptor.value }
  }
}


// Performance Improvement
class AsyncAddMonitorV3 {
  static watches: any[] = []

  static addWatch(target: any, name: string) {
    if (AsyncAddMonitorV3.watches.length === 0) {
      Promise.resolve(true).then(AsyncAddMonitorV3.run)
    }
    AsyncAddMonitorV3.watches.push([target, name])
  }

  static run() {
    for (let item of AsyncAddMonitorV3.watches) {
      ObserveV3.getObserve().constructMonitor(item[0], item[1])
    }
    AsyncAddMonitorV3.watches=[];
  }
}
