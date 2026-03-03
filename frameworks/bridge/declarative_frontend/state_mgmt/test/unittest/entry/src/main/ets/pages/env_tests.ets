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

import { EnvFactoryTests } from '../../env_tests/env_factory_tests'
import { IEnvBreakpointTests } from '../../env_tests/i_env_breakpointTests'
import { IEnvWindowSizeTests } from '../../env_tests/i_env_windowsizeTests'
import { IEnvWindowAvoidAreaTests } from '../../env_tests/i_env_windowavoidareaTests'
import { IEnvValueTests } from '../../env_tests/i_env_valueTests'

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
      TestRunner.bind(this)(new EnvFactoryTests('env_factory'));
      TestRunner.bind(this)(new IEnvBreakpointTests('i_env_breakpoint'));
      TestRunner.bind(this)(new IEnvWindowSizeTests('i_env_windowsize'));
      TestRunner.bind(this)(new IEnvWindowAvoidAreaTests('i_env_windowavoidarea'));
      TestRunner.bind(this)(new IEnvValueTests('i_env_value'));
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