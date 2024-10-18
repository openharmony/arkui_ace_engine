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

export default async function shapeStrokeDashOffsetTest() {
  /*
   * Shape组件 strokeDashOffset属性
   * 找到画面id为shapeStrokeDashOffset1,shapeStrokeDashOffset2的Shape组件
   * 获取shape1的strokeDashOffset属性与期待值10比对
   * 获取shape2的strokeDashOffset属性与期待值'20'比对
   */
  defineTest('shapeStrokeDashOffsetTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("shapeStrokeDashOffsetTestDemo running")
    let driver: Tester = Tester.create()
    let shape1: Component = await driver.findComponent(Matcher.create().id('shapeStrokeDashOffset1').enabled(true))
    let shape2: Component = await driver.findComponent(Matcher.create().id('shapeStrokeDashOffset2').enabled(true))

    let strokeDashOffset1: string = await shape1.getInspectorInfo()
    assertEqual(JSON.parse(strokeDashOffset1).$attrs.strokeDashOffset, '10.00vp')

    let strokeDashOffset2: string = await shape2.getInspectorInfo()
    assertEqual(JSON.parse(strokeDashOffset2).$attrs.strokeDashOffset, '20.00vp')
  }, 0)
}