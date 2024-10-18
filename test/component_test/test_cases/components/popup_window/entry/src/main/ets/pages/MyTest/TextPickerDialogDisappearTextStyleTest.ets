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

export default async function textPickerDialogDisappearTextStyleTest() {
  /*
   * TextPickerDialog组件 DisappearTextStyle对象
   * 找到画面文本为TextPickerDialogBackgroundBlurStyle1,TextPickerDialogBackgroundBlurStyle2,TextPickerDialogBackgroundBlurStyle3,ClickToggleWeight的Button组件
   * 点击Button1改变DisappearTextStyle对象color属性为Color.Red,
   * 改变DisappearTextStyle对象size属性为30,
   * 改变DisappearTextStyle对象weight属性为100
   * 找到可以滚动的TextPickerDialog组件
   * 获取disappearTextStyle1的DisappearTextStyle对象color属性与期待值Color.Red比对
   * 获取disappearTextStyle1的DisappearTextStyle对象size属性与期待值30比对
   * 获取disappearTextStyle1的DisappearTextStyle对象weight属性与期待值100比对
   * 点击屏幕坐标(100，100)
   * 点击Button4改变DisappearTextStyle对象color属性为0x0000ff,
   * 点击Button2弹出窗口
   * 改变DisappearTextStyle对象size属性为'30',
   * 改变DisappearTextStyle对象weight属性为FontWeight.Lighter
   * 找到可以滚动的TextPickerDialog组件
   * 获取disappearTextStyle2的DisappearTextStyle对象color属性与期待值0x0000ff比对
   * 获取disappearTextStyle2的DisappearTextStyle对象size属性与期待值'30'比对
   * 获取disappearTextStyle2的DisappearTextStyle对象weight属性与期待值FontWeight.Lighter比对
   * 点击屏幕坐标(100，100)
   * 点击Button4改变DisappearTextStyle对象weight属性为FontWeight.Normal
   * 点击Button2弹出窗口
   * 找到可以滚动的TextPickerDialog组件
   * 获取disappearTextStyle3的DisappearTextStyle对象weight属性与期待值FontWeight.Normal比对
   * 点击屏幕坐标(100，100)
   * 点击Button4改变DisappearTextStyle对象weight属性为FontWeight.Regular
   * 点击Button2弹出窗口
   * 找到可以滚动的TextPickerDialog组件
   * 获取disappearTextStyle4的DisappearTextStyle对象weight属性与期待值FontWeight.Regular比对
   * 点击屏幕坐标(100，100)
   * 点击Button4改变DisappearTextStyle对象weight属性为FontWeight.Medium
   * 点击Button2弹出窗口
   * 找到可以滚动的TextPickerDialog组件
   * 获取disappearTextStyle5的DisappearTextStyle对象weight属性与期待值FontWeight.Medium比对
   * 点击屏幕坐标(100，100)
   * 点击Button4改变DisappearTextStyle对象weight属性为FontWeight.Bold
   * 点击Button2弹出窗口
   * 找到可以滚动的TextPickerDialog组件
   * 获取disappearTextStyle6的DisappearTextStyle对象weight属性与期待值FontWeight.Bold比对
   * 点击屏幕坐标(100，100)
   * 点击Button4改变DisappearTextStyle对象weight属性为FontWeight.Bolder
   * 点击Button2弹出窗口
   * 找到可以滚动的TextPickerDialog组件
   * 获取disappearTextStyle7的DisappearTextStyle对象weight属性与期待值FontWeight.Bolder比对
   * 点击屏幕坐标(100，100)
   * 点击Button3改变DisappearTextStyle对象color属性为$r('app.color.color_red'),
   * 改变DisappearTextStyle对象size属性为$r('app.integer.font_size'),
   * 改变DisappearTextStyle对象weight属性为'800'
   * 找到可以滚动的TextPickerDialog组件
   * 获取disappearTextStyle8的DisappearTextStyle对象color属性与期待值$r('app.color.color_red')比对
   * 获取disappearTextStyle8的DisappearTextStyle对象size属性与期待值$r('app.integer.font_size')比对
   * 获取disappearTextStyle8的DisappearTextStyle对象weight属性与期待值'800'比对
   * 点击屏幕坐标(100，100)
   */
  defineTest('textPickerDialogDisappearTextStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textPickerDialogDisappearTextStyleTestDemo running")
    let driver: Tester = Tester.create()

    let button1: Component =
      await driver.findComponent(Matcher.create().text('TextPickerDialogDisappearTextStyle1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('TextPickerDialogDisappearTextStyle1').enabled(true))
    let button3: Component =
      await driver.findComponent(Matcher.create().text('TextPickerDialogDisappearTextStyle1').enabled(true))
    let button4: Component =
      await driver.findComponent(Matcher.create().text('ClickToggleWeight').enabled(true))

    await button1.tap()
    let textDisappearTextStyle1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let disappearTextStyle1: string = await textDisappearTextStyle1.getInspectorInfo()
    assertFalse(JSON.parse(disappearTextStyle1).$attrs.disappearTextStyle == undefined)
    assertEqual(JSON.parse(disappearTextStyle1).$attrs.disappearTextStyle.color, Color.Red)
    assertEqual(JSON.parse(disappearTextStyle1)
      .$attrs
      .disappearTextStyle
      .font
      .size, 30)
    assertEqual(JSON.parse(disappearTextStyle1)
      .$attrs
      .disappearTextStyle
      .font
      .weight, 100)
    await driver.tap(100, 100)

    await button4.tap()
    await button2.tap()
    let textDisappearTextStyle2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let disappearTextStyle2: string = await textDisappearTextStyle2.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle2).$attrs.selectedTextStyle.color, 0x0000ff)
    assertEqual(JSON.parse(disappearTextStyle2)
      .$attrs
      .selectedTextStyle
      .font
      .size, '30')
    assertEqual(JSON.parse(disappearTextStyle2)
      .$attrs
      .selectedTextStyle
      .font
      .weight, FontWeight.Lighter)
    await driver.tap(100, 100)

    await button4.tap()
    await button2.tap()
    let textDisappearTextStyle3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let disappearTextStyle3: string = await textDisappearTextStyle3.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle3)
      .$attrs
      .selectedTextStyle
      .font
      .weight, FontWeight.Normal)
    await driver.tap(100, 100)

    await button4.tap()
    await button2.tap()
    let textDisappearTextStyle4: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let disappearTextStyle4: string = await textDisappearTextStyle4.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle4)
      .$attrs
      .selectedTextStyle
      .font
      .weight, FontWeight.Regular)
    await driver.tap(100, 100)

    await button4.tap()
    await button2.tap()
    let textDisappearTextStyle5: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let disappearTextStyle5: string = await textDisappearTextStyle5.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle5)
      .$attrs
      .selectedTextStyle
      .font
      .weight, FontWeight.Medium)
    await driver.tap(100, 100)

    await button4.tap()
    await button2.tap()
    let textDisappearTextStyle6: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let disappearTextStyle6: string = await textDisappearTextStyle6.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle6)
      .$attrs
      .selectedTextStyle
      .font
      .weight, FontWeight.Bold)
    await driver.tap(100, 100)

    await button4.tap()
    await button2.tap()
    let textDisappearTextStyle7: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let disappearTextStyle7: string = await textDisappearTextStyle7.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle7)
      .$attrs
      .selectedTextStyle
      .font
      .weight, FontWeight.Bolder)
    await driver.tap(100, 100)

    await button3.tap()
    let textDisappearTextStyle8: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let disappearTextStyle8: string = await textDisappearTextStyle8.getInspectorInfo()
    assertEqual(JSON.parse(disappearTextStyle8).$attrs.selectedTextStyle.color, $r('app.color.color_red'))
    assertEqual(JSON.parse(disappearTextStyle8)
      .$attrs
      .selectedTextStyle
      .font
      .size, $r('app.integer.font_size'))
    assertEqual(JSON.parse(disappearTextStyle8)
      .$attrs
      .selectedTextStyle
      .font
      .weight, '800')
    await driver.tap(100, 100)
  }, 0)
}