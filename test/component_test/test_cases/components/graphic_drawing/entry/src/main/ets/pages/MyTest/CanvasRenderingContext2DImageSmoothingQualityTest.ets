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

import { assertEqual, assertContain, assertFalse, assertTrue } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'


export default async function canvasRenderingContext2DImageSmoothingQualityTest() {
  /*
 * CanvasRenderingContext2D组件 imageSmoothingQuality属性
 * 找到画面id为canvasImageSmoothingQuality的Canvas组件
 * 找到画面文本为CanvasImageSmoothingQuality1,CanvasImageSmoothingQuality2的Button组件
 * 获取canvas的imageSmoothingQuality属性与期待值'high'比对
 * 点击button1，变更canvas的imageSmoothingQuality属性值为'medium'
 * 获取canvas的imageSmoothingQuality属性与期待值'medium'比对
 * 点击button2，变更canvas的imageSmoothingQuality属性值为'low'
 * 获取canvas的imageSmoothingQuality属性与期待值'low'比对
 */
  defineTest('canvasRenderingContext2DImageSmoothingQualityImageSmoothingQualityTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("canvasRenderingContext2DImageSmoothingQualityImageSmoothingQualityTestDemo running")

    let driver: Tester = Tester.create()
    let canvas: Component = await driver.findComponent(Matcher.create().id('canvasImageSmoothingQuality').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('CanvasImageSmoothingQuality1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('CanvasImageSmoothingQuality2').enabled(true))

    let imageSmoothingQuality1: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(imageSmoothingQuality1).$attrs.imageSmoothingQuality, 'high')

    await button1.tap()
    let imageSmoothingQuality2: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(imageSmoothingQuality2).$attrs.imageSmoothingQuality, 'medium')

    await button2.tap()
    let imageSmoothingQuality3: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(imageSmoothingQuality3).$attrs.imageSmoothingQuality, 'low')
  }, 0)
}