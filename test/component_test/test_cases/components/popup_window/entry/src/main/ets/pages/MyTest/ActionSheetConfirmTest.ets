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

export default async function actionSheetConfirmTest() {
  /*
* ActionSheet,Text组件 Confirm对象
* 找到画面id为actionSheetConfirm的ActionSheet组件
* 找到画面文本为ActionSheetConfirm的Button组件
* 获取actionSheetConfirm的Confirm对象与期待值{ enabled: true,defaultFocus: true,style:DialogButtonStyle.DEFAULT,value: $r('app.string.actionSheet_confirm_value'),action: () => {this.String1 = 'Confirm_Button1'}比对
* 点击button，变更actionSheetConfirm的Confirm的对象值{ enabled: false,defaultFocus:false,style:DialogButtonStyle.HIGHLIGHT,value: 'Confirm_String'}
* 获取actionSheetConfirm的Confirm对象与期待值{ enabled:false,defaultFocus: false,style:DialogButtonStyle.HIGHLIGHT,value: 'Confirm_String'}比对
*/
  defineTest('actionSheetConfirmTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('actionSheetConfirmTestDemo running')
    let driver: Tester = Tester.create()
    let text1: Component = await driver.findComponent(Matcher.create().text('Confirm_Button').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ActionSheetConfirmTest1').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ActionSheetConfirm').enabled(true))

    await button1.tap()
    let actionSheetConfirm1: Component = await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('Confirm_Resource').enabled(true))
    let confirm1: string = await actionSheetConfirm1.getInspectorInfo()
    let content1: string = await text1.getInspectorInfo()
    assertFalse(JSON.parse(confirm1).$attrs.confirm == undefined)
    assertTrue(JSON.parse(confirm1).$attrs.confirm.enabled)
    assertTrue(JSON.parse(confirm1).$attrs.confirm.defaultFocus)
    assertEqual(JSON.parse(confirm1).$attrs.confirm, DialogButtonStyle.DEFAULT)
    assertEqual(JSON.parse(confirm1).$attrs.confirm.value, $r('app.string.actionSheet_confirm_value'))
    assertEqual(JSON.parse(content1).$attrs.content, 'Confirm_Button')
    await button2.tap()
    let content2: string = await text1.getInspectorInfo()
    assertEqual(JSON.parse(content2).$attrs.content, 'Confirm_Button1')

    await button.tap()
    await button1.tap()
    let actionSheetConfirm2: Component = await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let confirm2: string = await actionSheetConfirm2.getInspectorInfo()
    assertFalse(JSON.parse(confirm2).$attrs.confirm.enabled)
    assertFalse(JSON.parse(confirm2).$attrs.confirm.defaultFocus)
    assertEqual(JSON.parse(confirm2).$attrs.confirm.style, DialogButtonStyle.HIGHLIGHT)
    assertEqual(JSON.parse(confirm2).$attrs.confirm.value, 'Confirm_String')
    await driver.tap(1, 1)
  }, 0)
}