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

import { BusinessError } from '@kit.BasicServicesKit';
import { fileIo } from '@kit.CoreFileKit';
import { image } from '@kit.ImageKit';
import { photoAccessHelper } from '@kit.MediaLibraryKit';
import { Logger } from '../common/Logger';
import { PopupUtils } from '../common/PopupUtils';
import { common } from '@kit.AbilityKit';

const TAG: string = '[SnapshotPreview]';

/**
 * Long screenshot preview pop-up component
 */
@Component
export struct SnapshotPreview {
  @StorageLink('screenWidth') @Watch('onDisplayWidthChange') screenWidth: number = 0;
  @StorageLink('screenHeight') screenHeight: number = 0;
  // The size of the preview window after taking a screenshot
  @State snapPopupWidth: number = 100;
  @State snapPopupHeight: number = 200;
  // The position of the preview window after taking a screenshot
  @Link snapPopupPosition: Position;
  // Whether to display the screenshot preview pop-up window
  @Link isShowPreview: boolean;
  // Whether to display the screenshot preview pop-up window in large mode
  @Link isLargePreview: boolean;
  // The image generated after taking a screenshot
  @Link mergedImage: PixelMap | undefined;
  private context = this.getUIContext().getHostContext() as common.UIAbilityContext;
  // Saves the position information before sliding
  private xPositionBefore: number = 0;
  // Pan to the left gesture
  private panOption: PanGestureOptions = new PanGestureOptions({
    direction: PanDirection.Left,
    distance: 5
  });

  onDisplayWidthChange(): void {
    if (this.isLargePreview) {
      this.snapPopupHeight = 580;
      this.snapPopupWidth = this.screenWidth - 32;
      this.snapPopupPosition =
        PopupUtils.calcPopupCenter(this.screenWidth, this.screenHeight, this.snapPopupWidth, this.snapPopupHeight);
    }
  }

  /**
   * Close the screenshot pop-up window and restore the status.
   */
  // [Start close_and_clean_snapshot]
  closeSnapPopup(): void {
    // 关闭弹窗
    this.isShowPreview = false;
    // 释放位图对象
    this.mergedImage = undefined;
    // 重置相关参数
    this.snapPopupWidth = 100;
    this.snapPopupHeight = 200;
    this.snapPopupPosition =
      PopupUtils.calcPopupCenter(this.screenWidth, this.screenHeight, this.snapPopupWidth, this.snapPopupHeight);
    this.isLargePreview = false;
  }
  // [End close_and_clean_snapshot]

  // [Start save_snapshot1]
  async saveSnapshot(result: SaveButtonOnClickResult): Promise<void> {
    try {
      if (result === SaveButtonOnClickResult.SUCCESS) {
        const helper = photoAccessHelper.getPhotoAccessHelper(this.context);
        const uri = await helper.createAsset(photoAccessHelper.PhotoType.IMAGE, 'png');
        const file = await fileIo.open(uri, fileIo.OpenMode.READ_WRITE | fileIo.OpenMode.CREATE);
        const imagePackerApi: image.ImagePacker = image.createImagePacker();
        const packOpts: image.PackingOption = {
          format: 'image/png',
          quality: 100,
        };
        imagePackerApi.packToData(this.mergedImage, packOpts).then((data) => {
          fileIo.writeSync(file.fd, data);
          fileIo.closeSync(file.fd);
          Logger.info(TAG, `Succeeded in packToFile`);
          this.getUIContext().getPromptAction().showToast({
            // 请将$r('app.string.save_album_success')替换为实际资源文件，在本示例中该资源文件的value值为"Saved to album"
            message: $r('app.string.save_album_success'),
            duration: 1800
          })
        }).catch((error: BusinessError) => {
          Logger.error(TAG, `Failed to packToFile. Error code is ${error.code}, message is ${error.message}`);
        });
      }
      // [StartExclude save_snapshot1]
      this.closeSnapPopup();
      // [EndExclude save_snapshot1]
    } catch (err) {
      let error = err as BusinessError;
      Logger.error(TAG, `saveSnapshot err, errCode: ${error.code}, error message: ${error.message}`);
    }
  }
  // [End save_snapshot1]

  @Builder
  previewWindow() {
    Column() {
      this.previewSnapshot();
      if (this.isLargePreview) {
        this.buttonBar();
      }
    }
    .backgroundColor(Color.White)
    .width(this.snapPopupWidth)
    .height(this.snapPopupHeight)
    .position(this.snapPopupPosition)
    .borderRadius(this.isLargePreview ? 32 : 0)
    .animation({
      duration: 500,
      curve: Curve.Linear
    })
    .gesture(
      PanGesture(this.panOption)
        .onActionStart(() => {
          this.xPositionBefore = this.snapPopupPosition.x as number;
        })
        .onActionUpdate((event) => {
          // The left slide pop-up window closes, but allows a small part to be swiped to the right to create an
          // elastic effect and improve the operating feel
          if (event.offsetX < 30) {
            this.snapPopupPosition.x = this.xPositionBefore + event.offsetX;
          }
        })
        .onActionEnd((event) => {
          // Swipe left will trigger a pop-up window when it exceeds a certain threshold, improving user experience
          if (event.offsetX < -30) {
            this.getUIContext().animateTo({
              duration: 500,
              curve: Curve.Ease,
              onFinish: () => {
                this.isShowPreview = false;
              }
            }, () => {
              this.snapPopupPosition.x = -150;
            })
          } else {
            this.snapPopupPosition = PopupUtils.calcPopupBottomLeft(this.screenWidth, this.screenHeight)
          }
        })
    )
    .onGestureJudgeBegin((gestureInfo: GestureInfo) => {
      // Mask the panning event when previewing the image
      if (gestureInfo.type == GestureControl.GestureType.PAN_GESTURE && this.isLargePreview) {
        return GestureJudgeResult.REJECT;
      }
      return GestureJudgeResult.CONTINUE;
    })
  }

  @Builder
  previewSnapshot() {
    Scroll() {
      Column() {
        Image(this.mergedImage)
          .objectFit(ImageFit.Fill)
          .width('100%')
      }
      .borderWidth(5)
      // $r('sys.color.comp_background_secondary')需要替换为开发者所需的资源文件
      .borderColor($r('sys.color.comp_background_secondary'))
    }
    .borderRadius(this.isLargePreview ? 32 : 0)
    .width('100%')
    .layoutWeight(1)
    .scrollBar(BarState.Off)
    .backgroundColor(Color.White)
    .padding({
      top: this.isLargePreview ? 24 : 0,
      left: this.isLargePreview ? 24 : 0,
      right: this.isLargePreview ? 24 : 0
    })
    .onClick(() => {
      // Click to enlarge the preview window and display it flat and centered
      if (!this.isLargePreview) {
        this.getUIContext().animateTo({
          duration: 500,
          curve: Curve.Ease,
          onFinish: () => {
            this.isLargePreview = true;
          }
        }, () => {
          this.snapPopupWidth = this.screenWidth - 32;
          this.snapPopupHeight = 580;
          this.snapPopupPosition =
            PopupUtils.calcPopupCenter(this.screenWidth, this.screenHeight, this.snapPopupWidth,
              this.snapPopupHeight)
        })
      }
    })
  }

  @Builder
  buttonBar() {
    Row({ space: 16 }) {
      // 请将$r('app.string.button_cancel')替换为实际资源文件，在本示例中该资源文件的value值为"Cancel"
      Button($r('app.string.button_cancel'))
        .width('calc(50% - 24vp)')
        .height(40)
        .fontSize(16)
        .backgroundColor(Color.White)
        // $r('sys.color.font_emphasize')需要替换为开发者所需的资源文件
        .fontColor($r('sys.color.font_emphasize'))
        .onClick(() => {
          this.closeSnapPopup();
        })
      // [Start save_button]
      // src/main/ets/view/SnapshotPreview.ets
      SaveButton({
        icon: SaveIconStyle.FULL_FILLED,
        text: SaveDescription.SAVE_IMAGE,
        buttonType: ButtonType.Capsule
      })
        // [StartExclude save_button]
        .backgroundColor(Color.White)
        // $r('sys.color.font_emphasize')需要替换为开发者所需的资源文件
        .fontColor($r('sys.color.font_emphasize'))
        .iconColor($r('sys.color.font_emphasize'))
        .width('calc(50% - 24vp)')
        .height(40)
        .fontSize(16)
        // [EndExclude save_button]
        .onClick((event, result) => {
          this.saveSnapshot(result);
        })
      // [End save_button]
    }
    .justifyContent(FlexAlign.SpaceEvenly)
    .width('100%')
    .alignItems(VerticalAlign.Center)
    .padding({
      top: 8,
      bottom: 24
    })
  }

  build() {
    Column() {
      // The preview pane is displayed after the build
      if (this.mergedImage) {
        this.previewWindow();
      } else {
        // A pop-up window in the screenshot prompts
        // 请将$r('app.string.screen_is_taking')替换为实际资源文件，在本示例中该资源文件的value值为"Screenshot is taking, please wait..."
        Text($r('app.string.screen_is_taking'))
          .backgroundColor(Color.White)
          .textAlign(TextAlign.Center)
          .borderRadius(12)
          .padding(12)
          .width(120)
          .height(80)
      }
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
    // $r('sys.color.ohos_id_color_mask_thin')需要替换为开发者所需的资源文件
    .backgroundColor($r('sys.color.ohos_id_color_mask_thin'))
  }
}