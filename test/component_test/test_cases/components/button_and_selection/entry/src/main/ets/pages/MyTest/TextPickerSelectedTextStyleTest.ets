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

export default async function textPickerSelectedTextStyleTest() {
  /*
   * TextPicker组件 SelectedTextStyle属性
   * 找到画面id为textPickerSelectedTextStyle1，textPickerSelectedTextStyle2，textPickerSelectedTextStyle3，...，textPickerSelectedTextStyle9，textPickerSelectedTextStyle10的TextPicker组件
   * 找到画面文本为TextPickerSelectedTextStyle1，TextPickerSelectedTextStyle2的Button组件
   * 获取textPickerSelectedTextStyle1的SelectedTextStyle属性与期待值{color: Color.Green}比对
   * 获取textPickerSelectedTextStyle2的SelectedTextStyle属性与期待值{color: '#FFA52A2A'}比对
   * 获取textPickerSelectedTextStyle3的SelectedTextStyle属性与期待值{color: '#FF8EFF65'}比对
   * 获取textPickerSelectedTextStyle4的SelectedTextStyle属性与期待值{font: {weight: 'FontWeight.Lighter'}}对比
   * 获取textPickerSelectedTextStyle5的SelectedTextStyle属性与期待值{font: {weight: 'FontWeight.Normal'}}对比
   * 获取textPickerSelectedTextStyle6的SelectedTextStyle属性与期待值{font: {weight: 'FontWeight.Regular'}}对比
   * 获取textPickerSelectedTextStyle7的SelectedTextStyle属性与期待值{font: {weight: 'FontWeight.Medium'}}对比
   * 获取textPickerSelectedTextStyle8的SelectedTextStyle属性与期待值{font: {weight: 'FontWeight.Bold'}}对比
   * 获取textPickerSelectedTextStyle9的SelectedTextStyle属性与期待值{font: {weight: 'FontWeight.Bolder',size: $r('app.string.size'),family: 'Arial'}}对比
   * 获取textPickerSelectedTextStyle10的SelectedTextStyle属性与期待值{font: {weight: '50',size: '50',family: 'TESTFONT',style: 'FontStyle.Normal'}}对比
   * 点击button1，变更textPickerSelectedTextStyle3的SelectedTextStyle属性值为{color: $r('sys.color.ohos_fa_palette1')}
   * 获取textPickerSelectedTextStyle3的SelectedTextStyle属性与期待值{color: $r('sys.color.ohos_fa_palette1')}比对
   * 点击button2，变更textPickerSelectedTextStyle10的SelectedTextStyle属性值为{font: {weight: '200',size: '200',style: 'FontStyle.Italic'}}
   * 获取textPickerSelectedTextStyle10的SelectedTextStyle属性与期待值{font: {weight: '200',size: '200',style: 'FontStyle.Italic'}}比对
   */
  defineTest('textPickerSelectedTextStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('textPickerSelectedTextStyleTestDemo running')
    let driver: Tester = Tester.create()
    let textPickerSelectedTextStyle1: Component =
      await driver.findComponent(Matcher.create().id('textPickerSelectedTextStyle1').enabled(true))
    let textPickerSelectedTextStyle2: Component =
      await driver.findComponent(Matcher.create().id('textPickerSelectedTextStyle2').enabled(true))
    let textPickerSelectedTextStyle3: Component =
      await driver.findComponent(Matcher.create().id('textPickerSelectedTextStyle3').enabled(true))
    let textPickerSelectedTextStyle4: Component =
      await driver.findComponent(Matcher.create().id('textPickerSelectedTextStyle4').enabled(true))
    let textPickerSelectedTextStyle5: Component =
      await driver.findComponent(Matcher.create().id('textPickerSelectedTextStyle5').enabled(true))
    let textPickerSelectedTextStyle6: Component =
      await driver.findComponent(Matcher.create().id('textPickerSelectedTextStyle6').enabled(true))
    let textPickerSelectedTextStyle7: Component =
      await driver.findComponent(Matcher.create().id('textPickerSelectedTextStyle7').enabled(true))
    let textPickerSelectedTextStyle8: Component =
      await driver.findComponent(Matcher.create().id('textPickerSelectedTextStyle8').enabled(true))
    let textPickerSelectedTextStyle9: Component =
      await driver.findComponent(Matcher.create().id('textPickerSelectedTextStyle9').enabled(true))
    let textPickerSelectedTextStyle10: Component =
      await driver.findComponent(Matcher.create().id('textPickerSelectedTextStyle10').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('TextPickerSelectedTextStyle1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('TextPickerSelectedTextStyle2').enabled(true))

    let selectedTextStyle1: string = await textPickerSelectedTextStyle1.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle1)
      .$attrs
      .selectedTextStyle
      .color
      .toLowerCase(), Color.Green)

    let selectedTextStyle2: string = await textPickerSelectedTextStyle2.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle2).$attrs.selectedTextStyle.color, '#FFA52A2A')

    let selectedTextStyle3: string = await textPickerSelectedTextStyle3.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle3).$attrs.selectedTextStyle.color, '#FF8EFF65')

    let selectedTextStyle4: string = await textPickerSelectedTextStyle4.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle4)
      .$attrs
      .selectedTextStyle
      .font
      .weight, 'FontWeight.Lighter')

    let selectedTextStyle5: string = await textPickerSelectedTextStyle5.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle5)
      .$attrs
      .selectedTextStyle
      .font
      .weight, 'FontWeight.Normal')

    let selectedTextStyle6: string = await textPickerSelectedTextStyle6.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle6)
      .$attrs
      .selectedTextStyle
      .font
      .weight, 'FontWeight.Regular')

    let selectedTextStyle7: string = await textPickerSelectedTextStyle7.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle7)
      .$attrs
      .selectedTextStyle
      .font
      .weight, 'FontWeight.Medium')

    let selectedTextStyle8: string = await textPickerSelectedTextStyle8.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle8)
      .$attrs
      .selectedTextStyle
      .font
      .weight, 'FontWeight.Bold')

    let selectedTextStyle9: string = await textPickerSelectedTextStyle9.getInspectorInfo()
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

    let selectedTextStyle10: string = await textPickerSelectedTextStyle10.getInspectorInfo()
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
    let selectedTextStyle11: string = await textPickerSelectedTextStyle3.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle11).$attrs.selectedTextStyle.color, $r('sys.color.ohos_fa_palette1'))

    await button2.tap()
    let selectedTextStyle12: string = await textPickerSelectedTextStyle10.getInspectorInfo()
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