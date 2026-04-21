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

/**
 * V2 Change Observation Tests Entry Point
 *
 * This file serves as entry point for running unit tests for v2_change_observation.ts:
 * - ChangeObservationTestsV2 (tests for v2_change_observation.ts)
 *   Tests: ObserveV2, StackOfRenderedComponents, dependency tracking
 *
 * To run these tests:
 * 1. Build unittest target
 * 2. Run test executable
 * 3. Tests will execute automatically when this page is loaded
 *
 * Executable name: v2_change_observation_tests
 */

import { ChangeObservationTestsV2 } from '../../v2_tests/changeObservationTestsV2'
import { PageController } from '../../lib/pageController'
import { TestRunner } from '../../lib/testRunner'

import router from '@system.router'

@Entry
@ComponentV2
struct V2ChangeObservationTestsPage {
  // This is used in tests. Do not remove.
  // Add more UI elements if your test needs
  @Local finalResult: string = "Pending"

  aboutToAppear() {
    setTimeout(() => {
      console.log('==================================================');
      console.log('Starting V2 Change Observation Tests');
      console.log('==================================================');

      // Run ChangeObservationTestsV2
      // Tests: v2_change_observation.ts (ObserveV2 class)
      TestRunner.bind(this)(new ChangeObservationTestsV2('v2_change_observation'));

      // Navigate back
      router.back();

      // Notify test completion
      PageController.notifyPageFinished();

      console.log('==================================================');
      console.log('V2 Change Observation Tests Completed');
      console.log('==================================================');
    }, 100)
  }

  build() {
    Column({ space: 10 }) {
      Text('V2 Change Observation Tests').fontSize(30).fontWeight(FontWeight.Bold)
      Text(`Status: ${this.finalResult}`).fontSize(20).margin({ top: 20 })

      Text('Tests included:').fontSize(16).margin({ top: 30 })
      Text('1. ObserveV2 static constants').fontSize(14).margin({ top: 10 })
      Text('   - V2_DECO_META, SYMBOL_REFS, OB_PREFIX, etc.').fontSize(12)
      Text('2. ObserveV2 dependency tracking').fontSize(14).margin({ top: 20 })
      Text('   - addRef, addRef4IdInternal, clearBinding').fontSize(12)
      Text('3. ObserveV2 state changes').fontSize(14).margin({ top: 20 })
      Text('   - fireChange, executeUnobserved, setUnmonitored').fontSize(12)
      Text('4. StackOfRenderedComponents').fontSize(14).margin({ top: 20 })
      Text('   - push, pop, top operations').fontSize(12)
      Text('5. Monitor/Computed/Persistence support').fontSize(14).margin({ top: 20 })
      Text('   - updateDirty2Optimized, resetMonitorValues').fontSize(12)

      Text('See console for detailed results').fontSize(14).margin({ top: 40 })
      Text('Tests will start automatically...').fontSize(14)
    }
  }
}
