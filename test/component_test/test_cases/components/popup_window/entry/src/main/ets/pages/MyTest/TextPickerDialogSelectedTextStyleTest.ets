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
} from '@ohos.arkui.componentTest';

export default async function textPickerDialogSelectedTextStyleTest() {
  /*
    * TextPickerDialog组件 SelectedTextStyle对象
    * 找到画面文本为TextPickerDialogBackgroundBlurStyle1,TextPickerDialogBackgroundBlurStyle2,TextPickerDialogBackgroundBlurStyle3,ClickToggleWeight的Button组件
    * 点击Button1改变SelectedTextStyle对象color属性为Color.Red,
    * 改变SelectedTextStyle对象size属性为30,
    * 改变SelectedTextStyle对象weight属性为100
    * 找到可以滚动的TextPickerDialog组件
    * 获取selectedTextStyle1的SelectedTextStyle对象color属性与期待值Color.Red比对
    * 获取selectedTextStyle1的SelectedTextStyle对象size属性与期待值30比对
    * 获取selectedTextStyle1的SelectedTextStyle对象weight属性与期待值100比对
    * 点击屏幕坐标(100，100)
    * 点击Button4改变SelectedTextStyle对象color属性为0x0000ff,
    * 改变SelectedTextStyle对象size属性为'30',
    * 改变SelectedTextStyle对象weight属性为FontWeight.Lighter
    * 点击Button2弹出弹窗
    * 找到可以滚动的TextPickerDialog组件
    * 获取selectedTextStyle2的SelectedTextStyle对象color属性与期待值0x0000ff比对
    * 获取selectedTextStyle2的SelectedTextStyle对象size属性与期待值'30'比对
    * 获取selectedTextStyle2的SelectedTextStyle对象weight属性与期待值FontWeight.Lighter比对
    * 点击屏幕坐标(100，100)
    * 点击Button4改变SelectedTextStyle对象weight属性为FontWeight.Normal
    * 点击Button2弹出弹窗
    * 找到可以滚动的TextPickerDialog组件
    * 获取selectedTextStyle3的SelectedTextStyle对象weight属性与期待值FontWeight.Normal比对
    * 点击屏幕坐标(100，100)
    * 点击Button4改变SelectedTextStyle对象weight属性为FontWeight.Regular
    * 点击Button2弹出弹窗
    * 找到可以滚动的TextPickerDialog组件
    * 获取selectedTextStyle4的SelectedTextStyle对象weight属性与期待值FontWeight.Regular比对
    * 点击屏幕坐标(100，100)
    * 点击Button4改变SelectedTextStyle对象weight属性为FontWeight.Medium
    * 点击Button2弹出弹窗
    * 找到可以滚动的TextPickerDialog组件
    * 获取selectedTextStyle5的SelectedTextStyle对象weight属性与期待值FontWeight.Medium比对
    * 点击屏幕坐标(100，100)
    * 点击Button4改变SelectedTextStyle对象weight属性为FontWeight.Bold
    * 点击Button2弹出弹窗
    * 找到可以滚动的TextPickerDialog组件
    * 获取selectedTextStyle6的SelectedTextStyle对象weight属性与期待值FontWeight.Bold比对
    * 点击屏幕坐标(100，100)
    * 点击Button4改变SelectedTextStyle对象weight属性为FontWeight.Bolder
    * 点击Button2弹出弹窗
    * 找到可以滚动的TextPickerDialog组件
    * 获取selectedTextStyle7的SelectedTextStyle对象weight属性与期待值FontWeight.Bolder比对
    * 点击屏幕坐标(100，100)
    * 点击Button3改变SelectedTextStyle对象color属性为$r('app.color.color_red'),
    * 改变SelectedTextStyle对象size属性为$r('app.integer.font_size'),
    * 改变SelectedTextStyle对象weight属性为'800'
    * 找到可以滚动的TextPickerDialog组件
    * 获取selectedTextStyle8的SelectedTextStyle对象color属性与期待值$r('app.color.color_red')比对
    * 获取selectedTextStyle8的SelectedTextStyle对象size属性与期待值$r('app.integer.font_size')比对
    * 获取selectedTextStyle8的SelectedTextStyle对象weight属性与期待值'800'比对
    * 点击屏幕坐标(100，100)
    */
  defineTest('textPickerDialogSelectedTextStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textPickerDialogSelectedTextStyleTestDemo running")
    let driver: Tester = Tester.create()

    let button1: Component =
      await driver.findComponent(Matcher.create().text('TextPickerDialogSelectedTextStyle1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('TextPickerDialogSelectedTextStyle2').enabled(true))
    let button3: Component =
      await driver.findComponent(Matcher.create().text('TextPickerDialogSelectedTextStyle3').enabled(true))
    let button4: Component =
      await driver.findComponent(Matcher.create().text('ClickToggleWeight').enabled(true))

    await button1.tap()
    let textSelectedTextStyle1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let selectedTextStyle1: string = await textSelectedTextStyle1.getInspectorInfo()
    assertFalse(JSON.parse(selectedTextStyle1).$attrs.selectedTextStyle == undefined)
    assertEqual(JSON.parse(selectedTextStyle1).$attrs.selectedTextStyle.color, Color.Red)
    assertEqual(JSON.parse(selectedTextStyle1)
      .$attrs
      .selectedTextStyle
      .font
      .size, 30)
    assertEqual(JSON.parse(selectedTextStyle1)
      .$attrs
      .selectedTextStyle
      .font
      .weight, 100)
    await driver.tap(100, 100)

    await button4.tap()
    await button2.tap()
    let textSelectedTextStyle2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let selectedTextStyle2: string = await textSelectedTextStyle2.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle2).$attrs.selectedTextStyle.color, 0x0000ff)
    assertEqual(JSON.parse(selectedTextStyle2)
      .$attrs
      .selectedTextStyle
      .font
      .size, '30')
    assertEqual(JSON.parse(selectedTextStyle2)
      .$attrs
      .selectedTextStyle
      .font
      .weight, FontWeight.Lighter)
    await driver.tap(100, 100)

    await button4.tap()
    await button2.tap()
    let textSelectedTextStyle3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let selectedTextStyle3: string = await textSelectedTextStyle3.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle3)
      .$attrs
      .selectedTextStyle
      .font
      .weight, FontWeight.Normal)
    await driver.tap(100, 100)

    await button4.tap()
    await button2.tap()
    let textSelectedTextStyle4: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let selectedTextStyle4: string = await textSelectedTextStyle4.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle4)
      .$attrs
      .selectedTextStyle
      .font
      .weight, FontWeight.Regular)
    await driver.tap(100, 100)

    await button4.tap()
    await button2.tap()
    let textSelectedTextStyle5: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let selectedTextStyle5: string = await textSelectedTextStyle5.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle5)
      .$attrs
      .selectedTextStyle
      .font
      .weight, FontWeight.Medium)
    await driver.tap(100, 100)

    await button4.tap()
    await button2.tap()
    let textSelectedTextStyle6: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let selectedTextStyle6: string = await textSelectedTextStyle6.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle6)
      .$attrs
      .selectedTextStyle
      .font
      .weight, FontWeight.Bold)
    await driver.tap(100, 100)

    await button4.tap()
    await button2.tap()
    let textSelectedTextStyle7: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let selectedTextStyle7: string = await textSelectedTextStyle7.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle7)
      .$attrs
      .selectedTextStyle
      .font
      .weight, FontWeight.Bolder)
    await driver.tap(100, 100)

    await button3.tap()
    let textSelectedTextStyle8: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let selectedTextStyle8: string = await textSelectedTextStyle8.getInspectorInfo()
    assertEqual(JSON.parse(selectedTextStyle8).$attrs.selectedTextStyle.color, $r('app.color.color_red'))
    assertEqual(JSON.parse(selectedTextStyle8)
      .$attrs
      .selectedTextStyle
      .font
      .size, $r('app.integer.font_size'))
    assertEqual(JSON.parse(selectedTextStyle8)
      .$attrs
      .selectedTextStyle
      .font
      .weight, '800')
    await driver.tap(100, 100)
  }, 0)
}