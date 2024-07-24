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
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function scrollEnableScrollInteractionTest() {
  /*
 * Scroll组件 EnableScrollInteraction属性
 * 找到画面id为scrollEnableScrollInteraction的Scroll组件
 * 找到画面文本为scrollEnableScrollInteraction的Button组件
 * 获取scrollEnableScrollInteraction的EnableScrollInteraction属性与期待值True比对
 * 点击button，变更scrollEnableScrollInteraction的EnableScrollInteraction属性值为False
 * 获取scrollEnableScrollInteraction的EnableScrollInteraction属性与期待值False比对
 */
  defineTest('scrollEnableScrollInteractionTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('scrollEnableScrollInteractionTestDemo running')
    let driver: Tester = Tester.create()
    let scrollEnableScrollInteraction: Component =
      await driver.findComponent(Matcher.create().id('scrollEnableScrollInteraction').enabled(true))
    let button: Component =
      await driver.findComponent(Matcher.create().text('ScrollEnableScrollInteraction').enabled(true))

    let enableScrollInteraction1: string = await scrollEnableScrollInteraction.getInspectorInfo()
    assertTrue(JSON.parse(enableScrollInteraction1).$attrs.enableScrollInteraction)
    await button.tap()
    let enableScrollInteraction2: string = await scrollEnableScrollInteraction.getInspectorInfo()
    assertFalse(JSON.parse(enableScrollInteraction2).$attrs.enableScrollInteraction)
  }, 0)
}