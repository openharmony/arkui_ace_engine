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
import { DataCoderTestsV2 } from '../../v2_tests/dataCoderTestsV2'
import { V2EnvTests } from '../../v2_tests/envTestsV2'
import { Json2Tests } from '../../v2_tests/json2TestsV2'
import { MonitorTestsV2 } from '../../v2_tests/monitorTestsV2'
import { SyncMonitorTestsV2 } from '../../v2_tests/monitorTestsV2'
import { ObserveTestsV2 } from '../../v2_tests/observeTestsV2'
import { RecycleTestsV2 } from '../../v2_tests/recycleTestsV2'
import { PersistenceV2TestsV2 } from '../../v2_tests/persistenceV2TestsV2.ets'
import { PuLifecycleTestsV2 } from '../../v2_tests/puLifecycleTestsV2'
import { Puv2ViewBaseTestsV2 } from '../../v2_tests/puv2ViewBaseTestsV2'
import { PuUINodeRegistryProxyTestsV2 } from '../../v2_tests/puUINodeRegistryProxyTestsV2'
import { PuViewTestsV2 } from '../../v2_tests/puViewTestsV2'
import { PuRecycleManagerTestsV2 } from '../../v2_tests/puRecycleManagerTestsV2'
import { PuBuilderProxyTestsV2 } from '../../v2_tests/puBuilderProxyTestsV2'
import { PuBuilderBindingTestsV2 } from '../../v2_tests/puBuilderBindingTestsV2'
import { PageController } from '../../lib/pageController'
import { TestRunner } from '../../lib/testRunner'
import { V2ViewTests } from '../../v2_tests/v2ViewTests'
import { RecyclePoolV2Tests } from '../../v2_tests/recyclePoolV2Tests'

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
      TestRunner.bind(this)(new DataCoderTestsV2('V2_dataCoder'));
      TestRunner.bind(this)(new V2EnvTests('V2_env'));
      TestRunner.bind(this)(new Json2Tests('json2'));
      TestRunner.bind(this)(new MonitorTestsV2('V2_monitor'));
      TestRunner.bind(this)(new SyncMonitorTestsV2('V2_syncmonitor'));
      TestRunner.bind(this)(new ObserveTestsV2('V2_observe'));
      TestRunner.bind(this)(new RecycleTestsV2('V2_recycle'));
      TestRunner.bind(this)(new PersistenceV2TestsV2('V2_PersistenceV2TestsV2'));
      TestRunner.bind(this)(new PuLifecycleTestsV2('V2_puLifecycle'));
      TestRunner.bind(this)(new Puv2ViewBaseTestsV2('V2_puv2ViewBase'));
      TestRunner.bind(this)(new PuUINodeRegistryProxyTestsV2('V2_puUINodeRegistryProxy'));
      TestRunner.bind(this)(new PuViewTestsV2('V2_puView'));
      TestRunner.bind(this)(new PuRecycleManagerTestsV2('V2_puRecycleManager'));
      TestRunner.bind(this)(new PuBuilderProxyTestsV2('V2_puBuilderProxy'));
      TestRunner.bind(this)(new PuBuilderBindingTestsV2('V2_puBuilderBinding'));
      TestRunner.bind(this)(new V2ViewTests('V2_v2View'));
      TestRunner.bind(this)(new RecyclePoolV2Tests('V2_recyclePool'));
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