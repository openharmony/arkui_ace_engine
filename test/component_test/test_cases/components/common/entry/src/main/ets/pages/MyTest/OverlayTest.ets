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

import { assertEqual, assertFalse, assertTrue } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function overlayTest() {
  /*
* overlay 通用属性
* 找到画面id为 imageOverlay1 的组件
* 找到画面文本为 ButtonOverlay1 按钮
* 获取 imageOverlay1 的 overlay.title 属性与期望值 'Overlay' 比对
* 获取 imageOverlay1 的 overlay.options.offset.x 属性与期望值 '3.00vp' 比对
* 获取 imageOverlay1 的 overlay.options.offset.y 属性与期望值 '-1.00vp' 比对
* 获取 imageOverlay1 的 overlay.options.align 属性与期望值 'Alignment.TopStart' 比对
* 点击 button1 变更 imageOverlay1 的属性
* 获取 imageOverlay1 的 overlay.options.align 属性与期望值 'Alignment.Top' 比对
* 点击 button1 变更 imageOverlay1 的属性
* 获取 imageOverlay1 的 overlay.options.align 属性与期望值 'Alignment.TopEnd' 比对
* 点击 button1 变更 imageOverlay1 的属性
* 获取 imageOverlay1 的 overlay.options.align 属性与期望值 'Alignment.Start' 比对
* 点击 button1 变更 imageOverlay1 的属性
* 获取 imageOverlay1 的 overlay.options.align 属性与期望值 'Alignment.Center' 比对
* 点击 button1 变更 imageOverlay1 的属性
* 获取 imageOverlay1 的 overlay.options.align 属性与期望值 'Alignment.End' 比对
* 点击 button1 变更 imageOverlay1 的属性
* 获取 imageOverlay1 的 overlay.options.align 属性与期望值 'Alignment.BottomStart' 比对
* 点击 button1 变更 imageOverlay1 的属性
* 获取 imageOverlay1 的 overlay.options.align 属性与期望值 'Alignment.Bottom' 比对
* 点击 button1 变更 imageOverlay1 的属性
* 获取 imageOverlay1 的 overlay.options.align 属性与期望值 'Alignment.BottomEnd' 比对
* 找到画面中text为 myBUilder 的组件获取他的type与Text对比
* */
  defineTest('overlayTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('overlayTestDemo running')
    let driver: Tester = Tester.create()
    let imageOverlay1: Component = await driver.findComponent(Matcher.create().id('imageOverlay1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonOverlay1').enabled(true))
    let overlay1: string = await imageOverlay1.getInspectorInfo()
    assertEqual(JSON.parse(overlay1).$attrs.overlay.title, 'Overlay')
    assertEqual(JSON.parse(overlay1)
      .$attrs
      .overlay
      .options
      .offset
      .x, '3.00vp')
    assertEqual(JSON.parse(overlay1)
      .$attrs
      .overlay
      .options
      .offset
      .y, '-1.00vp')
    assertEqual(JSON.parse(overlay1)
      .$attrs
      .overlay
      .options
      .align, 'Alignment.TopStart')

    await button1.tap()
    let overlay2: string = await imageOverlay1.getInspectorInfo()
    assertEqual(JSON.parse(overlay2)
      .$attrs
      .overlay
      .options
      .align, 'Alignment.Top')

    await button1.tap()
    let overlay3: string = await imageOverlay1.getInspectorInfo()
    assertEqual(JSON.parse(overlay3)
      .$attrs
      .overlay
      .options
      .align, 'Alignment.TopEnd')

    await button1.tap()
    let overlay4: string = await imageOverlay1.getInspectorInfo()
    assertEqual(JSON.parse(overlay4)
      .$attrs
      .overlay
      .options
      .align, 'Alignment.Start')

    await button1.tap()
    let overlay5: string = await imageOverlay1.getInspectorInfo()
    assertEqual(JSON.parse(overlay5)
      .$attrs
      .overlay
      .options
      .align, 'Alignment.Center')

    await button1.tap()
    let overlay6: string = await imageOverlay1.getInspectorInfo()
    assertEqual(JSON.parse(overlay6)
      .$attrs
      .overlay
      .options
      .align, 'Alignment.End')

    await button1.tap()
    let overlay7: string = await imageOverlay1.getInspectorInfo()
    assertEqual(JSON.parse(overlay7)
      .$attrs
      .overlay
      .options
      .align, 'Alignment.BottomStart')

    await button1.tap()
    let overlay8: string = await imageOverlay1.getInspectorInfo()
    assertEqual(JSON.parse(overlay8)
      .$attrs
      .overlay
      .options
      .align, 'Alignment.Bottom')

    await button1.tap()
    let overlay9: string = await imageOverlay1.getInspectorInfo()
    assertEqual(JSON.parse(overlay9)
      .$attrs
      .overlay
      .options
      .align, 'Alignment.BottomEnd')

    let imageBuilder: Component = await driver.findComponent(Matcher.create().text('myBuilder'))
    let getBuilder: string = await imageBuilder.getType()
    assertEqual(getBuilder, 'Text')
  }, 0)
}