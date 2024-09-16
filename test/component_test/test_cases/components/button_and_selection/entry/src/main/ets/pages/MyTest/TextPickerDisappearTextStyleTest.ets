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

export default async function textPickerDisappearTextStyleTest() {
  /*
   * TextPicker组件 DisappearTextStyle属性
   * 找到画面id为textPickerDisappearTextStyle1，textPickerDisappearTextStyle2，textPickerDisappearTextStyle3，...，textPickerDisappearTextStyle9，textPickerDisappearTextStyle10的TextPicker组件
   * 找到画面文本为TextPickerDisappearTextStyle1，TextPickerDisappearTextStyle2的Button组件
   * 获取textPickerDisappearTextStyle1的DisappearTextStyle属性与期待值{color: Color.Green}比对
   * 获取textPickerDisappearTextStyle2的DisappearTextStyle属性与期待值{color: '#FFA52A2A'}比对
   * 获取textPickerDisappearTextStyle3的DisappearTextStyle属性与期待值{color: '#FF8EFF65'}比对
   * 获取textPickerDisappearTextStyle4的DisappearTextStyle属性与期待值{font: {weight: 'FontWeight.Lighter'}}对比
   * 获取textPickerDisappearTextStyle5的DisappearTextStyle属性与期待值{font: {weight: 'FontWeight.Normal'}}对比
   * 获取textPickerDisappearTextStyle6的DisappearTextStyle属性与期待值{font: {weight: 'FontWeight.Regular'}}对比
   * 获取textPickerDisappearTextStyle7的DisappearTextStyle属性与期待值{font: {weight: 'FontWeight.Medium'}}对比
   * 获取textPickerDisappearTextStyle8的DisappearTextStyle属性与期待值{font: {weight: 'FontWeight.Bold'}}对比
   * 获取textPickerDisappearTextStyle9的DisappearTextStyle属性与期待值{font: {weight: 'FontWeight.Bolder',size: $r('app.string.size'),family: 'Arial'}}对比
   * 获取textPickerDisappearTextStyle10的DisappearTextStyle属性与期待值{font: {weight: '50',size: '50',family: 'TESTFONT',style: 'FontStyle.Normal'}}对比
   * 点击button1，变更textPickerDisappearTextStyle3的DisappearTextStyle属性值为{color: $r('sys.color.ohos_fa_palette1')}
   * 获取textPickerDisappearTextStyle3的DisappearTextStyle属性与期待值{color: $r('sys.color.ohos_fa_palette1')}比对
   * 点击button2，变更textPickerDisappearTextStyle10的DisappearTextStyle属性值为{font: {weight: '200',size: '200',style: 'FontStyle.Italic'}}
   * 获取textPickerDisappearTextStyle10的DisappearTextStyle属性与期待值{font: {weight: '200',size: '200',style: 'FontStyle.Italic'}}比对
   */
  defineTest('textPickerDisappearTextStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('textPickerDisappearTextStyleTestDemo running')
    let driver: Tester = Tester.create()
    let textPickerDisappearTextStyle1: Component =
      await driver.findComponent(Matcher.create().id('textPickerDisappearTextStyle1').enabled(true))
    let textPickerDisappearTextStyle2: Component =
      await driver.findComponent(Matcher.create().id('textPickerDisappearTextStyle2').enabled(true))
    let textPickerDisappearTextStyle3: Component =
      await driver.findComponent(Matcher.create().id('textPickerDisappearTextStyle3').enabled(true))
    let textPickerDisappearTextStyle4: Component =
      await driver.findComponent(Matcher.create().id('textPickerDisappearTextStyle4').enabled(true))
    let textPickerDisappearTextStyle5: Component =
      await driver.findComponent(Matcher.create().id('textPickerDisappearTextStyle5').enabled(true))
    let textPickerDisappearTextStyle6: Component =
      await driver.findComponent(Matcher.create().id('textPickerDisappearTextStyle6').enabled(true))
    let textPickerDisappearTextStyle7: Component =
      await driver.findComponent(Matcher.create().id('textPickerDisappearTextStyle7').enabled(true))
    let textPickerDisappearTextStyle8: Component =
      await driver.findComponent(Matcher.create().id('textPickerDisappearTextStyle8').enabled(true))
    let textPickerDisappearTextStyle9: Component =
      await driver.findComponent(Matcher.create().id('textPickerDisappearTextStyle9').enabled(true))
    let textPickerDisappearTextStyle10: Component =
      await driver.findComponent(Matcher.create().id('textPickerDisappearTextStyle10').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('TextPickerDisappearTextStyle1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('TextPickerDisappearTextStyle2').enabled(true))

    let disappearTextStyle1: string = await textPickerDisappearTextStyle1.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle1)
      .$attrs
      .disappearTextStyle
      .color
      .toLowerCase(), Color.Green)

    let disappearTextStyle2: string = await textPickerDisappearTextStyle2.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle2).$attrs.disappearTextStyle.color, '#FFA52A2A')

    let disappearTextStyle3: string = await textPickerDisappearTextStyle3.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle3).$attrs.disappearTextStyle.color, '#FF8EFF65')

    let disappearTextStyle4: string = await textPickerDisappearTextStyle4.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle4)
      .$attrs
      .disappearTextStyle
      .font
      .weight, 'FontWeight.Lighter')

    let disappearTextStyle5: string = await textPickerDisappearTextStyle5.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle5)
      .$attrs
      .disappearTextStyle
      .font
      .weight, 'FontWeight.Normal')

    let disappearTextStyle6: string = await textPickerDisappearTextStyle6.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle6)
      .$attrs
      .disappearTextStyle
      .font
      .weight, 'FontWeight.Regular')

    let disappearTextStyle7: string = await textPickerDisappearTextStyle7.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle7)
      .$attrs
      .disappearTextStyle
      .font
      .weight, 'FontWeight.Medium')

    let disappearTextStyle8: string = await textPickerDisappearTextStyle8.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle8)
      .$attrs
      .disappearTextStyle
      .font
      .weight, 'FontWeight.Bold')

    let disappearTextStyle9: string = await textPickerDisappearTextStyle9.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle9)
      .$attrs
      .disappearTextStyle
      .font
      .weight, 'FontWeight.Bolder')
    assertEqual(JSON.parse(disappearTextStyle9)
      .$attrs
      .disappearTextStyle
      .font
      .size, $r('app.string.size'))
    assertEqual(JSON.parse(disappearTextStyle9)
      .$attrs
      .disappearTextStyle
      .font
      .family, 'Arial')

    let disappearTextStyle10: string = await textPickerDisappearTextStyle10.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle10)
      .$attrs
      .disappearTextStyle
      .font
      .weight, '50')
    assertEqual(JSON.parse(disappearTextStyle10)
      .$attrs
      .disappearTextStyle
      .font
      .size, '50')
    assertEqual(JSON.parse(disappearTextStyle10)
      .$attrs
      .disappearTextStyle
      .font
      .family, 'TESTFONT')
    assertEqual(JSON.parse(disappearTextStyle10)
      .$attrs
      .disappearTextStyle
      .font
      .style, 'FontStyle.Normal')

    await button1.tap()
    let disappearTextStyle11: string = await textPickerDisappearTextStyle3.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle11).$attrs.disappearTextStyle.color, $r('sys.color.ohos_fa_palette1'))

    await button2.tap()
    let disappearTextStyle12: string = await textPickerDisappearTextStyle10.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle12)
      .$attrs
      .disappearTextStyle
      .font
      .weight, '200')
    assertEqual(JSON.parse(disappearTextStyle12)
      .$attrs
      .disappearTextStyle
      .font
      .size, '200')
    assertEqual(JSON.parse(disappearTextStyle12)
      .$attrs
      .disappearTextStyle
      .font
      .style, 'FontStyle.Italic')
  }, 0)
}