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

export default async function listChainAnimationTest() {
  /*
   * List组件 ChainAnimation属性
   * 找到画面id为listChainAnimation1,listChainAnimation2的List组件
   * 找到画面文本为ListChainAnimation的Button组件
   * 获取list的ChainAnimation属性与期待值false比对
   * 点击button，变更list1的ChainAnimation属性值为true
   * 获取list的ChainAnimation属性与期待值true比对
   */
  defineTest('listChainAnimationTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('listChainAnimationTestDemo running')
    let driver: Tester = Tester.create()
    let list: Component = await driver.findComponent(Matcher.create().id('listChainAnimation').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ListChainAnimation').enabled(true))

    let chainAnimation1: string = await list.getInspectorInfo()
    assertFalse(JSON.parse(chainAnimation1).$attrs.chainAnimation)
    await button.tap()
    let chainAnimation2: string = await list.getInspectorInfo()
    assertTrue(JSON.parse(chainAnimation2).$attrs.chainAnimation)
  }, 0)
}