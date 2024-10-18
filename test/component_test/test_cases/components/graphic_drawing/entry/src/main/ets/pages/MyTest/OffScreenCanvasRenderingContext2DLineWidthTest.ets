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

export default async function offScreenCanvasRenderingContext2DLineWidthTest() {
  /*
   * OffScreenCanvasRenderingContext2D组件 lineWidth属性
   * 找到画面id为offScreenCanvasRenderingContext2DLineWidth的Canvas组件
   * 找到画面文本为OffScreenCanvasRenderingContext2DLineWidth的Button组件
   * 获取offCanvas的lineWidth属性与期待值5比对
   * 点击button，变更canvas的lineWidth属性值为10
   * 获取offCanvas的lineWidth属性与期待值10比对
   */
  defineTest('offScreenCanvasRenderingContext2DLineWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("offScreenCanvasRenderingContext2DLineWidthTestDemo running")

    let driver: Tester = Tester.create()
    let offCanvas: Component =
      await driver.findComponent(Matcher.create().id('offScreenCanvasRenderingContext2DLineWidth').enabled(true))
    let button: Component =
      await driver.findComponent(Matcher.create().text('OffScreenCanvasRenderingContext2DLineWidth').enabled(true))

    let lineWidth1: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(lineWidth1).$attrs.lineWidth, 5)

    await button.tap()
    let lineWidth2: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(lineWidth2).$attrs.lineWidth, 10)
  }, 0)
}