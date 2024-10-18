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

export default async function offScreenCanvasRenderingContext2DFillStyleStringTest() {
  /*
   * OffScreenCanvasRenderingContext2D组件 fillStyle属性
   * 找到画面id为CanvasOffFillStyle的Canvas组件
   * 找到画面文本为FillStyle的Button组件
   * 获取offCanvas的fillStyle属性与期待值'#0000ff'比对
   * 点击button，变更circle1的fillStyle属性值为0xFFC1C1
   * 获取offCanvas的fillStyle属性与期待值0xFFC1C1比对
   */
  defineTest('offScreenCanvasRenderingContext2DFillStyleStringTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("offScreenCanvasRenderingContext2DFillStyleStringTestDemo running")

    let driver: Tester = Tester.create()
    let offCanvas: Component =
      await driver.findComponent(Matcher.create().id('offScreenCanvasRenderingContext2DFillStyle').enabled(true))
    let button: Component =
      await driver.findComponent(Matcher.create().text('OffScreenCanvasRenderingContext2DFillStyle').enabled(true))

    let offFillStyle1: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(offFillStyle1).$attrs.fillStyle, '#0000ff')

    await button.tap()
    let offFillStyle2: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(offFillStyle2).$attrs.fillStyle, 0xFFC1C1)
  }, 0)
}