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

import { ResetStateVarsOnReuseTestsV2 } from '../../v2_tests/resetStateVarsOnReuseTestsV2'
import { PageController } from '../../lib/pageController'
import { TestRunner } from '../../lib/testRunner'

import router from '@system.router'

@Entry
@ComponentV2
struct Parent {

  // This is used in tests. Do not remove.
  // Add more UI elements if your test needs
  @Local finalResult: string = 'Pending';
  @Provider('bbb') provider0: number = 100;
  @Provider() consumerWithoutAliasWithProvider: number = 101;


  build() {
    Column({ space: 10 }) {
      Text(`V2 testing. Status: ${this.finalResult}`).fontSize(30)
      ReusableV2Child({
        paramOut: 9,
        paramOnceOut: 9
      })
    }
  }
}

@ReusableV2
@ComponentV2
struct ReusableV2Child {
  @Consumer('aaa') consumerWithAliasWithoutProvider: number = 1;
  @Consumer() consumerWithoutAliasWithoutProvider: number = 2;
  @Consumer('bbb') consumerWithAliasWithProvider: number = 3;
  @Consumer() consumerWithoutAliasWithProvider: number = 4;

  @Require @Param paramOut: number;
  @Param paramIn: number = 10;
  @Require @Param @Once paramOnceOut: number;
  @Param @Once paramOnceIn: number = 11;

  @Local local: number = 111;
  @Computed
  get computed(): number {
    return this.local;
  }

  @Local val: number = 20;
  @Local before: number = 0;
  @Local after: number = 0;
  @Monitor('val')
  monitor(m: IMonitor) {
    this.before = m.value()!.before as number;
    this.after = m.value()!.now as number;
  }
  aboutToAppear() {
    setTimeout(() => {
        TestRunner.bind(this)(new ResetStateVarsOnReuseTestsV2('resetVarsOnReuse'));
        router.back();
        PageController.notifyPageFinished();
    }, 100);
  }
  build() {
  }
}