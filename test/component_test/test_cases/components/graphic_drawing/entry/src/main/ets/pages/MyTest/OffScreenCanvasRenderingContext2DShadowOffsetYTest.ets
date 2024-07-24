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

export default async function offScreenCanvasRenderingContext2DShadowOffsetYTest() {
  /*
  * OffScreenCanvasRenderingContext2D组件 shadowOffsetY属性
  * 找到画面id为offScreenCanvasRenderingContext2DShadowOffsetY的Canvas组件
  * 获取offCanvas的shadowOffsetY属性与期待值20比对
  */
  defineTest('offScreenCanvasRenderingContext2DShadowOffsetYTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("offScreenCanvasRenderingContext2DShadowOffsetYTestDemo running")

    let driver: Tester = Tester.create()
    let offCanvas: Component =
      await driver.findComponent(Matcher.create().id('offScreenCanvasRenderingContext2DShadowOffsetY').enabled(true))

    let shadowOffsetY: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(shadowOffsetY).$attrs.shadowOffsetY, 20)
  }, 0)
}