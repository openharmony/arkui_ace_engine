import { int32 } from 'stateManagement/mock/env_mock'
import { TestMSM } from 'stateManagement/utest/lib/testAddRefFireChange'
import { StateMgmtFactory } from 'stateManagement/interface/iStateMgmtFactory.ets'
import { __StateMgmtFactoryImpl } from 'stateManagement/base/stateMgmtFactory.ets'
import { FactoryInternal } from 'stateManagement/base/iFactoryInternal.ets'
import { TestFactory } from 'stateManagement/utest/lib/testAddRefFireChange.ets'
import { Observe } from 'stateManagement/interface/iObserve.ets'
import { ITestResults, getTestStats } from 'stateManagement/utest/lib/testFramework'
import { ObserveSingleton } from 'stateManagement/base/observeSingleton.ets'
import { stateMgmtConsole } from 'stateManagement/tools/stateMgmtConsoleTrace'
import { run_observed_object3 } from 'stateManagement/utest/uiPlugin/uipluginObservedObject3'
import { run_observed_object4 } from 'stateManagement/utest/uiPlugin/uipluginObservedObject4'
import { run_observed_object5 } from 'stateManagement/utest/uiPlugin/uipluginObservedObject5'
import { run_observed_interface1 } from 'stateManagement/utest/src/testObservedInterface1.ets'
import { run_state } from 'stateManagement/utest/uiPlugin/uipluginState.ets'
import { run_stateNumber } from 'stateManagement/utest/uiPlugin/uipluginStateSimple.ets'
import { run_link1 } from 'stateManagement/utest/uiPlugin/uipluginLink1.ets'
import { run_link2 } from 'stateManagement/utest/uiPlugin/uipluginLink2.ets'
import { run_link3 } from 'stateManagement/utest/uiPlugin/uipluginLink3.ets'
import { run_consume } from 'stateManagement/utest/uiPlugin/uipluginProvideConsume.ets'
import { run_consumetypes } from 'stateManagement/utest/uiPlugin/uipluginProvideConsume_override.ets'
import { run_local } from 'stateManagement/utest/uiPlugin/uipluginLocal.ets'
import { run_param } from 'stateManagement/utest/uiPlugin/uipluginParam.ets'
import { run_param_once } from 'stateManagement/utest/uiPlugin/uipluginParamOnce.ets'
import { run_consumer } from 'stateManagement/utest/uiPlugin/uipluginProviderConsumer'
import { run_computed } from 'stateManagement/utest/uiPlugin/uipluginComputed.ets'
import { run_computed_params } from 'stateManagement/utest/uiPlugin/uipluginComputedParams.ets'
import { run_monitor } from 'stateManagement/utest/uiPlugin/uiplugin_monitor'
import { run_monitor_chained } from 'stateManagement/utest/uiPlugin/uiplugin_monitor_chained'
import { run_monitor_array } from 'stateManagement/utest/uiPlugin/uiplugin_monitor_array'
import { run_monitor_object } from 'stateManagement/utest/uiPlugin/uiplugin_monitor_object'
import { run_wrappedarray_v1state_to_v2param } from 'stateManagement/utest/uiPlugin/v1Tov2/uipluginArrayStateToParam.ets'
import { run_wrappedarray_v2local_to_v1prop } from 'stateManagement/utest/uiPlugin/v2Tov1/uipluginArrayLocalToProp.ets'
import { run_custom_arrays } from 'stateManagement/utest/uiPlugin/uiplugin_custom_arrays'
import { run_makeobserved } from 'stateManagement/utest/uiPlugin/uipluginUiUtils'
import { run_storage1 } from 'stateManagement/utest/src/test_storage1.ets'
import { run_storage2 } from 'stateManagement/utest/src/test_storage2.ets'
import { run_persiststorage } from 'stateManagement/utest/src/test_persistStorage.ets'
import { run_storagelink1 } from 'stateManagement/utest/src/test_storageLink1.ets'
import { run_storagelink2 } from 'stateManagement/utest/src/test_storageLink2.ets'
import { run_prop } from 'stateManagement/utest/uiPlugin/uipluginPropRef.ets'
import { run_prop_special } from 'stateManagement/utest/uiPlugin/uipluginPropRef_special_cases.ets'
import { run_storagePropRef } from 'stateManagement/utest/uiPlugin/uipluginStoragePropRef.ets'
import { run_app_storage_v2 } from 'stateManagement/utest/uiPlugin/uipluginAppStorageV2.ets'
import { run_persistent_storage_v2 } from 'stateManagement/utest/uiPlugin/uipluginPersistentStorageV2.ets'

type TestCase = () => boolean;

const tests: TestCase[] = [
  // @Observed
  run_observed_object3,
  run_observed_object4,
  run_observed_object5,

  // observation interface type
  run_observed_interface1,

  // observation of built in types
  run_wrappedarray_v1state_to_v2param,
  run_wrappedarray_v2local_to_v1prop,
  run_custom_arrays,

  // V1 decorators
  run_state,
  run_stateNumber,
  run_link1,
  run_link2,
  run_link3,
  run_prop,
  run_prop_special,

  run_consume,
  run_consumetypes,
  run_stateNumber,

  // V1 storage
  // run_persiststorage, run_storage1 depend on a clean storage
  run_persiststorage,

  run_storage1,

  // WARN: run_storage2 leaves an unclean AppStorage
  // because AppStorage.delete can only be done after GC has eaten then
  // @StorageLink objects and their references to storage
  run_storage2,
  run_storagelink1,
  run_storagelink2,

  run_storagePropRef,

  // V2
  run_local,
  run_param,   
  run_param_once,
  run_consumer,

  // @Monitor
  run_monitor,
  run_monitor_chained,
  run_monitor_array,
  run_monitor_object,

  // @Computed
  run_computed,
  run_computed_params,

  // UIUtils
  run_makeobserved,

  // StorageV2
  run_app_storage_v2,
  run_persistent_storage_v2,
]

export function runTests(): void {

  stateMgmtConsole.log("Creating special FactoryInternal instance for testing ...")


  StateMgmtFactory = new __StateMgmtFactoryImpl()
  FactoryInternal = new TestFactory();
  Observe = ObserveSingleton.instance;

  let passed = 0
  let totalRuns = 0
  let failed = 0
  const results: Array<string> = new Array<string>();
  const startTime = Date.now();

  // Changed false by default. 
  const stopAllOnErrorToDebugAnIssue: boolean = false;
  for (const test of tests) {
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
        console.log("Stopping all tests on error");
        break;
      }
    }
  }

  const endTime = Date.now();
  const durationMs = endTime - startTime;
  console.log("\x1b[34m\n\nTest Results:\x1b[0m\n");

  for (const line of results) {
    console.log('  ' + line)
  }

  console.log(`\nSummary: \x1b[32m${passed}\x1b[0m passed. \x1b[31m${failed}\x1b[0m failed. Total test assertions: ${totalRuns}. Total time: ${durationMs} ms\n\n `)
}
