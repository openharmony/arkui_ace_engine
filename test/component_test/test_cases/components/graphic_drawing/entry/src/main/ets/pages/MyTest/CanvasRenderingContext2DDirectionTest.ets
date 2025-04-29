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

export default async function canvasRenderingContext2DDirectionTest() {
  /*
   * CanvasRenderingContext2D组件 direction属性
   * 找到画面id为canvasDirection的Canvas组件
   * 找到画面文本为CanvasDirection1,CanvasDirection2的Button组件
   * 获取canvas的direction属性与期待值'inherit'比对
   * 点击button1，变更canvas的direction属性值为'rtl'
   * 获取canvas的direction属性与期待值'rtl'比对
   * 点击button2，变更canvas的direction属性值为'ltr'
   * 获取canvas的direction属性与期待值'ltr'比对
   */
  defineTest('canvasRenderingContext2DDirectionTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("canvasRenderingContext2DDirectionTestDemo running")

    let driver: Tester = Tester.create()
    let canvas: Component = await driver.findComponent(Matcher.create().id('canvasDirection').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('CanvasDirection1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('CanvasDirection2').enabled(true))

    let direction1: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(direction1).$attrs.direction, 'inherit')

    await button1.tap()
    let direction2: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(direction2).$attrs.direction, 'rtl')

    await button2.tap()
    let direction3: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(direction3).$attrs.direction, 'ltr')
  }, 0)
}