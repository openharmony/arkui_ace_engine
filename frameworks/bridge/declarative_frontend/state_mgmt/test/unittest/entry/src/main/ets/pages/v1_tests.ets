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
import { LocalStorageTestsV1 } from '../../v1_tests/localStorageTestsV1'
import { AppStorageTestsV1 } from '../../v1_tests/appStorageTestsV1'
import { PersistentStorageTestsV1 } from '../../v1_tests/persistentStorageTestsV1'
import { EnvironmentTestsV1 } from '../../v1_tests/environmentTestsV1'
import { TestRunner } from '../../lib/testRunner'
import { PageController } from '../../lib/pageController'
import { PuSyncedPropertyOneWayTests } from '../../v1_tests/pu_synced_property_one_way_tests'
import { PuSyncedPropertyTwoWayTests } from '../../v1_tests/pu_synced_property_two_way_tests'
import { ObservedPropertyAbstractPUTestsV1 } from '../../v1_tests/pu_observed_property_abstract_tests_v1'
import { PuObservedPropertyTests } from '../../v1_tests/pu_observed_property_tests_v1'
import router from '@system.router'

const storage = new LocalStorage();
interface MockObject1 {
  num: number;
}
interface MockObject2 {
  key: string;
  nested: MockObject1
}
@Entry(storage)
@Component
struct Parent {

  // This is used in tests. Do not remove.
  // Add more UI elements if your test needs
  @State finalResult: string = "Pending"
  // Basic type properties
  @State testNumberProp: number = 42;
  @State testStringProp: string = "hello";
  @State testBooleanProp: boolean = true;
  @State testObjectProp: MockObject2 = { key: "value", nested: { num: 123 } as MockObject1 } as MockObject2;
  @State testArrayProp: Array<number> = [1, 2, 3, 4, 5];
  @State testNullProp: null = null;
  @State testUndefinedProp: undefined = undefined;

  // Subscriber sync properties
  @State testSyncSourceProp: number = 100;
  @State testSyncTargetProp: number = 200;

  // Delayed notification property
  @State testDelayedProp: string = "delayed";

  // Dependency management properties
  @State testDependentProp1: number = 1;
  @State testDependentProp2: number = 2;

  // Edge case properties
  @State testZeroProp: number = 0;
  @State testEmptyStringProp: string = "";
  @State testEmptyArrayProp: Array<number> = [];
  aboutToAppear() {
    setTimeout(() => {
      TestRunner.bind(this)(new CommonTestsV2('V1_common'));
      TestRunner.bind(this)(new LocalStorageTestsV1('V1_localstorage'));
      TestRunner.bind(this)(new AppStorageTestsV1('V1_appstorage'));
      TestRunner.bind(this)(new PersistentStorageTestsV1('V1_persistentstorage'));
      TestRunner.bind(this)(new EnvironmentTestsV1('V1_environment'));
      TestRunner.bind(this)(new PuSyncedPropertyOneWayTests('V1_pu_synced_property_one_way'));
      TestRunner.bind(this)(new PuSyncedPropertyTwoWayTests('V1_pu_synced_property_two_way'));
      TestRunner.bind(this)(new ObservedPropertyAbstractPUTestsV1('V1_pu_observed_property_abstract'));
      TestRunner.bind(this)(new PuObservedPropertyTests('V1_pu_observed_property'));
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