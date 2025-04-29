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

export default async function buttonStateEffectTest() {
  /*
   * Button组件 StateEffect属性
   * 找到画面id为buttonStateEffect的Button组件
   * 找到画面文本为ButtonStateEffect的Button组件
   * 获取buttonStateEffect的StateEffect属性与期待值true比对
   * 点击button，变更buttonStateEffect的StateEffect属性值为false
   * 获取buttonStateEffect的StateEffect属性与期待值false比对
   */
  defineTest('buttonStateEffectTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('buttonStateEffectTestDemo running')
    let driver: Tester = Tester.create()
    let buttonStateEffect: Component =
      await driver.findComponent(Matcher.create().id('buttonStateEffect').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonStateEffect').enabled(true))

    let effect1: string = await buttonStateEffect.getInspectorInfo()
    assertTrue(JSON.parse(effect1).$attrs.stateEffect)

    await button.tap()
    let effect2: string = await buttonStateEffect.getInspectorInfo()
    assertFalse(JSON.parse(effect2).$attrs.stateEffect)
  }, 0)
}