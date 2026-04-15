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
 * V2 Observed Proxy Tests Entry Point
 *
 * This file serves as entry point for running unit tests for v2_observed_proxy.ts:
 * - ObservedProxyTestsV2 (tests for v2_observed_proxy.ts)
 *   Tests: ObjectProxyHandler, ArrayProxyHandler, SetMapProxyHandler
 *
 * To run these tests:
 * 1. Build unittest target
 * 2. Run test executable
 * 3. Tests will execute automatically when this page is loaded
 *
 * Executable name: v2_observed_proxy_tests
 */

import { ObservedProxyTestsV2 } from '../../v2_tests/observedProxyTestsV2'
import { PageController } from '../../lib/pageController'
import { TestRunner } from '../../lib/testRunner'

import router from '@system.router'

@Entry
@ComponentV2
struct V2ObservedProxyTestsPage {
  // This is used in tests. Do not remove.
  // Add more UI elements if your test needs
  @Local finalResult: string = "Pending"

  aboutToAppear() {
    setTimeout(() => {
      console.log('==================================================');
      console.log('Starting V2 Observed Proxy Tests');
      console.log('==================================================');

      // Run ObservedProxyTestsV2
      // Tests: v2_observed_proxy.ts (ObjectProxyHandler, ArrayProxyHandler, SetMapProxyHandler)
      TestRunner.bind(this)(new ObservedProxyTestsV2('v2_observed_proxy'));

      // Navigate back
      router.back();

      // Notify test completion
      PageController.notifyPageFinished();

      console.log('==================================================');
      console.log('V2 Observed Proxy Tests Completed');
      console.log('==================================================');
    }, 100)
  }

  build() {
    Column({ space: 10 }) {
      Text('V2 Observed Proxy Tests').fontSize(30).fontWeight(FontWeight.Bold)
      Text(`Status: ${this.finalResult}`).fontSize(20).margin({ top: 20 })

      Text('Tests included:').fontSize(16).margin({ top: 30 })
      Text('1. ObjectProxyHandler').fontSize(14).margin({ top: 10 })
      Text('   - Property read/write, nested object proxy, same-value no-op').fontSize(12)
      Text('   - Date: getFullYear, setFullYear, setMonth, setDate, setTime, setHours').fontSize(12)
      Text('   - Symbol: iterator, proxyGetTarget, makeObserved').fontSize(12)
      Text('2. ArrayProxyHandler').fontSize(14).margin({ top: 20 })
      Text('   - Element read/write, length access').fontSize(12)
      Text('   - Length-changing: push, pop, shift, unshift, splice').fontSize(12)
      Text('   - Mutating: sort, reverse, fill, copyWithin').fontSize(12)
      Text('   - Iteration: forEach, map, filter, reduce, find, some, every').fontSize(12)
      Text('   - Utility: indexOf, includes, join, slice, concat').fontSize(12)
      Text('3. SetMapProxyHandler - Set').fontSize(14).margin({ top: 20 })
      Text('   - has, add, delete, clear, size, forEach, keys, values, entries').fontSize(12)
      Text('4. SetMapProxyHandler - Map').fontSize(14).margin({ top: 20 })
      Text('   - get, set, has, delete, clear, size, forEach, keys, values, entries').fontSize(12)
      Text('5. Mixed / Edge Cases').fontSize(14).margin({ top: 20 })
      Text('   - Multi-type properties, object array elements, complex map keys').fontSize(12)

      Text('See console for detailed results').fontSize(14).margin({ top: 40 })
      Text('Tests will start automatically...').fontSize(14)
    }
  }
}
