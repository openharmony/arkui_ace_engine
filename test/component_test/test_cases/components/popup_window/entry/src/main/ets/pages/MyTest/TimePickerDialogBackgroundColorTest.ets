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

export default async function timePickerDialogBackgroundColorTest() {
  /*
   * TimePickerDialog.show 的 backgroundColor 属性
   * 获取文本为 TimePickerDialogBackgroundColor 的按钮，点击打开弹窗
   * 获取 scrollable 可滑动的组件 命名为 timePickerDialog1
   * 获取 backgroundColor1 的值与 $r('app.color.TimePickerDialog') 比对
   * 点击组件外部回到主页
   * 获取文本为 TimePickerDialogBackgroundColor 的按钮，点击打开弹窗
   * 获取 scrollable 可滑动的组件 命名为 timePickerDialog2
   * 获取 backgroundColor2 的值与 Color.Pink 比对
   * 点击组件外部回到主页
   * 获取文本为 TimePickerDialogBackgroundColor 的按钮，点击打开弹窗
   * 获取 scrollable 可滑动的组件 命名为 timePickerDialog3
   * 获取 backgroundColor3 的值与 'rgba(255, 228, 91, 1.00)' 比对
   * 点击组件外部回到主页
   * 获取文本为 TimePickerDialogBackgroundColor 的按钮，点击打开弹窗
   * 获取 scrollable 可滑动的组件 命名为 timePickerDialog4
   * 获取 backgroundColor4 的值与 0x80FFAA 比对
   * 点击组件外部回到主页
   */
  defineTest('timePickerDialogBackgroundColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('timePickerDialogBackgroundColorTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('TimePickerDialogBackgroundColor').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('ClickToggleBackgroundColor').enabled(true))
    await button1.tap()
    let timePickerDialog1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundColor1: string = await timePickerDialog1.getInspectorInfo()
    assertFalse(JSON.parse(backgroundColor1).$attrs.backgroundColor == '#33000000')
    assertEqual(JSON.parse(backgroundColor1).$attrs.backgroundColor, $r("app.color.time_picker_dialog"))
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let timePickerDialog2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundColor2: string = await timePickerDialog2.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor2).$attrs.backgroundColor, Color.Pink)
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let timePickerDialog3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundColor3: string = await timePickerDialog3.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor3).$attrs.backgroundColor, 'rgba(255, 228, 91, 1.00)')
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let timePickerDialog4: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundColor4: string = await timePickerDialog4.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor4).$attrs.backgroundColor, '0x80FFAA')
    await driver.tap(1, 1)
  }, 0)
}