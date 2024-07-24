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

export default async function canvasRenderingContext2DGlobalCompositeOperationTest() {
  /*
   * CanvasRenderingContext2D组件 globalCompositeOperation属性
   * 找到画面id为canvasGlobalCompositeOperation的Canvas组件
   * 找到画面文本为CanvasGlobalCompositeOperation的Button组件
   * 获取canvas的globalCompositeOperation属性与期待值'source-over'比对
   * 点击button，变更canvas的globalCompositeOperation属性值为'source-over'
   * 获取canvas的globalCompositeOperation属性与期待值'source-over'比对
   * 点击button，变更canvas的globalCompositeOperation属性值为'source-atop'
   * 获取canvas的globalCompositeOperation属性与期待值'source-atop'比对
   * 点击button，变更canvas的globalCompositeOperation属性值为'source-in'
   * 获取canvas的globalCompositeOperation属性与期待值'source-in'比对
   * 点击button，变更canvas的globalCompositeOperation属性值为'source-out'
   * 获取canvas的globalCompositeOperation属性与期待值'source-out'比对
   * 点击button，变更canvas的globalCompositeOperation属性值为'destination-over'
   * 获取canvas的globalCompositeOperation属性与期待值'destination-over'比对
   * 点击button，变更canvas的globalCompositeOperation属性值为'destination-atop'
   * 获取canvas的globalCompositeOperation属性与期待值'destination-atop'比对
   * 点击button，变更canvas的globalCompositeOperation属性值为'destination-in'
   * 获取canvas的globalCompositeOperation属性与期待值'destination-in'比对
   * 点击button，变更canvas的globalCompositeOperation属性值为'destination-out'
   * 获取canvas的globalCompositeOperation属性与期待值'destination-out'比对
   * 点击button，变更canvas的globalCompositeOperation属性值为'lighter'
   * 获取canvas的globalCompositeOperation属性与期待值'lighter'比对
   * 点击button，变更canvas的globalCompositeOperation属性值为'copy'
   * 获取canvas的globalCompositeOperation属性与期待值'copy'比对
   * 点击button，变更canvas的globalCompositeOperation属性值为'xor'
   * 获取canvas的globalCompositeOperation属性与期待值'xor'比对
   */
  defineTest('canvasRenderingContext2DGlobalCompositeOperationTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("canvasRenderingContext2DGlobalCompositeOperationTestDemo running")

    let driver: Tester = Tester.create()
    let canvas: Component =
      await driver.findComponent(Matcher.create().id('canvasGlobalCompositeOperation').enabled(true))
    let button: Component =
      await driver.findComponent(Matcher.create().text('CanvasGlobalCompositeOperation').enabled(true))

    let globalCompositeOperation1: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(globalCompositeOperation1).$attrs.globalCompositeOperation, 'source-over')

    await button.tap()
    let globalCompositeOperation2: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(globalCompositeOperation2).$attrs.globalCompositeOperation, 'source-over')

    await button.tap()
    let globalCompositeOperation3: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(globalCompositeOperation3).$attrs.globalCompositeOperation, 'source-atop')

    await button.tap()
    let globalCompositeOperation4: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(globalCompositeOperation4).$attrs.globalCompositeOperation, 'source-in')

    await button.tap()
    let globalCompositeOperation5: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(globalCompositeOperation5).$attrs.globalCompositeOperation, 'source-out')

    await button.tap()
    let globalCompositeOperation6: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(globalCompositeOperation6).$attrs.globalCompositeOperation, 'destination-over')

    await button.tap()
    let globalCompositeOperation7: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(globalCompositeOperation7).$attrs.globalCompositeOperation, 'destination-atop')

    await button.tap()
    let globalCompositeOperation8: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(globalCompositeOperation8).$attrs.globalCompositeOperation, 'destination-in')

    await button.tap()
    let globalCompositeOperation9: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(globalCompositeOperation9).$attrs.globalCompositeOperation, 'destination-out')

    await button.tap()
    let globalCompositeOperation10: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(globalCompositeOperation10).$attrs.globalCompositeOperation, 'lighter')

    await button.tap()
    let globalCompositeOperation11: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(globalCompositeOperation11).$attrs.globalCompositeOperation, 'copy')

    await button.tap()
    let globalCompositeOperation12: string = await canvas.getInspectorInfo()
    assertEqual(JSON.parse(globalCompositeOperation12).$attrs.globalCompositeOperation, 'xor')

  }, 0)
}