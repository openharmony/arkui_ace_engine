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

import { assertFalse, assertTrue } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function monopolizeEventsTest() {
  /*
  * colum组件 monopolizeEvents属性
  * 找到画面id为columMonopolizeEvents1的colum组件
  * 找到画面文本为ButtonMonopolizeEvents1的Button组件
  * 获取columMonopolizeEvents1的monopolizeEvents属性与期待值false比对
  * 点击button1，变更columMonopolizeEvents1的monopolizeEvents属性为true
  * 获取columMonopolizeEvents1的monopolizeEvents属性与期待值true比对
  */
  defineTest('monopolizeEventsTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("monopolizeEventsTest running")
    let driver: Tester = Tester.create()
    let columMonopolizeEvents1: Component =
      await driver.findComponent(Matcher.create().id('columMonopolizeEvents1').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonMonopolizeEvents1').enabled(true))
    let monopolizeEvents1: string = await columMonopolizeEvents1.getInspectorInfo()
    assertFalse(JSON.parse(monopolizeEvents1).$attrs.monopolizeEvents)

    await button.tap()
    let monopolizeEvents2: string = await columMonopolizeEvents1.getInspectorInfo()
    assertTrue(JSON.parse(monopolizeEvents2).$attrs.monopolizeEvents)
  }, 0)
}