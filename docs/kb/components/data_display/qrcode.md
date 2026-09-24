# QRCode Context

> 文档版本：v1.0
> 更新时间：2026-07-29
> 来源：`docs/context_registry.json` 主题 `QRCode`

## 定位

QRCode 是信息展示类组件，将字符串编码为二维码图像并显示。核心能力包括自定义前景色/背景色、内容透明度、主题颜色响应、正方形布局约束。组件已组件化，支持动态/静态两种前端管线按需加载。

## 快速路由

### 源码入口

- 组件根目录：`frameworks/core/components_ng/pattern/qrcode/`
- Pattern 层：`frameworks/core/components_ng/pattern/qrcode/qrcode_pattern.cpp`
- Model 层：`frameworks/core/components_ng/pattern/qrcode/qrcode_model_ng.cpp`
- Modifier 层：`frameworks/core/components_ng/pattern/qrcode/qrcode_modifier.cpp`
- Layout 层：`frameworks/core/components_ng/pattern/qrcode/qrcode_layout_algorithm.cpp`

### API 入口

- 动态 API（.d.ts）：`<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/qrcode.d.ts`
- 静态 API（.static.d.ets）：`<OH_ROOT>/interface/sdk-js/api/arkui/component/qrcode.static.d.ets`
- Modifier API：`<OH_ROOT>/interface/sdk-js/api/arkui/QRCodeModifier.d.ts`
- 静态 Modifier API：`<OH_ROOT>/interface/sdk-js/api/arkui/QRCodeModifier.static.d.ets`
- Ark Component：`frameworks/core/components_ng/pattern/qrcode/arkui_qrcode.js`
- NAPI 模块名：`arkui.qrcode`

### API 解析实现路径

QRCode 组件已组件化（`is_component_model = true`），具备完整的多管线覆盖：

- **动态管线**：`frameworks/core/components_ng/pattern/qrcode/bridge/qrcode_dynamic_modifier.cpp` → `ArkUIQRCodeModifier` 函数指针表
- **静态管线**：`frameworks/core/components_ng/pattern/qrcode/bridge/qrcode_static_modifier.cpp` → `GENERATED_ArkUIQRCodeModifier`（GeneratedModifier::QRCodeModifier::ConstructImpl + QRCodeInterfaceModifier + QRCodeAttributeModifier）
- **CJ 管线**：`CJUIQRCodeModifier`（通过 qrcode_dynamic_modifier.cpp 中 GetCJUIQRCodeModifier）
- **ArkTS Native Bridge**：`frameworks/core/components_ng/pattern/qrcode/bridge/arkts_native_qrcode_bridge.cpp` → RegisterQRCodeAttributes
- **动态模块**：`frameworks/core/components_ng/pattern/qrcode/bridge/qrcode_dynamic_module.cpp` → `OHOS_ACE_DynamicModule_Create_QRCode` 入口
- **C API Modifier**：`frameworks/core/interfaces/native/node/qrcode_modifier.h` → `NodeModifier::GetQRCodeModifier()`

### 外部依赖入口

- qrcode_generator 库：`qrcode_generator:qrcodegen`（外部依赖，BUILD.gn 中 external_deps）
  - C API：`QrcodeImageEncodeString()`, `QrcodeImageFree()`, `QrcodeGetModule()`
  - 编码纠错等级：`QRCODE_ECC_MEDIUM`（硬编码）
- QrcodeTheme：`frameworks/core/components/qrcode/qrcode_theme.h`
- QRCodeThemeWrapper：`frameworks/core/components_ng/pattern/qrcode/qrcode_theme_wrapper.h`（Token 主题映射）

### 测试入口

- 单元测试：`test/unittest/core/pattern/qrcode/qrcode_test_ng.cpp`
- 旧版测试：`test/unittest/core/pattern/qrcode/qrcode_test_core.cpp`

### 相关 Spec

- Spec 域：`specs/05-ui-components/10-information-display-components/06-qrcode`
- arkui-specs 规格仓：`specs/05-ui-components/10-information-display-components/06-qr-code/Feat-01-qrcode-display-spec.md`
- FuncID：05-10-06

## 常见问题定位

| 问题 | 定位关键词/搜索路径 |
|------|---------------------|
| 二维码不显示 | 搜索 `QrcodeImageEncodeString` 返回 null，或 `qrCodeSize < qrWidth` 条件 |
| 非正方形尺寸 | 搜索 `MeasureContent` → `std::min(width, height)` |
| 颜色不生效 | 搜索 `QRCodeColorSetByUser` / `QRBackgroundColorSetByUser` 标记 |
| 主题切换后颜色被覆盖 | 搜索 `OnColorConfigurationUpdate` → `HasQRCodeColorSetByUser` |
| API 版本行为差异 | 搜索 `PLATFORM_VERSION_11` / `VERSION_TWELVE` / `VERSION_TWENTY_SIX` |
| 字符串长度截断 | 搜索 `QRCODE_VALUE_MAX_LENGTH` (512) |
| BackgroundColor HDR | 搜索 `SetHDRColorHeadRoom` / `GetHeadRoomColor` |

## 调试入口

- 日志标签：`AceLogTag::ACE_QRCODE`
- DumpInfo：QRCodePattern::DumpInfo 输出 Color、ContentOpacity、ContentString
- Inspector：QRCodePaintProperty::ToJsonValue 输出 value、color、backgroundColor、contentOpacity

## 相关主题

- LayoutFramework（布局框架）
- ThemeManager（主题管理器）