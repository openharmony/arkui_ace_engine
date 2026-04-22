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
  static debug(...args: Object[]): void;
}

declare class ConfigureStateMgmt {
  static instance__?: ConfigureStateMgmt;
  v2ObservedTrackInUse_: boolean;
  puObservedTrackInUse_: boolean;
  static get instance(): ConfigureStateMgmt;
  usingV2ObservedTrack(feature: string, contextOfUse?: string): void;
  usingPUObservedTrack(feature: string, contextOfUse?: string): void;
  needsV2Observe(): boolean;
}

export class StateMgmtConfigureTests implements ITestFile {
  private idString: string = '';

  constructor(str: string) {
    this.idString = str;
  }

  public beforeAll(): void {}

  public beforeEach(): void {
    ConfigureStateMgmt.instance__ = undefined;
  }

  public afterAll(): void {}

  public afterEach(): void {}

  public getId(): string {
    return this.idString;
  }

  public testInstanceReturnsSingleton(): void {
    const instance1 = ConfigureStateMgmt.instance;
    const instance2 = ConfigureStateMgmt.instance;

    eq(instance1, instance2);
  }

  public testUsingV2ObservedTrackEnablesNeedsV2Observe(): void {
    const instance = ConfigureStateMgmt.instance;

    instance.usingV2ObservedTrack('ObservedV2', 'in test');

    eq(instance.v2ObservedTrackInUse_, true);
    eq(instance.needsV2Observe(), true);
  }

  public testUsingPUObservedTrackOnlyUpdatesPuFlag(): void {
    const instance = ConfigureStateMgmt.instance;

    instance.usingPUObservedTrack('PUObserved', 'in test');

    eq(instance.puObservedTrackInUse_, true);
    eq(instance.needsV2Observe(), false);
  }

  public testNeedsV2ObserveIsFalseByDefault(): void {
    eq(ConfigureStateMgmt.instance.needsV2Observe(), false);
  }
}
