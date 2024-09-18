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

export default async function circleStrokeDashOffsetTest() {
  /*
 * Circle组件 StrokeDashOffset属性
 * 找到画面id为circleStrokeDashOffset的Circle组件
 * 找到画面文本为CircleStrokeDashOffset的Button组件
 * 获取circle的StrokeDashOffset属性与期待值'12.00vp'比对
 * 点击button，变更Circle的StrokeDashOffset属性值为'-21'
 * 获取circle的StrokeDashOffset属性与期待值'-21.00vp'比对
 */
  defineTest('circleStrokeDashOffsetTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("circleStrokeDashOffsetTestDemo running")
    let driver: Tester = Tester.create()
    let circle: Component = await driver.findComponent(Matcher.create().id('circleStrokeDashOffset').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('CircleStrokeDashOffset').enabled(true))

    let fillOpacity1: string = await circle.getInspectorInfo()
    assertEqual(JSON.parse(fillOpacity1).$attrs.strokeDashOffset, '12.00vp')

    await button.tap()
    let fillOpacity2: string = await circle.getInspectorInfo()
    assertEqual(JSON.parse(fillOpacity2).$attrs.strokeDashOffset, '-21.00vp')
  }, 0)
}