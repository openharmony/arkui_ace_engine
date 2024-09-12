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

import { assertEqual } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function blendModeTest_three() {
  /*
   * Row组件 BlendMode属性
   * 找到画面id为rowBlendMode3的组件
   * 找到画面text为ButtonBlendMode3的button组件
   * 获取rowBlendMode3的blendMode属性与期待值 BlendMode.XOR, type: BlendApplyType.OFFSCREEN 比较
   * 点击button，变更rowBlendMode3的blendMode属性为 BlendMode.PLUS
   * 获取rowBlendMode3的blendMode属性与期待值 BlendMode.PLUS 比较
   * 点击button，变更rowBlendMode3的blendMode属性为 BlendMode.MODULATE
   * 获取rowBlendMode3的blendMode属性与期待值 BlendMode.MODULATE 比较
   * 点击button，变更rowBlendMode3的blendMode属性为 BlendMode.SCREEN
   * 获取rowBlendMode3的blendMode属性与期待值 BlendMode.SCREEN 比较
   * 点击button，变更rowBlendMode3的blendMode属性为 BlendMode.OVERLAY
   * 获取rowBlendMode3的blendMode属性与期待值 BlendMode.OVERLAY 比较
   * 点击button，变更rowBlendMode3的blendMode属性为 BlendMode.DARKEN
   * 获取rowBlendMode3的blendMode属性与期待值 BlendMode.DARKEN 比较
   */
  defineTest('blendModeTest_threeDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('blendModeTest_threeDemo running')
    let driver: Tester = Tester.create()
    let rowBlendMode3: Component = await driver.findComponent(Matcher.create().id('rowBlendMode3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonBlendMode3').enabled(true))

    let blendMode1: string = await rowBlendMode3.getInspectorInfo()
    assertEqual(JSON.parse(blendMode1).$attrs.blendMode, BlendMode.XOR)
    assertEqual(JSON.parse(blendMode1).$attrs.blendMode.type, BlendApplyType.OFFSCREEN)

    await button.tap()
    let blendMode2: string = await rowBlendMode3.getInspectorInfo()
    assertEqual(JSON.parse(blendMode2).$attrs.blendMode, BlendMode.PLUS)

    await button.tap()
    let blendMode3: string = await rowBlendMode3.getInspectorInfo()
    assertEqual(JSON.parse(blendMode3).$attrs.blendMode, BlendMode.MODULATE)

    await button.tap()
    let blendMode4: string = await rowBlendMode3.getInspectorInfo()
    assertEqual(JSON.parse(blendMode4).$attrs.blendMode, BlendMode.SCREEN)

    await button.tap()
    let blendMode5: string = await rowBlendMode3.getInspectorInfo()
    assertEqual(JSON.parse(blendMode5).$attrs.blendMode, BlendMode.OVERLAY)

    await button.tap()
    let blendMode6: string = await rowBlendMode3.getInspectorInfo()
    assertEqual(JSON.parse(blendMode6).$attrs.blendMode, BlendMode.DARKEN)
  }, 0)
}