/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import {
  assertEqual,
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function stepperItemNextLabelTest() {
  /*
 * StepperItem组件 NextLabel属性
 * 找到画面id为stepperItemNextLabel1的StepperItem组件
 * 获取stepperItem1的nextLabel属性与期待值'Next'比对
 */
  defineTest('stepperItemNextLabelTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('stepperItemNextLabelTestDemo running')
    let driver: Tester = Tester.create()
    let stepperItem1: Component = await driver.findComponent(Matcher.create().id('stepperItemNextLabel1').enabled(true))
    let nextLabel1: string = await stepperItem1.getInspectorInfo()
    assertEqual(JSON.parse(nextLabel1).$attrs.nextLabel, 'Next')
  }, 0)
}