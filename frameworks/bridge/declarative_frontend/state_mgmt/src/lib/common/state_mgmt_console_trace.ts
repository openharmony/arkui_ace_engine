/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
 * state mgmt library uses its own class for logging
* allows to remap separately from other use of aceConsole
*
* everything in this file is framework internal
*/

enum LogTag {
  STATE_MGMT = 0
}

class stateMgmtConsole {
  private static startTimer: boolean = false;

  private static errorLogFrequency: Map<string, number> = new Map<string, number>();

  private static errorLogFlag: Set<string> = new Set<string>();

  private static MAX_LOG_TYPES: number = 3000;

  public static log(...args: any): void {
    aceConsole.log(LogTag.STATE_MGMT, ...args);
  }
  public static debug(...args: any): void {
    aceConsole.debug(LogTag.STATE_MGMT, ...args);
  }
  public static info(...args: any): void {
    aceConsole.info(LogTag.STATE_MGMT, ...args);
  }
  public static warn(...args: any): void {
    aceConsole.warn(LogTag.STATE_MGMT, ...args);
  }
  public static error(...args: any): void {
    aceConsole.error(LogTag.STATE_MGMT, ...args);
  }
  public static propertyAccess(...args: any): void {
    // enable for fine grain debugging variable observation
    // aceConsole.error(...args)
  }
  public static applicationError(...args: any): void {
    aceConsole.error(LogTag.STATE_MGMT, `FIX THIS APPLICATION ERROR:`, ...args);
  }

  public static applicationWarn(...args: any): void {
    aceConsole.warn(LogTag.STATE_MGMT, ...args);
  }

  public static frequentApplicationError(msg: string): void {
    if (!stateMgmtConsole.startTimer) {
      stateMgmtConsole.startTimer = true;
      setTimeout(() => {
        stateMgmtConsole.errorLogFlag.clear();
        stateMgmtConsole.startTimer = false;
      }, 20000);
    }
    const count = stateMgmtConsole.errorLogFrequency.get(msg);
    stateMgmtConsole.errorLogFrequency.set(msg, count ? count + 1 : 1);
    if (!stateMgmtConsole.errorLogFlag.has(msg)) {
      stateMgmtConsole.errorLogFlag.add(msg);
      if (count) {
        aceConsole.error(LogTag.STATE_MGMT, `FIX THIS APPLICATION ERROR:`, msg, `Current log drops ${count + 1} line(s).`);
      } else {
        aceConsole.error(LogTag.STATE_MGMT, `FIX THIS APPLICATION ERROR:`, msg);
      }
    }

    if (stateMgmtConsole.errorLogFrequency.size > stateMgmtConsole.MAX_LOG_TYPES) {
      aceConsole.error(LogTag.STATE_MGMT, `There are more than ${stateMgmtConsole.errorLogFrequency.size} different kinds application error logs, please check the previous log printed.`);
      stateMgmtConsole.errorLogFrequency.clear();
    }
  }

  public static featureCombinationError(msg: string): void {
    aceConsole.warn(LogTag.STATE_MGMT, msg);
  }
}

type TraceArgs = string | number | boolean;

class stateMgmtTrace {
  public static scopedTrace<T>(codeBlock: () => T, arg1: string, ...args: TraceArgs[]): T {
    aceTrace.begin(arg1, ...args);
    let result: T = codeBlock();
    aceTrace.end();
    return result;
  }
}

class errorReport {
  public static varValueCheckFailed<T>(params: { customComponent: string, variableDeco: string, variableName: string, expectedType: string, value: T }): void {
    let msg = `@Component '${params.customComponent}': Illegal variable value error with decorated variable ${params.variableDeco} '${params.variableName}': `;
    msg += `failed validation: '${params.expectedType}`;
    try {
      msg += `, attempt to assign value type: '${typeof params.value}'`;
      msg += `, value: '${JSON.stringify(params.value, null, 4)}'`;
    } catch (e) { }

    msg += '!';
    stateMgmtConsole.applicationError(msg);
    throw new TypeError(msg);
  }

  public static varObservationFailed<T>(params: { customComponent: string, variableDeco: string, variableName: string, value: T }): void {
    let msg = `@Component '${params.customComponent}': decorated variable ${params.variableDeco} '${params.variableName}': `;
    msg += `its class is neither decorated with '@Observed' nor it is an instance of 'SubscribableAbstract'`;

    try {
      msg += `, attempt to assign value type: '${typeof params.value}'`;
      msg += `, value: '${JSON.stringify(params.value, null, 4)}'`;
    } catch (e) { }

    msg += '!';

    throw new TypeError(msg);
  }
}