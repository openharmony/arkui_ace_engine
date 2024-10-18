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

export default async function sliderTrackBorderRadiusTest() {
  /*
   * Slider组件 TrackBorderRadius属性
   * 找到画面id为trackBorderRadius1，trackBorderRadius2的Slider组件
   * 找到画面文本为SliderTrackBorderRadius的Button组件
   * 获取sliderTrackBorderRadius1的TrackBorderRadius属性与期待值'10.00px'比对
   * 获取sliderTrackBorderRadius2的TrackBorderRadius属性与期待值'20.00vp'比对
   * 点击button，变更sliderTrackBorderRadius2的TrackBorderRadius属性值为$r('app.string.radius_number')
   * 获取sliderTrackBorderRadius2的TrackBorderRadius属性与期待值$r('app.string.radius_number')比对
   */
  defineTest('sliderTrackBorderRadiusTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('sliderTrackBorderRadiusTestDemo running')
    let driver: Tester = Tester.create()
    let sliderTrackBorderRadius1: Component =
      await driver.findComponent(Matcher.create().id('trackBorderRadius1').enabled(true))
    let sliderTrackBorderRadius2: Component =
      await driver.findComponent(Matcher.create().id('trackBorderRadius2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('SliderTrackBorderRadius').enabled(true))

    let trackBorderRadius1: string = await sliderTrackBorderRadius1.getInspectorInfo()
    assertEqual(JSON.parse(trackBorderRadius1).$attrs.trackBorderRadius, '10.00px')

    let trackBorderRadius2: string = await sliderTrackBorderRadius2.getInspectorInfo()
    assertEqual(JSON.parse(trackBorderRadius2).$attrs.trackBorderRadius, '20.00vp')

    await button.tap()
    let trackBorderRadius3: string = await sliderTrackBorderRadius2.getInspectorInfo()
    assertEqual(JSON.parse(trackBorderRadius3).$attrs.trackBorderRadius, $r('app.string.radius_number'))
  }, 0)
}