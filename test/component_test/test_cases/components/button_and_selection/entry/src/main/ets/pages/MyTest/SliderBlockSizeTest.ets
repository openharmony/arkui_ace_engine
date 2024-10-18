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

export default async function sliderBlockSizeTest() {
  /*
  * Slider组件 BlockSize属性
  * 找到画面id为sliderBlockSize1，sliderBlockSize2，sliderBlockSize3的Slider组件
  * 找到画面文本为SliderBlockSize的Button组件
  * 获取sliderBlockSize1的BlockSize属性与期待值{ width: '40.00vp', height: '40.00vp' }比对
  * 获取sliderBlockSize2的BlockSize属性与期待值{ width: '16.00vp', height: '16.00vp' }比对
  * 获取sliderBlockSize3的BlockSize属性与期待值{ width: '60.00px', height: '60.00px' }比对
  * 点击button，变更sliderBlockSize3的BlockSize属性值为{ width: $r('app.string.slider_blockSize'), height: $r('app.string.slider_blockSize') }
  * 获取sliderBlockSize3的BlockSize属性与期待值${ width: $r('app.string.slider_blockSize'), height: $r('app.string.slider_blockSize') }比对
  */
  defineTest('sliderBlockSizeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('sliderBlockSizeTestDemo running')
    let driver: Tester = Tester.create()
    let sliderBlockSize1: Component = await driver.findComponent(Matcher.create().id('sliderBlockSize1').enabled(true))
    let sliderBlockSize2: Component = await driver.findComponent(Matcher.create().id('sliderBlockSize2').enabled(true))
    let sliderBlockSize3: Component = await driver.findComponent(Matcher.create().id('sliderBlockSize3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('SliderBlockSize').enabled(true))

    let blockSize1: string = await sliderBlockSize1.getInspectorInfo()
    assertEqual(JSON.parse(blockSize1).$attrs.blockSize.width, '40.00vp')
    assertEqual(JSON.parse(blockSize1).$attrs.blockSize.height, '40.00vp')

    let blockSize2: string = await sliderBlockSize2.getInspectorInfo()
    assertEqual(JSON.parse(blockSize2).$attrs.blockSize.width, '16.00vp')
    assertEqual(JSON.parse(blockSize2).$attrs.blockSize.height, '16.00vp')

    let blockSize3: string = await sliderBlockSize3.getInspectorInfo()
    assertEqual(JSON.parse(blockSize3).$attrs.blockSize.width, '60.00px')
    assertEqual(JSON.parse(blockSize3).$attrs.blockSize.height, '60.00px')

    await button.tap()
    let blockSize4: string = await sliderBlockSize3.getInspectorInfo()
    assertEqual(JSON.parse(blockSize4).$attrs.blockSize.width, $r('app.string.slider_blockSize'))
    assertEqual(JSON.parse(blockSize4).$attrs.blockSize.height, $r('app.string.slider_blockSize'))
  }, 0)
}