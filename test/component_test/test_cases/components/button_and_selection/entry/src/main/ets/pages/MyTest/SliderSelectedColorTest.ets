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

export default async function sliderSelectedColorTest() {
  /*
   * Slider组件 SelectedColor属性
   * 找到画面id为sliderSelectedColor1，sliderSelectedColor2的Slider组件
   * 找到画面文本为SliderSelectedColor1，SliderSelectedColor2的Button组件
   * 获取slider1的SelectedColor属性与期待值Color.Red比对
   * 获取slider2的SelectedColor属性与期待值'#FF008000'比对
   * 点击button1，变更slider1的SelectedColor属性值为'#FFFFFF00'
   * 获取slider1的SelectedColor属性与期待值'#FFFFFF00'比对
   * 点击button2，变更slider2的SelectedColor属性值为$r('app.color.start_window_background')
   * 获取slider2的SelectedColor属性与期待值$r('app.color.start_window_background')比对
   */
  defineTest('sliderSelectedColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('sliderSelectedColorTestDemo running')
    let driver: Tester = Tester.create()
    let sliderSelectedColor1: Component =
      await driver.findComponent(Matcher.create().id('sliderSelectedColor1').enabled(true))
    let sliderSelectedColor2: Component =
      await driver.findComponent(Matcher.create().id('sliderSelectedColor2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SliderSelectedColor1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('SliderSelectedColor2').enabled(true))

    let selectedColor1: string = await sliderSelectedColor1.getInspectorInfo()
    assertEqual(JSON.parse(selectedColor1).$attrs.selectedColor.toLowerCase(), Color.Red)

    let selectedColor2: string = await sliderSelectedColor2.getInspectorInfo()
    assertEqual(JSON.parse(selectedColor2).$attrs.selectedColor, '#FF008000')

    await button1.tap()
    let selectedColor3: string = await sliderSelectedColor1.getInspectorInfo()
    assertEqual(JSON.parse(selectedColor3).$attrs.selectedColor, '#FFFFFF00')

    await button2.tap()
    let selectedColor4: string = await sliderSelectedColor2.getInspectorInfo()
    assertEqual(JSON.parse(selectedColor4).$attrs.selectedColor, $r('sys.color.ohos_fa_palette1'))
  })
}