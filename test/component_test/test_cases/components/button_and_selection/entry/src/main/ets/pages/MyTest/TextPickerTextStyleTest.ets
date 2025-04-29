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

export default async function textPickerTextStyleTest() {
  /*
   * TextPicker组件 TextStyle属性
   * 找到画面id为textPickerTextStyle1，textPickerTextStyle2，textPickerTextStyle3，...，textPickerTextStyle9，textPickerTextStyle10的TextPicker组件
   * 找到画面文本为TextPickerTextStyle1，TextPickerTextStyle2的Button组件
   * 获取textPickerTextStyle1的TextStyle属性与期待值{color: Color.Green}比对
   * 获取textPickerTextStyle2的TextStyle属性与期待值{color: '#FFA52A2A'}比对
   * 获取textPickerTextStyle3的TextStyle属性与期待值{color: '#FF8EFF65'}比对
   * 获取textPickerTextStyle4的TextStyle属性与期待值{font: {weight: 'FontWeight.Lighter'}}对比
   * 获取textPickerTextStyle5的TextStyle属性与期待值{font: {weight: 'FontWeight.Normal'}}对比
   * 获取textPickerTextStyle6的TextStyle属性与期待值{font: {weight: 'FontWeight.Regular'}}对比
   * 获取textPickerTextStyle7的TextStyle属性与期待值{font: {weight: 'FontWeight.Medium'}}对比
   * 获取textPickerTextStyle8的TextStyle属性与期待值{font: {weight: 'FontWeight.Bold'}}对比
   * 获取textPickerTextStyle9的TextStyle属性与期待值{font: {weight: 'FontWeight.Bolder',size: $r('app.string.size'),family: 'Arial'}}对比
   * 获取textPickerTextStyle10的TextStyle属性与期待值{font: {weight: '50',size: '50',family: 'TESTFONT',style: 'FontStyle.Normal'}}对比
   * 点击button1，变更textPickerTextStyle3的TextStyle属性值为{color: $r('sys.color.ohos_fa_palette1')}
   * 获取textPickerTextStyle3的TextStyle属性与期待值{color: $r('sys.color.ohos_fa_palette1')}比对
   * 点击button2，变更textPickerTextStyle10的TextStyle属性值为{font: {weight: '200',size: '200',style: 'FontStyle.Italic'}}
   * 获取textPickerTextStyle10的TextStyle属性与期待值{font: {weight: '200',size: '200',style: 'FontStyle.Italic'}}比对
   */
  defineTest('textPickerTextStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('textPickerTextStyleTestDemo running')
    let driver: Tester = Tester.create()
    let textPickerTextStyle1: Component =
      await driver.findComponent(Matcher.create().id('textPickerTextStyle1').enabled(true))
    let textPickerTextStyle2: Component =
      await driver.findComponent(Matcher.create().id('textPickerTextStyle2').enabled(true))
    let textPickerTextStyle3: Component =
      await driver.findComponent(Matcher.create().id('textPickerTextStyle3').enabled(true))
    let textPickerTextStyle4: Component =
      await driver.findComponent(Matcher.create().id('textPickerTextStyle4').enabled(true))
    let textPickerTextStyle5: Component =
      await driver.findComponent(Matcher.create().id('textPickerTextStyle5').enabled(true))
    let textPickerTextStyle6: Component =
      await driver.findComponent(Matcher.create().id('textPickerTextStyle6').enabled(true))
    let textPickerTextStyle7: Component =
      await driver.findComponent(Matcher.create().id('textPickerTextStyle7').enabled(true))
    let textPickerTextStyle8: Component =
      await driver.findComponent(Matcher.create().id('textPickerTextStyle8').enabled(true))
    let textPickerTextStyle9: Component =
      await driver.findComponent(Matcher.create().id('textPickerTextStyle9').enabled(true))
    let textPickerTextStyle10: Component =
      await driver.findComponent(Matcher.create().id('textPickerTextStyle10').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TextPickerTextStyle1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TextPickerTextStyle2').enabled(true))

    let textStyle1: string = await textPickerTextStyle1.getInspectorInfo()
    assertEqual(JSON.parse(textStyle1)
      .$attrs
      .textStyle
      .color
      .toLowerCase(), Color.Green)

    let textStyle2: string = await textPickerTextStyle2.getInspectorInfo()
    assertEqual(JSON.parse(textStyle2).$attrs.textStyle.color, '#FFA52A2A')

    let textStyle3: string = await textPickerTextStyle3.getInspectorInfo()
    assertEqual(JSON.parse(textStyle3).$attrs.textStyle.color, '#FF8EFF65')

    let textStyle4: string = await textPickerTextStyle4.getInspectorInfo()
    assertEqual(JSON.parse(textStyle4)
      .$attrs
      .textStyle
      .font
      .weight, 'FontWeight.Lighter')

    let textStyle5: string = await textPickerTextStyle5.getInspectorInfo()
    assertEqual(JSON.parse(textStyle5)
      .$attrs
      .textStyle
      .font
      .weight, 'FontWeight.Normal')

    let textStyle6: string = await textPickerTextStyle6.getInspectorInfo()
    assertEqual(JSON.parse(textStyle6)
      .$attrs
      .textStyle
      .font
      .weight, 'FontWeight.Regular')

    let textStyle7: string = await textPickerTextStyle7.getInspectorInfo()
    assertEqual(JSON.parse(textStyle7)
      .$attrs
      .textStyle
      .font
      .weight, 'FontWeight.Medium')

    let textStyle8: string = await textPickerTextStyle8.getInspectorInfo()
    assertEqual(JSON.parse(textStyle8)
      .$attrs
      .textStyle
      .font
      .weight, 'FontWeight.Bold')

    let textStyle9: string = await textPickerTextStyle9.getInspectorInfo()
    assertEqual(JSON.parse(textStyle9)
      .$attrs
      .textStyle
      .font
      .weight, 'FontWeight.Bolder')
    assertEqual(JSON.parse(textStyle9)
      .$attrs
      .textStyle
      .font
      .size, $r('app.string.size'))
    assertEqual(JSON.parse(textStyle9)
      .$attrs
      .textStyle
      .font
      .family, 'Arial')

    let textStyle10: string = await textPickerTextStyle10.getInspectorInfo()
    assertEqual(JSON.parse(textStyle10)
      .$attrs
      .textStyle
      .font
      .weight, '50')
    assertEqual(JSON.parse(textStyle10)
      .$attrs
      .textStyle
      .font
      .size, '50')
    assertEqual(JSON.parse(textStyle10)
      .$attrs
      .textStyle
      .font
      .family, 'TESTFONT')
    assertEqual(JSON.parse(textStyle10)
      .$attrs
      .textStyle
      .font
      .style, 'FontStyle.Normal')

    await button1.tap()
    let textStyle11: string = await textPickerTextStyle3.getInspectorInfo()
    assertEqual(JSON.parse(textStyle11).$attrs.textStyle.color, $r('sys.color.ohos_fa_palette1'))

    await button2.tap()
    let textStyle12: string = await textPickerTextStyle10.getInspectorInfo()
    assertEqual(JSON.parse(textStyle12)
      .$attrs
      .textStyle
      .font
      .weight, '200')
    assertEqual(JSON.parse(textStyle12)
      .$attrs
      .textStyle
      .font
      .size, '200')
    assertEqual(JSON.parse(textStyle12)
      .$attrs
      .textStyle
      .font
      .style, 'FontStyle.Italic')
  }, 0)
}