# TASK-2: 接口层 — 静态 API + 动态 API 补齐 TextEncoding + encoding 参数

## 目标

在静态 API 声明文件 `textCommon.static.d.ets` 和动态 API 声明文件 `text_common.d.ts` 中补齐 `TextEncoding` 枚举和三接口的 `encoding?` 参数（en + zh-cn 同步）。

## 受影响文件

- `interface_sdk-js/api/arkui/component/textCommon.static.d.ets` — 新增 `export declare enum TextEncoding` + 三接口方法重载
- `interface_sdk-js/api/@internal/component/ets/text_common.d.ts` — 新增 `declare enum TextEncoding` + 三接口方法重载（en）
- `interface_sdk-js/zh-cn/api/@internal/component/ets/text_common.d.ts` — 同上中文版

## 实现要点

### textCommon.static.d.ets
1. 在 `LayoutManager` interface 后新增 `export declare enum TextEncoding { TEXT_ENCODING_UTF8 = 0, TEXT_ENCODING_UTF16 = 1 }`（`@since 26.0.0 static`）
2. `getCharacterPositionAtCoordinate` 新增带 `encoding?: TextEncoding` 的方法重载（`@since 26.0.0 static`）；旧方法 @since 12 保留不变
3. `getGlyphRangeForCharacterRange` 同上新增带 `encoding?: TextEncoding` 的方法重载
4. `getCharacterRangeForGlyphRange` 同上新增带 `encoding?: TextEncoding` 的方法重载
5. JSDoc `@param encoding` 描述默认值为 `TextEncoding.TEXT_ENCODING_UTF8`

### text_common.d.ts（en + zh-cn）
6. 在 `LayoutManager` interface 后新增 `declare enum TextEncoding { TEXT_ENCODING_UTF8 = 0, TEXT_ENCODING_UTF16 = 1 }`（`@since 26.0.0 dynamic`）
7. 三接口新增带 `encoding?: TextEncoding` 的方法重载（`@since 26.0.0 dynamic`）；旧方法 @since 24 保留不变（`PositionWithAffinity` 已含 `| undefined`，无需修改）
8. JSDoc `@param encoding` 描述默认值为 `TextEncoding.TEXT_ENCODING_UTF8`
9. zh-cn 版本与 en 版本一一对应，参数名/枚举名/枚举值不变，仅 JSDoc 文案中文化

> 注：原 proposal.md 轮次 1 表述"接口层 text_common.d.ts 已有 TextEncoding 枚举"为错误判断，已在轮次 9 更正；实际 d.ts 需新增枚举与方法重载，并非仅 JSDoc 修订。

## 验证

- `.d.ets` / `.d.ts` 语法正确（TypeScript declaration 格式）
- 枚举值名 `TEXT_ENCODING_UTF8`/`TEXT_ENCODING_UTF16` 在静态/动态 API 中保持一致
- en 与 zh-cn 版本一一对应
- 旧方法签名未改动（向后兼容）
