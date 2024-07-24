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
} from '@ohos.arkui.componentTest'

export default async function actionSheetSheetsTest() {
  /*
* ActionSheet组件 Sheets对象
* 找到画面id为actionSheetSheets的ActionSheet组件
* 找到画面文本为ActionSheetSheets的Button组件
* 获取actionSheetSheets的Sheets对象与期待值[{ title: 'title1', icon: 'pages/icon/Sheet1.jpg', action: () => {this.String ='applesText1'} },]比对
* 点击button，变更actionSheetSheets，的对象值[{ title: $r('app.string.actionSheet_title'), icon: $r('app.media.startIcon'), action: () => {this.String ='applesText1'} },]
* 获取actionSheetSheets的Sheets对象与期待值[{ title: $r('app.string.actionSheet_title'), icon: $r('app.media.startIcon'), action: () => {this.String ='applesText1'} },]比对

*/
  defineTest('actionSheetSheetsTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('actionSheetSheetsTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component = await driver.findComponent(Matcher.create().text('ActionSheetSheetsTest1').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ActionSheetSheets1').enabled(true))
    let text1: Component = await driver.findComponent(Matcher.create().text('actionText').enabled(true))

    await button1.tap()
    let actionSheetSheets1: Component = await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('../../../resources/base/media/icon.png').enabled(true))
    let sheets1: string = await actionSheetSheets1.getInspectorInfo()
    let content1: string = await text1.getInspectorInfo()
    assertFalse(JSON.parse(sheets1).$attrs.sheets == undefined)
    assertEqual(JSON.parse(sheets1).$attrs.sheets.title, 'title1')
    assertEqual(JSON.parse(sheets1).$attrs.sheets.icon, '../../../resources/base/media/icon.png')
    assertEqual(JSON.parse(content1).$attrs.content, 'applesText')
    await button2.tap()
    let content2: string = await text1.getInspectorInfo()
    assertEqual(JSON.parse(content2).$attrs.content, 'actionText1')

    await button.tap()
    await button1.tap()
    let actionSheetSheets2: Component = await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let sheets2: string = await actionSheetSheets2.getInspectorInfo()
    assertEqual(JSON.parse(sheets2).$attrs.sheets.title, $r('app.string.actionSheet_title'))
    assertEqual(JSON.parse(sheets2).$attrs.sheets.icon, $r('app.media.startIcon'))
    assertEqual(JSON.parse(sheets2).$attrs.sheets.action, 'applesText1')
    await driver.tap(1, 1)
  }, 0)
}