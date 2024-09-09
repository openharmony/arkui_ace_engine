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
} from '@ohos.arkui.componentTest';

export default async function alertDialogButtonsTest() {
  /*
   * AlertDialog弹窗 Buttons对象说明
   * 找到画面text为button end的文本
   * 找到画面文本为One Button Dialog的Button组件
   * 点击button1，弹出text为'按钮1'的AlertDialogButtons1按钮的AlertDialog弹窗
   * 获取AlertDialogButtons1属性与期待值{'按钮1'，DialogButtonStyle.DEFAULT，Color.Green，Color.Gray}比对
   * 点击AlertDialogButtons1按钮退出
   * 变更text的文本为button1 ending,如发生文本改变，则视为发生回调
   * 点击button1，弹出text为'按钮2'的AlertDialogButtons2的AlertDialog弹窗
   * 获取AlertDialogButtons2属性与期待值{$r('app.string.alert_dialog_buttons_value')，0x8B008B，0xFFE4C4}比对
   * 点击AlertDialogButtons2按钮退出
   * 变更text的文本为button2 ending,如发生文本改变，则视为发生回调
   * 点击button1，弹出text为'按钮3'的AlertDialogButtons3的AlertDialog弹窗
   * 获取AlertDialogButtons3属性与期待值{true，true, DialogButtonStyle.HIGHLIGHT,'rgb(255,105,180)'，$r('sys.color.ohos_id_color_text_hyperlink')}比对
   * 点击AlertDialogButtons3按钮退出
   * 变更text的文本为button3 ending,如发生文本改变，则视为发生回调
   * 点击button1，弹出text为'按钮4'的AlertDialogButtons4的AlertDialog弹窗
   * 获取AlertDialogButtons4属性与期待值{false，false, $r('sys.color.ohos_id_color_text_hyperlink'),'rgb(255,240,245)'}比对
   * 点击AlertDialogButtons4按钮退出
   * 变更text的文本为button4 ending,如发生文本改变，则视为发生回调
   */
  defineTest('alertDialogButtonsTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("alertDialogButtonsTestDemo running")
    let driver: Tester = Tester.create()
    let button1: Component = await driver.findComponent(Matcher.create().text('One Button Dialog').enabled(true))
    let text: Component = await driver.findComponent(Matcher.create().text('button end').enabled(true))

    await button1.tap()
    let alertDialogButtons1: Component = await driver.findComponent(Matcher.create().type('AlertDialog').enabled(true))
    let buttons1: string = await alertDialogButtons1.getInspectorInfo()
    assertFalse(JSON.parse(buttons1).$attrs.buttons == undefined)
    assertEqual(JSON.parse(buttons1).$attrs.buttons.value, '按钮1')
    assertEqual(JSON.parse(buttons1).$attrs.buttons.style, DialogButtonStyle.DEFAULT)
    assertEqual(JSON.parse(buttons1).$attrs.buttons.fontColor, Color.Green)
    assertEqual(JSON.parse(buttons1).$attrs.buttons.backgroundColor, Color.Gray)
    await alertDialogButtons1.tap()
    let content1: string = await text.getInspectorInfo()
    assertEqual(JSON.parse(content1).$attrs.content, 'button1 ending')

    await button1.tap()
    let alertDialogButtons2: Component = await driver.findComponent(Matcher.create().text('按钮2').enabled(true))
    let buttons2: string = await alertDialogButtons2.getInspectorInfo()
    assertEqual(JSON.parse(buttons2).$attrs.buttons.value, $r('app.string.alert_dialog_buttons_value'))
    assertEqual(JSON.parse(buttons2).$attrs.buttons.fontColor, 0x8B008B)
    assertEqual(JSON.parse(buttons2).$attrs.buttons.backgroundColor, 0xFFE4C4)
    await alertDialogButtons2.tap()
    let content2: string = await text.getInspectorInfo()
    assertEqual(JSON.parse(content2).$attrs.content, 'button2 ending')

    await button1.tap()
    let alertDialogButtons3: Component = await driver.findComponent(Matcher.create().text('按钮3').enabled(true))
    let buttons3: string = await alertDialogButtons3.getInspectorInfo()
    assertTrue(JSON.parse(buttons3).$attrs.buttons.enable)
    assertTrue(JSON.parse(buttons3).$attrs.buttons.defaultFocus)
    assertEqual(JSON.parse(buttons3).$attrs.buttons.style, DialogButtonStyle.HIGHLIGHT)
    assertEqual(JSON.parse(buttons3).$attrs.buttons.fontColor, 'rgb(255,105,180)')
    assertEqual(JSON.parse(buttons3).$attrs.buttons.backgroundColor, $r('sys.color.ohos_id_color_text_hyperlink'))
    await alertDialogButtons3.tap()
    let content3: string = await text.getInspectorInfo()
    assertEqual(JSON.parse(content3).$attrs.content, 'button3 ending')

    await button1.tap()
    let alertDialogButtons4: Component = await driver.findComponent(Matcher.create().text('按钮4').enabled(true))
    let buttons4: string = await alertDialogButtons4.getInspectorInfo()
    assertFalse(JSON.parse(buttons4).$attrs.buttons.enable)
    assertFalse(JSON.parse(buttons4).$attrs.buttons.defaultFocus)
    assertEqual(JSON.parse(buttons4).$attrs.buttons.fontColor, $r('sys.color.ohos_id_color_text_hyperlink'))
    assertEqual(JSON.parse(buttons4).$attrs.buttons.backgroundColor, 'rgb(255,240,245)')
    await alertDialogButtons4.tap()
    let content4: string = await text.getInspectorInfo()
    assertEqual(JSON.parse(content4).$attrs.content, 'button4 ending')
  }, 0)
}