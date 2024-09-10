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

export default async function rectStrokeDashOffsetTest() {
  /*
 * Rect组件 strokeDashOffset属性
 * 找到画面id为rectStrokeDashOffset的Rect组件
 * 找到画面文本为RectStrokeDashOffset的Button组件
 * 获取rect的strokeDashOffset属性与期待值-5比对
 * 点击button,变更rect的strokeDashOffset属性值为'-10'
 * 获取rect的strokeDashOffset属性与期待值'-10'比对
 */
  defineTest('rectStrokeDashOffsetTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("rectStrokeDashOffsetTestDemo running")
    let driver: Tester = Tester.create()
    let rect: Component = await driver.findComponent(Matcher.create().id('rectStrokeDashOffset').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('RectStrokeDashOffset').enabled(true))

    let strokeDashOffset1: string = await rect.getInspectorInfo()
    assertEqual(JSON.parse(strokeDashOffset1).$attrs.strokeDashOffset, '-5.00vp')

    await button.tap()
    let strokeDashOffset2: string = await rect.getInspectorInfo()
    assertEqual(JSON.parse(strokeDashOffset2).$attrs.strokeDashOffset, '-10.00vp')
  }, 0)
}