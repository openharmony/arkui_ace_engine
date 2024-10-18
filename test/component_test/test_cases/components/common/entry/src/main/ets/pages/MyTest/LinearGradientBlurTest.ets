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
import { assertEqual, assertFalse } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function linearGradientBlurTest() {
  /*
   * image组件 LinearGradientBlur通用属性
   * 找到画面id为imageLinearGradientBlur的组件
   * 找到画面text为ButtonLinearGradientBlur的button组件
   * 获取imageLinearGradientBlur的LinearGradientBlur属性与期待值{ options: { direction: GradientDirection.Left } }比较
   * 点击button，变更linearGradientBlur属性中的LinearGradientBlur为{ options: { direction: GradientDirection.Top } }
   * 获取imageLinearGradientBlur的LinearGradientBlur属性与期待值{ options: { direction: GradientDirection.Top } }比较
   * 点击button，变更linearGradientBlur属性中的LinearGradientBlur为{ options: { direction: GradientDirection.Right } }
   * 获取imageLinearGradientBlur的LinearGradientBlur属性与期待值{ options: { direction: GradientDirection.Right } }比较
   * 点击button，变更linearGradientBlur属性中的LinearGradientBlur为{ options: { direction: GradientDirection.Bottom } }
   * 获取imageLinearGradientBlur的LinearGradientBlur属性与期待值{ options: { direction: GradientDirection.Bottom } }比较
   * 点击button，变更linearGradientBlur属性中的LinearGradientBlur为{ options: { direction: GradientDirection.LeftTop } }
   * 获取imageLinearGradientBlur的LinearGradientBlur属性与期待值{ options: { direction: GradientDirection.LeftTop } }比较
   * 点击button，变更linearGradientBlur属性中的LinearGradientBlur为{ options: { direction: GradientDirection.LeftBottom } }
   * 获取imageLinearGradientBlur的LinearGradientBlur属性与期待值{ options: { direction: GradientDirection.LeftBottom } }比较
   * 点击button，变更linearGradientBlur属性中的LinearGradientBlur为{ options: { direction: GradientDirection.RightTop } }
   * 获取imageLinearGradientBlur的LinearGradientBlur属性与期待值{ options: { direction: GradientDirection.RightTop } }比较
   * 点击button，变更linearGradientBlur属性中的LinearGradientBlur为{ options: { direction: GradientDirection.RightBottom } }
   * 获取imageLinearGradientBlur的LinearGradientBlur属性与期待值{ options: { direction: GradientDirection.RightBottom } }比较
   * 点击button，变更linearGradientBlur属性中的LinearGradientBlur为{ options: { direction: GradientDirection.None } }
   * 获取imageLinearGradientBlur的LinearGradientBlur属性与期待值{ options: { direction: GradientDirection.None } }比较
   */
  defineTest('linearGradientBlurTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('linearGradientBlurTestDemo running')
    let driver: Tester = Tester.create()
    let imageLinearGradientBlur: Component =
      await driver.findComponent(Matcher.create().id('imageLinearGradientBlur').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonLinearGradientBlur').enabled(true))
    let linearGradientBlur1: string = await imageLinearGradientBlur.getInspectorInfo()
    assertFalse(JSON.parse(linearGradientBlur1).$attrs.linearGradientBlur == undefined)

    assertEqual(JSON.parse(linearGradientBlur1)
      .$attrs
      .linearGradientBlur
      .direction, GradientDirection.Left)

    await button.tap()
    let linearGradientBlur2: string = await imageLinearGradientBlur.getInspectorInfo()
    assertEqual(JSON.parse(linearGradientBlur2)
      .$attrs
      .linearGradientBlur
      .options
      .direction, GradientDirection.Top)

    await button.tap()
    let linearGradientBlur3: string = await imageLinearGradientBlur.getInspectorInfo()
    assertEqual(JSON.parse(linearGradientBlur3)
      .$attrs
      .linearGradientBlur
      .options
      .direction, GradientDirection.Right)

    await button.tap()
    let linearGradientBlur4: string = await imageLinearGradientBlur.getInspectorInfo()
    assertEqual(JSON.parse(linearGradientBlur4)
      .$attrs
      .linearGradientBlur
      .options
      .direction, GradientDirection.Bottom)

    await button.tap()
    let linearGradientBlur5: string = await imageLinearGradientBlur.getInspectorInfo()
    assertEqual(JSON.parse(linearGradientBlur5)
      .$attrs
      .linearGradientBlur
      .options
      .direction, GradientDirection.LeftTop)

    await button.tap()
    let linearGradientBlur6: string = await imageLinearGradientBlur.getInspectorInfo()
    assertEqual(JSON.parse(linearGradientBlur6)
      .$attrs
      .linearGradientBlur
      .options
      .direction, GradientDirection.LeftBottom)

    await button.tap()
    let linearGradientBlur7: string = await imageLinearGradientBlur.getInspectorInfo()
    assertEqual(JSON.parse(linearGradientBlur7)
      .$attrs
      .linearGradientBlur
      .options
      .direction, GradientDirection.RightTop)

    await button.tap()
    let linearGradientBlur8: string = await imageLinearGradientBlur.getInspectorInfo()
    assertEqual(JSON.parse(linearGradientBlur8)
      .$attrs
      .linearGradientBlur
      .options
      .direction, GradientDirection.RightBottom)

    await button.tap()
    let linearGradientBlur9: string = await imageLinearGradientBlur.getInspectorInfo()
    assertEqual(JSON.parse(linearGradientBlur9)
      .$attrs
      .linearGradientBlur
      .options
      .direction, GradientDirection.None)
  }, 0)
}