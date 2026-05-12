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

import { StateMgmtConsole } from '../tools/stateMgmtDFX';
import { run_computed } from './uipluginComputed'
import { ITestResults, getTestStats } from './lib/testFramework'
import { run_app_storage_v2_simple } from './uipluginAppStorageV2simple'
import { run_app_storage_v2 } from './uipluginAppStorageV2'
import { run_persistent_storage_v2 } from './uipluginPersistentStorageV2'
import { run_persistent_storage_v2_simple } from './uipluginPersistentStorageV2simple'
import { run_computed_params } from './uipluginComputedParams'
import { run_stateNumber } from './uipluginStateSimple'
import { run_state } from './uipluginState'
import { run_custom_arrays } from './uiplugin_custom_arrays'
import { run_observed_object3 } from './uipluginObservedObject3'
import { run_makeobserved, run_makeobserved_short } from './uipluginUiUtils'
import { run_monitor, run_sync_monitor } from './uipluginMonitorAsyncSyncBasics'
import { run_monitor_date, run_syncmonitor_date } from './uipluginMonitorAsyncSyncDate'
import { run_monitor_wildcard, run_syncmonitor_wildcard } from './uipluginMonitorWithWildcard'
import { run_monitor_object } from './uipluginMonitorObject'
import { run_monitor_map, run_syncmonitor_map } from './uipluginMonitorAsyncSyncMap'
import { run_monitor_set, run_syncmonitor_set } from './uipluginMonitorAsyncSyncSet'
import { run_monitor_class_map_set, run_syncmonitor_class_map_set } from './uipluginMonitorAsyncSyncClassMapSet'
import { run_addmonitor } from './uipluginAddMonitorWildcards'
import { run_addmonitor_date, run_addsyncmonitor_date } from './uipluginAddMonitorAsyncSyncDate'
import { run_monitor_array, run_syncmonitor_array } from './uipluginMonitorAsyncSyncArray'
import { run_monitor_computed, run_syncmonitor_computed } from './uipluginMonitorAsyncSyncComputed'
import { run_monitor_edge_lambda, run_syncmonitor_edge_lambda } from './uipluginMonitorAsyncSyncEdgeLambda'
import { run_monitor_edge_api, run_syncmonitor_edge_api } from './uipluginMonitorAsyncSyncEdgeAPI'


type TestCase = () => boolean;

const tests11: TestCase[] = [
    run_app_storage_v2_simple,
    run_app_storage_v2,
    run_computed,
    run_computed_params,
    run_stateNumber,
    run_state,
    run_observed_object3,
    run_makeobserved,
    run_makeobserved_short,
    run_persistent_storage_v2,
    run_persistent_storage_v2_simple,
    run_monitor,
    run_monitor_object,
    run_sync_monitor,
    run_addmonitor,
    run_monitor_wildcard,
  ]

const tests2: TestCase[] = [
  run_monitor,
  run_monitor_object,
  run_addmonitor,
  run_monitor_array,
  run_syncmonitor_array,
  run_syncmonitor_date,
  run_syncmonitor_map,
  run_syncmonitor_set,
  //run_custom_arrays,
  run_computed,
  run_monitor_wildcard,
  run_syncmonitor_wildcard,
  run_sync_monitor, //fixme
  ]

const tests: TestCase[] = [
  // Storage
  run_app_storage_v2_simple,
  run_app_storage_v2,
  run_persistent_storage_v2,
  run_persistent_storage_v2_simple,
  // State / utilities
  run_stateNumber,
  run_state,
  run_custom_arrays,
  run_observed_object3,
  run_makeobserved,
  run_makeobserved_short,
  // Computed
  run_computed,
  run_computed_params,
  // Monitor
  run_monitor,
  run_monitor_object,
  run_monitor_array,
  run_monitor_computed,
  run_monitor_date,
  run_monitor_map,
  run_monitor_set,
  run_monitor_class_map_set,
  run_monitor_wildcard,
  run_monitor_edge_lambda,
  run_monitor_edge_api,
  run_addmonitor,
  run_addmonitor_date,
  // Sync monitor
  run_sync_monitor,
  run_syncmonitor_array,
  run_syncmonitor_computed,
  run_syncmonitor_date,
  run_syncmonitor_map,
  run_syncmonitor_set,
  run_syncmonitor_class_map_set,
  run_syncmonitor_wildcard,
  run_syncmonitor_edge_lambda,
  run_syncmonitor_edge_api,
  run_addsyncmonitor_date,
]

export function runTests(): void {
  console.error('runTests start')
  StateMgmtConsole.log('Creating special FactoryInternal instance for testing ...')

  let passed = 0
  let totalTcases = 0
  let totalRuns = 0
  let failed = 0
  const results: Array<string> = new Array<string>();
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
        totalTcases += stats.tCases_;
        totalRuns += stats.tests_;
      } else {
        const msg = `\x1b[31mFAILED\x1b[0m ${test.name}. TCases: ${stats.tCases_}, Total test assertions: ${stats.tests_},\n         \x1b[31m${stats.failed_}\x1b[0m failed assertions:${stats.failedAssertionsList}`;
        console.error(msg);
        results.push(msg);
        failed++;
        totalTcases += stats.tCases_;
        totalRuns += stats.tests_;
      }
    } catch (e) {
      const stats: ITestResults = getTestStats();

      results.push(`\x1b[31mFAILED\x1b[0m ${test.name}. TCases: ${stats.tCases_}, Total tests run: ${stats.tests_} (\x1b[31m${e})\x1b[0m`);
      failed++;
      totalTcases += stats.tCases_;
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

  const totalSuites = passed + failed;
  console.log(`\nSummary: Test suites: ${totalSuites} (\x1b[32m${passed}\x1b[0m passed, \x1b[31m${failed}\x1b[0m failed). Test cases: ${totalTcases}. Test assertions: ${totalRuns}. Total time: ${durationMs} ms\n\n `)
}
