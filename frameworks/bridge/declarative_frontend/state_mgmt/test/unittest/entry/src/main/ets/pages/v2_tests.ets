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

import { CommonTestsV2 } from '../../v2_tests/commonTestsV2'
import { MonitorTestsV2 } from '../../v2_tests/monitorTestsV2'
import { ObserveTestsV2 } from '../../v2_tests/observeTestsV2'
import { RecycleTestsV2 } from '../../v2_tests/recycleTestsV2'
import { PageController } from '../../lib/pageController'
import { TestRunner } from '../../lib/testRunner'

import router from '@system.router'

@Entry
@ComponentV2
struct Parent {

  // This is used in tests. Do not remove.
  // Add more UI elements if your test needs
  @Local finalResult: string = "Pending"

  aboutToAppear() {
    setTimeout(() => {
      TestRunner.bind(this)(new CommonTestsV2('V2_common'));
      TestRunner.bind(this)(new MonitorTestsV2('V2_monitor'));
      TestRunner.bind(this)(new ObserveTestsV2('V2_observe'));
      TestRunner.bind(this)(new RecycleTestsV2('V2_recycle'));
      router.back();
      PageController.notifyPageFinished();
    }, 100)
  }

  build() {
    Column({ space: 10 }) {
      Text(`V2 testing. Status: ${this.finalResult}`).fontSize(30)
    }
  }
}