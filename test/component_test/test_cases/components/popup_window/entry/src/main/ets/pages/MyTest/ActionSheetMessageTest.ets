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

export default async function actionSheetMessageTest() {
  /*
* ActionSheet组件 Message对象
* 找到画面id为actionSheetMessage的ActionSheet组件
* 找到画面文本为ActionSheetMessage的Button组件
* 获取actionSheetMessage的Message对象与期待值'message1'比对
* 点击button，变更actionSheetMessage，的对象值$r('app.string.actionSheet_message')
* 获取actionSheetMessage的Message对象与期待值$r('app.string.actionSheet_message')比对

*/
  defineTest('actionSheetMessageTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('actionSheetMessageTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component = await driver.findComponent(Matcher.create().text('ActionSheetMessageTest1').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ActionSheetMessage1').enabled(true))
    await button1.tap()
    let actionSheetMessage1: Component = await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let message1: string = await actionSheetMessage1.getInspectorInfo()
    assertEqual(JSON.parse(message1).$attrs.message, 'message1')
    await driver.tap(1, 1)
    await button.tap()
    await button1.tap()
    let actionSheetMessage2: Component = await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let message2: string = await actionSheetMessage2.getInspectorInfo()
    assertEqual(JSON.parse(message2).$attrs.message, $r('app.string.actionSheet_message'))
    await driver.tap(1, 1)
  }, 0)
}