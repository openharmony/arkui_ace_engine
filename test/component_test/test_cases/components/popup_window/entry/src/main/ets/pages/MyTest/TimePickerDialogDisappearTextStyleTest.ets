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

export default async function timePickerDialogDisappearTextStyleTest() {
  /*
   * TimePickerDialog.show 的 textStyle 属性
   * 获取文本为 TimePickerDialogBackgroundColor
   * TimePickerDialog1 TimePickerDialog2 TimePickerDialog3 的Button组件
   * 点击 TimePickerDialogBackgroundColor 打开弹窗
   * 获取 scrollable 可滑动的组件 命名为 timePickerDialog1 并获取 timePickerDialog1 的值
   * disappearTextStyle.color 与期望值 $r('app.color.TimePickerDialog') 比对
   * disappearTextStyle.size 与期望值 $r('app.string.timePickerDialog_value_one') 比对
   * disappearTextStyle.weight 与期望值 '13px' 比对
   * 点击组件外部回到主页
   * 点击 TimePickerDialog1 切换属性，点击 TimePickerDialogBackgroundColor 打开弹窗
   * 获取 scrollable 可滑动的组件 命名为 timePickerDialog2 并获取 timePickerDialog2 的值
   * disappearTextStyle.color 与期望值 'rgba(255, 183, 0, 1.00)' 比对
   * disappearTextStyle.size 与期望值 '10px' 比对
   * disappearTextStyle.weight 与期望值 13 比对
   * 点击组件外部回到主页
   * 点击 TimePickerDialog2 切换属性，点击 TimePickerDialogBackgroundColor 打开弹窗
   * disappearTextStyle.color 与期望值 0xC0FF3E 比对
   * disappearTextStyle.size 与期望值 13 比对
   * disappearTextStyle.weight 与期望值 FontWeight.Lighter 比对
   * 点击组件外部回到主页
   * 点击 TimePickerDialog3 切换属性，点击 TimePickerDialogBackgroundColor 打开弹窗
   * disappearTextStyle.color 与期望值 Color.Gray 比对
   * disappearTextStyle.weight 与期望值 FontWeight.Normal 比对
   * 点击组件外部回到主页
   * 点击 TimePickerDialogBackgroundColor 打开弹窗
   * disappearTextStyle.weight 与期望值 FontWeight.Regular 比对
   * 点击组件外部回到主页
   * 点击 TimePickerDialogBackgroundColor 打开弹窗
   * 以此类推直至将FontWeight的 { FontWeight.Medium  FontWeight.Bold  FontWeight.Bolder } 测完
   */
  defineTest('timePickerDialogDisappearTextStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('timePickerDialogDisappearTextStyleTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('TimePickerDialogDisappearTextStyle').enabled(true))
    let button5: Component =
      await driver.findComponent(Matcher.create().text('ClickToggleWeight').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TimePickerDialog1').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('TimePickerDialog2').enabled(true))
    let button4: Component = await driver.findComponent(Matcher.create().text('TimePickerDialog3').enabled(true))
    await button1.tap()
    let timePickerDialog1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let disappearTextStyle1: string = await timePickerDialog1.getInspectorInfo()
    assertFalse(JSON.parse(disappearTextStyle1).$attrs.disappearTextStyle == undefined)
    assertEqual(JSON.parse(disappearTextStyle1)
      .$attrs
      .disappearTextStyle
      .color, $r('app.color.time_picker_dialog'))
    assertEqual(JSON.parse(disappearTextStyle1)
      .$attrs
      .disappearTextStyle
      .font
      .size, $r('app.string.timePickerDialog_value_one'))
    assertEqual(JSON.parse(disappearTextStyle1)
      .$attrs
      .disappearTextStyle
      .font
      .weight, '13px')
    await driver.tap(1, 1)

    await button5.tap()
    await button2.tap()
    await button1.tap()
    let timePickerDialog2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let disappearTextStyle2: string = await timePickerDialog2.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle2)
      .$attrs
      .disappearTextStyle
      .color, 'rgba(255, 183, 0, 1.00)')
    assertEqual(JSON.parse(disappearTextStyle2)
      .$attrs
      .disappearTextStyle
      .font
      .size, '10px')
    assertEqual(JSON.parse(disappearTextStyle2)
      .$attrs
      .disappearTextStyle
      .font
      .weight, 13)
    await driver.tap(1, 1)

    await button5.tap()
    await button3.tap()
    await button1.tap()
    let timePickerDialog3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let disappearTextStyle3: string = await timePickerDialog3.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle3)
      .$attrs
      .disappearTextStyle
      .color, 0xC0FF3E)
    assertEqual(JSON.parse(disappearTextStyle3)
      .$attrs
      .disappearTextStyle
      .font
      .size, 10)
    assertEqual(JSON.parse(disappearTextStyle3)
      .$attrs
      .disappearTextStyle
      .font
      .weight, FontWeight.Lighter)
    await driver.tap(1, 1)

    await button5.tap()
    await button4.tap()
    await button1.tap()
    let timePickerDialog4: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let disappearTextStyle4: string = await timePickerDialog4.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle4)
      .$attrs
      .disappearTextStyle
      .font
      .weight, FontWeight.Normal)
    assertEqual(JSON.parse(disappearTextStyle4)
      .$attrs
      .disappearTextStyle
      .color, Color.Gray)
    await driver.tap(1, 1)

    await button1.tap()
    let timePickerDialog5: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let disappearTextStyle5: string = await timePickerDialog5.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle5)
      .$attrs
      .disappearTextStyle
      .font
      .weight, FontWeight.Regular)
    await driver.tap(1, 1)

    await button5.tap()
    await button1.tap()
    let timePickerDialog6: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let disappearTextStyle6: string = await timePickerDialog6.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle6)
      .$attrs
      .disappearTextStyle
      .font
      .weight, FontWeight.Medium)
    await driver.tap(1, 1)

    await button5.tap()
    await button1.tap()
    let timePickerDialog7: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let disappearTextStyle7: string = await timePickerDialog7.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle7)
      .$attrs
      .disappearTextStyle
      .font
      .weight, FontWeight.Bold)
    await driver.tap(1, 1)

    await button5.tap()
    await button1.tap()
    let timePickerDialog8: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let disappearTextStyle8: string = await timePickerDialog8.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle8)
      .$attrs
      .disappearTextStyle
      .font
      .weight, FontWeight.Bolder)
    await driver.tap(1, 1)
  }, 0)
}