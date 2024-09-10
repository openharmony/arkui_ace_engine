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

export default async function geometryTransitionTest() {
  /*
  * image组件 geometryTransition属性
  * 找到画面id为imageGeometryTransition1的image组件
  * 获取imageGeometryTransition1的geometryTransition属性与期待值"picture"比对
  */
  defineTest('geometryTransitionTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("geometryTransitionTestDemo running")
    let driver: Tester = Tester.create()
    let imageGeometryTransition1: Component =
      await driver.findComponent(Matcher.create().id('imageGeometryTransition1').enabled(true))
    let geometryTransition1: string = await imageGeometryTransition1.getInspectorInfo()
    assertFalse(JSON.parse(geometryTransition1).$attrs.geometryTransition == undefined)
    assertEqual(JSON.parse(geometryTransition1).$attrs.geometryTransition, "picture")
  }, 0)
}