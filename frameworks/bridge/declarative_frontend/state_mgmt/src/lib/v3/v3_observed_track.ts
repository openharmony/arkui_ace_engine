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
 * @ObservedV2 class and @trace class property decorators
 * ObserveV3 core helper class to keep track of all the object -> UINode/elmtId 
 * Monitor/watchId, Computed/computedId dependencies.
 */

class ObserveV3 {
  public static readonly V3_DECO_META = Symbol('__v3_deco_meta__'); 
  public static readonly SYMBOL_REFS = Symbol('__use_refs__');
  public static readonly ID_REFS = Symbol('__id_refs__');

  private static readonly SYMBOL_PROXY_GET_TARGET = Symbol("__proxy_get_target");

  public static readonly OB_PREFIX = "__ob_";  // OB_PREFIX + attrName => backing store attribute name
  public static readonly OB_PREFIX_LEN = 5;

  // used by array Handler to create dependency on artificial "length"
  // property of array, mark it as changed when array has changed.
  private static readonly OB_LENGTH = "___obj_length"; 
  private static readonly OB_MAP_SET_ANY_PROPERTY = "___ob_map_set"; 
  private static readonly OB_DATE = "__date__";

  // see MonitorV3.observeObjectAccess: bindCmp is the MonitorV3
  // see modified observeComponentCreation, bindCmp is the ViewPU
  private bindCmp_:  ViewPU | MonitorV3 | ComputedV3 | null = null;

  // bindId: UINode elmtId or watchId, depending on what is being observed
  private bindId_: number = UINodeRegisterProxy.notRecordingDependencies;

  // Map bindId to WeakRef<ViewPU> | MonitorV3
  private id2cmp_: { number: object } = {} as { number: object }

  // Map bindId -> Set of @observed class objects
  // reverse dependency map for quickly removing all dependencies of a bindId
  private id2targets_: { number: object } = {} as { number: object }

  // queued up Set of bindId
  // elmtIds of UINodes need re-render
  // @monitor functions that need to execute
  private elmtIdsChanged_: Set<number> = new Set()
  private computedPropIdsChanged_: Set<number> = new Set()
  private monitorIdsChanged_: Set<number> = new Set()

  // avoid recursive execution of updateDirty
  // by state changes => fireChange while
  // UINode rerender or @monitor function execution
  private startDirty_: boolean = false

  // flag to indicate change observation is disabled
  private disabled_ : boolean = false;

  // flag to indicate ComputedV3 calculation is ongoing
  private calculatingComputedProp_ : boolean = false;

  private static obsInstance_: ObserveV3;

  public static getObserve(): ObserveV3 {
    if (!this.obsInstance_) {
      this.obsInstance_ = new ObserveV3();
    }
    return this.obsInstance_;
  }

  // return true given value is @observed object
  public static IsObservedObjectV3(value : any) : boolean {
    return (value && typeof(value) == "object" && value[ObserveV3.V3_DECO_META])
  }

  // At the start of observeComponentCreation or
  // MonitorV3.observeObjectAccess
  public startBind(cmp: ViewPU | MonitorV3 | ComputedV3 | null, id: number): void {
    this.bindCmp_ = cmp;
    this.bindId_ = id;
    if (cmp != null) {
      this.clearBinding(id);
      this.id2cmp_[id] = (cmp instanceof ViewPU) ? new WeakRef<ViewPU>(cmp) : cmp;
    }
  }


  // clear any previously created dependency view model object to elmtId
  // find these view model objects with the reverse map id2targets_
  public clearBinding(id: number): void {
    this.id2targets_[id]?.forEach((target) => {
      const idRefs : Object | undefined = target[ObserveV3.ID_REFS]
      const symRefs : Object = target[ObserveV3.SYMBOL_REFS]

      if (idRefs) {
        idRefs[id]?.forEach(key => symRefs?.[key]?.delete(id));
        delete idRefs[id];
      } else {
        for (let key in symRefs) { symRefs[key]?.delete(id) };
      }
    })

    delete this.id2targets_[id]
    delete this.id2cmp_[id]

    stateMgmtConsole.propertyAccess(`clearBinding (at the end): id2cmp_ length=${Object.keys(this.id2cmp_).length}, entries=${JSON.stringify(Object.keys(this.id2cmp_))} `);
    stateMgmtConsole.propertyAccess(`... id2targets_ length=${Object.keys(this.id2targets_).length}, entries=${JSON.stringify(Object.keys(this.id2targets_))} `);
  }

  /**
   * Method only for testing
   *
   * @param expectedLength
   * @returns true if length matches
   */
  public get id2CompLength(): number {
    return Object.keys(this.id2cmp_).length;
  }

  public assertOnId2Comp(expectedLength: number): boolean {
    const result = expectedLength == this.id2CompLength;
    if (!result) {
      stateMgmtConsole.error(`assertOnId2Comp expected length ${expectedLength}, actual ${this.id2CompLength}, entries=${JSON.stringify(Object.keys(this.id2cmp_))}`);
    }
    return result;
  }

  /**
   * Method only for testing
   * 
   * @param expectedLength 
   * @returns true if length matches
   */
  public get id2TargetsLength(): number {
    return Object.keys(this.id2targets_).length;
  }

  public assertOnId2Targets(expectedLength: number): boolean {
    const result = expectedLength == Object.keys(this.id2cmp_).length;
    if (!result) {
      stateMgmtConsole.error(`assertOnId2Target expected length ${expectedLength}, actual ${Object.keys(this.id2targets_)}, entries=${JSON.stringify(Object.keys(this.id2targets_))}`);
    }
    return result;
  }


  // add dependency view model object 'target' property 'attrName'
  // to current this.bindId
  public addRef(target: object, attrName: string): void {
    if (this.bindCmp_ === null) {
      return;
    }
    if (this.bindId_ == UINodeRegisterProxy.monitorIllegalV2V3StateAccess) {
      const error = `${attrName}: ObserveV3.addRef: trying to use V3 state '${attrName}' to init/update child V2 @Component. Application error`;
      stateMgmtConsole.applicationError(error);
      throw new TypeError(error);
    }

    stateMgmtConsole.propertyAccess(`ObserveV3.addRef '${attrName}' for id ${this.bindId_}...`);
    const id = this.bindId_

    // Map: attribute/symbol -> dependent id
    const symRefs = target[ObserveV3.SYMBOL_REFS] ??= {}
    symRefs[attrName] ??= new Set()
    symRefs[attrName].add(id)

    // Map id -> attribute/symbol
    // optimization for faster clearBinding
    const idRefs = target[ObserveV3.ID_REFS]
    if (idRefs) {
      idRefs[id] ??= new Set()
      idRefs[id].add(attrName)
    }

    this.id2targets_[id] ??= new Set()
    this.id2targets_[id].add(target);
  }

  /**
   * setReadOnlyAttr - helper function used to update an immutable attribute
   * such update as a @param variable from parent @Component
   * @param target  - the object, usually the ViewPU
   * @param attrName - @param variable name
   * @param newValue - update to new value
   */
  public setReadOnlyAttr<Z>(target: object, attrName: string, newValue: Z): void {
    const storeProp = ObserveV3.OB_PREFIX + attrName;
    if (storeProp in target) {
      // @observed class and @track attrName
      if (newValue === target[storeProp]) {
        stateMgmtConsole.propertyAccess(`setReadOnlyAttr '${attrName}' - tracked but unchanged. Doing nothing.`);
        return;
      }
      stateMgmtConsole.propertyAccess(`setReadOnlyAttr '${attrName}' - updating backing store and fireChange.`);
      target[storeProp] = newValue;
      ObserveV3.getObserve().fireChange(target, attrName)
    } else {
      stateMgmtConsole.propertyAccess(`setReadOnlyAttr '${attrName}' - untracked, assigning straight.`);
      // untracked attrName
      target[attrName] = newValue;
    }
  }

  /**
   * 
   * @param target set tracked attribute to new value without notifying the change
   *               !! use with caution !!
   * @param attrName 
   * @param newValue 
   */
  public setUnmonitored<Z>(target: object, attrName: string, newValue: Z): void {    
    const storeProp = ObserveV3.OB_PREFIX + attrName;
    if (storeProp in target) {
      // @track attrName
      stateMgmtConsole.propertyAccess(`setUnmonitored '${attrName}' - tracked but unchanged. Doing nothing.`);
      target[storeProp] = newValue;
    } else {
      stateMgmtConsole.propertyAccess(`setUnmonitored '${attrName}' - untracked, assigning straight.`);
      // untracked attrName
      target[attrName] = newValue;
    }
  }

  /**
   * Execute given task while state change observation is disabled
   * A state mutation caused by the task will NOT trigger UI rerender 
   * and @monitor function execution. 
   * 
   * !!! Use with Caution !!!
   * 
   * @param task a function to execute without monitoring state changes
   * @returns task function return value
   */
  public executeUnobserved<Z>(task: () => Z): Z {
    stateMgmtConsole.propertyAccess(`executeUnobserved - start`);
    this.disabled_ = true;
    let ret : Z;
    try {
      ret = task();
    } catch (e) {
      stateMgmtConsole.applicationError(`executeUnobserved - task execution caused error ${e} !`);
    }
    this.disabled_ = false;
    stateMgmtConsole.propertyAccess(`executeUnobserved - done`);
    return ret;
  }
 

  // mark view model object 'target' property 'attrName' as changed
  // notify affected watchIds and elmtIds
  public fireChange(target: object, attrName: string): void {
    // enable to get more fine grained traces
    // including 2 (!) .end calls.
    // aceTrace.begin(`ObservedV3.FireChange '${attrName}'`)

    if (!target[ObserveV3.SYMBOL_REFS] || this.disabled_) {
      return;
    }

    if (this.calculatingComputedProp_) {
      const error = `Usage of ILLEGAL @computed function detected for ${(this.bindCmp_ as ComputedV3).getProp()}! The @computed function MUST NOT change the state of any observed state variable!`;
      stateMgmtConsole.applicationError(error);
      throw new Error(error);
    }

    // enable this trace marker for more fine grained tracing of the update pipeline
    // note: two (!) end markers need to be enabled
    // aceTrace.begin("fireChange");
    let changedIdSet = target[ObserveV3.SYMBOL_REFS][attrName];
    if (!changedIdSet || !(changedIdSet instanceof Set)) {
      // aceTrace.end();
      return;
    }

    stateMgmtConsole.propertyAccess(`ObserveV3.fireChange '${attrName}' dependent ids: ${JSON.stringify(Array.from(changedIdSet))}  ...`);
    for (const id of changedIdSet) {
      // Cannot fireChange the object that is being created.
      if (id === this.bindId_) {
        continue;
      }

      // if this is the first id to be added to any Set of changed ids, 
      // schedule an 'updateDirty' task
      // that will run after the current call stack has unwound.
      // purpose of check for startDirty_ is to avoid going into recursion. This could happen if
      // exec a re-render or exec a monitor function changes some state -> calls fireChange -> ...
      if ((this.elmtIdsChanged_.size + this.monitorIdsChanged_.size + this.computedPropIdsChanged_.size == 0)
        && /* update not already in progress */ !this.startDirty_) {
        Promise.resolve().then(this.updateDirty.bind(this))
      }

      // add bindId to the correct Set of pending changes.
      if (id < ComputedV3.MIN_COMPUTED_ID) {
        this.elmtIdsChanged_.add(id);
      } else if (id < MonitorV3.MIN_WATCH_ID) {
        this.computedPropIdsChanged_.add(id);
      } else {
        this.monitorIdsChanged_.add(id);
      }
    } // for
    // aceTrace.end();
  }

  private updateDirty(): void {
    this.startDirty_ = true
    this.updateDirty2()
    this.startDirty_ = false
  }

  private updateDirty2(): void {
    aceTrace.begin("updateDirty2")
    stateMgmtConsole.debug(`ObservedV3.updateDirty2 ... `);
    // obtain and unregister the removed elmtIds 
    UINodeRegisterProxy.obtainDeletedElmtIds();
    UINodeRegisterProxy.unregisterElmtIdsFromViewPUs();

    // priority order of processing:
    // 1- update computed properties until no more need computed props update 
    // 2- update monitors until no more monitors and no more computed props
    // 3- update UINodes until no more monitors, no more computed props, and no more UINodes
    // FIXME prevent infinite loops
    do {
      do {
        while (this.computedPropIdsChanged_.size) {
          //  sort the ids and update in ascending order
          // If a @computed property depends on other @computed properties, their
          // ids will be smaller as they are defined first.
          const computedProps = Array.from(this.computedPropIdsChanged_).sort((id1, id2) => id1-id2);
          this.computedPropIdsChanged_ = new Set<number>();
          this.updateDirtyComputedProps(computedProps);
        }

        if (this.monitorIdsChanged_.size) {
          const monitors = this.monitorIdsChanged_;
          this.monitorIdsChanged_ = new Set<number>();
          this.updateDirtyMonitors(monitors);
        }
      } while (this.monitorIdsChanged_.size + this.computedPropIdsChanged_.size > 0)

      if (this.elmtIdsChanged_.size) {
        const elmtIds = Array.from(this.elmtIdsChanged_).sort((elmtId1, elmtId2) => elmtId1-elmtId2);
        this.elmtIdsChanged_ = new Set<number>();
        this.updateUINodes(elmtIds);
      }
    } while (this.elmtIdsChanged_.size + this.monitorIdsChanged_.size + this.computedPropIdsChanged_.size > 0)
    aceTrace.end();
  }

  private updateDirtyComputedProps(computed: Array<number>): void {
    stateMgmtConsole.debug(`ObservedV3.updateDirtyComputedProps ${computed.length} props: ${JSON.stringify(computed)} ...`);
    aceTrace.begin(`ObservedV3.updateDirtyComputedProps ${computed.length} @computed`);
    computed.forEach((id) => {
      let comp: ComputedV3 | undefined = this.id2cmp_[id];
      if (comp instanceof ComputedV3) {
        const target = comp.getTarget() as ViewPU;
        if (target instanceof ViewPU && !target.isViewActive()) {
          // FIXME @Component freeze enable
          // view.addDelayedComputedIds(id);
        } else {
          comp.fireChange();
        }
      }
    });
    aceTrace.end();
  }


  private updateDirtyMonitors(monitors: Set<number>): void {
    stateMgmtConsole.debug(`ObservedV3.updateDirtyMonitors: ${Array.from(monitors).length} @monitor funcs: ${JSON.stringify(Array.from(monitors))} ...`);
    aceTrace.begin(`ObservedV3.updateDirtyMonitors: ${Array.from(monitors).length} @monitor`);
    let monitor : MonitorV3 | undefined;
    let monitorTarget : Object;
    monitors.forEach((watchId) => {
      monitor = this.id2cmp_[watchId];
      if (monitor instanceof MonitorV3) {
        if (((monitorTarget=monitor.getTarget()) instanceof ViewPU) && !monitorTarget.isViewActive()) {
        // FIXME @Component freeze enable
        // monitor notifyChange delayed if target is a View that is not active
        // monitorTarget.addDelayedMonitorIds(watchId);
        } else {
          monitor.notifyChange();
        }
      }
    });
    aceTrace.end();
  }

  /**
   * This version of UpdateUINodes does not wait for VSYNC, violates rules
   * calls UpdateElement, thereby avoids the long and frequent code path from 
   * FlushDirtyNodesUpdate to CustomNode to ViewPU.updateDirtyElements to UpdateElement
   * Code left here to reproduce benchmark measurements, compare with future optimisation
   * @param elmtIds 
   */
  private updateUINodesWithoutVSync(elmtIds: Array<number>): void {
    stateMgmtConsole.debug(`ObserveV3.updateUINodes: ${elmtIds.length} elmtIds: ${JSON.stringify(elmtIds)} ...`);
    aceTrace.begin(`ObserveV3.updateUINodes: ${elmtIds.length} elmtId`)
    let view : Object;
    let weak : any;
    elmtIds.forEach((elmtId) => {
      if ((weak = this.id2cmp_[elmtId]) && (typeof weak == "object") && ("deref" in weak)
        && (view = weak.deref()) && (view instanceof ViewPU)) {
        if (view.isViewActive()) {
          // FIXME need to call syncInstanceId before update?
          view.UpdateElement(elmtId);
        } else {
          // FIXME @Component freeze
          //....
        }
      } // if ViewPU
    });
    aceTrace.end();
  }

  // This is the code path similar to V2, follows the rule that UI updates on VSYNC.
  // ViewPU queues the elmtId that need update, marks the CustomNode dirty in RenderContext
  // On next VSYNC runs FlushDirtyNodesUpdate to call rerender to call UpdateElement. Much longer code path
  // much slower
  private updateUINodes(elmtIds: Array<number>): void {
    stateMgmtConsole.debug(`ObserveV3.updateUINodesSlow: ${elmtIds.length} elmtIds need rerender: ${JSON.stringify(elmtIds)} ...`);
    aceTrace.begin(`ObserveV3.updateUINodesSlow: ${elmtIds.length} elmtId`);
    let viewWeak : WeakRef<Object>;
    let view : Object | undefined;
    elmtIds.forEach((elmtId) => {
      viewWeak = this.id2cmp_[elmtId];
      if (viewWeak && "deref" in viewWeak && (view=viewWeak.deref()) && view instanceof ViewPU) {
        if (view.isViewActive()) {
          view.uiNodeNeedUpdateV3(elmtId);
        } else {
          // FIXME delayed update
        }
      }
    });
    aceTrace.end();
  }

  public constructMonitor(target: Object, name: string): void {
    let watchProp = Symbol.for(MonitorV3.WATCH_PREFIX + name)
    if (target && (typeof target == "object") && target[watchProp]) {
      Object.entries(target[watchProp]).forEach(([funcName, func]) => {
        if (func && funcName && typeof func == "function") {
          new MonitorV3(target, funcName, func as (m: IMonitor) => void).InitRun();
        }
        // FIXME Else handle error
      });
    } // if target[watchProp]
  }

  public constructComputed(target: Object, name: string): void {
    let watchProp = Symbol.for(ComputedV3.COMPUTED_PREFIX + name)
    if (target && (typeof target == "object") && target[watchProp]) {
      Object.entries(target[watchProp]).forEach(([propertyName, computeFunc]) => {
        stateMgmtConsole.debug(`constructComputed: in ${target?.constructor?.name} found @computed ${propertyName}`);
        new ComputedV3(target, propertyName, computeFunc as unknown as () => any).InitRun();
      })
    }
  }

  public clearWatch(id: number): void {
    this.clearBinding(id)
  }



  public static autoProxyObject(target: Object, key: string | symbol): any {
    let val = target[key]
    // Not an object, not a collection, no proxy required
    if (!val || typeof (val) !== "object"
      || !(Array.isArray(val) || val instanceof Set || val instanceof Map || val instanceof Date)) {
      return val
    }

    // Only collections require proxy observation, and if it has been observed, it does not need to be observed again.
    if (!val[ObserveV3.SYMBOL_PROXY_GET_TARGET]) {
      target[key] = new Proxy(val, ObserveV3.arraySetMapProxy)
      val = target[key]
    }

    // If the return value is an Array, Set, Map 
    if (!(val instanceof Date)) {
      ObserveV3.getObserve().addRef(val, ObserveV3.OB_LENGTH)
    }

    return val
  }

  private static readonly arrayLengthChangingFunctions = new Set(["push", "pop", "shift", "splice", "unshift"]);
  private static readonly arrayMutatingFunctions = new Set(["copyWithin", "fill", "reverse", "sort"]);
  private static readonly dateSetFunctions = new Set(["setFullYear", "setMonth", "setDate", "setHours", "setMinutes",
    "setSeconds", "setMilliseconds", "setTime", "setUTCFullYear", "setUTCMonth", "setUTCDate", "setUTCHours",
    "setUTCMinutes", "setUTCSeconds", "setUTCMilliseconds"]);

  public static readonly arraySetMapProxy = {
    get(target: any, key: string | symbol, receiver: any) {
      if (typeof key === "symbol") {
        if (key === Symbol.iterator) {
          ObserveV3.getObserve().fireChange(target, ObserveV3.OB_MAP_SET_ANY_PROPERTY);
          ObserveV3.getObserve().addRef(target, ObserveV3.OB_LENGTH)
          return (...args) => target[key](...args);
        } else {
          return key === ObserveV3.SYMBOL_PROXY_GET_TARGET ? target : target[key]
        }
      }

      if (key === "size") {
        ObserveV3.getObserve().addRef(target, ObserveV3.OB_LENGTH);
        return target.size;
      }

      let ret = ObserveV3.autoProxyObject(target, key)
      if (typeof (ret) !== "function") {
        ObserveV3.getObserve().addRef(target, key)
        return ret
      }

      if (Array.isArray(target)) {
        if (ObserveV3.arrayMutatingFunctions.has(key)) {
          return function (...args) {
            ret.call(target, ...args);
            ObserveV3.getObserve().fireChange(target, ObserveV3.OB_LENGTH);
            // returning the 'receiver(proxied object)' ensures that when chain calls also 2nd function call
            // operates on the proxied object.
            return receiver;
          };
        } else if (ObserveV3.arrayLengthChangingFunctions.has(key)) {
          return function (...args) {
            const result = ret.call(target, ...args);
            ObserveV3.getObserve().fireChange(target, ObserveV3.OB_LENGTH);
            return result;
          };
        } else { 
          return ret.bind(receiver);
        }
      }

      if (target instanceof Date) {
        if (ObserveV3.dateSetFunctions.has(key)) {
          return function (...args) {
            // execute original function with given arguments
            let result = ret.call(this, ...args);
            ObserveV3.getObserve().fireChange(target, ObserveV3.OB_DATE);
            return result;
            // bind "this" to target inside the function
          }.bind(target)
        } else {
            ObserveV3.getObserve().addRef(target, ObserveV3.OB_DATE);
        }
        return ret.bind(target);
      }

      if (target instanceof Set || target instanceof Map) {
        if (key === "has") {
          return prop => {
            const ret= target.has(prop);
            if (ret) {
              ObserveV3.getObserve().addRef(target, prop);
            } else {
              ObserveV3.getObserve().addRef(target, ObserveV3.OB_LENGTH);
            }
            return ret;
          }
        }
        if (key === "delete") {
          return prop => {
            if (target.has(prop)) {
              ObserveV3.getObserve().fireChange(target, prop)
              ObserveV3.getObserve().fireChange(target, ObserveV3.OB_LENGTH)
              return target.delete(prop);
            } else {
              return false;
            }
          }
        }
        if (key === "clear") {
          return () => {
            if (target.size > 0) {
              target.forEach((_, prop) => {
                ObserveV3.getObserve().fireChange(target, prop.toString())
              })
              ObserveV3.getObserve().fireChange(target, ObserveV3.OB_LENGTH)
              ObserveV3.getObserve().addRef(target, ObserveV3.OB_MAP_SET_ANY_PROPERTY)
              target.clear()
            }
          }
        }
        if (key === "keys" || key === "values" || key === "entries") {
          return () => {
            ObserveV3.getObserve().addRef(target, ObserveV3.OB_MAP_SET_ANY_PROPERTY)
            ObserveV3.getObserve().addRef(target, ObserveV3.OB_LENGTH)
            return target[key]()
          }
        }
      }

      if (target instanceof Set) {
        return key === "add" ? val => {
          ObserveV3.getObserve().fireChange(target, val.toString())
          ObserveV3.getObserve().fireChange(target, ObserveV3.OB_MAP_SET_ANY_PROPERTY)
          if (!target.has(val)) {
            ObserveV3.getObserve().fireChange(target, ObserveV3.OB_LENGTH)
            target.add(val);
          }
          // return proxied This
          return receiver;
        } : (typeof ret == "function")
            ? ret.bind(target) : ret;
      }

      if (target instanceof Map) {
        if (key === "get") { // for Map
          return (prop) => {
            if (target.has(prop)) {
              ObserveV3.getObserve().addRef(target, prop)
            } else {
              ObserveV3.getObserve().addRef(target, ObserveV3.OB_LENGTH)
            }
            return target.get(prop)
          }
        }
        if (key === "set") { // for Map
          return (prop, val) => {
            if (!target.has(prop)) {
              ObserveV3.getObserve().fireChange(target, ObserveV3.OB_LENGTH);
            } else if(target.get(prop) !== val) {
              ObserveV3.getObserve().fireChange(target, prop)
            }
            ObserveV3.getObserve().fireChange(target, ObserveV3.OB_MAP_SET_ANY_PROPERTY)
            target.set(prop, val)
            return receiver;
          }
        }
      }

      return (typeof ret == "function") ? ret.bind(target) : ret;
    },
    
    set(target: any, key: string | symbol, value: any) {
      if (typeof key === 'symbol') {
        if (key !== ObserveV3.SYMBOL_PROXY_GET_TARGET) {
          target[key] = value
        }
        return true;
      }

      if (target[key] === value) {
        return true;
      }
      target[key] = value
      ObserveV3.getObserve().fireChange(target, key.toString())
      return true
    }
  }

  /**
   * Helper function to add meta data about decorator to ViewPU
   * @param proto prototype object of application class derived from ViewPU 
   * @param varName decorated variable
   * @param deco "@state", "@event", etc (note "@model" gets transpiled in "@param" and "@event")
   */
  public static addVariableDecoMeta(proto: Object, varName: string, deco: string): void {
    // add decorator meta data
    const meta = proto[ObserveV3.V3_DECO_META] ??= {};
    meta[varName] = {};
    meta[varName]["deco"] = deco;

    // FIXME 
    // when splitting ViewPU and ViewV3
    // use instanceOf. Until then, this is a workaround.
    // any @state, @track, etc V3 event handles this function to return false
    Reflect.defineProperty(proto, "isViewV3", {
      get() { return true; },
      enumerable: false
    }
    );
  }

 
  public static usesV3Variables(proto : Object) : boolean {
  return (proto && typeof proto =="object" && proto[ObserveV3.V3_DECO_META]);
  }
} // class ObserveV3

/**
 * @Trace class property decorator 
 * 
 * @param target  class prototype object
 * @param propertyKey  class property name
 * 
 * turns given property into getter and setter functions
 * adds property target[storeProp] as the backing store
 * 
 * part of SDK
 * @from 12
 */
const Trace = (target: Object, propertyKey: string) => {
  ConfigureStateMgmt.instance.usingV2ObservedTrack(`@track`, propertyKey);
  return trackInternal(target, propertyKey);
}

const trackInternal = (target: any, propertyKey: string) => {
  if (typeof target === "function" && !Reflect.has(target, propertyKey)) {
    // dynamic track，and it not a static attribute
    target = target.prototype
  }
  let storeProp = ObserveV3.OB_PREFIX + propertyKey
  target[storeProp] = target[propertyKey]
  Reflect.defineProperty(target, propertyKey, {
    get() {
      ObserveV3.getObserve().addRef(this, propertyKey)
      return ObserveV3.autoProxyObject(this, ObserveV3.OB_PREFIX + propertyKey)
    },
    set(val) {
      // If the object has not been observed, you can directly assign a value to it. This improves performance.
      if (val !== this[storeProp]) {
        this[storeProp] = val
      if (this[ObserveV3.SYMBOL_REFS]) { // This condition can improve performance.
          ObserveV3.getObserve().fireChange(this, propertyKey)
        }
      }
    },
    enumerable: true
  })
  // this marks the proto as having at least one @track property inside 
  // used by IsObservedObjectV3
  target[ObserveV3.V3_DECO_META]??={};
} // track


/**
 * @ObservedV2 class decorator
 * only @ObservedV2 classes can have functional @track attributes inside.
 * and only changes of such decorated properties can be deep observed
 * (decorated along the entire path from root object to property)
 * 
 * part of SDK
 * @from 12
 * 
 */
type ConstructorV3 = { new(...args: any[]): any };

function ObservedV2<T extends ConstructorV3>(BaseClass: T) : ConstructorV3 {
  ConfigureStateMgmt.instance.usingV2ObservedTrack(`@observed`, BaseClass?.name);

  // prevent @Track inside @observed class
  if (BaseClass.prototype && Reflect.has(BaseClass.prototype,  TrackedObject.___IS_TRACKED_OPTIMISED)) {
    const error=`'@observed class ${BaseClass?.name}': invalid use of V2 @Track decorator inside V3 @observed class. Need to fix class definition to use @track.`
    stateMgmtConsole.applicationError(error);
    throw new Error(error);
  }


  if (BaseClass.prototype && !Reflect.has(BaseClass.prototype, ObserveV3.V3_DECO_META)) {
    // not an error, suspicious of developer oversight
    stateMgmtConsole.warn(`'@observed class ${BaseClass?.name}': no @track property inside. Is thi intended? Check our application.`);
  }

  // Use ID_REFS only if number of observed attrs is significant
  const attrList = Object.getOwnPropertyNames(BaseClass.prototype);
  const count = attrList.filter(attr => attr.startsWith(ObserveV3.OB_PREFIX)).length;
  if (count > 5) {
    BaseClass.prototype[ObserveV3.ID_REFS] = {};
  }

  return class extends BaseClass {
    constructor(...args) {
      super(...args)
        AsyncAddMonitorV3.addMonitor(this, BaseClass.name)
        AsyncAddComputedV3.addComputed(this, BaseClass.name)
    }
  }
}
