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
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function alertDialogSecondaryButtonTest() {
  /*
* AlertDialog组件 secondaryButton对象
* 找到画面id为alertDialogSecondary的Text组件
* 找到画面文本为AlertDialogSecondaryButton1、AlertDialogSecondaryButton2、AlertDialogSecondaryButton3、alertDialogPrimary的Button组件
* 点击button1
* 获取画面文本为title的AlertDialog组件和画面文本为button1的Button组件
* 获取secondaryButton1的secondaryButton.style对象与期待值DialogButtonStyle.HIGHLIGHT比对
* 获取secondaryButton1的secondaryButton.enabled对象与期待值true比对
* 获取secondaryButton1的secondaryButton.defaultFocus对象与期待值false比对
* 获取secondaryButton1的secondaryButton.value对象与期待值button1比对
* 获取secondaryButton1的secondaryButton.fontColor对象与期待值Color.Green比对
* 获取secondaryButton1的secondaryButton.backgroundColor对象与期待值Color.Brown比对
* 点击button2
* 获取text的content值与dialogOne比对
* 点击button3后点击button1
* 获取画面文本为title的AlertDialog组件和画面文本为button1的Button组件
* 获取secondaryButton2的secondaryButton.fontColor对象与期待值$r('app.color.alert_color1')比对
* 获取secondaryButton2的secondaryButton.backgroundColor对象与期待值$r('app.color.alert_color2')比对
* 点击button4
* 点击button5后点击button1
* 获取画面文本为title的AlertDialog组件和画面文本为button1的Button组件
* 获取secondaryButton3的secondaryButton.fontColor对象与期待值'#1A94C2'比对
* 获取secondaryButton3的secondaryButton.backgroundColor对象与期待值'#C025BE'比对
* 点击button6
* 点击button7后点击button1
* 获取画面文本为title的AlertDialog组件和画面文本为alertDialog的Button组件
* 获取secondaryButton4的secondaryButton.fontColor对象与期待值0xff8207比对
* 获取secondaryButton4的secondaryButton.value对象与期待值'alertDialog'比对
* 获取secondaryButton4的secondaryButton.backgroundColor对象与期待值0xff1234比对
* 获取secondaryButton4的secondaryButton.style对象与期待值DialogButtonStyle.DEFAULT比对
* 获取secondaryButton4的secondaryButton.enabled对象与期待值false比对
* 获取secondaryButton4的secondaryButton.defaultFocus对象与期待值true比对
* 点击button8后点击屏幕坐标为(100,100)的位置
*/
  defineTest('alertDialogSecondaryButtonTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("alertDialogSecondaryButtonTestDemo running")
    let driver: Tester = Tester.create()
    let text: Component = await driver.findComponent(Matcher.create().id('alertDialogSecondary').enabled(true))

    let button1: Component = await driver.findComponent(Matcher.create().text('AlertDialog').enabled(true))
    await button1.tap()

    let alertDialog1: Component = await driver.findComponent(Matcher.create().type('AlertDialog').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('button1').enabled(true))
    let secondaryButton1: string = await alertDialog1.getInspectorInfo()
    assertFalse(JSON.parse(secondaryButton1).$attrs.secondaryButton == undefined)
    assertEqual(JSON.parse(secondaryButton1).$attrs.secondaryButton.style, DialogButtonStyle.HIGHLIGHT)
    assertTrue(JSON.parse(secondaryButton1).$attrs.secondaryButton.enabled)
    assertFalse(JSON.parse(secondaryButton1).$attrs.secondaryButton.defaultFocus)
    assertEqual(JSON.parse(secondaryButton1).$attrs.secondaryButton.value, 'button1')
    assertEqual(JSON.parse(secondaryButton1).$attrs.secondaryButton.fontColor, Color.Green)
    assertEqual(JSON.parse(secondaryButton1).$attrs.secondaryButton.backgroundColor, Color.Brown)
    await button2.tap()
    let value: string = await text.getInspectorInfo()
    assertEqual(JSON.parse(value).$attrs.content, 'dialogOne')

    let button3: Component =
      await driver.findComponent(Matcher.create().text('AlertDialogSecondaryButton1').enabled(true))
    await button3.tap()
    await button1.tap()
    let alertDialog2: Component = await driver.findComponent(Matcher.create().text('title').enabled(true))
    let button4: Component = await driver.findComponent(Matcher.create().text('button1').enabled(true))
    let secondaryButton2: string = await alertDialog2.getInspectorInfo()
    assertEqual(JSON.parse(secondaryButton2).$attrs.secondaryButton.fontColor, $r('app.color.alert_color1'))
    assertEqual(JSON.parse(secondaryButton2).$attrs.secondaryButton.backGroundColor, $r('app.color.alert_color2'))
    await button4.tap()

    let button5: Component =
      await driver.findComponent(Matcher.create().text('AlertDialogSecondaryButton2').enabled(true))
    await button5.tap()
    await button1.tap()
    let alertDialog3: Component = await driver.findComponent(Matcher.create().text('title').enabled(true))
    let button6: Component = await driver.findComponent(Matcher.create().text('button1').enabled(true))
    let secondaryButton3: string = await alertDialog3.getInspectorInfo()
    assertEqual(JSON.parse(secondaryButton3).$attrs.secondaryButton.fontColor, '#1A94C2')
    assertEqual(JSON.parse(secondaryButton3).$attrs.secondaryButton.backGroundColor, '#C025BE')
    await button6.tap()

    let button7: Component =
      await driver.findComponent(Matcher.create().text('AlertDialogSecondaryButton3').enabled(true))
    await button7.tap()
    await button1.tap()
    let alertDialog4: Component = await driver.findComponent(Matcher.create().text('title').enabled(true))
    let button8: Component = await driver.findComponent(Matcher.create().text('alertDialog').enabled(true))
    let secondaryButton4: string = await alertDialog4.getInspectorInfo()
    assertEqual(JSON.parse(secondaryButton4).$attrs.secondaryButton.fontColor, 0xff8207)
    assertEqual(JSON.parse(secondaryButton4).$attrs.secondaryButton.value, 'alertDialog')
    assertEqual(JSON.parse(secondaryButton4).$attrs.secondaryButton.backGroundColor, 0xff1234)
    assertEqual(JSON.parse(secondaryButton4).$attrs.secondaryButton.style, DialogButtonStyle.DEFAULT)
    assertFalse(JSON.parse(secondaryButton4).$attrs.secondaryButton.enabled)
    assertTrue(JSON.parse(secondaryButton4).$attrs.secondaryButton.defaultFocus)
    await button8.tap()
    await driver.tap(100, 100)
  }, 0)
}