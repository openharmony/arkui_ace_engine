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
  static startTimer: boolean;
  static errorLogFrequency: Map<string, number>;
  static errorLogFlag: Set<string>;
  static limitLog(msg: string): number | undefined;
  static applicationError(...args: Object[]): void;
  static frequentApplicationError(msg: string): void;
  static frequentWarn(msg: string): void;
  static frequentError(msg: string): void;
}

declare let setTimeout: ((callback: () => void, delay: number) => number) | undefined;

export class StateMgmtConsoleTraceTests implements ITestFile {
  private idString: string = '';

  constructor(str: string) {
    this.idString = str;
  }

  public beforeAll(): void {}

  public beforeEach(): void {
    this.resetStateMgmtConsole();
  }

  public afterAll(): void {}

  public afterEach(): void {}

  public getId(): string {
    return this.idString;
  }


  public testFrequentWarnSuppressesDuplicate(): void {
    stateMgmtConsole.frequentWarn('warn once');
    stateMgmtConsole.frequentWarn('warn once');

    eq(stateMgmtConsole.errorLogFlag.has('warn once'), true, 'warning key should be recorded');
    eq(stateMgmtConsole.errorLogFlag.size, 1, 'duplicate warning should not create extra flag entries');
    eq(stateMgmtConsole.errorLogFrequency.get('warn once'), 2, 'warning frequency should still be counted');
  }

  public testLimitLogRecordsFrequency(): void {
    const firstCount = stateMgmtConsole.limitLog('limit once');
    const secondCount = stateMgmtConsole.limitLog('limit once');

    eq(firstCount, undefined, 'first limitLog should not have previous count');
    eq(secondCount, 1, 'second limitLog should return previous count');
    eq(stateMgmtConsole.startTimer, true, 'limitLog should start timer flag');
    eq(stateMgmtConsole.errorLogFrequency.get('limit once'), 2, 'limitLog should update frequency');
  }

  public testLimitLogResetsFlagAfterTimeout(): void {
    stateMgmtConsole.errorLogFlag.add('timeout msg');
    stateMgmtConsole.errorLogFlag.add('timeout msg 1');
    stateMgmtConsole.errorLogFlag.add('timeout msg 2');
    stateMgmtConsole.limitLog('timeout msg');
    
    eq(stateMgmtConsole.startTimer, true, 'limitLog should enable timer before timeout callback');
    eq(stateMgmtConsole.errorLogFlag.size, 3, 'timeout callback should clear errorLogFlag');
  }

  public testFrequentApplicationErrorSuppressesDuplicate(): void {
    stateMgmtConsole.frequentApplicationError('app error once');
    stateMgmtConsole.frequentApplicationError('app error once');

    eq(stateMgmtConsole.errorLogFlag.has('app error once'), true, 'application error key should be recorded');
    eq(stateMgmtConsole.errorLogFlag.size, 1, 'duplicate application error should not create extra flag entries');
    eq(stateMgmtConsole.errorLogFrequency.get('app error once'), 2, 'application error frequency should still be counted');
  }

  public testFrequentErrorSuppressesDuplicate(): void {
    stateMgmtConsole.frequentError('error once');
    stateMgmtConsole.frequentError('error once');

    eq(stateMgmtConsole.errorLogFlag.has('error once'), true, 'error key should be recorded');
    eq(stateMgmtConsole.errorLogFlag.size, 1, 'duplicate error should not create extra flag entries');
    eq(stateMgmtConsole.errorLogFrequency.get('error once'), 2, 'error frequency should still be counted');
  }


  private resetStateMgmtConsole(): void {
    stateMgmtConsole.startTimer = false;
    stateMgmtConsole.errorLogFrequency = new Map<string, number>();
    stateMgmtConsole.errorLogFlag = new Set<string>();
  }
}
