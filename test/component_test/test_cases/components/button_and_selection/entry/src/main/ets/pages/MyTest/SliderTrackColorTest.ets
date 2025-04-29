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

export default async function sliderTrackColorTest() {
  /*
   * Slider组件 TrackColor属性
   * 找到画面id为sliderTrackColor1，sliderTrackColor2的Slider组件
   * 找到画面文本为SliderTrackColor1，SliderTrackColor2的Button组件
   * 获取sliderTrackColor1的TrackColor属性与期待值Color.Red比对
   * 获取sliderTrackColor2的TrackColor属性与期待值'#FF008000'比对
   * 点击button1，变更sliderTrackColor1的TrackColor属性值为'#FFFFFF00'
   * 获取sliderTrackColor1的TrackColor属性与期待值'#FFFFFF00'比对
   * 点击button2，变更sliderTrackColor2的TrackColor属性值为$r('app.color.start_window_background')
   * 获取sliderTrackColor2的TrackColor属性与期待值$r('app.color.start_window_background')比对
   */
  defineTest('sliderTrackColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('sliderTrackColorTestDemo running')
    let driver: Tester = Tester.create()
    let sliderTrackColor1: Component =
      await driver.findComponent(Matcher.create().id('sliderTrackColor1').enabled(true))
    let sliderTrackColor2: Component =
      await driver.findComponent(Matcher.create().id('sliderTrackColor2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SliderTrackColor1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('SliderTrackColor2').enabled(true))

    let trackColor1: string = await sliderTrackColor1.getInspectorInfo()
    assertEqual(JSON.parse(trackColor1).$attrs.trackColor.toLowerCase(), Color.Red)

    let trackColor2: string = await sliderTrackColor2.getInspectorInfo()
    assertEqual(JSON.parse(trackColor2).$attrs.trackColor, '#FF008000')

    await button1.tap()
    let trackColor3: string = await sliderTrackColor1.getInspectorInfo()
    assertEqual(JSON.parse(trackColor3).$attrs.trackColor, '#FFFFFF00')

    await button2.tap()
    let trackColor4: string = await sliderTrackColor2.getInspectorInfo()
    assertEqual(JSON.parse(trackColor4).$attrs.trackColor, $r('sys.color.ohos_fa_palette1'))
  })
}