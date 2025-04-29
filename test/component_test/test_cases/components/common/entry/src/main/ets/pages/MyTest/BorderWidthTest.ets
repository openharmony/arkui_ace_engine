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
import { assertEqual } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function borderWidthTest() {
  /*
   * Text组件 BorderWidth通用属性
   * 找到画面id为textBorderWidth的组件
   * 找到画面text为ButtonBorderWidth的button组件
   * 获取textBorderWidth的BorderWidth属性与期待值 '10px' 比较
   * 点击button，变更textBorderWidth的BorderWidth属性与期待值 10 比较
   * 点击button，变更textBorderWidth的borderWidth属性与期待值 $r('app.string.common_breadth') 比较
   * 点击button，变更textBorderWidth的borderWidth属性与期待值
   * { left: '8px', right: '10px', top: '8px', bottom: '10px' }比较
   * 点击button变更textBorderWidth的borderWidth属性与期待值{ left: 5, right: 5, top: 5, bottom: 5 }比较
   * 点击button变更textBorderWidth的borderWidth属性与期待值
   * { left: $r('app.string.common_breadth'), right: $r('app.string.common_breadth'),
   * top: $r('app.string.common_breadth'), bottom: $r('app.string.common_breadth') }比较
   */
  defineTest('borderWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('borderWidthTestDemo running')
    let driver: Tester = Tester.create()
    let textBorderWidth: Component = await driver.findComponent(Matcher.create().id('textBorderWidth').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonBorderWidth').enabled(true))

    let borderWidth1: string = await textBorderWidth.getInspectorInfo()
    assertEqual(JSON.parse(borderWidth1).$attrs.borderWidth, '10.00px')

    await button.tap()
    let borderWidth2: string = await textBorderWidth.getInspectorInfo()
    assertEqual(JSON.parse(borderWidth2).$attrs.borderWidth, '10.00vp')
    await button.tap()
    let borderWidth3: string = await textBorderWidth.getInspectorInfo()
    assertEqual(JSON.parse(borderWidth3).$attrs.borderWidth, $r('app.string.common_breadth'))

    await button.tap()
    let borderWidth4: string = await textBorderWidth.getInspectorInfo()
    assertEqual(JSON.parse(borderWidth4).$attrs.borderWidth.left, '8.00px')
    assertEqual(JSON.parse(borderWidth4).$attrs.borderWidth.right, '10.00px')
    assertEqual(JSON.parse(borderWidth4).$attrs.borderWidth.top, '8.00px')
    assertEqual(JSON.parse(borderWidth4).$attrs.borderWidth.bottom, '10.00px')

    await button.tap()
    let borderWidth5: string = await textBorderWidth.getInspectorInfo()
    assertEqual(JSON.parse(borderWidth5).$attrs.borderWidth.left, '5.00vp')
    assertEqual(JSON.parse(borderWidth5).$attrs.borderWidth.right, '5.00vp')
    assertEqual(JSON.parse(borderWidth5).$attrs.borderWidth.top, '5.00vp')
    assertEqual(JSON.parse(borderWidth5).$attrs.borderWidth.bottom, '5.00vp')

    await button.tap()
    let borderWidth6: string = await textBorderWidth.getInspectorInfo()
    assertEqual(JSON.parse(borderWidth6).$attrs.borderWidth.left, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(borderWidth6).$attrs.borderWidth.right, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(borderWidth6).$attrs.borderWidth.top, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(borderWidth6).$attrs.borderWidth.bottom, $r('app.string.common_breadth'))
  }, 0)
}