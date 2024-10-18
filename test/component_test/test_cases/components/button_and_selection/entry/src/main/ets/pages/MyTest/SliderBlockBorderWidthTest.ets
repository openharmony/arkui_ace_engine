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

export default async function sliderBlockBorderWidthTest() {
  /*
   * Slider组件 BlockBorderWidth属性
   * 找到画面id为sliderBlockBorderWidth1，sliderBlockBorderWidth2，sliderBlockBorderWidth3，sliderBlockBorderWidth4，sliderBlockBorderWidth5的Slider组件
   * 找到画面文本为SliderBlockBorderWidth的Button组件
   * 获取sliderBlockBorderWidth1的BlockBorderWidth属性与期待值'1.00vp'比对
   * 获取sliderBlockBorderWidth2的BlockBorderWidth属性与期待值'2.00vp'比对
   * 获取sliderBlockBorderWidth3的BlockBorderWidth属性与期待值'50.00vp'比对
   * 获取sliderBlockBorderWidth4的BlockBorderWidth属性与期待值'5.00px'比对
   * 获取sliderBlockBorderWidth5的BlockBorderWidth属性与期待值'50.00vp'比对
   * 点击button，变更sliderBlockBorderWidth3的BlockBorderWidth属性值为$r('app.string.border_width')，sliderBlockBorderWidth4的BlockBorderWidth属性值为'30.00vp'，sliderBlockBorderWidth5的BlockBorderWidth属性值为$r('app.string.border_width')
   * 获取sliderBlockBorderWidth3的BlockBorderWidth属性与期待值$r('app.string.border_width')比对，sliderBlockBorderWidth4的BlockBorderWidth属性与期待值'30.00vp'比对，sliderBlockBorderWidth5的BlockBorderWidth属性与期待值$r('app.string.border_width')比对
   */
  defineTest('sliderBlockBorderWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('sliderBlockBorderWidthTestDemo running')
    let driver: Tester = Tester.create()
    let sliderBlockBorderWidth1: Component =
      await driver.findComponent(Matcher.create().id('sliderBlockBorderWidth1').enabled(true))
    let sliderBlockBorderWidth2: Component =
      await driver.findComponent(Matcher.create().id('sliderBlockBorderWidth2').enabled(true))
    let sliderBlockBorderWidth3: Component =
      await driver.findComponent(Matcher.create().id('sliderBlockBorderWidth3').enabled(true))
    let sliderBlockBorderWidth4: Component =
      await driver.findComponent(Matcher.create().id('sliderBlockBorderWidth4').enabled(true))
    let sliderBlockBorderWidth5: Component =
      await driver.findComponent(Matcher.create().id('sliderBlockBorderWidth5').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('SliderBlockBorderWidth').enabled(true))

    let blockBorderWidth1: string = await sliderBlockBorderWidth1.getInspectorInfo()
    assertEqual(JSON.parse(blockBorderWidth1).$attrs.blockBorderWidth, '1.00vp')

    let blockBorderWidth2: string = await sliderBlockBorderWidth2.getInspectorInfo()
    assertEqual(JSON.parse(blockBorderWidth2).$attrs.blockBorderWidth, '2.00vp')

    let blockBorderWidth3: string = await sliderBlockBorderWidth3.getInspectorInfo()
    assertEqual(JSON.parse(blockBorderWidth3).$attrs.blockBorderWidth, '50.00vp')

    let blockBorderWidth4: string = await sliderBlockBorderWidth4.getInspectorInfo()
    assertEqual(JSON.parse(blockBorderWidth4).$attrs.blockBorderWidth, '5.00px')

    let blockBorderWidth5: string = await sliderBlockBorderWidth5.getInspectorInfo()
    assertEqual(JSON.parse(blockBorderWidth5).$attrs.blockBorderWidth, '50.00vp')

    await button.tap()
    let blockBorderWidth6: string = await sliderBlockBorderWidth3.getInspectorInfo()
    assertEqual(JSON.parse(blockBorderWidth6).$attrs.blockBorderWidth, $r('app.string.border_width'))

    let blockBorderWidth7: string = await sliderBlockBorderWidth4.getInspectorInfo()
    assertEqual(JSON.parse(blockBorderWidth7).$attrs.blockBorderWidth, '30.00vp')

    let blockBorderWidth8: string = await sliderBlockBorderWidth5.getInspectorInfo()
    assertEqual(JSON.parse(blockBorderWidth8).$attrs.blockBorderWidth, $r('app.string.border_width'))
  }, 0)
}