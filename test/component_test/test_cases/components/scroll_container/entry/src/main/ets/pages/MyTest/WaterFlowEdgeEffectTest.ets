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

export default async function waterFlowEdgeEffectTest() {
  /*
* WaterFlow组件  edgeEffect属性
* 找到画面id为waterFlowEdgeEffect1,waterFlowEdgeEffect2的waterFlow组件
* 找到画面文本为WaterFlowEdgeEffect的button组件
* 获取waterFlow1的edgeEffect属性与期待值EdgeEffect.Fade,true比对
* 获取waterFlow2的edgeEffect属性与期待值EdgeEffect.Spring,true比对
* 点击button，变更waterFlow1的 edgeEffect属性值为EdgeEffect.None,false
* 获取waterFlow2的edgeEffect属性与期待值EdgeEffect.None,false比对
*/
  defineTest('waterFlowEdgeEffectTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("waterFlowEdgeEffectTestDemo running")
    let driver: Tester = Tester.create()
    let waterFlow1: Component = await driver.findComponent(Matcher.create().id('waterFlowEdgeEffect1').enabled(true))
    let waterFlow2: Component = await driver.findComponent(Matcher.create().id('waterFlowEdgeEffect2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('WaterFlowEdgeEffect').enabled(true))

    let edgeEffect1: string = await waterFlow2.getInspectorInfo()
    assertEqual(JSON.parse(edgeEffect1).$attrs.edgeEffect, 'EdgeEffect.Spring')
    assertTrue(JSON.parse(edgeEffect1).$attrs.edgeEffectOptions.alwaysEnabled)
    let edgeEffect2: string = await waterFlow1.getInspectorInfo()
    assertEqual(JSON.parse(edgeEffect2).$attrs.edgeEffect, 'EdgeEffect.Fade')
    assertTrue(JSON.parse(edgeEffect2).$attrs.edgeEffectOptions.alwaysEnabled)
    await button.tap()
    let edgeEffect3: string = await waterFlow1.getInspectorInfo()
    assertEqual(JSON.parse(edgeEffect3).$attrs.edgeEffect, 'EdgeEffect.None')
    assertFalse(JSON.parse(edgeEffect3).$attrs.edgeEffectOptions.alwaysEnabled)
  }, 0)
}