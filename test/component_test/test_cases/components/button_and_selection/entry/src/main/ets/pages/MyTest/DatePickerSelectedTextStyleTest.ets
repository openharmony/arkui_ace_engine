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

export default async function datePickerSelectedTextStyleTest() {
  /*
   * DatePicker组件 SelectedTextStyle属性
   * 找到画面id为datePickerSelectedTextStyle1，datePickerSelectedTextStyle2，datePickerSelectedTextStyle3，...，datePickerSelectedTextStyle9，datePickerSelectedTextStyle10的DatePicker组件
   * 找到画面文本为DatePickerSelectedTextStyle1，DatePickerSelectedTextStyle2的Button组件
   * 获取datePickerSelectedTextStyle1的SelectedTextStyle属性与期待值{color: Color.Green}比对
   * 获取datePickerSelectedTextStyle2的SelectedTextStyle属性与期待值{color: '#FFA52A2A'}比对
   * 获取datePickerSelectedTextStyle3的SelectedTextStyle属性与期待值{color: '#FF8EFF65'}比对
   * 获取datePickerSelectedTextStyle4的SelectedTextStyle属性与期待值{font: {weight: 'FontWeight.Lighter'}}对比
   * 获取datePickerSelectedTextStyle5的SelectedTextStyle属性与期待值{font: {weight: 'FontWeight.Normal'}}对比
   * 获取datePickerSelectedTextStyle6的SelectedTextStyle属性与期待值{font: {weight: 'FontWeight.Regular'}}对比
   * 获取datePickerSelectedTextStyle7的SelectedTextStyle属性与期待值{font: {weight: 'FontWeight.Medium'}}对比
   * 获取datePickerSelectedTextStyle8的SelectedTextStyle属性与期待值{font: {weight: 'FontWeight.Bold'}}对比
   * 获取datePickerSelectedTextStyle9的SelectedTextStyle属性与期待值{font: {weight: 'FontWeight.Bolder',size: $r('app.string.size'),family: 'Arial'}}对比
   * 获取datePickerSelectedTextStyle10的SelectedTextStyle属性与期待值{font: {weight: 50,size: 50,family: 'TESTFONT',style: 'FontStyle.Normal'}}对比
   * 点击button1，变更datePickerSelectedTextStyle3的SelectedTextStyle属性值为{color: $r('sys.color.ohos_fa_palette1')}
   * 获取datePickerSelectedTextStyle3的SelectedTextStyle属性与期待值{color: $r('sys.color.ohos_fa_palette1')}比对
   * 点击button2，变更datePickerSelectedTextStyle10的SelectedTextStyle属性值为{font: {weight: '200',size: '200',style: 'FontStyle.Italic'}}
   * 获取datePickerSelectedTextStyle10的SelectedTextStyle属性与期待值{font: {weight: '200',size: '200',style: 'FontStyle.Italic'}}比对
   */
  defineTest('datePickerSelectedTextStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('datePickerSelectedTextStyleTestDemo running')
    let driver: Tester = Tester.create()
    let datePickerSelectedTextStyle1: Component =
      await driver.findComponent(Matcher.create().id('datePickerSelectedTextStyle1').enabled(true))
    let datePickerSelectedTextStyle2: Component =
      await driver.findComponent(Matcher.create().id('datePickerSelectedTextStyle2').enabled(true))
    let datePickerSelectedTextStyle3: Component =
      await driver.findComponent(Matcher.create().id('datePickerSelectedTextStyle3').enabled(true))
    let datePickerSelectedTextStyle4: Component =
      await driver.findComponent(Matcher.create().id('datePickerSelectedTextStyle4').enabled(true))
    let datePickerSelectedTextStyle5: Component =
      await driver.findComponent(Matcher.create().id('datePickerSelectedTextStyle5').enabled(true))
    let datePickerSelectedTextStyle6: Component =
      await driver.findComponent(Matcher.create().id('datePickerSelectedTextStyle6').enabled(true))
    let datePickerSelectedTextStyle7: Component =
      await driver.findComponent(Matcher.create().id('datePickerSelectedTextStyle7').enabled(true))
    let datePickerSelectedTextStyle8: Component =
      await driver.findComponent(Matcher.create().id('datePickerSelectedTextStyle8').enabled(true))
    let datePickerSelectedTextStyle9: Component =
      await driver.findComponent(Matcher.create().id('datePickerSelectedTextStyle9').enabled(true))
    let datePickerSelectedTextStyle10: Component =
      await driver.findComponent(Matcher.create().id('datePickerSelectedTextStyle10').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('DatePickerSelectedTextStyle1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('DatePickerSelectedTextStyle2').enabled(true))

    let selectedTextStyle1: string = await datePickerSelectedTextStyle1.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle1)
      .$attrs
      .selectedTextStyle
      .color
      .toLowerCase(), Color.Green)

    let selectedTextStyle2: string = await datePickerSelectedTextStyle2.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle2).$attrs.selectedTextStyle.color, '#FFA52A2A')

    let selectedTextStyle3: string = await datePickerSelectedTextStyle3.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle3).$attrs.selectedTextStyle.color, '#FF8EFF65')

    let selectedTextStyle4: string = await datePickerSelectedTextStyle4.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle4)
      .$attrs
      .selectedTextStyle
      .font
      .weight, 'FontWeight.Lighter')

    let selectedTextStyle5: string = await datePickerSelectedTextStyle5.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle5)
      .$attrs
      .selectedTextStyle
      .font
      .weight, 'FontWeight.Normal')

    let selectedTextStyle6: string = await datePickerSelectedTextStyle6.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle6)
      .$attrs
      .selectedTextStyle
      .font
      .weight, 'FontWeight.Regular')

    let selectedTextStyle7: string = await datePickerSelectedTextStyle7.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle7)
      .$attrs
      .selectedTextStyle
      .font
      .weight, 'FontWeight.Medium')

    let selectedTextStyle8: string = await datePickerSelectedTextStyle8.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle8)
      .$attrs
      .selectedTextStyle
      .font
      .weight, 'FontWeight.Bold')

    let selectedTextStyle9: string = await datePickerSelectedTextStyle9.getInspectorInfo()
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

    let selectedTextStyle10: string = await datePickerSelectedTextStyle10.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle10)
      .$attrs
      .selectedTextStyle
      .font
      .weight, 50)
    assertEqual(JSON.parse(selectedTextStyle10)
      .$attrs
      .selectedTextStyle
      .font
      .size, 50)
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
    let selectedTextStyle11: string = await datePickerSelectedTextStyle3.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle11).$attrs.selectedTextStyle.color, $r('sys.color.ohos_fa_palette1'))

    await button2.tap()
    let selectedTextStyle12: string = await datePickerSelectedTextStyle10.getInspectorInfo()
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