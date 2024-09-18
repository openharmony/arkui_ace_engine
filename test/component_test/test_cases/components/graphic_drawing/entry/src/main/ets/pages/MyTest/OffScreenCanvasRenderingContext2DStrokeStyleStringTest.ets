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

export default async function OffScreenCanvasRenderingContext2DStrokeStyleStringTest() {
  /*
 * OffScreenCanvasRenderingContext2D组件 strokeStyle属性
 * 找到画面id为OffCanvasStrokeStyle的Canvas组件
 * 找到画面文本为OffStrokeStyle的Button组件
 * 获取offCanvas的strokeStyle属性与期待值0x0000ff比对
 * 点击button，变更offCanvas的strokeStyle属性值为'#c12c1f'
 * 获取offCanvas的strokeStyle属性与期待值'#c12c1f'比对
 */
  defineTest('OffScreenCanvasRenderingContext2DStrokeStyleStringTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("OffScreenCanvasRenderingContext2DStrokeStyleStringTestDemo running")

    let driver: Tester = Tester.create()
    let offCanvas: Component = await driver.findComponent(Matcher.create().id('OffCanvasStrokeStyle').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('OffStrokeStyle').enabled(true))

    let strokeStyle1: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(strokeStyle1).$attrs.strokeStyle, 0x0000ff)

    await button.tap()
    let strokeStyle2: string = await offCanvas.getInspectorInfo()
    assertEqual(JSON.parse(strokeStyle2).$attrs.strokeStyle, '#c12c1f')
  }, 0)
}