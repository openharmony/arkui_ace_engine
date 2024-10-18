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

export default async function canvasRenderingContext2DShadowBlurTest() {
  /*
    * CanvasRenderingContext2D组件 shadowBlur属性
    * 找到画面id为canvasShadowBlur的Canvas组件
    * 找到画面文本为CanvasShadowBlur的Button组件
    * 获取canvas的shadowBlur属性与期待值30比对
    * 点击button，变更canvas的shadowBlur属性值为-2.0
    * 获取canvas的shadowBlur属性与期待值0.0比对
    */
  defineTest('canvasRenderingContext2DShadowBlurTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("canvasRenderingContext2DShadowBlurTestDemo running")

    let driver: Tester = Tester.create()
    let canvas: Component = await driver.findComponent(Matcher.create().id('canvasShadowBlur').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('CanvasShadowBlur').enabled(true))

    let shadowBlur1: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(shadowBlur1).$attrs.shadowBlur, 5.0)

    await button.tap()
    let shadowBlur2: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(shadowBlur2).$attrs.shadowBlur, 0.0)
  }, 0)
}