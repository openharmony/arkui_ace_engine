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
 * V2 Computed Tests Entry Point
 *
 * This file serves as entry point for running unit tests for v2_computed.ts:
 * - ComputedTestsV2 (tests for v2_computed.ts)
 *   Tests: ComputedV2 class, AsyncAddComputedV2 class, @Computed decorator
 *
 * To run these tests:
 * 1. Build unittest target
 * 2. Run test executable
 * 3. Tests will execute automatically when this page is loaded
 *
 * Executable name: v2_computed_tests
 */

import { ComputedTestsV2 } from '../../v2_tests/computedTestsV2'
import { PageController } from '../../lib/pageController'
import { TestRunner } from '../../lib/testRunner'

import router from '@system.router'

@Entry
@ComponentV2
struct V2ComputedTestsPage {
  // This is used in tests. Do not remove.
  // Add more UI elements if your test needs
  @Local finalResult: string = "Pending"

  aboutToAppear() {
    setTimeout(() => {
      console.log('==================================================');
      console.log('Starting V2 Computed Tests');
      console.log('==================================================');

      // Run ComputedTestsV2
      // Tests: v2_computed.ts (ComputedV2, AsyncAddComputedV2)
      TestRunner.bind(this)(new ComputedTestsV2('v2_computed'));

      // Navigate back
      router.back();

      // Notify test completion
      PageController.notifyPageFinished();

      console.log('==================================================');
      console.log('V2 Computed Tests Completed');
      console.log('==================================================');
    }, 100)
  }

  build() {
    Column({ space: 10 }) {
      Text('V2 Computed Tests').fontSize(30).fontWeight(FontWeight.Bold)
      Text(`Status: ${this.finalResult}`).fontSize(20).margin({ top: 20 })

      Text('Tests included:').fontSize(16).margin({ top: 30 })
      Text('1. ComputedV2 class').fontSize(14).margin({ top: 10 })
      Text('   - Static constants (MIN_COMPUTED_ID, COMPUTED_PREFIX, etc.)').fontSize(12)
      Text('   - Constructor (target, prop, func)').fontSize(12)
      Text('   - InitRun() - Initialize computed property').fontSize(12)
      Text('   - fireChange() - Recalculate and notify').fontSize(12)
      Text('   - Getter methods (getTarget, getProp, getComputedId)').fontSize(12)
      Text('   - Static methods (getComputedIds, clearComputedFromTarget)').fontSize(12)
      Text('   - resetComputed() - Reset computed property').fontSize(12)

      Text('2. AsyncAddComputedV2 class').fontSize(14).margin({ top: 20 })
      Text('   - addComputed() - Add computed asynchronously').fontSize(12)
      Text('   - run() - Process pending computed additions').fontSize(12)

      Text('3. @Computed decorator functionality').fontSize(14).margin({ top: 20 })
      Text('   - Computed property lifecycle').fontSize(12)
      Text('   - Dependency tracking').fontSize(12)
      Text('   - Cache management').fontSize(12)
      Text('   - Batch processing').fontSize(12)

      Text('See console for detailed results').fontSize(14).margin({ top: 40 })
      Text('Tests will start automatically...').fontSize(14)
    }
  }
}
