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

export default async function blendModeTest_five() {
  /*
   * Row组件 BlendMode属性
   * 找到画面id为rowBlendMode5的组件
   * 找到画面text为ButtonBlendMode5的button组件
   * 获取rowBlendMode5的blendMode属性与期待值{ value: BlendMode.EXCLUSION, type: BlendApplyType.OFFSCREEN }比较
   * 点击button，变更rowBlendMode5的blendMode属性为{ value: BlendMode.MULTIPLY }
   * 获取rowBlendMode5的blendMode属性与期待值{ value: BlendMode.MULTIPLY }比较
   * 点击button，变更rowBlendMode5的blendMode属性为{ value: BlendMode.HUE }
   * 获取rowBlendMode5的blendMode属性与期待值{ value: BlendMode.HUE }比较
   * 点击button，变更rowBlendMode5的blendMode属性为{ value: BlendMode.SATURATION }
   * 获取rowBlendMode5的blendMode属性与期待值{ value: BlendMode.SATURATION }比较
   * 点击button，变更rowBlendMode5的blendMode属性为{ value: BlendMode.COLOR }
   * 获取rowBlendMode5的blendMode属性与期待值{ value: BlendMode.COLOR }比较
   * 点击button，变更rowBlendMode5的blendMode属性为{ value: BlendMode.LUMINOSITY }
   * 获取rowBlendMode5的blendMode属性与期待值{ value: BlendMode.LUMINOSITY }比较
   */
  defineTest('blendModeTest_fiveDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('blendModeTest_fiveDemo running')
    let driver: Tester = Tester.create()
    let rowBlendMode5: Component = await driver.findComponent(Matcher.create().id('rowBlendMode5').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonBlendMode5').enabled(true))

    let blendMode1: string = await rowBlendMode5.getInspectorInfo()
    assertEqual(JSON.parse(blendMode1).$attrs.blendMode, BlendMode.EXCLUSION)
    assertEqual(JSON.parse(blendMode1).$attrs.blendMode.type, BlendApplyType.OFFSCREEN)

    await button.tap()
    let blendMode2: string = await rowBlendMode5.getInspectorInfo()
    assertEqual(JSON.parse(blendMode2).$attrs.blendMode, BlendMode.MULTIPLY)

    await button.tap()
    let blendMode3: string = await rowBlendMode5.getInspectorInfo()
    assertEqual(JSON.parse(blendMode3).$attrs.blendMode, BlendMode.HUE)

    await button.tap()
    let blendMode4: string = await rowBlendMode5.getInspectorInfo()
    assertEqual(JSON.parse(blendMode4).$attrs.blendMode, BlendMode.SATURATION)

    await button.tap()
    let blendMode5: string = await rowBlendMode5.getInspectorInfo()
    assertEqual(JSON.parse(blendMode5).$attrs.blendMode, BlendMode.COLOR)

    await button.tap()
    let blendMode6: string = await rowBlendMode5.getInspectorInfo()
    assertEqual(JSON.parse(blendMode6).$attrs.blendMode, BlendMode.LUMINOSITY)
  }, 0)
}