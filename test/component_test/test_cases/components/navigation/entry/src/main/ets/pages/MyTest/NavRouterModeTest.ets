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

export default async function navRouterModeTest() {
  /*
 * NavRouter组件 Mode属性
 * 找到画面id为navRouterMode1，navRouterMode2的NavRouter组件
 * 找到画面文本为NavRouterMode11的Button组件
 * 获取navRouter1的mode属性与期待值PUSH_WITH_RECREATE比对
 * 获取navRouter2的mode属性与期待值NavRouteMode.PUSH比对
 * 点击button1，变更navRouterMode2的mode属性值为NavRouteMode.REPLACE
 * 获取navRouter2的mode属性与期待值NavRouteMode.REPLACE比对
 */
  defineTest('navRouterModeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('navRouterModeTestDemo running')
    let driver: Tester = Tester.create()
    let navRouter1: Component = await driver.findComponent(Matcher.create().id('navRouterMode1').enabled(true))
    let navRouter2: Component = await driver.findComponent(Matcher.create().id('navRouterMode2').enabled(true))

    let button1: Component = await driver.findComponent(Matcher.create().text('NavRouterMode1').enabled(true))

    let mode1: string = await navRouter1.getInspectorInfo()
    assertEqual(JSON.parse(mode1).$attrs.mode, NavRouteMode.PUSH_WITH_RECREATE)
    let mode2: string = await navRouter2.getInspectorInfo()
    assertEqual(JSON.parse(mode2).$attrs.mode, NavRouteMode.PUSH)

    await button1.tap()
    let mode3: string = await navRouter2.getInspectorInfo()
    assertEqual(JSON.parse(mode3).$attrs.mode, NavRouteMode.REPLACE)
  }, 0)
}