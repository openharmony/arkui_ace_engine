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

import { assertFalse, assertTrue } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function useShadowBatchingTest() {
  /*
 * colum组件 useShadowBatching属性
 * 找到画面id为columUseShadowBatching1的colum组件
 * 找到画面文本为ButtonUseShadowBatching1的Button组件
 * 获取columUseShadowBatching1的useShadowBatching属性与期待值true比对
 * 点击button1，变更columUseShadowBatching2的useShadowBatching属性值为false
 * 获取columUseShadowBatching2的useShadowBatching属性与期待值false比对
 */
  defineTest('UseShadowBatchingTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("UseShadowBatchingTest running")
    let driver: Tester = Tester.create()
    let columUseShadowBatching1: Component =
      await driver.findComponent(Matcher.create().id('columUseShadowBatching1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonUseShadowBatching1').enabled(true))
    let useShadowBatching1: string = await columUseShadowBatching1.getInspectorInfo()
    assertTrue(JSON.parse(useShadowBatching1).$attrs.useShadowBatching)
    await button1.tap()
    let useShadowBatching2: string = await columUseShadowBatching1.getInspectorInfo()
    assertFalse(JSON.parse(useShadowBatching2).$attrs.useShadowBatching)
  }, 0)
}