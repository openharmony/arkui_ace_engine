/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cstring>
#include <napi/native_api.h>
#include <hilog/log.h>

#include "visual_test_impl.h"

#undef LOG_DOMAIN
#define LOG_DOMAIN 0xD003F00
#undef LOG_TAG
#define LOG_TAG "VisualTest"

namespace {

napi_value CaptureAndCompare(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value argv[2];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    size_t len = 0;
    napi_get_value_string_utf8(env, argv[0], nullptr, 0, &len);
    std::string testName(len, '\0');
    napi_get_value_string_utf8(env, argv[0], testName.data(), len + 1, &len);

    double threshold = 0.95;
    if (argc >= 2) {
        napi_get_value_double(env, argv[1], &threshold);
    }

    auto frame = VisualTest::CaptureFrame();
    if (frame.data.empty()) {
        HILOG_WARN(LOG_APP, "No frame data: %{public}s", testName.c_str());
        napi_value result;
        napi_create_object(env, &result);
        napi_value passVal, scoreVal, nameVal;
        napi_get_boolean(env, false, &passVal);
        napi_create_double(env, 0.0, &scoreVal);
        napi_create_string_utf8(env, testName.c_str(), NAPI_AUTO_LENGTH, &nameVal);
        napi_set_named_property(env, result, "pass", passVal);
        napi_set_named_property(env, result, "score", scoreVal);
        napi_set_named_property(env, result, "testName", nameVal);
        return result;
    }

    std::string goldenPath = VisualTest::GetHapDir() + "/resources/rawfile/golden/" + testName + ".png";
    int32_t gw = 0, gh = 0;
    auto goldenData = VisualTest::ReadPNG(goldenPath, &gw, &gh);
    if (goldenData.empty()) {
        HILOG_WARN(LOG_APP, "Golden not found: %{public}s", goldenPath.c_str());
        napi_value result;
        napi_create_object(env, &result);
        napi_value passVal, scoreVal, nameVal;
        napi_get_boolean(env, false, &passVal);
        napi_create_double(env, 0.0, &scoreVal);
        napi_create_string_utf8(env, testName.c_str(), NAPI_AUTO_LENGTH, &nameVal);
        napi_set_named_property(env, result, "pass", passVal);
        napi_set_named_property(env, result, "score", scoreVal);
        napi_set_named_property(env, result, "testName", nameVal);
        return result;
    }

    auto cmp = VisualTest::CompareImages(frame.data.data(), frame.width, frame.height,
                                         goldenData.data(), gw, gh, threshold);

    HILOG_INFO(LOG_APP, "COMPARE: '%{public}s' actual=%dx%d golden=%dx%d score=%.4f thr=%.2f %s",
                 testName.c_str(), frame.width, frame.height, gw, gh,
                 cmp.score, threshold, cmp.pass ? "PASS" : "FAIL");

    if (!cmp.pass) {
        std::string diffPath = VisualTest::GetOutputDir() + "/" + testName + "_diff.png";
        std::string actualPath = VisualTest::GetOutputDir() + "/" + testName + "_actual.png";
        std::string expectedPath = VisualTest::GetOutputDir() + "/" + testName + "_expected.png";
        VisualTest::WriteDiffPNG(frame.data.data(), goldenData.data(),
                                 frame.width, frame.height, diffPath);
        VisualTest::WritePNG(frame.data.data(), frame.width, frame.height, actualPath);
        VisualTest::WritePNG(goldenData.data(), gw, gh, expectedPath);
    }

    HILOG_INFO(LOG_APP, "%{public}s: %s (score=%.4f)",
                 testName.c_str(), cmp.pass ? "PASS" : "FAIL", cmp.score);

#ifdef PREVIEW
    std::string capturePath = VisualTest::GetOutputDir() + "/capture_" + testName + ".png";
    VisualTest::WritePNG(frame.data.data(), frame.width, frame.height, capturePath);
#endif

    napi_value result;
    napi_create_object(env, &result);
    napi_value passVal, scoreVal, nameVal;
    napi_get_boolean(env, cmp.pass, &passVal);
    napi_create_double(env, cmp.score, &scoreVal);
    napi_create_string_utf8(env, testName.c_str(), NAPI_AUTO_LENGTH, &nameVal);
    napi_set_named_property(env, result, "pass", passVal);
    napi_set_named_property(env, result, "score", scoreVal);
    napi_set_named_property(env, result, "testName", nameVal);
    return result;
}

napi_value CaptureFrame(napi_env env, napi_callback_info info)
{
    auto frame = VisualTest::CaptureFrame();
    napi_value buffer;
    void* data = nullptr;
    napi_create_arraybuffer(env, frame.data.size(), &data, &buffer);
    if (!frame.data.empty()) {
        memcpy(data, frame.data.data(), frame.data.size());
    }
    return buffer;
}

napi_value Compare(napi_env env, napi_callback_info info)
{
    size_t argc = 4;
    napi_value argv[4];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    void* aData = nullptr;
    size_t aLen = 0;
    napi_get_arraybuffer_info(env, argv[0], &aData, &aLen);
    void* bData = nullptr;
    size_t bLen = 0;
    napi_get_arraybuffer_info(env, argv[1], &bData, &bLen);
    int32_t w = 0, h = 0;
    napi_get_value_int32(env, argv[2], &w);
    napi_get_value_int32(env, argv[3], &h);

    auto result = VisualTest::CompareImages(
        static_cast<const uint8_t*>(aData), w, h,
        static_cast<const uint8_t*>(bData), w, h, 0.0);
    napi_value scoreVal;
    napi_create_double(env, result.score, &scoreVal);
    return scoreVal;
}

napi_value ReadGolden(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    size_t len = 0;
    napi_get_value_string_utf8(env, argv[0], nullptr, 0, &len);
    std::string testName(len, '\0');
    napi_get_value_string_utf8(env, argv[0], testName.data(), len + 1, &len);

    std::string path = VisualTest::GetHapDir() + "/resources/rawfile/golden/" + testName + ".png";
    int32_t w = 0, h = 0;
    auto data = VisualTest::ReadPNG(path, &w, &h);

    napi_value buffer;
    void* outData = nullptr;
    napi_create_arraybuffer(env, data.size(), &outData, &buffer);
    if (!data.empty()) {
        memcpy(outData, data.data(), data.size());
    }
    return buffer;
}

napi_value WritePNG(napi_env env, napi_callback_info info)
{
    size_t argc = 4;
    napi_value argv[4];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    void* data = nullptr;
    size_t dataLen = 0;
    napi_get_arraybuffer_info(env, argv[0], &data, &dataLen);
    int32_t w = 0, h = 0;
    napi_get_value_int32(env, argv[1], &w);
    napi_get_value_int32(env, argv[2], &h);

    size_t pathLen = 0;
    napi_get_value_string_utf8(env, argv[3], nullptr, 0, &pathLen);
    std::string path(pathLen, '\0');
    napi_get_value_string_utf8(env, argv[3], path.data(), pathLen + 1, &pathLen);

    bool ok = VisualTest::WritePNG(static_cast<const uint8_t*>(data), w, h, path);
    napi_value result;
    napi_get_boolean(env, ok, &result);
    return result;
}

napi_value GetScreenSize(napi_env env, napi_callback_info info)
{
    auto size = VisualTest::GetScreenSize();
    napi_value result;
    napi_create_object(env, &result);
    napi_value wVal, hVal;
    napi_create_int32(env, size.width, &wVal);
    napi_create_int32(env, size.height, &hVal);
    napi_set_named_property(env, result, "width", wVal);
    napi_set_named_property(env, result, "height", hVal);
    return result;
}

napi_value IsPreviewer(napi_env env, napi_callback_info info)
{
    napi_value result;
    napi_get_boolean(env, VisualTest::IsPreviewer(), &result);
    return result;
}

napi_value SetOutputDir(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    size_t len = 0;
    napi_get_value_string_utf8(env, argv[0], nullptr, 0, &len);
    std::string dir(len, '\0');
    napi_get_value_string_utf8(env, argv[0], dir.data(), len + 1, &len);

    VisualTest::SetOutputDir(dir);
    return nullptr;
}

napi_value SetHapDir(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    size_t len = 0;
    napi_get_value_string_utf8(env, argv[0], nullptr, 0, &len);
    std::string dir(len, '\0');
    napi_get_value_string_utf8(env, argv[0], dir.data(), len + 1, &len);

    VisualTest::SetHapDir(dir);
    return nullptr;
}

napi_value ExitHeadlessTest(napi_env env, napi_callback_info info)
{
    return nullptr;
}

napi_value WriteFile(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value argv[2];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    size_t pathLen = 0;
    napi_get_value_string_utf8(env, argv[0], nullptr, 0, &pathLen);
    std::string path(pathLen, '\0');
    napi_get_value_string_utf8(env, argv[0], path.data(), pathLen + 1, &pathLen);

    void* data = nullptr;
    size_t dataLen = 0;
    napi_get_arraybuffer_info(env, argv[1], &data, &dataLen);

    bool ok = VisualTest::WriteFile(path, static_cast<const uint8_t*>(data), dataLen);
    napi_value result;
    napi_get_boolean(env, ok, &result);
    return result;
}

napi_value RequestRenderStable(napi_env env, napi_callback_info info)
{
    VisualTest::RequestRenderStable();
    return nullptr;
}

napi_value IsRenderStable(napi_env env, napi_callback_info info)
{
    napi_value result;
    napi_get_boolean(env, VisualTest::IsRenderStable(), &result);
    return result;
}

napi_module visualTestModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = nullptr,
    .nm_modname = "arkui.visualTest",
    .nm_priv = nullptr,
    .reserved = { 0 },
};

napi_value VisualTestExport(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        {"captureAndCompare", nullptr, CaptureAndCompare, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"captureFrame", nullptr, CaptureFrame, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"compare", nullptr, Compare, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"readGolden", nullptr, ReadGolden, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"writePNG", nullptr, WritePNG, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"writeFile", nullptr, WriteFile, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getScreenSize", nullptr, GetScreenSize, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"isPreviewer", nullptr, IsPreviewer, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"setOutputDir", nullptr, SetOutputDir, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"setHapDir", nullptr, SetHapDir, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"requestRenderStable", nullptr, RequestRenderStable, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"exit", nullptr, ExitHeadlessTest, nullptr, nullptr, nullptr, napi_default, nullptr},

        {"isRenderStable", nullptr, IsRenderStable, nullptr, nullptr, nullptr, napi_default, nullptr},
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}

extern "C" __attribute__((constructor)) void VisualTestRegister()
{
    visualTestModule.nm_register_func = VisualTestExport;
    napi_module_register(&visualTestModule);
}

} // namespace
