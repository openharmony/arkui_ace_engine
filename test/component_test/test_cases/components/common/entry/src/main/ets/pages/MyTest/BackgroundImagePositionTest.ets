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

export default async function backgroundImagePositionTest() {
  /*
  * 使用Menu、Marquee组件 BackgroundImagePosition属性
  * 找到画面id为menuBackgroundImagePosition1,menuBackgroundImagePosition2,
  * menuBackgroundImagePosition3,marqueeBackgroundImagePosition的Menu与Marquee组件
  * 找到画面文本为BackgroundImagePosition的Button组件
  * 获取menuBackgroundImagePosition1的BackgroundImagePosition的x属性与期待值30比对
  * 获取menuBackgroundImagePosition1的BackgroundImagePosition的y属性与期待值45比对
  * 获取menuBackgroundImagePosition2的BackgroundImagePosition的x属性与期待值10比对
  * 获取menuBackgroundImagePosition2的BackgroundImagePosition的y属性与期待值15比对
  * 获取marqueeBackgroundImagePosition的BackgroundImagePosition的x属性与期待值$r('app.string.commonPosition_length')比对
  * 获取marqueeBackgroundImagePosition的BackgroundImagePosition的y属性与期待值$r('app.string.commonPosition_length')比对
  * 获取menuBackgroundImagePosition3的BackgroundImagePosition属性与期待值Alignment.TopStart比对
  * 点击button，变更menuBackgroundImagePosition3的BackgroundImagePosition属性值为Alignment.Top
  * 获取menuBackgroundImagePosition3的BackgroundImagePosition属性与期待值Alignment.Top比对
  * 点击button，变更menuBackgroundImagePosition3的BackgroundImagePosition属性值为Alignment.TopEnd
  * 获取menuBackgroundImagePosition3的BackgroundImagePosition属性与期待值Alignment.TopEnd
  * 点击button，变更menuBackgroundImagePosition3的BackgroundImagePosition属性值为Alignment.Start
  * 获取menuBackgroundImagePosition3的BackgroundImagePosition属性与期待值Alignment.Start比对
  * 点击button，变更menuBackgroundImagePosition3的BackgroundImagePosition属性值为Alignment.Center
  * 获取menuBackgroundImagePosition3的BackgroundImagePosition属性与期待值Alignment.Center比对
  * 点击button，变更menuBackgroundImagePosition3的BackgroundImagePosition属性值为Alignment.End
  * 获取menuBackgroundImagePosition3的BackgroundImagePosition属性与期待值Alignment.End比对
  * 点击button，变更menuBackgroundImagePosition3的BackgroundImagePosition属性值为Alignment.BottomStart
  * 获取menuBackgroundImagePosition3的BackgroundImagePosition属性与期待值Alignment.BottomStart比对
  * 点击button，变更menuBackgroundImagePosition3的BackgroundImagePosition属性值为Alignment.Bottom
  * 获取menuBackgroundImagePosition3的BackgroundImagePosition属性与期待值Alignment.Bottom比对
  * 点击button，变更menuBackgroundImagePosition3的BackgroundImagePosition属性值为Alignment.BottomEnd
  * 获取menuBackgroundImagePosition3的BackgroundImagePosition属性与期待值Alignment.BottomEnd比对
  */
  defineTest('backgroundImagePositionTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('backgroundImagePositionTestDemo running')
    let driver: Tester = Tester.create()
    let menuBackgroundImagePosition1: Component =
      await driver.findComponent(Matcher.create().id('menuBackgroundImagePosition1').enabled(true))
    let menuBackgroundImagePosition2: Component =
      await driver.findComponent(Matcher.create().id('menuBackgroundImagePosition2').enabled(true))
    let menuBackgroundImagePosition3: Component =
      await driver.findComponent(Matcher.create().id('menuBackgroundImagePosition3').enabled(true))
    let marqueeBackgroundImagePosition: Component =
      await driver.findComponent(Matcher.create().id('marqueeBackgroundImagePosition').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('BackgroundImagePosition').enabled(true))
    let backgroundImagePosition1: string = await menuBackgroundImagePosition1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(backgroundImagePosition1).$attrs.backgroundImagePosition).x, 30)
    assertEqual(JSON.parse(JSON.parse(backgroundImagePosition1).$attrs.backgroundImagePosition).y, 45)
    let backgroundImagePosition2: string = await menuBackgroundImagePosition2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(backgroundImagePosition2).$attrs.backgroundImagePosition).x, 10)
    assertEqual(JSON.parse(JSON.parse(backgroundImagePosition2).$attrs.backgroundImagePosition).y, 15)
    let backgroundImagePosition3: string = await marqueeBackgroundImagePosition.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(backgroundImagePosition3).$attrs.backgroundImagePosition).x,
      $r('app.string.commonPosition_length'))
    assertEqual(JSON.parse(JSON.parse(backgroundImagePosition3).$attrs.backgroundImagePosition).y,
      $r('app.string.commonPosition_length'))
    let backgroundImagePosition4: string = await menuBackgroundImagePosition3.getInspectorInfo()
    assertEqual(JSON.parse(backgroundImagePosition4).$attrs.backgroundImagePosition, 'Alignment.TopStart')

    await button.tap()
    let backgroundImagePosition5: string = await menuBackgroundImagePosition3.getInspectorInfo()
    assertEqual(JSON.parse(backgroundImagePosition5).$attrs.backgroundImagePosition, 'Alignment.Top')

    await button.tap()
    let backgroundImagePosition6: string = await menuBackgroundImagePosition3.getInspectorInfo()
    assertEqual(JSON.parse(backgroundImagePosition6).$attrs.backgroundImagePosition, 'Alignment.TopEnd')

    await button.tap()
    let backgroundImagePosition7: string = await menuBackgroundImagePosition3.getInspectorInfo()
    assertEqual(JSON.parse(backgroundImagePosition7).$attrs.backgroundImagePosition, 'Alignment.Start')

    await button.tap()
    let backgroundImagePosition8: string = await menuBackgroundImagePosition3.getInspectorInfo()
    assertEqual(JSON.parse(backgroundImagePosition8).$attrs.backgroundImagePosition, 'Alignment.Center')

    await button.tap()
    let backgroundImagePosition9: string = await menuBackgroundImagePosition3.getInspectorInfo()
    assertEqual(JSON.parse(backgroundImagePosition9).$attrs.backgroundImagePosition, 'Alignment.End')

    await button.tap()
    let backgroundImagePosition10: string = await menuBackgroundImagePosition3.getInspectorInfo()
    assertEqual(JSON.parse(backgroundImagePosition10).$attrs.backgroundImagePosition, 'Alignment.BottomStart')

    await button.tap()
    let backgroundImagePosition11: string = await menuBackgroundImagePosition3.getInspectorInfo()
    assertEqual(JSON.parse(backgroundImagePosition11).$attrs.backgroundImagePosition, 'Alignment.Bottom')

    await button.tap()
    let backgroundImagePosition12: string = await menuBackgroundImagePosition3.getInspectorInfo()
    assertEqual(JSON.parse(backgroundImagePosition12).$attrs.backgroundImagePosition, 'Alignment.BottomEnd')
  }, 0)
}