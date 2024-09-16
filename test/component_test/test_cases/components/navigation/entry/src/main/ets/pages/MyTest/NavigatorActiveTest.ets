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

export default async function navigatorActiveTest() {
  /*
* Navigator组件 Active属性
* 找到画面id为navigatorActive的Navigator组件
* 找到画面文本为NavigatorActive的button组件
* 获取navigator的Active属性与期待值false比对
* 点击button，变更navigator的Active属性值为true
* 获取navigator的Active属性与期待值true比对
*/
  defineTest('navigatorActiveTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("navigatorActiveTestDemo running")
    let driver: Tester = Tester.create()
    let navigator: Component = await driver.findComponent(Matcher.create().id('navigatorActive').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('NavigatorActive').enabled(true))

    let active1: string = await navigator.getInspectorInfo()
    assertFalse(JSON.parse(active1).$attrs.active)

    await button.tap()
    let active2: string = await navigator.getInspectorInfo()
    assertTrue(JSON.parse(active2).$attrs.active)
  }, 0)
}