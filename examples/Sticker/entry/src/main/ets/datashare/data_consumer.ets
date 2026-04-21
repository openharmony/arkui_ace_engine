/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 import { dataShare, ValuesBucket, DataShareResultSet } from '@kit.ArkData';
import { dataSharePredicates } from '@kit.ArkData';
import { BusinessError } from '@kit.BasicServicesKit';
import { common } from '@kit.AbilityKit';
import { fileIo } from '@kit.CoreFileKit';
import { photoAccessHelper } from '@kit.MediaLibraryKit';

interface StickerInfo {
  id: number;
  createTime: number;
  filepath: string;
}

@Entry
@Component
struct Index {
  @State message: string = '贴纸管理示例';
  @State stickers: StickerInfo[] = [];
  @State selectedSticker: StickerInfo | null = null;
  @State statusMessage: string = '';

  // DataShare URI（根据提供方的包名和Extension名称调整）
  private readonly DATA_SHARE_URI: string = 'datashare:///com.acts.example.datashare.DataShareExtAbility';

  async aboutToAppear(): Promise<void> {
    await this.queryAllStickers();
  }

  /**
   * 查询所有贴纸
   */
  async queryAllStickers(): Promise<void> {
    const context = getContext(this) as common.UIAbilityContext;
    let helper: dataShare.DataShareHelper | null = null;

    try {
      helper = await dataShare.createDataShareHelper(context, this.DATA_SHARE_URI);
      
      let predicates = new dataSharePredicates.DataSharePredicates();
      let columns = ['id', 'create_time', 'filepath'];

      let resultSet: DataShareResultSet = await helper.query(this.DATA_SHARE_URI, predicates, columns);
      
      const stickerList: StickerInfo[] = [];
      let hasData = await resultSet.goToFirstRow();
      if (hasData) {
        do {
          const id = resultSet.getLong(resultSet.getColumnIndex('id'));
          const createTime = resultSet.getLong(resultSet.getColumnIndex('create_time'));
          const filepath = resultSet.getString(resultSet.getColumnIndex('filepath'));
          stickerList.push({ id, createTime, filepath });
        } while (await resultSet.goToNextRow());
      }
      
      await resultSet.close();
      this.stickers = stickerList;
      this.statusMessage = `查询成功，共 ${stickerList.length} 张贴纸`;
      console.info(`Query success: ${JSON.stringify(stickerList)}`);
    } catch (err) {
      const error = err as BusinessError;
      this.statusMessage = `查询失败: ${error.message}`;
      console.error(`queryAllStickers error: ${error.message}`);
    } finally {
      if (helper) {
        await helper.close();
      }
    }
  }

  /**
   * 插入贴纸（从图库选择图片）
   */
  async insertSticker(): Promise<void> {
    const context = getContext(this) as common.UIAbilityContext;
    let helper: dataShare.DataShareHelper | null = null;

    try {
      // 1. 从图库选择图片（使用 photoAccessHelper）
      const photoPicker = photoAccessHelper.createPhotoPicker(context);
      const pickResult = await photoPicker.select({
        type: photoAccessHelper.PhotoPickerType.IMAGE,
        maxSelectCount: 1
      });
      
      if (pickResult.photoUris.length === 0) {
        this.statusMessage = '未选择图片';
        return;
      }
      
      const sourceUri = pickResult.photoUris[0];
      this.statusMessage = `已选择图片: ${sourceUri}`;

      // 2. 获取图片的真实路径（用于复制）
      // 注意：需要将 URI 转换为可访问的文件路径
      const file = await fileIo.open(sourceUri, fileIo.OpenMode.READ_ONLY);
      const destPath = `${context.filesDir}/temp_${Date.now()}.jpg`;
      await fileIo.copyFile(file.fd, destPath);
      await fileIo.close(file.fd);

      // 3. 调用 DataShare 插入
      helper = await dataShare.createDataShareHelper(context, this.DATA_SHARE_URI);
      
      let value: ValuesBucket = {
        'filepath': destPath  // 传递临时文件路径
      };
      
      const id = await helper.insert(this.DATA_SHARE_URI, value);
      this.statusMessage = `插入成功，ID: ${id}`;
      console.info(`Insert success, id: ${id}`);
      
      // 4. 删除临时文件
      await fileIo.unlink(destPath);
      
      // 5. 刷新列表
      await this.queryAllStickers();
    } catch (err) {
      const error = err as BusinessError;
      this.statusMessage = `插入失败: ${error.message}`;
      console.error(`insertSticker error: ${error.message}`);
    } finally {
      if (helper) {
        await helper.close();
      }
    }
  }

  /**
   * 更新贴纸（替换图片）
   * @param sticker 要更新的贴纸
   */
  async updateSticker(sticker: StickerInfo): Promise<void> {
    const context = getContext(this) as common.UIAbilityContext;
    let helper: dataShare.DataShareHelper | null = null;

    try {
      // 1. 从图库选择新图片
      const photoPicker = photoAccessHelper.createPhotoPicker(context);
      const pickResult = await photoPicker.select({
        type: photoAccessHelper.PhotoPickerType.IMAGE,
        maxSelectCount: 1
      });
      
      if (pickResult.photoUris.length === 0) {
        this.statusMessage = '未选择图片';
        return;
      }
      
      const sourceUri = pickResult.photoUris[0];
      
      // 2. 获取图片的真实路径
      const file = await fileIo.open(sourceUri, fileIo.OpenMode.READ_ONLY);
      const destPath = `${context.filesDir}/temp_${Date.now()}.jpg`;
      await fileIo.copyFile(file.fd, destPath);
      await fileIo.close(file.fd);

      // 3. 调用 DataShare 更新
      helper = await dataShare.createDataShareHelper(context, this.DATA_SHARE_URI);
      
      let predicates = new dataSharePredicates.DataSharePredicates();
      predicates.equalTo('id', sticker.id);
      
      let value: ValuesBucket = {
        'filepath': destPath  // 传递新图片的临时路径
      };
      
      const rows = await helper.update(this.DATA_SHARE_URI, predicates, value);
      this.statusMessage = `更新成功，影响行数: ${rows}`;
      console.info(`Update success, rows: ${rows}`);
      
      // 4. 删除临时文件
      await fileIo.unlink(destPath);
      
      // 5. 刷新列表
      await this.queryAllStickers();
    } catch (err) {
      const error = err as BusinessError;
      this.statusMessage = `更新失败: ${error.message}`;
      console.error(`updateSticker error: ${error.message}`);
    } finally {
      if (helper) {
        await helper.close();
      }
    }
  }

  /**
   * 删除贴纸
   * @param sticker 要删除的贴纸
   */
  async deleteSticker(sticker: StickerInfo): Promise<void> {
    const context = getContext(this) as common.UIAbilityContext;
    let helper: dataShare.DataShareHelper | null = null;

    try {
      helper = await dataShare.createDataShareHelper(context, this.DATA_SHARE_URI);
      
      let predicates = new dataSharePredicates.DataSharePredicates();
      predicates.equalTo('id', sticker.id);
      
      const rows = await helper.delete(this.DATA_SHARE_URI, predicates);
      this.statusMessage = `删除成功，影响行数: ${rows}`;
      console.info(`Delete success, rows: ${rows}`);
      
      // 刷新列表
      await this.queryAllStickers();
    } catch (err) {
      const error = err as BusinessError;
      this.statusMessage = `删除失败: ${error.message}`;
      console.error(`deleteSticker error: ${error.message}`);
    } finally {
      if (helper) {
        await helper.close();
      }
    }
  }

  /**
   * 格式化时间戳
   */
  private formatTime(timestamp: number): string {
    const date = new Date(timestamp);
    return `${date.getFullYear()}-${date.getMonth() + 1}-${date.getDate()} ${date.getHours()}:${date.getMinutes()}:${date.getSeconds()}`;
  }

  build() {
    Column() {
      // 标题栏
      Row() {
        Text(this.message)
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .margin({ left: 16 })
        
        Blank()
        
        Button('添加贴纸')
          .fontSize(14)
          .padding({ left: 12, right: 12 })
          .onClick(() => this.insertSticker())
          .margin({ right: 16 })
      }
      .width('100%')
      .height(56)
      .backgroundColor('#F5F5F5')

      // 状态信息
      Text(this.statusMessage)
        .fontSize(12)
        .fontColor('#666666')
        .padding(8)
        .width('100%')

      // 贴纸列表
      List() {
        ForEach(this.stickers, (sticker: StickerInfo, index: number) => {
          ListItem() {
            Row() {
              // 贴纸预览（显示路径）
              Column() {
                Text(`ID: ${sticker.id}`)
                  .fontSize(14)
                  .fontWeight(FontWeight.Medium)
                Text(`创建时间: ${this.formatTime(sticker.createTime)}`)
                  .fontSize(12)
                  .fontColor('#666666')
                Text(`路径: ${sticker.filepath}`)
                  .fontSize(10)
                  .fontColor('#999999')
                  .width('100%')
                  .maxLines(1)
                  .textOverflow({ overflow: TextOverflow.Ellipsis })
              }
              .alignItems(HorizontalAlign.Start)
              .layoutWeight(1)
              
              Row() {
                Button('替换')
                  .fontSize(12)
                  .onClick(() => this.updateSticker(sticker))
                Button('删除')
                  .fontSize(12)
                  .backgroundColor('#FF4444')
                  .onClick(() => this.deleteSticker(sticker))
              }
              .margin({ left: 8 })
            }
            .width('100%')
            .padding(12)
            .backgroundColor(index % 2 === 0 ? '#FFFFFF' : '#FAFAFA')
          }
        }, (sticker: StickerInfo) => sticker.id.toString())
      }
      .layoutWeight(1)
      .width('100%')
      .margin({ top: 8 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F0F0F0')
  }
}