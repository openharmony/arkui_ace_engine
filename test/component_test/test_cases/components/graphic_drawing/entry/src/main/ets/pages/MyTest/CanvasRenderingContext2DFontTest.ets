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

export default async function canvasRenderingContext2DFontTest() {
  /*
   * CanvasRenderingContext2D组件 Fill属性
   * 找到画面id为canvasFont的Canvas组件
   * 找到画面文本为CanvasFont1,CanvasFont2的Button组件
   * 获取canvas的font属性与期待值'30px sans-serif'比对
   * 点击button1，变更canvas的font属性值为'normal normal 14px sans-serif'
   * 获取canvas的font属性与期待值'normal normal 14px sans-serif'比对
   * 点击button2，变更canvas的font属性值为'italic bold 14px serif'
   * 获取canvas的font属性与期待值'italic bold 14px serif'比对
   * 点击button3，变更canvas的font属性值为'normal bolder 14px monospace'
   * 获取canvas的font属性与期待值'normal bolder 14px monospace'比对
   * 点击button4，变更canvas的font属性值为'normal lighter 14px monospace'
   * 获取canvas的font属性与期待值'normal lighter 14px monospace'比对
   * 点击button5，变更canvas的font属性值为'normal 100 14px serif'
   * 获取canvas的font属性与期待值'normal 100 14px serif'比对
   */
  defineTest('canvasRenderingContext2DFontTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("canvasRenderingContext2DFontTestDemo running")

    let driver: Tester = Tester.create()
    let canvas: Component = await driver.findComponent(Matcher.create().id('canvasFont').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('CanvasFont1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('CanvasFont2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('CanvasFont3').enabled(true))
    let button4: Component = await driver.findComponent(Matcher.create().text('CanvasFont4').enabled(true))
    let button5: Component = await driver.findComponent(Matcher.create().text('CanvasFont5').enabled(true))

    let font1: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(font1).$attrs.font, '30px sans-serif')

    await button1.tap()
    let font2: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(font2).$attrs.font, 'normal normal 14px sans-serif')

    await button2.tap()
    let font3: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(font3).$attrs.font, 'italic bold 14px serif')

    await button3.tap()
    let font4: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(font4).$attrs.font, 'normal bolder 14px monospace')

    await button4.tap()
    let font5: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(font5).$attrs.font, 'normal lighter 14px monospace')

    await button5.tap()
    let font6: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(font6).$attrs.font, 'normal 100 14px serif')
  }, 0)
}