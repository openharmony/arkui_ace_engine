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
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function waterFlowNestedScrollTest() {
  /*
* WaterFlow组件  nestedScroll属性
* 找到画面id为waterFlowNestedScroll1,waterFlowNestedScroll2的waterFlow组件
* 找到画面文本为WaterFlowNestedScroll1,WaterFlowNestedScroll2的button组件
* 获取waterFlow1的nestedScroll属性与期待值NestedScrollMode.SELF_ONLY,NestedScrollMode.SELF_ONLY比对
* 获取waterFlow2的nestedScroll属性与期待值NestedScrollMode.SELF_FIRST,NestedScrollMode.SELF_FIRST比对
* 点击button1，变更waterFlow2的nestedScroll属性值为NestedScrollMode.PARENT_FIRST,NestedScrollMode.PARENT_FIRST
* 获取waterFlow2的nestedScroll属性与期待值NestedScrollMode.PARENT_FIRST,NestedScrollMode.PARENT_FIRST比对
* 点击button2，变更waterFlow2的nestedScroll属性值为NestedScrollMode.PARALLEL,NestedScrollMode.PARALLEL
* 获取waterFlow2的nestedScroll属性与期待值NestedScrollMode.PARALLEL,NestedScrollMode.PARALLEL比对
*/
  defineTest('waterFlowNestedScrollTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("waterFlowNestedScrollTestDemo running")
    let driver: Tester = Tester.create()
    let waterFlow1: Component = await driver.findComponent(Matcher.create().id('waterFlowNestedScroll1').enabled(true))
    let waterFlow2: Component = await driver.findComponent(Matcher.create().id('waterFlowNestedScroll2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('WaterFlowNestedScroll1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('WaterFlowNestedScroll2').enabled(true))
    let nestedScroll1: string = await waterFlow1.getInspectorInfo()
    assertFalse(JSON.parse(nestedScroll1).$attrs.nestedScroll == undefined)
    assertEqual(JSON.parse(nestedScroll1).$attrs.nestedScroll.scrollForward, NestedScrollMode.SELF_ONLY)
    assertEqual(JSON.parse(nestedScroll1).$attrs.nestedScroll.scrollBackward, NestedScrollMode.SELF_ONLY)
    let nestedScroll2: string = await waterFlow2.getInspectorInfo()
    assertEqual(JSON.parse(nestedScroll2).$attrs.nestedScroll.scrollForward, NestedScrollMode.SELF_FIRST)
    assertEqual(JSON.parse(nestedScroll2).$attrs.nestedScroll.scrollBackward, NestedScrollMode.SELF_FIRST)
    await button1.tap()
    let nestedScroll3: string = await waterFlow2.getInspectorInfo()
    assertEqual(JSON.parse(nestedScroll3).$attrs.nestedScroll.scrollForward, NestedScrollMode.PARENT_FIRST)
    assertEqual(JSON.parse(nestedScroll3).$attrs.nestedScroll.scrollBackward, NestedScrollMode.PARENT_FIRST)
    await button2.tap()
    let nestedScroll4: string = await waterFlow2.getInspectorInfo()
    assertEqual(JSON.parse(nestedScroll4).$attrs.nestedScroll.scrollForward, NestedScrollMode.PARALLEL)
    assertEqual(JSON.parse(nestedScroll4).$attrs.nestedScroll.scrollBackward, NestedScrollMode.PARALLEL)
  }, 0)
}