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
import { eq, gt, ITestFile } from '../lib/testRunner'

// See stateMgmt.d.ts. You can add more methods to classes from that file.
declare class Utils {
  static getApiVersion(): number;
  static isApiVersionEQAbove(target: number): boolean;
  static currentAppApiVersion: number;
}

declare class UINodeRegisterProxy {
  static readonly notRecordingDependencies: number;
  static readonly monitorIllegalV1V2StateAccess: number;
  static obtainDeletedElmtIds(): void;
  static unregisterElmtIdsFromIViews(): void;
  static unregisterRemovedElmtsFromViewPUs(removedElements: Array<number>): void;
  unregisterElmtIdsFromIViews(): void;
  static instance_: UINodeRegisterProxy;
  removeElementsInfo_: Array<number>;
  static ElementIdToOwningViewPU_: Map<number, WeakRef<ViewBuildNodeBase>>;
}

declare class UpdateFuncsByElmtId {
  private map_;
  delete(elmtId: number): boolean;
  clear(): void;
  get size(): number;
}

declare abstract class ViewBuildNodeBase {
  protected isView_: boolean;
  updateFuncByElmtId: UpdateFuncsByElmtId;
}

declare class PUV2ViewBase extends ViewBuildNodeBase{
  protected get isViewV2() : boolean;
}
type UpdateFunc = (elmtId: number, isFirstRender: boolean, param?: Object) => void;

declare class ObserveV2   {
  static getObserve(): ObserveV2;
  public stopRecordDependencies(): void;
  public startRecordDependencies(cmp: any, id: number): void;
  public getDecoratorInfo(target: object, attrName: string): string;
  public static readonly MONITOR_REFS;
  public static readonly V2_DECO_META;
  public clearBinding(id: number): void;
  public static IsObservedObjectV2(value :any) : boolean;
  public static getCurrentRecordedId(): number;
  public executeUnobserved<Z>(task: () => Z): Z;
  public static addVariableDecoMeta(proto: Object, varName: string, deco: string): void;
  public updateDirty(): void;
  public idleTasks_: (Array<[(...any: any[]) => any, ...any[]]> & { first: number, end: number });
}

declare class ViewV2 extends PUV2ViewBase{
  public debugInfo__(): string;
  public hasBeenRecycled_: boolean;
  public recycleSelf(reuseId: string): void;
  hasRecyclePool(): boolean;
  observeComponentCreation2(compilerAssignedUpdateFunc: UpdateFunc, classObject: {
    prototype: Object;
    pop?: () => void;
  }): void;
  get isViewV2(): boolean;
}

declare const trackInternal: (target: any, propertyKey: string) => void;

declare class ConfigureStateMgmt {
    private static readonly HOW_TO_SAY;
    private static instance__?;
    private v2ObservedTrackInUse_;
    private puObservedTrackInUse_;
    static get instance(): ConfigureStateMgmt;
    /**
     * framework code call this function when it sees use of a stateMgmt V2 @ObservedV2 @Trace
     *
     * @param feature specify feature separately from context of use, so that in future decision can be made
     *                for individual features, not use permit either use of V1 or V2.
     * @param contextOfUse purely for error messages. Give enough info that use is able to local the feature use in source code.
     * @returns true if no mix of features detected, false if mix is detected
     */
    usingV2ObservedTrack(feature: string, contextOfUse?: string): void;
    /**
 * framework code call this function when it sees use of a stateMgmt PU Observed / @Track
 *
 * @param feature specify feature separately from context of use, so that in future decision can be made
 *                for individual features, not use permit either use of V1 or V2.
 * @param contextOfUse purely for error messages. Give enough info that use is able to local the feature use in source code.
 * @returns true if no mix of features detected, false if mix is detected
 */
    usingPUObservedTrack(feature: string, contextOfUse?: string): void;
    /**
      * Return true if object deep observation mechanisms need to be enabled
      * that is when seen V2 @ObservedV2, @Trace, or @Monitor decorator used in at least one class
      * (we could but we do not check for class object instance creation for performance reasons)
      * @returns
      */
    needsV2Observe(): boolean;
}

export class CommonTestsV2 implements ITestFile {

  private idString : string = "";

  constructor(str : string) {
    console.log(`Creating StateManagemetTest: ${str}`)
    this.idString = str;
  }

  // Executed before any tests. Can be empty
  public beforeAll () : void {}

  // Executed before every invidual tests. Can be empty
  public beforeEach () : void {}

  // Executed after any tests. Can be empty
  public afterAll () : void {}

  // Executed after every individual tests. Can be empty
  public afterEach () : void {}


  public getId() : string {
    return this.idString;
  }

  // Test cases start from here. All functions are run automatically except those starting with _

  /* Verify that Utils API version check is working
  * Calls getApiVersion and isApiVersionEQAbove
  */
  public verifyAPIVersion() : void {
    const atLeast: number = 14;
    const apiVer: number = Utils.getApiVersion();
    // Note Api version format looks like this 50002014
    // So to compare it to needed one isApiVersionEQAbove is used
    gt(apiVer, 0, 'Api version exists');
    eq(Utils.isApiVersionEQAbove(atLeast), true, 'Api version big enough');
  }

  /* Verify that detections of V1 vs. V2 works
  * Calls: isViewV2 - expects true;
  */
  public verifyThisIsV2Object(): void {
    const bIsV2: boolean = (this as any as ViewV2)?.isViewV2;
    eq(bIsV2, true);
  }
  /* Test ConfigureStateMgmt
  * needsV2Observe should return true after usingV2ObservedTrack called.
  */
 public testConfigureStateMgmt(): void {
   const conf : ConfigureStateMgmt = new ConfigureStateMgmt();
   conf.usingV2ObservedTrack('testConfigureStateMgmt', 'testConfigureStateMgmt');
   eq(conf.needsV2Observe(), true, 'ConfigureStateMgmt needs V2 observe');
 }
}