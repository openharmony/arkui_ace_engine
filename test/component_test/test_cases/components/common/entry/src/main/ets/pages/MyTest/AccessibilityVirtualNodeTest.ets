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
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest';

export default async function accessibilityVirtualNodeTest() {
  /*
  * text组件 accessibilityVirtualNode属性
  * 找到画面id为textAccessibilityVirtualNode1的text组件
  * 获取textAccessibilityVirtualNode1的文字与期待值 'customAccessibilityNode' 比对
  */
  defineTest('accessibilityVirtualNodeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("accessibilityVirtualNodeTestDemo running")
    let driver: Tester = Tester.create()
    let textAccessibilityVirtualNode1: Component =
      await driver.findComponent(Matcher.create().id('textAccessibilityVirtualNode1').enabled(true))
    let accessibilityVirtualNode1: string = await textAccessibilityVirtualNode1.getInspectorInfo()
    assertFalse(JSON.parse(accessibilityVirtualNode1).$attrs.accessibilityVirtualNode == undefined)
    assertEqual(JSON.parse(accessibilityVirtualNode1).$attrs.accessibilityVirtualNode, 'customAccessibilityNode')
  }, 0)
}