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

export default async function offScreenCanvasRenderingContext2DLineCapSquareTest() {
  /*
 * OffScreenCanvasRenderingContext2D组件 lineCap属性
 * 找到画面id为offScreenCanvasRenderingContext2DLineCapSquare的Canvas组件
 * 找到画面文本为OffScreenCanvasRenderingContext2DLineCapSquare1,
 * OffScreenCanvasRenderingContext2DLineCapSquare2的Button组件
 * 获取offCanvas的lineCap属性与期待值'butt'比对
 * 点击button1，变更offCanvas的lineCap属性值为'round'
 * 获取offCanvas的lineCap属性与期待值'round'比对
 * 点击button2，变更offCanvas的lineCap属性值为'square'
 * 获取offCanvas的lineCap属性与期待值'square'比对
 */
  defineTest('offScreenCanvasRenderingContext2DLineCapSquareTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("offScreenCanvasRenderingContext2DLineCapSquareTestDemo running")

    let driver: Tester = Tester.create()
    let offCanvas: Component =
      await driver.findComponent(Matcher.create().id('offScreenCanvasRenderingContext2DLineCapSquare').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('OffScreenCanvasRenderingContext2DLineCapSquare1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('OffScreenCanvasRenderingContext2DLineCapSquare2').enabled(true))

    let lineCap1: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(lineCap1).$attrs.lineCap, 'butt')

    await button1.tap()
    let lineCap2: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(lineCap2).$attrs.lineCap, 'round')

    await button2.tap()
    let lineCap3: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(lineCap3).$attrs.lineCap, 'square')
  }, 0)
}