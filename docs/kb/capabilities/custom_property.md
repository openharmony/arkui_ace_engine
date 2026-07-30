# Custom Property Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `CustomProperty`

## 定位

本主题的主角是 **ArkTS 的 `.customProperty(name, value)` 设置 + `FrameNode.getCustomProperty(name)` 读取**——为组件附加任意键值对自定义属性（非框架预定义属性）的机制。采用 JS 侧 Map + FrameNode 双存储 + 懒加载物化，并提供 C-API（NDK）读写通路。

ArkTS 侧 `.customProperty()` 经 `JsCustomProperty` 下沉到 `FrameNode::SetJSCustomProperty`，值存于 JS Map（`__elementIdToCustomProperties__`，Object 源）+ FrameNode `customPropertyMap_`（字符串化+freshness flag）。**`FrameNode` 的 C++ 双存储是本主题的底层能力提供者**，ArkTS API 行为为主角。读取经 `frame_node.ts` JS 优先回退 C-API。

行为事实以 SDK 类型声明（`common.d.ts`/`common.static.d.ets`/`FrameNode.d.ts`）、ArkTS 实现（`js_view_abstract.cpp`/`ArkComponent.ts`/`frame_node.ts`）、测试与长期规格为准；本页仅作路由导航，不重复行为矩阵。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| **JS Bridge（设置入口）** | `frameworks/bridge/declarative_frontend/jsview/js_view_abstract.cpp` | `JsCustomProperty`(:10502/:13137) + ParseJsFunc(:13096)/ParseJsGetFunc(:13045)/JsGetCustomMapFunc(:13071) 回调工厂 |
| JS 存储 | `frameworks/bridge/declarative_frontend/ark_component/src/ArkComponent.ts` | `__elementIdToCustomProperties__`(:6678) Map + `__set/get/removeCustomProperty__` 全局(:6680-6758) |
| **FrameNode 双存储（主角底层）** | `frameworks/core/components_ng/base/frame_node.h/cpp` | `customPropertyMap_`(:1960) [strValue,flag] + `extraCustomPropertyMap_`(:1962) void* + 3 回调(:1861-1863)；SetJSCustomProperty(:8371)/GetJSCustomProperty(:8386)/GetCapiCustomProperty(:8403)/AddCustomProperty(:8413) |
| 读取入口 | `frameworks/bridge/declarative_frontend/ark_node/src/frame_node.ts:770` | getCustomProperty JS 优先回退 getCustomPropertyCapiByKey |
| 边界 | `frameworks/bridge/declarative_frontend/ark_node/src/trans_frame_node.ts:30` | transferDynamic FrameNode getCustomProperty 抛 100031 |
| C-API 声明 | `interfaces/native/native_node.h:13745/13754/13767` + `native_type.h:276/3515/3524` | Add/Remove(@since 13) + Get+handle(@since 14) |
| C-API 实现 | `interfaces/native/node/node_utils.cpp:244/256/268` + `frameworks/core/interfaces/native/node/frame_node_modifier.cpp:933/945/1002` | NDK 入口 + modifier 转发 |
| ANI | `frameworks/core/interfaces/native/ani/common_ani_modifier.cpp:477/492` | SetCustomPropertyCallBack/GetCustomProperty |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| **SDK 设置（主角）** | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts:19582` | `customProperty(name, value: Optional<Object>)` @since 12 dynamic |
| **SDK 读取（主角）** | `<OH_ROOT>/interface/sdk-js/api/arkui/FrameNode.d.ts:991` | `getCustomProperty(name): Object \| undefined` @since 12 dynamic |
| SDK 静态 | `arkui/component/common.static.d.ets:11491`（设置）+ `arkui/FrameNode.static.d.ets:801`（读取） | @since 23 static；`CustomProperty` 类型(:11431) |
| C-API | `interfaces/native/native_node.h` + `native_type.h` | Add/Remove @since 13、Get+Destroy/GetStringValue @since 14 |

### API 解析实现路径

| 路径 | 入口文件 | 说明 |
|------|----------|------|
| JS 设置 | `js_view_abstract.cpp:13137` | JsCustomProperty 构建回调→SetJSCustomProperty |
| JS 存储 | `ArkComponent.ts:6758` | __setCustomProperty__ 写 JS Map（value===undefined 移除） |
| 原生存储 | `frame_node.cpp:8371/8426` | SetJSCustomProperty 写+置 flag "0"(stale)；GetJSCustomProperty flag "0" 经回调重取置 "1"(懒物化) |
| 读取 | `frame_node.ts:770` | __getCustomProperty__ JS 优先，miss 回退 getCustomPropertyCapiByKey |
| C-API | `node_utils.cpp:244/268` | AddCustomProperty 直写 {value,"1"}；GetCustomProperty 先 Capi 后 JS |

**关键版本/边界**（详见 Feat 规格风险表）：API 26.0.0 起自定义组件支持（动态文档，静态未同步，风险 R-1）；transferDynamic 抛 100031（风险 R-2）；JS 值字符串化（风险 R-3）；extraCustomPropertyMap_ 原生指针侧信道（风险 R-4）。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单测 | `test/unittest/core/base/frame_node_test_ng*.cpp` | FrameNode customPropertyMap_ 双存储与懒物化 |
| C-API 单测 | `test/unittest/capi/` | OH_ArkUI_NodeUtils_Add/Remove/GetCustomProperty |

### 相关 Spec

| Spec | 路径 | 状态 |
|------|------|------|
| 设计基线 | `specs/04-common-capability/05-custom-extension/05-custom-property/design.md` | Baselined（`DESIGN-Func-04-05-05`） |
| Feat-01 设置读取与双存储 | `specs/04-common-capability/05-custom-extension/05-custom-property/Feat-01-custom-property-set-read-storage-spec.md` | Baselined |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| getCustomProperty 读回的是字符串非 Object | customPropertyMap_ 存 stringifiedValue，Object 经 JSON 序列化(风险 R-3)。见 Feat-01 R-1 |
| 自定义组件(@Component)设 customProperty 无效 | API < 26.0.0 自定义组件不支持；静态文档仍注明不支持(风险 R-1)。见 Feat-01 R-16/R-17 |
| transferDynamic 创建的 FrameNode getCustomProperty 抛 100031 | 设计边界，不可读。见 Feat-01 R-10 |
| C-API 设的值 JS 读不到或反之 | C-API AddCustomProperty 直写 flag "1"；JS 设值置 flag "0" 经懒物化。两路径共用 customPropertyMap_。见 Feat-01 R-11/R-7 |
| handle 泄漏 | OH_ArkUI_NodeUtils_GetCustomProperty 返回的 handle 须 OH_ArkUI_CustomProperty_Destroy 释放。见 Feat-01 R-15 |

## 调试入口

- **双存储状态**：`frame_node.h:1960/1962` 的 `customPropertyMap_`(flag "0"=stale/"1"=valid) + `extraCustomPropertyMap_`(void* 侧信道)。
- **JS Map**：`ArkComponent.ts:6678` `__elementIdToCustomProperties__` 为 Object 值源。
- **Inspector**：`frame_node.cpp:1770-1780` 序列化 customPropertyMap_ 为 JSON。

## 相关主题

- [FrameNode](./frame_node.md) — customProperty 存储于 FrameNode（04-06-02）
- [DrawModifier](./draw_modifier.md) — 自定义绘制（04-05-01）
- [Attribute Modifier](./attribute_modifier.md) — 动态属性通路（04-05-02）
- [Component Modifier](./component_modifier.md) — 命令式 Modifier 类（04-05-06）
