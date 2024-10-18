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

export default async function offScreenCanvasRenderingContext2DGlobalAlphaTest() {
  /*
   * OffScreenCanvasRenderingContext2D组件 globalAlpha属性
   * 找到画面id为OffGlobalAlpha的Canvas组件
   * 找到画面文本为OffScreenCanvasRenderingContext2DGlobalAlpha的Button组件
   * 获取offCanvas的globalAlpha属性与期待值0.4比对
   * 点击button，变更circle1的globalAlpha属性值为0.0
   * 获取offCanvas的globalAlpha属性与期待值0.0比对
   */
  defineTest('offScreenCanvasRenderingContext2DGlobalAlphaTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("offScreenCanvasRenderingContext2DGlobalAlphaTestDemo running")

    let driver: Tester = Tester.create()
    let offCanvas: Component =
      await driver.findComponent(Matcher.create().id('offScreenCanvasRenderingContext2DGlobalAlpha').enabled(true))
    let button: Component =
      await driver.findComponent(Matcher.create().text('OffScreenCanvasRenderingContext2DGlobalAlpha').enabled(true))

    let offGlobalAlpha1: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(offGlobalAlpha1).$attrs.globalAlpha, 0.4)

    await button.tap()
    let offGlobalAlpha2: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(offGlobalAlpha2).$attrs.globalAlpha, 0.0)

  }, 0)
}