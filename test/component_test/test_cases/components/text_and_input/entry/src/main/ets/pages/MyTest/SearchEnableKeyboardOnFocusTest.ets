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
} from '@ohos.arkui.componentTest';

export default async function searchEnableKeyboardOnFocusTest() {
  /*
   * Search组件 EnableKeyboardOnFocus属性
   * 找到画面id为searchEnableKeyboardOnFocus1的Search组件
   * 找到画面文本为SearchEnableKeyboardOnFocus1的Button组件
   * 获取search1的EnableKeyboardOnFocus属性与期待值true比对
   * 点击button1，变更search1的EnableKeyboardOnFocus属性值为false
   * 获取search1的EnableKeyboardOnFocus属性与期待值false比对
   */
  defineTest('searchEnableKeyboardOnFocusTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("searchEnableKeyboardOnFocusTestDemo running")
    let driver: Tester = Tester.create()
    let search1: Component =
      await driver.findComponent(Matcher.create().id('searchEnableKeyboardOnFocus1').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('SearchEnableKeyboardOnFocus').enabled(true))

    let enableKeyboardOnFocus1: string = await search1.getInspectorInfo()
    assertFalse(JSON.parse(enableKeyboardOnFocus1).$attrs.enableKeyboardOnFocus == undefined)
    assertTrue(JSON.parse(enableKeyboardOnFocus1).$attrs.enableKeyboardOnFocus)

    await button1.tap()
    let enableKeyboardOnFocus2: string = await search1.getInspectorInfo()
    assertFalse(JSON.parse(enableKeyboardOnFocus2).$attrs.enableKeyboardOnFocus)
  }, 0)
}