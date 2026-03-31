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

  public static isWildcardSubPath(path: string): boolean {
    return path === '*';
  }

  // 'a.b.c.*' => 'a.b.c';
  public static pathBeforeWildcard(path: string): string {
    if (!MonitorPathHelper.hasWildcardEnding(path)) {
      return path;
    }
    return path.substring(0, path.length - 2);
  }

  public static isValid(path: string, wildcardEnabled: boolean): boolean {
    return wildcardEnabled
      ? MonitorPathHelper.isValidWildcardPath(path)
      : MonitorPathHelper.isValidNoWildcardPath(path);
  }

  public static isValidWildcardPath(path: string): boolean {
    let count = path.split('*').length - 1;
    return ((count <= 0) || (count === 1 && path.endsWith('.*')));
  }

  public static isValidNoWildcardPath(path: string): boolean {
    return !path.includes('*');
  }
}

class MonitorValueV2<T> {
  public before?: T;
  public now?: T;
  public path: string;
  private reportedPath_: string;
  // properties on the path
  public props: string[];
  public id: number;
  private dirty: boolean;
  // indicate the value is accessible or not
  // only used for AddMonitor
  private isAccessible: boolean;

  // Properties for wildcard support below:
  // Flag telling that this path is a wildcard path
  // Wildcard path: objLevel00.objectLevel01.*
  // Last sure value path: objLevel00.objectLevel01
  private readonly wildCard_: boolean;

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

  constructor(path: string, id?: number) {
    this.path = path;
    this.reportedPath_ = path;
    this.dirty = false;
    this.props = path.split('.');
    this.wildCard_ = MonitorPathHelper.isWildcardSubPath(this.props[this.props.length - 1]);
    this.id = id ? id : -1;
    this.isAccessible = false;
    this.wildcardPath_ = undefined;
    this.lastSureValuePath_ = undefined;
  }

  setValue(isInit: boolean, newValue: T): boolean {
    this.now = newValue;

    if (isInit) {
      this.before = this.now;
      this.isAccessible = true;
      // just init the before and now value not dirty in init
      return false;
    }

    if (this.id < MonitorV2.MIN_MONITOR_WITH_OPTIONS_OR_ASYNC_API_ID) {
      // @Monitor without options branch
      // @Monitor does not care if the property is accessible or not, so ignore to set isAccessible
      this.dirty = this.before !== this.now;
    } else {
      // AddMonitor, @SyncMonitor, @Monitor with options
      // consider value dirty if it wasn't accessible before setting the new value
      this.dirty = this.wildCard_ || (!this.isAccessible) || (this.before !== this.now);
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
    return this.wildCard_;
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

  getReportedPath(): string {
    return this.reportedPath_;
  }
  setReportedPath(path): void {
    this.reportedPath_ = path;
  }
}

enum MonitorType {
  MONITOR_DECORATOR = '@Monitor',
  SYNC_MONITOR_DECORATOR = '@SyncMonitor',
  MONITOR_WITH_OPTIONS_DECORATOR = '@Monitor(options)',
  ADD_MONITOR_API = 'AddMonitor API'
}

/**
 * MonitorV2
 * one MonitorV2 object per @Monitor function
 * monitorId - similar to elmtId, identify one MonitorV2 in Observe.idToCmp Map
 * observeObjectAccess = get each object on the 'path' to create dependency and add them with Observe.addRef
 * fireChange - exec @Monitor function and re-new dependencies with observeObjectAccess
 */

class MonitorV2 {
  // Decorator populated property names prefixes, no prefix for AddMonitor API, not a decorator:
  public static readonly MONITOR_ORIG_PREFIX = '___monitor_orig_';
  public static readonly MONITOR_WITH_OPTIONS_PREFIX = '___monitor_with_options_';
  public static readonly SYNC_MONITOR_PREFIX = '___sync_monitor_';

  public static readonly OB_ANY = '___observe_any_property';
  public static readonly LSV_PREFIX = '000_lsv_';
  private static readonly MONITOR_PATH_NOT_FOUND = Symbol('MONITOR_PATH_NOT_FOUND');
  // start with high number to avoid same id as elmtId for components/Computed.
  // 0 --- 0x1000000000 ----- 0x1000000000000 --------- 0x1010000000000 -------- 0x1015000000000 ---- 0x1020000000000 ----
  //  elementId       computedId              @Monitor                  MonitorAPI            MonitorAPIForSync    PersistenceV2
  public static readonly MIN_MONITOR_ORIG_ID = 0x1000000000000;
  public static readonly MIN_MONITOR_WITH_OPTIONS_OR_ASYNC_API_ID = 0x1010000000000;
  public static readonly MIN_SYNC_MONITOR_OR_SYNC_API_ID = 0x1015000000000;
  public static nextMonitorId_ = MonitorV2.MIN_MONITOR_ORIG_ID;
  public static nextMonitorWithOptionsOrAsyncApiId_ = MonitorV2.MIN_MONITOR_WITH_OPTIONS_OR_ASYNC_API_ID;
  public static nextSyncMonitorOrSyncApiId_ = MonitorV2.MIN_SYNC_MONITOR_OR_SYNC_API_ID;
  // count of currently running @Monitor functions
  public static runningCount: number = 0;

  private values_: Map<string, MonitorValueV2<unknown>> = new Map<string, MonitorValueV2<unknown>>();
  private target_: object; // @Monitor function 'this': data object or ViewV2
  private monitorFunction: (m: IMonitor) => void;
  private monitorId_: number; // unique id, similar to elmtId but identifies this object
  private isSync_: boolean = false;
  private isWildcardEnabled_: boolean = false;
  private monitorType_: MonitorType;
  private isSyncMonitorDecorator_: boolean;
  private isMonitorDecorator_: boolean;
  private isMonitorWithOptionsDecorator_: boolean;

  constructor(target: object, pathsString: string, func: (m: IMonitor) => void,
    type: MonitorType, isSync: boolean = false, wildcardEnabled = false) {
    this.monitorType_ = type;
    this.target_ = target;
    this.monitorFunction = func;
    this.isSync_ = isSync;
    this.isWildcardEnabled_ = wildcardEnabled;
    // split space separated array of paths
    let paths = pathsString.split(/\s+/g);

    this.isSyncMonitorDecorator_ = type === MonitorType.SYNC_MONITOR_DECORATOR;
    this.isMonitorDecorator_ = type === MonitorType.MONITOR_DECORATOR;
    this.isMonitorWithOptionsDecorator_ = type === MonitorType.MONITOR_WITH_OPTIONS_DECORATOR;

    // Original @Monitor without options
    if (this.isMonitorDecorator()) {
      this.monitorId_ = ++MonitorV2.nextMonitorId_;
      paths.forEach(path => {
        if (!MonitorPathHelper.isValidNoWildcardPath(path)) {
          stateMgmtConsole.applicationError(this.errorMessage(path, 'not a valid path string'));
          return;
        }
        this.values_.set(path, new MonitorValueV2<unknown>(path));
      });
      this.monitorFunction = func;
      return;
    }

    // @SyncMonitor, addMonitor API, @Monitor with options
    this.monitorId_ = this.isSync_ ? ++MonitorV2.nextSyncMonitorOrSyncApiId_ : ++MonitorV2.nextMonitorWithOptionsOrAsyncApiId_;
    paths.forEach(path => {
      this.addPath(path);
    });
  }

  public getTarget(): Object {
    return this.target_;
  }

  public isSync(): boolean {
    return this.isSync_;
  }

  public isWildcardEnabled(): boolean {
    return this.isWildcardEnabled_;
  }

  // path - path to monitored value separated with dots
  // @Monitor does not use addPath method
  public addPath(path: string, lsv: boolean = false): MonitorValueV2<unknown> | undefined {
    if (!MonitorPathHelper.isValid(path, this.isWildcardEnabled())) {
      stateMgmtConsole.applicationError(this.errorMessage(path, 'not a valid path string'));
      return undefined;
    }
    const pathkey = (lsv? MonitorV2.LSV_PREFIX : '') + path;
    if (this.values_.has(pathkey)) {
      stateMgmtConsole.applicationError(this.errorMessage(path, 'failed when adding duplicate path'));
      let monitorPath = this.values_.get(pathkey)!;
      return monitorPath;
    }
    let monitorValue = new MonitorValueV2<unknown>(path, this.isSync_ ? ++MonitorV2.nextSyncMonitorOrSyncApiId_ : ++MonitorV2.nextMonitorWithOptionsOrAsyncApiId_)
    if (!lsv && this.isWildcardEnabled() && MonitorPathHelper.hasWildcardEnding(path)) {
      let lastSureValuePath = this.addPath(MonitorPathHelper.pathBeforeWildcard(path), true);
      lastSureValuePath?.setWildcardPath(monitorValue);
      lastSureValuePath?.setReportedPath(path);
      monitorValue.setLastSureValuePath(lastSureValuePath);
    }
    // Add wildcard path after last sure value path
    // Path with last sure value will be processed before path
    // with the wildcard on initial evaluation.
    this.values_.set(pathkey, monitorValue);
    return monitorValue;
  }

  private doRemovePath(path: string, monitorValue?: MonitorValueV2<unknown>): boolean {
    if (monitorValue) {
      if (!(this.target_ instanceof PUV2ViewBase)) {
        WeakRefPool.clearMonitorId(this.target_, monitorValue.id);
      }
      ObserveV2.getObserve().clearBinding(monitorValue.id);
      delete ObserveV2.getObserve().id2Others_[monitorValue.id];
      this.values_.delete(path);
      return true;
    }
    return false;
  }

  public removePath(path: string): boolean {
    const monitorValue = this.values_.get(path);
    if (monitorValue && monitorValue.isWildcard()) {
      const lsvPath = MonitorV2.LSV_PREFIX + MonitorPathHelper.pathBeforeWildcard(path);
      this.doRemovePath(lsvPath, monitorValue.getLastSureValuePath())
    }

    return this.doRemovePath(path, monitorValue);
  }

  // Returns true for @SyncMonitor
  public isSyncMonitorDecorator(): boolean {
    return this.isSyncMonitorDecorator_;
  }

  public isMonitorDecorator(): boolean {
    return this.isMonitorDecorator_;
  }

  public isMonitorWithOptionsdDecorator(): boolean {
    return this.isMonitorWithOptionsDecorator_;
  }

  public getMonitorId(): number {
    return this.monitorId_;
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
        ret.push(monitorValue.getReportedPath());
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
      const monitorValue = this.values_.get(path);
      if (monitorValue === undefined) {
        return undefined;
      }
      return monitorValue.isWildcard() ? undefined : monitorValue as IMonitorValue<T>;
    }
    for (let monitorValue of this.values_.values()) {
      if (monitorValue.isDirty() && !monitorValue.isWildcard()) {
        return monitorValue as MonitorValueV2<T> as IMonitorValue<T>;
      }
    }
    return undefined;
  }

  InitRun(): MonitorV2 {
    // if @Monitor, run the bindRun which is the same logic as before
    if (this.isMonitorDecorator()) {
      this.bindRun(true);
      return this;
    }

    // AddMonitor, record dependencies for all path
    ObserveV2.getObserve().registerMonitor(this, this.monitorId_);
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

  // re-record the dependencies for each path / MonitorValueV2
  // invoked on @ReusableV2 re-use, see ViewV2.resetAllMonitorsOnReuse
  public recordDependenciesForProps(): void {
    this.values_.forEach((monitorValue: MonitorValueV2<unknown>) => {
      // set initRun: true, pretend this is a first run, do not mark dirty on path value change  
      this.recordDependenciesForProp(monitorValue, true);
    });
  }

  // Called by ObserveV2 once if any monitored path was dirty.
  // Executes the monitor function.
  public runMonitorFunction(): void {
    stateMgmtConsole.debug(`${this.getDecoratorName()} function '${this.monitorFunction.name}' exec ...`);
    if (this.dirty.length === 0) {
      stateMgmtConsole.debug(`No dirty values! not firing!`);
      return;
    }
    try {
      // exec @Monitor/AddMonitor/@SyncMonitor function
      MonitorV2.runningCount++;
      this.monitorFunction.call(this.target_, this);
    } catch (e) {
      stateMgmtConsole.applicationError(`${this.getDecoratorName()} exception caught for ${this.monitorFunction.name}`, e.toString());
      throw e;
    } finally {
      this.resetMonitor();
      MonitorV2.runningCount--;
    }
  }

  public notifyChange(): void {
    if (this.bindRun(/* is init / first run */ false)) {
      stateMgmtConsole.debug(`${this.getDecoratorName()} function '${this.monitorFunction.name}' exec ...`);
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
        return this.recordDependenciesForProp(monitorValue) ? this.monitorId_ : -1;
      }
    }
    return -1;
  }
  // Only used for MonitorAPI: AddMonitor
  // record dependencies for given MonitorValue, when any monitored path
  // has changed and notifyChange is called
  private recordDependenciesForProp(monitoredValue: MonitorValueV2<unknown>, initRun = false): boolean {
    let success: boolean = false;
    let value: unknown | Symbol = undefined;
    if (this.isWildcardEnabled() && monitoredValue.isWildcard()) {
      let lastSureValue = monitoredValue.getLastSureValuePath()?.now
      if (lastSureValue !== undefined && (lastSureValue instanceof Object)) {
        ObserveV2.getObserve().startRecordDependencies(this, monitoredValue.id);
        if (ObserveV2.IsProxiedObservedV2OrMakeObserved(lastSureValue)) {
          // Proxy handler will add ref to 'make observed' container object
          lastSureValue[MonitorV2.OB_ANY];
        } else {
          // Regular ObservedV2 object
          // ObserveV2.IsObservedObjectV2(lastSureValue) === true
          ObserveV2.getObserve().addRef(lastSureValue as unknown as Object, MonitorV2.OB_ANY);
        }
        ObserveV2.getObserve().stopRecordDependencies();
        success = true;
      }
    } else {
      ObserveV2.getObserve().startRecordDependencies(this, monitoredValue.id);
      value = this.analysisProp(initRun, monitoredValue);
      success = value !== MonitorV2.MONITOR_PATH_NOT_FOUND;
      ObserveV2.getObserve().stopRecordDependencies();
    }
    if (!success) {
      stateMgmtConsole.debug(this.errorMessage(monitoredValue.getReportedPath(), 'input path no longer valid.'));
      return monitoredValue.setNotFound(initRun);
    }
    let retValue = monitoredValue.setValue(initRun, value);

    // Last sure value updated (that is path before '.*', fireChange called),
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
    ObserveV2.getObserve().startRecordDependencies(this, this.monitorId_);
    let ret = false;
    this.values_.forEach((item) => {
      const value = this.analysisProp(isInit, item);
      if (value === MonitorV2.MONITOR_PATH_NOT_FOUND) {
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
  private analysisProp<T>(isInit: boolean, monitoredValue: MonitorValueV2<T>): T | Symbol {
    let obj = this.target_;
    for (let prop of monitoredValue.props) {
      if (obj && typeof obj === 'object' && Reflect.has(obj, prop)) {
        obj = obj[prop];
      } else {
        isInit && stateMgmtConsole.frequentApplicationError(this.errorMessage(monitoredValue.getReportedPath(), 'initialize not found, make sure it exists!'));
        return MonitorV2.MONITOR_PATH_NOT_FOUND;
      }
    }
    return obj as unknown as T;
  }

  public getDecoratorName(): string {
    return this.monitorType_;
  }

  public errorMessage(path: string, description: string): string {
    return `${this.getDecoratorName()} '${this.monitorFunction.name}' owned by '${this.target_.constructor.name}' path: '${path}' - ${description}`;
  }

  public static getMonitorIds(target: Object): number[] {
    let meta: Object;
    let meta1: Object;
    let monitorIds = [];
    if (target && typeof target === 'object') {
      // get @Monitor id
      meta = target[ObserveV2.MONITOR_REFS];
      if (meta && typeof meta === 'object') {
        monitorIds = Array.from(Object.values(meta)).map((monitor: MonitorV2) => monitor.monitorId_);
      }
      // get AddMonitor id
      meta1 = target[ObserveV2.ADD_MONITOR_API_REFS];
      if (meta1 && typeof meta1 === 'object') {
        monitorIds = [...monitorIds, ...Array.from(Object.values(meta1)).map((monitor: MonitorV2) => monitor.monitorId_)];
      }
      // get @SyncMonitor id or @Monitor with options id
      meta1 = target[ObserveV2.MONITOR_WITH_OPTIONS_OR_SYNC_MONITOR_REFS];
      if (meta1 && typeof meta1 === 'object') {
        monitorIds = [...monitorIds, ...Array.from(Object.values(meta1)).map((monitor: MonitorV2) => monitor.monitorId_)];
      }
    }

    return monitorIds;
  }

  public static clearWatchesFromTarget(target: Object): void {
    const monitorIds = MonitorV2.getMonitorIds(target);
    stateMgmtConsole.debug(`MonitorV2: clearWatchesFromTarget: from target ${target.constructor?.name} monitorIds to clear ${JSON.stringify(monitorIds)}`);
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
      ObserveV2.getObserve().constructMonitorsWithOptions(item[0], item[1]);
    }
    AsyncAddMonitorV2.watches = [];
  }
}
