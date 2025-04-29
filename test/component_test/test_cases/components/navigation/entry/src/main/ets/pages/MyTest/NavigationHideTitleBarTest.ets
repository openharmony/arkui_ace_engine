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

export default async function navigationHideTitleBarTestTest() {
  /*
* Navigation组件 HideTitleBar属性
* 找到画面id为navigationHideTitleBar的Navigation组件
* 找到画面文本为NavigationHideTitleBar的Button组件
* 获取navigation1的HideTitleBar属性与期待值True比对
* 点击button1，变更navigation1的HideTitleBar属性值为False
* 获取navigation1的HideTitleBar属性与期待值False比对
*/
  defineTest('navigationHideTitleBarTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("navigationHideTitleBarTestDemo running")
    let driver: Tester = Tester.create()
    let navigation1: Component = await driver.findComponent(Matcher.create().id('navigationHideTitleBar').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('NavigationHideTitleBar').enabled(true))
    let hideTitleBar1: string = await navigation1.getInspectorInfo()
    assertTrue(JSON.parse(hideTitleBar1).$attrs.hideTitleBar)
    await button1.tap()
    let hideTitleBar2: string = await navigation1.getInspectorInfo()
    assertFalse(JSON.parse(hideTitleBar2).$attrs.hideTitleBar)
  }, 0)
}