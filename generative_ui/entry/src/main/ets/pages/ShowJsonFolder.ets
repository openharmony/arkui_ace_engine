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

import { router } from '@kit.ArkUI';
import { common } from '@kit.AbilityKit';
import { util } from '@kit.ArkTS';

interface FileItem {
  name: string;
  path: string;
  type: 'file' | 'folder';
}

class FileItemDataSource implements IDataSource {
  private fileItems: FileItem[] = [];
  private listeners: DataChangeListener[] = [];

  public totalCount(): number {
    return this.fileItems.length;
  }

  public getData(index: number): FileItem {
    return this.fileItems[index];
  }

  public registerDataChangeListener(listener: DataChangeListener): void {
    if (this.listeners.indexOf(listener) < 0) {
      this.listeners.push(listener);
    }
  }

  public unregisterDataChangeListener(listener: DataChangeListener): void {
    const index = this.listeners.indexOf(listener);
    if (index >= 0) {
      this.listeners.splice(index, 1);
    }
  }

  public addData(data: FileItem[]): void {
    this.fileItems = data;
    this.notifyDataReload();
  }

  private notifyDataReload(): void {
    this.listeners.forEach(listener => {
      listener.onDataReloaded();
    });
  }
}

@Entry
@Component
struct ShowJson {
  @State currentPath: string = '';
  private dataSource: FileItemDataSource = new FileItemDataSource();

  private context: common.Context = this.getUIContext().getHostContext() as common.Context;

  aboutToAppear(): void {
    this.loadFiles('');
  }

  private async loadFiles(relativePath: string): Promise<void> {
    this.currentPath = relativePath;
    const items = await this.getFileList(relativePath);
    this.dataSource.addData(items);
  }

  private async getFileList(relativePath: string): Promise<FileItem[]> {
    const items: FileItem[] = [];
    try {
      const files = await this.context.resourceManager.getRawFileList(relativePath);
      
      const folders = new Set<string>();
      const jsonFiles: FileItem[] = [];

      files.forEach(file => {
        if (file.endsWith('.json')) {
          const path = relativePath ? relativePath + '/' + file : file;
          jsonFiles.push({
            name: file,
            path: path,
            type: 'file'
          });
        } else {
          folders.add(file);
        }
      });

      const folderArray = Array.from(folders).sort();
      folderArray.forEach(folder => {
        items.push({
          name: folder,
          path: relativePath ? relativePath + '/' + folder : folder,
          type: 'folder'
        });
      });

      jsonFiles.sort((a, b) => a.name.localeCompare(b.name));
      items.push(...jsonFiles);

    } catch (error) {
      console.error('获取文件列表失败:', error);
    }

    return items;
  }

  private handleItemClick(item: FileItem): void {
    if (item.type === 'folder') {
      this.loadFiles(item.path);
    } else {
      router.pushUrl({
        url: 'pages/JSONDetail',
        params: {
          fileName: item.path
        }
      });
    }
  }

  private handleBack(): void {
    if (this.currentPath) {
      const parts = this.currentPath.split('/');
      parts.pop();
      this.loadFiles(parts.join('/'));
    } else {
      router.back();
    }
  }

  private handleBreadcrumbClick(index: number): void {
    if (index === 0) {
      this.loadFiles('');
    } else {
      const parts = this.currentPath.split('/').slice(0, index);
      this.loadFiles(parts.join('/'));
    }
  }

  build() {
    Column() {
      Row() {
        Button('← 返回')
          .onClick(() => {
            this.handleBack();
          })
          .margin({ left: 10, right: 10 })

        Text(this.currentPath || '根目录')
          .fontSize(16)
          .layoutWeight(1)
          .maxLines(1)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
      }
      .width('100%')
      .height(50)
      .backgroundColor('#f1f3f5')
      .padding(10)

      List({ space: 10 }) {
        LazyForEach(this.dataSource, (item: FileItem, index: number) => {
          ListItem() {
            Row() {
              if (item.type === 'folder') {
                Text('📁')
                  .fontSize(24)
                  .margin({ right: 10 })
              } else {
                Text('📄')
                  .fontSize(24)
                  .margin({ right: 10 })
              }

              Text(item.name)
                .fontSize(16)
                .layoutWeight(1)

              if (item.type === 'folder') {
                Text('>')
                  .fontSize(16)
                  .fontColor(Color.Gray)
              }
            }
            .width('100%')
            .padding(15)
            .backgroundColor(Color.White)
            .borderRadius(8)
            .onClick(() => {
              this.handleItemClick(item);
            })
          }
        }, (item: FileItem, index: number) => {
          return item.path + index;
        })
      }
      .layoutWeight(1)
      .width('100%')
      .padding(10)
    }
    .height('100%')
    .width('100%')
    .backgroundColor('#f5f5f5')
  }
}
