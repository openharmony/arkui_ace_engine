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
import {
  assertEqual,
  assertFalse,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function marginTest_two() {
  /*
   * Text组件 Margin通用属性
   * 找到画面id为 textMargin2 textMargin3 textMargin4的组件
   * 获取textMargin2的Margin属性与期待值
   * { left: '8.00px', right: '10.00px', top: '8.00px', bottom: '10.00px' }比较
   * 获取textMargin3的Margin属性与期待值
   * { left: '5.00vp', right: '5.00vp', top: '5.00vp', bottom: '5.00vp' }比较
   * 获取textMargin4的Margin属性与期待值
   * { left: $r('app.string.common_breadth'), right: $r('app.string.common_breadth'),
   * top: $r('app.string.common_breadth'), bottom: $r('app.string.common_breadth') }比较
   */
  defineTest('marginTest_twoDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('marginTest_twoDemo running')
    let driver: Tester = Tester.create()
    let textMargin2: Component = await driver.findComponent(Matcher.create().id('textMargin2').enabled(true))
    let textMargin3: Component = await driver.findComponent(Matcher.create().id('textMargin3').enabled(true))
    let textMargin4: Component = await driver.findComponent(Matcher.create().id('textMargin4').enabled(true))

    let information1: string = await textMargin2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(information1).$attrs.margin).left, '8.00px')
    assertEqual(JSON.parse(JSON.parse(information1).$attrs.margin).right, '10.00px')
    assertEqual(JSON.parse(JSON.parse(information1).$attrs.margin).top, '8.00px')
    assertEqual(JSON.parse(JSON.parse(information1).$attrs.margin).bottom, '10.00px')

    let information2: string = await textMargin3.getInspectorInfo()
    assertFalse(JSON.parse(information2).$attrs.margin == '5.00vp')
    assertEqual(JSON.parse(JSON.parse(information2).$attrs.margin).left, '5.00vp')
    assertEqual(JSON.parse(JSON.parse(information2).$attrs.margin).right, '5.00vp')
    assertEqual(JSON.parse(JSON.parse(information2).$attrs.margin).top, '5.00vp')
    assertEqual(JSON.parse(JSON.parse(information2).$attrs.margin).bottom, '5.00vp')

    let information3: string = await textMargin4.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(information3).$attrs.margin).left, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(JSON.parse(information3).$attrs.margin).right, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(JSON.parse(information3).$attrs.margin).top, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(JSON.parse(information3).$attrs.margin).bottom, $r('app.string.common_breadth'))
  }, 0)
}