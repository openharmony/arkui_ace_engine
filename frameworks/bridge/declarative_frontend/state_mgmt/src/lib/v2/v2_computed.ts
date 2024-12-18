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
 */

/**
 * ComputedV2
 * one ComputedV2 object per @Computed variable
 * computedId_ - similar to elmtId, identify one ComputedV2 in Observe.idToCmp Map
 * observeObjectAccess = calculate the compute function and create dependencies to
 * source variables
 * fireChange - execute compute function and re-new dependencies with observeObjectAccess
 */
class ComputedV2 {

  // start with high number to avoid same id as elmtId for components.
  public static readonly MIN_COMPUTED_ID = 0x1000000000;
  private static nextCompId_ = ComputedV2.MIN_COMPUTED_ID;

  // name of @Computed property
  private prop_: string;

  // owning object of @Computed property
  private target_: object;

  // computation function for property
  private propertyComputeFunc_: () => any;
  private computedId_: number;

  public static readonly COMPUTED_PREFIX = '___comp_';
  public static readonly COMPUTED_CACHED_PREFIX = '___comp_cached_';

  constructor(target: object, prop: string, func: (...args: any[]) => any) {
    this.target_ = target;
    this.propertyComputeFunc_ = func;
    this.computedId_ = ++ComputedV2.nextCompId_;
    this.prop_ = prop;
  }

  public InitRun(): number {
    let cachedProp = ComputedV2.COMPUTED_CACHED_PREFIX + this.prop_;
    let propertyKey = this.prop_;
    Reflect.defineProperty(this.target_, propertyKey, {
      get() {
        ObserveV2.getObserve().addRef(this, propertyKey);
        return ObserveV2.autoProxyObject(this, cachedProp);
      },
      set(_) {
        const error = `@Computed ${propertyKey} is readonly, cannot set value for it`;
        stateMgmtConsole.applicationError(error);
        throw new Error(error);
      },
      enumerable: true
    });

    this.target_[cachedProp] = this.observeObjectAccess();
    return this.computedId_;
  }

  public fireChange(): void {
    let newVal = this.observeObjectAccess();
    let cachedProp = ComputedV2.COMPUTED_CACHED_PREFIX + this.prop_;
    if (this.target_[cachedProp] !== newVal) {
      this.target_[cachedProp] = newVal;
        ObserveV2.getObserve().fireChange(this.target_, this.prop_);
    }
  }

  public getTarget() : object {
    return this.target_;
  }

  public getProp() : string {
    return this.prop_;
  }

  // register current watchId while executing compute function
  private observeObjectAccess(): Object | undefined {
    ObserveV2.getObserve().startRecordDependencies(this, this.computedId_);
    let ret;

    try {
        ret = this.propertyComputeFunc_.call(this.target_);
    } catch (e) {
        stateMgmtConsole.applicationError(`@Computed Exception caught for ${this.propertyComputeFunc_.name}`, e.toString());
        ret = undefined;
        throw e;
    } finally {
        ObserveV2.getObserve().stopRecordDependencies();
    }

    return ret;
  }

  public static clearComputedFromTarget(target: Object): void {
    let meta: Object;
    if (!target || typeof target !== 'object' ||
        !(meta = target[ObserveV2.COMPUTED_REFS]) || typeof meta !== 'object') {
      return;
    }

    stateMgmtConsole.debug(`ComputedV2: clearComputedFromTarget: from target ${target.constructor?.name} computedIds to clear ${JSON.stringify(Array.from(Object.values(meta)))}`);
    Array.from(Object.values(meta)).forEach((computed: ComputedV2) => ObserveV2.getObserve().clearWatch(computed.computedId_));
  }
}

interface AsyncAddComputedJobEntryV2 {
  target: Object;
  name: string;
}
class AsyncAddComputedV2 {
  static computedVars : Array<AsyncAddComputedJobEntryV2> = new Array<AsyncAddComputedJobEntryV2>();

  static addComputed(target: Object, name: string): void {
    if (AsyncAddComputedV2.computedVars.length === 0) {
      Promise.resolve(true)
      .then(AsyncAddComputedV2.run)
      .catch(error => {
        stateMgmtConsole.applicationError(`Exception caught in @Computed ${name}`, error);
        _arkUIUncaughtPromiseError(error);
      });
    }
    AsyncAddComputedV2.computedVars.push({target: target, name: name});
  }

  static run(): void {
    AsyncAddComputedV2.computedVars.forEach((computedVar : AsyncAddComputedJobEntryV2) =>
      ObserveV2.getObserve().constructComputed(computedVar.target, computedVar.name));
    // according to stackoverflow this is the fastest way to clear an Array
    // ref https://stackoverflow.com/questions/1232040/how-do-i-empty-an-array-in-javascript
    AsyncAddComputedV2.computedVars.length = 0;
  }
}
