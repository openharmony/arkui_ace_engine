/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * ...
 *
 * TASK-0: 共享过滤工具函数实现
 * 从 content_controller.cpp 迁移，逻辑保持不变。
 */

#include "text_filter_utils.h"

namespace OHOS::Ace::Ng::TextFilterUtils {

// --- Migrated from content_controller.cpp L41-51 ---
std::wstring ContentToWstring(const std::u16string& str)
{
    auto utf16Len = str.length();
    std::unique_ptr<wchar_t[]> pBuf16 = std::make_unique<wchar_t[]>(utf16Len);
    wchar_t* wBuf = pBuf16.get();
    for (uint32_t i = 0; i < utf16Len; i++) {
        wBuf[i] = static_cast<wchar_t>(str[i]);
    }
    return std::wstring(wBuf, utf16Len);
}

// --- Migrated from content_controller.cpp L53-62 ---
std::u16string ContentToU16string(const std::wstring& str)
{
    auto utf16Len = str.length();
    std::unique_ptr<char16_t[]> pBuf16 = std::make_unique<char16_t[]>(utf16Len);
    char16_t* buf16 = pBuf16.get();
    for (uint32_t i = 0; i < utf16Len; i++) {
        buf16[i] = static_cast<char16_t>(str[i]);
    }
    return std::u16string(buf16, utf16Len);
}

// --- Migrated from content_controller.cpp L289-308 ---
std::u16string RemoveErrorTextFromValue(const std::u16string& value, const std::u16string& errorText)
{
    std::u16string result;
    int32_t valuePtr = 0;
    int32_t errorTextPtr = 0;
    auto valueSize = static_cast<int32_t>(value.length());
    auto errorTextSize = static_cast<int32_t>(errorText.length());
    while (errorTextPtr < errorTextSize) {
        while (value[valuePtr] != errorText[errorTextPtr] && valuePtr < valueSize) {
            result += value[valuePtr];
            valuePtr++;
        }
        if (valuePtr >= valueSize) {
            return result;
        }
        valuePtr++;
        errorTextPtr++;
    }
    // Append remaining characters after all error chars processed
    while (valuePtr < valueSize) {
        result += value[valuePtr];
        valuePtr++;
    }
    return result;
}

// --- Migrated from content_controller.cpp L314-324 ---
std::u16string FilterWithRegex(const std::u16string& filter, std::u16string& result)
{
    // convert wstring for processing unicode characters
    std::wstring wFilter = ContentToWstring(filter);
    std::wstring wResult = ContentToWstring(result);
    std::wregex wFilterRegex(wFilter);
    std::wstring wErrorText = std::regex_replace(wResult, wFilterRegex, L"");
    std::u16string errorText = ContentToU16string(wErrorText);
    result = RemoveErrorTextFromValue(result, errorText);
    return errorText;
}

} // namespace OHOS::Ace::Ng::TextFilterUtils
