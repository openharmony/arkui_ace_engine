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

export default async function offScreenCanvasWidthTest() {
  /*
  * OffScreenCanvas组件 width属性
  * 找到画面id为offScreenCanvas的Canvas组件
  * 找到画面文本为OffScreenCanvas的Button组件
  * 获取offScreenCanvas的width属性与期待值100比对
  * 点击button，变更offScreenCanvas的width属性值为200
  * 获取offScreenCanvas的width属性与期待值200比对
  */
  defineTest('offScreenCanvasWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("offScreenCanvasWidthTestDemo running")

    let driver: Tester = Tester.create()
    let offScreenCanvas: Component =
      await driver.findComponent(Matcher.create().id('offScreenCanvasWidth').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('OffScreenCanvasWidth').enabled(true))

    let offCanvasWidth1: string = await offScreenCanvas.getInspectorInfo()
    assertFalse(JSON.parse(offCanvasWidth1).$attrs.fillRect == undefined)
    assertEqual(JSON.parse(offCanvasWidth1).$attrs.fillRect.width, 100)

    await button.tap()
    let offCanvasWidth2: string = await offScreenCanvas.getInspectorInfo()
    assertEqual(JSON.parse(offCanvasWidth2).$attrs.fillRect.width, 200)
  }, 0)
}