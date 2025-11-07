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

class MonitorPathHelper {
  public static hasWildcardEnding(path: string): boolean {
    return path.endsWith('.*');
  }

  public static isWildcardPath(path: string): boolean {
    return path === '*';
  }

  // "a.b.c.*" => "a.b.c";
  public static pathBeforeWildcard(path: string): string {
    if (!MonitorPathHelper.hasWildcardEnding(path)) {
      return path;
    }
    return path.substring(0, path.length - 2);
  }

  public static isValid(path: string): boolean {
    let count = path.split('*').length - 1;
    // Allow top level "*"
    return ((count <= 0)
      || (count == 1 && (path.endsWith(".*") || (path == "*"))));
  }
}

class MonitorValueV2<T> {
  public before?: T;
  public now?: T;
  public path: string;
  // properties on the path
  public props: string[];
  public id: number;
  private dirty: boolean;
  // indicate the value is accessible or not
  // only used for AddMonitor
  private isAccessible: boolean;

  // Properties for wildcard suuport below:
  // Flag telling that this path is wildcard path
  // Wildcard path: objLevel00.objectLevel01.*
  // Last sure value path: objLevel00.objectLevel01
  private readonly wildCard: boolean;

  // Points from MonitorValueV2 with Last Sure Value path
  // to MonitorValueV2 with path including wildcard, "parent" path.
  // this.path: objLevel00.objectLevel01
  // this.wildcardPath_.path: objLevel00.objectLevel01.*
  private wildcardPath_: MonitorValueV2<T> | undefined;

  // Points from MonitorValueV2 with the path including wildcard
  // to MonitorValueV2 with the path to Last Sure Value
  // This MonitorValueV2 is created by the framework when it processes
  // path with the wildcard.
  // this.path: objLevel00.objectLevel01.*
  // this.lastSureValuePath_.path: objLevel00.objectLevel01
  private lastSureValuePath_: MonitorValueV2<T> | undefined;

  private addedByAPI_: boolean;

  constructor(path: string, apiAdded: boolean, id?: number) {
    this.path = path;
    this.dirty = false;
    this.props = path.split('.');
    this.wildCard = MonitorPathHelper.isWildcardPath(this.props[this.props.length - 1]);
    this.id = id ? id : -1;
    this.isAccessible = false;
    this.wildcardPath_ = undefined;
    this.lastSureValuePath_ = undefined;
    this.addedByAPI_ = apiAdded;
  }

  setValue(isInit: boolean, newValue: T): boolean {
    this.now = newValue;

    if (isInit) {
      this.before = this.now;
      this.isAccessible = true;
      // just init the before and now value not dirty in init
      return false;
    }

    if (this.id < MonitorV2.MIN_WATCH_FROM_API_ID) {
      // @Monitor
      // @Monitor does not care if the property is accessible or not, so ignore to set isAccessible
      this.dirty = this.before !== this.now;
    } else {
      // AddMonitor
      // consider value dirty if it wasn't accessible before setting the new value
      this.dirty = this.wildCard || (!this.isAccessible) || (this.before !== this.now);
      this.isAccessible = true;
    }
    return this.dirty;
  }

  setNotFound(isInit: boolean): boolean {
    if (!isInit && this.isAccessible) {
      this.dirty = true;
    }
    this.isAccessible = false;
    this.now = undefined;
    return this.dirty;
  }

  // mv newValue to oldValue, set dirty to false
  reset(): void {
    this.before = this.now;
    this.dirty = false;
  }

  isDirty(): boolean {
    return this.dirty;
  }

  isWildcard(): boolean {
    return this.wildCard;
  }

  isLastSureValue(): boolean {
    return this.wildcardPath_ !== undefined;
  }

  getWildcardPath(): MonitorValueV2<T> | undefined {
    return this.wildcardPath_;
  }

  setWildcardPath(childPath: MonitorValueV2<T> | undefined): void {
    this.wildcardPath_ = childPath;
  }

  getLastSureValuePath(): MonitorValueV2<T> | undefined {
    return this.lastSureValuePath_;
  }

  setLastSureValuePath(path: MonitorValueV2<T> | undefined): void {
    this.lastSureValuePath_ = path;
  }

  isAddedByAPi(): boolean {
    return this.addedByAPI_;
  }
  clearAddedByAPI() {
    this.addedByAPI_ = false;
  }
  setAddedByAPI() {
    this.addedByAPI_ = true;
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
  public static readonly SYNC_MONITOR_PREFIX = '___sync_monitor_';
  public static readonly OB_ANY = '___observe_any_property';

  // start with high number to avoid same id as elmtId for components/Computed.
  // 0 --- 0x1000000000 ----- 0x1000000000000 --------- 0x1010000000000 -------- 0x1015000000000 ---- 0x1020000000000 ----
  //  elementId       computedId              @Monitor                  MonitorAPI            MonitorAPIForSync    PersistenceV2
  public static readonly MIN_WATCH_ID = 0x1000000000000;
  public static readonly MIN_WATCH_FROM_API_ID = 0x1010000000000;
  public static readonly MIN_SYNC_WATCH_FROM_API_ID = 0x1015000000000;
  public static nextWatchId_ = MonitorV2.MIN_WATCH_ID;
  public static nextWatchApiId_ = MonitorV2.MIN_WATCH_FROM_API_ID;
  public static nextSyncWatchApiId_ = MonitorV2.MIN_SYNC_WATCH_FROM_API_ID;
  // count of currently running @Monitor functions
  public static runningCount: number = 0;

  private values_: Map<string, MonitorValueV2<unknown>> = new Map<string, MonitorValueV2<unknown>>();
  private target_: object; // @Monitor function 'this': data object or ViewV2
  private monitorFunction: (m: IMonitor) => void;
  private watchId_: number; // unique id, similar to elmtId but identifies this object
  private isSync_: boolean = false;
  private isDecorator_: boolean = true;

  constructor(target: object, pathsString: string, func: (m: IMonitor) => void, isDecorator: boolean, isSync: boolean = false) {
    this.target_ = target;
    this.monitorFunction = func;
    this.isDecorator_ = isDecorator;
    this.isSync_ = isSync;
    // split space separated array of paths
    let paths = pathsString.split(/\s+/g);

    if (this.isDecorator_) {
      this.watchId_ = ++MonitorV2.nextWatchId_;
      paths.forEach(path => {
        this.values_.set(path, new MonitorValueV2<unknown>(path, true));
      });
      this.monitorFunction = func;
    } else {
      this.watchId_ = this.isSync_ ? ++MonitorV2.nextSyncWatchApiId_ : ++MonitorV2.nextWatchApiId_;
      paths.forEach(path => {
        this.addPath(path, true);
      });
    }
  }

  public getTarget(): Object {
    return this.target_;
  }

  public isSync(): boolean {
    return this.isSync_;
  }

  public addPath(path: string, apiAdded: boolean): MonitorValueV2<unknown> {
    if (!MonitorPathHelper.isValid(path)) {
      stateMgmtConsole.applicationError(`AddMonitor/@SyncMonitor - not a valid path string '${path}'`);
      throw new Error(`AddMonitor/@SyncMonitor - not a valid path string  '${path}'`);
    }
    if (this.values_.has(path)) {
      stateMgmtConsole.applicationError(`AddMonitor ${this.getMonitorFuncName()} failed when adding path ${path} because duplicate key`);
      return this.values_.get(path)!;
    }
    let monitorValue = new MonitorValueV2<unknown>(path, apiAdded, this.isSync_ ? ++MonitorV2.nextSyncWatchApiId_ : ++MonitorV2.nextWatchApiId_)
    if (this.isSync_ && MonitorPathHelper.hasWildcardEnding(path)) {
      let lastSureValuePath = this.addPath(MonitorPathHelper.pathBeforeWildcard(path), false);
      lastSureValuePath.setWildcardPath(monitorValue);
      monitorValue.setLastSureValuePath(lastSureValuePath);
    }
    // Add wildcard path after last sure value path
    // Path with last sure value will be processed before path
    // with the wildcard on initial evaluation.
    this.values_.set(path, monitorValue);
    return monitorValue;
  }

  // lastSurePath true if we want to remove injected path to last sure value
  private doRemovePath(monitorValue: MonitorValueV2<unknown> | undefined, lastSurePath: boolean): boolean {
    if(monitorValue === undefined) {
      return false;
    }

    console.log("### doRemovePath: " + monitorValue.path + " LSV " + monitorValue.isLastSureValue() + " API " + monitorValue.isAddedByAPi());

    if (monitorValue.isLastSureValue() && monitorValue.isAddedByAPi())
    {
      if (lastSurePath) {
        console.log("### doRemovePath - clear setLastSureValuePath");
        monitorValue.setLastSureValuePath(undefined);
      } else {
        console.log("### doRemovePath - clear clearAddedByAPI");
        monitorValue.clearAddedByAPI();
      }
      return false;
    }

    if (!lastSurePath && !monitorValue.isAddedByAPi()) {
      return false;
    }

    if (lastSurePath && !monitorValue.isLastSureValue()) {
      return false;
    }

    console.log("### doRemovePath, removing " + monitorValue.path);
    const path = monitorValue.path;
    // In case wildcard path was added with AddMonitor API call
    if (this.isSync_ && monitorValue.isWildcard()) {
      this.doRemovePath(monitorValue.getLastSureValuePath(), true);
    }
    if (!(this.target_ instanceof PUV2ViewBase)) {
      WeakRefPool.clearMonitorId(this.target_, monitorValue.id);
    }
    ObserveV2.getObserve().clearBinding(monitorValue.id);
    delete ObserveV2.getObserve().id2Others_[monitorValue.id];
    this.values_.delete(path);
    return true;
  }

  public removePath(path: string): boolean {
    console.log("### removePath: " + path);
    const monitorValue = this.values_.get(path);
    return this.doRemovePath(monitorValue, false);
  }

  public getWatchId(): number {
    return this.watchId_;
  }

  public getMonitorFuncName(): string {
    return this.monitorFunction.name;
  }

  public getValues(): Map<string, MonitorValueV2<unknown>> {
    return this.values_;
  }

  /**
      Return array of those monitored paths
      that changed since previous invocation
   */
  public get dirty(): Array<string> {
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
  public value<T>(path?: string): IMonitorValue<T> {
    if (path) {
      return this.values_.get(path) as IMonitorValue<T>;
    }
    for (let monitorValue of this.values_.values()) {
      if (monitorValue.isDirty()) {
        return monitorValue as MonitorValueV2<T> as IMonitorValue<T>;
      }
    }
    return undefined;
  }

  InitRun(): MonitorV2 {
    // if @Monitor, run the bindRun which is the same logic as before
    if (this.isDecorator_) {
      this.bindRun(true);
      return this;
    }

    // AddMonitor, record dependencies for all path
    ObserveV2.getObserve().registerMonitor(this, this.watchId_);
    this.values_.forEach((monitorValue: MonitorValueV2<unknown>) => {
      // each path has its own id, and will be push into the stack
      // the state value will only collect the path id not the whole MonitorV2 id like the @Monitor does
      if (!(this.target_ instanceof PUV2ViewBase)) {
        WeakRefPool.addMonitorId(this.target_, monitorValue.id);
      }
      this.recordDependenciesForProp(monitorValue, true);
    })
    return this;
  }

  // Called by ObserveV2 once if any monitored path was dirty.
  // Executes the monitor function.
  public runMonitorFunction(): void {
    stateMgmtConsole.debug(`@Monitor function '${this.monitorFunction.name}' exec ...`);
    if (this.dirty.length === 0) {
      stateMgmtConsole.debug(`No dirty values! not firing!`);
      return;
    }
    try {
      // exec @Monitor/AddMonitor function
      MonitorV2.runningCount++;
      this.monitorFunction.call(this.target_, this);
    } catch (e) {
      stateMgmtConsole.applicationError(`AddMonitor exception caught for ${this.monitorFunction.name}`, e.toString());
      throw e;
    } finally {
      this.resetMonitor();
      MonitorV2.runningCount--;
    }
  }

  public notifyChange(): void {
    if (this.bindRun(/* is init / first run */ false)) {
      stateMgmtConsole.debug(`@Monitor function '${this.monitorFunction.name}' exec ...`);
      this.runMonitorFunction();
    }
  }

  // Only used for MonitorAPI: AddMonitor
  // Called by ObserveV2 when a monitor path has changed.
  // Analyze the changed path and return this Monitor's
  // watchId if the path was dirty and the monitor function needs to be executed later.
  public notifyChangeForEachPath(pathId: number): number {
    for (const monitorValue of this.values_.values()) {
      if (monitorValue.id === pathId) {
        return this.recordDependenciesForProp(monitorValue) ? this.watchId_ : -1;
      }
    }
    return -1;
  }
  // Only used for MonitorAPI: AddMonitor
  // record dependencies for given MonitorValue, when any monitored path
  // has changed and notifyChange is called
  private recordDependenciesForProp(monitoredValue: MonitorValueV2<unknown>, initRun = false): boolean {
    let success: boolean = false;
    let value = undefined;
    if (this.isSync_ && monitoredValue.isWildcard()) {
      let sureValue = monitoredValue.getLastSureValuePath()?.now
      if (sureValue === undefined && MonitorPathHelper.isWildcardPath(monitoredValue.path)) {
        // For single top level wildcard
        sureValue = this.target_;
      }
      if (sureValue !== undefined && (sureValue instanceof Object)) {
        ObserveV2.getObserve().startRecordDependencies(this, monitoredValue.id);
        if (ObserveV2.IsObservedObjectV2(sureValue)) {
          ObserveV2.getObserve().addRef(sureValue as unknown as Object, MonitorV2.OB_ANY);
        } else if (ObserveV2.IsProxiedObservedV2(sureValue) || ObserveV2.IsMakeObserved(sureValue)) {
          // Proxy handler will add ref to "make observed" container object
          sureValue[MonitorV2.OB_ANY];
        } else {
          // That should not happen
          // TODO: do we need it?
          ObserveV2.getObserve().addRef(sureValue as unknown as Object, MonitorV2.OB_ANY);
        }
        ObserveV2.getObserve().stopRecordDependencies();
        success = true;
      }
    } else {
      ObserveV2.getObserve().startRecordDependencies(this, monitoredValue.id);
      [success, value] = this.analysisProp(false, monitoredValue);
      ObserveV2.getObserve().stopRecordDependencies();
    }
    if (!success) {
      stateMgmtConsole.debug(`AddMonitor input path no longer valid.`);
      return monitoredValue.setNotFound(initRun);
    }
    let retValue = monitoredValue.setValue(initRun, value); // dirty?

    // Last sure value updated (that is path before ".*", fireChange called),
    // because of that we have to record dependency again for
    // the linked path that ends with '*' for the new last sure value object.
    // Code inside of the if statement below is not executed on initialisation
    // of the monitor, only on update of the last sure value.
    if (!initRun && (monitoredValue.getWildcardPath() !== undefined)) {
      this.recordDependenciesForProp(monitoredValue.getWildcardPath()!, true);
    }
    return retValue;
  }

  public notifyChangeOnReuse(): void {
    this.bindRun(true);
  }

  // called after @Monitor function call
  private resetMonitor(): void {
    this.values_.forEach(item => item.reset());
  }

  // analysisProp for each monitored path
  private bindRun(isInit: boolean = false): boolean {
    ObserveV2.getObserve().startRecordDependencies(this, this.watchId_);
    let ret = false;
    this.values_.forEach((item) => {
      const [success, value] = this.analysisProp(isInit, item);
      if (!success) {
        // cannot invoke setNotFound there, bindRun is only run in @Monitor 
        stateMgmtConsole.debug(`@Monitor path no longer valid.`);
        return;
      }
      let dirty = item.setValue(isInit, value);
      ret = ret || dirty;
    });

    ObserveV2.getObserve().stopRecordDependencies();
    return ret;
  }

  // record / update object dependencies by reading each object along the path
  // return the value, i.e. the value of the last path item
  private analysisProp<T>(isInit: boolean, monitoredValue: MonitorValueV2<T>): [success: boolean, value: T] {
    let obj = this.target_;
    for (let prop of monitoredValue.props) {
      if (obj && typeof obj === 'object' && Reflect.has(obj, prop)) {
        obj = obj[prop];
      } else {
        isInit && stateMgmtConsole.frequentApplicationError(`${this.debugInfo()} path ${monitoredValue.path} initialize not found, make sure it exists!`);
        return [false, undefined];
      }
    }
    return [true, obj as unknown as T];
  }

  public debugInfo(): string {
    return `@Monitor ${this.monitorFunction.name} owned by ${this.target_.constructor.name}`;
  }

  public static getMonitorIds(target: Object): number[] {
    let meta: Object;
    let meta1: Object;
    let monitorIds = [];
    if (target && typeof target === 'object') {
      // get @Monitor id
      meta = target[ObserveV2.MONITOR_REFS];
      if (meta && typeof meta === 'object') {
        monitorIds = Array.from(Object.values(meta)).map((monitor: MonitorV2) => monitor.watchId_);
      }
      // get AddMonitor id
      meta1 = target[ObserveV2.ADD_MONITOR_REFS];
      if (meta1 && typeof meta1 === 'object') {
        monitorIds = [...monitorIds, ...Array.from(Object.values(meta1)).map((monitor: MonitorV2) => monitor.watchId_)];
      }
    }

    return monitorIds;
  }

  public static clearWatchesFromTarget(target: Object): void {
    const monitorIds = MonitorV2.getMonitorIds(target);
    stateMgmtConsole.debug(`MonitorV2: clearWatchesFromTarget: from target ${target.constructor?.name} watchIds to clear ${JSON.stringify(monitorIds)}`);
    monitorIds.forEach((watchId) => {
      ObserveV2.getObserve().clearWatch(watchId);
      delete ObserveV2.getObserve().id2Others_[watchId];
    });
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
      ObserveV2.getObserve().constructSyncMonitors(item[0], item[1]);
    }
    AsyncAddMonitorV2.watches = [];
  }
}
