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
import { assertEqual, assertTrue } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function textInputCaretPositionTest() {
  /*
   * TextInput组件 CaretPosition属性
   * 找到画面id为textInputCaretPosition的TextInput组件
   * 找到画面文本为TextInputCaretPosition的Button组件
   * 点击button，变更textInput的CaretPosition属性值为5
   * 获取textInput的CaretPosition属性与期待值5比对
   */
  defineTest('textInputCaretPositionTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textInputCaretPositionTestDemo running")
    let driver: Tester = Tester.create()
    let textInput: Component = await driver.findComponent(Matcher.create().id('textInputCaretPosition').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextInputCaretPosition').enabled(true))

    assertTrue(textInput == null)
    await button.tap()
    let caretPosition: string = await textInput.getInspectorInfo()
    assertEqual(JSON.parse(caretPosition).$attrs.caretPosition, 5)
  }, 0)
}