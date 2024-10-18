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

export default async function timePickerDialogMaskRectTest() {
  /*
   * TimePickerDialog.show 的 maskRect 属性
   * 获取文本为 TimePickerDialogMaskRect TimePickerDialog1 TimePickerDialog2 的Button组件
   * 点击 TimePickerDialogMaskRect 打开弹窗
   * 获取 scrollable 可滑动的组件 命名为 timePickerDialog1 并获取 timePickerDialog1 的值
   * maskRect.x 与期望值 0 比对
   * maskRect.y 与期望值 0 比对
   * maskRect.width 与期望值 '100%' 比对
   * maskRect.height 与期望值 '100%' 比对
   * 点击组件外部回到主页
   * 点击 TimePickerDialog1 切换属性，点击 TimePickerDialogMaskRect 打开弹窗
   * 获取 scrollable 可滑动的组件 命名为 timePickerDialog2 并获取 timePickerDialog2 的值
   * maskRect.x 与期望值 '10px' 比对
   * maskRect.y 与期望值 '10px' 比对
   * maskRect.width 与期望值 8000 比对
   * maskRect.height 与期望值 8000 比对
   * 点击组件外部回到主页
   * 点击 TimePickerDialog2 切换属性，点击 TimePickerDialogMaskRect 打开弹窗
   * 获取 scrollable 可滑动的组件 命名为 timePickerDialog3 并获取 timePickerDialog3 的值
   * maskRect.x 与期望值 $r('app.string.timePickerDialog_value_one') 比对
   * maskRect.y 与期望值 $r('app.string.timePickerDialog_value_one') 比对
   * 点击组件外部回到主页
   */
  defineTest('timePickerDialogBackgroundColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('timePickerDialogBackgroundColorTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component = await driver.findComponent(Matcher.create().text('TimePickerDialogMaskRect').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TimePickerDialog1').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('TimePickerDialog2').enabled(true))
    await button1.tap()
    let timePickerDialog1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let maskRect1: string = await timePickerDialog1.getInspectorInfo()
    assertFalse(JSON.parse(maskRect1).$attrs.maskRect == undefined)
    assertEqual(JSON.parse(maskRect1)
      .$attrs
      .maskRect
      .x, 0)
    assertEqual(JSON.parse(maskRect1)
      .$attrs
      .maskRect
      .y, 0)
    assertEqual(JSON.parse(maskRect1)
      .$attrs
      .maskRect
      .width, '100%')
    assertEqual(JSON.parse(maskRect1)
      .$attrs
      .maskRect
      .height, '100%')
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let timePickerDialog2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let maskRect2: string = await timePickerDialog2.getInspectorInfo()
    assertEqual(JSON.parse(maskRect2)
      .$attrs
      .maskRect
      .x, '10px')
    assertEqual(JSON.parse(maskRect2)
      .$attrs
      .maskRect
      .y, '10px')
    assertEqual(JSON.parse(maskRect2)
      .$attrs
      .maskRect
      .width, 8000)
    assertEqual(JSON.parse(maskRect2)
      .$attrs
      .maskRect
      .height, 8000)
    await driver.tap(1, 1)

    await button3.tap()
    await button1.tap()
    let timePickerDialog3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let maskRect3: string = await timePickerDialog3.getInspectorInfo()
    assertEqual(JSON.parse(maskRect3)
      .$attrs
      .maskRect
      .x, $r('app.string.timePickerDialog_value_one'))
    assertEqual(JSON.parse(maskRect3)
      .$attrs
      .maskRect
      .y, $r('app.string.timePickerDialog_value_one'))
  }, 0)
}