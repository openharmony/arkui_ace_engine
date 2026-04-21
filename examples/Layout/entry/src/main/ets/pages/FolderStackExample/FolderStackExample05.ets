/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

class MyFolderStackModifier implements AttributeModifier<FolderStackAttribute> {
  applyNormalAttribute(instance: FolderStackAttribute): void {
    // folderStack回调 当折叠状态改变时回调
    instance.onFolderStateChange((msg) => {
      if (msg.foldStatus === FoldStatus.FOLD_STATUS_EXPANDED) {
        console.info("The device is currently in the expanded state")
      } else if (msg.foldStatus === FoldStatus.FOLD_STATUS_HALF_FOLDED) {
        console.info("The device is currently in the half folded state")
      } else if (msg.foldStatus === FoldStatus.FOLD_STATUS_FOLDED) {
        console.info("The device is currently in the folded state")
      } else {
        // .............
      }
    })
    // hoverStatusChange回调 当悬停状态改变时回调
    instance.onHoverStatusChange((msg) => {
      console.info('this foldStatus:' + msg.foldStatus);
      console.info('this isHoverMode:' + msg.isHoverMode);
      console.info('this appRotation:' + msg.appRotation);
      console.info('this windowStatusType:' + msg.windowStatusType);
    })
  }
}

@Entry
@Component
struct FolderStackExample5 {
  @State modifier: MyFolderStackModifier = new MyFolderStackModifier()

  build() {
    Column() {
      Text('Modifier onFolderStateChange&onHoverStatusChange')
      // upperItems将所需要的悬停到上半屏的id放入upperItems传入，其余组件会堆叠在下半屏区域
      FolderStack({ upperItems: ["upperitemsId5"] }) {
        // 此Column会自动上移到上半屏
        Column() {
          Text("video zone").height("100%").width("100%").textAlign(TextAlign.Center).fontSize(25)
        }.backgroundColor('rgb(0, 74, 175)').width("100%").height("100%").id("upperitemsId5")

        // 下列两个Column堆叠在下半屏区域
        Column() {
          Text("video title")
            .width("100%")
            .height(50)
            .textAlign(TextAlign.Center)
            .backgroundColor('rgb(213, 213, 213)')
            .fontSize(25)
        }.width("100%").height("100%").justifyContent(FlexAlign.Start)

        Column() {
          Text("video bar ")
            .width("100%")
            .height(50)
            .textAlign(TextAlign.Center)
            .backgroundColor('rgb(213, 213, 213)')
            .fontSize(25)
        }.width("100%").height("100%").justifyContent(FlexAlign.End)
      }
      .backgroundColor('rgb(39, 135, 217)')
      // 是否启动动效
      .enableAnimation(true)
      // 是否自动旋转
      .autoHalfFold(true)
      .attributeModifier(this.modifier)
      // folderStack如果不撑满页面全屏，作为普通Stack使用
      .alignContent(Alignment.Bottom)
      .height("100%")
      .width("100%")
      .backgroundColor('rgb(39, 135, 217)')
    }
    .height("100%")
    .width("100%")
    .borderWidth(1)
    .borderColor('rgb(213, 213, 213)')
    .backgroundColor('rgb(0, 74, 175)')
    .expandSafeArea([SafeAreaType.SYSTEM], [SafeAreaEdge.BOTTOM])
  }
}