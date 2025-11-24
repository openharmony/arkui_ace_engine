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

let report : string = "";
let shortReport : string = "";

let tCases_ : number = 0;
let tests_ : number = 0;
let failed_ : number = 0;
let failedAssertionsList : string = "";

export interface ITestResults {
  tCases_: number;
  tests_: number;
  failed_ : number;
  failedAssertionsList : string;
}

export function getTestStats(): ITestResults {

  return { tCases_, tests_, failed_, failedAssertionsList};
}


export function tsuite(msg: string, testMe: () => void): () => void {
  return () => {
    const log = (`\nRun test suite: '${msg}'\n`);
    report += `\n${log}\n\n`;
    shortReport += `\n${log}\n`;
    console.log(log)
    tCases_ = 0;
    tests_ = 0;
    failed_ = 0;
    testMe();
  };
}

export function tcase(msg: string, testMe: () => void): void {
  try {
    tCases_++;
    const log = `\n----- Run test case: '${msg}' ------`;
    console.log(log);
    testMe();
  } catch (e) {
    throw new Error(`Test Case '${msg}' failed with error: ${e instanceof Error ? e.message : String(e)}`);
  }
}

export function test(msg: string, assertion: boolean): void {
  tests_++;
  if (!assertion) {
    console.error(`The failed test assertion is: '${msg}' ❌ \n`);
    failedAssertionsList += `\n         - ${msg}`;

    failed_ += 1;
  } else {
    console.log(`${msg} ✅`);
  }
}

// compare a and b are equal value and equal type
// a - the expression
// b - the correct value
export function eq<T>(a : T, b : T) : boolean  {
  const ok : boolean = (a === b);
  if (!ok) {
    console.error(`WRONG actual value '${a}' expected equal to value '${b}'`);
    console.error(`WRONG class value '${Type.of(a).getName()}' expected equal to value '${Type.of(b).getName()}'`);
  }
  return ok;
}


export function neq<T>(a : T, b : T) : boolean  {
  const ok : boolean = (a !== b);
  if (!ok) {
    console.error(`WRONG actual value '${a}' should be unequal to '${b}'`);
  }
  return ok;
}

export function not_eq<T>(a : T, b : T) : boolean {
  const ok : boolean = (a !== b);
  if (!ok) {
    console.error(`WRONG actual value '${a}' ❌ to be different from value '${b}'`);
  }
  return ok;
}