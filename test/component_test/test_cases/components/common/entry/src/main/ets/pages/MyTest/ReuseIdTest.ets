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

export default async function reuseIdTest() {
  /*
  * 使用Checkbox组件 ReuseId属性
  * 找到画面id为checkboxReuseId的Checkbox组件
  * 获取checkboxReuseId的ReuseId属性与期待值checkboxReuseId比对
  */
  defineTest('reuseIdTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('reuseIdTestDemo running')
    let driver: Tester = Tester.create()
    let checkboxReuseId: Component = await driver.findComponent(Matcher.create().id('checkboxReuseId').enabled(true))
    let reuseId: string = await checkboxReuseId.getInspectorInfo()
    assertFalse(JSON.parse(reuseId).$attrs.reuseId == undefined)
    assertEqual(JSON.parse(reuseId).$attrs.reuseId, 'checkboxReuseId')
  }, 0)
}