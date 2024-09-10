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

export default async function offScreenCanvasHeightTest() {
  /*
   * OffScreenCanvas组件 height属性
   * 找到画面id为offScreenCanvasHeight的OffScreenCanvas组件
   * 找到画面文本为OffScreenCanvasHeight的Button组件
   * 获取offScreenCanvas的height属性与期待值100比对
   * 点击button，变更offScreenCanvas的height属性值为200
   * 获取offScreenCanvas的height属性与期待值200比对
   */
  defineTest('offScreenCanvasHeightTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("offScreenCanvasHeightTestDemo running")

    let driver: Tester = Tester.create()
    let offScreenCanvas: Component =
      await driver.findComponent(Matcher.create().id('offScreenCanvasHeight').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('OffScreenCanvasHeight').enabled(true))

    let offCanvasHeight1: string = await offScreenCanvas.getInspectorInfo()
    assertFalse(JSON.parse(offCanvasHeight1).$attrs.fillRect == undefined)
    assertEqual(JSON.parse(offCanvasHeight1).$attrs.fillRect.height, 100)

    await button.tap()
    let offCanvasHeight2: string = await offScreenCanvas.getInspectorInfo()
    assertEqual(JSON.parse(offCanvasHeight2).$attrs.fillRect.height, 200)
  }, 0)
}