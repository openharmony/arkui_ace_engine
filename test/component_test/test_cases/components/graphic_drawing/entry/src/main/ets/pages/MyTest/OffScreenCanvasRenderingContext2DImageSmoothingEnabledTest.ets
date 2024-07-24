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

export default async function offScreenCanvasRenderingContext2DImageSmoothingEnabledTest() {
  /*
   * OffScreenCanvasRenderingContext2D组件 imageSmoothingEnabled属性
   * 找到画面id为offCanvasRenderingContext2DImageSmoothingEnabled的Canvas组件
   * 找到画面文本为OffCanvasRenderingContext2DImageSmoothingEnabled的Button组件
   * 获取offCanvas的imageSmoothingEnabled属性与期待值判断是否为假
   * 点击button，变更offCanvas的imageSmoothingEnabled属性值为真
   * 获取offCanvas的imageSmoothingEnabled属性与期待值判断是否为真
   */
  defineTest('offScreenCanvasRenderingContext2DImageSmoothingEnabledTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("offScreenCanvasRenderingContext2DImageSmoothingEnabledTestDemo running")

    let driver: Tester = Tester.create()
    let offCanvas: Component =
      await driver.findComponent(Matcher.create().id('offCanvasRenderingContext2DImageSmoothingEnabled').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create()
      .text('OffCanvasRenderingContext2DImageSmoothingEnabled')
      .enabled(true))

    let offImageSmoothingEnabled1: string = await offCanvas.getInspectorInfo()
    assertFalse(JSON.parse(offImageSmoothingEnabled1).$attrs.imageSmoothingEnabled == undefined)
    assertFalse(JSON.parse(offImageSmoothingEnabled1).$attrs.imageSmoothingEnabled)

    await button.tap()
    let offImageSmoothingEnabled2: string = await offCanvas.getInspectorInfo()
    assertTrue(JSON.parse(offImageSmoothingEnabled2).$attrs.imageSmoothingEnabled)

  }, 0)
}