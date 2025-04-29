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
import { assertFalse, assertTrue } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function textInputShowUnderlineTest() {
  /*
   * TextInput组件 ShowUnderline属性
   * 找到画面id为textInputShowUnderline的TextInput组件
   * 找到画面文本为TextInputShowUnderline的Button组件
   * 获取textInput的ShowUnderline属性与期待值true比对
   * 点击button，变更textInput的ShowUnderline属性值为false
   * 获取textInput的ShowUnderline属性与期待值false比对
   */
  defineTest('textInputShowUnderlineTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textInputShowUnderlineTestDemo running")
    let driver: Tester = Tester.create()
    let textInput: Component = await driver.findComponent(Matcher.create().id('textInputShowUnderline').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextInputShowUnderline').enabled(true))

    let showUnderline1: string = await textInput.getInspectorInfo()
    assertFalse(JSON.parse(showUnderline1).$attrs.showUnderline)

    await button.tap()
    let showUnderline2: string = await textInput.getInspectorInfo()
    assertTrue(JSON.parse(showUnderline2).$attrs.showUnderline)
  }, 0)
}