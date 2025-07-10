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

import { TestStats } from './testStats'

export interface ITestFile {
  getId(): string;
  beforeAll(): void;
  beforeEach(): void;
  afterAll(): void;
  afterEach(): void;
}

// Run all functions from testInstance (excluding constructor and interfaceMethodNames)
// You can add functions to test classes and getOwnPropertyNames automatically get names
// of those. Then tests are executed. And result is logged.
export function TestRunner(testInstance : ITestFile) {

  // List of methods from ITestFile to exclude
  // Also exclude function starting with _ so that its possible to make helper functions
  // that are not test cases
  const interfaceMethodNames = ['getId', 'beforeAll', 'beforeEach', 'afterAll', 'afterEach'];

  const testCaseNames = Object.getOwnPropertyNames(Object.getPrototypeOf(testInstance))
    .filter(name =>
    name !== 'constructor' &&
      typeof (testInstance as any)[name] === 'function' &&
      !interfaceMethodNames.includes(name) &&
      !name.startsWith('_')
    );

  let passed = 0;
  let failed = 0;
  const testResults: { name: string, duration: number, result: boolean | Error }[] = [];

  const totalStart = Date.now();

  // Call actions before all tests...
  try {
    testInstance.beforeAll();
  } catch (err: any) {
    console.error(`❌ $ERROR start executing test class: ${testInstance.getId()}`, err);
    TestStats.addResult(`${testInstance.getId()}`, false, '' + `beforeAll() call FAILED`);
    return;
  }
  console.log(`---- Running ${testInstance.getId()} ----`);

  for (const name of testCaseNames) {

    // Add result to stats for final results af all tests.
    const nameWithTestsClass = testInstance.getId() + '->' + name;

    const start = Date.now();
    try {
      // Call functions that is executed before every test
      // If test does not throw error it is PASSED
      (testInstance as ITestFile).beforeEach();
      // Call testMethod
      (testInstance as any)[name].bind(this)();
      (testInstance as ITestFile).afterEach();
      const duration = Date.now() - start;
      passed++;
      console.log(`✅ ${name} passed (${duration}ms)`);
      testResults.push({ name, duration, result: true});
      TestStats.addResult(nameWithTestsClass, true, `${duration} ms` );
    } catch (err: any) {
      const duration = Date.now() - start;
      failed++;
      console.error(`❌ ${name} ERROR (${duration}ms):`, err);
      testResults.push({ name, duration, result: err });
      TestStats.addResult(nameWithTestsClass, false, `${duration} ms` + ` ${err}`);
    }
  }

  // Call actions before all tests...
  try {
    testInstance.afterAll();
  } catch (err: any) {
    console.error(`❌ $ERROR calling afterAll for ${testInstance.getId()}`, err);
    TestStats.addResult(`${testInstance.getId()}`, false, '' + `afterAll() call FAILED`);
    return;
  }

  const totalDuration = Date.now() - totalStart;

  // Summary report
  console.log(`\n🔎 Test Summary:`);
  console.log(`Total tests: ${testCaseNames.length}`);
  console.log(`✅ Passed: ${passed}`);
  console.error(`❌ Failed: ${failed}`);
  console.log(`⏱ Total time: ${totalDuration}ms`);

  if (failed > 0) {
    console.error(`❗ ${failed} test(s) failed. See logs above.`);
  } else {
    console.log(`🎉 All tests passed.`);
  }

}

// Compare that two values are equal
// a - the actual value or expression
// b - the expected correct value
// desc - optional description of test conditions; useful to identify which case failed when
//  multiple conditions exist in one test
export function eq<T>(a : T, b : T, desc?:string) : void {
  const ok : boolean = (a === b);
  if (!ok) {
    throw new Error(`WRONG value: ${a} expected: ${b}. ${desc}`);
  }
}

// Compare that two values are not equal
// a - the actual value or expression
// b - the value that 'a' must not equal
// desc - optional description of test conditions; useful to identify which case failed when
//  multiple conditions exist in one test
export function neq<T>(a : T, b : T, desc?:string) : void {
  const ok : boolean = (a !== b);
  if (!ok) {
    throw new Error(`WRONG value: ${a} must not equal to: ${b}. ${desc}`);
  }
}

// Compare that a is greater than b
// a - the actual value or expression
// b - the value that a should be greater than
// desc - optional description of test conditions; useful to identify which case failed when
//  multiple conditions exist in one test
export function gt<T>(a : T, b : T, desc?:string) : void {
  const ok : boolean = (a > b);
  if (!ok) {
    throw new Error(`WRONG value: ${a} expected >: ${b}. ${desc}`);
  }
}

// Compare that a is less than b
// a - the actual value or expression
// b - the value that a should be less than
// desc optional description of test conditions. Useful when there are multiple test
// conditions inside one test to identify the failed one in case of all not pass.
export function lt<T>(a : T, b : T, desc?:string) : void {
  const ok : boolean = (a < b);
  if (!ok) {
    throw new Error(`WRONG value: ${a} expected <: ${b}. ${desc}`);
  }
}