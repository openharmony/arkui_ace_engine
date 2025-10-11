/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#pragma once

#include <algorithm>
#include <functional>
#include <filesystem>
#include <fstream>
#include <cstdint>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>

#include "interop-types.h"

using std::string;

const int UndefinedDimensionUnit = -1;
const int DrawBehind = 0;
const int DrawContent = 1;
const int DrawFront = 2;

struct Dimension
{
    float value = 0;
    int32_t unit = UndefinedDimensionUnit;
};

struct DrawModifierCaller {
    private:
    std::function<void(Ark_DrawContext event)> _drawBehindCallback;
    std::function<void(Ark_DrawContext event)> _drawContentCallback;
    std::function<void(Ark_DrawContext event)> _drawFrontCallback;

    public:
    void setDrawModifierCallback(std::function<void(Ark_DrawContext event)> callback, int type) {
        switch (type)
        {
        case DrawBehind:
            _drawBehindCallback = callback;
            break;
        case DrawContent:
            _drawContentCallback = callback;
            break;
        case DrawFront:
            _drawFrontCallback = callback;
            break;
        default:
            break;
        }
    }

    void callDrawModifierCallback(Ark_DrawContext context, int type) {
        switch (type)
        {
        case DrawBehind:
            if (_drawBehindCallback) _drawBehindCallback(context);
            break;
        case DrawContent:
            if (_drawContentCallback) _drawContentCallback(context);
            break;
        case DrawFront:
            if (_drawFrontCallback) _drawFrontCallback(context);
            break;
        default:
            break;
        }
    }
};

std::unordered_map<Ark_DrawModifier, std::shared_ptr<DrawModifierCaller>> DrawModifiersQueue;

struct TreeNode {
  private:
    static int _globalId;
    static string _noAttribute;
    string _name;
    int _customIntData;
    std::unique_ptr<void, std::function<void(const void *)>> _customVoidData;
    int _peerId;
    int _flags;
    // Id of our peer.
    int _id;
    // Id of updater callback.
    int _updaterId;
    // Id of indexer callback.
    int _indexerId;
    // Id of custom callback.
    int _customId;
    std::vector<TreeNode*> _children;
    std::unordered_map<string, string> _attributes;
    TreeNode* _parent;
    float _width;
    float _height;
    float _x;
    float _y;

    Ark_DrawModifier _drawModifier = nullptr;

    std::function<void(Ark_ClickEvent event)> _clickCallback;


  public:
    TreeNode(const string& name, int peerId, int flags) :
        _name(name), _customIntData(0), _peerId(peerId), _flags(flags), _id(_globalId++), _updaterId(0), _indexerId(0), _parent(nullptr) {}

    ~TreeNode() = default;

    string name() const { return _name; }

    void setCustomIntData(int intData) {
        _customIntData = intData;
    }

    template<class T>
    void setCustomVoidData(T *const ptr) {
        _customVoidData = {ptr, [ptr](const void *) { delete ptr; }};
    }

    void *customVoidData() const {
        return _customVoidData.get();
    }
    const char* namePtr() const { return _name.c_str(); }

    int peerId() const { return _peerId; }

    int id() const { return _id; }

    int updaterId() const { return _updaterId; }
    int indexerId() const { return _indexerId; }
    int customId() const { return _customId; }

    void setUpdaterId(int updaterId) { _updaterId = updaterId; }
    void setIndexerId(int indexerId) { _indexerId = indexerId; }
    void setCustomId(int customId) { _customId = customId; }
    void setClickEvent(std::function<void(Ark_ClickEvent event)> event) {
        _clickCallback = event;
    }
    void callClickEvent(Ark_ClickEvent event) {
        if (_clickCallback) {
            _clickCallback(event);
        } else {
            fprintf(stderr, "#### Callback is nullptr, peerId = %d\n", _peerId);
        }
    }

    void setDrawModifier(Ark_DrawModifier modifier) { _drawModifier = modifier; }

    const std::vector<TreeNode*>* children() { return &_children; }

    void dispose() {
        if (_drawModifier) DrawModifiersQueue.erase(_drawModifier);
        delete this;
    }

    void setParent(TreeNode* parent) {
        this->_parent = parent;
    }

    TreeNode* parent() const {
        return this->_parent;
    }

    int addChild(TreeNode* node) {
        _children.push_back(node);
        node->setParent(this);
        return 0;
    }

    float measure(Ark_VMContext vmContext, float* data);
    float layout(Ark_VMContext vmContext, float* data);
    float draw(Ark_VMContext vmContext, float* data);

    void setMeasureWidthValue(float value);
    float getMeasureWidthValue();
    void setMeasureHeightValue(float value);
    float getMeasureHeightValue();
    void setXValue(float value);
    float getXValue();
    void setYValue(float value);
    float getYValue();

    void removeChild(TreeNode* node) {
        auto it = std::find(_children.begin(), _children.end(), node);
        if (it != _children.end()) {
            _children.erase(it);
            node->setParent(nullptr);
        }
    }

    int insertChildAfter(TreeNode* node, TreeNode* sibling) {
        if (sibling == (TreeNode*)1 || sibling == nullptr) {
            node->setParent(this);
            _children.push_back(node);
            return 0;
        }

        if (_children.empty()) {
            _children.push_back(node);
            return 0;
        }
        auto it = std::find(_children.begin(), _children.end(), sibling);
        if (it == _children.end()) {
            fprintf(stderr, "insertChildAfter: sibling node %p not found among children\n", sibling);
            INTEROP_FATAL("Error");
        }
        auto next = std::next(it);
        _children.insert(next, node);
        node->setParent(this);
        return 0;
    }

    int insertChildBefore(TreeNode* node, TreeNode* sibling) {
        if (sibling == (TreeNode*)1 || sibling == nullptr) {
            _children.insert(_children.begin(), node);
            return 0;
        }

        if (_children.empty()) {
            _children.push_back(node);
            return 0;
        }
        auto it = std::find(_children.begin(), _children.end(), sibling);
        if (it == _children.end()) {
            fprintf(stderr, "insertChildBefore: sibling node %p not found among children\n", sibling);
            INTEROP_FATAL("Error");
        }
        _children.insert(it, node);
        node->setParent(this);
        return 0;
    }

    int insertChildAt(TreeNode* node, int position) {
        if ((size_t)position <= _children.size()) {
            _children.insert(std::next(_children.begin(), position), node);
        } else {
            INTEROP_FATAL("TreeNode::insertChildAt position=%d larger than size of children(%d)", position, static_cast<int>(_children.size()));
        }
        node->setParent(this);
        return 0;
    }

    void* needMoreElements(void* mark, int32_t direction) {
        fprintf(stderr, "needMoreElements %p %d\n", mark, direction);
        if (_children.size() == 0)
            return (void*)0x1;
        if (_children.size() > 5)
            return nullptr;
        return direction == 0 ? _children.front() : _children.back();
    }

    const string& getAttribute(const std::string& key) const {
        auto it = _attributes.find(key);
        if (it != _attributes.end())
            return it->second;
        else
            return _noAttribute;
    }

    void setAttribute(const string& key, const string& value) {
        _attributes[key] = value;
    }

    void resetAttribute(const string& key) {
        _attributes.erase(key);
    }

    Dimension dimensionWidth;
    Dimension dimensionHeight;
    int32_t alignment = 0;
    float* measureResult = nullptr;
    float* layoutResult = nullptr;
};

struct Color {
    char r;
    char g;
    char b;
    Color(char r, char g, char b) : r(r), g(g), b(b) {}
    bool operator==(const Color& other) const {
        return (r == other.r && g == other.g && b == other.b);
    }
    bool operator!=(const Color& other) const {
        return !(r == other.r && g == other.g && b == other.b);
    }
};
#pragma pack(push, 1)
struct TGAHeader {
    uint8_t  idLength;
    uint8_t  colorMapType;
    uint8_t  imageType;
    uint16_t colorMapOrigin;
    uint16_t colorMapLength;
    uint8_t  colorMapDepth;
    uint16_t xOrigin;
    uint16_t yOrigin;
    uint16_t width;
    uint16_t height;
    uint8_t  bitsPerPixel;
    uint8_t  imageDescriptor;
};
#pragma pack(pop)

const unsigned char tga_tail[26] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x54, 0x52,
    0x55, 0x45, 0x56, 0x49, 0x53, 0x49, 0x4f, 0x4e, 0x2d, 0x58,
    0x46, 0x49, 0x4c, 0x45, 0x2e, 0x00
}; // TRUEVISION-XFILE.
struct TGAInfo {
    TGAHeader header;
    std::vector<char> pixels;
};

const std::string baseGoldenPath = "../ets-tests/ets/golden-tests/golden/";
const std::string baseBuildPath = "../ets-tests/build/golden/";

bool WriteImageTGA(std::string name, TGAInfo &info) {
    fprintf(stderr, "image: %s %s\n", std::filesystem::current_path().c_str(), name.c_str());
    std::ofstream file(name + ".tga", std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        fprintf(stderr, "Cannot write image: %s\n", name.c_str());
        INTEROP_FATAL("Error");
        return false;
    }
    info.header.imageType = 2; // Uncompressed RGB
    info.header.bitsPerPixel = 24; // 24-bit RGB

    file.write(reinterpret_cast<const char*>(&info.header), sizeof(TGAHeader));
    file.write(reinterpret_cast<const char*>(info.pixels.data()), info.header.width * info.header.height * 3);

    file.close();
    return true;
}

bool ReadImageTGA(std::string name, TGAInfo &info) {
    fprintf(stderr, "image: %s %s\n", std::filesystem::current_path().c_str(), name.c_str());
    std::ifstream file(name + ".tga", std::ios::binary);
    if (!file.is_open()) {
        fprintf(stderr, "Cannot read image: %s\n", name.c_str());
        INTEROP_FATAL("Error");
        return false;
    }
    file.read(reinterpret_cast<char*>(&info.header), sizeof(TGAHeader));
    uint32_t size = info.header.width * info.header.height * (info.header.bitsPerPixel / 8);
    info.pixels.resize(size);
    file.read(reinterpret_cast<char*>(info.pixels.data()), size);
    file.close();
    return true;
}

bool WriteDiffTGA(std::string name, std::vector<char> &golden, std::vector<char> &target, TGAHeader &header) {
    uint32_t size = header.width * header.height * (header.bitsPerPixel / 8);
    std::vector<uint8_t> pixels(size);
    for(uint32_t i = 0; i < size; i += 3) {
        // BGR
        pixels[i] = 0x00;
        pixels[i + 1] = 0x00;
        Color gld(golden[i], golden[i + 1], golden[i + 2]);
        Color trg(target[i], target[i + 1], target[i + 2]);
        if (trg != gld) {
            pixels[i + 2] = 0xFF;
        } else {
            pixels[i + 2] = 0x00;
        }
    }
    std::ofstream file(name + ".tga", std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        fprintf(stderr, "Cannot write image: %s\n", name.c_str());
        INTEROP_FATAL("Error");
        return false;
    }
    file.write(reinterpret_cast<const char*>(&header), sizeof(TGAHeader));
    file.write(reinterpret_cast<const char*>(pixels.data()), size);
    file.close();

    return true;
}

bool CompareTwoTGA(std::string name, TGAInfo golden, TGAInfo target) {
    bool result = true;
    if (golden.pixels.size() != target.pixels.size()) {
        fprintf(stderr, "Image sizes is not identical! Golden: %ld vs Target: %ld\n", golden.pixels.size(), target.pixels.size());
        INTEROP_FATAL("Error");
        return false;
    }
    for(uint32_t i = 0; i < golden.pixels.size(); i++) {
        auto gld = golden.pixels[i];
        auto trg = target.pixels[i];
        if (trg != gld) {
            result = false;
            break;
        }
    }
    if (!result) {
        WriteImageTGA(baseBuildPath + std::string(name), golden);
        WriteDiffTGA(baseBuildPath + std::string(name + "_diff"), golden.pixels, target.pixels, golden.header);
    }
    return result;
}

bool StubTGA(std::string name, TGAInfo &info) {
    fprintf(stderr, "image: %s %s\n", std::filesystem::current_path().c_str(), name.c_str());
    std::ofstream file(name + ".tga", std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        fprintf(stderr, "Cannot write stub image: %s\n", name.c_str());
        INTEROP_FATAL("Error");
        return false;
    }

    uint32_t size = info.header.width * info.header.height * (info.header.bitsPerPixel / 8);
    info.pixels.resize(size);

    for(uint32_t i = 0; i < size; i++) {
        info.pixels[i] = 0x80;
    }

    file.write(reinterpret_cast<const char*>(&info.header), sizeof(TGAHeader));
    file.write(reinterpret_cast<const char*>(info.pixels.data()), info.header.width * info.header.height * 3);

    file.close();
    return true;
}

void CopyTGAHeaders(TGAInfo &from, TGAInfo &to) {
    to.header.idLength = from.header.idLength;
    to.header.colorMapDepth = from.header.colorMapDepth;
    to.header.colorMapLength = from.header.colorMapLength;
    to.header.colorMapOrigin = from.header.colorMapOrigin;
    to.header.colorMapType = from.header.colorMapType;
    to.header.imageDescriptor = from.header.imageDescriptor;
    to.header.imageType = from.header.imageType;
    to.header.bitsPerPixel = from.header.bitsPerPixel;
    to.header.width = from.header.width;
    to.header.height = from.header.height;
    to.header.xOrigin = from.header.xOrigin;
    to.header.yOrigin = from.header.yOrigin;
}