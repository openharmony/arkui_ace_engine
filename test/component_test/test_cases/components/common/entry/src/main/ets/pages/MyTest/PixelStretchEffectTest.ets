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

export default async function pixelStretchEffectTest() {
  /*
   * Text组件 PixelStretchEffect通用属性
   * 找到画面id为 textPixelStretchEffect 的组件
   * 找到画面text为 ButtonPixelStretchEffect 的button组件
   * 获取 textPixelStretchEffect 的 PixelStretchEffect.top 属性与期待值 '100.00px' 比对
   * 获取 textPixelStretchEffect 的 PixelStretchEffect.left 属性与期待值 '100.00px' 比对
   * 获取 textPixelStretchEffect 的 PixelStretchEffect.right 属性与期待值 '100.00px' 比对
   * 获取 textPixelStretchEffect 的 PixelStretchEffect.bottom 属性与期待值 '100.00px' 比对
   * 点击button切换属性
   * 获取 textPixelStretchEffect 的 PixelStretchEffect.top 属性与期待值 '50.00px' 比对
   * 获取 textPixelStretchEffect 的 PixelStretchEffect.left 属性与期待值 '50.00px' 比对
   * 获取 textPixelStretchEffect 的 PixelStretchEffect.right 属性与期待值 '50.00px' 比对
   * 获取 textPixelStretchEffect 的 PixelStretchEffect.bottom 属性与期待值 '50.00px' 比对
   * 点击button切换属性
   * 获取 textPixelStretchEffect 的 PixelStretchEffect.top 属性与期待值 $r('app.string.common_breadth') 比对
   * 获取 textPixelStretchEffect 的 PixelStretchEffect.left 属性与期待值 $r('app.string.common_breadth') 比对
   * 获取 textPixelStretchEffect 的 PixelStretchEffect.right 属性与期待值 $r('app.string.common_breadth') 比对
   * 获取 textPixelStretchEffect 的 PixelStretchEffect.bottom 属性与期待值 $r('app.string.common_breadth') 比对
   */
  defineTest('pixelStretchEffectTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('pixelStretchEffectTestDemo running')
    let driver: Tester = Tester.create()
    let textPixelStretchEffect: Component =
      await driver.findComponent(Matcher.create().id('textPixelStretchEffect').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonPixelStretchEffect').enabled(true))
    let pixelStretchEffect1: string = await textPixelStretchEffect.getInspectorInfo()
    assertEqual(JSON.parse(pixelStretchEffect1).$attrs.pixelStretchEffect.top, '100.00px')
    assertEqual(JSON.parse(pixelStretchEffect1).$attrs.pixelStretchEffect.left, '100.00px')
    assertEqual(JSON.parse(pixelStretchEffect1).$attrs.pixelStretchEffect.right, '100.00px')
    assertEqual(JSON.parse(pixelStretchEffect1).$attrs.pixelStretchEffect.bottom, '100.00px')

    await button.tap()
    let pixelStretchEffect2: string = await textPixelStretchEffect.getInspectorInfo()
    assertEqual(JSON.parse(pixelStretchEffect2).$attrs.pixelStretchEffect.top, '50.00vp')
    assertEqual(JSON.parse(pixelStretchEffect2).$attrs.pixelStretchEffect.left, '50.00vp')
    assertEqual(JSON.parse(pixelStretchEffect2).$attrs.pixelStretchEffect.right, '50.00vp')
    assertEqual(JSON.parse(pixelStretchEffect2).$attrs.pixelStretchEffect.bottom, '50.00vp')

    await button.tap()
    let pixelStretchEffect3: string = await textPixelStretchEffect.getInspectorInfo()
    assertEqual(JSON.parse(pixelStretchEffect3).$attrs.pixelStretchEffect.top, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(pixelStretchEffect3).$attrs.pixelStretchEffect.left, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(pixelStretchEffect3).$attrs.pixelStretchEffect.right, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(pixelStretchEffect3).$attrs.pixelStretchEffect.bottom, $r('app.string.common_breadth'))
  }, 0)
}