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

export default async function backgroundImageSizeTest() {
  /*
  * 使用Row容器 BackgroundImageSize属性
  * 找到画面id为rowBackgroundImageSize1,rowBackgroundImageSize2,
  * columnBackgroundImageSize的row与column组件
  * 找到画面文本为ButtonBackgroundImageSize的Button组件
  * 获取rowBackgroundImageSize1的BackgroundImageSize的height属性与期待值'140.00px'比对
  * 获取rowBackgroundImageSize2的BackgroundImageSize的width属性与期待值‘0.00px'比对
  * 获取rowBackgroundImageSize2的BackgroundImageSize的height属性与期待值‘0.00px'比对
  * 获取columnBackgroundImageSize的BackgroundImageSize的width属性与期待值'250.00px'比对
  * 获取columnBackgroundImageSize的BackgroundImageSize的height属性与期待值'140.00px'比对
  * 点击button变更columnBackgroundImageSize的属性
  * 获取columnBackgroundImageSize的BackgroundImageSize的width属性与期待值$r('app.string.commonImage_width')比对
  * 获取columnBackgroundImageSize的BackgroundImageSize的height属性与期待值$r('app.string.commonImage_height')比对
  * 点击button变更columnBackgroundImageSize的属性
  * 获取columnBackgroundImageSize的BackgroundImageSize的width属性与期待值1000比对
  * 获取columnBackgroundImageSize的BackgroundImageSize的height属性与期待值500比对
  * 点击button，变更columnBackgroundImageSize的BackgroundImageSize属性值为ImageSize.Auto
  * 获取columnBackgroundImageSize的BackgroundImageSize属性与期待值ImageSize.Auto比对
  * 点击button，变更columnBackgroundImageSize的BackgroundImageSize属性值为ImageSize.Cover
  * 获取columnBackgroundImageSize的BackgroundImageSize属性与期待值ImageSize.Cover比对
  * 点击button，变更columnBackgroundImageSize的BackgroundImageSize属性值为ImageSize.Contain
  * 获取columnBackgroundImageSize的BackgroundImageSize属性与期待值ImageSize.Contain比对
  */
  defineTest('backgroundImageSizeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('backgroundImageSizeTestDemo running')
    let driver: Tester = Tester.create()
    let rowBackgroundImageSize1: Component =
      await driver.findComponent(Matcher.create().id('rowBackgroundImageSize1').enabled(true))
    let rowBackgroundImageSize2: Component =
      await driver.findComponent(Matcher.create().id('rowBackgroundImageSize2').enabled(true))
    let columnBackgroundImageSize: Component =
      await driver.findComponent(Matcher.create().id('columnBackgroundImageSize').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonBackgroundImageSize').enabled(true))
    let backgroundImageSize1: string = await rowBackgroundImageSize1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(backgroundImageSize1).$attrs.backgroundImageSize).height, '140.00px')
    let backgroundImageSize2: string = await rowBackgroundImageSize2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(backgroundImageSize2).$attrs.backgroundImageSize).width, '0.00px')
    assertEqual(JSON.parse(JSON.parse(backgroundImageSize2).$attrs.backgroundImageSize).height, '0.00px')
    let backgroundImageSize3: string = await columnBackgroundImageSize.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(backgroundImageSize3).$attrs.backgroundImageSize).width, '250.00px')
    assertEqual(JSON.parse(JSON.parse(backgroundImageSize3).$attrs.backgroundImageSize).height, '140.00px')
    await button.tap()
    let backgroundImageSize4: string = await columnBackgroundImageSize.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(backgroundImageSize4).$attrs.backgroundImageSize).width,
      $r('app.string.commonImage_width'))
    assertEqual(JSON.parse(JSON.parse(backgroundImageSize4).$attrs.backgroundImageSize).height,
      $r('app.string.commonImage_height'))
    await button.tap()
    let backgroundImageSize5: string = await columnBackgroundImageSize.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(backgroundImageSize5).$attrs.backgroundImageSize).width, '1000.00px')
    assertEqual(JSON.parse(JSON.parse(backgroundImageSize5).$attrs.backgroundImageSize).height, '500.00px')
    await button.tap()
    let backgroundImageSize6: string = await columnBackgroundImageSize.getInspectorInfo()
    assertEqual(JSON.parse(backgroundImageSize6).$attrs.backgroundImageSize, 'ImageSize.Auto')
    await button.tap()
    let backgroundImageSize7: string = await columnBackgroundImageSize.getInspectorInfo()
    assertEqual(JSON.parse(backgroundImageSize7).$attrs.backgroundImageSize, 'ImageSize.Cover')
    await button.tap()
    let backgroundImageSize8: string = await columnBackgroundImageSize.getInspectorInfo()
    assertEqual(JSON.parse(backgroundImageSize8).$attrs.backgroundImageSize, 'ImageSize.Contain')
  }, 0)
}