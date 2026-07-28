#include <cstring>
#include <napi/native_api.h>

#include "imagecompare.h"

namespace {

using namespace imagecompare;

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

Image ArrayBufferToImage(napi_env env, napi_value buffer, int32_t width, int32_t height)
{
    Image img;
    img.width = width;
    img.height = height;

    bool isArrayBuffer = false;
    if (napi_is_arraybuffer(env, buffer, &isArrayBuffer) != napi_ok || !isArrayBuffer) {
        printf("[ImageCompare] ArrayBufferToImage: not an ArrayBuffer\n");
        return img;
    }

    void* data = nullptr;
    size_t len = 0;
    if (napi_get_arraybuffer_info(env, buffer, &data, &len) != napi_ok) {
        printf("[ImageCompare] ArrayBufferToImage: get_arraybuffer_info failed\n");
        return img;
    }

    size_t expected = static_cast<size_t>(width) * static_cast<size_t>(height) * 4;
    if (len < expected) {
        printf("[ImageCompare] ArrayBufferToImage: buffer too small: %zu < %zu\n", len, expected);
        return img;
    }

    img.data.assign(static_cast<const uint8_t*>(data),
                    static_cast<const uint8_t*>(data) + expected);
    return img;
}

napi_value ImageToObject(napi_env env, const Image& img)
{
    napi_value result;
    napi_create_object(env, &result);

    napi_value dataVal;
    void* outData = nullptr;
    napi_status createStatus = napi_create_arraybuffer(env, img.data.size(), &outData, &dataVal);
    if (createStatus == napi_ok && outData != nullptr) {
        if (!img.data.empty()) {
            std::memcpy(outData, img.data.data(), img.data.size());
        }
        napi_set_named_property(env, result, "data", dataVal);
    }

    napi_value wVal, hVal;
    napi_create_int32(env, img.width, &wVal);
    napi_create_int32(env, img.height, &hVal);
    napi_set_named_property(env, result, "width", wVal);
    napi_set_named_property(env, result, "height", hVal);

    return result;
}

napi_value DiffResultToObject(napi_env env, const DiffResult& r)
{
    napi_value result;
    napi_create_object(env, &result);

    napi_value passVal, scoreVal, errorVal;
    napi_get_boolean(env, r.pass, &passVal);
    napi_create_double(env, r.score, &scoreVal);
    if (r.error) {
        napi_create_string_utf8(env, r.error, NAPI_AUTO_LENGTH, &errorVal);
    } else {
        napi_get_null(env, &errorVal);
    }

    napi_set_named_property(env, result, "pass", passVal);
    napi_set_named_property(env, result, "score", scoreVal);
    napi_set_named_property(env, result, "error", errorVal);

    return result;
}

// ---------------------------------------------------------------------------
// Exported functions
// ---------------------------------------------------------------------------

napi_value Compare(napi_env env, napi_callback_info info)
{
    size_t argc = 7;
    napi_value argv[7];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    int32_t aw = 0, ah = 0, gw = 0, gh = 0;
    double threshold = 0.95;

    if (argc >= 2) napi_get_value_int32(env, argv[1], &aw);
    if (argc >= 3) napi_get_value_int32(env, argv[2], &ah);
    if (argc >= 5) napi_get_value_int32(env, argv[4], &gw);
    if (argc >= 6) napi_get_value_int32(env, argv[5], &gh);
    if (argc >= 7) napi_get_value_double(env, argv[6], &threshold);

    Image actual = ArrayBufferToImage(env, argv[0], aw, ah);
    Image golden = ArrayBufferToImage(env, argv[3], gw, gh);

    DiffResult result = ImageCompare::Get().Compare(actual, golden, threshold);
    return DiffResultToObject(env, result);
}

napi_value DecodePNG(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    void* data = nullptr;
    size_t len = 0;
    napi_get_arraybuffer_info(env, argv[0], &data, &len);

    Image img = ImageCompare::Get().DecodePNG(static_cast<const uint8_t*>(data), len);
    return ImageToObject(env, img);
}

napi_value DecodePNGFile(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    std::string path;
    if (argc >= 1) {
        size_t len = 0;
        napi_get_value_string_utf8(env, argv[0], nullptr, 0, &len);
        path.resize(len);
        napi_get_value_string_utf8(env, argv[0], &path[0], len + 1, &len);
    }

    Image img = ImageCompare::Get().DecodePNGFile(path);
    return ImageToObject(env, img);
}

napi_value EncodePNG(napi_env env, napi_callback_info info)
{
    size_t argc = 3;
    napi_value argv[3];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    int32_t w = 0, h = 0;
    if (argc >= 2) napi_get_value_int32(env, argv[1], &w);
    if (argc >= 3) napi_get_value_int32(env, argv[2], &h);

    Image img = ArrayBufferToImage(env, argv[0], w, h);
    std::vector<uint8_t> png = ImageCompare::Get().EncodePNG(img);

    napi_value buffer;
    void* outData = nullptr;
    napi_status createStatus = napi_create_arraybuffer(env, png.size(), &outData, &buffer);
    if (createStatus != napi_ok || outData == nullptr) {
        napi_value undef;
        napi_get_undefined(env, &undef);
        return undef;
    }
    if (!png.empty()) {
        std::memcpy(outData, png.data(), png.size());
    }
    return buffer;
}

napi_value WritePNG(napi_env env, napi_callback_info info)
{
    size_t argc = 4;
    napi_value argv[4];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    int32_t w = 0, h = 0;
    if (argc >= 2) napi_get_value_int32(env, argv[1], &w);
    if (argc >= 3) napi_get_value_int32(env, argv[2], &h);

    std::string path;
    if (argc >= 4) {
        size_t len = 0;
        napi_get_value_string_utf8(env, argv[3], nullptr, 0, &len);
        path.resize(len);
        napi_get_value_string_utf8(env, argv[3], &path[0], len + 1, &len);
    }

    Image img = ArrayBufferToImage(env, argv[0], w, h);
    ImageCompare::Get().WritePNG(img, path);
    return nullptr;
}

napi_value WriteDiff(napi_env env, napi_callback_info info)
{
    size_t argc = 7;
    napi_value argv[7];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    int32_t aw = 0, ah = 0, gw = 0, gh = 0;
    if (argc >= 2) napi_get_value_int32(env, argv[1], &aw);
    if (argc >= 3) napi_get_value_int32(env, argv[2], &ah);
    if (argc >= 5) napi_get_value_int32(env, argv[4], &gw);
    if (argc >= 6) napi_get_value_int32(env, argv[5], &gh);

    std::string path;
    if (argc >= 7) {
        size_t len = 0;
        napi_get_value_string_utf8(env, argv[6], nullptr, 0, &len);
        path.resize(len);
        napi_get_value_string_utf8(env, argv[6], &path[0], len + 1, &len);
    }

    Image actual = ArrayBufferToImage(env, argv[0], aw, ah);
    Image golden = ArrayBufferToImage(env, argv[3], gw, gh);

    ImageCompare::Get().WriteDiff(actual, golden, path);
    return nullptr;
}

napi_value WriteManifest(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value argv[2];
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);

    std::string json, path;
    if (argc >= 1) {
        size_t len = 0;
        napi_get_value_string_utf8(env, argv[0], nullptr, 0, &len);
        json.resize(len);
        napi_get_value_string_utf8(env, argv[0], &json[0], len + 1, &len);
    }
    if (argc >= 2) {
        size_t len = 0;
        napi_get_value_string_utf8(env, argv[1], nullptr, 0, &len);
        path.resize(len);
        napi_get_value_string_utf8(env, argv[1], &path[0], len + 1, &len);
    }

    ImageCompare::Get().WriteManifest(json, path);
    return nullptr;
}

// ---------------------------------------------------------------------------
// Module registration
// ---------------------------------------------------------------------------

napi_module imageCompareModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = nullptr,
    .nm_modname = "arkui.visualtest.compare",
    .nm_priv = nullptr,
    .reserved = { 0 },
};

napi_value ImageCompareExport(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        {"compare",       nullptr, Compare,       nullptr, nullptr, nullptr, napi_default, nullptr},
        {"decodePNG",     nullptr, DecodePNG,     nullptr, nullptr, nullptr, napi_default, nullptr},
        {"decodePNGFile", nullptr, DecodePNGFile, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"encodePNG",     nullptr, EncodePNG,     nullptr, nullptr, nullptr, napi_default, nullptr},
        {"writePNG",      nullptr, WritePNG,      nullptr, nullptr, nullptr, napi_default, nullptr},
        {"writeDiff",     nullptr, WriteDiff,     nullptr, nullptr, nullptr, napi_default, nullptr},
        {"writeManifest", nullptr, WriteManifest, nullptr, nullptr, nullptr, napi_default, nullptr},
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}

extern "C" __attribute__((constructor)) void ImageCompareRegister()
{
    imageCompareModule.nm_register_func = ImageCompareExport;
    napi_module_register(&imageCompareModule);
    printf("[ImageCompare] NAPI module 'compare' registered (prefix: arkui)\n");
}

}  // namespace
