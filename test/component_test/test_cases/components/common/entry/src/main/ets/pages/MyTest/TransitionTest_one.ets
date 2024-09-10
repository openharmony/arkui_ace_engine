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

export default async function transitionTest_one() {
  /*
  * image组件 transition属性
  * 找到画面id为imageTransition1的image组件命名为image
  * 获取image的 transition 属性的 opacity 与期待值 1 比对
  * 获取image的 transition 属性的 opacity 与期待值 1 比对
  * 获取image的 transition 属性的 opacity 与期待值 1 比对
  * 获取image的 transition 属性的 opacity 与期待值 1 比对
  * 获取image的 transition 属性的 opacity 与期待值 1 比对
  * 点击button1，变更menu2的ClickEffect属性值为ClickEffectLevel.LIGHT
  * 获取menu2的ClickEffect属性与期待值ClickEffectLevel.LIGHT比对
  * 点击button2，变更menu2的ClickEffect属性值为ClickEffectLevel.MIDDLE
  * 获取menu2的ClickEffect属性与期待值ClickEffectLevel.MIDDLE比对
  * *点击button3，变更menu2的ClickEffect属性值为ClickEffectLevel.HEAVY
  * 获取menu2的ClickEffect属性与期待值ClickEffectLevel.HEAVY比对
  */
  defineTest('transitionTest_oneDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("transitionTest_oneDemo running")
    let driver: Tester = Tester.create()
    let image: Component = await driver.findComponent(Matcher.create().id('imageTransition1').enabled(true))
    let transition1: string = await image.getInspectorInfo()
    assertFalse(JSON.parse(transition1).$attrs.transition == undefined)

    assertEqual(JSON.parse(transition1).$attrs.transition.opacity, 1)
    assertEqual(JSON.parse(transition1)
      .$attrs
      .transition
      .translate
      .x, 10)
    assertEqual(JSON.parse(transition1)
      .$attrs
      .transition
      .translate
      .y, 10)
    assertEqual(JSON.parse(transition1)
      .$attrs
      .transition
      .translate
      .z, 10)
    assertEqual(JSON.parse(transition1)
      .$attrs
      .transition
      .scale
      .x, 1)
    assertEqual(JSON.parse(transition1)
      .$attrs
      .transition
      .scale
      .y, 1)
    assertEqual(JSON.parse(transition1)
      .$attrs
      .transition
      .scale
      .z, 1)
    assertEqual(JSON.parse(transition1)
      .$attrs
      .transition
      .scale
      .centerX, 1)
    assertEqual(JSON.parse(transition1)
      .$attrs
      .transition
      .scale
      .centerY, 1)
    assertEqual(JSON.parse(transition1)
      .$attrs
      .transition
      .rotate
      .x, 1)
    assertEqual(JSON.parse(transition1)
      .$attrs
      .transition
      .rotate
      .y, 1)
    assertEqual(JSON.parse(transition1)
      .$attrs
      .transition
      .rotate
      .z, 1)
    assertEqual(JSON.parse(transition1)
      .$attrs
      .transition
      .rotate
      .angle, 1)
    assertEqual(JSON.parse(transition1)
      .$attrs
      .transition
      .rotate
      .centerX, 1)
    assertEqual(JSON.parse(transition1)
      .$attrs
      .transition
      .rotate
      .centerY, 1)
    assertEqual(JSON.parse(transition1)
      .$attrs
      .transition
      .rotate
      .centerZ, 1)
    assertEqual(JSON.parse(transition1)
      .$attrs
      .transition
      .rotate
      .perspective, 1)
  }, 0)
}