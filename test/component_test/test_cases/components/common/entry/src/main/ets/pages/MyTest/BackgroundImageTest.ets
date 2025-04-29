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
  assertFalse,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function backgroundImageTest() {
  /*
   * Row组件 BackgroundImage属性
   * 找到画面id为rowBackgroundImage的Row组件
   * 找到画面text为ButtonBackgroundImage的button组件
   * 获取rowBackgroundImage的BackgroundImage的src属性与期待值 '../../../resources/base/media/b.jpg' 比较
   * 获取rowBackgroundImage的BackgroundImage的repeat属性与期待值 ImageRepeat.NoRepeat 比较
   * 点击button，变更rowBackgroundImage的BackgroundImage的src属性与期待值 $r('app.media.icon') 比较
   * rowBackgroundImage的BackgroundImage的repeat属性与期待值 ImageRepeat.X 比较
   * 点击button，变更rowBackgroundImage的BackgroundImage的repeat属性与期待值 ImageRepeat.Y 比较
   * 点击button，变更rowBackgroundImage的BackgroundImage的repeat属性与期待值 ImageRepeat.XY 比较
   */

  defineTest('backgroundImageDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('backgroundImageDemo running')
    let driver: Tester = Tester.create()
    let rowBackgroundImage: Component =
      await driver.findComponent(Matcher.create().id('rowBackgroundImage').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonBackgroundImage').enabled(true))

    let backgroundImage1: string = await rowBackgroundImage.getInspectorInfo()
    assertFalse(JSON.parse(backgroundImage1).$attrs.backGroundImage == undefined)
    assertEqual(JSON.parse(backgroundImage1).$attrs.backGroundImage.src, '../../../resources/base/media/b.jpg')
    assertEqual(JSON.parse(backgroundImage1).$attrs.backGroundImage.repeat, ImageRepeat.NoRepeat)

    await button.tap()
    let backgroundImage2: string = await rowBackgroundImage.getInspectorInfo()
    assertEqual(JSON.parse(backgroundImage2).$attrs.backGroundImage.src, $r('app.media.app_icon'))
    assertEqual(JSON.parse(backgroundImage2).$attrs.backGroundImage.repeat, ImageRepeat.X)

    await button.tap()
    let backgroundImage3: string = await rowBackgroundImage.getInspectorInfo()
    assertEqual(JSON.parse(backgroundImage3).$attrs.backGroundImage.repeat, ImageRepeat.Y)

    await button.tap()
    let backgroundImage4: string = await rowBackgroundImage.getInspectorInfo()
    assertEqual(JSON.parse(backgroundImage4).$attrs.backGroundImage.repeat, ImageRepeat.XY)
  }, 0)
}
