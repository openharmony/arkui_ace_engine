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

export default async function listItemSelectableTest() {
  /*
  * ListItem组件 selectable属性
  * 找到画面id为listItemSelectable1，listItemSelectable2的ListItem组件
  * 找到画面文本为ListItemSelectable的button组件
  * 获取listItem1的selectable属性与期待值true比对
  * 获取listItem2的selectable属性与期待值true比对
  * 点击button，变更listItem1的selectable属性值为false
  * 获取listItem1的selectable属性与期待值false比对
  */
  defineTest('listItemSelectableTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("listItemSelectableTestDemo running")
    let driver: Tester = Tester.create()
    let listItem1: Component = await driver.findComponent(Matcher.create().id('listItemSelectable1').enabled(true))
    let listItem2: Component = await driver.findComponent(Matcher.create().id('listItemSelectable2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ListItemSelectable').enabled(true))

    let selectable1: string = await listItem1.getInspectorInfo()
    assertTrue(JSON.parse(selectable1).$attrs.selectable)
    let selectable2: string = await listItem2.getInspectorInfo()
    assertTrue(JSON.parse(selectable2).$attrs.selectable)
    await button.tap()
    let selectable3: string = await listItem1.getInspectorInfo()
    assertFalse(JSON.parse(selectable3).$attrs.selectable)
  }, 0)
}
