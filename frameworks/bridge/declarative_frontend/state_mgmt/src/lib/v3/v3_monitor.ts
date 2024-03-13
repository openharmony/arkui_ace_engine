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
 * @Monitor function decorator implementation and supporting classes MonitorV3 and AsyncMonitorV3
 * 
 */


interface IMonitor {
 dirty: Array<string>;
 value<T>(path?: string): IMonitorValue<T> | undefined
}

interface IMonitorValue<T> {
  before: T;
  now: T;
  path: string;
}


class MonitorValueV3<T> {
  public before?: T
  public now?: T
  public path: string
  // properties on the path
  public props : string[];

  private dirty : boolean;

  constructor(path: string) {
    this.path = path;
    this.dirty = false;
    this.props = path.split(".")
  }

  setValue(isInit: boolean, newValue: T): boolean {
    this.now = newValue
    if (isInit) {
      this.before = this.now
    }
    this.dirty = this.before !== this.now;
    return this.dirty
  }

  // mv newValue to oldValue, set dirty to false
  reset() {
    this.before = this.now
    this.dirty = false
  }

  isDirty() {
    return this.dirty;
  }
}

/**
 * MonitorV3
 * one MonitorV3 object per @Monitor function
 * watchId - similar to elmtId, identify one MonitorV3 in Observe.idToCmp Map
 * observeObjectAccess = get each object on the 'path' to create dependency and add them with Observe.addRef
 * fireChange - exec @Monitor function and re-new dependencies with observeObjectAccess
 */


class MonitorV3 {
  public static readonly WATCH_PREFIX = "___watch_";
  public static readonly WATCH_INSTANCE_PREFIX = "___watch__obj_";

  // start with high number to avoid same id as elmtId for components.
  public static readonly MIN_WATCH_ID = 0x1000000000000;
  public static nextWatchId_ = MonitorV3.MIN_WATCH_ID;


  private values_: Array<MonitorValueV3<unknown>> = new Array<MonitorValueV3<unknown>>();
  private target_: object  // @Monitor function 'this': data object or ViewPU
  private monitorFunction: (m: IMonitor) => void;
  private watchId_: number;  // unique id, similar to elmtId but identifies this object

  constructor(target: object, pathsString: string, func: (m: IMonitor) => void) {
    this.target_ = target;
    this.monitorFunction = func;
    this.watchId_ = ++MonitorV3.nextWatchId_;

    // split space separated array of paths
    let paths = pathsString.split(/\s+/g)
    paths.forEach(path => this.values_.push(new MonitorValueV3<unknown>(path)))

    // add watchId to owning ViewPU or view model data object
    // ViewPU uses to call clearBinding(id)
    // FIXME data object leave data inside ObservedV3, because they can not 
    // call clearBinding(id) before they get deleted.
    const meta = target[MonitorV3.WATCH_INSTANCE_PREFIX]??={};
    meta[pathsString]=this.watchId_;
  }

  public getTarget() : Object {
    return this.target_;
  }

  /**
      Return array of those monitored paths
      that changed since previous invocation
   */
  public get dirty() : Array<string> {
    let ret = new Array<string>();
    this.values_.forEach(monitorValue => {
      if (monitorValue.isDirty()) {
        ret.push(monitorValue.path)
      }
    })
    return ret;
  }

  /**
   * return IMonitorValue for given path
   * or if no path is specified any dirty (changed) monitor value
   */
  public value<T>(path?: String): IMonitorValue<T> {
    for (let monitorValue of this.values_) {
      if ((path === undefined && monitorValue.isDirty()) || monitorValue.path === path) {
        return monitorValue as MonitorValueV3<T> as IMonitorValue<T>;
      }
    }
    return undefined
  }

  InitRun(): MonitorV3 {
    this.bindRun(true)
    return this
  }

  public notifyChange() {
    if (this.bindRun(/* is init / first run */ false)) {
      stateMgmtConsole.debug(`@Monitor function '${this.monitorFunction.name}' exec ...`);

      // exec @Monitor function
      this.monitorFunction.call(this.target_, this)

      // now -> before value
      this.reset()
    }
  }

  // called after @Monitor function call
  private reset() {
    this.values_.forEach(item => item.reset())
  }

  // analysisProp for each monitored path
  private bindRun(isInit: boolean = false): boolean {
    ObserveV3.getObserve().startBind(this, this.watchId_)
    let ret = false
    this.values_.forEach((item) => {
      let dirty = item.setValue(isInit, this.analysisProp(isInit, item))
      ret = ret || dirty
    })

    ObserveV3.getObserve().startBind(null, -1)
    return ret
  }

  // record / update object dependencies by reading each object along the path
  // return the value, i.e. the value of the last path item
  private analysisProp<T>(isInit: boolean, monitoredValue: MonitorValueV3<T>): T | undefined {
    let obj = this.target_;
    for (let prop of monitoredValue.props) {
      if (typeof obj=="object" &&  Reflect.has(obj, prop)) {
        obj = obj[prop]
      } else {
        isInit && stateMgmtConsole.warn(`watch prop "${monitoredValue.path}" initialize not found, make sure it exists!`)
        return undefined
      }
    }
    return obj as unknown as T;
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


// Performance Improvement
class AsyncAddMonitorV3 {
  static watches: any[] = []
  
  static addMonitor(target: any, name: string) {
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


/**
 * @Monitor("variable.path.expression [, variable.path.expression") function decorator
 */

const Monitor = function (path : string, ...paths: string[]) {
  const pathsUniqueString = paths? [path, ...paths].join(" ") : path;
  return function (target, _, descriptor) {
    stateMgmtConsole.debug(`@Monitor('${pathsUniqueString}')`);
    let watchProp = Symbol.for(MonitorV3.WATCH_PREFIX + target.constructor.name);
    const monitorFunc = descriptor.value;
    target[watchProp] ? target[watchProp][pathsUniqueString] = monitorFunc : target[watchProp] = { [pathsUniqueString]: monitorFunc }
  }
}
