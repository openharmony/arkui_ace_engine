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
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function waterFlowEnableScrollInteractionTest() {
  /*
* WaterFlow组件 enableScrollInteraction属性
* 找到画面id为waterFlowEnableScrollInteraction的waterFlow组件
* 找到画面文本为WaterFlowEnableScrollInteraction的button组件
* 获取waterFlow的enableScrollInteraction属性与期待值true比对
* 点击button，变更waterFlow的 enableScrollInteraction属性值为false
* 获取waterFlow的enableScrollInteraction属性与期待值false比对
*/
  defineTest('waterFlowEnableScrollInteractionTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("waterFlowEnableScrollInteractionTestDemo running")
    let driver: Tester = Tester.create()
    let waterFlow: Component =
      await driver.findComponent(Matcher.create().id('waterFlowEnableScrollInteraction').enabled(true))
    let button: Component =
      await driver.findComponent(Matcher.create().text('WaterFlowEnableScrollInteraction').enabled(true))
    let enableScrollInteraction1: string = await waterFlow.getInspectorInfo()
    assertTrue(JSON.parse(enableScrollInteraction1).$attrs.enableScrollInteraction)
    await button.tap()
    let enableScrollInteraction2: string = await waterFlow.getInspectorInfo()
    assertFalse(JSON.parse(enableScrollInteraction2).$attrs.enableScrollInteraction)
  }, 0)
}
