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

export default async function sliderBlockBorderColorTest() {
  /*
   * Slider组件 BlockBorderColor属性
   * 找到画面id为sliderBlockBorderColor1，sliderBlockBorderColor2，...，sliderBlockBorderColor5，sliderBlockBorderColor6的Slider组件
   * 找到画面文本为SliderBlockBorderColor的Button组件
   * 获取sliderBlockBorderColor1的BlockBorderColor属性与期待值Color.Black比对
   * 获取sliderBlockBorderColor2的BlockBorderColor属性与期待值Color.Yellow比对
   * 获取sliderBlockBorderColor3的BlockBorderColor属性与期待值Color.Red比对
   * 获取sliderBlockBorderColor4的BlockBorderColor属性与期待值'#FFFFFFFF'比对
   * 获取sliderBlockBorderColor5的BlockBorderColor属性与期待值'#FFFF64FF'比对
   * 获取sliderBlockBorderColor6的BlockBorderColor属性与期待值Color.Red比对
   * 点击button，变更sliderBlockBorderColor3的BlockBorderColor属性值为$r('sys.color.ohos_fa_activated')，sliderBlockBorderColor5的BlockBorderColor属性值为Color.Yellow，sliderBlockBorderColor6的BlockBorderColor属性值为$r('sys.color.ohos_fa_activated')
   * 获取sliderBlockBorderColor3的BlockBorderColor属性与期待值$r('sys.color.ohos_fa_activated')比对，sliderBlockBorderColor5的BlockBorderColor属性与期待值Color.Yellow比对，sliderBlockBorderColor6的BlockBorderColor属性与期待值$r('sys.color.ohos_fa_activated')比对
   */
  defineTest('sliderBlockBorderColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('sliderBlockBorderColorTestDemo running')
    let driver: Tester = Tester.create()
    let sliderBlockBorderColor1: Component =
      await driver.findComponent(Matcher.create().id('sliderBlockBorderColor1').enabled(true))
    let sliderBlockBorderColor2: Component =
      await driver.findComponent(Matcher.create().id('sliderBlockBorderColor2').enabled(true))
    let sliderBlockBorderColor3: Component =
      await driver.findComponent(Matcher.create().id('sliderBlockBorderColor3').enabled(true))
    let sliderBlockBorderColor4: Component =
      await driver.findComponent(Matcher.create().id('sliderBlockBorderColor4').enabled(true))
    let sliderBlockBorderColor5: Component =
      await driver.findComponent(Matcher.create().id('sliderBlockBorderColor5').enabled(true))
    let sliderBlockBorderColor6: Component =
      await driver.findComponent(Matcher.create().id('sliderBlockBorderColor6').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('SliderBlockBorderColor').enabled(true))

    let blockBorderColor1: string = await sliderBlockBorderColor1.getInspectorInfo()
    assertEqual(JSON.parse(blockBorderColor1).$attrs.blockBorderColor.toLowerCase(), Color.Black)

    let blockBorderColor2: string = await sliderBlockBorderColor2.getInspectorInfo()
    assertEqual(JSON.parse(blockBorderColor2).$attrs.blockBorderColor.toLowerCase(), Color.Yellow)

    let blockBorderColor3: string = await sliderBlockBorderColor3.getInspectorInfo()
    assertEqual(JSON.parse(blockBorderColor3).$attrs.blockBorderColor.toLowerCase(), Color.Red)

    let blockBorderColor4: string = await sliderBlockBorderColor4.getInspectorInfo()
    assertEqual(JSON.parse(blockBorderColor4).$attrs.blockBorderColor, '#FFFFFFFF')

    let blockBorderColor5: string = await sliderBlockBorderColor5.getInspectorInfo()
    assertEqual(JSON.parse(blockBorderColor5).$attrs.blockBorderColor, '#FFFF64FF')

    let blockBorderColor6: string = await sliderBlockBorderColor6.getInspectorInfo()
    assertEqual(JSON.parse(blockBorderColor6).$attrs.blockBorderColor.toLowerCase(), Color.Red)

    await button.tap()
    let blockBorderColor7: string = await sliderBlockBorderColor3.getInspectorInfo()
    assertEqual(JSON.parse(blockBorderColor7).$attrs.blockBorderColor, $r('sys.color.ohos_fa_activated'))

    let blockBorderColor8: string = await sliderBlockBorderColor5.getInspectorInfo()
    assertEqual(JSON.parse(blockBorderColor8).$attrs.blockBorderColor.toLowerCase(), Color.Yellow)

    let blockBorderColor9: string = await sliderBlockBorderColor6.getInspectorInfo()
    assertEqual(JSON.parse(blockBorderColor9).$attrs.blockBorderColor, $r('sys.color.ohos_fa_activated'))
  }, 0)
}