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

export default async function waterFlowCachedCountTest() {
  /*
* WaterFlow组件 cachedCount属性
* 找到画面id为waterFlowCachedCount的waterFlow组件
* 找到画面文本为WaterFlowCachedCount的button组件
* 获取waterFlow的cachedCount属性与期待值4比对
* 点击button，变更waterFlow的cachedCount属性值为-1
* 获取waterFlow的cachedCount属性与期待值1比对
*/
  defineTest('waterFlowCachedCountTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("waterFlowCachedCountTestDemo running")
    let driver: Tester = Tester.create()
    let waterFlow: Component = await driver.findComponent(Matcher.create().id('waterFlowCachedCount').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('WaterFlowCachedCount').enabled(true))
    let cachedCount1: string = await waterFlow.getInspectorInfo()
    assertFalse(JSON.parse(cachedCount1).$attrs.cachedCount == undefined)
    assertEqual(JSON.parse(cachedCount1).$attrs.cachedCount, 4)
    await button.tap()
    let cachedCount2: string = await waterFlow.getInspectorInfo()
    assertEqual(JSON.parse(cachedCount2).$attrs.cachedCount, 1)
  }, 0)
}
