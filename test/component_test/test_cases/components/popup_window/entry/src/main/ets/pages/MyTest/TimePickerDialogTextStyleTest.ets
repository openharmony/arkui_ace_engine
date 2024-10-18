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

export default async function timePickerDialogTextStyleTest() {
  /*
   * TimePickerDialog.show 的 textStyle 属性
   * 获取文本为 TimePickerDialogTextStyle
   * TimePickerDialog1 TimePickerDialog2 TimePickerDialog3 的Button组件
   * 点击 TimePickerDialogTextStyle 打开弹窗
   * 获取 scrollable 可滑动的组件 命名为 timePickerDialog1 并获取 timePickerDialog1 的值
   * textStyle.color 与期望值 $r('app.color.TimePickerDialog') 比对
   * textStyle.size 与期望值 $r('app.string.timePickerDialog_value_one') 比对
   * textStyle.weight 与期望值 '13vp' 比对
   * 点击组件外部回到主页
   * 点击 TimePickerDialog1 切换属性，点击 TimePickerDialogTextStyle 打开弹窗
   * 获取 scrollable 可滑动的组件 命名为 timePickerDialog2 并获取 timePickerDialog2 的值
   * textStyle.color 与期望值 'rgba(255, 183, 0, 1.00)' 比对
   * textStyle.size 与期望值 '13vp' 比对
   * textStyle.weight 与期望值 13 比对
   * 点击组件外部回到主页
   * 点击 TimePickerDialog2 切换属性，点击 TimePickerDialogTextStyle 打开弹窗
   * textStyle.color 与期望值 0xC0FF3E 比对
   * textStyle.size 与期望值 13 比对
   * textStyle.weight 与期望值 FontWeight.Lighter 比对
   * 点击组件外部回到主页
   * 点击 TimePickerDialog3 切换属性，点击 TimePickerDialogTextStyle 打开弹窗
   * textStyle.color 与期望值 Color.Red 比对
   * textStyle.weight 与期望值 FontWeight.Normal 比对
   * 点击组件外部回到主页
   * 点击 TimePickerDialogTextStyle 打开弹窗
   * textStyle.weight 与期望值 FontWeight.Regular 比对
   * 点击组件外部回到主页
   * 点击 TimePickerDialogTextStyle 打开弹窗
   * 以此类推直至将FontWeight的 { FontWeight.Medium  FontWeight.Bold  FontWeight.Bolder } 测完
   */
  defineTest('timePickerDialogTextStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('timePickerDialogTextStyleTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('TimePickerDialogTextStyle').enabled(true))
    let button5: Component =
      await driver.findComponent(Matcher.create().text('ClickToggleWeight').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TimePickerDialog1').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('TimePickerDialog2').enabled(true))
    let button4: Component = await driver.findComponent(Matcher.create().text('TimePickerDialog3').enabled(true))

    await button1.tap()
    let timePickerDialog1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let textStyle1: string = await timePickerDialog1.getInspectorInfo()
    assertFalse(JSON.parse(textStyle1).$attrs.textStyle == undefined)
    assertEqual(JSON.parse(textStyle1)
      .$attrs
      .textStyle
      .color, $r('app.color.time_picker_dialog'))
    assertEqual(JSON.parse(textStyle1)
      .$attrs
      .textStyle
      .size, $r('app.string.timePickerDialog_value_one'))
    assertEqual(JSON.parse(textStyle1)
      .$attrs
      .textStyle
      .weight, '13vp')
    await driver.tap(1, 1)

    await button5.tap()
    await button2.tap()
    await button1.tap()
    let timePickerDialog2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let textStyle2: string = await timePickerDialog2.getInspectorInfo()
    assertEqual(JSON.parse(textStyle2)
      .$attrs
      .textStyle
      .color, 'rgba(255, 183, 0, 1.00)')
    assertEqual(JSON.parse(textStyle2)
      .$attrs
      .textStyle
      .size, '13vp')
    assertEqual(JSON.parse(textStyle2)
      .$attrs
      .textStyle
      .weight, 13)
    await driver.tap(1, 1)

    await button5.tap()
    await button3.tap()
    await button1.tap()
    let timePickerDialog3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let textStyle3: string = await timePickerDialog3.getInspectorInfo()
    assertEqual(JSON.parse(textStyle3)
      .$attrs
      .textStyle
      .color, 0xC0FF3E)
    assertEqual(JSON.parse(textStyle3)
      .$attrs
      .textStyle
      .size, 13)
    assertEqual(JSON.parse(textStyle3)
      .$attrs
      .textStyle
      .weight, FontWeight.Lighter)
    await driver.tap(1, 1)

    await button5.tap()
    await button4.tap()
    await button1.tap()
    let timePickerDialog4: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let textStyle4: string = await timePickerDialog4.getInspectorInfo()
    assertEqual(JSON.parse(textStyle4)
      .$attrs
      .textStyle
      .color, Color.Red)
    assertEqual(JSON.parse(textStyle4)
      .$attrs
      .textStyle
      .weight, FontWeight.Normal)
    await driver.tap(1, 1)

    await button5.tap()
    await button1.tap()
    let timePickerDialog5: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let textStyle5: string = await timePickerDialog5.getInspectorInfo()
    assertEqual(JSON.parse(textStyle5)
      .$attrs
      .textStyle
      .weight, FontWeight.Regular)
    await driver.tap(1, 1)

    await button5.tap()
    await button1.tap()
    let timePickerDialog6: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let textStyle6: string = await timePickerDialog6.getInspectorInfo()
    assertEqual(JSON.parse(textStyle6)
      .$attrs
      .textStyle
      .weight, FontWeight.Medium)
    await driver.tap(1, 1)

    await button5.tap()
    await button1.tap()
    let timePickerDialog7: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let textStyle7: string = await timePickerDialog7.getInspectorInfo()
    assertEqual(JSON.parse(textStyle7)
      .$attrs
      .textStyle
      .weight, FontWeight.Bold)
    await driver.tap(1, 1)

    await button5.tap()
    await button1.tap()
    let timePickerDialog8: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let textStyle8: string = await timePickerDialog8.getInspectorInfo()
    assertEqual(JSON.parse(textStyle8)
      .$attrs
      .textStyle
      .weight, FontWeight.Bolder)
  }, 0)
}