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

export default async function canvasRenderingContext2DTextBaselineTest() {
  /*
   * CanvasRenderingContext2D组件 textBaseline属性
   * 找到画面id为canvasTextBaseline的Canvas组件
   * 找到画面文本为CanvasTextBaseline1,CanvasTextBaseline2,CanvasTextBaseline3,
   * CanvasTextBaseline4,CanvasTextBaseline5的Button组件
   * 获取canvas的textBaseline属性与期待值'top'比对
   * 点击button1，变更canvas的textBaseline属性值为'bottom'
   * 获取canvas的textBaseline属性与期待值'bottom'比对
   * 点击button2，变更canvas的textBaseline属性值为'middle'
   * 获取canvas的textBaseline属性与期待值'middle'比对
   * 点击button3，变更canvas的textBaseline属性值为'alphabetic'
   * 获取canvas的textBaseline属性与期待值'alphabetic'比对
   * 点击button4，变更canvas的textBaseline属性值为'hanging'
   * 获取canvas的textBaseline属性与期待值'hanging'比对
   * 点击button5，变更canvas的textBaseline属性值为'ideographic'
   * 获取canvas的textBaseline属性与期待值'ideographic'比对
   */
  defineTest('canvasRenderingContext2DTextBaselineTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("canvasRenderingContext2DTextBaselineTestDemo running")

    let driver: Tester = Tester.create()
    let canvas: Component = await driver.findComponent(Matcher.create().id('canvasTextBaseline').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('CanvasTextBaseline1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('CanvasTextBaseline2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('CanvasTextBaseline3').enabled(true))
    let button4: Component = await driver.findComponent(Matcher.create().text('CanvasTextBaseline4').enabled(true))
    let button5: Component = await driver.findComponent(Matcher.create().text('CanvasTextBaseline5').enabled(true))

    let textBaseline1: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(textBaseline1).$attrs.textBaseline, 'top')

    await button1.tap()
    let textBaseline2: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(textBaseline2).$attrs.textBaseline, 'bottom')

    await button2.tap()
    let textBaseline3: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(textBaseline3).$attrs.textBaseline, 'middle')

    await button3.tap()
    let textBaseline4: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(textBaseline4).$attrs.textBaseline, 'alphabetic')

    await button4.tap()
    let textBaseline5: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(textBaseline5).$attrs.textBaseline, 'hanging')

    await button5.tap()
    let textBaseline6: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(textBaseline6).$attrs.textBaseline, 'ideographic')
  }, 0)
}