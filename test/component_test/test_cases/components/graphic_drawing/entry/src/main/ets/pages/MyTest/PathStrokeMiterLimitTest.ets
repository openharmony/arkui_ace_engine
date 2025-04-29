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

import { assertEqual, assertContain, assertFalse, assertTrue } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function pathStrokeMiterLimitTest() {
  /*
   * Path组件 strokeMiterLimit属性
   * 找到画面id为pathStrokeMiterLimit的Path组件
   * 找到画面文本为PathStrokeMiterLimit的Button组件
   * 获取path的strokeMiterLimit属性与期待值10比对
   * 点击button，变更path的strokeMiterLimit属性值为'15'
   * 获取path的strokeMiterLimit属性与期待值'15'比对
   */
  defineTest('pathStrokeMiterLimitTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("pathStrokeMiterLimitTestDemo running")
    let driver: Tester = Tester.create()
    let path: Component = await driver.findComponent(Matcher.create().id('pathStrokeMiterLimit').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('PathStrokeMiterLimit').enabled(true))

    let strokeMiterLimit1: string = await path.getInspectorInfo()
    assertEqual(JSON.parse(strokeMiterLimit1).$attrs.strokeMiterLimit, '10.000000')

    await button.tap()
    let strokeMiterLimit2: string = await path.getInspectorInfo()
    assertEqual(JSON.parse(strokeMiterLimit2).$attrs.strokeMiterLimit, '15.000000')
  }, 0)
}