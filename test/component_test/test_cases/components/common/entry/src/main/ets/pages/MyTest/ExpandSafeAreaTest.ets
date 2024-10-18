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
import { assertEqual, assertFalse } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function expandSafeAreaTest() {
  /*
  * 使用Marquee组件 ExpandSafeArea属性
  * 找到画面id为marqueeExpandSafeArea1组件
  * 获取marqueeExpandSafeArea1的ExpandSafeArea属性与期待值
  * {[SafeAreaType.SYSTEM, SafeAreaType.CUTOUT, SafeAreaType.KEYBOARD],
  * [SafeAreaEdge.TOP, SafeAreaEdge.BOTTOM, SafeAreaEdge.START, SafeAreaEdge.END]}比对
  */
  defineTest('expandSafeAreaTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('expandSafeAreaTestDemo running')
    let driver: Tester = Tester.create()
    let marqueeExpandSafeArea1: Component =
      await driver.findComponent(Matcher.create().id('marqueeExpandSafeArea1').enabled(true))
    let expandSafeArea1: string = await marqueeExpandSafeArea1.getInspectorInfo()
    assertFalse(JSON.parse(expandSafeArea1).$attrs.expandSafeArea == undefined)
    assertEqual(JSON.parse(expandSafeArea1).$attrs.expandSafeArea,
      [SafeAreaType.SYSTEM, SafeAreaType.CUTOUT, SafeAreaType.KEYBOARD])
    assertEqual(JSON.parse(expandSafeArea1).$attrs.expandSafeArea,
      [SafeAreaEdge.TOP, SafeAreaEdge.BOTTOM, SafeAreaEdge.START, SafeAreaEdge.END])
  }, 0)
}