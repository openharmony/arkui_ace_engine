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

export default async function timePickerDialogSelectedTextStyleTest() {
  /*
   * TimePickerDialog.show 的 selectedTextStyle 属性
   * 获取文本为 TimePickerDialogSelectedTextStyle
   * TimePickerDialog1 TimePickerDialog2 TimePickerDialog3 的Button组件
   * 点击 TimePickerDialogSelectedTextStyle 打开弹窗
   * 获取 scrollable 可滑动的组件 命名为 timePickerDialog1 并获取 timePickerDialog1 的值
   * selectedTextStyle.color 与期望值 $r('app.color.TimePickerDialog') 比对
   * selectedTextStyle.size 与期望值 $r('app.string.timePickerDialog_value_one') 比对
   * selectedTextStyle.weight 与期望值 '13vp' 比对
   * 点击组件外部回到主页
   * 点击 TimePickerDialog1 切换属性，点击 TimePickerDialogSelectedTextStyle 打开弹窗
   * 获取 scrollable 可滑动的组件 命名为 timePickerDialog2 并获取 timePickerDialog2 的值
   * selectedTextStyle.color 与期望值 'rgba(255, 183, 0, 1.00)' 比对
   * selectedTextStyle.size 与期望值 '13vp' 比对
   * selectedTextStyle.weight 与期望值 13 比对
   * 点击组件外部回到主页
   * 点击 TimePickerDialog2 切换属性，点击 TimePickerDialogSelectedTextStyle 打开弹窗
   * selectedTextStyle.color 与期望值 0xC0FF3E 比对
   * selectedTextStyle.size 与期望值 13 比对
   * selectedTextStyle.weight 与期望值 FontWeight.Lighter 比对
   * 点击组件外部回到主页
   * 点击 TimePickerDialog3 切换属性，点击 TimePickerDialogSelectedTextStyle 打开弹窗
   * selectedTextStyle.color 与期望值 Color.Red 比对
   * selectedTextStyle.weight 与期望值 FontWeight.Normal 比对
   * 点击组件外部回到主页
   * 点击 TimePickerDialogSelectedTextStyle 打开弹窗
   * selectedTextStyle.weight 与期望值 FontWeight.Regular 比对
   * 点击组件外部回到主页
   * 点击 TimePickerDialogSelectedTextStyle 打开弹窗
   * 以此类推直至将FontWeight的 { FontWeight.Medium  FontWeight.Bold  FontWeight.Bolder } 测完
   * */

  defineTest('timePickerDialogSelectedTextStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('timePickerDialogSelectedTextStyleTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('TimePickerDialogSelectedTextStyle').enabled(true))
    let button5: Component =
      await driver.findComponent(Matcher.create().text('ClickToggleWeight').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TimePickerDialog1').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('TimePickerDialog2').enabled(true))
    let button4: Component = await driver.findComponent(Matcher.create().text('TimePickerDialog3').enabled(true))

    await button1.tap()
    let timePickerDialog1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let selectedTextStyle1: string = await timePickerDialog1.getInspectorInfo()
    assertFalse(JSON.parse(selectedTextStyle1).$attrs.selectedTextStyle == undefined)
    assertEqual(JSON.parse(selectedTextStyle1)
      .$attrs
      .selectedTextStyle
      .color, $r('app.color.time_picker_dialog'))
    assertEqual(JSON.parse(selectedTextStyle1)
      .$attrs
      .selectedTextStyle
      .size, $r('app.string.timePickerDialog_value_one'))
    assertEqual(JSON.parse(selectedTextStyle1)
      .$attrs
      .selectedTextStyle
      .weight, '13vp')
    await driver.tap(1, 1)

    await button5.tap()
    await button2.tap()
    await button1.tap()
    let timePickerDialog2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let selectedTextStyle2: string = await timePickerDialog2.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle2)
      .$attrs
      .selectedTextStyle
      .color, 'rgba(255, 183, 0, 1.00)')
    assertEqual(JSON.parse(selectedTextStyle2)
      .$attrs
      .selectedTextStyle
      .size, '13vp')
    assertEqual(JSON.parse(selectedTextStyle2)
      .$attrs
      .selectedTextStyle
      .weight, 13)
    await driver.tap(1, 1)

    await button5.tap()
    await button3.tap()
    await button1.tap()
    let timePickerDialog3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let selectedTextStyle3: string = await timePickerDialog3.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle3)
      .$attrs
      .selectedTextStyle
      .color, 0xC0FF3E)
    assertEqual(JSON.parse(selectedTextStyle2)
      .$attrs
      .selectedTextStyle
      .size, 13)
    assertEqual(JSON.parse(selectedTextStyle3)
      .$attrs
      .selectedTextStyle
      .weight, FontWeight.Lighter)
    await driver.tap(1, 1)

    await button5.tap()
    await button4.tap()
    await button1.tap()
    let timePickerDialog4: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let selectedTextStyle4: string = await timePickerDialog4.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle3)
      .$attrs
      .selectedTextStyle
      .color, Color.Red)
    assertEqual(JSON.parse(selectedTextStyle4)
      .$attrs
      .selectedTextStyle
      .weight, FontWeight.Normal)
    await driver.tap(1, 1)

    await button1.tap()
    let timePickerDialog5: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let selectedTextStyle5: string = await timePickerDialog5.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle5)
      .$attrs
      .selectedTextStyle
      .weight, FontWeight.Regular)
    await driver.tap(1, 1)

    await button5.tap()
    await button1.tap()
    let timePickerDialog6: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let selectedTextStyle6: string = await timePickerDialog6.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle6)
      .$attrs
      .selectedTextStyle
      .weight, FontWeight.Medium)
    await driver.tap(1, 1)

    await button5.tap()
    await button1.tap()
    let timePickerDialog7: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let selectedTextStyle7: string = await timePickerDialog7.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle7)
      .$attrs
      .selectedTextStyle
      .weight, FontWeight.Bold)
    await driver.tap(1, 1)

    await button5.tap()
    await button1.tap()
    let timePickerDialog8: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let selectedTextStyle8: string = await timePickerDialog8.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle8)
      .$attrs
      .selectedTextStyle
      .weight, FontWeight.Bolder)
  }, 0)
}