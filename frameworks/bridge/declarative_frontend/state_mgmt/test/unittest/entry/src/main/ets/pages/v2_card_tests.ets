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

import { CardTestsV2 } from '../../v2_tests/cardTestsV2'
import { PageController } from '../../lib/pageController'
import { TestRunner } from '../../lib/testRunner'

import router from '@system.router'

@Entry
@ComponentV2
struct Parent {

  // This is used in tests. Do not remove.
  // Add more UI elements if your test needs
  @Local finalResult: string = 'Pending'

  @Local local: number = 9;
  @Param param: number = 10;
  @Param @Once paramOnce: number = 11;
  @Event event: ()=>void = () => {};
  @Provider('aaa') provider: number = 12;
  @Provider() providerNoAlias: number = 13;
  @Consumer('bbb') consumer: number = 14;
  @Consumer() consumerNoAlias: number = 15;
  regular: number = 16;

  @Computed
  get computed(): number {
    return 17;
  }
  
  @Monitor('local')
  monitor(m: IMonitor) {

  }

  aboutToAppear() {
    setTimeout(() => {
      TestRunner.bind(this)(new CardTestsV2('v2_card'));
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