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

export default async function canvasRenderingContext2DFilterTest() {
  /*
   * CanvasRenderingContext2D组件 filter属性
   * 找到画面id为canvasFilter的Circle组件
   * 找到画面文本为CanvasFilter的Button组件
   * 获取canvas的filter属性与期待值'none'比对
   * 点击button，变更canvas的filter属性值为'none'
   * 获取canvas的filter属性与期待值'none'比对
   * 点击button，变更canvas的filter属性值为'grayscale(50%)'
   * 获取canvas的filter属性与期待值'grayscale(50%)'比对
   * 点击button，变更canvas的filter属性值为'sepia(60%)'
   * 获取canvas的filter属性与期待值'sepia(60%)'比对
   * 点击button，变更canvas的filter属性值为'saturate(30%)'
   * 获取canvas的filter属性与期待值'saturate(30%)'比对
   * 点击button，变更canvas的filter属性值为'hue-rotate(90deg)'
   * 获取canvas的filter属性与期待值'hue-rotate(90deg)'比对
   * 点击button，变更canvas的filter属性值为'invert(100%)'
   * 获取canvas的filter属性与期待值'invert(100%)'比对
   * 点击button，变更canvas的filter属性值为'opacity(25%)'
   * 获取canvas的filter属性与期待值'opacity(25%)'比对
   * 点击button，变更canvas的filter属性值为'brightness(0.4)'
   * 获取canvas的filter属性与期待值'brightness(0.4)'比对
   * 点击button，变更canvas的filter属性值为'contrast(200%)'
   * 获取canvas的filter属性与期待值'contrast(200%)'比对
   * 点击button，变更canvas的filter属性值为'blur(5px)'
   * 获取canvas的filter属性与期待值'blur(5px)'比对
   */
  defineTest('canvasRenderingContext2DFilterTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("canvasRenderingContext2DFilterTestDemo running")

    let driver: Tester = Tester.create()
    let canvas: Component = await driver.findComponent(Matcher.create().id('canvasFilter').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('CanvasFilter').enabled(true))

    let filter1: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(filter1).$attrs.filter, 'none')

    await button.tap()
    let filter2: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(filter2).$attrs.filter, 'none')

    await button.tap()
    let filter3: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(filter3).$attrs.filter, 'grayscale(50%)')

    await button.tap()
    let filter4: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(filter4).$attrs.filter, 'sepia(60%)')

    await button.tap()
    let filter5: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(filter5).$attrs.filter, 'saturate(30%)')

    await button.tap()
    let filter6: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(filter6).$attrs.filter, 'hue-rotate(90deg)')

    await button.tap()
    let filter7: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(filter7).$attrs.filter, 'invert(100%)')

    await button.tap()
    let filter8: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(filter8).$attrs.filter, 'opacity(25%)')

    await button.tap()
    let filter9: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(filter9).$attrs.filter, 'brightness(0.4)')

    await button.tap()
    let filter10: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(filter10).$attrs.filter, 'contrast(200%)')

    await button.tap()
    let filter11: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(filter11).$attrs.filter, 'blur(5px)')
  }, 0)
}