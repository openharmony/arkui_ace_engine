/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

class stateMgmtConsole {
    public static log (...args : any) : void {
        aceConsole.log(...args);
    }
    public static debug(...args : any) : void {
        aceConsole.debug(...args);
    }
    public static info (...args : any) : void {
        aceConsole.info(...args);
    }
    public static warn (...args : any) : void  {
        aceConsole.warn(...args);
    }
    public static error (...args : any) : void {
        aceConsole.error(...args);
    }
}

type TraceArgs = string | number | boolean;

class stateMgmtTrace {
    public static scopedTrace<T>(codeBlock: () => T, arg1: string, ...args: TraceArgs[]): T{
        aceTrace.begin(arg1, ...args);
        let result: T = codeBlock();
        aceTrace.end();
        return result;
    }
}
