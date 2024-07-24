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
import { assertEqual } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function fontWeightTest() {
  /*
  * TextArea、Text、TextInput组件 fontWeight属性
  * 找到画面id为 textAreaFontWeight1 textAreaFontWeight2 textFontWeight3 的组件
  * 找到画面文本为 ButtonFontWeight1 的Button组件
  * 获取 textFontWeight1 的fontWeight属性与期待值700比对
  * 获取 textFontWeight2 的fontWeight属性与期待值500比对
  * 获取textFontWeight3的fontWeight属性与期待值FontWeight.Lighter比对
  * 点击button1变更textFontWeight3的fontWeight属性与期待值'FontWeight.Normal'比对
  * 点击button1变更textFontWeight3的fontWeight属性与期待值'FontWeight.Regular'比对
  * 点击button1变更textFontWeight3的fontWeight属性与期待值'FontWeight.Medium'比对
  * 点击button1变更textFontWeight3的fontWeight属性与期待值'FontWeight.Bold'比对
  * 点击button1变更textFontWeight3的fontWeight属性与期待值'FontWeight.Bolder'比对
  */
  defineTest('fontWeightTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("fontWeightTestDemo running")
    let driver: Tester = Tester.create()
    let textFontWeight1: Component =
      await driver.findComponent(Matcher.create().id('textAreaFontWeight1').enabled(true))
    let textFontWeight2: Component =
      await driver.findComponent(Matcher.create().id('textAreaFontWeight2').enabled(true))
    let textFontWeight3: Component = await driver.findComponent(Matcher.create().id('textFontWeight3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonFontWeight1').enabled(true))
    let fontWeight1: string = await textFontWeight1.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight1).$attrs.fontWeight, '700')

    let fontWeight2: string = await textFontWeight2.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight2).$attrs.fontWeight, "500")

    let fontWeight3: string = await textFontWeight3.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight3).$attrs.fontWeight, 'FontWeight.Lighter')

    await button1.tap()
    let fontWeight4: string = await textFontWeight3.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight4).$attrs.fontWeight, 'FontWeight.Normal')

    await button1.tap()
    let fontWeight5: string = await textFontWeight3.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight5).$attrs.fontWeight, 'FontWeight.Regular')

    await button1.tap()
    let fontWeight6: string = await textFontWeight3.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight6).$attrs.fontWeight, 'FontWeight.Medium')

    await button1.tap()
    let fontWeight7: string = await textFontWeight3.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight7).$attrs.fontWeight, 'FontWeight.Bold')

    await button1.tap()
    let fontWeight8: string = await textFontWeight3.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight8).$attrs.fontWeight, 'FontWeight.Bolder')
  }, 0)
}