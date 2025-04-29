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

export default async function borderImageTest_two() {
  /*
   * BorderImage通用属性 Text组件
   * 找到画面id为textBorderImage2的组件
   * 找到画面text为ButtonBorderImage2的button组件
   * 获取textBorderImage2的borderImage属性与期待值
   * { slice: '10px', colors: 'rgb(72 61 139)', direction: GradientDirection.Left}比较
   * 点击button，变更textBorderImage2的borderImage属性与期待值
   * { slice: 10, colors: 0X528B8B, direction: GradientDirection.Top }比较
   * 点击button，变更textBorderImage2的borderImage属性与期待值
   * { slice: $r('app.string.common_breadth'), colors: Color.Red, direction: GradientDirection.Right }比较
   * 点击button，变更textBorderImage2的borderImage属性与期待值
   * { slice: { left: '8px', right: '10px', top: '8px', bottom: '10px' },
   * colors: $r('sys.color.ohos_id_color_text_hyperlink'), direction: GradientDirection.Bottom }比较
   * 点击button变更borderImage属性与期待值
   * { slice: { left: 5, right: 5, top: 5, bottom: 5 },
   * colors: 'rgb(72 61 139)', direction: GradientDirection.LeftTop }比较
   * 点击button变更borderImage属性与期待值
   * { slice: { left: $r('app.string.common_breadth'), right: $r('app.string.common_breadth'),
   * top: $r('app.string.common_breadth'), bottom: $r('app.string.common_breadth')},
   * colors: 0X528B8B, direction: GradientDirection.LeftBottom }比较
   * 点击button变更borderImage属性与期待值
   * { slice: '10px', colors: Color.Red, direction: GradientDirection.RightTop }比较
   * 点击button变更borderImage属性与期待值
   * { slice: 10, colors: $r('sys.color.ohos_id_color_text_hyperlink'),
   * direction: GradientDirection.RightBottom }比较
   * 点击button变更borderImage属性与期待值
   * { slice: $r('app.string.common_breadth'),
   * colors: 'rgb(72 61 139)', direction: GradientDirection.None }比较
   */
  defineTest('borderImageTest_twoDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('borderImageTest_twoDemo running')
    let driver: Tester = Tester.create()
    let textBorderImage2: Component = await driver.findComponent(Matcher.create().id('textBorderImage2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonBorderImage2').enabled(true))
    let borderImage1: string = await textBorderImage2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(borderImage1).$attrs.borderImage).slice, '10.00px')
    assertEqual(JSON.parse(JSON.parse(borderImage1).$attrs.borderImage).colors, 'rgb(72, 61, 139)')
    assertEqual(JSON.parse(JSON.parse(borderImage1).$attrs.borderImage).direction, GradientDirection.Left)

    await button.tap()
    let borderImage2: string = await textBorderImage2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(borderImage2).$attrs.borderImage).slice, 10)
    assertEqual(JSON.parse(JSON.parse(borderImage2).$attrs.borderImage).colors, 0X528B8B)
    assertEqual(JSON.parse(JSON.parse(borderImage2).$attrs.borderImage).direction, GradientDirection.Top)

    await button.tap()
    let borderImage3: string = await textBorderImage2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(borderImage3).$attrs.borderImage).slice, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(JSON.parse(borderImage3).$attrs.borderImage).colors, Color.Red)
    assertEqual(JSON.parse(JSON.parse(borderImage3).$attrs.borderImage).direction, GradientDirection.Right)

    await button.tap()
    let borderImage4: string = await textBorderImage2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(borderImage4).$attrs.borderImage).slice.left, '8px')
    assertEqual(JSON.parse(JSON.parse(borderImage4).$attrs.borderImage).slice.right, '10px')
    assertEqual(JSON.parse(JSON.parse(borderImage4).$attrs.borderImage).slice.top, '8px')
    assertEqual(JSON.parse(JSON.parse(borderImage4).$attrs.borderImage).slice.bottom, '10px')
    assertEqual(JSON.parse(JSON.parse(borderImage4).$attrs.borderImage).colors,
      $r('sys.color.ohos_id_color_text_hyperlink'))
    assertEqual(JSON.parse(JSON.parse(borderImage4).$attrs.borderImage).direction, GradientDirection.Bottom)

    await button.tap()
    let borderImage5: string = await textBorderImage2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(borderImage5).$attrs.borderImage).slice.left, 5)
    assertEqual(JSON.parse(JSON.parse(borderImage5).$attrs.borderImage).slice.right, 5)
    assertEqual(JSON.parse(JSON.parse(borderImage5).$attrs.borderImage).slice.top, 5)
    assertEqual(JSON.parse(JSON.parse(borderImage5).$attrs.borderImage).slice.bottom, 5)
    assertEqual(JSON.parse(JSON.parse(borderImage5).$attrs.borderImage).colors, 'rgb(72, 61, 139)')
    assertEqual(JSON.parse(JSON.parse(borderImage5).$attrs.borderImage).direction, GradientDirection.LeftTop)

    await button.tap()
    let borderImage6: string = await textBorderImage2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(borderImage6).$attrs.borderImage).slice.left, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(JSON.parse(borderImage6).$attrs.borderImage).slice.right, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(JSON.parse(borderImage6).$attrs.borderImage).slice.top, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(JSON.parse(borderImage6).$attrs.borderImage).slice.bottom, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(JSON.parse(borderImage6).$attrs.borderImage).colors, 0X528B8B)
    assertEqual(JSON.parse(JSON.parse(borderImage6).$attrs.borderImage).direction, GradientDirection.LeftBottom)

    await button.tap()
    let borderImage7: string = await textBorderImage2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(borderImage7).$attrs.borderImage).slice, '10px')
    assertEqual(JSON.parse(JSON.parse(borderImage7).$attrs.borderImage).colors, Color.Red)
    assertEqual(JSON.parse(JSON.parse(borderImage7).$attrs.borderImage).direction, GradientDirection.RightTop)

    await button.tap()
    let borderImage8: string = await textBorderImage2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(borderImage8).$attrs.borderImage).slice, 10)
    assertEqual(JSON.parse(JSON.parse(borderImage8).$attrs.borderImage).colors,
      $r('sys.color.ohos_id_color_text_hyperlink'))
    assertEqual(JSON.parse(JSON.parse(borderImage8).$attrs.borderImage).direction, GradientDirection.RightBottom)

    await button.tap()
    let borderImage9: string = await textBorderImage2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(borderImage9).$attrs.borderImage).slice, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(JSON.parse(borderImage9).$attrs.borderImage).colors, 'rgb(72 61 139)')
    assertEqual(JSON.parse(JSON.parse(borderImage9).$attrs.borderImage).direction, GradientDirection.None)
  }, 0)
}