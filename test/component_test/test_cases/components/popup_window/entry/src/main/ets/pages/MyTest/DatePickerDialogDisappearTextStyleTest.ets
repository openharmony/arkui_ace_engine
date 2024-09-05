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

export default async function datePickerDialogDisappearTextStyleTest() {
  /*
   * DatePickerDialog组件 DisappearTextStyle对象
   * 找到画面text为DatePickerDialogDisappearTextStyle1，DatePickerDialogDisappearTextStyle2的Button组件
   * 点击button1，弹出弹窗
   * 获取datePickerDialogDisappearTextStyle1的DisappearTextStyle对象与期待值{ color: 'rgb(142, 255, 101)',
            font: {size: 10, weight: 10 } }对比
   * 点击坐标(1, 1)，退出弹窗
   * 获取datePickerDialogDisappearTextStyle2的DisappearTextStyle对象与期待值{ color: 0xa52a2a,
            font: {size: $r('app.string.text_style_size'), weight: FontWeight.Bolder } }对比
   * 点击坐标(1, 1)，退出弹窗
   * 获取datePickerDialogDisappearTextStyle3的DisappearTextStyle对象与期待值{ color: Color.Blue,
            font: { weight: FontWeight.Bold } }对比
   * 点击坐标(1, 1)，退出弹窗
   * 获取datePickerDialogDisappearTextStyle4的DisappearTextStyle对象与期待值{ font: { weight: FontWeight.Medium } }对比
   * 点击坐标(1, 1)，退出弹窗
   * 获取datePickerDialogDisappearTextStyle5的DisappearTextStyle对象与期待值{ font: { weight: FontWeight.Regular } }对比
   * 点击坐标(1, 1)，退出弹窗
   * 获取datePickerDialogDisappearTextStyle6的DisappearTextStyle对象与期待值{ font: { weight: FontWeight.Normal } }对比
   * 点击坐标(1, 1)，退出弹窗
   * 获取datePickerDialogDisappearTextStyle7的DisappearTextStyle对象与期待值BlurStyle.BACKGROUND_ULTRA_THICK对比
   * 点击坐标(1, 1)，退出弹窗
   * 点击button2，变更datePickerDialogDisappearTextStyle8的DisappearTextStyle对象为{ color: $r('sys.color.ohos_fa_palette1'),
            font: '30', weight: '30' } }
   * 点击button1，弹出弹窗
   * 获取datePickerDialogDisappearTextStyle8的DisappearTextStyle对象与期待值{ color: $r('sys.color.ohos_fa_palette1'),
            font: '30', weight: '30' } }对比
   * 点击坐标(1, 1)，退出弹窗
   */

  defineTest('datePickerDialogDisappearTextStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('datePickerDialogDisappearTextStyleTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('DatePickerDialogDisappearTextStyle1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('DatePickerDialogDisappearTextStyle2').enabled(true))

    await button1.tap()
    let datePickerDialogDisappearTextStyle1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let disappearTextStyle1: string = await datePickerDialogDisappearTextStyle1.getInspectorInfo()
    assertFalse(JSON.parse(disappearTextStyle1).$attrs.disappearTextStyle == undefined)
    assertEqual(JSON.parse(disappearTextStyle1).$attrs.disappearTextStyle.color, 'rgb(142, 255, 101)')
    assertEqual(JSON.parse(disappearTextStyle1)
      .$attrs
      .disappearTextStyle
      .font
      .size, 10)
    assertEqual(JSON.parse(disappearTextStyle1)
      .$attrs
      .disappearTextStyle
      .font
      .weight, 10)
    await driver.tap(1, 1)

    let datePickerDialogDisappearTextStyle2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let disappearTextStyle2: string = await datePickerDialogDisappearTextStyle2.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle2).$attrs.disappearTextStyle.color, 0xa52a2a)
    assertEqual(JSON.parse(disappearTextStyle2)
      .$attrs
      .disappearTextStyle
      .font
      .size, $r('app.string.text_style_size'))
    assertEqual(JSON.parse(disappearTextStyle2)
      .$attrs
      .disappearTextStyle
      .font
      .weight, FontWeight.Bolder)
    await driver.tap(1, 1)

    let datePickerDialogDisappearTextStyle3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let disappearTextStyle3: string = await datePickerDialogDisappearTextStyle3.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle3)
      .$attrs
      .disappearTextStyle
      .color, Color.Blue)
    assertEqual(JSON.parse(disappearTextStyle3)
      .$attrs
      .disappearTextStyle
      .font
      .weight, FontWeight.Bold)
    await driver.tap(1, 1)

    let datePickerDialogDisappearTextStyle4: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let disappearTextStyle4: string = await datePickerDialogDisappearTextStyle4.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle4)
      .$attrs
      .disappearTextStyle
      .font
      .weight, FontWeight.Medium)
    await driver.tap(1, 1)

    let datePickerDialogDisappearTextStyle5: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let disappearTextStyle5: string = await datePickerDialogDisappearTextStyle5.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle5)
      .$attrs
      .disappearTextStyle
      .font
      .weight, FontWeight.Regular)
    await driver.tap(1, 1)

    let datePickerDialogDisappearTextStyle6: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let disappearTextStyle6: string = await datePickerDialogDisappearTextStyle6.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle6)
      .$attrs
      .disappearTextStyle
      .font
      .weight, FontWeight.Normal)
    await driver.tap(1, 1)

    let datePickerDialogDisappearTextStyle7: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let disappearTextStyle7: string = await datePickerDialogDisappearTextStyle7.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle7)
      .$attrs
      .disappearTextStyle
      .font
      .weight, FontWeight.Lighter)
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogDisappearTextStyle8: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let disappearTextStyle8: string = await datePickerDialogDisappearTextStyle8.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle8)
      .$attrs
      .disappearTextStyle
      .color, $r('sys.color.ohos_fa_palette1'))
    assertEqual(JSON.parse(disappearTextStyle8)
      .$attrs
      .disappearTextStyle
      .font
      .size, '30')
    assertEqual(JSON.parse(disappearTextStyle8)
      .$attrs
      .disappearTextStyle
      .font
      .weight, '30')
    await driver.tap(1, 1)
  }, 0)
}