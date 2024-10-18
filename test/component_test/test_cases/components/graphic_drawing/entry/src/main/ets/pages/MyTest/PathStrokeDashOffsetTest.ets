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

export default async function pathStrokeDashOffsetTest() {
  /*
   * Path组件 strokeDashOffset属性
   * 找到画面id为pathStrokeDashOffset的Path组件
   * 找到画面文本为PathStrokeDashOffset的Button组件
   * 获取path的strokeDashOffset属性与期待值-5比对
   * 点击button，变更path的strokeDashOffset属性值为10
   * 获取path的strokeDashOffset属性与期待值10比对
   */
  defineTest('pathStrokeDashOffsetTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("pathStrokeDashOffsetTestDemo running")
    let driver: Tester = Tester.create()
    let path: Component = await driver.findComponent(Matcher.create().id('pathStrokeDashOffset').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('PathStrokeDashOffset').enabled(true))

    let strokeDashOffset1: string = await path.getInspectorInfo()
    assertEqual(JSON.parse(strokeDashOffset1).$attrs.strokeDashOffset, '-5.00vp')

    await button.tap()
    let strokeDashOffset2: string = await path.getInspectorInfo()
    assertEqual(JSON.parse(strokeDashOffset2).$attrs.strokeDashOffset, '10.00vp')
  }, 0)
}