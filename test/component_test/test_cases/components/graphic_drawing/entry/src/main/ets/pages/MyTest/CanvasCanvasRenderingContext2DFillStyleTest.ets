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

export default async function canvasCanvasRenderingContext2DFillStyleTest() {
  /*
   * CanvasRenderingContext2D组件 fillStyle属性
   * 找到画面id为canvasFillStyle的Canvas组件
   * 找到画面文本为CanvasFillStyle的Button组件
   * 获取canvas的fillStyle属性与期待值0xff0000比对
   * 点击button，变更canvas的fillStyle属性值为'rgb(0,0,255)'
   * 获取canvas的fillStyle属性与期待值'rgb(0,0,255)'比对
   */
  defineTest('canvasCanvasRenderingContext2DFillStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("canvasCanvasRenderingContext2DFillStyleTestDemo running")

    let driver: Tester = Tester.create()
    let canvas: Component = await driver.findComponent(Matcher.create().id('canvasFillStyle').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('CanvasFillStyle').enabled(true))

    let fillStyle1: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(fillStyle1).$attrs.fillStyle, 0xff0000)

    await button.tap()
    let fillStyle2: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(fillStyle2).$attrs.fillStyle, 'rgb(0,0,255)')
  }, 0)
}