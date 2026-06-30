/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

//[Start SpringLoading_start]
import { dragController } from '@kit.ArkUI';
import { unifiedDataChannel, uniformTypeDescriptor } from '@kit.ArkData';

//[StartExclude SpringLoading_start]
export const springLoadingRoutePrefix: string = 'springLoadingExample';

//[EndExclude SpringLoading_start]

@Entry
@ComponentV2
export struct SpringLoadingPage {
  context1 = this.getUIContext().getHostContext();
  @Local isShowSheet: boolean = false;
  // 请将$r('app.string.Select_Result')替换为实际资源文件，在本示例中该资源文件的value值为"搜索结果：\n  设备 1\n  设备 2\n  设备 3\n  ... ..."
  private searchResult: string = this.context1?.resourceManager.getStringSync($r('app.string.Select_Result').id)!;
  @Local isSearchDone: boolean = false;
  private reminderColor: Color = Color.Green;
  private normalColor: Color = Color.Blue;
  @Local buttonBackgroundColor: Color = this.normalColor;

  //[Start springLoading_builder]
  @Builder
  SheetBuilder() {
    Column() {
      // 输入框
      // 请将$r('app.string.Push_Here')替换为实际资源文件，在本示例中该资源文件的value值为"拖入此处"
      TextInput({ placeholder: $r('app.string.Push_Here') })
        .width('80%')
        .borderWidth(1)
        .borderColor(Color.Black)
        //[StartExclude springLoading_builder]
        .padding({ bottom: 5 })
        //[EndExclude springLoading_builder]
        .onChange((value: string) => {
          if (value.length == 0) {
            this.isSearchDone = false;
            return;
          }
          // 此处简化处理，直接显示固定搜索结果
          this.isSearchDone = true;
        })
      if (this.isSearchDone) {
        Text(this.searchResult).fontSize(20)
        //[StartExclude springLoading_builder]
          .textAlign(TextAlign.Start)
          .width('80%')
        //[EndExclude springLoading_builder]
      }
    }.width('100%').height('100%')
  }

  //[End springLoading_builder]
  // 检查拖拽数据类型是否包含所希望的plain-text
  checkDataType(dataSummary: unifiedDataChannel.Summary | undefined): boolean {
    let summary = dataSummary?.summary;
    if (summary == undefined) {
      return false;
    }

    let dataSummaryObjStr: string = JSON.stringify(summary);
    let dataSummaryArray: Array<Array<string>> = JSON.parse(dataSummaryObjStr);
    let isDataTypeMatched: boolean = false;
    dataSummaryArray.forEach((record: Array<string>) => {
      if (record[0] == 'general.plain-text') {
        isDataTypeMatched = true;
      }
    });
    return isDataTypeMatched;
  }

  // 处理BEGIN状态
  handleBeginState(context: SpringLoadingContext): boolean {
    // 检查用户所拖拽的数据类型是否自己能够处理的
    if (this.checkDataType(context?.dragInfos?.dataSummary)) {
      return true;
    }
    // 如果数据无法处理，直接终止Spring Loading
    context.abort();
    return false;
  }

  // Spring Loading处理入口
  //[Start springLoading_handleSpringLoading]
  handleSpringLoading(context: SpringLoadingContext) {
    // BEGIN 状态时检查拖拽数据类型
    if (context.state == dragController.DragSpringLoadingState.BEGIN) {
      //[StartExclude springLoading_handleSpringLoading]
      if (this.handleBeginState(context)) {
        // 我们已经在onDragEnter时刷新了提醒色，进入Spring Loading状态时，恢复UI，提醒用户继续保持不动
        this.buttonBackgroundColor = this.normalColor;
      }
      //[EndExclude springLoading_handleSpringLoading]
      //[StartExclude SpringLoading_start]
      // 进行必要判断，决定是否要终止触发
      //[EndExclude SpringLoading_start]
      return;
    }
    if (context.state == dragController.DragSpringLoadingState.UPDATE) {
      //[StartExclude springLoading_handleSpringLoading]
      // 奇数次UPDATE通知刷新提醒UI，偶数次复原UI
      if (context.currentNotifySequence % 2 != 0) {
        this.buttonBackgroundColor = this.reminderColor;
      } else {
        this.buttonBackgroundColor = this.normalColor;
      }
      //[EndExclude springLoading_handleSpringLoading]
      //[StartExclude SpringLoading_start]
      // 刷新提醒
      //[EndExclude SpringLoading_start]
      return;
    }
    // 处理Spring Loading结束，触发视图切换
    if (context.state == dragController.DragSpringLoadingState.END) {
      //[StartExclude springLoading_handleSpringLoading]
      this.isShowSheet = true;
      //[EndExclude springLoading_handleSpringLoading]
      //[StartExclude SpringLoading_start]
      // 视图激活或跳转
      //[EndExclude SpringLoading_start]
      return;
    }
    // 处理CANCEL状态，复原UI
    if (context.state == dragController.DragSpringLoadingState.CANCEL) {
      //[StartExclude springLoading_handleSpringLoading]
      this.buttonBackgroundColor = this.normalColor;
      //[EndExclude springLoading_handleSpringLoading]
      //[StartExclude SpringLoading_start]
      // 恢复状态与UI
      //[EndExclude SpringLoading_start]
      return;
    }
  }

  //[End springLoading_handleSpringLoading]
  //[Start springLoading_example]
  build() {
    Column() {
      //[StartExclude springLoading_example]
      //[StartExclude SpringLoading_start]
      NavDestination() {
        //[EndExclude SpringLoading_start]
        //[EndExclude springLoading_example]
        Column() {
          // 请将$r('app.string.DoubleClick_Text')替换为实际资源文件，在本示例中该资源文件的value值为"双击文字选择后拖出: \n     DeviceName"
          Text($r('app.string.DoubleClick_Text'))
            .fontSize(30)
            .copyOption(CopyOptions.InApp) // 开启copyOption之后，文本组件即可支持选择内容进行拖拽
        }.padding({ bottom: 30 })

        // 请将$r('app.string.Search_Device')替换为实际资源文件，在本示例中该资源文件的value值为"搜索设备"
        Button($r('app.string.Search_Device'))
          .width('80%')
          .height('80vp')
          .fontSize(30)
          .bindSheet($$this.isShowSheet, this.SheetBuilder(), {
            detents: [SheetSize.MEDIUM, SheetSize.LARGE, 600],
            preferType: SheetType.BOTTOM,
            // 请将$r('app.string.Search_Device')替换为实际资源文件，在本示例中该资源文件的value值为"搜索设备"
            title: { title: $r('app.string.Search_Device') },
          })
          //[StartExclude springLoading_example]
          .allowDrop([uniformTypeDescriptor.UniformDataType.PLAIN_TEXT])
          .backgroundColor(this.buttonBackgroundColor)
          //[Start springLoading_onDragEnter]
          .onDragEnter(() => {
            // 当用户拖拽进入按钮范围，即提醒用户，此处是可以处理数据的
            this.buttonBackgroundColor = this.reminderColor;
          })
          .onDragLeave(() => {
            // 当用户拖拽离开按钮范围，恢复UI
            this.buttonBackgroundColor = this.normalColor;
          })
          //[End springLoading_onDragEnter]
          //[Start springLoading_onDragSpringLoading_null]
          .onDragSpringLoading(null)
          //[End springLoading_onDragSpringLoading_null]
          .onDragSpringLoading((context: SpringLoadingContext) => {
            this.handleSpringLoading(context);
          })
        //[StartExclude SpringLoading_start]
      }
      .backgroundColor('#f1f3f5')
      .title('', {
        backgroundBlurStyle: BlurStyle.COMPONENT_THICK,
        barStyle: BarStyle.STACK
      })
      // 请将$r('app.string.Pages_Index_DropAnimation')替换为实际资源文件，在本示例中该资源文件的value值为"拖放动画事件/DropAnimation"
      .title($r('app.string.Pages_Index_DropAnimation'))

      //[EndExclude springLoading_example]
      //[EndExclude SpringLoading_start]
    }.width('100%').height('100%')
    .justifyContent(FlexAlign.Center)
  }

  //[End springLoading_example]
}

//[End SpringLoading_start]