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

export default async function blendModeTest_one() {
  /*
   * Row组件 BlendMode属性
   * 找到画面id为rowBlendMode1的组件
   * 找到画面text为ButtonBlendMode1的button组件
   * 获取rowBlendMode1的blendMode属性与期待值 BlendMode.NONE, BlendApplyType.OFFSCREEN 比较
   * 点击button，变更rowBlendMode1的blendMode属性为 BlendMode.CLEAR
   * 获取rowBlendMode1的blendMode属性与期待值 BlendMode.CLEAR 比较
   * 点击button，变更rowBlendMode1的blendMode属性为 BlendMode.SRC
   * 获取rowBlendMode1的blendMode属性与期待值 BlendMode.SRC 比较
   * 点击button，变更rowBlendMode1的blendMode属性为 BlendMode.DST
   * 获取rowBlendMode1的blendMode属性与期待值 BlendMode.DST 比较
   * 点击button，变更rowBlendMode1的blendMode属性为 BlendMode.SRC_OVER
   * 获取rowBlendMode1的blendMode属性与期待值 BlendMode.SRC_OVER 比较
   * 点击button，变更rowBlendMode1的blendMode属性为 BlendMode.DST_OVER
   * 获取rowBlendMode1的blendMode属性中的value与期待值 BlendMode.DST_OVER 比较
   */

  defineTest('blendModeTest_oneDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('blendModeTest_oneDemo running')
    let driver: Tester = Tester.create()
    let rowBlendMode1: Component = await driver.findComponent(Matcher.create().id('rowBlendMode1').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonBlendMode1').enabled(true))

    let blendMode1: string = await rowBlendMode1.getInspectorInfo()
    assertEqual(JSON.parse(blendMode1).$attrs.blendMode, BlendMode.NONE)
    assertEqual(JSON.parse(blendMode1).$attrs.blendMode.type, BlendApplyType.OFFSCREEN)

    await button.tap()
    let blendMode2: string = await rowBlendMode1.getInspectorInfo()
    assertEqual(JSON.parse(blendMode2).$attrs.blendMode, BlendMode.CLEAR)

    await button.tap()
    let blendMode3: string = await rowBlendMode1.getInspectorInfo()
    assertEqual(JSON.parse(blendMode3).$attrs.blendMode, BlendMode.SRC)

    await button.tap()
    let blendMode4: string = await rowBlendMode1.getInspectorInfo()
    assertEqual(JSON.parse(blendMode4).$attrs.blendMode, BlendMode.DST)

    await button.tap()
    let blendMode5: string = await rowBlendMode1.getInspectorInfo()
    assertEqual(JSON.parse(blendMode5).$attrs.blendMode, BlendMode.SRC_OVER)

    await button.tap()
    let blendMode6: string = await rowBlendMode1.getInspectorInfo()
    assertEqual(JSON.parse(blendMode6).$attrs.blendMode, BlendMode.DST_OVER)
  }, 0)
}