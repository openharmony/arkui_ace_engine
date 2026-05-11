'use static'
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

import { run_computed } from './uipluginComputed'
import { ITestResults, getTestStats } from './lib/testFramework'
import { run_computed_params } from './uipluginComputedParams'
import { run_stateNumber } from './uipluginStateSimple'
import { run_state } from './uipluginState'
import { run_observed_object3 } from './uipluginObservedObject3'
import { run_makeobserved, run_makeobserved_short } from './uipluginUiUtils'
import { Entry, Component, Text, Column, State } from '@kit.ArkUI'

type TestCase = () => boolean;

const tests: TestCase[] = [
  run_computed,
  run_computed_params,
  run_stateNumber,
  run_state,
  run_observed_object3,
  run_makeobserved,
  run_makeobserved_short,
]

export function runTests(): string {
  console.error('runTests start')
  console.log('Creating special FactoryInternal instance for testing ...')

  let passed = 0
  let totalRuns = 0
  let failed = 0
  const results: string[] = [];
  const startTime = Date.now();

  // Changed false by default. 
  const stopAllOnErrorToDebugAnIssue: boolean = false;
  for (const test of tests) {
    // try catch disabled because of compiler errors
    try {
      test(); // Run test first
      // Now retrieve stats after test runs
      const stats: ITestResults = getTestStats();
      const ok = (stats.failed_ === 0);

      if (ok === true) {
        const msg = `\x1b[32mPASSED\x1b[0m ${test.name}. TCases: ${stats.tCases_}, Total test assertions: ${stats.tests_}`
        console.log(msg)
        results.push(msg);
        passed++;
        totalRuns += stats.tests_;
      } else {
        const msg = `\x1b[31mFAILED\x1b[0m ${test.name}. TCases: ${stats.tCases_}, Total test assertions: ${stats.tests_},\n         \x1b[31m${stats.failed_}\x1b[0m failed assertions:${stats.failedAssertionsList}`;
        console.error(msg);
        results.push(msg);
        failed++;
        totalRuns += stats.tests_;
      }
    } catch (e) {
      const stats: ITestResults = getTestStats();

      results.push(`\x1b[31mFAILED\x1b[0m ${test.name}. TCases: ${stats.tCases_}, Total tests run: ${stats.tests_} (\x1b[31m${e})\x1b[0m`);
      failed++;
      totalRuns += stats.tests_;

      if (stopAllOnErrorToDebugAnIssue) {
        console.log('Stopping all tests on error');
        break;
      }
    }
  }

  const endTime = Date.now();
  const durationMs = endTime - startTime;
  console.log('\x1b[34m\n\nTest Results:\x1b[0m\n');

  for (const line of results) {
    console.log('  ' + line)
  }

  const result = `\nSummary: ${passed} passed. ${failed} failed. Total test assertions: ${totalRuns}. Total time: ${durationMs} ms\n\n `;
  console.log(result);
  return result;
}

@Entry
@Component
struct Index {
  @State message: string = 'testing...';
  aboutToAppear() {
    this.message = runTests();
  }
  build() {
    Column() {
      Text(this.message)
    }
  }
}