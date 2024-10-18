/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 // * You may obtain a copy of the License at
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

export default async function selectOptionFontTest() {
  /*
   * Select组件 OptionFont属性
   * 找到画面id为selectOptionFont1,selectOptionFont2,selectOptionFont3,...,selectOptionFont6,selectOptionFont7的Select组件
   * 找到画面文本为SelectOptionFont的Button组件
   * 获取selectOptionFont1的OptionFont属性与期待值{ weight: 'FontWeight.Lighter' }比对
   * 获取selectOptionFont2的OptionFont属性与期待值{ weight: 'FontWeight.Normal' }比对
   * 获取selectOptionFont3的OptionFont属性与期待值{ weight: 'FontWeight.Regular' }比对
   * 获取selectOptionFont4的OptionFont属性与期待值{ weight: 'FontWeight.Medium', size: '0.00fp' }比对
   * 获取selectOptionFont5的OptionFont属性与期待值{ weight: 'FontWeight.Bold', size: '16.00fp' }比对
   * 获取selectOptionFont6的OptionFont属性与期待值{ weight: 'FontWeight.Bolder', size: $r('app.string.size'), family: 'Arial' }比对
   * 获取selectOptionFont7的OptionFont属性与期待值{ weight: '100', size: '20.00fp', family: 'TESTFONT', style: 'FontStyle.Normal' }比对
   * 点击button，变更selectOptionFont7的OptionFont属性值为{ weight: '200', size: '40.00fp', style: 'FontStyle.Italic' }
   * 获取selectOptionFont7的OptionFont属性与期待值{ weight: '200', size: '40.00fp', style: 'FontStyle.Italic' }比对
   */
  defineTest('selectOptionFontTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('selectOptionFontTestDemo running')
    let driver: Tester = Tester.create()
    let selectOptionFont1: Component =
      await driver.findComponent(Matcher.create().id('selectOptionFont1').enabled(true))
    let selectOptionFont2: Component =
      await driver.findComponent(Matcher.create().id('selectOptionFont2').enabled(true))
    let selectOptionFont3: Component =
      await driver.findComponent(Matcher.create().id('selectOptionFont3').enabled(true))
    let selectOptionFont4: Component =
      await driver.findComponent(Matcher.create().id('selectOptionFont4').enabled(true))
    let selectOptionFont5: Component =
      await driver.findComponent(Matcher.create().id('selectOptionFont5').enabled(true))
    let selectOptionFont6: Component =
      await driver.findComponent(Matcher.create().id('selectOptionFont6').enabled(true))
    let selectOptionFont7: Component =
      await driver.findComponent(Matcher.create().id('selectOptionFont7').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('SelectOptionFont').enabled(true))

    let optionFont1: string = await selectOptionFont1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(optionFont1).$attrs.optionFont).weight, 'FontWeight.Lighter')

    let optionFont2: string = await selectOptionFont2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(optionFont2).$attrs.optionFont).weight, 'FontWeight.Normal')

    let optionFont3: string = await selectOptionFont3.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(optionFont3).$attrs.optionFont).weight, 'FontWeight.Regular')

    let optionFont4: string = await selectOptionFont4.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(optionFont4).$attrs.optionFont).weight, 'FontWeight.Medium')
    assertEqual(JSON.parse(JSON.parse(optionFont4).$attrs.optionFont).size, '0.00fp')

    let optionFont5: string = await selectOptionFont5.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(optionFont5).$attrs.optionFont).weight, 'FontWeight.Bold')
    assertEqual(JSON.parse(JSON.parse(optionFont5).$attrs.optionFont).size, '16.00fp')

    let optionFont6: string = await selectOptionFont6.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(optionFont6).$attrs.optionFont).weight, 'FontWeight.Bolder')
    assertEqual(JSON.parse(JSON.parse(optionFont6).$attrs.optionFont).size, $r('app.string.size'))
    assertEqual(JSON.parse(JSON.parse(optionFont6).$attrs.optionFont).family, 'Arial')

    let optionFont7: string = await selectOptionFont7.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(optionFont7).$attrs.optionFont).weight, '100')
    assertEqual(JSON.parse(JSON.parse(optionFont7).$attrs.optionFont).size, '20.00fp')
    assertEqual(JSON.parse(JSON.parse(optionFont7).$attrs.optionFont).family, 'TESTFONT')
    assertEqual(JSON.parse(JSON.parse(optionFont7).$attrs.optionFont).style, 'FontStyle.Normal')

    await button.tap()
    let optionFont8: string = await selectOptionFont7.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(optionFont8).$attrs.optionFont).weight, '200')
    assertEqual(JSON.parse(JSON.parse(optionFont8).$attrs.optionFont).size, '40.00fp')
    assertEqual(JSON.parse(JSON.parse(optionFont8).$attrs.optionFont).style, 'FontStyle.Italic')
  }, 0)
}