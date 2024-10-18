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
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function accessibilityDescriptionTest() {
  /*
   * accessibilityLevel 通用属性
   * 找到画面id为 datePickerAccessibilityDescription1 的 DatePicker 组件
   * 找到画面文本为 DatePickerAccessibilityDescription1 的 Button 组件
   * 获取 datePicker1 的属性与期望值 '' 比对
   * 点击 button1 变更 datePicker1 的属性
   * 获取 datePicker1 的属性与期望值 "accessibilityDescription" 比对
   * */
  defineTest('accessibilityDescriptionTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('accessibilityDescriptionTestDemo running')
    let driver: Tester = Tester.create()
    let datePicker1: Component =
      await driver.findComponent(Matcher.create().id('datePickerAccessibilityDescription1').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('DatePickerAccessibilityDescription1').enabled(true))
    let accessibilityDescription1: string = await datePicker1.getInspectorInfo()
    assertFalse(JSON.parse(accessibilityDescription1).$attrs.accessibilityDescription == undefined)
    assertEqual(JSON.parse(accessibilityDescription1).$attrs.accessibilityDescription, '')
    await button1.tap()
    let accessibilityDescription2: string = await datePicker1.getInspectorInfo()
    assertEqual(JSON.parse(accessibilityDescription2).$attrs.accessibilityDescription, "accessibilityDescription")
  }, 0)
}