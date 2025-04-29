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

import { assertEqual, assertFalse } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

/*
 * row组件 gridOffset属性
 * 找到id为 rowGridOffset 的row组件 命名为row1
 * 获取row1的属性gridOffset 与期望值 1 比对
 * */
export default async function gridOffsetTest() {
  defineTest('gridOffsetTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gridOffsetTestDemo running')
    let driver: Tester = Tester.create()
    let row1: Component = await driver.findComponent(Matcher.create().id('rowGridOffset').enabled(true))
    let gridOffset1: string = await row1.getInspectorInfo()
    assertEqual(JSON.parse(gridOffset1).$attrs.gridOffset, 1)
  }, 0)
}