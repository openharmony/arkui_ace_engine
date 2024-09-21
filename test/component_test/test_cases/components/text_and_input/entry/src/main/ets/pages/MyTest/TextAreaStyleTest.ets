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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function textAreaStyleTest() {
  /*
   * TextArea组件 Style属性
   * 找到画面id为textAreaStyle的TextArea组件
   * 找到画面文本为TextAreaStyle的Button组件
   * 获取textArea的Style属性与期待值'TextContentStyle.DEFAULT'比对
   * 点击button，变更textArea的Style属性值为TextContentStyle.INLINE
   * 获取textArea的Style属性与期待值'TextContentStyle.INLINE'比对
   */
  defineTest('textAreaStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textAreaStyleTestDemo running")
    let driver: Tester = Tester.create()
    let textArea: Component = await driver.findComponent(Matcher.create().id('textAreaStyle').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextAreaStyle').enabled(true))

    let style1: string = await textArea.getInspectorInfo()
    assertEqual(JSON.parse(style1).$attrs.style, 'TextContentStyle.DEFAULT')

    await button.tap()
    let style2: string = await textArea.getInspectorInfo()
    assertEqual(JSON.parse(style2).$attrs.style, 'TextContentStyle.INLINE')
  }, 0)
}