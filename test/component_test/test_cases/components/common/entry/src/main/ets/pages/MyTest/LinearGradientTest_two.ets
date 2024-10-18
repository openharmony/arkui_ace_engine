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
import { assertEqual, assertTrue, assertFalse } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function linearGradientTest_two() {
  /*
  * 使用List组件 LinearGradient属性
  * 找到画面id为listLinearGradient3的List组件
  * 找到画面文本为ButtonLinearGradient1的Button组件
  * 点击button变更listLinearGradient3的LinearGradient属性与期待值GradientDirection.Top
  * 获取listLinearGradient3的LinearGradient属性与期待值 GradientDirection.Top比对
  * 点击button变更listLinearGradient3的LinearGradient属性与期待值GradientDirection.Right
  * 获取listLinearGradient3的LinearGradient属性与期待值 GradientDirection.Right比对
  * 点击button变更listLinearGradient3的LinearGradient属性与期待值GradientDirection.Bottom
  * 获取listLinearGradient3的LinearGradient属性与期待值 GradientDirection.Bottom比对
  * 点击button变更listLinearGradient3的LinearGradient属性与期待值GradientDirection.LeftTop
  * 获取listLinearGradient3的LinearGradient属性与期待值 GradientDirection.LeftTop比对
  * 点击button变更listLinearGradient3的LinearGradient属性与期待值GradientDirection.LeftBottom
  * 获取listLinearGradient3的LinearGradient属性与期待值 GradientDirection.LeftBottom比对
  * 点击button变更listLinearGradient3的LinearGradient属性与期待值 GradientDirection.RightTop
  * 获取listLinearGradient3的LinearGradient属性与期待值 GradientDirection.RightTop比对
  * 点击button变更listLinearGradient3的LinearGradient属性与期待值 GradientDirection.RightBottom
  * 获取listLinearGradient3的LinearGradient属性与期待值 GradientDirection.RightBottom比对
  * 点击button变更listLinearGradient3的LinearGradient属性与期待值 GradientDirection.None
  * 获取listLinearGradient3的LinearGradient属性与期待值 GradientDirection.None比对
  */
  defineTest('linearGradientTest_twoDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('linearGradientTest_twoDemo running')
    let driver: Tester = Tester.create()
    let listLinearGradient3: Component =
      await driver.findComponent(Matcher.create().id('listLinearGradient3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonLinearGradient1').enabled(true))

    await button1.tap()
    let linearGradient1: string = await listLinearGradient3.getInspectorInfo()
    assertEqual(JSON.parse(linearGradient1).$attrs.linearGradient.direction, 'GradientDirection.Top')

    await button1.tap()
    let linearGradient2: string = await listLinearGradient3.getInspectorInfo()
    assertEqual(JSON.parse(linearGradient2).$attrs.linearGradient.direction, 'GradientDirection.Right')

    await button1.tap()
    let linearGradient3: string = await listLinearGradient3.getInspectorInfo()
    assertEqual(JSON.parse(linearGradient3).$attrs.linearGradient.direction, 'GradientDirection.Bottom')

    await button1.tap()
    let linearGradient4: string = await listLinearGradient3.getInspectorInfo()
    assertEqual(JSON.parse(linearGradient4).$attrs.linearGradient.direction, 'GradientDirection.LeftTop')

    await button1.tap()
    let linearGradient5: string = await listLinearGradient3.getInspectorInfo()
    assertEqual(JSON.parse(linearGradient5).$attrs.linearGradient.direction, 'GradientDirection.LeftBottom')

    await button1.tap()
    let linearGradient6: string = await listLinearGradient3.getInspectorInfo()
    assertEqual(JSON.parse(linearGradient6).$attrs.linearGradient.direction, 'GradientDirection.RightTop')

    await button1.tap()
    let linearGradient7: string = await listLinearGradient3.getInspectorInfo()
    assertEqual(JSON.parse(linearGradient7).$attrs.linearGradient.direction, 'GradientDirection.RightBottom')

    await button1.tap()
    let linearGradient8: string = await listLinearGradient3.getInspectorInfo()
    assertEqual(JSON.parse(linearGradient8).$attrs.linearGradient.direction, 'GradientDirection.None')
  }, 0)
}