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

export default async function actionSheetShowInSubWindowTest() {
  /*
* ActionSheet组件 ShowInSubWindow对象
* 找到画面id为actionSheetShowInSubWindow的ActionSheet组件
* 找到画面文本为ActionSheetShowInSubWindow的Button组件
* 获取actionSheetShowInSubWindow的ShowInSubWindow对象与期待值true比对
* 点击button，变更actionSheetShowInSubWindow，的对象值false
* 获取actionSheetShowInSubWindow的ShowInSubWindow对象与期待值false比对

*/
  defineTest('actionSheetShowInSubWindowTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('actionSheetShowInSubWindowTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('ActionSheetShowInSubWindowTest1').enabled(true))
    let button: Component =
      await driver.findComponent(Matcher.create().text('ActionSheetShowInSubWindow1').enabled(true))
    await button1.tap()
    let actionSheetShowInSubWindow1: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let showInSubWindow1: string = await actionSheetShowInSubWindow1.getInspectorInfo()
    assertTrue(JSON.parse(showInSubWindow1).$attrs.showInSubWindow)
    await driver.tap(1, 1)
    await button.tap()
    await button1.tap()
    let actionSheetShowInSubWindow2: Component =
      await driver.findComponent(Matcher.create().type('ActionSheet').enabled(true))
    let showInSubWindow2: string = await actionSheetShowInSubWindow2.getInspectorInfo()
    assertFalse(JSON.parse(showInSubWindow2).$attrs.showInSubWindow)
    await driver.tap(1, 1)
  }, 0)
}