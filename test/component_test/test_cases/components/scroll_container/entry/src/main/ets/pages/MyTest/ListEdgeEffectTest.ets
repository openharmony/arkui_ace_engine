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

export default async function listEdgeEffectTest() {
  /*
   * List组件 EdgeEffect属性
   * 找到画面id为listEdgeEffect1,listEdgeEffect2的List组件
   * 找到画面文本为ListEdgeEffect的Button组件
   * 获取list1的EdgeEffect属性与期待值{EdgeEffect.Fade,true}比对
   * 获取list2的EdgeEffect属性与期待值{EdgeEffect.None,false}比对
   * 点击button，变更list1的EdgeEffect属性值为EdgeEffect.Spring
   * 获取list1的EdgeEffect属性与期待值EdgeEffect.Spring比对
   */
  defineTest('listEdgeEffectTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('listEdgeEffectTestDemo running')
    let driver: Tester = Tester.create()
    let list1: Component = await driver.findComponent(Matcher.create().id('listEdgeEffect1').enabled(true))
    let list2: Component = await driver.findComponent(Matcher.create().id('listEdgeEffect2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ListEdgeEffect').enabled(true))

    let edgeEffect1: string = await list1.getInspectorInfo()
    assertEqual(JSON.parse(edgeEffect1).$attrs.edgeEffect, 'EdgeEffect.Fade')
    assertTrue(JSON.parse(edgeEffect1).$attrs.edgeEffectOptions.alwaysEnabled)
    let edgeEffect2: string = await list2.getInspectorInfo()
    assertEqual(JSON.parse(edgeEffect2).$attrs.edgeEffect, 'EdgeEffect.None')
    assertFalse(JSON.parse(edgeEffect2).$attrs.edgeEffectOptions.alwaysEnabled)
    await button.tap()
    let edgeEffect3: string = await list1.getInspectorInfo()
    assertEqual(JSON.parse(edgeEffect3).$attrs.edgeEffect, 'EdgeEffect.Spring')
  }, 0)
}