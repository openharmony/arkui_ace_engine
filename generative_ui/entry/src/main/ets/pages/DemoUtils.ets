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

import { common } from '@kit.AbilityKit';
import { util } from '@kit.ArkTS';

/**
 * Demo页面工具类
 */
export class DemoUtils {
  /**
   * 格式化时间戳为相对时间
   */
  static formatTimestamp(timestamp: string): string {
    try {
      let normalizedTimestamp = timestamp;

      if (!isNaN(Number(timestamp))) {
        normalizedTimestamp = new Date(Number(timestamp)).toISOString();
      } else if (timestamp.includes('T') && !timestamp.includes(':')) {
        normalizedTimestamp = timestamp.replace(/T(\d{2})-(\d{2})-(\d{2})/, 'T$1:$2:$3');
        normalizedTimestamp = normalizedTimestamp.replace(/(\+\d{2})-(\d{2})/, '$1:$2');
      }

      const date = new Date(normalizedTimestamp);
      if (isNaN(date.getTime())) {
        console.warn('无效的时间戳:', timestamp);
        return timestamp;
      }

      const now = new Date();
      const diff = now.getTime() - date.getTime();
      const hours = Math.floor(diff / (1000 * 60 * 60));

      if (hours < 1) {
        const minutes = Math.floor(diff / (1000 * 60));
        if (minutes < 1) {
          return '刚刚';
        }
        return `${minutes}分钟前`;
      } else if (hours < 24) {
        return `${hours}小时前`;
      } else if (hours < 24 * 7) {
        const days = Math.floor(hours / 24);
        return `${days}天前`;
      } else {
        const year = date.getFullYear();
        const month = String(date.getMonth() + 1).padStart(2, '0');
        const day = String(date.getDate()).padStart(2, '0');
        return `${year}-${month}-${day}`;
      }
    } catch (error) {
      console.error('格式化时间戳失败:', error);
      return timestamp;
    }
  }



  /**
   * 加载Mock数据
   */
  static loadMockData(context: common.Context, fileName: string): string[] {
    try {
      const content = context.resourceManager.getRawFileContentSync(fileName);
      const textDecoderOptions: util.TextDecoderOptions = {
        fatal: false,
        ignoreBOM: true
      };
      const decodeToStringOptions: util.DecodeToStringOptions = {
        stream: false
      };
      const textDecoder = util.TextDecoder.create('utf-8', textDecoderOptions);
      const strContent = textDecoder.decodeToString(content, decodeToStringOptions);
      return DemoUtils.parseStringArray(strContent);
    } catch (error) {
      console.error('加载mock_data.json时出错:', error);
      return [];
    }
  }

  /**
   * 解析A2UI v0.9消息
   */
  static parseStringArray(line: string): string[] {
    try {
      const obj: Record<string, Object>[] | string[] = JSON.parse(line) as Record<string, Object>[] | string[];
      // 如果是对象数组，将其转换为JSON字符串数组
      if (Array.isArray(obj) && obj.length > 0 && typeof obj[0] === 'object') {
        return (obj as Record<string, Object>[]).map((item: Record<string, Object>) => JSON.stringify(item));
      }
      return obj as string[];
    } catch (e) {
      console.error('Failed to parse A2UI v0.9 message:', e);
      return [];
    }
  }
}
