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

export default async function textInputFontWeightTest() {
  /*
   * TextInput组件 FontWeight属性
   * 找到画面id为textInputFontWeight1,textInputFontWeight2,textInputFontWeight3,textInputFontWeight4的TextInput组件
   * 找到画面文本为TextInputFontWeight的Button组件
   * 获取textInput1的FontWeight属性与期待值'FontWeight.Lighter'比对
   * 获取textInput2的FontWeight属性与期待值'400'比对
   * 获取textInput3的FontWeight属性与期待值'FontWeight.Normal'比对
   * 获取textInput4的FontWeight属性Font.weight与期待值'FontWeight.Regular'比对
   * 点击button，变更textInput4的FontWeight属性值为FontWeight.Bold
   * 获取textInput4的FontWeight属性与期待值'FontWeight.Bold'比对
   * 点击button，变更textInput4的FontWeight属性值为FontWeight.Medium
   * 获取textInput4的FontWeight属性与期待值'FontWeight.Medium'比对
   * 点击button，变更textInput4的FontWeight属性值为FontWeight.Bolder
   * 获取textInput4的FontWeight属性与期待值'FontWeight.Bolder'比对
   * 点击button，变更textInput4的FontWeight属性Font.weight值为800
   * 获取textInput4的FontWeight属性Font.weight与期待值'800'比对
   */
  defineTest('textInputFontWeightTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textInputFontWeightTestDemo running")
    let driver: Tester = Tester.create()
    let textInput1: Component = await driver.findComponent(Matcher.create().id('textInputFontWeight1').enabled(true))
    let textInput2: Component = await driver.findComponent(Matcher.create().id('textInputFontWeight2').enabled(true))
    let textInput3: Component = await driver.findComponent(Matcher.create().id('textInputFontWeight3').enabled(true))
    let textInput4: Component = await driver.findComponent(Matcher.create().id('textInputFontWeight4').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextInputFontWeight').enabled(true))

    let fontWeight1: string = await textInput1.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight1).$attrs.fontWeight, 'FontWeight.Lighter')
    let fontWeight2: string = await textInput2.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight2).$attrs.fontWeight, '400')
    let fontWeight3: string = await textInput3.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight3).$attrs.fontWeight, 'FontWeight.Normal')
    let fontWeight4: string = await textInput4.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight4).$attrs.fontWeight, 'FontWeight.Bold')

    await button.tap()
    let fontWeight5: string = await textInput4.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight5).$attrs.fontWeight, 'FontWeight.Regular')
    await button.tap()
    let fontWeight6: string = await textInput4.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight6).$attrs.fontWeight, 'FontWeight.Medium')
    await button.tap()
    let fontWeight7: string = await textInput4.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight7).$attrs.fontWeight, 'FontWeight.Bolder')
    await button.tap()
    let fontWeight8: string = await textInput4.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight8).$attrs.fontWeight, '800')
  }, 0)
}