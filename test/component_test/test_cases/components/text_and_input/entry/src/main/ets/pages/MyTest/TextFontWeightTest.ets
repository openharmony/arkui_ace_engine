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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest';

export default async function textFontWeightTest() {
  /*
   * Text组件 FontWeight属性
   * 找到画面id为textFontWeight1,textFontWeight2,textFontWeight3,textFontWeight4的Text组件
   * 找到画面文本为TextFontWeight的Button组件
   * 获取text1的FontWeight属性与期待值'FontWeight.Normal'比对
   * 获取text2的FontWeight属性与期待值'FontWeight.Lighter'比对
   * 获取text3的FontWeight属性与期待值"300"比对
   * 获取text4的FontWeight属性Font.weight与期待值'FontWeight.Regular'比对
   * 点击button，变更text4的FontWeight属性值为FontWeight.Bold
   * 获取text4的FontWeight属性与期待值'FontWeight.Bold'比对
   * 点击button，变更text4的FontWeight属性值为FontWeight.Medium
   * 获取text4的FontWeight属性与期待值'FontWeight.Medium'比对
   * 点击button，变更text4的FontWeight属性值为FontWeight.Bolder
   * 获取text4的FontWeight属性与期待值'FontWeight.Bolder'比对
   * 点击button，变更text4的FontWeight属性Font.weight值为100
   * 获取text4的FontWeight属性Font.weight与期待值'100'比对
   */
  defineTest('textFontWeightTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textFontWeightTestDemo running")
    let driver: Tester = Tester.create()
    let text1: Component = await driver.findComponent(Matcher.create().id('textFontWeight1').enabled(true))
    let text2: Component = await driver.findComponent(Matcher.create().id('textFontWeight2').enabled(true))
    let text3: Component = await driver.findComponent(Matcher.create().id('textFontWeight3').enabled(true))
    let text4: Component = await driver.findComponent(Matcher.create().id('textFontWeight4').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextFontWeight').enabled(true))

    let fontWeight1: string = await text1.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight1).$attrs.fontWeight, 'FontWeight.Normal')
    let fontWeight2: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight2).$attrs.fontWeight, 'FontWeight.Lighter')
    let fontWeight3: string = await text3.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight3).$attrs.fontWeight, "300")
    let fontWeight4: string = await text4.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight4).$attrs.fontWeight, 'FontWeight.Regular')

    await button.tap()
    let fontWeight5: string = await text4.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight5).$attrs.fontWeight, 'FontWeight.Bold')
    await button.tap()
    let fontWeight6: string = await text4.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight6).$attrs.fontWeight, 'FontWeight.Medium')
    await button.tap()
    let fontWeight7: string = await text4.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight7).$attrs.fontWeight, 'FontWeight.Bolder')
    await button.tap()
    let fontWeight8: string = await text4.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight8).$attrs.fontWeight, '100')
  }, 0)
}