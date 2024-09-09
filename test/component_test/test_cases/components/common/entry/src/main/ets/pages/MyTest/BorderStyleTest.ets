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

export default async function borderStyleTest() {
  /*
   * Text组件 BorderStyle通用属性
   * 找到画面id为textBorderStyle的组件
   * 找到画面text为ButtonBorderStyle的button组件
   * 获取textBorderStyle的BorderStyle属性与期待值BorderStyle.Dotted比较
   * 点击button，变更textBorderStyle的BorderStyle属性与期待值BorderStyle.Dashed比较
   * 点击button，变更textBorderStyle的BorderStyle属性与期待值BorderStyle.Solid比较
   * 点击button，变更textBorderStyle的BorderStyle属性与期待值
   * { left: BorderStyle.Dotted, right: BorderStyle.Dotted,
   * top: BorderStyle.Dotted, bottom: BorderStyle.Dotted }比较
   * 点击button，变更textBorderStyle的BorderStyle属性与期待值
   * { left: BorderStyle.Dashed, right: BorderStyle.Dashed,
   * top: BorderStyle.Dashed, bottom: BorderStyle.Dashed }比较
   * 点击button，变更textBorderStyle的BorderStyle属性与期待值
   * { left: BorderStyle.Solid, right: BorderStyle.Solid,
   * top: BorderStyle.Solid, bottom: BorderStyle.Solid }比较
   */
  defineTest('borderStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('borderStyleTestDemo running')
    let driver: Tester = Tester.create()
    let textBorderStyle: Component = await driver.findComponent(Matcher.create().id('textBorderStyle').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonBorderStyle').enabled(true))

    let borderStyle1: string = await textBorderStyle.getInspectorInfo()
    assertEqual(JSON.parse(borderStyle1).$attrs.borderStyle, 'BorderStyle.Dotted')

    await button.tap()
    let borderStyle2: string = await textBorderStyle.getInspectorInfo()
    assertEqual(JSON.parse(borderStyle2).$attrs.borderStyle, 'BorderStyle.Dashed')

    await button.tap()
    let borderStyle3: string = await textBorderStyle.getInspectorInfo()
    assertEqual(JSON.parse(borderStyle3).$attrs.borderStyle, 'BorderStyle.Solid')

    await button.tap()
    let borderStyle4: string = await textBorderStyle.getInspectorInfo()
    assertEqual(JSON.parse(borderStyle4).$attrs.borderStyle.left, 'BorderStyle.Dotted')
    assertEqual(JSON.parse(borderStyle4).$attrs.borderStyle.right, 'BorderStyle.Dotted')
    assertEqual(JSON.parse(borderStyle4).$attrs.borderStyle.top, 'BorderStyle.Dotted')
    assertEqual(JSON.parse(borderStyle4).$attrs.borderStyle.bottom, 'BorderStyle.Dotted')

    await button.tap()
    let borderStyle5: string = await textBorderStyle.getInspectorInfo()
    assertEqual(JSON.parse(borderStyle5).$attrs.borderStyle.left, 'BorderStyle.Dashed')
    assertEqual(JSON.parse(borderStyle5).$attrs.borderStyle.right, 'BorderStyle.Dashed')
    assertEqual(JSON.parse(borderStyle5).$attrs.borderStyle.top, 'BorderStyle.Dashed')
    assertEqual(JSON.parse(borderStyle5).$attrs.borderStyle.bottom, 'BorderStyle.Dashed')

    await button.tap()
    let borderStyle6: string = await textBorderStyle.getInspectorInfo()
    assertEqual(JSON.parse(borderStyle6).$attrs.borderStyle.left, 'BorderStyle.Solid')
    assertEqual(JSON.parse(borderStyle6).$attrs.borderStyle.right, 'BorderStyle.Solid')
    assertEqual(JSON.parse(borderStyle6).$attrs.borderStyle.top, 'BorderStyle.Solid')
    assertEqual(JSON.parse(borderStyle6).$attrs.borderStyle.bottom, 'BorderStyle.Solid')
  }, 0)
}