/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 // * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import {
  assertEqual,
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function scrollEdgeEffectTest() {
  /*
   * Scroll组件 EdgeEffect属性
   * 找到画面id为scrollEdgeEffect1,scrollEdgeEffect2的Scroll组件
   * 找到画面文本为scrollEdgeEffect的Button组件
   * 获取scrollEdgeEffect1的{ edgeEffect.EdgeEffect, edgeEffect.AlwaysEnabled }属性与期待值{ EdgeEffect.None, true }比对
   * 获取scrollEdgeEffect2的{ edgeEffect.EdgeEffect, edgeEffect.AlwaysEnabled }属性与期待值{ EdgeEffect.Spring, false }比对
   * 点击button，变更scrollEdgeEffect2的BarState属性值为EdgeEffect.Fade
   * 获取scrollEdgeEffect2的{ edgeEffect.EdgeEffect, edgeEffect.AlwaysEnabled }属性与期待值{ EdgeEffect.Fade, false }比对
   */
  defineTest('scrollEdgeEffectTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('scrollEdgeEffectTestDemo running')
    let driver: Tester = Tester.create()
    let scrollEdgeEffect1: Component =
      await driver.findComponent(Matcher.create().id('scrollEdgeEffect1').enabled(true))
    let scrollEdgeEffect2: Component =
      await driver.findComponent(Matcher.create().id('scrollEdgeEffect2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ScrollEdgeEffect').enabled(true))

    let edgeEffect1: string = await scrollEdgeEffect1.getInspectorInfo()
    assertEqual(JSON.parse(edgeEffect1).$attrs.edgeEffect, 'EdgeEffect.None')
    assertTrue(JSON.parse(edgeEffect1).$attrs.edgeEffectOptions.alwaysEnabled)
    let edgeEffect2: string = await scrollEdgeEffect2.getInspectorInfo()
    assertEqual(JSON.parse(edgeEffect2).$attrs.edgeEffect, 'EdgeEffect.Spring')
    assertFalse(JSON.parse(edgeEffect2).$attrs.edgeEffectOptions.alwaysEnabled)
    await button.tap()
    let edgeEffect3: string = await scrollEdgeEffect2.getInspectorInfo()
    assertEqual(JSON.parse(edgeEffect3).$attrs.edgeEffect, 'EdgeEffect.Fade')
    assertFalse(JSON.parse(edgeEffect3).$attrs.edgeEffectOptions.alwaysEnabled)
  }, 0)
}