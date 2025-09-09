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

declare class ObserveV2   {
  public static readonly SYMBOL_REFS;
  addRef4IdInternal;
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
  addRef(target: object, attrName: string): void;
  addRefV2Compatibility(target: object, attrName: string): void;
  addRef4Id(id: number, target: object, attrName: string): void;
  runIdleTasks(deadline?: number): void;
}

interface IMonitor {
  dirty: Array<string>;
  value<T>(key?: string): IMonitorValue<T> | undefined;
}

declare const Monitor: (key: string, ...keys: string[]) => (target: any, _: any, descriptor: any) => void;

@ObservedV2
class TestClass {
  @Local testVar1 : number = 0;
  @Local testVar2 : number = 0;
  @Local testVar3 : number = 0;

  constructor () {
  }
}

declare class Text {
  static create(label: string): void;
  static pop(): void;
}

export class ObserveTestsV2 implements ITestFile {

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

  /* Verify that addVariableDecoMeta function works
  * Calls addVariableDecoMeta and verifies it adds the
  * correct decorator. For example '@Local'
  */
  public addVariableDecoMetaTest(): void {
    const deco: string  ='@Local'
    let testClass = new TestClass();
    const testVarName = 'testVarTest';
    ObserveV2.addVariableDecoMeta(testClass, testVarName, deco)
    const decoMeta = testClass[ObserveV2.V2_DECO_META][testVarName]?.deco;
    eq(decoMeta, deco);
  }

  /*  Tests that startRecordDependencies and stopRecordDependencies
  *
  */

  public testStartStopGetRecording(): void {
    let idAtStart = ObserveV2.getCurrentRecordedId();
    const idNum: number = 5;
    ObserveV2.getObserve().startRecordDependencies(this, idNum);
    let idAtRecording = ObserveV2.getCurrentRecordedId()
    ObserveV2.getObserve().stopRecordDependencies();
    let idAtEnd = ObserveV2.getCurrentRecordedId();
    eq(idAtStart, idAtEnd, 'Start equals end');
    eq (idAtRecording, idNum, 'Recording id is correct');
  }

  /*  Tests that executeUnobserved function
  * Should run lambda which changes val to 100
  */
  public testExecuteUnobservedFunc(): void {
    let val: number = ObserveV2.getObserve().executeUnobserved<number>(() => 100)
    eq(val, 100);
  }
  /*  Tests addRef4IdInternal
  * Should return true for given "test" set has the value given.
  */
  public testAddRef(): void {
    const testId:number = 1000;
    ObserveV2.getObserve().addRef4IdInternal(testId, this, "test");
    eq( this[ObserveV2.SYMBOL_REFS]["test"].has(testId), true, "addRef4IdInternal test")
  }

}