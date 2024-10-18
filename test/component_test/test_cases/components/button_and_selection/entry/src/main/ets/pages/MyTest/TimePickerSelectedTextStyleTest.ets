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

import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function timePickerSelectedTextStyleTest() {
  /*
   * TimePicker组件 SelectedTextStyle属性
   * 找到画面id为timePickerSelectedTextStyle1，timePickerSelectedTextStyle2，timePickerSelectedTextStyle3，...，timePickerSelectedTextStyle9，timePickerSelectedTextStyle10的TextPicker组件
   * 找到画面文本为TimePickerSelectedTextStyle1，TimePickerSelectedTextStyle2的Button组件
   * 获取timePickerSelectedTextStyle1的SelectedTextStyle属性与期待值{color: Color.Green}比对
   * 获取timePickerSelectedTextStyle2的SelectedTextStyle属性与期待值{color: '#FFA52A2A'}比对
   * 获取timePickerSelectedTextStyle3的SelectedTextStyle属性与期待值{color: '#FF8EFF65'}比对
   * 获取timePickerSelectedTextStyle4的SelectedTextStyle属性与期待值{font: {weight: 'FontWeight.Lighter'}}对比
   * 获取timePickerSelectedTextStyle5的SelectedTextStyle属性与期待值{font: {weight: 'FontWeight.Normal'}}对比
   * 获取timePickerSelectedTextStyle6的SelectedTextStyle属性与期待值{font: {weight: 'FontWeight.Regular'}}对比
   * 获取timePickerSelectedTextStyle7的SelectedTextStyle属性与期待值{font: {weight: 'FontWeight.Medium'}}对比
   * 获取timePickerSelectedTextStyle8的SelectedTextStyle属性与期待值{font: {weight: 'FontWeight.Bold'}}对比
   * 获取timePickerSelectedTextStyle9的SelectedTextStyle属性与期待值{font: {weight: 'FontWeight.Bolder',size: $r('app.string.size'),family: 'Arial'}}对比
   * 获取timePickerSelectedTextStyle10的SelectedTextStyle属性与期待值{font: {weight: '50',size: '50',family: 'TESTFONT',style: 'FontStyle.Normal'}}对比
   * 点击button1，变更timePickerSelectedTextStyle3的SelectedTextStyle属性值为{color: $r('sys.color.ohos_fa_palette1')}
   * 获取timePickerSelectedTextStyle3的SelectedTextStyle属性与期待值{color: $r('sys.color.ohos_fa_palette1')}比对
   * 点击button2，变更timePickerSelectedTextStyle10的SelectedTextStyle属性值为{font: {weight: '200',size: '200',style: 'FontStyle.Italic'}}
   * 获取timePickerSelectedTextStyle10的SelectedTextStyle属性与期待值{font: {weight: '200',size: '200',style: 'FontStyle.Italic'}}比对
   */
  defineTest('timePickerSelectedTextStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('timePickerSelectedTextStyleTestDemo running')
    let driver: Tester = Tester.create()
    let timePickerSelectedTextStyle1: Component =
      await driver.findComponent(Matcher.create().id('timePickerSelectedTextStyle1').enabled(true))
    let timePickerSelectedTextStyle2: Component =
      await driver.findComponent(Matcher.create().id('timePickerSelectedTextStyle2').enabled(true))
    let timePickerSelectedTextStyle3: Component =
      await driver.findComponent(Matcher.create().id('timePickerSelectedTextStyle3').enabled(true))
    let timePickerSelectedTextStyle4: Component =
      await driver.findComponent(Matcher.create().id('timePickerSelectedTextStyle4').enabled(true))
    let timePickerSelectedTextStyle5: Component =
      await driver.findComponent(Matcher.create().id('timePickerSelectedTextStyle5').enabled(true))
    let timePickerSelectedTextStyle6: Component =
      await driver.findComponent(Matcher.create().id('timePickerSelectedTextStyle6').enabled(true))
    let timePickerSelectedTextStyle7: Component =
      await driver.findComponent(Matcher.create().id('timePickerSelectedTextStyle7').enabled(true))
    let timePickerSelectedTextStyle8: Component =
      await driver.findComponent(Matcher.create().id('timePickerSelectedTextStyle8').enabled(true))
    let timePickerSelectedTextStyle9: Component =
      await driver.findComponent(Matcher.create().id('timePickerSelectedTextStyle9').enabled(true))
    let timePickerSelectedTextStyle10: Component =
      await driver.findComponent(Matcher.create().id('timePickerSelectedTextStyle10').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('TimePickerSelectedTextStyle1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('TimePickerSelectedTextStyle2').enabled(true))

    let selectedTextStyle1: string = await timePickerSelectedTextStyle1.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle1)
      .$attrs
      .selectedTextStyle
      .color
      .toLowerCase(), Color.Green)

    let selectedTextStyle2: string = await timePickerSelectedTextStyle2.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle2).$attrs.selectedTextStyle.color, '#FFA52A2A')

    let selectedTextStyle3: string = await timePickerSelectedTextStyle3.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle3).$attrs.selectedTextStyle.color, '#FF8EFF65')

    let selectedTextStyle4: string = await timePickerSelectedTextStyle4.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle4)
      .$attrs
      .selectedTextStyle
      .font
      .weight, 'FontWeight.Lighter')

    let selectedTextStyle5: string = await timePickerSelectedTextStyle5.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle5)
      .$attrs
      .selectedTextStyle
      .font
      .weight, 'FontWeight.Normal')

    let selectedTextStyle6: string = await timePickerSelectedTextStyle6.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle6)
      .$attrs
      .selectedTextStyle
      .font
      .weight, 'FontWeight.Regular')

    let selectedTextStyle7: string = await timePickerSelectedTextStyle7.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle7)
      .$attrs
      .selectedTextStyle
      .font
      .weight, 'FontWeight.Medium')

    let selectedTextStyle8: string = await timePickerSelectedTextStyle8.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle8)
      .$attrs
      .selectedTextStyle
      .font
      .weight, 'FontWeight.Bold')

    let selectedTextStyle9: string = await timePickerSelectedTextStyle9.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle9)
      .$attrs
      .selectedTextStyle
      .font
      .weight, 'FontWeight.Bolder')
    assertEqual(JSON.parse(selectedTextStyle9)
      .$attrs
      .selectedTextStyle
      .font
      .size, $r('app.string.size'))
    assertEqual(JSON.parse(selectedTextStyle9)
      .$attrs
      .selectedTextStyle
      .font
      .family, 'Arial')

    let selectedTextStyle10: string = await timePickerSelectedTextStyle10.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle10)
      .$attrs
      .selectedTextStyle
      .font
      .weight, '50')
    assertEqual(JSON.parse(selectedTextStyle10)
      .$attrs
      .selectedTextStyle
      .font
      .size, '50')
    assertEqual(JSON.parse(selectedTextStyle10)
      .$attrs
      .selectedTextStyle
      .font
      .family, 'TESTFONT')
    assertEqual(JSON.parse(selectedTextStyle10)
      .$attrs
      .selectedTextStyle
      .font
      .style, 'FontStyle.Normal')

    await button1.tap()
    let selectedTextStyle11: string = await timePickerSelectedTextStyle3.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle11).$attrs.selectedTextStyle.color, $r('sys.color.ohos_fa_palette1'))

    await button2.tap()
    let selectedTextStyle12: string = await timePickerSelectedTextStyle10.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle12)
      .$attrs
      .selectedTextStyle
      .font
      .weight, '200')
    assertEqual(JSON.parse(selectedTextStyle12)
      .$attrs
      .selectedTextStyle
      .font
      .size, '200')
    assertEqual(JSON.parse(selectedTextStyle12)
      .$attrs
      .selectedTextStyle
      .font
      .style, 'FontStyle.Italic')
  }, 0)
}