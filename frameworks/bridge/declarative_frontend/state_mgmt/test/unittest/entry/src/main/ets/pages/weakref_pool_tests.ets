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

import { TestRunner } from '../../lib/testRunner'
import { PageController } from '../../lib/pageController'
import { WeakRefPoolTests } from '../../common_tests/weakRefPoolTests'
import router from '@system.router'

@Entry
@ComponentV2
struct Parent {
  @Local finalResult: string = 'Pending';

  aboutToAppear() {
    setTimeout(() => {
      TestRunner.bind(this)(new WeakRefPoolTests('weakref_pool'));
      router.back();
      PageController.notifyPageFinished();
    }, 100)
  }

  build() {
    Column({ space: 10 }) {
      Text(`V2 Testing. Status: ${this.finalResult}`).fontSize(30)
    }
  }
}
