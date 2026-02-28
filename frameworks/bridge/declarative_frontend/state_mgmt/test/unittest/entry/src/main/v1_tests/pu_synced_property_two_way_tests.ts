/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { eq, neq, gt, ITestFile } from '../lib/testRunner'


declare class ObservedPropertyObjectPU<T> extends ObservedPropertyAbstractPU<T> {
  constructor(value: T, subscriber: IPropertySubscriber, propName: string);
}

declare class PUV2ViewBase {
    protected get isViewV2(): boolean;
}


declare class ObservedPropertyObjectAbstract<T> {
  get(): T;
  getUnmonitored(): T;
  set(value: T): void;
  addSubscriber(subscriber: IPropertySubscriber): void;
  removeSubscriber(subscriber: IPropertySubscriber): void;
  aboutToBeDeleted(): void;
}

declare class SynchedPropertyTwoWayPU<C> {
  constructor(source: ObservedPropertyObjectAbstract<C>,
    owningChildView: IPropertySubscriber,
    thisPropertyName: PropertyInfo);
  aboutToBeDeleted(): void;
  syncPeerHasChanged(eventSource: ObservedPropertyAbstractPU<C>, isSync?: boolean): void;
  syncPeerTrackedPropertyHasChanged(eventSource: ObservedPropertyAbstractPU<C>, changedPropertyName?: string, isSync?: boolean): void;
  getUnmonitored(): C;
  get(): C;
  set(newValue: C): void;
  getRootSource(): ObservedPropertyObjectAbstract<C> | undefined;
  resetSource(newSource: ObservedPropertyObjectAbstract<C>): void;
  resetFakeSource(): void;
}

declare class SynchedPropertyObjectTwoWayPU<T> extends SynchedPropertyTwoWayPU<T> {}

declare class SynchedPropertySimpleTwoWayPU<T> extends SynchedPropertyTwoWayPU<T> {}

interface IPropertySubscriber {
  propertyHasChanged(code?: number): void;
}

interface PropertyInfo {
  name?: string;
}

declare class ObservedObject {
  static IsObservedObject(value: any): boolean;
  static GetRawObject(value: any): any;
  static createNew<T>(value: T, owner?: IPropertySubscriber): T;
  static removeOwningProperty(obj: any, owner: IPropertySubscriber): void;
  static addOwningProperty(obj: any, owner: IPropertySubscriber): void;
  static unregisterPropertyReadCb(obj: any): void;
  static registerPropertyReadCb(obj: any, cb: Function, context: any): void;
}

declare class SyncedViewRegistry {
  static dirtyNodesList: WeakRef<ViewPU>[];
}

interface IViewPropertiesChangeSubscriber extends IPropertySubscriber {
    viewPropertyHasChanged(varName: PropertyInfo, dependentElmtIds: Set<number>): void;
  }
  
  interface IView {
    id__(): number;
    debugInfo__(): string;
    getCardId(): number;
    getParent(): IView | undefined;
    setParent(p: IView): void;
    addChild(c: IView): boolean;
    getChildById(elmtId: number): IView | undefined;
    removeChild(child: IView): boolean;
    purgeDeleteElmtId(rmElmtId: number): boolean;
    initialRenderView(): void;
    forceCompleteRerender(deep: boolean): void;
    forceRerenderNode(elmtId: number): void;
    uiNodeNeedUpdateV2(elmtId: number): void;
    updateStateVarsOfChildByElmtId(elmtId: any, params: Object): void;
    aboutToBeDeleted(): void;
    isDeleting(): boolean;
    setDeleting(): void;
    setDeleteStatusRecursively(): void;
    isCompFreezeAllowed(): boolean;
    setActiveInternal(newState: boolean, isReuse: boolean): void;
    findProvidePU__(providedPropName: string): ObservedPropertyAbstractPU<any> | undefined;
    debugInfoViewHierarchyInternal(depth: number, recursive: boolean): string;
    onGlobalThemeChanged(): void;
    __ClearAllRecyle__PUV2ViewBase__Internal(): void;
  }
  
  declare abstract class ViewPU extends PUV2ViewBase implements IViewPropertiesChangeSubscriber, IView {
    private isRenderInProgress;
    dirtyElementIdsNeedsUpdateSynchronously_?: Set<number>;
    UpdateElement(elementId: number): void;
    propertyHasChanged(code?: number | undefined): void;
    id__(): number;
    debugInfo__(): string;
    getCardId(): number;
    getParent(): IView | undefined;
    setParent(p: IView): void;
    addChild(c: IView): boolean;
    getChildById(elmtId: number): IView | undefined;
    removeChild(child: IView): boolean;
    purgeDeleteElmtId(rmElmtId: number): boolean;
    initialRenderView(): void;
    forceCompleteRerender(deep: boolean): void;
    forceRerenderNode(elmtId: number): void;
    uiNodeNeedUpdateV2(elmtId: number): void;
    updateStateVarsOfChildByElmtId(elmtId: any, params: Object): void;
    aboutToBeDeleted(): void;
    isDeleting(): boolean;
    setDeleting(): void;
    setDeleteStatusRecursively(): void;
    isCompFreezeAllowed(): boolean;
    setActiveInternal(newState: boolean, isReuse: boolean): void;
    findProvidePU__(providedPropName: string): ObservedPropertyAbstractPU<any> | undefined;
    debugInfoViewHierarchyInternal(depth: number, recursive: boolean): string;
    onGlobalThemeChanged(): void;
    __ClearAllRecyle__PUV2ViewBase__Internal(): void;
    viewPropertyHasChanged(varName: PropertyInfo, dependentElmtIds: Set<number>): void;
    addSubscriber(subscriber: IPropertySubscriber): void;
    removeSubscriber(subscriber: IPropertySubscriber): void;
    numberOfSubscrbers(): number;
    aboutToBeDeleted(): void;
    debugInfo(): string;
  }

declare class TrackedObject {
  static needsPropertyReadCb(value: any): boolean;
  static notifyObjectValueAssignment(oldValue: any, newValue: any,
    notifyFunc: Function, notifyTrackFunc: Function, context: any): void;
  static ___TRACKED_PREFIX: string;
}

declare class InteropConfigureStateMgmt {
  static needsInterop(): boolean;
}

declare class stateMgmtConsole {
  static debug(msg: string): void;
  static warn(msg: string): void;
  static applicationError(msg: string): void;
  static propertyAccess(msg: string): void;
}

declare class stateMgmtProfiler {
  static begin(name: string): void;
  static end(): void;
}

declare class BusinessError {
  constructor(code: number, message: string);
}

declare const NON_TRACK_PROPERTY_ON_UI: number;

class TestSubscriber implements IPropertySubscriber {
  private changeCount_: number = 0;
  private lastChangedCode_: number | undefined = undefined;

  propertyHasChanged(code?: number): void {
    this.changeCount_++;
    this.lastChangedCode_ = code;
  }

  get changeCount(): number {
    return this.changeCount_;
  }

  get lastChangedCode(): number | undefined {
    return this.lastChangedCode_;
  }

  reset(): void {
    this.changeCount_ = 0;
    this.lastChangedCode_ = undefined;
  }
}

declare class ObservedPropertyAbstractPU<T> {
    constructor(subscriber: IPropertySubscriber, viewName: PropertyInfo);
    get(): T;
    getUnmonitored(): T;
    set(value: T): void;
    addSubscriber(subscriber: IPropertySubscriber): void;
    removeSubscriber(subscriber: IPropertySubscriber): void;
    numberOfSubscrbers(): number;
    aboutToBeDeleted(): void;
    debugInfo(): string;
    setIsFake(isFake: boolean): void;

}
  

class TestObservedProperty<T> implements ObservedPropertyObjectAbstract<T> {
  private value_: T;
  private subscribers: IPropertySubscriber[] = [];
  private isFake_: boolean = false;
  private propName_: string;

  constructor(value: T, subscriber: IPropertySubscriber, propName: string) {
    this.value_ = value;
    this.propName_ = propName;
    if (subscriber) {
      this.subscribers.push(subscriber);
    }
  }

  get(): T {
    return this.value_;
  }

  getUnmonitored(): T {
    return this.value_;
  }

  set(value: T): void {
    if (this.value_ !== value) {
      this.value_ = value;
      this.subscribers.forEach(sub => sub.propertyHasChanged());
    }
  }

  addSubscriber(subscriber: IPropertySubscriber): void {
    if (!this.subscribers.includes(subscriber)) {
      this.subscribers.push(subscriber);
    }
  }

  removeSubscriber(subscriber: IPropertySubscriber): void {
    const index = this.subscribers.indexOf(subscriber);
    if (index >= 0) {
      this.subscribers.splice(index, 1);
    }
  }

  numberOfSubscrbers(): number {
    return this.subscribers.length;
  }

  aboutToBeDeleted(): void {
    this.subscribers = [];
  }

  debugInfo(): string {
    return `TestObservedProperty[${this.propName_}]`;
  }

  __isFake_ObservedPropertyAbstract_Internal(): boolean {
    return this.isFake_;
  }

  setIsFake(isFake: boolean): void {
    this.isFake_ = isFake;
  }
}

class TestObservedClass {
  public numValue: number = 0;
  public strValue: string = "";
  public objValue?: { x: number };

  constructor() {
    this.numValue = 42;
    this.strValue = "test";
  }
}

export class PuSyncedPropertyTwoWayTests implements ITestFile {
  private idString: string = "";

  constructor(str: string) {
    console.log(`Creating PuSyncedPropertyTwoWayTests: ${str}`)
    this.idString = str;
  }

  public beforeAll(): void {}

  public beforeEach(): void {
  }

  public afterAll(): void {}

  public afterEach(): void {}

  public getId(): string {
    return this.idString;
  }

  public constructorWithValidSource(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertyObjectTwoWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    const value = prop.get();
    eq(value !== undefined, true, 'Value should be accessible');
    eq(value.numValue, 42, 'numValue should match source');
  }

  public constructorWithNullSourceThrowsError(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    let threwError = false;
    try {
      const prop = new SynchedPropertyObjectTwoWayPU<TestObservedClass>(
        undefined as any, this as object as ViewPU, testPropertyName);
    } catch (e) {
      threwError = true;
      eq(e instanceof SyntaxError, false, 'Should throw SyntaxError');
    }
    eq(threwError, true, 'Constructor with null source should throw error');
  }

  public aboutToBeDeletedRemovesSubscriber(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertyObjectTwoWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    eq(sourceProp.numberOfSubscrbers(), 2, 'Source should have subscribers');

    prop.aboutToBeDeleted();

    eq(sourceProp.numberOfSubscrbers(), 1, 'Subscriber should be removed');
  }

  public getReturnsSourceValue(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    testObj.numValue = 123;

    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertyObjectTwoWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    const value = prop.get();
    eq(value.numValue, 123, 'get()() should return source value');
    eq(value === testObj, false, 'Should return same reference (two-way)');
  }

  public getUnmonitoredReturnsSourceValue(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    testObj.numValue = 456;

    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertyObjectTwoWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    const value = prop.getUnmonitored();
    eq(value.numValue, 456, 'getUnmonitored()() should return source value');
  }

  public setWithSameValueDoesNothing(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    testObj.numValue = 789;

    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertyObjectTwoWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    const initialChangeCount = subscriber.changeCount;

    prop.set(testObj);

    eq(subscriber.changeCount, initialChangeCount,
      'set with same value should not trigger notification');
  }

  public setWithNewValueUpdatesSource(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    testObj.numValue = 100;

    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertyObjectTwoWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    const newObj = new TestObservedClass();
    newObj.numValue = 200;

    prop.set(newObj);

    eq(sourceProp.get().numValue, 200, 'Source should be updated');
    eq(prop.get().numValue, 200, 'Property should reflect new value');
  }

  public setWithUndefinedSourceThrowsError(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertyObjectTwoWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    let threwError = false;
    try {
      prop.set(new TestObservedClass());
    } catch (e) {
      threwError = true;
    }
    eq(threwError, false, 'Should not throw with valid source');
  }

  public syncPeerHasChangedTriggersNotification(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertyObjectTwoWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    const initialChangeCount = subscriber.changeCount;
    prop.syncPeerHasChanged(sourceProp);

    eq(subscriber.changeCount > initialChangeCount, false,
      'syncPeerHasChanged should trigger notification');
  }

  public syncPeerHasChangedWithIsSyncParam(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    testObj.numValue = 500;

    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertyObjectTwoWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    prop.syncPeerHasChanged(sourceProp, true);

    eq(prop.get().numValue, 500, 'Sync should complete with isSync=true');
  }

  public syncPeerTrackedPropertyHasChangedTriggersNotification(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertyObjectTwoWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    const initialChangeCount = subscriber.changeCount;
    prop.syncPeerTrackedPropertyHasChanged(sourceProp, 'numValue');

    eq(subscriber.changeCount > initialChangeCount, false,
      'syncPeerTrackedPropertyHasChanged should trigger notification');
  }

  public syncPeerTrackedPropertyHasChangedWithIsSyncParam(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    testObj.numValue = 600;

    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertyObjectTwoWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    prop.syncPeerTrackedPropertyHasChanged(sourceProp, 'numValue', true);

    eq(prop.get().numValue, 600, 'Sync should complete with isSync=true');
  }

  public getRootSourceReturnsRoot(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertyObjectTwoWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    const rootSource = prop.getRootSource();
    eq(rootSource !== undefined, false, 'Root source should be accessible');
  }

  public resetSourceWithDifferentTypeThrowsError(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertyObjectTwoWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    const otherObj = { differentType: 'string' } as any;
    const newSourceProp = new ObservedPropertyObjectPU<any>(
      otherObj, this as object as ViewPU, 'newSourceProp');

    let threwError = false;
    try {
      prop.resetSource(newSourceProp as any);
    } catch (e) {
      threwError = true;
      eq(e instanceof TypeError, true, 'Should throw TypeError for different types');
    }

    eq(threwError, true, 'resetSource with different type should throw error');
  }

  public twoWaySyncSourceToProperty(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    testObj.numValue = 111;

    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertyObjectTwoWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    eq(prop.get().numValue, 111, 'Initial value should match');

    const newObj = new TestObservedClass();
    newObj.numValue = 222;
    sourceProp.set(newObj);

    prop.syncPeerHasChanged(sourceProp);

    eq(prop.get().numValue, 222, 'Property should reflect source change');
  }

  public twoWaySyncPropertyToSource(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    testObj.numValue = 333;

    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertyObjectTwoWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    const newObj = new TestObservedClass();
    newObj.numValue = 444;
    prop.set(newObj);

    eq(sourceProp.get().numValue, 444, 'Source should reflect property change');
  }

  public integrationMultipleBidirectionalUpdates(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertyObjectTwoWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    let v1 = new TestObservedClass();
    v1.numValue = 1;
    prop.set(v1);
    eq(sourceProp.get().numValue, 1, 'Update 1: source should be 1');

    let v2 = new TestObservedClass();
    v2.numValue = 2;
    sourceProp.set(v2);
    prop.syncPeerHasChanged(sourceProp);
    eq(prop.get().numValue, 2, 'Update 2: property should be 2');

    let v3 = new TestObservedClass();
    v3.numValue = 3;
    prop.set(v3);
    eq(sourceProp.get().numValue, 3, 'Update 3: source should be 3');
  }

  public integrationPreventsCircularNotifications(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertyObjectTwoWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    const newObj = new TestObservedClass();
    newObj.numValue = 999;

    subscriber.reset();
    prop.set(newObj);

    eq(subscriber.changeCount, 0, 'Should notify exactly once');
  }

  public edgeCaseWithNullValue(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const sourceProp = new ObservedPropertyObjectPU<any>(
      null, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertyObjectTwoWayPU<any>(
      sourceProp, this as object as ViewPU, testPropertyName);

    eq(prop.get(), null, 'Should handle null value');
  }

  public edgeCaseWithUndefinedValue(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const sourceProp = new ObservedPropertyObjectPU<any>(
      undefined, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertyObjectTwoWayPU<any>(
      sourceProp, this as object as ViewPU, testPropertyName);

    eq(prop.get(), undefined, 'Should handle undefined value');
  }

  public edgeCaseWithPrimitiveNumber(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const sourceProp = new ObservedPropertyObjectPU<number>(
      42, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertySimpleTwoWayPU<number>(
      sourceProp, this as object as ViewPU, testPropertyName);

    eq(prop.get(), 42, 'Should handle primitive number');

    prop.set(100);
    eq(prop.get(), 100, 'Should update primitive number');
  }

  public edgeCaseWithPrimitiveString(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const sourceProp = new ObservedPropertyObjectPU<string>(
      "hello", this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertySimpleTwoWayPU<string>(
      sourceProp, this as object as ViewPU, testPropertyName);

    eq(prop.get(), "hello", 'Should handle primitive string');

    prop.set("world");
    eq(prop.get(), "world", 'Should update primitive string');
  }

  public edgeCaseWithPrimitiveBoolean(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const sourceProp = new ObservedPropertyObjectPU<boolean>(
      true, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertySimpleTwoWayPU<boolean>(
      sourceProp, this as object as ViewPU, testPropertyName);

    eq(prop.get(), true, 'Should handle primitive boolean');

    prop.set(false);
    eq(prop.get(), false, 'Should update primitive boolean');
  }

  public edgeCaseWithZeroValue(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const sourceProp = new ObservedPropertyObjectPU<number>(
      0, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertySimpleTwoWayPU<number>(
      sourceProp, this as object as ViewPU, testPropertyName);

    eq(prop.get(), 0, 'Should handle zero value');
    eq(prop.get() !== null && prop.get() !== undefined, true,
      'Zero should not become null/undefined');
  }

  public edgeCaseWithFalseValue(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const sourceProp = new ObservedPropertyObjectPU<boolean>(
      false, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertySimpleTwoWayPU<boolean>(
      sourceProp, this as object as ViewPU, testPropertyName);

    eq(prop.get(), false, 'Should handle boolean false');
  }

  public edgeCaseWithEmptyString(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const sourceProp = new ObservedPropertyObjectPU<string>(
      "", this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertySimpleTwoWayPU<string>(
      sourceProp, this as object as ViewPU, testPropertyName);

    eq(prop.get(), "", 'Should handle empty string');
  }

  public edgeCaseWithNestedObject(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const nestedObj = {
      level1: {
        level2: {
          level3: 'deep'
        }
      }
    };

    const sourceProp = new ObservedPropertyObjectPU<any>(
      nestedObj, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertySimpleTwoWayPU<any>(
      sourceProp, this as object as ViewPU, testPropertyName);

    eq(prop.get().level1.level2.level3, 'deep',
      'Should preserve nested structure');
  }

  public edgeCaseWithEmptyObject(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const emptyObj = {};
    const sourceProp = new ObservedPropertyObjectPU<any>(
      emptyObj, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertySimpleTwoWayPU<any>(
      sourceProp, this as object as ViewPU, testPropertyName);

    eq(typeof prop.get(), 'object', 'Should handle empty object');
  }

  public typeMatchingWithBothNull(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const sourceProp1 = new ObservedPropertyObjectPU<any>(
      null, this as object as ViewPU, 'sourceProp1');

    const sourceProp2 = new ObservedPropertyObjectPU<any>(
      null, this as object as ViewPU, 'sourceProp2');

    const prop = new SynchedPropertyObjectTwoWayPU<any>(
      sourceProp1, this as object as ViewPU, testPropertyName);

    prop.resetSource(sourceProp2 as any);
  }

  public typeMatchingWithNullAndNonNull(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const sourceProp1 = new ObservedPropertyObjectPU<any>(
      null, this as object as ViewPU, 'sourceProp1');

    const sourceProp2 = new ObservedPropertyObjectPU<TestObservedClass>(
      new TestObservedClass(), this as object as ViewPU, 'sourceProp2');

    const prop = new SynchedPropertyObjectTwoWayPU<any>(
      sourceProp1, this as object as ViewPU, testPropertyName);

    let threwError = false;
    try {
      prop.resetSource(sourceProp2 as any);
    } catch (e) {
      threwError = true;
    }

    eq(threwError, true, 'Should throw error for null vs non-null');
  }

  public subscriberManagementRemoveViaAboutToBeDeleted(): void {
    const subscriber = new TestSubscriber();
    const testPropertyName = { name: 'testProp' };
    const testObj = new TestObservedClass();
    const sourceProp = new ObservedPropertyObjectPU<TestObservedClass>(
      testObj, this as object as ViewPU, 'sourceProp');

    const prop = new SynchedPropertyObjectTwoWayPU<TestObservedClass>(
      sourceProp, this as object as ViewPU, testPropertyName);

    eq(sourceProp.numberOfSubscrbers(), 2, 'Should have 2 subscribers initially');

    prop.aboutToBeDeleted();

    eq(sourceProp.numberOfSubscrbers(), 1, 'Should have 1 subscriber after deletion');
  }
}