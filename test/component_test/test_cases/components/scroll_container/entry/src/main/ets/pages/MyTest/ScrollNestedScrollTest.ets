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
  assertEqual,
  assertFalse,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function scrollNestedScrollTest() {
  /*
 * Scroll组件 NestedScroll属性
 * 找到画面id为scrollNestedScroll的Scroll组件
 * 找到画面文本为ScrollNestedScroll的Button组件
 * 获取scrollNestedScroll的{ NestedScroll.ScrollForward, NestedScroll.ScrollBackward }属性与期待值{ NestedScrollMode.PARALLEL, NestedScrollMode.PARALLEL }比对
 * 点击button，变更scrollNestedScroll的NestedScroll属性值为NestedScrollMode.PARENT_FIRST
 * 获取scrollNestedScroll的{ NestedScroll.ScrollForward, NestedScroll.ScrollBackward }属性与期待值{ NestedScrollMode.PARENT_FIRST, NestedScrollMode.PARENT_FIRST }比对
 * 点击button，变更scrollNestedScroll的NestedScroll属性值为NestedScrollMode.SELF_FIRST
 * 获取scrollNestedScroll的{ NestedScroll.ScrollForward, NestedScroll.ScrollBackward }属性与期待值{ NestedScrollMode.SELF_FIRST, NestedScrollMode.SELF_FIRST }比对
 * 点击button，变更scrollNestedScroll的NestedScroll属性值为NestedScrollMode.SELF_ONLY
 * 获取scrollNestedScroll的{ NestedScroll.ScrollForward, NestedScroll.ScrollBackward }属性与期待值{ NestedScrollMode.SELF_ONLY, NestedScrollMode.SELF_ONLY }比对
 */
  defineTest('scrollNestedScrollTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('scrollNestedScrollTestDemo running')
    let driver: Tester = Tester.create()
    let scrollNestedScroll: Component =
      await driver.findComponent(Matcher.create().id('scrollNestedScroll').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ScrollNestedScroll').enabled(true))

    let nestedScroll1: string = await scrollNestedScroll.getInspectorInfo()
    assertFalse(JSON.parse(nestedScroll1).$attrs.nestedScroll == undefined)
    assertEqual(JSON.parse(nestedScroll1).$attrs.nestedScroll.scrollForward, NestedScrollMode.PARALLEL)
    assertEqual(JSON.parse(nestedScroll1).$attrs.nestedScroll.scrollBackward, NestedScrollMode.PARALLEL)
    await button.tap()
    let nestedScroll2: string = await scrollNestedScroll.getInspectorInfo()
    assertEqual(JSON.parse(nestedScroll2).$attrs.nestedScroll.scrollForward, NestedScrollMode.PARENT_FIRST)
    assertEqual(JSON.parse(nestedScroll2).$attrs.nestedScroll.scrollBackward, NestedScrollMode.PARENT_FIRST)
    await button.tap()
    let nestedScroll3: string = await scrollNestedScroll.getInspectorInfo()
    assertEqual(JSON.parse(nestedScroll3).$attrs.nestedScroll.scrollForward, NestedScrollMode.SELF_FIRST)
    assertEqual(JSON.parse(nestedScroll3).$attrs.nestedScroll.scrollBackward, NestedScrollMode.SELF_FIRST)
    await button.tap()
    let nestedScroll4: string = await scrollNestedScroll.getInspectorInfo()
    assertEqual(JSON.parse(nestedScroll4).$attrs.nestedScroll.scrollForward, NestedScrollMode.SELF_ONLY)
    assertEqual(JSON.parse(nestedScroll4).$attrs.nestedScroll.scrollBackward, NestedScrollMode.SELF_ONLY)
  }, 0)
}