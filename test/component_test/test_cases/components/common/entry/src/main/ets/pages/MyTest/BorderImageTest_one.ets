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
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function borderImageTest_one() {
  /*
   * Text组件 BorderImage属性
   * 找到画面id为textBorderImage1的组件
   * 找到画面text为ButtonBorderImage1的button组件
   * 获取textBorderImage1的borderImage属性与期待值
   * { outset: '10.00px', repeat: RepeatMode.Repeat, fill: ture }比较
   * 点击button，变更textBorderImage1的borderImage属性为{ outset: 10.00px, repeat: RepeatMode.Stretch }
   * 获取textBorderImage1的borderImage属性与期待值{ outset: 10.00px , repeat: RepeatMode.Stretch }比较
   * 点击button，变更textBorderImage1的borderImage属性为
   * { outset: $r('app.string.common_breadth'), repeat: RepeatMode.Round }
   * 获取textBorderImage1的borderImage属性与期待值
   * { outset: $r('app.string.common_breadth'), repeat: RepeatMode.Round }比较
   * 点击button，变更textBorderImage1的borderImage属性为
   * { outset: { left: '8.00px', right: '10.00px', top: '8.00px', bottom: '10.00px' }, repeat: RepeatMode.Space }
   * 获取textBorderImage1的borderImage属性与期待值
   * { outset: { left: '8.00px', right: '10.00px', top: '8.00px', bottom: '10.00px' }, repeat: RepeatMode.Space }比较
   * 点击button，变更borderImage属性为{ outset: { left: 5, right: 5, top: 5, bottom: 5 } }
   * 获取textBorderImage1的borderImage属性与期待值{ outset: { left: 5, right: 5, top: 5, bottom: 5 } }比较
   * 点击button变更borderImage属性为{ outset: { left: $r('app.string.common_breadth'),
   * right: $r('app.string.common_breadth'), top: $r('app.string.common_breadth'),
   * bottom: $r('app.string.common_breadth') } }
   * 获取textBorderImage1的borderImage属性与期待值{ outset: { left: $r('app.string.common_breadth'),
   * right: $r('app.string.common_breadth'), top: $r('app.string.common_breadth'),
   * bottom: $r('app.string.common_breadth') } }比较
   */
  defineTest('borderImageTest_oneDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('borderImageTest_oneDemo running')
    let driver: Tester = Tester.create()
    let textBorderImage1: Component = await driver.findComponent(Matcher.create().id('textBorderImage1').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonBorderImage1').enabled(true))

    let borderImage1: string = await textBorderImage1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(borderImage1).$attrs.borderImage).outset, '10.00px')
    assertEqual(JSON.parse(JSON.parse(borderImage1).$attrs.borderImage).repeat, 'RepeatMode.Repeat')
    assertTrue(JSON.parse(JSON.parse(borderImage1).$attrs.borderImage).fill)

    await button.tap()
    let borderImage2: string = await textBorderImage1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(borderImage2).$attrs.borderImage).outset, '10.00vp')
    assertEqual(JSON.parse(JSON.parse(borderImage2).$attrs.borderImage).repeat, 'RepeatMode.Stretch')

    await button.tap()
    let borderImage3: string = await textBorderImage1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(borderImage3).$attrs.borderImage).outset, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(JSON.parse(borderImage3).$attrs.borderImage).repeat, 'RepeatMode.Round')

    await button.tap()
    let borderImage4: string = await textBorderImage1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(borderImage4).$attrs.borderImage).outset,
      'left: [8.00px] right: [10.00px] top: [8.00px] bottom: [10.00px]')
    assertEqual(JSON.parse(JSON.parse(borderImage4).$attrs.borderImage).repeat, 'RepeatMode.Space')

    await button.tap()
    let borderImage5: string = await textBorderImage1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(borderImage5).$attrs.borderImage).outset,
      'left: [5.00vp] right: [5.00vp] top: [5.00vp] bottom: [5.00vp]')

    await button.tap()
    let borderImage6: string = await textBorderImage1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(borderImage6).$attrs.borderImage).outset.left, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(JSON.parse(borderImage6).$attrs.borderImage).outset.right, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(JSON.parse(borderImage6).$attrs.borderImage).outset.top, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(JSON.parse(borderImage6).$attrs.borderImage).outset.bottom, $r('app.string.common_breadth'))
  }, 0)
}