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

export default async function timePickerDialogUseMilitaryTimeTest() {
  /*
   * TimePickerDialog.show 的 useMilitaryTime 属性
   * 获取文本为 TimePickerDialogUseMilitaryTime 的Button组件
   * 点击 TimePickerDialogUseMilitaryTime 打开弹窗
   * 获取 scrollable 可滑动的组件 命名为 timePickerDialog1 并获取 timePickerDialog1 的值
   * options.useMilitaryTime 与期望值 true 比对
   * 点击组件外部回到主页
   * 点击 TimePickerDialogUseMilitaryTime 打开弹窗
   * 获取 scrollable 可滑动的组件 命名为 timePickerDialog2 并获取 timePickerDialog2 的值
   * options.useMilitaryTime 与期望值 false 比对
   */
  defineTest('timePickerDialogUseMilitaryTimeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('timePickerDialogUseMilitaryTimeTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('TimePickerDialogUseMilitaryTime1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('TimePickerDialogUseMilitaryTime2').enabled(true))
    await button1.tap()
    let timePickerDialog1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let useMilitaryTime1: string = await timePickerDialog1.getInspectorInfo()
    assertFalse(JSON.parse(useMilitaryTime1).$attrs.useMilitaryTime == undefined)
    assertTrue(JSON.parse(useMilitaryTime1)
      .$attrs
      .useMilitaryTime)
    await driver.tap(1, 1)
    await button2.tap()
    let timePickerDialog2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let useMilitaryTime2: string = await timePickerDialog2.getInspectorInfo()
    assertFalse(JSON.parse(useMilitaryTime2)
      .$attrs
      .useMilitaryTime)
  }, 0)
}