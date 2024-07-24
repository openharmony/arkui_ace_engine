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

export default async function timePickerDialogOffsetTest() {
  /*
   * TimePickerDialog.show 的 offset 属性
   * 获取文本为 TimePickerDialogOffset TimePickerDialog1 TimePickerDialog2 的Button组件
   * 点击 TimePickerDialogOffsetSample 打开弹窗
   * 获取 scrollable 可滑动的组件 命名为 timePickerDialog1 并获取 timePickerDialog1 的值
   * offset.dx 与期望值 10 比对
   * offset.dy 与期望值 10 比对
   * 点击组件外部回到主页
   * 点击 TimePickerDialog1 切换属性，点击 TimePickerDialogOffset 打开弹窗
   * 获取 scrollable 可滑动的组件 命名为 timePickerDialog2 并获取 timePickerDialog2 的值
   * offset.dx 与期望值 '20px' 比对
   * offset.dy 与期望值 '20px' 比对
   * 点击组件外部回到主页
   * 点击 TimePickerDialog2 切换属性，点击 TimePickerDialogOffset 打开弹窗
   * 获取 scrollable 可滑动的组件 命名为 timePickerDialog3 并获取 timePickerDialog3 的值
   * offset.dx 与期望值 $r('app.string.timePickerDialog_value_one') 比对
   * offset.dx 与期望值 $r('app.string.timePickerDialog_value_one') 比对
   */
  defineTest('timePickerDialogOffsetTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('timePickerDialogOffsetTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component = await driver.findComponent(Matcher.create().text('TimePickerDialogOffset').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TimePickerDialog1').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('TimePickerDialog2').enabled(true))
    await button1.tap()
    let timePickerDialog1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let offset1: string = await timePickerDialog1.getInspectorInfo()
    assertEqual(JSON.parse(offset1).$attrs.offset.dX, 10)
    assertEqual(JSON.parse(offset1).$attrs.offset.dY, 10)
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let timePickerDialog2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let offset2: string = await timePickerDialog2.getInspectorInfo()
    assertEqual(JSON.parse(offset2).$attrs.offset.dX, 20)
    assertEqual(JSON.parse(offset2).$attrs.offset.dY, 20)
    await driver.tap(1, 1)

    await button3.tap()
    await button1.tap()
    let timePickerDialog3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let offset3: string = await timePickerDialog3.getInspectorInfo()
    assertEqual(JSON.parse(offset3)
      .$attrs
      .offset
      .dX
      .toString(), $r('app.string.timePickerDialog_value_one'))
    assertEqual(JSON.parse(offset3)
      .$attrs
      .offset
      .dY
      .toString(), $r('app.string.timePickerDialog_value_one'))
  }, 0)
}