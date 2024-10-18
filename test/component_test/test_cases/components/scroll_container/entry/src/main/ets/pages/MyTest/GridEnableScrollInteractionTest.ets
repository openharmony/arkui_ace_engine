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

export default async function gridEnableScrollInteractionTest() {
  /*
  * Grid组件 EnableScrollInteraction属性
  * 找到画面id为gridEnableScrollInteraction的Grid组件
  * 找到画面文本为GridEnableScrollInteraction的Button组件
  * 获取gridEnableScrollInteraction的EnableScrollInteraction属性与期待值true比对
  * 点击button，变更gridEnableScrollInteraction的EnableScrollInteraction属性值为false
  * 获取gridEnableScrollInteraction的EnableScrollInteraction属性与期待值false比对
  */
  defineTest('gridEnableScrollInteractionTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gridEnableScrollInteractionTestDemo running')
    let driver: Tester = Tester.create()
    let gridEnableScrollInteraction: Component =
      await driver.findComponent(Matcher.create().id('gridEnableScrollInteraction').enabled(true))
    let button: Component =
      await driver.findComponent(Matcher.create().text('GridEnableScrollInteraction').enabled(true))

    let enableScrollInteraction1: string = await gridEnableScrollInteraction.getInspectorInfo()
    assertTrue(JSON.parse(enableScrollInteraction1).$attrs.enableScrollInteraction)
    await button.tap()
    let enableScrollInteraction2: string = await gridEnableScrollInteraction.getInspectorInfo()
    assertFalse(JSON.parse(enableScrollInteraction2).$attrs.enableScrollInteraction)
  }, 0)
}