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

export default async function canvasRenderingContext2DMiterLimitTest() {
  /*
   * CanvasRenderingContext2D组件 miterLimit属性
   * 找到画面id为canvasMiterLimit的Canvas组件
   * 找到画面文本为CanvasMiterLimit的Button组件
   * 获取canvas的miterLimit属性与期待值3比对
   * 点击button，变更canvas的miterLimit属性值为-5
   * 获取canvas的miterLimit属性与期待值-5比对
   */
  defineTest('canvasRenderingContext2DMiterLimitTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("canvasRenderingContext2DMiterLimitTestDemo running")

    let driver: Tester = Tester.create()
    let canvas: Component = await driver.findComponent(Matcher.create().id('canvasMiterLimit').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('CanvasMiterLimit').enabled(true))

    let miterLimit1: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(miterLimit1).$attrs.miterLimit, 3)

    await button.tap()
    let miterLimit2: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(miterLimit2).$attrs.miterLimit, -5)
  }, 0)
}