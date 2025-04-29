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

import { assertEqual, assertFalse, assertTrue } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function sharedTransitionTest() {
  /*
  * rect组件 sharedTransition属性
  * 找到画面id为 rectSharedTransition1 的rect组件
  * 获取 rectSharedTransition1 的sharedTransition属性下id参数与期待值'sharedTransitionRect'比对
  * 获取 rectSharedTransition1 的sharedTransition属性下duration参数与期待值800比对
  * 获取 rectSharedTransition1 的sharedTransition属性下curve参数与期待值 Curve.Linear 比对
  * 获取 rectSharedTransition1 的sharedTransition属性下delay参数与期待值10比对
  * 获取 rectSharedTransition2 的sharedTransition属性下motionPath的Path参数与期待值'Mstart.x start.y L300 200 L300 500 Lend.x end.y'比对
  * 获取 rectSharedTransition2 的sharedTransition属性下motionPath的from参数与期待值0.0比对
  * 获取 rectSharedTransition2 的sharedTransition属性下motionPath的to参数与期待值1.0比对
  * 获取 rectSharedTransition2 的sharedTransition属性下motionPath的rotatable参数与期待值true比对
  * 获取 rectSharedTransition2 的sharedTransition属性下zIndex参数与期待值10比对
  * 获取 rectSharedTransition2 的sharedTransition属性下type参数与期待值SharedTransitionEffectType.Static比对
  * 点击 id为 rectSharedTransition1 的 rect 组件，引入 MyTest 文件中的SharedTransitionTargetPage 的界面
  * 找到画面id为 rectSharedTransition2 的rect组件
  * 获取 rectSharedTransition2 的sharedTransition属性下curve参数与期待值1比对
  * 获取 rectSharedTransition2 的sharedTransition属性下type参数与期待值SharedTransitionEffectType.Exchange比对
  */
  defineTest('sharedTransitionTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("sharedTransitionTest running")
    let driver: Tester = Tester.create()
    let rectSharedTransition1: Component =
      await driver.findComponent(Matcher.create().id('rectSharedTransition1').enabled(true))
    let sharedTransition1: string = await rectSharedTransition1.getInspectorInfo()
    assertFalse(JSON.parse(sharedTransition1).$attrs.sharedTransition == undefined)
    assertEqual(JSON.parse(sharedTransition1).$attrs.sharedTransition, 'sharedTransitionRect')
    assertEqual(JSON.parse(sharedTransition1).$attrs.sharedTransition.duration, 800)
    assertEqual(JSON.parse(sharedTransition1).$attrs.sharedTransition.curve, Curve.Linear)
    assertEqual(JSON.parse(sharedTransition1).$attrs.sharedTransition.delay, 10)
    assertEqual(JSON.parse(sharedTransition1)
      .$attrs
      .sharedTransition
      .motionPath
      .path, 'Mstart.x start.y L300 200 L300 500 Lend.x end.y')
    assertEqual(JSON.parse(sharedTransition1)
      .$attrs
      .sharedTransition
      .motionPath
      .from, 0.0)
    assertEqual(JSON.parse(sharedTransition1)
      .$attrs
      .sharedTransition
      .motionPath
      .to, 1.0)
    assertTrue(JSON.parse(sharedTransition1)
      .$attrs
      .sharedTransition
      .motionPath
      .rotatable)
    assertEqual(JSON.parse(sharedTransition1).$attrs.sharedTransition.zIndex, 10)
    assertEqual(JSON.parse(sharedTransition1).$attrs.sharedTransition.type, SharedTransitionEffectType.Static)

    await rectSharedTransition1.tap()
    let rectSharedTransition2: Component =
      await driver.findComponent(Matcher.create().id('rectSharedTransition2').enabled(true))
    let sharedTransition2: string = await rectSharedTransition2.getInspectorInfo()
    assertEqual(JSON.parse(sharedTransition2).$attrs.sharedTransition.curve, 1)
    assertEqual(JSON.parse(sharedTransition2).$attrs.sharedTransition.type, SharedTransitionEffectType.Exchange)
  }, 0)
}