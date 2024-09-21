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

export default async function gridEdgeEffectTest() {
  /*
  * Grid组件 EdgeEffect属性
  * 找到画面id为gridEdgeEffect1，gridEdgeEffect2的Grid组件
  * 找到画面文本为GridEdgeEffect的Button组件
  * 获取gridEdgeEffect1的EdgeEffect属性与期待值{ EdgeEffect.Spring, { alwaysEnabled: true } }比对
  * 获取gridEdgeEffect2的EdgeEffect属性与期待值{ EdgeEffect.Fade, { alwaysEnabled: false } }比对
  * 点击button，变更gridEdgeEffect2的EdgeEffect属性值为{ EdgeEffect.None, { alwaysEnabled: false } }
  * 获取gridEdgeEffect2的EdgeEffect属性与期待值{ EdgeEffect.None, { alwaysEnabled: false } }比对
  */
  defineTest('gridEdgeEffectTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gridEdgeEffectTestDemo running')
    let driver: Tester = Tester.create()
    let gridEdgeEffect1: Component = await driver.findComponent(Matcher.create().id('gridEdgeEffect1').enabled(true))
    let gridEdgeEffect2: Component = await driver.findComponent(Matcher.create().id('gridEdgeEffect2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('GridEdgeEffect').enabled(true))

    let edgeEffect1: string = await gridEdgeEffect1.getInspectorInfo()
    assertEqual(JSON.parse(edgeEffect1).$attrs.edgeEffect, 'EdgeEffect.Spring')
    assertTrue(JSON.parse(edgeEffect1).$attrs.edgeEffectOptions.alwaysEnabled)
    let edgeEffect2: string = await gridEdgeEffect2.getInspectorInfo()
    assertEqual(JSON.parse(edgeEffect2).$attrs.edgeEffect, 'EdgeEffect.Fade')
    assertFalse(JSON.parse(edgeEffect2).$attrs.edgeEffectOptions.alwaysEnabled)
    await button.tap()
    let edgeEffect3: string = await gridEdgeEffect2.getInspectorInfo()
    assertEqual(JSON.parse(edgeEffect3).$attrs.edgeEffect, 'EdgeEffect.None')
    assertFalse(JSON.parse(edgeEffect3).$attrs.edgeEffectOptions.alwaysEnabled)
  }, 0)
}