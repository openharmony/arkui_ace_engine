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

import { assertEqual } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function displayPriorityTest() {
  /*
 * text组件 displayPriority属性
 * 找到画面id为textDisplayPriority1的text组件
 * 获取textDisplayPriority1的displayPriority属性与期待值1比对
 */
  defineTest('displayPriorityTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("displayPriorityTestDemo running")
    let driver: Tester = Tester.create()
    let text1: Component = await driver.findComponent(Matcher.create().id('textDisplayPriority1').enabled(true))
    let displayPriority1: string = await text1.getInspectorInfo()
    assertEqual(JSON.parse(displayPriority1).$attrs.displayPriority, 1)
  }, 0)
}