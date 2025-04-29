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

export default async function textInputTextAlignTest() {
  /*
   * TextInput组件 TextAlign属性
   * 找到画面id为textInputTextAlign1,textInputTextAlign2的TextInput组件
   * 找到画面文本为TextInputTextAlign1,TextInputTextAlign2的Button组件
   * 获取textInput1的TextAlign属性与期待值'TextAlign.Start'比对
   * 获取textInput2的TextAlign属性与期待值'TextAlign.Center'比对
   * 点击button1，变更textInput2的TextAlign属性值为TextAlign.End
   * 获取textInput2的TextAlign属性与期待值'TextAlign.End'比对
   * 点击button2，变更textInput2的TextAlign属性值为TextAlign.JUSTIFY
   * 获取textInput2的TextAlign属性与期待值'TextAlign.JUSTIFY'比对
   */
  defineTest('textInputTextAlignTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textInputTextAlignTestDemo running")
    let driver: Tester = Tester.create()
    let textInput1: Component = await driver.findComponent(Matcher.create().id('textInputTextAlign1').enabled(true))
    let textInput2: Component = await driver.findComponent(Matcher.create().id('textInputTextAlign2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TextInputTextAlign1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TextInputTextAlign2').enabled(true))

    let textAlign1: string = await textInput1.getInspectorInfo()
    assertEqual(JSON.parse(textAlign1).$attrs.textAlign, 'TextAlign.Start')

    let textAlign2: string = await textInput2.getInspectorInfo()
    assertEqual(JSON.parse(textAlign2).$attrs.textAlign, 'TextAlign.Center')

    await button1.tap()
    let textAlign3: string = await textInput2.getInspectorInfo()
    assertEqual(JSON.parse(textAlign3).$attrs.textAlign, 'TextAlign.End')

    await button2.tap()
    let textAlign4: string = await textInput2.getInspectorInfo()
    assertEqual(JSON.parse(textAlign4).$attrs.textAlign, 'TextAlign.JUSTIFY')
  }, 0)
}