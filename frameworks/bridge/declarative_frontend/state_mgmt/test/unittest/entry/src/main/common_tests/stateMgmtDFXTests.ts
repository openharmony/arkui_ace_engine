/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { eq, ITestFile } from '../lib/testRunner';

declare class stateMgmtConsole {
  static warn(...args: Object[]): void;
}

declare class stateMgmtDFX {
  static enableProfiler: boolean;
  static unwrapRawValue<T>(prop: T): T;
  static dumpDepenetElementV2(dependentElmIds: Set<number> | undefined, isGetElement?: boolean): Object[];
}

declare function setProfilerStatus(profilerStatus: boolean): void;

declare class ObservedPropertyAbstract<T> {
  getUnmonitored(): T;
}

declare class ObservedObject {
  static GetRawObject<T>(value: T): T;
}

declare class ObserveV2 {
  static SYMBOL_PROXY_GET_TARGET: string;
  static IsProxiedObservedV2(value: Object): boolean;
  static getObserve(): ObserveV2;
  getElementNameById(id: number): string;
  getElementInfoById(id: number): string;
}

declare class ComputedV2 {
  static MIN_COMPUTED_ID: number;
}

class TestObservedProperty<T> extends ObservedPropertyAbstract<T> {
  constructor(private value_: T) {
    super();
  }

  public getUnmonitored(): T {
    return this.value_;
  }
}

export class StateMgmtDFXTests implements ITestFile {
  private idString: string = '';
  static warnCalledCount: number = 0;
  static getElementNameByIdFunc: Function | undefined;

  constructor(str: string) {
    this.idString = str;
  }

  public beforeAll(): void {}

  public beforeEach(): void {
    StateMgmtDFXTests.warnCalledCount = 0;
    stateMgmtDFX.enableProfiler = false;
    stateMgmtConsole.warn = (): void => { StateMgmtDFXTests.warnCalledCount += 1; };
    ObservedObject.GetRawObject = <T>(value: T): T => value;
    ObserveV2.SYMBOL_PROXY_GET_TARGET = '__proxy_target';
    ObserveV2.IsProxiedObservedV2 = (value: Object): boolean => !!value && '__proxy_target' in value;
    const observeV2Instance = ObserveV2.getObserve();
    StateMgmtDFXTests.getElementNameByIdFunc = observeV2Instance.getElementNameById;
    observeV2Instance.getElementNameById = (id: number): string => `Text${id}`;
    observeV2Instance.getElementInfoById = (id: number): string => `Text[${id}]`;
    ComputedV2.MIN_COMPUTED_ID = 1000;
  }

  public afterAll(): void {}

  public afterEach(): void {
    const observeV2Instance = ObserveV2.getObserve();
    if (StateMgmtDFXTests.getElementNameByIdFunc) {
      observeV2Instance.getElementNameById = StateMgmtDFXTests.getElementNameByIdFunc as (id: number) => string;
    }
  }

  public getId(): string {
    return this.idString;
  }

  public testUnwrapRawValue(): void {
    eq((stateMgmtDFX.unwrapRawValue(new TestObservedProperty({ value: 10 })) as Object as { value: number }).value, 10);
    eq((stateMgmtDFX.unwrapRawValue({ __proxy_target: { value: 20 } }) as Object as { value: number }).value, 20);
  }

  public testDumpDepenetElementV2(): void {
    eq(JSON.stringify(stateMgmtDFX.dumpDepenetElementV2(new Set<number>([1, 2]))), JSON.stringify(['Text[1]', 'Text[2]']));
    eq(JSON.stringify(stateMgmtDFX.dumpDepenetElementV2(new Set<number>([1]), true)), JSON.stringify([{ elementId: 1, elementName: 'Text1' }]));
  }

  public testSetProfilerStatus(): void {
    setProfilerStatus(true);
    eq(stateMgmtDFX.enableProfiler, true);
    setProfilerStatus(false);
    eq(stateMgmtDFX.enableProfiler, false);
    eq(this.warnCalledCount, 2);
  }
}
