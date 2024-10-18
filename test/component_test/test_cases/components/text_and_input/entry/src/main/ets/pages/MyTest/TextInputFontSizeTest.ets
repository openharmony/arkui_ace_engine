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

export default async function textInputFontSizeTest() {
  /*
   * TextInput组件 FontSize属性
   * 找到画面id为textInputFontSize的TextInput组件
   * 找到画面文本为TextInputFontSize1,TextInputFontSize2的Button组件
   * 获取textInput的FontStyle属性与期待值'20px'比对
   * 点击button1，变更textInput的FontStyle属性值为800
   * 获取textInput的FontStyle属性与期待值800比对
   * 点击button2，变更textInput的FontStyle属性值为$r('app.string.fp_length')
   * 获取textInput的FontStyle属性与期待值$r('app.string.fp_length')比对
   */
  defineTest('textInputFontSizeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textInputFontSizeTestDemo running")
    let driver: Tester = Tester.create()
    let textInput: Component = await driver.findComponent(Matcher.create().id('textInputFontSize').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TextInputFontSize1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TextInputFontSize2').enabled(true))

    let fontSize1: string = await textInput.getInspectorInfo()
    assertEqual(JSON.parse(fontSize1).$attrs.fontSize, '20.00px')

    await button2.tap()
    let fontSize2: string = await textInput.getInspectorInfo()
    assertEqual(JSON.parse(fontSize2).$attrs.fontSize, $r('app.string.fp_length'))

    await button1.tap()
    let fontSize3: string = await textInput.getInspectorInfo()
    assertEqual(JSON.parse(fontSize3).$attrs.fontSize, '400.00fp')
  }, 0)
}