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

export default async function textAreaSelectionMenuHiddenTest() {
  /*
* TextArea组件 SelectionMenuHidden属性
* 找到画面id为textAreaSelectionMenuHidden的TextArea组件
* 找到画面文本为TextAreaSelectionMenuHidden的Button组件
* 获取textArea的SelectionMenuHidden属性与期待值true比对
* 点击button，变更textArea的SelectionMenuHidden属性值为false
* 获取textArea的SelectionMenuHidden属性与期待值false比对
*/
  defineTest('textAreaSelectionMenuHiddenTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textAreaSelectionMenuHiddenTestDemo running")
    let driver: Tester = Tester.create()
    let textArea: Component =
      await driver.findComponent(Matcher.create().id('textAreaSelectionMenuHidden').enabled(true))
    let button: Component =
      await driver.findComponent(Matcher.create().text('TextAreaSelectionMenuHidden').enabled(true))

    let selectionMenuHidden1: string = await textArea.getInspectorInfo()
    assertFalse(JSON.parse(selectionMenuHidden1).$attrs.selectionMenuHidden == undefined)
    assertTrue(JSON.parse(selectionMenuHidden1).$attrs.selectionMenuHidden)

    await button.tap()
    let selectionMenuHidden2: string = await textArea.getInspectorInfo()
    assertFalse(JSON.parse(selectionMenuHidden2).$attrs.selectionMenuHidden)
  }, 0)
}