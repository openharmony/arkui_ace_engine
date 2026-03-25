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

import { DataShareExtensionAbility, ValuesBucket } from '@kit.ArkData';
import { relationalStore } from '@kit.ArkData';
import { Want } from '@kit.AbilityKit';
import { dataSharePredicates } from '@kit.ArkData';
import { BusinessError } from '@kit.BasicServicesKit';
import { fileIo } from '@kit.CoreFileKit';
import { common } from '@kit.AbilityKit';

const DATABASE_NAME = 'Sticker.db';
const TABLE_NAME = 'sticker';
const COLUMN_ID = 'id';
const COLUMN_CREATE_TIME = 'create_time';
const COLUMN_FILEPATH = 'filepath';

const STORE_CONFIG: relationalStore.StoreConfig = {
  name: DATABASE_NAME,
  securityLevel: relationalStore.SecurityLevel.S1
};

let appContext: common.ApplicationContext | null = null;

export default class DataShareExtAbility extends DataShareExtensionAbility {
  private rdbStore: relationalStore.RdbStore | null = null;
  private stickerDir: string = '';

  private async initDatabase() {
    try {
      this.rdbStore = await relationalStore.getRdbStore(this.context, STORE_CONFIG);
      const createTableSql = `CREATE TABLE IF NOT EXISTS ${TABLE_NAME} (
        ${COLUMN_ID} INTEGER PRIMARY KEY AUTOINCREMENT,
        ${COLUMN_CREATE_TIME} INTEGER NOT NULL,
        ${COLUMN_FILEPATH} TEXT NOT NULL
      )`;
      await this.rdbStore.executeSql(createTableSql);
      console.info('DataShareExtAbility: database initialized');

      appContext = this.context.getApplicationContext();
      this.stickerDir = appContext.filesDir + '/stickers/';
      await fileIo.mkdir(this.stickerDir);
    } catch (err) {
      console.error(`DataShareExtAbility: init failed: ${(err as BusinessError).message}`);
    }
  }

  onCreate(want: Want): void {
    console.info('DataShareExtAbility: onCreate');
    this.initDatabase();
  }

  private async copyStickerFile(srcPath: string): Promise<string> {
    const fileName = `${Date.now()}_${Math.random().toString(36).substring(2)}.png`;
    const destPath = `${this.stickerDir}${fileName}`;
    await fileIo.copyFile(srcPath, destPath);
    console.info(`File copied: ${srcPath} -> ${destPath}`);
    return destPath;
  }

  private async deleteStickerFile(filePath: string): Promise<void> {
    try {
      await fileIo.unlink(filePath);
      console.info(`File deleted: ${filePath}`);
    } catch (err) {
      console.error(`Failed to delete file: ${filePath}, error: ${(err as BusinessError).message}`);
    }
  }

  async query(uri: string, predicates: dataSharePredicates.DataSharePredicates, columns: Array<string>): Promise<relationalStore.ResultSet> {
    console.info(`DataShareExtAbility: query uri: ${uri}`);
    if (!this.rdbStore) {
      throw new Error('Database not ready');
    }
    let queryPredicates = new relationalStore.RdbPredicates(TABLE_NAME);
    const resultSet = await this.rdbStore.query(queryPredicates, columns);
    return resultSet;
  }

  async insert(uri: string, value: ValuesBucket): Promise<number> {
    console.info(`DataShareExtAbility: insert uri: ${uri}`);
    if (!this.rdbStore) {
      throw new Error('Database not ready');
    }

    const srcPath = value[COLUMN_FILEPATH] as string;
    if (!srcPath) {
      throw new Error('Missing filepath');
    }

    const destPath = await this.copyStickerFile(srcPath);

    // 使用字符串字面量作为属性名（符合 ArkTS 规范）
    const record: ValuesBucket = {
      'create_time': Date.now(),
      'filepath': destPath
    };

    const id = await this.rdbStore.insert(TABLE_NAME, record);
    console.info(`Insert success, id: ${id}`);
    return id;
  }

  async update(uri: string, predicates: dataSharePredicates.DataSharePredicates, value: ValuesBucket): Promise<number> {
    console.info(`DataShareExtAbility: update uri: ${uri}`);
    if (!this.rdbStore) {
      throw new Error('Database not ready');
    }

    let updatePredicates = new relationalStore.RdbPredicates(TABLE_NAME);
    const resultSet = await this.rdbStore.query(updatePredicates, ['id', COLUMN_FILEPATH]);
    let affectedRows = 0;
    let hasData = await resultSet.goToFirstRow();
    if (hasData) {
      do {
        const oldId = resultSet.getLong(resultSet.getColumnIndex(COLUMN_ID));
        const oldFilePath = resultSet.getString(resultSet.getColumnIndex(COLUMN_FILEPATH));
        if (value[COLUMN_FILEPATH]) {
          const newSrcPath = value[COLUMN_FILEPATH] as string;
          const newDestPath = await this.copyStickerFile(newSrcPath);
          await this.deleteStickerFile(oldFilePath);
          // 使用字符串字面量作为属性名
          const updateValue: ValuesBucket = { 'filepath': newDestPath };
          const where = new relationalStore.RdbPredicates(TABLE_NAME).equalTo(COLUMN_ID, oldId);
          const rows = await this.rdbStore.update(updateValue, where);
          affectedRows += rows;
        }
      } while (await resultSet.goToNextRow());
    }
    await resultSet.close();
    return affectedRows;
  }

  async delete(uri: string, predicates: dataSharePredicates.DataSharePredicates): Promise<number> {
    console.info(`DataShareExtAbility: delete uri: ${uri}`);
    if (!this.rdbStore) {
      throw new Error('Database not ready');
    }

    let queryPredicates = new relationalStore.RdbPredicates(TABLE_NAME);
    const resultSet = await this.rdbStore.query(queryPredicates, ['id', COLUMN_FILEPATH]);

    let hasData = await resultSet.goToFirstRow();
    if (hasData) {
      do {
        const filePath = resultSet.getString(resultSet.getColumnIndex(COLUMN_FILEPATH));
        await this.deleteStickerFile(filePath);
      } while (await resultSet.goToNextRow());
    }
    await resultSet.close();

    let deletePredicates = new relationalStore.RdbPredicates(TABLE_NAME);
    const rows = await this.rdbStore.delete(deletePredicates);
    console.info(`Deleted ${rows} records, corresponding files removed.`);
    return rows;
  }

  getType(uri: string): string {
    console.info(`DataShareExtAbility: getType uri: ${uri}`);
    return 'vnd.huawei.datashare.item';
  }

  batchInsert(uri: string, values: Array<ValuesBucket>): Promise<number> {
    console.info(`DataShareExtAbility: batchInsert uri: ${uri}`);
    return Promise.resolve(0);
  }

  normalizeUri(uri: string): string {
    return uri;
  }

  denormalizeUri(uri: string): string {
    return uri;
  }
}