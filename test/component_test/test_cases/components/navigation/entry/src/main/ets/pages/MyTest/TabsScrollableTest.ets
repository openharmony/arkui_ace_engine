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

export default async function tabsScrollableTest() {
  /*
* Tabs组件 Scrollable属性
* 找到画面id为tabsScrollable的Tabs组件
* 找到画面文本为TabsScrollable的Button组件
* 获取tabs的Scrollable属性与期待值true比对
* 点击button，变更tabs的Scrollable属性值为false
* 获取tabs的Scrollable属性与期待值false比对
*/
  defineTest('tabsScrollableTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('tabsScrollableTestDemo running')
    let driver: Tester = Tester.create()
    let tabs: Component = await driver.findComponent(Matcher.create().id('tabsScrollable').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TabsScrollable').enabled(true))

    let scrollable1: string = await tabs.getInspectorInfo()
    assertTrue(JSON.parse(scrollable1).$attrs.scrollable)
    await button.tap()
    let scrollable2: string = await tabs.getInspectorInfo()
    assertFalse(JSON.parse(scrollable2).$attrs.scrollable)
  }, 0)
}