/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

@Entry
@Component
struct MenuStyle_normal {
  @Builder
  MyMenu(){
    Menu() {
      MenuItem({ content: '菜单选项1' })
      MenuItem({ content: '菜单选项2' })
      MenuItem({ content: '菜单选项3' })
      MenuItem({ content: '菜单选项4' })
      MenuItem({ content: '菜单选项5' })
      MenuItem({ content: '菜单选项6' })
      MenuItem({ content: '菜单选项7' })
      MenuItem({ content: '菜单选项8' })
      MenuItem({ content: '菜单选项9' })
      MenuItem({ content: '菜单选项10' })
      MenuItem({ content: '菜单选项11' })
      MenuItem({ content: '菜单选项12' })
      MenuItem({ content: '菜单选项13' })
      MenuItem({ content: '菜单选项14' })
      MenuItem({ content: '菜单选项15' })
      MenuItem({ content: '菜单选项16' })
      MenuItem({ content: '菜单选项17' })
      MenuItem({ content: '菜单选项18' })
      MenuItem({ content: '菜单选项19' })
      MenuItem({ content: '菜单选项20' })
    }
  }
  build() {
    Row() {
      Text('点击展示菜单')
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
    }
    .bindMenu(this.MyMenu)
  }
}