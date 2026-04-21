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

declare interface ArkTsUtil {
  name?: string;
}

declare class Utils {
  static currentAppApiVersion: number;
  static arkTsUtil: ArkTsUtil | undefined;
  static getApiVersion(): number;
  static isApiVersionEQAbove(target: number): boolean;
  static getArkTsUtil(): ArkTsUtil;
  static isNull(obj: any): boolean;
}

declare class ViewStackProcessor {
  static getApiVersion(): number;
}

declare class stateMgmtConsole {
  static error(...args: Object[]): void;
}

declare let requireInternal: (moduleName: string) => ArkTsUtil;

export class UtilsTests implements ITestFile {
  private idString: string = '';
  static getApiVersionCalledCount: number = 0;
  static requireInternalCalledCount: number = 0;
  static errorCalledCount: number = 0;
  static originalRequireInternal : Function | undefined;

  constructor(str: string) {
    this.idString = str;
  }

  public beforeAll(): void {}

  public beforeEach(): void {
    UtilsTests.getApiVersionCalledCount = 0;
    UtilsTests.requireInternalCalledCount = 0;
    UtilsTests.errorCalledCount = 0;
    Utils.currentAppApiVersion = -1;
    Utils.arkTsUtil = undefined;
    ViewStackProcessor.getApiVersion = (): number => {
      UtilsTests.getApiVersionCalledCount += 1;
      return 1200;
    };
    stateMgmtConsole.error = (...args: Object[]): void => {
      UtilsTests.errorCalledCount += 1;
    };
    UtilsTests.originalRequireInternal = globalThis.requireInternal;
    globalThis.requireInternal = (moduleName: string): ArkTsUtil => {
      UtilsTests.requireInternalCalledCount += 1;
      return { name: moduleName };
    };
  }

  public afterAll(): void {}

  public afterEach(): void {
    globalThis.requireInternal = UtilsTests.originalRequireInternal;
  }


  public getId(): string {
    return this.idString;
  }

  public testGetApiVersionCachesValue(): void {
    const firstVersion = Utils.getApiVersion();
    const secondVersion = Utils.getApiVersion();

    eq(firstVersion, 1200);
    eq(secondVersion, 1200);
    eq(UtilsTests.getApiVersionCalledCount, 1, 'getApiVersion should be cached');
    eq(Utils.currentAppApiVersion, 1200, 'currentAppApiVersion should be updated');
  }

  public testGetApiVersionReturnsMinusOneWhenViewStackProcessorUnavailable(): void {
    Utils.currentAppApiVersion = -1;
    ViewStackProcessor.getApiVersion = undefined as unknown as () => number;

    eq(Utils.getApiVersion(), -1);
  }

  public testIsApiVersionEQAboveReturnsTrueWhenVersionMatches(): void {
    Utils.currentAppApiVersion = 2011;

    eq(Utils.isApiVersionEQAbove(11), true);
  }

  public testIsApiVersionEQAboveReturnsFalseAndLogsWhenVersionInvalid(): void {
    Utils.currentAppApiVersion = -1;
    ViewStackProcessor.getApiVersion = (): number => -1;

    eq(Utils.isApiVersionEQAbove(9), false);
    eq(UtilsTests.errorCalledCount, 1, 'invalid version should log error');
  }

  public testGetArkTsUtilCachesRequireInternalResult(): void {
    const firstUtil = Utils.getArkTsUtil();
    const secondUtil = Utils.getArkTsUtil();

    eq(firstUtil.name, 'util');
    eq(secondUtil.name, 'util');
    eq(UtilsTests.requireInternalCalledCount, 1, 'getArkTsUtil should be cached');
    eq(Utils.arkTsUtil?.name, 'util');
  }

  public testIsNullChecksNullAndUndefined(): void {
    eq(Utils.isNull(null), true);
    eq(Utils.isNull(undefined), true);
    eq(Utils.isNull(0 as unknown as Object), false);
    eq(Utils.isNull('' as unknown as Object), false);
  }
}
