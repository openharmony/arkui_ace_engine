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

export default async function textInputStyleTest() {
  /*
   * TextInput组件 Style属性
   * 找到画面id为textInputStyle1,textInputStyle2的TextInput组件
   * 找到画面文本为TextInputStyle1,TextInputStyle2的Button组件
   * 获取textInput1的Style属性与期待值'TextInputStyle.Default'比对
   * 获取textInput2的Style属性与期待值'TextContentStyle.DEFAULT'比对
   * 点击button1，变更textInput1的Style属性值为TextInputStyle.Inline
   * 获取textInput1的Style属性与期待值'TextInputStyle.Inline'比对
   * 点击button2，变更textInput2的Style属性值为TextContentStyle.INLINE
   * 获取textInput2的Style属性与期待值'TextContentStyle.INLINE'比对
   */
  defineTest('textInputStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textInputStyleTestDemo running")
    let driver: Tester = Tester.create()
    let textInput1: Component = await driver.findComponent(Matcher.create().id('textInputStyle1').enabled(true))
    let textInput2: Component = await driver.findComponent(Matcher.create().id('textInputStyle2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TextInputStyle1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TextInputStyle2').enabled(true))

    let style1: string = await textInput1.getInspectorInfo()
    assertEqual(JSON.parse(style1).$attrs.style, 'TextInputStyle.Default')

    let style2: string = await textInput2.getInspectorInfo()
    assertEqual(JSON.parse(style2).$attrs.style, 'TextContentStyle.DEFAULT')

    await button1.tap()
    let style3: string = await textInput1.getInspectorInfo()
    assertEqual(JSON.parse(style3).$attrs.style, 'TextInputStyle.Inline')

    await button2.tap()
    let style4: string = await textInput2.getInspectorInfo()
    assertEqual(JSON.parse(style4).$attrs.style, 'TextContentStyle.INLINE')
  }, 0)
}