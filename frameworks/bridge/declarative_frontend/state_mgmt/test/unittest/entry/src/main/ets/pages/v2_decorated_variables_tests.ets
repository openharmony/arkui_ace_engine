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
 * V2 Decorated Variables Tests Entry Point
 *
 * This file serves as the entry point for running newly created unit tests:
 * - DecoratedVariablesTestsV2 (tests for v2_decorated_variables.ts)
 *
 * To run these tests:
 * 1. Build unittest target
 * 2. Run test executable
 * 3. Tests will execute automatically when this page is loaded
 */

import { DecoratedVariablesTestsV2 } from '../../v2_tests/decoratedVariablesTestsV2'
import { PageController } from '../../lib/pageController'
import { TestRunner } from '../../lib/testRunner'

import router from '@system.router'

@Entry
@ComponentV2
struct DecoratedVariablesTestsPage {
  // This is used in tests. Do not remove.
  // Add more UI elements if your test needs
  @Local finalResult: string = "Pending"

  aboutToAppear() {
    setTimeout(() => {
      console.log('==================================================');
      console.log('Starting V2 Decorated Variables Tests');
      console.log('==================================================');

      // Run DecoratedVariablesTestsV2
      // Tests: v2_decorated_variables.ts (VariableUtilV2, ProviderConsumerUtilV2)
      TestRunner.bind(this)(new DecoratedVariablesTestsV2('V2_decorated_variables'));

      // Navigate back
      router.back();

      // Notify test completion
      PageController.notifyPageFinished();

      console.log('==================================================');
      console.log('V2 Decorated Variables Tests Completed');
      console.log('==================================================');
    }, 100)
  }

  build() {
    Column({ space: 10 }) {
      Text('V2 Decorated Variables Tests').fontSize(30).fontWeight(FontWeight.Bold)
      Text(`Status: ${this.finalResult}`).fontSize(20).margin({ top: 20 })

      Text('Tests included:').fontSize(16).margin({ top: 30 })
      Text('1. DecoratedVariablesTestsV2').fontSize(14).margin({ top: 10 })
      Text('   - VariableUtilV2 (@Param decorator)').fontSize(12)
      Text('   - ProviderConsumerUtilV2 (@Provider/@Consumer)').fontSize(12)
      Text('   - Provider/Consumer connection').fontSize(12)
      Text('   - Lifecycle tests').fontSize(12)

      Text('See console for detailed results').fontSize(14).margin({ top: 40 })
      Text('Tests will start automatically...').fontSize(14)
    }
  }
}
