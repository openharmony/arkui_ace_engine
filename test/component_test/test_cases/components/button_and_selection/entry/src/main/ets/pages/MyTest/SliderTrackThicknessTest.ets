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

export default async function sliderTrackThicknessTest() {
  /*
   * Slider组件 TrackThickness属性
   * 找到画面id为sliderTrackThickness1，sliderTrackThickness2，sliderTrackThickness3的Slider组件
   * 找到画面文本为SliderTrackThickness的Button组件
   * 获取sliderTrackThickness1的TrackThickness属性与期待值'20.00vp'比对
   * 获取sliderTrackThickness2的TrackThickness属性与期待值'15.00px'比对
   * 获取sliderTrackThickness3的TrackThickness属性与期待值'35.00vp'比对
   * 点击button，变更sliderTrackThickness3的TrackThickness属性值为$r('app.string.track_thickness')
   * 获取sliderTrackThickness3的TrackThickness属性与期待值$r('app.string.track_thickness')比对
   */
  defineTest('sliderTrackThicknessTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('sliderTrackThicknessTestDemo running')
    let driver: Tester = Tester.create()
    let sliderTrackThickness1: Component =
      await driver.findComponent(Matcher.create().id('sliderTrackThickness1').enabled(true))
    let sliderTrackThickness2: Component =
      await driver.findComponent(Matcher.create().id('sliderTrackThickness2').enabled(true))
    let sliderTrackThickness3: Component =
      await driver.findComponent(Matcher.create().id('sliderTrackThickness3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('SliderTrackThickness').enabled(true))

    let trackThickness1: string = await sliderTrackThickness1.getInspectorInfo()
    assertEqual(JSON.parse(trackThickness1).$attrs.trackThickness, '20.00vp')

    let trackThickness2: string = await sliderTrackThickness2.getInspectorInfo()
    assertEqual(JSON.parse(trackThickness2).$attrs.trackThickness, '15.00px')

    let trackThickness3: string = await sliderTrackThickness3.getInspectorInfo()
    assertEqual(JSON.parse(trackThickness3).$attrs.trackThickness, '35.00vp')

    await button.tap()
    let trackThickness4: string = await sliderTrackThickness3.getInspectorInfo()
    assertEqual(JSON.parse(trackThickness4).$attrs.trackThickness, $r('app.string.track_thickness'))
  }, 0)
}