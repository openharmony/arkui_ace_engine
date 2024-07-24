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
import { assertEqual } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function flexShrinkTest() {
  /*
  * 使用 Menu组件 FlexShrink属性
  * 找到画面id为menuFlexShrink1，menuFlexShrink2的menu组件
  * 获取menuFlexShrink1的FlexShrink属性与期待值0比对
  * 获取menuFlexShrink2的FlexShrink属性与期待值1比对
  */
  defineTest('flexShrinkTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('flexShrinkTestDemo running')
    let driver: Tester = Tester.create()
    let menuFlexShrink1: Component = await driver.findComponent(Matcher.create().id('menuFlexShrink1').enabled(true))
    let menuFlexShrink2: Component = await driver.findComponent(Matcher.create().id('menuFlexShrink2').enabled(true))
    let flexShrink1: string = await menuFlexShrink1.getInspectorInfo()
    assertEqual(JSON.parse(flexShrink1).$attrs.flexShrink, 0)

    let flexShrink2: string = await menuFlexShrink2.getInspectorInfo()
    assertEqual(JSON.parse(flexShrink2).$attrs.flexShrink, 1)
  }, 0)
}