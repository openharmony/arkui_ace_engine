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
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function accessibilityGroupTest() {
  /*
   * accessibilityLevel 通用属性
   * 找到画面id为 datePickerAccessibilityGroup1 的 DatePicker 组件
   * 找到画面文本为 DatePickerAccessibilityGroup1 的 Button 组件
   * 获取 datePicker1 的属性与期望值 true 比对
   * 点击 button1 变更 datePicker1 的属性
   * 获取 datePicker1 的属性与期望值 false 比对
   * */
  defineTest('accessibilityGroupTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('accessibilityGroupTestDemo running')
    let driver: Tester = Tester.create()
    let datePicker1: Component =
      await driver.findComponent(Matcher.create().id('datePickerAccessibilityGroup1').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('DatePickerAccessibilityGroup1').enabled(true))
    let accessibilityGroup1: string = await datePicker1.getInspectorInfo()
    assertFalse(JSON.parse(accessibilityGroup1).$attrs.accessibilityGroup == undefined)
    assertTrue(JSON.parse(accessibilityGroup1).$attrs.accessibilityGroup)

    await button1.tap()
    let accessibilityGroup2: string = await datePicker1.getInspectorInfo()
    assertFalse(JSON.parse(accessibilityGroup2).$attrs.accessibilityGroup)
  }, 0)
}