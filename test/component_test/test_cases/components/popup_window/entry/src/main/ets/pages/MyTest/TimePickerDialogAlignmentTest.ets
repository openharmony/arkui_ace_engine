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

export default async function timePickerDialogAlignmentTest() {
  /*
   * TimePickerDialog.show 的 alignment 属性
   * 获取文本为 TimePickerDialogOnAccept 的按钮
   * 点击打开 时间 弹窗
   * 获取 scrollable 可滑动的组件 命名为 timePickerDialog1
   * 获取 timePickerDialog1 的值与 DialogAlignment.Top 比对
   * 点击组件外部回到主页
   * 以此类推将 DialogAlignment 测完
   */
  defineTest('timePickerDialogAlignmentTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('timePickerDialogOnAcceptTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('TimePickerDialogAlignment').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ClickToggleAlignment').enabled(true))
    await button1.tap()
    let timePickerDialog1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment1: string = await timePickerDialog1.getInspectorInfo()
    assertEqual(JSON.parse(alignment1).$attrs.alignment, 'DialogAlignment.TOP')
    await driver.tap(1, 1)
    await button2.tap()
    await button1.tap()
    let timePickerDialog2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment2: string = await timePickerDialog2.getInspectorInfo()
    assertEqual(JSON.parse(alignment2).$attrs.alignment, 'DialogAlignment.CENTER')
    await driver.tap(1, 1)
    await button2.tap()
    await button1.tap()
    let timePickerDialog3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment3: string = await timePickerDialog3.getInspectorInfo()
    assertEqual(JSON.parse(alignment3).$attrs.alignment, 'DialogAlignment.BOTTOM')
    await driver.tap(1, 1)
    await button2.tap()
    await button1.tap()
    let timePickerDialog4: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment4: string = await timePickerDialog4.getInspectorInfo()
    assertEqual(JSON.parse(alignment4).$attrs.alignment, 'DialogAlignment.DEFAULT')
    await driver.tap(1, 1)
    await button2.tap()
    await button1.tap()
    let timePickerDialog5: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment5: string = await timePickerDialog5.getInspectorInfo()
    assertEqual(JSON.parse(alignment5).$attrs.alignment, 'DialogAlignment.TOP_START')
    await driver.tap(1000, 1)
    await button2.tap()
    await button1.tap()
    let timePickerDialog6: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment6: string = await timePickerDialog6.getInspectorInfo()
    assertEqual(JSON.parse(alignment6).$attrs.alignment, 'DialogAlignment.TOP_END')
    await driver.tap(1, 1)
    await button2.tap()
    await button1.tap()
    let timePickerDialog7: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment7: string = await timePickerDialog7.getInspectorInfo()
    assertEqual(JSON.parse(alignment7).$attrs.alignment, 'DialogAlignment.CENTER_START')
    await driver.tap(1, 1)
    await button2.tap()
    await button1.tap()
    let timePickerDialog8: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment8: string = await timePickerDialog8.getInspectorInfo()
    assertEqual(JSON.parse(alignment8).$attrs.alignment, 'DialogAlignment.CENTER_END')
    await driver.tap(1, 1)
    await button2.tap()
    await button1.tap()
    let timePickerDialog9: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment9: string = await timePickerDialog9.getInspectorInfo()
    assertEqual(JSON.parse(alignment9).$attrs.alignment, 'DialogAlignment.BOTTOM_START')
    await driver.tap(1, 1)
    await button2.tap()
    await button1.tap()
    let timePickerDialog10: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment10: string = await timePickerDialog10.getInspectorInfo()
    assertEqual(JSON.parse(alignment10).$attrs.alignment, 'DialogAlignment.BOTTOM_END')
    await driver.tap(1, 1)
  }, 0)
}