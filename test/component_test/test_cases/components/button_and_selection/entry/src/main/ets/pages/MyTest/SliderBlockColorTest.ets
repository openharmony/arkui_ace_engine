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

export default async function sliderBlockColorTest() {
  /*
   * Slider组件 BlockColor属性
   * 找到画面id为sliderBlockColor1，sliderBlockColor2的Slider组件
   * 找到画面文本为SliderBlockColor1，SliderBlockColor2的Button组件
   * 获取sliderBlockColor1的BlockColor属性与期待值Color.Red比对
   * 获取sliderBlockColor2的BlockColor属性与期待值'#FF008000'比对
   * 点击button1，变更sliderBlockColor1的BlockColor属性值为'#FFFFFF00'
   * 获取sliderBlockColor1的BlockColor属性与期待值'#FFFFFF00'比对
   * 点击button2，变更sliderBlockColor2的BlockColor属性值为$r('sys.color.ohos_fa_palette1')
   * 获取sliderBlockColor2的BlockColor属性与期待值$r('sys.color.ohos_fa_palette1')比对
   */
  defineTest('sliderBlockColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('sliderBlockColorTestDemo running')
    let driver: Tester = Tester.create()
    let sliderBlockColor1: Component =
      await driver.findComponent(Matcher.create().id('sliderBlockColor1').enabled(true))
    let sliderBlockColor2: Component =
      await driver.findComponent(Matcher.create().id('sliderBlockColor2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SliderBlockColor1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('SliderBlockColor2').enabled(true))

    let blockColor1: string = await sliderBlockColor1.getInspectorInfo()
    assertEqual(JSON.parse(blockColor1).$attrs.blockColor.toLowerCase(), Color.Red)

    let blockColor2: string = await sliderBlockColor2.getInspectorInfo()
    assertEqual(JSON.parse(blockColor2).$attrs.blockColor, '#FF008000')

    await button1.tap()
    let blockColor3: string = await sliderBlockColor1.getInspectorInfo()
    assertEqual(JSON.parse(blockColor3).$attrs.blockColor, '#FFFFFF00')

    await button2.tap()
    let blockColor4: string = await sliderBlockColor2.getInspectorInfo()
    assertEqual(JSON.parse(blockColor4).$attrs.blockColor, $r('sys.color.ohos_fa_palette1'))
  })
}