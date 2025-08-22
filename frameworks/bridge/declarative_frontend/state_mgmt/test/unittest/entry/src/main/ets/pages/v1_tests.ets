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

import { CommonTestsV2 } from '../../v1_tests/commonTestsV1'
import { LocalStorageTest1 } from '../../v1_tests/localStorageV1'
import { TestRunner } from '../../lib/testRunner'
import { PageController } from '../../lib/pageController'
import router from '@system.router'

const storage = new LocalStorage();

@Entry(storage)
@Component
struct Parent {

  // This is used in tests. Do not remove.
  // Add more UI elements if your test needs
  @State finalResult: string = "Pending"

  aboutToAppear() {
    setTimeout(() => {
      TestRunner.bind(this)(new CommonTestsV2('V1_common'));
      TestRunner.bind(this)(new LocalStorageTest1('V1_local'));
      router.back();
      PageController.notifyPageFinished();
    }, 100)
  }

  build() {
    Column({ space: 10 }) {
      Text(`V1 Testing. Status: ${this.finalResult}`).fontSize(30)
    }
  }
}