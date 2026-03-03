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

#ifndef SCENARIO7_SETTINGS_H
#define SCENARIO7_SETTINGS_H

#include "scenarios/ScenarioBase.h"
#include <vector>
#include <memory>

namespace NativeXComponentSample {

/**
 * Scenario7: Settings Page
 *
 * 场景描述：设置页面，演示事件管理和高级状态接口
 *
 * 覆盖的Native接口（14个）:
 * 1. OH_ArkUI_CreateAccessibilityEventInfo - 创建事件信息对象
 * 2. OH_ArkUI_DestoryAccessibilityEventInfo - 销毁事件信息对象
 * 3. OH_ArkUI_AccessibilityEventSetEventType - 设置事件类型
 * 4. OH_ArkUI_AccessibilityEventSetTextAnnouncedForAccessibility - 设置播报文本
 * 5. OH_ArkUI_AccessibilityEventSetRequestFocusId - 设置请求焦点ID
 * 6. OH_ArkUI_AccessibilityEventSetElementInfo - 设置关联的元素信息
 * 7. OH_ArkUI_AccessibilityElementInfoSetEnabled - 设置是否启用
 * 8. OH_ArkUI_AccessibilityElementInfoSetVisible - 设置是否可见
 * 9. OH_ArkUI_AccessibilityElementInfoSetAccessibilityLevel - 设置无障碍级别
 * 10. OH_ArkUI_AccessibilityElementInfoSetZIndex - 设置Z轴层级
 * 11. OH_ArkUI_AccessibilityElementInfoSetAccessibilityOpacity - 设置透明度
 * 12. OH_ArkUI_AccessibilityElementInfoSetBackgroundColor - 设置背景颜色
 * 13. OH_ArkUI_AccessibilityElementInfoSetHintText - 设置提示文本
 * 14. OH_ArkUI_SendAccessibilityAsyncEvent - 发送无障碍事件
 *
 * 覆盖的事件类型枚举（5个）:
 * 1. ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_SELECTED - 状态改变（选中/未选中）
 * 2. ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_ACCESSIBILITY_FOCUSED - 焦点事件
 * 3. ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_ACCESSIBILITY_FOCUS_CLEARED - 清除焦点
 * 4. ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_ANNOUNCE_FOR_ACCESSIBILITY - 播报事件
 * 5. ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_TEXT_UPDATE - 文本更新
 *
 * 测试用例（7个）:
 * 1. 点击WiFi开关，触发SELECTED事件和播报
 * 2. 点击蓝牙开关，触发事件并验证SetIsEnable
 * 3. 点击通知开关，验证SetIsVisible和事件
 * 4. 点击主题选择，验证高级视觉属性（背景色、透明度、Z轴层级）
 * 5. 点击语言选择，验证SetHintText和播报事件
 * 6. 点击关于按钮，验证焦点事件和accessibilityLevel
 * 7. 点击恢复默认，验证所有开关重置和批量事件发送
 *
 * 节点数量：7个（1个容器 + 6个子节点）
 */
class Scenario7Settings : public ScenarioBase {
public:
    Scenario7Settings();
    ~Scenario7Settings() override;

    // ScenarioBase接口实现
    const char* GetId() const override
    {
        return "scenario7_settings";
    }
    const char* GetName() const override
    {
        return "设置页面";
    }
    const char* GetDescription() const override
    {
        return "演示事件管理和高级状态接口的设置页面";
    }
    void Initialize() override;
    const std::vector<AccessibleObject*>& GetNodes() const override;
    AccessibleObject* GetRootNode() const override;
    AccessibleObject* GetNodeById(int64_t elementId) override;
    bool HandleAction(int64_t elementId, ArkUI_Accessibility_ActionType action) override;
    void Cleanup() override;

    int GetInterfaceCount() const override
    {
        return 14;
    }
    int GetTestCaseCount() const override
    {
        return 7;
    }

private:
    void CreateNodes();
    void ConfigureNodes();
    void UpdateSwitchStates();
    void SendStateChangedEvent(AccessibleObject* node, const std::string& announcement);
    void SendAnnouncementEvent(const std::string& text);

    int64_t AllocateElementId()
    {
        return nextElementId_++;
    }

    // 节点存储
    std::vector<AccessibleObject*> nodes_;
    AccessibleObject* rootNode_ = nullptr;

    // 设置项节点
    AccessibleObject* wifiSwitch_ = nullptr;      // WiFi开关
    AccessibleObject* bluetoothSwitch_ = nullptr; // 蓝牙开关
    AccessibleObject* notificationSwitch_ = nullptr; // 通知开关
    AccessibleObject* themeSelector_ = nullptr;   // 主题选择
    AccessibleObject* languageSelector_ = nullptr; // 语言选择
    AccessibleObject* aboutButton_ = nullptr;     // 关于按钮

    // 状态
    bool wifiEnabled_ = true;
    bool bluetoothEnabled_ = false;
    bool notificationEnabled_ = true;
    int currentThemeIndex_ = 0;
    int currentLanguageIndex_ = 0;

    int64_t nextElementId_ = 1;

    // 主题配置（用于演示高级视觉属性）
    struct ThemeConfig {
        const char* name;
        const char* backgroundColor;
        float opacity;
        int zIndex;
    };
    static const int THEME_COUNT = 3;
    ThemeConfig themes_[THEME_COUNT];
};

} // namespace NativeXComponentSample

#endif // SCENARIO7_SETTINGS_H
