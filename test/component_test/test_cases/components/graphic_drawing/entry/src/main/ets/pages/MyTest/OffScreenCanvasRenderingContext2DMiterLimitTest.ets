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

export default async function offScreenCanvasRenderingContext2DMiterLimitTest() {
  /*
   * OffScreenCanvasRenderingContext2D组件 miterLimit属性
   * 找到画面id为offScreenCanvasRenderingContext2DMiterLimit的Canvas组件
   * 找到画面文本为OffScreenCanvasRenderingContext2DMiterLimit1,
   * OffScreenCanvasRenderingContext2DMiterLimit2的Button组件
   * 获取offCanvas的miterLimit属性与期待值3比对
   * 点击button1，变更offCanvas的miterLimit属性值为-1
   * 获取offCanvas的miterLimit属性与期待值-1比对
   * 点击button2，变更offCanvas的miterLimit属性值为0
   * 获取offCanvas的miterLimit属性与期待值0比对
   */
  defineTest('offScreenCanvasRenderingContext2DMiterLimitTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("offScreenCanvasRenderingContext2DMiterLimitTestDemo running")

    let driver: Tester = Tester.create()
    let offCanvas: Component =
      await driver.findComponent(Matcher.create().id('offScreenCanvasRenderingContext2DMiterLimit').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('OffScreenCanvasRenderingContext2DMiterLimit1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('OffScreenCanvasRenderingContext2DMiterLimit2').enabled(true))

    let miterLimit1: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(miterLimit1).$attrs.miterLimit, 3)

    await button1.tap()
    let miterLimit2: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(miterLimit2).$attrs.miterLimit, -1)

    await button2.tap()
    let miterLimit3: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(miterLimit3).$attrs.miterLimit, 0)
  }, 0)
}