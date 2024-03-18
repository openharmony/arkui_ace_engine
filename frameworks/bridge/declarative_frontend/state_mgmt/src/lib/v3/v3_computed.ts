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
 * ComputedV3
 * one ComputedV3 object per @computed variable
 * computedId_ - similar to elmtId, identify one ComputedV3 in Observe.idToCmp Map
 * observeObjectAccess = calculate the compute function and create dependencies to
 * source variables
 * fireChange - execute compute function and re-new dependencies with observeObjectAccess
 */
class ComputedV3 {

  // start with high number to avoid same id as elmtId for components.
  public static readonly MIN_COMPUTED_ID = 0x1000000000;
  private static nextCompId_ = ComputedV3.MIN_COMPUTED_ID;

  // name of @computed property
  private prop_: string;

  // owning object of @computed property
  private target_: object; 

  // computation function for property
  private propertyComputeFunc_: () => any;
  private computedId_: number; 

  public static readonly COMPUTED_PREFIX =  "___comp_";
  public static readonly COMPUTED_CACHED_PREFIX = "___comp_cached_";

  constructor(target: object, prop: string, func: (...args: any[]) => any) {
    this.target_ = target;
    this.propertyComputeFunc_ = func;
    this.computedId_ = ++ComputedV3.nextCompId_;
    this.prop_ = prop;
  }

  public InitRun(): number {
    let cachedProp = ComputedV3.COMPUTED_CACHED_PREFIX + this.prop_;
    let propertyKey = this.prop_;
    Reflect.defineProperty(this.target_, propertyKey, {
      get() {
        ObserveV3.getObserve().addRef(this, propertyKey);
        return ObserveV3.autoProxyObject(this, cachedProp);
      },
      enumerable: true
    });

    this.target_[cachedProp] = this.observeObjectAccess();
    return this.computedId_;
  }

  public fireChange(): void {
    let newVal = this.observeObjectAccess();
    let cachedProp = ComputedV3.COMPUTED_CACHED_PREFIX + this.prop_;
    if (this.target_[cachedProp] !== newVal) {
      this.target_[cachedProp] = newVal;
        ObserveV3.getObserve().fireChange(this.target_, this.prop_);
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
    ObserveV3.getObserve().startBind(this, this.computedId_);
    let ret = this.propertyComputeFunc_.call(this.target_);
    ObserveV3.getObserve().startBind(null, 0);
    return ret;
  }
}

interface AsyncAddComputedJobEntryV3 {
  target: Object
  name: string
}
class AsyncAddComputedV3 {
  static computedVars : Array<AsyncAddComputedJobEntryV3> = new Array<AsyncAddComputedJobEntryV3>();

  static addComputed(target: Object, name: string) {
    if (AsyncAddComputedV3.computedVars.length === 0) {
      Promise.resolve(true).then(AsyncAddComputedV3.run)
    }
    AsyncAddComputedV3.computedVars.push({target: target, name: name});
  }

  static run() {
    AsyncAddComputedV3.computedVars.forEach((computedVar : AsyncAddComputedJobEntryV3) => ObserveV3.getObserve().constructComputed(computedVar.target, computedVar.name));
    // according to stackoverflow this is the fastest way to clear an Array
    // ref https://stackoverflow.com/questions/1232040/how-do-i-empty-an-array-in-javascript
    AsyncAddComputedV3.computedVars.length=0;
  }
}



/**
 * @computed variable decorator
 */
/**
   * @computed class property decorator 
   * 
   * must be a 'computed' class property, e.g. @computed get varName() { return this.state1 + this.state2 }
   * value assignment / set not allowed = has no setter. 
   * 
   * @param target  class prototype object
   * @param propertyKey  class property name
   *
   * part of SDK
   * @from 12
   *
   */
  /*
const computed = (target: Object, propertyKey: string, descriptor: PropertyDescriptor) => {
  stateMgmtConsole.debug(`@computed ${propertyKey}`);
  let watchProp = Symbol.for(ComputedV3.COMPUTED_PREFIX + target.constructor.name);
  const computeFunction = descriptor.get;
  target[watchProp] ? target[watchProp][propertyKey] = computeFunction 
                    : target[watchProp] = { [propertyKey]: computeFunction };
}

*/
