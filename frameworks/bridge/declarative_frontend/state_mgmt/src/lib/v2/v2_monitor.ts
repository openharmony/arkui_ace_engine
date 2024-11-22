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
 * 
 * This file includes only framework internal classes and functions 
 * non are part of SDK. Do not access from app.
 * 
 * It includes @Monitor function decorator  supporting classes MonitorV2 and AsyncMonitorV2
 * 
 */


class MonitorValueV2<T> {
  public before?: T;
  public now?: T;
  public path: string;
  public id: number;
  // properties on the path
  public props: string[];

  private dirty: boolean;
  private isPresent: boolean;

  constructor(path: string, id: number) {
    this.path = path;
    this.id = id;
    this.props = path.split('.');
    this.dirty = false;
    this.isPresent = false;
  }

  setValue(isInit: boolean, newValue: T): boolean {
    this.now = newValue;
    if (isInit) {
      this.before = this.now;
      this.isPresent = true;
      return false; // not dirty at init
    }
    // Consider value dirty if it wasn't present before setting the new value
    this.dirty = !this.isPresent || this.before !== this.now;
    this.isPresent = true;
    return this.dirty;
  }

  setNotFound(): void {
    this.isPresent = false;
    this.before = undefined;
  }

  // mv newValue to oldValue, set dirty to false
  reset(): void {
    this.before = this.now;
    this.dirty = false;
  }

  isDirty(): boolean {
    return this.dirty;
  }
}

/**
 * MonitorV2
 * one MonitorV2 object per @Monitor function
 * watchId - similar to elmtId, identify one MonitorV2 in Observe.idToCmp Map
 * observeObjectAccess = get each object on the 'path' to create dependency and add them with Observe.addRef
 * fireChange - exec @Monitor function and re-new dependencies with observeObjectAccess
 */


class MonitorV2 {
  public static readonly WATCH_PREFIX = '___watch_';
  public static readonly WATCH_INSTANCE_PREFIX = '___watch__obj_';

  // start with high number to avoid same id as elmtId for components.
  public static readonly MIN_WATCH_ID = 0x1000000000000;
  public static nextWatchId_ = MonitorV2.MIN_WATCH_ID;


  private values_: Array<MonitorValueV2<unknown>> = new Array<MonitorValueV2<unknown>>();
  private target_: object; // @Monitor function 'this': data object or ViewV2
  private monitorFunction: (m: IMonitor) => void;
  private watchId_: number; // unique id, similar to elmtId but identifies this object

  constructor(target: object, pathsString: string, func: (m: IMonitor) => void) {
    this.target_ = target;
    this.monitorFunction = func;
    this.watchId_ = ++MonitorV2.nextWatchId_;

    // split space separated array of paths
    let paths = pathsString.split(/\s+/g);
    paths.forEach(path => this.values_.push(new MonitorValueV2<unknown>(path, ++MonitorV2.nextWatchId_)));

    // add watchId to owning ViewV2 or view model data object
    // ViewV2 uses to call clearBinding(id)
    // FIXME data object leave data inside ObservedV2, because they can not 
    // call clearBinding(id) before they get deleted.
    const meta = target[MonitorV2.WATCH_INSTANCE_PREFIX] ??= {};
    meta[pathsString] = this.watchId_;
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
        ret.push(monitorValue.path);
      }
    });
    return ret;
  }

  /**
   * return IMonitorValue for given path
   * or if no path is specified any dirty (changed) monitor value
   */
  public value<T>(path?: String): IMonitorValue<T> {
    for (let monitorValue of this.values_) {
      if ((path === undefined && monitorValue.isDirty()) || monitorValue.path === path) {
        return monitorValue as MonitorValueV2<T> as IMonitorValue<T>;
      }
    }
    return undefined;
  }

  InitRun(): MonitorV2 {
    // Register this Monitor to known components
    ObserveV2.getObserve().registerMonitor(this, this.watchId_);

    // Record dependencies for all the paths
    this.values_.forEach((item) => {
      ObserveV2.getObserve().startRecordDependencies(this, item.id);
      const [success, value] = this.analysisProp(true, item);
      ObserveV2.getObserve().stopRecordDependencies();

      if (!success) {
        stateMgmtConsole.debug(`@Monitor path '${item.path}' not initially found`);
        return;
      }
      item.setValue(true, value);
    });

    return this;
  }

  // Called by ObserveV2 when a monitor path has changed.
  // Analyze the changed path and return this Monitor's
  // watchId if the path was dirty and the monitor function
  // needs to be executed later.
  public notifyChange(pathId: number): number {
    let value = this.values_.find((item) => item.id === pathId);
    stateMgmtConsole.debug(`@Monitor notifyChange for path ${value.path}`);
    return this.recordDependenciesForProp(value) ? this.watchId_ : -1;
  }

  // Called by ObserveV2 once if any monitored path was dirty.
  // Executes the monitor function.
  public runMonitorFunction(): void {
    if (this.dirty.length === 0) {
      stateMgmtConsole.debug(`No dirty values! not firing!`);
      return;
    }

    stateMgmtConsole.debug(`@Monitor function '${this.monitorFunction.name}' exec ...`);
    try {
      // exec @Monitor function
      this.monitorFunction.call(this.target_, this);
    } catch(e) {
      stateMgmtConsole.applicationError(`@Monitor exception caught for ${this.monitorFunction.name}`, e.toString());
      throw e;
    } finally {
      this.reset();
    }
  }

  // called after @Monitor function call
  private reset(): void {
    this.values_.forEach(item => item.reset());
  }

  // record dependencies for given MonitorValue, when any monitored path
  // has changed and notifyChange is called
  private recordDependenciesForProp<T>(monitoredValue: MonitorValueV2<T>): boolean {
    ObserveV2.getObserve().startRecordDependencies(this, monitoredValue.id);
    const [success, value] = this.analysisProp(false, monitoredValue);
    ObserveV2.getObserve().stopRecordDependencies();

    if (!success) {
      stateMgmtConsole.debug(`@Monitor path '${monitoredValue.path}' no longer valid.`);
      monitoredValue.setNotFound();
      return false;
    }
    return monitoredValue.setValue(false, value); // dirty?
  }

  // record / update object dependencies by reading each object along the path
  // return the value, i.e. the value of the last path item
  private analysisProp<T>(isInit: boolean, monitoredValue: MonitorValueV2<T>): [success: boolean, value : T] {
    let parentObj = this.target_; // main pointer
    let specialCur; // special pointer for Array
    let obj; // main property
    let lastProp; // last property name in path
    let specialProp; // property name for Array
    let props = monitoredValue.props; // get the props
    for (let i = 0; i < props.length; i++) {
      lastProp = props[i]; // get the current property name
      if (parentObj && typeof parentObj === 'object' && Reflect.has(parentObj, lastProp)) {
        obj = parentObj[lastProp]; // store property value, obj maybe Proxy added by V2
        if (Array.isArray(UIUtilsImpl.instance().getTarget(obj))) {
          // if obj is Array, store the infomation at the 'first' time.
          // if we reset the specialCur, that means we do not need to care Array.
          if (!specialCur) {
            // only for the 'first' time, store infomation.
            // this is for multi-dimension array, only the first Array need to be checked.
            specialCur = parentObj;
            specialProp = lastProp;
          }
        } else {
          if (specialCur && i === props.length - 1) {
            // if final target is the item of Array, return to use special info.
            break;
          } else {
            // otherwise turn back to normal property read...
            specialCur = undefined;
          }
        }
        if (i < props.length - 1) {
          // move the parentObj to its property, and go on
          parentObj = obj;
        }
      } else {
        isInit && stateMgmtConsole.warn(`@Monitor prop ${monitoredValue.path} initialize not found, make sure it exists!`);
        return [false, undefined];
      }
    }
    if (specialCur) {
      // if case for Array, use special info..
      lastProp = specialProp;
      parentObj = specialCur;
    }
    if (!ObserveV2.IsMakeObserved(obj) && !ObserveV2.IsTrackedProperty(parentObj, lastProp)) {
      stateMgmtConsole.applicationError(`@Monitor "${monitoredValue.path}" cannot be monitored, make sure it is decorated !!`);
      return [false, undefined];
    }
    return [true, obj as unknown as T];
  }

  public static clearWatchesFromTarget(target: Object): void {
    let meta: Object;
    if (!target || typeof target !== 'object' ||
        !(meta = target[MonitorV2.WATCH_INSTANCE_PREFIX]) || typeof meta !== 'object') {
      return;
    }

    stateMgmtConsole.debug(`MonitorV2: clearWatchesFromTarget: from target ${target.constructor?.name} watchIds to clear ${JSON.stringify(Array.from(Object.values(meta)))}`);
    Array.from(Object.values(meta)).forEach((watchId) => ObserveV2.getObserve().clearWatch(watchId));
  }
}


// Performance Improvement
class AsyncAddMonitorV2 {
  static watches: any[] = [];
  
  static addMonitor(target: any, name: string): void {
    if (AsyncAddMonitorV2.watches.length === 0) {
      Promise.resolve(true)
      .then(AsyncAddMonitorV2.run)
      .catch(error => {
        stateMgmtConsole.applicationError(`Exception caught in @Monitor function ${name}`, error);
        _arkUIUncaughtPromiseError(error);
      });
    }
    AsyncAddMonitorV2.watches.push([target, name]);
  }

  static run(): void {
    for (let item of AsyncAddMonitorV2.watches) {
      ObserveV2.getObserve().constructMonitor(item[0], item[1]);
    }
    AsyncAddMonitorV2.watches = [];
  }
}
