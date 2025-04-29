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
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function actionSheetIsModalTest() {
  /*
* ActionSheet组件 IsModal对象
* 找到画面id为actionSheetIsModal的ActionSheet组件
* 找到画面文本为ActionSheetIsModal的Button组件
* 获取actionSheetIsModal的IsModal对象与期待值true比对
* 点击button，变更actionSheetIsModal，的对象值false
* 获取actionSheetIsModal的IsModal对象与期待值false比对

*/
  defineTest('actionSheetIsModalTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('actionSheetIsModalTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component = await driver.findComponent(Matcher.create().text('ActionSheetIsModalTest1').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ActionSheetIsModal1').enabled(true))

    await button1.tap()
    let actionSheetIsModal1: Component = await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let isModal1: string = await actionSheetIsModal1.getInspectorInfo()
    assertTrue(JSON.parse(isModal1).$attrs.isModal)
    await driver.tap(1, 1)
    await button.tap()
    await button1.tap()
    let actionSheetIsModal2: Component = await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let isModal2: string = await actionSheetIsModal2.getInspectorInfo()
    assertFalse(JSON.parse(isModal2).$attrs.isModal)
    await driver.tap(1, 1)
  }, 0)
}