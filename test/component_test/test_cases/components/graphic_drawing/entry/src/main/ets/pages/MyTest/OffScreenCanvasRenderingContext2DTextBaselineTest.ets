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

export default async function offScreenCanvasRenderingContext2DTextBaselineTest() {
  /*
  * OffScreenCanvasRenderingContext2D组件 textBaseline属性
  * 找到画面id为offScreenCanvasRenderingContext2DTextBaseline的Canvas组件
  * 找到画面文本为OffScreenCanvasRenderingContext2DTextBaseline1,OffScreenCanvasRenderingContext2DTextBaseline2,
  * OffScreenCanvasRenderingContext2DTextBaseline3,OffScreenCanvasRenderingContext2DTextBaseline4,
  * OffScreenCanvasRenderingContext2DTextBaseline5的Button组件
  * 获取offCanvas的textBaseline属性与期待值'top'比对
  * 点击button1，变更offCanvas的textBaseline属性值为'bottom'
  * 获取offCanvas的textBaseline属性与期待值'bottom'比对
  * 点击button2，变更offCanvas的textBaseline属性值为'middle'
  * 获取offCanvas的textBaseline属性与期待值'middle'比对
  * 点击button3，变更offCanvas的textBaseline属性值为'alphabetic'
  * 获取offCanvas的textBaseline属性与期待值'alphabetic'比对
  * 点击button4，变更offCanvas的textBaseline属性值为'hanging'
  * 获取offCanvas的textBaseline属性与期待值'hanging'比对
  * 点击button5，变更offCanvas的textBaseline属性值为'ideographic'
  * 获取offCanvas的textBaseline属性与期待值'ideographic'比对
  */
  defineTest('offScreenCanvasRenderingContext2DTextBaselineTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("offScreenCanvasRenderingContext2DTextBaselineTestDemo running")

    let driver: Tester = Tester.create()
    let offCanvas: Component =
      await driver.findComponent(Matcher.create().id('offScreenCanvasRenderingContext2DTextBaseline').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('OffScreenCanvasRenderingContext2DTextBaseline1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('OffScreenCanvasRenderingContext2DTextBaseline2').enabled(true))
    let button3: Component =
      await driver.findComponent(Matcher.create().text('OffScreenCanvasRenderingContext2DTextBaseline3').enabled(true))
    let button4: Component =
      await driver.findComponent(Matcher.create().text('OffScreenCanvasRenderingContext2DTextBaseline4').enabled(true))
    let button5: Component =
      await driver.findComponent(Matcher.create().text('OffScreenCanvasRenderingContext2DTextBaseline5').enabled(true))

    let textBaseline1: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(textBaseline1).$attrs.textBaseline, 'top')

    await button1.tap()
    let textBaseline2: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(textBaseline2).$attrs.textBaseline, 'bottom')

    await button2.tap()
    let textBaseline3: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(textBaseline3).$attrs.textBaseline, 'middle')

    await button3.tap()
    let textBaseline4: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(textBaseline4).$attrs.textBaseline, 'alphabetic')

    await button4.tap()
    let textBaseline5: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(textBaseline5).$attrs.textBaseline, 'hanging')

    await button5.tap()
    let textBaseline6: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(textBaseline6).$attrs.textBaseline, 'ideographic')
  }, 0)
}