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

export default async function tabsVerticalTest() {
  /*
* Tabs组件 Vertical属性
* 找到画面id为tabsVertical的Tabs组件
* 找到画面文本为TabsVertical的Button组件
* 获取tabs的Vertical属性与期待值true比对
* 点击button，变更tabs的Vertical属性值为false
* 获取tabs的Vertical属性与期待值false比对
*/
  defineTest('tabsVerticalTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('tabsVerticalTestDemo running')
    let driver: Tester = Tester.create()
    let tabs: Component = await driver.findComponent(Matcher.create().id('tabsVertical').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TabsVertical').enabled(true))

    let vertical1: string = await tabs.getInspectorInfo()
    assertTrue(JSON.parse(vertical1).$attrs.vertical)
    await button.tap()
    let vertical2: string = await tabs.getInspectorInfo()
    assertFalse(JSON.parse(vertical2).$attrs.vertical)
  }, 0)
}