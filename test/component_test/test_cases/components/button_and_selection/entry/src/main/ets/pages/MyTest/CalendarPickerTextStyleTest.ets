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

export default async function calendarPickerTextStyleTest() {
  /*
   * CalendarPicker组件 TextStyle属性
   * 找到画面id为calendarPickerTextStyle1，calendarPickerTextStyle2，calendarPickerTextStyle3，...，calendarPickerTextStyle9，calendarPickerTextStyle10的CalendarPicker组件
   * 找到画面文本为CalendarPickerTextStyle1，CalendarPickerTextStyle2的Button组件
   * 获取calendarPickerTextStyle1的TextStyle属性与期待值{color: Color.Black}比对
   * 获取calendarPickerTextStyle2的TextStyle属性与期待值{color: '#FFA52A2A'}比对
   * 获取calendarPickerTextStyle3的TextStyle属性与期待值{color: '#FF8EFF65'}比对
   * 获取calendarPickerTextStyle4的TextStyle属性与期待值{font: {weight: 'FontWeight.Lighter'}}对比
   * 获取calendarPickerTextStyle5的TextStyle属性与期待值{font: {weight: 'FontWeight.Normal'}}对比
   * 获取calendarPickerTextStyle6的TextStyle属性与期待值{font: {weight: 'FontWeight.Regular'}}对比
   * 获取calendarPickerTextStyle7的TextStyle属性与期待值{font: {weight: 'FontWeight.Medium'}}对比
   * 获取calendarPickerTextStyle8的TextStyle属性与期待值{font: {weight: 'FontWeight.Bold',size: $r('app.string.size')}}对比
   * 获取calendarPickerTextStyle9的TextStyle属性与期待值{font: {weight: 'FontWeight.Bolder',size: '10px',family: 'Arial'}}对比
   * 获取calendarPickerTextStyle10的TextStyle属性与期待值{font: {weight: '50',size: '50',family: 'TESTFONT',style: 'FontStyle.Normal'}}对比
   * 点击button1，变更calendarPickerTextStyle3的TextStyle属性值为{color: $r('sys.color.ohos_fa_palette1')}
   * 获取calendarPickerTextStyle3的TextStyle属性与期待值{color: $r('sys.color.ohos_fa_palette1')}比对
   * 点击button2，变更calendarPickerTextStyle10的TextStyle属性值为{font: {weight: '100',size: '100', style: 'FontStyle.Italic'}}
   * 获取calendarPickerTextStyle10的TextStyle属性与期待值{font: {weight: '100',size: '100', style: 'FontStyle.Italic'}}比对
   */
  defineTest('calendarPickerTextStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('calendarPickerTextStyleTestDemo running')
    let driver: Tester = Tester.create()
    let calendarPickerTextStyle1: Component =
      await driver.findComponent(Matcher.create().id('calendarPickerTextStyle1').enabled(true))
    let calendarPickerTextStyle2: Component =
      await driver.findComponent(Matcher.create().id('calendarPickerTextStyle2').enabled(true))
    let calendarPickerTextStyle3: Component =
      await driver.findComponent(Matcher.create().id('calendarPickerTextStyle3').enabled(true))
    let calendarPickerTextStyle4: Component =
      await driver.findComponent(Matcher.create().id('calendarPickerTextStyle4').enabled(true))
    let calendarPickerTextStyle5: Component =
      await driver.findComponent(Matcher.create().id('calendarPickerTextStyle5').enabled(true))
    let calendarPickerTextStyle6: Component =
      await driver.findComponent(Matcher.create().id('calendarPickerTextStyle6').enabled(true))
    let calendarPickerTextStyle7: Component =
      await driver.findComponent(Matcher.create().id('calendarPickerTextStyle7').enabled(true))
    let calendarPickerTextStyle8: Component =
      await driver.findComponent(Matcher.create().id('calendarPickerTextStyle8').enabled(true))
    let calendarPickerTextStyle9: Component =
      await driver.findComponent(Matcher.create().id('calendarPickerTextStyle9').enabled(true))
    let calendarPickerTextStyle10: Component =
      await driver.findComponent(Matcher.create().id('calendarPickerTextStyle10').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('CalendarPickerTextStyle1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('CalendarPickerTextStyle2').enabled(true))

    let textStyle1: string = await calendarPickerTextStyle1.getInspectorInfo()
    assertEqual(JSON.parse(textStyle1)
      .$attrs
      .textStyle
      .color
      .toLowerCase(), Color.Black)

    let textStyle2: string = await calendarPickerTextStyle2.getInspectorInfo()
    assertEqual(JSON.parse(textStyle2).$attrs.textStyle.color, '#FFA52A2A')

    let textStyle3: string = await calendarPickerTextStyle3.getInspectorInfo()
    assertEqual(JSON.parse(textStyle3).$attrs.textStyle.color, '#FF8EFF65')

    let textStyle4: string = await calendarPickerTextStyle4.getInspectorInfo()
    assertEqual(JSON.parse(textStyle4)
      .$attrs
      .textStyle
      .font
      .weight, 'FontWeight.Lighter')

    let textStyle5: string = await calendarPickerTextStyle5.getInspectorInfo()
    assertEqual(JSON.parse(textStyle5)
      .$attrs
      .textStyle
      .font
      .weight, 'FontWeight.Normal')

    let textStyle6: string = await calendarPickerTextStyle6.getInspectorInfo()
    assertEqual(JSON.parse(textStyle6)
      .$attrs
      .textStyle
      .font
      .weight, 'FontWeight.Regular')

    let textStyle7: string = await calendarPickerTextStyle7.getInspectorInfo()
    assertEqual(JSON.parse(textStyle7)
      .$attrs
      .textStyle
      .font
      .weight, 'FontWeight.Medium')

    let textStyle8: string = await calendarPickerTextStyle8.getInspectorInfo()
    assertEqual(JSON.parse(textStyle8)
      .$attrs
      .textStyle
      .font
      .weight, 'FontWeight.Bold')

    let textStyle9: string = await calendarPickerTextStyle9.getInspectorInfo()
    assertEqual(JSON.parse(textStyle9)
      .$attrs
      .textStyle
      .font
      .weight, 'FontWeight.Bolder')
    assertEqual(JSON.parse(textStyle9)
      .$attrs
      .textStyle
      .font
      .size, '10.00px')
    assertEqual(JSON.parse(textStyle9)
      .$attrs
      .textStyle
      .font
      .family, 'Arial')

    let textStyle10: string = await calendarPickerTextStyle10.getInspectorInfo()
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
    let textStyle11: string = await calendarPickerTextStyle3.getInspectorInfo()
    assertEqual(JSON.parse(textStyle11).$attrs.textStyle.color, $r('sys.color.ohos_fa_palette1'))

    await button2.tap()
    let textStyle12: string = await calendarPickerTextStyle10.getInspectorInfo()
    assertEqual(JSON.parse(textStyle12)
      .$attrs
      .textStyle
      .font
      .weight, '100')
    assertEqual(JSON.parse(textStyle12)
      .$attrs
      .textStyle
      .font
      .size, '100')
    assertEqual(JSON.parse(textStyle12)
      .$attrs
      .textStyle
      .font
      .style, 'FontStyle.Italic')
  }, 0)
}