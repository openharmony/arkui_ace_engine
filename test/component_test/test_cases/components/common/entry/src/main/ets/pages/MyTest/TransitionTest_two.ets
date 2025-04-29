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
import { assertEqual, assertFalse } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function transitionTest_two() {
  /*
  * menu组件 clickEffect属性
  * 找到画面id为menu1，menu2的menu组件
  * 找到画面文本为ClickEffect1、ClickEffect2、ClickEffect3的Button组件
  * 获取menu1的ClickEffect属性与期待值 null比对
  * 获取menu2的ClickEffect属性与期待值 20比对
  * 点击button1，变更menu2的ClickEffect属性值为ClickEffectLevel.LIGHT
  * 获取menu2的ClickEffect属性与期待值ClickEffectLevel.LIGHT比对
  * 点击button2，变更menu2的ClickEffect属性值为ClickEffectLevel.MIDDLE
  * 获取menu2的ClickEffect属性与期待值ClickEffectLevel.MIDDLE比对
  * *点击button3，变更menu2的ClickEffect属性值为ClickEffectLevel.HEAVY
  * 获取menu2的ClickEffect属性与期待值ClickEffectLevel.HEAVY比对
  */
  defineTest('transitionTest_twoDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("transitionTest_twoDemo running")
    let driver: Tester = Tester.create()
    let image: Component = await driver.findComponent(Matcher.create().id('imageTransition2').enabled(true))
    let transition1: string = await image.getInspectorInfo()
    assertFalse(JSON.parse(transition1).$attrs.transition == undefined)

    assertEqual(JSON.parse(transition1)
      .$attrs
      .transition
      .asymmetric
      .appear
      .move, TransitionEdge.START)
    assertEqual(JSON.parse(transition1)
      .$attrs
      .transition
      .asymmetric
      .disappear
      .move, TransitionEdge.END)
    assertEqual(JSON.parse(transition1)
      .$attrs
      .transition
      .combine
      .translate
      .x, 100)
    assertEqual(JSON.parse(transition1)
      .$attrs
      .transition
      .combine
      .animation
      .duration, 1000)
  }, 0)
}