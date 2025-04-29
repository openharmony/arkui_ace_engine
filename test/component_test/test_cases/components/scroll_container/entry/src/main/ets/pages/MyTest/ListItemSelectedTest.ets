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

export default async function listItemSelectedTest() {
  /*
* ListItem组件 selected属性
* 找到画面id为listItemSelected1，listItemSelected2的ListItem组件
* 找到画面文本为ListItemSelected的button组件
* 获取listItem1的selected属性与期待值true比对
* 获取listItem2的selected属性与期待值false比对
* 点击button，变更listItem2的selected属性值为true
* 获取listItem2的selected属性与期待值true比对
*/
  defineTest('listItemSelectedTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("listItemSelectedTestDemo running")
    let driver: Tester = Tester.create()
    let listItem1: Component = await driver.findComponent(Matcher.create().id('listItemSelected1').enabled(true))
    let listItem2: Component = await driver.findComponent(Matcher.create().id('listItemSelected2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ListItemSelected').enabled(true))

    let selected1: string = await listItem1.getInspectorInfo()
    assertFalse(JSON.parse(selected1).$attrs.selected == undefined)
    assertTrue(JSON.parse(selected1).$attrs.selected)
    let selected2: string = await listItem2.getInspectorInfo()
    assertFalse(JSON.parse(selected2).$attrs.selected)
    await button.tap()
    let selected3: string = await listItem2.getInspectorInfo()
    assertTrue(JSON.parse(selected3).$attrs.selected)
  }, 0)
}
