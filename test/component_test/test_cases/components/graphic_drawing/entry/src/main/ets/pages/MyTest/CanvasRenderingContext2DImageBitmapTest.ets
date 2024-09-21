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

/*
 * CanvasRenderingContext2D组件 imageBitmap属性
 * 找到画面id为Canvas的Canvas组件
 * 获取canvas的imageBitmap属性与期待值"./image.jpg"比对
 */
export default async function canvasRenderingContext2DImageBitmapTest() {
  defineTest('canvasRenderingContext2DImageBitmapTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("canvasRenderingContext2DImageBitmapTestDemo running")

    let driver: Tester = Tester.create()
    let canvas: Component = await driver.findComponent(Matcher.create().id('canvasImageBitmap').enabled(true))

    let imageBitmap: string = await canvas.getInspectorInfo()
    assertFalse(JSON.parse(imageBitmap).$attrs.drawImage == undefined)
    assertEqual(JSON.parse(imageBitmap).$attrs.drawImage.image, "./image.jpg")
  }, 0)
}