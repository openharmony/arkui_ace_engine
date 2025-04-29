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

export default async function offScreenCanvasRenderingContext2DTextAlignTest() {
  /*
  * OffScreenCanvasRenderingContext2D组件 textAlign属性
  * 找到画面id为offScreenCanvasRenderingContext2DTextAlign的Canvas组件
  * 找到画面文本为OffScreenCanvasRenderingContext2DTextAlign1,OffScreenCanvasRenderingContext2DTextAlign2,
  * OffScreenCanvasRenderingContext2DTextAlign3,OffScreenCanvasRenderingContext2DTextAlign4的Button组件
  * 获取offCanvas的textAlign属性与期待值'start'比对
  * 点击button1，变更offCanvas的textAlign属性值为'end'
  * 获取offCanvas的textAlign属性与期待值'end'比对
  * 点击button2，变更offCanvas的textAlign属性值为'left'
  * 获取offCanvas的textAlign属性与期待值'left'比对
  * 点击button3，变更offCanvas的textAlign属性值为'center'
  * 获取offCanvas的textAlign属性与期待值'center'比对
  * 点击button4，变更offCanvas的textAlign属性值为'right'
  * 获取offCanvas的textAlign属性与期待值'right'比对
  */
  defineTest('offScreenCanvasRenderingContext2DTextAlignTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("offScreenCanvasRenderingContext2DTextAlignTestDemo running")

    let driver: Tester = Tester.create()
    let offCanvas: Component =
      await driver.findComponent(Matcher.create().id('offScreenCanvasRenderingContext2DTextAlign').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('OffScreenCanvasRenderingContext2DTextAlign1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('OffScreenCanvasRenderingContext2DTextAlign2').enabled(true))
    let button3: Component =
      await driver.findComponent(Matcher.create().text('OffScreenCanvasRenderingContext2DTextAlign3').enabled(true))
    let button4: Component =
      await driver.findComponent(Matcher.create().text('OffScreenCanvasRenderingContext2DTextAlign4').enabled(true))

    let textAlign1: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(textAlign1).$attrs.textAlign, 'start')

    await button1.tap()
    let textAlign2: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(textAlign2).$attrs.textAlign, 'end')

    await button2.tap()
    let textAlign3: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(textAlign3).$attrs.textAlign, 'left')

    await button3.tap()
    let textAlign4: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(textAlign4).$attrs.textAlign, 'center')

    await button4.tap()
    let textAlign5: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(textAlign5).$attrs.textAlign, 'right')
  }, 0)
}