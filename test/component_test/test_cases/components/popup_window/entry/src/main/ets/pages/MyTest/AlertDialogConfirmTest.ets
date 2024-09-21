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

export default async function alertDialogConfirmTest() {
  /*
* AlertDialog组件 Confirm对象
* 找到画面id为alertDialogConfirm的Text组件
* 找到画面文本为AlertDialogConfirm1、AlertDialogConfirm2、AlertDialogConfirm3、AlertDialog的Button组件
* 点击button1
* 获取画面文本为title的AlertDialog组件和画面文本为button1的Button组件
* 获取confirm1的confirm.style对象与期待值DialogButtonStyle.HIGHLIGHT比对
* 获取confirm1的confirm.enabled对象与期待值true比对
* 获取confirm1的confirm.defaultFocus对象与期待值false比对
* 获取confirm1的confirm.value对象与期待值button1比对
* 获取confirm1的confirm.fontColor对象与期待值Color.Green比对
* 获取confirm1的confirm.backgroundColor对象与期待值Color.Brown比对
* 点击button2
* 获取text的content值与dialogOne比对
* 点击button3后点击button1
* 获取画面文本为title的AlertDialog组件和画面文本为button1的Button组件
* 获取confirm2的confirm.fontColor对象与期待值$r('app.color.alert_color1')比对
* 获取confirm2的confirm.backgroundColor对象与期待值$r('app.color.alert_color2')比对
* 点击button4
* 点击button5后点击button1
* 获取画面文本为title的AlertDialog组件和画面文本为button1的Button组件
* 获取confirm3的confirm.fontColor对象与期待值'#1A94C2'比对
* 获取confirm3的confirm.backgroundColor对象与期待值'#C025BE'比对
* 点击button6
* 点击button7后点击button1
* 获取画面文本为title的AlertDialog组件和画面文本为alertDialog的Button组件
* 获取confirm4的confirm.fontColor对象与期待值0xff8207比对
* 获取confirm4的confirm.value对象与期待值'alertDialog'比对
* 获取confirm4的confirm.backgroundColor对象与期待值0xff1234比对
* 获取confirm4的confirm.style对象与期待值DialogButtonStyle.DEFAULT比对
* 获取confirm4的confirm.enabled对象与期待值false比对
* 获取confirm4的confirm.defaultFocus对象与期待值true比对
* 点击button8后点击屏幕坐标为(100,100)的位置
*/
  defineTest('alertDialogConfirmTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("alertDialogConfirmTestDemo running")
    let driver: Tester = Tester.create()
    let text: Component = await driver.findComponent(Matcher.create().id('alertDialogConfirm').enabled(true))

    let button1: Component = await driver.findComponent(Matcher.create().text('AlertDialog').enabled(true))
    await button1.tap()
    let alertDialog1: Component = await driver.findComponent(Matcher.create().type('AlertDialog').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('button1').enabled(true))
    let confirm1: string = await alertDialog1.getInspectorInfo()
    assertFalse(JSON.parse(confirm1).$attrs.confirm == undefined)
    assertEqual(JSON.parse(confirm1).$attrs.confirm.style, DialogButtonStyle.HIGHLIGHT)
    assertTrue(JSON.parse(confirm1).$attrs.confirm.enabled)
    assertFalse(JSON.parse(confirm1).$attrs.confirm.defaultFocus)
    assertEqual(JSON.parse(confirm1).$attrs.confirm.value, 'button1')
    assertEqual(JSON.parse(confirm1).$attrs.confirm.fontColor, Color.Green)
    assertEqual(JSON.parse(confirm1).$attrs.confirm.backgroundColor, Color.Brown)
    await button2.tap()
    let value: string = await text.getInspectorInfo()
    assertEqual(JSON.parse(value).$attrs.content, 'dialogOne')

    let button3: Component = await driver.findComponent(Matcher.create().text('AlertDialogConfirm1').enabled(true))
    await button3.tap()
    await button1.tap()
    let alertDialog2: Component = await driver.findComponent(Matcher.create().text('title').enabled(true))
    let button4: Component = await driver.findComponent(Matcher.create().text('button1').enabled(true))
    let confirm2: string = await alertDialog2.getInspectorInfo()
    assertEqual(JSON.parse(confirm2).$attrs.confirm.fontColor, $r('app.color.alert_color1'))
    assertEqual(JSON.parse(confirm2).$attrs.confirm.backGroundColor, $r('app.color.alert_color2'))
    await button4.tap()

    let button5: Component = await driver.findComponent(Matcher.create().text('AlertDialogConfirm2').enabled(true))
    await button5.tap()
    await button1.tap()
    let alertDialog3: Component = await driver.findComponent(Matcher.create().text('title').enabled(true))
    let button6: Component = await driver.findComponent(Matcher.create().text('button1').enabled(true))
    let confirm3: string = await alertDialog3.getInspectorInfo()
    assertEqual(JSON.parse(confirm3).$attrs.confirm.fontColor, '#1A94C2')
    assertEqual(JSON.parse(confirm3).$attrs.confirm.backGroundColor, '#C025BE')
    await button6.tap()

    let button7: Component = await driver.findComponent(Matcher.create().text('AlertDialogConfirm3').enabled(true))
    await button7.tap()
    await button1.tap()
    let alertDialog4: Component = await driver.findComponent(Matcher.create().text('title').enabled(true))
    let button8: Component = await driver.findComponent(Matcher.create().text('alertDialog').enabled(true))
    let confirm4: string = await alertDialog4.getInspectorInfo()
    assertEqual(JSON.parse(confirm4).$attrs.confirm.fontColor, 0xff8207)
    assertEqual(JSON.parse(confirm4).$attrs.confirm.value, 'alertDialog')
    assertEqual(JSON.parse(confirm4).$attrs.confirm.backGroundColor, 0xff1234)
    assertEqual(JSON.parse(confirm4).$attrs.confirm.style, DialogButtonStyle.DEFAULT)
    assertFalse(JSON.parse(confirm4).$attrs.confirm.enabled)
    assertTrue(JSON.parse(confirm4).$attrs.confirm.defaultFocus)
    await button8.tap()
    await driver.tap(100, 100)
  }, 0)
}