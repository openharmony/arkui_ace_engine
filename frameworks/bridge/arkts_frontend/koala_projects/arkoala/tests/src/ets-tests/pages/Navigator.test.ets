/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
import router from '@ohos.router'

@Entry
@Component
struct NavigatorTest {
  @State textParam: object = {name: 'news'}
  //@State text: any = router.getParams()
  

  build() {
    Navigator() {
      Text("Navigator test 1")
    }
    .active(false)
    .type(NavigationType.Push)
    .target("/target/attribute/page 1")
    .params({text: this.textParam})

    Navigator({target: "/target/param/page2", type: NavigationType.Back}) {
      Text("Navigator test 2")
    }
    .active(false)
    .type(NavigationType.Push)
    .target("/target/attribute/page")
  }
}