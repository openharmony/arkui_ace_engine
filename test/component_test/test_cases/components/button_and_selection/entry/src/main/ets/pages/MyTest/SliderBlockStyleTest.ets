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

export default async function sliderBlockStyleTest() {
  /*
  * Slider组件 BlockStyle属性
  * 找到画面id为sliderBlockStyle1，sliderBlockStyle2，sliderBlockStyle3的Slider组件
  * 找到画面文本为SliderBlockStyle的Button组件
  * 获取sliderBlockStyle1的BlockStyle属性与期待值{ type: 'SliderBlockType.DEFAULT', shape: new Circle({ width: '150', height: '150' }) }比对
  * 获取sliderBlockStyle2的BlockStyle属性与期待值{ type: 'SliderBlockType.DEFAULT', shape: new Ellipse({ width: '150', height: '100' }) }比对
  * 获取sliderBlockStyle3的BlockStyle属性与期待值{ type: 'SliderBlockType.IMAGE', image: "/pages/slider/StarYellow.png", shape: new Path({ commands: 'M60 60 M30 30 L15 56 L45 56 Z' }) }比对
  * 点击button，变更sliderBlockStyle3的BlockStyle属性值为{ type: 'SliderBlockType.SHAPE', image: $r('app.media.startIcon'), shape: new Rect({ width: '150', height: '150' }) }
  * 获取sliderBlockStyle3的BlockStyle属性与期待值{ type: 'SliderBlockType.SHAPE', image: $r('app.media.startIcon'), shape: new Rect({ width: '150', height: '150' }) }比对
  */
  defineTest('sliderBlockStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('sliderBlockStyleTestDemo running')
    let driver: Tester = Tester.create()
    let sliderBlockStyle1: Component =
      await driver.findComponent(Matcher.create().id('sliderBlockStyle1').enabled(true))
    let sliderBlockStyle2: Component =
      await driver.findComponent(Matcher.create().id('sliderBlockStyle2').enabled(true))
    let sliderBlockStyle3: Component =
      await driver.findComponent(Matcher.create().id('sliderBlockStyle3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('SliderBlockStyle').enabled(true))

    let blockStyle1: string = await sliderBlockStyle1.getInspectorInfo()
    assertFalse(JSON.parse(blockStyle1).$attrs.blockStyle == undefined)
    assertEqual(JSON.parse(blockStyle1).$attrs.blockStyle.type, 'SliderBlockType.DEFAULT')
    assertEqual(JSON.parse(blockStyle1).$attrs.blockStyle.shape, new Circle({
      width: '150', height: '150'
    }))

    let blockStyle2: string = await sliderBlockStyle2.getInspectorInfo()
    assertEqual(JSON.parse(blockStyle2).$attrs.blockStyle.type, 'SliderBlockType.DEFAULT')
    assertEqual(JSON.parse(blockStyle2).$attrs.blockStyle.shape, new Ellipse({
      width: '150', height: '100'
    }))

    let blockStyle3: string = await sliderBlockStyle3.getInspectorInfo()
    assertEqual(JSON.parse(blockStyle3).$attrs.blockStyle.type, 'SliderBlockType.IMAGE')
    assertEqual(JSON.parse(blockStyle3).$attrs.blockStyle.image, "/pages/slider/StarYellow.png")
    assertEqual(JSON.parse(blockStyle3).$attrs.blockStyle.shape, new Path({
      commands: 'M60 60 M30 30 L15 56 L45 56 Z'
    }))

    await button.tap()
    let blockStyle4: string = await sliderBlockStyle3.getInspectorInfo()
    assertEqual(JSON.parse(blockStyle4).$attrs.blockStyle.type, 'SliderBlockType.SHAPE')
    assertEqual(JSON.parse(blockStyle4).$attrs.blockStyle.image, $r('app.media.startIcon'))
    assertEqual(JSON.parse(blockStyle4).$attrs.blockStyle.shape, new Rect({
      width: '150', height: '150'
    }))
  }, 0)
}