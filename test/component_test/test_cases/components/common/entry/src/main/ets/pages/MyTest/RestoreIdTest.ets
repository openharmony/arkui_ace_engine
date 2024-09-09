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

import { assertEqual, assertFalse } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function restoreIdTest() {
  /*
  * list组件 restoreId属性
  * 找到画面id为listRestoreId1的list组件
  * 获取listRestoreId1的restoreId属性与期待值1比对
  */
  defineTest('restoreIdTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("restoreIdTest running")
    let driver: Tester = Tester.create()
    let listRestoreId1: Component = await driver.findComponent(Matcher.create().id('listRestoreId1').enabled(true))
    let restoreId1: string = await listRestoreId1.getInspectorInfo()
    assertFalse(JSON.parse(restoreId1).$attrs.restoreId == undefined)
    assertEqual(JSON.parse(restoreId1).$attrs.restoreId.valve, 1)
  }, 0)
}