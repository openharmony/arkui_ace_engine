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
import { ObservedObjectNameTestsV1 } from '../../v1_tests/pu_observed_object_name_tests_v1'
import router from '@system.router'

const storage = new LocalStorage();
interface MockObject1 {
  num: number;
}
interface MockObject2 {
  key: string;
  nested: MockObject1
}

@Observed
class TestObservedNameA {
  valueA: number = 1;
}

@Observed
class TestObservedNameB {
  valueB: string = 'test';
  constructor(str?: string) {
    if (str) {
      this.valueB = str;
    }
  }
}

@Observed
class TestObservedNameChild extends TestObservedNameA {
  extraProp: string = 'child';
}

@Observed
class TestObservedNameGrandChild extends TestObservedNameChild {
  grandProp: number = 0;
}

@Observed
class TestObservedNameContainer {
  nestedA: TestObservedNameA = new TestObservedNameA();
  nestedB: TestObservedNameB = new TestObservedNameB();
}

@Observed
class TestObservedNameContainerArray {
  items: TestObservedNameA[] = [new TestObservedNameA()];
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

  // ObservedObject name test properties
  @State testObservedNameA: TestObservedNameA = new TestObservedNameA();
  @State testObservedNameB: TestObservedNameB = new TestObservedNameB();
  @State testObservedNameChild: TestObservedNameChild = new TestObservedNameChild();
  @State testObservedNameGrandChild: TestObservedNameGrandChild = new TestObservedNameGrandChild();
  @State testObservedNameContainer: TestObservedNameContainer = new TestObservedNameContainer();
  @State testObservedNameContainerArr: TestObservedNameContainerArray = new TestObservedNameContainerArray();
  @State testObservedNameArray: number[] = [1, 2, 3];
  @State testObservedNameMap: Map<string, number> = new Map([['a', 1]]);
  @State testObservedNameSet: Set<string> = new Set(['x', 'y']);
  @State testObservedNameDate: Date = new Date(2025, 0, 1);
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
      TestRunner.bind(this)(new ObservedObjectNameTestsV1('V1_pu_observed_object_name'));
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
