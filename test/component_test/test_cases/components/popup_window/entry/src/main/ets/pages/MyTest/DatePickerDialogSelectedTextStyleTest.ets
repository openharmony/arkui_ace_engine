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

export default async function datePickerDialogSelectedTextStyleTest() {
  /*
   * DatePickerDialog组件 SelectedTextStyle对象
   * 找到画面text为DatePickerDialogSelectedTextStyle1，DatePickerDialogSelectedTextStyle2的Button组件
   * 点击button1，弹出弹窗
   * 获取datePickerDialogSelectedTextStyle1的SelectedTextStyle对象与期待值{ color: 'rgb(142, 255, 101)',
            font: {size: 10, weight: 10 } }对比
   * 点击坐标(1, 1)，退出弹窗
   * 获取datePickerDialogSelectedTextStyle2的SelectedTextStyle对象与期待值{ color: 0xa52a2a,
            font: {size: $r('app.string.text_style_size'), weight: FontWeight.Bolder } }对比
   * 点击坐标(1, 1)，退出弹窗
   * 获取datePickerDialogSelectedTextStyle3的SelectedTextStyle对象与期待值{ color: Color.Blue,
            font: { weight: FontWeight.Bold } }对比
   * 点击坐标(1, 1)，退出弹窗
   * 获取datePickerDialogSelectedTextStyle4的SelectedTextStyle对象与期待值{ font: { weight: FontWeight.Medium } }对比
   * 点击坐标(1, 1)，退出弹窗
   * 获取datePickerDialogSelectedTextStyle5的SelectedTextStyle对象与期待值{ font: { weight: FontWeight.Regular } }对比
   * 点击坐标(1, 1)，退出弹窗
   * 获取datePickerDialogSelectedTextStyle6的SelectedTextStyle对象与期待值{ font: { weight: FontWeight.Normal } }对比
   * 点击坐标(1, 1)，退出弹窗
   * 获取datePickerDialogSelectedTextStyle7的SelectedTextStyle对象与期待值BlurStyle.BACKGROUND_ULTRA_THICK对比
   * 点击坐标(1, 1)，退出弹窗
   * 点击button2，变更datePickerDialogSelectedTextStyle8的SelectedTextStyle对象为{ color: $r('sys.color.ohos_fa_palette1'),
            font: '30', weight: '30' } }
   * 点击button1，弹出弹窗
   * 获取datePickerDialogSelectedTextStyle8的SelectedTextStyle对象与期待值{ color: $r('sys.color.ohos_fa_palette1'),
            font: '30', weight: '30' } }对比
   * 点击坐标(1, 1)，退出弹窗
   */

  defineTest('datePickerDialogSelectedTextStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('datePickerDialogSelectedTextStyleTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('DatePickerDialogSelectedTextStyle1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('DatePickerDialogSelectedTextStyle2').enabled(true))

    await button1.tap()
    let datePickerDialogSelectedTextStyle1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let selectedTextStyle1: string = await datePickerDialogSelectedTextStyle1.getInspectorInfo()
    assertFalse(JSON.parse(selectedTextStyle1).$attrs.selectedTextStyle == undefined)
    assertEqual(JSON.parse(selectedTextStyle1).$attrs.selectedTextStyle.color, 'rgb(142, 255, 101)')
    assertEqual(JSON.parse(selectedTextStyle1)
      .$attrs
      .selectedTextStyle
      .font
      .size, 10)
    assertEqual(JSON.parse(selectedTextStyle1)
      .$attrs
      .selectedTextStyle
      .font
      .weight, 10)
    await driver.tap(1, 1)

    let datePickerDialogSelectedTextStyle2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let selectedTextStyle2: string = await datePickerDialogSelectedTextStyle2.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle2).$attrs.selectedTextStyle.color, 0xa52a2a)
    assertEqual(JSON.parse(selectedTextStyle2)
      .$attrs
      .selectedTextStyle
      .font
      .size, $r('app.string.text_style_size'))
    assertEqual(JSON.parse(selectedTextStyle2)
      .$attrs
      .selectedTextStyle
      .font
      .weight, FontWeight.Bolder)
    await driver.tap(1, 1)

    let datePickerDialogSelectedTextStyle3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let selectedTextStyle3: string = await datePickerDialogSelectedTextStyle3.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle3).$attrs.selectedTextStyle.color, Color.Blue)
    assertEqual(JSON.parse(selectedTextStyle3)
      .$attrs
      .selectedTextStyle
      .font
      .weight, FontWeight.Bold)
    await driver.tap(1, 1)

    let datePickerDialogSelectedTextStyle4: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let selectedTextStyle4: string = await datePickerDialogSelectedTextStyle4.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle4)
      .$attrs
      .selectedTextStyle
      .font
      .weight, FontWeight.Medium)
    await driver.tap(1, 1)

    let datePickerDialogSelectedTextStyle5: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let selectedTextStyle5: string = await datePickerDialogSelectedTextStyle5.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle5)
      .$attrs
      .selectedTextStyle
      .font
      .weight, FontWeight.Regular)
    await driver.tap(1, 1)

    let datePickerDialogSelectedTextStyle6: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let selectedTextStyle6: string = await datePickerDialogSelectedTextStyle6.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle6)
      .$attrs
      .selectedTextStyle
      .font
      .weight, FontWeight.Normal)
    await driver.tap(1, 1)

    let datePickerDialogSelectedTextStyle7: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let selectedTextStyle7: string = await datePickerDialogSelectedTextStyle7.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle7)
      .$attrs
      .selectedTextStyle
      .font
      .weight, FontWeight.Lighter)
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogSelectedTextStyle8: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let selectedTextStyle8: string = await datePickerDialogSelectedTextStyle8.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle8).$attrs.selectedTextStyle.color, $r('sys.color.ohos_fa_palette1'))
    assertEqual(JSON.parse(selectedTextStyle8)
      .$attrs
      .selectedTextStyle
      .font
      .size, '30')
    assertEqual(JSON.parse(selectedTextStyle8)
      .$attrs
      .selectedTextStyle
      .font
      .weight, '30')
    await driver.tap(1, 1)
  }, 0)
}