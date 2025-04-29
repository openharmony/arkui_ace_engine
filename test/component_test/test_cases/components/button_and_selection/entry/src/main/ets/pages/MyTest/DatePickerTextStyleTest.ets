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

export default async function datePickerTextStyleTest() {
  /*
   * DatePicker组件 TextStyle属性
   * 找到画面id为datePickerTextStyle1，datePickerTextStyle2，datePickerTextStyle3，...，datePickerTextStyle9，datePickerTextStyle10的DatePicker组件
   * 找到画面文本为DatePickerTextStyle1，DatePickerTextStyle2的Button组件
   * 获取datePickerTextStyle1的TextStyle属性与期待值{color: Color.Green}比对
   * 获取datePickerTextStyle2的TextStyle属性与期待值{color: '#FFA52A2A'}比对
   * 获取datePickerTextStyle3的TextStyle属性与期待值{color: '#FF8EFF65'}比对
   * 获取datePickerTextStyle4的TextStyle属性与期待值{font: {weight: 'FontWeight.Lighter'}}对比
   * 获取datePickerTextStyle5的TextStyle属性与期待值{font: {weight: 'FontWeight.Normal'}}对比
   * 获取datePickerTextStyle6的TextStyle属性与期待值{font: {weight: 'FontWeight.Regular'}}对比
   * 获取datePickerTextStyle7的TextStyle属性与期待值{font: {weight: 'FontWeight.Medium'}}对比
   * 获取datePickerTextStyle8的TextStyle属性与期待值{font: {weight: 'FontWeight.Bold'}}对比
   * 获取datePickerTextStyle9的TextStyle属性与期待值{font: {weight: 'FontWeight.Bolder',size: $r('app.string.size'),family: 'Arial'}}对比
   * 获取datePickerTextStyle10的TextStyle属性与期待值{font: {weight: 50,size: 50,family: 'TESTFONT',style: 'FontStyle.Normal'}}对比
   * 点击button1，变更datePickerTextStyle3的TextStyle属性值为{color: $r('sys.color.ohos_fa_palette1')}
   * 获取datePickerTextStyle3的TextStyle属性与期待值{color: $r('sys.color.ohos_fa_palette1')}比对
   * 点击button2，变更datePickerTextStyle10的TextStyle属性值为{font: {weight: '200',size: '200',style: 'FontStyle.Italic'}}
   * 获取datePickerTextStyle10的TextStyle属性与期待值{font: {weight: '200',size: '200',style: 'FontStyle.Italic'}}比对
   */
  defineTest('datePickerTextStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('datePickerTextStyleTestDemo running')
    let driver: Tester = Tester.create()
    let datePickerTextStyle1: Component =
      await driver.findComponent(Matcher.create().id('datePickerTextStyle1').enabled(true))
    let datePickerTextStyle2: Component =
      await driver.findComponent(Matcher.create().id('datePickerTextStyle2').enabled(true))
    let datePickerTextStyle3: Component =
      await driver.findComponent(Matcher.create().id('datePickerTextStyle3').enabled(true))
    let datePickerTextStyle4: Component =
      await driver.findComponent(Matcher.create().id('datePickerTextStyle4').enabled(true))
    let datePickerTextStyle5: Component =
      await driver.findComponent(Matcher.create().id('datePickerTextStyle5').enabled(true))
    let datePickerTextStyle6: Component =
      await driver.findComponent(Matcher.create().id('datePickerTextStyle6').enabled(true))
    let datePickerTextStyle7: Component =
      await driver.findComponent(Matcher.create().id('datePickerTextStyle7').enabled(true))
    let datePickerTextStyle8: Component =
      await driver.findComponent(Matcher.create().id('datePickerTextStyle8').enabled(true))
    let datePickerTextStyle9: Component =
      await driver.findComponent(Matcher.create().id('datePickerTextStyle9').enabled(true))
    let datePickerTextStyle10: Component =
      await driver.findComponent(Matcher.create().id('datePickerTextStyle10').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('DatePickerTextStyle1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('DatePickerTextStyle2').enabled(true))

    let textStyle1: string = await datePickerTextStyle1.getInspectorInfo()
    assertEqual(JSON.parse(textStyle1)
      .$attrs
      .textStyle
      .color
      .toLowerCase(), Color.Green)

    let textStyle2: string = await datePickerTextStyle2.getInspectorInfo()
    assertEqual(JSON.parse(textStyle2).$attrs.textStyle.color, '#FFA52A2A')

    let textStyle3: string = await datePickerTextStyle3.getInspectorInfo()
    assertEqual(JSON.parse(textStyle3).$attrs.textStyle.color, '#FF8EFF65')

    let textStyle4: string = await datePickerTextStyle4.getInspectorInfo()
    assertEqual(JSON.parse(textStyle4)
      .$attrs
      .textStyle
      .font
      .weight, 'FontWeight.Lighter')

    let textStyle5: string = await datePickerTextStyle5.getInspectorInfo()
    assertEqual(JSON.parse(textStyle5)
      .$attrs
      .textStyle
      .font
      .weight, 'FontWeight.Normal')

    let textStyle6: string = await datePickerTextStyle6.getInspectorInfo()
    assertEqual(JSON.parse(textStyle6)
      .$attrs
      .textStyle
      .font
      .weight, 'FontWeight.Regular')

    let textStyle7: string = await datePickerTextStyle7.getInspectorInfo()
    assertEqual(JSON.parse(textStyle7)
      .$attrs
      .textStyle
      .font
      .weight, 'FontWeight.Medium')

    let textStyle8: string = await datePickerTextStyle8.getInspectorInfo()
    assertEqual(JSON.parse(textStyle8)
      .$attrs
      .textStyle
      .font
      .weight, 'FontWeight.Bold')

    let textStyle9: string = await datePickerTextStyle9.getInspectorInfo()
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

    let textStyle10: string = await datePickerTextStyle10.getInspectorInfo()
    assertEqual(JSON.parse(textStyle10)
      .$attrs
      .textStyle
      .font
      .weight, 50)
    assertEqual(JSON.parse(textStyle10)
      .$attrs
      .textStyle
      .font
      .size, 50)
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
    let textStyle11: string = await datePickerTextStyle3.getInspectorInfo()
    assertEqual(JSON.parse(textStyle11).$attrs.textStyle.color, $r('sys.color.ohos_fa_palette1'))

    await button2.tap()
    let textStyle12: string = await datePickerTextStyle10.getInspectorInfo()
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