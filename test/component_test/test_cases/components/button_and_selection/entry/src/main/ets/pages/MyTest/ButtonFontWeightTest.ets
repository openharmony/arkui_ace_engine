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

export default async function buttonFontWeightTest() {
  /*
   * Button组件 FontWeight属性
   * 找到画面id为button1，button2，button3，button4，button5，button6的Button组件
   * 找到画面文本为ButtonFontWeight6的Button组件
   * 获取button1的FontWeight属性与期待值FontWeight.Lighter比对
   * 获取button2的FontWeight属性与期待值FontWeight.Normal比对
   * 获取button3的FontWeight属性与期待值FontWeight.Regular比对
   * 获取button4的FontWeight属性与期待值FontWeight.Bold比对
   * 获取button5的FontWeight属性与期待值FontWeight.Bolder比对
   * 获取button6的FontWeight属性与期待值'200'比对
   * 点击button，变更button3的FontWeight属性值为FontWeight.Medium，button6的FontWeight属性值为'700'
   * 获取button3的FontWeight属性与期待值FontWeight.Medium比对，button6的FontWeight属性与期待值'700'比对
   */
  defineTest('buttonFontWeightTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('buttonFontWeightTestDemo running')
    let driver: Tester = Tester.create()
    let buttonFontWeight1: Component =
      await driver.findComponent(Matcher.create().id('buttonFontWeight1').enabled(true))
    let buttonFontWeight2: Component =
      await driver.findComponent(Matcher.create().id('buttonFontWeight2').enabled(true))
    let buttonFontWeight3: Component =
      await driver.findComponent(Matcher.create().id('buttonFontWeight3').enabled(true))
    let buttonFontWeight4: Component =
      await driver.findComponent(Matcher.create().id('buttonFontWeight4').enabled(true))
    let buttonFontWeight5: Component =
      await driver.findComponent(Matcher.create().id('buttonFontWeight5').enabled(true))
    let buttonFontWeight6: Component =
      await driver.findComponent(Matcher.create().id('buttonFontWeight6').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonFontWeight6').enabled(true))

    let fontWeight1: string = await buttonFontWeight1.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight1).$attrs.fontWeight, 'FontWeight.Lighter')

    let fontWeight2: string = await buttonFontWeight2.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight2).$attrs.fontWeight, 'FontWeight.Normal')

    let fontWeight3: string = await buttonFontWeight3.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight3).$attrs.fontWeight, 'FontWeight.Regular')

    let fontWeight4: string = await buttonFontWeight4.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight4).$attrs.fontWeight, 'FontWeight.Bold')

    let fontWeight5: string = await buttonFontWeight5.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight5).$attrs.fontWeight, 'FontWeight.Bolder')

    let fontWeight6: string = await buttonFontWeight6.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight6).$attrs.fontWeight, '200')

    await button.tap()
    let fontWeight7: string = await buttonFontWeight3.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight7).$attrs.fontWeight, 'FontWeight.Medium')
    let fontWeight8: string = await buttonFontWeight6.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight8).$attrs.fontWeight, '700')
  }, 0)
}