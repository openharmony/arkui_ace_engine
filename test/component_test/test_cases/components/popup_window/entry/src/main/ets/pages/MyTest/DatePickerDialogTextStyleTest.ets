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

export default async function datePickerDialogTextStyleTest() {
  /*
   * DatePickerDialog组件 TextStyle对象
   * 找到画面text为DatePickerDialogTextStyle1，DatePickerDialogTextStyle2的Button组件
   * 点击button1，弹出弹窗
   * 获取datePickerDialogTextStyle1的TextStyle对象与期待值{ color: 'rgb(142, 255, 101)',
            font: {size: 10, weight: 10 } }对比
   * 点击坐标(1, 1)，退出弹窗
   * 获取datePickerDialogTextStyle2的TextStyle对象与期待值{ color: 0xa52a2a,
            font: {size: $r('app.string.text_style_size'), weight: FontWeight.Bolder } }对比
   * 点击坐标(1, 1)，退出弹窗
   * 获取datePickerDialogTextStyle3的TextStyle对象与期待值{ color: Color.Blue,
            font: { weight: FontWeight.Bold } }对比
   * 点击坐标(1, 1)，退出弹窗
   * 获取datePickerDialogTextStyle4的TextStyle对象与期待值{ font: { weight: FontWeight.Medium } }对比
   * 点击坐标(1, 1)，退出弹窗
   * 获取datePickerDialogTextStyle5的TextStyle对象与期待值{ font: { weight: FontWeight.Regular } }对比
   * 点击坐标(1, 1)，退出弹窗
   * 获取datePickerDialogTextStyle6的TextStyle对象与期待值{ font: { weight: FontWeight.Normal } }对比
   * 点击坐标(1, 1)，退出弹窗
   * 获取datePickerDialogTextStyle7的TextStyle对象与期待值BlurStyle.BACKGROUND_ULTRA_THICK对比
   * 点击坐标(1, 1)，退出弹窗
   * 点击button2，变更datePickerDialogTextStyle8的TextStyle对象为{ color: $r('sys.color.ohos_fa_palette1'),
            font: '30', weight: '30' } }
   * 点击button1，弹出弹窗
   * 获取datePickerDialogTextStyle8的TextStyle对象与期待值{ color: $r('sys.color.ohos_fa_palette1'),
            font: '30', weight: '30' } }对比
   * 点击坐标(1, 1)，退出弹窗
   */

  defineTest('datePickerDialogTextStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('datePickerDialogTextStyleTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('DatePickerDialogTextStyle1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('DatePickerDialogTextStyle2').enabled(true))

    await button1.tap()
    let datePickerDialogTextStyle1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let textStyle1: string = await datePickerDialogTextStyle1.getInspectorInfo()
    assertFalse(JSON.parse(textStyle1).$attrs.textStyle == undefined)
    assertEqual(JSON.parse(textStyle1)
      .$attrs
      .textStyle
      .color, 'rgb(142, 255, 101)')
    assertEqual(JSON.parse(textStyle1)
      .$attrs
      .textStyle
      .font
      .size, 10)
    assertEqual(JSON.parse(textStyle1)
      .$attrs
      .textStyle
      .font
      .weight, 10)
    await driver.tap(1, 1)

    let datePickerDialogTextStyle2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let textStyle2: string = await datePickerDialogTextStyle2.getInspectorInfo()
    assertEqual(JSON.parse(textStyle2)
      .$attrs
      .textStyle
      .color, 0xa52a2a)
    assertEqual(JSON.parse(textStyle2)
      .$attrs
      .textStyle
      .font
      .size, $r('app.string.text_style_size'))
    assertEqual(JSON.parse(textStyle2)
      .$attrs
      .textStyle
      .font
      .weight, FontWeight.Bolder)
    await driver.tap(1, 1)

    let datePickerDialogTextStyle3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let textStyle3: string = await datePickerDialogTextStyle3.getInspectorInfo()
    assertEqual(JSON.parse(textStyle3)
      .$attrs
      .textStyle
      .color, Color.Blue)
    assertEqual(JSON.parse(textStyle3)
      .$attrs
      .textStyle
      .font
      .weight, FontWeight.Bold)
    await driver.tap(1, 1)

    let datePickerDialogTextStyle4: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let textStyle4: string = await datePickerDialogTextStyle4.getInspectorInfo()
    assertEqual(JSON.parse(textStyle4)
      .$attrs
      .textStyle
      .font
      .weight, FontWeight.Medium)
    await driver.tap(1, 1)

    let datePickerDialogTextStyle5: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let textStyle5: string = await datePickerDialogTextStyle5.getInspectorInfo()
    assertEqual(JSON.parse(textStyle5)
      .$attrs
      .textStyle
      .font
      .weight, FontWeight.Regular)
    await driver.tap(1, 1)

    let datePickerDialogTextStyle6: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let textStyle6: string = await datePickerDialogTextStyle6.getInspectorInfo()
    assertEqual(JSON.parse(textStyle6)
      .$attrs
      .textStyle
      .font
      .weight, FontWeight.Normal)
    await driver.tap(1, 1)

    let datePickerDialogTextStyle7: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let textStyle7: string = await datePickerDialogTextStyle7.getInspectorInfo()
    assertEqual(JSON.parse(textStyle7)
      .$attrs
      .textStyle
      .font
      .weight, FontWeight.Lighter)
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogTextStyle8: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let textStyle8: string = await datePickerDialogTextStyle8.getInspectorInfo()
    assertEqual(JSON.parse(textStyle8)
      .$attrs
      .textStyle
      .color, $r('sys.color.ohos_fa_palette1'))
    assertEqual(JSON.parse(textStyle8)
      .$attrs
      .textStyle
      .font
      .size, '30')
    assertEqual(JSON.parse(textStyle8)
      .$attrs
      .textStyle
      .font
      .weight, '30')
    await driver.tap(1, 1)
  }, 0)
}