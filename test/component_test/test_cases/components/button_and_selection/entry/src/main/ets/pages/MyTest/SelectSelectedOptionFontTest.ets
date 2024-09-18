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

export default async function selectSelectedOptionFontTest() {
  /*
   * Select组件 SelectedOptionFont属性
   * 找到画面id为selectSelectedOptionFont1,selectSelectedOptionFont2,selectSelectedOptionFont3,...,selectSelectedOptionFont6,selectSelectedOptionFont7的Select组件
   * 找到画面文本为SelectOptionFont的Button组件
   * 获取selectSelectedOptionFont1的SelectedOptionFont属性与期待值{ weight: 'FontWeight.Lighter' }比对
   * 获取selectSelectedOptionFont2的SelectedOptionFont属性与期待值{ weight: 'FontWeight.Normal' }比对
   * 获取selectSelectedOptionFont3的SelectedOptionFont属性与期待值{ weight: 'FontWeight.Regular' }比对
   * 获取selectSelectedOptionFont4的SelectedOptionFont属性与期待值{ weight: 'FontWeight.Medium', size: '0.00fp' }比对
   * 获取selectSelectedOptionFont5的SelectedOptionFont属性与期待值{ weight: 'FontWeight.Bold', size: '-1.00fp' }比对
   * 获取selectSelectedOptionFont6的SelectedOptionFont属性与期待值{ weight: 'FontWeight.Bolder', size: $r('app.string.size'), family: 'Arial' }比对
   * 获取selectSelectedOptionFont7的SelectedOptionFont属性与期待值{ weight: '100', size: '20.00fp', family: 'TESTFONT', style: 'FontStyle.Normal' }比对
   * 点击button，变更selectSelectedOptionFont7的SelectedOptionFont属性值为{ weight: '200', size: '40.00fp', style: 'FontStyle.Italic' }
   * 获取selectSelectedOptionFont7的SelectedOptionFont属性与期待值{ weight: '200', size: '40.00fp', style: 'FontStyle.Italic' }比对
   */
  defineTest('selectSelectedOptionFontTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('selectSelectedOptionFontTestDemo running')
    let driver: Tester = Tester.create()
    let selectSelectedOptionFont1: Component =
      await driver.findComponent(Matcher.create().id('selectSelectedOptionFont1').enabled(true))
    let selectSelectedOptionFont2: Component =
      await driver.findComponent(Matcher.create().id('selectSelectedOptionFont2').enabled(true))
    let selectSelectedOptionFont3: Component =
      await driver.findComponent(Matcher.create().id('selectSelectedOptionFont3').enabled(true))
    let selectSelectedOptionFont4: Component =
      await driver.findComponent(Matcher.create().id('selectSelectedOptionFont4').enabled(true))
    let selectSelectedOptionFont5: Component =
      await driver.findComponent(Matcher.create().id('selectSelectedOptionFont5').enabled(true))
    let selectSelectedOptionFont6: Component =
      await driver.findComponent(Matcher.create().id('selectSelectedOptionFont6').enabled(true))
    let selectSelectedOptionFont7: Component =
      await driver.findComponent(Matcher.create().id('selectSelectedOptionFont7').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('SelectSelectedOptionFont').enabled(true))

    let selectedOptionFont1: string = await selectSelectedOptionFont1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(selectedOptionFont1).$attrs.selectedOptionFont).weight, 'FontWeight.Lighter')

    let selectedOptionFont2: string = await selectSelectedOptionFont2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(selectedOptionFont2).$attrs.selectedOptionFont).weight, 'FontWeight.Normal')

    let selectedOptionFont3: string = await selectSelectedOptionFont3.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(selectedOptionFont3).$attrs.selectedOptionFont).weight, 'FontWeight.Regular')

    let selectedOptionFont4: string = await selectSelectedOptionFont4.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(selectedOptionFont4).$attrs.selectedOptionFont).weight, 'FontWeight.Medium')
    assertEqual(JSON.parse(JSON.parse(selectedOptionFont4).$attrs.selectedOptionFont).size, '0.00fp')

    let selectedOptionFont5: string = await selectSelectedOptionFont5.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(selectedOptionFont5).$attrs.selectedOptionFont).weight, 'FontWeight.Bold')
    assertEqual(JSON.parse(JSON.parse(selectedOptionFont5).$attrs.selectedOptionFont).size, '-1.00fp')

    let selectedOptionFont6: string = await selectSelectedOptionFont6.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(selectedOptionFont6).$attrs.selectedOptionFont).weight, 'FontWeight.Bolder')
    assertEqual(JSON.parse(JSON.parse(selectedOptionFont6).$attrs.selectedOptionFont).size, $r('app.string.size'))
    assertEqual(JSON.parse(JSON.parse(selectedOptionFont6).$attrs.selectedOptionFont).family, 'Arial')

    let selectedOptionFont7: string = await selectSelectedOptionFont7.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(selectedOptionFont7).$attrs.selectedOptionFont).weight, '100')
    assertEqual(JSON.parse(JSON.parse(selectedOptionFont7).$attrs.selectedOptionFont).size, '20.00fp')
    assertEqual(JSON.parse(JSON.parse(selectedOptionFont7).$attrs.selectedOptionFont).family, 'TESTFONT')
    assertEqual(JSON.parse(JSON.parse(selectedOptionFont7).$attrs.selectedOptionFont).style, 'FontStyle.Normal')

    await button.tap()
    let selectedOptionFont8: string = await selectSelectedOptionFont7.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(selectedOptionFont8).$attrs.selectedOptionFont).weight, '200')
    assertEqual(JSON.parse(JSON.parse(selectedOptionFont8).$attrs.selectedOptionFont).size, '40.00fp')
    assertEqual(JSON.parse(JSON.parse(selectedOptionFont8).$attrs.selectedOptionFont).style, 'FontStyle.Italic')
  }, 0)
}