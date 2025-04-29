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

export default async function offScreenCanvasRenderingContext2DFontTest() {
  /*
   * OffScreenCanvasRenderingContext2D组件 font属性
   * 找到画面id为offCanvasRenderingContext2DFont的Canvas组件
   * 找到画面文本为OffCanvasRenderingContext2DFont1,OffCanvasRenderingContext2DFont2的Button组件
   * 获取offCanvas的font属性与期待值'30px'比对
   * 点击button1，变更offCanvas的font属性值为'30px,bolder,100'
   * 获取offCanvas的font属性与期待值'30px,bolder,100'比对
   * 点击button2，变更offCanvas的font属性值为'30px,100,200'
   * 获取offCanvas的font属性与期待值'30px,100,200'比对
   */
  defineTest('offScreenCanvasRenderingContext2DFontTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("offScreenCanvasRenderingContext2DFontTestDemo running")
    let driver: Tester = Tester.create()
    let offCanvas: Component =
      await driver.findComponent(Matcher.create().id('offCanvasRenderingContext2DFont').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('OffCanvasRenderingContext2DFont1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('OffCanvasRenderingContext2DFont2').enabled(true))

    let offFont1: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(offFont1).$attrs.font, '30px')

    await button1.tap()
    let offFont2: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(offFont2).$attrs.font, '30px,bolder,100')

    await button2.tap()
    let offFont3: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(offFont3).$attrs.font, '30px,100,200')
  }, 0)
}