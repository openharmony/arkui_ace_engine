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

export default async function textInputEnableKeyboardOnFocusTest() {
  /*
   * TextInput组件 EnableKeyboardOnFocus属性
   * 找到画面id为textInputEnableKeyboardOnFocus的TextInput组件
   * 找到画面文本为TextInputEnableKeyboardOnFocus的Button组件
   * 获取textInput的EnableKeyboardOnFocus属性与期待值true比对
   * 点击button，变更textInput的EnableKeyboardOnFocus属性值为false
   * 获取textInput的EnableKeyboardOnFocus属性与期待值false比对
   */
  defineTest('textInputEnableKeyboardOnFocusTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textInputEnableKeyboardOnFocusTestDemo running")
    let driver: Tester = Tester.create()
    let textInput: Component =
      await driver.findComponent(Matcher.create().id('textInputEnableKeyboardOnFocus').enabled(true))
    let button: Component =
      await driver.findComponent(Matcher.create().text('TextInputEnableKeyboardOnFocus').enabled(true))

    let enableKeyboardOnFocus1: string = await textInput.getInspectorInfo()
    assertFalse(JSON.parse(enableKeyboardOnFocus1).$attrs.enableKeyboardOnFocus == undefined)
    assertTrue(JSON.parse(enableKeyboardOnFocus1).$attrs.enableKeyboardOnFocus)

    await button.tap()
    let enableKeyboardOnFocus2: string = await textInput.getInspectorInfo()
    assertFalse(JSON.parse(enableKeyboardOnFocus2).$attrs.enableKeyboardOnFocus)
  }, 0)
}