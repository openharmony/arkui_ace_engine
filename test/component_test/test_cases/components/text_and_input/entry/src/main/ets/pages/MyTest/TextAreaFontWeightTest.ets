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

export default async function textAreaFontWeightTest() {
  /*
   * TextArea组件 FontWeight属性
   * 找到画面id为textAreaFontWeight1,textAreaFontWeight2,textAreaFontWeight3,textAreaFontWeight4的TextArea组件
   * 找到画面文本为TextAreaFontWeight的Button组件
   * 获取textArea1的FontWeight属性与期待值'FontWeight.Lighter'比对
   * 获取textArea2的FontWeight属性与期待值'FontWeight.Normal'比对
   * 获取textArea3的FontWeight属性与期待值"400"比对
   * 获取textArea4的FontWeight属性Font.weight与期待值'FontWeight.Regular'比对
   * 点击button，变更textArea3的FontWeight属性值为FontWeight.Bold
   * 获取textArea3的FontWeight属性与期待值'FontWeight.Bold'比对
   * 点击button，变更textArea3的FontWeight属性值为FontWeight.Medium
   * 获取textArea3的FontWeight属性与期待值'FontWeight.Medium'比对
   * 点击button，变更textArea3的FontWeight属性值为FontWeight.Bolder
   * 获取textArea3的FontWeight属性与期待值'FontWeight.Bolder'比对
   * 点击button，变更textArea3的FontWeight属性Font.weight值为800
   * 获取textArea3的FontWeight属性Font.weight与期待值'800'比对

   */
  defineTest('textAreaFontWeightTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textAreaFontWeightTestDemo running")
    let driver: Tester = Tester.create()
    let textArea1: Component = await driver.findComponent(Matcher.create().id('textAreaFontWeight1').enabled(true))
    let textArea2: Component = await driver.findComponent(Matcher.create().id('textAreaFontWeight2').enabled(true))
    let textArea3: Component = await driver.findComponent(Matcher.create().id('textAreaFontWeight3').enabled(true))
    let textArea4: Component = await driver.findComponent(Matcher.create().id('textAreaFontWeight4').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextAreaFontWeight').enabled(true))

    let fontWeight1: string = await textArea1.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight1).$attrs.fontWeight, 'FontWeight.Lighter')
    let fontWeight2: string = await textArea2.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight2).$attrs.fontWeight, 'FontWeight.Normal')
    let fontWeight3: string = await textArea4.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight3).$attrs.fontWeight, '400')
    let fontWeight4: string = await textArea3.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight4).$attrs.fontWeight, 'FontWeight.Regular')

    await button.tap()
    let fontWeight5: string = await textArea3.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight5).$attrs.fontWeight, 'FontWeight.Bold')

    await button.tap()
    let fontWeight6: string = await textArea3.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight6).$attrs.fontWeight, 'FontWeight.Medium')

    await button.tap()
    let fontWeight7: string = await textArea3.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight7).$attrs.fontWeight, 'FontWeight.Bolder')

    await button.tap()
    let fontWeight8: string = await textArea3.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight8).$attrs.fontWeight, '800')
  }, 0)
}