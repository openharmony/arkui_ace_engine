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

export default async function canvasRenderingContext2DImageSmoothingEnabledTest() {
  /*
   * CanvasRenderingContext2D组件 imageSmoothingEnabled属性
   * 找到画面id为canvasImageSmoothingEnabled的Canvas组件
   * 找到画面文本为CanvasImageSmoothingEnabled的Button组件
   * 获取canvas的imageSmoothingEnabled属性与期待值判断是否为假
   * 点击button，变更canvas的imageSmoothingEnabled属性值为真
   * 获取canvas的imageSmoothingEnabled属性与期待值判断是否为真
   */
  defineTest('canvasRenderingContext2DImageSmoothingEnabledTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("canvasRenderingContext2DImageSmoothingEnabledTestDemo running")

    let driver: Tester = Tester.create()
    let canvas: Component = await driver.findComponent(Matcher.create().id('canvasImageSmoothingEnabled').enabled(true))
    let button: Component =
      await driver.findComponent(Matcher.create().text('CanvasImageSmoothingEnabled').enabled(true))

    let imageSmoothingEnabled1: string = await canvas.getInspectorInfo()
    assertFalse(JSON.parse(imageSmoothingEnabled1).$attrs.imageSmoothingEnabled == undefined)
    await button.tap()
    let imageSmoothingEnabled2: string = await canvas.getInspectorInfo()
    assertTrue(JSON.parse(imageSmoothingEnabled2).$attrs.imageSmoothingEnabled)
  }, 0)
}