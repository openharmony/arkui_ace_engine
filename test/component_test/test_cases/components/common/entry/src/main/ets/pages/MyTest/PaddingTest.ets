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

export default async function paddingTest() {
  /*
   * Slider组件 Padding通用属性
   * 找到画面id为sliderPadding的组件
   * 找到画面text为ButtonPadding的button组件
   * 获取sliderPadding的Padding属性与期待值 '10.00px' 比较
   * 点击button，变更sliderPadding的Padding属性为10
   * 获取sliderPadding的Padding属性与期待值 '10.00vp' 比较
   * 点击button，变更sliderPadding的Padding属性为$r('app.string.common_breadth')
   * 获取sliderPadding的Padding属性与期待值 $r('app.string.common_breadth') 比较
   * 点击button，变更sliderPadding的Padding属性为{ left: '8.00px', right: '10.00px', top: '8.00px', bottom: '10.00px' }
   * 获取sliderPadding的Padding属性与期待值 { left: '8.00px', right: '10.00px', top: '8.00px', bottom: '10.00px' } 比较
   * 点击button，变更sliderPadding的Padding属性为{ left: 5, right: 5, top: 5, bottom: 5 }
   * 获取sliderPadding的Padding属性与期待值 { left: 5, right: 5, top: 5, bottom: 5 } 比较
   * 点击button，变更sliderPadding的Padding属性为{ left: $r('app.string.common_breadth'), right: $r('app.string.common_breadth'),
   * top: $r('app.string.common_breadth'), bottom: $r('app.string.common_breadth') }
   * 获取sliderPadding的Padding属性与期待值 { left: $r('app.string.common_breadth'), right: $r('app.string.common_breadth'),
   * top: $r('app.string.common_breadth'), bottom: $r('app.string.common_breadth') } 比较
   */
  defineTest('paddingTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('paddingTestDemo running')
    let driver: Tester = Tester.create()
    let sliderPadding: Component = await driver.findComponent(Matcher.create().id('sliderPadding').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonPadding').enabled(true))
    let padding1: string = await sliderPadding.getInspectorInfo()
    assertEqual(JSON.parse(padding1).$attrs.padding, '10.00px')

    await button.tap()
    let padding2: string = await sliderPadding.getInspectorInfo()
    assertEqual(JSON.parse(padding2).$attrs.padding, '10.00vp')

    await button.tap()
    let padding3: string = await sliderPadding.getInspectorInfo()
    assertEqual(JSON.parse(padding3).$attrs.padding, $r('app.string.common_breadth'))

    await button.tap()
    let padding4: string = await sliderPadding.getInspectorInfo()
    assertEqual(JSON.parse(padding4)
      .$attrs
      .padding
      .left, '8.00px')
    assertEqual(JSON.parse(padding4)
      .$attrs
      .padding
      .right, '10.00px')
    assertEqual(JSON.parse(padding4)
      .$attrs
      .padding
      .top, '8.00px')
    assertEqual(JSON.parse(padding4)
      .$attrs
      .padding
      .bottom, '10.00px')

    await button.tap()
    let padding5: string = await sliderPadding.getInspectorInfo()
    assertEqual(JSON.parse(padding5)
      .$attrs
      .padding
      .left, 5)
    assertEqual(JSON.parse(padding5)
      .$attrs
      .padding
      .right, 5)
    assertEqual(JSON.parse(padding5)
      .$attrs
      .padding
      .top, 5)
    assertEqual(JSON.parse(padding5)
      .$attrs
      .padding
      .bottom, 5)

    await button.tap()
    let padding6: string = await sliderPadding.getInspectorInfo()
    assertEqual(JSON.parse(padding6)
      .$attrs
      .padding
      .left, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(padding6)
      .$attrs
      .padding
      .right, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(padding6)
      .$attrs
      .padding
      .top, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(padding6)
      .$attrs
      .padding
      .bottom, $r('app.string.common_breadth'))
  }, 0)
}